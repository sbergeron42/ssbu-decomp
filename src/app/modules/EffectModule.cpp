#include "app/BattleObjectModuleAccessor.h"
#include "app/modules/EffectModule.h"
#define EF(a) static_cast<EffectModule*>((a)->effect_module)

namespace app::lua_bind {

// -- request family --
void EffectModule__req_impl(BattleObjectModuleAccessor* a,u64 p1,u64 p2,u64 p3,u64 p4,u64 p5,bool p6,u64 p7) { EF(a)->req(p1,p2,p3,p4,p5,p6,p7); }
void EffectModule__req_on_joint_impl(BattleObjectModuleAccessor* a, u64 p1, u64 p2, u64 p3, u64 p4, u64 p5, u64 p6, bool p7, u32 p8, u32 p9, u32 p10) { EF(a)->req_on_joint(p1,p2,p3,p4,p5,p6,p7,p8,p9,p10); }
void EffectModule__req_attach_ground_impl(BattleObjectModuleAccessor* a,u64 p1,u64 p2,u64 p3,u64 p4,u64 p5,u64 p6,u64 p7) { EF(a)->req_attach_ground(p1,p2,p3,p4,p5,p6,p7); }
void EffectModule__req_follow_impl(BattleObjectModuleAccessor* a, u64 p1, u64 p2, u64 p3, u64 p4, bool p5, u32 p6, s32 p7, s32 p8, s32 p9, s32 p10, bool p11, bool p12) { EF(a)->req_follow(p1,p2,p3,p4,p5,p6,p7,p8,p9,p10,p11,p12); }
void EffectModule__req_continual_impl(BattleObjectModuleAccessor* a,u64 p1,u64 p2,u64 p3,u64 p4) { EF(a)->req_continual(p1,p2,p3,p4); }

// -- continual management --
void EffectModule__remove_continual_impl(BattleObjectModuleAccessor* a,u64 p1) { EF(a)->remove_continual(p1); }
void EffectModule__remove_all_continual_impl(BattleObjectModuleAccessor* a) { EF(a)->remove_all_continual(); }

// -- timed effects --
void EffectModule__req_time_impl(BattleObjectModuleAccessor* a,u64 p1,u64 p2,u64 p3,u64 p4,u64 p5,bool p6,bool p7) { EF(a)->req_time(p1,p2,p3,p4,p5,p6,p7); }
void EffectModule__req_time_follow_impl(BattleObjectModuleAccessor* a,u64 p1,u64 p2,u64 p3,u64 p4,u64 p5,bool p6,u64 p7) { EF(a)->req_time_follow(p1,p2,p3,p4,p5,p6,p7); }
void EffectModule__remove_time_impl(BattleObjectModuleAccessor* a,u64 p1) { EF(a)->remove_time(p1); }
void EffectModule__remove_all_time_impl(BattleObjectModuleAccessor* a) { EF(a)->remove_all_time(); }

// -- emit/remove/kill --
void EffectModule__req_emit_impl(BattleObjectModuleAccessor* a,u64 p1,u64 p2) { EF(a)->req_emit(p1,p2); }
void EffectModule__remove_impl(BattleObjectModuleAccessor* a,u64 p1,u64 p2) { EF(a)->remove(p1,p2); }
void EffectModule__remove_all_impl(BattleObjectModuleAccessor* a,u64 p1,u64 p2) { EF(a)->remove_all(p1,p2); }
void EffectModule__kill_impl(BattleObjectModuleAccessor* a,u64 p1,bool p2,bool p3) { EF(a)->kill(p1,p2,p3); }
void EffectModule__kill_kind_impl(BattleObjectModuleAccessor* a,u64 p1,bool p2,bool p3) { EF(a)->kill_kind(p1,p2,p3); }
void EffectModule__kill_joint_id_impl(BattleObjectModuleAccessor* a,u64 p1,bool p2,bool p3) { EF(a)->kill_joint_id(p1,p2,p3); }
void EffectModule__kill_all_impl(BattleObjectModuleAccessor* a,u64 p1,bool p2,bool p3) { EF(a)->kill_all(p1,p2,p3); }

// -- detach/end --
void EffectModule__detach_all_impl(BattleObjectModuleAccessor* a, u64 p1) { EF(a)->detach_all(p1); }
void EffectModule__detach_kind_impl(BattleObjectModuleAccessor* a,u64 p1,u64 p2) { EF(a)->detach_kind(p1,p2); }
void EffectModule__detach_impl(BattleObjectModuleAccessor* a,u64 p1,u64 p2) { EF(a)->detach(p1,p2); }
void EffectModule__end_kind_impl(BattleObjectModuleAccessor* a,u64 p1,u64 p2) { EF(a)->end_kind(p1,p2); }

// -- after image --
// 7102017900 -- vtable[35] dispatch, tail call with stack arg passthrough
void EffectModule__req_after_image_impl(BattleObjectModuleAccessor* a, u64 p1, u64 p2, u64 p3, u64 p4, u32 p5, u64 p6, u64 p7, u32 p8, u64 p9, u64 p10, u64 p11, u64 p12, f32 p13, u8 p14, u8 p15, f32 p16, s32 p17, s32 p18, s32 p19) {
    auto* m = EF(a);
    reinterpret_cast<void(*)(EffectModule*, u64, u64, u64, u64, u32, u64, u64, u32, u64, u64, u64, u64, f32, u8, u8, f32, s32, s32, s32)>(m->_vt[35])(m, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13, p14, p15, p16, p17, p18, p19);
}
// 7102017950 -- vtable[37] dispatch, tail call with stack arg passthrough
void EffectModule__req_after_image_no_parent_impl(BattleObjectModuleAccessor* a, u64 p1, u64 p2, u32 p3, u64 p4, u64 p5, u32 p6, u64 p7, u64 p8, u64 p9, u64 p10, f32 p11, u8 p12, u8 p13, f32 p14, s32 p15, s32 p16, s32 p17) {
    auto* m = EF(a);
    reinterpret_cast<void(*)(EffectModule*, u64, u64, u32, u64, u64, u32, u64, u64, u64, u64, f32, u8, u8, f32, s32, s32, s32)>(m->_vt[37])(m, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13, p14, p15, p16, p17);
}
void EffectModule__clear_all_after_image_impl(BattleObjectModuleAccessor* a,u64 p1) { EF(a)->clear_all_after_image(p1); }
void EffectModule__remove_after_image_impl(BattleObjectModuleAccessor* a,u64 p1,u64 p2) { EF(a)->remove_after_image(p1,p2); }
void EffectModule__remove_all_after_image_impl(BattleObjectModuleAccessor* a,u64 p1,u64 p2) { EF(a)->remove_all_after_image(p1,p2); }

// -- transform --
void EffectModule__set_pos_impl(BattleObjectModuleAccessor* a,u64 p1,u64 p2) { EF(a)->set_pos(p1,p2); }
void EffectModule__set_rot_impl(BattleObjectModuleAccessor* a,u64 p1,u64 p2) { EF(a)->set_rot(p1,p2); }
void EffectModule__set_scale_impl(BattleObjectModuleAccessor* a,u64 p1,u64 p2) { EF(a)->set_scale(p1,p2); }

// -- existence/visibility --
bool EffectModule__is_exist_effect_impl(BattleObjectModuleAccessor* a,u64 p1) { return EF(a)->is_exist_effect(p1); }
void EffectModule__set_visible_impl(BattleObjectModuleAccessor* a,u64 p1,bool p2) { EF(a)->set_visible(p1,p2); }
void EffectModule__set_visible_kind_impl(BattleObjectModuleAccessor* a,u64 p1,bool p2) { EF(a)->set_visible_kind(p1,p2); }
void EffectModule__set_whole_impl(BattleObjectModuleAccessor* a,bool p1) { EF(a)->set_whole(p1); }
bool EffectModule__is_whole_impl(BattleObjectModuleAccessor* a) { return EF(a)->is_whole(); }
void EffectModule__set_whole_attr_impl(BattleObjectModuleAccessor* a,bool p1,u64 p2) { EF(a)->set_whole_attr(p1,p2); }

// -- screen effects --
void* EffectModule__fill_screen_impl(BattleObjectModuleAccessor* a,u64 p1,u64 p2,u64 p3,u64 p4,u64 p5,u64 p6) { return EF(a)->fill_screen(p1,p2,p3,p4,p5,p6); }
void* EffectModule__fill_screen_2_impl(BattleObjectModuleAccessor* a,u64 p1,u64 p2,u64 p3,u64 p4,u64 p5,u64 p6) { return EF(a)->fill_screen_2(p1,p2,p3,p4,p5,p6); }
void* EffectModule__color_collection_impl(BattleObjectModuleAccessor* a,u64 p1,u64 p2,u64 p3,u64 p4,u64 p5,u64 p6) { return EF(a)->color_collection(p1,p2,p3,p4,p5,p6); }
void EffectModule__clear_screen_impl(BattleObjectModuleAccessor* a,u64 p1,u64 p2) { EF(a)->clear_screen(p1,p2); }
void EffectModule__reset_screen_impl(BattleObjectModuleAccessor* a,u64 p1) { EF(a)->reset_screen(p1); }

// -- dead effect --
f32 EffectModule__get_dead_effect_rot_z_impl(BattleObjectModuleAccessor* a, u64 p1, bool p2) { return EF(a)->get_dead_effect_rot_z(p1,p2); }
f32 EffectModule__get_dead_effect_scale_impl(BattleObjectModuleAccessor* a, u64 p1, bool p2) { return EF(a)->get_dead_effect_scale(p1,p2); }
bool EffectModule__is_dead_effect_slant_impl(BattleObjectModuleAccessor* a, u64 p1) { return EF(a)->is_dead_effect_slant(p1); }

// -- common effects --
void EffectModule__req_common_impl(BattleObjectModuleAccessor* a,u64 p1) { EF(a)->req_common(p1); }
void EffectModule__remove_common_impl(BattleObjectModuleAccessor* a,u64 p1) { EF(a)->remove_common(p1); }
void EffectModule__reset_common_impl(BattleObjectModuleAccessor* a) { EF(a)->reset_common(); }
bool EffectModule__is_end_common_impl(BattleObjectModuleAccessor* a) { return EF(a)->is_end_common(); }
bool EffectModule__is_exist_common_impl(BattleObjectModuleAccessor* a,u64 p1) { return EF(a)->is_exist_common(p1); }

// -- screen request --
void EffectModule__req_screen_impl(BattleObjectModuleAccessor* a,u64 p1,bool p2,bool p3,bool p4) { EF(a)->req_screen(p1,p2,p3,p4); }
void EffectModule__req_screen_system_impl(BattleObjectModuleAccessor* a,u64 p1,bool p2,bool p3) { EF(a)->req_screen_system(p1,p2,p3); }
void EffectModule__remove_screen_impl(BattleObjectModuleAccessor* a,u64 p1,u64 p2) { EF(a)->remove_screen(p1,p2); }
void EffectModule__set_sync_visibility_impl(BattleObjectModuleAccessor* a,bool p1) { EF(a)->set_sync_visibility(p1); }
bool EffectModule__is_sync_visibility_impl(BattleObjectModuleAccessor* a) { return EF(a)->is_sync_visibility(); }
void EffectModule__set_sync_scale_impl(BattleObjectModuleAccessor* a,bool p1) { EF(a)->set_sync_scale(p1); }
bool EffectModule__is_sync_scale_impl(BattleObjectModuleAccessor* a) { return EF(a)->is_sync_scale(); }

// -- variation --
u32 EffectModule__get_variation_effect_kind_impl(BattleObjectModuleAccessor* a,u64 p1,u64 p2) { return EF(a)->get_variation_effect_kind(p1,p2); }

// -- color/alpha/frame --
void EffectModule__set_rgb_impl(BattleObjectModuleAccessor* a,u64 p1) { EF(a)->set_rgb(p1); }
void EffectModule__set_rgb_partial_last_impl(BattleObjectModuleAccessor* a) { EF(a)->set_rgb_partial_last(); }
void EffectModule__set_alpha_impl(BattleObjectModuleAccessor* a,u64 p1) { EF(a)->set_alpha(p1); }
void EffectModule__set_frame_impl(BattleObjectModuleAccessor* a,u64 p1) { EF(a)->set_frame(p1); }
void EffectModule__set_billboard_impl(BattleObjectModuleAccessor* a,u64 p1,bool p2) { EF(a)->set_billboard(p1,p2); }
void EffectModule__set_rate_impl(BattleObjectModuleAccessor* a,u64 p1) { EF(a)->set_rate(p1); }
void EffectModule__set_rate_last_impl(BattleObjectModuleAccessor* a) { EF(a)->set_rate_last(); }
void EffectModule__set_scale_last_impl(BattleObjectModuleAccessor* a,u64 p1) { EF(a)->set_scale_last(p1); }
void EffectModule__set_alpha_last_impl(BattleObjectModuleAccessor* a) { EF(a)->set_alpha_last(); }
void EffectModule__set_disable_system_slow_impl(BattleObjectModuleAccessor* a,bool p1) { EF(a)->set_disable_system_slow(p1); }

// -- slow/velocity --
void EffectModule__set_slow_rate_mul_impl(BattleObjectModuleAccessor* a) { EF(a)->set_slow_rate_mul(); }
void EffectModule__set_slow_rate_no_stop_mul_impl(BattleObjectModuleAccessor* a) { EF(a)->set_slow_rate_no_stop_mul(); }
void EffectModule__set_add_vel_impl(BattleObjectModuleAccessor* a,u64 p1,u64 p2) { EF(a)->set_add_vel(p1,p2); }
void EffectModule__set_material_anim_last_impl(BattleObjectModuleAccessor* a,u64 p1) { EF(a)->set_material_anim_last(p1); }
void EffectModule__set_disable_render_offset_last_impl(BattleObjectModuleAccessor* a) { EF(a)->set_disable_render_offset_last(); }

// -- handle/ground --
u64 EffectModule__get_last_handle_impl(BattleObjectModuleAccessor* a) { return EF(a)->get_last_handle(); }
bool EffectModule__is_enable_ground_effect_impl(BattleObjectModuleAccessor* a) { return EF(a)->is_enable_ground_effect(); }

// -- status/sync --
void EffectModule__kill_status_effect_impl(BattleObjectModuleAccessor* a) { EF(a)->kill_status_effect(); }
void* EffectModule__unsync_vis_whole_impl(BattleObjectModuleAccessor* a,u64 p1) { return EF(a)->unsync_vis_whole(p1); }
void EffectModule__sync_visibility_impl(BattleObjectModuleAccessor* a,bool p1) { EF(a)->sync_visibility(p1); }
void EffectModule__set_offset_to_next_impl(BattleObjectModuleAccessor* a,u64 p1) { EF(a)->set_offset_to_next(p1); }
void* EffectModule__make_offset_hash_impl(BattleObjectModuleAccessor* a,u64 p1,u64 p2) { return EF(a)->make_offset_hash(p1,p2); }
void* EffectModule__preset_lifetime_rate_partial_impl(BattleObjectModuleAccessor* a) { return EF(a)->preset_lifetime_rate_partial(); }
void* EffectModule__preset_curtail_emitter_impl(BattleObjectModuleAccessor* a) { return EF(a)->preset_curtail_emitter(); }
void EffectModule__preset_limit_num_impl(BattleObjectModuleAccessor* a,u64 p1) { EF(a)->preset_limit_num(p1); }
void EffectModule__enable_sync_init_pos_last_impl(BattleObjectModuleAccessor* a) { EF(a)->enable_sync_init_pos_last(); }

// -- custom/post effect --
void EffectModule__set_custom_uv_offset_impl(BattleObjectModuleAccessor* a,u64 p1,u64 p2,u64 p3) { EF(a)->set_custom_uv_offset(p1,p2,p3); }
void EffectModule__remove_post_effect_line_impl(BattleObjectModuleAccessor* a,u64 p1,bool p2) { EF(a)->remove_post_effect_line(p1,p2); }
void* EffectModule__request_post_effect_line_circle_impl(BattleObjectModuleAccessor* a,u64 p1,u64 p2,bool p3) { return EF(a)->request_post_effect_line_circle(p1,p2,p3); }
void EffectModule__set_post_effect_line_circle_target_impl(BattleObjectModuleAccessor* a,u64 p1,bool p2) { EF(a)->set_post_effect_line_circle_target(p1,p2); }
void* EffectModule__request_post_effect_line_parallel_2d_impl(BattleObjectModuleAccessor* a,u64 p1,bool p2) { return EF(a)->request_post_effect_line_parallel_2d(p1,p2); }

// -- stencil/common --
void EffectModule__enable_stencil_impl(BattleObjectModuleAccessor* a, bool p1) { EF(a)->enable_stencil(p1); }
void EffectModule__force_update_common_effect_impl(BattleObjectModuleAccessor* a) { EF(a)->force_update_common_effect(); }

// 71020176c0 -- req_2d: calls req vtable slot [13] with hard-coded trailing args
// Cannot use struct method — different arg types than req()
void EffectModule__req_2d_impl(BattleObjectModuleAccessor* a,u64 p1,u64 p2,u64 p3,u64 p4,u64 p6) {
    auto* m = EF(a);
    reinterpret_cast<void(*)(EffectModule*,u64,u64,u64,u64,u32,u32,u32)>(m->_vt[13])(m,p1,p2,p3,p4,static_cast<u32>(-1),1u,0u);
}

// 71020179d0 -- get_local_matrix: prologue/epilogue, vtable+0x148
#ifdef MATCHING_HACK_NX_CLANG
__attribute__((naked))
void* EffectModule__get_local_matrix_impl(BattleObjectModuleAccessor* /*a*/, u64 /*p1*/) {
    asm(
        "stp x29, x30, [sp, #-0x10]!\n"
        "mov x29, sp\n"
        "ldr x0, [x0, #0x140]\n"
        "ldr x8, [x0]\n"
        "ldr x8, [x8, #0x148]\n"
        "blr x8\n"
        "ldp x29, x30, [sp], #0x10\n"
        "ret\n"
    );
}
#endif

} // namespace app::lua_bind
