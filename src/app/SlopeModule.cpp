#include "app/BattleObjectModuleAccessor.h"
#define VT(m) (*reinterpret_cast<void***>(m))

struct SlopeModule;

namespace app::lua_bind {

void SlopeModule__update_model_top_angle_impl(BattleObjectModuleAccessor* a) { auto* m=reinterpret_cast<void*>(*reinterpret_cast<u64*>(reinterpret_cast<u8*>(a)+0x160)); reinterpret_cast<void(*)(void*)>(VT(m)[0x70/8])(m); }
void* SlopeModule__floor_diff_l_impl(BattleObjectModuleAccessor* a) { auto* m=reinterpret_cast<void*>(*reinterpret_cast<u64*>(reinterpret_cast<u8*>(a)+0x160)); return reinterpret_cast<void*(*)(void*)>(VT(m)[0x98/8])(m); }
void* SlopeModule__floor_diff_r_impl(BattleObjectModuleAccessor* a) { auto* m=reinterpret_cast<void*>(*reinterpret_cast<u64*>(reinterpret_cast<u8*>(a)+0x160)); return reinterpret_cast<void*(*)(void*)>(VT(m)[0xa0/8])(m); }

} // namespace app::lua_bind
