# Worker: pool-d

## Model: Opus

## Task: Phase 1 — MotionModule + StatusModule typed wrapper adoption

## Priority: QUALITY REFACTOR (not new decomp)

## Context
The `BattleObjectModuleAccessor` fields are now typed (`MotionModule*`, `StatusModule*` etc, not `void*`).
A code reviewer (`tools/review_diff.py`) now gates all merges.
Your job is to replace raw vtable dispatch with typed method wrappers.

## File Territory

### MotionModule (11 raw VT calls)
- `src/app/fighter_motion.cpp` (4 raw VT calls)
- `src/app/fun_batch_e3_022.cpp` (6 raw VT calls)
- `src/app/fun_batch_e3_021.cpp` (1 raw VT call)

### StatusModule (9 raw VT calls)
- `src/app/fighter_status.cpp` (StatusModule VT calls only — 3)
- `src/app/fun_typed_b_001.cpp` (3)
- `src/app/fun_batch_e_006.cpp` (1)
- `src/app/fun_batch_e_003.cpp` (1)
- `src/app/fun_batch_e2_012.cpp` (1)

### Your pending code (fix REJECT violations)
- `src/app/fun_hard_d_030.cpp`
- `src/app/fun_hard_d_031.cpp`

## Step 1: Fix your own pending REJECT violations
Run `python tools/review_diff.py pool-d` and fix any STRUCT_REQUIRED or other rejections.

## Step 2: Convert MotionModule consumer files
Add `#include "app/modules/MotionModule.h"`. Replace:
```cpp
// BEFORE:
void** vt = *reinterpret_cast<void***>(motion_mod);
reinterpret_cast<void(*)(void*, u64, f32, bool, bool, bool)>(vt[28])(motion_mod, hash, rate, p1, p2, p3);

// AFTER:
acc->motion_module->change_motion(hash, rate, p1, p2, p3);
```

### Key MotionModule vtable slot -> method mapping
| Slot | Method |
|------|--------|
| _vt[28] | `change_motion` |
| _vt[100] | `add_motion_partial` |
| _vt[106] | `end_frame_partial` |
| _vt[108] | `rate_partial` |
| _vt[109] | `frame_partial` |
| _vt[126] | `whole_rate` |
| _vt[130] | `update_rate` |

See `include/app/modules/MotionModule.h` for all 95 methods.

## Step 3: Convert StatusModule consumer files
Add `#include "app/modules/StatusModule.h"`. The StatusModule uses a `StatusModuleVtbl` struct. Replace:
```cpp
// BEFORE:
s32 kind = reinterpret_cast<s32(*)(void*)>(vt[0x110/8])(status_mod);

// AFTER:
s32 kind = acc->status_module->status_kind();
```

### Key StatusModule vtable slot -> method mapping
| Slot | Method |
|------|--------|
| 0x110/8 | `status_kind` |
| 0x118/8 | `prev_status_kind` |
| 0x120/8 | `situation_kind` |

See `include/app/modules/StatusModule.h`.

## Self-Check (MANDATORY before committing)
```bash
python tools/review_diff.py pool-d
```
Must score 50+ with zero REJECT violations.

## Build
```bash
python tools/build.py 2>&1 | tee build_output.txt
```
