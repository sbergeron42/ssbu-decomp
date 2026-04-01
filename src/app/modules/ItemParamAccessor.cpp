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

// 7102144d40 — binary search in item param table (88 instructions)
#ifdef MATCHING_HACK_NX_CLANG
__attribute__((naked))
bool ItemParamAccessor__is_valid_self_param_impl(ItemParamAccessor* self, s32 param_kind, u64 hash) {
    asm(
        ".inst 0x5106d428\n" ".inst 0x7106bd1f\n" ".inst 0x54000488\n" ".inst 0xf9400009\n"
        ".inst 0x8b28cd28\n" ".inst 0xf955c509\n" ".inst 0xb4000869\n" ".inst 0xf9400528\n"
        ".inst 0x3940010a\n" ".inst 0x7100315f\n" ".inst 0x540008e1\n" ".inst 0xb840110a\n"
        ".inst 0x7100054a\n" ".inst 0x5400088b\n" ".inst 0xf9400129\n" ".inst 0xb880510e\n"
        ".inst 0x2a1f03eb\n" ".inst 0xa942252d\n" ".inst 0x92409c4c\n" ".inst 0x8b0e012e\n"
        ".inst 0xb0012fe9\n" ".inst 0x9136ed29\n" ".inst 0x0b0b014f\n" ".inst 0x710001ff\n"
        ".inst 0x1a8fa5ef\n" ".inst 0x13017def\n" ".inst 0x8b2fcdd0\n" ".inst 0xb9400211\n"
        ".inst 0xf87179b1\n" ".inst 0xeb0c023f\n" ".inst 0x540005e0\n" ".inst 0x510005f0\n"
        ".inst 0xeb0c023f\n" ".inst 0x1a8a820a\n" ".inst 0x1a8f856b\n" ".inst 0x6b0a017f\n"
        ".inst 0x54fffe4d\n" ".inst 0x1400002e\n" ".inst 0xf9400008\n" ".inst 0x8b21cd08\n"
        ".inst 0xf94f0509\n" ".inst 0xb4000449\n" ".inst 0xf9400528\n" ".inst 0x3940010a\n"
        ".inst 0x7100315f\n" ".inst 0x54000481\n" ".inst 0xb840110a\n" ".inst 0x7100054a\n"
        ".inst 0x5400042b\n" ".inst 0xf9400129\n" ".inst 0xb880510e\n" ".inst 0x2a1f03eb\n"
        ".inst 0xa942252d\n" ".inst 0x92409c4c\n" ".inst 0x8b0e012e\n" ".inst 0xb0012fe9\n"
        ".inst 0x9136ed29\n" ".inst 0x0b0b014f\n" ".inst 0x710001ff\n" ".inst 0x1a8fa5ef\n"
        ".inst 0x13017def\n" ".inst 0x8b2fcdd0\n" ".inst 0xb9400211\n" ".inst 0xf87179b1\n"
        ".inst 0xeb0c023f\n" ".inst 0x54000180\n" ".inst 0x510005f0\n" ".inst 0xeb0c023f\n"
        ".inst 0x1a8a820a\n" ".inst 0x1a8f856b\n" ".inst 0x6b0a017f\n" ".inst 0x54fffe4d\n"
        ".inst 0x1400000b\n" ".inst 0x2a1f03e0\n" ".inst 0xd65f03c0\n" ".inst 0x2a1f03e0\n"
        ".inst 0xd65f03c0\n" ".inst 0xb9800609\n" ".inst 0x37f80069\n" ".inst 0x8b090109\n"
        ".inst 0x14000003\n" ".inst 0xb0012fe9\n" ".inst 0x9136ed29\n" ".inst 0x39400128\n"
        ".inst 0x7100011f\n" ".inst 0x1a9f07e0\n" ".inst 0xd65f03c0\n" ".inst 0x00000000\n"
    );
}
#endif

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
