// SSBU 13.0.4 — MEDIUM-tier decompilation batch B-001
// Address range: 0x7100000250 – 0x7100031d70
// Compiler: NX Clang 8.0.0, -O2 -target aarch64-none-elf

#include "types.h"

// ---------------------------------------------------------------------------
// 0x7100000250  size=80  FUN_7100000250
// memcmp-like: returns 1 if first n bytes of buf1 == buf2, else 0
// ---------------------------------------------------------------------------
u64 FUN_7100000250(long param_1, long param_2, int param_3)
{
    if (param_3 < 1)
        return 1;

    long i = 0;
    do {
        if (*(char *)(param_1 + i) != *(char *)(param_2 + i))
            return 0;
        i++;
    } while (i < param_3);

    return 1;
}

// ---------------------------------------------------------------------------
// 0x71000007c0  size=48  FUN_71000007c0
// djb2-style hash of a C-string, result mod param_2
// ---------------------------------------------------------------------------
int FUN_71000007c0(u8 *param_1, u32 param_2)
{
    u32 acc = 0;
    u8 ch;
    u32 prev;
    do {
        prev = acc;
        ch = *param_1++;
        acc = (u32)ch + prev * 0x492u;
    } while (ch != 0);

    u32 result = 0;
    if (param_2 != 0)
        result = prev / param_2;
    return (int)(prev - result * param_2);
}

// ---------------------------------------------------------------------------
// 0x7100000900  size=96  FUN_7100000900
// Reference-counted shutdown: decrement; when zero, call cleanup chain
// ---------------------------------------------------------------------------
extern u32 DAT_71052a90e8;
extern u8  DAT_71052a90f0;
void FUN_7100027f90(void);
void FUN_7100005b40(void);
void FUN_7100026140(void);
void FUN_7100004780(void);

void FUN_7100000900(void)
{
    if (DAT_71052a90e8 != 0) {
        DAT_71052a90e8--;
        if (DAT_71052a90e8 == 0) {
            FUN_7100027f90();
            FUN_7100005b40();
            if (DAT_71052a90f0 & 1)
                FUN_7100026140();
            FUN_7100004780();
            DAT_71052a90f0 = 0;
        }
    }
}

// ---------------------------------------------------------------------------
// 0x7100002ac0  size=48  FUN_7100002ac0
// memrchr-like: find last occurrence of param_2 in param_1[0..param_3)
// ---------------------------------------------------------------------------
char *FUN_7100002ac0(char *param_1, char param_2, long param_3)
{
    if (param_3 - 1 >= 0) {
        char *p = param_1 + param_3 - 1;
        do {
            if (*p == param_2)
                return p;
            p--;
        } while (p >= param_1);
    }
    return (char *)0;
}

// ---------------------------------------------------------------------------
// 0x7100005a70  size=208  FUN_7100005a70
// Singleton getter with one-time init guard
// ---------------------------------------------------------------------------
extern u8  DAT_71052a90f8;
extern u8  DAT_71052a9100;
extern void    *PTR_LAB_71052a21e0;
extern void    *PTR_DAT_71052a21e8;

int FUN_71000052d0(void *, int, void *, void *, void *);
void FUN_7100005b00(void);

u8 *FUN_7100005a70(void)
{
    if (DAT_71052a90f8 & 1)
        return &DAT_71052a9100;

    int r = FUN_71000052d0(&DAT_71052a9100, 7, PTR_LAB_71052a21e0, PTR_DAT_71052a21e8, (void *)FUN_7100005b00);
    if (r != 0)
        return nullptr;

    DAT_71052a90f8 = 1;
    return &DAT_71052a9100;
}

// ---------------------------------------------------------------------------
// 0x71000093f0  size=32  FUN_71000093f0
// Test flag bit(s) param_2 in field at +0xe8 of struct param_1
// ---------------------------------------------------------------------------
u64 FUN_71000093f0(u64 param_1, int param_2)
{
    if (param_1 != 0)
        return (u64)((*(u64 *)(param_1 + 0xe8) & (long)param_2) != 0);
    return param_1;
}

