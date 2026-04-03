#include "types.h"

// HARD-tier FUN_* functions — 0x7100 address range, batch hard-d-025
// Pool-d worker: ctors, StationURL lazy-parse accessors, 8x nn::nex tree-free variants (64B each)

#define HIDDEN __attribute__((visibility("hidden")))

// ---- External data -------------------------------------------------------

extern u8 *PTR_DAT_71052a4898 HIDDEN;
extern u8 *PTR_DAT_71052a4e08 HIDDEN;

// ---- External functions --------------------------------------------------

extern void FUN_71001b1970(s64 *);
extern void FUN_71001d6020(s64 *);
extern void FUN_71001e04b0(s64 *);
extern void FUN_71002193d0(s64 *, u64 *);

namespace nn {
namespace nex {
    void MemoryManager_Free(void *);
    void StationURL_Parse(s64);
    u32  InetAddress_GetPortNumber(void *);
    void InetAddress_SetAddress(void *, void *);
}
}

// ---- Functions ---------------------------------------------------------------

// 0x71001b1930 — ctor: zero [8], set vtable, two init helpers (64 bytes)
void FUN_71001b1930(s64 *param_1)
{
    param_1[8] = 0;
    *param_1 = (s64)(PTR_DAT_71052a4898 + 0x10);
    FUN_71001b1970(param_1);
    FUN_71001d6020(param_1);
}

// 0x71001dcfd0 — recursive post-order binary tree free via MemoryManager (64 bytes)
void FUN_71001dcfd0(u64 param_1, u64 *param_2)
{
    if (param_2 != nullptr) {
        FUN_71001dcfd0(param_1, (u64 *)*param_2);
        FUN_71001dcfd0(param_1, (u64 *)param_2[1]);
        nn::nex::MemoryManager_Free((void *)param_2);
    }
}

// 0x71001e0470 — ctor: set vtable, init helper, tail-call tree-free (64 bytes)
void FUN_71001e0470(s64 *param_1)
{
    *param_1 = (s64)(PTR_DAT_71052a4e08 + 0x10);
    FUN_71001e04b0(param_1);
    FUN_71002193d0(param_1 + 5, (u64 *)param_1[6]);
}

// 0x71001e5d60 — StationURL: lazy-parse then GetPortNumber (64 bytes)
u32 FUN_71001e5d60(s64 param_1)
{
    if (*(u8 *)(param_1 + 0x68) == 0) {
        nn::nex::StationURL_Parse(param_1);
    }
    return nn::nex::InetAddress_GetPortNumber(*(void **)(param_1 + 0x8));
}

// 0x71001f2a40 — StationURL: lazy-parse, clear dirty flag, SetAddress (64 bytes)
void FUN_71001f2a40(s64 param_1, void *addr)
{
    if (*(u8 *)(param_1 + 0x68) == 0) {
        nn::nex::StationURL_Parse(param_1);
    }
    *(u8 *)(param_1 + 0x69) = 0;
    nn::nex::InetAddress_SetAddress(*(void **)(param_1 + 0x8), addr);
}

// 0x71002193d0 — recursive post-order binary tree free variant G (64 bytes)
void FUN_71002193d0(u64 param_1, u64 *param_2)
{
    if (param_2 != nullptr) {
        FUN_71002193d0(param_1, (u64 *)*param_2);
        FUN_71002193d0(param_1, (u64 *)param_2[1]);
        nn::nex::MemoryManager_Free((void *)param_2);
    }
}

// 0x710021a3e0 — recursive post-order binary tree free variant A (64 bytes)
void FUN_710021a3e0(u64 param_1, u64 *param_2)
{
    if (param_2 != nullptr) {
        FUN_710021a3e0(param_1, (u64 *)*param_2);
        FUN_710021a3e0(param_1, (u64 *)param_2[1]);
        nn::nex::MemoryManager_Free((void *)param_2);
    }
}

// 0x710021a420 — recursive post-order binary tree free variant B (64 bytes)
void FUN_710021a420(u64 param_1, u64 *param_2)
{
    if (param_2 != nullptr) {
        FUN_710021a420(param_1, (u64 *)*param_2);
        FUN_710021a420(param_1, (u64 *)param_2[1]);
        nn::nex::MemoryManager_Free((void *)param_2);
    }
}

// 0x710021a460 — recursive post-order binary tree free variant C (64 bytes)
void FUN_710021a460(u64 param_1, u64 *param_2)
{
    if (param_2 != nullptr) {
        FUN_710021a460(param_1, (u64 *)*param_2);
        FUN_710021a460(param_1, (u64 *)param_2[1]);
        nn::nex::MemoryManager_Free((void *)param_2);
    }
}

// 0x710021ab20 — recursive post-order binary tree free variant D (64 bytes)
void FUN_710021ab20(u64 param_1, u64 *param_2)
{
    if (param_2 != nullptr) {
        FUN_710021ab20(param_1, (u64 *)*param_2);
        FUN_710021ab20(param_1, (u64 *)param_2[1]);
        nn::nex::MemoryManager_Free((void *)param_2);
    }
}

// 0x710021ab60 — recursive post-order binary tree free variant E (64 bytes)
void FUN_710021ab60(u64 param_1, u64 *param_2)
{
    if (param_2 != nullptr) {
        FUN_710021ab60(param_1, (u64 *)*param_2);
        FUN_710021ab60(param_1, (u64 *)param_2[1]);
        nn::nex::MemoryManager_Free((void *)param_2);
    }
}

// 0x710021aba0 — recursive post-order binary tree free variant F (64 bytes)
void FUN_710021aba0(u64 param_1, u64 *param_2)
{
    if (param_2 != nullptr) {
        FUN_710021aba0(param_1, (u64 *)*param_2);
        FUN_710021aba0(param_1, (u64 *)param_2[1]);
        nn::nex::MemoryManager_Free((void *)param_2);
    }
}
