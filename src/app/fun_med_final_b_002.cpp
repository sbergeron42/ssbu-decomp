// SSBU 13.0.4 — MEDIUM-tier decompilation batch B-002
// Address range: 0x7100033190 – 0x710009e130

#include "types.h"

// ---------------------------------------------------------------------------
// 0x7100033190  size=48  FUN_7100033190
// If flags & 0x49c0: dispatch vtable call on param_1+0xb8
// ---------------------------------------------------------------------------
extern void *PTR_DAT_71052a24e8;

void FUN_7100033190(long param_1, u32 param_2)
{
    if (param_2 & 0x49c0u) {
        typedef void (*fn_t)(u64, int);
        fn_t fn = *(fn_t *)PTR_DAT_71052a24e8;
        fn(*(u64 *)(param_1 + 0xb8), 1);
    }
}

// ---------------------------------------------------------------------------
// 0x7100037790  size=32  FUN_7100037790
// Table lookup: index into 8-byte entries at DAT_71044705bc
// ---------------------------------------------------------------------------
extern u8 DAT_71044705bc;

u32 FUN_7100037790(u64 param_1)
{
    return *(u32 *)(&DAT_71044705bc + (param_1 & 0xffffffff) * 8);
}

// ---------------------------------------------------------------------------
// 0x7100037cb0  size=112  FUN_7100037cb0
// Thread-safe singleton init (cxa_guard) for a 9-field zero struct
// ---------------------------------------------------------------------------
extern u8 DAT_71052aa330;
extern u64 DAT_71052aa338;
extern u64 DAT_71052aa340;
extern u64 DAT_71052aa348;
extern u64 DAT_71052aa350;
extern u64 DAT_71052aa358;
extern u64 DAT_71052aa360;
extern u64 DAT_71052aa368;
extern u64 DAT_71052aa370;
extern u64 DAT_71052aa378;
int __cxa_guard_acquire(void *);
void __cxa_guard_release(void *);

u64 *FUN_7100037cb0(void)
{
    if (!(DAT_71052aa330 & 1)) {
        if (__cxa_guard_acquire(&DAT_71052aa330) != 0) {
            DAT_71052aa370 = 0; DAT_71052aa378 = 0;
            DAT_71052aa360 = 0; DAT_71052aa368 = 0;
            DAT_71052aa338 = 0; DAT_71052aa350 = 0;
            DAT_71052aa358 = 0; DAT_71052aa340 = 0;
            DAT_71052aa348 = 0;
            __cxa_guard_release(&DAT_71052aa330);
        }
    }
    return &DAT_71052aa338;
}

// ---------------------------------------------------------------------------
// 0x71000380b0  size=80  FUN_71000380b0
// If lVar1+0x30 != lVar1+0x20: clear lVar1+0x30; else call FUN_71000339b0
// ---------------------------------------------------------------------------
void FUN_71000339b0(void);

void FUN_71000380b0(long param_1)
{
    long lVar1 = *(long *)(param_1 + 0x28);
    if (*(long *)(lVar1 + 0x30) != *(long *)(lVar1 + 0x20)) {
        *(u64 *)(lVar1 + 0x30) = 0;
        return;
    }
    FUN_71000339b0();
    *(u64 *)(lVar1 + 0x30) = 0;
}

// ---------------------------------------------------------------------------
// 0x7100038120  size=48  FUN_7100038120
// Zero-initialize 15-slot uint64 array
// ---------------------------------------------------------------------------
void FUN_7100038120(u64 *param_1)
{
    param_1[0]  = 0; param_1[1]  = 0; param_1[2]  = 0;
    param_1[3]  = 0; param_1[4]  = 0; param_1[5]  = 0;
    param_1[6]  = 0; param_1[7]  = 0; param_1[8]  = 0;
    param_1[9]  = 0; param_1[10] = 0; param_1[11] = 0;
    param_1[12] = 0; param_1[13] = 0; param_1[14] = 0;
}

// ---------------------------------------------------------------------------
// 0x7100038210  size=64  FUN_7100038210
// Release handle via vtable, clear fields
// ---------------------------------------------------------------------------
extern void *PTR_DAT_71052a2c78;

void FUN_7100038210(u8 *param_1)
{
    typedef void (*fn_t)(u64);
    fn_t fn = *(fn_t *)PTR_DAT_71052a2c78;
    fn(*(u64 *)(param_1 + 8));
    *(u64 *)(param_1 + 8) = 0;
    *param_1 = 0;
}

