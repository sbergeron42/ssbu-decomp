# Worker: pool-a

## Model: Opus

## Task: Clean up fighter_status.cpp — replace raw casts/offsets with typed module access

## Priority: QUALITY CLEANUP

## Context
`fighter_status.cpp` is the single dirtiest file: 1,461 reinterpret_casts, 908 raw offsets, 3,254 lines. The typed module headers exist (`WorkModule.h`, `StatusModule.h`, `MotionModule.h`, `ControlModule.h`, `GroundModule.h`, etc.) and the accessor is typed. Most casts are loading a module from the accessor then doing raw vtable dispatch — exactly the pattern the headers replace.

## File Territory
- `src/app/fighter_status.cpp` (CLEANUP — do not add new functions, only clean existing code)
- `include/app/modules/*.h` (extend if needed — add missing vtable slot wrappers)
- `include/app/placeholders/` (create placeholder structs for non-module types)

## What To Do
1. Add `#include` for all module headers this file uses
2. Replace `reinterpret_cast<Type*>(acc->work_module)` → just use `acc->work_module` (already typed)
3. Replace `VT(mod)[slot]` dispatch → `mod->method_name(...)` using the headers
4. For vtable slots that don't have wrappers yet, add them to the module header
5. For non-module pointer types (FighterManager, FighterInformation, etc.), use existing structs or create placeholders
6. Run `python tools/review_diff.py pool-a` — cast density must stay under 10%

## Do NOT
- Delete functions
- Add new functions
- Rename functions
- Change function signatures
- This is purely internal cleanup of existing code

## Build
```bash
python tools/build.py 2>&1 | tee build_output.txt
```
