# Super Smash Bros. Ultimate Decompilation — Research Notes

Starting point for a matching decompilation of SSBU (Nintendo Switch, AArch64).

## Target Binary

- **Game**: Super Smash Bros. Ultimate (SSBU)
- **Platform**: Nintendo Switch (NX64 / AArch64)
- **Developer**: Bandai Namco Studios / Sora Ltd.
- **Internal engine**: `cross2app` (Bandai Namco proprietary)
- **Build system**: Visual Studio 2015 solution, Perforce VCS
- **Binary format**: NSO (Nintendo Switch Object — compressed ELF)
- **Moveset scripts**: Lua compiled via `lua2cpp` into `.nrs` dynamic libraries

### Build path (from embedded strings in 13.0.4 binary)

```
C:\c2\p4\patch-13.0.1\work\build\vs2015.built\cross2app+standalone\NX64\Release\cross2_Release.nss
```

Note: Build path says `patch-13.0.1` even in the 13.0.4 binary — likely a minor hotfix on the same source branch.

### SDK path (from embedded strings)

```
C:/c2/nintendo/NintendoSDK-NXAddon/NintendoSDK/Libraries/NX-NXFP2-a64/Release/
```

### SDK & middleware versions (confirmed from 13.0.4 binary strings)

| Component | Version |
|-----------|---------|
| NintendoSDK | **8.2.1** |
| NintendoWare (Ui2d, Font, Vfx, G3d) | 8.2.1 |
| NEX (online services) | 4.6.13 |
| Pia (P2P networking) | 5.19.1 |
| libcurl | 8.2.1 (SDK-bundled) |
| libz | 8.2.1 (SDK-bundled) |

### Memory layout (from Ghidra, 13.0.4)

| Section | Start | End | Size |
|---------|-------|-----|------|
| .text | 7100000000 | 71039bfa8f | ~60 MB |
| .rodata.1 | 710424d304 | 7104f15f5f | ~12 MB |
| .data | 7104f16000 | 710529d747 | ~1.5 MB |
| .bss | 71052a9000 | 71074460ff | ~30 MB |

## Compiler

### What we know

