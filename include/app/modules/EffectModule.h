#pragma once
#include "types.h"

namespace app {

// EffectModule virtual dispatch wrapper
// Vtable entries recovered from lua_bind dispatcher analysis
// All method names derived from .dynsym lua_bind::EffectModule__*_impl dispatcher analysis.
// Module accessed via BattleObjectModuleAccessor +0x140
struct EffectModule {
    void** _vt;

    // Vtable dispatchers — index = byte_offset / 8
    // Names: [confirmed: lua_bind API name]

    // -- request [13-17] --
    void req(u64 p1, u64 p2, u64 p3, u64 p4, u64 p5, bool p6, u64 p7) { ((void(*)(EffectModule*,u64,u64,u64,u64,u64,bool,u64))_vt[13])(this,p1,p2,p3,p4,p5,p6,p7); }
    void req_on_joint(u64 p1, u64 p2, u64 p3, u64 p4, u64 p5, u64 p6, bool p7, u32 p8, u32 p9, u32 p10) { ((void(*)(EffectModule*,u64,u64,u64,u64,u64,u64,bool,u32,u32,u32))_vt[14])(this,p1,p2,p3,p4,p5,p6,p7,p8,p9,p10); }
    void req_attach_ground(u64 p1, u64 p2, u64 p3, u64 p4, u64 p5, u64 p6, u64 p7) { ((void(*)(EffectModule*,u64,u64,u64,u64,u64,u64,u64))_vt[15])(this,p1,p2,p3,p4,p5,p6,p7); }
    void req_follow(u64 p1, u64 p2, u64 p3, u64 p4, bool p5, u32 p6, s32 p7, s32 p8, s32 p9, s32 p10, bool p11, bool p12) { ((void(*)(EffectModule*,u64,u64,u64,u64,bool,u32,s32,s32,s32,s32,bool,bool))_vt[16])(this,p1,p2,p3,p4,p5,p6,p7,p8,p9,p10,p11,p12); }
    void req_continual(u64 p1, u64 p2, u64 p3, u64 p4) { ((void(*)(EffectModule*,u64,u64,u64,u64))_vt[17])(this,p1,p2,p3,p4); }

    // -- continual management [18-19] --
    void remove_continual(u64 p1) { ((void(*)(EffectModule*,u64))_vt[18])(this,p1); }
    void remove_all_continual() { ((void(*)(EffectModule*))_vt[19])(this); }

    // -- timed effects [20-23] --
    void req_time(u64 p1, u64 p2, u64 p3, u64 p4, u64 p5, bool p6, bool p7) { ((void(*)(EffectModule*,u64,u64,u64,u64,u64,bool,bool))_vt[20])(this,p1,p2,p3,p4,p5,p6,p7); }
    void req_time_follow(u64 p1, u64 p2, u64 p3, u64 p4, u64 p5, bool p6, u64 p7) { ((void(*)(EffectModule*,u64,u64,u64,u64,u64,bool,u64))_vt[21])(this,p1,p2,p3,p4,p5,p6,p7); }
    void remove_time(u64 p1) { ((void(*)(EffectModule*,u64))_vt[22])(this,p1); }
    void remove_all_time() { ((void(*)(EffectModule*))_vt[23])(this); }

    // -- emit/remove/kill [24-30] --
    void req_emit(u64 p1, u64 p2) { ((void(*)(EffectModule*,u64,u64))_vt[24])(this,p1,p2); }
    void remove(u64 p1, u64 p2) { ((void(*)(EffectModule*,u64,u64))_vt[25])(this,p1,p2); }
    void remove_all(u64 p1, u64 p2) { ((void(*)(EffectModule*,u64,u64))_vt[26])(this,p1,p2); }
    void kill(u64 p1, bool p2, bool p3) { ((void(*)(EffectModule*,u64,bool,bool))_vt[27])(this,p1,p2,p3); }
    void kill_kind(u64 p1, bool p2, bool p3) { ((void(*)(EffectModule*,u64,bool,bool))_vt[28])(this,p1,p2,p3); }
    void kill_joint_id(u64 p1, bool p2, bool p3) { ((void(*)(EffectModule*,u64,bool,bool))_vt[29])(this,p1,p2,p3); }
    void kill_all(u64 p1, bool p2, bool p3) { ((void(*)(EffectModule*,u64,bool,bool))_vt[30])(this,p1,p2,p3); }

