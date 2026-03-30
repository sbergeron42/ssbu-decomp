#include "app/BattleObjectModuleAccessor.h"
#define TM(a) (*reinterpret_cast<void**>(reinterpret_cast<u8*>(a) + 0xD8))
#define VT(m) (*reinterpret_cast<void***>(m))
namespace app::lua_bind {
u32 TeamModule__team_no_impl(BattleObjectModuleAccessor* a) { auto* m=TM(a); return reinterpret_cast<u32(*)(void*)>(VT(m)[0x50/8])(m); }
void TeamModule__set_team_impl(BattleObjectModuleAccessor* a,u64 p1,bool p2) { auto* m=TM(a); reinterpret_cast<void(*)(void*,u64,bool)>(VT(m)[0x60/8])(m,p1,p2); }
void TeamModule__set_team_second_impl(BattleObjectModuleAccessor* a,u64 p1) { auto* m=TM(a); reinterpret_cast<void(*)(void*,u64)>(VT(m)[0x68/8])(m,p1); }
u32 TeamModule__hit_team_no_impl(BattleObjectModuleAccessor* a) { auto* m=TM(a); return reinterpret_cast<u32(*)(void*)>(VT(m)[0x78/8])(m); }
u32 TeamModule__hit_team_second_no_impl(BattleObjectModuleAccessor* a) { auto* m=TM(a); return reinterpret_cast<u32(*)(void*)>(VT(m)[0x80/8])(m); }
void TeamModule__set_hit_team_impl(BattleObjectModuleAccessor* a,u64 p1) { auto* m=TM(a); reinterpret_cast<void(*)(void*,u64)>(VT(m)[0x88/8])(m,p1); }
void TeamModule__set_hit_team_second_impl(BattleObjectModuleAccessor* a,u64 p1) { auto* m=TM(a); reinterpret_cast<void(*)(void*,u64)>(VT(m)[0x90/8])(m,p1); }
void TeamModule__set_team_owner_id_impl(BattleObjectModuleAccessor* a,u64 p1) { auto* m=TM(a); reinterpret_cast<void(*)(void*,u64)>(VT(m)[0xA0/8])(m,p1); }
u32 TeamModule__team_owner_id_impl(BattleObjectModuleAccessor* a) { auto* m=TM(a); return reinterpret_cast<u32(*)(void*)>(VT(m)[0xA8/8])(m); }
u32 TeamModule__metamon_owner_fighter_entry_id_impl(BattleObjectModuleAccessor* a) { auto* m=TM(a); return reinterpret_cast<u32(*)(void*)>(VT(m)[0xD8/8])(m); }
} // namespace app::lua_bind
