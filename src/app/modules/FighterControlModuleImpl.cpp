#include "app/BattleObjectModuleAccessor.h"
#define CONTROL_MODULE(a) (a->fighter_control_module)
#define VT(m) (*reinterpret_cast<void***>(m))

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

// Indexed pointer chain reads/writes (5-6 instructions)
// Pattern: module + (index * 8) + base → load ptr → read/write field
u8 FighterControlModuleImpl__special_command_step_impl(BattleObjectModuleAccessor* a, s32 idx) {
    auto* p = reinterpret_cast<u8*>(a->fighter_control_module);
    auto* entry = *reinterpret_cast<u8**>(p + static_cast<s64>(idx) * 8 + 0x7f0);
    return entry[0x9];
}
void FighterControlModuleImpl__set_special_command_life_max_impl(BattleObjectModuleAccessor* a, s32 idx, u8 val) {
    auto* p = reinterpret_cast<u8*>(a->fighter_control_module);
    auto* entry = *reinterpret_cast<u8**>(p + static_cast<s64>(idx) * 8 + 0x7f0);
    entry[0xc] = val;
}
void FighterControlModuleImpl__set_special_command_life_impl(BattleObjectModuleAccessor* a, s32 idx, bool val) {
    auto* p = reinterpret_cast<u8*>(a->fighter_control_module);
    auto* entry = *reinterpret_cast<u8**>(p + static_cast<s64>(idx) * 8 + 0x7f0);
    entry[0xd] = val & 1;
}
void FighterControlModuleImpl__reset_special_command_individual_impl(BattleObjectModuleAccessor* a, s32 idx) {
    auto* p = reinterpret_cast<u8*>(a->fighter_control_module);
    auto* entry = *reinterpret_cast<u8**>(p + static_cast<s64>(idx) * 8 + 0x7f0);
    *reinterpret_cast<u16*>(entry + 0x8) = 0;
}

// Bit-test patterns (7 instructions: ldr field, lsl mask, tst, cset)
bool FighterControlModuleImpl__get_stick_button_trigger_impl(BattleObjectModuleAccessor* a, s32 bit) {
    auto* p = reinterpret_cast<u8*>(a->fighter_control_module);
    u8 flags = p[0xabe];
    return (flags & (1u << bit)) != 0;
}
bool FighterControlModuleImpl__get_stick_button_repeat_impl(BattleObjectModuleAccessor* a, s32 bit) {
    auto* p = reinterpret_cast<u8*>(a->fighter_control_module);
    u8 flags = p[0xac0];
    return (flags & (1u << bit)) != 0;
}

// Auto-generated named dispatchers
void* FighterControlModuleImpl__delete_reserve_turn_lr_impl(BattleObjectModuleAccessor* a,u64 p1,u64 p2) { auto* m=CONTROL_MODULE(a); return reinterpret_cast<void*(*)(void*,u64,u64)>(VT(m)[0x450/8])(m,p1,p2); }
void FighterControlModuleImpl__reset_special_command_impl(BattleObjectModuleAccessor* a,bool p1) { auto* m=CONTROL_MODULE(a); reinterpret_cast<void(*)(void*,bool)>(VT(m)[0x460/8])(m,p1); }
void* FighterControlModuleImpl__get_special_command_lr_impl(BattleObjectModuleAccessor* a,u64 p1) { auto* m=CONTROL_MODULE(a); return reinterpret_cast<void*(*)(void*,u64)>(VT(m)[0x470/8])(m,p1); }
} // namespace app::lua_bind
