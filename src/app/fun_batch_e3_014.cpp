#include "types.h"

// MEDIUM-tier FUN_* functions — 0x7102 address range, batch e3-014
// Pool-e worker: lua_bind dispatch functions 0x7102002fc0–0x7102027fb0
// Pattern: load module from *(*(L-8) + MODULE_OFF), call vtable[VTBL_OFF]

extern "C" u64 FUN_71038f4000(u64, int, int);

// ---- Module offset 0x30 (ControlModule) ------------------------------------

// 0x7102002fc0 (512 bytes) — void dispatch, vtable[0xc8]
u64 FUN_7102002fc0(u64 L) {
    u64 acc = *(u64*)(L - 8); if (!acc) return 0;
    u64 mod = *(u64*)(acc + 0x30); if (!mod) return 0;
    u64 a = FUN_71038f4000(L, 1, 0);
    (**(void(**)(u64,u64))(*(u64*)mod + 0xc8))(mod, a);
    return 0;
}

// 0x71020034f0 (432 bytes) — void dispatch, vtable[0x100]
u64 FUN_71020034f0(u64 L) {
    u64 acc = *(u64*)(L - 8); if (!acc) return 0;
    u64 mod = *(u64*)(acc + 0x30); if (!mod) return 0;
    u64 a = FUN_71038f4000(L, 1, 0);
    (**(void(**)(u64,u64))(*(u64*)mod + 0x100))(mod, a);
    return 0;
}

// 0x7102005360 (336 bytes) — float(0x13) return, vtable[0x228]
u64 FUN_7102005360(u64 L) {
    u64 acc = *(u64*)(L - 8); if (!acc) return 0;
    u64 mod = *(u64*)(acc + 0x30); if (!mod) return 0;
    u64 a = FUN_71038f4000(L, 1, 0);
    u64 r = (**(u64(**)(u64,u64))(*(u64*)mod + 0x228))(mod, a);
    u64* s = *(u64**)(L + 0x10);
    *s = r & 0xff;
    *(u32*)(s + 1) = 0x13;
    *(u64*)(L + 0x10) += 0x10;
    return 1;
}

// 0x71020058a0 (336 bytes) — bool return, vtable[0x250]
u64 FUN_71020058a0(u64 L) {
    u64 acc = *(u64*)(L - 8); if (!acc) return 0;
    u64 mod = *(u64*)(acc + 0x30); if (!mod) return 0;
    u64 a = FUN_71038f4000(L, 1, 0);
    u32 r = (**(u32(**)(u64,u64))(*(u64*)mod + 0x250))(mod, a);
    u32* s = *(u32**)(L + 0x10); s[0] = r & 1; s[2] = 1;
    *(u64*)(L + 0x10) += 0x10; return 1;
}

// 0x71020059f0 (336 bytes) — bool return, vtable[0x258]
u64 FUN_71020059f0(u64 L) {
    u64 acc = *(u64*)(L - 8); if (!acc) return 0;
    u64 mod = *(u64*)(acc + 0x30); if (!mod) return 0;
    u64 a = FUN_71038f4000(L, 1, 0);
    u32 r = (**(u32(**)(u64,u64))(*(u64*)mod + 0x258))(mod, a);
    u32* s = *(u32**)(L + 0x10); s[0] = r & 1; s[2] = 1;
    *(u64*)(L + 0x10) += 0x10; return 1;
}

// 0x7102005b40 (336 bytes) — bool return, vtable[0x260]
u64 FUN_7102005b40(u64 L) {
    u64 acc = *(u64*)(L - 8); if (!acc) return 0;
    u64 mod = *(u64*)(acc + 0x30); if (!mod) return 0;
    u64 a = FUN_71038f4000(L, 1, 0);
    u32 r = (**(u32(**)(u64,u64))(*(u64*)mod + 0x260))(mod, a);
    u32* s = *(u32**)(L + 0x10); s[0] = r & 1; s[2] = 1;
    *(u64*)(L + 0x10) += 0x10; return 1;
}

// 0x7102005c90 (336 bytes) — bool return, vtable[0x268]
u64 FUN_7102005c90(u64 L) {
    u64 acc = *(u64*)(L - 8); if (!acc) return 0;
    u64 mod = *(u64*)(acc + 0x30); if (!mod) return 0;
    u64 a = FUN_71038f4000(L, 1, 0);
    u32 r = (**(u32(**)(u64,u64))(*(u64*)mod + 0x268))(mod, a);
    u32* s = *(u32**)(L + 0x10); s[0] = r & 1; s[2] = 1;
    *(u64*)(L + 0x10) += 0x10; return 1;
}

