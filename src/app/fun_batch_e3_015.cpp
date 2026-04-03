#include "types.h"

// MEDIUM-tier FUN_* functions — 0x7102 address range, batch e3-015
// Pool-e worker: lua_bind dispatch functions 0x710202bcb0–0x710203e6d0
// Pattern: get module from *(*(L-8) + MODULE_OFF), call vtable[VTBL_OFF]

extern "C" u64 FUN_71038f4000(u64, int, int);

// ---- Module offset 0x40 (StatusModule) -------------------------------------

// 0x710202bcb0 (304 bytes) — void dispatch, vtable[0x148]
u64 FUN_710202bcb0(u64 L) {
    u64 acc = *(u64*)(L - 8); if (!acc) return 0;
    u64 mod = *(u64*)(acc + 0x40); if (!mod) return 0;
    u64 a = FUN_71038f4000(L, 1, 0);
    (**(void(**)(u64,u64))(*(u64*)mod + 0x148))(mod, a);
    return 0;
}

// 0x710202cd40 (528 bytes) — void dispatch, vtable[0x218]
u64 FUN_710202cd40(u64 L) {
    u64 acc = *(u64*)(L - 8); if (!acc) return 0;
    u64 mod = *(u64*)(acc + 0x40); if (!mod) return 0;
    u64 a = FUN_71038f4000(L, 1, 0);
    (**(void(**)(u64,u64))(*(u64*)mod + 0x218))(mod, a);
    return 0;
}

// 0x710202f6c0 (432 bytes) — void dispatch, vtable[0x368]
u64 FUN_710202f6c0(u64 L) {
    u64 acc = *(u64*)(L - 8); if (!acc) return 0;
    u64 mod = *(u64*)(acc + 0x40); if (!mod) return 0;
    u64 a = FUN_71038f4000(L, 1, 0);
    (**(void(**)(u64,u64))(*(u64*)mod + 0x368))(mod, a);
    return 0;
}

// 0x710202ff40 (336 bytes) — bool return, vtable[0x3b0]
u64 FUN_710202ff40(u64 L) {
    u64 acc = *(u64*)(L - 8); if (!acc) return 0;
    u64 mod = *(u64*)(acc + 0x40); if (!mod) return 0;
    u64 a = FUN_71038f4000(L, 1, 0);
    u32 r = (**(u32(**)(u64,u64))(*(u64*)mod + 0x3b0))(mod, a);
    u32* s = *(u32**)(L + 0x10); s[0] = r & 1; s[2] = 1;
    *(u64*)(L + 0x10) += 0x10; return 1;
}

// 0x7102030090 (512 bytes) — void dispatch, vtable[0x3b8]
u64 FUN_7102030090(u64 L) {
    u64 acc = *(u64*)(L - 8); if (!acc) return 0;
    u64 mod = *(u64*)(acc + 0x40); if (!mod) return 0;
    u64 a = FUN_71038f4000(L, 1, 0);
    (**(void(**)(u64,u64))(*(u64*)mod + 0x3b8))(mod, a);
    return 0;
}

// 0x7102030290 (352 bytes) — u32 return, vtable[0x3d0]
u64 FUN_7102030290(u64 L) {
    u64 acc = *(u64*)(L - 8); if (!acc) return 0;
    u64 mod = *(u64*)(acc + 0x40); if (!mod) return 0;
    u64 a = FUN_71038f4000(L, 1, 0);
    u32 r = (**(u32(**)(u64,u64))(*(u64*)mod + 0x3d0))(mod, a);
    u32* s = *(u32**)(L + 0x10); s[0] = r; s[2] = 3;
    *(u64*)(L + 0x10) += 0x10; return 1;
}

// 0x71020303f0 (432 bytes) — void dispatch, vtable[0x3e8]
u64 FUN_71020303f0(u64 L) {
    u64 acc = *(u64*)(L - 8); if (!acc) return 0;
    u64 mod = *(u64*)(acc + 0x40); if (!mod) return 0;
    u64 a = FUN_71038f4000(L, 1, 0);
    (**(void(**)(u64,u64))(*(u64*)mod + 0x3e8))(mod, a);
    return 0;
}