// ---------------------------------------------------------------------------
// 0x7100039e30  size=32  FUN_7100039e30
// Zero-initialize 9-slot uint64 array
// ---------------------------------------------------------------------------
void FUN_7100039e30(u64 *param_1)
{
    param_1[0] = 0; param_1[1] = 0; param_1[2] = 0;
    param_1[3] = 0; param_1[4] = 0; param_1[5] = 0;
    param_1[6] = 0; param_1[7] = 0; param_1[8] = 0;
}

// ---------------------------------------------------------------------------
// 0x710003a0e0  size=32  FUN_710003a0e0
// Zero-initialize 27-slot uint64 array
// ---------------------------------------------------------------------------
void FUN_710003a0e0(u64 *param_1)
{
    for (int i = 0; i <= 0x1a; i++)
        param_1[i] = 0;
}

// ---------------------------------------------------------------------------
// 0x710003a200  size=64  FUN_710003a200
// Release handle via alternate vtable ptr, clear fields
// ---------------------------------------------------------------------------
extern void *PTR_DAT_71052a2ae8;

void FUN_710003a200(u8 *param_1)
{
    typedef void (*fn_t)(u64);
    fn_t fn = *(fn_t *)PTR_DAT_71052a2ae8;
    fn(*(u64 *)(param_1 + 8));
    *(u64 *)(param_1 + 8) = 0;
    *param_1 = 0;
}

// ---------------------------------------------------------------------------
// 0x710003a240  size=32  FUN_710003a240
// Zero-initialize 9-slot uint64 array
// ---------------------------------------------------------------------------
void FUN_710003a240(u64 *param_1)
{
    param_1[0] = 0; param_1[1] = 0; param_1[2] = 0;
    param_1[3] = 0; param_1[4] = 0; param_1[5] = 0;
    param_1[6] = 0; param_1[7] = 0; param_1[8] = 0;
}

// ---------------------------------------------------------------------------
// 0x710003a3b0  size=32  FUN_710003a3b0
// Zero-initialize 3 fields of a small struct
// ---------------------------------------------------------------------------
void FUN_710003a3b0(u8 *param_1)
{
    *param_1 = 0;
    *(u64 *)(param_1 + 8) = 0;
    *(u64 *)(param_1 + 0x10) = 0;
}

// ---------------------------------------------------------------------------
// 0x710003a3c0  size=32  FUN_710003a3c0
// Zero-initialize 9-slot uint64 array
// ---------------------------------------------------------------------------
void FUN_710003a3c0(u64 *param_1)
{
    param_1[0] = 0; param_1[1] = 0; param_1[2] = 0;
    param_1[3] = 0; param_1[4] = 0; param_1[5] = 0;
    param_1[6] = 0; param_1[7] = 0; param_1[8] = 0;
}

// ---------------------------------------------------------------------------
// 0x710003a4e0  size=32  FUN_710003a4e0
// Zero-initialize 9-slot uint64 array
// ---------------------------------------------------------------------------
void FUN_710003a4e0(u64 *param_1)
{
    param_1[0] = 0; param_1[1] = 0; param_1[2] = 0;
    param_1[3] = 0; param_1[4] = 0; param_1[5] = 0;
    param_1[6] = 0; param_1[7] = 0; param_1[8] = 0;
}

// ---------------------------------------------------------------------------
// 0x710003a7d0  size=64  FUN_710003a7d0
// Zero-initialize 24-slot uint64 array
// ---------------------------------------------------------------------------
void FUN_710003a7d0(u64 *param_1)
{
    for (int i = 0; i <= 0x17; i++)
        param_1[i] = 0;
}

// ---------------------------------------------------------------------------
// 0x710003aac0  size=48  FUN_710003aac0
// Init doubly-linked-list-style node with vtable ptr from PTR_DAT_71052a3328
// ---------------------------------------------------------------------------
extern u8 *PTR_DAT_71052a3328;

void FUN_710003aac0(long *param_1, u32 param_2, u32 param_3)
{
    param_1[2] = 0;
    *(u32 *)(param_1 + 3) = param_2;
    *(u32 *)((u8 *)param_1 + 0x1c) = 2;
    *(u32 *)(param_1 + 4) = param_3;
    *(u64 *)((u8 *)param_1 + 0x24) = 0;
    param_1[6] = 0;
    param_1[7] = 0;
    *param_1 = (long)(PTR_DAT_71052a3328 + 0x10);
    param_1[1] = 0;
}