// 0x7102005de0 (336 bytes) — bool return, vtable[0x270]
u64 FUN_7102005de0(u64 L) {
    u64 acc = *(u64*)(L - 8); if (!acc) return 0;
    u64 mod = *(u64*)(acc + 0x30); if (!mod) return 0;
    u64 a = FUN_71038f4000(L, 1, 0);
    u32 r = (**(u32(**)(u64,u64))(*(u64*)mod + 0x270))(mod, a);
    u32* s = *(u32**)(L + 0x10); s[0] = r & 1; s[2] = 1;
    *(u64*)(L + 0x10) += 0x10; return 1;
}

// 0x71020063c0 (336 bytes) — bool return, vtable[0x298]
u64 FUN_71020063c0(u64 L) {
    u64 acc = *(u64*)(L - 8); if (!acc) return 0;
    u64 mod = *(u64*)(acc + 0x30); if (!mod) return 0;
    u64 a = FUN_71038f4000(L, 1, 0);
    u32 r = (**(u32(**)(u64,u64))(*(u64*)mod + 0x298))(mod, a);
    u32* s = *(u32**)(L + 0x10); s[0] = r & 1; s[2] = 1;
    *(u64*)(L + 0x10) += 0x10; return 1;
}

// 0x710200a340 (304 bytes) — void dispatch, vtable[0x488]
u64 FUN_710200a340(u64 L) {
    u64 acc = *(u64*)(L - 8); if (!acc) return 0;
    u64 mod = *(u64*)(acc + 0x30); if (!mod) return 0;
    u64 a = FUN_71038f4000(L, 1, 0);
    (**(void(**)(u64,u64))(*(u64*)mod + 0x488))(mod, a);
    return 0;
}

// 0x710200a470 (304 bytes) — void dispatch, vtable[0x490]
u64 FUN_710200a470(u64 L) {
    u64 acc = *(u64*)(L - 8); if (!acc) return 0;
    u64 mod = *(u64*)(acc + 0x30); if (!mod) return 0;
    u64 a = FUN_71038f4000(L, 1, 0);
    (**(void(**)(u64,u64))(*(u64*)mod + 0x490))(mod, a);
    return 0;
}

// ---- Module offset 0xa0 (AttackModule) -------------------------------------

// 0x710200b250 (432 bytes) — void dispatch, vtable[0x48]
u64 FUN_710200b250(u64 L) {
    u64 acc = *(u64*)(L - 8); if (!acc) return 0;
    u64 mod = *(u64*)(acc + 0xa0); if (!mod) return 0;
    u64 a = FUN_71038f4000(L, 1, 0);
    (**(void(**)(u64,u64))(*(u64*)mod + 0x48))(mod, a);
    return 0;
}

// ---- Module offset 0x90 (StopModule) ---------------------------------------

// 0x710200c4d0 (336 bytes) — u32 return, vtable[0xc8]
u64 FUN_710200c4d0(u64 L) {
    u64 acc = *(u64*)(L - 8); if (!acc) return 0;
    u64 mod = *(u64*)(acc + 0x90); if (!mod) return 0;
    u64 a = FUN_71038f4000(L, 1, 0);
    u32 r = (**(u32(**)(u64,u64))(*(u64*)mod + 0xc8))(mod, a);
    u32* s = *(u32**)(L + 0x10); s[0] = r; s[2] = 3;
    *(u64*)(L + 0x10) += 0x10; return 1;
}

// 0x710200c620 (336 bytes) — u32 return, vtable[0xd0]
u64 FUN_710200c620(u64 L) {
    u64 acc = *(u64*)(L - 8); if (!acc) return 0;
    u64 mod = *(u64*)(acc + 0x90); if (!mod) return 0;
    u64 a = FUN_71038f4000(L, 1, 0);
    u32 r = (**(u32(**)(u64,u64))(*(u64*)mod + 0xd0))(mod, a);
    u32* s = *(u32**)(L + 0x10); s[0] = r; s[2] = 3;
    *(u64*)(L + 0x10) += 0x10; return 1;
}

// 0x710200c770 (336 bytes) — u32 return, vtable[0xd8]
u64 FUN_710200c770(u64 L) {
    u64 acc = *(u64*)(L - 8); if (!acc) return 0;
    u64 mod = *(u64*)(acc + 0x90); if (!mod) return 0;
    u64 a = FUN_71038f4000(L, 1, 0);
    u32 r = (**(u32(**)(u64,u64))(*(u64*)mod + 0xd8))(mod, a);
    u32* s = *(u32**)(L + 0x10); s[0] = r; s[2] = 3;
    *(u64*)(L + 0x10) += 0x10; return 1;
}

// ---- Module offset 0x128 (CancelModule) ------------------------------------

