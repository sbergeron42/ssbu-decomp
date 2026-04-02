#include "app/BattleObjectModuleAccessor.h"
#define IM(a) (*reinterpret_cast<void**>(reinterpret_cast<u8*>(a) + 0xC8))
#define HIT_MODULE(a) IM(a)
#define VT(m) (*reinterpret_cast<void***>(m))
namespace app::lua_bind {
// M-fix: mangled name says (accessor*) but body needs (accessor*, u64) to preserve x1 → use asm attr
void* ItemModule__get_have_item_size_impl(BattleObjectModuleAccessor* a,u64 p1) asm("_ZN3app8lua_bind35ItemModule__get_have_item_size_implEPNS_26BattleObjectModuleAccessorE");
void* ItemModule__get_have_item_size_impl(BattleObjectModuleAccessor* a,u64 p1) { auto* m=IM(a); return reinterpret_cast<void*(*)(void*,u64)>(VT(m)[0xd0/8])(m,p1); }
u32 ItemModule__get_have_item_kind_impl(BattleObjectModuleAccessor* a,u64 p1) asm("_ZN3app8lua_bind35ItemModule__get_have_item_kind_implEPNS_26BattleObjectModuleAccessorE");
u32 ItemModule__get_have_item_kind_impl(BattleObjectModuleAccessor* a,u64 p1) { auto* m=IM(a); return reinterpret_cast<u32(*)(void*,u64)>(VT(m)[0xd8/8])(m,p1); }
u32 ItemModule__get_have_item_hold_kind_impl(BattleObjectModuleAccessor* a,u64 p1) asm("_ZN3app8lua_bind40ItemModule__get_have_item_hold_kind_implEPNS_26BattleObjectModuleAccessorE");
u32 ItemModule__get_have_item_hold_kind_impl(BattleObjectModuleAccessor* a,u64 p1) { auto* m=IM(a); return reinterpret_cast<u32(*)(void*,u64)>(VT(m)[0xe8/8])(m,p1); }
u32 ItemModule__get_have_item_id_impl(BattleObjectModuleAccessor* a,u64 p1) asm("_ZN3app8lua_bind33ItemModule__get_have_item_id_implEPNS_26BattleObjectModuleAccessorE");
u32 ItemModule__get_have_item_id_impl(BattleObjectModuleAccessor* a,u64 p1) { auto* m=IM(a); return reinterpret_cast<u32(*)(void*,u64)>(VT(m)[0x108/8])(m,p1); }
// M-fix: mangled says (accessor*, u64, bool) but body needs (accessor*, u64, u64, bool)
void* ItemModule__attach_item_impl(BattleObjectModuleAccessor* a,u64 p1,u64 p2,bool p3) asm("_ZN3app8lua_bind28ItemModule__attach_item_implEPNS_26BattleObjectModuleAccessorEyb");
void* ItemModule__attach_item_impl(BattleObjectModuleAccessor* a,u64 p1,u64 p2,bool p3) { auto* m=IM(a); return reinterpret_cast<void*(*)(void*,u64,u64,bool)>(VT(m)[0x1f0/8])(m,p1,p2,p3); }
// M-fix: mangled says (accessor*, u64) but body only uses (accessor*) → add u64, vtable call stays (m)
u32 ItemModule__get_attach_item_count_impl(BattleObjectModuleAccessor* a,u64 p1) { auto* m=IM(a); return reinterpret_cast<u32(*)(void*)>(VT(m)[0x218/8])(m); }
// O functions (already matching)
void ItemModule__drop_item_impl(BattleObjectModuleAccessor* a,u64 p1) { auto* m=IM(a); reinterpret_cast<void(*)(void*,u64)>(VT(m)[0x168/8])(m,p1); }
void ItemModule__born_item_impl(BattleObjectModuleAccessor* a,u64 p1) { auto* m=IM(a); reinterpret_cast<void(*)(void*,u64)>(VT(m)[0x188/8])(m,p1); }
void ItemModule__attach_item_2_impl(BattleObjectModuleAccessor* a,u64 p1,bool p2) { auto* m=IM(a); reinterpret_cast<void(*)(void*,u64,bool)>(VT(m)[0x200/8])(m,p1,p2); }
void ItemModule__drop_attach_impl(BattleObjectModuleAccessor* a,u64 p1) { auto* m=IM(a); reinterpret_cast<void(*)(void*,u64)>(VT(m)[0x268/8])(m,p1); }
void ItemModule__drop_attach_group_impl(BattleObjectModuleAccessor* a,u64 p1) { auto* m=IM(a); reinterpret_cast<void(*)(void*,u64)>(VT(m)[0x270/8])(m,p1); }
// U functions -- all use accessor offset 0xC8 and tail-call via br
void ItemModule__have_item_impl(BattleObjectModuleAccessor* a,u64 p1,u64 p2,u64 p3,bool p4,bool p5) { auto* m=IM(a); reinterpret_cast<void(*)(void*,u64,u64,u64,bool,bool)>(VT(m)[0x58/8])(m,p1,p2,p3,p4,p5); }
void ItemModule__have_item_instance_impl(BattleObjectModuleAccessor* a,u64 p1,u64 p2,bool p3,bool p4,bool p5,bool p6) { auto* m=IM(a); reinterpret_cast<void(*)(void*,u64,u64,bool,bool,bool,bool)>(VT(m)[0x68/8])(m,p1,p2,p3,p4,p5,p6); }
void* ItemModule__use_item_instance_impl(BattleObjectModuleAccessor* a,u64 p1,bool p2) { auto* m=IM(a); return reinterpret_cast<void*(*)(void*,u64,bool)>(VT(m)[0x98/8])(m,p1,p2); }
void* ItemModule__use_item_impl(BattleObjectModuleAccessor* a,u64 p1,bool p2) { auto* m=IM(a); return reinterpret_cast<void*(*)(void*,u64,bool)>(VT(m)[0xa0/8])(m,p1,p2); }
void* ItemModule__pickup_item_impl(BattleObjectModuleAccessor* a,u64 p1,u64 p2,u64 p3,u64 p4,u64 p5) { auto* m=IM(a); return reinterpret_cast<void*(*)(void*,u64,u64,u64,u64,u64)>(VT(m)[0xa8/8])(m,p1,p2,p3,p4,p5); }
bool ItemModule__is_success_pickup_item_impl(BattleObjectModuleAccessor* a) { auto* m=IM(a); return reinterpret_cast<bool(*)(void*)>(VT(m)[0xb0/8])(m); }
void* ItemModule__success_auto_pickup_item_impl(BattleObjectModuleAccessor* a) { auto* m=IM(a); return reinterpret_cast<void*(*)(void*)>(VT(m)[0xb8/8])(m); }
bool ItemModule__is_success_auto_pickup_item_impl(BattleObjectModuleAccessor* a) { auto* m=IM(a); return reinterpret_cast<bool(*)(void*)>(VT(m)[0xc0/8])(m); }
bool ItemModule__is_have_item_impl(BattleObjectModuleAccessor* a,u64 p1) { auto* m=IM(a); return reinterpret_cast<bool(*)(void*,u64)>(VT(m)[0xc8/8])(m,p1); }
void* ItemModule__get_have_item_trait_impl(BattleObjectModuleAccessor* a,u64 p1) { auto* m=IM(a); return reinterpret_cast<void*(*)(void*,u64)>(VT(m)[0xe0/8])(m,p1); }
void* ItemModule__get_have_item_status_param_int_impl(BattleObjectModuleAccessor* a,u64 p1,u64 p2) { auto* m=IM(a); return reinterpret_cast<void*(*)(void*,u64,u64)>(VT(m)[0xf0/8])(m,p1,p2); }
void* ItemModule__get_have_item_status_param_float_impl(BattleObjectModuleAccessor* a,u64 p1,u64 p2) { auto* m=IM(a); return reinterpret_cast<void*(*)(void*,u64,u64)>(VT(m)[0xf8/8])(m,p1,p2); }
void* ItemModule__get_have_item_status_param_bool_impl(BattleObjectModuleAccessor* a,u64 p1,u64 p2) { auto* m=IM(a); return reinterpret_cast<void*(*)(void*,u64,u64)>(VT(m)[0x100/8])(m,p1,p2); }
u32 ItemModule__get_pickable_item_object_id_impl(BattleObjectModuleAccessor* a) { auto* m=IM(a); return reinterpret_cast<u32(*)(void*)>(VT(m)[0x120/8])(m); }
f32 ItemModule__get_pickable_item_size_impl(BattleObjectModuleAccessor* a) { auto* m=IM(a); return reinterpret_cast<f32(*)(void*)>(VT(m)[0x128/8])(m); }
u32 ItemModule__get_pickable_item_kind_impl(BattleObjectModuleAccessor* a) { auto* m=IM(a); return reinterpret_cast<u32(*)(void*)>(VT(m)[0x130/8])(m); }
void* ItemModule__get_pickable_item_trait_impl(BattleObjectModuleAccessor* a) { auto* m=IM(a); return reinterpret_cast<void*(*)(void*)>(VT(m)[0x138/8])(m); }
void* ItemModule__remove_item_impl(BattleObjectModuleAccessor* a,u64 p1) { auto* m=IM(a); return reinterpret_cast<void*(*)(void*,u64)>(VT(m)[0x148/8])(m,p1); }
void* ItemModule__remove_all_impl(BattleObjectModuleAccessor* a) { auto* m=IM(a); return reinterpret_cast<void*(*)(void*)>(VT(m)[0x150/8])(m); }
void* ItemModule__throw_item_impl(BattleObjectModuleAccessor* a,u64 p1,bool p2) { auto* m=IM(a); return reinterpret_cast<void*(*)(void*,u64,bool)>(VT(m)[0x158/8])(m,p1,p2); }
void* ItemModule__warp_item_impl(BattleObjectModuleAccessor* a,u64 p1,u64 p2) { auto* m=IM(a); return reinterpret_cast<void*(*)(void*,u64,u64)>(VT(m)[0x170/8])(m,p1,p2); }
void* ItemModule__warp_attach_item_impl(BattleObjectModuleAccessor* a,u64 p1) { auto* m=IM(a); return reinterpret_cast<void*(*)(void*,u64)>(VT(m)[0x180/8])(m,p1); }
void* ItemModule__shoot_item_bullet_impl(BattleObjectModuleAccessor* a,u64 p1,u64 p2) { auto* m=IM(a); return reinterpret_cast<void*(*)(void*,u64,u64)>(VT(m)[0x190/8])(m,p1,p2); }
void* ItemModule__shoot_item_bullet_blanks_impl(BattleObjectModuleAccessor* a,u64 p1,u64 p2) { auto* m=IM(a); return reinterpret_cast<void*(*)(void*,u64,u64)>(VT(m)[0x198/8])(m,p1,p2); }
void* ItemModule__get_shoot_item_bullet_impl(BattleObjectModuleAccessor* a,u64 p1) { auto* m=IM(a); return reinterpret_cast<void*(*)(void*,u64)>(VT(m)[0x1a0/8])(m,p1); }
void ItemModule__update_have_item_action_info_impl(BattleObjectModuleAccessor* a,u64 p1) { auto* m=IM(a); reinterpret_cast<void(*)(void*,u64)>(VT(m)[0x1a8/8])(m,p1); }
void ItemModule__set_have_item_scale_anim_impl(BattleObjectModuleAccessor* a,u64 p1,u64 p2) { auto* m=IM(a); reinterpret_cast<void(*)(void*,u64,u64)>(VT(m)[0x1b0/8])(m,p1,p2); }
void ItemModule__set_have_item_action_impl(BattleObjectModuleAccessor* a,u64 p1,u64 p2) { auto* m=IM(a); reinterpret_cast<void(*)(void*,u64,u64)>(VT(m)[0x1b8/8])(m,p1,p2); }
void ItemModule__set_have_item_visibility_impl(BattleObjectModuleAccessor* a,bool p1,u64 p2) { auto* m=IM(a); reinterpret_cast<void(*)(void*,bool,u64)>(VT(m)[0x1c0/8])(m,p1,p2); }
void ItemModule__set_have_item_hold_anim_impl(BattleObjectModuleAccessor* a,bool p1,u64 p2) { auto* m=IM(a); reinterpret_cast<void(*)(void*,bool,u64)>(VT(m)[0x1c8/8])(m,p1,p2); }
void ItemModule__set_have_item_constraint_joint_impl(BattleObjectModuleAccessor* a,u64 p1,u64 p2) { auto* m=IM(a); reinterpret_cast<void(*)(void*,u64,u64)>(VT(m)[0x1d0/8])(m,p1,p2); }
void ItemModule__reset_have_item_constraint_node_impl(BattleObjectModuleAccessor* a,u64 p1) { auto* m=IM(a); reinterpret_cast<void(*)(void*,u64)>(VT(m)[0x1d8/8])(m,p1); }
void ItemModule__set_have_item_hit_sleep_impl(BattleObjectModuleAccessor* a,u64 p1,bool p2) { auto* m=IM(a); reinterpret_cast<void(*)(void*,u64,bool)>(VT(m)[0x1e0/8])(m,p1,p2); }
void ItemModule__attach_item_instance_impl(BattleObjectModuleAccessor* a,u64 p1,bool p2) { auto* m=IM(a); reinterpret_cast<void(*)(void*,u64,bool)>(VT(m)[0x200/8])(m,p1,p2); }
bool ItemModule__is_attach_item_impl(BattleObjectModuleAccessor* a,u64 p1) { auto* m=IM(a); return reinterpret_cast<bool(*)(void*,u64)>(VT(m)[0x208/8])(m,p1); }
void ItemModule__set_attach_item_visibility_impl(BattleObjectModuleAccessor* a,bool p1,u64 p2) { auto* m=IM(a); reinterpret_cast<void(*)(void*,bool,u64)>(VT(m)[0x228/8])(m,p1,p2); }
void ItemModule__eject_have_item_impl(BattleObjectModuleAccessor* a,u64 p1,bool p2,bool p3) { auto* m=IM(a); reinterpret_cast<void(*)(void*,u64,bool,bool)>(VT(m)[0x240/8])(m,p1,p2,p3); }
void ItemModule__eject_attach_item_impl(BattleObjectModuleAccessor* a,u64 p1,bool p2,bool p3,bool p4) { auto* m=IM(a); reinterpret_cast<void(*)(void*,u64,bool,bool,bool)>(VT(m)[0x248/8])(m,p1,p2,p3,p4); }
void ItemModule__eject_attach_impl(BattleObjectModuleAccessor* a,u64 p1,bool p2,bool p3) { auto* m=IM(a); reinterpret_cast<void(*)(void*,u64,bool,bool)>(VT(m)[0x250/8])(m,p1,p2,p3); }
void* ItemModule__scale_attach_impl(BattleObjectModuleAccessor* a,u64 p1) { auto* m=IM(a); return reinterpret_cast<void*(*)(void*,u64)>(VT(m)[0x278/8])(m,p1); }
void ItemModule__set_attach_item_action_impl(BattleObjectModuleAccessor* a,u64 p1,u64 p2) { auto* m=IM(a); reinterpret_cast<void(*)(void*,u64,u64)>(VT(m)[0x280/8])(m,p1,p2); }
void ItemModule__set_have_item_team_impl(BattleObjectModuleAccessor* a,u64 p1,u64 p2) { auto* m=IM(a); reinterpret_cast<void(*)(void*,u64,u64)>(VT(m)[0x290/8])(m,p1,p2); }
void ItemModule__set_change_status_event_impl(BattleObjectModuleAccessor* a,bool p1) { auto* m=IM(a); reinterpret_cast<void(*)(void*,bool)>(VT(m)[0x2b0/8])(m,p1); }
} // namespace app::lua_bind
