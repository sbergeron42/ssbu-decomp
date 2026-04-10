# Worker: pool-a

## Model: Opus

## Task: Fighter logic — status transitions and state machines

## Priority: NEW DECOMP (community high-value)

## Context
Fighter status logic is the core of how characters behave — transitions between idle, attack, damage, grab, etc. The .dynsym has hundreds of `StatusModule__*_impl` names. The typed accessor and module headers are ready. This is what the modding community cares most about.

## Approach
1. Use `mcp__ghidra__search_functions_by_name` to find `status` functions in the 0x71015xxxxx-0x71016xxxxx range
2. Start with small/medium functions (under 200 bytes) for higher match rate
3. Define placeholder structs for any new types encountered — cast density must stay under 10%
4. Use typed module access: `acc->status_module`, `acc->work_module->get_int()`, etc.

## File Territory
- `src/app/fighter_status.cpp` (extend — already has 3,254 lines)
- `src/app/fighter_status_*.cpp` (create new files if fighter_status.cpp gets too large)
- `include/app/modules/StatusModule.h` (extend with new vtable slot wrappers)
- `include/app/placeholders/` (new types as needed)

## Quality Rules
- NO `FUN_` names — name every function you call
- NO Ghidra variable names
- NO raw vtable dispatch — use typed wrappers
- NO naked asm
- Cast density under 10%
- Create placeholder structs for unknown types, log in `data/undefined_types.md`
- Run `python tools/review_diff.py pool-a` before committing

## Build
```bash
python tools/build.py 2>&1 | tee build_output.txt
```
