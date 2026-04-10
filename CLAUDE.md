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
```bash
python tools/build.py
```
Or: `python tools/progress.py` to check status.
**WARNING:** `build.bat` is deprecated — it runs obsolete post-processors that inflate match counts. Always use `build.py`.

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
**CRITICAL:** Each pool has a unique `WORKER-pool-{letter}.md` file (e.g., `WORKER-pool-a.md`).
This is the **single source of truth** for that pool's assignment. Pool-specific filenames prevent rebase clobbering.
1. **READ the pool's `WORKER-pool-{letter}.md`** before reassigning — check if it's already doing useful work
2. **WRITE `WORKER-pool-{letter}.md`** in the pool's worktree when assigning new work
3. These files are tracked in git and survive rebases (unique filenames = no conflicts)
4. `data/pool_assignments.md` is just a quick overview — the WORKER file wins if they conflict
5. Pools that ignore their assignment waste hours of compute — this is a serious problem

### Worker Rules
1. **ONLY edit files in your assigned file territory** — see your `WORKER-pool-{letter}.md`
2. **NEVER modify `data/functions.csv`** — the orchestrator handles this exclusively
3. **NEVER edit files assigned to other workers**
4. Commit to your worker branch, never push to master directly

### Worker Code Quality Rules

**ALL WORKER DIFFS ARE REVIEWED BY `tools/review_diff.py` BEFORE MERGE.**
The orchestrator will REJECT diffs that fail the reviewer. Do not submit code that violates these rules — it wastes your compute budget and the orchestrator's time.

1. **Write C++ that a Bandai Namco developer would have written.** Use the struct definitions in `include/app/` and `include/resource/`. If Ghidra shows a pattern, understand it and rewrite it idiomatically — do NOT copy-paste Ghidra pseudocode.
2. **STRUCT FIRST — define types before writing functions.** If a function accesses 3+ distinct offsets on the same pointer, you MUST define or extend a struct in `include/` BEFORE writing the function. Use `unk_0xNN` for unknown fields, typed fields for known ones. Raw hex offset access on untyped `u8*`/`void*`/`u64*` is REJECTED by the reviewer.
   - **GOOD:** `stage->sub_object` (struct field at +0x738)
   - **BAD:** `param_1[0xe7]` or `*(u64*)(sub + 0x790)`
   - **Exception:** trivial 1-2 field leaf functions (e.g., singleton getters) may use raw access.
3. **NO `__attribute__((naked))`.** Naked asm is BANNED outright. If a function can't match after 3 attempts, SKIP IT — do not inflate progress with pasted assembly. The reviewer auto-rejects any `naked` attribute.
4. **NO Ghidra default names.** `uVar1`, `plVar2`, `iVar3` variable names and `FUN_71XXXXXXXX` function names in new code are auto-rejected. If you're calling a function, name it based on what it does (e.g., `tryFindBattleObjectById_71003ac560`). Keep the address suffix for linker disambiguation. Run `python tools/name_audit.py` to see the most-referenced unnamed functions.
5. **Minimize `reinterpret_cast` — it's a debt metric.** Every `reinterpret_cast` means a type hasn't been recovered yet. Diffs above 10% cast density are REJECTED. The fix is NOT to avoid the function — it's to define a placeholder struct:
   - Create `include/app/placeholders/UnkType_XXXXXXXX.h` (named after the first function address that uses it)
   - Use `unk_0xNN` for unknown fields, typed fields for known offsets
   - Add an entry to `data/undefined_types.md` describing what's known and what needs research
   - A struct with `unk_` fields is infinitely better than `reinterpret_cast` — it compiles the same but compounds as more functions reveal more fields
6. **Use struct field access, not raw offsets.** Write `acc->camera_module` not `*reinterpret_cast<void**>(reinterpret_cast<u8*>(acc) + 0x60)`. If the struct header exists, use it.
7. **Decompile module-by-module, not random addresses.** Understand the module's struct layout first, then decomp its functions. Each function you decomp should reveal new field information for the struct.
8. **Document derivation chains for every struct field name.** Every named field must include HOW the name was derived, traceable back to binary evidence:
   - `situation_kind`  — `// +0xD8 [derived: situation_kind_impl (.dynsym) reads this as s32]`
   - `field_0xE0_s32`  — `// +0xE0 [inferred: bitmask pattern in 12 functions, no proven name]`
   - `unk_0xE4[0x5C]`  — unknown padding, honest gap
   - NEVER label an inferred field name as if it were confirmed. Wrong names that look authoritative mislead the community.
   - The derivation chain should be enough for someone to verify the name by checking the referenced function in Ghidra.
