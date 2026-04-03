# Worker: pool-b

## Model: Opus

## Task: Refactor game type files to use struct field access

Replace raw reinterpret_cast offset patterns with proper struct member access in the game type source files (non-module, non-batch).

### Your files
- src/app/FighterInformation.cpp (27 casts)
- src/app/FighterManager.cpp
- src/app/FighterEntry.cpp
- src/app/FighterKineticEnergyMotion.cpp (13)
- src/app/FighterKineticEnergyController.cpp (11)
- src/app/FighterKineticEnergyGravity.cpp (10)
- src/app/KineticEnergy.cpp
- src/app/KineticEnergyNormal.cpp (20)
- src/app/KineticEnergyRotNormal.cpp
- src/app/BattleObjectSlow.cpp
- src/app/BattleObjectWorld.cpp
- src/app/BattleObjectManager.cpp
- src/app/BossManager.cpp
- src/app/StageManager.cpp
- src/app/Item.cpp
- src/app/ItemManager.cpp
- src/app/Weapon.cpp
- src/app/Article.cpp

### What to change
Use the struct headers in include/app/:
    #include "app/FighterInformation.h"
Replace raw offset patterns with named field access.

### Critical rule
After EACH file, rebuild and verify: cmd /c build.bat && python tools/verify_all.py --summary
If verified drops, REVERT and move on.

### Rules
- ONLY edit files listed above
- Do NOT edit modules/ (done), fun_batch/fun_region (pool-a), or data files (pool-c)
- Do NOT modify include/ headers, tools/, or data/
