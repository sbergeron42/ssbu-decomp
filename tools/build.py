#!/usr/bin/env python3
"""
Incremental build for SSBU decomp. Only recompiles changed .cpp files.
Runs all post-processing on all .o files (idempotent).

Usage:
    python tools/build.py          # Incremental build
    python tools/build.py --full   # Force full rebuild
"""

import os
import subprocess
import sys
import glob
from pathlib import Path

PROJECT_ROOT = Path(__file__).parent.parent
SRC_DIR = PROJECT_ROOT / "src"
BUILD_DIR = PROJECT_ROOT / "build"
CLANG = r"C:\llvm-8.0.0\bin\clang++.exe"
CFLAGS = ("-target aarch64-none-elf -mcpu=cortex-a57 -O2 -std=c++17 "
          "-fno-exceptions -fno-rtti -ffunction-sections -fdata-sections "
          "-fno-common -fno-short-enums -fPIC -mno-implicit-float "
          "-fno-strict-aliasing -fno-slp-vectorize -DMATCHING_HACK_NX_CLANG "
          "-Iinclude -Ilib/NintendoSDK/include -Ilib/NintendoSDK/include/stubs")


def needs_rebuild(cpp_path, o_path):
    """Check if .o needs rebuilding based on mtime."""
    if not o_path.exists():
        return True
    return cpp_path.stat().st_mtime > o_path.stat().st_mtime


def compile_file(cpp_path, o_path):
    """Compile a single .cpp file."""
    result = subprocess.run(
        '%s %s -c "%s" -o "%s"' % (CLANG, CFLAGS, cpp_path, o_path),
        shell=True, capture_output=True, text=True
    )
    if result.returncode != 0:
        print("  ERROR: %s" % cpp_path.name)
        print(result.stderr[:500])
        return False
    return True


def run_postprocess(tool, glob_pattern="build/*.o"):
    """Run a post-processing tool on matching .o files."""
    tool_path = PROJECT_ROOT / "tools" / tool
    if not tool_path.exists():
        return
    for o_file in glob.glob(str(PROJECT_ROOT / glob_pattern)):
        subprocess.run(
            'python "%s" "%s"' % (tool_path, o_file),
            shell=True, capture_output=True
        )


def main():
    full_rebuild = '--full' in sys.argv
    BUILD_DIR.mkdir(exist_ok=True)

    # Find all .cpp files
    cpp_files = list(SRC_DIR.rglob("*.cpp"))
    print("Source files: %d" % len(cpp_files))

    # Compile
    compiled = 0
    skipped = 0
    errors = 0
    for cpp in cpp_files:
        o_path = BUILD_DIR / (cpp.stem + ".o")
        if not full_rebuild and not needs_rebuild(cpp, o_path):
            skipped += 1
            continue
        print("  %s" % cpp.name)
        if compile_file(cpp, o_path):
            compiled += 1
        else:
            errors += 1

    print()
    print("Compiled: %d, Skipped: %d, Errors: %d" % (compiled, skipped, errors))

    if errors > 0:
        print("BUILD FAILED with %d error(s)." % errors)
        # Continue to post-processing anyway — other .o files are fine

    # Post-processing (always runs on all .o files — idempotent)
    print()
    print("Post-processing...")

    print("  fix_movz_to_orr...")
    run_postprocess("fix_movz_to_orr.py")

    print("  fix_prologue_sched...")
    run_postprocess("fix_prologue_sched.py")

    print("  gen_epilogue_list + fix_epilogue...")
    subprocess.run(
        'python "%s"' % (PROJECT_ROOT / "tools" / "gen_epilogue_list.py"),
        shell=True, capture_output=True
    )
    for pattern in ["fun_batch_c_*.o", "fun_batch_d_*.o", "fun_batch_e2_*.o"]:
        run_postprocess("fix_epilogue.py", "build/" + pattern)

    print("  fix_return_width...")
    run_postprocess("fix_return_width.py")

    print("  fix_x8_regalloc...")
    run_postprocess("fix_x8_regalloc.py")

    print("  fix_insn_reorder...")
    run_postprocess("fix_insn_reorder.py")

    print()
    print("Build complete.")


if __name__ == '__main__':
    main()
