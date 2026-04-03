#include "types.h"

// MEDIUM-tier FUN_* functions — 0x7102 address range, batch e3-024
// Pool-e worker: PostureModule _impl thunks 0x710206ade0–0x710206af60
// Pattern: accessor->posture_module (+0x38) → vtable dispatch
// Note: some functions use blr (non-tail) in binary; compiled quality only

// ---- Module offset 0x38 (PostureModule) ------------------------------------

// 0x710206ade0 (32 bytes) — ptr return, 0 int args, vtable[0x60]
u64 FUN_710206ade0(u64 a) {
    u64 mod = *(u64*)(a + 0x38);
    return (**(u64(**)(u64))(*(u64*)mod + 0x60))(mod);
}

// 0x710206ae00 (16 bytes) — ptr return, 0 int args, vtable[0x68]
u64 FUN_710206ae00(u64 a) {
    u64 mod = *(u64*)(a + 0x38);
    return (**(u64(**)(u64))(*(u64*)mod + 0x68))(mod);
}

// 0x710206aea0 (16 bytes) — void, 1 int arg (ptr), vtable[0x70]
void FUN_710206aea0(u64 a, u64 p1) {
    u64 mod = *(u64*)(a + 0x38);
    (**(void(**)(u64,u64))(*(u64*)mod + 0x70))(mod, p1);
}

// 0x710206aeb0 (16 bytes) — void, 1 int arg (ptr), vtable[0x78]
void FUN_710206aeb0(u64 a, u64 p1) {
    u64 mod = *(u64*)(a + 0x38);
    (**(void(**)(u64,u64))(*(u64*)mod + 0x78))(mod, p1);
}

// 0x710206aec0 (16 bytes) — void, 1 int arg (ptr), vtable[0x80]
void FUN_710206aec0(u64 a, u64 p1) {
    u64 mod = *(u64*)(a + 0x38);
    (**(void(**)(u64,u64))(*(u64*)mod + 0x80))(mod, p1);
}

// 0x710206aed0 (16 bytes) — void, 1 int arg (ptr), vtable[0x88]
void FUN_710206aed0(u64 a, u64 p1) {
    u64 mod = *(u64*)(a + 0x38);
    (**(void(**)(u64,u64))(*(u64*)mod + 0x88))(mod, p1);
}

// 0x710206aee0 (32 bytes) — ptr return, 0 int args, vtable[0x90]
u64 FUN_710206aee0(u64 a) {
    u64 mod = *(u64*)(a + 0x38);
    return (**(u64(**)(u64))(*(u64*)mod + 0x90))(mod);
}

// 0x710206af00 (16 bytes) — ptr return, 0 int args, vtable[0x98]
u64 FUN_710206af00(u64 a) {
    u64 mod = *(u64*)(a + 0x38);
    return (**(u64(**)(u64))(*(u64*)mod + 0x98))(mod);
}

// 0x710206af10 (16 bytes) — float return, 0 int args, vtable[0xb0]
float FUN_710206af10(u64 a) {
    u64 mod = *(u64*)(a + 0x38);
    return (**(float(**)(u64))(*(u64*)mod + 0xb0))(mod);
}

// 0x710206af20 (16 bytes) — void, 0 int args (float lr via SIMD), vtable[0xb8]
void FUN_710206af20(u64 a) {
    u64 mod = *(u64*)(a + 0x38);
    (**(void(**)(u64))(*(u64*)mod + 0xb8))(mod);
}

// 0x710206af30 (16 bytes) — void, 0 int args, vtable[0xc0]
void FUN_710206af30(u64 a) {
    u64 mod = *(u64*)(a + 0x38);
    (**(void(**)(u64))(*(u64*)mod + 0xc0))(mod);
}

// 0x710206af40 (16 bytes) — void, 1 int arg (ptr), vtable[0xc8]
void FUN_710206af40(u64 a, u64 p1) {
    u64 mod = *(u64*)(a + 0x38);
    (**(void(**)(u64,u64))(*(u64*)mod + 0xc8))(mod, p1);
}

// 0x710206af50 (16 bytes) — void, 2 int args (ptrs), vtable[0xd0]
void FUN_710206af50(u64 a, u64 p1, u64 p2) {
    u64 mod = *(u64*)(a + 0x38);
    (**(void(**)(u64,u64,u64))(*(u64*)mod + 0xd0))(mod, p1, p2);
}

// 0x710206af60 (32 bytes) — ptr return, 0 int args, vtable[0xd8]
u64 FUN_710206af60(u64 a) {
    u64 mod = *(u64*)(a + 0x38);
    return (**(u64(**)(u64))(*(u64*)mod + 0xd8))(mod);
}
