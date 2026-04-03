#include "types.h"

// MEDIUM-tier FUN_* functions — 0x7102 address range, batch e3-018
// Pool-e worker: ModelModule _impl thunks 0x71020575b0–0x7102057750
// Pattern: accessor->model_module (offset +0x78) → vtable dispatch, no null check
// 4-insn tail calls: ldr x0,[x0,#0x78] / ldr x8,[x0] / ldr xN,[x8,#vtbl] / br xN

// ---- Module offset 0x78 (ModelModule) --------------------------------------

// 0x71020575b0 (16 bytes) — void, 1 int arg, vtable[0xe0]
void FUN_71020575b0(u64 a, u64 p1) {
    u64 mod = *(u64*)(a + 0x78);
    (**(void(**)(u64,u64))(*(u64*)mod + 0xe0))(mod, p1);
}

// 0x71020575c0 (16 bytes) — u32 return, 0 int args, vtable[0xe8]
u32 FUN_71020575c0(u64 a) {
    u64 mod = *(u64*)(a + 0x78);
    return (**(u32(**)(u64))(*(u64*)mod + 0xe8))(mod);
}

// 0x71020575d0 (16 bytes) — ptr return, 0 int args, vtable[0xf0]
u64 FUN_71020575d0(u64 a) {
    u64 mod = *(u64*)(a + 0x78);
    return (**(u64(**)(u64))(*(u64*)mod + 0xf0))(mod);
}

// 0x71020575e0 (16 bytes) — void, 0 int args (scale via SIMD regs), vtable[0xf8]
void FUN_71020575e0(u64 a) {
    u64 mod = *(u64*)(a + 0x78);
    (**(void(**)(u64))(*(u64*)mod + 0xf8))(mod);
}

// 0x71020575f0 (16 bytes) — float return, 0 int args, vtable[0x100]
float FUN_71020575f0(u64 a) {
    u64 mod = *(u64*)(a + 0x78);
    return (**(float(**)(u64))(*(u64*)mod + 0x100))(mod);
}

// 0x7102057600 (16 bytes) — void, 0 int args (scale_z via SIMD), vtable[0x108]
void FUN_7102057600(u64 a) {
    u64 mod = *(u64*)(a + 0x78);
    (**(void(**)(u64))(*(u64*)mod + 0x108))(mod);
}

// 0x7102057610 (16 bytes) — void, 0 int args (scale_z via SIMD), vtable[0x110]
void FUN_7102057610(u64 a) {
    u64 mod = *(u64*)(a + 0x78);
    (**(void(**)(u64))(*(u64*)mod + 0x110))(mod);
}

// 0x7102057660 (16 bytes) — ptr return, 2 int args, vtable[0x170]
u64 FUN_7102057660(u64 a, u64 p1, u64 p2) {
    u64 mod = *(u64*)(a + 0x78);
    return (**(u64(**)(u64,u64,u64))(*(u64*)mod + 0x170))(mod, p1, p2);
}

// 0x7102057670 (16 bytes) — void, 3 int args, vtable[0x178]
void FUN_7102057670(u64 a, u64 p1, u64 p2, u64 p3) {
    u64 mod = *(u64*)(a + 0x78);
    (**(void(**)(u64,u64,u64,u64))(*(u64*)mod + 0x178))(mod, p1, p2, p3);
}

// 0x71020576c0 (16 bytes) — void, 4 int args, vtable[0x190]
void FUN_71020576c0(u64 a, u64 p1, u64 p2, u64 p3, u64 p4) {
    u64 mod = *(u64*)(a + 0x78);
    (**(void(**)(u64,u64,u64,u64,u64))(*(u64*)mod + 0x190))(mod, p1, p2, p3, p4);
}

// 0x71020576d0 (16 bytes) — void, 2 int args, vtable[0x198]
void FUN_71020576d0(u64 a, u64 p1, u64 p2) {
    u64 mod = *(u64*)(a + 0x78);
    (**(void(**)(u64,u64,u64))(*(u64*)mod + 0x198))(mod, p1, p2);
}

// 0x71020576e0 (16 bytes) — void, 4 int args, vtable[0x1a0]
void FUN_71020576e0(u64 a, u64 p1, u64 p2, u64 p3, u64 p4) {
    u64 mod = *(u64*)(a + 0x78);
    (**(void(**)(u64,u64,u64,u64,u64))(*(u64*)mod + 0x1a0))(mod, p1, p2, p3, p4);
}

// 0x7102057710 (16 bytes) — void, 1 int arg, vtable[0x1b0]
void FUN_7102057710(u64 a, u64 p1) {
    u64 mod = *(u64*)(a + 0x78);
    (**(void(**)(u64,u64))(*(u64*)mod + 0x1b0))(mod, p1);
}

// 0x7102057720 (16 bytes) — ptr return, 2 int args, vtable[0x1b8]
u64 FUN_7102057720(u64 a, u64 p1, u64 p2) {
    u64 mod = *(u64*)(a + 0x78);
    return (**(u64(**)(u64,u64,u64))(*(u64*)mod + 0x1b8))(mod, p1, p2);
}

// 0x7102057750 (16 bytes) — bool return, 0 int args, vtable[0x1c8]
u32 FUN_7102057750(u64 a) {
    u64 mod = *(u64*)(a + 0x78);
    return (**(u32(**)(u64))(*(u64*)mod + 0x1c8))(mod);
}