    // -- detach/end [31-34] --
    void detach_all(u64 p1) { ((void(*)(EffectModule*,u64))_vt[31])(this,p1); }
    void detach_kind(u64 p1, u64 p2) { ((void(*)(EffectModule*,u64,u64))_vt[32])(this,p1,p2); }
    void detach(u64 p1, u64 p2) { ((void(*)(EffectModule*,u64,u64))_vt[33])(this,p1,p2); }
    void end_kind(u64 p1, u64 p2) { ((void(*)(EffectModule*,u64,u64))_vt[34])(this,p1,p2); }

    // -- after image [35-40] --
    void req_after_image(u64 p1, u64 p2, u64 p3, u64 p4, u32 p5, u64 p6, u64 p7, u32 p8, u64 p9, u64 p10, u64 p11, u64 p12, bool p13, bool p14, s32 p15, s32 p16, s32 p17) { ((void(*)(EffectModule*,u64,u64,u64,u64,u32,u64,u64,u32,u64,u64,u64,u64,bool,bool,s32,s32,s32))_vt[35])(this,p1,p2,p3,p4,p5,p6,p7,p8,p9,p10,p11,p12,p13,p14,p15,p16,p17); }
    // [36] unknown
    void req_after_image_no_parent(u64 p1, u64 p2, u32 p3, u64 p4, u64 p5, u32 p6, u64 p7, u64 p8, u64 p9, u64 p10, bool p11, bool p12, s32 p13, s32 p14, s32 p15) { ((void(*)(EffectModule*,u64,u64,u32,u64,u64,u32,u64,u64,u64,u64,bool,bool,s32,s32,s32))_vt[37])(this,p1,p2,p3,p4,p5,p6,p7,p8,p9,p10,p11,p12,p13,p14,p15); }
    void clear_all_after_image(u64 p1) { ((void(*)(EffectModule*,u64))_vt[38])(this,p1); }
    void remove_after_image(u64 p1, u64 p2) { ((void(*)(EffectModule*,u64,u64))_vt[39])(this,p1,p2); }
    void remove_all_after_image(u64 p1, u64 p2) { ((void(*)(EffectModule*,u64,u64))_vt[40])(this,p1,p2); }

    // -- matrix/transform [41-44] --
    void* get_local_matrix(u64 p1) { return ((void*(*)(EffectModule*,u64))_vt[41])(this,p1); }
    void set_pos(u64 p1, u64 p2) { ((void(*)(EffectModule*,u64,u64))_vt[42])(this,p1,p2); }
    void set_rot(u64 p1, u64 p2) { ((void(*)(EffectModule*,u64,u64))_vt[43])(this,p1,p2); }
    void set_scale(u64 p1, u64 p2) { ((void(*)(EffectModule*,u64,u64))_vt[44])(this,p1,p2); }

    // -- existence/visibility [49-55] --
    bool is_exist_effect(u64 p1) { return ((bool(*)(EffectModule*,u64))_vt[49])(this,p1); }
    void set_visible(u64 p1, bool p2) { ((void(*)(EffectModule*,u64,bool))_vt[50])(this,p1,p2); }
    void set_visible_kind(u64 p1, bool p2) { ((void(*)(EffectModule*,u64,bool))_vt[51])(this,p1,p2); }
    // [52] unknown
    void set_whole(bool p1) { ((void(*)(EffectModule*,bool))_vt[53])(this,p1); }
    bool is_whole() { return ((bool(*)(EffectModule*))_vt[54])(this); }
    void set_whole_attr(bool p1, u64 p2) { ((void(*)(EffectModule*,bool,u64))_vt[55])(this,p1,p2); }

