#pragma once
#include "types.h"

namespace app {

// MotionModule virtual dispatch wrapper
// Vtable entries recovered from lua_bind dispatcher analysis
// All method names derived from .dynsym lua_bind::MotionModule__*_impl functions.
// Module accessed via BattleObjectModuleAccessor +0x88
struct MotionModule {
    void** _vt;

    // Vtable dispatchers — index = byte_offset / 8
    // Dual-named entries share the same vtable slot

    // -- change_motion family [28-33] --
    void change_motion(u64 h, f32 r, bool p1, bool p2, bool p3) { ((void(*)(MotionModule*,u64,f32,bool,bool,bool))_vt[28])(this,h,r,p1,p2,p3); }
    void change_motion_inherit_frame(u64 h, bool p1, bool p2) { ((void(*)(MotionModule*,u64,bool,bool))_vt[29])(this,h,p1,p2); }
    void change_motion_inherit_frame_keep_rate(u64 h) { ((void(*)(MotionModule*,u64))_vt[30])(this,h); }
    void change_motion_force_inherit_frame(u64 h) { ((void(*)(MotionModule*,u64))_vt[31])(this,h); }
    void change_motion_kind(u64 h) { ((void(*)(MotionModule*,u64))_vt[32])(this,h); }
    void add_motion_2nd(u64 h, bool p1) { ((void(*)(MotionModule*,u64,bool))_vt[33])(this,h,p1); }

    // -- [34] change_motion_2nd / set_weight --
    void change_motion_2nd(bool p1) { ((void(*)(MotionModule*,bool))_vt[34])(this,p1); }
    void set_weight(bool p1) { ((void(*)(MotionModule*,bool))_vt[34])(this,p1); }

    // -- getters [35-36] --
    f32 get_weight() { return ((f32(*)(MotionModule*))_vt[35])(this); }
    f32 get_weight_2nd() { return ((f32(*)(MotionModule*))_vt[36])(this); }
    void set_weight_rate() { ((void(*)(MotionModule*))_vt[36])(this); }

    // -- state [37-43] --
    bool is_blend() { return ((bool(*)(MotionModule*))_vt[37])(this); }
    bool is_changing() { return ((bool(*)(MotionModule*))_vt[38])(this); }
    u64 motion_kind() { return ((u64(*)(MotionModule*))_vt[39])(this); }
    f32 rate() { return ((f32(*)(MotionModule*))_vt[40])(this); }
    bool is_changing_2nd() { return ((bool(*)(MotionModule*))_vt[41])(this); }
    void set_rate() { ((void(*)(MotionModule*))_vt[41])(this); }
    f32 rate_2nd() { return ((f32(*)(MotionModule*))_vt[42])(this); }
    u64 motion_kind_prev() { return ((u64(*)(MotionModule*))_vt[43])(this); }
    void set_rate_2nd() { ((void(*)(MotionModule*))_vt[43])(this); }

    // -- frame [44-51] --
    f32 frame() { return ((f32(*)(MotionModule*))_vt[44])(this); }
    f32 prev_frame() { return ((f32(*)(MotionModule*))_vt[45])(this); }
    void set_frame(bool p1) { ((void(*)(MotionModule*,bool))_vt[46])(this,p1); }
    void set_frame_sync_anim_cmd(f32 f, bool p1, bool p2, bool p3) { ((void(*)(MotionModule*,f32,bool,bool,bool))_vt[47])(this,f,p1,p2,p3); }
    f32 end_frame() { return ((f32(*)(MotionModule*))_vt[48])(this); }
    void* end_frame_from_hash(u64 p1) { return ((void*(*)(MotionModule*,u64))_vt[49])(this,p1); }
    void set_frame_2nd(bool p1) { ((void(*)(MotionModule*,bool))_vt[50])(this,p1); }
    f32 frame_2nd() { return ((f32(*)(MotionModule*))_vt[51])(this); }

