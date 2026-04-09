#include "app/BattleObjectModuleAccessor.h"
#include "app/modules/WorkModule.h"

#define WM(a) (a->work_module)

namespace app::lua_bind {

// ============================================================
// WorkModule lua_bind vtable dispatchers -- accessor+0x50
// All functions load work_module, index vtable, tail-call.
// ============================================================

// --- Float operations ---

// 710208db50  get_float [vt+0x58]
f32 WorkModule__get_float_impl(BattleObjectModuleAccessor* a, s32 index) {
    return WM(a)->get_float(index);
}

// 710208db60  set_float [vt+0x60]
void WorkModule__set_float_impl(BattleObjectModuleAccessor* a, s32 index, f32 value) {
    WM(a)->set_float(index, value);
}

// 710208db70  rnd_float [vt+0x70]
f32 WorkModule__rnd_float_impl(BattleObjectModuleAccessor* a, s32 index) {
    return WM(a)->rnd_float(index);
}

// 710208db80  add_float [vt+0x78]
f32 WorkModule__add_float_impl(BattleObjectModuleAccessor* a, s32 index, f32 value) {
    return WM(a)->add_float(index, value);
}

// 710208db90  sub_float [vt+0x80]
f32 WorkModule__sub_float_impl(BattleObjectModuleAccessor* a, s32 index, f32 value) {
    return WM(a)->sub_float(index, value);
}

// 710208dba0  mul_float [vt+0x88]
f32 WorkModule__mul_float_impl(BattleObjectModuleAccessor* a, s32 index, f32 value) {
    return WM(a)->mul_float(index, value);
}

// 710208dbb0  div_float [vt+0x90]
f32 WorkModule__div_float_impl(BattleObjectModuleAccessor* a, s32 index, f32 value) {
    return WM(a)->div_float(index, value);
}

// --- Integer operations ---

// 710208dbc0  get_int [vt+0x98]
s32 WorkModule__get_int_impl(BattleObjectModuleAccessor* a, s32 index) {
    return WM(a)->get_int(index);
}

// 710208dbd0  set_int [vt+0xa0]
void WorkModule__set_int_impl(BattleObjectModuleAccessor* a, u64 p1, u64 p2) {
    auto* m = WM(a);
    reinterpret_cast<void(*)(WorkModule*, u64, u64)>(m->_vt[0xa0/8])(m, p1, p2);
}

// 710208dbe0  get_int64 [vt+0xb0]
s64 WorkModule__get_int64_impl(BattleObjectModuleAccessor* a, s32 index) {
    return WM(a)->get_int64(index);
}

// 710208dbf0  set_int64 [vt+0xb8]
void WorkModule__set_int64_impl(BattleObjectModuleAccessor* a, u64 p1, u64 p2) {
    auto* m = WM(a);
    reinterpret_cast<void(*)(WorkModule*, u64, u64)>(m->_vt[0xb8/8])(m, p1, p2);
}

// 710208dc00  rnd_int [vt+0xc0]
s32 WorkModule__rnd_int_impl(BattleObjectModuleAccessor* a, s32 p1, s32 p2, s32 p3) {
    return WM(a)->rnd_int(p1, p2, p3);
}

// 710208dc10  inc_int [vt+0xc8]
void WorkModule__inc_int_impl(BattleObjectModuleAccessor* a, s32 index) {
    WM(a)->inc_int(index);
}

// 710208dc20  dec_int [vt+0xd0]
void WorkModule__dec_int_impl(BattleObjectModuleAccessor* a, s32 index) {
    WM(a)->dec_int(index);
}

// 710208dc30  add_int [vt+0xd8]
void WorkModule__add_int_impl(BattleObjectModuleAccessor* a, s32 index, s32 value) {
    WM(a)->add_int(index, value);
}

// 710208dc40  sub_int [vt+0xe0]
void* WorkModule__sub_int_impl(BattleObjectModuleAccessor* a, u64 p1, u64 p2) {
    auto* m = WM(a);
    return reinterpret_cast<void*(*)(WorkModule*, u64, u64)>(m->_vt[0xe0/8])(m, p1, p2);
}

// 710208dc50  mul_int [vt+0xe8]
void* WorkModule__mul_int_impl(BattleObjectModuleAccessor* a, u64 p1, u64 p2) {
    auto* m = WM(a);
    return reinterpret_cast<void*(*)(WorkModule*, u64, u64)>(m->_vt[0xe8/8])(m, p1, p2);
}

// 710208dc60  div_int [vt+0xf0]
void* WorkModule__div_int_impl(BattleObjectModuleAccessor* a, u64 p1, u64 p2) {
    auto* m = WM(a);
    return reinterpret_cast<void*(*)(WorkModule*, u64, u64)>(m->_vt[0xf0/8])(m, p1, p2);
}

// 710208dc70  count_down_int [vt+0xf8]
void* WorkModule__count_down_int_impl(BattleObjectModuleAccessor* a, u64 p1, u64 p2) {
    auto* m = WM(a);
    return reinterpret_cast<void*(*)(WorkModule*, u64, u64)>(m->_vt[0xf8/8])(m, p1, p2);
}

// --- Flag operations ---

// 710208dc80  is_flag [vt+0x108]
bool WorkModule__is_flag_impl(BattleObjectModuleAccessor* a, s32 index) {
    return WM(a)->is_flag(index);
}

// 710208dc90  on_flag [vt+0x110]
void WorkModule__on_flag_impl(BattleObjectModuleAccessor* a, s32 index) {
    WM(a)->on_flag(index);
}

// 710208dca0  off_flag [vt+0x120]
void WorkModule__off_flag_impl(BattleObjectModuleAccessor* a, s32 index) {
    WM(a)->off_flag(index);
}

// 710208dcb0  set_flag [vt+0x130]
void WorkModule__set_flag_impl(BattleObjectModuleAccessor* a, bool value, s32 index) {
    WM(a)->set_flag(value, index);
}

// 710208dcd0  turn_off_flag [vt+0x138]
void WorkModule__turn_off_flag_impl(BattleObjectModuleAccessor* a, s32 index) {
    WM(a)->turn_off_flag(index);
}

// --- Transition term group operations ---

// 710208dce0  enable_transition_term_group [vt+0x140]
void WorkModule__enable_transition_term_group_impl(BattleObjectModuleAccessor* a, s32 group) {
    WM(a)->enable_transition_term_group(group);
}

// 710208dcf0  unable_transition_term_group [vt+0x148]
void WorkModule__enable_transition_term_group_impl_2(BattleObjectModuleAccessor* a, u64 group) {
    auto* m = WM(a);
    reinterpret_cast<void(*)(WorkModule*, u64)>(m->_vt[0x148/8])(m, group);
}

// 710208dd00  clear_transition_term_group [vt+0x150]
void WorkModule__clear_transition_term_group_impl(BattleObjectModuleAccessor* a, s32 group) {
    WM(a)->clear_transition_term_group(group);
}

// 710208dd10  is_enable_transition_term_group [vt+0x158]
bool WorkModule__is_enable_transition_term_group_impl(BattleObjectModuleAccessor* a, s32 group) {
    return WM(a)->is_enable_transition_term_group(group);
}

// 710208dd20  enable_transition_term_group_ex [vt+0x160]
void WorkModule__enable_transition_term_group_ex_impl(BattleObjectModuleAccessor* a, s32 group) {
    WM(a)->enable_transition_term_group_ex(group);
}

// 710208dd30  enable_transition_term_group_ex_all [vt+0x168]
void WorkModule__enable_transition_term_group_ex_all_impl(BattleObjectModuleAccessor* a, s32 group) {
    WM(a)->enable_transition_term_group_ex_all(group);
}

// 710208dd40  unable_transition_term_group_ex [vt+0x170]
void WorkModule__unable_transition_term_group_ex_impl(BattleObjectModuleAccessor* a, s32 group) {
    WM(a)->unable_transition_term_group_ex(group);
}

// 710208dd50  unable_transition_term_group_ex_all [vt+0x178]
void WorkModule__unable_transition_term_group_ex_all_impl(BattleObjectModuleAccessor* a, u64 group) {
    auto* m = WM(a);
    reinterpret_cast<void(*)(WorkModule*, u64)>(m->_vt[0x178/8])(m, group);
}

// --- Transition term operations ---

// 710208dd60  is_enable_transition_term [vt+0x180]
bool WorkModule__is_enable_transition_term_impl(BattleObjectModuleAccessor* a, s32 term) {
    return WM(a)->is_enable_transition_term(term);
}

// 710208dd70  enable_transition_term [vt+0x188]
void WorkModule__enable_transition_term_impl(BattleObjectModuleAccessor* a, s32 term) {
    WM(a)->enable_transition_term(term);
}

// 710208dd80  unable_transition_term [vt+0x190]
void WorkModule__unable_transition_term_impl(BattleObjectModuleAccessor* a, s32 term) {
    WM(a)->unable_transition_term(term);
}

// 710208dd90  clear_transition_term [vt+0x198]
void WorkModule__clear_transition_term_impl(BattleObjectModuleAccessor* a) {
    WM(a)->clear_transition_term();
}

// --- Transition term forbid operations ---

// 710208dda0  is_enable_transition_term_forbid [vt+0x1a0]
void WorkModule__v0x1a0(BattleObjectModuleAccessor* a, u64 p1) {
    auto* m = WM(a);
    reinterpret_cast<void(*)(WorkModule*, u64)>(m->_vt[0x1a0/8])(m, p1);
}

// 710208ddb0  enable_transition_term_forbid [vt+0x1a8]
void WorkModule__enable_transition_term_forbid_impl(BattleObjectModuleAccessor* a, s32 term) {
    WM(a)->enable_transition_term_forbid(term);
}

// 710208ddc0  unable_transition_term_forbid [vt+0x1b0]
void WorkModule__v0x1b0(BattleObjectModuleAccessor* a, u64 p1) {
    auto* m = WM(a);
    reinterpret_cast<void(*)(WorkModule*, u64)>(m->_vt[0x1b0/8])(m, p1);
}

// 710208ddd0  enable_transition_term_forbid_group [vt+0x1b8]
void WorkModule__enable_transition_term_forbid_group_impl(BattleObjectModuleAccessor* a, s32 group) {
    WM(a)->enable_transition_term_forbid_group(group);
}

// 710208dde0  unable_transition_term_forbid_group [vt+0x1c0]
void WorkModule__v0x1c0(BattleObjectModuleAccessor* a, u64 p1) {
    auto* m = WM(a);
    reinterpret_cast<void(*)(WorkModule*, u64)>(m->_vt[0x1c0/8])(m, p1);
}

// 710208ddf0  clear_transition_term_forbid [vt+0x1c8]
void WorkModule__clear_transition_term_forbid_impl(BattleObjectModuleAccessor* a) {
    WM(a)->clear_transition_term_forbid();
}

// 710208de00  enable_transition_term_forbid_indivi [vt+0x1f8]
void WorkModule__enable_transition_term_forbid_indivi_impl(BattleObjectModuleAccessor* a, s32 term) {
    WM(a)->enable_transition_term_forbid_indivi(term);
}

// 710208de10  unable_transition_term_forbid_indivi [vt+0x200]
void WorkModule__v0x200(BattleObjectModuleAccessor* a, u64 p1) {
    auto* m = WM(a);
    reinterpret_cast<void(*)(WorkModule*, u64)>(m->_vt[0x200/8])(m, p1);
}

// --- Misc operations ---

// 710208de20  clear_all [vt+0x220]
void WorkModule__clear_all_impl(BattleObjectModuleAccessor* a, s32 p1) {
    WM(a)->clear_all(p1);
}

// 710208de30  get_param_int [vt+0x248]
void* WorkModule__get_param_int_impl(BattleObjectModuleAccessor* a, u64 p1, u64 p2) {
    auto* m = WM(a);
    return reinterpret_cast<void*(*)(WorkModule*, u64, u64)>(m->_vt[0x248/8])(m, p1, p2);
}

// 710208de40  get_param_int64 [vt+0x258]
void* WorkModule__get_param_int64_impl(BattleObjectModuleAccessor* a, u64 p1, u64 p2) {
    auto* m = WM(a);
    return reinterpret_cast<void*(*)(WorkModule*, u64, u64)>(m->_vt[0x258/8])(m, p1, p2);
}

// 710208de50  get_param_float [vt+0x268]
void* WorkModule__get_param_float_impl(BattleObjectModuleAccessor* a, u64 p1, u64 p2) {
    auto* m = WM(a);
    return reinterpret_cast<void*(*)(WorkModule*, u64, u64)>(m->_vt[0x268/8])(m, p1, p2);
}

// 710208de60  set_customize_no [vt+0x278]
void WorkModule__set_customize_no_impl(BattleObjectModuleAccessor* a, u64 p1, u64 p2) {
    auto* m = WM(a);
    reinterpret_cast<void(*)(WorkModule*, u64, u64)>(m->_vt[0x278/8])(m, p1, p2);
}

} // namespace app::lua_bind
