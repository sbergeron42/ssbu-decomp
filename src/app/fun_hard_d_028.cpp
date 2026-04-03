#include "types.h"

// HARD-tier FUN_* functions — 0x7100 address range, batch hard-d-028
// Pool-d worker: 4x nn::nex tree-free variants, linked-list freer, crypto key init, struct ctor (64B each)

#define HIDDEN __attribute__((visibility("hidden")))

// ---- External data -------------------------------------------------------

extern u8 *PTR_DAT_71052a55e0 HIDDEN;

// ---- External functions --------------------------------------------------

extern void FUN_7100228130(void *);
extern void FUN_71001d6a00(s64 *);
extern void FUN_71001afba0(s64 *);

namespace nn {
namespace nex {
    void MemoryManager_Free(void *);
    void EncryptionAlgorithm_SetKey(s64, void *);
    void KeyedChecksumAlgorithm_SetKey(s64, void *);
    void Key_assign(s64, void *);
}
}

// ---- Functions ---------------------------------------------------------------

// 0x710021abe0 — recursive post-order binary tree free variant H (64 bytes)
void FUN_710021abe0(u64 param_1, u64 *param_2)
{
    if (param_2 != nullptr) {
        FUN_710021abe0(param_1, (u64 *)*param_2);
        FUN_710021abe0(param_1, (u64 *)param_2[1]);
        nn::nex::MemoryManager_Free((void *)param_2);
    }
}

// 0x71002281a0 — walk singly-linked list and free every node via custom free wrapper (64 bytes)
void FUN_71002281a0(s64 *param_1)
{
    if (param_1 == nullptr) {
        return;
    }
    s64 *node = (s64 *)*param_1;
    while (node != nullptr) {
        s64 *next = (s64 *)node[1];
        FUN_7100228130(node);
        node = next;
    }
    FUN_7100228130(param_1);
}

// 0x710022bac0 — set encryption, keyed-checksum, and copy key on nn::nex crypto context (64 bytes)
void FUN_710022bac0(s64 param_1, void *param_2)
{
    nn::nex::EncryptionAlgorithm_SetKey(param_1 + 0x8, param_2);
    nn::nex::KeyedChecksumAlgorithm_SetKey(param_1 + 0x2a0, param_2);
    nn::nex::Key_assign(param_1 + 0x378, param_2);
}

// 0x710022ecf0 — struct ctor: set vtable, init two sub-objects at +0x50 and +0x08 (64 bytes)
void FUN_710022ecf0(s64 *param_1)
{
    *param_1 = (s64)(PTR_DAT_71052a55e0 + 0x10);
    FUN_71001d6a00(param_1 + 0xa);
    FUN_71001afba0(param_1 + 1);
}

// 0x71002333f0 — recursive post-order binary tree free variant I (64 bytes)
void FUN_71002333f0(u64 param_1, u64 *param_2)
{
    if (param_2 != nullptr) {
        FUN_71002333f0(param_1, (u64 *)*param_2);
        FUN_71002333f0(param_1, (u64 *)param_2[1]);
        nn::nex::MemoryManager_Free((void *)param_2);
    }
}

// 0x7100246ae0 — recursive post-order binary tree free variant J (64 bytes)
void FUN_7100246ae0(u64 param_1, u64 *param_2)
{
    if (param_2 != nullptr) {
        FUN_7100246ae0(param_1, (u64 *)*param_2);
        FUN_7100246ae0(param_1, (u64 *)param_2[1]);
        nn::nex::MemoryManager_Free((void *)param_2);
    }
}

// 0x7100293800 — recursive post-order binary tree free variant K (64 bytes)
void FUN_7100293800(u64 param_1, u64 *param_2)
{
    if (param_2 != nullptr) {
        FUN_7100293800(param_1, (u64 *)*param_2);
        FUN_7100293800(param_1, (u64 *)param_2[1]);
        nn::nex::MemoryManager_Free((void *)param_2);
    }
}