    // -- transform [52-56] --
    void* trans_tra(u64 p1, bool p2, bool p3) { return ((void*(*)(MotionModule*,u64,bool,bool))_vt[52])(this,p1,p2,p3); }
    void* trans_tra_2nd(u64 p1, bool p2, bool p3) { return ((void*(*)(MotionModule*,u64,bool,bool))_vt[53])(this,p1,p2,p3); }
    void* joint_local_tra(u64 p1, bool p2, u64 p3) { return ((void*(*)(MotionModule*,u64,bool,u64))_vt[55])(this,p1,p2,p3); }
    f32 prev_frame_2nd(u64 p1, u64 p2) { return ((f32(*)(MotionModule*,u64,u64))_vt[56])(this,p1,p2); }
    void* trans_tra_end_frame(u64 p1, u64 p2) { return ((void*(*)(MotionModule*,u64,u64))_vt[56])(this,p1,p2); }

    // -- end/loop [57-63] --
    bool is_end() { return ((bool(*)(MotionModule*))_vt[57])(this); }
    bool is_looped() { return ((bool(*)(MotionModule*))_vt[58])(this); }
    bool is_loop_flag() { return ((bool(*)(MotionModule*))_vt[63])(this); }

    // -- interpreting/trans_move [67-72] --
    bool is_interpreting() { return ((bool(*)(MotionModule*))_vt[67])(this); }
    void update_trans_move_speed() { ((void(*)(MotionModule*))_vt[67])(this); }
    bool is_interpreting_2nd() { return ((bool(*)(MotionModule*))_vt[69])(this); }
    void* trans_move_speed() { return ((void*(*)(MotionModule*))_vt[69])(this); }
    bool is_interpreting_partial() { return ((bool(*)(MotionModule*))_vt[71])(this); }
    void* trans_move_speed_2nd() { return ((void*(*)(MotionModule*))_vt[71])(this); }
    void set_trans_move_speed_no_scale(bool p1) { ((void(*)(MotionModule*,bool))_vt[72])(this,p1); }

    // -- anim resource [78-81] --
    bool is_anim_resource(u64 p1) { return ((bool(*)(MotionModule*,u64))_vt[78])(this,p1); }
    void* resource_id(u64 p1) { return ((void*(*)(MotionModule*,u64))_vt[80])(this,p1); }
    void* animcmd_name_hash(u64 p1) { return ((void*(*)(MotionModule*,u64))_vt[81])(this,p1); }

    // -- hash/weight [83-88] --
    u64 trans_hash() { return ((u64(*)(MotionModule*))_vt[83])(this); }
    void* weight() { return ((void*(*)(MotionModule*))_vt[83])(this); }
    f32 prev_weight() { return ((f32(*)(MotionModule*))_vt[84])(this); }
    u64 body_hash() { return ((u64(*)(MotionModule*))_vt[86])(this); }
    void set_weight_change_motion() { ((void(*)(MotionModule*))_vt[86])(this); }
    void* calc_joint(u64 p1, u64 p2, u64 p3) { return ((void*(*)(MotionModule*,u64,u64,u64))_vt[87])(this,p1,p2,p3); }
    void* joint_local_scale() { return ((void*(*)(MotionModule*))_vt[88])(this); }
    void update_dynamic_skeleton_without_complete_matrix() { ((void(*)(MotionModule*))_vt[88])(this); }

    // -- joint [90-91] --
    void* joint_local_rotation(u64 p1, u64 p2) { return ((void*(*)(MotionModule*,u64,u64))_vt[90])(this,p1,p2); }
    void* joint_local_tra_2nd(u64 p1) { return ((void*(*)(MotionModule*,u64))_vt[91])(this,p1); }
    void set_trans_joint_id(u64 p1) { ((void(*)(MotionModule*,u64))_vt[91])(this,p1); }

    // -- 2nd motion [92-98] --
    f32 end_frame_2nd() { return ((f32(*)(MotionModule*))_vt[92])(this); }
    bool is_end_2nd() { return ((bool(*)(MotionModule*))_vt[93])(this); }
    u64 motion_kind_2nd() { return ((u64(*)(MotionModule*))_vt[94])(this); }
    bool is_flag_link(u64 p1) { return ((bool(*)(MotionModule*,u64))_vt[95])(this,p1); }
    bool is_flag_start_1_frame_from_motion_kind(u64 p1) { return ((bool(*)(MotionModule*,u64))_vt[96])(this,p1); }
    bool is_flag_start_1_frame() { return ((bool(*)(MotionModule*))_vt[97])(this); }
    bool is_flag_start_1_frame_2nd() { return ((bool(*)(MotionModule*))_vt[98])(this); }

