#include "types.h"

// MEDIUM-tier FUN_* functions — 0x7102 address range, batch e3-021
// Pool-e worker: MotionModule _impl thunks 0x710205cb70–0x710205ce10
// Pattern: accessor->motion_module (+0x88) → vtable dispatch, 4/5-insn tail calls

// ---- Module offset 0x88 (MotionModule) -------------------------------------

// 0x710205cb70 (16 bytes) — void, 1 int arg, vtable[0xf0]
void FUN_710205cb70(u64 a, u64 p1) {
    u64 mod = *(u64*)(a + 0x88);
    (**(void(**)(u64,u64))(*(u64*)mod + 0xf0))(mod, p1);
}

// 0x710205cb80 (16 bytes) — void, 1 int arg, vtable[0xf8]
void FUN_710205cb80(u64 a, u64 p1) {
    u64 mod = *(u64*)(a + 0x88);
    (**(void(**)(u64,u64))(*(u64*)mod + 0xf8))(mod, p1);
}

// 0x710205cb90 (16 bytes) — void, 1 int arg, vtable[0x100]
void FUN_710205cb90(u64 a, u64 p1) {
    u64 mod = *(u64*)(a + 0x88);
    (**(void(**)(u64,u64))(*(u64*)mod + 0x100))(mod, p1);
}

// 0x710205cbe0 (16 bytes) — float return, 0 int args, vtable[0x118]
float FUN_710205cbe0(u64 a) {
    u64 mod = *(u64*)(a + 0x88);
    return (**(float(**)(u64))(*(u64*)mod + 0x118))(mod);
}

// 0x710205cbf0 (16 bytes) — float return, 0 int args, vtable[0x120]
float FUN_710205cbf0(u64 a) {
    u64 mod = *(u64*)(a + 0x88);
    return (**(float(**)(u64))(*(u64*)mod + 0x120))(mod);
}

// 0x710205cc00 (16 bytes) — bool return, 0 int args, vtable[0x128]
u32 FUN_710205cc00(u64 a) {
    u64 mod = *(u64*)(a + 0x88);
    return (**(u32(**)(u64))(*(u64*)mod + 0x128))(mod);
}

// 0x710205cc10 (16 bytes) — bool return, 0 int args, vtable[0x130]
u32 FUN_710205cc10(u64 a) {
    u64 mod = *(u64*)(a + 0x88);
    return (**(u32(**)(u64))(*(u64*)mod + 0x130))(mod);
}

// 0x710205cc20 (16 bytes) — u64 return (hash), 0 int args, vtable[0x138]
u64 FUN_710205cc20(u64 a) {
    u64 mod = *(u64*)(a + 0x88);
    return (**(u64(**)(u64))(*(u64*)mod + 0x138))(mod);
}

// 0x710205cc30 (16 bytes) — float return, 0 int args, vtable[0x140]
float FUN_710205cc30(u64 a) {
    u64 mod = *(u64*)(a + 0x88);
    return (**(float(**)(u64))(*(u64*)mod + 0x140))(mod);
}

// 0x710205cc40 (16 bytes) — bool return, 0 int args, vtable[0x148]
u32 FUN_710205cc40(u64 a) {
    u64 mod = *(u64*)(a + 0x88);
    return (**(u32(**)(u64))(*(u64*)mod + 0x148))(mod);
}

// 0x710205cc50 (16 bytes) — float return, 0 int args, vtable[0x150]
float FUN_710205cc50(u64 a) {
    u64 mod = *(u64*)(a + 0x88);
    return (**(float(**)(u64))(*(u64*)mod + 0x150))(mod);
}

// 0x710205cc60 (16 bytes) — u64 return (hash), 0 int args, vtable[0x158]
u64 FUN_710205cc60(u64 a) {
    u64 mod = *(u64*)(a + 0x88);
    return (**(u64(**)(u64))(*(u64*)mod + 0x158))(mod);
}

// 0x710205cc70 (16 bytes) — float return, 0 int args, vtable[0x160]
float FUN_710205cc70(u64 a) {
    u64 mod = *(u64*)(a + 0x88);
    return (**(float(**)(u64))(*(u64*)mod + 0x160))(mod);
}

