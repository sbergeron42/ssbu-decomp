# Worker: pool-b

## Model: Opus

## Task: Refactor module files H-Z to use struct field access

Replace raw pointer arithmetic with proper struct member access across module source files. The struct headers now exist in include/app/.

### What to change
Replace patterns like:
    auto* m = *reinterpret_cast<void**>(reinterpret_cast<u8*>(acc) + 0x60);
With:
    auto* m = acc->camera_module;

### Your files
Refactor these source files (alphabetically H through Z):
- src/app/modules/HitModule.cpp
- src/app/modules/ItemModule.cpp
- src/app/modules/JostleModule.cpp
- src/app/modules/KineticModule.cpp
- src/app/modules/LinkModule.cpp
- src/app/modules/ModelModule.cpp
- src/app/modules/MotionAnimcmdModule.cpp
- src/app/modules/MotionModule.cpp
- src/app/modules/PhysicsModule.cpp
- src/app/modules/PostureModule.cpp
- src/app/modules/ReflectModule.cpp
- src/app/modules/ReflectorModule.cpp
- src/app/modules/SearchModule.cpp
- src/app/modules/ShieldModule.cpp
- src/app/modules/SlowModule.cpp
- src/app/modules/SoundModule.cpp
- src/app/modules/StatusModule.cpp
- src/app/modules/TurnModule.cpp
- src/app/modules/VisibilityModule.cpp
- src/app/modules/WorkModule.cpp

### Critical rule
After EACH file change, rebuild and verify matching is preserved:
    cmd /c build.bat && python tools/verify_all.py --summary
If verified count drops, REVERT that file and move on.

### Include the header
Add #include "app/BattleObjectModuleAccessor.h" at top of each file.

### Rules
- ONLY edit files listed above
- Do NOT edit include/ headers
- Do NOT modify data/functions.csv or tools/
- NEVER reduce verified count
