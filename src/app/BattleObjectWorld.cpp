#include "types.h"

// BattleObjectWorld -- operates on BattleObjectWorld* directly
// Simple struct field reads

struct BattleObjectWorld {
    u8  pad_0x00[0x4];
    f32 gravity_speed_coefficient;  // +0x4
    f32 scale_z;                    // +0x8
    u8  scale_z_disabled;           // +0xC
    u8  pad_0x0D[0x13];
    u8  move_speed[0x39];           // +0x20
    u8  is_gravity;                 // +0x59
    bool is_move;                   // +0x5A
    u8  pad_0x5B;
    u8  gravity_normal;             // +0x5C
    bool is_disable_reverse;        // +0x5D
};

namespace app::lua_bind {

// 7101fca1f0 -- 2 instructions
f32 BattleObjectWorld__gravity_speed_coefficient_impl(BattleObjectWorld* world) {
    return world->gravity_speed_coefficient;
}

// 7101fca2d0 -- 2 instructions
bool BattleObjectWorld__is_move_impl(BattleObjectWorld* world) {
    return world->is_move;
}

// 7101fca2e0 -- 2 instructions (returns pointer to +0x20)
void* BattleObjectWorld__move_speed_impl(BattleObjectWorld* world) {
    return world->move_speed;
}

// 7101fca2f0 -- 2 instructions
bool BattleObjectWorld__is_disable_reverse_impl(BattleObjectWorld* world) {
    return world->is_disable_reverse;
}

// 7101fca200 -- scale_z (5 instructions, branch)
f32 BattleObjectWorld__scale_z_impl(BattleObjectWorld* world) {
    if (world->scale_z_disabled) return 1.0f;
    return world->scale_z;
}

// 7101fca2b0 -- is_gravity_normal (8 instructions, branch)
bool BattleObjectWorld__is_gravity_normal_impl(BattleObjectWorld* world) {
    if (world->gravity_normal) return true;
    return world->is_gravity != 0;
}

} // namespace app::lua_bind