// 0x71020305d0 (368 bytes) — u32 return, vtable[0x408]
u64 FUN_71020305d0(u64 L) {
    u64 acc = *(u64*)(L - 8); if (!acc) return 0;
    u64 mod = *(u64*)(acc + 0x40); if (!mod) return 0;
    u64 a = FUN_71038f4000(L, 1, 0);
    u32 r = (**(u32(**)(u64,u64))(*(u64*)mod + 0x408))(mod, a);
    u32* s = *(u32**)(L + 0x10); s[0] = r; s[2] = 3;
    *(u64*)(L + 0x10) += 0x10; return 1;
}

// 0x7102030740 (336 bytes) — u32 return, vtable[0x410]
u64 FUN_7102030740(u64 L) {
    u64 acc = *(u64*)(L - 8); if (!acc) return 0;
    u64 mod = *(u64*)(acc + 0x40); if (!mod) return 0;
    u64 a = FUN_71038f4000(L, 1, 0);
    u32 r = (**(u32(**)(u64,u64))(*(u64*)mod + 0x410))(mod, a);
    u32* s = *(u32**)(L + 0x10); s[0] = r; s[2] = 3;
    *(u64*)(L + 0x10) += 0x10; return 1;
}

// 0x7102030890 (336 bytes) — u32 return, vtable[0x418]
u64 FUN_7102030890(u64 L) {
    u64 acc = *(u64*)(L - 8); if (!acc) return 0;
    u64 mod = *(u64*)(acc + 0x40); if (!mod) return 0;
    u64 a = FUN_71038f4000(L, 1, 0);
    u32 r = (**(u32(**)(u64,u64))(*(u64*)mod + 0x418))(mod, a);
    u32* s = *(u32**)(L + 0x10); s[0] = r; s[2] = 3;
    *(u64*)(L + 0x10) += 0x10; return 1;
}

// 0x71020309e0 (352 bytes) — u32 return, vtable[0x420]
u64 FUN_71020309e0(u64 L) {
    u64 acc = *(u64*)(L - 8); if (!acc) return 0;
    u64 mod = *(u64*)(acc + 0x40); if (!mod) return 0;
    u64 a = FUN_71038f4000(L, 1, 0);
    u32 r = (**(u32(**)(u64,u64))(*(u64*)mod + 0x420))(mod, a);
    u32* s = *(u32**)(L + 0x10); s[0] = r; s[2] = 3;
    *(u64*)(L + 0x10) += 0x10; return 1;
}

// 0x7102030b40 (336 bytes) — u32 return, vtable[0x430]
u64 FUN_7102030b40(u64 L) {
    u64 acc = *(u64*)(L - 8); if (!acc) return 0;
    u64 mod = *(u64*)(acc + 0x40); if (!mod) return 0;
    u64 a = FUN_71038f4000(L, 1, 0);
    u32 r = (**(u32(**)(u64,u64))(*(u64*)mod + 0x430))(mod, a);
    u32* s = *(u32**)(L + 0x10); s[0] = r; s[2] = 3;
    *(u64*)(L + 0x10) += 0x10; return 1;
}

// 0x7102030c90 (336 bytes) — u32 return, vtable[0x438]
u64 FUN_7102030c90(u64 L) {
    u64 acc = *(u64*)(L - 8); if (!acc) return 0;
    u64 mod = *(u64*)(acc + 0x40); if (!mod) return 0;
    u64 a = FUN_71038f4000(L, 1, 0);
    u32 r = (**(u32(**)(u64,u64))(*(u64*)mod + 0x438))(mod, a);
    u32* s = *(u32**)(L + 0x10); s[0] = r; s[2] = 3;
    *(u64*)(L + 0x10) += 0x10; return 1;
}

