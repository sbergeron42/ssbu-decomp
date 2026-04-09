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
CLANG = os.environ.get("DECOMP_CLANG", r"C:\llvm-8.0.0\bin\clang++.exe")
CFLAGS = ("-target aarch64-none-elf -mcpu=cortex-a57 -O2 -std=c++17 "
          "-fno-exceptions -fno-rtti -ffunction-sections -fdata-sections "
          "-fno-common -fno-short-enums -fPIC -mno-implicit-float "
          "-fno-strict-aliasing -fno-slp-vectorize -DMATCHING_HACK_NX_CLANG "
          "-Iinclude -Ilib/NintendoSDK/include -Ilib/NintendoSDK/include/stubs")
# NX Clang compat flags (only effective with the patched compiler from
# decomp-compiler-fork). Set DECOMP_NX_CFLAGS env var to enable.
# Recommended: "-mllvm -aarch64-nx-prologue"
#   Prologue patch: +91 matches, +5,852 bytes in testing.
#   Other patches (movz, return-width, epilogue) cause regressions
#   because they apply unconditionally; keep their post-processing scripts.
NX_CFLAGS = os.environ.get("DECOMP_NX_CFLAGS", "")
if NX_CFLAGS:
    CFLAGS = CFLAGS + " " + NX_CFLAGS


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
    """Run a post-processing tool on all matching .o files in a single invocation."""
    tool_path = PROJECT_ROOT / "tools" / tool
    if not tool_path.exists():
        return
    # Use relative paths + cwd to stay within Windows command line length limit
    matching = glob.glob(glob_pattern, root_dir=str(PROJECT_ROOT))
    if not matching:
        return
    subprocess.run(
        ['python', str(tool_path)] + matching,
        cwd=str(PROJECT_ROOT),
        capture_output=True
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

    # Post-processing (sequential — parallel was tested and causes regressions
    # due to tools writing to the same .o files concurrently)
    print()
    print("Post-processing...")

    print("  fix_plt_stubs...")
    run_postprocess("fix_plt_stubs.py")

    # Skip post-processing scripts that are superseded by compiler NX flags.
    # When NX_CFLAGS contains the corresponding -mllvm flag, the compiler
    # handles the fix natively and running the script would conflict.
    if "-aarch64-nx-movz" not in NX_CFLAGS:
        print("  fix_movz_to_orr...")
        run_postprocess("fix_movz_to_orr.py")
    else:
        print("  fix_movz_to_orr... SKIPPED (compiler handles it)")

    if "-aarch64-nx-prologue" not in NX_CFLAGS:
        print("  fix_prologue_sched...")
        run_postprocess("fix_prologue_sched.py")
    else:
        print("  fix_prologue_sched... SKIPPED (compiler handles it)")

    if "-aarch64-nx-epilogue" not in NX_CFLAGS:
        print("  gen_epilogue_list + fix_epilogue...")
        subprocess.run(
            'python "%s"' % (PROJECT_ROOT / "tools" / "gen_epilogue_list.py"),
            shell=True, capture_output=True
        )
        for pattern in ["fun_batch_c_*.o", "fun_batch_d_*.o", "fun_batch_e2_*.o"]:
            run_postprocess("fix_epilogue.py", "build/" + pattern)
    else:
        print("  fix_epilogue... SKIPPED (compiler handles it)")

    # Oracle scripts (read original binary) — disabled for honest matching.
    # These produce "matches" by peeking at the answer key, not by applying
    # known blind transforms.  Kept in repo for analysis but not in pipeline.
    #   fix_return_width.py  — peeks at original to decide 32/64 width
    #   fix_x8_regalloc.py   — peeks at original to verify register rewrite
    #   fix_insn_reorder.py  — copies instruction order from original
    #   fix_commutative.py   — peeks at original to decide swap direction

    print()
    print("Build complete.")


if __name__ == '__main__':
    main()
