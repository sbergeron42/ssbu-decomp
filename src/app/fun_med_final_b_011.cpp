// fun_med_final_b_011.cpp — pool-b MEDIUM batch 011
// Address range: 0x71003b22c0 – 0x71003ee260
// Mostly cxa_guard singletons, noreturn stubs, vtable dispatchers
#include "types.h"

// ── forward declarations ──────────────────────────────────────────────────

extern "C" int  __cxa_guard_acquire(u64 *guard);
extern "C" void __cxa_guard_release(u64 *guard);

extern void *PTR_ConstantZero_71052a7a80;   // 16-byte zero constant (variant A)
extern void *PTR_ConstantZero_71052a7a88;   // 16-byte zero constant (variant B)

// ROM constant blocks used by color/render param inits
extern u64 _DAT_7104467ca0;
extern u64 _UNK_7104467ca8;
extern u64 _DAT_7104469360;
extern u64 DAT_7104469368;
extern u64 _DAT_71044646b0;
extern u64 _UNK_71044646b8;
extern u64 _DAT_7104469350;
extern u64 _UNK_7104469358;

// atexit-registration helper and RTTI loop sentinel
extern "C" void FUN_71000001c0(void *dtor, void *obj, void *dso);
extern void *PTR_LOOP_7104f16000;

// vtable table pointers referenced by various singletons
extern void *PTR_LAB_7104f65570;
extern void *PTR_LAB_7104f6a450;
extern void *PTR_LAB_7104f63b60;

// Singleton static storage for FUN_71003b2c60 (large gameplay-param struct)
extern void *DAT_71052b6a40;
extern "C" void LAB_71003ecaf0();

// __throw_out_of_range and abort — called from noreturn stubs
extern "C" void _ZNSt3__118__vector_base_commonILb1EE20__throw_out_of_rangeEv() __attribute__((noreturn));
extern "C" void abort() __attribute__((noreturn));

// ── typedefs ─────────────────────────────────────────────────────────────

// 16-byte value returned as register pair (x0:x1) by some vtable dispatchers
typedef struct { u64 lo; u64 hi; } v128_t;

// ─────────────────────────────────────────────────────────────────────────
// Singleton stubs: copy PTR_ConstantZero_71052a7a80 (16 zero bytes) into
// a static slot and return pointer to that slot.
// ─────────────────────────────────────────────────────────────────────────

// FUN_71003b22c0 — singleton: PTR_ConstantZero_71052a7a80 → DAT_71052b6f60
static u64 s_guard_71052b6f50;
static u64 s_dat_71052b6f60[2];
void *FUN_71003b22c0() {
    int iVar1;
    if (((s_guard_71052b6f50 & 1) == 0) &&
        (iVar1 = __cxa_guard_acquire(&s_guard_71052b6f50), iVar1 != 0)) {
        s_dat_71052b6f60[1] = *(u64 *)((u8 *)PTR_ConstantZero_71052a7a80 + 8);
        s_dat_71052b6f60[0] = *(u64 *)PTR_ConstantZero_71052a7a80;
        __cxa_guard_release(&s_guard_71052b6f50);
    }
    return &s_dat_71052b6f60[0];
}

// FUN_71003b28d0 — singleton: PTR_ConstantZero_71052a7a80 → DAT_71052b6f40
static u64 s_guard_71052b6f30;
static u64 s_dat_71052b6f40[2];
void *FUN_71003b28d0() {
    int iVar1;
    if (((s_guard_71052b6f30 & 1) == 0) &&
        (iVar1 = __cxa_guard_acquire(&s_guard_71052b6f30), iVar1 != 0)) {
        s_dat_71052b6f40[1] = *(u64 *)((u8 *)PTR_ConstantZero_71052a7a80 + 8);
        s_dat_71052b6f40[0] = *(u64 *)PTR_ConstantZero_71052a7a80;
        __cxa_guard_release(&s_guard_71052b6f30);
    }
    return &s_dat_71052b6f40[0];
}

