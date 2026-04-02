#include "types.h"

// MEDIUM-tier FUN_* functions — 0x7100 address range, batch d3-018
// Pool-d worker: auto-generated from Ghidra decompilation

// ---- External declarations -----------------------------------------------

namespace nn {
    namespace os {
        void WaitEvent(void *);
        void ClearEvent(void *);
        void SendMessageQueue(void *, u64);
        void JamMessageQueue(void *, u64);
    }
    namespace pia { namespace common {
        struct CriticalSection {
            static void Lock(void *);
            static void Unlock(void *);
        };
    } }
}

// ---- Functions ---------------------------------------------------------------

// 0x710011be50 — offset: return param_1 + 0x18 (16 bytes)
s64 FUN_710011be50(s64 param_1)
{
    return param_1 + 0x18;
}

// 0x710011be60 — offset: return param_1 + 0x900 (16 bytes)
s64 FUN_710011be60(s64 param_1)
{
    return param_1 + 0x900;
}

// 0x710012cf40 — setter: write u16 to +0x18 (48 bytes)
void FUN_710012cf40(s64 param_1, u16 param_2)
{
    *(u16 *)(param_1 + 0x18) = param_2;
}

// 0x710012cf70 — setter: write param_2&1 to byte at +0x1e (16 bytes)
void FUN_710012cf70(s64 param_1, u8 param_2)
{
    *(u8 *)(param_1 + 0x1e) = param_2 & 1;
}

// 0x710012eb20 — set two u16 fields, OR bit 1 into flag (32 bytes)
void FUN_710012eb20(s64 param_1, u16 param_2)
{
    *(u16 *)(param_1 + 0x256) = param_2;
    *(u16 *)(param_1 + 600) = param_2;
    *(u32 *)(param_1 + 0x260) = *(u32 *)(param_1 + 0x260) | 1;
}

// 0x710012eb40 — set two u16 fields, OR bit 2 into flag (32 bytes)
void FUN_710012eb40(s64 param_1, u16 param_2)
{
    *(u16 *)(param_1 + 0x25a) = param_2;
    *(u16 *)(param_1 + 0x25c) = param_2;
    *(u32 *)(param_1 + 0x260) = *(u32 *)(param_1 + 0x260) | 2;
}

// 0x710012eb60 — setter: write byte&1 to +0x25e, OR bit 4 (32 bytes)
void FUN_710012eb60(s64 param_1, u8 param_2)
{
    *(u8 *)(param_1 + 0x25e) = param_2 & 1;
    *(u32 *)(param_1 + 0x260) = *(u32 *)(param_1 + 0x260) | 4;
}

// 0x710012eb80 — setter: write byte&1 to +0x25f, OR bit 8 (32 bytes)
void FUN_710012eb80(s64 param_1, u8 param_2)
{
    *(u8 *)(param_1 + 0x25f) = param_2 & 1;
    *(u32 *)(param_1 + 0x260) = *(u32 *)(param_1 + 0x260) | 8;
}

// 0x710012eba0 — setter: write u32 to +0x20, OR bit 0x10 (32 bytes)
void FUN_710012eba0(s64 param_1, u32 param_2)
{
    *(u32 *)(param_1 + 0x20) = param_2;
    *(u32 *)(param_1 + 0x260) = *(u32 *)(param_1 + 0x260) | 0x10;
}

// 0x710012ebc0 — setter: write u32 to +0x24, OR bit 0x20 (32 bytes)
void FUN_710012ebc0(s64 param_1, u32 param_2)
{
    *(u32 *)(param_1 + 0x24) = param_2;
    *(u32 *)(param_1 + 0x260) = *(u32 *)(param_1 + 0x260) | 0x20;
}

// 0x710012fd50 — setter: write u64 to +0x60 (16 bytes)
void FUN_710012fd50(s64 param_1, u64 param_2)
{
    *(u64 *)(param_1 + 0x60) = param_2;
}

// 0x710012fd60 — getter: return u64 at +0x60 (16 bytes)
u64 FUN_710012fd60(s64 param_1)
{
    return *(u64 *)(param_1 + 0x60);
}

// 0x7100130530 — constant: return 0x32 (32 bytes)
u64 FUN_7100130530(void)
{
    return 0x32;
}

// 0x7100130ac0 — list insert: splice param_2 after *param_1 head (32 bytes)
void FUN_7100130ac0(s64 *param_1, s64 *param_2)
{
    s64 lVar1;

    lVar1 = *param_1;
    *param_1 = (s64)param_2;
    *param_2 = lVar1;
    param_2[1] = (s64)param_1;
    if (lVar1 != 0) {
        *(s64 **)(lVar1 + 8) = param_2;
    }
}

// 0x7100130b10 — list clear: walk list zeroing nodes, re-init sentinel (48 bytes)
void FUN_7100130b10(u64 *param_1)
{
    u64 *puVar1;
    u64 *puVar2;

    puVar1 = (u64 *)param_1[1];
    while (puVar1 != param_1) {
        puVar2 = (u64 *)puVar1[1];
        *puVar1 = 0;
        puVar1[1] = 0;
        puVar1 = puVar2;
    }
    *(u32 *)(param_1 + 2) = 0;
    *param_1 = (u64)param_1;
    param_1[1] = (u64)param_1;
}

// 0x7100135690 — copy: u64 field from param_2+8 to param_1+8 (32 bytes)
void FUN_7100135690(s64 param_1, s64 param_2)
{
    *(u64 *)(param_1 + 8) = *(u64 *)(param_2 + 8);
}

// 0x7100135780 — null-terminate: write 0 at ptr[count-1] (32 bytes)
void FUN_7100135780(s64 param_1)
{
    *(u8 *)(*(s64 *)(param_1 + 8) + (s64)*(s32 *)(param_1 + 0x10) + -1) = 0;
}

// 0x710013bb20 — WaitEvent: wait on event at +0x20 (16 bytes)
void FUN_710013bb20(s64 param_1)
{
    nn::os::WaitEvent((void *)(param_1 + 0x20));
}

// 0x710013bb70 — ClearEvent: clear event at +0x20 (16 bytes)
void FUN_710013bb70(s64 param_1)
{
    nn::os::ClearEvent((void *)(param_1 + 0x20));
}

// 0x710013bb90 — empty stub (16 bytes)
void FUN_710013bb90(void)
{
}

// 0x710013bc98 — SendMessageQueue wrapper: send and return 1 (24 bytes)
u64 FUN_710013bc98(void *param_1, u64 param_2)
{
    nn::os::SendMessageQueue(param_1, param_2);
    return 1;
}

// 0x710013bd08 — JamMessageQueue wrapper: jam and return 1 (24 bytes)
u64 FUN_710013bd08(void *param_1, u64 param_2)
{
    nn::os::JamMessageQueue(param_1, param_2);
    return 1;
}

// 0x710013bde0 — CriticalSection::Lock at +0x20 (16 bytes)
void FUN_710013bde0(s64 param_1)
{
    nn::pia::common::CriticalSection::Lock((void *)(param_1 + 0x20));
}

// 0x710013bdf0 — CriticalSection::Unlock at +0x20 (16 bytes)
void FUN_710013bdf0(s64 param_1)
{
    nn::pia::common::CriticalSection::Unlock((void *)(param_1 + 0x20));
}
