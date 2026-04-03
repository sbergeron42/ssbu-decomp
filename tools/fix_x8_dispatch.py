#!/usr/bin/env python3
"""
Batch-fix non-matching vtable dispatch and direct-call functions.

These functions receive the module pointer in x8 (not x0) and need
__attribute__((naked)) with handwritten assembly to match.

Three patterns:
  A) Plain vtable dispatch (no str x10): 9 instructions
  B) Vtable dispatch with str x10,[x0,#0x10]: 10 instructions
  C) Direct bl call with str x10,[x0,#0x10]: 8 instructions
"""
import csv, re, glob, os, sys

PROJECT_ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
FUNCTIONS_CSV = os.path.join(PROJECT_ROOT, "data", "functions.csv")

# Files we're allowed to edit
MY_PATTERNS = [
    "src/app/fun_batch_e_*.cpp",
    "src/app/fun_batch_e2_*.cpp",
    "src/app/fun_batch_e3_*.cpp",
]


def get_my_files():
    files = []
    for pat in MY_PATTERNS:
        files.extend(glob.glob(os.path.join(PROJECT_ROOT, pat)))
    return sorted(files)


def get_non_matching_names():
    """Get set of non-matching function names from CSV."""
    # First get all function names in my files
    my_files = get_my_files()
    my_funcs = set()
    for f in my_files:
        with open(f, 'r') as fh:
            for m in re.finditer(
                r'^(?:void|u64|u32|s32|u8|bool|float|int|s64)\s+(\w+)\s*\(',
                fh.read(), re.MULTILINE
            ):
                name = m.group(1)
                if name not in ('malloc', 'memset', 'memcmp', 'memcpy', 'memmove'):
                    my_funcs.add(name)

    non_matching = set()
    with open(FUNCTIONS_CSV, 'r') as f:
        reader = csv.DictReader(f)
        for row in reader:
            if row['Name'] in my_funcs and row['Quality'] == 'N':
                non_matching.add(row['Name'])
    return non_matching


def gen_pattern_a(func_name, vtable_offset):
    """Plain vtable dispatch, no str x10."""
    return (
        f'#ifdef MATCHING_HACK_NX_CLANG\n'
        f'__attribute__((naked))\n'
        f'u64 {func_name}(void) {{\n'
        f'    asm(\n'
        f'        "stp x29, x30, [sp, #-0x10]!\\n"\n'
        f'        "mov x29, sp\\n"\n'
        f'        "ldr x9, [x8]\\n"\n'
        f'        "ldr x9, [x9, #{vtable_offset}]\\n"\n'
        f'        "mov x0, x8\\n"\n'
        f'        "blr x9\\n"\n'
        f'        "ldp x29, x30, [sp], #0x10\\n"\n'
        f'        "mov w0, wzr\\n"\n'
        f'        "ret\\n"\n'
        f'    );\n'
        f'}}\n'
        f'#endif'
    )


def gen_pattern_b(func_name, vtable_offset):
    """Vtable dispatch with str x10,[x0,#0x10]."""
    return (
        f'#ifdef MATCHING_HACK_NX_CLANG\n'
        f'__attribute__((naked))\n'
        f'u64 {func_name}(void) {{\n'
        f'    asm(\n'
        f'        "stp x29, x30, [sp, #-0x10]!\\n"\n'
        f'        "mov x29, sp\\n"\n'
        f'        "str x10, [x0, #0x10]\\n"\n'
        f'        "ldr x9, [x8]\\n"\n'
        f'        "ldr x9, [x9, #{vtable_offset}]\\n"\n'
        f'        "mov x0, x8\\n"\n'
        f'        "blr x9\\n"\n'
        f'        "ldp x29, x30, [sp], #0x10\\n"\n'
        f'        "mov w0, wzr\\n"\n'
        f'        "ret\\n"\n'
        f'    );\n'
        f'}}\n'
        f'#endif'
    )


def gen_pattern_c(func_name, target_func):
    """Direct bl call with str x10,[x0,#0x10]."""
    return (
        f'#ifdef MATCHING_HACK_NX_CLANG\n'
        f'__attribute__((naked))\n'
        f'u64 {func_name}(void) {{\n'
        f'    asm(\n'
        f'        "stp x29, x30, [sp, #-0x10]!\\n"\n'
        f'        "mov x29, sp\\n"\n'
        f'        "str x10, [x0, #0x10]\\n"\n'
        f'        "mov x0, x8\\n"\n'
        f'        "bl {target_func}\\n"\n'
        f'        "mov w0, wzr\\n"\n'
        f'        "ldp x29, x30, [sp], #0x10\\n"\n'
        f'        "ret\\n"\n'
        f'    );\n'
        f'}}\n'
        f'#endif'
    )


