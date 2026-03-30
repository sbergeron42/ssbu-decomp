#include "app/BattleObjectModuleAccessor.h"

namespace app::lua_bind {

// WorkModule vtable dispatchers — accessor+0x50

// 710208db50 — get_float  [vtable+0x58]
f32 WorkModule__get_float_impl(BattleObjectModuleAccessor* accessor, s32 index) {
    auto* module = accessor->work_module;
    auto* vtable = *reinterpret_cast<void***>(module);
    return reinterpret_cast<f32 (*)(void*, s32)>(vtable[0x58 / 8])(module, index);
}

// 710208db80 — add_float  [vtable+0x78]
f32 WorkModule__add_float_impl(BattleObjectModuleAccessor* accessor, s32 index, f32 value) {
    auto* module = accessor->work_module;
    auto* vtable = *reinterpret_cast<void***>(module);
    return reinterpret_cast<f32 (*)(void*, s32, f32)>(vtable[0x78 / 8])(module, index, value);
}

// 710208dba0 — mul_float  [vtable+0x88]
f32 WorkModule__mul_float_impl(BattleObjectModuleAccessor* accessor, s32 index, f32 value) {
    auto* module = accessor->work_module;
    auto* vtable = *reinterpret_cast<void***>(module);
    return reinterpret_cast<f32 (*)(void*, s32, f32)>(vtable[0x88 / 8])(module, index, value);
}

// 710208dbb0 — div_float  [vtable+0x90]
f32 WorkModule__div_float_impl(BattleObjectModuleAccessor* accessor, s32 index, f32 value) {
    auto* module = accessor->work_module;
    auto* vtable = *reinterpret_cast<void***>(module);
    return reinterpret_cast<f32 (*)(void*, s32, f32)>(vtable[0x90 / 8])(module, index, value);
}

// 710208dbc0 — get_int  [vtable+0x98]
s32 WorkModule__get_int_impl(BattleObjectModuleAccessor* accessor, s32 index) {
    auto* module = accessor->work_module;
    auto* vtable = *reinterpret_cast<void***>(module);
    return reinterpret_cast<s32 (*)(void*, s32)>(vtable[0x98 / 8])(module, index);
}

// 710208dbe0 — get_int64  [vtable+0xb0]
s64 WorkModule__get_int64_impl(BattleObjectModuleAccessor* accessor, s32 index) {
    auto* module = accessor->work_module;
    auto* vtable = *reinterpret_cast<void***>(module);
    return reinterpret_cast<s64 (*)(void*, s32)>(vtable[0xb0 / 8])(module, index);
}

// 710208dc10 — inc_int  [vtable+0xc8]
void WorkModule__inc_int_impl(BattleObjectModuleAccessor* accessor, s32 index) {
    auto* module = accessor->work_module;
    auto* vtable = *reinterpret_cast<void***>(module);
    reinterpret_cast<void (*)(void*, s32)>(vtable[0xc8 / 8])(module, index);
}

// 710208dc20 — dec_int  [vtable+0xd0]
void WorkModule__dec_int_impl(BattleObjectModuleAccessor* accessor, s32 index) {
    auto* module = accessor->work_module;
    auto* vtable = *reinterpret_cast<void***>(module);
    reinterpret_cast<void (*)(void*, s32)>(vtable[0xD0 / 8])(module, index);
}

// 710208dc30 — add_int  [vtable+0xd8]
void WorkModule__add_int_impl(BattleObjectModuleAccessor* accessor, s32 index, s32 value) {
    auto* module = accessor->work_module;
    auto* vtable = *reinterpret_cast<void***>(module);
    reinterpret_cast<void (*)(void*, s32, s32)>(vtable[0xD8 / 8])(module, index, value);
}

// 710208dc50 — mul_int  [vtable+0xe8]
void WorkModule__mul_int_impl(BattleObjectModuleAccessor* accessor, s32 index, s32 value, s32 p3) {
    auto* module = accessor->work_module;
    auto* vtable = *reinterpret_cast<void***>(module);
    reinterpret_cast<void (*)(void*, s32, s32, s32)>(vtable[0xe8 / 8])(module, index, value, p3);
}

// 710208dc60 — div_int  [vtable+0xf0]
void WorkModule__div_int_impl(BattleObjectModuleAccessor* accessor, s32 index, s32 value, s32 p3) {
    auto* module = accessor->work_module;
    auto* vtable = *reinterpret_cast<void***>(module);
    reinterpret_cast<void (*)(void*, s32, s32, s32)>(vtable[0xf0 / 8])(module, index, value, p3);
}

// 710208dc70 — count_down_int  [vtable+0xf8]
void WorkModule__count_down_int_impl(BattleObjectModuleAccessor* accessor, s32 index, s32 value, s32 p3) {
    auto* module = accessor->work_module;
    auto* vtable = *reinterpret_cast<void***>(module);
    reinterpret_cast<void (*)(void*, s32, s32, s32)>(vtable[0xf8 / 8])(module, index, value, p3);
}

// 710208dc80 — is_flag  [vtable+0x108]
bool WorkModule__is_flag_impl(BattleObjectModuleAccessor* accessor, s32 index) {
    auto* module = accessor->work_module;
    auto* vtable = *reinterpret_cast<void***>(module);
    return reinterpret_cast<bool (*)(void*, s32)>(vtable[0x108 / 8])(module, index);
}

// 710208dce0 — enable_transition_term_group  [vtable+0x140]
void WorkModule__enable_transition_term_group_impl(BattleObjectModuleAccessor* accessor, s32 group) {
    auto* module = accessor->work_module;
    auto* vtable = *reinterpret_cast<void***>(module);
    reinterpret_cast<void (*)(void*, s32)>(vtable[0x140 / 8])(module, group);
}

// 710208dd00 — clear_transition_term_group  [vtable+0x150]
void WorkModule__clear_transition_term_group_impl(BattleObjectModuleAccessor* accessor, s32 group) {
    auto* module = accessor->work_module;
    auto* vtable = *reinterpret_cast<void***>(module);
    reinterpret_cast<void (*)(void*, s32)>(vtable[0x150 / 8])(module, group);
}

// 710208dd10 — is_enable_transition_term_group  [vtable+0x158]
bool WorkModule__is_enable_transition_term_group_impl(BattleObjectModuleAccessor* accessor, s32 group) {
    auto* module = accessor->work_module;
    auto* vtable = *reinterpret_cast<void***>(module);
    return reinterpret_cast<bool (*)(void*, s32)>(vtable[0x158 / 8])(module, group);
}

// 710208dd60 — is_enable_transition_term  [vtable+0x180]
bool WorkModule__is_enable_transition_term_impl(BattleObjectModuleAccessor* accessor, s32 term) {
    auto* module = accessor->work_module;
    auto* vtable = *reinterpret_cast<void***>(module);
    return reinterpret_cast<bool (*)(void*, s32)>(vtable[0x180 / 8])(module, term);
}

// 710208dd70 — enable_transition_term  [vtable+0x188]
void WorkModule__enable_transition_term_impl(BattleObjectModuleAccessor* accessor, s32 term) {
    auto* module = accessor->work_module;
    auto* vtable = *reinterpret_cast<void***>(module);
    reinterpret_cast<void (*)(void*, s32)>(vtable[0x188 / 8])(module, term);
}

// 710208dd90 — clear_transition_term  [vtable+0x198]
void WorkModule__clear_transition_term_impl(BattleObjectModuleAccessor* accessor) {
    auto* module = accessor->work_module;
    auto* vtable = *reinterpret_cast<void***>(module);
    reinterpret_cast<void (*)(void*)>(vtable[0x198 / 8])(module);
}

// 710208de20 — clear_all  [vtable+0x220]
void WorkModule__clear_all_impl(BattleObjectModuleAccessor* accessor, s32 p1) {
    auto* module = accessor->work_module;
    auto* vtable = *reinterpret_cast<void***>(module);
    reinterpret_cast<void (*)(void*, s32)>(vtable[0x220 / 8])(module, p1);
}

// 710208de30 — get_param_int  [vtable+0x248]
s32 WorkModule__get_param_int_impl(BattleObjectModuleAccessor* accessor, s32 p1, s32 p2, s32 p3) {
    auto* module = accessor->work_module;
    auto* vtable = *reinterpret_cast<void***>(module);
    return reinterpret_cast<s32 (*)(void*, s32, s32, s32)>(vtable[0x248 / 8])(module, p1, p2, p3);
}

// 710208de40 — get_param_int64  [vtable+0x258]
s64 WorkModule__get_param_int64_impl(BattleObjectModuleAccessor* accessor, s32 p1, s32 p2, s32 p3) {
    auto* module = accessor->work_module;
    auto* vtable = *reinterpret_cast<void***>(module);
    return reinterpret_cast<s64 (*)(void*, s32, s32, s32)>(vtable[0x258 / 8])(module, p1, p2, p3);
}

// 710208de50 — get_param_float  [vtable+0x268]
f32 WorkModule__get_param_float_impl(BattleObjectModuleAccessor* accessor, s32 p1, s32 p2, s32 p3) {
    auto* module = accessor->work_module;
    auto* vtable = *reinterpret_cast<void***>(module);
    return reinterpret_cast<f32 (*)(void*, s32, s32, s32)>(vtable[0x268 / 8])(module, p1, p2, p3);
}

// 710208db60 — set_float  [vtable+0x60]
void WorkModule__set_float_impl(BattleObjectModuleAccessor* accessor, s32 index, f32 value) {
    auto* module = accessor->work_module;
    auto* vtable = *reinterpret_cast<void***>(module);
    reinterpret_cast<void (*)(void*, s32, f32)>(vtable[0x60 / 8])(module, index, value);
}
// 710208dbd0 — set_int  [vtable+0xa0]
void WorkModule__set_int_impl(BattleObjectModuleAccessor* accessor, s32 index, s32 value, s32 p3) {
    auto* module = accessor->work_module;
    auto* vtable = *reinterpret_cast<void***>(module);
    reinterpret_cast<void (*)(void*, s32, s32, s32)>(vtable[0xa0 / 8])(module, index, value, p3);
}
// 710208dbf0 — set_int64  [vtable+0xb8]
void WorkModule__set_int64_impl(BattleObjectModuleAccessor* accessor, s32 index, s64 value, s32 p3) {
    auto* module = accessor->work_module;
    auto* vtable = *reinterpret_cast<void***>(module);
    reinterpret_cast<void (*)(void*, s32, s64, s32)>(vtable[0xb8 / 8])(module, index, value, p3);
}
// 710208dc90 — on_flag  [vtable+0x110]
void WorkModule__on_flag_impl(BattleObjectModuleAccessor* accessor, s32 index) {
    auto* module = accessor->work_module;
    auto* vtable = *reinterpret_cast<void***>(module);
    reinterpret_cast<void (*)(void*, s32)>(vtable[0x110 / 8])(module, index);
}
// 710208dca0 — off_flag  [vtable+0x120]
void WorkModule__off_flag_impl(BattleObjectModuleAccessor* accessor, s32 index) {
    auto* module = accessor->work_module;
    auto* vtable = *reinterpret_cast<void***>(module);
    reinterpret_cast<void (*)(void*, s32)>(vtable[0x120 / 8])(module, index);
}
// 710208dcb0 — set_flag (bool param)  [vtable+0x130]
void WorkModule__set_flag_impl(BattleObjectModuleAccessor* accessor, bool value, s32 index) {
    auto* module = accessor->work_module;
    auto* vtable = *reinterpret_cast<void***>(module);
    reinterpret_cast<void (*)(void*, bool, s32)>(vtable[0x130 / 8])(module, value, index);
}
// 710208dd20 — enable_transition_term_group_ex  [vtable+0x160]
void WorkModule__enable_transition_term_group_ex_impl(BattleObjectModuleAccessor* accessor, s32 group) {
    auto* module = accessor->work_module;
    auto* vtable = *reinterpret_cast<void***>(module);
    reinterpret_cast<void (*)(void*, s32)>(vtable[0x160 / 8])(module, group);
}
// 710208dd30 — enable_transition_term_group_ex_all  [vtable+0x168]
void WorkModule__enable_transition_term_group_ex_all_impl(BattleObjectModuleAccessor* accessor, s32 group) {
    auto* module = accessor->work_module;
    auto* vtable = *reinterpret_cast<void***>(module);
    reinterpret_cast<void (*)(void*, s32)>(vtable[0x168 / 8])(module, group);
}
// 710208dda0 — is_enable_transition_term_forbid  [vtable+0x1a0]  (missing from search but exists)
// 710208ddb0 — enable_transition_term_forbid  [vtable+0x1a8]
void WorkModule__enable_transition_term_forbid_impl(BattleObjectModuleAccessor* accessor, s32 term) {
    auto* module = accessor->work_module;
    auto* vtable = *reinterpret_cast<void***>(module);
    reinterpret_cast<void (*)(void*, s32)>(vtable[0x1a8 / 8])(module, term);
}
// 710208ddd0 — enable_transition_term_forbid_group  [vtable+0x1b8]
void WorkModule__enable_transition_term_forbid_group_impl(BattleObjectModuleAccessor* accessor, s32 group) {
    auto* module = accessor->work_module;
    auto* vtable = *reinterpret_cast<void***>(module);
    reinterpret_cast<void (*)(void*, s32)>(vtable[0x1b8 / 8])(module, group);
}
// 710208ddf0 — clear_transition_term_forbid  [vtable+0x1c8]
void WorkModule__clear_transition_term_forbid_impl(BattleObjectModuleAccessor* accessor) {
    auto* module = accessor->work_module;
    auto* vtable = *reinterpret_cast<void***>(module);
    reinterpret_cast<void (*)(void*)>(vtable[0x1c8 / 8])(module);
}
// 710208de00 — enable_transition_term_forbid_indivi  [vtable+0x1f8]
void WorkModule__enable_transition_term_forbid_indivi_impl(BattleObjectModuleAccessor* accessor, s32 term) {
    auto* module = accessor->work_module;
    auto* vtable = *reinterpret_cast<void***>(module);
    reinterpret_cast<void (*)(void*, s32)>(vtable[0x1f8 / 8])(module, term);
}
// 710208de60 — set_customize_no  [vtable+0x278]
void WorkModule__set_customize_no_impl(BattleObjectModuleAccessor* accessor, s32 p1, s32 p2, s32 p3) {
    auto* module = accessor->work_module;
    auto* vtable = *reinterpret_cast<void***>(module);
    reinterpret_cast<void (*)(void*, s32, s32, s32)>(vtable[0x278 / 8])(module, p1, p2, p3);
}

} // namespace app::lua_bind