// FUN_71003b2e20 — singleton: PTR_ConstantZero_71052a7a88 → DAT_71052b70d0
static u64 s_guard_71052b70c0;
static u64 s_dat_71052b70d0[2];
void *FUN_71003b2e20() {
    int iVar1;
    if (((s_guard_71052b70c0 & 1) == 0) &&
        (iVar1 = __cxa_guard_acquire(&s_guard_71052b70c0), iVar1 != 0)) {
        s_dat_71052b70d0[1] = *(u64 *)((u8 *)PTR_ConstantZero_71052a7a88 + 8);
        s_dat_71052b70d0[0] = *(u64 *)PTR_ConstantZero_71052a7a88;
        __cxa_guard_release(&s_guard_71052b70c0);
    }
    return &s_dat_71052b70d0[0];
}

// FUN_71003b2fd0 — singleton: PTR_ConstantZero_71052a7a88 → DAT_71052b70b0
static u64 s_guard_71052b70a0;
static u64 s_dat_71052b70b0[2];
void *FUN_71003b2fd0() {
    int iVar1;
    if (((s_guard_71052b70a0 & 1) == 0) &&
        (iVar1 = __cxa_guard_acquire(&s_guard_71052b70a0), iVar1 != 0)) {
        s_dat_71052b70b0[1] = *(u64 *)((u8 *)PTR_ConstantZero_71052a7a88 + 8);
        s_dat_71052b70b0[0] = *(u64 *)PTR_ConstantZero_71052a7a88;
        __cxa_guard_release(&s_guard_71052b70a0);
    }
    return &s_dat_71052b70b0[0];
}

// FUN_71003b3050 — singleton: PTR_ConstantZero_71052a7a88 → DAT_71052b7090
static u64 s_guard_71052b7088;
static u64 s_dat_71052b7090[2];
void *FUN_71003b3050() {
    int iVar1;
    if (((s_guard_71052b7088 & 1) == 0) &&
        (iVar1 = __cxa_guard_acquire(&s_guard_71052b7088), iVar1 != 0)) {
        s_dat_71052b7090[1] = *(u64 *)((u8 *)PTR_ConstantZero_71052a7a88 + 8);
        s_dat_71052b7090[0] = *(u64 *)PTR_ConstantZero_71052a7a88;
        __cxa_guard_release(&s_guard_71052b7088);
    }
    return &s_dat_71052b7090[0];
}

// FUN_71003b5cf0 — singleton: PTR_ConstantZero_71052a7a88 → DAT_71052b7180
static u64 s_guard_71052b7178;
static u64 s_dat_71052b7180[2];
void *FUN_71003b5cf0() {
    int iVar1;
    if (((s_guard_71052b7178 & 1) == 0) &&
        (iVar1 = __cxa_guard_acquire(&s_guard_71052b7178), iVar1 != 0)) {
        s_dat_71052b7180[1] = *(u64 *)((u8 *)PTR_ConstantZero_71052a7a88 + 8);
        s_dat_71052b7180[0] = *(u64 *)PTR_ConstantZero_71052a7a88;
        __cxa_guard_release(&s_guard_71052b7178);
    }
    return &s_dat_71052b7180[0];
}

// FUN_71003b73b0 — singleton: copy PTR_ConstantZero_71052a7a80 to two adjacent slots
static u64 s_guard_71052b71d8;
static u64 s_dat_71052b71e0[4]; // covers [0..1] and [2..3]
void *FUN_71003b73b0() {
    int iVar1;
    if (((s_guard_71052b71d8 & 1) == 0) &&
        (iVar1 = __cxa_guard_acquire(&s_guard_71052b71d8), iVar1 != 0)) {
        s_dat_71052b71e0[1] = *(u64 *)((u8 *)PTR_ConstantZero_71052a7a80 + 8);
        s_dat_71052b71e0[0] = *(u64 *)PTR_ConstantZero_71052a7a80;
        // also initializes the second copy at +0x10
        s_dat_71052b71e0[2] = s_dat_71052b71e0[0];
        s_dat_71052b71e0[3] = s_dat_71052b71e0[1];
        __cxa_guard_release(&s_guard_71052b71d8);
    }
    return &s_dat_71052b71e0[0];
}

