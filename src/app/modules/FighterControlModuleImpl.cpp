#include "app/BattleObjectModuleAccessor.h"

namespace app::lua_bind {

// 71020aec30 — 3 instructions (trivial getter)
u32 FighterControlModuleImpl__get_attack_s3_turn_impl(BattleObjectModuleAccessor* accessor) {
    return *reinterpret_cast<u32*>(reinterpret_cast<u8*>(accessor->fighter_control_module) + 0x614);
}

// 71020aed80 — 6 instructions (indexed store with smaddl)
void FighterControlModuleImpl__set_command_life_count_impl(
    BattleObjectModuleAccessor* accessor, s32 index, s32 offset, u8 value)
{
    auto* module = reinterpret_cast<u8*>(accessor->fighter_control_module);
    auto* table = *reinterpret_cast<u8**>(module + static_cast<s64>(index) * 0x28 + 0x578);
    table[static_cast<u32>(offset)] = value;
}

// 71020aeb10 — 22 instructions (vtable call + conditional selects + frame)
f32 FighterControlModuleImpl__get_param_attack_hi4_flick_y_impl(BattleObjectModuleAccessor* accessor) {
    auto* module = reinterpret_cast<u8*>(accessor->fighter_control_module);
#ifdef MATCHING_HACK_NX_CLANG
    asm(""); // Prevent post-RA scheduler from moving fp setup past loads
#endif

    // vtable call: module+0x118 -> obj -> vtable[0x98/8]
    auto* obj = *reinterpret_cast<void**>(module + 0x118);
    auto* vtable = *reinterpret_cast<void***>(obj);
    auto fn = reinterpret_cast<u8 (*)(void*)>(vtable[0x98 / 8]);
    u8 result = fn(obj);

    s64 param_offset;
    if (result == 0) {
        param_offset = 0xc14;
    } else if (result == 2) {
        param_offset = 0xc10;
    } else {
        param_offset = 0x2b8;
    }

    auto* param_data = *reinterpret_cast<u8**>(module + 0x140);
    return static_cast<f32>(*reinterpret_cast<s32*>(param_data + param_offset));
}

} // namespace app::lua_bind
