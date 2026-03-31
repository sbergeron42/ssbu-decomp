#include "app/BattleObjectModuleAccessor.h"
#define STP(a) (*reinterpret_cast<void**>(reinterpret_cast<u8*>(a) + 0x90))
#define VT(m) (*reinterpret_cast<void***>(m))
namespace app::lua_bind {
void StopModule__cancel_hit_stop_impl(BattleObjectModuleAccessor* a) { auto* m=STP(a); reinterpret_cast<void(*)(void*)>(VT(m)[0x48/8])(m); }
void* StopModule__get_other_stop_impl(BattleObjectModuleAccessor* a,u64 p1) { auto* m=reinterpret_cast<void*>(*reinterpret_cast<u64*>(reinterpret_cast<u8*>(a)+0x90)); return reinterpret_cast<void*(*)(void*,u64)>(VT(m)[0x58/8])(m,p1); }
void* StopModule__cancel_other_stop_impl(BattleObjectModuleAccessor* a,u64 p1) { auto* m=reinterpret_cast<void*>(*reinterpret_cast<u64*>(reinterpret_cast<u8*>(a)+0x90)); return reinterpret_cast<void*(*)(void*,u64)>(VT(m)[0x60/8])(m,p1); }
u32 StopModule__get_item_stop_impl(BattleObjectModuleAccessor* a) { auto* m=STP(a); return reinterpret_cast<u32(*)(void*)>(VT(m)[0x70/8])(m); }
void StopModule__cancel_item_stop_impl(BattleObjectModuleAccessor* a) { auto* m=STP(a); reinterpret_cast<void(*)(void*)>(VT(m)[0x78/8])(m); }
bool StopModule__is_hit_impl(BattleObjectModuleAccessor* a) { auto* m=STP(a); return reinterpret_cast<bool(*)(void*)>(VT(m)[0x98/8])(m); }
bool StopModule__is_damage_impl(BattleObjectModuleAccessor* a) { auto* m=STP(a); return reinterpret_cast<bool(*)(void*)>(VT(m)[0xA0/8])(m); }
bool StopModule__is_item_impl(BattleObjectModuleAccessor* a) { auto* m=STP(a); return reinterpret_cast<bool(*)(void*)>(VT(m)[0xB0/8])(m); }
u32 StopModule__get_hit_stop_real_frame_impl(BattleObjectModuleAccessor* a) { auto* m=STP(a); return reinterpret_cast<u32(*)(void*)>(VT(m)[0xC8/8])(m); }
void StopModule__end_stop_impl(BattleObjectModuleAccessor* a) { auto* m=STP(a); reinterpret_cast<void(*)(void*)>(VT(m)[0xE8/8])(m); }
void StopModule__set_other_stop_impl(BattleObjectModuleAccessor* a,u64 p1,u64 p2) { auto* m=reinterpret_cast<void*>(*reinterpret_cast<u64*>(reinterpret_cast<u8*>(a)+0x90)); reinterpret_cast<void(*)(void*,u64,u64)>(VT(m)[0x50/8])(m,p1,p2); }
void StopModule__set_item_stop_impl(BattleObjectModuleAccessor* a,u64 p1) { auto* m=STP(a); reinterpret_cast<void(*)(void*,u64)>(VT(m)[0x68/8])(m,p1); }
void StopModule__set_link_stop_impl(BattleObjectModuleAccessor* a,bool p1,bool p2) { auto* m=reinterpret_cast<void*>(*reinterpret_cast<u64*>(reinterpret_cast<u8*>(a)+0x90)); reinterpret_cast<void(*)(void*,bool,bool)>(VT(m)[0x80/8])(m,p1,p2); }
bool StopModule__is_stop_impl(BattleObjectModuleAccessor* a) { auto* m=STP(a); return reinterpret_cast<bool(*)(void*)>(VT(m)[0x88/8])(m); }
bool StopModule__is_special_stop_impl(BattleObjectModuleAccessor* a) { auto* m=STP(a); return reinterpret_cast<bool(*)(void*)>(VT(m)[0x90/8])(m); }
bool StopModule__is_other_impl(BattleObjectModuleAccessor* a) { auto* m=STP(a); return reinterpret_cast<bool(*)(void*)>(VT(m)[0xb8/8])(m); }
void StopModule__set_hit_stop_frame_impl(BattleObjectModuleAccessor* a,u64 p1,bool p2) { auto* m=STP(a); reinterpret_cast<void(*)(void*,u64,bool)>(VT(m)[0xd0/8])(m,p1,p2); }
void StopModule__set_hit_stop_frame_fix_impl(BattleObjectModuleAccessor* a,u64 p1) { auto* m=STP(a); reinterpret_cast<void(*)(void*,u64)>(VT(m)[0xd8/8])(m,p1); }
void StopModule__set_special_stop_impl(BattleObjectModuleAccessor* a,bool p1) { auto* m=reinterpret_cast<void*>(*reinterpret_cast<u64*>(reinterpret_cast<u8*>(a)+0x90)); reinterpret_cast<void(*)(void*,bool)>(VT(m)[0xe0/8])(m,p1); }
} // namespace app::lua_bind
