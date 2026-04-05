#include "types.h"

// Batch decompiled via Ghidra MCP -- pool-e, batch 006
// Range: 0x7100000000 -- 0x7100FFFFFF

// ---- SDK declarations -------------------------------------------------------

namespace nn { namespace os {
    struct MutexType;
    extern void LockMutex(MutexType *);
    extern void UnlockMutex(MutexType *);
}}

namespace nn { namespace detail {
    [[noreturn]] extern void UnexpectedDefaultImpl(const char *, const char *, s32);
}}

// ---- External declarations --------------------------------------------------

extern "C" {
    void  abort(void);
    void *malloc(u64);
    u64   strlen(const char *);
    char *strcpy(char *, const char *);
    s32  __cxa_guard_acquire(s64 *);
    void __cxa_guard_release(s64 *);
}

// Called functions
extern void FUN_71000b1900(void *);
extern void FUN_71000b1910(s64, void *);
extern s32  FUN_71001c4c40(u32, s64, s64, u64 *, u64, s32);
extern u64  FUN_71001b4200(u64, void *);
extern u64  FUN_71000b1b90(void);
extern s64  FUN_7100130810(u64, u64);
extern u64  FUN_7101717b00(u64);
extern s64  FUN_71001dacc0(s64);
extern void FUN_71001f2180(s64);
extern void FUN_71001bec20(u64, u64);
extern void FUN_71001e1770(u64, u32, void *);
extern void FUN_71000baa20(void);
extern void FUN_71001b47e0(s64, s64, s64);
extern void FUN_71000bb5d0(s64 *);
extern s64 *FUN_71000bb680(void);
extern void FUN_7100179c70(s64, u64);

// Data
extern u8  *PTR_DAT_71052a3db8;
extern u8   DAT_71052b4270[];
extern u16  DAT_71052b4278;
extern u8  *PTR_DAT_71052a5538;
extern void *PTR_DAT_71052a5818;
extern u8  *PTR_DAT_71052a5820;
extern u8  *PTR_DAT_71052a50b0;
extern u8   DAT_71052b82e0;
extern u8   DAT_71052b82f0;
extern u8   DAT_71044a7c80[];
extern u32  DAT_71044718a4;
extern u32  DAT_71044723d8;

// ---- Functions --------------------------------------------------------------

// 0x7100154200 -- init object fields with stack-allocated intermediate
void FUN_7100154200(s64 param_1)
{
    u8 temp[24];

    *(u64 *)(param_1 + 0x10) = 0;
    FUN_71000b1900(temp);
    FUN_71000b1910(param_1 + 0x18, temp);
    *(u16 *)(param_1 + 0x2c) = 0;
    *(u64 *)(param_1 + 8) = 0;
}

// 0x71001ce780 -- strcpy "Encryption Error" if buffer large enough
u64 FUN_71001ce780(u64 param_1, u64 param_2, char *buf, u64 buf_size)
{
    u64 len;

    len = strlen("Encryption Error");
    if (len < buf_size) {
        strcpy(buf, "Encryption Error");
        return 1;
    }
    return 0;
}

// 0x71001e0910 -- return language code
u16 FUN_71001e0910(void)
{
    u32 *puVar1;

    return DAT_71052b4278;
}

// 0x71001e1710 -- conditional field assign or error
void FUN_71001e1710(u64 param_1, s64 param_2, u64 param_3)
{
    u32 status;

    if (*(s64 *)(param_2 + 0x80) != 0) {
        status = 0x8001000e;
        FUN_71001b4200(param_1, &status);
        return;
    }
    *(u64 *)(param_2 + 0x80) = param_3;
    status = 0x10001;
    FUN_71001b4200(param_1, &status);
}

// 0x71004f6590 -- guarded global init, return byte
u8 FUN_71004f6590(void)
{
    s32 acquired;

    if (((DAT_71052b82e0 & 1) == 0) &&
        (acquired = __cxa_guard_acquire((s64 *)&DAT_71052b82e0), acquired != 0)) {
        __cxa_guard_release((s64 *)&DAT_71052b82e0);
    }
    return DAT_71052b82f0;
}

// 0x710065f8a8 -- abort stub
void FUN_710065f8a8(void)
{
    abort();
}

// 0x710065f65c -- abort stub
void FUN_710065f65c(void)
{
    abort();
}

// 0x710049f570 -- double vtable dereference, return inverted bit 0
u32 FUN_710049f570(s64 param_1)
{
    s64 *inner;
    u32 result;

    inner = *(s64 **)(*(s64 *)(param_1 + 0x10) + 0x38);
    inner = (s64 *)(*(s64 (*)(s64 *, s32))(*inner + 0x10))(inner, 0);
    result = (*(u32 (**)())(*inner + 0x78))();
    return ~result & 1;
}

