#include "types.h"

// MEDIUM-tier FUN_* functions — 0x7102 address range, batch e3-019
// Pool-e worker: ModelModule _impl thunks 0x7102057620–0x7102057760
// Pattern: accessor->model_module (+0x78) → vtable dispatch with bool arg masking
// 5-insn (20-byte): ldr/ldr/ldr xN/and wM,wM,#1/br xN
// 6-insn (32-byte): ldr/ldr/ldr xN/and/and/br xN

// ---- Module offset 0x78 (ModelModule), bool-masking variants -----------------

// 0x7102057620 (20 bytes) — ptr return, 3 int args, p3=bool, vtable[0x150]
u64 FUN_7102057620(u64 a, u64 p1, u64 p2, u32 p3) {
    u64 mod = *(u64*)(a + 0x78);
    return (**(u64(**)(u64,u64,u64,u32))(*(u64*)mod + 0x150))(mod, p1, p2, p3 & 1);
}

// 0x7102057640 (20 bytes) — ptr return, 4 int args, p4=bool, vtable[0x158]
u64 FUN_7102057640(u64 a, u64 p1, u64 p2, u64 p3, u32 p4) {
    u64 mod = *(u64*)(a + 0x78);
    return (**(u64(**)(u64,u64,u64,u64,u32))(*(u64*)mod + 0x158))(mod, p1, p2, p3, p4 & 1);
}

// 0x7102057680 (20 bytes) — ptr return, 3 int args, p3=bool, vtable[0x180]
u64 FUN_7102057680(u64 a, u64 p1, u64 p2, u32 p3) {
    u64 mod = *(u64*)(a + 0x78);
    return (**(u64(**)(u64,u64,u64,u32))(*(u64*)mod + 0x180))(mod, p1, p2, p3 & 1);
}

// 0x71020576a0 (20 bytes) — ptr return, 3 int args, p3=bool, vtable[0x188]
u64 FUN_71020576a0(u64 a, u64 p1, u64 p2, u32 p3) {
    u64 mod = *(u64*)(a + 0x78);
    return (**(u64(**)(u64,u64,u64,u32))(*(u64*)mod + 0x188))(mod, p1, p2, p3 & 1);
}

// 0x71020576f0 (32 bytes) — void, 4 int args, p3=bool, p4=bool, vtable[0x1a8]
void FUN_71020576f0(u64 a, u64 p1, u64 p2, u32 p3, u32 p4) {
    u64 mod = *(u64*)(a + 0x78);
    (**(void(**)(u64,u64,u64,u32,u32))(*(u64*)mod + 0x1a8))(mod, p1, p2, p3 & 1, p4 & 1);
}

// 0x7102057730 (20 bytes) — void, 1 int arg, p1=bool, vtable[0x1c0]
void FUN_7102057730(u64 a, u32 p1) {
    u64 mod = *(u64*)(a + 0x78);
    (**(void(**)(u64,u32))(*(u64*)mod + 0x1c0))(mod, p1 & 1);
}

// 0x7102057760 (20 bytes) — void, 2 int args, p2=bool, vtable[0x1d0]
void FUN_7102057760(u64 a, u64 p1, u32 p2) {
    u64 mod = *(u64*)(a + 0x78);
    (**(void(**)(u64,u64,u32))(*(u64*)mod + 0x1d0))(mod, p1, p2 & 1);
}
