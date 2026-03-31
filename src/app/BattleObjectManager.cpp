#include "types.h"

// Forward declarations
struct BattleObjectManager;

extern "C" void* get_battle_object_from_id(u32 id);

namespace app::lua_bind {

// 7101fca0b0 — 19 instructions (calls, branches, tbz, cset)
bool BattleObjectManager__is_active_find_battle_object_impl(BattleObjectManager* mgr, u32 id) {
#ifdef MATCHING_HACK_NX_CLANG
    asm("" : "+r"(id)); // Prevent mov w0,w1 from being scheduled before prologue
#endif
    auto* obj = reinterpret_cast<u8*>(get_battle_object_from_id(id));
    if (obj == nullptr) {
        return false;
    }

    // vtable call: obj->vtable[0]()
    auto* vtable = *reinterpret_cast<void***>(obj);
    auto fn = reinterpret_cast<u64 (*)(void*)>(vtable[0]);
    u64 result = fn(obj);

    if (result & 1) {
        return false;
    }

    return obj[0x3a] > 3;
}

} // namespace app::lua_bind
