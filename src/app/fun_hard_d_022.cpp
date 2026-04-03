#include "types.h"

// HARD-tier FUN_* functions — 0x7101 address range, batch hard-d-022
// Pool-d worker: nn::nex map insert (96B interior), dtor 4x String (80B interior), string-clear + cleanup (80B interior)

#define HIDDEN __attribute__((visibility("hidden")))

// ---- External data -------------------------------------------------------

extern u64 PTR_FUN_710509b3e8 HIDDEN;
extern u64 PTR_LAB_710509ac08 HIDDEN;
extern u64 PTR_LAB_710509b2e8 HIDDEN;
extern u64 PTR_LAB_710509b2c8 HIDDEN;

// ---- External functions --------------------------------------------------

extern void FUN_71001d7780(s64 *);

namespace nn {
namespace nex {
    void String_DeleteContent(u64 *);
    void String_Assign(u64 *, u64, u64);
    void MemoryManager_Free(void *);
    void *MemoryManager_Allocate(u64);
}
}

// ---- Functions ---------------------------------------------------------------

// 0x71017123e0 — non-deleting dtor: vtable + 4x String::DeleteContent (80 bytes, interior)
// Ghidra entry at 0x7101712390; triage address 0x71017123e0 is interior
void FUN_7101712390(s64 *param_1)
{
    *param_1 = (s64)&PTR_FUN_710509b3e8;
    param_1[0x11] = (s64)&PTR_LAB_710509ac08;
    nn::nex::String_DeleteContent((u64 *)(param_1 + 0x11));
    param_1[0xc] = (s64)&PTR_LAB_710509ac08;
    nn::nex::String_DeleteContent((u64 *)(param_1 + 0xc));
    param_1[7] = (s64)&PTR_LAB_710509ac08;
    nn::nex::String_DeleteContent((u64 *)(param_1 + 7));
    param_1[2] = (s64)&PTR_LAB_710509ac08;
    nn::nex::String_DeleteContent((u64 *)(param_1 + 2));
}

// 0x710171cff0 — clear string + 3x FUN_71001d7780 cleanup (80 bytes, interior)
// Ghidra entry at 0x710171cf20; triage address 0x710171cff0 is interior
void FUN_710171cf20(s64 param_1)
{
    u8  local_40;
    u8 *local_30;
    u64 local_28;
    u64 local_48;

    *(u16 *)(param_1 + 9) = 0;
    *(u8 *)(param_1 + 0xb) = 0;
    local_40 = 0;
    local_28 = 0x10;
    local_30 = &local_40;
    if ((u8 **)(param_1 + 0x10) != (u8 **)&local_48) {
        u8 *puVar1 = (u8 *)(param_1 + 0x18);
        local_40 = *puVar1;
        local_30 = *(u8 **)(param_1 + 0x28);
        *puVar1 = 0;
        local_28 = *(u64 *)(param_1 + 0x30);
        *(u8 **)(param_1 + 0x28) = &local_40;
        *(u64 *)(param_1 + 0x30) = 0x10;
        if (local_30 == puVar1) {
            local_30 = &local_40;
        }
        *(u8 **)(param_1 + 0x28) = puVar1;
    }
    local_48 = (u64)&PTR_LAB_710509ac08;
    nn::nex::String_DeleteContent(&local_48);
    FUN_71001d7780((s64 *)(param_1 + 0x38));
    FUN_71001d7780((s64 *)(param_1 + 0x70));
    FUN_71001d7780((s64 *)(param_1 + 0xa8));
}

// 0x7101711b30 — vector copy ctor: allocate + copy nn::nex objects with two String fields each (80 bytes, interior)
// Ghidra entry at 0x7101711a50; triage address 0x7101711b30 is interior
void FUN_7101711a50(u64 *param_1, s64 *param_2)
{
    param_1[1] = 0;
    param_1[2] = 0;
    param_1[0] = 0;
    if (param_2[1] - param_2[0] != 0) {
        s64 lVar3 = (param_2[1] - param_2[0]) >> 5;
        if (0x2aaaaaaaaaaaaaa < (u64)((u64)lVar3 * (u64)-0x5555555555555555)) {
            // would overflow — abort via throw
            return;
        }
        u64 *puVar2 = (u64 *)nn::nex::MemoryManager_Allocate((u64)(lVar3 * 0x60));
        param_1[2] = (u64)(puVar2 + (u64)lVar3 * 4);
        param_1[0] = (u64)puVar2;
        param_1[1] = (u64)puVar2;
        s64 lVar1 = param_2[1];
        for (s64 lVar4 = param_2[0]; lVar4 != lVar1; lVar4 += 0x60) {
            *puVar2 = (u64)&PTR_LAB_710509b2e8;
            *(u8 *)(puVar2 + 1) = *(u8 *)(lVar4 + 8);
            puVar2[2] = (u64)&PTR_LAB_710509ac08;
            *(u8 *)(puVar2 + 3) = 0;
            puVar2[5] = (u64)(puVar2 + 3);
            puVar2[6] = 0x10;
            nn::nex::String_Assign(puVar2 + 2, *(u64 *)(lVar4 + 0x28), 0xffffffffffffffff);
            puVar2[7] = (u64)&PTR_LAB_710509ac08;
            *(u8 *)(puVar2 + 8) = 0;
            puVar2[10] = (u64)(puVar2 + 8);
            puVar2[0xb] = 0x10;
            nn::nex::String_Assign(puVar2 + 7, *(u64 *)(lVar4 + 0x50), 0xffffffffffffffff);
            *puVar2 = (u64)&PTR_LAB_710509b2c8;
            puVar2 = (u64 *)(param_1[1] + 0x60);
            param_1[1] = (u64)puVar2;
        }
    }
}
