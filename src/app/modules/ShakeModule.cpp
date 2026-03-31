#include "app/BattleObjectModuleAccessor.h"
#define SK(a) (*reinterpret_cast<void**>(reinterpret_cast<u8*>(a) + 0x168))
#define VT(m) (*reinterpret_cast<void***>(m))
namespace app::lua_bind {
void ShakeModule__req_impl(BattleObjectModuleAccessor* a,u64 p1,u64 p2,bool p3,u64 p4,bool p5,bool p6) { auto* m=SK(a); reinterpret_cast<void(*)(void*,u64,u64,bool,u64,bool,bool)>(VT(m)[0x50/8])(m,p1,p2,p3,p4,p5,p6); }
void ShakeModule__req_time_scale_impl(BattleObjectModuleAccessor* a,u64 p1,u64 p2,bool p3,u64 p4,bool p5,bool p6,u64 p7) { auto* m=reinterpret_cast<void*>(*reinterpret_cast<u64*>(reinterpret_cast<u8*>(a)+0x168)); reinterpret_cast<void(*)(void*,u64,u64,bool,u64,bool,bool,u64)>(VT(m)[0x58/8])(m,p1,p2,p3,p4,p5,p6,p7); }
void ShakeModule__extend_impl(BattleObjectModuleAccessor* a,u64 p1,u64 p2) { auto* m=SK(a); reinterpret_cast<void(*)(void*,u64,u64)>(VT(m)[0x60/8])(m,p1,p2); }
void ShakeModule__stop_impl(BattleObjectModuleAccessor* a) { auto* m=SK(a); reinterpret_cast<void(*)(void*)>(VT(m)[0x68/8])(m); }
void ShakeModule__stop_kind_impl(BattleObjectModuleAccessor* a,u64 p1) { auto* m=SK(a); reinterpret_cast<void(*)(void*,u64)>(VT(m)[0x70/8])(m,p1); }
bool ShakeModule__is_shake_impl(BattleObjectModuleAccessor* a) { auto* m=SK(a); return reinterpret_cast<bool(*)(void*)>(VT(m)[0x88/8])(m); }
void* ShakeModule__offset_impl(BattleObjectModuleAccessor* a,u64 p1) { auto* m=SK(a); return reinterpret_cast<void*(*)(void*,u64)>(VT(m)[0x90/8])(m,p1); }
void ShakeModule__enable_offset_impl(BattleObjectModuleAccessor* a,u64 p1) { auto* m=SK(a); reinterpret_cast<void(*)(void*,u64)>(VT(m)[0x98/8])(m,p1); }
void ShakeModule__disable_offset_impl(BattleObjectModuleAccessor* a) { auto* m=SK(a); reinterpret_cast<void(*)(void*)>(VT(m)[0xa0/8])(m); }
void ShakeModule__set_scale_kind_impl(BattleObjectModuleAccessor* a,u64 p1) { auto* m=SK(a); reinterpret_cast<void(*)(void*,u64)>(VT(m)[0xa8/8])(m,p1); }
void ShakeModule__set_axis_xy_kind_impl(BattleObjectModuleAccessor* a,u64 p1,bool p2) { auto* m=SK(a); reinterpret_cast<void(*)(void*,u64,bool)>(VT(m)[0xb0/8])(m,p1,p2); }
void ShakeModule__set_ignore_slow_impl(BattleObjectModuleAccessor* a,bool p1) { auto* m=SK(a); reinterpret_cast<void(*)(void*,bool)>(VT(m)[0xb8/8])(m,p1); }
} // namespace app::lua_bind
