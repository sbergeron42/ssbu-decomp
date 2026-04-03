# Worker: pool-c

## Model: Opus

## Task: Define data struct headers + refactor data/event/link files

Your assigned files don't use BattleObjectModuleAccessor — they use their own data structs (AttackData, DamageLog, Circle, etc.) with raw offset access. To refactor these, define the struct layouts first.

### Phase 1: Define struct headers
Create NEW header files in include/app/ for the data types used by your files:
- include/app/AttackData.h
- include/app/AttackAbsoluteData.h  
- include/app/DamageLog.h
- include/app/DamageInfo.h
- include/app/AreaContactLog.h
- include/app/Circle.h
- include/app/Rhombus2.h
- include/app/stWaterAreaInfo.h
- (any others you discover)

Derive the struct layout from the offset patterns in the .cpp files. For example, if code does:
    *reinterpret_cast<float*>(reinterpret_cast<u8*>(obj)+0x10) = v;
Then the struct has a float field at offset 0x10.

Use Ghidra MCP to cross-reference: mcp__ghidra__decompile_function_by_address to see how Ghidra types these.

### Phase 2: Refactor source files
Replace raw offset casts with struct field access using your new headers.

### Your files
- src/app/AttackData.cpp, AttackAbsoluteData.cpp
- src/app/DamageLog.cpp, DamageInfo.cpp
- src/app/AreaContactLog.cpp, Circle.cpp, Rhombus2.cpp, stWaterAreaInfo.cpp
- src/app/OnCalcParamEvent.cpp
- src/app/GimmickEvent*.cpp, LinkEvent*.cpp
- src/app/FighterPikmin*.cpp, FighterCloud*.cpp, FighterInkling*.cpp, etc.
- src/app/Weapon*.cpp
- src/app/gameplay_functions.cpp, lib.cpp
- src/app/particle/audio/graphics/network/memory/threading_functions.cpp

### Rules
- CAN create NEW headers in include/app/ for data types listed above
- Do NOT edit existing headers (BattleObjectModuleAccessor.h, FighterManager.h, etc. — pool-b territory)
- Do NOT edit modules/ or fun_batch/fun_region files
- After each file change: cmd /c build.bat && python tools/verify_all.py --summary
- If verified drops, REVERT and move on