// 0x710065fa1c -- abort stub
void FUN_710065fa1c(void)
{
    abort();
}

// 0x710065f610 -- abort stub
void FUN_710065f610(void)
{
    abort();
}

// 0x7100f574d0 -- status kind range check with bitmask
u32 FUN_7100f574d0(u64 param_1, s64 param_2)
{
    u32 status_kind;

    status_kind = (*(u32 (**)())(*(s64 *)(*(s64 *)(*(s64 *)(param_2 + 0x20) + 0x40)) + 0x110))();
    if ((u32)(status_kind - 0x3c) < 5) {
        return (u32)(0xcU >> ((u64)(u32)((status_kind - 0x3c) & 0x1f))) & 1;
    }
    return 1;
}

// 0x71001daf50 -- conditional field dereference returning u32
u32 FUN_71001daf50(s64 param_1)
{
    s64 node;

    node = FUN_71001dacc0(param_1 + 8);
    if (*(s64 *)(node + 0x10) != 0) {
        node = FUN_71001dacc0(param_1 + 8);
        return *(u32 *)(*(s64 *)(node + 8) + 0x24);
    }
    return 0;
}

// 0x71001dafa0 -- conditional field dereference returning u16
u16 FUN_71001dafa0(s64 param_1)
{
    s64 node;

    node = FUN_71001dacc0(param_1 + 8);
    if (*(s64 *)(node + 0x10) != 0) {
        node = FUN_71001dacc0(param_1 + 8);
        return *(u16 *)(*(s64 *)(node + 8) + 0x28);
    }
    return 0;
}

// 0x71001e0070 -- conditional init + dispatch, return 1
u64 FUN_71001e0070(s64 param_1, u64 param_2)
{
    if (*(char *)(param_1 + 0x68) == '\0') {
        FUN_71001f2180(param_1);
    }
    FUN_71001bec20(*(u64 *)(param_1 + 8), param_2);
    *(u8 *)(param_1 + 0x69) = 0;
    return 1;
}

// 0x7100186580 -- vtable ptr + list head init
void FUN_7100186580(s64 *param_1)
{
    u8 *vtable_base;

    FUN_71000baa20();
    vtable_base = PTR_DAT_71052a5538;
    param_1[0xb] = 0;
    param_1[0xc] = 0x2710;
    *(u32 *)((s64)param_1 + 0x7c) = 0;
    param_1[0xd] = 0;
    param_1[0xe] = 0;
    *param_1 = (s64)(vtable_base + 0x10);
    *(u16 *)(param_1 + 0xf) = 0;
}

// 0x71001aea80 -- clock delta calculation
s64 FUN_71001aea80(s64 *param_1)
{
    s64 elapsed;
    s64 *freq_ptr;
    s64 delta;
    s64 now;

    if ((char)param_1[1] != '\0') {
        now = 0;
        FUN_71000bb5d0(&now);
        delta = now - *param_1;
        freq_ptr = FUN_71000bb680();
        elapsed = 0;
        if (*freq_ptr != 0) {
            elapsed = delta / *freq_ptr;
        }
        return elapsed;
    }
    return -1;
}

// 0x71001b4510 -- aligned alloc via custom or system allocator
u64 *FUN_71001b4510(s64 param_1)
{
    u64 *ptr;

    if (*(void (**)())PTR_DAT_71052a5818 == nullptr) {
        ptr = (u64 *)malloc((u64)((param_1 + 0x17) & ~(s64)7));
    } else {
        ptr = (u64 *)(*(u64 (**)())PTR_DAT_71052a5818)();
    }
    *ptr = *(u64 *)PTR_DAT_71052a5820;
    return ptr + 2;
}

// 0x7100181380 -- mutex-locked vtable call
u32 FUN_7100181380(s64 param_1)
{
    u32 result;

    nn::os::LockMutex((nn::os::MutexType *)(param_1 + 0x2e0));
    result = (*(u32 (**)())(*(s64 *)(*(s64 *)(param_1 + 0x308)) + 0x48))();
    nn::os::UnlockMutex((nn::os::MutexType *)(param_1 + 0x2e0));
    return result;
}

// 0x7100179620 -- allocator with extra init param
s64 FUN_7100179620(void)
{
    u64 heap_id;
    s64 obj;
    u64 init_param;

    init_param = *(u64 *)PTR_DAT_71052a50b0;
    heap_id = FUN_71000b1b90();
    obj = FUN_7100130810(0x1b8, heap_id);
    if (obj != 0) {
        FUN_7100179c70(obj, init_param);
    }
    return obj;
}
