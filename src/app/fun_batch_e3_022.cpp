#include "types.h"

// MEDIUM-tier FUN_* functions — 0x7102 address range, batch e3-022
// Pool-e worker: MotionModule _impl thunks 0x710205ce20–0x710205d200
// Pattern: accessor->motion_module (+0x88) → vtable dispatch, 4/5-insn tail calls

// ---- Module offset 0x88 (MotionModule) — continued -------------------------

// 0x710205ce20 (16 bytes) — u64 return, 1 int arg, vtable[0x280]
u64 FUN_710205ce20(u64 a, u64 p1) {
    u64 mod = *(u64*)(a + 0x88);
    return (**(u64(**)(u64,u64))(*(u64*)mod + 0x280))(mod, p1);
}

// 0x710205ce30 (16 bytes) — u64 return, 1 int arg, vtable[0x288]
u64 FUN_710205ce30(u64 a, u64 p1) {
    u64 mod = *(u64*)(a + 0x88);
    return (**(u64(**)(u64,u64))(*(u64*)mod + 0x288))(mod, p1);
}

// 0x710205ce40 (16 bytes) — u64 return, 0 int args, vtable[0x298]
u64 FUN_710205ce40(u64 a) {
    u64 mod = *(u64*)(a + 0x88);
    return (**(u64(**)(u64))(*(u64*)mod + 0x298))(mod);
}

// 0x710205ce50 (16 bytes) — float return, 0 int args, vtable[0x2a0]
float FUN_710205ce50(u64 a) {
    u64 mod = *(u64*)(a + 0x88);
    return (**(float(**)(u64))(*(u64*)mod + 0x2a0))(mod);
}

// 0x710205ce60 (16 bytes) — u64 return, 0 int args, vtable[0x2b0]
u64 FUN_710205ce60(u64 a) {
    u64 mod = *(u64*)(a + 0x88);
    return (**(u64(**)(u64))(*(u64*)mod + 0x2b0))(mod);
}

// 0x710205ce70 (16 bytes) — void, 3 int args, vtable[0x2b8]
void FUN_710205ce70(u64 a, u64 p1, u64 p2, u64 p3) {
    u64 mod = *(u64*)(a + 0x88);
    (**(void(**)(u64,u64,u64,u64))(*(u64*)mod + 0x2b8))(mod, p1, p2, p3);
}

// 0x710205ce80 (16 bytes) — void, 0 int args, vtable[0x2c0]
void FUN_710205ce80(u64 a) {
    u64 mod = *(u64*)(a + 0x88);
    (**(void(**)(u64))(*(u64*)mod + 0x2c0))(mod);
}

// 0x710205ce90 (16 bytes) — ptr return, 2 int args, vtable[0x2d0]
u64 FUN_710205ce90(u64 a, u64 p1, u64 p2) {
    u64 mod = *(u64*)(a + 0x88);
    return (**(u64(**)(u64,u64,u64))(*(u64*)mod + 0x2d0))(mod, p1, p2);
}

// 0x710205cea0 (16 bytes) — ptr return, 1 int arg, vtable[0x2d8]
u64 FUN_710205cea0(u64 a, u64 p1) {
    u64 mod = *(u64*)(a + 0x88);
    return (**(u64(**)(u64,u64))(*(u64*)mod + 0x2d8))(mod, p1);
}

// 0x710205ceb0 (16 bytes) — float return, 0 int args, vtable[0x2e0]
float FUN_710205ceb0(u64 a) {
    u64 mod = *(u64*)(a + 0x88);
    return (**(float(**)(u64))(*(u64*)mod + 0x2e0))(mod);
}

// 0x710205cec0 (16 bytes) — bool return, 0 int args, vtable[0x2e8]
u32 FUN_710205cec0(u64 a) {
    u64 mod = *(u64*)(a + 0x88);
    return (**(u32(**)(u64))(*(u64*)mod + 0x2e8))(mod);
}

// 0x710205ced0 (16 bytes) — u64 return, 0 int args, vtable[0x2f0]
u64 FUN_710205ced0(u64 a) {
    u64 mod = *(u64*)(a + 0x88);
    return (**(u64(**)(u64))(*(u64*)mod + 0x2f0))(mod);
}

// 0x710205cee0 (16 bytes) — bool return, 1 int arg, vtable[0x2f8]
u32 FUN_710205cee0(u64 a, u64 p1) {
    u64 mod = *(u64*)(a + 0x88);
    return (**(u32(**)(u64,u64))(*(u64*)mod + 0x2f8))(mod, p1);
}

