#include "types.h"

// HARD-tier FUN_* functions — 0x7100 address range, batch hard-d-010
// Pool-d worker: linked-list ops, binary tree traversals (nn::nex free),
//                PRNG state init, struct init helpers, dtor patterns (80B each)

#define HIDDEN __attribute__((visibility("hidden")))

extern "C" {
    void *memset(void *s, int c, u64 n);
    void  free(void *ptr);
}

// ---- External data -------------------------------------------------------

// Vtable bases
extern u8 *PTR_DAT_71052a2c68 HIDDEN;
extern u8 *PTR_DAT_71052a4478 HIDDEN;
extern u8 *PTR_DAT_71052a4518 HIDDEN;
extern u8 *PTR_DAT_71052a4970 HIDDEN;
extern u8 *PTR_DAT_71052a4c30 HIDDEN;
extern u8 *PTR_DAT_71052a4e08 HIDDEN;

// Singleton pointer globals (store a pointer value)
extern u64 PTR_s_pInstance_71052a2c70 HIDDEN; // nn::pia::common::Scheduler*

// Function-pointer table globals (stores ptr-to-fptr)
extern u64 PTR_DAT_71052a14e8 HIDDEN;

// Globals whose addresses are stored (used with &)
extern u64 PTR_DAT_7104f15560 HIDDEN;
extern u64 PTR_DAT_7104f15580 HIDDEN;
extern u8  DAT_7104f155a0[] HIDDEN;

// ---- External functions --------------------------------------------------

extern void FUN_710002f100(void);
extern void FUN_71000b4760(s64 *);  // free / base-class dtor thunk (defined here too)
extern void FUN_71001c5630(u64 *);
extern void FUN_71001c9ca0(u64 *);
extern void *FUN_71001e0110(void);
extern void FUN_71000b5a90(s32 *);

// SDK namespace declarations
namespace nn {
namespace pia {
namespace common {
    void Scheduler_ResetJob(u64, s64 *); // Scheduler::ResetJob
}
}
}

namespace nn {
namespace nex {
    void MemoryManager_Free(void *);      // MemoryManager::Free
    void Network_ctor(void *);            // Network::Network()
}
}

// ---- Functions ---------------------------------------------------------------

// 0x710002f0b0 — set vtable pointer slots + call init (80 bytes)
// param_1 is a large struct; fields at 0xb5x-0xb9x store vtable/self-ref pointers
void FUN_710002f0b0(s64 param_1)
{
    *(u64 **)(param_1 + 0xb68) = &PTR_DAT_7104f15560;
    *(s64 *)(param_1 + 0xb70) = param_1 + 0x9c8;
    *(u64 **)(param_1 + 0xb80) = &PTR_DAT_7104f15580;
    *(s64 *)(param_1 + 0xb58) = param_1 + 0xd4;
    *(u16 *)(param_1 + 0x1730) = 0;
    *(s64 *)(param_1 + 0xb88) = param_1 + 0xabc;
    *(u8 **)(param_1 + 0xb98) = DAT_7104f155a0;
    *(u32 *)(param_1 + 0x1734) = 0;
    FUN_710002f100();
}

// 0x7100031190 — clear/init mixed-type struct fields (80 bytes)
void FUN_7100031190(u32 *param_1)
{
    *param_1 = 0x3020002;
    *(u16 *)(param_1 + 1) = *(u16 *)(param_1 + 1) & 0xfff0;
    *(u16 *)((s64)param_1 + 0x1a) = *(u16 *)((s64)param_1 + 0x1a) & 0xfffe;
    *(u8 *)(param_1 + 6) = 1;
    param_1[4] = 0;
    *(u64 *)(param_1 + 2) = 0;
    *(u8 *)((s64)param_1 + 6) = 0;
    param_1[7] = 0xffffffff;
}

