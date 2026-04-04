#include "types.h"

// Forward-declare in global scope to match original mangled names
struct FighterInformation;
struct FighterManager;
struct BattleObjectWorld;

namespace app::lua_bind {

// ============================================================
// FighterInformation — fi+0x08 → data pointer, read bool fields
// Pattern: ldr x8,[x0,#8]; ldrb w0,[x8,#off]; ret  (12 bytes)
// ============================================================

// 0x71020c9dd0
bool FighterInformation__is_rabbit_cap_impl(FighterInformation* fi) {
    return *reinterpret_cast<bool*>(*reinterpret_cast<u8**>(reinterpret_cast<u8*>(fi) + 8) + 0x59);
}

// 0x71020c9de0
bool FighterInformation__is_reflector_impl(FighterInformation* fi) {
    return *reinterpret_cast<bool*>(*reinterpret_cast<u8**>(reinterpret_cast<u8*>(fi) + 8) + 0x5a);
}

// 0x71020c9df0
bool FighterInformation__is_superleaf_impl(FighterInformation* fi) {
    return *reinterpret_cast<bool*>(*reinterpret_cast<u8**>(reinterpret_cast<u8*>(fi) + 8) + 0x5b);
}

// 0x71020c9e00
bool FighterInformation__is_rocketbelt_impl(FighterInformation* fi) {
    return *reinterpret_cast<bool*>(*reinterpret_cast<u8**>(reinterpret_cast<u8*>(fi) + 8) + 0x5c);
}

// 0x71020c9e10
bool FighterInformation__is_screw_impl(FighterInformation* fi) {
    return *reinterpret_cast<bool*>(*reinterpret_cast<u8**>(reinterpret_cast<u8*>(fi) + 8) + 0x5d);
}

// 0x71020c9e20
bool FighterInformation__is_backshield_impl(FighterInformation* fi) {
    return *reinterpret_cast<bool*>(*reinterpret_cast<u8**>(reinterpret_cast<u8*>(fi) + 8) + 0x5e);
}

// 0x71020c9e30
bool FighterInformation__is_operation_cpu_impl(FighterInformation* fi) {
    return *reinterpret_cast<bool*>(*reinterpret_cast<u8**>(reinterpret_cast<u8*>(fi) + 8) + 0x92);
}

// 0x71020c9e40
bool FighterInformation__get_no_change_hp_impl(FighterInformation* fi) {
    return *reinterpret_cast<bool*>(*reinterpret_cast<u8**>(reinterpret_cast<u8*>(fi) + 8) + 0x93);
}

// 0x71020c9ef0
bool FighterInformation__is_last_dead_suicide_impl(FighterInformation* fi) {
    return *reinterpret_cast<bool*>(*reinterpret_cast<u8**>(reinterpret_cast<u8*>(fi) + 8) + 0x1a3);
}

// 0x71020c9f10
bool FighterInformation__is_on_rebirth_impl(FighterInformation* fi) {
    return *reinterpret_cast<bool*>(*reinterpret_cast<u8**>(reinterpret_cast<u8*>(fi) + 8) + 0x38c);
}

// 0x71020c9f90
bool FighterInformation__is_battle_event_stick_reverse_impl(FighterInformation* fi) {
    return *reinterpret_cast<bool*>(*reinterpret_cast<u8**>(reinterpret_cast<u8*>(fi) + 8) + 0x9ca);
}

// ============================================================
// FighterManager — mgr+0x00 → data pointer
// Read pattern: ldr x8,[x0]; ldrb w0,[x8,#off]; ret  (12 bytes)
// Write pattern: ldr x8,[x0]; and w9,w1,#1; strb w9,[x8,#off]; ret  (16 bytes)
// ============================================================

// 0x71021410e0
u8 FighterManager__is_discretion_final_enabled_impl(FighterManager* mgr) {
    return *reinterpret_cast<u8*>(*reinterpret_cast<u8**>(mgr) + 0xcc);
}

// 0x71021411f0
u8 FighterManager__is_ready_go_impl(FighterManager* mgr) {
    return *reinterpret_cast<u8*>(*reinterpret_cast<u8**>(mgr) + 0xd2);
}

// 0x7102141200
void FighterManager__set_cursor_whole_impl(FighterManager* mgr, bool val) {
    *reinterpret_cast<u8*>(*reinterpret_cast<u8**>(mgr) + 0xd6) = val;
}

// 0x7102141620
u8 FighterManager__is_result_mode_impl(FighterManager* mgr) {
    return *reinterpret_cast<u8*>(*reinterpret_cast<u8**>(mgr) + 0xe9);
}

// ============================================================
// BattleObjectWorld — direct byte read from struct
// Pattern: ldrb w0,[x0,#off]; ret  (8 bytes)
// ============================================================

// 0x7101fca2d0
bool BattleObjectWorld__is_move_impl(BattleObjectWorld* world) {
    return *reinterpret_cast<bool*>(reinterpret_cast<u8*>(world) + 0x5a);
}

// 0x7101fca2f0
bool BattleObjectWorld__is_disable_reverse_impl(BattleObjectWorld* world) {
    return *reinterpret_cast<bool*>(reinterpret_cast<u8*>(world) + 0x5d);
}

} // namespace app::lua_bind
