#include "types.h"

// MEDIUM-tier FUN_* functions — 0x7102 address range, batch e3-016
// Pool-e worker: lua_bind dispatch functions 0x7102043d70–0x710204c140
// Pattern: get module from *(*(L-8) + MODULE_OFF), call vtable[VTBL_OFF]

extern "C" u64 FUN_71038f4000(u64, int, int);

// ---- Module offset 0x50 (WorkModule) ----------------------------------------

// 0x7102043d70 (304 bytes) — void dispatch, vtable[0x98]
u64 FUN_7102043d70(u64 L) {
    u64 acc = *(u64*)(L - 8); if (!acc) return 0;
    u64 mod = *(u64*)(acc + 0x50); if (!mod) return 0;
    u64 a = FUN_71038f4000(L, 1, 0);
    (**(void(**)(u64,u64))(*(u64*)mod + 0x98))(mod, a);
    return 0;
}

// 0x71020441e0 (368 bytes) — u32 return, vtable[0xc0]
u64 FUN_71020441e0(u64 L) {
    u64 acc = *(u64*)(L - 8); if (!acc) return 0;
    u64 mod = *(u64*)(acc + 0x50); if (!mod) return 0;
    u64 a = FUN_71038f4000(L, 1, 0);
    u32 r = (**(u32(**)(u64,u64))(*(u64*)mod + 0xc0))(mod, a);
    u32* s = *(u32**)(L + 0x10); s[0] = r; s[2] = 3;
    *(u64*)(L + 0x10) += 0x10; return 1;
}

// 0x7102044350 (336 bytes) — u32 return, vtable[0xc8]
u64 FUN_7102044350(u64 L) {
    u64 acc = *(u64*)(L - 8); if (!acc) return 0;
    u64 mod = *(u64*)(acc + 0x50); if (!mod) return 0;
    u64 a = FUN_71038f4000(L, 1, 0);
    u32 r = (**(u32(**)(u64,u64))(*(u64*)mod + 0xc8))(mod, a);
    u32* s = *(u32**)(L + 0x10); s[0] = r; s[2] = 3;
    *(u64*)(L + 0x10) += 0x10; return 1;
}

// 0x71020444a0 (336 bytes) — u32 return, vtable[0xd0]
u64 FUN_71020444a0(u64 L) {
    u64 acc = *(u64*)(L - 8); if (!acc) return 0;
    u64 mod = *(u64*)(acc + 0x50); if (!mod) return 0;
    u64 a = FUN_71038f4000(L, 1, 0);
    u32 r = (**(u32(**)(u64,u64))(*(u64*)mod + 0xd0))(mod, a);
    u32* s = *(u32**)(L + 0x10); s[0] = r; s[2] = 3;
    *(u64*)(L + 0x10) += 0x10; return 1;
}

// 0x71020445f0 (336 bytes) — u32 return, vtable[0xd8]
u64 FUN_71020445f0(u64 L) {
    u64 acc = *(u64*)(L - 8); if (!acc) return 0;
    u64 mod = *(u64*)(acc + 0x50); if (!mod) return 0;
    u64 a = FUN_71038f4000(L, 1, 0);
    u32 r = (**(u32(**)(u64,u64))(*(u64*)mod + 0xd8))(mod, a);
    u32* s = *(u32**)(L + 0x10); s[0] = r; s[2] = 3;
    *(u64*)(L + 0x10) += 0x10; return 1;
}

// 0x7102045950 (528 bytes) — void dispatch, vtable[0x118]
u64 FUN_7102045950(u64 L) {
    u64 acc = *(u64*)(L - 8); if (!acc) return 0;
    u64 mod = *(u64*)(acc + 0x50); if (!mod) return 0;
    u64 a = FUN_71038f4000(L, 1, 0);
    (**(void(**)(u64,u64))(*(u64*)mod + 0x118))(mod, a);
    return 0;
}

