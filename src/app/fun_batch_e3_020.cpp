#include "types.h"

// MEDIUM-tier FUN_* functions — 0x7102 address range, batch e3-020
// Pool-e worker: ModelModule _impl thunks 0x7102057780–0x7102057800
// Pattern: accessor->model_module (+0x78) → vtable dispatch, 4-insn tail calls

// ---- Module offset 0x78 (ModelModule) --------------------------------------

// 0x7102057780 (16 bytes) — void, 0 int args (float alpha via SIMD), vtable[0x1f0]
void FUN_7102057780(u64 a) {
    u64 mod = *(u64*)(a + 0x78);
    (**(void(**)(u64))(*(u64*)mod + 0x1f0))(mod);
}

// 0x7102057790 (16 bytes) — void, 1 int arg (hash), vtable[0x1f8]
void FUN_7102057790(u64 a, u64 p1) {
    u64 mod = *(u64*)(a + 0x78);
    (**(void(**)(u64,u64))(*(u64*)mod + 0x1f8))(mod, p1);
}

// 0x71020577a0 (16 bytes) — void, 0 int args (float scale via SIMD), vtable[0x258]
void FUN_71020577a0(u64 a) {
    u64 mod = *(u64*)(a + 0x78);
    (**(void(**)(u64))(*(u64*)mod + 0x258))(mod);
}

// 0x71020577b0 (16 bytes) — void, 1 int arg, vtable[0x2d8]
void FUN_71020577b0(u64 a, u64 p1) {
    u64 mod = *(u64*)(a + 0x78);
    (**(void(**)(u64,u64))(*(u64*)mod + 0x2d8))(mod, p1);
}

// 0x71020577c0 (16 bytes) — void, 0 int args (float offset via SIMD), vtable[0x2e8]
void FUN_71020577c0(u64 a) {
    u64 mod = *(u64*)(a + 0x78);
    (**(void(**)(u64))(*(u64*)mod + 0x2e8))(mod);
}

// 0x71020577d0 (16 bytes) — void, 1 int arg, vtable[0x2f0]
void FUN_71020577d0(u64 a, u64 p1) {
    u64 mod = *(u64*)(a + 0x78);
    (**(void(**)(u64,u64))(*(u64*)mod + 0x2f0))(mod, p1);
}

// 0x71020577e0 (16 bytes) — ptr return, 1 int arg, vtable[0x328]
u64 FUN_71020577e0(u64 a, u64 p1) {
    u64 mod = *(u64*)(a + 0x78);
    return (**(u64(**)(u64,u64))(*(u64*)mod + 0x328))(mod, p1);
}

// 0x71020577f0 (16 bytes) — void, 0 int args, vtable[0x358]
void FUN_71020577f0(u64 a) {
    u64 mod = *(u64*)(a + 0x78);
    (**(void(**)(u64))(*(u64*)mod + 0x358))(mod);
}

// 0x7102057800 (16 bytes) — void, 0 int args, vtable[0x360]
void FUN_7102057800(u64 a) {
    u64 mod = *(u64*)(a + 0x78);
    (**(void(**)(u64))(*(u64*)mod + 0x360))(mod);
}
