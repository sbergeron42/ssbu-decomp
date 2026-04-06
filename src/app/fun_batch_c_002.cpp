#include "types.h"

// Batch C - 002: vtable dispatch thunks (0x7102 range)
// Pattern: x8 register holds object pointer, dispatches through vtable at various offsets.
// Two variants: (A) plain dispatch, (B) stores x10 into param_1+0x10 before dispatch.

#define VT(m) (*reinterpret_cast<void***>(m))

// ---- Variant B: store result + vtable dispatch --------------------------------
// x10 → param_1+0x10 (coroutine return slot), then vtable call on obj (x8)

// 0x710202c9f0
u32 FUN_710202c9f0(s64 *param_1, s64 param_2)
{
    register s64 *obj asm("x8");
    register u64 result asm("x10");
    asm volatile("" : "+r"(obj));
    asm volatile("" : "+r"(result));
    *(u64 *)((char *)param_1 + 0x10) = result;
    reinterpret_cast<void (*)(s64 *)>(VT(obj)[0x1f8 / 8])(obj);
    return 0;
}

// 0x710202cd00
u32 FUN_710202cd00(s64 *param_1, s64 param_2)
{
    register s64 *obj asm("x8");
    register u64 result asm("x10");
    asm volatile("" : "+r"(obj));
    asm volatile("" : "+r"(result));
    *(u64 *)((char *)param_1 + 0x10) = result;
    reinterpret_cast<void (*)(s64 *)>(VT(obj)[0x210 / 8])(obj);
    return 0;
}

// ---- Variant A: plain vtable dispatch -----------------------------------------

// 0x710202d2c0
u32 FUN_710202d2c0(s64 *param_1)
{
    register s64 *obj asm("x8");
    asm volatile("" : "+r"(obj));
    reinterpret_cast<void (*)(s64 *)>(VT(obj)[0x250 / 8])(obj);
    return 0;
}

// 0x710202d370
u32 FUN_710202d370(s64 *param_1)
{
    register s64 *obj asm("x8");
    asm volatile("" : "+r"(obj));
    reinterpret_cast<void (*)(s64 *)>(VT(obj)[0x258 / 8])(obj);
    return 0;
}

// 0x710202d930
u32 FUN_710202d930(s64 *param_1)
{
    register s64 *obj asm("x8");
    asm volatile("" : "+r"(obj));
    reinterpret_cast<void (*)(s64 *)>(VT(obj)[0x278 / 8])(obj);
    return 0;
}

// 0x710202e020
u32 FUN_710202e020(s64 *param_1)
{
    register s64 *obj asm("x8");
    asm volatile("" : "+r"(obj));
    reinterpret_cast<void (*)(s64 *)>(VT(obj)[0x2c8 / 8])(obj);
    return 0;
}

// ---- Variant B (continued) ---------------------------------------------------

// 0x710202e180
u32 FUN_710202e180(s64 *param_1, s64 param_2)
{
    register s64 *obj asm("x8");
    register u64 result asm("x10");
    asm volatile("" : "+r"(obj));
    asm volatile("" : "+r"(result));
    *(u64 *)((char *)param_1 + 0x10) = result;
    reinterpret_cast<void (*)(s64 *)>(VT(obj)[0x2d0 / 8])(obj);
    return 0;
}

// 0x710202e2f0
u32 FUN_710202e2f0(s64 *param_1, s64 param_2)
{
    register s64 *obj asm("x8");
    register u64 result asm("x10");
    asm volatile("" : "+r"(obj));
    asm volatile("" : "+r"(result));
    *(u64 *)((char *)param_1 + 0x10) = result;
    reinterpret_cast<void (*)(s64 *)>(VT(obj)[0x2d8 / 8])(obj);
    return 0;
}

// 0x710202e630
u32 FUN_710202e630(s64 *param_1, s64 param_2)
{
    register s64 *obj asm("x8");
    register u64 result asm("x10");
    asm volatile("" : "+r"(obj));
    asm volatile("" : "+r"(result));
    *(u64 *)((char *)param_1 + 0x10) = result;
    reinterpret_cast<void (*)(s64 *)>(VT(obj)[0x2f0 / 8])(obj);
    return 0;
}

// ---- Variant A (continued) ---------------------------------------------------

