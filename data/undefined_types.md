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

## FighterAI
- **Header**: `include/app/placeholders/FighterAI.h`
- **Size**: ~0xc80 bytes (from largest known offset 0xc7c + 2)
- **Known fields**:
  - +0x00: `void* mode_ptr` [derived: change_mode_action double-derefs]
  - +0x168: `FighterAIState* state` [derived: all AI_STATE accesses]
  - +0x170: `void** analyst_ptr` [derived: status_prev/count double-deref]
  - +0x180: action sub-object base [derived: change_action, enable/disable_command]
  - +0x198: `u16 action_id` [derived: act_id, set_action_id_none]
  - +0x19a: `u16 action_id_prev` [derived: set_action_id_none]
  - +0x270: `f32[4] goal_pos` [derived: goal_pos returns 16B]
  - +0x2bc: `s32 auto_stop` [derived: set_auto_stop]
  - +0x2fc: `u32 update_count` [derived: update_count, is_update_count_odd]
  - +0xad0..0xb84: indexed param tables (sp_u_high, sp_u_length, cliff, goal arrays)
  - +0xc08: `u8 cp_type` [derived: cp_type]
  - +0xc0c: `s32 rank` [derived: rank]
  - +0xc30: `f32[4] stick_data` [derived: reset_stick zeroes 16B]
  - +0xc40: `u32 button_state` [derived: add_button ORs bitmask]
  - +0xc50: target reference data [derived: target lookup functions]
  - +0xc7c: `s16 return_count` [derived: reset/set_no_return_frame]
- **Used by**: `src/app/ai_helpers_a.cpp` (50 functions)
- **Research leads**:
  - All app::ai::* functions in Ghidra .dynsym use this as context (L-8)
  - lua_ai_init at 0x71002c9900 (62KB) constructs this object
  - fighter_ai_init at 0x7100658af0 initializes per-fighter instance
- **Best guess**: `app::FighterAI` (confidence: high — .dynsym prefix matches)

## FighterAIState
- **Header**: `include/app/placeholders/FighterAI.h`
- **Size**: ~0x278 bytes
- **Known fields**:
  - +0x28: `u32 fighter_kind` [derived: fighter_kind getter]
  - +0x2c: `u32 status_kind` [derived: status_kind getter]
  - +0x30: `u32 prev_status_kind` [derived: prev_status_kind getter]
  - +0x38: `u64 motion_kind` [derived: motion_kind returns u64 hash]
  - +0x48: `u32 motion_frame` [derived: motion_frame getter]
  - +0x54: `u32 stat_flags` [derived: check_stat_air bit 0, check_over_ground bits 0-1]
  - +0x74: `u32 uniq_stat` [derived: uniq_stat, check_over_ground checks 6/7]
  - +0x80: `f32 pos_x` [derived: distance_to_target, floor_lr]
  - +0x84: `f32 pos_y` [derived: distance_y_to_target]
  - +0xc4: `f32 lr` [derived: lr_to_target fallback, lr getter]
  - +0xd0: `AIFloorCollisionData*` [derived: floor_width, floor_center]
  - +0xe0: `u32 damage` [derived: damage getter]
  - +0xe4: `u32 hp` [derived: hp getter]
  - +0xe8: `f32 shield_hp` / +0xec: `f32 shield_max` [derived: shield_rate = e8/ec]
  - +0x240: `s32 fighter_kind_index` [derived: indexed param lookups]
  - +0x274: `s32 predict_landing_frame` [derived: scvtf float conversion]
- **Used by**: `src/app/ai_helpers_a.cpp` (50 functions)
- **Research leads**:
  - Snapshot of per-frame fighter state, updated each AI tick
  - +0x10 contains accessor chain to BattleObjectModuleAccessor
  - stat_flags bits map to check_stat_* function family (30+ functions)
- **Best guess**: `app::FighterAIState` (confidence: medium — inferred from usage pattern)

## AIAnalyst
- **Header**: `include/app/placeholders/FighterAI.h`
- **Size**: >= 0x20 bytes
- **Known fields**:
  - +0x10: `u32 status_prev` [derived: app::analyst::status_prev]
  - +0x14: `u32 status_count` [derived: app::analyst::status_count]
  - +0x1c: `u32 chanced_frame` [derived: app::analyst::chanced_frame]
- **Used by**: `src/app/ai_helpers_a.cpp` (3 functions)
- **Research leads**:
  - Double-deref from FighterAI+0x170 suggests a shared_ptr or indirect owner
  - app::analyst namespace in .dynsym
- **Best guess**: `app::AIAnalyst` (confidence: medium)

## AIFloorCollisionData
- **Header**: `include/app/placeholders/FighterAI.h`
- **Size**: >= 0x60 bytes
- **Known fields**:
  - +0x10: `f32[4] movement` [derived: floor_moves returns 16B]
  - +0x20: `f32 left_edge` [derived: floor_width, floor_center]
  - +0x30: `f32 right_edge` [derived: floor_width, floor_center]
  - +0x5e: `u8 flags` [derived: check_over_ground reads bit 1]
- **Used by**: `src/app/ai_helpers_a.cpp` (7 functions)
- **Research leads**:
  - Shared between self and target (is_target_on_same_floor compares pointers)
  - Likely references GroundCollisionLine or similar stage collision data
- **Best guess**: Unknown (confidence: low)

## FighterAIManager
- **Header**: `include/app/placeholders/FighterAI.h`
- **Size**: >= 0x158 bytes
- **Known fields**:
  - +0xc8: `AIDeadZone* cam_bounds` [derived: dead_top/bottom/left/right]
  - +0x150: `u32 current_stage_id` [derived: current_id]
- **Used by**: `src/app/ai_helpers_a.cpp` (7 functions via DAT_71052b5fd8)
- **Research leads**:
  - Singleton at DAT_71052b5fd8 (double-deref pattern)
  - Also used as first param to FUN_7100314030 (target lookup)
- **Best guess**: `app::FighterAIManager` (confidence: high — .dynsym singleton pattern)

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
