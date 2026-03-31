#include "app/BattleObjectModuleAccessor.h"
#define VT(m) (*reinterpret_cast<void***>(m))
namespace app::lua_bind {

// 71020adb50 — 6 instructions (vtable dispatcher with 2 bool masks)
void* FighterWorkModuleImpl__calc_param_impl(BattleObjectModuleAccessor* a,bool p1,bool p2) { auto* m=reinterpret_cast<void*>(*reinterpret_cast<u64*>(reinterpret_cast<u8*>(a)+0x50)); return reinterpret_cast<void*(*)(void*,bool,bool)>(VT(m)[0x280/8])(m,p1,p2); }

} // namespace app::lua_bind