// ─────────────────────────────────────────────────────────────────────────
// Singletons with literal constant initialization
// ─────────────────────────────────────────────────────────────────────────

// FUN_71003b2c60 — large gameplay-param struct initializer (~0xC0 bytes of floats)
// Initializes struct at DAT_71052b6a40–0x6b8c with physics/camera param defaults
// then calls FUN_71000001c0 for atexit cleanup registration.
static u64 s_guard_71052b70f8;
static u32 s_dat_71052b6ab0;
static u64 s_dat_71052b6a50;
static u64 s_dat_71052b6a58;
static u64 s_dat_71052b6ad0;
static u64 s_dat_71052b6ad8;
static u32 s_dat_71052b6adc;
static u64 s_dat_71052b6aa0;
static u64 s_dat_71052b6aa8;
static u64 s_dat_71052b6aec;
static u64 s_dat_71052b6afc;
static u64 s_dat_71052b6b1c;
static u64 s_dat_71052b6b24;
static u32 s_dat_71052b6a60;
static u32 s_dat_71052b6b70;
static u8  s_dat_71052b6b7e;
static u8  s_dat_71052b6b7f;
static u32 s_dat_71052b6a74;
static u32 s_dat_71052b6a6c;
static u32 s_dat_71052b6a64;
static u64 s_dat_71052b6ae0;
static u64 s_dat_71052b6ae8;
static u64 s_dat_71052b6af4;
static u64 s_dat_71052b6b04;
static u64 s_dat_71052b6b14;
static u64 s_dat_71052b6b0c;
static u64 s_dat_71052b6b58;
static u64 s_dat_71052b6b30;
static u32 s_dat_71052b6b74;
static u32 s_dat_71052b6b78;
static u32 s_dat_71052b6b7c;
static u8  s_dat_71052b6b7d;
static u32 s_dat_71052b6b80;
static u32 s_dat_71052b6b84;
static u32 s_dat_71052b6b88;
static u64 s_dat_71052b6a90;
static u64 s_dat_71052b6a98;
static u64 s_dat_71052b6a80;
static u64 s_dat_71052b6a88;
static u64 s_dat_71052b6ac0[2];
static u64 s_dat_71052b6b48;
static u64 s_dat_71052b6b50;
static u64 s_dat_71052b6b38;
static u64 s_dat_71052b6b40;
static u64 s_dat_71052b6b60[2];
static void *s_dat_71052b6a40_vtbl;