// 0x710202f690
u32 FUN_710202f690(s64 *param_1)
{
    register s64 *obj asm("x8");
    asm volatile("" : "+r"(obj));
    reinterpret_cast<void (*)(s64 *)>(VT(obj)[0x360 / 8])(obj);
    return 0;
}

// 0x710202f870
u32 FUN_710202f870(s64 *param_1)
{
    register s64 *obj asm("x8");
    asm volatile("" : "+r"(obj));
    reinterpret_cast<void (*)(s64 *)>(VT(obj)[0x370 / 8])(obj);
    return 0;
}

// ---- Variant B (continued) ---------------------------------------------------

// 0x710202ff00
u32 FUN_710202ff00(s64 *param_1, s64 param_2)
{
    register s64 *obj asm("x8");
    register u64 result asm("x10");
    asm volatile("" : "+r"(obj));
    asm volatile("" : "+r"(result));
    *(u64 *)((char *)param_1 + 0x10) = result;
    reinterpret_cast<void (*)(s64 *)>(VT(obj)[0x3a8 / 8])(obj);
    return 0;
}

// ---- Variant A (continued) ---------------------------------------------------

// 0x71020305a0
u32 FUN_71020305a0(s64 *param_1)
{
    register s64 *obj asm("x8");
    asm volatile("" : "+r"(obj));
    reinterpret_cast<void (*)(s64 *)>(VT(obj)[0x400 / 8])(obj);
    return 0;
}

// 0x710203a1a0
u32 FUN_710203a1a0(s64 *param_1)
{
    register s64 *obj asm("x8");
    asm volatile("" : "+r"(obj));
    reinterpret_cast<void (*)(s64 *)>(VT(obj)[0x6b8 / 8])(obj);
    return 0;
}

// ---- Variant B (continued) ---------------------------------------------------

// 0x710203a300
u32 FUN_710203a300(s64 *param_1, s64 param_2)
{
    register s64 *obj asm("x8");
    register u64 result asm("x10");
    asm volatile("" : "+r"(obj));
    asm volatile("" : "+r"(result));
    *(u64 *)((char *)param_1 + 0x10) = result;
    reinterpret_cast<void (*)(s64 *)>(VT(obj)[0x6c0 / 8])(obj);
    return 0;
}

// 0x710203a8e0
u32 FUN_710203a8e0(s64 *param_1, s64 param_2)
{
    register s64 *obj asm("x8");
    register u64 result asm("x10");
    asm volatile("" : "+r"(obj));
    asm volatile("" : "+r"(result));
    *(u64 *)((char *)param_1 + 0x10) = result;
    reinterpret_cast<void (*)(s64 *)>(VT(obj)[0x6e0 / 8])(obj);
    return 0;
}

// ---- Variant A (continued) ---------------------------------------------------

// 0x710203ab40
u32 FUN_710203ab40(s64 *param_1)
{
    register s64 *obj asm("x8");
    asm volatile("" : "+r"(obj));
    reinterpret_cast<void (*)(s64 *)>(VT(obj)[0x730 / 8])(obj);
    return 0;
}

// ---- Variant B (continued) ---------------------------------------------------

// 0x710203aca0
u32 FUN_710203aca0(s64 *param_1, s64 param_2)
{
    register s64 *obj asm("x8");
    register u64 result asm("x10");
    asm volatile("" : "+r"(obj));
    asm volatile("" : "+r"(result));
    *(u64 *)((char *)param_1 + 0x10) = result;
    reinterpret_cast<void (*)(s64 *)>(VT(obj)[0x750 / 8])(obj);
    return 0;
}

// ---- Variant A (continued) ---------------------------------------------------

// 0x710203ae90
u32 FUN_710203ae90(s64 *param_1)
{
    register s64 *obj asm("x8");
    asm volatile("" : "+r"(obj));
    reinterpret_cast<void (*)(s64 *)>(VT(obj)[0x798 / 8])(obj);
    return 0;
}

// 0x710203af40
u32 FUN_710203af40(s64 *param_1)
{
    register s64 *obj asm("x8");
    asm volatile("" : "+r"(obj));
    reinterpret_cast<void (*)(s64 *)>(VT(obj)[0x7a0 / 8])(obj);
    return 0;
}

// ---- Variant B (continued) ---------------------------------------------------

