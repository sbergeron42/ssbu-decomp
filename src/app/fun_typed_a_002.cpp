// fun_typed_a_002.cpp — Animcmd script handlers for AbsorberModule + ArticleModule
// Worker pool-a: 12 functions, simplified dispatch (compiled, non-matching)
// NOTE: NX Clang generates full lua-stack arg parsing that upstream Clang 8 omits.
// These capture correct semantics but won't byte-match the original 336-byte handlers.
// Pattern: load module from *(*(L-8) + MODULE_OFF), call vtable[VTBL_OFF]

#include "types.h"

extern "C" u64 FUN_71038f4000(u64, int, int);

// ---- Module offset 0xf0 (AbsorberModule in script context) -----------------

// 0x7102079930 (336 bytes) — bool return, vtable[0xb8] — AbsorberModule::is_hop
u64 FUN_7102079930(u64 L) {
    u64 acc = *(u64*)(L - 8); if (!acc) return 0;
    u64 mod = *(u64*)(acc + 0xf0); if (!mod) return 0;
    u64 a = FUN_71038f4000(L, 1, 0);
    u32 r = (**(u32(**)(u64,u64))(*(u64*)mod + 0xb8))(mod, a);
    u32* s = *(u32**)(L + 0x10); s[0] = r & 1; s[2] = 1;
    *(u64*)(L + 0x10) += 0x10; return 1;
}

// 0x7102079a80 (336 bytes) — u32 return, vtable[0xc0] — AbsorberModule::get_hop_angle
u64 FUN_7102079a80(u64 L) {
    u64 acc = *(u64*)(L - 8); if (!acc) return 0;
    u64 mod = *(u64*)(acc + 0xf0); if (!mod) return 0;
    u64 a = FUN_71038f4000(L, 1, 0);
    u32 r = (**(u32(**)(u64,u64))(*(u64*)mod + 0xc0))(mod, a);
    u32* s = *(u32**)(L + 0x10); s[0] = r; s[2] = 3;
    *(u64*)(L + 0x10) += 0x10; return 1;
}

// 0x7102079bd0 (336 bytes) — bool return, vtable[0xc8] — AbsorberModule::is_no_hop
u64 FUN_7102079bd0(u64 L) {
    u64 acc = *(u64*)(L - 8); if (!acc) return 0;
    u64 mod = *(u64*)(acc + 0xf0); if (!mod) return 0;
    u64 a = FUN_71038f4000(L, 1, 0);
    u32 r = (**(u32(**)(u64,u64))(*(u64*)mod + 0xc8))(mod, a);
    u32* s = *(u32**)(L + 0x10); s[0] = r & 1; s[2] = 1;
    *(u64*)(L + 0x10) += 0x10; return 1;
}

// 0x710207a4e0 (336 bytes) — u32 return, vtable[0xf0] — AbsorberModule::get_attack_mul
u64 FUN_710207a4e0(u64 L) {
    u64 acc = *(u64*)(L - 8); if (!acc) return 0;
    u64 mod = *(u64*)(acc + 0xf0); if (!mod) return 0;
    u64 a = FUN_71038f4000(L, 1, 0);
    u32 r = (**(u32(**)(u64,u64))(*(u64*)mod + 0xf0))(mod, a);
    u32* s = *(u32**)(L + 0x10); s[0] = r; s[2] = 3;
    *(u64*)(L + 0x10) += 0x10; return 1;
}

// 0x710207a830 (336 bytes) — u32 return, vtable[0x100] — AbsorberModule::get_speed_mul
u64 FUN_710207a830(u64 L) {
    u64 acc = *(u64*)(L - 8); if (!acc) return 0;
    u64 mod = *(u64*)(acc + 0xf0); if (!mod) return 0;
    u64 a = FUN_71038f4000(L, 1, 0);
    u32 r = (**(u32(**)(u64,u64))(*(u64*)mod + 0x100))(mod, a);
    u32* s = *(u32**)(L + 0x10); s[0] = r; s[2] = 3;
    *(u64*)(L + 0x10) += 0x10; return 1;
}

