#include "app/BattleObjectModuleAccessor.h"
#include "app/modules/ModelModule.h"
#define MM(a) static_cast<ModelModule*>((a)->model_module)

namespace app::lua_bind {

void ModelModule__set_rotation_order_impl(BattleObjectModuleAccessor* a, u64 p1) { MM(a)->set_rotation_order(p1); }
u32 ModelModule__rotation_order_impl(BattleObjectModuleAccessor* a) { return MM(a)->rotation_order(); }
void* ModelModule__scale_impl(BattleObjectModuleAccessor* a) { return MM(a)->scale(); }
void ModelModule__set_scale_impl(BattleObjectModuleAccessor* a) { MM(a)->set_scale(); }
f32 ModelModule__scale_z_impl(BattleObjectModuleAccessor* a) { return MM(a)->scale_z(); }
void ModelModule__set_scale_z_impl(BattleObjectModuleAccessor* a) { MM(a)->set_scale_z(); }
void ModelModule__set_temporary_scale_z_impl(BattleObjectModuleAccessor* a) { MM(a)->set_temporary_scale_z(); }
void* ModelModule__joint_global_position_impl(BattleObjectModuleAccessor* a, u64 p1, u64 p2, bool p3) { return MM(a)->joint_global_position(p1, p2, p3); }
void* ModelModule__joint_global_position_with_offset_impl(BattleObjectModuleAccessor* a, u64 p1, u64 p2, u64 p3, bool p4) { return MM(a)->joint_global_position_with_offset(p1, p2, p3, p4); }
void* ModelModule__joint_global_offset_from_top_impl(BattleObjectModuleAccessor* a, u64 p1, u64 p2) { return MM(a)->joint_global_offset_from_top(p1, p2); }
void* ModelModule__top_joint_global_position_from_joint_impl(BattleObjectModuleAccessor* a, u64 p1, u64 p2, u64 p3) { return MM(a)->top_joint_global_position_from_joint(p1, p2, p3); }
void* ModelModule__joint_global_rotation_impl(BattleObjectModuleAccessor* a, u64 p1, u64 p2, bool p3) { return MM(a)->joint_global_rotation(p1, p2, p3); }
void* ModelModule__joint_global_axis_impl(BattleObjectModuleAccessor* a, u64 p1, u64 p2, bool p3) { return MM(a)->joint_global_axis(p1, p2, p3); }
void ModelModule__set_joint_srt_impl(BattleObjectModuleAccessor* a, u64 p1, u64 p2, u64 p3, u64 p4) { MM(a)->set_joint_srt(p1, p2, p3, p4); }
void ModelModule__set_joint_scale_impl(BattleObjectModuleAccessor* a, u64 p1, u64 p2) { MM(a)->set_joint_scale(p1, p2); }
void ModelModule__set_joint_rotate_impl(BattleObjectModuleAccessor* a, u64 p1, u64 p2, u64 p3, u64 p4) { MM(a)->set_joint_rotate(p1, p2, p3, p4); }
void ModelModule__set_joint_translate_impl(BattleObjectModuleAccessor* a, u64 p1, u64 p2, bool p3, bool p4) { MM(a)->set_joint_translate(p1, p2, p3, p4); }
void ModelModule__clear_joint_srt_impl(BattleObjectModuleAccessor* a, u64 p1) { MM(a)->clear_joint_srt(p1); }
void* ModelModule__joint_rotate_impl(BattleObjectModuleAccessor* a, u64 p1, u64 p2) { return MM(a)->joint_rotate(p1, p2); }
void ModelModule__set_visibility_impl(BattleObjectModuleAccessor* a, bool p1) { MM(a)->set_visibility(p1); }
bool ModelModule__is_visible_impl(BattleObjectModuleAccessor* a) { return MM(a)->is_visible(); }
void ModelModule__set_mesh_visibility_impl(BattleObjectModuleAccessor* a, u64 p1, bool p2) { MM(a)->set_mesh_visibility(p1, p2); }
void ModelModule__set_alpha_impl(BattleObjectModuleAccessor* a) { MM(a)->set_alpha(); }
void ModelModule__set_color_rgb_impl(BattleObjectModuleAccessor* a, u64 p1) { MM(a)->set_color_rgb(p1); }
void ModelModule__set_emmisive_scale_impl(BattleObjectModuleAccessor* a) { MM(a)->set_emmisive_scale(); }
void ModelModule__set_render_offset_position_impl(BattleObjectModuleAccessor* a, u64 p1) { MM(a)->set_render_offset_position(p1); }
void ModelModule__set_depth_offset_impl(BattleObjectModuleAccessor* a) { MM(a)->set_depth_offset(); }
void ModelModule__set_depth_stencil_impl(BattleObjectModuleAccessor* a, u64 p1) { MM(a)->set_depth_stencil(p1); }
void* ModelModule__virtual_joint_tra_impl(BattleObjectModuleAccessor* a, u64 p1) { return MM(a)->virtual_joint_tra(p1); }
void ModelModule__enable_gold_eye_impl(BattleObjectModuleAccessor* a) { MM(a)->enable_gold_eye(); }
void ModelModule__disable_gold_eye_impl(BattleObjectModuleAccessor* a) { MM(a)->disable_gold_eye(); }

} // namespace app::lua_bind