// 0x7102045b60 (304 bytes) — void dispatch, vtable[0x128]
u64 FUN_7102045b60(u64 L) {
    u64 acc = *(u64*)(L - 8); if (!acc) return 0;
    u64 mod = *(u64*)(acc + 0x50); if (!mod) return 0;
    u64 a = FUN_71038f4000(L, 1, 0);
    (**(void(**)(u64,u64))(*(u64*)mod + 0x128))(mod, a);
    return 0;
}

// 0x7102045c90 (304 bytes) — void dispatch, vtable[0x130]
u64 FUN_7102045c90(u64 L) {
    u64 acc = *(u64*)(L - 8); if (!acc) return 0;
    u64 mod = *(u64*)(acc + 0x50); if (!mod) return 0;
    u64 a = FUN_71038f4000(L, 1, 0);
    (**(void(**)(u64,u64))(*(u64*)mod + 0x130))(mod, a);
    return 0;
}

// 0x7102045dc0 (336 bytes) — bool return, vtable[0x138]
u64 FUN_7102045dc0(u64 L) {
    u64 acc = *(u64*)(L - 8); if (!acc) return 0;
    u64 mod = *(u64*)(acc + 0x50); if (!mod) return 0;
    u64 a = FUN_71038f4000(L, 1, 0);
    u32 r = (**(u32(**)(u64,u64))(*(u64*)mod + 0x138))(mod, a);
    u32* s = *(u32**)(L + 0x10); s[0] = r & 1; s[2] = 1;
    *(u64*)(L + 0x10) += 0x10; return 1;
}

// 0x7102045f10 (304 bytes) — void dispatch, vtable[0x140]
u64 FUN_7102045f10(u64 L) {
    u64 acc = *(u64*)(L - 8); if (!acc) return 0;
    u64 mod = *(u64*)(acc + 0x50); if (!mod) return 0;
    u64 a = FUN_71038f4000(L, 1, 0);
    (**(void(**)(u64,u64))(*(u64*)mod + 0x140))(mod, a);
    return 0;
}

// 0x7102046040 (304 bytes) — void dispatch, vtable[0x148]
u64 FUN_7102046040(u64 L) {
    u64 acc = *(u64*)(L - 8); if (!acc) return 0;
    u64 mod = *(u64*)(acc + 0x50); if (!mod) return 0;
    u64 a = FUN_71038f4000(L, 1, 0);
    (**(void(**)(u64,u64))(*(u64*)mod + 0x148))(mod, a);
    return 0;
}

// ---- Module offset 0xb8 (ComboModule) ---------------------------------------

// 0x7102048ef0 (336 bytes) — bool return, vtable[0x78]
u64 FUN_7102048ef0(u64 L) {
    u64 acc = *(u64*)(L - 8); if (!acc) return 0;
    u64 mod = *(u64*)(acc + 0xb8); if (!mod) return 0;
    u64 a = FUN_71038f4000(L, 1, 0);
    u32 r = (**(u32(**)(u64,u64))(*(u64*)mod + 0x78))(mod, a);
    u32* s = *(u32**)(L + 0x10); s[0] = r & 1; s[2] = 1;
    *(u64*)(L + 0x10) += 0x10; return 1;
}

// 0x7102049040 (496 bytes) — float(0x13) return, vtable[0x80]
u64 FUN_7102049040(u64 L) {
    u64 acc = *(u64*)(L - 8); if (!acc) return 0;
    u64 mod = *(u64*)(acc + 0xb8); if (!mod) return 0;
    u64 a = FUN_71038f4000(L, 1, 0);
    u64 r = (**(u64(**)(u64,u64))(*(u64*)mod + 0x80))(mod, a);
    u64* s = *(u64**)(L + 0x10);
    *s = r & 0xff; *(u32*)(s + 1) = 0x13;
    *(u64*)(L + 0x10) += 0x10; return 1;
}

