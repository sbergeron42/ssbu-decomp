#include "types.h"

// Article -- operates on Article* directly (vtable dispatch)

struct Article;

namespace app::lua_bind {

// 71020f2d80 -- get_battle_object_id (3 instructions, vtable dispatch)
u32 Article__get_battle_object_id_impl(Article* article) {
    auto* vtable = *reinterpret_cast<void***>(article);
    return reinterpret_cast<u32 (*)(Article*)>(vtable[0x30 / 8])(article);
}

} // namespace app::lua_bind
