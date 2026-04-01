<<<<<<< HEAD
# Worker: pool-d (Round 4)

## Assignment
Large `store_l2c_table_impl` serialization functions across all event/gimmick modules.
These are 200-2000 byte functions that serialize struct fields to Lua tables.

## Assigned Modules (all remaining store_l2c_table variants)
- All `LinkEvent*` modules (LinkEventCapture, LinkEventThrow, LinkEventPos, LinkEventMask, etc.)
- All `GimmickEvent*` modules (GimmickEventPos, GimmickEventNotify, GimmickEventWarp, etc.)
- All `FighterPikmin*` modules
- `FighterCloudLinkEventFinal`, `FighterInklingLinkEventPaint`, `FighterRidleyLinkEventMotion`
- `FighterRyuLinkEventFinalDeadDamage`, `FighterRyuLinkEventFinalMoveTarget`
- `FighterPokemonLinkEventChange`
- `WeaponRobotHominglaserLinkEvent*`, `WeaponShizueFishingrodLinkEvent*`
- `OnCalcParamEvent`, `GimmickEventPresenter`, `LinkEventTouchItem`, `LinkEventLassoHang`
- `BossManager` (1 remaining)
=======
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
>>>>>>> worker/pool-b

## Rules
1. **ONLY edit .cpp files for your assigned modules**
2. **NEVER modify data/functions.csv**
<<<<<<< HEAD
3. Commit to branch `worker/pool-d`

## Key Notes
- These `store_l2c_table` functions call external functions via `b` (PC-relative branch)
- They WON'T byte-match — decompile them anyway for viking semantic verification
- Use Ghidra MCP to decompile: `mcp__ghidra__decompile_function_by_address`
- For `store_l2c_table` return type: use `LargeRet` to force x9 scratch register

## Workflow
```bash
python tools/verify_local.py --build --modules GimmickEventPos LinkEventCapture
git add src/app/GimmickEventPos.cpp src/app/LinkEventCapture.cpp
git commit -m "Decompile store_l2c_table for N modules"
=======
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
>>>>>>> worker/pool-b
```
