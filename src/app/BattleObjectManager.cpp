#include "types.h"
#include "app/BattleObject.h"

// Forward declarations
struct BattleObjectManager;

namespace app::lua_bind {

// FUN_71003ac560 — lookup BattleObject by ID, returns nullptr if not found
// [derived: called by is_active_find_battle_object_impl and 15+ other functions]
extern "C" app::BattleObject* FUN_71003ac560(u32);

// 0x7101fca0b0 (76B) — check if a battle object is active by ID
// [derived: Ghidra — looks up object, checks vtable[0] (isInvalid), then category > 3]
bool BattleObjectManager__is_active_find_battle_object_impl(BattleObjectManager* mgr, u32 id) {
#ifdef MATCHING_HACK_NX_CLANG
    asm("" : "+r"(id));
#endif
    auto* obj = FUN_71003ac560(id);
    if (!obj) return false;
    if (obj->virtualFunc_0()) return false;
    return obj->category > 3;
}

} // namespace app::lua_bind
