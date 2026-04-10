# Worker: pool-f

## Model: Opus

## Task: Lua ACMD — animcmd script functions (sv_animcmd_*, lua_acmd)

## Priority: NEW DECOMP

## Context
ACMD (animation command) scripts drive attack animations, hitbox timing, and effect spawning. The .dynsym has hundreds of `sv_animcmd::*` and `lua_acmd::*` functions. `include/lib/L2CValue.h` and `include/lib/L2CAgent.h` provide typed wrappers.

## Approach
1. Use `mcp__ghidra__search_functions_by_name` to find `acmd`, `animcmd`, `L2CValue`, `L2CAgent` functions
2. Start with small L2C helper functions for quick wins
3. Use typed L2CValue/L2CAgent access, not raw casts

## File Territory
- `src/app/lua_acmd.cpp` (extend — pool-d also owns this, coordinate via WORKER files)
- `src/app/sv_animcmd_*.cpp` (EXCLUDING `sv_animcmd_effect.cpp` which pool-c owns)
- `include/lib/L2CValue.h` (extend)
- `include/lib/L2CAgent.h` (extend)
- `include/app/placeholders/` (new types as needed)

## Quality Rules
- NO `FUN_` names, NO Ghidra vars, NO raw vtable dispatch, NO naked asm
- Cast density under 10%
- Use typed L2CValue wrappers from include/lib/L2CValue.h
- Run `python tools/review_diff.py pool-f` before committing

## Build
```bash
python tools/build.py 2>&1 | tee build_output.txt
```
