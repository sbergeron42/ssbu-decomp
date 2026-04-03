#include "types.h"

// MEDIUM-tier FUN_* functions — 0x7102 address range, batch e3-023
// Pool-e worker: MotionModule thunks 0x710205d0e0–0x710205d3a0
//                MotionAnimcmdModule thunks 0x7102069040–0x71020691a0
// Pattern: accessor->module → vtable dispatch, 4/5-insn tail calls

// ---- Module offset 0x88 (MotionModule) — bool-setter variants ---------------

// 0x710205d0e0 (20 bytes) — void, p1=bool, vtable[0x3d0]
void FUN_710205d0e0(u64 a, u32 p1) {
    u64 mod = *(u64*)(a + 0x88);
    (**(void(**)(u64,u32))(*(u64*)mod + 0x3d0))(mod, p1 & 1);
}

// 0x710205d100 (20 bytes) — void, p1=bool, vtable[0x3d8]
void FUN_710205d100(u64 a, u32 p1) {
    u64 mod = *(u64*)(a + 0x88);
    (**(void(**)(u64,u32))(*(u64*)mod + 0x3d8))(mod, p1 & 1);
}

// 0x710205d150 (20 bytes) — void, p1=bool, vtable[0x420]
void FUN_710205d150(u64 a, u32 p1) {
    u64 mod = *(u64*)(a + 0x88);
    (**(void(**)(u64,u32))(*(u64*)mod + 0x420))(mod, p1 & 1);
}

// 0x710205d170 (20 bytes) — void, p1=bool, vtable[0x438]
void FUN_710205d170(u64 a, u32 p1) {
    u64 mod = *(u64*)(a + 0x88);
    (**(void(**)(u64,u32))(*(u64*)mod + 0x438))(mod, p1 & 1);
}

// 0x710205d1b0 (20 bytes) — void, p1=bool, vtable[0x468]
void FUN_710205d1b0(u64 a, u32 p1) {
    u64 mod = *(u64*)(a + 0x88);
    (**(void(**)(u64,u32))(*(u64*)mod + 0x468))(mod, p1 & 1);
}

// 0x710205d1e0 (20 bytes) — void, p1=bool, vtable[0x478]
void FUN_710205d1e0(u64 a, u32 p1) {
    u64 mod = *(u64*)(a + 0x88);
    (**(void(**)(u64,u32))(*(u64*)mod + 0x478))(mod, p1 & 1);
}

// 0x710205d210 (20 bytes) — void, p1=bool, vtable[0x4c0]
void FUN_710205d210(u64 a, u32 p1) {
    u64 mod = *(u64*)(a + 0x88);
    (**(void(**)(u64,u32))(*(u64*)mod + 0x4c0))(mod, p1 & 1);
}

// 0x710205d230 (20 bytes) — void, p1=bool, vtable[0x4f8]
void FUN_710205d230(u64 a, u32 p1) {
    u64 mod = *(u64*)(a + 0x88);
    (**(void(**)(u64,u32))(*(u64*)mod + 0x4f8))(mod, p1 & 1);
}

// 0x710205d250 (16 bytes) — void, 1 int arg, vtable[0x500]
void FUN_710205d250(u64 a, u64 p1) {
    u64 mod = *(u64*)(a + 0x88);
    (**(void(**)(u64,u64))(*(u64*)mod + 0x500))(mod, p1);
}

// 0x710205d280 (20 bytes) — void, p1=bool, vtable[0x588]
void FUN_710205d280(u64 a, u32 p1) {
    u64 mod = *(u64*)(a + 0x88);
    (**(void(**)(u64,u32))(*(u64*)mod + 0x588))(mod, p1 & 1);
}

// 0x710205d2a0 (16 bytes) — void, 0 int args, vtable[0x590]
void FUN_710205d2a0(u64 a) {
    u64 mod = *(u64*)(a + 0x88);
    (**(void(**)(u64))(*(u64*)mod + 0x590))(mod);
}

// 0x710205d2b0 (16 bytes) — void, 1 int arg, vtable[0x598]
void FUN_710205d2b0(u64 a, u64 p1) {
    u64 mod = *(u64*)(a + 0x88);
    (**(void(**)(u64,u64))(*(u64*)mod + 0x598))(mod, p1);
}

// 0x710205d2c0 (20 bytes) — void, p1=bool, vtable[0x5a0]
void FUN_710205d2c0(u64 a, u32 p1) {
    u64 mod = *(u64*)(a + 0x88);
    (**(void(**)(u64,u32))(*(u64*)mod + 0x5a0))(mod, p1 & 1);
}

// 0x710205d2e0 (20 bytes) — void, p1=bool, vtable[0x5b8]
void FUN_710205d2e0(u64 a, u32 p1) {
    u64 mod = *(u64*)(a + 0x88);
    (**(void(**)(u64,u32))(*(u64*)mod + 0x5b8))(mod, p1 & 1);
}

// 0x710205d300 (20 bytes) — void, 2 int args, p2=bool, vtable[0x5c0]
void FUN_710205d300(u64 a, u64 p1, u32 p2) {
    u64 mod = *(u64*)(a + 0x88);
    (**(void(**)(u64,u64,u32))(*(u64*)mod + 0x5c0))(mod, p1, p2 & 1);
}

// 0x710205d320 (20 bytes) — void, 2 int args, p2=bool, vtable[0x5c8]
void FUN_710205d320(u64 a, u64 p1, u32 p2) {
    u64 mod = *(u64*)(a + 0x88);
    (**(void(**)(u64,u64,u32))(*(u64*)mod + 0x5c8))(mod, p1, p2 & 1);
}

