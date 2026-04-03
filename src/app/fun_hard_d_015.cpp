#include "types.h"

// HARD-tier FUN_* functions — 0x7100 address range, batch hard-d-015
// Pool-d worker: nn::nex tree dtors, String/Key/Buffer dtors, conditional field assign (96B each)

#define HIDDEN __attribute__((visibility("hidden")))

// ---- External data -------------------------------------------------------

// Vtable bases
extern u8 *PTR_DAT_71052a2d80 HIDDEN;
extern u8 *PTR_DAT_71052a5680 HIDDEN;
extern u8 *PTR_DAT_71052a5978 HIDDEN;

// Data constant (empty string sentinel)
extern u8 DAT_710440f4cc HIDDEN;

// ---- External functions --------------------------------------------------

extern void FUN_7100229f10(void);
extern void FUN_7100232cb0(s64 *);
extern void FUN_7100235160(s64 *);
extern void FUN_71001b3cb0(s64, u8 *);
extern u64  FUN_71001b4d20(u64);
extern void FUN_71001b2f70(s64, s64);

extern "C" {
    void free_default(void *);
}

namespace nn {
namespace nex {
    void String_DeleteContent(u64 *);  // nn::nex::String::DeleteContent (this = node+4)
    void InetAddress_dtor(u64 *);      // nn::nex::InetAddress::~InetAddress
    void MemoryManager_Free(void *);   // nn::nex::MemoryManager::Free
    void Key_dtor(s64 *);              // nn::nex::Key::~Key
    void Buffer_dtor(s64 *);           // nn::nex::Buffer::~Buffer
    void RootObject_delete(s64 *);     // nn::nex::RootObject::operator_delete
    s64  String_GetLength(s64);        // nn::nex::String::GetLength
}
}

// ---- Functions ---------------------------------------------------------------

// 0x7100219ca0 — recursive binary tree dtor: String node free (96 bytes)
void FUN_7100219ca0(u64 param_1, u64 *param_2)
{
    if (param_2 != nullptr) {
        FUN_7100219ca0(param_1, (u64 *)*param_2);
        FUN_7100219ca0(param_1, (u64 *)param_2[1]);
        param_2[4] = (u64)(PTR_DAT_71052a2d80 + 0x10);
        nn::nex::String_DeleteContent(param_2 + 4);
        nn::nex::MemoryManager_Free((void *)param_2);
    }
}

// 0x710021acc0 — recursive binary tree dtor: 2x InetAddress dtor + MemoryManager::Free (96 bytes)
void FUN_710021acc0(u64 param_1, u64 *param_2)
{
    if (param_2 != nullptr) {
        FUN_710021acc0(param_1, (u64 *)*param_2);
        FUN_710021acc0(param_1, (u64 *)param_2[1]);
        nn::nex::InetAddress_dtor(param_2 + 0x16);
        nn::nex::InetAddress_dtor(param_2 + 4);
        nn::nex::MemoryManager_Free((void *)param_2);
    }
}

// 0x71002317b0 — dtor: vtable + set String vtable + String/Key/Buffer dtors + RootObject delete (96 bytes)
void FUN_71002317b0(s64 *param_1)
{
    u8 *puVar1 = PTR_DAT_71052a2d80 + 0x10;
    *param_1 = (s64)(PTR_DAT_71052a5680 + 0x10);
    param_1[0x12] = (s64)puVar1;
    nn::nex::String_DeleteContent((u64 *)(param_1 + 0x12));
    nn::nex::Key_dtor(param_1 + 0xb);
    nn::nex::Buffer_dtor(param_1 + 2);
    nn::nex::RootObject_delete(param_1);
}

// 0x7100242df0 — dtor: vtable + FUN_7100229f10 + 2 sub-dtors + RootObject delete (96 bytes)
void FUN_7100242df0(s64 *param_1)
{
    *param_1 = (s64)(PTR_DAT_71052a5978 + 0x10);
    FUN_7100229f10();
    FUN_7100232cb0(param_1 + 4);
    FUN_7100235160(param_1);
    nn::nex::RootObject_delete(param_1);
}

// ---- String-length check + conditional field assign (2 variants, 96 bytes each) ----
// If string empty: clear field to DAT_710440f4cc; else: validate and copy.

// 0x7100254970 — operate on param_1+0x128
u64 FUN_7100254970(s64 param_1, s64 param_2)
{
    s64 lVar1 = nn::nex::String_GetLength(param_2);
    if (lVar1 == 0) {
        FUN_71001b3cb0(param_1 + 0x128, &DAT_710440f4cc);
    } else {
        lVar1 = FUN_71001b4d20(*(u64 *)(param_2 + 0x18));
        if (lVar1 == 0) {
            return 0;
        }
        FUN_71001b2f70(param_1 + 0x128, param_2);
    }
    return 1;
}

// 0x7100255ba0 — identical pattern at param_1+0x108
u64 FUN_7100255ba0(s64 param_1, s64 param_2)
{
    s64 lVar1 = nn::nex::String_GetLength(param_2);
    if (lVar1 == 0) {
        FUN_71001b3cb0(param_1 + 0x108, &DAT_710440f4cc);
    } else {
        lVar1 = FUN_71001b4d20(*(u64 *)(param_2 + 0x18));
        if (lVar1 == 0) {
            return 0;
        }
        FUN_71001b2f70(param_1 + 0x108, param_2);
    }
    return 1;
}

// 0x71002c5580 — recursive binary tree free: conditional free_default on flag bits (96 bytes)
void FUN_71002c5580(u64 *param_1)
{
    if (param_1 != nullptr) {
        FUN_71002c5580((u64 *)*param_1);
        FUN_71002c5580((u64 *)param_1[1]);
        if ((*(u8 *)(param_1 + 7) & 1) != 0 && (void *)param_1[9] != nullptr) {
            free_default((void *)param_1[9]);
        }
        if ((*(u8 *)(param_1 + 4) & 1) != 0 && (void *)param_1[6] != nullptr) {
            free_default((void *)param_1[6]);
        }
        free_default(param_1);
    }
}