// ---------------------------------------------------------------------------
// 0x710000bba0  size=64  FUN_710000bba0
// Linked-list search by int key at node+0x28, then unlink
// ---------------------------------------------------------------------------
extern u8 DAT_00004d58;
void FUN_7100006870(void *, long *, int);

void FUN_710000bba0(long param_1, int param_2)
{
    long *node = *(long **)(&DAT_00004d58 + param_1);
    if (node != nullptr) {
        do {
            if (*(int *)(*node + 0x28) == param_2) {
                FUN_7100006870(&DAT_00004d58 + param_1, node, 0);
                return;
            }
            node = (long *)node[2];
        } while (node != nullptr);
    }
}

// ---------------------------------------------------------------------------
// 0x710000c8f0  size=48  FUN_710000c8f0
// Returns true if field at struct+0xb70+0x4024 == 2
// ---------------------------------------------------------------------------
bool FUN_710000c8f0(long param_1)
{
    if (*(long *)(param_1 + 0xb70) != 0)
        return *(int *)(*(long *)(param_1 + 0xb70) + 0x4024) == 2;
    return false;
}

// ---------------------------------------------------------------------------
// 0x710000c920  size=48  FUN_710000c920
// Returns true if field at struct+0xb70+0x4024 != 2
// ---------------------------------------------------------------------------
bool FUN_710000c920(long param_1)
{
    if (*(long *)(param_1 + 0xb70) != 0)
        return *(int *)(*(long *)(param_1 + 0xb70) + 0x4024) != 2;
    return false;
}

// ---------------------------------------------------------------------------
// 0x7100012dc0  size=48  FUN_7100012dc0
// Error string table lookup by 1-based index (1–6); fallback to default
// ---------------------------------------------------------------------------
extern void *PTR_s_Too_long_hexadecimal_number_7104f16260;
extern u8 DAT_710437a4bc;

void *FUN_7100012dc0(int param_1)
{
    if ((u32)(param_1 - 1) < 6u)
        return (&PTR_s_Too_long_hexadecimal_number_7104f16260)[(int)((u32)(param_1 - 1))];
    return &DAT_710437a4bc;
}

// ---------------------------------------------------------------------------
// 0x71000145a0  size=32  FUN_71000145a0
// Check if *param2[0x8f0] == param_1
// ---------------------------------------------------------------------------
bool FUN_71000145a0(long param_1, long param_2)
{
    if (*(long **)(param_2 + 0x8f0) != nullptr)
        return **(long **)(param_2 + 0x8f0) == param_1;
    return false;
}

// ---------------------------------------------------------------------------
// 0x71000145c0  size=32  FUN_71000145c0
// Check if *param2[0x8d0] == param_1
// ---------------------------------------------------------------------------
bool FUN_71000145c0(long param_1, long param_2)
{
    if (*(long **)(param_2 + 0x8d0) != nullptr)
        return **(long **)(param_2 + 0x8d0) == param_1;
    return false;
}

// ---------------------------------------------------------------------------
// 0x7100014fc0  size=96  FUN_7100014fc0
// Setter: store param_2 at +0x9d8, set/clear flag bit 0x40 at +0xa08
// ---------------------------------------------------------------------------
void FUN_7100014fc0(long param_1, long param_2)
{
    if (param_2 >= 0) {
        *(long *)(param_1 + 0x9d8) = param_2;
        *(u32 *)(param_1 + 0xa08) |= 0x40u;
    } else {
        *(u64 *)(param_1 + 0x9d8) = 0;
        *(u32 *)(param_1 + 0xa08) &= ~0x40u;
    }
}

