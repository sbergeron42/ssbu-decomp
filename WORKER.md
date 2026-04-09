# Worker: pool-b

## Model: Opus

## Task: Fighter status + AI decomp — community priority #1

## Strategy
Fighter state machines are the #1 community request. Moveset modders need to understand status transitions, AI decision logic, and ACMD integration. Use types-first approach: recover struct layouts from cross-referencing, then decomp functions using typed access.

## Targets
1. **fighter_status.cpp** — Continue adding check_stat_*, AI target, command step functions
2. **fighter_attack.cpp** — AI check_stat bitfield readers, attack data dispatchers
3. **New: fighter_ai.cpp** — AI decision functions (188 undecompiled, 91 KB)
4. **Named fighter functions** — 1,124 undecompiled functions with "fighter" in name

## Approach
- Use Ghidra to decompile each function
- Cross-reference with existing struct headers in include/app/
- Use BattleObjectModuleAccessor field access, NOT raw offsets
- Derive field names with provenance tags [derived: ...] or [inferred: ...]
- 3-attempt limit per function, skip if register allocation won't match

## File Territory
- src/app/fighter_status.cpp
- src/app/fighter_attack.cpp
- src/app/fighter_ai.cpp (new)
- include/app/ (struct updates only)

## Quality Rules
- Write C++ a Bandai Namco dev would write — use struct headers
- No naked asm
- No shallow variable renames without struct access
- Document derivation chains for every field name