// ---------------------------------------------------------------------------
// 0x710003ac20  size=32  FUN_710003ac20
// Set address type (1 or 2) and store param_2 at +0x28
// ---------------------------------------------------------------------------
void FUN_710003ac20(long param_1, int param_2)
{
    u32 type = (param_2 > 0xffff) ? 2u : 1u;
    *(u32 *)(param_1 + 0x1c) = type;
    *(int *)(param_1 + 0x28) = param_2;
}

// ---------------------------------------------------------------------------
// 0x710003bc80  size=32  FUN_710003bc80
// Init node with vtable from PTR_DAT_71052a3390; param_1[1] = 0x1f00000000
// ---------------------------------------------------------------------------
extern u8 *PTR_DAT_71052a3390;

void FUN_710003bc80(long *param_1)
{
    param_1[2] = 0;
    param_1[3] = 0;
    *param_1 = (long)(PTR_DAT_71052a3390 + 0x10);
    param_1[1] = 0x1f00000000LL;
    *(u32 *)(param_1 + 4) = 0;
}

// ---------------------------------------------------------------------------
// 0x710003c350  size=640  FUN_710003c350
// State machine step: for state 0/2 dispatch vtable +0xd8 and +0x98; 4/6 → 0
// ---------------------------------------------------------------------------
u64 FUN_710003c350(long *param_1)
{
    switch ((int)param_1[1]) {
    case 0: case 2:
        (*(void (*)(long *, int))(*param_1 + 0xd8))(param_1, 1);
        (*(void (*)(long *))(*param_1 + 0x98))(param_1);
        break;
    case 4: case 6:
        return 0;
    }
    return 1;
}

// ---------------------------------------------------------------------------
// 0x710003de30  size=240  FUN_710003de30
// State machine step (states 0/2/5 active; 4/6 idle)
// ---------------------------------------------------------------------------
u64 FUN_710003de30(long *param_1)
{
    switch ((int)param_1[1]) {
    case 0: case 2: case 5:
        (*(void (*)(long *, int))(*param_1 + 0xd8))(param_1, 1);
        (*(void (*)(long *))(*param_1 + 0x98))(param_1);
        break;
    case 4: case 6:
        return 0;
    }
    return 1;
}

// ---------------------------------------------------------------------------
// 0x710003e030  size=240  FUN_710003e030
// State machine step (identical pattern to FUN_710003de30)
// ---------------------------------------------------------------------------
u64 FUN_710003e030(long *param_1)
{
    switch ((int)param_1[1]) {
    case 0: case 2: case 5:
        (*(void (*)(long *, int))(*param_1 + 0xd8))(param_1, 1);
        (*(void (*)(long *))(*param_1 + 0x98))(param_1);
        break;
    case 4: case 6:
        return 0;
    }
    return 1;
}

// ---------------------------------------------------------------------------
// 0x7100044c70  size=32  FUN_7100044c70
// Init connection fields: set active flag, clear addr/port, store handle
// ---------------------------------------------------------------------------
void FUN_7100044c70(long param_1, u64 param_2)
{
    *(u8 *)(param_1 + 0x18c) = 1;
    *(u64 *)(param_1 + 400) = 0;
    *(u16 *)(param_1 + 0x198) = 0;
    *(u64 *)(param_1 + 0xc0) = param_2;
}

// ---------------------------------------------------------------------------
// 0x7100044dd0  size=64  FUN_7100044dd0
// Update addr+port if changed; returns 1 on change, 0 if same
// ---------------------------------------------------------------------------
u32 FUN_7100044dd0(long param_1, long param_2, s16 param_3)
{
    if (*(long *)(param_1 + 400) == param_2 && *(s16 *)(param_1 + 0x198) == param_3)
        return 0;
    *(long *)(param_1 + 400) = param_2;
    *(s16 *)(param_1 + 0x198) = param_3;
    return 1;
}

// ---------------------------------------------------------------------------
// 0x7100047c70  size=32  FUN_7100047c70
// Doubly-linked list insert (circular): splice param_2 after param_1
// ---------------------------------------------------------------------------
void FUN_7100047c70(long *param_1, long param_2)
{
    long *next = (long *)(param_2 + 8);
    long old_next = *next;
    *next = *param_1;
    *(long **)(old_next + 8) = param_1;
    *(long **)(*param_1 + 8) = next;
    *param_1 = old_next;
}

