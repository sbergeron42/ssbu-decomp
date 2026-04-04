#include "app/BattleObjectModuleAccessor.h"
#include "app/modules/ArticleModule.h"
#define AR(a) static_cast<ArticleModule*>((a)->article_module)

namespace app::lua_bind {

void* ArticleModule__generate_article_impl(BattleObjectModuleAccessor* a, u64 p1, bool p2, u64 p3) { return AR(a)->generate_article(p1, p2, p3); }
void* ArticleModule__generate_article_enable_impl(BattleObjectModuleAccessor* a, u64 p1, bool p2, u64 p3) { return AR(a)->generate_article_enable(p1, p2, p3); }
void* ArticleModule__generate_article_have_item_impl(BattleObjectModuleAccessor* a, u64 p1, u64 p2, u64 p3) { return AR(a)->generate_article_have_item(p1, p2, p3); }
void* ArticleModule__have_impl(BattleObjectModuleAccessor* a, u64 p1, u64 p2, u64 p3, u64 p4, bool p5) { return AR(a)->have(p1, p2, p3, p4, p5); }
void ArticleModule__shoot_impl(BattleObjectModuleAccessor* a, u64 p1, u64 p2, bool p3) { AR(a)->shoot(p1, p2, p3); }
void ArticleModule__shoot_exist_impl(BattleObjectModuleAccessor* a, u64 p1, u64 p2, bool p3) { AR(a)->shoot_exist(p1, p2, p3); }
void ArticleModule__set_pos_impl(BattleObjectModuleAccessor* a, u64 p1) { AR(a)->set_pos(p1); }
void* ArticleModule__motion_kind_impl(BattleObjectModuleAccessor* a, u64 p1, u64 p2) { return AR(a)->motion_kind(p1, p2); }
void ArticleModule__change_motion_impl(BattleObjectModuleAccessor* a, u64 p1, u64 p2, bool p3) { AR(a)->change_motion(p1, p2, p3); }
void ArticleModule__change_motion_from_no_impl(BattleObjectModuleAccessor* a, u64 p1, u64 p2, u64 p3, bool p4) { AR(a)->change_motion_from_no(p1, p2, p3, p4); }
void ArticleModule__add_motion_2nd_impl(BattleObjectModuleAccessor* a, u64 p1, u64 p2, bool p3) { AR(a)->add_motion_2nd(p1, p2, p3); }
void* ArticleModule__motion_kind_2nd_impl(BattleObjectModuleAccessor* a, u64 p1, u64 p2) { return AR(a)->motion_kind_2nd(p1, p2); }
void ArticleModule__set_weight_impl(BattleObjectModuleAccessor* a, u64 p1, bool p2) { AR(a)->set_weight(p1, p2); }
void ArticleModule__add_motion_partial_impl(BattleObjectModuleAccessor* a, u64 p1, u64 p2, u64 p3, bool p4, bool p5, bool p6, bool p7, bool p8) {
    AR(a)->add_motion_partial(p1, p2, p3, p4 & 1, p5 & 1, p6 & 1, p7 & 1, p8 & 1);
}
void ArticleModule__set_frame_impl(BattleObjectModuleAccessor* a, u64 p1) { AR(a)->set_frame(p1); }
void ArticleModule__set_frame_2nd_impl(BattleObjectModuleAccessor* a, u64 p1, bool p2) { AR(a)->set_frame_2nd(p1, p2); }
void ArticleModule__set_rate_impl(BattleObjectModuleAccessor* a, u64 p1) { AR(a)->set_rate(p1); }
void* ArticleModule__change_status_impl(BattleObjectModuleAccessor* a, u64 p1, u64 p2, u64 p3) { return AR(a)->change_status(p1, p2, p3); }
void* ArticleModule__change_status_exist_impl(BattleObjectModuleAccessor* a, u64 p1, u64 p2) { return AR(a)->change_status_exist(p1, p2); }
void ArticleModule__set_visibility_whole_impl(BattleObjectModuleAccessor* a, u64 p1, bool p2, u64 p3) { AR(a)->set_visibility_whole(p1, p2, p3); }
void ArticleModule__set_visibility_impl(BattleObjectModuleAccessor* a, u64 p1, u64 p2, u64 p3, u64 p4) { AR(a)->set_visibility(p1, p2, p3, p4); }
void ArticleModule__set_visibility_whole_2_impl(BattleObjectModuleAccessor* a, u64 p1, u64 p2, u64 p3, u64 p4) { AR(a)->set_visibility(p1, p2, p3, p4); }
void ArticleModule__set_default_visibility_impl(BattleObjectModuleAccessor* a, u64 p1, u64 p2, u64 p3) { AR(a)->set_default_visibility(p1, p2, p3); }
void ArticleModule__set_situation_kind_impl(BattleObjectModuleAccessor* a, u64 p1, u64 p2) { AR(a)->set_situation_kind(p1, p2); }
void ArticleModule__set_flag_impl(BattleObjectModuleAccessor* a, u64 p1, bool p2, u64 p3) { AR(a)->set_flag(p1, p2, p3); }
bool ArticleModule__is_flag_impl(BattleObjectModuleAccessor* a, u64 p1, u64 p2) { return AR(a)->is_flag(p1, p2); }
bool ArticleModule__is_flag_from_no_impl(BattleObjectModuleAccessor* a, u64 p1, u64 p2, u64 p3) { return AR(a)->is_flag_from_no(p1, p2, p3); }
void ArticleModule__set_int_impl(BattleObjectModuleAccessor* a, u64 p1, u64 p2, u64 p3) { AR(a)->set_int(p1, p2, p3); }
void ArticleModule__set_int_from_no_impl(BattleObjectModuleAccessor* a, u64 p1, u64 p2, u64 p3) { AR(a)->set_int(p1, p2, p3); }
void* ArticleModule__get_int_impl(BattleObjectModuleAccessor* a, u64 p1, u64 p2) { return AR(a)->get_int(p1, p2); }
void ArticleModule__set_float_impl(BattleObjectModuleAccessor* a, u64 p1, u64 p2) { AR(a)->set_float(p1, p2); }
void* ArticleModule__get_float_impl(BattleObjectModuleAccessor* a, u64 p1, u64 p2) { return AR(a)->get_float(p1, p2); }
void ArticleModule__set_float_from_no_impl(BattleObjectModuleAccessor* a, u64 p1, u64 p2, u64 p3) { AR(a)->set_float_from_no(p1, p2, p3); }
void ArticleModule__get_float_from_no_impl(BattleObjectModuleAccessor* a, u64 p1, u64 p2) { AR(a)->get_float_from_no(p1, p2); }
void* ArticleModule__remove_impl(BattleObjectModuleAccessor* a, u64 p1, u64 p2) { return AR(a)->remove(p1, p2); }
void* ArticleModule__remove_exist_impl(BattleObjectModuleAccessor* a, u64 p1, u64 p2) { return AR(a)->remove_exist(p1, p2); }
void ArticleModule__remove_exist_object_id_impl(BattleObjectModuleAccessor* a, u64 p1) { AR(a)->remove_exist_object_id(p1); }
bool ArticleModule__is_exist_impl(BattleObjectModuleAccessor* a, u64 p1) { return AR(a)->is_exist(p1); }
u32 ArticleModule__get_num_impl(BattleObjectModuleAccessor* a, u64 p1) { return AR(a)->get_num(p1); }
bool ArticleModule__is_generatable_impl(BattleObjectModuleAccessor* a, u64 p1) { return AR(a)->is_generatable(p1); }
u32 ArticleModule__get_active_num_impl(BattleObjectModuleAccessor* a, u64 p1) { return AR(a)->get_active_num(p1); }
void* ArticleModule__get_article_impl(BattleObjectModuleAccessor* a, u64 p1) { return AR(a)->get_article(p1); }
u32 ArticleModule__get_article_from_no_impl(BattleObjectModuleAccessor* a, u64 p1, u64 p2) { return AR(a)->get_article_from_no(p1, p2); }
void* ArticleModule__get_joint_pos_impl(BattleObjectModuleAccessor* a, u64 p1, u64 p2, u64 p3) { return AR(a)->get_joint_pos(p1, p2, p3); }
void* ArticleModule__get_joint_rotate_impl(BattleObjectModuleAccessor* a, u64 p1, u64 p2, u64 p3) { return AR(a)->get_joint_rotate(p1, p2, p3); }
void* ArticleModule__get_joint_scale_impl(BattleObjectModuleAccessor* a) { return AR(a)->get_joint_scale(); }

} // namespace app::lua_bind
