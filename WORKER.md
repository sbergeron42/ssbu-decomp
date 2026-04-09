# Worker: pool-c

## Model: Opus

## Task: Stage + camera medium functions — targeting 196 KB

## Targets (by size, descending)
### Stage (167 KB)
1. StageBase (14,820 bytes @ 0x71025d2dc0)
2. set_stage_random_settings (12,804 bytes @ 0x710177a980)
3. ~StageWufuIsland (2,700 bytes @ 0x7103008320)
4. ~~StageBase (2,572 bytes @ 0x71025d7c90)
5. StageWufuIsland (1,676 bytes @ 0x7103007a30)

NOTE: Skip create_stage (114,600 bytes) — too large for this round.

### Camera (29 KB)
1. set_pause_camera_param (3,996 bytes @ 0x7102623350)
2. ~CameraQuake (3,192 bytes @ 0x7100515190)
3. CHECK_VALID_START_CAMERA (2,812 bytes @ 0x71022b1740)
4. set_camera_param (2,344 bytes @ 0x7102625020)
5. CHECK_VALID_FINAL_START_CAMERA (1,880 bytes @ 0x71022b0fe0)

## Approach
- Continue StageManager.cpp from prior WIP
- Stage constructors/destructors reveal struct layout — prioritize these
- Camera functions likely share patterns with existing CameraModule decomp
- Use Ghidra MCP for decompilation

## File Territory
- src/app/StageManager.cpp
- src/app/camera_functions.cpp (new)
- src/app/Gimmick*.cpp (existing)
- include/app/ (struct updates)

## Quality Rules
- Use module vtable method wrappers
- No naked asm
- Document derivation chains
