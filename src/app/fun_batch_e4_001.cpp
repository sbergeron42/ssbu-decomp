// Pool-e batch e4_001: mixed small functions from EASY/HARD tiers
// Addresses verified in Ghidra MCP against SSBU 13.0.4

#include "types.h"

// ---- Callee declarations ---------------------------------------------------

extern "C" {
// abort @ 0x71039c20a0
[[noreturn]] void abort();

// Resource release — identified in res_load_helpers.cpp
// FUN_7103540560(FilesystemInfo* fs, u32 handle)
void FUN_7103540560(void*, u32);

// je_free @ 0x710392e590
void FUN_710392e590(void*);

// Base class destructor called from FUN_71016225c0
void FUN_71004cc000(void*);

// Callees for FUN_7101ce7d80
void FUN_71032d6260(void*, s32);
void FUN_7101ce1a40(void*, u32, s32, s32, s32, s32);
}

// ---- Data symbols ----------------------------------------------------------
// All data symbols use hidden visibility to emit adrp+add/ldr instead of GOT

// Vtable pointer for class destroyed by FUN_71016225c0
// [derived: adrp+add loads 0x7105077930 as vtable in destructor at 0x71016225c0]
__attribute__((visibility("hidden"))) extern void* PTR_FUN_7105077930;

// Global FilesystemInfo* singleton
// [derived: adrp+ldr at 0x71016225ec loads value from 0x7105331f20, passed to FUN_7103540560]
__attribute__((visibility("hidden"))) extern void* DAT_7105331f20;

// Vtable pointers for 0x71036defc0 / 0x71036dfcd0 destructors
// [derived: adrp+add in destructor prologue]
__attribute__((visibility("hidden"))) extern void* PTR_FUN_710523a4a8;
__attribute__((visibility("hidden"))) extern void* PTR_FUN_710523a548;

// ---- Functions -------------------------------------------------------------

// 0x7101607630 (12 bytes) — calls abort(), does not return
// [inferred: Ghidra WARNING "Subroutine does not return", bl to abort@0x71039c20a0]
void FUN_7101607630(void)
{
    abort();
}

// 0x7101ce7d80 (64 bytes) — two-call dispatch
// param_1 [inferred: struct with void* at +0x20, used as context ptr]
// Calls FUN_71032d6260(param_1, 0), then FUN_7101ce1a40(*(param_1+0x20), param_2, 9, 4, 1, 0)
void FUN_7101ce7d80(void* param_1, u32 param_2)
{
    FUN_71032d6260(param_1, 0);
    void* ctx = *(void**)((u8*)param_1 + 0x20);
#ifdef MATCHING_HACK_NX_CLANG
    asm("" : "+r"(ctx), "+r"(param_2));
#endif
    FUN_7101ce1a40(ctx, param_2, 9, 4, 1, 0);
}

// 0x71016225c0 (80 bytes) — destructor: set vtable, release handle, call base dtor
// param_1 [inferred: object with vtable at +0, handle(s32) at +0x80c]
//   +0x000 [inferred: vtable ptr, set to PTR_FUN_7105077930]
//   +0x80c [inferred: resource handle (s32), sentinel 0xFFFFFF = invalid]
void FUN_71016225c0(void* param_1)
{
    s32 handle = *(s32*)((u8*)param_1 + 0x80c);
    *(void**)param_1 = &PTR_FUN_7105077930;
    if (handle != 0xffffff) {
        FUN_7103540560(DAT_7105331f20, handle);
        *(s32*)((u8*)param_1 + 0x80c) = 0xffffff;
    }
    FUN_71004cc000(param_1);
}

// 0x71036defc0 (96 bytes) — destructor: set vtable, release handle, conditional free
// param_1 [inferred: object with vtable at +0, handle(s32) at +0xb8, ptr at +0x90/+0x98]
//   +0x000 [inferred: vtable ptr, set to PTR_FUN_710523a4a8]
//   +0x0b8 [inferred: resource handle (s32), sentinel 0xFFFFFF = invalid]
//   +0x090 [inferred: owned pointer, freed if non-null]
//   +0x098 [inferred: set to +0x90 value before free — move semantics]
void FUN_71036defc0(void* param_1)
{
    s32 handle = *(s32*)((u8*)param_1 + 0xb8);
    *(void**)param_1 = &PTR_FUN_710523a4a8;
    if (handle != 0xffffff) {
        FUN_7103540560(DAT_7105331f20, handle);
        *(s32*)((u8*)param_1 + 0xb8) = 0xffffff;
    }
    void* ptr = *(void**)((u8*)param_1 + 0x90);
    if (ptr != nullptr) {
        *(void**)((u8*)param_1 + 0x98) = ptr;
        FUN_710392e590(ptr);
    }
}

