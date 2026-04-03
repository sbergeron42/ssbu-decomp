#include "types.h"

// MEDIUM-tier FUN_* functions — 0x7102 address range, batch e3-026
// Pool-e worker: ReflectModule 0x710206ed90–0x710206ee20, SearchModule 0x71020702b0–0x71020703a0
// ReflectModule module offset: +0xf8, SearchModule module offset: +0xe0

// ---- Module offset 0xf8 (ReflectModule) — continued -------------------------

// 0x710206ed90 (16 bytes) — void, 0 int args (float via SIMD), vtable[0x90]
void FUN_710206ed90(u64 a) {
    u64 mod = *(u64*)(a + 0xf8);
    (**(void(**)(u64))(*(u64*)mod + 0x90))(mod);
}

// 0x710206eda0 (16 bytes) — float return, 0 int args, vtable[0x98]
float FUN_710206eda0(u64 a) {
    u64 mod = *(u64*)(a + 0xf8);
    return (**(float(**)(u64))(*(u64*)mod + 0x98))(mod);
}

// 0x710206edb0 (16 bytes) — void, 0 int args (float via SIMD), vtable[0xa0]
void FUN_710206edb0(u64 a) {
    u64 mod = *(u64*)(a + 0xf8);
    (**(void(**)(u64))(*(u64*)mod + 0xa0))(mod);
}

// 0x710206edc0 (16 bytes) — bool return, 0 int args, vtable[0xa8]
u32 FUN_710206edc0(u64 a) {
    u64 mod = *(u64*)(a + 0xf8);
    return (**(u32(**)(u64))(*(u64*)mod + 0xa8))(mod);
}

// 0x710206edd0 (20 bytes) — void, p1=bool, vtable[0xb0]
void FUN_710206edd0(u64 a, u32 p1) {
    u64 mod = *(u64*)(a + 0xf8);
    (**(void(**)(u64,u32))(*(u64*)mod + 0xb0))(mod, p1 & 1);
}

// 0x710206edf0 (16 bytes) — bool return, 0 int args, vtable[0xb8]
u32 FUN_710206edf0(u64 a) {
    u64 mod = *(u64*)(a + 0xf8);
    return (**(u32(**)(u64))(*(u64*)mod + 0xb8))(mod);
}

// 0x710206ee00 (16 bytes) — u32 return, 0 int args, vtable[0xc0]
u32 FUN_710206ee00(u64 a) {
    u64 mod = *(u64*)(a + 0xf8);
    return (**(u32(**)(u64))(*(u64*)mod + 0xc0))(mod);
}

// 0x710206ee10 (16 bytes) — float return, 0 int args, vtable[0xd8]
float FUN_710206ee10(u64 a) {
    u64 mod = *(u64*)(a + 0xf8);
    return (**(float(**)(u64))(*(u64*)mod + 0xd8))(mod);
}

// 0x710206ee20 (16 bytes) — void, 1 int arg, vtable[0xe0]
void FUN_710206ee20(u64 a, u64 p1) {
    u64 mod = *(u64*)(a + 0xf8);
    (**(void(**)(u64,u64))(*(u64*)mod + 0xe0))(mod, p1);
}

// ---- Module offset 0xe0 (SearchModule) --------------------------------------

// 0x71020702b0 (16 bytes) — void, 0 int args, vtable[0x50]
void FUN_71020702b0(u64 a) {
    u64 mod = *(u64*)(a + 0xe0);
    (**(void(**)(u64))(*(u64*)mod + 0x50))(mod);
}

// 0x71020702c0 (16 bytes) — void, 1 int arg, vtable[0x58]
void FUN_71020702c0(u64 a, u64 p1) {
    u64 mod = *(u64*)(a + 0xe0);
    (**(void(**)(u64,u64))(*(u64*)mod + 0x58))(mod, p1);
}

// 0x71020702d0 (16 bytes) — void, 2 int args, vtable[0x68]
void FUN_71020702d0(u64 a, u64 p1, u64 p2) {
    u64 mod = *(u64*)(a + 0xe0);
    (**(void(**)(u64,u64,u64))(*(u64*)mod + 0x68))(mod, p1, p2);
}

