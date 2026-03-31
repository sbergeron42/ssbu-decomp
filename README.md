# SSBU Decomp

A matching decompilation of **Super Smash Bros. Ultimate** (Nintendo Switch, AArch64).

Targeting the final version: **patch 13.0.4**.

## Progress

<!-- Verified by tools/verify_all.py against real 13.0.4 binary -->

| Category | Count | Percentage |
|----------|------:|------------|
| **Total functions** | 39,635 | |
| Verified matching | 474 | 1.20% |
| Compiled (pending verification) | 1,178 | 2.97% |
| **Total decompiled** | **1,652** | **4.17%** |
| Undecompiled | 37,983 | 95.83% |

```
Verified  [#                                       ]    474 / 39,635  (1.20%)
Compiled  [##                                      ]  1,652 / 39,635  (4.17%)
```

> **474 functions verified byte-identical** against the real 13.0.4 binary.
> 1,178 more compiled and awaiting improved address mapping for verification.

## Build Info

| Property | Value |
|----------|-------|
| Game | Super Smash Bros. Ultimate v13.0.4 |
| Platform | Nintendo Switch (NX64 / AArch64) |
| Engine | cross2app (Bandai Namco) |
| SDK | NintendoSDK 8.2.1 |
| Compiler | Upstream Clang 8.0.0 |
| .text size | ~60 MB |

## Building

Requires [LLVM/Clang 8.0.0](https://releases.llvm.org/8.0.0/) installed to `C:\llvm-8.0.0\` (or update path in `build.bat`).

```bat
build.bat
```

Or manually:

```bash
clang++ -target aarch64-none-elf -mcpu=cortex-a57 -O2 -std=c++17 \
  -fno-exceptions -fno-rtti -ffunction-sections -fdata-sections \
  -fno-common -fno-short-enums -fPIC -mno-implicit-float \
  -fno-strict-aliasing -fno-slp-vectorize -DMATCHING_HACK_NX_CLANG \
  -Iinclude -c src/app/modules/FighterAreaModuleImpl.cpp -o build/FighterAreaModuleImpl.o
```

Post-processing to fix NX Clang encoding differences:

```bash
python tools/fix_orr_movz.py build/*.o
```

## Project Structure

```
src/           Decompiled C++ source
include/       Headers (game structs, SDK types)
asm/           Expected assembly from the original binary
data/          Function database (functions.csv)
tools/         Build, diff, and verification scripts
toolchain/     CMake cross-compilation config
config/        Symbol maps, matching targets
```

## Tools

- `tools/progress.py` — Show decompilation progress
- `tools/fix_orr_movz.py` — Post-process compiled objects (NX Clang encoding fix)
- `tools/diff_function.py` — Compare compiled assembly against target
- `tools/mark_status.py` — Update function status in the database

## References

- [KinokoDecomp-S](https://github.com/Moddimation/KinokoDecomp-S) — Captain Toad decomp (same SDK generation, primary reference)
- [zeldaret/botw](https://github.com/zeldaret/botw) — BotW decomp (pioneered the upstream Clang approach)
- [ultimate-research](https://github.com/ultimate-research) — SSBU RE community
- [decomp.me](https://decomp.me/) — Collaborative decomp scratchpad (supports Switch/AArch64)

## License

This project does not contain any original game code or assets. All decompiled source is written from scratch based on reverse engineering of the publicly available binary.
