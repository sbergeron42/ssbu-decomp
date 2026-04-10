# Undefined Types — Research Queue

Placeholder structs that need community research to identify proper names.
Each entry has: what we know from the binary, where it's used, and what's still unknown.

To contribute: identify the real class name, update the header, and remove the entry here.

## How to read this file

- **Placeholder name**: temporary name based on first-seen function address or usage
- **Header**: where the placeholder struct lives
- **Known fields**: offsets we've typed from binary evidence
- **Used by**: function addresses / source files that operate on this type
- **Research leads**: .dynsym symbols, vtable contents, cross-references that might identify it

---

## Active placeholders

## FighterParamAccessor2PhysicsParams
- **Header**: `include/app/placeholders/FighterParamAccessor2.h`
- **Size**: ~0x2B0 bytes (estimated from largest offset +0x2AC + 4)
- **Known fields**:
  - +0x230: `u32 init_bound_frame` [derived: FUN_71016593a0]
  - +0x234: `f32 special_lw_gravity` [derived: FUN_71016593c0]
  - +0x240: `f32 length_gravity` [derived: FUN_7101659400]
  - +0x244: `f32 length_speed_y_max` [derived: FUN_7101659420]
  - +0x260..+0x268: length angle x/y/z velocity (f32 each)
  - +0x26C..+0x270: side gravity, side_speed_y_max (f32 each)
  - +0x28C..+0x294: side angle x/y/z velocity (f32 each)
  - +0x2A4: `u32 flashing_frame_before_life_over` [derived: FUN_7101659560]
  - +0x2A8..+0x2AC: rebound speed x/y add (f32 each)
- **Used by**: `src/app/fighter_core.cpp` (15+ param getter functions)
- **Research leads**:
  - .dynsym: `_ZN3lib9SingletonIN3app22FighterParamAccessor2EE9instance_E`
  - Accessed via FighterParamAccessor2+0x12D0 pointer dereference
  - Community names from param mod databases, all verified against Ghidra offsets
- **Best guess**: Physics/kinetic common params sub-struct (confidence: high)

<!-- Template for new entries:

## UnkType_XXXXXXXX
- **Header**: `include/app/placeholders/UnkType_XXXXXXXX.h`
- **Size**: ~0xNNN bytes (estimated from largest offset + field size)
- **Known fields**:
  - +0x00: `void** vtable`
  - +0xNN: `type (description)` [derived/inferred: evidence]
- **Used by**: `src/app/file.cpp` (N functions)
- **Research leads**:
  - .dynsym: `symbol_name` references this type
  - Vtable at 0x71XXXXXXXX has N entries
  - Similar to `KnownType` (shares N fields)
- **Best guess**: `ClassName` (confidence: low/medium/high)

-->
