#include "types.h"

// MEDIUM-tier FUN_* functions — 0x71033/0x71037 address range, batch e2-013
// Pool-e worker: x8/x9 register dispatch wrappers decoded from binary

// ---- Forward declarations -----------------------------------------------

extern "C" void FUN_710377a470(u64);

// ---- x8/x9 dispatch wrappers (32 bytes + 8-byte zero padding = 40 bytes each) -------
// Pattern: load args from param_1 fields, set x0=in_x8, call *in_x9
// x8 = hidden "this" arg passed into the function via register
// x9 = function pointer called via blr x9
// Return: (u32) cast of u64 result generates and x0,x0,#0xffffffff

// 0x71037160d8 — ldr w1,[x0,#0x20]; mov x0,x8; blr x9; and x0,x0,#0xffffffff
u64 FUN_71037160d8(u64 param_1)
{
    register u64 in_x8 asm("x8");
    register u64 (*in_x9)(u64, u32) asm("x9");
    asm volatile("" : "+r"(in_x8), "+r"(in_x9));
    return (u32)(*in_x9)(in_x8, *(u32 *)(param_1 + 0x20));
}

// 0x71037165b8 — identical to FUN_71037160d8
u64 FUN_71037165b8(u64 param_1)
{
    register u64 in_x8 asm("x8");
    register u64 (*in_x9)(u64, u32) asm("x9");
    asm volatile("" : "+r"(in_x8), "+r"(in_x9));
    return (u32)(*in_x9)(in_x8, *(u32 *)(param_1 + 0x20));
}

// 0x7103716858 — ldp x1,x2,[x0,#0x20]; ldr x3,[x0,#0x30]; mov x0,x8; blr x9
u64 FUN_7103716858(u64 param_1)
{
    register u64 in_x8 asm("x8");
    register u64 (*in_x9)(u64, u64, u64, u64) asm("x9");
    asm volatile("" : "+r"(in_x8), "+r"(in_x9));
    return (u32)(*in_x9)(in_x8, *(u64 *)(param_1 + 0x20), *(u64 *)(param_1 + 0x28), *(u64 *)(param_1 + 0x30));
}

// 0x71037169a8 — ldp x1,x2,[x0,#0x20]; mov x0,x8; blr x9
u64 FUN_71037169a8(u64 param_1)
{
    register u64 in_x8 asm("x8");
    register u64 (*in_x9)(u64, u64, u64) asm("x9");
    asm volatile("" : "+r"(in_x8), "+r"(in_x9));
    return (u32)(*in_x9)(in_x8, *(u64 *)(param_1 + 0x20), *(u64 *)(param_1 + 0x28));
}

// 0x7103716ca8 — ldr x1,[x0,#0x20] (64-bit); mov x0,x8; blr x9
u64 FUN_7103716ca8(u64 param_1)
{
    register u64 in_x8 asm("x8");
    register u64 (*in_x9)(u64, u64) asm("x9");
    asm volatile("" : "+r"(in_x8), "+r"(in_x9));
    return (u32)(*in_x9)(in_x8, *(u64 *)(param_1 + 0x20));
}

// 0x7103716df8 — identical to FUN_7103716ca8
u64 FUN_7103716df8(u64 param_1)
{
    register u64 in_x8 asm("x8");
    register u64 (*in_x9)(u64, u64) asm("x9");
    asm volatile("" : "+r"(in_x8), "+r"(in_x9));
    return (u32)(*in_x9)(in_x8, *(u64 *)(param_1 + 0x20));
}

// 0x7103716f48 — identical to FUN_7103716ca8
u64 FUN_7103716f48(u64 param_1)
{
    register u64 in_x8 asm("x8");
    register u64 (*in_x9)(u64, u64) asm("x9");
    asm volatile("" : "+r"(in_x8), "+r"(in_x9));
    return (u32)(*in_x9)(in_x8, *(u64 *)(param_1 + 0x20));
}

// ---- x9 double-dereference wrappers -----------------------------------------------

// 0x710335a7e8 — ldr x8,[x9,#8]; ldr x0,[x8]; bl FUN_710377a470; return 0
// Epilogue: ldp → mov w0,wzr → ret (NX Clang ordering, handled by fix_epilogue)
u32 FUN_710335a7e8(void)
{
    register u64 **in_x9 asm("x9");
    asm volatile("" : "+r"(in_x9));
    FUN_710377a470(**(in_x9 + 1));
    return 0;
}