// 0x7102030de0 (352 bytes) — u32 return, vtable[0x440]
u64 FUN_7102030de0(u64 L) {
    u64 acc = *(u64*)(L - 8); if (!acc) return 0;
    u64 mod = *(u64*)(acc + 0x40); if (!mod) return 0;
    u64 a = FUN_71038f4000(L, 1, 0);
    u32 r = (**(u32(**)(u64,u64))(*(u64*)mod + 0x440))(mod, a);
    u32* s = *(u32**)(L + 0x10); s[0] = r; s[2] = 3;
    *(u64*)(L + 0x10) += 0x10; return 1;
}

// 0x7102031560 (336 bytes) — float(0x13) return, vtable[0x478]
u64 FUN_7102031560(u64 L) {
    u64 acc = *(u64*)(L - 8); if (!acc) return 0;
    u64 mod = *(u64*)(acc + 0x40); if (!mod) return 0;
    u64 a = FUN_71038f4000(L, 1, 0);
    u64 r = (**(u64(**)(u64,u64))(*(u64*)mod + 0x478))(mod, a);
    u64* s = *(u64**)(L + 0x10);
    *s = r & 0xff; *(u32*)(s + 1) = 0x13;
    *(u64*)(L + 0x10) += 0x10; return 1;
}

// 0x71020316b0 (368 bytes) — u32 return, vtable[0x480]
u64 FUN_71020316b0(u64 L) {
    u64 acc = *(u64*)(L - 8); if (!acc) return 0;
    u64 mod = *(u64*)(acc + 0x40); if (!mod) return 0;
    u64 a = FUN_71038f4000(L, 1, 0);
    u32 r = (**(u32(**)(u64,u64))(*(u64*)mod + 0x480))(mod, a);
    u32* s = *(u32**)(L + 0x10); s[0] = r; s[2] = 3;
    *(u64*)(L + 0x10) += 0x10; return 1;
}

// 0x7102031820 (336 bytes) — bool return, vtable[0x4a0]
u64 FUN_7102031820(u64 L) {
    u64 acc = *(u64*)(L - 8); if (!acc) return 0;
    u64 mod = *(u64*)(acc + 0x40); if (!mod) return 0;
    u64 a = FUN_71038f4000(L, 1, 0);
    u32 r = (**(u32(**)(u64,u64))(*(u64*)mod + 0x4a0))(mod, a);
    u32* s = *(u32**)(L + 0x10); s[0] = r & 1; s[2] = 1;
    *(u64*)(L + 0x10) += 0x10; return 1;
}

// 0x7102031dd0 (336 bytes) — bool return, vtable[0x4e8]
u64 FUN_7102031dd0(u64 L) {
    u64 acc = *(u64*)(L - 8); if (!acc) return 0;
    u64 mod = *(u64*)(acc + 0x40); if (!mod) return 0;
    u64 a = FUN_71038f4000(L, 1, 0);
    u32 r = (**(u32(**)(u64,u64))(*(u64*)mod + 0x4e8))(mod, a);
    u32* s = *(u32**)(L + 0x10); s[0] = r & 1; s[2] = 1;
    *(u64*)(L + 0x10) += 0x10; return 1;
}

// 0x710203ace0 (432 bytes) — void dispatch, vtable[0x788]
u64 FUN_710203ace0(u64 L) {
    u64 acc = *(u64*)(L - 8); if (!acc) return 0;
    u64 mod = *(u64*)(acc + 0x40); if (!mod) return 0;
    u64 a = FUN_71038f4000(L, 1, 0);
    (**(void(**)(u64,u64))(*(u64*)mod + 0x788))(mod, a);
    return 0;
}

// 0x710203b0e0 (496 bytes) — u32 return, vtable[0x7b0]
u64 FUN_710203b0e0(u64 L) {
    u64 acc = *(u64*)(L - 8); if (!acc) return 0;
    u64 mod = *(u64*)(acc + 0x40); if (!mod) return 0;
    u64 a = FUN_71038f4000(L, 1, 0);
    u32 r = (**(u32(**)(u64,u64))(*(u64*)mod + 0x7b0))(mod, a);
    u32* s = *(u32**)(L + 0x10); s[0] = r; s[2] = 3;
    *(u64*)(L + 0x10) += 0x10; return 1;
}

