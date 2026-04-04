#include "app/BattleObjectModuleAccessor.h"
#include "app/modules/MotionModule.h"
#define MO(a) static_cast<MotionModule*>((a)->motion_module)
namespace app::lua_bind {
// change_motion variants
void MotionModule__change_motion_impl(BattleObjectModuleAccessor* a,u64 h,f32 r,bool p1,bool p2,bool p3) { MO(a)->change_motion(h,r,p1,p2,p3); }
void MotionModule__change_motion_inherit_frame_impl(BattleObjectModuleAccessor* a,u64 h,bool p1,bool p2) { MO(a)->change_motion_inherit_frame(h,p1,p2); }
void MotionModule__change_motion_inherit_frame_keep_rate_impl(BattleObjectModuleAccessor* a,u64 h) { MO(a)->change_motion_inherit_frame_keep_rate(h); }
void MotionModule__change_motion_force_inherit_frame_impl(BattleObjectModuleAccessor* a,u64 h) { MO(a)->change_motion_force_inherit_frame(h); }
void MotionModule__change_motion_kind_impl(BattleObjectModuleAccessor* a,u64 h) { MO(a)->change_motion_kind(h); }
void MotionModule__add_motion_2nd_impl(BattleObjectModuleAccessor* a,u64 h,bool p1) { MO(a)->add_motion_2nd(h,p1); }
// getters
f32 MotionModule__get_weight_impl(BattleObjectModuleAccessor* a) { return MO(a)->get_weight(); }
bool MotionModule__is_blend_impl(BattleObjectModuleAccessor* a) { return MO(a)->is_blend(); }
bool MotionModule__is_changing_impl(BattleObjectModuleAccessor* a) { return MO(a)->is_changing(); }
u64 MotionModule__motion_kind_impl(BattleObjectModuleAccessor* a) { return MO(a)->motion_kind(); }
f32 MotionModule__rate_impl(BattleObjectModuleAccessor* a) { return MO(a)->rate(); }
f32 MotionModule__rate_2nd_impl(BattleObjectModuleAccessor* a) { return MO(a)->rate_2nd(); }
f32 MotionModule__frame_impl(BattleObjectModuleAccessor* a) { return MO(a)->frame(); }
f32 MotionModule__prev_frame_impl(BattleObjectModuleAccessor* a) { return MO(a)->prev_frame(); }
void MotionModule__set_frame_impl(BattleObjectModuleAccessor* a,bool p1) { MO(a)->set_frame(p1); }
void MotionModule__set_frame_sync_anim_cmd_impl(BattleObjectModuleAccessor* a,f32 f,bool p1,bool p2,bool p3) { MO(a)->set_frame_sync_anim_cmd(f,p1,p2,p3); }
f32 MotionModule__end_frame_impl(BattleObjectModuleAccessor* a) { return MO(a)->end_frame(); }
void* MotionModule__end_frame_from_hash_impl(BattleObjectModuleAccessor* a,u64 p1) { return MO(a)->end_frame_from_hash(p1); }
void MotionModule__set_frame_2nd_impl(BattleObjectModuleAccessor* a,bool p1) { MO(a)->set_frame_2nd(p1); }
f32 MotionModule__frame_2nd_impl(BattleObjectModuleAccessor* a) { return MO(a)->frame_2nd(); }
void* MotionModule__joint_local_tra_impl(BattleObjectModuleAccessor* a,u64 p1,bool p2,u64 p3) { return MO(a)->joint_local_tra(p1,p2,p3); }
bool MotionModule__is_end_impl(BattleObjectModuleAccessor* a) { return MO(a)->is_end(); }
bool MotionModule__is_looped_impl(BattleObjectModuleAccessor* a) { return MO(a)->is_looped(); }
bool MotionModule__is_loop_flag_impl(BattleObjectModuleAccessor* a) { return MO(a)->is_loop_flag(); }
void* MotionModule__resource_id_impl(BattleObjectModuleAccessor* a,u64 p1) { return MO(a)->resource_id(p1); }
void* MotionModule__animcmd_name_hash_impl(BattleObjectModuleAccessor* a,u64 p1) { return MO(a)->animcmd_name_hash(p1); }
f32 MotionModule__prev_weight_impl(BattleObjectModuleAccessor* a) { return MO(a)->prev_weight(); }
void* MotionModule__calc_joint_impl(BattleObjectModuleAccessor* a,u64 p1,u64 p2,u64 p3) { return MO(a)->calc_joint(p1,p2,p3); }
void* MotionModule__joint_local_rotation_impl(BattleObjectModuleAccessor* a,u64 p1,u64 p2) { return MO(a)->joint_local_rotation(p1,p2); }
f32 MotionModule__end_frame_2nd_impl(BattleObjectModuleAccessor* a) { return MO(a)->end_frame_2nd(); }
u64 MotionModule__motion_kind_2nd_impl(BattleObjectModuleAccessor* a) { return MO(a)->motion_kind_2nd(); }
bool MotionModule__is_flag_link_impl(BattleObjectModuleAccessor* a,u64 p1) { return MO(a)->is_flag_link(p1); }
bool MotionModule__is_flag_start_1_frame_from_motion_kind_impl(BattleObjectModuleAccessor* a,u64 p1) { return MO(a)->is_flag_start_1_frame_from_motion_kind(p1); }
bool MotionModule__is_flag_start_1_frame_impl(BattleObjectModuleAccessor* a) { return MO(a)->is_flag_start_1_frame(); }
bool MotionModule__is_flag_start_1_frame_2nd_impl(BattleObjectModuleAccessor* a) { return MO(a)->is_flag_start_1_frame_2nd(); }
void* MotionModule__joint_rotate_impl(BattleObjectModuleAccessor* a,u64 p1,u64 p2) { return MO(a)->joint_rotate(p1,p2); }
void MotionModule__add_motion_partial_impl(BattleObjectModuleAccessor* a,u64 p1,u64 p2,f32 p3,bool p4,bool p5,bool p6,bool p7,bool p8) { MO(a)->add_motion_partial(p1,p2,p3,p4,p5,p6,p7,p8); }
void MotionModule__remove_motion_partial_impl(BattleObjectModuleAccessor* a,u64 p1,bool p2) { MO(a)->remove_motion_partial(p1,p2); }
void* MotionModule__remove_motion_partial_comp_impl(BattleObjectModuleAccessor* a,u64 p1) { return MO(a)->remove_motion_partial_comp(p1); }
void* MotionModule__motion_kind_partial_impl(BattleObjectModuleAccessor* a,u64 p1) { return MO(a)->motion_kind_partial(p1); }
bool MotionModule__is_end_partial_impl(BattleObjectModuleAccessor* a,u64 p1) { return MO(a)->is_end_partial(p1); }
void* MotionModule__end_frame_partial_impl(BattleObjectModuleAccessor* a,u64 p1) { return MO(a)->end_frame_partial(p1); }
void* MotionModule__rate_partial_impl(BattleObjectModuleAccessor* a,u64 p1) { return MO(a)->rate_partial(p1); }
void* MotionModule__frame_partial_impl(BattleObjectModuleAccessor* a,u64 p1) { return MO(a)->frame_partial(p1); }
void* MotionModule__prev_frame_partial_impl(BattleObjectModuleAccessor* a,u64 p1) { return MO(a)->prev_frame_partial(p1); }
void MotionModule__set_frame_partial_impl(BattleObjectModuleAccessor* a,u64 p1,bool p2) { MO(a)->set_frame_partial(p1,p2); }
void MotionModule__set_frame_partial_sync_anim_cmd_impl(BattleObjectModuleAccessor* a,u64 p1,bool p2) { MO(a)->set_frame_partial_sync_anim_cmd(p1,p2); }
bool MotionModule__is_flag_start_1_frame_partial_impl(BattleObjectModuleAccessor* a,u64 p1) { return MO(a)->is_flag_start_1_frame_partial(p1); }
bool MotionModule__is_flip_impl(BattleObjectModuleAccessor* a) { return MO(a)->is_flip(); }
void MotionModule__set_flip_impl(BattleObjectModuleAccessor* a,bool p1,bool p2,bool p3) { MO(a)->set_flip(p1,p2,p3); }
void MotionModule__set_link_flip_target_joint_impl(BattleObjectModuleAccessor* a,bool p1) { MO(a)->set_link_flip_target_joint(p1); }
void MotionModule__set_frame_material_impl(BattleObjectModuleAccessor* a,u64 p1) { MO(a)->set_frame_material(p1); }
void MotionModule__set_loop_flag_material_impl(BattleObjectModuleAccessor* a,u64 p1,u64 p2) { MO(a)->set_loop_flag_material(p1,p2); }
void MotionModule__set_helper_calculation_impl(BattleObjectModuleAccessor* a,bool p1) { MO(a)->set_helper_calculation(p1); }
void MotionModule__set_recalc_ik_impl(BattleObjectModuleAccessor* a,bool p1) { MO(a)->set_recalc_ik(p1); }
bool MotionModule__is_no_comp_impl(BattleObjectModuleAccessor* a) { return MO(a)->is_no_comp(); }
void MotionModule__set_kind_offset_impl(BattleObjectModuleAccessor* a,u64 p1) { MO(a)->set_kind_offset(p1); }
void MotionModule__enable_shift_material_animation_impl(BattleObjectModuleAccessor* a,bool p1) { MO(a)->enable_shift_material_animation(p1); }
bool MotionModule__is_flip_resource_impl(BattleObjectModuleAccessor* a) { return MO(a)->is_flip_resource(); }
void MotionModule__set_force_progress_2nd_weight_impl(BattleObjectModuleAccessor* a,bool p1) { MO(a)->set_force_progress_2nd_weight(p1); }
void MotionModule__clear_joint_srt_impl(BattleObjectModuleAccessor* a,u64 p1) { MO(a)->clear_joint_srt(p1); }
void MotionModule__set_keep_pose_change_motion_impl(BattleObjectModuleAccessor* a,bool p1) { MO(a)->set_keep_pose_change_motion(p1); }
void MotionModule__enable_remove_2nd_change_motion_impl(BattleObjectModuleAccessor* a,bool p1) { MO(a)->enable_remove_2nd_change_motion(p1); }
void MotionModule__enable_set_frame_2nd_partial_impl(BattleObjectModuleAccessor* a,u64 p1,bool p2) { MO(a)->enable_set_frame_2nd_partial(p1,p2); }
void MotionModule__set_frame_partial_sync_anim_cmd_revised_impl(BattleObjectModuleAccessor* a,u64 p1,bool p2) { MO(a)->set_frame_partial_sync_anim_cmd_revised(p1,p2); }
void MotionModule__set_keep_pose_change_motion_with_update_pose_impl(BattleObjectModuleAccessor* a,bool p1) { MO(a)->set_keep_pose_change_motion_with_update_pose(p1); }
void MotionModule__set_animcmd_done_impl(BattleObjectModuleAccessor* a,bool p1) { MO(a)->set_animcmd_done(p1); }
void MotionModule__set_link_no_impl(BattleObjectModuleAccessor* a,u64 p1) { MO(a)->set_link_no(p1); }
// Missing from earlier: is_anim_resource
bool MotionModule__is_anim_resource_impl(BattleObjectModuleAccessor* a,u64 p1) { return MO(a)->is_anim_resource(p1); }
bool MotionModule__is_end_2nd_impl(BattleObjectModuleAccessor* a) { return MO(a)->is_end_2nd(); }
void* MotionModule__get_frame_material_impl(BattleObjectModuleAccessor* a,u64 p1) { return MO(a)->get_frame_material(p1); }
// Remaining MotionModule dispatchers
void MotionModule__change_motion_2nd_impl(BattleObjectModuleAccessor* a,bool p1) { MO(a)->change_motion_2nd(p1); }
f32 MotionModule__get_weight_2nd_impl(BattleObjectModuleAccessor* a) { return MO(a)->get_weight_2nd(); }
bool MotionModule__is_changing_2nd_impl(BattleObjectModuleAccessor* a) { return MO(a)->is_changing_2nd(); }
u64 MotionModule__motion_kind_prev_impl(BattleObjectModuleAccessor* a) { return MO(a)->motion_kind_prev(); }
void MotionModule__set_rate_2nd_impl(BattleObjectModuleAccessor* a) { MO(a)->set_rate_2nd(); }
void MotionModule__set_rate_partial_impl(BattleObjectModuleAccessor* a,u64 p1) { MO(a)->set_rate_partial(p1); }
f32 MotionModule__prev_frame_2nd_impl(BattleObjectModuleAccessor* a,u64 p1,u64 p2) { return MO(a)->prev_frame_2nd(p1,p2); }
bool MotionModule__is_interpreting_impl(BattleObjectModuleAccessor* a) { return MO(a)->is_interpreting(); }
bool MotionModule__is_interpreting_2nd_impl(BattleObjectModuleAccessor* a) { return MO(a)->is_interpreting_2nd(); }
bool MotionModule__is_interpreting_partial_impl(BattleObjectModuleAccessor* a) { return MO(a)->is_interpreting_partial(); }
void MotionModule__set_rate_impl(BattleObjectModuleAccessor* a) { MO(a)->set_rate(); }
u64 MotionModule__trans_hash_impl(BattleObjectModuleAccessor* a) { return MO(a)->trans_hash(); }
u64 MotionModule__body_hash_impl(BattleObjectModuleAccessor* a) { return MO(a)->body_hash(); }
void* MotionModule__joint_local_scale_impl(BattleObjectModuleAccessor* a) { return MO(a)->joint_local_scale(); }
void* MotionModule__joint_local_tra_2nd_impl(BattleObjectModuleAccessor* a,u64 p1) { return MO(a)->joint_local_tra_2nd(p1); }
f32 MotionModule__rate_2nd_partial_impl(BattleObjectModuleAccessor* a,u64 p1) { return MO(a)->rate_2nd_partial(p1); }
void MotionModule__set_frame_material_2nd_impl(BattleObjectModuleAccessor* a,u64 p1) { MO(a)->set_frame_material_2nd(p1); }
void MotionModule__set_helper_calculation_2nd_impl(BattleObjectModuleAccessor* a,bool p1) { MO(a)->set_helper_calculation_2nd(p1); }
void MotionModule__set_frame_looped_flag_impl(BattleObjectModuleAccessor* a) { MO(a)->set_frame_looped_flag(); }
bool MotionModule__is_flag_disable_change_motion_impl(BattleObjectModuleAccessor* a) { return MO(a)->is_flag_disable_change_motion(); }
void MotionModule__set_flag_disable_change_motion_impl(BattleObjectModuleAccessor* a) { MO(a)->set_flag_disable_change_motion(); }
void MotionModule__set_no_comp_2nd_impl(BattleObjectModuleAccessor* a,bool p1) { MO(a)->set_no_comp_2nd(p1); }
void MotionModule__set_kind_offset_2nd_impl(BattleObjectModuleAccessor* a) { MO(a)->set_kind_offset_2nd(); }
void MotionModule__enable_shift_material_animation_2nd_impl(BattleObjectModuleAccessor* a,bool p1) { MO(a)->enable_shift_material_animation_2nd(p1); }
void MotionModule__set_force_progress_2nd_weight_2nd_impl(BattleObjectModuleAccessor* a,bool p1) { MO(a)->set_force_progress_2nd_weight_2nd(p1); }
void MotionModule__set_keep_pose_change_motion_2nd_impl(BattleObjectModuleAccessor* a,bool p1,u64 p2) { MO(a)->set_keep_pose_change_motion_2nd(p1,p2); }
void MotionModule__set_keep_anim_frame_change_motion_impl(BattleObjectModuleAccessor* a) { MO(a)->set_keep_anim_frame_change_motion(); }
void MotionModule__set_keep_anim_frame_change_motion_2nd_impl(BattleObjectModuleAccessor* a,u64 p1) { MO(a)->set_keep_anim_frame_change_motion_2nd(p1); }
void MotionModule__set_keep_anim_frame_change_motion_partial_impl(BattleObjectModuleAccessor* a,bool p1) { MO(a)->set_keep_anim_frame_change_motion_partial(p1); }
void MotionModule__set_link_no_2nd_impl(BattleObjectModuleAccessor* a,bool p1) { MO(a)->set_link_no_2nd(p1); }
// Auto-generated named dispatchers (alternate names for same vtable slots)
void MotionModule__set_weight_impl(BattleObjectModuleAccessor* a,bool p1) { MO(a)->set_weight(p1); }
void MotionModule__set_weight_rate_impl(BattleObjectModuleAccessor* a) { MO(a)->set_weight_rate(); }
void* MotionModule__trans_tra_end_frame_impl(BattleObjectModuleAccessor* a,u64 p1,u64 p2) { return MO(a)->trans_tra_end_frame(p1,p2); }
void MotionModule__update_trans_move_speed_impl(BattleObjectModuleAccessor* a) { MO(a)->update_trans_move_speed(); }
void* MotionModule__trans_move_speed_impl(BattleObjectModuleAccessor* a) { return MO(a)->trans_move_speed(); }
void* MotionModule__trans_move_speed_2nd_impl(BattleObjectModuleAccessor* a) { return MO(a)->trans_move_speed_2nd(); }
void MotionModule__set_trans_move_speed_no_scale_impl(BattleObjectModuleAccessor* a,bool p1) { MO(a)->set_trans_move_speed_no_scale(p1); }
void* MotionModule__weight_impl(BattleObjectModuleAccessor* a) { return MO(a)->weight(); }
void MotionModule__set_weight_change_motion_impl(BattleObjectModuleAccessor* a) { MO(a)->set_weight_change_motion(); }
void MotionModule__update_dynamic_skeleton_without_complete_matrix_impl(BattleObjectModuleAccessor* a) { MO(a)->update_dynamic_skeleton_without_complete_matrix(); }
void MotionModule__set_trans_joint_id_impl(BattleObjectModuleAccessor* a,u64 p1) { MO(a)->set_trans_joint_id(p1); }
void MotionModule__set_rate_material_impl(BattleObjectModuleAccessor* a,u64 p1) { MO(a)->set_rate_material(p1); }
void MotionModule__set_skip_rate_impl(BattleObjectModuleAccessor* a,bool p1) { MO(a)->set_skip_rate(p1); }
void* MotionModule__whole_rate_impl(BattleObjectModuleAccessor* a) { return MO(a)->whole_rate(); }
void MotionModule__set_whole_rate_impl(BattleObjectModuleAccessor* a) { MO(a)->set_whole_rate(); }
void MotionModule__update_rate_impl(BattleObjectModuleAccessor* a) { MO(a)->update_rate(); }
void MotionModule__set_no_comp_impl(BattleObjectModuleAccessor* a,bool p1) { MO(a)->set_no_comp(p1); }
void* MotionModule__trans_joint_scale_impl(BattleObjectModuleAccessor* a) { return MO(a)->trans_joint_scale(); }
void MotionModule__set_stop_interpolation_impl(BattleObjectModuleAccessor* a,bool p1) { MO(a)->set_stop_interpolation(p1); }
void MotionModule__set_reverse_impl(BattleObjectModuleAccessor* a,bool p1) { MO(a)->set_reverse(p1); }
void* MotionModule__start_flip_interpolation_impl(BattleObjectModuleAccessor* a,bool p1,u64 p2) { return MO(a)->start_flip_interpolation(p1,p2); }
void MotionModule__set_next_no_comp_impl(BattleObjectModuleAccessor* a) { MO(a)->set_next_no_comp(); }
void MotionModule__set_remove_change_motion_partial_impl(BattleObjectModuleAccessor* a,u64 p1) { MO(a)->set_remove_change_motion_partial(p1); }
void MotionModule__set_remove_partial_after_intp_impl(BattleObjectModuleAccessor* a,bool p1) { MO(a)->set_remove_partial_after_intp(p1); }
void MotionModule__set_part_animcmd_fix_impl(BattleObjectModuleAccessor* a,bool p1) { MO(a)->set_part_animcmd_fix(p1); }
// Multi-bool dispatchers
void* MotionModule__trans_tra_impl(BattleObjectModuleAccessor* a,u64 p1,bool p2,bool p3) { return MO(a)->trans_tra(p1,p2,p3); }
void* MotionModule__trans_tra_2nd_impl(BattleObjectModuleAccessor* a,u64 p1,bool p2,bool p3) { return MO(a)->trans_tra_2nd(p1,p2,p3); }
} // namespace app::lua_bind