// 0x7100031490 — conditional byte flag + capacity field init (80 bytes)
void FUN_7100031490(u8 *param_1, u64 param_2, u32 param_3, u32 param_4)
{
    *param_1 = 1;
    *(u64 *)(param_1 + 8) = param_2;
    u8 bVar1 = param_1[1] | 5;
    if ((param_3 & 1) == 0) {
        bVar1 = (u8)((param_1[1] & 0xfe) | 4);
    }
    param_1[1] = bVar1;
    u32 uVar2 = 0x1f;
    if ((param_4 & 0x20) != 0) {
        uVar2 = 0x20;
    }
    *(u32 *)(param_1 + 4) = uVar2;
    *(u64 *)(param_1 + 0xd0) = 0;
}

// 0x71000331c0 — bit-check dispatch via function pointer (80 bytes)
void FUN_71000331c0(s64 param_1, u32 param_2)
{
    if (((param_2 >> 6 & 0x48) != 0 || (param_2 & 0x4020) != 0) || (param_2 & 0x2050) != 0) {
        (*(void (*)(u64))(PTR_DAT_71052a14e8))(*(u64 *)(param_1 + 0xb8));
    }
}

// 0x7100044d60 — scatter-copy 8 u64s from src array to dst struct (80 bytes)
// Source is interleaved: src[0,2,4,6] → dst[+0x10,+0x20,+0x30,+0x40],
//                        src[1,3,5,7] → dst[+0x18,+0x28,+0x38,+0x48]
void FUN_7100044d60(s64 param_1, u64 *param_2)
{
    u64 uVar1 = param_2[1];
    *(u64 *)(param_1 + 0x28) = param_2[3];
    *(u64 *)(param_1 + 0x18) = uVar1;
    uVar1 = param_2[5];
    *(u64 *)(param_1 + 0x48) = param_2[7];
    *(u64 *)(param_1 + 0x38) = uVar1;
    uVar1 = param_2[0];
    *(u64 *)(param_1 + 0x20) = param_2[2];
    *(u64 *)(param_1 + 0x10) = uVar1;
    uVar1 = param_2[4];
    *(u64 *)(param_1 + 0x40) = param_2[6];
    *(u64 *)(param_1 + 0x30) = uVar1;
}

// 0x7100059f90 — pack render descriptor from source struct (80 bytes)
void FUN_7100059f90(u64 *param_1, s64 param_2, u64 param_3)
{
    *param_1 = *(u64 *)(*(s64 *)(param_2 + 0xb8) + 0x80);
    param_1[1] = (u64)(param_2 + 0x50);
    param_1[2] = *(u64 *)(param_2 + 0xb0);
    *(u32 *)(param_1 + 3) = 0x3f800000; // 1.0f
    *(u8 *)((s64)param_1 + 0x1c) = *(u8 *)(param_2 + 0x18e) & 1;
    *(u8 *)((s64)param_1 + 0x1d) = (*(u8 *)(param_2 + 0x18e) >> 1) & 1;
    u8 bVar1 = *(u8 *)(param_2 + 0x18e);
    *(u8 *)((s64)param_1 + 0x1f) = 0;
    param_1[4] = param_3;
    *(u8 *)((s64)param_1 + 0x1e) = (bVar1 >> 2) & 1;
}

// 0x7100081a30 — binary tree search by 48-bit composite key (80 bytes)
// Traverses left/right child links at +0x20/+0x28; key is at node+0x30
void FUN_7100081a30(s64 *param_1, u32 param_2, s64 param_3, u32 param_4)
{
    s64 lVar1 = *param_1;
    if (lVar1 != 0) {
        u64 uVar2 = (u64)param_3 << 0x30 |
                    (((u64)param_4 << 32 | (u64)param_2) & 0xffffffffffff);
        do {
            u64 uVar3;
            while (uVar3 = *(u64 *)(lVar1 + 0x30), uVar2 > uVar3 || uVar3 == uVar2) {
                if (uVar2 <= uVar3) {
                    return;
                }
                lVar1 = *(s64 *)(lVar1 + 0x28);
                if (lVar1 == 0) {
                    return;
                }
            }
            lVar1 = *(s64 *)(lVar1 + 0x20);
        } while (lVar1 != 0);
    }
}