// 0x710205cef0 (16 bytes) — bool return, 1 int arg, vtable[0x300]
u32 FUN_710205cef0(u64 a, u64 p1) {
    u64 mod = *(u64*)(a + 0x88);
    return (**(u32(**)(u64,u64))(*(u64*)mod + 0x300))(mod, p1);
}

// 0x710205cf00 (16 bytes) — bool return, 0 int args, vtable[0x308]
u32 FUN_710205cf00(u64 a) {
    u64 mod = *(u64*)(a + 0x88);
    return (**(u32(**)(u64))(*(u64*)mod + 0x308))(mod);
}

// 0x710205cf10 (16 bytes) — bool return, 0 int args, vtable[0x310]
u32 FUN_710205cf10(u64 a) {
    u64 mod = *(u64*)(a + 0x88);
    return (**(u32(**)(u64))(*(u64*)mod + 0x310))(mod);
}

// 0x710205cf20 (16 bytes) — ptr return, 2 int args, vtable[0x318]
u64 FUN_710205cf20(u64 a, u64 p1, u64 p2) {
    u64 mod = *(u64*)(a + 0x88);
    return (**(u64(**)(u64,u64,u64))(*(u64*)mod + 0x318))(mod, p1, p2);
}

// 0x710205cf60 (20 bytes) — void, 2 int args, p2=bool, vtable[0x328]
void FUN_710205cf60(u64 a, u64 p1, u32 p2) {
    u64 mod = *(u64*)(a + 0x88);
    (**(void(**)(u64,u64,u32))(*(u64*)mod + 0x328))(mod, p1, p2 & 1);
}

// 0x710205cf80 (16 bytes) — void, 1 int arg, vtable[0x338]
void FUN_710205cf80(u64 a, u64 p1) {
    u64 mod = *(u64*)(a + 0x88);
    (**(void(**)(u64,u64))(*(u64*)mod + 0x338))(mod, p1);
}

// 0x710205cf90 (16 bytes) — u64 return, 1 int arg, vtable[0x340]
u64 FUN_710205cf90(u64 a, u64 p1) {
    u64 mod = *(u64*)(a + 0x88);
    return (**(u64(**)(u64,u64))(*(u64*)mod + 0x340))(mod, p1);
}

// 0x710205cfa0 (16 bytes) — bool return, 1 int arg, vtable[0x348]
u32 FUN_710205cfa0(u64 a, u64 p1) {
    u64 mod = *(u64*)(a + 0x88);
    return (**(u32(**)(u64,u64))(*(u64*)mod + 0x348))(mod, p1);
}

// 0x710205cfb0 (16 bytes) — float return, 1 int arg, vtable[0x350]
float FUN_710205cfb0(u64 a, u64 p1) {
    u64 mod = *(u64*)(a + 0x88);
    return (**(float(**)(u64,u64))(*(u64*)mod + 0x350))(mod, p1);
}

// 0x710205cfc0 (16 bytes) — void, 1 int arg (floats/bools via SIMD/other regs), vtable[0x358]
void FUN_710205cfc0(u64 a, u64 p1) {
    u64 mod = *(u64*)(a + 0x88);
    (**(void(**)(u64,u64))(*(u64*)mod + 0x358))(mod, p1);
}

// 0x710205cfd0 (16 bytes) — float return, 1 int arg, vtable[0x360]
float FUN_710205cfd0(u64 a, u64 p1) {
    u64 mod = *(u64*)(a + 0x88);
    return (**(float(**)(u64,u64))(*(u64*)mod + 0x360))(mod, p1);
}

// 0x710205cfe0 (16 bytes) — float return, 1 int arg, vtable[0x368]
float FUN_710205cfe0(u64 a, u64 p1) {
    u64 mod = *(u64*)(a + 0x88);
    return (**(float(**)(u64,u64))(*(u64*)mod + 0x368))(mod, p1);
}

// 0x710205cff0 (16 bytes) — float return, 1 int arg, vtable[0x370]
float FUN_710205cff0(u64 a, u64 p1) {
    u64 mod = *(u64*)(a + 0x88);
    return (**(float(**)(u64,u64))(*(u64*)mod + 0x370))(mod, p1);
}

// 0x710205d000 (20 bytes) — void, 2 int args, p2=bool, vtable[0x378]
void FUN_710205d000(u64 a, u64 p1, u32 p2) {
    u64 mod = *(u64*)(a + 0x88);
    (**(void(**)(u64,u64,u32))(*(u64*)mod + 0x378))(mod, p1, p2 & 1);
}

