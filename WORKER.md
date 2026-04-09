# Worker: pool-b

## Model: Opus

## Task: Fighter + game core medium functions — targeting 100+ KB

## Targets (by size, descending)
1. get_entry_in_fighter_param_kind_struct (15,848 bytes @ 0x71006f3b00)
2. create_status_script_for_projectile_article (15,648 bytes @ 0x71033abee0)
3. save_aura_ball_status (13,348 bytes @ 0x7100c5e1a0)
4. load_fighter? (7,776 bytes @ 0x71017e6510)
5. heal_fighters (3,644 bytes @ 0x7101676250)
6. get_fighter_id_from_fighter_kind? (3,604 bytes @ 0x710066cd40)
7. chase_fighter (3,148 bytes @ 0x7101672f90)
8. escape_from_fighter (2,700 bytes @ 0x7101672500)

Plus continue fighter_status.cpp AI functions from prior round.

## Approach
- Use Ghidra to decompile each target
- These are LARGE functions — focus on understanding structure first
- Cross-reference with existing fighter struct headers
- For switch/case dispatchers, identify the dispatch pattern before writing code
- 3-attempt limit — if register alloc won't match, document and move on as N-quality

## File Territory
- src/app/fighter_status.cpp
- src/app/fighter_attack.cpp
- src/app/fighter_core.cpp (new — for game core fighter functions)
- include/app/ (struct updates)

## Quality Rules
- Use BattleObjectModuleAccessor struct access
- No naked asm
- Document derivation chains
