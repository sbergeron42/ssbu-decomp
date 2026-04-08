# SSBU Decomp

A matching decompilation of **Super Smash Bros. Ultimate** (Nintendo Switch, AArch64).

Targeting the final version: **patch 13.0.4**.

## Progress

<!-- Verified by tools/verify_all.py against real 13.0.4 binary -->

### By function count

| Category | Count | % of total |
|----------|------:|------------|
| **Total functions** | 39,635 | |
| Verified byte-identical | 10,123 | 25.54% |
| Compiled (non-matching) | 3,331 | 8.40% |
| **Total decompiled** | **13,454** | **33.94%** |
| Undecompiled | 26,181 | 66.06% |

### By bytes (.text)

| Category | Size | % of .text |
|----------|-----:|------------|
| **.text total** | **27.0 MB** | |
| Compiled | 1.69 MB | 6.24% |
| Byte-matched | 0.47 MB | 1.75% |

```
By functions:  13,454 / 39,635  (33.94% compiled, 25.54% verified)
By bytes:       1.69M / 27.0M   ( 6.24% compiled,  1.75% verified)
```

> Progress skews toward small functions: avg matched function is 46 bytes vs
> avg undecompiled 967 bytes. Byte-weighted progress is the more accurate
> measure of source recovery. Both metrics are shown for transparency.
>
> Naked asm functions (569) are binary-identical but not real source recovery
> -- they are tracked separately from C++ decomp.

### Counting methodology

**Total functions (39,635):** Every function entry in `data/functions.csv`, derived from Ghidra analysis of the 13.0.4 binary. Function boundaries are Ghidra's best estimate — some may be over-sized (trailing alignment padding) or split (one function misidentified as two).

**Compiled:** Count of unique CSV addresses where `verify_all.py` successfully matched a compiled `.o` symbol to an original binary address and compared bytes. This is address-deduplicated — if two `.o` symbols resolve to the same binary address, it counts as one. The `.o` file count (~676 files, ~16,000 symbols) is higher because of duplicate definitions across compilation units.

**Verified (byte-identical):** Subset of compiled where every instruction matches the original binary after relocation patching. Relocations (BL/ADRP/ADD targets) are resolved in-place using symbol addresses from the CSV, so a function with correct instructions but unlinked `bl #0` still counts as verified if the relocation target is correct.

**Non-matching:** Compiled but not byte-identical. Causes include: NX Clang register allocation divergence, prologue scheduling, shrink-wrapping, wrong source code, or missing code paths.

**Match rate:** `verified / (verified + non-matching)` — percentage of compiled functions that byte-match. Does NOT include uncompiled functions in the denominator.

**Tools:** `tools/verify_all.py --update` is the authoritative source. `tools/update_readme.py` reads from verify_all.py output + CSV. `tools/progress.py` provides an alternate view.

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

## Compiler Gap: NX Clang vs Upstream

The original binary was compiled with **Nintendo's proprietary NX Clang fork** (based on Clang/LLVM 8.0.0 from SDK 8.2.1). This project uses **upstream Clang 8.0.0** for decomp, which produces identical output for small leaf functions but diverges significantly on non-trivial code.

**Measured divergence:** Compiling zstd v1.3.7 (confirmed same version as in-binary) with upstream Clang 8.0.0 produces functions with identical sizes but 0% instruction match — different register allocation, instruction selection, and code layout. This is not a post-processing gap; it's a fundamental backend divergence in Nintendo's LLVM fork.

**What this means:**
- **Small functions** (accessors, thunks, simple dispatchers): upstream Clang matches. These make up the bulk of current verified matches.
- **Library code** (~6-15MB of jemalloc, zstd, Lua, curl, NintendoSDK): can be identified and typed using upstream source, but cannot be byte-matched without the NX compiler. These functions are tracked as identified but non-matching.
- **Complex game logic** (state machines, physics, AI): requires manual decomp guided by Ghidra, iterating on source until the upstream compiler output matches. Some will never match due to irreducible compiler differences.

Byte-matched progress reflects the subset of the binary where upstream Clang produces identical output to NX Clang.

## Build Info

| Property | Value |
|----------|-------|
| Game | Super Smash Bros. Ultimate v13.0.4 |
| Platform | Nintendo Switch (NX64 / AArch64) |
| Engine | cross2app (Bandai Namco) |
| SDK | NintendoSDK 8.2.1 |
| Original compiler | NX Clang (proprietary LLVM fork, SDK 8.2.1) |
| Decomp compiler | Upstream Clang 8.0.0 |
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

## AI-Assisted Methodology

This project uses [Claude Code](https://claude.ai/code) as an accelerator within a human-led decomp workflow. Here's what the AI does and doesn't do.

### What the AI handles

- **Cross-referencing functions to discover struct layouts.** The AI reads dozens of functions that access the same struct offset, determines the field type from usage patterns, and builds struct definitions. Tedious work that benefits from processing hundreds of functions at once.
- **Writing C++ against known types.** Given a Ghidra decompilation and the project's struct headers, the AI rewrites functions using proper field access, compiles, and iterates on matching. The types come from external sources (see below) — the AI does the mechanical translation.
- **Bulk pattern fixes.** Identifying systematic mismatches (e.g., abort stubs that should be `__throw_out_of_range`) across thousands of functions and fixing them in batch.
- **Post-processing script development.** Writing `fix_*.py` binary patchers that close known NX Clang divergences (prologue scheduling, movz/orr encoding, return width, etc.).

### What the AI doesn't do

- **Name fields without evidence.** Every struct field traces back to a verifiable source: binary `.dynsym` symbols, ARCropolis/smash-arc community types, or cross-referenced function behavior. Fields without evidence are left as `unk_0xNN` or tagged `[inferred:]`.
- **Override community knowledge.** Resource service types use the exact names from ARCropolis and smash-arc. Module names come from the binary's exported symbols. The AI doesn't invent alternative naming.
- **Claim understanding it doesn't have.** When a function's purpose is unclear, it's documented as such — not given a speculative name.

### Verification chain

1. **Structural correctness** — every decompiled function is byte-compared against the original 13.0.4 binary by `tools/verify_all.py`. Wrong offsets, wrong types, or wrong control flow cause verification failure. This is automated and runs on every merge.
2. **Naming provenance** — struct headers carry `[derived:]` and `[inferred:]` tags showing how each field name was determined. See the [Naming Provenance](#naming-provenance) table above.
3. **Community-sourced types** — resource service structs are sourced from [ARCropolis](https://github.com/Raytwo/ARCropolis) and [smash-arc](https://github.com/jam1garner/smash-arc), which have been validated by the modding community over 7 years of use.

### Multi-agent workflow

The project uses parallel Claude Code sessions ("pools") working on isolated git worktrees. An orchestrator merges verified work to master. Each pool has exclusive file territory to prevent conflicts. Worker rules (in CLAUDE.md) enforce quality gates: no naked asm as a first approach, no Ghidra paste copy, 3-attempt limit per function, mandatory provenance tags.

## License

This project does not contain any original game code or assets. All decompiled source is written from scratch based on reverse engineering of the publicly available binary.
