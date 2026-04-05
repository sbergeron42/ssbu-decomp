#include "types.h"

// External functions
extern "C" void FUN_710018da80(void*);
extern "C" void FUN_71001d5110(void*);
extern "C" void FUN_71002c2e40(void*);

// ============================================================
// Trivial functions: stubs, getters, wrappers
// ============================================================

// 0x710007db90 (4 bytes, no-op stub)
void FUN_710007db90(void) {
}

// 0x7100157cf0 (8 bytes, field getter at +0x38)
void* FUN_7100157cf0(void** self) {
    return self[7];
}

// 0x71001936d0 (16 bytes, conditional tail-call cleanup)
void FUN_71001936d0(void** self) {
    void* sub = self[1];
    if (!sub) return;
    FUN_710018da80(sub);
}

// 0x71001df8b0 (8 bytes, offset wrapper)
void FUN_71001df8b0(void* self) {
    FUN_71001d5110(static_cast<char*>(self) + 0x10);
}

// 0x71002c28d0 (8 bytes, load field + tail-call)
void FUN_71002c28d0(void** self) {
    FUN_71002c2e40(self[2]);
}
