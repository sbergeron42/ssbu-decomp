#include "types.h"

// MEDIUM-tier FUN_* functions — 0x7102 address range, batch e3-027
// Pool-e worker: SearchModule 0x71020703c0–0x7102070440, ShadowModule 0x7102072ad0–0x7102072b20,
//                ShakeModule 0x7102073220–0x71020732c0
// SearchModule module offset: +0xe0, ShadowModule: +0x180, ShakeModule: +0x168

// ---- Module offset 0xe0 (SearchModule) — continued -------------------------

// 0x71020703c0 (16 bytes) — void, 1 int arg, vtable[0xf8]
void FUN_71020703c0(u64 a, u64 p1) {
    u64 mod = *(u64*)(a + 0xe0);
    (**(void(**)(u64,u64))(*(u64*)mod + 0xf8))(mod, p1);
}

// 0x71020703d0 (16 bytes) — u64 return, 0 int args, vtable[0x100]
u64 FUN_71020703d0(u64 a) {
    u64 mod = *(u64*)(a + 0xe0);
    return (**(u64(**)(u64))(*(u64*)mod + 0x100))(mod);
}

// 0x71020703e0 (16 bytes) — void, 1 int arg, vtable[0x108]
void FUN_71020703e0(u64 a, u64 p1) {
    u64 mod = *(u64*)(a + 0xe0);
    (**(void(**)(u64,u64))(*(u64*)mod + 0x108))(mod, p1);
}

// 0x71020703f0 (20 bytes) — void, p1=bool, vtable[0x110]
void FUN_71020703f0(u64 a, u32 p1) {
    u64 mod = *(u64*)(a + 0xe0);
    (**(void(**)(u64,u32))(*(u64*)mod + 0x110))(mod, p1 & 1);
}

// 0x7102070410 (20 bytes) — void, p1=bool, vtable[0x118]
void FUN_7102070410(u64 a, u32 p1) {
    u64 mod = *(u64*)(a + 0xe0);
    (**(void(**)(u64,u32))(*(u64*)mod + 0x118))(mod, p1 & 1);
}

// 0x7102070430 (16 bytes) — u32 return, 0 int args, vtable[0x120]
u32 FUN_7102070430(u64 a) {
    u64 mod = *(u64*)(a + 0xe0);
    return (**(u32(**)(u64))(*(u64*)mod + 0x120))(mod);
}

// 0x7102070440 (16 bytes) — void, 0 int args, vtable[0x128]
void FUN_7102070440(u64 a) {
    u64 mod = *(u64*)(a + 0xe0);
    (**(void(**)(u64))(*(u64*)mod + 0x128))(mod);
}

// ---- Module offset 0x180 (ShadowModule) -------------------------------------

// 0x7102072ad0 (20 bytes) — void, p1=u64, p2=bool, vtable[0x48]
void FUN_7102072ad0(u64 a, u64 p1, u32 p2) {
    u64 mod = *(u64*)(a + 0x180);
    (**(void(**)(u64,u64,u32))(*(u64*)mod + 0x48))(mod, p1, p2 & 1);
}

// 0x7102072af0 (20 bytes) — void, p1=bool, vtable[0x50]
void FUN_7102072af0(u64 a, u32 p1) {
    u64 mod = *(u64*)(a + 0x180);
    (**(void(**)(u64,u32))(*(u64*)mod + 0x50))(mod, p1 & 1);
}

// 0x7102072b10 (16 bytes) — void, 0 int args (float via SIMD), vtable[0x60]
void FUN_7102072b10(u64 a) {
    u64 mod = *(u64*)(a + 0x180);
    (**(void(**)(u64))(*(u64*)mod + 0x60))(mod);
}

// 0x7102072b20 (16 bytes) — void, 0 int args (float via SIMD), vtable[0x78]
void FUN_7102072b20(u64 a) {
    u64 mod = *(u64*)(a + 0x180);
    (**(void(**)(u64))(*(u64*)mod + 0x78))(mod);
}

// ---- Module offset 0x168 (ShakeModule) --------------------------------------

// 0x7102073220 (16 bytes) — void, 2 int args, vtable[0x60]
void FUN_7102073220(u64 a, u64 p1, u64 p2) {
    u64 mod = *(u64*)(a + 0x168);
    (**(void(**)(u64,u64,u64))(*(u64*)mod + 0x60))(mod, p1, p2);
}

// 0x7102073230 (16 bytes) — void, 0 int args, vtable[0x68]
void FUN_7102073230(u64 a) {
    u64 mod = *(u64*)(a + 0x168);
    (**(void(**)(u64))(*(u64*)mod + 0x68))(mod);
}

// 0x7102073240 (16 bytes) — void, 1 int arg, vtable[0x70]
void FUN_7102073240(u64 a, u64 p1) {
    u64 mod = *(u64*)(a + 0x168);
    (**(void(**)(u64,u64))(*(u64*)mod + 0x70))(mod, p1);
}

// 0x7102073250 (16 bytes) — bool return, 0 int args, vtable[0x88]
u32 FUN_7102073250(u64 a) {
    u64 mod = *(u64*)(a + 0x168);
    return (**(u32(**)(u64))(*(u64*)mod + 0x88))(mod);
}

// 0x7102073260 (16 bytes) — u64 return, 1 int arg, vtable[0x90]
u64 FUN_7102073260(u64 a, u64 p1) {
    u64 mod = *(u64*)(a + 0x168);
    return (**(u64(**)(u64,u64))(*(u64*)mod + 0x90))(mod, p1);
}

// 0x7102073270 (16 bytes) — void, 1 int arg, vtable[0x98]
void FUN_7102073270(u64 a, u64 p1) {
    u64 mod = *(u64*)(a + 0x168);
    (**(void(**)(u64,u64))(*(u64*)mod + 0x98))(mod, p1);
}

// 0x7102073280 (16 bytes) — void, 0 int args, vtable[0xa0]
void FUN_7102073280(u64 a) {
    u64 mod = *(u64*)(a + 0x168);
    (**(void(**)(u64))(*(u64*)mod + 0xa0))(mod);
}

// 0x7102073290 (16 bytes) — void, 1 int arg, vtable[0xa8]
void FUN_7102073290(u64 a, u64 p1) {
    u64 mod = *(u64*)(a + 0x168);
    (**(void(**)(u64,u64))(*(u64*)mod + 0xa8))(mod, p1);
}

// 0x71020732a0 (20 bytes) — void, p1=u64, p2=bool, vtable[0xb0]
void FUN_71020732a0(u64 a, u64 p1, u32 p2) {
    u64 mod = *(u64*)(a + 0x168);
    (**(void(**)(u64,u64,u32))(*(u64*)mod + 0xb0))(mod, p1, p2 & 1);
}

// 0x71020732c0 (20 bytes) — void, p1=bool, vtable[0xb8]
void FUN_71020732c0(u64 a, u32 p1) {
    u64 mod = *(u64*)(a + 0x168);
    (**(void(**)(u64,u32))(*(u64*)mod + 0xb8))(mod, p1 & 1);
}
