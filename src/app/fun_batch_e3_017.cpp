#include "types.h"

// MEDIUM-tier FUN_* functions — 0x7102 address range, batch e3-017
// Pool-e worker: lua_bind dispatch functions 0x710204c700–0x710204f210
// Pattern: load module from *(*(L-8) + MODULE_OFF), call vtable[VTBL_OFF]

extern "C" u64 FUN_71038f4000(u64, int, int);

// ---- Module offset 0xb8 (ComboModule) --------------------------------------

// 0x710204c700 (336 bytes) — u32 return, vtable[0x1e0]
u64 FUN_710204c700(u64 L) {
    u64 acc = *(u64*)(L - 8); if (!acc) return 0;
    u64 mod = *(u64*)(acc + 0xb8); if (!mod) return 0;
    u64 a = FUN_71038f4000(L, 1, 0);
    u32 r = (**(u32(**)(u64,u64))(*(u64*)mod + 0x1e0))(mod, a);
    u32* s = *(u32**)(L + 0x10); s[0] = r; s[2] = 3;
    *(u64*)(L + 0x10) += 0x10; return 1;
}

// 0x710204c850 (336 bytes) — u32 return, vtable[0x1e8]
u64 FUN_710204c850(u64 L) {
    u64 acc = *(u64*)(L - 8); if (!acc) return 0;
    u64 mod = *(u64*)(acc + 0xb8); if (!mod) return 0;
    u64 a = FUN_71038f4000(L, 1, 0);
    u32 r = (**(u32(**)(u64,u64))(*(u64*)mod + 0x1e8))(mod, a);
    u32* s = *(u32**)(L + 0x10); s[0] = r; s[2] = 3;
    *(u64*)(L + 0x10) += 0x10; return 1;
}

// 0x710204c9a0 (336 bytes) — u32 return, vtable[0x1f0]
u64 FUN_710204c9a0(u64 L) {
    u64 acc = *(u64*)(L - 8); if (!acc) return 0;
    u64 mod = *(u64*)(acc + 0xb8); if (!mod) return 0;
    u64 a = FUN_71038f4000(L, 1, 0);
    u32 r = (**(u32(**)(u64,u64))(*(u64*)mod + 0x1f0))(mod, a);
    u32* s = *(u32**)(L + 0x10); s[0] = r; s[2] = 3;
    *(u64*)(L + 0x10) += 0x10; return 1;
}

// 0x710204d080 (336 bytes) — bool return, vtable[0x210]
u64 FUN_710204d080(u64 L) {
    u64 acc = *(u64*)(L - 8); if (!acc) return 0;
    u64 mod = *(u64*)(acc + 0xb8); if (!mod) return 0;
    u64 a = FUN_71038f4000(L, 1, 0);
    u32 r = (**(u32(**)(u64,u64))(*(u64*)mod + 0x210))(mod, a);
    u32* s = *(u32**)(L + 0x10); s[0] = r & 1; s[2] = 1;
    *(u64*)(L + 0x10) += 0x10; return 1;
}

// 0x710204d1d0 (336 bytes) — bool return, vtable[0x218]
u64 FUN_710204d1d0(u64 L) {
    u64 acc = *(u64*)(L - 8); if (!acc) return 0;
    u64 mod = *(u64*)(acc + 0xb8); if (!mod) return 0;
    u64 a = FUN_71038f4000(L, 1, 0);
    u32 r = (**(u32(**)(u64,u64))(*(u64*)mod + 0x218))(mod, a);
    u32* s = *(u32**)(L + 0x10); s[0] = r & 1; s[2] = 1;
    *(u64*)(L + 0x10) += 0x10; return 1;
}

// 0x710204d320 (336 bytes) — float(0x13) return, vtable[0x220]
u64 FUN_710204d320(u64 L) {
    u64 acc = *(u64*)(L - 8); if (!acc) return 0;
    u64 mod = *(u64*)(acc + 0xb8); if (!mod) return 0;
    u64 a = FUN_71038f4000(L, 1, 0);
    u64 r = (**(u64(**)(u64,u64))(*(u64*)mod + 0x220))(mod, a);
    u64* s = *(u64**)(L + 0x10);
    *s = r & 0xff; *(u32*)(s + 1) = 0x13;
    *(u64*)(L + 0x10) += 0x10; return 1;
}

