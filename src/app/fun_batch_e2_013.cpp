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
//
// param_1 [inferred: lua call frame / dispatch arg struct]
//   +0x20 [inferred: first argument slot in dispatch struct]
//   +0x28 [inferred: second argument slot in dispatch struct]
//   +0x30 [inferred: third argument slot in dispatch struct]

// 0x71037160d8 — x8/x9 dispatch: loads u32 arg from +0x20, calls fn ptr in x9
u64 FUN_71037160d8(u64 param_1)
{
    register u64 in_x8 asm("x8");
    register u64 (*in_x9)(u64, u32) asm("x9");
    asm volatile("" : "+r"(in_x8), "+r"(in_x9));
    // +0x20 [inferred: first arg slot, u32 — loaded as w1]
    return (u32)(*in_x9)(in_x8, *(u32 *)(param_1 + 0x20));
}

// 0x71037165b8 — x8/x9 dispatch: identical pattern to FUN_71037160d8
u64 FUN_71037165b8(u64 param_1)
{
    register u64 in_x8 asm("x8");
    register u64 (*in_x9)(u64, u32) asm("x9");
    asm volatile("" : "+r"(in_x8), "+r"(in_x9));
    // +0x20 [inferred: first arg slot, u32 — loaded as w1]
    return (u32)(*in_x9)(in_x8, *(u32 *)(param_1 + 0x20));
}

// 0x7103716858 — x8/x9 dispatch: loads 3 args from +0x20/+0x28/+0x30, calls fn ptr in x9
u64 FUN_7103716858(u64 param_1)
{
    register u64 in_x8 asm("x8");
    register u64 (*in_x9)(u64, u64, u64, u64) asm("x9");
    asm volatile("" : "+r"(in_x8), "+r"(in_x9));
    // +0x20 [inferred: first arg slot, u64 — loaded as x1 via ldp]
    // +0x28 [inferred: second arg slot, u64 — loaded as x2 via ldp]
    // +0x30 [inferred: third arg slot, u64 — loaded as x3]
    return (u32)(*in_x9)(in_x8, *(u64 *)(param_1 + 0x20), *(u64 *)(param_1 + 0x28), *(u64 *)(param_1 + 0x30));
}

// 0x71037169a8 — x8/x9 dispatch: loads 2 args from +0x20/+0x28, calls fn ptr in x9
u64 FUN_71037169a8(u64 param_1)
{
    register u64 in_x8 asm("x8");
    register u64 (*in_x9)(u64, u64, u64) asm("x9");
    asm volatile("" : "+r"(in_x8), "+r"(in_x9));
    // +0x20 [inferred: first arg slot, u64 — loaded as x1 via ldp]
    // +0x28 [inferred: second arg slot, u64 — loaded as x2 via ldp]
    return (u32)(*in_x9)(in_x8, *(u64 *)(param_1 + 0x20), *(u64 *)(param_1 + 0x28));
}

// 0x7103716ca8 — x8/x9 dispatch: loads 1 u64 arg from +0x20, calls fn ptr in x9
u64 FUN_7103716ca8(u64 param_1)
{
    register u64 in_x8 asm("x8");
    register u64 (*in_x9)(u64, u64) asm("x9");
    asm volatile("" : "+r"(in_x8), "+r"(in_x9));
    // +0x20 [inferred: first arg slot, u64 — loaded as x1]
    return (u32)(*in_x9)(in_x8, *(u64 *)(param_1 + 0x20));
}

// 0x7103716df8 — x8/x9 dispatch: identical pattern to FUN_7103716ca8
u64 FUN_7103716df8(u64 param_1)
{
    register u64 in_x8 asm("x8");
    register u64 (*in_x9)(u64, u64) asm("x9");
    asm volatile("" : "+r"(in_x8), "+r"(in_x9));
    // +0x20 [inferred: first arg slot, u64 — loaded as x1]
    return (u32)(*in_x9)(in_x8, *(u64 *)(param_1 + 0x20));
}

// 0x7103716f48 — x8/x9 dispatch: identical pattern to FUN_7103716ca8
u64 FUN_7103716f48(u64 param_1)
{
    register u64 in_x8 asm("x8");
    register u64 (*in_x9)(u64, u64) asm("x9");
    asm volatile("" : "+r"(in_x8), "+r"(in_x9));
    // +0x20 [inferred: first arg slot, u64 — loaded as x1]
    return (u32)(*in_x9)(in_x8, *(u64 *)(param_1 + 0x20));
}

// ---- x9 double-dereference wrappers -----------------------------------------------

// 0x710335a7e8 — x9 double-deref dispatch: loads ptr from *(x9+8), dereferences, calls FUN_710377a470
// in_x9 [inferred: context struct pointer]
//   +0x08 [inferred: pointer to pointer — double-deref to get dispatch target arg]
u32 FUN_710335a7e8(void)
{
    register u64 **in_x9 asm("x9");
    asm volatile("" : "+r"(in_x9));
    // *(in_x9 + 1) = in_x9[1] = *(x9+8) [inferred: pointer to object pointer, double-deref for arg]
    FUN_710377a470(**(in_x9 + 1));
    return 0;
}