    // -- joint rotate [99] --
    void* joint_rotate(u64 p1, u64 p2) { return ((void*(*)(MotionModule*,u64,u64))_vt[99])(this,p1,p2); }

    // -- partial motion [100-113] --
    void add_motion_partial(u64 p1, u64 p2, f32 p3, bool p4, bool p5, bool p6, bool p7, bool p8) { ((void(*)(MotionModule*,u64,u64,f32,bool,bool,bool,bool,bool))_vt[100])(this,p1,p2,p3,p4,p5,p6,p7,p8); }
    void remove_motion_partial(u64 p1, bool p2) { ((void(*)(MotionModule*,u64,bool))_vt[101])(this,p1,p2); }
    void* remove_motion_partial_comp(u64 p1) { return ((void*(*)(MotionModule*,u64))_vt[103])(this,p1); }
    void* motion_kind_partial(u64 p1) { return ((void*(*)(MotionModule*,u64))_vt[104])(this,p1); }
    bool is_end_partial(u64 p1) { return ((bool(*)(MotionModule*,u64))_vt[105])(this,p1); }
    void* end_frame_partial(u64 p1) { return ((void*(*)(MotionModule*,u64))_vt[106])(this,p1); }
    f32 rate_2nd_partial(u64 p1) { return ((f32(*)(MotionModule*,u64))_vt[107])(this,p1); }
    void set_rate_partial(u64 p1) { ((void(*)(MotionModule*,u64))_vt[107])(this,p1); }
    void* rate_partial(u64 p1) { return ((void*(*)(MotionModule*,u64))_vt[108])(this,p1); }
    void* frame_partial(u64 p1) { return ((void*(*)(MotionModule*,u64))_vt[109])(this,p1); }
    void* prev_frame_partial(u64 p1) { return ((void*(*)(MotionModule*,u64))_vt[110])(this,p1); }
    void set_frame_partial(u64 p1, bool p2) { ((void(*)(MotionModule*,u64,bool))_vt[111])(this,p1,p2); }
    void set_frame_partial_sync_anim_cmd(u64 p1, bool p2) { ((void(*)(MotionModule*,u64,bool))_vt[112])(this,p1,p2); }
    bool is_flag_start_1_frame_partial(u64 p1) { return ((bool(*)(MotionModule*,u64))_vt[113])(this,p1); }

    // -- flip [114-117] --
    bool is_flip() { return ((bool(*)(MotionModule*))_vt[114])(this); }
    void set_flip(bool p1, bool p2, bool p3) { ((void(*)(MotionModule*,bool,bool,bool))_vt[116])(this,p1,p2,p3); }
    void set_link_flip_target_joint(bool p1) { ((void(*)(MotionModule*,bool))_vt[117])(this,p1); }

    // -- material [118-123] --
    void set_frame_material(u64 p1) { ((void(*)(MotionModule*,u64))_vt[118])(this,p1); }
    void set_frame_material_2nd(u64 p1) { ((void(*)(MotionModule*,u64))_vt[119])(this,p1); }
    void set_rate_material(u64 p1) { ((void(*)(MotionModule*,u64))_vt[119])(this,p1); }
    void set_loop_flag_material(u64 p1, u64 p2) { ((void(*)(MotionModule*,u64,u64))_vt[120])(this,p1,p2); }
    void* get_frame_material(u64 p1) { return ((void*(*)(MotionModule*,u64))_vt[121])(this,p1); }
    void set_helper_calculation(bool p1) { ((void(*)(MotionModule*,bool))_vt[122])(this,p1); }
    void set_helper_calculation_2nd(bool p1) { ((void(*)(MotionModule*,bool))_vt[123])(this,p1); }
    void set_skip_rate(bool p1) { ((void(*)(MotionModule*,bool))_vt[123])(this,p1); }

