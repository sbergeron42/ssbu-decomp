#include "types.h"

// pool-e: EASY tier remaining functions
// Small stubs, field accessors, and tail calls

// External function declarations
extern "C" void FUN_710018da80(void*);
extern "C" void FUN_71001d5110(void*);
extern "C" void FUN_71002c2e40(void*);
extern "C" int memset_s(void*, u64, int, u64);

// ---------------------------------------------------------------------------
// 0x710007db90  96B (noop -- single ret)
// ---------------------------------------------------------------------------
void FUN_710007db90_7db90() { }

// ---------------------------------------------------------------------------
// 0x71000b63c0  16B  memset_s(buf, n, 0, n) tail call
// asm: mov w2,wzr; mov x3,x1; b memset_s
// ---------------------------------------------------------------------------
void FUN_71000b63c0_b63c0(void* buf, u64 n) {
    memset_s(buf, n, 0, n);
}

// ---------------------------------------------------------------------------
// 0x7100157cf0  48B  field accessor -- return *(u64*)(p + 0x38)
// asm: ldr x0,[x0,#0x38]; ret
// ---------------------------------------------------------------------------
u64 FUN_7100157cf0_157cf0(void* p) {
    return *reinterpret_cast<u64*>(reinterpret_cast<u8*>(p) + 0x38);
}

// ---------------------------------------------------------------------------
// 0x71001936d0  16B  conditional tail call
// asm: ldr x0,[x0,#0x8]; cbz x0,ret; b FUN_710018da80
// ---------------------------------------------------------------------------
void FUN_71001936d0_1936d0(void* p) {
    void* val = *reinterpret_cast<void**>(reinterpret_cast<u8*>(p) + 0x8);
    if (val != nullptr) {
        FUN_710018da80(val);
    }
}

// ---------------------------------------------------------------------------
// 0x71001df8b0  16B  tail call with offset
// asm: add x0,x0,#0x10; b FUN_71001d5110
// ---------------------------------------------------------------------------
void FUN_71001df8b0_1df8b0(void* p) {
    FUN_71001d5110(reinterpret_cast<u8*>(p) + 0x10);
}

// ---------------------------------------------------------------------------
// 0x71002c28d0  16B  tail call through field
// asm: ldr x0,[x0,#0x10]; b FUN_71002c2e40
// ---------------------------------------------------------------------------
void FUN_71002c28d0_2c28d0(void* p) {
    FUN_71002c2e40(*reinterpret_cast<void**>(reinterpret_cast<u8*>(p) + 0x10));
}