// 0x71036dfcd0 (96 bytes) — destructor: set vtable, release handle, conditional free
// param_1 [inferred: object with vtable at +0, handle(s32) at +0x80, ptr at +0x50/+0x58]
//   +0x000 [inferred: vtable ptr, set to PTR_FUN_710523a548]
//   +0x080 [inferred: resource handle (s32), sentinel 0xFFFFFF = invalid]
//   +0x050 [inferred: owned pointer, freed if non-null]
//   +0x058 [inferred: set to +0x50 value before free — move semantics]
void FUN_71036dfcd0(void* param_1)
{
    s32 handle = *(s32*)((u8*)param_1 + 0x80);
    *(void**)param_1 = &PTR_FUN_710523a548;
    if (handle != 0xffffff) {
        FUN_7103540560(DAT_7105331f20, handle);
        *(s32*)((u8*)param_1 + 0x80) = 0xffffff;
    }
    void* ptr = *(void**)((u8*)param_1 + 0x50);
    if (ptr != nullptr) {
        *(void**)((u8*)param_1 + 0x58) = ptr;
        FUN_710392e590(ptr);
    }
}

// 0x710323b580 (96 bytes) — recursive binary tree node cleanup
// Traverses left/right children, releases resource handle, frees node
// param_1 [inferred: tree node with left(u64*) at +0x00, right(u64*) at +0x08,
//          resource handle(s32) at +0x28, sentinel 0xFFFFFF = invalid]
// Calls self recursively on children, then FUN_7103540560 to release handle,
// then FUN_710392e590 (je_free) to free node
void FUN_710323b580(u64* param_1)
{
    if (param_1 == nullptr) return;
    FUN_710323b580(reinterpret_cast<u64*>(*param_1));
    FUN_710323b580(reinterpret_cast<u64*>(param_1[1]));
    if (*(s32*)(param_1 + 5) != 0xffffff) {
        FUN_7103540560(DAT_7105331f20, *(s32*)(param_1 + 5));
        *(s32*)(param_1 + 5) = 0xffffff;
    }
    FUN_710392e590(param_1);
}

// 0x710357c8e0 (96 bytes) — destructor: release nested ptr, free container
// param_1 [inferred: struct with ptr** at +0x18]
//   +0x18 [inferred: pointer to a struct with owned-ptr at +0x00]
// Loads inner ptr, zeroes it, calls FUN_710357bc00 + je_free on it, then je_frees outer
extern "C" {
void FUN_710357bc00(void*);
void FUN_7101ac82a0(void*);
void FUN_7101d30e10(void*);
void FUN_71032d6180(void*);
void FUN_7101ca2a00(void*);
void FUN_7101acec10(void*);
void FUN_7101ae82f0(void*);
}

// Vtable pointers for FUN_7101acb830 / FUN_7101d36880
// [derived: adrp+add in destructor prologue stores vtable]
__attribute__((visibility("hidden"))) extern void* PTR_FUN_71050a8990;
__attribute__((visibility("hidden"))) extern void* PTR_FUN_71050adf58;
__attribute__((visibility("hidden"))) extern void* PTR_FUN_71050ad048;
__attribute__((visibility("hidden"))) extern void* PTR_FUN_71050a8a08;
__attribute__((visibility("hidden"))) extern void* PTR_FUN_71050a9078;

// Global ptr→ptr→bitmask, cleared in destructor pair
// [derived: adrp+ldr in FUN_7101acb830 loads value, then double-deref to u32 bitmask]
__attribute__((visibility("hidden"))) extern void* DAT_710593a988;

void FUN_710357c8e0(void* param_1)
{
    void** inner = *(void***)((u8*)param_1 + 0x18);
    if (inner != nullptr) {
        void* owned = *inner;
        *inner = nullptr;
        if (owned != nullptr) {
            FUN_710357bc00(owned);
            FUN_710392e590(owned);
        }
        FUN_710392e590(inner);
    }
}

