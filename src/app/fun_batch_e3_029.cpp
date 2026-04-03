#include "types.h"

// MEDIUM-tier FUN_* functions — 0x7102 address range, batch e3-029
// Category: framed_vtable_call — direct module pointer dispatch
// Same two sub-patterns as e3-028 (plain 9-insn / x10-side-store 10-insn)
// All: receives module ptr in x8, calls vtable[N] via blr, returns 0

// 0x71020833d0 — str x10, vtable[0xd8]
u64 FUN_71020833d0(u64 mod) {
    (**(void(**)(u64))(*(u64*)mod + 0xd8))(mod);
    return 0;
}

// 0x7102083610 — str x10, vtable[0xe8]
u64 FUN_7102083610(u64 mod) {
    (**(void(**)(u64))(*(u64*)mod + 0xe8))(mod);
    return 0;
}

// 0x7102085b70 — plain, vtable[0x1b0]
u64 FUN_7102085b70(u64 mod) {
    (**(void(**)(u64))(*(u64*)mod + 0x1b0))(mod);
    return 0;
}

// 0x7102085cd0 — str x10, vtable[0x1b8]
u64 FUN_7102085cd0(u64 mod) {
    (**(void(**)(u64))(*(u64*)mod + 0x1b8))(mod);
    return 0;
}

// 0x71020861a0 — plain, vtable[0x1d8]
u64 FUN_71020861a0(u64 mod) {
    (**(void(**)(u64))(*(u64*)mod + 0x1d8))(mod);
    return 0;
}

// 0x71020864b0 — plain, vtable[0x238]
u64 FUN_71020864b0(u64 mod) {
    (**(void(**)(u64))(*(u64*)mod + 0x238))(mod);
    return 0;
}

// 0x7102086560 — plain, vtable[0x240]
u64 FUN_7102086560(u64 mod) {
    (**(void(**)(u64))(*(u64*)mod + 0x240))(mod);
    return 0;
}

// 0x7102086fd0 — str x10, vtable[0x2c0]
u64 FUN_7102086fd0(u64 mod) {
    (**(void(**)(u64))(*(u64*)mod + 0x2c0))(mod);
    return 0;
}

// 0x7102087140 — str x10, vtable[0x2d8]
u64 FUN_7102087140(u64 mod) {
    (**(void(**)(u64))(*(u64*)mod + 0x2d8))(mod);
    return 0;
}

// 0x7102088b40 — str x10, vtable[0x188]
u64 FUN_7102088b40(u64 mod) {
    (**(void(**)(u64))(*(u64*)mod + 0x188))(mod);
    return 0;
}

// 0x7102089340 — plain, vtable[0x48]
u64 FUN_7102089340(u64 mod) {
    (**(void(**)(u64))(*(u64*)mod + 0x48))(mod);
    return 0;
}

// 0x71020899f0 — plain, vtable[0x78]
u64 FUN_71020899f0(u64 mod) {
    (**(void(**)(u64))(*(u64*)mod + 0x78))(mod);
    return 0;
}

// 0x7102089c08 — str x10, vtable[0x80]
u64 FUN_7102089c08(u64 mod) {
    (**(void(**)(u64))(*(u64*)mod + 0x80))(mod);
    return 0;
}

// 0x710208a5f0 — str x10, vtable[0xe0]
u64 FUN_710208a5f0(u64 mod) {
    (**(void(**)(u64))(*(u64*)mod + 0xe0))(mod);
    return 0;
}

// 0x710208a6b0 — plain, vtable[0xe8]
u64 FUN_710208a6b0(u64 mod) {
    (**(void(**)(u64))(*(u64*)mod + 0xe8))(mod);
    return 0;
}

// 0x710208bb90 — plain, vtable[0x58]
u64 FUN_710208bb90(u64 mod) {
    (**(void(**)(u64))(*(u64*)mod + 0x58))(mod);
    return 0;
}

// 0x710208bef0 — str x10, vtable[0x90]
u64 FUN_710208bef0(u64 mod) {
    (**(void(**)(u64))(*(u64*)mod + 0x90))(mod);
    return 0;
}

// 0x710208bfb0 — plain, vtable[0x98]
u64 FUN_710208bfb0(u64 mod) {
    (**(void(**)(u64))(*(u64*)mod + 0x98))(mod);
    return 0;
}

// 0x710208c980 — plain, vtable[0x80]
u64 FUN_710208c980(u64 mod) {
    (**(void(**)(u64))(*(u64*)mod + 0x80))(mod);
    return 0;
}

// 0x710208ca30 — plain, vtable[0x88]
u64 FUN_710208ca30(u64 mod) {
    (**(void(**)(u64))(*(u64*)mod + 0x88))(mod);
    return 0;
}

// 0x710208d900 — str x10, vtable[0x118]
u64 FUN_710208d900(u64 mod) {
    (**(void(**)(u64))(*(u64*)mod + 0x118))(mod);
    return 0;
}

// 0x7102090ff0 — plain, vtable[0x198]
u64 FUN_7102090ff0(u64 mod) {
    (**(void(**)(u64))(*(u64*)mod + 0x198))(mod);
    return 0;
}

// 0x71020916b0 — plain, vtable[0x1c8]
u64 FUN_71020916b0(u64 mod) {
    (**(void(**)(u64))(*(u64*)mod + 0x1c8))(mod);
    return 0;
}

// 0x7102091c20 — plain, vtable[0x218]
u64 FUN_7102091c20(u64 mod) {
    (**(void(**)(u64))(*(u64*)mod + 0x218))(mod);
    return 0;
}

// 0x71020929d0 — plain, vtable[0x50]
u64 FUN_71020929d0(u64 mod) {
    (**(void(**)(u64))(*(u64*)mod + 0x50))(mod);
    return 0;
}

// 0x7102092a80 — plain, vtable[0x68]
u64 FUN_7102092a80(u64 mod) {
    (**(void(**)(u64))(*(u64*)mod + 0x68))(mod);
    return 0;
}

// 0x7102099f00 — plain, vtable[0xb8]
u64 FUN_7102099f00(u64 mod) {
    (**(void(**)(u64))(*(u64*)mod + 0xb8))(mod);
    return 0;
}