    // -- screen effects [58-63] --
    void* fill_screen(u64 p1, u64 p2, u64 p3, u64 p4, u64 p5, u64 p6) { return ((void*(*)(EffectModule*,u64,u64,u64,u64,u64,u64))_vt[58])(this,p1,p2,p3,p4,p5,p6); }
    void* fill_screen_2(u64 p1, u64 p2, u64 p3, u64 p4, u64 p5, u64 p6) { return ((void*(*)(EffectModule*,u64,u64,u64,u64,u64,u64))_vt[59])(this,p1,p2,p3,p4,p5,p6); }
    void* color_collection(u64 p1, u64 p2, u64 p3, u64 p4, u64 p5, u64 p6) { return ((void*(*)(EffectModule*,u64,u64,u64,u64,u64,u64))_vt[60])(this,p1,p2,p3,p4,p5,p6); }
    void clear_screen(u64 p1, u64 p2) { ((void(*)(EffectModule*,u64,u64))_vt[61])(this,p1,p2); }
    // [62] unknown
    void reset_screen(u64 p1) { ((void(*)(EffectModule*,u64))_vt[63])(this,p1); }

    // -- dead effect [66-68] --
    f32 get_dead_effect_rot_z(u64 p1, bool p2) { return ((f32(*)(EffectModule*,u64,bool))_vt[66])(this,p1,p2); }
    f32 get_dead_effect_scale(u64 p1, bool p2) { return ((f32(*)(EffectModule*,u64,bool))_vt[67])(this,p1,p2); }
    bool is_dead_effect_slant(u64 p1) { return ((bool(*)(EffectModule*,u64))_vt[68])(this,p1); }

    // -- common effects [69-74] --
    void req_common(u64 p1) { ((void(*)(EffectModule*,u64))_vt[69])(this,p1); }
    // [70] unknown
    void remove_common(u64 p1) { ((void(*)(EffectModule*,u64))_vt[71])(this,p1); }
    void reset_common() { ((void(*)(EffectModule*))_vt[72])(this); }
    bool is_end_common() { return ((bool(*)(EffectModule*))_vt[73])(this); }
    bool is_exist_common(u64 p1) { return ((bool(*)(EffectModule*,u64))_vt[74])(this,p1); }

    // -- screen request [76-84] --
    void req_screen(u64 p1, bool p2, bool p3, bool p4) { ((void(*)(EffectModule*,u64,bool,bool,bool))_vt[76])(this,p1,p2,p3,p4); }
    // [77] unknown
    void req_screen_system(u64 p1, bool p2, bool p3) { ((void(*)(EffectModule*,u64,bool,bool))_vt[78])(this,p1,p2,p3); }
    // [79] unknown
    void remove_screen(u64 p1, u64 p2) { ((void(*)(EffectModule*,u64,u64))_vt[80])(this,p1,p2); }
    void set_sync_visibility(bool p1) { ((void(*)(EffectModule*,bool))_vt[81])(this,p1); }
    bool is_sync_visibility() { return ((bool(*)(EffectModule*))_vt[82])(this); }
    void set_sync_scale(bool p1) { ((void(*)(EffectModule*,bool))_vt[83])(this,p1); }
    bool is_sync_scale() { return ((bool(*)(EffectModule*))_vt[84])(this); }

    // -- variation [88] --
    u32 get_variation_effect_kind(u64 p1, u64 p2) { return ((u32(*)(EffectModule*,u64,u64))_vt[88])(this,p1,p2); }