    // -- frame/rate misc [126-137] --
    void set_frame_looped_flag() { ((void(*)(MotionModule*))_vt[126])(this); }
    void* whole_rate() { return ((void*(*)(MotionModule*))_vt[126])(this); }
    bool is_flag_disable_change_motion() { return ((bool(*)(MotionModule*))_vt[127])(this); }
    void set_whole_rate() { ((void(*)(MotionModule*))_vt[127])(this); }
    void set_flag_disable_change_motion() { ((void(*)(MotionModule*))_vt[130])(this); }
    void update_rate() { ((void(*)(MotionModule*))_vt[130])(this); }
    void set_recalc_ik(bool p1) { ((void(*)(MotionModule*,bool))_vt[132])(this,p1); }
    void set_no_comp(bool p1) { ((void(*)(MotionModule*,bool))_vt[135])(this,p1); }
    void set_no_comp_2nd(bool p1) { ((void(*)(MotionModule*,bool))_vt[135])(this,p1); }
    bool is_no_comp() { return ((bool(*)(MotionModule*))_vt[136])(this); }
    void set_kind_offset(u64 p1) { ((void(*)(MotionModule*,u64))_vt[137])(this,p1); }

    // -- shift/anim [141-148] --
    void enable_shift_material_animation(bool p1) { ((void(*)(MotionModule*,bool))_vt[141])(this,p1); }
    void set_kind_offset_2nd() { ((void(*)(MotionModule*))_vt[142])(this); }
    void* trans_joint_scale() { return ((void*(*)(MotionModule*))_vt[142])(this); }
    void enable_shift_material_animation_2nd(bool p1) { ((void(*)(MotionModule*,bool))_vt[143])(this,p1); }
    void set_stop_interpolation(bool p1) { ((void(*)(MotionModule*,bool))_vt[143])(this,p1); }
    bool is_flip_resource() { return ((bool(*)(MotionModule*))_vt[148])(this); }

    // -- progress [152-160] --
    void set_force_progress_2nd_weight_2nd(bool p1) { ((void(*)(MotionModule*,bool))_vt[152])(this,p1); }
    void set_reverse(bool p1) { ((void(*)(MotionModule*,bool))_vt[152])(this,p1); }
    void set_force_progress_2nd_weight(bool p1) { ((void(*)(MotionModule*,bool))_vt[159])(this,p1); }
    void clear_joint_srt(u64 p1) { ((void(*)(MotionModule*,u64))_vt[160])(this,p1); }

    // -- keep pose [165-192] --
    void set_keep_pose_change_motion_2nd(bool p1, u64 p2) { ((void(*)(MotionModule*,bool,u64))_vt[165])(this,p1,p2); }
    void* start_flip_interpolation(bool p1, u64 p2) { return ((void*(*)(MotionModule*,bool,u64))_vt[165])(this,p1,p2); }
    void set_keep_pose_change_motion(bool p1) { ((void(*)(MotionModule*,bool))_vt[177])(this,p1); }
    void set_keep_anim_frame_change_motion() { ((void(*)(MotionModule*))_vt[178])(this); }
    void set_next_no_comp() { ((void(*)(MotionModule*))_vt[178])(this); }
    void set_keep_anim_frame_change_motion_2nd(u64 p1) { ((void(*)(MotionModule*,u64))_vt[179])(this,p1); }
    void set_remove_change_motion_partial(u64 p1) { ((void(*)(MotionModule*,u64))_vt[179])(this,p1); }
    void set_keep_anim_frame_change_motion_partial(bool p1) { ((void(*)(MotionModule*,bool))_vt[180])(this,p1); }
    void set_remove_partial_after_intp(bool p1) { ((void(*)(MotionModule*,bool))_vt[180])(this,p1); }
    void enable_remove_2nd_change_motion(bool p1) { ((void(*)(MotionModule*,bool))_vt[183])(this,p1); }
    void enable_set_frame_2nd_partial(u64 p1, bool p2) { ((void(*)(MotionModule*,u64,bool))_vt[184])(this,p1,p2); }
    void set_frame_partial_sync_anim_cmd_revised(u64 p1, bool p2) { ((void(*)(MotionModule*,u64,bool))_vt[185])(this,p1,p2); }
    void set_link_no_2nd(bool p1) { ((void(*)(MotionModule*,bool))_vt[186])(this,p1); }
    void set_part_animcmd_fix(bool p1) { ((void(*)(MotionModule*,bool))_vt[186])(this,p1); }
    void set_keep_pose_change_motion_with_update_pose(bool p1) { ((void(*)(MotionModule*,bool))_vt[188])(this,p1); }
    void set_animcmd_done(bool p1) { ((void(*)(MotionModule*,bool))_vt[191])(this,p1); }
    void set_link_no(u64 p1) { ((void(*)(MotionModule*,u64))_vt[192])(this,p1); }
};

} // namespace app
