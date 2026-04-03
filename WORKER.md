# Worker: pool-e

## Model: Opus

## Task: Fix non-matching functions in fun_batch_b* and remaining scattered files

5,101 non-matching functions need codegen fixes. This pool handles batch_b files plus any non-matching in non-batch source files.

### Workflow
1. Run python tools/verify_all.py to get the non-matching list
2. Filter to functions in YOUR files only
3. Use python tools/show_diff.py func_name for instruction-level diff
4. Common fixes: swap u32/s32, u8/bool, void*/u64, add asm("") barriers
5. Rebuild (cmd /c build.bat), re-verify, commit in batches of 10-20

### Rules
- ONLY edit: src/app/fun_batch_b_*.cpp, src/app/fun_batch_a_*.cpp, src/app/fun_batch_test.cpp
- Also can edit: src/app/gameplay_functions.cpp, src/app/engine_functions.cpp, src/app/audio_functions.cpp, src/app/graphics_functions.cpp, src/app/particle_functions.cpp, src/app/network_functions.cpp, src/app/memory_functions.cpp, src/app/threading_functions.cpp, src/app/lib.cpp
- Do NOT edit modules/, game type files, or other batch files

### Progress (session 5, 2026-04-03)
Starting non-matching: 89 in pool-e territory.

**Fixes applied:**
- Removed 28 duplicate definitions from gameplay_functions.cpp (already matching in module/batch files)
- Fixed wrong implementations:
  - stop_stage_sound: wrong global (DAT_71052bb3b0 → DAT_71053299d8, double deref)
  - GetNetworkFactory_162480: wrong offset (+0 → +8)
  - GetBlockSize_b5090: u64→u32 shift width
  - Fiber_353c200: empty→store zero
  - dtor_Mutex_37c9250: empty→tail call FUN_71039c0460
  - GetRequiredMemorySize_3e10: address typo (3e10 → 39e10)
- Fixed scheduling with asm barriers:
  - HOLYWATER_HIT_*: asm("+r" base, fighter_kind) → all 5 MATCH
  - FUN_710022b510/e510: asm("+r" base) for reassociation → 16/17
- Fixed tail-call optimization:
  - throw_attack, set_dead_camera_hit_rumble: asm("") after bl → MATCH
- Fixed wrong addresses:
  - batch_b_006/008: guard-init→return-0 stubs (orig was mov x0,xzr;ret)
  - batch_b_013: iterator addresses removed (mid-function addresses)
  - batch_b_014-017: mid-function addresses removed

**Current: verified=260, non-matching=49**

**Known blockers (batch_b_001-005):**
- ~30 functions have NX Clang prologue divergence (sub sp vs str-with-predecrement)
  - Cannot be fixed at C level; would need a new post-processing tool
- Several functions have register allocation differences in vtable dispatch chains