9. **Use vtable method wrappers from module headers.** Headers in `include/app/modules/` have named methods for vtable slots. Write `mod->change_motion(hash, rate, p1, p2, p3)` not `reinterpret_cast<void(*)(MotionModule*,u64,f32,bool,bool,bool)>(mod->_vt[28])(mod, hash, rate, p1, p2, p3)`. The reviewer warns on raw vtable dispatch.
10. **Renaming variables is NOT a rewrite.** Changing `uVar1` to `result` without replacing raw offsets with struct access is not acceptable. The goal is structural rewriting with typed field access, not cosmetic renames.

### Self-Check Before Committing
Workers SHOULD run the reviewer against their own branch before committing:
```bash
python tools/review_diff.py pool-{letter}
```
If the score is below 50 or there are REJECT violations, fix them before committing. The orchestrator WILL reject your diff otherwise.

### Resource Service Guidelines
- **Use ARCropolis community names.** Field names come from `ARCropolis` (Rust mod loader) and `smash-arc` (ARC format library). These are empirically validated by millions of mod installations. Tag with `[derived: ARCropolis field_name]`.
- **OOM retry pattern.** Many resource functions use: `alloc(); if (!ptr && OOM_handler) { OOM_handler->retry(); alloc(); }`. Factor this into `alloc_with_oom_retry()` rather than inlining it everywhere.
- **FixedString<N> template.** The game uses fixed-length strings with inline storage + length field. Use the `FixedString256` type from `include/resource/containers.h`.
- **Singleton creation pattern.** Uses CAS spinlock (`ldxr/stxr` loop) + `nn::os::YieldThread()`. Recognize and document it, don't paste the raw exclusive monitor instructions.
- **0xFFFFFF sentinel.** Invalid index for filepath and directory handles. Use named constant or document inline.
- **Library code identification.** If a function matches a known open-source library (jemalloc, zlib, zstd), identify the version and document with `// library_name version: source_file.c:line`. Do NOT try to byte-match library code compiled with different optimization flags — document the version and move on.

### Worker Efficiency Rules
1. **NEVER rebuild just to re-parse output** — run `python tools/build.py 2>&1 | tee build_output.txt` once, then grep the saved file. One build, not ten.
2. **Save Ghidra results to disk** — after each `mcp__ghidra__decompile_function_by_address` call, append the result to `data/ghidra_cache/<pool_name>.txt` (NOT /tmp — it gets wiped on reboot). On context continuation, read the file instead of re-calling Ghidra.
3. **Use existing helper scripts** — run `python tools/next_batch.py` to find targets, `python tools/compare_bytes.py` to diff. Do NOT write inline Python for CSV parsing or byte comparison.
4. **Do NOT fix infrastructure** — if a tool (verify_all.py, build.py, linker script) is broken, report the issue in your commit message and move to the next function. The orchestrator handles tool fixes.
5. **3-attempt limit on matching** — if a function doesn't match after 3 edit-build-verify cycles, skip it and move on. Do NOT spiral on one function. Do NOT use `__attribute__((naked))` — it is banned.

### Worker Verification
Workers use `tools/verify_local.py` for self-checks (read-only, no CSV writes):
```bash
python tools/verify_local.py --build --modules GroundModule
```

### Orchestrator
Orchestrator workflow (merge, verify, assign, setup, linking infrastructure) is in `docs/ORCHESTRATOR.md`.

## Reference Projects
- KinokoDecomp-S (Captain Toad, same SDK 8.2.x) — primary reference for toolchain and patterns
- BotW decomp (zeldaret/botw) — pioneered upstream Clang approach, links throughout with auto-stubs
- decomp.me — hosts clang-8.0.0 for Switch platform