// 0x710207ab80 (336 bytes) — u32 return, vtable[0x110] — AbsorberModule::get_life_mul
u64 FUN_710207ab80(u64 L) {
    u64 acc = *(u64*)(L - 8); if (!acc) return 0;
    u64 mod = *(u64*)(acc + 0xf0); if (!mod) return 0;
    u64 a = FUN_71038f4000(L, 1, 0);
    u32 r = (**(u32(**)(u64,u64))(*(u64*)mod + 0x110))(mod, a);
    u32* s = *(u32**)(L + 0x10); s[0] = r; s[2] = 3;
    *(u64*)(L + 0x10) += 0x10; return 1;
}

// 0x710207aed0 (336 bytes) — u32 return, vtable[0x120] — AbsorberModule::get_attack_limit
u64 FUN_710207aed0(u64 L) {
    u64 acc = *(u64*)(L - 8); if (!acc) return 0;
    u64 mod = *(u64*)(acc + 0xf0); if (!mod) return 0;
    u64 a = FUN_71038f4000(L, 1, 0);
    u32 r = (**(u32(**)(u64,u64))(*(u64*)mod + 0x120))(mod, a);
    u32* s = *(u32**)(L + 0x10); s[0] = r; s[2] = 3;
    *(u64*)(L + 0x10) += 0x10; return 1;
}

// ---- Module offset 0x80 (ArticleModule in script context) ------------------

// 0x7102097780 (304 bytes) — void return, vtable[0x1c0] — ArticleModule::remove_exist_object_id
u64 FUN_7102097780(u64 L) {
    u64 acc = *(u64*)(L - 8); if (!acc) return 0;
    u64 mod = *(u64*)(acc + 0x80); if (!mod) return 0;
    u64 a = FUN_71038f4000(L, 1, 0);
    (**(void(**)(u64,u64))(*(u64*)mod + 0x1c0))(mod, a);
    return 0;
}

// 0x71020978b0 (336 bytes) — bool return, vtable[0x1c8] — ArticleModule::is_exist
u64 FUN_71020978b0(u64 L) {
    u64 acc = *(u64*)(L - 8); if (!acc) return 0;
    u64 mod = *(u64*)(acc + 0x80); if (!mod) return 0;
    u64 a = FUN_71038f4000(L, 1, 0);
    u32 r = (**(u32(**)(u64,u64))(*(u64*)mod + 0x1c8))(mod, a);
    u32* s = *(u32**)(L + 0x10); s[0] = r & 1; s[2] = 1;
    *(u64*)(L + 0x10) += 0x10; return 1;
}

// 0x7102097a00 (336 bytes) — s32→s64 return, vtable[0x1d0] — ArticleModule::get_num
u64 FUN_7102097a00(u64 L) {
    u64 acc = *(u64*)(L - 8); if (!acc) return 0;
    u64 mod = *(u64*)(acc + 0x80); if (!mod) return 0;
    u64 a = FUN_71038f4000(L, 1, 0);
    s32 r = (**(s32(**)(u64,u64))(*(u64*)mod + 0x1d0))(mod, a);
    s64* s = *(s64**)(L + 0x10);
    *s = (s64)r;
    *(u32*)(s + 1) = 0x13;
    *(u64*)(L + 0x10) += 0x10;
    return 1;
}

// 0x7102097b50 (336 bytes) — bool return, vtable[0x1d8] — ArticleModule::is_generatable
u64 FUN_7102097b50(u64 L) {
    u64 acc = *(u64*)(L - 8); if (!acc) return 0;
    u64 mod = *(u64*)(acc + 0x80); if (!mod) return 0;
    u64 a = FUN_71038f4000(L, 1, 0);
    u32 r = (**(u32(**)(u64,u64))(*(u64*)mod + 0x1d8))(mod, a);
    u32* s = *(u32**)(L + 0x10); s[0] = r & 1; s[2] = 1;
    *(u64*)(L + 0x10) += 0x10; return 1;
}

// 0x7102097ca0 (336 bytes) — s32→s64 return, vtable[0x1e0] — ArticleModule::get_active_num
u64 FUN_7102097ca0(u64 L) {
    u64 acc = *(u64*)(L - 8); if (!acc) return 0;
    u64 mod = *(u64*)(acc + 0x80); if (!mod) return 0;
    u64 a = FUN_71038f4000(L, 1, 0);
    s32 r = (**(s32(**)(u64,u64))(*(u64*)mod + 0x1e0))(mod, a);
    s64* s = *(s64**)(L + 0x10);
    *s = (s64)r;
    *(u32*)(s + 1) = 0x13;
    *(u64*)(L + 0x10) += 0x10;
    return 1;
}