// 0x710205d020 (20 bytes) — void, 2 int args, p2=bool, vtable[0x380]
void FUN_710205d020(u64 a, u64 p1, u32 p2) {
    u64 mod = *(u64*)(a + 0x88);
    (**(void(**)(u64,u64,u32))(*(u64*)mod + 0x380))(mod, p1, p2 & 1);
}

// 0x710205d040 (16 bytes) — bool return, 1 int arg, vtable[0x388]
u32 FUN_710205d040(u64 a, u64 p1) {
    u64 mod = *(u64*)(a + 0x88);
    return (**(u32(**)(u64,u64))(*(u64*)mod + 0x388))(mod, p1);
}

// 0x710205d050 (16 bytes) — bool return, 0 int args, vtable[0x390]
u32 FUN_710205d050(u64 a) {
    u64 mod = *(u64*)(a + 0x88);
    return (**(u32(**)(u64))(*(u64*)mod + 0x390))(mod);
}

// 0x710205d080 (20 bytes) — void, 1 int arg p1=bool, vtable[0x3a8]
void FUN_710205d080(u64 a, u32 p1) {
    u64 mod = *(u64*)(a + 0x88);
    (**(void(**)(u64,u32))(*(u64*)mod + 0x3a8))(mod, p1 & 1);
}

// 0x710205d0a0 (16 bytes) — void, 1 int arg, vtable[0x3b0]
void FUN_710205d0a0(u64 a, u64 p1) {
    u64 mod = *(u64*)(a + 0x88);
    (**(void(**)(u64,u64))(*(u64*)mod + 0x3b0))(mod, p1);
}

// 0x710205d0b0 (16 bytes) — void, 1 int arg, vtable[0x3b8]
void FUN_710205d0b0(u64 a, u64 p1) {
    u64 mod = *(u64*)(a + 0x88);
    (**(void(**)(u64,u64))(*(u64*)mod + 0x3b8))(mod, p1);
}

// 0x710205d0c0 (16 bytes) — void, 2 int args, vtable[0x3c0]
void FUN_710205d0c0(u64 a, u64 p1, u64 p2) {
    u64 mod = *(u64*)(a + 0x88);
    (**(void(**)(u64,u64,u64))(*(u64*)mod + 0x3c0))(mod, p1, p2);
}

// 0x710205d0d0 (16 bytes) — u64 return, 1 int arg, vtable[0x3c8]
u64 FUN_710205d0d0(u64 a, u64 p1) {
    u64 mod = *(u64*)(a + 0x88);
    return (**(u64(**)(u64,u64))(*(u64*)mod + 0x3c8))(mod, p1);
}

// 0x710205d120 (16 bytes) — float return, 0 int args, vtable[0x3f0]
float FUN_710205d120(u64 a) {
    u64 mod = *(u64*)(a + 0x88);
    return (**(float(**)(u64))(*(u64*)mod + 0x3f0))(mod);
}

// 0x710205d130 (16 bytes) — bool return, 0 int args, vtable[0x3f8]
u32 FUN_710205d130(u64 a) {
    u64 mod = *(u64*)(a + 0x88);
    return (**(u32(**)(u64))(*(u64*)mod + 0x3f8))(mod);
}

// 0x710205d140 (16 bytes) — float return, 0 int args, vtable[0x410]
float FUN_710205d140(u64 a) {
    u64 mod = *(u64*)(a + 0x88);
    return (**(float(**)(u64))(*(u64*)mod + 0x410))(mod);
}

// 0x710205d190 (16 bytes) — bool return, 0 int args, vtable[0x440]
u32 FUN_710205d190(u64 a) {
    u64 mod = *(u64*)(a + 0x88);
    return (**(u32(**)(u64))(*(u64*)mod + 0x440))(mod);
}

// 0x710205d1a0 (16 bytes) — void, 1 int arg, vtable[0x448]
void FUN_710205d1a0(u64 a, u64 p1) {
    u64 mod = *(u64*)(a + 0x88);
    (**(void(**)(u64,u64))(*(u64*)mod + 0x448))(mod, p1);
}

// 0x710205d1d0 (16 bytes) — ptr return, 0 int args, vtable[0x470]
u64 FUN_710205d1d0(u64 a) {
    u64 mod = *(u64*)(a + 0x88);
    return (**(u64(**)(u64))(*(u64*)mod + 0x470))(mod);
}

// 0x710205d200 (16 bytes) — bool return, 0 int args, vtable[0x4a0]
u32 FUN_710205d200(u64 a) {
    u64 mod = *(u64*)(a + 0x88);
    return (**(u32(**)(u64))(*(u64*)mod + 0x4a0))(mod);
}
