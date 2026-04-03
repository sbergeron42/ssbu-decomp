#include "types.h"

// HARD-tier FUN_* functions — 0x7100 address range, batch hard-d-017
// Pool-d worker: nn::nex tree dtors, Key/Buffer/String dtor variants (80B each)

#define HIDDEN __attribute__((visibility("hidden")))

// ---- External data -------------------------------------------------------

// Vtable bases
extern u8 *PTR_DAT_71052a2d80 HIDDEN;
extern u8 *PTR_DAT_71052a5680 HIDDEN;
extern u8 *PTR_DAT_71052a5aa8 HIDDEN;

// ---- External functions --------------------------------------------------

extern void FUN_710024af90(void);
extern void FUN_7100232cb0(s64 *);
extern void FUN_7100235160(s64 *);
extern void FUN_7103736840(u64 *);

extern "C" {
    void free_default(void *);
}

namespace nn {
namespace nex {
    void InetAddress_dtor(u64 *);    // nn::nex::InetAddress::~InetAddress
    void MemoryManager_Free(void *); // nn::nex::MemoryManager::Free
    void String_DeleteContent(u64 *);
    void Key_dtor(s64 *);
    void Buffer_dtor(s64 *);
    void RootObject_delete(s64 *);
}
}

// ---- Functions ---------------------------------------------------------------

// 0x710021ac70 — recursive binary tree dtor: InetAddress dtor + MemoryManager::Free (80 bytes)
void FUN_710021ac70(u64 param_1, u64 *param_2)
{
    if (param_2 != nullptr) {
        FUN_710021ac70(param_1, (u64 *)*param_2);
        FUN_710021ac70(param_1, (u64 *)param_2[1]);
        nn::nex::InetAddress_dtor(param_2 + 5);
        nn::nex::MemoryManager_Free((void *)param_2);
    }
}

// 0x7100231760 — non-deleting dtor: vtable + String::DeleteContent + Key::~Key + Buffer::~Buffer (80 bytes)
// (Sibling of FUN_71002317b0 which adds RootObject::delete)
void FUN_7100231760(s64 *param_1)
{
    u8 *puVar1 = PTR_DAT_71052a2d80 + 0x10;
    *param_1 = (s64)(PTR_DAT_71052a5680 + 0x10);
    param_1[0x12] = (s64)puVar1;
    nn::nex::String_DeleteContent((u64 *)(param_1 + 0x12));
    nn::nex::Key_dtor(param_1 + 0xb);
    nn::nex::Buffer_dtor(param_1 + 2);
}

// ---- vtable + FUN_710024af90 + 2x FUN_7100232cb0 + FUN_7100235160 (2 variants, 80 bytes each) ----

// 0x710024af40 — non-deleting dtor
void FUN_710024af40(s64 *param_1)
{
    *param_1 = (s64)(PTR_DAT_71052a5aa8 + 0x10);
    FUN_710024af90();
    FUN_7100232cb0(param_1 + 0x16);
    FUN_7100232cb0(param_1 + 4);
    FUN_7100235160(param_1);
}

// 0x710024b0f0 — deleting dtor (adds RootObject::delete)
void FUN_710024b0f0(s64 *param_1)
{
    *param_1 = (s64)(PTR_DAT_71052a5aa8 + 0x10);
    FUN_710024af90();
    FUN_7100232cb0(param_1 + 0x16);
    FUN_7100232cb0(param_1 + 4);
    FUN_7100235160(param_1);
    nn::nex::RootObject_delete(param_1);
}

// 0x710057d5e0 — recursive binary tree dtor: FUN_7103736840 cleanup + sentinel + free_default (80 bytes)
// Note: Ghidra resolves entry at 0x710057d5c0; triage address 0x710057d5e0 is a mid-entry variant
void FUN_710057d5e0(u64 *param_1)
{
    if (param_1 != nullptr) {
        FUN_710057d5e0((u64 *)*param_1);
        FUN_710057d5e0((u64 *)param_1[1]);
        FUN_7103736840(param_1 + 5);
        *(u32 *)(param_1 + 6) = 0xffffffff;
        param_1[5] = 0;
        free_default(param_1);
    }
}
