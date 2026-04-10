#include "types.h"
#include "app/BattleObject.h"

struct BattleObjectManager;

extern "C" app::BattleObject* tryFindBattleObjectById_71003ac560(u32);

namespace app::lua_bind {

bool BattleObjectManager__is_active_find_battle_object_impl(BattleObjectManager* mgr, u32 id) {
#ifdef MATCHING_HACK_NX_CLANG
    asm("" : "+r"(id));
#endif
    auto* obj = tryFindBattleObjectById_71003ac560(id);
    if (!obj) return false;
    if (obj->virtualFunc_0()) return false;
    return obj->category > 3;
}

} // namespace app::lua_bind
