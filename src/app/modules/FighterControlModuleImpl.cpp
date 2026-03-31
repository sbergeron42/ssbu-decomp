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

// Field reads — 3 instructions (ldr module, ldr/ldrb field, ret)
u32 FighterControlModuleImpl__get_attack_s4_turn_impl(BattleObjectModuleAccessor* a) {
    return *reinterpret_cast<u32*>(reinterpret_cast<u8*>(a->fighter_control_module) + 0x614);
}
u32 FighterControlModuleImpl__get_special_s_turn_impl(BattleObjectModuleAccessor* a) {
    return *reinterpret_cast<u32*>(reinterpret_cast<u8*>(a->fighter_control_module) + 0x610);
}
u8 FighterControlModuleImpl__special_command_623_step_impl(BattleObjectModuleAccessor* a) {
    return reinterpret_cast<u8*>(a->fighter_control_module)[0x620];
}
u8 FighterControlModuleImpl__special_command_236236_step_impl(BattleObjectModuleAccessor* a) {
    return reinterpret_cast<u8*>(a->fighter_control_module)[0x621];
}
u8 FighterControlModuleImpl__special_command_214214_step_impl(BattleObjectModuleAccessor* a) {
    return reinterpret_cast<u8*>(a->fighter_control_module)[0x622];
}
u8 FighterControlModuleImpl__special_command_21416_step_impl(BattleObjectModuleAccessor* a) {
    return reinterpret_cast<u8*>(a->fighter_control_module)[0x624];
}
u8 FighterControlModuleImpl__special_command_23634_step_impl(BattleObjectModuleAccessor* a) {
    return reinterpret_cast<u8*>(a->fighter_control_module)[0x623];
}

// Field writes — 3-4 instructions
void FighterControlModuleImpl__set_overwrite_pad_lr_impl(BattleObjectModuleAccessor* a, f32 val) {
    *reinterpret_cast<f32*>(reinterpret_cast<u8*>(a->fighter_control_module) + 0x60c) = val;
}
void FighterControlModuleImpl__reserve_on_attack_button_impl(BattleObjectModuleAccessor* a, u32 val) {
    *reinterpret_cast<u32*>(reinterpret_cast<u8*>(a->fighter_control_module) + 0x618) = val;
}
void FighterControlModuleImpl__set_button_smash_special_s_smash_impl(BattleObjectModuleAccessor* a, u32 val) {
    *reinterpret_cast<u32*>(reinterpret_cast<u8*>(a->fighter_control_module) + 0x628) = val;
}
void FighterControlModuleImpl__reserve_on_special_button_impl(BattleObjectModuleAccessor* a, u32 val) {
    *reinterpret_cast<u32*>(reinterpret_cast<u8*>(a->fighter_control_module) + 0x62c) = val;
}
void FighterControlModuleImpl__set_ref_stick_x_org_impl(BattleObjectModuleAccessor* a, f32 val) {
    *reinterpret_cast<f32*>(reinterpret_cast<u8*>(a->fighter_control_module) + 0x608) = val;
}

} // namespace app::lua_bind
