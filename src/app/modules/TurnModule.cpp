#include "app/BattleObjectModuleAccessor.h"
#define TN(a) (*reinterpret_cast<void**>(reinterpret_cast<u8*>(a) + 0xF0))
#define VT(m) (*reinterpret_cast<void***>(m))
namespace app::lua_bind {
// set_turn has 3 bool params (and w2,w3,w4 #1)
void TurnModule__set_turn_impl(BattleObjectModuleAccessor* a,u64 p1,bool p2,bool p3,bool p4) { auto* m=TN(a); reinterpret_cast<void(*)(void*,u64,bool,bool,bool)>(VT(m)[0x48/8])(m,p1,p2,p3,p4); }
void TurnModule__end_turn_impl(BattleObjectModuleAccessor* a) { auto* m=TN(a); reinterpret_cast<void(*)(void*)>(VT(m)[0x58/8])(m); }
bool TurnModule__is_turn_impl(BattleObjectModuleAccessor* a) { auto* m=TN(a); return reinterpret_cast<bool(*)(void*)>(VT(m)[0x68/8])(m); }
// is_turn_after90 is a stub: mov w0,wzr; ret (hardcoded return false)
bool TurnModule__is_turn_after90_impl(BattleObjectModuleAccessor*) { return false; }
bool TurnModule__is_extern_impl(BattleObjectModuleAccessor* a) { auto* m=TN(a); return reinterpret_cast<bool(*)(void*)>(VT(m)[0x70/8])(m); }
void TurnModule__set_omit_intermediate_impl(BattleObjectModuleAccessor* a,bool p1) { auto* m=TN(a); reinterpret_cast<void(*)(void*,bool)>(VT(m)[0x90/8])(m,p1); }
void TurnModule__ry_reverse_impl(BattleObjectModuleAccessor* a) { auto* m=TN(a); reinterpret_cast<void(*)(void*)>(VT(m)[0x98/8])(m); }
} // namespace app::lua_bind
