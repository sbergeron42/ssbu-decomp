#include "app/BattleObjectModuleAccessor.h"
#define PM(a) (*reinterpret_cast<void**>(reinterpret_cast<u8*>(a) + 0x80))
#define VT(m) (*reinterpret_cast<void***>(m))
namespace app::lua_bind {
u32 PhysicsModule__get_2nd_status_impl(BattleObjectModuleAccessor* a) { auto* m=PM(a); return reinterpret_cast<u32(*)(void*)>(VT(m)[0x118/8])(m); }
f32 PhysicsModule__get_2nd_line_length_impl(BattleObjectModuleAccessor* a,u64 p1) { auto* m=PM(a); return reinterpret_cast<f32(*)(void*,u64)>(VT(m)[0x130/8])(m,p1); }
u32 PhysicsModule__get_2nd_node_num_impl(BattleObjectModuleAccessor* a,u64 p1) { auto* m=PM(a); return reinterpret_cast<u32(*)(void*,u64)>(VT(m)[0x150/8])(m,p1); }
u32 PhysicsModule__get_2nd_active_node_num_impl(BattleObjectModuleAccessor* a,u64 p1) { auto* m=PM(a); return reinterpret_cast<u32(*)(void*,u64)>(VT(m)[0x158/8])(m,p1); }
f32 PhysicsModule__get_2nd_active_length_impl(BattleObjectModuleAccessor* a,u64 p1) { auto* m=PM(a); return reinterpret_cast<f32(*)(void*,u64)>(VT(m)[0x160/8])(m,p1); }
u32 PhysicsModule__get_2nd_joint_num_impl(BattleObjectModuleAccessor* a,u64 p1) { auto* m=PM(a); return reinterpret_cast<u32(*)(void*,u64)>(VT(m)[0x248/8])(m,p1); }
u32 PhysicsModule__get_2nd_joint_id_impl(BattleObjectModuleAccessor* a,u64 p1) { auto* m=PM(a); return reinterpret_cast<u32(*)(void*,u64)>(VT(m)[0x250/8])(m,p1); }
void* PhysicsModule__get_2nd_pos_impl(BattleObjectModuleAccessor* a,u64 p1) { auto* m=PM(a); return reinterpret_cast<void*(*)(void*,u64)>(VT(m)[0x2A8/8])(m,p1); }
void* PhysicsModule__get_2nd_speed_impl(BattleObjectModuleAccessor* a,u64 p1) { auto* m=PM(a); return reinterpret_cast<void*(*)(void*,u64)>(VT(m)[0x2B8/8])(m,p1); }
void PhysicsModule__clear_2nd_speed_impl(BattleObjectModuleAccessor* a,u64 p1) { auto* m=PM(a); reinterpret_cast<void(*)(void*,u64)>(VT(m)[0x2E8/8])(m,p1); }
} // namespace app::lua_bind
