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

## Multi-Agent Parallel Workflow
This repo supports parallel decomp work via git worktrees. Multiple Claude Code sessions can work simultaneously on different modules.

### Architecture
- **Orchestrator** (main repo on `master`): merges worker branches, runs global verification, updates `functions.csv`
- **Workers** (git worktrees on `worker/pool-*` branches): decomp assigned modules, compile, verify locally

### Pool Assignment Protocol
**CRITICAL:** Each pool's `WORKER.md` is the **single source of truth** for its assignment.
1. **READ the pool's WORKER.md** before reassigning — check if it's already doing useful work
2. **WRITE WORKER.md** in the pool's worktree when assigning new work
3. WORKER.md is tracked in git and survives rebases
4. `data/pool_assignments.md` is just a quick overview — WORKER.md wins if they conflict
5. Pools that ignore their assignment waste hours of compute — this is a serious problem

### Worker Rules
1. **ONLY edit files in your assigned file territory** — see WORKER.md
2. **NEVER modify `data/functions.csv`** — the orchestrator handles this exclusively
3. **NEVER edit files assigned to other workers**
4. Commit to your worker branch, never push to master directly

### Worker Code Quality Rules
1. **Write C++ that a Bandai Namco developer would have written.** Use the struct definitions in `include/app/`. If Ghidra shows a pattern, understand it and rewrite it idiomatically — do NOT copy-paste Ghidra pseudocode.
2. **Use struct field access, not raw offsets.** Write `acc->camera_module` not `*reinterpret_cast<void**>(reinterpret_cast<u8*>(acc) + 0x60)`. If the struct header exists, use it.
3. **Do NOT paste assembly into C functions.** `__attribute__((naked))` with inline asm is a last resort after 3 failed matching attempts, not a first approach. It inflates progress metrics without recovering source.
4. **Decompile module-by-module, not random addresses.** Understand the module's struct layout first, then decomp its functions. Each function you decomp should reveal new field information for the struct.

### Worker Efficiency Rules
1. **NEVER rebuild just to re-parse output** — run `cmd /c build.bat 2>&1 | tee /tmp/build.txt` once, then grep the saved file. One build, not ten.
2. **Save Ghidra results to disk** — after each `mcp__ghidra__decompile_function_by_address` call, append the result to `/tmp/ghidra_results.txt`. On context continuation, read the file instead of re-calling Ghidra.
3. **Use existing helper scripts** — run `python tools/next_batch.py` to find targets, `python tools/compare_bytes.py` to diff. Do NOT write inline Python for CSV parsing or byte comparison.
4. **Do NOT fix infrastructure** — if a tool (verify_all.py, build.bat, linker script) is broken, report the issue in your commit message and move to the next function. The orchestrator handles tool fixes.
5. **3-attempt limit on matching** — if a function doesn't match after 3 edit-build-verify cycles, either use `__attribute__((naked))` with inline asm or skip it and move on. Do NOT spiral on one function.

### Worker Verification
Workers use `tools/verify_local.py` for self-checks (read-only, no CSV writes):
```bash
python tools/verify_local.py --build --modules GroundModule
```

### Orchestrator Commands
```bash
python tools/setup_worktrees.py              # Create worker worktrees
bash tools/merge_worker.sh pool-a            # Merge a worker branch
python tools/verify_all.py --update          # Global verify + CSV update
```

### Setup
```bash
python tools/setup_worktrees.py   # Creates 3 worktrees: pool-a, pool-b, pool-c
cd "../SSBU Decomp-pool-a"        # Open a worker directory
claude                             # Start Claude Code in the worktree
```

## Reference Projects
- KinokoDecomp-S (Captain Toad, same SDK 8.2.x) — primary reference for toolchain and patterns
- BotW decomp (zeldaret/botw) — pioneered upstream Clang approach
- decomp.me — hosts clang-8.0.0 for Switch platform