// 0x710009a9d0 — invoke vtable[2] on doubly-nested object + update fields (80 bytes)
void FUN_710009a9d0(s64 param_1, s64 param_2)
{
    (*(void (**)())(*(u64 *)(*(s64 *)(param_1 + 8)) + 0x10))();
    *(s64 *)(param_1 + 0x10) = *(s64 *)(param_1 + 0x10) + param_2;
    *(s32 *)(param_1 + 0x18) = *(s32 *)(param_1 + 0x18) + 1;
}

// 0x71000a6710 — append node to singly-linked list at param_1+0x12a8/12b0 (80 bytes)
void FUN_71000a6710(s64 param_1, s64 param_2)
{
    s64 lVar2 = *(s64 *)(param_1 + 0x12a8);
    s64 lVar3 = lVar2;
    if (lVar2 != 0) {
        do {
            if (lVar3 == param_2) {
                return;
            }
            s64 *plVar1 = (s64 *)(lVar3 + 0x90);
            lVar3 = *plVar1;
        } while (lVar3 != 0);
        if (lVar2 != 0) {
            *(s64 *)(*(s64 *)(param_1 + 0x12b0) + 0x90) = param_2;
            goto done;
        }
    }
    *(s64 *)(param_1 + 0x12a8) = param_2;
done:
    *(s64 *)(param_1 + 0x12b0) = param_2;
    *(u64 *)(param_2 + 0x90) = 0;
}

// 0x71000b4760 — base-class dtor: reset vtable + optional Scheduler::ResetJob (80 bytes)
void FUN_71000b4760(s64 *param_1)
{
    *param_1 = (s64)(PTR_DAT_71052a2c68 + 0x10);
    if (param_1[3] != 0 && param_1[4] != 0) {
        if (PTR_s_pInstance_71052a2c70 != 0) {
            nn::pia::common::Scheduler_ResetJob(PTR_s_pInstance_71052a2c70, param_1);
        }
    }
}

// 0x71000c4cf0 — vtable[4] conditional call via sub-object at +0x50 (80 bytes)
s64 *FUN_71000c4cf0(s64 param_1, u64 param_2)
{
    s64 *plVar1 = *(s64 **)(param_1 + 0x50);
    if (plVar1 != nullptr) {
        u64 uVar2 = (*(u64 (*)(s64 *))((*plVar1) + 0x20))(plVar1);
        if ((uVar2 & 1) == 0) {
            return nullptr;
        }
        plVar1 = (s64 *)1;
        *(u64 *)(param_1 + 0xc0) = param_2;
    }
    return plVar1;
}

// ---- vtable + CallContext dtor + heap free + self-free (2 more variants) ----

// 0x7100184110
extern void FUN_71001b4760_dtor(s64 *);  // forward
namespace nn { namespace pia { namespace common {
    void CallContext_dtor(s64 *);
}}}
namespace pead { void freeToSeadHeap(void *); }

void FUN_7100184110(s64 *param_1)
{
    s64 lVar1 = param_1[0xc];
    *param_1 = (s64)(PTR_DAT_71052a4478 + 0x10);
    if (lVar1 != 0) {
        nn::pia::common::CallContext_dtor((s64 *)lVar1);
        pead::freeToSeadHeap((void *)lVar1);
    }
    param_1[0xd] = 0;
    FUN_71000b4760(param_1);
}

// 0x7100185ec0
void FUN_7100185ec0(s64 *param_1)
{
    s64 lVar1 = param_1[0xc];
    *param_1 = (s64)(PTR_DAT_71052a4518 + 0x10);
    if (lVar1 != 0) {
        nn::pia::common::CallContext_dtor((s64 *)lVar1);
        pead::freeToSeadHeap((void *)lVar1);
    }
    param_1[0xd] = 0;
    FUN_71000b4760(param_1);
}