// ---------------------------------------------------------------------------
// 0x710004a590  size=48  FUN_710004a590
// Bounds-checked array element access by 1-based index
// ---------------------------------------------------------------------------
extern void *PTR_DAT_71052a3648;

u64 FUN_710004a590(long *param_1)
{
    int idx = (int)param_1[1];
    if (idx < 1 || *(int *)PTR_DAT_71052a3648 < idx)
        return 0;
    return *(u64 *)(*param_1 + (long)(idx - 1) * 8);
}

// ---------------------------------------------------------------------------
// 0x710004c5e0  size=32  FUN_710004c5e0
// Array element access: base + (index - param_2) * 8
// ---------------------------------------------------------------------------
u64 FUN_710004c5e0(long *param_1, u32 param_2)
{
    return *(u64 *)(*param_1 + (long)((int)param_1[1] - (int)param_2) * 8);
}

// ---------------------------------------------------------------------------
// 0x7100055470  size=32  FUN_7100055470
// Get base + offset from nested struct pointer; returns 0 if null
// ---------------------------------------------------------------------------
long FUN_7100055470(long param_1, long param_2)
{
    long base = *(long *)(*(long *)(param_2 + 200) + 0x38);
    if (base != 0)
        return base + (u64)*(u32 *)(param_1 + 0x34);
    return 0;
}

// ---------------------------------------------------------------------------
// 0x7100059860  size=48  FUN_7100059860
// Get queue depth minus 1 if first-entry occupied; 0 if no queue
// ---------------------------------------------------------------------------
int FUN_7100059860(long param_1)
{
    if (*(long *)(param_1 + 0xa8) != 0)
        return (u32)*(u16 *)(*(long *)(param_1 + 0xa8) + 8) - (*(int *)(param_1 + 0x60) != 0 ? 1 : 0);
    return 0;
}

// ---------------------------------------------------------------------------
// 0x7100059890  size=64  FUN_7100059890
// Get pointer into queue at param_1+0xa8, offset by first-entry status
// ---------------------------------------------------------------------------
long FUN_7100059890(long param_1)
{
    long q = *(long *)(param_1 + 0xa8);
    if (q == 0)
        return 0;
    if (*(int *)(param_1 + 0x60) != 0) {
        if (*(u16 *)(q + 8) != 1)
            return q + 0x18;
#ifdef MATCHING_HACK_NX_CLANG
        asm("");
#endif
        return 0;
    }
    return q + 0xc;
}

// ---------------------------------------------------------------------------
// 0x7100060e80  size=32  FUN_7100060e80
// Clear high slots of ushort array, set low bits of [0] to 0x90
// ---------------------------------------------------------------------------
void FUN_7100060e80(u16 *param_1)
{
    param_1[4] = 0; param_1[5] = 0; param_1[6] = 0; param_1[7] = 0;
    param_1[0] = (param_1[0] & 0xe000u) | 0x90u;
}

// ---------------------------------------------------------------------------
// 0x7100060ea0  size=64  FUN_7100060ea0
// Conditional set of 64-bit value at +4; update low byte flag 0x90
// ---------------------------------------------------------------------------
void FUN_7100060ea0(u16 *param_1, long param_2)
{
    param_1[4] = 0; param_1[5] = 0; param_1[6] = 0; param_1[7] = 0;
    if (param_2 != 0) {
        u16 old = param_1[0];
        *(long *)(param_1 + 4) = param_2;
        param_1[0] = (old & 0xe000u) | 0x90u;
    } else {
        param_1[0] &= 0xe0ffu;
    }
}

// ---------------------------------------------------------------------------
// 0x7100060f20  size=32  FUN_7100060f20
// Pack two 2-bit fields into low nibble of param_1[0]
// ---------------------------------------------------------------------------
void FUN_7100060f20(u16 *param_1, u16 param_2, u32 param_3)
{
    *param_1 = (param_2 & 3u) | (u16)((param_3 & 3u) << 2) | (*param_1 & 0xfff0u);
}