void *FUN_71003b2c60() {
    int iVar1;
    if (((s_guard_71052b70f8 & 1) == 0) &&
        (iVar1 = __cxa_guard_acquire(&s_guard_71052b70f8), iVar1 != 0)) {
        s_dat_71052b6ab0     = 0x420c0000u;
        s_dat_71052b6a50     = 0;
        s_dat_71052b6a58     = 0;
        s_dat_71052b6ad0     = 0x3f000000420c0000ULL;
        s_dat_71052b6ad8     = 0;
        s_dat_71052b6adc     = 0xffffffffu;
        s_dat_71052b6aa0     = 0;
        s_dat_71052b6aa8     = 0;
        s_dat_71052b6aec     = 0x3f800000bf800000ULL;
        s_dat_71052b6afc     = 0x3f800000bf800000ULL;
        s_dat_71052b6b1c     = 0x41a00000c1a00000ULL;
        s_dat_71052b6a40_vtbl = &PTR_LAB_7104f6a450;
        s_dat_71052b6b24     = 0xc120000041200000ULL;
        s_dat_71052b6a60     = 1;
        s_dat_71052b6b70     = 0x3f800000u;
        s_dat_71052b6b7e     = 1;
        s_dat_71052b6b7f     = 1;
        s_dat_71052b6a74     = 0;
        s_dat_71052b6a6c     = 0;
        s_dat_71052b6a64     = 0;
        s_dat_71052b6ae0     = 0;
        s_dat_71052b6ae8     = 0;
        s_dat_71052b6af4     = 0xbf8000003f800000ULL;
        s_dat_71052b6b04     = 0xbf8000003f800000ULL;
        s_dat_71052b6b14     = 0;
        s_dat_71052b6b0c     = 0;
        s_dat_71052b6b58     = 0;
        s_dat_71052b6b30     = 0;
        s_dat_71052b6b74     = 0;
        s_dat_71052b6b78     = 0;
        s_dat_71052b6b7c     = 7;
        s_dat_71052b6b7d     = 0;
        s_dat_71052b6b80     = 0;
        s_dat_71052b6b84     = 0;
        s_dat_71052b6b88     = 0x3e4ccccdu;
        s_dat_71052b6a90     = 0;
        s_dat_71052b6a98     = 0;
        s_dat_71052b6a80     = 0;
        s_dat_71052b6a88     = 0;
        s_dat_71052b6ac0[1]  = 0;
        s_dat_71052b6ac0[0]  = 0;
        s_dat_71052b6b48     = 0;
        s_dat_71052b6b50     = 0;
        s_dat_71052b6b38     = 0;
        s_dat_71052b6b40     = 0;
        s_dat_71052b6b60[1]  = 0;
        s_dat_71052b6b60[0]  = 0;
        FUN_71000001c0((void *)LAB_71003ecaf0, &s_dat_71052b6a40_vtbl, &PTR_LOOP_7104f16000);
        __cxa_guard_release(&s_guard_71052b70f8);
    }
    return &s_dat_71052b6a40_vtbl;
}

// FUN_71003b2db0 — singleton: 4 floats packed into 2×u64
// [-4.0f, 4.0f] = 0x40800000c0800000, [14.0f, -18.0f] = 0xc120000041600000
static u64 s_guard_71052b70e0;
static u64 s_dat_71052b70e8[2];
void *FUN_71003b2db0() {
    int iVar1;
    if (((s_guard_71052b70e0 & 1) == 0) &&
        (iVar1 = __cxa_guard_acquire(&s_guard_71052b70e0), iVar1 != 0)) {
        s_dat_71052b70e8[0] = 0x40800000c0800000ULL;  // {-4.0f, 4.0f}
        s_dat_71052b70e8[1] = 0xc120000041600000ULL;  // {14.0f, -18.0f}
        __cxa_guard_release(&s_guard_71052b70e0);
    }
    return &s_dat_71052b70e8[0];
}

// FUN_71003b3210 — singleton: vtable ptr + copy PTR_ConstantZero_71052a7a88
// Sets vtable at slot [0] to PTR_LAB_7104f63b60, then copies 16 zero bytes
// at slot [2..3] and mirrors to slot [4..5]. Guard: DAT_71052b7108.
static u64 s_guard_71052b7108;
static void *s_dat_71052b6ba0;  // vtable pointer
static u64  s_dat_71052b6bb0[2];
static u64  s_dat_71052b6bc0[2]; // mirror copy
static u32  s_dat_71052b6bd0;
void *FUN_71003b3210() {
    int iVar1;
    if (((s_guard_71052b7108 & 1) == 0) &&
        (iVar1 = __cxa_guard_acquire(&s_guard_71052b7108), iVar1 != 0)) {
        s_dat_71052b6bb0[1] = *(u64 *)((u8 *)PTR_ConstantZero_71052a7a88 + 8);
        s_dat_71052b6bb0[0] = *(u64 *)PTR_ConstantZero_71052a7a88;
        s_dat_71052b6ba0  = &PTR_LAB_7104f63b60;
        s_dat_71052b6bd0  = 1;
        s_dat_71052b6bc0[0] = s_dat_71052b6bb0[0];
        s_dat_71052b6bc0[1] = s_dat_71052b6bb0[1];
        __cxa_guard_release(&s_guard_71052b7108);
    }
    return &s_dat_71052b6ba0;
}