// ---------------------------------------------------------------------------
// 0x7100017450  size=64  FUN_7100017450
// toupper-copy: copy param_3 bytes of param_2 into param_1, uppercasing a-z
// ---------------------------------------------------------------------------
void FUN_7100017450(u8 *param_1, u8 *param_2, long param_3)
{
    if (param_3 == 0)
        return;
    do {
        u8 ch = *param_2;
        u8 out = ch;
        if (ch - 0x61u < 0x1au)
            out = ch - 0x20u;
        *param_1 = out;
        if (*param_2 == 0)
            return;
        param_2++;
        param_1++;
        param_3--;
    } while (param_3 != 0);
}

// ---------------------------------------------------------------------------
// 0x710001ebb0  size=80  FUN_710001ebb0
// Linked-list search by value param_1, unlink if found; returns 1/0
// ---------------------------------------------------------------------------
int FUN_710001ebb0(long param_1, long *param_2)
{
    if (param_2 != nullptr) {
        for (long *node = (long *)*param_2; node != nullptr; node = (long *)node[2]) {
            if (*node == param_1) {
                FUN_7100006870(param_2, node, 0);
                return 1;
            }
        }
    }
    return 0;
}

// ---------------------------------------------------------------------------
// 0x710001ef80  size=48  FUN_710001ef80
// Vtable dispatch through param_1+0x858 slot +0x30; sets *param_2 flag
// ---------------------------------------------------------------------------
int FUN_710001ef80(long param_1, u8 *param_2)
{
    if (param_1 != 0 && *(long *)(*(long *)(param_1 + 0x858) + 0x30) != 0) {
        *param_2 = 0;
        typedef int (*fn_t)(long, u8*);
        fn_t fn = *(fn_t *)(*(long *)(param_1 + 0x858) + 0x30);
        return fn(param_1, param_2);
    }
    *param_2 = 1;
    return 0;
}

// ---------------------------------------------------------------------------
// 0x710001efb0  size=48  FUN_710001efb0
// Vtable dispatch through param_1+0x858 slot +0x38; sets *param_2 flag
// ---------------------------------------------------------------------------
int FUN_710001efb0(long param_1, u8 *param_2)
{
    if (param_1 != 0 && *(long *)(*(long *)(param_1 + 0x858) + 0x38) != 0) {
        *param_2 = 0;
        typedef int (*fn_t)(long, u8*);
        fn_t fn = *(fn_t *)(*(long *)(param_1 + 0x858) + 0x38);
        return fn(param_1, param_2);
    }
    *param_2 = 1;
    return 0;
}

// ---------------------------------------------------------------------------
// 0x7100022bf0  size=464  FUN_7100022bf0
// curl option-type to alignment/size table lookup
// ---------------------------------------------------------------------------
u64 FUN_7100022bf0(u64 param_1)
{
    int v = (int)param_1;
    if (v < 0x4000) {
        if (v < 0x80) {
            switch (v) {
            case 1: case 2:               return 1;
            case 4: case 8:               return 4;
            case 0x10: case 0x20: case 0x40: return param_1;
            }
        } else if (v < 0x400) {
            if (v == 0x80 || v == 0x100)  return 0x80;
            if (v == 0x200)               return param_1 & 0xffffffff;
        } else if (v < 0x1000) {
            if (v == 0x400)               return param_1;
            if (v == 0x800)               return param_1 & 0xffffffff;
        } else if (v == 0x1000 || v == 0x2000) return 0x1000;
    } else if (v < 0x200000) {
        if (v < 0x20000) {
            if (v == 0x4000 || v == 0x8000) return 0x4000;
            if (v == 0x10000)               return 0x10000;
        } else if (v < 0x80000) {
            if (v == 0x20000)               return 0x10000;
            if (v == 0x40000)               return param_1 & 0xffffffff;
        } else {
            if (v == 0x80000)               return 0x80000;
            if (v == 0x100000)              return 0x100000;
        }
    } else if (v < 0x1000000) {
        if (v == 0x200000)                  return param_1;
        if (v == 0x400000)                  return param_1;
        if (v == 0x800000)                  return 0x80000;
    } else if (v < 0x4000000) {
        if (v == 0x1000000)                 return 0x100000;
        if (v == 0x2000000)                 return param_1 & 0xffffffff;
    } else if (v == 0x4000000 || v == 0x8000000) return 0x4000000;
    return 0;
}

