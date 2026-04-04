#include "app/BattleObjectModuleAccessor.h"
#include "app/modules/JostleModule.h"
#define JM(a) static_cast<JostleModule*>((a)->jostle_module)

namespace app::lua_bind {

void JostleModule__set_status_impl(BattleObjectModuleAccessor* a, bool p1) { JM(a)->set_status(p1); }
void JostleModule__set_layer_impl(BattleObjectModuleAccessor* a, u64 p1) { JM(a)->set_layer(p1); }
void JostleModule__set_fix_impl(BattleObjectModuleAccessor* a, bool p1) { JM(a)->set_fix(p1); }
void JostleModule__set_ignore_speed_x_impl(BattleObjectModuleAccessor* a, bool p1) { JM(a)->set_ignore_speed_x(p1); }
void JostleModule__sleep_impl(BattleObjectModuleAccessor* a, bool p1) { JM(a)->sleep(p1); }
bool JostleModule__is_sleep_impl(BattleObjectModuleAccessor* a) { return JM(a)->is_sleep(); }
f32 JostleModule__jostle_speed_x_impl(BattleObjectModuleAccessor* a) { return JM(a)->jostle_speed_x(); }
f32 JostleModule__speed_attenuation_rate_impl(BattleObjectModuleAccessor* a) { return JM(a)->speed_attenuation_rate(); }
void* JostleModule__target_weight_impl(BattleObjectModuleAccessor* a) { return JM(a)->target_weight(); }
f32 JostleModule__pos_z_impl(BattleObjectModuleAccessor* a) { return JM(a)->pos_z(); }
void JostleModule__set_refer_impl(BattleObjectModuleAccessor* a, bool p1) { JM(a)->set_refer(p1); }
void JostleModule__set_push_speed_x_impl(BattleObjectModuleAccessor* a, bool p1) { JM(a)->set_push_speed_x(p1); }
void JostleModule__set_push_speed_x_2_impl(BattleObjectModuleAccessor* a, u64 p1, bool p2) { JM(a)->set_push_speed_x_2(p1, p2); }
void JostleModule__set_priority_impl(BattleObjectModuleAccessor* a, u64 p1) { JM(a)->set_priority(p1); }
u32 JostleModule__priority_impl(BattleObjectModuleAccessor* a) { return JM(a)->priority(); }
void JostleModule__set_force_gap_impl(BattleObjectModuleAccessor* a, u64 p1) { JM(a)->set_force_gap(p1); }
void JostleModule__set_ignore_owner_id_impl(BattleObjectModuleAccessor* a, u64 p1) { JM(a)->set_ignore_owner_id(p1); }
void* JostleModule__ignore_owner_id_impl(BattleObjectModuleAccessor* a) { return JM(a)->ignore_owner_id(); }
void JostleModule__reset_area_impl(BattleObjectModuleAccessor* a) { JM(a)->reset_area(); }
void JostleModule__overlap_x_impl(BattleObjectModuleAccessor* a, bool p1) { JM(a)->overlap_x(p1); }
void JostleModule__set_ignore_pri_impl(BattleObjectModuleAccessor* a, u64 p1) { JM(a)->set_ignore_pri(p1); }
void JostleModule__set_push_speed_x_overlap_rate_impl(BattleObjectModuleAccessor* a) { JM(a)->set_push_speed_x_overlap_rate(); }
void JostleModule__set_push_speed_x_overlap_rate_status_impl(BattleObjectModuleAccessor* a) { JM(a)->set_push_speed_x_overlap_rate_status(); }
u32 JostleModule__area_kind_impl(BattleObjectModuleAccessor* a) { return JM(a)->area_kind(); }
f32 JostleModule__weight_impl(BattleObjectModuleAccessor* a) { return JM(a)->weight(); }
void JostleModule__set_weight_impl(BattleObjectModuleAccessor* a) { JM(a)->set_weight(); }
void JostleModule__set_influence_opponent_weight_impl(BattleObjectModuleAccessor* a, bool p1) { JM(a)->set_influence_opponent_weight(p1); }
void JostleModule__set_propagate_push_speed_impl(BattleObjectModuleAccessor* a, bool p1) { JM(a)->set_propagate_push_speed(p1); }
void JostleModule__set_overlap_rate_mul_impl(BattleObjectModuleAccessor* a) { JM(a)->set_overlap_rate_mul(); }
void JostleModule__set_team_impl(BattleObjectModuleAccessor* a, u64 p1) { JM(a)->set_team(p1); }

} // namespace app::lua_bind
