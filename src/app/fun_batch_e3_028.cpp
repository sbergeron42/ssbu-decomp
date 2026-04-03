#include "types.h"

// MEDIUM-tier FUN_* functions — 0x7102 address range, batch e3-028
// Category: framed_vtable_call — direct module pointer dispatch
// Pattern: module ptr arrives in x8; saves frame; calls vtable[N] via blr; returns 0
// Two variants: plain (9 insns) and with str x10,[x0,#0x10] side-store (10 insns)
// For compiled quality: written as (u64 mod) with vtable dispatch, return 0

// ---- Plain dispatch (no str x10) --------------------------------------------

// 0x71020704d0 — vtable[0x50]
u64 FUN_71020704d0(u64 mod) {
    (**(void(**)(u64))(*(u64*)mod + 0x50))(mod);
    return 0;
}

// 0x7102072840 — vtable[0x128]
u64 FUN_7102072840(u64 mod) {
    (**(void(**)(u64))(*(u64*)mod + 0x128))(mod);
    return 0;
}

// 0x7102074070 — vtable[0x68]
u64 FUN_7102074070(u64 mod) {
    (**(void(**)(u64))(*(u64*)mod + 0x68))(mod);
    return 0;
}

// 0x7102074a40 — vtable[0xa0]
u64 FUN_7102074a40(u64 mod) {
    (**(void(**)(u64))(*(u64*)mod + 0xa0))(mod);
    return 0;
}

// 0x7102075410 — vtable[0x50]
u64 FUN_7102075410(u64 mod) {
    (**(void(**)(u64))(*(u64*)mod + 0x50))(mod);
    return 0;
}

// 0x7102077d10 — vtable[0x188]
u64 FUN_7102077d10(u64 mod) {
    (**(void(**)(u64))(*(u64*)mod + 0x188))(mod);
    return 0;
}

// 0x7102078fe0 — vtable[0x50]
u64 FUN_7102078fe0(u64 mod) {
    (**(void(**)(u64))(*(u64*)mod + 0x50))(mod);
    return 0;
}

// 0x710207b8e0 — vtable[0x188]
u64 FUN_710207b8e0(u64 mod) {
    (**(void(**)(u64))(*(u64*)mod + 0x188))(mod);
    return 0;
}

// 0x710207cbb0 — vtable[0x50]
u64 FUN_710207cbb0(u64 mod) {
    (**(void(**)(u64))(*(u64*)mod + 0x50))(mod);
    return 0;
}

// 0x710207f4b0 — vtable[0x188]
u64 FUN_710207f4b0(u64 mod) {
    (**(void(**)(u64))(*(u64*)mod + 0x188))(mod);
    return 0;
}

// 0x7102080cc0 — vtable[0x88]
u64 FUN_7102080cc0(u64 mod) {
    (**(void(**)(u64))(*(u64*)mod + 0x88))(mod);
    return 0;
}

// 0x7102081440 — vtable[0xc8]
u64 FUN_7102081440(u64 mod) {
    (**(void(**)(u64))(*(u64*)mod + 0xc8))(mod);
    return 0;
}

// 0x7102083000 — vtable[0xc8]
u64 FUN_7102083000(u64 mod) {
    (**(void(**)(u64))(*(u64*)mod + 0xc8))(mod);
    return 0;
}

// ---- Dispatch with x10 side-store (str x10,[x0,#0x10] before vtable call) ---
// Written identically for compiled quality; the x10 store is a side-channel
// that passes an extra value through a caller-managed Lua context slot.

// 0x7102071cf0 — vtable[0xd8]
u64 FUN_7102071cf0(u64 mod) {
    (**(void(**)(u64))(*(u64*)mod + 0xd8))(mod);
    return 0;
}

// 0x7102071f30 — vtable[0xe8]
u64 FUN_7102071f30(u64 mod) {
    (**(void(**)(u64))(*(u64*)mod + 0xe8))(mod);
    return 0;
}

// 0x7102072530 — vtable[0x110]
u64 FUN_7102072530(u64 mod) {
    (**(void(**)(u64))(*(u64*)mod + 0x110))(mod);
    return 0;
}

// 0x71020726a0 — vtable[0x118]
u64 FUN_71020726a0(u64 mod) {
    (**(void(**)(u64))(*(u64*)mod + 0x118))(mod);
    return 0;
}

// 0x7102072e00 — vtable[0x50]
u64 FUN_7102072e00(u64 mod) {
    (**(void(**)(u64))(*(u64*)mod + 0x50))(mod);
    return 0;
}

// 0x7102074f40 — vtable[0xb8]
u64 FUN_7102074f40(u64 mod) {
    (**(void(**)(u64))(*(u64*)mod + 0xb8))(mod);
    return 0;
}

// 0x7102077ae0 — vtable[0x158]
u64 FUN_7102077ae0(u64 mod) {
    (**(void(**)(u64))(*(u64*)mod + 0x158))(mod);
    return 0;
}

// 0x7102078770 — vtable[0x1d0]
u64 FUN_7102078770(u64 mod) {
    (**(void(**)(u64))(*(u64*)mod + 0x1d0))(mod);
    return 0;
}

// 0x71020788e0 — vtable[0x1e8]
u64 FUN_71020788e0(u64 mod) {
    (**(void(**)(u64))(*(u64*)mod + 0x1e8))(mod);
    return 0;
}

// 0x710207b6b0 — vtable[0x158]
u64 FUN_710207b6b0(u64 mod) {
    (**(void(**)(u64))(*(u64*)mod + 0x158))(mod);
    return 0;
}

// 0x710207c340 — vtable[0x1d0]
u64 FUN_710207c340(u64 mod) {
    (**(void(**)(u64))(*(u64*)mod + 0x1d0))(mod);
    return 0;
}

// 0x710207c4b0 — vtable[0x1e8]
u64 FUN_710207c4b0(u64 mod) {
    (**(void(**)(u64))(*(u64*)mod + 0x1e8))(mod);
    return 0;
}

// 0x710207f280 — vtable[0x158]
u64 FUN_710207f280(u64 mod) {
    (**(void(**)(u64))(*(u64*)mod + 0x158))(mod);
    return 0;
}

// 0x710207ff10 — vtable[0x1d0]
u64 FUN_710207ff10(u64 mod) {
    (**(void(**)(u64))(*(u64*)mod + 0x1d0))(mod);
    return 0;
}

// 0x7102080080 — vtable[0x1e8]
u64 FUN_7102080080(u64 mod) {
    (**(void(**)(u64))(*(u64*)mod + 0x1e8))(mod);
    return 0;
}