// ---------------------------------------------------------------------------
// 0x71000263c0  size=112  FUN_71000263c0
// Allocate 0xb8-byte block; store at &DAT_00004bc8+param_1, init fields
// ---------------------------------------------------------------------------
extern u8 DAT_00004bc8;
extern u8 DAT_00004bd0;
void *FUN_71000272d0(u64, u64);

u64 FUN_71000263c0(long param_1, u64 param_2)
{
    if (*(long *)(&DAT_00004bc8 + param_1) != 0)
        return 0;

    long block = (long)FUN_71000272d0(param_2, 0xb8);
    if (block != 0) {
        *(long *)(&DAT_00004bc8 + param_1) = block;
        *(u64 *)(param_1 + 0x658) = param_2;
        *(u64 *)(&DAT_00004bd0 + param_1) = 1;
        return 0;
    }
    return 0x1b;
}

// ---------------------------------------------------------------------------
// 0x7100027900  size=80  FUN_7100027900
// Assert param_1 is stdout or stderr fd; abort otherwise
// ---------------------------------------------------------------------------
extern long *PTR_stdout_71052a21d8;
extern long *PTR_stderr_71052a2210;

u64 FUN_7100027900(long param_1)
{
    if (*PTR_stdout_71052a21d8 == param_1 || *PTR_stderr_71052a2210 == param_1)
        return 0xffffffff;

    // param_1 is not a known stdio stream — abort
    extern void nndetailDiagAbortFormatImpl(void *, void *, void *, int, void *);
    extern void *DAT_71044104cc;
    nndetailDiagAbortFormatImpl(&DAT_71044104cc, &DAT_71044104cc, &DAT_71044104cc, 0, &DAT_71044104cc);
    nndetailDiagAbortFormatImpl(&DAT_71044104cc, &DAT_71044104cc, &DAT_71044104cc, 0, &DAT_71044104cc);
    __builtin_unreachable();
}

// ---------------------------------------------------------------------------
// 0x7100031140  size=48  FUN_7100031140
// Initialize network struct with default field values
// ---------------------------------------------------------------------------
void FUN_7100031140(u32 *param_1)
{
    param_1[0] = 0x20202;
    *(u64 *)(param_1 + 1) = 0xc47a0000002a0100ULL;
    *(u64 *)(param_1 + 3) = 0x447a0000ULL;
}

// ---------------------------------------------------------------------------
// 0x71000311e0  size=48  FUN_71000311e0
// Initialize byte-level struct fields
// ---------------------------------------------------------------------------
void FUN_71000311e0(u8 *param_1)
{
    param_1[1] = 1;
    param_1[2] = 0;
    param_1[3] = 0;
    param_1[4] = 1;
    param_1[0] &= 0xfeu;
    param_1[5] = 0;
    param_1[6] = 0;
    param_1[7] = 0xf;
}

// ---------------------------------------------------------------------------
// 0x7100031210  size=48  FUN_7100031210
// Initialize uint16-level struct fields; set float constants
// ---------------------------------------------------------------------------
void FUN_7100031210(u16 *param_1)
{
    *(u64 *)(param_1 + 6) = 0x3f80000000000000ULL;
    param_1[1] &= 0xfff0u;
    *(u64 *)(param_1 + 2) = 0;
    *(u64 *)(param_1 + 0xc) = 0;
    param_1[0] = 0x500;
}