// 0x71020702e0 (16 bytes) — void, 2 int args, vtable[0x70]
void FUN_71020702e0(u64 a, u64 p1, u64 p2) {
    u64 mod = *(u64*)(a + 0xe0);
    (**(void(**)(u64,u64,u64))(*(u64*)mod + 0x70))(mod, p1, p2);
}

// 0x71020702f0 (16 bytes) — u32 return, 0 int args, vtable[0x78]
u32 FUN_71020702f0(u64 a) {
    u64 mod = *(u64*)(a + 0xe0);
    return (**(u32(**)(u64))(*(u64*)mod + 0x78))(mod);
}

// 0x7102070300 (16 bytes) — bool return, 1 int arg, vtable[0x80]
u32 FUN_7102070300(u64 a, u64 p1) {
    u64 mod = *(u64*)(a + 0xe0);
    return (**(u32(**)(u64,u64))(*(u64*)mod + 0x80))(mod, p1);
}

// 0x7102070310 (16 bytes) — u64 return, 1 int arg, vtable[0x88]
u64 FUN_7102070310(u64 a, u64 p1) {
    u64 mod = *(u64*)(a + 0xe0);
    return (**(u64(**)(u64,u64))(*(u64*)mod + 0x88))(mod, p1);
}

// 0x7102070320 (16 bytes) — void, 1 int arg, vtable[0x90]
void FUN_7102070320(u64 a, u64 p1) {
    u64 mod = *(u64*)(a + 0xe0);
    (**(void(**)(u64,u64))(*(u64*)mod + 0x90))(mod, p1);
}

// 0x7102070330 (16 bytes) — void, 4 int args, vtable[0x98]
void FUN_7102070330(u64 a, u64 p1, u64 p2, u64 p3, u64 p4) {
    u64 mod = *(u64*)(a + 0xe0);
    (**(void(**)(u64,u64,u64,u64,u64))(*(u64*)mod + 0x98))(mod, p1, p2, p3, p4);
}

// 0x7102070340 (16 bytes) — void, 3 int args, vtable[0xa0]
void FUN_7102070340(u64 a, u64 p1, u64 p2, u64 p3) {
    u64 mod = *(u64*)(a + 0xe0);
    (**(void(**)(u64,u64,u64,u64))(*(u64*)mod + 0xa0))(mod, p1, p2, p3);
}

// 0x7102070350 (16 bytes) — bool return, 0 int args, vtable[0xc8]
u32 FUN_7102070350(u64 a) {
    u64 mod = *(u64*)(a + 0xe0);
    return (**(u32(**)(u64))(*(u64*)mod + 0xc8))(mod);
}

// 0x7102070360 (16 bytes) — void, 1 int arg, vtable[0xd0]
void FUN_7102070360(u64 a, u64 p1) {
    u64 mod = *(u64*)(a + 0xe0);
    (**(void(**)(u64,u64))(*(u64*)mod + 0xd0))(mod, p1);
}

// 0x7102070370 (20 bytes) — void, p1=bool, vtable[0xd8]
void FUN_7102070370(u64 a, u32 p1) {
    u64 mod = *(u64*)(a + 0xe0);
    (**(void(**)(u64,u32))(*(u64*)mod + 0xd8))(mod, p1 & 1);
}

// 0x7102070390 (16 bytes) — void, 0 int args, vtable[0xe0]
void FUN_7102070390(u64 a) {
    u64 mod = *(u64*)(a + 0xe0);
    (**(void(**)(u64))(*(u64*)mod + 0xe0))(mod);
}

// 0x71020703a0 (20 bytes) — void, p1=bool, vtable[0xe8]
void FUN_71020703a0(u64 a, u32 p1) {
    u64 mod = *(u64*)(a + 0xe0);
    (**(void(**)(u64,u32))(*(u64*)mod + 0xe8))(mod, p1 & 1);
}
