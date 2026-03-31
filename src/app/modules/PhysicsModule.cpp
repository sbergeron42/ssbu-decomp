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
// Remaining PhysicsModule dispatchers
void PhysicsModule__v0x60(BattleObjectModuleAccessor* a,bool p1,bool p2) { auto* m=PM(a); reinterpret_cast<void(*)(void*,bool,bool)>(VT(m)[0x60/8])(m,p1,p2); }
void PhysicsModule__v0x88(BattleObjectModuleAccessor* a,u64 p1) { auto* m=PM(a); reinterpret_cast<void(*)(void*,u64)>(VT(m)[0x88/8])(m,p1); }
void PhysicsModule__v0xa8(BattleObjectModuleAccessor* a,bool p1) { auto* m=PM(a); reinterpret_cast<void(*)(void*,bool)>(VT(m)[0xa8/8])(m,p1); }
void PhysicsModule__v0xc0(BattleObjectModuleAccessor* a,bool p1,u64 p2,bool p3) { auto* m=PM(a); reinterpret_cast<void(*)(void*,bool,u64,bool)>(VT(m)[0xc0/8])(m,p1,p2,p3); }
void PhysicsModule__v0xc8(BattleObjectModuleAccessor* a,bool p1) { auto* m=PM(a); reinterpret_cast<void(*)(void*,bool)>(VT(m)[0xc8/8])(m,p1); }
void PhysicsModule__v0xf0(BattleObjectModuleAccessor* a,u64 p1) { auto* m=PM(a); reinterpret_cast<void(*)(void*,u64)>(VT(m)[0xf0/8])(m,p1); }
void PhysicsModule__v0xf8(BattleObjectModuleAccessor* a,bool p1) { auto* m=PM(a); reinterpret_cast<void(*)(void*,bool)>(VT(m)[0xf8/8])(m,p1); }
void PhysicsModule__v0x100(BattleObjectModuleAccessor* a,u64 p1) { auto* m=PM(a); reinterpret_cast<void(*)(void*,u64)>(VT(m)[0x100/8])(m,p1); }
void PhysicsModule__v0x110(BattleObjectModuleAccessor* a,u64 p1) { auto* m=PM(a); reinterpret_cast<void(*)(void*,u64)>(VT(m)[0x110/8])(m,p1); }
void PhysicsModule__v0x120(BattleObjectModuleAccessor* a,u64 p1) { auto* m=PM(a); reinterpret_cast<void(*)(void*,u64)>(VT(m)[0x120/8])(m,p1); }
void PhysicsModule__v0x140(BattleObjectModuleAccessor* a,u64 p1) { auto* m=PM(a); reinterpret_cast<void(*)(void*,u64)>(VT(m)[0x140/8])(m,p1); }
void PhysicsModule__v0x168(BattleObjectModuleAccessor* a,u64 p1) { auto* m=PM(a); reinterpret_cast<void(*)(void*,u64)>(VT(m)[0x168/8])(m,p1); }
void PhysicsModule__v0x178(BattleObjectModuleAccessor* a,u64 p1) { auto* m=PM(a); reinterpret_cast<void(*)(void*,u64)>(VT(m)[0x178/8])(m,p1); }
void PhysicsModule__v0x180(BattleObjectModuleAccessor* a,bool p1) { auto* m=PM(a); reinterpret_cast<void(*)(void*,bool)>(VT(m)[0x180/8])(m,p1); }
void PhysicsModule__v0x190(BattleObjectModuleAccessor* a,u64 p1) { auto* m=PM(a); reinterpret_cast<void(*)(void*,u64)>(VT(m)[0x190/8])(m,p1); }
void PhysicsModule__v0x198(BattleObjectModuleAccessor* a,bool p1) { auto* m=PM(a); reinterpret_cast<void(*)(void*,bool)>(VT(m)[0x198/8])(m,p1); }
void PhysicsModule__v0x1b0(BattleObjectModuleAccessor* a,u64 p1) { auto* m=PM(a); reinterpret_cast<void(*)(void*,u64)>(VT(m)[0x1b0/8])(m,p1); }
void PhysicsModule__v0x1d0(BattleObjectModuleAccessor* a,u64 p1) { auto* m=PM(a); reinterpret_cast<void(*)(void*,u64)>(VT(m)[0x1d0/8])(m,p1); }
void PhysicsModule__v0x1d8(BattleObjectModuleAccessor* a,u64 p1) { auto* m=PM(a); reinterpret_cast<void(*)(void*,u64)>(VT(m)[0x1d8/8])(m,p1); }
void PhysicsModule__v0x1e0(BattleObjectModuleAccessor* a,u64 p1) { auto* m=PM(a); reinterpret_cast<void(*)(void*,u64)>(VT(m)[0x1e0/8])(m,p1); }
void PhysicsModule__v0x1f0(BattleObjectModuleAccessor* a,u64 p1) { auto* m=PM(a); reinterpret_cast<void(*)(void*,u64)>(VT(m)[0x1f0/8])(m,p1); }
void PhysicsModule__v0x200(BattleObjectModuleAccessor* a,u64 p1) { auto* m=PM(a); reinterpret_cast<void(*)(void*,u64)>(VT(m)[0x200/8])(m,p1); }
void PhysicsModule__v0x210(BattleObjectModuleAccessor* a,u64 p1) { auto* m=PM(a); reinterpret_cast<void(*)(void*,u64)>(VT(m)[0x210/8])(m,p1); }
void PhysicsModule__v0x218(BattleObjectModuleAccessor* a,u64 p1) { auto* m=PM(a); reinterpret_cast<void(*)(void*,u64)>(VT(m)[0x218/8])(m,p1); }
void PhysicsModule__v0x228(BattleObjectModuleAccessor* a,u64 p1) { auto* m=PM(a); reinterpret_cast<void(*)(void*,u64)>(VT(m)[0x228/8])(m,p1); }
void PhysicsModule__v0x240(BattleObjectModuleAccessor* a,u64 p1) { auto* m=PM(a); reinterpret_cast<void(*)(void*,u64)>(VT(m)[0x240/8])(m,p1); }
void PhysicsModule__v0x258(BattleObjectModuleAccessor* a,u64 p1) { auto* m=PM(a); reinterpret_cast<void(*)(void*,u64)>(VT(m)[0x258/8])(m,p1); }
void PhysicsModule__v0x268(BattleObjectModuleAccessor* a,u64 p1) { auto* m=PM(a); reinterpret_cast<void(*)(void*,u64)>(VT(m)[0x268/8])(m,p1); }
void PhysicsModule__v0x270(BattleObjectModuleAccessor* a,u64 p1,bool p2) { auto* m=PM(a); reinterpret_cast<void(*)(void*,u64,bool)>(VT(m)[0x270/8])(m,p1,p2); }
void PhysicsModule__v0x278(BattleObjectModuleAccessor* a,u64 p1,bool p2) { auto* m=PM(a); reinterpret_cast<void(*)(void*,u64,bool)>(VT(m)[0x278/8])(m,p1,p2); }
void PhysicsModule__v0x280(BattleObjectModuleAccessor* a,u64 p1) { auto* m=PM(a); reinterpret_cast<void(*)(void*,u64)>(VT(m)[0x280/8])(m,p1); }
void PhysicsModule__v0x288(BattleObjectModuleAccessor* a,u64 p1) { auto* m=PM(a); reinterpret_cast<void(*)(void*,u64)>(VT(m)[0x288/8])(m,p1); }
void PhysicsModule__v0x290(BattleObjectModuleAccessor* a,u64 p1) { auto* m=PM(a); reinterpret_cast<void(*)(void*,u64)>(VT(m)[0x290/8])(m,p1); }
void PhysicsModule__v0x2a0(BattleObjectModuleAccessor* a,u64 p1) { auto* m=PM(a); reinterpret_cast<void(*)(void*,u64)>(VT(m)[0x2a0/8])(m,p1); }
void PhysicsModule__v0x2b0(BattleObjectModuleAccessor* a,u64 p1) { auto* m=PM(a); reinterpret_cast<void(*)(void*,u64)>(VT(m)[0x2b0/8])(m,p1); }
void PhysicsModule__v0x2c0(BattleObjectModuleAccessor* a,u64 p1) { auto* m=PM(a); reinterpret_cast<void(*)(void*,u64)>(VT(m)[0x2c0/8])(m,p1); }
void PhysicsModule__v0x2e0(BattleObjectModuleAccessor* a,u64 p1) { auto* m=PM(a); reinterpret_cast<void(*)(void*,u64)>(VT(m)[0x2e0/8])(m,p1); }
void PhysicsModule__v0x2f0(BattleObjectModuleAccessor* a,bool p1) { auto* m=PM(a); reinterpret_cast<void(*)(void*,bool)>(VT(m)[0x2f0/8])(m,p1); }
void PhysicsModule__v0x300(BattleObjectModuleAccessor* a,bool p1) { auto* m=PM(a); reinterpret_cast<void(*)(void*,bool)>(VT(m)[0x300/8])(m,p1); }
void PhysicsModule__v0x308(BattleObjectModuleAccessor* a,u64 p1) { auto* m=PM(a); reinterpret_cast<void(*)(void*,u64)>(VT(m)[0x308/8])(m,p1); }
void PhysicsModule__v0x310(BattleObjectModuleAccessor* a,u64 p1) { auto* m=PM(a); reinterpret_cast<void(*)(void*,u64)>(VT(m)[0x310/8])(m,p1); }
void PhysicsModule__v0x318(BattleObjectModuleAccessor* a,u64 p1) { auto* m=PM(a); reinterpret_cast<void(*)(void*,u64)>(VT(m)[0x318/8])(m,p1); }
void PhysicsModule__v0x320(BattleObjectModuleAccessor* a,u64 p1) { auto* m=PM(a); reinterpret_cast<void(*)(void*,u64)>(VT(m)[0x320/8])(m,p1); }
void PhysicsModule__v0x340(BattleObjectModuleAccessor* a,u64 p1) { auto* m=PM(a); reinterpret_cast<void(*)(void*,u64)>(VT(m)[0x340/8])(m,p1); }
void PhysicsModule__v0x358(BattleObjectModuleAccessor* a,u64 p1) { auto* m=PM(a); reinterpret_cast<void(*)(void*,u64)>(VT(m)[0x358/8])(m,p1); }
void PhysicsModule__v0x3a8(BattleObjectModuleAccessor* a,u64 p1) { auto* m=PM(a); reinterpret_cast<void(*)(void*,u64)>(VT(m)[0x3a8/8])(m,p1); }
void PhysicsModule__v0x3b8(BattleObjectModuleAccessor* a,bool p1) { auto* m=PM(a); reinterpret_cast<void(*)(void*,bool)>(VT(m)[0x3b8/8])(m,p1); }
} // namespace app::lua_bind
