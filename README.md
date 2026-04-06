# SSBU Decomp

A matching decompilation of **Super Smash Bros. Ultimate** (Nintendo Switch, AArch64).

Targeting the final version: **patch 13.0.4**.

## Progress

<!-- Verified by tools/verify_all.py against real 13.0.4 binary -->

| Category | Count | Percentage |
|----------|------:|------------|
| **Total functions** | 39,635 | |
| Verified byte-identical | 8,388 | 21.16% |
| Compiled (non-matching) | 6,899 | 17.41% |
| **Total decompiled** | **15,287** | **38.57%** |
| Undecompiled | 24,348 | 61.43% |

```
Verified  [########                                ]  8,388 / 39,635  (21.16%)
Compiled  [###############                         ]  15,287 / 39,635  (38.57%)
```

> **8,388 functions verified byte-identical** against the real 13.0.4 binary.
> 56.9% match rate on verified functions. Autonomous multi-agent orchestrator operational.

## Naming Provenance

This project's naming comes from sources with different confidence levels:

| Source | Count | Evidence |
|--------|------:|----------|
| Binary .dynsym exports | 4,888 | **Ground truth** — mangled C++ symbols in the ELF |
| Vtable method names | ~800 | Derived from .dynsym names via decompilation + byte-match |
| Module accessor offsets | 41 | Structural — verified by byte-matching |
| Community Ghidra labels | ~10,191 | Human-assigned during RE, ported from 13.0.1 — no formal provenance |
| Struct field names | ~260 | Inferred from function behavior — offsets verified, names are best guesses |

Struct headers use derivation comments to show how each field name was determined.
Fields tagged `[derived: ...]` trace back to binary-proven function names.
Fields tagged `[inferred: ...]` are usage-pattern guesses — verify before building on them.

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

Link into a shared ELF for verification:

```bash
ld.lld -shared -o build/ssbu-decomp.elf build/*.o \
  -Bsymbolic-functions --unresolved-symbols=ignore-all --no-undefined-version
```

## Verification

```bash
python tools/verify_all.py --summary
```

Or use [viking](https://github.com/open-ead/nx-decomp-tools) for semantic comparison:

```bash
tools/common/nx-decomp-tools/viking/target/release/check.exe FunctionName
```

## Project Structure

```
src/           Decompiled C++ source
include/       Headers (game structs, SDK types)
data/          Function database (functions.csv), original ELF
tools/         Build, diff, and verification scripts
tools/common/  nx-decomp-tools submodule (viking, asm-differ)
config/        Symbol maps, matching targets
```

## Tools

- `tools/verify_all.py` — Byte-compare all compiled functions against original binary
- `tools/gen_from_elf.py` — Auto-generate vtable dispatch functions from original ELF
- `tools/fix_params.py` — Fix parameter counts using original binary analysis
- `tools/migrate_csv.py` — Convert functions.csv between formats
- `tools/diff_function.py` — Compare compiled assembly against target

## References

- [KinokoDecomp-S](https://github.com/Moddimation/KinokoDecomp-S) — Captain Toad decomp (same SDK generation, primary reference)
- [zeldaret/botw](https://github.com/zeldaret/botw) — BotW decomp (pioneered the upstream Clang approach)
- [ultimate-research](https://github.com/ultimate-research) — SSBU RE community
- [decomp.me](https://decomp.me/) — Collaborative decomp scratchpad (supports Switch/AArch64)

## License

This project does not contain any original game code or assets. All decompiled source is written from scratch based on reverse engineering of the publicly available binary.