// 0x7100193180 — set bit N in 32-bit flags at +0xc4 (80 bytes)
void FUN_7100193180(s64 param_1, u8 param_2)
{
    if (param_2 < 0x20) {
        u32 uVar1;
        if (param_2 == 0) {
            uVar1 = 1;
        } else {
            u16 uVar2 = 0;
            uVar1 = 1;
            do {
                uVar2 = uVar2 + 1;
                uVar1 = uVar1 << 1;
            } while (uVar2 < param_2);
        }
        *(u32 *)(param_1 + 0xc4) = *(u32 *)(param_1 + 0xc4) | uVar1;
    }
}

// 0x71001ad0b0 — fill 2D char table in row-major order, clear cursor fields (80 bytes)
void FUN_71001ad0b0(s64 param_1)
{
    u32 uVar1 = *(u32 *)(param_1 + 0x3c);
    if (uVar1 != 0) {
        u32 uVar2 = 0;
        do {
            u32 uVar3 = 0;
            do {
                uVar1 = uVar3 + uVar2 * uVar1;
                uVar3 = uVar3 + 1;
                *(u8 *)(*(s64 *)(param_1 + 8) + uVar1) = (u8)uVar2;
                uVar1 = *(u32 *)(param_1 + 0x3c);
            } while (uVar3 < uVar1);
            uVar2 = uVar2 + 1;
        } while (uVar2 < uVar1);
    }
    *(u64 *)(param_1 + 0x44) = 0;
    *(u64 *)(param_1 + 0x34) = 0;
}

// 0x71001b3450 — init Lehmer-style PRNG state table (624-entry LCG) (80 bytes)
void FUN_71001b3450(s32 *param_1, s32 param_2)
{
    s32 iVar2 = 0x1105;
    if (param_2 != 0) {
        iVar2 = param_2;
    }
    *param_1 = iVar2;
    param_1[1] = iVar2 * 0x10dcd;
    u64 uVar3 = 2;
    u64 uVar4 = 1;
    param_1[0x270] = 2;
    u32 uVar1;
    do {
        param_1[uVar3] = param_1[uVar4] * 0x10dcd;
        uVar4 = (u64)(u32)param_1[0x270];
        uVar1 = param_1[0x270] + 1;
        uVar3 = (u64)uVar1;
        param_1[0x270] = uVar1;
    } while (uVar1 < 0x270);
}

// 0x71001b5e10 — decode hex ASCII string into byte array (80 bytes)
// Each pair of hex chars → one byte; 'A'-'F' offset by 9; '0'-'9' offset by -48
void FUN_71001b5e10(s64 param_1, u8 *param_2, s64 param_3)
{
    if (param_3 != 0) {
        u8 *pbVar1 = (u8 *)(param_1 + 1);
        do {
            s8 cVar2 = '\t';  // 0x09: 'A'-'F' offset (A=0x41, +9 = 0x4a; *16 >> 4 = hi nibble)
            if ((u32)(pbVar1[-1] - 0x41) > 5) {
                cVar2 = '\0';
            }
            s8 cVar3 = -0x37;  // '0'-'9': 0x30 + (-0x30) = 0; 'A'-'F': 0x41 + (-0x37) = 0xa
            if ((u32)(*pbVar1 - 0x41) > 5) {
                cVar3 = -0x30;
            }
            param_3 = param_3 - 1;
            *param_2 = (u8)(*pbVar1 + cVar3 | (pbVar1[-1] + cVar2) * '\x10');
            param_2 = param_2 + 1;
            pbVar1 = pbVar1 + 2;
        } while (param_3 != 0);
    }
}

// 0x71001b6180 — reset SSO/small-string buffer to empty state (80 bytes)
void FUN_71001b6180(s64 param_1)
{
    if (param_1 + 0x20 != *(s64 *)(param_1 + 8)) {
        u64 *ptr = (u64 *)(*(s64 *)(param_1 + 8) - 0x14);
        void (*pcVar1)() = (void (*)())*ptr;
        if (pcVar1 == nullptr) {
            free(ptr);
        } else {
            pcVar1();
        }
    }
    u8 *puVar2 = (u8 *)(param_1 + 0x20);
    *puVar2 = 0;
    *(u8 **)(param_1 + 8) = puVar2;
    *(u64 *)(param_1 + 0x10) = 0x100;
    *(u8 **)(param_1 + 0x18) = puVar2;
}

