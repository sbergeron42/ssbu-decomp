#include "types.h"

struct ItemParamAccessor;

namespace app::lua_bind {

// 7102144d00 — table lookup via base ptr + group*8 + 0xef8 null check,
//               then base + group*32 + param_id*4 + 0x7da48
u32 ItemParamAccessor__boss_common_param_int_impl(ItemParamAccessor* self, s32 group, u32 param_id) {
    u8* base = *reinterpret_cast<u8**>(self);
    void* check = *reinterpret_cast<void**>(base + (s64)group * 8 + 0xef8);
    if (!check) return 0;
    u8* row = base + (s64)group * 32 + (u64)param_id * 4;
    return *reinterpret_cast<u32*>(row + 0x7da48);
}

} // namespace app::lua_bind