// ---- Module offset 0x50 (WorkModule) ----------------------------------------

// 0x7102043b70 (464 bytes) — u32 return, vtable[0x60]
u64 FUN_7102043b70(u64 L) {
    u64 acc = *(u64*)(L - 8); if (!acc) return 0;
    u64 mod = *(u64*)(acc + 0x50); if (!mod) return 0;
    u64 a = FUN_71038f4000(L, 1, 0);
    u32 r = (**(u32(**)(u64,u64))(*(u64*)mod + 0x60))(mod, a);
    u32* s = *(u32**)(L + 0x10); s[0] = r; s[2] = 3;
    *(u64*)(L + 0x10) += 0x10; return 1;
}

// ---- Module offset 0x98 (ArticleModule) ------------------------------------

// 0x710203de90 (304 bytes) — void dispatch, vtable[0x88]
u64 FUN_710203de90(u64 L) {
    u64 acc = *(u64*)(L - 8); if (!acc) return 0;
    u64 mod = *(u64*)(acc + 0x98); if (!mod) return 0;
    u64 a = FUN_71038f4000(L, 1, 0);
    (**(void(**)(u64,u64))(*(u64*)mod + 0x88))(mod, a);
    return 0;
}

// 0x710203e6d0 (352 bytes) — float(0x13) return, vtable[0xd8]
u64 FUN_710203e6d0(u64 L) {
    u64 acc = *(u64*)(L - 8); if (!acc) return 0;
    u64 mod = *(u64*)(acc + 0x98); if (!mod) return 0;
    u64 a = FUN_71038f4000(L, 1, 0);
    u64 r = (**(u64(**)(u64,u64))(*(u64*)mod + 0xd8))(mod, a);
    u64* s = *(u64**)(L + 0x10);
    *s = r & 0xff; *(u32*)(s + 1) = 0x13;
    *(u64*)(L + 0x10) += 0x10; return 1;
}

// ---- Module offset 0x100 (ShieldModule) ------------------------------------

// 0x7102042070 (528 bytes) — void dispatch, vtable[0xc8]
u64 FUN_7102042070(u64 L) {
    u64 acc = *(u64*)(L - 8); if (!acc) return 0;
    u64 mod = *(u64*)(acc + 0x100); if (!mod) return 0;
    u64 a = FUN_71038f4000(L, 1, 0);
    (**(void(**)(u64,u64))(*(u64*)mod + 0xc8))(mod, a);
    return 0;
}

// 0x7102042280 (304 bytes) — void dispatch, vtable[0xe0]
u64 FUN_7102042280(u64 L) {
    u64 acc = *(u64*)(L - 8); if (!acc) return 0;
    u64 mod = *(u64*)(acc + 0x100); if (!mod) return 0;
    u64 a = FUN_71038f4000(L, 1, 0);
    (**(void(**)(u64,u64))(*(u64*)mod + 0xe0))(mod, a);
    return 0;
}

// 0x7102043520 (304 bytes) — void dispatch, vtable[0x160]
u64 FUN_7102043520(u64 L) {
    u64 acc = *(u64*)(L - 8); if (!acc) return 0;
    u64 mod = *(u64*)(acc + 0x100); if (!mod) return 0;
    u64 a = FUN_71038f4000(L, 1, 0);
    (**(void(**)(u64,u64))(*(u64*)mod + 0x160))(mod, a);
    return 0;
}

// ---- Module offset 0x180 (MotionAnimcmdModule) ------------------------------

// 0x7102040c10 (304 bytes) — void dispatch, vtable[0xb8]
u64 FUN_7102040c10(u64 L) {
    u64 acc = *(u64*)(L - 8); if (!acc) return 0;
    u64 mod = *(u64*)(acc + 0x180); if (!mod) return 0;
    u64 a = FUN_71038f4000(L, 1, 0);
    (**(void(**)(u64,u64))(*(u64*)mod + 0xb8))(mod, a);
    return 0;
}
