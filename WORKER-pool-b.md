# Worker: pool-b

## Model: Opus

## Task: Phase 1 — WorkModule typed wrapper adoption

## Priority: QUALITY REFACTOR (not new decomp)

## Context
The `BattleObjectModuleAccessor` fields are now typed (`WorkModule*` not `void*`).
A code reviewer (`tools/review_diff.py`) now gates all merges.
Your job is to replace raw vtable dispatch with typed method wrappers.

## File Territory
- `src/app/modules/WorkModule.cpp` (49 raw VT calls to convert)
- `src/app/fighter_status.cpp` (WorkModule VT calls only)
- `src/app/fighter_effects.cpp` (WorkModule VT calls only)
- `src/app/fun_typed_e_004.cpp`
- `src/app/fun_typed_b_002.cpp`
- `src/app/fun_batch_c2_018.cpp`
- `src/app/fun_batch_b_025.cpp` (your pending code — fix REJECT violations)
- `src/app/fun_batch_b_026.cpp` (your pending code — fix REJECT violations)

## Step 1: Fix your own pending REJECT violations
Your diff scored 30/100. Fix the 11 STRUCT_REQUIRED and 17 USE_VTABLE_WRAPPERS issues in fun_batch_b_025.cpp and fun_batch_b_026.cpp FIRST. Replace `VT(work)[0x98/8]` with `acc->work_module->get_int(...)` etc.

## Step 2: Convert WorkModule.cpp
Add `#include "app/modules/WorkModule.h"`. Replace all 49 `VT(m)[slot]` dispatches with typed `m->method()` calls.

## Step 3: Convert consumer files
For each file in territory, replace:
```cpp
// BEFORE:
u8* work = reinterpret_cast<u8*>(acc->work_module);
u32 val = reinterpret_cast<u32(*)(u8*, u32)>(VT(work)[0x98/8])(work, 0x10000000);

// AFTER:
u32 val = acc->work_module->get_int(0x10000000);
```

## Key vtable slot -> method mapping
| Slot | Method |
|------|--------|
| 0x58/8 | `get_float` |
| 0x98/8 | `get_int` |
| 0xa0/8 | `set_int` |
| 0x108/8 | `is_flag` |
| 0x110/8 | `on_flag` |
| 0x118/8 | `off_flag` |
| 0x1d0/8 | `enable_transition_term` |
| 0x1d8/8 | `unable_transition_term` |
| 0x1e8/8 | `is_enable_transition_term` |

See `include/app/modules/WorkModule.h` for the complete list.

## Self-Check (MANDATORY before committing)
```bash
python tools/review_diff.py pool-b
```
Must score 50+ with zero REJECT violations. The orchestrator WILL reject your diff otherwise.

## Build
```bash
python tools/build.py 2>&1 | tee build_output.txt
```
