#include "types.h"

struct ItemParamAccessor;

namespace app::lua_bind {

// 7102144d00 — array index into param data with null-guard (64 bytes)
// base = *a; if base[idx*8+0xef8] == 0: return 0; else: return base[idx*32 + subidx*4 + 0x7da48]
u32 ItemParamAccessor__boss_common_param_int_impl(ItemParamAccessor* a, s32 idx, u32 subidx) {
    auto* base = *reinterpret_cast<u8**>(a);
    if (!*reinterpret_cast<u64*>(base + (s64)idx * 8 + 0xef8)) return 0;
    return *reinterpret_cast<u32*>(base + (s64)idx * 32 + (u64)subidx * 4 + 0x7da48);
}

// 7102144d40 — binary search through sorted param key arrays (352 bytes)
// Two paths: idx in [0x1b5,0x364] checks offset 0x2b88, else checks 0x1e08
// Uses adrp globals as sentinel pointer — won't match
bool ItemParamAccessor__is_valid_self_param_impl(ItemParamAccessor* a, u32 idx, u64 key) {
    (void)a; (void)idx; (void)key;
    return false;
}

// 7102144ea0 — single instruction: b 0x7101602a30 (tail call, won't match)
f32 ItemParamAccessor__get_self_param_float_impl(ItemParamAccessor* a, u32 idx, u64 key) {
    (void)a; (void)idx; (void)key;
    return 0.0f;
}

// 7102144eb0 — single instruction: b 0x7101602b90 (tail call, won't match)
s32 ItemParamAccessor__get_self_param_int_impl(ItemParamAccessor* a, u32 idx, u64 key) {
    (void)a; (void)idx; (void)key;
    return 0;
}

} // namespace app::lua_bind