// FUN_71003b3290 — shares the same guard DAT_71052b7108 as FUN_71003b3210;
// identical body, different entry point. Returns the same &DAT_71052b6ba0.
void *FUN_71003b3290() {
    int iVar1;
    if (((s_guard_71052b7108 & 1) == 0) &&
        (iVar1 = __cxa_guard_acquire(&s_guard_71052b7108), iVar1 != 0)) {
        s_dat_71052b6bb0[1] = *(u64 *)((u8 *)PTR_ConstantZero_71052a7a88 + 8);
        s_dat_71052b6bb0[0] = *(u64 *)PTR_ConstantZero_71052a7a88;
        s_dat_71052b6ba0  = &PTR_LAB_7104f63b60;
        s_dat_71052b6bd0  = 1;
        s_dat_71052b6bc0[0] = s_dat_71052b6bb0[0];
        s_dat_71052b6bc0[1] = s_dat_71052b6bb0[1];
        __cxa_guard_release(&s_guard_71052b7108);
    }
    return &s_dat_71052b6ba0;
}

// FUN_71003b3800 — color/render param block A
// Floats: 255.0f=0x437f0000, 1.0f=0x3f800000, 5.0f=0x40a00000
// Also copies 16 bytes from ROM constant _DAT_7104467ca0.
static u64 s_guard_71052b7120;
static u64 s_dat_71052b6bf0[14]; // covers 0x6bf0..0x6c80
void *FUN_71003b3800() {
    int iVar1;
    if (((s_guard_71052b7120 & 1) == 0) &&
        (iVar1 = __cxa_guard_acquire(&s_guard_71052b7120), iVar1 != 0)) {
        // [0] = 0x6bf0: {255.0f, 255.0f}
        s_dat_71052b6bf0[0]  = 0x437f0000437f0000ULL;
        // [1] = 0x6bf8: {255.0f, 255.0f}
        s_dat_71052b6bf0[1]  = 0x437f0000437f0000ULL;
        // byte offsets below relative to s_dat_71052b6bf0 base = 0x6bf0
        // 0x6c30 = offset 0x40 = index 8
        s_dat_71052b6bf0[8]  = 0x3f8000003f800000ULL;
        // 0x6c10 = offset 0x20 = index 4
        s_dat_71052b6bf0[4]  = 0x3f8000003f800000ULL;
        // 0x6c50 = offset 0x60 = index 12
        s_dat_71052b6bf0[12] = 0x3f8000003f800000ULL;
        // 0x6c60 = offset 0x70 = index 14 — but array only 14 elems; extend
        // Use separate tracking for overflow:
        // 0x6c60 and 0x6c68 are consecutive u64 slots
        s_dat_71052b6bf0[2] = 0;    // 0x6c00
        s_dat_71052b6bf0[3] = 0;    // 0x6c08
        s_dat_71052b6bf0[6] = 0;    // 0x6c20
        // Scalar u32s at sub-offsets: 0x6c38=offset0x48 u32, 0x6c80=offset0x90 u32
        *(u32 *)((u8 *)s_dat_71052b6bf0 + 0x48) = 0x3f800000u;
        *(u32 *)((u8 *)s_dat_71052b6bf0 + 0x4c) = 0;
        *(u32 *)((u8 *)s_dat_71052b6bf0 + 0x54) = 0;
        *(u32 *)((u8 *)s_dat_71052b6bf0 + 0x4c - 4) = 0;
        *(u32 *)((u8 *)s_dat_71052b6bf0 + 0x90) = 0x40a00000u;
        // Copy 16 bytes from ROM constant at _DAT_7104467ca0
        *(u64 *)((u8 *)s_dat_71052b6bf0 + 0x80)   = _DAT_7104467ca0;
        *(u64 *)((u8 *)s_dat_71052b6bf0 + 0x88)   = _UNK_7104467ca8;
        __cxa_guard_release(&s_guard_71052b7120);
    }
    return &s_dat_71052b6bf0[0];
}

