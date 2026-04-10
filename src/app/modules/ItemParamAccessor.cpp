#include "types.h"

struct ItemParamAccessor;

extern "C" f32 FUN_7101602a30(ItemParamAccessor*, s32, u32);
extern "C" u32 FUN_7101602b90(ItemParamAccessor*, s32, u32);

namespace app::lua_bind {

// 7102144ea0 -- pure tail-call to internal get_self_param_float
f32 ItemParamAccessor__get_self_param_float_impl(ItemParamAccessor* self, s32 kind, u32 id) {
    return FUN_7101602a30(self, kind, id);
}

// 7102144eb0 -- pure tail-call to internal get_self_param_int
u32 ItemParamAccessor__get_self_param_int_impl(ItemParamAccessor* self, s32 kind, u32 id) {
    return FUN_7101602b90(self, kind, id);
}

// 7102144d00 -- array index into param data with null-guard (64 bytes)
// base = *a; if base[idx*8+0xef8] == 0: return 0; else: return base[idx*32 + subidx*4 + 0x7da48]
u32 ItemParamAccessor__boss_common_param_int_impl(ItemParamAccessor* a, s32 idx, u32 subidx) {
    auto* base = *reinterpret_cast<u8**>(a);
    if (!*reinterpret_cast<u64*>(base + (s64)idx * 8 + 0xef8)) return 0;
    return *reinterpret_cast<u32*>(base + (s64)idx * 32 + (u64)subidx * 4 + 0x7da48);
}

} // namespace app::lua_bind

