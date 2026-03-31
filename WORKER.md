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

## Rules
1. **ONLY edit .cpp files for your assigned modules**
2. **NEVER modify data/functions.csv**
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
```