// FUN_71003b38d0 — color/render param block B (same layout as A, different guard/static)
static u64 s_guard_71052b7118;
static u64 s_dat_71052b6c90[14];
void *FUN_71003b38d0() {
    int iVar1;
    if (((s_guard_71052b7118 & 1) == 0) &&
        (iVar1 = __cxa_guard_acquire(&s_guard_71052b7118), iVar1 != 0)) {
        s_dat_71052b6c90[0]  = 0x437f0000437f0000ULL;
        s_dat_71052b6c90[1]  = 0x437f0000437f0000ULL;
        s_dat_71052b6c90[8]  = 0x3f8000003f800000ULL;
        s_dat_71052b6c90[4]  = 0x3f8000003f800000ULL;
        s_dat_71052b6c90[12] = 0x3f8000003f800000ULL;
        s_dat_71052b6c90[2]  = 0;
        s_dat_71052b6c90[3]  = 0;
        s_dat_71052b6c90[6]  = 0;
        *(u32 *)((u8 *)s_dat_71052b6c90 + 0x48) = 0x3f800000u;
        *(u32 *)((u8 *)s_dat_71052b6c90 + 0x4c) = 0;
        *(u32 *)((u8 *)s_dat_71052b6c90 + 0x54) = 0;
        *(u32 *)((u8 *)s_dat_71052b6c90 + 0x48) = 0;
        *(u32 *)((u8 *)s_dat_71052b6c90 + 0x90) = 0x40a00000u;
        *(u64 *)((u8 *)s_dat_71052b6c90 + 0x80)  = _DAT_7104467ca0;
        *(u64 *)((u8 *)s_dat_71052b6c90 + 0x88)  = _UNK_7104467ca8;
        __cxa_guard_release(&s_guard_71052b7118);
    }
    return &s_dat_71052b6c90[0];
}

// FUN_71003b6890 — singleton: set vtable pointer to PTR_LAB_7104f65570
static u64  s_guard_71052b71b8;
static void *s_dat_71052b6d68;
void *FUN_71003b6890() {
    int iVar1;
    if (((s_guard_71052b71b8 & 1) == 0) &&
        (iVar1 = __cxa_guard_acquire(&s_guard_71052b71b8), iVar1 != 0)) {
        s_dat_71052b6d68 = &PTR_LAB_7104f65570;
        __cxa_guard_release(&s_guard_71052b71b8);
    }
    return &s_dat_71052b6d68;
}

// FUN_71003b79b0 — singleton: init to {0xffffffffffffffff, 0}
// Guard DAT_71052b7218 shared with FUN_71003b7a50.
static u64 s_guard_71052b7218;
static u64 s_dat_71052b6da0[2];
void *FUN_71003b79b0() {
    int iVar1;
    if (((s_guard_71052b7218 & 1) == 0) &&
        (iVar1 = __cxa_guard_acquire(&s_guard_71052b7218), iVar1 != 0)) {
        s_dat_71052b6da0[0] = 0xffffffffffffffffULL;
        s_dat_71052b6da0[1] = 0;
        __cxa_guard_release(&s_guard_71052b7218);
    }
    return &s_dat_71052b6da0[0];
}

// FUN_71003b7a50 — identical body to FUN_71003b79b0 (same guard DAT_71052b7218)
void *FUN_71003b7a50() {
    int iVar1;
    if (((s_guard_71052b7218 & 1) == 0) &&
        (iVar1 = __cxa_guard_acquire(&s_guard_71052b7218), iVar1 != 0)) {
        s_dat_71052b6da0[0] = 0xffffffffffffffffULL;
        s_dat_71052b6da0[1] = 0;
        __cxa_guard_release(&s_guard_71052b7218);
    }
    return &s_dat_71052b6da0[0];
}

