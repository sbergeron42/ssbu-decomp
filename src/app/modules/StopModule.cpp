#include "app/BattleObjectModuleAccessor.h"
#define STP(a) (*reinterpret_cast<void**>(reinterpret_cast<u8*>(a) + 0x90))
#define VT(m) (*reinterpret_cast<void***>(m))
namespace app::lua_bind {
void StopModule__cancel_hit_stop_impl(BattleObjectModuleAccessor* a) { auto* m=STP(a); reinterpret_cast<void(*)(void*)>(VT(m)[0x48/8])(m); }
u32 StopModule__get_other_stop_impl(BattleObjectModuleAccessor* a) { auto* m=STP(a); return reinterpret_cast<u32(*)(void*)>(VT(m)[0x58/8])(m); }
void StopModule__cancel_other_stop_impl(BattleObjectModuleAccessor* a) { auto* m=STP(a); reinterpret_cast<void(*)(void*)>(VT(m)[0x60/8])(m); }
u32 StopModule__get_item_stop_impl(BattleObjectModuleAccessor* a) { auto* m=STP(a); return reinterpret_cast<u32(*)(void*)>(VT(m)[0x70/8])(m); }
void StopModule__cancel_item_stop_impl(BattleObjectModuleAccessor* a) { auto* m=STP(a); reinterpret_cast<void(*)(void*)>(VT(m)[0x78/8])(m); }
bool StopModule__is_hit_impl(BattleObjectModuleAccessor* a) { auto* m=STP(a); return reinterpret_cast<bool(*)(void*)>(VT(m)[0x98/8])(m); }
bool StopModule__is_damage_impl(BattleObjectModuleAccessor* a) { auto* m=STP(a); return reinterpret_cast<bool(*)(void*)>(VT(m)[0xA0/8])(m); }
bool StopModule__is_item_impl(BattleObjectModuleAccessor* a) { auto* m=STP(a); return reinterpret_cast<bool(*)(void*)>(VT(m)[0xB0/8])(m); }
u32 StopModule__get_hit_stop_real_frame_impl(BattleObjectModuleAccessor* a) { auto* m=STP(a); return reinterpret_cast<u32(*)(void*)>(VT(m)[0xC8/8])(m); }
void StopModule__end_stop_impl(BattleObjectModuleAccessor* a) { auto* m=STP(a); reinterpret_cast<void(*)(void*)>(VT(m)[0xE8/8])(m); }
} // namespace app::lua_bind