// 0x7102049230 (336 bytes) — bool return, vtable[0x88]
u64 FUN_7102049230(u64 L) {
    u64 acc = *(u64*)(L - 8); if (!acc) return 0;
    u64 mod = *(u64*)(acc + 0xb8); if (!mod) return 0;
    u64 a = FUN_71038f4000(L, 1, 0);
    u32 r = (**(u32(**)(u64,u64))(*(u64*)mod + 0x88))(mod, a);
    u32* s = *(u32**)(L + 0x10); s[0] = r & 1; s[2] = 1;
    *(u64*)(L + 0x10) += 0x10; return 1;
}

// 0x7102049380 (336 bytes) — float(0x13) return, vtable[0x90]
u64 FUN_7102049380(u64 L) {
    u64 acc = *(u64*)(L - 8); if (!acc) return 0;
    u64 mod = *(u64*)(acc + 0xb8); if (!mod) return 0;
    u64 a = FUN_71038f4000(L, 1, 0);
    u64 r = (**(u64(**)(u64,u64))(*(u64*)mod + 0x90))(mod, a);
    u64* s = *(u64**)(L + 0x10);
    *s = r & 0xff; *(u32*)(s + 1) = 0x13;
    *(u64*)(L + 0x10) += 0x10; return 1;
}

// 0x710204a030 (352 bytes) — float(0x13) return, vtable[0xd0]
u64 FUN_710204a030(u64 L) {
    u64 acc = *(u64*)(L - 8); if (!acc) return 0;
    u64 mod = *(u64*)(acc + 0xb8); if (!mod) return 0;
    u64 a = FUN_71038f4000(L, 1, 0);
    u64 r = (**(u64(**)(u64,u64))(*(u64*)mod + 0xd0))(mod, a);
    u64* s = *(u64**)(L + 0x10);
    *s = r & 0xff; *(u32*)(s + 1) = 0x13;
    *(u64*)(L + 0x10) += 0x10; return 1;
}

// 0x710204a190 (336 bytes) — bool return, vtable[0xd8]
u64 FUN_710204a190(u64 L) {
    u64 acc = *(u64*)(L - 8); if (!acc) return 0;
    u64 mod = *(u64*)(acc + 0xb8); if (!mod) return 0;
    u64 a = FUN_71038f4000(L, 1, 0);
    u32 r = (**(u32(**)(u64,u64))(*(u64*)mod + 0xd8))(mod, a);
    u32* s = *(u32**)(L + 0x10); s[0] = r & 1; s[2] = 1;
    *(u64*)(L + 0x10) += 0x10; return 1;
}

// 0x710204b530 (336 bytes) — u32 return, vtable[0x178]
u64 FUN_710204b530(u64 L) {
    u64 acc = *(u64*)(L - 8); if (!acc) return 0;
    u64 mod = *(u64*)(acc + 0xb8); if (!mod) return 0;
    u64 a = FUN_71038f4000(L, 1, 0);
    u32 r = (**(u32(**)(u64,u64))(*(u64*)mod + 0x178))(mod, a);
    u32* s = *(u32**)(L + 0x10); s[0] = r; s[2] = 3;
    *(u64*)(L + 0x10) += 0x10; return 1;
}

// 0x710204b680 (336 bytes) — u32 return, vtable[0x180]
u64 FUN_710204b680(u64 L) {
    u64 acc = *(u64*)(L - 8); if (!acc) return 0;
    u64 mod = *(u64*)(acc + 0xb8); if (!mod) return 0;
    u64 a = FUN_71038f4000(L, 1, 0);
    u32 r = (**(u32(**)(u64,u64))(*(u64*)mod + 0x180))(mod, a);
    u32* s = *(u32**)(L + 0x10); s[0] = r; s[2] = 3;
    *(u64*)(L + 0x10) += 0x10; return 1;
}

