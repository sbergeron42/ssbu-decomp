// fun_typed_a_004.cpp — HARD-tier destructors and tree walkers
// Worker pool-a: small structural patterns (64–96 bytes)

#include "types.h"

extern "C" {
    void jeFree_710392e590(void*);     // free_default
    void FUN_710171d040(void*);     // member cleanup
    void FUN_7101813d70(void*);     // member cleanup
    void FUN_710181e8a0(void*);     // member cleanup
    void FUN_71017fb680(u64);       // member destructor
    void FUN_71033866e0(u64);       // sub cleanup on offset
}

// --- Data symbols ---
#define DATA_SYM(name) extern "C" __attribute__((visibility("hidden"))) char name[]

DATA_SYM(DAT_7104f6d4c0);     // FUN_7101611e90 vtable
DATA_SYM(DAT_710509cad8);     // FUN_710171cff0 vtable
DATA_SYM(PTR_LAB_71050a0d00); // FUN_7101813f80 vtable
DATA_SYM(PTR_LAB_71050a1208); // FUN_710181e9a0 vtable

// =====================================================================
// 0x710184c5f0 (64 bytes) — Recursive binary tree delete (simplest)
// =====================================================================
void FUN_710184c5f0(u64* node) {
    if (!node) return;
    FUN_710184c5f0((u64*)node[0]);
    FUN_710184c5f0((u64*)node[1]);
    jeFree_710392e590(node);
}

// =====================================================================
// 0x710171cff0 (80 bytes) — Destructor: vtable set + member cleanup + free
// =====================================================================
void FUN_710171cff0(u64* p) {
    u64 old = p[2];
    p[0] = (u64)DAT_710509cad8;
    p[2] = 0;
    if (old) {
        FUN_710171d040((void*)old);
        jeFree_710392e590((void*)old);
    }
    jeFree_710392e590(p);
}

// =====================================================================
// 0x7101813f80 (80 bytes) — Destructor: vtable at [0], member at [0xb]
// =====================================================================
void FUN_7101813f80(u64* p) {
    u64 old = p[0xb];
    p[0] = (u64)PTR_LAB_71050a0d00;
    p[0xb] = 0;
    if (old) {
        FUN_7101813d70((void*)old);
        jeFree_710392e590((void*)old);
    }
    jeFree_710392e590(p);
}

// =====================================================================
// 0x710181e9a0 (80 bytes) — Destructor: vtable at [0], member at [0xb]
// =====================================================================
void FUN_710181e9a0(u64* p) {
    u64 old = p[0xb];
    p[0] = (u64)PTR_LAB_71050a1208;
    p[0xb] = 0;
    if (old) {
        FUN_710181e8a0((void*)old);
        jeFree_710392e590((void*)old);
    }
    jeFree_710392e590(p);
}

// =====================================================================
// 0x7101611e90 (96 bytes) — Linked list walk destructor
// Walks list at p[4], frees each node, then cleans member at p[2]
// =====================================================================
void FUN_7101611e90(u64* p) {
    p[0] = (u64)DAT_7104f6d4c0;
    u64* cur = (u64*)p[4];
    while (cur) {
        u64* next = (u64*)cur[0];
        jeFree_710392e590(cur);
        cur = next;
    }
    u64 old = p[2];
    p[2] = 0;
    if (old) {
        jeFree_710392e590((void*)old);
    }
}

// =====================================================================
// 0x71017fd430 (80 bytes) — Cleanup: calls sub on member+0x178, then destroys member
// =====================================================================
void FUN_71017fd430(u64 p) {
    FUN_71033866e0(*(u64*)(p + 0x58) + 0x178);
    u64 old = *(u64*)(p + 0x58);
    *(u64*)(p + 0x58) = 0;
    if (old) {
        FUN_71017fb680(old);
        jeFree_710392e590((void*)old);
    }
}