// ---------------------------------------------------------------------------
// 0x7100060f40  size=32  FUN_7100060f40
// Pack 3-bit and 1-bit fields into bits [4:7] of param_1[0]
// ---------------------------------------------------------------------------
void FUN_7100060f40(u16 *param_1, u32 param_2, u32 param_3)
{
    *param_1 = (u16)((param_2 & 7u) << 4) | (u16)((param_3 & 1u) << 7) | (*param_1 & 0xff0fu);
}

// ---------------------------------------------------------------------------
// 0x7100065800  size=64  FUN_7100065800
// Vtable dispatch: call slot +0x58 (no args), then slot +0x20 with bool flag
// ---------------------------------------------------------------------------
void FUN_7100065800(long *param_1, u64 param_2, u32 param_3)
{
    (*(void (*)(void))(*param_1 + 0x58))();
    (*(void (*)(long *, bool))(*param_1 + 0x20))(param_1, (param_3 & 1) != 0);
}

// ---------------------------------------------------------------------------
// 0x7100066040  size=32  FUN_7100066040
// Returns whether string pointer at param_1+0x68 is non-empty
// ---------------------------------------------------------------------------
u64 FUN_7100066040(u64 param_1)
{
    if (param_1 != 0)
        return (u64)(**(char **)(param_1 + 0x68) != '\0');
    return param_1;
}

// ---------------------------------------------------------------------------
// 0x7100078b00  size=32  FUN_7100078b00
// Circular doubly-linked list splice: insert param_2 node at param_1+0x38
// ---------------------------------------------------------------------------
void FUN_7100078b00(long param_1, long param_2)
{
    long *ins = (long *)(param_2 + 0x48);
    long old  = *ins;
    long *dst = (long *)(param_1 + 0x38);
    *ins = *dst;
    *(long **)(old + 8) = dst;
    *(long **)(*dst + 8) = ins;
    *dst = old;
}

// ---------------------------------------------------------------------------
// 0x7100078b20  size=48  FUN_7100078b20
// Initialize 8-slot struct: set all-ones, float 1.0 constants, zero rest
// ---------------------------------------------------------------------------
void FUN_7100078b20(u64 *param_1)
{
    param_1[0] = 0xffffffffffffffffULL;
    param_1[1] = 0x3f80000000000000ULL;
    *(u16 *)(param_1 + 7) = 0xff00u;
    param_1[2] = 0x3f800000ULL;
    param_1[3] = 0; param_1[4] = 0; param_1[5] = 0; param_1[6] = 0;
}

// ---------------------------------------------------------------------------
// 0x7100078f80  size=64  FUN_7100078f80
// Zero-initialize 24-slot struct; also clear uint32 at +0xc
// ---------------------------------------------------------------------------
void FUN_7100078f80(u64 *param_1)
{
    param_1[0] = 0;
    *(u32 *)(param_1 + 1) = 0;
    for (int i = 2; i <= 0x17; i++)
        param_1[i] = 0;
}

// ---------------------------------------------------------------------------
// 0x71000837a0  size=96  FUN_71000837a0
// Returns 0 for Unicode format characters (zero-width, bidi); 1 otherwise
// ---------------------------------------------------------------------------
u64 FUN_71000837a0(u32 param_1)
{
    if ((param_1 & 0xffffff00u) == 0x2000u) {
        switch (param_1) {
        case 0x200b: case 0x200e: case 0x200f:
        case 0x202a: case 0x202b: case 0x202c: case 0x202d: case 0x202e:
        case 0x2060:
            return 0;
        }
        if (param_1 - 0x2066u < 4u)
            return 0;
    }
    return 1;
}

// ---------------------------------------------------------------------------
// 0x71000887d0  size=128  FUN_71000887d0
// Advance round-robin slot counter; update current-slot pointer
// ---------------------------------------------------------------------------
u64 FUN_71000887d0(long param_1, int param_2)
{
    if (param_2 == 2) {
        if (*(char *)(param_1 + 9) == '\0' && *(char *)(param_1 + 10) == '\0')
            return 0;
    } else if (param_2 != 1) {
        return 0;
    }

    *(u16 *)(param_1 + 9) = 0;

    int total  = *(int *)(param_1 + 0x30) + 1;
    int nslots = 2;
    if (*(char *)(*(long *)(*(long *)(param_1 + 0x78) + 0x20) + 0x36) != '\0')
        nslots = 3;

    int quot   = (nslots != 0) ? total / nslots : 0;
    u32 rem = (u32)(total - quot * nslots);
    *(u32 *)(param_1 + 0x30) = rem;
    *(u64 *)(param_1 + 0xc0) = param_1 + (u64)rem * 0x58 + 200;
    return 1;
}