// ---- Binary tree post-order traversals (nn::nex::MemoryManager::Free) --------

// 0x71001c9a90 — recurse then free extra field [+0xb0] then free node
void FUN_71001c9a90(u64 param_1, u64 *param_2)
{
    if (param_2 != nullptr) {
        FUN_71001c9a90(param_1, (u64 *)*param_2);
        FUN_71001c9a90(param_1, (u64 *)param_2[1]);
        FUN_71001c5630(param_2 + 0x16);
        nn::nex::MemoryManager_Free(param_2);
    }
}

// 0x71001c9c50 — recurse then free extra field [+4] then free node
void FUN_71001c9c50(u64 param_1, u64 *param_2)
{
    if (param_2 != nullptr) {
        FUN_71001c9c50(param_1, (u64 *)*param_2);
        FUN_71001c9c50(param_1, (u64 *)param_2[1]);
        FUN_71001c9ca0(param_2 + 4);
        nn::nex::MemoryManager_Free(param_2);
    }
}

// 0x71001ced40 — vtable[2] call + byte set + vtable[4] tail-call on sub-object (80 bytes)
void FUN_71001ced40(s64 param_1, u8 param_2)
{
    void *obj = (void *)(param_1 + 0x250);
    (*(void (**)(void *))(*(u64 **)obj + 0x10 / 8))(obj);
    *(u8 *)(param_1 + 0x24a) = param_2 & 1;
    (*(void (**)(void *))(*(u64 **)obj + 0x20 / 8))(obj);
}

// 0x71001d3950 — vtable swap + optional vtable[1] call on child + vtable restore (80 bytes)
void FUN_71001d3950(s64 *param_1)
{
    *param_1 = (s64)(PTR_DAT_71052a4c30 + 0x10);
    if ((s64 *)param_1[0x16] != nullptr) {
        void *inner = (void *)param_1[0x16];
        (*(void (**)(void *))(*(u64 **)inner + 8 / 8))(inner);
    }
    *param_1 = (s64)(PTR_DAT_71052a4970 + 0x10);
}

// 0x71001dd1b0 — post-order traversal: free all nodes (no extra child) (80 bytes)
void FUN_71001dd1b0(u64 param_1, u64 *param_2)
{
    if (param_2 != nullptr) {
        FUN_71001dd1b0(param_1, (u64 *)*param_2);
        FUN_71001dd1b0(param_1, (u64 *)param_2[1]);
        nn::nex::MemoryManager_Free(param_2);
    }
}

// 0x71001e00c0 — struct init + nn::nex::Network ctor (80 bytes)
void FUN_71001e00c0(s64 *param_1, u64 param_2, s64 param_3)
{
    void *pvVar2 = (void *)FUN_71001e0110();
    param_1[2] = 0;
    param_1[3] = param_3;
    *(u8 *)(param_1 + 4) = 0;
    *param_1 = (s64)(PTR_DAT_71052a4e08 + 0x10);
    param_1[6] = 0;
    param_1[7] = 0;
    param_1[5] = (s64)(param_1 + 6);
    nn::nex::Network_ctor(pvVar2);
}

// 0x7100219840 — post-order traversal: call fn-ptr at [4] then free node (80 bytes)
void FUN_7100219840(u64 param_1, u64 *param_2)
{
    if (param_2 != nullptr) {
        FUN_7100219840(param_1, (u64 *)*param_2);
        FUN_7100219840(param_1, (u64 *)param_2[1]);
        (*(void (***)(void))param_2[4])[0]();
        nn::nex::MemoryManager_Free(param_2);
    }
}
