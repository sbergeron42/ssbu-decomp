# SSBU Decomp — Matching Decompilation of Super Smash Bros. Ultimate

## Project Overview
Matching decompilation of SSBU (Nintendo Switch, AArch64) targeting patch 13.0.4 (final version).

## Target Binary
- **Game**: Super Smash Bros. Ultimate v13.0.4
- **Platform**: Nintendo Switch (NX64 / AArch64)
- **Engine**: cross2app (Bandai Namco proprietary)
- **SDK**: NintendoSDK 8.2.1
- **Build path**: `C:/c2/p4/patch-13.0.1/work/build/vs2015.built/cross2app+standalone/NX64/Release/`
- **Binary format**: NSO (compressed ELF)
- **.text size**: ~60 MB
- **Total functions**: 39,635 (9,298 named by community)

## Compiler
- NX Clang (Nintendo's proprietary Clang/LLVM fork)
- SDK 8.2.1 → **upstream Clang 8.0.0** (confirmed via KinokoDecomp-S)
- Installed at `C:\llvm-8.0.0\`
- Key flags: `-target aarch64-none-elf -mcpu=cortex-a57 -O2 -fPIC -mno-implicit-float -fno-strict-aliasing -fno-slp-vectorize -DMATCHING_HACK_NX_CLANG`
- Post-processing: `tools/fix_orr_movz.py` patches `orr Wd, wzr, #imm` → `movz Wd, #imm`
- Known NX fork divergence: prologue frame pointer scheduling in non-leaf functions
- Use `asm("")` barriers (guarded by `MATCHING_HACK_NX_CLANG`) for instruction ordering issues

## Project Structure
- `src/` — Decompiled C++ source files (44 files)
- `include/` — Headers (game structs, SDK types)
- `asm/` — Expected assembly from Ghidra (for diffing)
- `tools/` — Build/diff/verification scripts
- `config/` — Symbol maps, first targets
- `data/` — Function database (functions.csv with 39,635 entries)

## Build
```bat
build.bat
```
Or: `python tools/progress.py` to check status.

## Module Accessor Pattern
Most `lua_bind` functions take `BattleObjectModuleAccessor*` as first param and dispatch to a sub-module via vtable. The accessor has module pointers at fixed offsets (+0x38 through +0x188). See `include/app/BattleObjectModuleAccessor.h` for the full layout.

Key module offsets: +0x38 Posture, +0x40 Status, +0x48 Control, +0x50 Work, +0x58 Ground, +0x60 Camera, +0x68 Kinetic, +0x88 Motion, +0xA0 Attack, +0xA8 Damage, +0xC0 Area, +0x140 Effect, +0x148 Sound.

## Conventions
- Function names use Skyline/ultimate-research modding community naming where available
- Use `app::lua_bind` namespace for all decompiled functions
- `BattleObjectModuleAccessor*` is the standard first param for module functions
- FighterManager, FighterInformation, BattleObjectSlow/World operate on their own struct pointers (not accessor)
- Vtable offset macros: `#define VT(m) (*reinterpret_cast<void***>(m))`

## Reference Projects
- KinokoDecomp-S (Captain Toad, same SDK 8.2.x) — primary reference for toolchain and patterns
- BotW decomp (zeldaret/botw) — pioneered upstream Clang approach
- decomp.me — hosts clang-8.0.0 for Switch platform