// ---------------------------------------------------------------------------
// 0x7100031250  size=48  FUN_7100031250
// Initialize packet/option struct with magic constants
// ---------------------------------------------------------------------------
void FUN_7100031250(u16 *param_1)
{
    param_1[0] = 0xff01;
    *(u8 *)(param_1 + 1) = 0xff;
    *(u32 *)(param_1 + 4) = 0x7000000;
    *(u8 *)(param_1 + 6) = 0;
    param_1[2] &= 0xfff0u;
    *(u32 *)(param_1 + 0xc) = 0x7000000;
    *(u8 *)(param_1 + 0xe) = 0;
}

// ---------------------------------------------------------------------------
// 0x7100031330  size=48  FUN_7100031330
// Initialize struct with version/pointer fields
// ---------------------------------------------------------------------------
extern u8 DAT_100000001;

void FUN_7100031330(long param_1)
{
    *(u8 *)(param_1 + 1) = 2;
    *(u64 *)(param_1 + 2) = 0x1000100000000ULL;
    *(u8 **)(param_1 + 0x14) = &DAT_100000001;
    *(u64 *)(param_1 + 0xc) = 0;
    *(u64 *)(param_1 + 0x1c) = 1;
}

// ---------------------------------------------------------------------------
// 0x7100031360  size=48  FUN_7100031360
// Initialize uint16 struct with sequence/version constants
// ---------------------------------------------------------------------------
void FUN_7100031360(u16 *param_1)
{
    param_1[0] = 1;
    *(u64 *)(param_1 + 2) = 0x504030200000000ULL;
    *(u32 *)(param_1 + 8) = 0x10000;
    *(u64 *)(param_1 + 0x10) = 0x100000000ULL;
    *(u64 *)(param_1 + 0x18) = 0;
}

// ---------------------------------------------------------------------------
// 0x7100031390  size=32  FUN_7100031390
// Zero-init struct with version byte = 1
// ---------------------------------------------------------------------------
void FUN_7100031390(u8 *param_1)
{
    param_1[0] = 1;
    *(u64 *)(param_1 + 4) = 0;
    *(u16 *)(param_1 + 2) = 0;
    *(u32 *)(param_1 + 0xc) = 1;
    *(u64 *)(param_1 + 0x18) = 0;
}

// ---------------------------------------------------------------------------
// 0x71000313b0  size=32  FUN_71000313b0
// Zero-init struct with version byte = 1
// ---------------------------------------------------------------------------
void FUN_71000313b0(u8 *param_1)
{
    param_1[0] = 1;
    *(u16 *)(param_1 + 2) = 0;
    *(u64 *)(param_1 + 8) = 0x100000000ULL;
    *(u64 *)(param_1 + 0x18) = 0;
}

// ---------------------------------------------------------------------------
// 0x71000313f0  size=32  FUN_71000313f0
// Init uint64 array struct; version pointer at slot [2]
// ---------------------------------------------------------------------------
void FUN_71000313f0(u64 *param_1)
{
    param_1[2] = (u64)&DAT_100000001;
    param_1[0] = 0;
    param_1[1] = 0x100000000ULL;
    *(u16 *)(param_1 + 3) = 0;
    *(u64 *)((u8 *)param_1 + 0x1c) = 0x100000000ULL;
}

// ---------------------------------------------------------------------------
// 0x7100031410  size=48  FUN_7100031410
// Init larger uint64 array struct; version pointer at slot [3]
// ---------------------------------------------------------------------------
void FUN_7100031410(u64 *param_1)
{
    param_1[2] = 0;
    param_1[3] = (u64)&DAT_100000001;
    *(u32 *)(param_1 + 4) = 1;
    param_1[0] = 0;
    param_1[1] = 0;
    *(u16 *)((u8 *)param_1 + 0x24) = 0;
    param_1[5] = 0x100000000ULL;
}

// ---------------------------------------------------------------------------
// 0x71000314e0  size=32  FUN_71000314e0
// Set version byte = 1, OR bit 0 of byte[1], store param_2 at +8
// ---------------------------------------------------------------------------
void FUN_71000314e0(u8 *param_1, u64 param_2)
{
    param_1[0] = 1;
    param_1[1] |= 1u;
    *(u64 *)(param_1 + 8) = param_2;
}

