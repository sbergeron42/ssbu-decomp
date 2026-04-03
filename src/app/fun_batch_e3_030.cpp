#include "types.h"

// MEDIUM-tier FUN_* functions — 0x7102 address range, batch e3-030
// Category: framed_vtable_call — direct module pointer dispatch
// Same two sub-patterns as e3-028/029 (plain 9-insn / x10-side-store 10-insn)

// 0x710209b1e0 — plain, vtable[0x150]
u64 FUN_710209b1e0(u64 mod) {
    (**(void(**)(u64))(*(u64*)mod + 0x150))(mod);
    return 0;
}

// 0x710209f2f0 — str x10, vtable[0x2b0]
u64 FUN_710209f2f0(u64 mod) {
    (**(void(**)(u64))(*(u64*)mod + 0x2b0))(mod);
    return 0;
}

// 0x710209fee8 — str x10, vtable[0x60]
u64 FUN_710209fee8(u64 mod) {
    (**(void(**)(u64))(*(u64*)mod + 0x60))(mod);
    return 0;
}

// 0x710209ff90 — plain, vtable[0x88]
u64 FUN_710209ff90(u64 mod) {
    (**(void(**)(u64))(*(u64*)mod + 0x88))(mod);
    return 0;
}

// 0x71020a04c0 — str x10, vtable[0xc8]
u64 FUN_71020a04c0(u64 mod) {
    (**(void(**)(u64))(*(u64*)mod + 0xc8))(mod);
    return 0;
}

// 0x71020a0800 — str x10, vtable[0xf8]
u64 FUN_71020a0800(u64 mod) {
    (**(void(**)(u64))(*(u64*)mod + 0xf8))(mod);
    return 0;
}

// 0x71020a1ae0 — str x10, vtable[0x180]
u64 FUN_71020a1ae0(u64 mod) {
    (**(void(**)(u64))(*(u64*)mod + 0x180))(mod);
    return 0;
}

// 0x71020a1d20 — str x10, vtable[0x198]
u64 FUN_71020a1d20(u64 mod) {
    (**(void(**)(u64))(*(u64*)mod + 0x198))(mod);
    return 0;
}

// 0x71020a2e00 — plain, vtable[0x200]
u64 FUN_71020a2e00(u64 mod) {
    (**(void(**)(u64))(*(u64*)mod + 0x200))(mod);
    return 0;
}

// 0x71020a5c40 — plain, vtable[0x2e8]
u64 FUN_71020a5c40(u64 mod) {
    (**(void(**)(u64))(*(u64*)mod + 0x2e8))(mod);
    return 0;
}

// 0x71020a5da0 — str x10, vtable[0x2f0]
u64 FUN_71020a5da0(u64 mod) {
    (**(void(**)(u64))(*(u64*)mod + 0x2f0))(mod);
    return 0;
}

// 0x71020a5f10 — str x10, vtable[0x300]
u64 FUN_71020a5f10(u64 mod) {
    (**(void(**)(u64))(*(u64*)mod + 0x300))(mod);
    return 0;
}

// 0x71020a7008 — str x10, vtable[0x3a8]
u64 FUN_71020a7008(u64 mod) {
    (**(void(**)(u64))(*(u64*)mod + 0x3a8))(mod);
    return 0;
}

// 0x71020a7160 — str x10, vtable[0x3b8]
u64 FUN_71020a7160(u64 mod) {
    (**(void(**)(u64))(*(u64*)mod + 0x3b8))(mod);
    return 0;
}

// 0x71020a79e0 — plain, vtable[0x70]
u64 FUN_71020a79e0(u64 mod) {
    (**(void(**)(u64))(*(u64*)mod + 0x70))(mod);
    return 0;
}

// 0x71020adef0 — str x10, vtable[0x280]
u64 FUN_71020adef0(u64 mod) {
    (**(void(**)(u64))(*(u64*)mod + 0x280))(mod);
    return 0;
}
