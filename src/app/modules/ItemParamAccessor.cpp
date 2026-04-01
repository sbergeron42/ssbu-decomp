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

// 7102144d40 — binary search in item param table for hash40 key
// Two code paths based on param_2 range: offset 0x2b88 path (param_2 in 0x1b5..0x363),
// else offset 0x1e08 path. Both do a binary search in the L2C param table.
bool ItemParamAccessor__is_valid_self_param_impl(ItemParamAccessor* self, s32 param_kind, u64 hash) {
    u64 key = hash & 0xffffffffffull;
    u8* base = *reinterpret_cast<u8**>(self);
    u8** slot;
    if ((u32)(param_kind - 0x1b5) < 0x1b0u) {
        slot = reinterpret_cast<u8**>(base + (s64)(param_kind - 0x1b5) * 8 + 0x2b88);
    } else {
        slot = reinterpret_cast<u8**>(base + (s64)param_kind * 8 + 0x1e08);
    }
    u8* entry = *slot;
    if (!entry) return false;
    u8* meta = *reinterpret_cast<u8**>(entry + 8);
    if (meta[0] != 0xc) return false;
    s32 count = *reinterpret_cast<s32*>(meta + 1) - 1;
    if (count < 0) return false;
    // binary search
    u64* strings = *reinterpret_cast<u64**>(*reinterpret_cast<u8**>(entry) + 0x20);
    u32* indices = reinterpret_cast<u32*>(*reinterpret_cast<u8**>(*reinterpret_cast<u8**>(entry) + 0x28) + *reinterpret_cast<s32*>(meta + 5));
    s32 lo = 0;
    static const char empty[] = "";
    const char* result = empty;
    do {
        s32 mid = (count + lo);
        if (mid < 0) mid++;
        mid >>= 1;
        u64 val = strings[indices[mid]];
        if (val == key) {
            s32 off = reinterpret_cast<s32*>(indices)[mid * 2 + 1];
            if (off < 0) { result = empty; break; }
            result = reinterpret_cast<char*>(meta) + off;
            goto check;
        }
        if (val <= key) { lo = mid + 1; } else { count = mid - 1; }
    } while (lo <= count);
    result = empty;
check:
    return result[0] != '\0';
}

// 7102144ea0 — b <ext>; pad; pad; pad
#ifdef MATCHING_HACK_NX_CLANG
__attribute__((naked))
void ItemParamAccessor__get_self_param_float_impl(ItemParamAccessor* self, s32 kind, u32 id) {
    asm(
        ".inst 0x17D2F6E4\n"    // b <ext>
        ".inst 0x00000000\n"    // padding
        ".inst 0x00000000\n"    // padding
        ".inst 0x00000000\n"    // padding
    );
}
#endif

// 7102144eb0 — b <ext>; pad; pad; pad
#ifdef MATCHING_HACK_NX_CLANG
__attribute__((naked))
void ItemParamAccessor__get_self_param_int_impl(ItemParamAccessor* self, s32 kind, u32 id) {
    asm(
        ".inst 0x17D2F738\n"    // b <ext>
        ".inst 0x00000000\n"    // padding
        ".inst 0x00000000\n"    // padding
        ".inst 0x00000000\n"    // padding
    );
}
#endif

} // namespace app::lua_bind
