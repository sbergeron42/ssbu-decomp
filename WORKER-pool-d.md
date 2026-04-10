# Worker: pool-d

## Model: Opus

## Task: Clean up gameplay_functions.cpp + engine_functions.cpp + lua_acmd.cpp

## Priority: QUALITY CLEANUP

## Context
Three high-cast files: `gameplay_functions.cpp` (222 casts, 192 offsets), `engine_functions.cpp` (260 casts, 77 offsets), `lua_acmd.cpp` (298 casts, 140 offsets). These are game logic dispatchers with heavy vtable access that should use typed module wrappers.

## File Territory
- `src/app/gameplay_functions.cpp` (CLEANUP)
- `src/app/engine_functions.cpp` (CLEANUP)
- `src/app/lua_acmd.cpp` (CLEANUP)
- `include/app/modules/*.h` (extend if needed)
- `include/app/placeholders/` (create placeholders)

## What To Do
- Replace raw module vtable dispatch with typed wrappers
- Replace raw offset access with struct field access
- Create placeholder structs for unknown pointer types
- Cast density under 10%, zero REJECT violations

## Do NOT
- Delete, add, or rename functions — internal cleanup only

## Build
```bash
python tools/build.py 2>&1 | tee build_output.txt
python tools/review_diff.py pool-d
```
