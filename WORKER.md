# Worker: pool-d (Round 3)

## Assignment
Fighter kinetic/final + managers

## Assigned Modules
- `FighterBayonettaFinalModule`
- `FighterKineticEnergyController`
- `FighterKineticEnergyGravity`
- `FighterKineticEnergyMotion`
- `FighterPitBFinalModule`
- `FighterParamAccessor2`
- `BossManager`
- `StageManager`
- `KineticEnergyNormal`
- `KineticEnergy`

## Rules
1. **ONLY edit .cpp files for your assigned modules**
2. **NEVER modify data/functions.csv**
3. **NEVER edit modules assigned to other workers**
4. Commit to your branch (`worker/pool-d`), never push to master

## Key Notes
- For store_l2c_table_impl: use `LargeRet` return type (forces x9 scratch register)
- For bool fields: use `bool*` cast, not `u8` to avoid cmp+cset
- New modules need new .cpp files with `#include "types.h"` or `#include "app/BattleObjectModuleAccessor.h"`
- Use Ghidra MCP to disassemble functions: `mcp__ghidra__disassemble_function`

## Workflow
```bash
python tools/verify_local.py --build --modules YourModule
git add src/app/YourModule.cpp
git commit -m "Match N functions in YourModule"
```