// 0x710201a410 (432 bytes) — void dispatch, vtable[0x90]
u64 FUN_710201a410(u64 L) {
    u64 acc = *(u64*)(L - 8); if (!acc) return 0;
    u64 mod = *(u64*)(acc + 0x128); if (!mod) return 0;
    u64 a = FUN_71038f4000(L, 1, 0);
    (**(void(**)(u64,u64))(*(u64*)mod + 0x90))(mod, a);
    return 0;
}

// 0x710201b140 (432 bytes) — void dispatch, vtable[0xb0]
u64 FUN_710201b140(u64 L) {
    u64 acc = *(u64*)(L - 8); if (!acc) return 0;
    u64 mod = *(u64*)(acc + 0x128); if (!mod) return 0;
    u64 a = FUN_71038f4000(L, 1, 0);
    (**(void(**)(u64,u64))(*(u64*)mod + 0xb0))(mod, a);
    return 0;
}

// 0x710201e600 (336 bytes) — bool return, vtable[0x188]
u64 FUN_710201e600(u64 L) {
    u64 acc = *(u64*)(L - 8); if (!acc) return 0;
    u64 mod = *(u64*)(acc + 0x128); if (!mod) return 0;
    u64 a = FUN_71038f4000(L, 1, 0);
    u32 r = (**(u32(**)(u64,u64))(*(u64*)mod + 0x188))(mod, a);
    u32* s = *(u32**)(L + 0x10); s[0] = r & 1; s[2] = 1;
    *(u64*)(L + 0x10) += 0x10; return 1;
}

// 0x71020217e0 (432 bytes) — void dispatch, vtable[0x238]
u64 FUN_71020217e0(u64 L) {
    u64 acc = *(u64*)(L - 8); if (!acc) return 0;
    u64 mod = *(u64*)(acc + 0x128); if (!mod) return 0;
    u64 a = FUN_71038f4000(L, 1, 0);
    (**(void(**)(u64,u64))(*(u64*)mod + 0x238))(mod, a);
    return 0;
}

// 0x7102021a90 (336 bytes) — bool return, vtable[0x250]
u64 FUN_7102021a90(u64 L) {
    u64 acc = *(u64*)(L - 8); if (!acc) return 0;
    u64 mod = *(u64*)(acc + 0x128); if (!mod) return 0;
    u64 a = FUN_71038f4000(L, 1, 0);
    u32 r = (**(u32(**)(u64,u64))(*(u64*)mod + 0x250))(mod, a);
    u32* s = *(u32**)(L + 0x10); s[0] = r & 1; s[2] = 1;
    *(u64*)(L + 0x10) += 0x10; return 1;
}

// 0x7102024650 (432 bytes) — void dispatch, vtable[0x390]
u64 FUN_7102024650(u64 L) {
    u64 acc = *(u64*)(L - 8); if (!acc) return 0;
    u64 mod = *(u64*)(acc + 0x128); if (!mod) return 0;
    u64 a = FUN_71038f4000(L, 1, 0);
    (**(void(**)(u64,u64))(*(u64*)mod + 0x390))(mod, a);
    return 0;
}

// 0x7102025250 (432 bytes) — void dispatch, vtable[0x438]
u64 FUN_7102025250(u64 L) {
    u64 acc = *(u64*)(L - 8); if (!acc) return 0;
    u64 mod = *(u64*)(acc + 0x128); if (!mod) return 0;
    u64 a = FUN_71038f4000(L, 1, 0);
    (**(void(**)(u64,u64))(*(u64*)mod + 0x438))(mod, a);
    return 0;
}

// ---- Module offset 0x140 (EffectModule) ------------------------------------

// 0x7102027cb0 (304 bytes) — void dispatch, vtable[0x58]
u64 FUN_7102027cb0(u64 L) {
    u64 acc = *(u64*)(L - 8); if (!acc) return 0;
    u64 mod = *(u64*)(acc + 0x140); if (!mod) return 0;
    u64 a = FUN_71038f4000(L, 1, 0);
    (**(void(**)(u64,u64))(*(u64*)mod + 0x58))(mod, a);
    return 0;
}

// 0x7102027fb0 (336 bytes) — bool return, vtable[0x78]
u64 FUN_7102027fb0(u64 L) {
    u64 acc = *(u64*)(L - 8); if (!acc) return 0;
    u64 mod = *(u64*)(acc + 0x140); if (!mod) return 0;
    u64 a = FUN_71038f4000(L, 1, 0);
    u32 r = (**(u32(**)(u64,u64))(*(u64*)mod + 0x78))(mod, a);
    u32* s = *(u32**)(L + 0x10); s[0] = r & 1; s[2] = 1;
    *(u64*)(L + 0x10) += 0x10; return 1;
}