// ---------------------------------------------------------------------------
// 0x710008a130  size=272  FUN_710008a130
// Remove node param_2 from doubly-linked list rooted at param_1; two list styles
// ---------------------------------------------------------------------------
void FUN_710008a130(long param_1, char *param_2)
{
    long next;
    if (*param_2 == '\0') {
        next = *(long *)(param_2 + 0x88);
        if (next != 0 && *(long *)(param_2 + 0x80) != 0) {
            *(long *)(next + 0x80) = *(long *)(param_2 + 0x80);
            *(u64 *)(*(long *)(param_2 + 0x80) + 0x88) = *(u64 *)(param_2 + 0x88);
            return;
        }
        if (*(char **)(param_1 + 0x150) == param_2) {
            *(u64 *)(param_1 + 0x150) = *(u64 *)(param_2 + 0x80);
            long nxt = *(long *)(param_2 + 0x80);
            if (nxt == 0) { *(u64 *)(param_1 + 0x158) = 0; return; }
            *(u64 *)(nxt + 0x88) = *(u64 *)(param_2 + 0x88);
            return;
        }
        if (*(char **)(param_1 + 0x158) == param_2) {
            *(long *)(param_1 + 0x158) = next;
            next = *(long *)(param_2 + 0x88);
            if (next == 0) { *(u64 *)(param_1 + 0x150) = 0; return; }
        }
    } else {
        next = *(long *)(param_2 + 0x88);
        if (next != 0 && *(long *)(param_2 + 0x80) != 0) {
            *(long *)(next + 0x80) = *(long *)(param_2 + 0x80);
            *(u64 *)(*(long *)(param_2 + 0x80) + 0x88) = *(u64 *)(param_2 + 0x88);
            return;
        }
        long lVar1 = *(long *)(param_2 + 0x548) + (long)*(int *)(param_2 + 0x20) * 8;
        if (*(char **)(lVar1 + 0x440) == param_2) {
            *(u64 *)(lVar1 + 0x440) = *(u64 *)(param_2 + 0x80);
            long nxt = *(long *)(param_2 + 0x80);
            if (nxt == 0) { *(u64 *)(lVar1 + 0x4c0) = 0; return; }
            *(u64 *)(nxt + 0x88) = *(u64 *)(param_2 + 0x88);
            return;
        }
        if (*(char **)(lVar1 + 0x4c0) == param_2) {
            *(long *)(lVar1 + 0x4c0) = next;
            next = *(long *)(param_2 + 0x88);
            if (next == 0) { *(u64 *)(lVar1 + 0x440) = 0; return; }
        } else { return; }
    }
    *(u64 *)(next + 0x80) = *(u64 *)(param_2 + 0x80);
}

// ---------------------------------------------------------------------------
// 0x710008a3b0  size=48  FUN_710008a3b0
// Walk linked list at param_1+0x150 forward param_2 steps
// ---------------------------------------------------------------------------
void FUN_710008a3b0(long param_1, int param_2)
{
    long node = *(long *)(param_1 + 0x150);
    if (param_2 != 0 && node != 0) {
        int remaining = param_2 - 1;
        do {
            node = *(long *)(node + 0x80);
            if (remaining-- == 0) return;
        } while (node != 0);
    }
}

// ---------------------------------------------------------------------------
// 0x710008a3e0  size=48  FUN_710008a3e0
// Return *param_1 if param_1[1] == (*param_1)+0x2c field; else 0
// ---------------------------------------------------------------------------
long FUN_710008a3e0(long *param_1)
{
    long ptr = *param_1;
    if (ptr != 0) {
        if ((int)param_1[1] != *(int *)(ptr + 0x2c))
            return 0;
        return ptr;
    }
    return 0;
}

// ---------------------------------------------------------------------------
// 0x710009e130  size=48  FUN_710009e130
// Count chain length at struct+0x418 list; base from +0x2c
// ---------------------------------------------------------------------------
int FUN_710009e130(long param_1)
{
    if (*(char *)(*(long *)(param_1 + 0x418) + 0x10) == '\0')
        return 0;
    int count = *(int *)(param_1 + 0x2c);
    for (long node = *(long *)(*(long *)(param_1 + 0x418) + 0x18); node != 0; node = *(long *)(node + 0x68))
        count++;
    return count;
}
