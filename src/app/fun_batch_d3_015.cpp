#include "types.h"

// MEDIUM-tier FUN_* functions — 0x7100 address range, batch d3-015
// Pool-d worker: auto-generated from Ghidra decompilation

// ---- External declarations -----------------------------------------------

extern "C" void *memset(void *, int, u64);

namespace nn {
    namespace util {
        void ReferSymbol(const char *);
    }
    namespace os {
        void InitializeMutex(void *, bool, int);
    }
    namespace pia { namespace common {
        struct Time { static void SetNow(void *); };
    } }
}

// ---- Functions ---------------------------------------------------------------

// 0x71000af310 — empty stub (16 bytes)
void FUN_71000af310(void)
{
}

// 0x71000afc80 — indexed read: return u64 at param_1 + param_2*8 + 0x50 (16 bytes)
u64 FUN_71000afc80(s64 param_1, u32 param_2)
{
    return *(u64 *)(param_1 + (u64)param_2 * 8 + 0x50);
}

// 0x71000afc90 — empty stub (16 bytes)
void FUN_71000afc90(void)
{
}

// 0x71000afca0 — pointer arithmetic: return param_1 + param_2*0x10 + 0x20 (16 bytes)
s64 FUN_71000afca0(s64 param_1, u32 param_2)
{
    return param_1 + (u64)param_2 * 0x10 + 0x20;
}

// 0x71000b18f0 — empty stub (16 bytes)
void FUN_71000b18f0(void)
{
}

// 0x71000b1940 — SDK symbol anchor: call ReferSymbol with SDK version string (32 bytes)
void FUN_71000b1940(void)
{
    nn::util::ReferSymbol("SDK MW+Nintendo+PiaCommon-5_19_1");
}

// 0x71000b1cf0 — empty stub (32 bytes)
void FUN_71000b1cf0(void)
{
}

// 0x71000b3840 — setter: write param_2 to +0x598 (16 bytes)
void FUN_71000b3840(s64 param_1, u64 param_2)
{
    *(u64 *)(param_1 + 0x598) = param_2;
}

// 0x71000b3850 — setter: clear +0x598 (16 bytes)
void FUN_71000b3850(s64 param_1)
{
    *(u64 *)(param_1 + 0x598) = 0;
}

// 0x71000b4140 — empty dtor: ~CallContext (16 bytes)
void FUN_71000b4140(void)
{
}

// 0x71000b4150 — setter: write two u64 fields at +0x18 and +0x20 (16 bytes)
void FUN_71000b4150(s64 param_1, u64 param_2, u64 param_3)
{
    *(u64 *)(param_1 + 0x18) = param_2;
    *(u64 *)(param_1 + 0x20) = param_3;
}

// 0x71000b4160 — InitiateCall: set result=1, clear pending byte, return 1 (32 bytes)
u64 FUN_71000b4160(u32 *param_1)
{
    *param_1 = 1;
    *(u8 *)(param_1 + 10) = 0;
    return 1;
}

// 0x71000b4c30 — init mutex: call nn::os::InitializeMutex(param_1, true, 0) (16 bytes)
void FUN_71000b4c30(void *param_1)
{
    nn::os::InitializeMutex(param_1, true, 0);
}

// 0x71000b50c0 — zero-init: memset param_1 to 0 for 0x188 bytes (16 bytes)
void FUN_71000b50c0(void *param_1)
{
    memset(param_1, 0, 0x188);
}

// 0x71000b65e0 — init: set sentinel, clear field, set flag, call Time::SetNow (32 bytes)
void FUN_71000b65e0(u32 *param_1)
{
    *param_1 = 0xffffffff;
    *(u64 *)(param_1 + 2) = 0;
    *(u8 *)(param_1 + 4) = 1;
    nn::pia::common::Time::SetNow(param_1 + 2);
}

// 0x71000b6600 — empty stub (16 bytes)
void FUN_71000b6600(void)
{
}

// 0x71000b71c0 — dequeue: unlink head node, decrement count, return it (64 bytes)
s64 *FUN_71000b71c0(u64 *param_1)
{
    s64 lVar1;
    s32 iVar2;
    s64 *plVar3;

    iVar2 = *(s32 *)(param_1 + 2);
    if (iVar2 != 0) {
        plVar3 = (s64 *)*param_1;
        lVar1 = *plVar3;
        *(s64 *)(lVar1 + 8) = plVar3[1];
        *(s64 *)plVar3[1] = lVar1;
        *plVar3 = 0;
        plVar3[1] = 0;
        *(s32 *)(param_1 + 2) = iVar2 + -1;
        return plVar3;
    }
    return (s64 *)0x0;
}

// 0x71000b7080 — ListBase::Init: self-referential circular list init (16 bytes)
void FUN_71000b7080(s64 param_1)
{
    *(s64 *)param_1 = param_1;
    *(s64 *)(param_1 + 8) = param_1;
    *(u32 *)(param_1 + 0x10) = 0;
}

// 0x71000b8870 — GetSerializedSize: return 0x10 (16 bytes)
u64 FUN_71000b8870(void)
{
    return 0x10;
}

// 0x71000b8bc0 — GetSerializedSize: return 0x10 (16 bytes)
u64 FUN_71000b8bc0(void)
{
    return 0x10;
}

// 0x71000b9f30 — init sentinels: set 0xffffffff, clear byte, set 0xffffffff at +0xc (32 bytes)
void FUN_71000b9f30(u64 *param_1)
{
    *param_1 = 0xffffffff;
    *(u8 *)(param_1 + 1) = 0;
    *(u32 *)((s64)param_1 + 0xc) = 0xffffffff;
}

// 0x71000b9f50 — empty dtor: ~Socket (16 bytes)
void FUN_71000b9f50(void)
{
}

// 0x71000baa00 — empty stub (16 bytes)
void FUN_71000baa00(void)
{
}

// 0x71000baa10 — empty stub (16 bytes)
void FUN_71000baa10(void)
{
}

// 0x71000bae40 — GetBuffer: return ptr at +8 (16 bytes)
u64 FUN_71000bae40(s64 param_1)
{
    return *(u64 *)(param_1 + 8);
}

// 0x71000bae50 — getter: return u32 at +0x14 (16 bytes)
u32 FUN_71000bae50(s64 param_1)
{
    return *(u32 *)(param_1 + 0x14);
}

// 0x71000bae60 — getter: return u64 at +8 (16 bytes)
u64 FUN_71000bae60(s64 param_1)
{
    return *(u64 *)(param_1 + 8);
}

// 0x71000bb970 — bswap64: byte-swap u64 via bit manipulation (16 bytes)
u64 FUN_71000bb970(u64 *param_1)
{
    u64 uVar1;

    uVar1 = (*param_1 & 0xff00ff00ff00ff00ULL) >> 8 | (*param_1 & 0xff00ff00ff00ffULL) << 8;
    uVar1 = (uVar1 & 0xffff0000ffff0000ULL) >> 0x10 | (uVar1 & 0xffff0000ffffULL) << 0x10;
    return uVar1 >> 0x20 | uVar1 << 0x20;
}

// 0x71000bb9d0 — byte store: *param_1 = param_2 (16 bytes)
void FUN_71000bb9d0(u8 *param_1, u8 param_2)
{
    *param_1 = param_2;
}

// 0x71000bb9e0 — byte load: return *param_1 (16 bytes)
u8 FUN_71000bb9e0(u8 *param_1)
{
    return *param_1;
}

// 0x71000bc790 — empty stub (16 bytes)
void FUN_71000bc790(void)
{
}
