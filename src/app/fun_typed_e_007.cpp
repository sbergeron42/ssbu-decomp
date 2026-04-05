// pool-e: SlowModule / StopModule / TurnModule / VisibilityModule lua_bind thunks
// Types-first HARD decomp — all vtable dispatchers for these 4 modules
//
// Functions where the mangled name's param list differs from the vtable's
// actual params use asm() overrides (same pattern as fun_typed_d_001.cpp).

#include "app/BattleObjectModuleAccessor.h"
#include "app/modules/SlowModule.h"
#include "app/modules/StopModule.h"
#include "app/modules/TurnModule.h"
#include "app/modules/VisibilityModule.h"

using app::BattleObjectModuleAccessor;
using app::SlowModule;
using app::StopModule;
using app::TurnModule;
using app::VisibilityModule;

#define SL(a) reinterpret_cast<SlowModule*>((a)->slow_module)
#define ST(a) reinterpret_cast<StopModule*>((a)->stop_module)
#define TN(a) reinterpret_cast<TurnModule*>((a)->turn_module)
#define VS(a) reinterpret_cast<VisibilityModule*>((a)->visibility_module)

namespace app::lua_bind {

// ===========================================================================
// SlowModule lua_bind thunks (0x7102080480 — 0x7102080590)
// ===========================================================================

// 0x7102080480  16B
bool SlowModule__is_slow_impl(BattleObjectModuleAccessor* a) {
    return SL(a)->is_slow();
}

// 0x7102080490  20B — mangled (acc,y,b), actual (acc,y,y,y,b,y)
void SlowModule__set_fix(BattleObjectModuleAccessor* a, u64 p1, u64 p2, u64 p3, bool p4, u64 p5)
    asm("_ZN3app8lua_bind20SlowModule__set_implEPNS_26BattleObjectModuleAccessorEyb");
void SlowModule__set_fix(BattleObjectModuleAccessor* a, u64 p1, u64 p2, u64 p3, bool p4, u64 p5) {
    SL(a)->set(p1, p2, p3, p4, p5);
}

// 0x71020804b0  16B
f32 SlowModule__mag_impl(BattleObjectModuleAccessor* a, u64 p1) {
    return SL(a)->mag(p1);
}

// 0x71020804c0  16B
f32 SlowModule__rate_ignore_effect_impl(BattleObjectModuleAccessor* a) {
    return SL(a)->rate_ignore_effect();
}

// 0x71020804d0  16B
f32 SlowModule__frame_impl(BattleObjectModuleAccessor* a, u64 p1) {
    return SL(a)->frame(p1);
}

// 0x71020804e0  16B
void SlowModule__clear_impl(BattleObjectModuleAccessor* a) {
    SL(a)->clear();
}

// 0x71020804f0  16B
void SlowModule__clear_2_impl(BattleObjectModuleAccessor* a, u64 p1) {
    SL(a)->clear_2(p1);
}

// 0x7102080500  20B
void SlowModule__clear_immediate_impl(BattleObjectModuleAccessor* a, u64 p1, bool p2) {
    SL(a)->clear_immediate(p1, p2);
}

// 0x7102080520  16B
f32 SlowModule__rate_impl2(BattleObjectModuleAccessor* a) {
    return SL(a)->rate();
}

// 0x7102080530  16B
bool SlowModule__is_skip_impl(BattleObjectModuleAccessor* a) {
    return SL(a)->is_skip();
}

// 0x7102080540  16B
bool SlowModule__is_prev_skip_impl(BattleObjectModuleAccessor* a) {
    return SL(a)->is_prev_skip();
}

// 0x7102080550  16B — mangled (acc,y), actual (acc,y,y)
void SlowModule__set_whole_fix(BattleObjectModuleAccessor* a, u64 p1, u64 p2)
    asm("_ZN3app8lua_bind26SlowModule__set_whole_implEPNS_26BattleObjectModuleAccessorEy");
void SlowModule__set_whole_fix(BattleObjectModuleAccessor* a, u64 p1, u64 p2) {
    SL(a)->set_whole(p1, p2);
}

// 0x7102080560  16B
void SlowModule__clear_whole_impl(BattleObjectModuleAccessor* a) {
    SL(a)->clear_whole();
}

// 0x7102080570  16B
f32 SlowModule__whole_mag_impl(BattleObjectModuleAccessor* a) {
    return SL(a)->whole_mag();
}

// 0x7102080580  16B
void SlowModule__set_whole_frame_impl(BattleObjectModuleAccessor* a, u64 p1) {
    SL(a)->set_whole_frame(p1);
}

// 0x7102080590  16B
f32 SlowModule__whole_frame_impl(BattleObjectModuleAccessor* a) {
    return SL(a)->whole_frame();
}

// ===========================================================================
// StopModule lua_bind thunks (0x7102089160 — 0x71020892b0)
// ===========================================================================

// 0x7102089160  16B
void StopModule__cancel_hit_stop_impl(BattleObjectModuleAccessor* a) {
    ST(a)->cancel_hit_stop();
}

// 0x7102089170  16B — mangled (acc,y), actual (acc,y,y)
void StopModule__set_other_stop_fix(BattleObjectModuleAccessor* a, u64 p1, u64 p2)
    asm("_ZN3app8lua_bind31StopModule__set_other_stop_implEPNS_26BattleObjectModuleAccessorEy");
void StopModule__set_other_stop_fix(BattleObjectModuleAccessor* a, u64 p1, u64 p2) {
    ST(a)->set_other_stop(p1, p2);
}

// 0x7102089180  16B — mangled (acc), actual (acc,y)
void* StopModule__get_other_stop_fix(BattleObjectModuleAccessor* a, u64 p1)
    asm("_ZN3app8lua_bind31StopModule__get_other_stop_implEPNS_26BattleObjectModuleAccessorE");
void* StopModule__get_other_stop_fix(BattleObjectModuleAccessor* a, u64 p1) {
    return ST(a)->get_other_stop(p1);
}

// 0x7102089190  16B — mangled (acc), actual (acc,y)
void* StopModule__cancel_other_stop_fix(BattleObjectModuleAccessor* a, u64 p1)
    asm("_ZN3app8lua_bind34StopModule__cancel_other_stop_implEPNS_26BattleObjectModuleAccessorE");
void* StopModule__cancel_other_stop_fix(BattleObjectModuleAccessor* a, u64 p1) {
    return ST(a)->cancel_other_stop(p1);
}

// 0x71020891a0  16B
void StopModule__set_item_stop_impl(BattleObjectModuleAccessor* a, u64 p1) {
    ST(a)->set_item_stop(p1);
}

// 0x71020891b0  16B
u32 StopModule__get_item_stop_impl(BattleObjectModuleAccessor* a) {
    return ST(a)->get_item_stop();
}

// 0x71020891c0  16B
void StopModule__cancel_item_stop_impl(BattleObjectModuleAccessor* a) {
    ST(a)->cancel_item_stop();
}

// 0x71020891d0  24B — mangled (acc,y,y,b), actual (acc,b,b)
void StopModule__set_link_stop_fix(BattleObjectModuleAccessor* a, bool p1, bool p2)
    asm("_ZN3app8lua_bind30StopModule__set_link_stop_implEPNS_26BattleObjectModuleAccessorEyyb");
void StopModule__set_link_stop_fix(BattleObjectModuleAccessor* a, bool p1, bool p2) {
    ST(a)->set_link_stop(p1, p2);
}

// 0x71020891f0  16B
bool StopModule__is_stop_impl(BattleObjectModuleAccessor* a) {
    return ST(a)->is_stop();
}

// 0x7102089200  16B
bool StopModule__is_special_stop_impl(BattleObjectModuleAccessor* a) {
    return ST(a)->is_special_stop();
}

// 0x7102089210  16B
bool StopModule__is_hit_impl(BattleObjectModuleAccessor* a) {
    return ST(a)->is_hit();
}

// 0x7102089220  16B
bool StopModule__is_damage_impl(BattleObjectModuleAccessor* a) {
    return ST(a)->is_damage();
}

// 0x7102089230  16B
bool StopModule__is_item_impl(BattleObjectModuleAccessor* a) {
    return ST(a)->is_item();
}

// 0x7102089240  16B
bool StopModule__is_other_impl(BattleObjectModuleAccessor* a) {
    return ST(a)->is_other();
}

// 0x7102089250  16B
u32 StopModule__get_hit_stop_real_frame_impl(BattleObjectModuleAccessor* a) {
    return ST(a)->get_hit_stop_real_frame();
}

// 0x7102089260  20B
void StopModule__set_hit_stop_frame_impl(BattleObjectModuleAccessor* a, u64 p1, bool p2) {
    ST(a)->set_hit_stop_frame(p1, p2);
}

// 0x7102089280  16B
void StopModule__set_hit_stop_frame_fix_impl(BattleObjectModuleAccessor* a, u64 p1) {
    ST(a)->set_hit_stop_frame_fix(p1);
}

// 0x7102089290  20B — mangled (acc,y,b), actual (acc,b)
void StopModule__set_special_stop_fix(BattleObjectModuleAccessor* a, bool p1)
    asm("_ZN3app8lua_bind33StopModule__set_special_stop_implEPNS_26BattleObjectModuleAccessorEyb");
void StopModule__set_special_stop_fix(BattleObjectModuleAccessor* a, bool p1) {
    ST(a)->set_special_stop(p1);
}

// 0x71020892b0  16B
void StopModule__end_stop_impl(BattleObjectModuleAccessor* a) {
    ST(a)->end_stop();
}

// ===========================================================================
// TurnModule lua_bind thunks (0x710208b6d0 — 0x710208b750)
// ===========================================================================

// 0x710208b6d0  28B
void TurnModule__set_turn_impl(BattleObjectModuleAccessor* a, u64 p1, bool p2, bool p3, bool p4) {
    TN(a)->set_turn(p1, p2, p3, p4);
}

// 0x710208b6f0  16B
void TurnModule__end_turn_impl(BattleObjectModuleAccessor* a) {
    TN(a)->end_turn();
}

// 0x710208b700  16B
bool TurnModule__is_turn_impl(BattleObjectModuleAccessor* a) {
    return TN(a)->is_turn();
}

// 0x710208b710  8B  stub: always false
bool TurnModule__is_turn_after90_impl(BattleObjectModuleAccessor* a) {
    return false;
}

// 0x710208b720  16B
bool TurnModule__is_extern_impl(BattleObjectModuleAccessor* a) {
    return TN(a)->is_extern();
}

// 0x710208b730  20B
void TurnModule__set_omit_intermediate_impl(BattleObjectModuleAccessor* a, bool p1) {
    TN(a)->set_omit_intermediate(p1);
}

// 0x710208b750  16B
void TurnModule__ry_reverse_impl(BattleObjectModuleAccessor* a) {
    TN(a)->ry_reverse();
}

// ===========================================================================
// VisibilityModule lua_bind thunks (0x710208bfe0 — 0x710208c153)
// ===========================================================================

// 0x710208bfe0  16B
void VisibilityModule__set_impl(BattleObjectModuleAccessor* a, u64 p1, u64 p2) {
    VS(a)->set(p1, p2);
}

// 0x710208bff0  16B — mangled (acc,y), actual (acc,y,y)
void VisibilityModule__set_int64_fix(BattleObjectModuleAccessor* a, u64 p1, u64 p2)
    asm("_ZN3app8lua_bind32VisibilityModule__set_int64_implEPNS_26BattleObjectModuleAccessorEy");
void VisibilityModule__set_int64_fix(BattleObjectModuleAccessor* a, u64 p1, u64 p2) {
    VS(a)->set_int64(p1, p2);
}

// 0x710208c000  16B
void VisibilityModule__set_status_default_impl(BattleObjectModuleAccessor* a, u64 p1, u64 p2) {
    VS(a)->set_status_default(p1, p2);
}

// 0x710208c010  16B
void VisibilityModule__set_status_default_int64_impl(BattleObjectModuleAccessor* a, u64 p1, u64 p2) {
    VS(a)->set_status_default_int64(p1, p2);
}

// 0x710208c020  16B
void VisibilityModule__reset_status_default_impl(BattleObjectModuleAccessor* a, u64 p1) {
    VS(a)->reset_status_default(p1);
}

// 0x710208c030  16B
void VisibilityModule__reset_status_default_int64_impl(BattleObjectModuleAccessor* a, u64 p1) {
    VS(a)->reset_status_default_int64(p1);
}

// 0x710208c040  16B
void VisibilityModule__reset_status_default_all_impl(BattleObjectModuleAccessor* a) {
    VS(a)->reset_status_default_all();
}

// 0x710208c050  16B
void VisibilityModule__set_default_all_impl(BattleObjectModuleAccessor* a) {
    VS(a)->set_default_all();
}

// 0x710208c060  20B — name collision with impl, use asm override
void VisibilityModule__set_mesh_visibility_thunk(BattleObjectModuleAccessor* a, u64 p1, u64 p2, bool p3)
    asm("_ZN3app8lua_bind42VisibilityModule__set_mesh_visibility_implEPNS_26BattleObjectModuleAccessorEyyb");
void VisibilityModule__set_mesh_visibility_thunk(BattleObjectModuleAccessor* a, u64 p1, u64 p2, bool p3) {
    VS(a)->set_mesh_visibility(p1, p2, p3);
}

// 0x710208c080  20B — name collision with impl, use asm override
void VisibilityModule__set_mesh_visibility_int64_thunk(BattleObjectModuleAccessor* a, u64 p1, u64 p2, bool p3)
    asm("_ZN3app8lua_bind48VisibilityModule__set_mesh_visibility_int64_implEPNS_26BattleObjectModuleAccessorEyyb");
void VisibilityModule__set_mesh_visibility_int64_thunk(BattleObjectModuleAccessor* a, u64 p1, u64 p2, bool p3) {
    VS(a)->set_mesh_visibility_int64(p1, p2, p3);
}

// 0x710208c0a0  20B
void VisibilityModule__set_material_anim_priority_impl(BattleObjectModuleAccessor* a, u64 p1, bool p2) {
    VS(a)->set_material_anim_priority(p1, p2);
}

// 0x710208c0c0  20B
void VisibilityModule__set_whole_impl(BattleObjectModuleAccessor* a, bool p1) {
    VS(a)->set_whole(p1);
}

// 0x710208c0e0  16B
u64 VisibilityModule__get_whole_impl(BattleObjectModuleAccessor* a) {
    return VS(a)->get_whole();
}

// 0x710208c0f0  16B — mangled (acc,y), actual (acc)
bool VisibilityModule__is_visible_fix(BattleObjectModuleAccessor* a)
    asm("_ZN3app8lua_bind33VisibilityModule__is_visible_implEPNS_26BattleObjectModuleAccessorEy");
bool VisibilityModule__is_visible_fix(BattleObjectModuleAccessor* a) {
    return VS(a)->is_visible();
}

// 0x710208c100  16B
void VisibilityModule__set_default_impl(BattleObjectModuleAccessor* a, u64 p1) {
    VS(a)->set_default(p1);
}

// 0x710208c110  16B
void VisibilityModule__set_default_int64_impl(BattleObjectModuleAccessor* a, u64 p1) {
    VS(a)->set_default_int64(p1);
}

// 0x710208c120  16B
bool VisibilityModule__is_visible_mesh_impl(BattleObjectModuleAccessor* a, u64 p1) {
    return VS(a)->is_visible_mesh(p1);
}

// 0x710208c130  16B
void VisibilityModule__set_visibility_mode_impl(BattleObjectModuleAccessor* a, u64 p1) {
    VS(a)->set_visibility_mode(p1);
}

// 0x710208c140  20B
void VisibilityModule__set_model_visible_impl(BattleObjectModuleAccessor* a, bool p1) {
    VS(a)->set_model_visible(p1);
}

} // namespace app::lua_bind