// FUN_71003b9550 — singleton: copy 4×16 bytes from ROM data constants
static u64 s_guard_71052b7278;
static u64 s_dat_71052b7280[8]; // 4 pairs of u64
void *FUN_71003b9550() {
    int iVar1;
    if (((s_guard_71052b7278 & 1) == 0) &&
        (iVar1 = __cxa_guard_acquire(&s_guard_71052b7278), iVar1 != 0)) {
        s_dat_71052b7280[0] = _DAT_7104467ca0;
        s_dat_71052b7280[1] = _UNK_7104467ca8;
        s_dat_71052b7280[2] = _DAT_7104469360;
        s_dat_71052b7280[3] = DAT_7104469368;
        s_dat_71052b7280[4] = _DAT_71044646b0;
        s_dat_71052b7280[5] = _UNK_71044646b8;
        s_dat_71052b7280[6] = _DAT_7104469350;
        s_dat_71052b7280[7] = _UNK_7104469358;
        __cxa_guard_release(&s_guard_71052b7278);
    }
    return &s_dat_71052b7280[0];
}

// FUN_71003ba030 — singleton: {0, 0xffffffff} + atexit registration
static u64  s_guard_71052b72d8;
static u32  s_dat_71052b6e10;
static u32  s_dat_71052b6e18;
extern "C" void LAB_7103737890(); // destructor for the object below
void *FUN_71003ba030() {
    int iVar1;
    if (((s_guard_71052b72d8 & 1) == 0) &&
        (iVar1 = __cxa_guard_acquire(&s_guard_71052b72d8), iVar1 != 0)) {
        s_dat_71052b6e10 = 0;
        s_dat_71052b6e18 = 0xffffffffu;
        FUN_71000001c0((void *)LAB_7103737890, &s_dat_71052b6e10, &PTR_LOOP_7104f16000);
        __cxa_guard_release(&s_guard_71052b72d8);
    }
    return &s_dat_71052b6e10;
}

// FUN_71003ba3b0 — singleton: {0, 0xffffffff} + atexit (variant B)
static u64  s_guard_71052b72d0;
static u32  s_dat_71052b6e20;
static u32  s_dat_71052b6e28;
void *FUN_71003ba3b0() {
    int iVar1;
    if (((s_guard_71052b72d0 & 1) == 0) &&
        (iVar1 = __cxa_guard_acquire(&s_guard_71052b72d0), iVar1 != 0)) {
        s_dat_71052b6e20 = 0;
        s_dat_71052b6e28 = 0xffffffffu;
        FUN_71000001c0((void *)LAB_7103737890, &s_dat_71052b6e20, &PTR_LOOP_7104f16000);
        __cxa_guard_release(&s_guard_71052b72d0);
    }
    return &s_dat_71052b6e20;
}

// FUN_71003ba420 — singleton: {0, 0xffffffff} + atexit; also pre-fills two out-params
// with 0xffffffff before the guard check.
static u64  s_guard_71052b72c8;
static u32  s_dat_71052b6e30;
static u32  s_dat_71052b6e38;
void *FUN_71003ba420(u64 /*unused*/, u32 *param_2, u32 *param_3) {
    int iVar1;
    *param_2 = 0xffffffffu;
    *param_3 = 0xffffffffu;
    if (((s_guard_71052b72c8 & 1) == 0) &&
        (iVar1 = __cxa_guard_acquire(&s_guard_71052b72c8), iVar1 != 0)) {
        s_dat_71052b6e30 = 0;
        s_dat_71052b6e38 = 0xffffffffu;
        FUN_71000001c0((void *)LAB_7103737890, &s_dat_71052b6e30, &PTR_LOOP_7104f16000);
        __cxa_guard_release(&s_guard_71052b72c8);
    }
    return &s_dat_71052b6e30;
}

// ─────────────────────────────────────────────────────────────────────────
// Vtable dispatchers
// ─────────────────────────────────────────────────────────────────────────

