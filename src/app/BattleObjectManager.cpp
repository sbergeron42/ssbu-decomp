#include "types.h"

// Forward declarations
struct BattleObjectManager;

namespace app::lua_bind {

// 7101fca0b0 -- 19 instructions (calls, branches, tbz, cset)
extern "C" void* FUN_71003ac560(u32);
bool BattleObjectManager__is_active_find_battle_object_impl(BattleObjectManager* mgr, u32 id) {
    auto* obj = reinterpret_cast<u8*>(FUN_71003ac560(id));
    if (!obj) return false;
    auto fn = reinterpret_cast<bool(*)(void*)>(*reinterpret_cast<void***>(obj)[0]);
    if (fn(obj)) return false;
    return obj[0x3a] > 3;
}

} // namespace app::lua_bind
