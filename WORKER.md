# Worker: pool-b (Round 4)

## Assignment
Remaining Item complex functions + event store_l2c_table serialization (split with pool-d)

## Assigned Modules
- `Item` (10 remaining — complex, 48-288B)
- `ItemKineticModuleImpl` (7 remaining — SIMD patterns)
- `ItemCameraModuleImpl` (6 remaining — complex vtable chains)
- `ItemParamAccessor` (3 remaining)
- `ItemDamageModuleImpl` (1 remaining)
- `ItemManager` (1 remaining)
- `WeaponKineticEnergyGravity` (1 remaining)
- Event store_l2c_table (first half, alphabetically A-G):
  - `FighterCloudLinkEventFinal`, `FighterInklingLinkEventPaint`
  - `FighterPikminLinkEvent*` (all 9 modules)
  - `FighterPokemonLinkEventChange`, `FighterRidleyLinkEventMotion`
  - `FighterRyuLinkEventFinal*` (2 modules)
  - `GimmickEvent`, `GimmickEventBarrel`, `GimmickEventCatch`
  - `GimmickEventDrum*` (5 modules)

## Rules
1. **ONLY edit .cpp files for your assigned modules**
2. **NEVER modify data/functions.csv**
3. Commit to branch `worker/pool-b`

## Key Notes
- store_l2c_table functions use `b` (external branch) — won't byte-match but decompile anyway
- Use Ghidra MCP: `mcp__ghidra__decompile_function_by_address`
- SIMD patterns: use `v4sf` type with `__attribute__((vector_size(16)))`

## Workflow
```bash
python tools/verify_local.py --build --modules Item ItemKineticModuleImpl
git add src/app/*.cpp src/app/modules/*.cpp
git commit -m "Decompile N functions across Item + events"
```
