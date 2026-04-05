// fun_typed_d_010.cpp — WorkModule + ArticleModule + StatusModule + StopModule signature-fix dispatchers
// Binary mangled names have different parameter encodings than our builds.

#include "app/BattleObjectModuleAccessor.h"
#include "app/modules/ArticleModule.h"
#include "app/modules/StatusModule.h"

using app::BattleObjectModuleAccessor;
using app::ArticleModule;
using app::StatusModule;

#define WM(a) (a->work_module)
#define VT(m) (*reinterpret_cast<void***>(m))
#define AR(a) static_cast<ArticleModule*>((a)->article_module)
#define STP(a) (a->stop_module)

namespace app::lua_bind {

// ======================= WorkModule =======================

// count_down_int: CSV=(acc,s32,s32,s32), ABI passthrough (p3 unused)
void* WorkModule__count_down_int_fix(BattleObjectModuleAccessor* a, s32 p1, s32 p2)
    asm("_ZN3app8lua_bind31WorkModule__count_down_int_implEPNS_26BattleObjectModuleAccessorEiii");
void* WorkModule__count_down_int_fix(BattleObjectModuleAccessor* a, s32 p1, s32 p2) {
    auto* m = WM(a);
    return reinterpret_cast<void*(*)(void*, s32, s32)>(VT(m)[0xf8/8])(m, p1, p2);
}

// div_int: CSV=(acc,s32,s32,s32), ABI passthrough (p3 unused)
void* WorkModule__div_int_fix(BattleObjectModuleAccessor* a, s32 p1, s32 p2)
    asm("_ZN3app8lua_bind24WorkModule__div_int_implEPNS_26BattleObjectModuleAccessorEiii");
void* WorkModule__div_int_fix(BattleObjectModuleAccessor* a, s32 p1, s32 p2) {
    auto* m = WM(a);
    return reinterpret_cast<void*(*)(void*, s32, s32)>(VT(m)[0xf0/8])(m, p1, p2);
}

// mul_int: CSV=(acc,s32,s32,s32), ABI passthrough (p3 unused)
void* WorkModule__mul_int_fix(BattleObjectModuleAccessor* a, s32 p1, s32 p2)
    asm("_ZN3app8lua_bind24WorkModule__mul_int_implEPNS_26BattleObjectModuleAccessorEiii");
void* WorkModule__mul_int_fix(BattleObjectModuleAccessor* a, s32 p1, s32 p2) {
    auto* m = WM(a);
    return reinterpret_cast<void*(*)(void*, s32, s32)>(VT(m)[0xe8/8])(m, p1, p2);
}

// sub_int: CSV=(acc,s32,s32,s32), ABI passthrough (p3 unused)
void* WorkModule__sub_int_fix(BattleObjectModuleAccessor* a, s32 p1, s32 p2)
    asm("_ZN3app8lua_bind24WorkModule__sub_int_implEPNS_26BattleObjectModuleAccessorEiii");
void* WorkModule__sub_int_fix(BattleObjectModuleAccessor* a, s32 p1, s32 p2) {
    auto* m = WM(a);
    return reinterpret_cast<void*(*)(void*, s32, s32)>(VT(m)[0xe0/8])(m, p1, p2);
}

// set_int: CSV=(acc,s32,s32,s32), ABI passthrough (p3 unused)
void WorkModule__set_int_fix(BattleObjectModuleAccessor* a, s32 p1, s32 p2)
    asm("_ZN3app8lua_bind24WorkModule__set_int_implEPNS_26BattleObjectModuleAccessorEiii");
void WorkModule__set_int_fix(BattleObjectModuleAccessor* a, s32 p1, s32 p2) {
    auto* m = WM(a);
    reinterpret_cast<void(*)(void*, s32, s32)>(VT(m)[0xa0/8])(m, p1, p2);
}

// set_int64: CSV=(acc,s32,s64,s32), ABI passthrough (p3 unused)
void WorkModule__set_int64_fix(BattleObjectModuleAccessor* a, s32 p1, s64 p2)
    asm("_ZN3app8lua_bind26WorkModule__set_int64_implEPNS_26BattleObjectModuleAccessorEixi");
void WorkModule__set_int64_fix(BattleObjectModuleAccessor* a, s32 p1, s64 p2) {
    auto* m = WM(a);
    reinterpret_cast<void(*)(void*, s32, s64)>(VT(m)[0xb8/8])(m, p1, p2);
}

// get_param_int: CSV=(acc,s32,s32,s32), ABI passthrough (p3 unused)
void* WorkModule__get_param_int_fix(BattleObjectModuleAccessor* a, s32 p1, s32 p2)
    asm("_ZN3app8lua_bind30WorkModule__get_param_int_implEPNS_26BattleObjectModuleAccessorEiii");
void* WorkModule__get_param_int_fix(BattleObjectModuleAccessor* a, s32 p1, s32 p2) {
    auto* m = WM(a);
    return reinterpret_cast<void*(*)(void*, s32, s32)>(VT(m)[0x248/8])(m, p1, p2);
}

// get_param_int64: CSV=(acc,s32,s32,s32), ABI passthrough (p3 unused)
void* WorkModule__get_param_int64_fix(BattleObjectModuleAccessor* a, s32 p1, s32 p2)
    asm("_ZN3app8lua_bind32WorkModule__get_param_int64_implEPNS_26BattleObjectModuleAccessorEiii");
void* WorkModule__get_param_int64_fix(BattleObjectModuleAccessor* a, s32 p1, s32 p2) {
    auto* m = WM(a);
    return reinterpret_cast<void*(*)(void*, s32, s32)>(VT(m)[0x258/8])(m, p1, p2);
}

// get_param_float: CSV=(acc,s32,s32,s32), ABI passthrough (p3 unused)
void* WorkModule__get_param_float_fix(BattleObjectModuleAccessor* a, s32 p1, s32 p2)
    asm("_ZN3app8lua_bind32WorkModule__get_param_float_implEPNS_26BattleObjectModuleAccessorEiii");
void* WorkModule__get_param_float_fix(BattleObjectModuleAccessor* a, s32 p1, s32 p2) {
    auto* m = WM(a);
    return reinterpret_cast<void*(*)(void*, s32, s32)>(VT(m)[0x268/8])(m, p1, p2);
}

// set_customize_no: CSV=(acc,s32,s32,s32), ABI passthrough (p3 unused)
void WorkModule__set_customize_no_fix(BattleObjectModuleAccessor* a, s32 p1, s32 p2)
    asm("_ZN3app8lua_bind33WorkModule__set_customize_no_implEPNS_26BattleObjectModuleAccessorEiii");
void WorkModule__set_customize_no_fix(BattleObjectModuleAccessor* a, s32 p1, s32 p2) {
    auto* m = WM(a);
    reinterpret_cast<void(*)(void*, s32, s32)>(VT(m)[0x278/8])(m, p1, p2);
}

// enable_transition_term_group_impl_2: CSV=(acc,s32), ABI passthrough
void WorkModule__enable_transition_term_group_impl_2_fix(BattleObjectModuleAccessor* a, s32 group)
    asm("_ZN3app8lua_bind47WorkModule__enable_transition_term_group_impl_2EPNS_26BattleObjectModuleAccessorEi");
void WorkModule__enable_transition_term_group_impl_2_fix(BattleObjectModuleAccessor* a, s32 group) {
    auto* m = WM(a);
    reinterpret_cast<void(*)(void*, s32)>(VT(m)[0x148/8])(m, group);
}

// NOTE: WorkModule v0x1a0, v0x1b0, v0x1c0, v0x200 already in fun_typed_d_006.cpp

// ======================= ArticleModule =======================

// generate_article: CSV=(acc,u64,bool), build=(acc,u64,bool,u64)
void* ArticleModule__generate_article_fix(BattleObjectModuleAccessor* a, u64 p1, bool p2, u64 p3)
    asm("_ZN3app8lua_bind36ArticleModule__generate_article_implEPNS_26BattleObjectModuleAccessorEyb");
void* ArticleModule__generate_article_fix(BattleObjectModuleAccessor* a, u64 p1, bool p2, u64 p3) {
    return AR(a)->generate_article(p1, p2, p3);
}

// generate_article_enable: CSV=(acc,u64,bool), build=(acc,u64,bool,u64)
void* ArticleModule__generate_article_enable_fix(BattleObjectModuleAccessor* a, u64 p1, bool p2, u64 p3)
    asm("_ZN3app8lua_bind43ArticleModule__generate_article_enable_implEPNS_26BattleObjectModuleAccessorEyb");
void* ArticleModule__generate_article_enable_fix(BattleObjectModuleAccessor* a, u64 p1, bool p2, u64 p3) {
    return AR(a)->generate_article_enable(p1, p2, p3);
}

// generate_article_have_item: CSV=(acc,u64), build=(acc,u64,u64,u64)
void* ArticleModule__generate_article_have_item_fix(BattleObjectModuleAccessor* a, u64 p1, u64 p2, u64 p3)
    asm("_ZN3app8lua_bind46ArticleModule__generate_article_have_item_implEPNS_26BattleObjectModuleAccessorEy");
void* ArticleModule__generate_article_have_item_fix(BattleObjectModuleAccessor* a, u64 p1, u64 p2, u64 p3) {
    return AR(a)->generate_article_have_item(p1, p2, p3);
}

// have: CSV=(acc,u64,u64,u64,bool), build=(acc,u64,u64,u64,u64,bool)
void* ArticleModule__have_fix(BattleObjectModuleAccessor* a, u64 p1, u64 p2, u64 p3, u64 p4, bool p5)
    asm("_ZN3app8lua_bind24ArticleModule__have_implEPNS_26BattleObjectModuleAccessorEyyyb");
void* ArticleModule__have_fix(BattleObjectModuleAccessor* a, u64 p1, u64 p2, u64 p3, u64 p4, bool p5) {
    return AR(a)->have(p1, p2, p3, p4, p5);
}

// change_status: CSV=(acc,u64), build=(acc,u64,u64,u64)
void* ArticleModule__change_status_fix(BattleObjectModuleAccessor* a, u64 p1, u64 p2, u64 p3)
    asm("_ZN3app8lua_bind33ArticleModule__change_status_implEPNS_26BattleObjectModuleAccessorEy");
void* ArticleModule__change_status_fix(BattleObjectModuleAccessor* a, u64 p1, u64 p2, u64 p3) {
    return AR(a)->change_status(p1, p2, p3);
}

// change_status_exist: CSV=(acc,u64), build=(acc,u64,u64)
void* ArticleModule__change_status_exist_fix(BattleObjectModuleAccessor* a, u64 p1, u64 p2)
    asm("_ZN3app8lua_bind39ArticleModule__change_status_exist_implEPNS_26BattleObjectModuleAccessorEy");
void* ArticleModule__change_status_exist_fix(BattleObjectModuleAccessor* a, u64 p1, u64 p2) {
    return AR(a)->change_status_exist(p1, p2);
}

// get_article_from_no: CSV=(acc,u64), build=(acc,u64,u64)
u32 ArticleModule__get_article_from_no_fix(BattleObjectModuleAccessor* a, u64 p1, u64 p2)
    asm("_ZN3app8lua_bind39ArticleModule__get_article_from_no_implEPNS_26BattleObjectModuleAccessorEy");
u32 ArticleModule__get_article_from_no_fix(BattleObjectModuleAccessor* a, u64 p1, u64 p2) {
    return AR(a)->get_article_from_no(p1, p2);
}

// get_float: CSV=(acc,u64), build=(acc,u64,u64)
void* ArticleModule__get_float_fix(BattleObjectModuleAccessor* a, u64 p1, u64 p2)
    asm("_ZN3app8lua_bind29ArticleModule__get_float_implEPNS_26BattleObjectModuleAccessorEy");
void* ArticleModule__get_float_fix(BattleObjectModuleAccessor* a, u64 p1, u64 p2) {
    return AR(a)->get_float(p1, p2);
}

// get_int: CSV=(acc,u64), build=(acc,u64,u64)
void* ArticleModule__get_int_fix(BattleObjectModuleAccessor* a, u64 p1, u64 p2)
    asm("_ZN3app8lua_bind27ArticleModule__get_int_implEPNS_26BattleObjectModuleAccessorEy");
void* ArticleModule__get_int_fix(BattleObjectModuleAccessor* a, u64 p1, u64 p2) {
    return AR(a)->get_int(p1, p2);
}

// get_joint_pos: CSV=(acc,u64), build=(acc,u64,u64,u64)
void* ArticleModule__get_joint_pos_fix(BattleObjectModuleAccessor* a, u64 p1, u64 p2, u64 p3)
    asm("_ZN3app8lua_bind33ArticleModule__get_joint_pos_implEPNS_26BattleObjectModuleAccessorEy");
void* ArticleModule__get_joint_pos_fix(BattleObjectModuleAccessor* a, u64 p1, u64 p2, u64 p3) {
    return AR(a)->get_joint_pos(p1, p2, p3);
}

// get_joint_rotate: CSV=(acc,u64), build=(acc,u64,u64,u64)
void* ArticleModule__get_joint_rotate_fix(BattleObjectModuleAccessor* a, u64 p1, u64 p2, u64 p3)
    asm("_ZN3app8lua_bind36ArticleModule__get_joint_rotate_implEPNS_26BattleObjectModuleAccessorEy");
void* ArticleModule__get_joint_rotate_fix(BattleObjectModuleAccessor* a, u64 p1, u64 p2, u64 p3) {
    return AR(a)->get_joint_rotate(p1, p2, p3);
}

// is_flag: CSV=(acc,u64), build=(acc,u64,u64)
bool ArticleModule__is_flag_fix(BattleObjectModuleAccessor* a, u64 p1, u64 p2)
    asm("_ZN3app8lua_bind27ArticleModule__is_flag_implEPNS_26BattleObjectModuleAccessorEy");
bool ArticleModule__is_flag_fix(BattleObjectModuleAccessor* a, u64 p1, u64 p2) {
    return AR(a)->is_flag(p1, p2);
}

// is_flag_from_no: CSV=(acc,u64), build=(acc,u64,u64,u64)
bool ArticleModule__is_flag_from_no_fix(BattleObjectModuleAccessor* a, u64 p1, u64 p2, u64 p3)
    asm("_ZN3app8lua_bind35ArticleModule__is_flag_from_no_implEPNS_26BattleObjectModuleAccessorEy");
bool ArticleModule__is_flag_from_no_fix(BattleObjectModuleAccessor* a, u64 p1, u64 p2, u64 p3) {
    return AR(a)->is_flag_from_no(p1, p2, p3);
}

// motion_kind: CSV=no params, build=(u64,u64)
void* ArticleModule__motion_kind_fix(BattleObjectModuleAccessor* a, u64 p1, u64 p2)
    asm("_ZN3app8lua_bind31ArticleModule__motion_kind_implEPNS_26BattleObjectModuleAccessorE");
void* ArticleModule__motion_kind_fix(BattleObjectModuleAccessor* a, u64 p1, u64 p2) {
    return AR(a)->motion_kind(p1, p2);
}

// motion_kind_2nd: CSV=no params, build=(u64,u64)
void* ArticleModule__motion_kind_2nd_fix(BattleObjectModuleAccessor* a, u64 p1, u64 p2)
    asm("_ZN3app8lua_bind35ArticleModule__motion_kind_2nd_implEPNS_26BattleObjectModuleAccessorE");
void* ArticleModule__motion_kind_2nd_fix(BattleObjectModuleAccessor* a, u64 p1, u64 p2) {
    return AR(a)->motion_kind_2nd(p1, p2);
}

// remove: CSV=(acc,u64), build=(acc,u64,u64)
void* ArticleModule__remove_fix(BattleObjectModuleAccessor* a, u64 p1, u64 p2)
    asm("_ZN3app8lua_bind26ArticleModule__remove_implEPNS_26BattleObjectModuleAccessorEy");
void* ArticleModule__remove_fix(BattleObjectModuleAccessor* a, u64 p1, u64 p2) {
    return AR(a)->remove(p1, p2);
}

// remove_exist: CSV=(acc,u64), build=(acc,u64,u64)
void* ArticleModule__remove_exist_fix(BattleObjectModuleAccessor* a, u64 p1, u64 p2)
    asm("_ZN3app8lua_bind32ArticleModule__remove_exist_implEPNS_26BattleObjectModuleAccessorEy");
void* ArticleModule__remove_exist_fix(BattleObjectModuleAccessor* a, u64 p1, u64 p2) {
    return AR(a)->remove_exist(p1, p2);
}

// set_default_visibility: CSV=(acc,u64), build=(acc,u64,u64,u64)
void ArticleModule__set_default_visibility_fix(BattleObjectModuleAccessor* a, u64 p1, u64 p2, u64 p3)
    asm("_ZN3app8lua_bind42ArticleModule__set_default_visibility_implEPNS_26BattleObjectModuleAccessorEy");
void ArticleModule__set_default_visibility_fix(BattleObjectModuleAccessor* a, u64 p1, u64 p2, u64 p3) {
    AR(a)->set_default_visibility(p1, p2, p3);
}

// set_flag: CSV=(acc,u64,bool), build=(acc,u64,bool,u64)
void ArticleModule__set_flag_fix(BattleObjectModuleAccessor* a, u64 p1, bool p2, u64 p3)
    asm("_ZN3app8lua_bind28ArticleModule__set_flag_implEPNS_26BattleObjectModuleAccessorEyb");
void ArticleModule__set_flag_fix(BattleObjectModuleAccessor* a, u64 p1, bool p2, u64 p3) {
    AR(a)->set_flag(p1, p2, p3);
}

// set_float: CSV=(acc,u64), build=(acc,u64,u64)
void ArticleModule__set_float_fix(BattleObjectModuleAccessor* a, u64 p1, u64 p2)
    asm("_ZN3app8lua_bind29ArticleModule__set_float_implEPNS_26BattleObjectModuleAccessorEy");
void ArticleModule__set_float_fix(BattleObjectModuleAccessor* a, u64 p1, u64 p2) {
    AR(a)->set_float(p1, p2);
}

// set_frame_2nd: CSV=(acc,u64), build=(acc,u64,bool)
void ArticleModule__set_frame_2nd_fix(BattleObjectModuleAccessor* a, u64 p1, bool p2)
    asm("_ZN3app8lua_bind33ArticleModule__set_frame_2nd_implEPNS_26BattleObjectModuleAccessorEy");
void ArticleModule__set_frame_2nd_fix(BattleObjectModuleAccessor* a, u64 p1, bool p2) {
    AR(a)->set_frame_2nd(p1, p2);
}

// set_rate: CSV=(acc,u64,bool), build=(acc,u64) -- binary has more params
void ArticleModule__set_rate_fix(BattleObjectModuleAccessor* a, u64 p1, bool p2)
    asm("_ZN3app8lua_bind28ArticleModule__set_rate_implEPNS_26BattleObjectModuleAccessorEyb");
void ArticleModule__set_rate_fix(BattleObjectModuleAccessor* a, u64 p1, bool p2) {
    AR(a)->set_rate(p1);
}

// set_visibility_whole: CSV=(acc,u64,u64,bool) [yyb], ABI: p2 masked to bool
void ArticleModule__set_visibility_whole_fix(BattleObjectModuleAccessor* a, u64 p1, bool p2, u64 p3)
    asm("_ZN3app8lua_bind40ArticleModule__set_visibility_whole_implEPNS_26BattleObjectModuleAccessorEyyb");
void ArticleModule__set_visibility_whole_fix(BattleObjectModuleAccessor* a, u64 p1, bool p2, u64 p3) {
    AR(a)->set_visibility_whole(p1, p2, p3);
}

// ======================= StatusModule =======================

// prev_status_kind: CSV=no params, build=(u64)
void* StatusModule__prev_status_kind_fix(BattleObjectModuleAccessor* a, u64 p1)
    asm("_ZN3app8lua_bind35StatusModule__prev_status_kind_implEPNS_26BattleObjectModuleAccessorE");
void* StatusModule__prev_status_kind_fix(BattleObjectModuleAccessor* a, u64 p1) {
    auto* m = static_cast<StatusModule*>(a->status_module);
    return reinterpret_cast<void*(*)(StatusModule*, u64)>(m->vtbl->PrevStatusKind)(m, p1);
}

// ======================= StopModule =======================

// cancel_other_stop: CSV=no params, build=(u64)
void* StopModule__cancel_other_stop_fix(BattleObjectModuleAccessor* a, u64 p1)
    asm("_ZN3app8lua_bind34StopModule__cancel_other_stop_implEPNS_26BattleObjectModuleAccessorE");
void* StopModule__cancel_other_stop_fix(BattleObjectModuleAccessor* a, u64 p1) {
    auto* m = STP(a);
    return reinterpret_cast<void*(*)(void*,u64)>(VT(m)[0x60/8])(m, p1);
}

// get_other_stop: CSV=no params, build=(u64)
void* StopModule__get_other_stop_fix(BattleObjectModuleAccessor* a, u64 p1)
    asm("_ZN3app8lua_bind31StopModule__get_other_stop_implEPNS_26BattleObjectModuleAccessorE");
void* StopModule__get_other_stop_fix(BattleObjectModuleAccessor* a, u64 p1) {
    auto* m = STP(a);
    return reinterpret_cast<void*(*)(void*,u64)>(VT(m)[0x58/8])(m, p1);
}

// set_link_stop: CSV=(acc,u64,u64,bool), ABI: p1,p2 masked to bool
void StopModule__set_link_stop_fix(BattleObjectModuleAccessor* a, bool p1, bool p2)
    asm("_ZN3app8lua_bind30StopModule__set_link_stop_implEPNS_26BattleObjectModuleAccessorEyyb");
void StopModule__set_link_stop_fix(BattleObjectModuleAccessor* a, bool p1, bool p2) {
    auto* m = STP(a);
    reinterpret_cast<void(*)(void*,bool,bool)>(VT(m)[0x80/8])(m, p1, p2);
}

// set_other_stop: CSV=(acc,u64), build=(acc,u64,u64)
void StopModule__set_other_stop_fix(BattleObjectModuleAccessor* a, u64 p1, u64 p2)
    asm("_ZN3app8lua_bind31StopModule__set_other_stop_implEPNS_26BattleObjectModuleAccessorEy");
void StopModule__set_other_stop_fix(BattleObjectModuleAccessor* a, u64 p1, u64 p2) {
    auto* m = STP(a);
    reinterpret_cast<void(*)(void*,u64,u64)>(VT(m)[0x50/8])(m, p1, p2);
}

// set_special_stop: CSV=(acc,u64,bool), ABI: bool in x1
void StopModule__set_special_stop_fix(BattleObjectModuleAccessor* a, bool p1)
    asm("_ZN3app8lua_bind33StopModule__set_special_stop_implEPNS_26BattleObjectModuleAccessorEyb");
void StopModule__set_special_stop_fix(BattleObjectModuleAccessor* a, bool p1) {
    auto* m = STP(a);
    reinterpret_cast<void(*)(void*,bool)>(VT(m)[0xe0/8])(m, p1);
}

} // namespace app::lua_bind