// 0x710204b7d0 (336 bytes) — u32 return, vtable[0x188]
u64 FUN_710204b7d0(u64 L) {
    u64 acc = *(u64*)(L - 8); if (!acc) return 0;
    u64 mod = *(u64*)(acc + 0xb8); if (!mod) return 0;
    u64 a = FUN_71038f4000(L, 1, 0);
    u32 r = (**(u32(**)(u64,u64))(*(u64*)mod + 0x188))(mod, a);
    u32* s = *(u32**)(L + 0x10); s[0] = r; s[2] = 3;
    *(u64*)(L + 0x10) += 0x10; return 1;
}

// 0x710204b920 (336 bytes) — float(0x13) return, vtable[0x190]
u64 FUN_710204b920(u64 L) {
    u64 acc = *(u64*)(L - 8); if (!acc) return 0;
    u64 mod = *(u64*)(acc + 0xb8); if (!mod) return 0;
    u64 a = FUN_71038f4000(L, 1, 0);
    u64 r = (**(u64(**)(u64,u64))(*(u64*)mod + 0x190))(mod, a);
    u64* s = *(u64**)(L + 0x10);
    *s = r & 0xff; *(u32*)(s + 1) = 0x13;
    *(u64*)(L + 0x10) += 0x10; return 1;
}

// 0x710204ba70 (336 bytes) — float(0x13) return, vtable[0x198]
u64 FUN_710204ba70(u64 L) {
    u64 acc = *(u64*)(L - 8); if (!acc) return 0;
    u64 mod = *(u64*)(acc + 0xb8); if (!mod) return 0;
    u64 a = FUN_71038f4000(L, 1, 0);
    u64 r = (**(u64(**)(u64,u64))(*(u64*)mod + 0x198))(mod, a);
    u64* s = *(u64**)(L + 0x10);
    *s = r & 0xff; *(u32*)(s + 1) = 0x13;
    *(u64*)(L + 0x10) += 0x10; return 1;
}

// 0x710204bbc0 (336 bytes) — float(0x13) return, vtable[0x1a0]
u64 FUN_710204bbc0(u64 L) {
    u64 acc = *(u64*)(L - 8); if (!acc) return 0;
    u64 mod = *(u64*)(acc + 0xb8); if (!mod) return 0;
    u64 a = FUN_71038f4000(L, 1, 0);
    u64 r = (**(u64(**)(u64,u64))(*(u64*)mod + 0x1a0))(mod, a);
    u64* s = *(u64**)(L + 0x10);
    *s = r & 0xff; *(u32*)(s + 1) = 0x13;
    *(u64*)(L + 0x10) += 0x10; return 1;
}

// 0x710204bff0 (336 bytes) — float(0x13) return, vtable[0x1b8]
u64 FUN_710204bff0(u64 L) {
    u64 acc = *(u64*)(L - 8); if (!acc) return 0;
    u64 mod = *(u64*)(acc + 0xb8); if (!mod) return 0;
    u64 a = FUN_71038f4000(L, 1, 0);
    u64 r = (**(u64(**)(u64,u64))(*(u64*)mod + 0x1b8))(mod, a);
    u64* s = *(u64**)(L + 0x10);
    *s = r & 0xff; *(u32*)(s + 1) = 0x13;
    *(u64*)(L + 0x10) += 0x10; return 1;
}

// 0x710204c140 (336 bytes) — bool return, vtable[0x1c0]
u64 FUN_710204c140(u64 L) {
    u64 acc = *(u64*)(L - 8); if (!acc) return 0;
    u64 mod = *(u64*)(acc + 0xb8); if (!mod) return 0;
    u64 a = FUN_71038f4000(L, 1, 0);
    u32 r = (**(u32(**)(u64,u64))(*(u64*)mod + 0x1c0))(mod, a);
    u32* s = *(u32**)(L + 0x10); s[0] = r & 1; s[2] = 1;
    *(u64*)(L + 0x10) += 0x10; return 1;
}
