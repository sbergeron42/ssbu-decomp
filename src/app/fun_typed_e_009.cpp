// pool-e: AI/L2CValue functions — tree cleanup, container ops, file close
// 10 HARD-tier functions from the AI/L2C address range (0x71037xxxxx)
//
// Many functions in this region appear compiled at -O0 (spill-reload, fallthrough
// branches). Use __attribute__((optnone)) for those — note NX Clang -O0 codegen
// differs from upstream Clang (callee-saved register alloc, fallthrough `b +4`).
// Two functions are -O2 optimized and match well modulo prologue scheduling.

#include "types.h"

// ---- External function declarations ----------------------------------------

extern "C" {
    void jeFree_710392e590(void *p);       // free_default
    void noop_71037aeec0(void *p);       // element destroy
    void FUN_71037aef40(void *p);       // element init/reset
    void FUN_71037b0cb0(void *p);       // base class cleanup
    void FUN_71037b2940(void *p);       // node/buffer free
    void FUN_71037b9d90(void *a, void *b); // pair operation
    void FUN_71037bc700(void *p);       // element destroy (stride 0x14)
    void CloseFile(u64 handle);         // nn::fs::CloseFile
}

// ---- Vtable / RODATA symbols -----------------------------------------------
#define DAT_HIDDEN __attribute__((visibility("hidden")))

extern "C" DAT_HIDDEN u64 DAT_7105240630;  // vtable for FUN_71037b0bd0

// ===========================================================================
// -O2 functions
// ===========================================================================

// 0x710378e2f0  72B — recursive binary tree node deletion (with member cleanup)
void FUN_710378e2f0(u64 *param_1)
{
    if (param_1 == nullptr) return;
    FUN_710378e2f0((u64 *)param_1[0]);
    FUN_710378e2f0((u64 *)param_1[1]);
    if (param_1[0xd] != 0) {
        param_1[0xe] = param_1[0xd];
        jeFree_710392e590((void *)param_1[0xd]);
    }
    jeFree_710392e590(param_1);
}

// 0x71037c68e0  84B — close file handle, return error code via x8 (sret)
// Note: x8 = hidden return pointer (struct return), x0 = file context
void FUN_71037c68e0(u32 *param_1, u64 *param_2)
{
    u32 result;
    if (*(s32 *)((u8 *)param_2 + 0x14) == 0) {
        result = 0xf0001003u;
    } else {
        CloseFile(*(u64 *)((u8 *)param_2 + 0x18));
        result = 0;
        *(u32 *)((u8 *)param_2 + 0x14) = 0;
        *(u64 *)((u8 *)param_2 + 0x20) = 0;
        *(u8 *)((u8 *)param_2 + 0x28) = 0;
        *(u16 *)((u8 *)param_2 + 0x22a) = 0;
    }
    *param_1 = result;
}

// ===========================================================================
// -O0 functions (use optnone to match original unoptimized codegen)
// ===========================================================================

// 0x71037b3b70  44B — destroy single member at +8
__attribute__((optnone))
void FUN_71037b3b70(u64 *param_1)
{
    FUN_71037b2940((void *)param_1[1]);
}

// 0x71037b73f0  72B — conditional buffer free (if buffer != inline sentinel)
__attribute__((optnone))
void FUN_71037b73f0(u64 *param_1)
{
    u64 buf = *param_1;
    u64 sentinel = (u64)(param_1 + 1);
    if (buf - sentinel != 0) {
        FUN_71037b2940((void *)*param_1);
        *param_1 = 0;
    }
}

// 0x71037b36d0  68B — destroy two members + call 71037b3b70
__attribute__((optnone))
void FUN_71037b36d0(u64 *param_1)
{
    FUN_71037b2940((void *)*(u64 *)((u8 *)param_1 + 0x30));
    FUN_71037b2940((void *)*(u64 *)((u8 *)param_1 + 0x40));
    FUN_71037b3b70(param_1);
}

// 0x71037bfdd0  52B — call pair operation twice with different args
__attribute__((optnone))
void FUN_71037bfdd0(u64 *param_1)
{
    FUN_71037b9d90((void *)*(u64 *)((u8 *)param_1 + 0x28),
                   (void *)*(u64 *)((u8 *)param_1 + 0x38));
    FUN_71037b9d90((void *)*(u64 *)((u8 *)param_1 + 0x28),
                   (void *)*(u64 *)((u8 *)param_1 + 0x30));
}

// 0x71037b0bd0  88B — vtable reset + element cleanup + init
__attribute__((optnone))
void FUN_71037b0bd0(u64 *param_1)
{
    FUN_71037b0cb0(param_1);
    *param_1 = (u64)&DAT_7105240630;
    noop_71037aeec0(param_1 + 2);
    *(u32 *)(param_1 + 1) = 0;
    *(u32 *)((u8 *)param_1 + 0xc) = 0;
    FUN_71037aef40(param_1 + 2);
}

// 0x71037af2c0  84B — loop destroy 2 elements at stride 8, then clear
__attribute__((optnone))
void FUN_71037af2c0(u64 *param_1)
{
    u8 *end = (u8 *)param_1 + 0x10;
    u8 *cur = (u8 *)param_1;
    do {
        noop_71037aeec0(cur);
        cur = cur + 8;
    } while (cur - end != 0);
    *(u64 *)((u8 *)param_1 + 0x10) = 0;
    *(u32 *)((u8 *)param_1 + 0x18) = 0;
    *(u32 *)((u8 *)param_1 + 0x1c) = 0;
}

// 0x71037bc630  88B — loop destroy 2 elements at stride 0x14, then cleanup
__attribute__((optnone))
void FUN_71037bc630(u64 *param_1)
{
    u8 *end = (u8 *)param_1 + 0x28;
    u8 *cur = (u8 *)param_1;
    do {
        FUN_71037bc700(cur);
        cur = cur + 0x14;
    } while (cur - end != 0);
    noop_71037aeec0((u8 *)param_1 + 0x28);
    noop_71037aeec0((u8 *)param_1 + 0x30);
}

// 0x71037c0510  80B — call destroy on base, then loop 2 elements at stride 8
__attribute__((optnone))
void FUN_71037c0510(u64 *param_1)
{
    noop_71037aeec0(param_1);
    u8 *cur = (u8 *)param_1 + 8;
    u8 *end = (u8 *)param_1 + 0x18;
    do {
        noop_71037aeec0(cur);
        cur = cur + 8;
    } while (cur - end != 0);
}
