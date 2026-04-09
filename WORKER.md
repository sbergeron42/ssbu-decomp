# Worker: pool-d

## Model: Opus

## Task: Lua/ACMD + AI system decomp — community priority #3

## Strategy
ACMD (Animation Command) is the core scripting system every moveset mod interacts with. The Lua/L2C binding layer translates between the game engine and ACMD scripts. AI system controls CPU behavior. Both are high-value for the modding community.

## Targets
1. **Lua/ACMD functions** — 137 undecompiled (121 KB). L2C binding, lua state management, ACMD interpreter hooks.
2. **AI system** — 188 undecompiled (91 KB). AI decision trees, combat evaluation, target selection.
3. **fighter_motion.cpp** — Continue kinetic energy + motion helpers (existing file).

## Approach
- Lua functions may be at -O0 optimization (0x71037xxxxx range) — try __attribute__((optnone))
- AI functions use the ai_data struct at +0x168 offset pattern (see fighter_status.cpp examples)
- ACMD interpreter functions are complex — focus on the dispatch wrappers first
- Cross-reference with Skyline/ARCropolis naming for ACMD opcodes

## File Territory
- src/app/fighter_motion.cpp
- src/app/lua_acmd.cpp (new)
- src/app/fighter_ai.cpp (coordinate with pool-b — pool-b owns AI stat checks, pool-d owns AI decision logic)
- include/app/ (struct updates)

## Quality Rules
- Use optnone for -O0 compiled functions (0x71037-0x71039 range)
- No naked asm
- Document Lua/ACMD opcode names with community sources