    // -- color/alpha/frame [95-106] --
    void set_rgb(u64 p1) { ((void(*)(EffectModule*,u64))_vt[95])(this,p1); }
    void set_rgb_partial_last() { ((void(*)(EffectModule*))_vt[96])(this); }
    void set_alpha(u64 p1) { ((void(*)(EffectModule*,u64))_vt[97])(this,p1); }
    void set_frame(u64 p1) { ((void(*)(EffectModule*,u64))_vt[98])(this,p1); }
    // [99-100] unknown
    void set_billboard(u64 p1, bool p2) { ((void(*)(EffectModule*,u64,bool))_vt[101])(this,p1,p2); }
    void set_rate(u64 p1) { ((void(*)(EffectModule*,u64))_vt[102])(this,p1); }
    void set_rate_last() { ((void(*)(EffectModule*))_vt[103])(this); }
    void set_scale_last(u64 p1) { ((void(*)(EffectModule*,u64))_vt[104])(this,p1); }
    void set_alpha_last() { ((void(*)(EffectModule*))_vt[105])(this); }
    void set_disable_system_slow(bool p1) { ((void(*)(EffectModule*,bool))_vt[106])(this,p1); }

    // -- slow/velocity [111-115] --
    void set_slow_rate_mul() { ((void(*)(EffectModule*))_vt[111])(this); }
    void set_slow_rate_no_stop_mul() { ((void(*)(EffectModule*))_vt[112])(this); }
    void set_add_vel(u64 p1, u64 p2) { ((void(*)(EffectModule*,u64,u64))_vt[113])(this,p1,p2); }
    void set_material_anim_last(u64 p1) { ((void(*)(EffectModule*,u64))_vt[114])(this,p1); }
    void set_disable_render_offset_last() { ((void(*)(EffectModule*))_vt[115])(this); }

    // -- handle/ground [116, 125] --
    u64 get_last_handle() { return ((u64(*)(EffectModule*))_vt[116])(this); }
    bool is_enable_ground_effect() { return ((bool(*)(EffectModule*))_vt[125])(this); }

    // -- status/sync [127-136] --
    void kill_status_effect() { ((void(*)(EffectModule*))_vt[127])(this); }
    void* unsync_vis_whole(u64 p1) { return ((void*(*)(EffectModule*,u64))_vt[128])(this,p1); }
    void sync_visibility(bool p1) { ((void(*)(EffectModule*,bool))_vt[129])(this,p1); }
    // [130] unknown
    void set_offset_to_next(u64 p1) { ((void(*)(EffectModule*,u64))_vt[131])(this,p1); }
    void* make_offset_hash(u64 p1, u64 p2) { return ((void*(*)(EffectModule*,u64,u64))_vt[132])(this,p1,p2); }
    void* preset_lifetime_rate_partial() { return ((void*(*)(EffectModule*))_vt[133])(this); }
    void* preset_curtail_emitter() { return ((void*(*)(EffectModule*))_vt[134])(this); }
    void preset_limit_num(u64 p1) { ((void(*)(EffectModule*,u64))_vt[135])(this,p1); }
    void enable_sync_init_pos_last() { ((void(*)(EffectModule*))_vt[136])(this); }

    // -- custom/post effect [137-146] --
    void set_custom_uv_offset(u64 p1, u64 p2, u64 p3) { ((void(*)(EffectModule*,u64,u64,u64))_vt[137])(this,p1,p2,p3); }
    void remove_post_effect_line(u64 p1, bool p2) { ((void(*)(EffectModule*,u64,bool))_vt[138])(this,p1,p2); }
    // [139] unknown
    void* request_post_effect_line_circle(u64 p1, u64 p2, bool p3) { return ((void*(*)(EffectModule*,u64,u64,bool))_vt[140])(this,p1,p2,p3); }
    void set_post_effect_line_circle_target(u64 p1, bool p2) { ((void(*)(EffectModule*,u64,bool))_vt[141])(this,p1,p2); }
    void* request_post_effect_line_parallel_2d(u64 p1, bool p2) { return ((void*(*)(EffectModule*,u64,bool))_vt[142])(this,p1,p2); }
    // [143-144] unknown
    void enable_stencil(bool p1) { ((void(*)(EffectModule*,bool))_vt[145])(this,p1); }
    void force_update_common_effect() { ((void(*)(EffectModule*))_vt[146])(this); }
};

} // namespace app