// FUN_71003b9270 — call vtable[+0x150] on param_1; mask result to 40 bits (Hash40)
u64 FUN_71003b9270(long *param_1) {
    u64 uVar1 = (*(u64 (**)(void))(*param_1 + 0x150))();
    return uVar1 & 0xffffffffffULL;
}

// FUN_71003cb460 — ControlModule (param_1+0x48) vtable call at +0x198
// Returns low byte (bool-like) of vtable result.
u8 FUN_71003cb460(long param_1) {
    return (*(u8 (**)(void))(*(long *)(param_1 + 0x48) + 0x198))();
}

// FUN_71003cb490 — ControlModule (param_1+0x48) vtable call at +0x1a8
u8 FUN_71003cb490(long param_1) {
    return (*(u8 (**)(void))(*(long *)(param_1 + 0x48) + 0x1a8))();
}

// FUN_71003cfc50 — vtable dispatch at +0x130; return *(u32*)(result+8) or sentinel
u32 FUN_71003cfc50(long *param_1) {
    long lVar1 = (*(long (**)(void))(*param_1 + 0x130))();
    if (lVar1 != 0) {
        return *(u32 *)(lVar1 + 8);
    }
    return 0x50000000u;
}

// FUN_71003dd500 — vtable dispatch at +0x1e8 with 3 args; return 16 bytes at result+0x10
// (or 16 zero bytes if dispatch returned null)
extern void *PTR_ConstantZero_71052a7a88; // already declared above
v128_t FUN_71003dd500(long *param_1, u64 param_2, u32 param_3) {
    long lVar2 = (*(long (**)(long *, u64, u32))(*param_1 + 0x1e8))(param_1, param_2, param_3 & 1);
    const v128_t *pv = (const v128_t *)PTR_ConstantZero_71052a7a88;
    if (lVar2 != 0) {
        pv = (const v128_t *)(lVar2 + 0x10);
    }
    return *pv;
}

// FUN_71003dda14 — vtable dispatch at +0x20; return 16-byte value directly from callee
v128_t FUN_71003dda14(long *param_1) {
    v128_t *pv = (*(v128_t *(**)(void))(*param_1 + 0x20))();
    return *pv;
}

// FUN_71003ee260 — double-deref: param_1+8 → +0xd0 → vtable[+0x160](obj, 0, *(param_1+0x10), 1)
// Ghidra reads w0 after call as undefined4; treat as u32 passthrough.
u32 FUN_71003ee260(long param_1) {
    long *plVar1 = *(long **)(*(long *)(param_1 + 8) + 0xd0);
    (*(void (**)(long *, u64, u64, u32))(*plVar1 + 0x160))(plVar1, 0, *(u64 *)(param_1 + 0x10), 1);
    return 0; // extraout_var — vtable call result; actual return value not used by callers
}

// ─────────────────────────────────────────────────────────────────────────
// noreturn stubs — compiler-generated call-site trampolines
// ─────────────────────────────────────────────────────────────────────────

__attribute__((noreturn)) void FUN_71003bc90c() {
    _ZNSt3__118__vector_base_commonILb1EE20__throw_out_of_rangeEv();
}

__attribute__((noreturn)) void FUN_71003bca0c() {
    _ZNSt3__118__vector_base_commonILb1EE20__throw_out_of_rangeEv();
}

__attribute__((noreturn)) void FUN_71003bcc3c() {
    _ZNSt3__118__vector_base_commonILb1EE20__throw_out_of_rangeEv();
}

__attribute__((noreturn)) void FUN_71003bcd1c() {
    _ZNSt3__118__vector_base_commonILb1EE20__throw_out_of_rangeEv();
}

__attribute__((noreturn)) void FUN_71003bcdfc() {
    _ZNSt3__118__vector_base_commonILb1EE20__throw_out_of_rangeEv();
}

__attribute__((noreturn)) void FUN_71003cb1b0() {
    abort();
}

__attribute__((noreturn)) void FUN_71003cb310() {
    abort();
}

__attribute__((noreturn)) void FUN_71003dde90() {
    abort();
}