// 0x710205cc80 (16 bytes) — float return, 0 int args, vtable[0x168]
float FUN_710205cc80(u64 a) {
    u64 mod = *(u64*)(a + 0x88);
    return (**(float(**)(u64))(*(u64*)mod + 0x168))(mod);
}

// 0x710205ccd0 (16 bytes) — float return, 0 int args, vtable[0x180]
float FUN_710205ccd0(u64 a) {
    u64 mod = *(u64*)(a + 0x88);
    return (**(float(**)(u64))(*(u64*)mod + 0x180))(mod);
}

// 0x710205cce0 (16 bytes) — float return, 1 int arg, vtable[0x188]
float FUN_710205cce0(u64 a, u64 p1) {
    u64 mod = *(u64*)(a + 0x88);
    return (**(float(**)(u64,u64))(*(u64*)mod + 0x188))(mod, p1);
}

// 0x710205ccf0 (20 bytes) — void, 1 int arg p1=bool, vtable[0x190]
void FUN_710205ccf0(u64 a, u32 p1) {
    u64 mod = *(u64*)(a + 0x88);
    (**(void(**)(u64,u32))(*(u64*)mod + 0x190))(mod, p1 & 1);
}

// 0x710205cd10 (16 bytes) — float return, 0 int args, vtable[0x198]
float FUN_710205cd10(u64 a) {
    u64 mod = *(u64*)(a + 0x88);
    return (**(float(**)(u64))(*(u64*)mod + 0x198))(mod);
}

// 0x710205cd80 (16 bytes) — ptr return, 2 int args, vtable[0x1c0]
u64 FUN_710205cd80(u64 a, u64 p1, u64 p2) {
    u64 mod = *(u64*)(a + 0x88);
    return (**(u64(**)(u64,u64,u64))(*(u64*)mod + 0x1c0))(mod, p1, p2);
}

// 0x710205cd90 (16 bytes) — bool return, 0 int args, vtable[0x1c8]
u32 FUN_710205cd90(u64 a) {
    u64 mod = *(u64*)(a + 0x88);
    return (**(u32(**)(u64))(*(u64*)mod + 0x1c8))(mod);
}

// 0x710205cda0 (16 bytes) — bool return, 0 int args, vtable[0x1d0]
u32 FUN_710205cda0(u64 a) {
    u64 mod = *(u64*)(a + 0x88);
    return (**(u32(**)(u64))(*(u64*)mod + 0x1d0))(mod);
}

// 0x710205cdb0 (16 bytes) — bool return, 0 int args, vtable[0x1f8]
u32 FUN_710205cdb0(u64 a) {
    u64 mod = *(u64*)(a + 0x88);
    return (**(u32(**)(u64))(*(u64*)mod + 0x1f8))(mod);
}

// 0x710205cdc0 (16 bytes) — bool return, 0 int args, vtable[0x218]
u32 FUN_710205cdc0(u64 a) {
    u64 mod = *(u64*)(a + 0x88);
    return (**(u32(**)(u64))(*(u64*)mod + 0x218))(mod);
}

// 0x710205cdd0 (16 bytes) — bool return, 0 int args, vtable[0x228]
u32 FUN_710205cdd0(u64 a) {
    u64 mod = *(u64*)(a + 0x88);
    return (**(u32(**)(u64))(*(u64*)mod + 0x228))(mod);
}

// 0x710205cde0 (16 bytes) — bool return, 0 int args, vtable[0x238]
u32 FUN_710205cde0(u64 a) {
    u64 mod = *(u64*)(a + 0x88);
    return (**(u32(**)(u64))(*(u64*)mod + 0x238))(mod);
}

// 0x710205ce10 (16 bytes) — bool return, 1 int arg, vtable[0x270]
u32 FUN_710205ce10(u64 a, u64 p1) {
    u64 mod = *(u64*)(a + 0x88);
    return (**(u32(**)(u64,u64))(*(u64*)mod + 0x270))(mod, p1);
}