// 0x710205d340 (20 bytes) — void, p1=bool, vtable[0x5d0]
void FUN_710205d340(u64 a, u32 p1) {
    u64 mod = *(u64*)(a + 0x88);
    (**(void(**)(u64,u32))(*(u64*)mod + 0x5d0))(mod, p1 & 1);
}

// 0x710205d360 (20 bytes) — void, p1=bool, vtable[0x5e0]
void FUN_710205d360(u64 a, u32 p1) {
    u64 mod = *(u64*)(a + 0x88);
    (**(void(**)(u64,u32))(*(u64*)mod + 0x5e0))(mod, p1 & 1);
}

// 0x710205d380 (20 bytes) — void, p1=bool, vtable[0x5f8]
void FUN_710205d380(u64 a, u32 p1) {
    u64 mod = *(u64*)(a + 0x88);
    (**(void(**)(u64,u32))(*(u64*)mod + 0x5f8))(mod, p1 & 1);
}

// 0x710205d3a0 (16 bytes) — void, 1 int arg, vtable[0x600]
void FUN_710205d3a0(u64 a, u64 p1) {
    u64 mod = *(u64*)(a + 0x88);
    (**(void(**)(u64,u64))(*(u64*)mod + 0x600))(mod, p1);
}

// ---- Module offset 0x188 (MotionAnimcmdModule) ------------------------------

// 0x7102069040 (16 bytes) — void, 0 int args, vtable[0x58]
void FUN_7102069040(u64 a) {
    u64 mod = *(u64*)(a + 0x188);
    (**(void(**)(u64))(*(u64*)mod + 0x58))(mod);
}

// 0x7102069090 (16 bytes) — void, 3 int args, vtable[0x78]
void FUN_7102069090(u64 a, u64 p1, u64 p2, u64 p3) {
    u64 mod = *(u64*)(a + 0x188);
    (**(void(**)(u64,u64,u64,u64))(*(u64*)mod + 0x78))(mod, p1, p2, p3);
}

// 0x71020690a0 (16 bytes) — void, 3 int args, vtable[0x80]
void FUN_71020690a0(u64 a, u64 p1, u64 p2, u64 p3) {
    u64 mod = *(u64*)(a + 0x188);
    (**(void(**)(u64,u64,u64,u64))(*(u64*)mod + 0x80))(mod, p1, p2, p3);
}

// 0x71020690b0 (20 bytes) — void, p1=bool, vtable[0x88]
void FUN_71020690b0(u64 a, u32 p1) {
    u64 mod = *(u64*)(a + 0x188);
    (**(void(**)(u64,u32))(*(u64*)mod + 0x88))(mod, p1 & 1);
}

// 0x71020690d0 (16 bytes) — void, 0 int args, vtable[0x90]
void FUN_71020690d0(u64 a) {
    u64 mod = *(u64*)(a + 0x188);
    (**(void(**)(u64))(*(u64*)mod + 0x90))(mod);
}

// 0x71020690e0 (20 bytes) — void, p1=bool, vtable[0x98]
void FUN_71020690e0(u64 a, u32 p1) {
    u64 mod = *(u64*)(a + 0x188);
    (**(void(**)(u64,u32))(*(u64*)mod + 0x98))(mod, p1 & 1);
}

// 0x7102069100 (20 bytes) — void, p1=bool, vtable[0xa0]
void FUN_7102069100(u64 a, u32 p1) {
    u64 mod = *(u64*)(a + 0x188);
    (**(void(**)(u64,u32))(*(u64*)mod + 0xa0))(mod, p1 & 1);
}

// 0x7102069120 (20 bytes) — void, p1=bool, vtable[0xa8]
void FUN_7102069120(u64 a, u32 p1) {
    u64 mod = *(u64*)(a + 0x188);
    (**(void(**)(u64,u32))(*(u64*)mod + 0xa8))(mod, p1 & 1);
}

// 0x7102069140 (20 bytes) — void, p1=bool, vtable[0xb0]
void FUN_7102069140(u64 a, u32 p1) {
    u64 mod = *(u64*)(a + 0x188);
    (**(void(**)(u64,u32))(*(u64*)mod + 0xb0))(mod, p1 & 1);
}

// 0x7102069160 (20 bytes) — void, p1=bool, vtable[0xb8]
void FUN_7102069160(u64 a, u32 p1) {
    u64 mod = *(u64*)(a + 0x188);
    (**(void(**)(u64,u32))(*(u64*)mod + 0xb8))(mod, p1 & 1);
}

// 0x7102069180 (16 bytes) — bool return, 0 int args, vtable[0xc0]
u32 FUN_7102069180(u64 a) {
    u64 mod = *(u64*)(a + 0x188);
    return (**(u32(**)(u64))(*(u64*)mod + 0xc0))(mod);
}

// 0x7102069190 (16 bytes) — void, 0 int args, vtable[0xc8]
void FUN_7102069190(u64 a) {
    u64 mod = *(u64*)(a + 0x188);
    (**(void(**)(u64))(*(u64*)mod + 0xc8))(mod);
}

// 0x71020691a0 (20 bytes) — void, p1=bool, vtable[0xd0]
void FUN_71020691a0(u64 a, u32 p1) {
    u64 mod = *(u64*)(a + 0x188);
    (**(void(**)(u64,u32))(*(u64*)mod + 0xd0))(mod, p1 & 1);
}
