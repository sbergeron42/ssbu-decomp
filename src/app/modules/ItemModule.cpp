#include "app/BattleObjectModuleAccessor.h"
#include "app/modules/ItemModule.h"
#define IM(a) static_cast<ItemModule*>((a)->item_module)

namespace app::lua_bind {

// -- have/use/pickup --
void ItemModule__have_item_impl(BattleObjectModuleAccessor* a, u64 p1, u64 p2, u64 p3, bool p4, bool p5) { IM(a)->have_item(p1, p2, p3, p4, p5); }
void ItemModule__have_item_instance_impl(BattleObjectModuleAccessor* a, u64 p1, u64 p2, bool p3, bool p4, bool p5, bool p6) { IM(a)->have_item_instance(p1, p2, p3, p4, p5, p6); }
void* ItemModule__use_item_instance_impl(BattleObjectModuleAccessor* a, u64 p1, bool p2) { return IM(a)->use_item_instance(p1, p2); }
void* ItemModule__use_item_impl(BattleObjectModuleAccessor* a, u64 p1, bool p2) { return IM(a)->use_item(p1, p2); }
void* ItemModule__pickup_item_impl(BattleObjectModuleAccessor* a, u64 p1, u64 p2, u64 p3, u64 p4, u64 p5) { return IM(a)->pickup_item(p1, p2, p3, p4, p5); }
bool ItemModule__is_success_pickup_item_impl(BattleObjectModuleAccessor* a) { return IM(a)->is_success_pickup_item(); }
void* ItemModule__success_auto_pickup_item_impl(BattleObjectModuleAccessor* a) { return IM(a)->success_auto_pickup_item(); }
bool ItemModule__is_success_auto_pickup_item_impl(BattleObjectModuleAccessor* a) { return IM(a)->is_success_auto_pickup_item(); }
bool ItemModule__is_have_item_impl(BattleObjectModuleAccessor* a, u64 p1) { return IM(a)->is_have_item(p1); }

// -- have_item queries --
void* ItemModule__get_have_item_size_impl(BattleObjectModuleAccessor* a, u64 p1) asm("_ZN3app8lua_bind35ItemModule__get_have_item_size_implEPNS_26BattleObjectModuleAccessorE");
void* ItemModule__get_have_item_size_impl(BattleObjectModuleAccessor* a, u64 p1) { return IM(a)->get_have_item_size(p1); }
u32 ItemModule__get_have_item_kind_impl(BattleObjectModuleAccessor* a, u64 p1) asm("_ZN3app8lua_bind35ItemModule__get_have_item_kind_implEPNS_26BattleObjectModuleAccessorE");
u32 ItemModule__get_have_item_kind_impl(BattleObjectModuleAccessor* a, u64 p1) { return IM(a)->get_have_item_kind(p1); }
void* ItemModule__get_have_item_trait_impl(BattleObjectModuleAccessor* a, u64 p1) { return IM(a)->get_have_item_trait(p1); }
u32 ItemModule__get_have_item_hold_kind_impl(BattleObjectModuleAccessor* a, u64 p1) asm("_ZN3app8lua_bind40ItemModule__get_have_item_hold_kind_implEPNS_26BattleObjectModuleAccessorE");
u32 ItemModule__get_have_item_hold_kind_impl(BattleObjectModuleAccessor* a, u64 p1) { return IM(a)->get_have_item_hold_kind(p1); }
void* ItemModule__get_have_item_status_param_int_impl(BattleObjectModuleAccessor* a, u64 p1, u64 p2) { return IM(a)->get_have_item_status_param_int(p1, p2); }
void* ItemModule__get_have_item_status_param_float_impl(BattleObjectModuleAccessor* a, u64 p1, u64 p2) { return IM(a)->get_have_item_status_param_float(p1, p2); }
void* ItemModule__get_have_item_status_param_bool_impl(BattleObjectModuleAccessor* a, u64 p1, u64 p2) { return IM(a)->get_have_item_status_param_bool(p1, p2); }
u32 ItemModule__get_have_item_id_impl(BattleObjectModuleAccessor* a, u64 p1) asm("_ZN3app8lua_bind33ItemModule__get_have_item_id_implEPNS_26BattleObjectModuleAccessorE");
u32 ItemModule__get_have_item_id_impl(BattleObjectModuleAccessor* a, u64 p1) { return IM(a)->get_have_item_id(p1); }

// -- pickable --
u32 ItemModule__get_pickable_item_object_id_impl(BattleObjectModuleAccessor* a) { return IM(a)->get_pickable_item_object_id(); }
f32 ItemModule__get_pickable_item_size_impl(BattleObjectModuleAccessor* a) { return IM(a)->get_pickable_item_size(); }
u32 ItemModule__get_pickable_item_kind_impl(BattleObjectModuleAccessor* a) { return IM(a)->get_pickable_item_kind(); }
void* ItemModule__get_pickable_item_trait_impl(BattleObjectModuleAccessor* a) { return IM(a)->get_pickable_item_trait(); }

// -- remove/throw/warp --
void* ItemModule__remove_item_impl(BattleObjectModuleAccessor* a, u64 p1) { return IM(a)->remove_item(p1); }
void* ItemModule__remove_all_impl(BattleObjectModuleAccessor* a) { return IM(a)->remove_all(); }
void* ItemModule__throw_item_impl(BattleObjectModuleAccessor* a, u64 p1, bool p2) { return IM(a)->throw_item(p1, p2); }
void ItemModule__drop_item_impl(BattleObjectModuleAccessor* a, u64 p1) { IM(a)->drop_item(p1); }
void* ItemModule__warp_item_impl(BattleObjectModuleAccessor* a, u64 p1, u64 p2) { return IM(a)->warp_item(p1, p2); }
void* ItemModule__warp_attach_item_impl(BattleObjectModuleAccessor* a, u64 p1) { return IM(a)->warp_attach_item(p1); }
void ItemModule__born_item_impl(BattleObjectModuleAccessor* a, u64 p1) { IM(a)->born_item(p1); }

// -- shoot --
void* ItemModule__shoot_item_bullet_impl(BattleObjectModuleAccessor* a, u64 p1, u64 p2) { return IM(a)->shoot_item_bullet(p1, p2); }
void* ItemModule__shoot_item_bullet_blanks_impl(BattleObjectModuleAccessor* a, u64 p1, u64 p2) { return IM(a)->shoot_item_bullet_blanks(p1, p2); }
void* ItemModule__get_shoot_item_bullet_impl(BattleObjectModuleAccessor* a, u64 p1) { return IM(a)->get_shoot_item_bullet(p1); }

// -- have_item actions --
void ItemModule__update_have_item_action_info_impl(BattleObjectModuleAccessor* a, u64 p1) { IM(a)->update_have_item_action_info(p1); }
void ItemModule__set_have_item_scale_anim_impl(BattleObjectModuleAccessor* a, u64 p1, u64 p2) { IM(a)->set_have_item_scale_anim(p1, p2); }
void ItemModule__set_have_item_action_impl(BattleObjectModuleAccessor* a, u64 p1, u64 p2) { IM(a)->set_have_item_action(p1, p2); }
void ItemModule__set_have_item_visibility_impl(BattleObjectModuleAccessor* a, bool p1, u64 p2) { IM(a)->set_have_item_visibility(p1, p2); }
void ItemModule__set_have_item_hold_anim_impl(BattleObjectModuleAccessor* a, bool p1, u64 p2) { IM(a)->set_have_item_hold_anim(p1, p2); }
void ItemModule__set_have_item_constraint_joint_impl(BattleObjectModuleAccessor* a, u64 p1, u64 p2) { IM(a)->set_have_item_constraint_joint(p1, p2); }
void ItemModule__reset_have_item_constraint_node_impl(BattleObjectModuleAccessor* a, u64 p1) { IM(a)->reset_have_item_constraint_node(p1); }
void ItemModule__set_have_item_hit_sleep_impl(BattleObjectModuleAccessor* a, u64 p1, bool p2) { IM(a)->set_have_item_hit_sleep(p1, p2); }

// -- attach --
void* ItemModule__attach_item_impl(BattleObjectModuleAccessor* a, u64 p1, u64 p2, bool p3) asm("_ZN3app8lua_bind28ItemModule__attach_item_implEPNS_26BattleObjectModuleAccessorEyb");
void* ItemModule__attach_item_impl(BattleObjectModuleAccessor* a, u64 p1, u64 p2, bool p3) { return IM(a)->attach_item(p1, p2, p3); }
void ItemModule__attach_item_2_impl(BattleObjectModuleAccessor* a, u64 p1, bool p2) { IM(a)->attach_item_2(p1, p2); }
void ItemModule__attach_item_instance_impl(BattleObjectModuleAccessor* a, u64 p1, bool p2) { IM(a)->attach_item_instance(p1, p2); }
bool ItemModule__is_attach_item_impl(BattleObjectModuleAccessor* a, u64 p1) { return IM(a)->is_attach_item(p1); }
u32 ItemModule__get_attach_item_count_impl(BattleObjectModuleAccessor* a, u64 p1) { return IM(a)->get_attach_item_count(); }
void ItemModule__set_attach_item_visibility_impl(BattleObjectModuleAccessor* a, bool p1, u64 p2) { IM(a)->set_attach_item_visibility(p1, p2); }
void ItemModule__eject_have_item_impl(BattleObjectModuleAccessor* a, u64 p1, bool p2, bool p3) { IM(a)->eject_have_item(p1, p2, p3); }
void ItemModule__eject_attach_item_impl(BattleObjectModuleAccessor* a, u64 p1, bool p2, bool p3, bool p4) { IM(a)->eject_attach_item(p1, p2, p3, p4); }
void ItemModule__eject_attach_impl(BattleObjectModuleAccessor* a, u64 p1, bool p2, bool p3) { IM(a)->eject_attach(p1, p2, p3); }
void ItemModule__drop_attach_impl(BattleObjectModuleAccessor* a, u64 p1) { IM(a)->drop_attach(p1); }
void ItemModule__drop_attach_group_impl(BattleObjectModuleAccessor* a, u64 p1) { IM(a)->drop_attach_group(p1); }
void* ItemModule__scale_attach_impl(BattleObjectModuleAccessor* a, u64 p1) { return IM(a)->scale_attach(p1); }
void ItemModule__set_attach_item_action_impl(BattleObjectModuleAccessor* a, u64 p1, u64 p2) { IM(a)->set_attach_item_action(p1, p2); }
void ItemModule__set_have_item_team_impl(BattleObjectModuleAccessor* a, u64 p1, u64 p2) { IM(a)->set_have_item_team(p1, p2); }
void ItemModule__set_change_status_event_impl(BattleObjectModuleAccessor* a, bool p1) { IM(a)->set_change_status_event(p1); }

} // namespace app::lua_bind
