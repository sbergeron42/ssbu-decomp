# Worker: pool-b

## Model: Opus

## Task: Phase 3 — Define StageBase struct + rewrite all stage users

## Priority: TYPE RECOVERY (struct definition + consumer rewrite)

## Context
`StageBase` is the base class for all stage types (~150 raw offset references across 10+ files). Stage destructors, camera hooks, and collision setup all operate on this type via raw offsets. The accessor is typed, the reviewer rejects >10% cast density, and placeholder structs go in `include/app/placeholders/`.

## File Territory
- `include/app/placeholders/StageBase.h` (CREATE — or `include/app/StageBase.h` if confident in the name)
- Any `src/` files with stage-related raw offset access (camera_functions.cpp stage destructors, StageWufuIsland.cpp, etc.)

## What To Do

### Step 1: Map the struct layout using Ghidra
Use `mcp__ghidra__decompile_function_by_address` on stage destructors and constructors to map the field layout:
- Pool-c's `camera_functions.cpp` already has stage destructors at 0x7102ccf720 (~StageNintendogs), 0x71029240a0 (~StageFlatZoneX), 0x7102f33f20 (~StageStreetPass)
- These show: vtable at +0x0, sub-object at +0x738, vectors at +0x830/+0x850/+0x898/+0x908, unique_ptrs at +0x950/+0xc78
- Look for the common destructor `FUN_71025d7310` (StageBase::~StageBase) — its offsets define the base class fields

### Step 2: Define the struct
```cpp
struct StageBase {
    void** vtable;           // +0x00
    u8 unk_0x08[0x730];
    void* sub_object;        // +0x738 [derived: loaded in all stage dtors]
    // ... fill in from Ghidra analysis
};
```
Use `unk_0xNN` for gaps. Document every named field with `[derived:]` or `[inferred:]`.

### Step 3: Rewrite stage functions
Replace raw offset access with struct field access. Target the stage destructors first (they reveal the most fields), then other stage functions.

### Step 4: Log in undefined_types.md
If the real class name is uncertain, add an entry to `data/undefined_types.md` with research leads.

## Rules
- Cast density must stay under 10% or your diff gets REJECTED
- Create placeholder structs for any new unknown types you encounter
- Every named field needs `[derived:]` or `[inferred:]` provenance
- NO Ghidra variable names, NO naked asm, NO raw vtable dispatch

## Self-Check
```bash
python tools/review_diff.py pool-b
```

## Build
```bash
python tools/build.py 2>&1 | tee build_output.txt
```
