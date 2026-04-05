// fun_typed_d_005.cpp — EffectModule signature-fix dispatchers (47 functions)
// Binary mangled names have different parameter counts than our EffectModule.cpp.

#include "app/BattleObjectModuleAccessor.h"
#include "app/modules/EffectModule.h"
#define EF(a) static_cast<EffectModule*>((a)->effect_module)

using app::BattleObjectModuleAccessor;
using app::EffectModule;

namespace app::lua_bind {

// --- request family (binary drops most params from mangled name) ---

void EffectModule__req_fix(BattleObjectModuleAccessor* a,u64 p1,u64 p2,u64 p3,u64 p4,u64 p5,bool p6,u64 p7)
    asm("_ZN3app8lua_bind22EffectModule__req_implEPNS_26BattleObjectModuleAccessorEyb");
void EffectModule__req_fix(BattleObjectModuleAccessor* a,u64 p1,u64 p2,u64 p3,u64 p4,u64 p5,bool p6,u64 p7) { EF(a)->req(p1,p2,p3,p4,p5,p6,p7); }

void EffectModule__req_attach_ground_fix(BattleObjectModuleAccessor* a,u64 p1,u64 p2,u64 p3,u64 p4,u64 p5,u64 p6,u64 p7)
    asm("_ZN3app8lua_bind36EffectModule__req_attach_ground_implEPNS_26BattleObjectModuleAccessorEy");
void EffectModule__req_attach_ground_fix(BattleObjectModuleAccessor* a,u64 p1,u64 p2,u64 p3,u64 p4,u64 p5,u64 p6,u64 p7) { EF(a)->req_attach_ground(p1,p2,p3,p4,p5,p6,p7); }

void EffectModule__req_continual_fix(BattleObjectModuleAccessor* a,u64 p1,u64 p2,u64 p3,u64 p4)
    asm("_ZN3app8lua_bind32EffectModule__req_continual_implEPNS_26BattleObjectModuleAccessorEy");
void EffectModule__req_continual_fix(BattleObjectModuleAccessor* a,u64 p1,u64 p2,u64 p3,u64 p4) { EF(a)->req_continual(p1,p2,p3,p4); }

void EffectModule__req_time_fix(BattleObjectModuleAccessor* a,u64 p1,u64 p2,u64 p3,u64 p4,u64 p5,bool p6,bool p7)
    asm("_ZN3app8lua_bind27EffectModule__req_time_implEPNS_26BattleObjectModuleAccessorEyyb");
void EffectModule__req_time_fix(BattleObjectModuleAccessor* a,u64 p1,u64 p2,u64 p3,u64 p4,u64 p5,bool p6,bool p7) { EF(a)->req_time(p1,p2,p3,p4,p5,p6,p7); }

void EffectModule__req_time_follow_fix(BattleObjectModuleAccessor* a,u64 p1,u64 p2,u64 p3,u64 p4,u64 p5,bool p6,u64 p7)
    asm("_ZN3app8lua_bind34EffectModule__req_time_follow_implEPNS_26BattleObjectModuleAccessorEyb");
void EffectModule__req_time_follow_fix(BattleObjectModuleAccessor* a,u64 p1,u64 p2,u64 p3,u64 p4,u64 p5,bool p6,u64 p7) { EF(a)->req_time_follow(p1,p2,p3,p4,p5,p6,p7); }

// --- emit/remove/kill (binary drops one param) ---

void EffectModule__req_emit_fix(BattleObjectModuleAccessor* a,u64 p1,u64 p2)
    asm("_ZN3app8lua_bind27EffectModule__req_emit_implEPNS_26BattleObjectModuleAccessorEy");
void EffectModule__req_emit_fix(BattleObjectModuleAccessor* a,u64 p1,u64 p2) { EF(a)->req_emit(p1,p2); }

void EffectModule__remove_fix(BattleObjectModuleAccessor* a,u64 p1,u64 p2)
    asm("_ZN3app8lua_bind25EffectModule__remove_implEPNS_26BattleObjectModuleAccessorEy");
void EffectModule__remove_fix(BattleObjectModuleAccessor* a,u64 p1,u64 p2) { EF(a)->remove(p1,p2); }

void EffectModule__remove_all_fix(BattleObjectModuleAccessor* a,u64 p1,u64 p2)
    asm("_ZN3app8lua_bind29EffectModule__remove_all_implEPNS_26BattleObjectModuleAccessorEy");
void EffectModule__remove_all_fix(BattleObjectModuleAccessor* a,u64 p1,u64 p2) { EF(a)->remove_all(p1,p2); }

void EffectModule__kill_fix(BattleObjectModuleAccessor* a,u64 p1,bool p2,bool p3)
    asm("_ZN3app8lua_bind23EffectModule__kill_implEPNS_26BattleObjectModuleAccessorEyb");
void EffectModule__kill_fix(BattleObjectModuleAccessor* a,u64 p1,bool p2,bool p3) { EF(a)->kill(p1,p2,p3); }

void EffectModule__kill_kind_fix(BattleObjectModuleAccessor* a,u64 p1,bool p2,bool p3)
    asm("_ZN3app8lua_bind28EffectModule__kill_kind_implEPNS_26BattleObjectModuleAccessorEyb");
void EffectModule__kill_kind_fix(BattleObjectModuleAccessor* a,u64 p1,bool p2,bool p3) { EF(a)->kill_kind(p1,p2,p3); }

void EffectModule__kill_joint_id_fix(BattleObjectModuleAccessor* a,u64 p1,bool p2,bool p3)
    asm("_ZN3app8lua_bind32EffectModule__kill_joint_id_implEPNS_26BattleObjectModuleAccessorEyb");
void EffectModule__kill_joint_id_fix(BattleObjectModuleAccessor* a,u64 p1,bool p2,bool p3) { EF(a)->kill_joint_id(p1,p2,p3); }

void EffectModule__kill_all_fix(BattleObjectModuleAccessor* a,u64 p1,bool p2,bool p3)
    asm("_ZN3app8lua_bind27EffectModule__kill_all_implEPNS_26BattleObjectModuleAccessorEyb");
void EffectModule__kill_all_fix(BattleObjectModuleAccessor* a,u64 p1,bool p2,bool p3) { EF(a)->kill_all(p1,p2,p3); }

// --- detach/end (binary drops one param) ---

void EffectModule__detach_kind_fix(BattleObjectModuleAccessor* a,u64 p1,u64 p2)
    asm("_ZN3app8lua_bind30EffectModule__detach_kind_implEPNS_26BattleObjectModuleAccessorEy");
void EffectModule__detach_kind_fix(BattleObjectModuleAccessor* a,u64 p1,u64 p2) { EF(a)->detach_kind(p1,p2); }

void EffectModule__detach_fix(BattleObjectModuleAccessor* a,u64 p1,u64 p2)
    asm("_ZN3app8lua_bind25EffectModule__detach_implEPNS_26BattleObjectModuleAccessorEy");
void EffectModule__detach_fix(BattleObjectModuleAccessor* a,u64 p1,u64 p2) { EF(a)->detach(p1,p2); }

void EffectModule__end_kind_fix(BattleObjectModuleAccessor* a,u64 p1,u64 p2)
    asm("_ZN3app8lua_bind27EffectModule__end_kind_implEPNS_26BattleObjectModuleAccessorEy");
void EffectModule__end_kind_fix(BattleObjectModuleAccessor* a,u64 p1,u64 p2) { EF(a)->end_kind(p1,p2); }

// --- after image ---

void EffectModule__clear_all_after_image_fix(BattleObjectModuleAccessor* a,u64 p1)
    asm("_ZN3app8lua_bind40EffectModule__clear_all_after_image_implEPNS_26BattleObjectModuleAccessorE");
void EffectModule__clear_all_after_image_fix(BattleObjectModuleAccessor* a,u64 p1) { EF(a)->clear_all_after_image(p1); }

void EffectModule__remove_after_image_fix(BattleObjectModuleAccessor* a,u64 p1,u64 p2)
    asm("_ZN3app8lua_bind37EffectModule__remove_after_image_implEPNS_26BattleObjectModuleAccessorEy");
void EffectModule__remove_after_image_fix(BattleObjectModuleAccessor* a,u64 p1,u64 p2) { EF(a)->remove_after_image(p1,p2); }

void EffectModule__remove_all_after_image_fix(BattleObjectModuleAccessor* a,u64 p1,u64 p2)
    asm("_ZN3app8lua_bind41EffectModule__remove_all_after_image_implEPNS_26BattleObjectModuleAccessorE");
void EffectModule__remove_all_after_image_fix(BattleObjectModuleAccessor* a,u64 p1,u64 p2) { EF(a)->remove_all_after_image(p1,p2); }

// --- transform (binary drops one param) ---

void EffectModule__set_pos_fix(BattleObjectModuleAccessor* a,u64 p1,u64 p2)
    asm("_ZN3app8lua_bind26EffectModule__set_pos_implEPNS_26BattleObjectModuleAccessorEy");
void EffectModule__set_pos_fix(BattleObjectModuleAccessor* a,u64 p1,u64 p2) { EF(a)->set_pos(p1,p2); }

void EffectModule__set_rot_fix(BattleObjectModuleAccessor* a,u64 p1,u64 p2)
    asm("_ZN3app8lua_bind26EffectModule__set_rot_implEPNS_26BattleObjectModuleAccessorEy");
void EffectModule__set_rot_fix(BattleObjectModuleAccessor* a,u64 p1,u64 p2) { EF(a)->set_rot(p1,p2); }

void EffectModule__set_scale_fix(BattleObjectModuleAccessor* a,u64 p1,u64 p2)
    asm("_ZN3app8lua_bind28EffectModule__set_scale_implEPNS_26BattleObjectModuleAccessorEy");
void EffectModule__set_scale_fix(BattleObjectModuleAccessor* a,u64 p1,u64 p2) { EF(a)->set_scale(p1,p2); }

// --- visibility/attr (binary drops one param) ---

void EffectModule__set_whole_attr_fix(BattleObjectModuleAccessor* a,bool p1,u64 p2)
    asm("_ZN3app8lua_bind33EffectModule__set_whole_attr_implEPNS_26BattleObjectModuleAccessorEb");
void EffectModule__set_whole_attr_fix(BattleObjectModuleAccessor* a,bool p1,u64 p2) { EF(a)->set_whole_attr(p1,p2); }

// --- screen effects (binary drops params) ---

void* EffectModule__fill_screen_fix(BattleObjectModuleAccessor* a,u64 p1,u64 p2,u64 p3,u64 p4,u64 p5,u64 p6)
    asm("_ZN3app8lua_bind30EffectModule__fill_screen_implEPNS_26BattleObjectModuleAccessorEy");
void* EffectModule__fill_screen_fix(BattleObjectModuleAccessor* a,u64 p1,u64 p2,u64 p3,u64 p4,u64 p5,u64 p6) { return EF(a)->fill_screen(p1,p2,p3,p4,p5,p6); }

void* EffectModule__fill_screen_2_fix(BattleObjectModuleAccessor* a,u64 p1,u64 p2,u64 p3,u64 p4,u64 p5,u64 p6)
    asm("_ZN3app8lua_bind32EffectModule__fill_screen_2_implEPNS_26BattleObjectModuleAccessorEy");
void* EffectModule__fill_screen_2_fix(BattleObjectModuleAccessor* a,u64 p1,u64 p2,u64 p3,u64 p4,u64 p5,u64 p6) { return EF(a)->fill_screen_2(p1,p2,p3,p4,p5,p6); }

void* EffectModule__color_collection_fix(BattleObjectModuleAccessor* a,u64 p1,u64 p2,u64 p3,u64 p4,u64 p5,u64 p6)
    asm("_ZN3app8lua_bind35EffectModule__color_collection_implEPNS_26BattleObjectModuleAccessorEy");
void* EffectModule__color_collection_fix(BattleObjectModuleAccessor* a,u64 p1,u64 p2,u64 p3,u64 p4,u64 p5,u64 p6) { return EF(a)->color_collection(p1,p2,p3,p4,p5,p6); }

void EffectModule__clear_screen_fix(BattleObjectModuleAccessor* a,u64 p1,u64 p2)
    asm("_ZN3app8lua_bind31EffectModule__clear_screen_implEPNS_26BattleObjectModuleAccessorEy");
void EffectModule__clear_screen_fix(BattleObjectModuleAccessor* a,u64 p1,u64 p2) { EF(a)->clear_screen(p1,p2); }

// --- common (binary adds param) ---

bool EffectModule__is_end_common_fix(BattleObjectModuleAccessor* a, u64 p1)
    asm("_ZN3app8lua_bind32EffectModule__is_end_common_implEPNS_26BattleObjectModuleAccessorEy");
bool EffectModule__is_end_common_fix(BattleObjectModuleAccessor* a, u64 p1) { return EF(a)->is_end_common(); }

// --- screen request (binary changes param types) ---

void EffectModule__req_screen_fix(BattleObjectModuleAccessor* a,u64 p1,bool p2,bool p3,bool p4)
    asm("_ZN3app8lua_bind29EffectModule__req_screen_implEPNS_26BattleObjectModuleAccessorEyyb");
void EffectModule__req_screen_fix(BattleObjectModuleAccessor* a,u64 p1,bool p2,bool p3,bool p4) { EF(a)->req_screen(p1,p2,p3,p4); }

void EffectModule__req_screen_system_fix(BattleObjectModuleAccessor* a,u64 p1,bool p2,bool p3)
    asm("_ZN3app8lua_bind36EffectModule__req_screen_system_implEPNS_26BattleObjectModuleAccessorEyb");
void EffectModule__req_screen_system_fix(BattleObjectModuleAccessor* a,u64 p1,bool p2,bool p3) { EF(a)->req_screen_system(p1,p2,p3); }

void EffectModule__remove_screen_fix(BattleObjectModuleAccessor* a,u64 p1,u64 p2)
    asm("_ZN3app8lua_bind32EffectModule__remove_screen_implEPNS_26BattleObjectModuleAccessorEy");
void EffectModule__remove_screen_fix(BattleObjectModuleAccessor* a,u64 p1,u64 p2) { EF(a)->remove_screen(p1,p2); }

// --- variation ---

u32 EffectModule__get_variation_effect_kind_fix(BattleObjectModuleAccessor* a,u64 p1,u64 p2)
    asm("_ZN3app8lua_bind44EffectModule__get_variation_effect_kind_implEPNS_26BattleObjectModuleAccessorEy");
u32 EffectModule__get_variation_effect_kind_fix(BattleObjectModuleAccessor* a,u64 p1,u64 p2) { return EF(a)->get_variation_effect_kind(p1,p2); }

// --- color/alpha/rate (binary adds unused param) ---

void EffectModule__set_rgb_partial_last_fix(BattleObjectModuleAccessor* a, u64 p1)
    asm("_ZN3app8lua_bind39EffectModule__set_rgb_partial_last_implEPNS_26BattleObjectModuleAccessorEy");
void EffectModule__set_rgb_partial_last_fix(BattleObjectModuleAccessor* a, u64 p1) { EF(a)->set_rgb_partial_last(); }

void EffectModule__set_rate_last_fix(BattleObjectModuleAccessor* a, u64 p1)
    asm("_ZN3app8lua_bind32EffectModule__set_rate_last_implEPNS_26BattleObjectModuleAccessorEy");
void EffectModule__set_rate_last_fix(BattleObjectModuleAccessor* a, u64 p1) { EF(a)->set_rate_last(); }

void EffectModule__set_alpha_last_fix(BattleObjectModuleAccessor* a, u64 p1)
    asm("_ZN3app8lua_bind33EffectModule__set_alpha_last_implEPNS_26BattleObjectModuleAccessorEy");
void EffectModule__set_alpha_last_fix(BattleObjectModuleAccessor* a, u64 p1) { EF(a)->set_alpha_last(); }

// --- slow/velocity ---

void EffectModule__set_slow_rate_mul_fix(BattleObjectModuleAccessor* a, u64 p1)
    asm("_ZN3app8lua_bind36EffectModule__set_slow_rate_mul_implEPNS_26BattleObjectModuleAccessorEy");
void EffectModule__set_slow_rate_mul_fix(BattleObjectModuleAccessor* a, u64 p1) { EF(a)->set_slow_rate_mul(); }

void EffectModule__set_slow_rate_no_stop_mul_fix(BattleObjectModuleAccessor* a, u64 p1)
    asm("_ZN3app8lua_bind44EffectModule__set_slow_rate_no_stop_mul_implEPNS_26BattleObjectModuleAccessorEy");
void EffectModule__set_slow_rate_no_stop_mul_fix(BattleObjectModuleAccessor* a, u64 p1) { EF(a)->set_slow_rate_no_stop_mul(); }

void EffectModule__set_add_vel_fix(BattleObjectModuleAccessor* a,u64 p1,u64 p2)
    asm("_ZN3app8lua_bind30EffectModule__set_add_vel_implEPNS_26BattleObjectModuleAccessorEy");
void EffectModule__set_add_vel_fix(BattleObjectModuleAccessor* a,u64 p1,u64 p2) { EF(a)->set_add_vel(p1,p2); }

void EffectModule__set_disable_render_offset_last_fix(BattleObjectModuleAccessor* a, u64 p1)
    asm("_ZN3app8lua_bind49EffectModule__set_disable_render_offset_last_implEPNS_26BattleObjectModuleAccessorEy");
void EffectModule__set_disable_render_offset_last_fix(BattleObjectModuleAccessor* a, u64 p1) { EF(a)->set_disable_render_offset_last(); }

// --- sync/hash/preset ---

void* EffectModule__unsync_vis_whole_fix(BattleObjectModuleAccessor* a,u64 p1)
    asm("_ZN3app8lua_bind35EffectModule__unsync_vis_whole_implEPNS_26BattleObjectModuleAccessorE");
void* EffectModule__unsync_vis_whole_fix(BattleObjectModuleAccessor* a,u64 p1) { return EF(a)->unsync_vis_whole(p1); }

void* EffectModule__make_offset_hash_fix(BattleObjectModuleAccessor* a,u64 p1,u64 p2)
    asm("_ZN3app8lua_bind35EffectModule__make_offset_hash_implEPNS_26BattleObjectModuleAccessorEy");
void* EffectModule__make_offset_hash_fix(BattleObjectModuleAccessor* a,u64 p1,u64 p2) { return EF(a)->make_offset_hash(p1,p2); }

void* EffectModule__preset_lifetime_rate_partial_fix(BattleObjectModuleAccessor* a, u64 p1)
    asm("_ZN3app8lua_bind47EffectModule__preset_lifetime_rate_partial_implEPNS_26BattleObjectModuleAccessorEy");
void* EffectModule__preset_lifetime_rate_partial_fix(BattleObjectModuleAccessor* a, u64 p1) { return EF(a)->preset_lifetime_rate_partial(); }

void* EffectModule__preset_curtail_emitter_fix(BattleObjectModuleAccessor* a, u64 p1)
    asm("_ZN3app8lua_bind41EffectModule__preset_curtail_emitter_implEPNS_26BattleObjectModuleAccessorEy");
void* EffectModule__preset_curtail_emitter_fix(BattleObjectModuleAccessor* a, u64 p1) { return EF(a)->preset_curtail_emitter(); }

void EffectModule__enable_sync_init_pos_last_fix(BattleObjectModuleAccessor* a, u64 p1)
    asm("_ZN3app8lua_bind44EffectModule__enable_sync_init_pos_last_implEPNS_26BattleObjectModuleAccessorEy");
void EffectModule__enable_sync_init_pos_last_fix(BattleObjectModuleAccessor* a, u64 p1) { EF(a)->enable_sync_init_pos_last(); }

// --- custom UV / post effects ---

void EffectModule__set_custom_uv_offset_fix(BattleObjectModuleAccessor* a,u64 p1,u64 p2,u64 p3)
    asm("_ZN3app8lua_bind39EffectModule__set_custom_uv_offset_implEPNS_26BattleObjectModuleAccessorEy");
void EffectModule__set_custom_uv_offset_fix(BattleObjectModuleAccessor* a,u64 p1,u64 p2,u64 p3) { EF(a)->set_custom_uv_offset(p1,p2,p3); }

void EffectModule__remove_post_effect_line_fix(BattleObjectModuleAccessor* a,u64 p1,bool p2)
    asm("_ZN3app8lua_bind42EffectModule__remove_post_effect_line_implEPNS_26BattleObjectModuleAccessorEb");
void EffectModule__remove_post_effect_line_fix(BattleObjectModuleAccessor* a,u64 p1,bool p2) { EF(a)->remove_post_effect_line(p1,p2); }

void* EffectModule__request_post_effect_line_circle_fix(BattleObjectModuleAccessor* a,u64 p1,u64 p2,bool p3)
    asm("_ZN3app8lua_bind50EffectModule__request_post_effect_line_circle_implEPNS_26BattleObjectModuleAccessorEb");
void* EffectModule__request_post_effect_line_circle_fix(BattleObjectModuleAccessor* a,u64 p1,u64 p2,bool p3) { return EF(a)->request_post_effect_line_circle(p1,p2,p3); }

void EffectModule__set_post_effect_line_circle_target_fix(BattleObjectModuleAccessor* a,u64 p1,bool p2)
    asm("_ZN3app8lua_bind53EffectModule__set_post_effect_line_circle_target_implEPNS_26BattleObjectModuleAccessorEb");
void EffectModule__set_post_effect_line_circle_target_fix(BattleObjectModuleAccessor* a,u64 p1,bool p2) { EF(a)->set_post_effect_line_circle_target(p1,p2); }

void* EffectModule__request_post_effect_line_parallel_2d_fix(BattleObjectModuleAccessor* a,u64 p1,bool p2)
    asm("_ZN3app8lua_bind55EffectModule__request_post_effect_line_parallel_2d_implEPNS_26BattleObjectModuleAccessorEb");
void* EffectModule__request_post_effect_line_parallel_2d_fix(BattleObjectModuleAccessor* a,u64 p1,bool p2) { return EF(a)->request_post_effect_line_parallel_2d(p1,p2); }

} // namespace app::lua_bind