// 0x71036f9ee0 (80 bytes) — recursive binary tree node cleanup (variant)
// Same pattern as FUN_710323b580 but with ptr move instead of sentinel release
// param_1 [inferred: tree node with left(u64*) at +0x00, right(u64*) at +0x08,
//          owned-ptr at +0x68, backup-ptr at +0x70]
void FUN_71036f9ee0(u64* param_1)
{
    if (param_1 == nullptr) return;
    FUN_71036f9ee0(reinterpret_cast<u64*>(*param_1));
    FUN_71036f9ee0(reinterpret_cast<u64*>(param_1[1]));
    void* ptr = reinterpret_cast<void*>(param_1[0xd]);
    if (ptr != nullptr) {
        param_1[0xe] = reinterpret_cast<u64>(ptr);
        FUN_710392e590(ptr);
    }
    FUN_710392e590(param_1);
}

// 0x7101acb830 (96 bytes) — destructor: set vtable, clear bitmask, release ptr, call base
// param_1 [inferred: object with vtable at +0, owned-ptr at +0x20 (param_1[4])]
//   +0x000 [inferred: vtable ptr, set to PTR_FUN_71050a8990]
//   +0x020 [inferred: owned pointer, freed if non-null]
// Also clears bit 1 in a global bitmask: *(u32*)(*(*(DAT_710593a988+8))) &= ~2
void FUN_7101acb830(u64* param_1)
{
    *param_1 = reinterpret_cast<u64>(&PTR_FUN_71050a8990);
    u32* bitmask = *(u32**)((u8*)DAT_710593a988 + 8);
    *bitmask = *bitmask & 0xfffffffd;
    void* ptr = reinterpret_cast<void*>(param_1[4]);
    param_1[4] = 0;
    if (ptr != nullptr) {
        FUN_7101ac82a0(ptr);
        FUN_710392e590(ptr);
    }
    FUN_71032d6180(param_1);
}

// 0x7101d36880 (96 bytes) — destructor: same pattern as FUN_7101acb830, different vtable/cleanup
// param_1 [inferred: object with vtable at +0, owned-ptr at +0x20 (param_1[4])]
//   +0x000 [inferred: vtable ptr, set to PTR_FUN_71050adf58]
//   +0x020 [inferred: owned pointer, freed if non-null]
void FUN_7101d36880(u64* param_1)
{
    *param_1 = reinterpret_cast<u64>(&PTR_FUN_71050adf58);
    u32* bitmask = *(u32**)((u8*)DAT_710593a988 + 8);
    *bitmask = *bitmask & 0xfffffffd;
    void* ptr = reinterpret_cast<void*>(param_1[4]);
    param_1[4] = 0;
    if (ptr != nullptr) {
        FUN_7101d30e10(ptr);
        FUN_710392e590(ptr);
    }
    FUN_71032d6180(param_1);
}

// 0x7101ca3b90 (96 bytes) — destructor: bitmask clear + vtable + ptr release + base dtor
void FUN_7101ca3b90(u64* param_1)
{
    *param_1 = reinterpret_cast<u64>(&PTR_FUN_71050ad048);
    u32* bitmask = *(u32**)((u8*)DAT_710593a988 + 8);
    *bitmask = *bitmask & 0xfffffffd;
    void* ptr = reinterpret_cast<void*>(param_1[4]);
    param_1[4] = 0;
    if (ptr != nullptr) {
        FUN_7101ca2a00(ptr);
        FUN_710392e590(ptr);
    }
    FUN_71032d6180(param_1);
}

// 0x7101ace880 (96 bytes) — destructor: same bitmask pattern
void FUN_7101ace880(u64* param_1)
{
    *param_1 = reinterpret_cast<u64>(&PTR_FUN_71050a8a08);
    u32* bitmask = *(u32**)((u8*)DAT_710593a988 + 8);
    *bitmask = *bitmask & 0xfffffffd;
    void* ptr = reinterpret_cast<void*>(param_1[4]);
    param_1[4] = 0;
    if (ptr != nullptr) {
        FUN_7101acec10(ptr);
        FUN_710392e590(ptr);
    }
    FUN_71032d6180(param_1);
}

// 0x7101aea130 (96 bytes) — destructor: same bitmask pattern
void FUN_7101aea130(u64* param_1)
{
    *param_1 = reinterpret_cast<u64>(&PTR_FUN_71050a9078);
    u32* bitmask = *(u32**)((u8*)DAT_710593a988 + 8);
    *bitmask = *bitmask & 0xfffffffd;
    void* ptr = reinterpret_cast<void*>(param_1[4]);
    param_1[4] = 0;
    if (ptr != nullptr) {
        FUN_7101ae82f0(ptr);
        FUN_710392e590(ptr);
    }
    FUN_71032d6180(param_1);
}
