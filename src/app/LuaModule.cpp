#include "app/BattleObjectModuleAccessor.h"
#define VT(m) (*reinterpret_cast<void***>(m))

struct LuaModule;

namespace app::lua_bind {

void LuaModule__enable_line_impl(BattleObjectModuleAccessor* a,u64 p1) { auto* m=reinterpret_cast<void*>(*reinterpret_cast<u64*>(reinterpret_cast<u8*>(a)+0x190)); reinterpret_cast<void(*)(void*,u64)>(VT(m)[0x58/8])(m,p1); }
void* LuaModule__disable_line_impl(BattleObjectModuleAccessor* a,u64 p1) { auto* m=reinterpret_cast<void*>(*reinterpret_cast<u64*>(reinterpret_cast<u8*>(a)+0x190)); return reinterpret_cast<void*(*)(void*,u64)>(VT(m)[0x60/8])(m,p1); }
bool LuaModule__is_valid_line_impl(BattleObjectModuleAccessor* a,u64 p1) { auto* m=reinterpret_cast<void*>(*reinterpret_cast<u64*>(reinterpret_cast<u8*>(a)+0x190)); return reinterpret_cast<bool(*)(void*,u64)>(VT(m)[0x68/8])(m,p1); }
void* LuaModule__get_execute_line_impl(BattleObjectModuleAccessor* a) { auto* m=reinterpret_cast<void*>(*reinterpret_cast<u64*>(reinterpret_cast<u8*>(a)+0x190)); return reinterpret_cast<void*(*)(void*)>(VT(m)[0x80/8])(m); }
void* LuaModule__reserve_status_data_array_impl(BattleObjectModuleAccessor* a,u64 p1) { auto* m=reinterpret_cast<void*>(*reinterpret_cast<u64*>(reinterpret_cast<u8*>(a)+0x190)); return reinterpret_cast<void*(*)(void*,u64)>(VT(m)[0x88/8])(m,p1); }
void LuaModule__enable_func_impl(BattleObjectModuleAccessor* a,u64 p1) { auto* m=reinterpret_cast<void*>(*reinterpret_cast<u64*>(reinterpret_cast<u8*>(a)+0x190)); reinterpret_cast<void(*)(void*,u64)>(VT(m)[0xa8/8])(m,p1); }
void* LuaModule__disable_func_impl(BattleObjectModuleAccessor* a,u64 p1) { auto* m=reinterpret_cast<void*>(*reinterpret_cast<u64*>(reinterpret_cast<u8*>(a)+0x190)); return reinterpret_cast<void*(*)(void*,u64)>(VT(m)[0xb0/8])(m,p1); }
bool LuaModule__is_valid_func_impl(BattleObjectModuleAccessor* a,u64 p1) { auto* m=reinterpret_cast<void*>(*reinterpret_cast<u64*>(reinterpret_cast<u8*>(a)+0x190)); return reinterpret_cast<bool(*)(void*,u64)>(VT(m)[0xb8/8])(m,p1); }

} // namespace app::lua_bind