- Nintendo Switch SDK uses a **proprietary fork of Clang/LLVM** ("NX Clang")
- Located at `NintendoSDK/Compilers/NX/nx/aarch64/bin/clang` in the SDK
- Nintendo presented their toolchain at the [2018 LLVM Developers' Meeting](https://llvmdev18.sched.com/event/H2U7/developer-toolchain-for-the-nintendo-switch)
- Early Switch titles (BotW, 2017) used a fork based on **Clang 4.0**
- SSBU shipped Dec 2018 with patches through 2021
- **SDK 8.2.1 → Clang 8.0.0** (confirmed by Captain Toad decomp using SDK 8.2.0 with Clang 8.0.0)

### SDK-to-Clang version mapping (known data points)

| Game | NintendoSDK | Upstream Clang |
|------|-------------|---------------|
| Super Mario Odyssey | ~3.x-4.x | **3.9.1** |
| Breath of the Wild v1.5.0 | ~4.x | **4.0.1** |
| Minecraft: Switch Edition | 4.4.1 | **4.0.1** |
| Captain Toad v1.3.0 | **8.2.0** | **8.0.0** |
| **SSBU v13.0.4** | **8.2.1** | **8.0.0** (confirmed) |

Sources: KinokoDecomp-S, decomp.me compiler repo, zeldaret/botw, Switchbrew

### The BotW approach (proven to work)

The [zeldaret/botw](https://github.com/zeldaret/botw) decomp project successfully uses **upstream open-source Clang 4.0.1** (not Nintendo's proprietary fork) to achieve matching builds. Where Nintendo's fork diverges from upstream, they use `#ifdef MATCHING_HACK_NX_CLANG` workarounds.

This means **you may not need the proprietary SDK compiler**. The right version of upstream Clang could match most code. The task is figuring out which upstream Clang version corresponds to SSBU's build.

### Determining the exact Clang version

Potential approaches:
1. **String dump the NSO** — look for embedded compiler version strings, `__clang_version__` macros, LLVM version metadata
2. **Compare codegen patterns** — compile test code with different Clang versions and compare instruction selection, register allocation, and scheduling against known SSBU functions
3. **Check SDK version** — if the NintendoSDK version can be identified from the binary, it maps to a known Clang base version
4. **Community knowledge** — the modding community may have already identified this

### Compiler testing results (2026-03-30)

Tested upstream Clang 7.0.1, 7.1.0, and 8.0.0 against three known functions.

**Flags that produce matches**: `-target aarch64-none-elf -mcpu=cortex-a57 -O2 -fPIC -mno-implicit-float -ffunction-sections -fdata-sections -fno-common -fno-exceptions -fno-rtti -std=c++17`

Key finding: **`-mno-implicit-float` is required** — without it, the compiler uses SIMD registers for zeroing memory (`movi v0.2d + str q0`) instead of scalar `str xzr` pairs.

**Results** (all three Clang versions produce identical output):

| Function | Match | Difference |
|----------|-------|------------|
| enable_fix_jostle_area_impl | 5/6 | `orr w9, wzr, #0x1` vs target's `mov w9, #0x1` (movz encoding) |
| enable_fix_jostle_area_xy_impl | **8/8** | Perfect match |
| disable_fix_jostle_area_impl | **7/7** | Perfect match |

**Known NX Clang divergence**: Upstream Clang uses `orr Wd, wzr, #imm` (logical immediate encoding `0x32xxxxxx`) for bitmask-representable values like 1. The target binary uses `movz Wd, #imm` (wide immediate encoding `0x52xxxxxx`). This is likely a Nintendo fork patch — BotW decomp handles similar differences with `MATCHING_HACK_NX_CLANG`.

**Recommendation**: Use **Clang 8.0.0** as the base compiler (matches SDK 8.2.1 era). The `orr`→`movz` difference is consistent across Clang 7.0.1, 7.1.0, and 8.0.0 — it's an upstream LLVM instruction selection choice. Nintendo's fork patches this. Handle with a post-processing script or patched Clang build.

### Reference decomp projects using same SDK generation

- **KinokoDecomp-S** (Captain Toad, SDK 8.2.0): https://github.com/Moddimation/KinokoDecomp-S — uses Clang 8.0.0
- **decomp.me** hosts `clang-8.0.0` for Switch platform

## Existing RE / Modding Community

No matching decomp project exists for SSBU yet. However, there is significant reverse engineering work already done:

### Key resources

| Resource | URL | What it provides |
|----------|-----|------------------|
| ultimate-research | https://github.com/ultimate-research | GitHub org with RE tools and findings |
| Skyline | https://github.com/skyline-dev/skyline | Runtime hooking/code patching framework |
| skyline-rs | https://github.com/ultimate-research/skyline-rs | Rust library for Switch game modding |
| nnsdk-rs | https://github.com/ultimate-research/nnsdk-rs | Unofficial Rust bindings for Nintendo SDK |
| smash-luadec | https://github.com/jam1garner/smash-luadec | Lua decompiler for moveset scripts |
| Smash Ultimate Docs | https://coolsonickirby.github.io/Smash-Ultimate-Documentation/ | Centralized modding/RE documentation |
| open-ead/nnheaders | https://github.com/open-ead | Open-source Nintendo SDK headers |
| open-ead/sead | https://github.com/open-ead/sead | Nintendo's standard C++ library (RE'd) |

### What exists already

- **Named functions**: The Skyline modding community has identified and named many game functions through hooking
- **SDK bindings**: `nnsdk-rs` provides unofficial bindings showing known SDK function signatures
- **Struct layouts**: Modders have reverse-engineered many game structs for gameplay modding
- **Lua scripts**: Moveset data has been decompiled — these aren't compiled C, but they document game behavior

## Reference Decomp Projects (templates)

### BotW decomp (closest template)

- **Repo**: https://github.com/zeldaret/botw
- **Status**: Active, significant progress
- **Target**: Switch version 1.5.0
- **Compiler**: Upstream Clang 4.0.1
- **Build system**: CMake + Ninja
- **Toolchain file**: `toolchain/ToolchainNX64.cmake`
- **Headers**: Uses open-ead/nnheaders (no proprietary SDK code)
- **Key files to study**:
  - `tools/setup.py` — compiler setup (`setup.set_up_compiler("4.0.1")`)
  - `toolchain/ToolchainNX64.cmake` — cross-compilation config
  - `CMakeLists.txt` — build structure
  - `diff_settings.py` — objdiff configuration

### Other Switch decomps

- **Splatoon 2**: https://github.com/splatoon-decomp (if it exists, check)
- **Mario Odyssey**: Community RE efforts exist

### Melee decomp (automation template)

- **Repo**: https://github.com/doldecomp/melee
- **Why relevant**: The overnight automation scripts can be adapted for any decomp project
- **Key scripts**: `scripts/decomp_overnight.sh`, `scripts/verify_match.py`

## Tooling Needed

### Binary extraction

- **hactool**: Extract NSO from Switch game dumps — https://github.com/SciresM/hactool
- **nx2elf**: Convert NSO to standard ELF for analysis — https://github.com/shuffle2/nx2elf

### Disassembly / Decompilation

- **Ghidra**: Free, supports AArch64 well, has a decompiler — https://ghidra-sre.org/
- **IDA Pro**: Commercial, excellent AArch64 support
- **m2c**: Assembly-to-C decompiler, supports ARM — https://github.com/matt-kempster/m2c
- **Binary Ninja**: Commercial, good ARM64 support

### Diffing / Verification

- **objdiff**: Binary diffing tool — https://github.com/encounter/objdiff (check ARM64 support)
- **asm-differ**: Instruction-level differ used by many decomp projects — https://github.com/simonlindholm/asm-differ
- **decomp.me**: Online collaborative decomp scratchpad — https://decomp.me/ (supports Switch/AArch64)

### Build system

- **Ninja**: Fast build system
- **CMake**: Cross-compilation toolchain (BotW approach)
- **decomp-toolkit**: May need ARM64 support or an equivalent

## Recommended First Steps

1. **Extract the binary**: Use hactool to get the main NSO, convert to ELF with nx2elf
2. **Load in Ghidra**: Disassemble, identify function count and structure
3. **Identify compiler version**: String dump for version info, compare codegen with upstream Clang versions
4. **Study BotW decomp**: Clone zeldaret/botw and understand their project structure
5. **Set up cross-compilation**: Get upstream Clang cross-compiling for AArch64 and matching a few known simple functions
6. **Import known symbols**: Pull function names from Skyline/ultimate-research into your symbol database
7. **Start small**: Match a few trivial functions to validate the toolchain before scaling up
8. **Automate**: Adapt the Melee overnight scripts once the manual workflow is proven

## Codegen Analysis (from 13.0.4 binary)

### Sample: FighterAreaModuleImpl leaf functions

These are ideal first matching candidates — simple, branchless leaf functions.

#### enable_fix_jostle_area_impl @ 71020ae240 (6 instructions)
```asm
ldr  x8, [x0, #0xc0]       ; load module ptr from BattleObjectModuleAccessor
mov  w9, #0x1
strb w9, [x8, #0x2a0]      ; set flag byte
str  s0, [x8, #0x2a4]      ; store float param_2
str  s1, [x8, #0x2a8]      ; store float param_3
ret
```

#### enable_fix_jostle_area_xy_impl @ 71020ae260 (8 instructions)
```asm
ldr  x9, [x0, #0xc0]
mov  w8, #0x101             ; two flag bytes (0x01, 0x01) packed as halfword
strh w8, [x9, #0x2a0]
str  s0, [x9, #0x2a4]
str  s1, [x9, #0x2a8]
str  s2, [x9, #0x2ac]
str  s3, [x9, #0x2b0]
ret
```

#### disable_fix_jostle_area_impl @ 71020ae280 (7 instructions)
```asm
ldr  x8, [x0, #0xc0]
strh wzr, [x8, #0x2a0]     ; clear flag halfword
add  x9, x8, #0x2a4
add  x8, x8, #0x2ac
str  xzr, [x8]             ; note: stores 0x2ac BEFORE 0x2a4 (compiler reordered)
str  xzr, [x9]
ret
```

### Codegen observations
- Standard AArch64 calling convention (floats in s0-s3, pointers in x0)
- Uses `xzr`/`wzr` registers for zeroing (efficient Clang pattern)
- Compiler reorders stores freely (disable writes 0x2ac before 0x2a4)
- Packs adjacent byte flags into halfword stores (`mov w8, #0x101; strh`)
- No unnecessary register moves — tight, efficient codegen
- Frame pointer setup uses `add x29, sp, #offset` (standard Clang)

## Architecture Notes

### Differences from Melee (GameCube/PPC)

- **More registers**: ARM64 has 31 GP registers vs PPC's 32, but Clang's register allocator is more sophisticated
- **More aggressive optimization**: Clang inlines more aggressively, does loop transforms, vectorization
- **C++ likely**: BotW and most Switch titles use C++, not C — expect vtables, RTTI, templates
- **Larger binary**: ~50+ MB of code vs Melee's ~4 MB — likely 100,000+ functions
- **Dynamic libraries**: Movesets are in separate `.nrs` files (Lua-compiled), not the main binary

### What makes this potentially tractable

- Upstream Clang can match (proven by BotW)
- Large existing RE community with named functions and structs
- AI (Claude) is deeply familiar with Clang codegen patterns
- decomp.me supports Switch/AArch64 for iterating on matches
- The Melee automation scripts provide a template for overnight runs
