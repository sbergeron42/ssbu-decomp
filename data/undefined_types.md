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

## BossEntity / BossEntitySlot
- **Header**: `include/app/placeholders/BossEntity.h`
- **Size**: BossEntity unknown (only vtable pointer mapped); BossEntitySlot = 0x10 bytes
- **Known fields**:
  - BossEntity+0x00: `BossEntityVtable* _vt` (vtable)
  - Vtable slot 2 (0x10): `bool is_expired(BossEntity*)` [derived: resolve_entity checks !vtable[2](entity)]
  - Vtable slot 6 (0x30): `s32 get_hash(BossEntity*)` [derived: boss iteration checks against target hash]
  - Vtable slot 10 (0x50): `void on_defeat(BossEntity*)` [derived: boss iteration calls on hash match]
  - BossEntitySlot+0x00: `BossEntity* entity` (managed pointer)
  - BossEntitySlot+0x08: `void* control_block` (shared_ptr control block)
- **Used by**: `src/app/BossManager.cpp` (3 entity iteration loops)
- **Research leads**:
  - Default singleton at 0x7104f73b70 (adrp 0x7104f73000 + 0xb70)
  - Vtable should be identifiable from the singleton's first 8 bytes in the binary
  - Entity list stored as std::vector in BossManagerInner at +0x110..+0x118
- **Best guess**: `BossEntity` or `BossItemBase` — likely inherits from a common item/entity base (confidence: medium)

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

## ItemKineticImpl
- **Header**: `include/app/placeholders/ItemKineticImpl.h`
- **Size**: at least 0xABC bytes (largest mapped offset +0xAB8 + 4)
- **Known fields**:
  - +0x3D0: `u8 param_gemini_vec[0x10]` [derived: set_param_gemini_impl zero-z/w SIMD write]
  - +0x9D8: `u32 kinetic_flags` [derived: get/set/on/off_kinetic_flag_impl]
  - +0x9E8: `u32 slope_type` [derived: set_slope_type_impl (<= 7 bounds check)]
  - +0xA04: `u32 it_ai_type` [derived: it_ai_type_impl]
  - +0xA10..+0xA2F: 4 x u64 (two Vec3 structs written together by it_ai_type_impl)
  - +0xA34: `f32 it_ai_distance_factor` [derived: range-checked to [0,1]]
  - +0xA50: `u8 it_ai_dir_rot_mode` [derived: `val & 1` bool store]
  - +0xA70: `f32 interpolate_rate` [derived: set_interpolate_rate_impl]
  - +0xA80: `u8 motion_trans_rate[0x10]` [derived: get_motion_trans_rate_impl returns &this+0xa80]
  - +0xA90: `f32 motion_trans_angle_rad` [derived: set_motion_trans_angle writes angle*deg2rad]
  - +0xAA0: `u8 motion_trans_rate_2nd[0x10]` [derived: get_motion_trans_rate_2nd_impl]
  - +0xAB0: `f32 motion_trans_angle_2nd_rad`
  - +0xAB4: `f32 param_gemini_p1`
  - +0xAB8: `f32 param_gemini_p2`
- **Used by**: `src/app/modules/ItemKineticModuleImpl.cpp` (17 dispatchers)
- **Research leads**:
  - .dynsym: all 17 `app::lua_bind::ItemKineticModuleImpl__*_impl` symbols
  - Concrete subclass of `KineticModule` (accessed via accessor+0x68 for item objects)
  - The 0x000..0x3CF region is the inherited KineticModule base + energy slots — needs separate research
  - Total object size unknown; only 0x3D0..0xABC mapped so far
- **Best guess**: `ItemKineticImpl` or `ItemKineticModuleImpl` (confidence: high — community name)

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