// 0x710203b0a0
u32 FUN_710203b0a0(s64 *param_1, s64 param_2)
{
    register s64 *obj asm("x8");
    register u64 result asm("x10");
    asm volatile("" : "+r"(obj));
    asm volatile("" : "+r"(result));
    *(u64 *)((char *)param_1 + 0x10) = result;
    reinterpret_cast<void (*)(s64 *)>(VT(obj)[0x7a8 / 8])(obj);
    return 0;
}

// ---- Variant A (continued) ---------------------------------------------------

// 0x710203b2d0
u32 FUN_710203b2d0(s64 *param_1)
{
    register s64 *obj asm("x8");
    asm volatile("" : "+r"(obj));
    reinterpret_cast<void (*)(s64 *)>(VT(obj)[0x7b8 / 8])(obj);
    return 0;
}

// ---- Variant B (continued) ---------------------------------------------------

// 0x710203b7d0
u32 FUN_710203b7d0(s64 *param_1, s64 param_2)
{
    register s64 *obj asm("x8");
    register u64 result asm("x10");
    asm volatile("" : "+r"(obj));
    asm volatile("" : "+r"(result));
    *(u64 *)((char *)param_1 + 0x10) = result;
    reinterpret_cast<void (*)(s64 *)>(VT(obj)[0x7d0 / 8])(obj);
    return 0;
}

// 0x710203b9c4
u32 FUN_710203b9c4(s64 *param_1, s64 param_2)
{
    register s64 *obj asm("x8");
    register u64 result asm("x10");
    asm volatile("" : "+r"(obj));
    asm volatile("" : "+r"(result));
    *(u64 *)((char *)param_1 + 0x10) = result;
    reinterpret_cast<void (*)(s64 *)>(VT(obj)[0x7d8 / 8])(obj);
    return 0;
}

// 0x710203bb30
u32 FUN_710203bb30(s64 *param_1, s64 param_2)
{
    register s64 *obj asm("x8");
    register u64 result asm("x10");
    asm volatile("" : "+r"(obj));
    asm volatile("" : "+r"(result));
    *(u64 *)((char *)param_1 + 0x10) = result;
    reinterpret_cast<void (*)(s64 *)>(VT(obj)[0x7f8 / 8])(obj);
    return 0;
}

// 0x710203bdd0
u32 FUN_710203bdd0(s64 *param_1, s64 param_2)
{
    register s64 *obj asm("x8");
    register u64 result asm("x10");
    asm volatile("" : "+r"(obj));
    asm volatile("" : "+r"(result));
    *(u64 *)((char *)param_1 + 0x10) = result;
    reinterpret_cast<void (*)(s64 *)>(VT(obj)[0x818 / 8])(obj);
    return 0;
}

// ---- Variant A: smaller vtable offsets ----------------------------------------

// 0x710203dcf0
u32 FUN_710203dcf0(s64 *param_1)
{
    register s64 *obj asm("x8");
    asm volatile("" : "+r"(obj));
    reinterpret_cast<void (*)(s64 *)>(VT(obj)[0x58 / 8])(obj);
    return 0;
}

// ---- Variant B (continued) ---------------------------------------------------

// 0x710203de50
u32 FUN_710203de50(s64 *param_1, s64 param_2)
{
    register s64 *obj asm("x8");
    register u64 result asm("x10");
    asm volatile("" : "+r"(obj));
    asm volatile("" : "+r"(result));
    *(u64 *)((char *)param_1 + 0x10) = result;
    reinterpret_cast<void (*)(s64 *)>(VT(obj)[0x70 / 8])(obj);
    return 0;
}

// 0x710203f810
u32 FUN_710203f810(s64 *param_1, s64 param_2)
{
    register s64 *obj asm("x8");
    register u64 result asm("x10");
    asm volatile("" : "+r"(obj));
    asm volatile("" : "+r"(result));
    *(u64 *)((char *)param_1 + 0x10) = result;
    reinterpret_cast<void (*)(s64 *)>(VT(obj)[0x188 / 8])(obj);
    return 0;
}

// ---- Variant A (continued) ---------------------------------------------------

// 0x7102040ae0
u32 FUN_7102040ae0(s64 *param_1)
{
    register s64 *obj asm("x8");
    asm volatile("" : "+r"(obj));
    reinterpret_cast<void (*)(s64 *)>(VT(obj)[0x80 / 8])(obj);
    return 0;
}
