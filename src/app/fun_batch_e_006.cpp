#include "types.h"

// Batch decompiled via Ghidra MCP -- pool-e, batch 006
// Rewritten with derivation chains + VT macro

#define VT(m) (*reinterpret_cast<void***>(m))

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
extern u8  *PTR_DAT_71052a5538;   // [inferred: vtable base pointer for service objects]
extern void *PTR_DAT_71052a5818;  // [inferred: custom allocator function pointer, null = use malloc]
extern u8  *PTR_DAT_71052a5820;   // [inferred: allocator header/tag value pointer]
extern u8  *PTR_DAT_71052a50b0;   // [inferred: init param pointer for FUN_7100179c70]
extern u8   DAT_71052b82e0;       // [inferred: __cxa_guard variable for one-time init]
extern u8   DAT_71052b82f0;       // [inferred: cached config byte, set during guarded init]
extern u8   DAT_71044a7c80[];
extern u32  DAT_71044718a4;
extern u32  DAT_71044723d8;

// ---- Functions --------------------------------------------------------------

// 0x7100154200 -- init object fields with stack-allocated intermediate
// param_1 [inferred: list/container struct, at least 0x2e bytes]
//   +0x08 [inferred: u64 field, cleared to 0]
//   +0x10 [inferred: u64 field, cleared to 0]
//   +0x18 [inferred: embedded sub-object, initialized via FUN_71000b1910]
//   +0x2c [inferred: u16 field, cleared to 0]
void FUN_7100154200(s64 param_1)
{
    u8 temp[24];

    *(u64 *)(param_1 + 0x10) = 0;             // +0x10 [inferred: data pointer, init null]
    FUN_71000b1900(temp);
    FUN_71000b1910(param_1 + 0x18, temp);      // +0x18 [inferred: embedded sub-object]
    *(u16 *)(param_1 + 0x2c) = 0;              // +0x2c [inferred: count/index, init 0]
    *(u64 *)(param_1 + 8) = 0;                 // +0x08 [inferred: head pointer, init null]
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

// 0x71001e0910 -- return language code from global
// DAT_71052b4278 [inferred: u16 current language code]
u16 FUN_71001e0910(void)
{
    u32 *puVar1;

    return DAT_71052b4278;
}

// 0x71001e1710 -- conditional field assign or return error
// param_2 [inferred: handler/callback struct]
//   +0x80 [inferred: s64 slot — 0 = available, nonzero = already occupied]
// 0x8001000e [inferred: error code "already assigned"]
// 0x10001 [inferred: success code]
void FUN_71001e1710(u64 param_1, s64 param_2, u64 param_3)
{
    u32 status;

    if (*(s64 *)(param_2 + 0x80) != 0) {      // +0x80 [inferred: callback slot]
        status = 0x8001000e;                    // [inferred: error: slot occupied]
        FUN_71001b4200(param_1, &status);
        return;
    }
    *(u64 *)(param_2 + 0x80) = param_3;        // +0x80 [inferred: assign callback]
    status = 0x10001;                           // [inferred: success]
    FUN_71001b4200(param_1, &status);
}

// 0x71004f6590 -- guarded global init, return cached byte
// DAT_71052b82e0 [inferred: __cxa_guard for one-time init]
// DAT_71052b82f0 [inferred: cached result byte]
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

// 0x710049f570 -- IsEnd2nd: double vtable dereference, return inverted bit 0
// NOTE: primary implementation in fun_typed_b_001.cpp (IsEnd2nd_49f570, 100% match)
// param_1 [inferred: battle object or iterator struct]
//   +0x10 [inferred: inner object pointer]
//   inner+0x38 [inferred: sub-object pointer (second level)]
//   sub vtable+0x10 [inferred: get-element method, param=0 → first element]
//   element vtable+0x78 [inferred: is-ended/is-done query method]
u32 FUN_710049f570(s64 param_1)
{
    // +0x10 [inferred: inner object] → +0x38 [inferred: sub-iterator/collection]
    s64 *inner = *(s64 **)(*(s64 *)(param_1 + 0x10) + 0x38);
    // vtable+0x10 [inferred: get element at index 0]
    inner = reinterpret_cast<s64 *>(
        reinterpret_cast<s64 (*)(s64 *, s32)>(VT(inner)[0x10 / 8])(inner, 0));
    // vtable+0x78 [inferred: is-ended query, returns bool]
    u32 result = reinterpret_cast<u32 (*)(s64 *)>(VT(inner)[0x78 / 8])(inner);
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
// param_2 [inferred: BattleObject*]
//   +0x20 [inferred: BattleObjectModuleAccessor* — same pattern across 5+ call sites]
//   acc+0x40 = status_module [derived: StatusModule__*_impl (.dynsym) loads from accessor+0x40]
//   vtable+0x110 = StatusKind [derived: status_kind_impl (.dynsym) dispatches to vtable+0x110]
// Returns 0 only if status_kind is 0x3c or 0x3d (bitmask 0xc = 0b1100, bits 0 and 1 of shifted value)
u32 FUN_7100f574d0(u64 param_1, s64 param_2)
{
    // +0x20 [inferred: module accessor from BattleObject]
    // +0x40 [derived: status_module, StatusModule__*_impl (.dynsym)]
    s64 *status_mod = *(s64 **)(*(s64 *)(param_2 + 0x20) + 0x40);
    // vtable+0x110 [derived: StatusKind, status_kind_impl (.dynsym)]
    u32 status_kind = reinterpret_cast<u32 (*)(s64 *)>(VT(status_mod)[0x110 / 8])(status_mod);
    if ((u32)(status_kind - 0x3c) < 5) {
        return (u32)(0xcU >> ((u64)(u32)((status_kind - 0x3c) & 0x1f))) & 1;
    }
    return 1;
}

// 0x71001daf50 -- conditional field dereference returning u32
// param_1 [inferred: iterator/cursor struct]
//   +0x08 [inferred: embedded node, passed to FUN_71001dacc0]
// node [inferred: linked-list node]
//   +0x08 [inferred: data pointer]
//   +0x10 [inferred: next pointer, 0 = end of list]
//   data+0x24 [inferred: u32 result field]
u32 FUN_71001daf50(s64 param_1)
{
    s64 node;

    node = FUN_71001dacc0(param_1 + 8);                // +0x08 [inferred: embedded node]
    if (*(s64 *)(node + 0x10) != 0) {                  // +0x10 [inferred: has-next check]
        node = FUN_71001dacc0(param_1 + 8);
        return *(u32 *)(*(s64 *)(node + 8) + 0x24);   // +0x08→+0x24 [inferred: data→u32 field]
    }
    return 0;
}

// 0x71001dafa0 -- conditional field dereference returning u16
// Same struct layout as FUN_71001daf50, reading u16 at data+0x28
u16 FUN_71001dafa0(s64 param_1)
{
    s64 node;

    node = FUN_71001dacc0(param_1 + 8);                // +0x08 [inferred: embedded node]
    if (*(s64 *)(node + 0x10) != 0) {                  // +0x10 [inferred: has-next check]
        node = FUN_71001dacc0(param_1 + 8);
        return *(u16 *)(*(s64 *)(node + 8) + 0x28);   // +0x08→+0x28 [inferred: data→u16 field]
    }
    return 0;
}

// 0x71001e0070 -- conditional init + dispatch, return 1
// param_1 [inferred: session/connection struct, same as FUN_71001e59e0 in batch 005]
//   +0x08 [inferred: inner handle]
//   +0x68 [inferred: initialized flag]
//   +0x69 [inferred: pending flag, cleared after dispatch]
u64 FUN_71001e0070(s64 param_1, u64 param_2)
{
    if (*(char *)(param_1 + 0x68) == '\0') {   // +0x68 [inferred: initialized flag]
        FUN_71001f2180(param_1);
    }
    FUN_71001bec20(*(u64 *)(param_1 + 8), param_2);  // +0x08 [inferred: inner handle]
    *(u8 *)(param_1 + 0x69) = 0;                      // +0x69 [inferred: pending flag, cleared]
    return 1;
}

// 0x7100186580 -- vtable ptr + field init for service object (0x80 bytes)
// param_1 [inferred: service object being constructed]
//   +0x00 [inferred: vtable pointer, set from PTR_DAT_71052a5538+0x10]
//   +0x58 (param_1[0xb]) [inferred: u64 field, init 0]
//   +0x60 (param_1[0xc]) [inferred: u64 field, init 0x2710 (10000)]
//   +0x68 (param_1[0xd]) [inferred: u64 field, init 0]
//   +0x70 (param_1[0xe]) [inferred: u64 field, init 0]
//   +0x78 (param_1+0x78) [inferred: u16 field, init 0]
//   +0x7c [inferred: u32 field, init 0]
void FUN_7100186580(s64 *param_1)
{
    u8 *vtable_base;

    FUN_71000baa20();
    vtable_base = PTR_DAT_71052a5538;     // [inferred: vtable table base]
    param_1[0xb] = 0;                      // +0x58 [inferred: init 0]
    param_1[0xc] = 0x2710;                 // +0x60 [inferred: default capacity/timeout 10000]
    *(u32 *)((s64)param_1 + 0x7c) = 0;     // +0x7c [inferred: u32 status field, init 0]
    param_1[0xd] = 0;                      // +0x68 [inferred: init 0]
    param_1[0xe] = 0;                      // +0x70 [inferred: init 0]
    *param_1 = (s64)(vtable_base + 0x10);  // +0x00 [inferred: vtable ptr from base+0x10]
    *(u16 *)(param_1 + 0xf) = 0;           // +0x78 [inferred: u16 field, init 0]
}

// 0x71001aea80 -- clock delta calculation
// param_1 [inferred: timer/stopwatch struct]
//   [0] (+0x00) [inferred: s64 start timestamp]
//   [1] (+0x08) [inferred: bool is_running flag]
// FUN_71000bb5d0 [inferred: get current tick count]
// FUN_71000bb680 [inferred: get tick frequency pointer]
s64 FUN_71001aea80(s64 *param_1)
{
    s64 elapsed;
    s64 *freq_ptr;
    s64 delta;
    s64 now;

    if ((char)param_1[1] != '\0') {       // +0x08 [inferred: is_running flag]
        now = 0;
        FUN_71000bb5d0(&now);
        delta = now - *param_1;            // +0x00 [inferred: start timestamp]
        freq_ptr = FUN_71000bb680();
        elapsed = 0;
        if (*freq_ptr != 0) {
            elapsed = delta / *freq_ptr;   // [inferred: ticks / frequency = seconds]
        }
        return elapsed;
    }
    return -1;
}

// 0x71001b4510 -- aligned alloc via custom or system allocator
// Allocates (param_1 + 0x17) & ~7 bytes (8-byte aligned), prepends 16-byte header
// PTR_DAT_71052a5818 [inferred: custom allocator function ptr, null = use malloc]
// PTR_DAT_71052a5820 [inferred: allocator tag/header value]
u64 *FUN_71001b4510(s64 param_1)
{
    u64 *ptr;

    if (*(void (**)())PTR_DAT_71052a5818 == nullptr) {
        ptr = (u64 *)malloc((u64)((param_1 + 0x17) & ~(s64)7));  // [inferred: 8-byte align up]
    } else {
        ptr = (u64 *)(*(u64 (**)())PTR_DAT_71052a5818)();         // [inferred: custom allocator]
    }
    *ptr = *(u64 *)PTR_DAT_71052a5820;    // [inferred: write allocator header/tag]
    return ptr + 2;                         // [inferred: skip 16-byte header, return usable ptr]
}

// 0x7100181380 -- mutex-locked vtable call
// param_1 [inferred: service object with mutex + inner handler]
//   +0x2e0 [inferred: nn::os::MutexType, used for thread safety]
//   +0x308 [inferred: inner handler pointer (vtable-bearing)]
//   handler vtable+0x48 [inferred: query method returning u32]
u32 FUN_7100181380(s64 param_1)
{
    u32 result;

    nn::os::LockMutex((nn::os::MutexType *)(param_1 + 0x2e0));  // +0x2e0 [inferred: mutex]
    // +0x308 [inferred: inner handler] → vtable+0x48 [inferred: query method]
    s64 *handler = *(s64 **)(param_1 + 0x308);
    result = reinterpret_cast<u32 (*)(s64 *)>(VT(handler)[0x48 / 8])(handler);
    nn::os::UnlockMutex((nn::os::MutexType *)(param_1 + 0x2e0));
    return result;
}

// 0x7100179620 -- factory: alloc 0x1b8, init with extra param from global
// PTR_DAT_71052a50b0 [inferred: global config/init parameter pointer]
s64 FUN_7100179620(void)
{
    u64 heap_id;
    s64 obj;
    u64 init_param;

    init_param = *(u64 *)PTR_DAT_71052a50b0;  // [inferred: read init param from global]
    heap_id = FUN_71000b1b90();
    obj = FUN_7100130810(0x1b8, heap_id);
    if (obj != 0) {
        FUN_7100179c70(obj, init_param);
    }
    return obj;
}