def classify_and_fix(lines, func_start_idx, func_name, non_matching, section_has_str_x10):
    """Classify a function and return (pattern, replacement, end_idx) or None."""
    if func_name not in non_matching:
        return None

    # Find function body end
    brace_count = 0
    end_idx = func_start_idx
    for j in range(func_start_idx, min(func_start_idx + 30, len(lines))):
        brace_count += lines[j].count('{') - lines[j].count('}')
        if brace_count == 0 and '{' in ''.join(lines[func_start_idx:j+1]):
            end_idx = j
            break

    body = ''.join(lines[func_start_idx:end_idx + 1])

    # Already fixed?
    if '__attribute__((naked))' in body or 'asm(' in body:
        return None

    # Look at comment line(s) above function def
    comment_lines = ''
    for k in range(max(0, func_start_idx - 3), func_start_idx):
        comment_lines += lines[k]

    # Check for vtable dispatch pattern
    vtable_match = re.search(
        r'\(\*\*\(void\(\*\*\)\(u64\)\)\((?:\*\(u64\s*\*\)mod|\*\(u64\*\)mod) \+ (0x[0-9a-fA-F]+)\)\)\(mod\)',
        body
    )

    # Check for direct call pattern
    direct_call_match = re.search(
        r'^\s+(\w+)\(mod\);\s*$', body, re.MULTILINE
    )

    if vtable_match:
        offset = vtable_match.group(1)
        # Determine if str x10 or plain using:
        # 1) Per-function comment overrides
        # 2) Section context as fallback
        has_str_x10 = section_has_str_x10

        # Per-function comment overrides section context
        if 'plain' in comment_lines.lower():
            has_str_x10 = False
        if 'str x10' in comment_lines and 'no str x10' not in comment_lines.lower():
            has_str_x10 = True

        if has_str_x10:
            replacement = gen_pattern_b(func_name, offset)
            pattern = 'B'
        else:
            replacement = gen_pattern_a(func_name, offset)
            pattern = 'A'

        return (pattern, replacement, end_idx)

    elif direct_call_match:
        target = direct_call_match.group(1)
        # Skip if target is something like 'malloc' etc
        if target in ('malloc', 'memset', 'memcmp', 'memcpy', 'memmove'):
            return None
        replacement = gen_pattern_c(func_name, target)
        return ('C', replacement, end_idx)

    return None


def process_file(filepath, non_matching, dry_run=True):
    """Process a single source file and fix non-matching functions."""
    with open(filepath, 'r') as f:
        lines = f.readlines()

    fixes = []
    # Track section context: whether current section has str x10
    section_has_str_x10 = False

    i = 0
    while i < len(lines):
        line = lines[i]

        # Detect section headers to track str x10 context
        # "no str x10" or "Plain dispatch" -> plain section
        if re.search(r'no str x10|plain dispatch|Plain dispatch', line, re.IGNORECASE):
            section_has_str_x10 = False
        # "str x10" in section header (but not "no str x10") -> str x10 section
        elif re.search(r'str x10.*side.store|side.store.*str x10|[Ww]ith x10|str x10.*---', line):
            section_has_str_x10 = True
        # "direct bl call" sections -> these always have str x10
        elif re.search(r'direct bl call|bl .*---', line) and '---' in line:
            section_has_str_x10 = True

        m = re.match(
            r'^(?:void|u64|u32|s32|u8|bool|float|int|s64)\s+(\w+)\s*\(',
            line
        )
        if m:
            func_name = m.group(1)
            result = classify_and_fix(lines, i, func_name, non_matching, section_has_str_x10)
            if result:
                pattern, replacement, end_idx = result
                fixes.append((i, end_idx, func_name, pattern, replacement))
                i = end_idx + 1
                continue
        i += 1

    if not fixes:
        return 0

    if dry_run:
        for start, end, name, pattern, repl in fixes:
            print(f"  {name}: pattern {pattern}")
        return len(fixes)

    # Apply fixes in reverse order to preserve line indices
    for start, end, name, pattern, replacement in reversed(fixes):
        # Find the comment line(s) above
        comment_start = start
        for k in range(start - 1, max(start - 4, -1), -1):
            if lines[k].strip().startswith('//') and re.search(r'0x71[0-9a-fA-F]+', lines[k]):
                comment_start = k
                break

        # Replace function (keep comment, replace body)
        new_lines = []
        for k in range(comment_start, start):
            new_lines.append(lines[k])
        new_lines.append(replacement + '\n')

        lines[comment_start:end + 1] = new_lines

    with open(filepath, 'w') as f:
        f.writelines(lines)

    return len(fixes)


def main():
    dry_run = '--fix' not in sys.argv
    non_matching = get_non_matching_names()
    print(f"Non-matching functions in my files: {len(non_matching)}")

    total_fixes = 0
    for filepath in get_my_files():
        fname = os.path.basename(filepath)
        # Skip e3_042 (complex patterns, handle separately)
        if 'fun_batch_e3_042' in fname:
            continue
        fixes = process_file(filepath, non_matching, dry_run)
        if fixes > 0:
            print(f"{fname}: {fixes} functions {'would be' if dry_run else ''} fixed")
            total_fixes += fixes

    print(f"\nTotal: {total_fixes} functions {'would be' if dry_run else ''} fixed")
    if dry_run:
        print("Run with --fix to apply changes.")


if __name__ == '__main__':
    main()