// 0x710204d470 (336 bytes) — bool return, vtable[0x228]
u64 FUN_710204d470(u64 L) {
    u64 acc = *(u64*)(L - 8); if (!acc) return 0;
    u64 mod = *(u64*)(acc + 0xb8); if (!mod) return 0;
    u64 a = FUN_71038f4000(L, 1, 0);
    u32 r = (**(u32(**)(u64,u64))(*(u64*)mod + 0x228))(mod, a);
    u32* s = *(u32**)(L + 0x10); s[0] = r & 1; s[2] = 1;
    *(u64*)(L + 0x10) += 0x10; return 1;
}

// 0x710204eb80 (336 bytes) — bool return, vtable[0x318]
u64 FUN_710204eb80(u64 L) {
    u64 acc = *(u64*)(L - 8); if (!acc) return 0;
    u64 mod = *(u64*)(acc + 0xb8); if (!mod) return 0;
    u64 a = FUN_71038f4000(L, 1, 0);
    u32 r = (**(u32(**)(u64,u64))(*(u64*)mod + 0x318))(mod, a);
    u32* s = *(u32**)(L + 0x10); s[0] = r & 1; s[2] = 1;
    *(u64*)(L + 0x10) += 0x10; return 1;
}

// 0x710204ecd0 (336 bytes) — bool return, vtable[0x320]
u64 FUN_710204ecd0(u64 L) {
    u64 acc = *(u64*)(L - 8); if (!acc) return 0;
    u64 mod = *(u64*)(acc + 0xb8); if (!mod) return 0;
    u64 a = FUN_71038f4000(L, 1, 0);
    u32 r = (**(u32(**)(u64,u64))(*(u64*)mod + 0x320))(mod, a);
    u32* s = *(u32**)(L + 0x10); s[0] = r & 1; s[2] = 1;
    *(u64*)(L + 0x10) += 0x10; return 1;
}

// 0x710204ee20 (336 bytes) — ptr return (lightuserdata, tag=2), vtable[0x330]
u64 FUN_710204ee20(u64 L) {
    u64 acc = *(u64*)(L - 8); if (!acc) return 0;
    u64 mod = *(u64*)(acc + 0xb8); if (!mod) return 0;
    u64 a = FUN_71038f4000(L, 1, 0);
    u64 r = (**(u64(**)(u64,u64))(*(u64*)mod + 0x330))(mod, a);
    u64* s = *(u64**)(L + 0x10);
    *s = r; *(u32*)(s + 1) = 2;
    *(u64*)(L + 0x10) += 0x10; return 1;
}

// 0x710204ef70 (336 bytes) — bool return, vtable[0x338]
u64 FUN_710204ef70(u64 L) {
    u64 acc = *(u64*)(L - 8); if (!acc) return 0;
    u64 mod = *(u64*)(acc + 0xb8); if (!mod) return 0;
    u64 a = FUN_71038f4000(L, 1, 0);
    u32 r = (**(u32(**)(u64,u64))(*(u64*)mod + 0x338))(mod, a);
    u32* s = *(u32**)(L + 0x10); s[0] = r & 1; s[2] = 1;
    *(u64*)(L + 0x10) += 0x10; return 1;
}

// 0x710204f0c0 (336 bytes) — ptr return (lightuserdata, tag=2), vtable[0x340]
u64 FUN_710204f0c0(u64 L) {
    u64 acc = *(u64*)(L - 8); if (!acc) return 0;
    u64 mod = *(u64*)(acc + 0xb8); if (!mod) return 0;
    u64 a = FUN_71038f4000(L, 1, 0);
    u64 r = (**(u64(**)(u64,u64))(*(u64*)mod + 0x340))(mod, a);
    u64* s = *(u64**)(L + 0x10);
    *s = r; *(u32*)(s + 1) = 2;
    *(u64*)(L + 0x10) += 0x10; return 1;
}

// 0x710204f210 (336 bytes) — float(0x13) return, vtable[0x348]
u64 FUN_710204f210(u64 L) {
    u64 acc = *(u64*)(L - 8); if (!acc) return 0;
    u64 mod = *(u64*)(acc + 0xb8); if (!mod) return 0;
    u64 a = FUN_71038f4000(L, 1, 0);
    u64 r = (**(u64(**)(u64,u64))(*(u64*)mod + 0x348))(mod, a);
    u64* s = *(u64**)(L + 0x10);
    *s = r & 0xff; *(u32*)(s + 1) = 0x13;
    *(u64*)(L + 0x10) += 0x10; return 1;
}
