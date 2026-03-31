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
    return *reinterpret_cast<u32*>(reinterpret_cast<u8*>(a->fighter_control_module) + 0x610);
}
u32 FighterControlModuleImpl__get_special_s_turn_impl(BattleObjectModuleAccessor* a) {
    return *reinterpret_cast<u32*>(reinterpret_cast<u8*>(a->fighter_control_module) + 0x618);
}
u8 FighterControlModuleImpl__special_command_623_step_impl(BattleObjectModuleAccessor* a) {
    return reinterpret_cast<u8*>(a->fighter_control_module)[0x901];
}
u8 FighterControlModuleImpl__special_command_236236_step_impl(BattleObjectModuleAccessor* a) {
    return reinterpret_cast<u8*>(a->fighter_control_module)[0x961];
}
u8 FighterControlModuleImpl__special_command_214214_step_impl(BattleObjectModuleAccessor* a) {
    return reinterpret_cast<u8*>(a->fighter_control_module)[0x971];
}
u8 FighterControlModuleImpl__special_command_21416_step_impl(BattleObjectModuleAccessor* a) {
    return reinterpret_cast<u8*>(a->fighter_control_module)[0x981];
}
u8 FighterControlModuleImpl__special_command_23634_step_impl(BattleObjectModuleAccessor* a) {
    return reinterpret_cast<u8*>(a->fighter_control_module)[0x991];
}

// Field writes — 3-4 instructions
void FighterControlModuleImpl__set_overwrite_pad_lr_impl(BattleObjectModuleAccessor* a, f32 val) {
    *reinterpret_cast<f32*>(reinterpret_cast<u8*>(a->fighter_control_module) + 0x650) = val;
}
void FighterControlModuleImpl__reserve_on_attack_button_impl(BattleObjectModuleAccessor* a, u32 val) {
    reinterpret_cast<u8*>(a->fighter_control_module)[0x645] = 1;
}
void FighterControlModuleImpl__set_button_smash_special_s_smash_impl(BattleObjectModuleAccessor* a, u32 val) {
    auto* module = reinterpret_cast<u8*>(a->fighter_control_module);
    module[0xAD0] = val & 1;
}
void FighterControlModuleImpl__reserve_on_special_button_impl(BattleObjectModuleAccessor* a, u32 val) {
    reinterpret_cast<u8*>(a->fighter_control_module)[0xAD2] = 1;
}
void FighterControlModuleImpl__set_ref_stick_x_org_impl(BattleObjectModuleAccessor* a, u32 val) {
    auto* module = reinterpret_cast<u8*>(a->fighter_control_module);
    module[0xAB6] = val & 1;
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
// 71020aea90 — load control module, mask bool, tail call
extern "C" void FUN_71006be630(void*, bool);
void FighterControlModuleImpl__update_attack_air_kind_impl(BattleObjectModuleAccessor* a, bool val) {
    FUN_71006be630(CONTROL_MODULE(a), val & 1);
}

// 71020aeab0 — vtable call on +0x118, then conditional offset into +0x140 param data
f32 FighterControlModuleImpl__get_param_dash_s4_frame_impl(BattleObjectModuleAccessor* a) {
    auto* module = reinterpret_cast<u8*>(CONTROL_MODULE(a));
    auto* obj = *reinterpret_cast<void**>(module + 0x118);
    auto* vtable = *reinterpret_cast<void***>(obj);
    auto fn = reinterpret_cast<u8 (*)(void*)>(vtable[0x98 / 8]);
    u8 result = fn(obj);

    s64 param_offset;
    if (result == 0) {
        param_offset = 0xc0c;
    } else if (result == 2) {
        param_offset = 0xc08;
    } else {
        param_offset = 0x78;
    }

    auto* param_data = *reinterpret_cast<u8**>(module + 0x140);
    return *reinterpret_cast<f32*>(param_data + param_offset);
}

// 71020aeb70 — same pattern, returns scvtf (int→float), different offsets
f32 FighterControlModuleImpl__get_param_attack_lw4_flick_y_impl(BattleObjectModuleAccessor* a) {
    auto* module = reinterpret_cast<u8*>(CONTROL_MODULE(a));
    auto* obj = *reinterpret_cast<void**>(module + 0x118);
    auto* vtable = *reinterpret_cast<void***>(obj);
    auto fn = reinterpret_cast<u8 (*)(void*)>(vtable[0x98 / 8]);
    u8 result = fn(obj);

    s64 param_offset;
    if (result == 0) {
        param_offset = 0xc1c;
    } else if (result == 2) {
        param_offset = 0xc18;
    } else {
        param_offset = 0x2c0;
    }

    auto* param_data = *reinterpret_cast<u8**>(module + 0x140);
    return static_cast<f32>(*reinterpret_cast<s32*>(param_data + param_offset));
}

// 71020aebd0 — indexed clear: clear bit in bitfield at +0x568, zero entries at +0x578/+0x588
void FighterControlModuleImpl__delete_command_impl(BattleObjectModuleAccessor* a, s32 group, s32 bit) {
    auto* module = reinterpret_cast<u8*>(CONTROL_MODULE(a));
    auto* base = module + static_cast<s64>(group) * 0x28;
    u32 mask = 1u << bit;
    u32* flags = reinterpret_cast<u32*>(base + 0x568);
    *flags = *flags & ~mask;
    auto* table1 = *reinterpret_cast<u8**>(base + 0x578);
    table1[static_cast<u32>(bit)] = 0;
    auto* table2 = *reinterpret_cast<u64**>(base + 0x588);
    table2[static_cast<u32>(bit)] = 0;
}

// 71020aeda0 — ldr x0,[x0,#0x48]; b external
extern "C" void FUN_71006bed50(void*);
void FighterControlModuleImpl__check_hit_stop_delay_command_impl(BattleObjectModuleAccessor* a) {
    FUN_71006bed50(CONTROL_MODULE(a));
}

// 71020aedb0 — comparison chain on module fields +0x7e0, +0x7dc, +0x7d4, +0x140→+0x228
bool FighterControlModuleImpl__is_enable_hit_stop_delay_impl(BattleObjectModuleAccessor* a) {
    auto* module = reinterpret_cast<u8*>(CONTROL_MODULE(a));
    s32 val_e0 = *reinterpret_cast<s32*>(module + 0x7e0);
    if (val_e0 >= 1) {
        s32 val_dc = *reinterpret_cast<s32*>(module + 0x7dc);
        if (val_dc >= val_e0) return false;
    }
    s32 val_d4 = *reinterpret_cast<s32*>(module + 0x7d4);
    auto* param_data = *reinterpret_cast<u8**>(module + 0x140);
    s32 threshold = *reinterpret_cast<s32*>(param_data + 0x228);
    return val_d4 < threshold;
}

// 71020aedf0 — simpler comparison on +0x7e0 and +0x7dc
bool FighterControlModuleImpl__is_enable_hit_stop_delay_life_impl(BattleObjectModuleAccessor* a) {
    auto* module = reinterpret_cast<u8*>(CONTROL_MODULE(a));
    s32 val_e0 = *reinterpret_cast<s32*>(module + 0x7e0);
    if (val_e0 >= 1) {
        s32 val_dc = *reinterpret_cast<s32*>(module + 0x7dc);
        if (val_dc >= val_e0) return false;
    }
    return true;
}

} // namespace app::lua_bind
