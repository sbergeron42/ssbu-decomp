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

## Compiler
- NX Clang (Nintendo's proprietary Clang/LLVM fork)
- SDK 8.2.1 → **upstream Clang 8.0.0** (confirmed via KinokoDecomp-S)
- Installed at `C:\llvm-8.0.0\`
- Key flags: `-target aarch64-none-elf -mcpu=cortex-a57 -O2 -fPIC -mno-implicit-float -fno-strict-aliasing -fno-slp-vectorize -DMATCHING_HACK_NX_CLANG`
- Post-processing: `tools/fix_orr_movz.py` patches `orr Wd, wzr, #imm` → `movz Wd, #imm`
- Known NX fork divergence: prologue frame pointer scheduling in non-leaf functions
- Use `asm("")` barriers (guarded by `MATCHING_HACK_NX_CLANG`) for instruction ordering issues

## Project Structure
- `src/` — Decompiled C++ source files
- `include/` — Headers (game structs, SDK types)
- `asm/` — Non-matching assembly stubs
- `tools/` — Build/diff/verification scripts
- `config/` — Symbol maps, linker scripts, build config
- `data/` — Data tables, constants extracted from binary

## Reference Projects
- BotW decomp (zeldaret/botw) — primary template for project structure and toolchain
- Melee decomp — automation scripts template

## Conventions
- Function names use the naming from the Skyline/ultimate-research modding community where available
- Use `app::` namespace prefix matching the binary's symbol table
- Module accessor pattern: `BattleObjectModuleAccessor*` is the standard first param for module impl functions
