#include "types.h"

struct ItemParamAccessor;

namespace app::lua_bind {

// 7102144d00 -- array index into param data with null-guard (64 bytes)
// base = *a; if base[idx*8+0xef8] == 0: return 0; else: return base[idx*32 + subidx*4 + 0x7da48]
u32 ItemParamAccessor__boss_common_param_int_impl(ItemParamAccessor* a, s32 idx, u32 subidx) {
    auto* base = *reinterpret_cast<u8**>(a);
    if (!*reinterpret_cast<u64*>(base + (s64)idx * 8 + 0xef8)) return 0;
    return *reinterpret_cast<u32*>(base + (s64)idx * 32 + (u64)subidx * 4 + 0x7da48);
}

} // namespace app::lua_bind