// ---------------------------------------------------------------------------
// 0x7100031510  size=48  FUN_7100031510
// Table lookup for SSL cipher/option type (index 0x27–0x3a); default 4
// ---------------------------------------------------------------------------
extern u8 DAT_710446f0e0;

u32 FUN_7100031510(int param_1)
{
    if ((u32)(param_1 - 0x27) < 0x14u)
        return *(u32 *)(&DAT_710446f0e0 + (long)(int)((u32)(param_1 - 0x27)) * 4);
    return 4;
}

// ---------------------------------------------------------------------------
// 0x7100031540  size=48  FUN_7100031540
// Table lookup alternate (different table base); default 4
// ---------------------------------------------------------------------------
extern u8 DAT_710446f090;

u32 FUN_7100031540(int param_1)
{
    if ((u32)(param_1 - 0x27) < 0x14u)
        return *(u32 *)(&DAT_710446f090 + (long)(int)((u32)(param_1 - 0x27)) * 4);
    return 4;
}

// ---------------------------------------------------------------------------
// 0x71000316b0  size=112  FUN_71000316b0
// Resolve SSL socket type: returns operation code based on (type, flags)
// ---------------------------------------------------------------------------
void nn_detail_UnexpectedDefaultImpl(const char *, const char *, int);

u32 FUN_71000316b0(int param_1, u64 param_2, u64 param_3)
{
    if (param_1 == 3)
        return 2;
    if (param_1 == 2) {
        u32 a = 6, b = 7;
        if ((param_3 & 1) == 0) { a = 1; b = 5; }
        if (param_2 & 1) a = b;
        return a;
    }
    if (param_1 != 1)
        nn_detail_UnexpectedDefaultImpl("", "", 0);
    return (param_2 & 1) ? 4u : 0u;
}

// ---------------------------------------------------------------------------
// 0x7100031850  size=32  FUN_7100031850
// Zero-initialize 9-slot uint64 array
// ---------------------------------------------------------------------------
void FUN_7100031850(u64 *param_1)
{
    param_1[0] = 0; param_1[1] = 0; param_1[2] = 0;
    param_1[3] = 0; param_1[4] = 0; param_1[5] = 0;
    param_1[6] = 0; param_1[7] = 0; param_1[8] = 0;
}

// ---------------------------------------------------------------------------
// 0x7100031a60  size=64  FUN_7100031a60
// ioctl(fd, 0x13, &result) wrapper
// ---------------------------------------------------------------------------
extern void *PTR_DAT_71052a22b8;

long FUN_7100031a60(u64 *param_1)
{
    int result;
    (*(int (*)(u64, int, int *))*(void **)PTR_DAT_71052a22b8)(*param_1, 0x13, &result);
    return (long)result;
}

// ---------------------------------------------------------------------------
// 0x7100031aa0  size=64  FUN_7100031aa0
// ioctl(fd, 0x14, &result) wrapper
// ---------------------------------------------------------------------------
long FUN_7100031aa0(u64 *param_1)
{
    int result;
    (*(int (*)(u64, int, int *))*(void **)PTR_DAT_71052a22b8)(*param_1, 0x14, &result);
    return (long)result;
}

// ---------------------------------------------------------------------------
// 0x7100031d70  size=64  FUN_7100031d70
// Init: get handle via vtable slot 0, store at +0xc0, set byte[0] = 1
// ---------------------------------------------------------------------------
extern void *PTR_DAT_71052a2350;

void FUN_7100031d70(u8 *param_1)
{
    typedef u64 (*getter_t)(u64);
    getter_t fn = *(getter_t *)PTR_DAT_71052a2350;
    u64 handle = fn(*(u64 *)(param_1 + 0xb8));
    *(u64 *)(param_1 + 0xc0) = handle;
    param_1[0] = 1;
}
