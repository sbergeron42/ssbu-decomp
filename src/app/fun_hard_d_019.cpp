#include "types.h"

// HARD-tier FUN_* functions — 0x7100 address range, batch hard-d-019
// Pool-d worker: resource-tree dtors, VirtualFree hook, InkPaintModule dtor (96B each)

#define HIDDEN __attribute__((visibility("hidden")))

// ---- External data -------------------------------------------------------

extern u64  LoadedTables HIDDEN;
extern u8  *PTR_VirtualFreeHook_71052a6a70 HIDDEN;
extern u64  PTR_LAB_7104f6c4c0 HIDDEN;  // vtable label for InkPaintModule

// ---- External functions --------------------------------------------------

extern void unload_resource_by_filepathidx(u64, u32);

extern "C" {
    void free_default(void *);
}

namespace nu {
    void VirtualFreeHook(void *);
}

// ---- Functions ---------------------------------------------------------------

// 0x7100495380 — recursive binary tree dtor: conditional resource unload + free (96 bytes)
// Ghidra entry at 0x7100495360; triage 0x7100495380 is interior
void FUN_7100495380(u64 *param_1)
{
    if (param_1 != nullptr) {
        FUN_7100495380((u64 *)*param_1);
        FUN_7100495380((u64 *)param_1[1]);
        if (*(u32 *)(param_1 + 5) != 0xffffff) {
            unload_resource_by_filepathidx(LoadedTables, *(u32 *)(param_1 + 5));
            *(u32 *)(param_1 + 5) = 0xffffff;
        }
        free_default(param_1);
    }
}

// 0x710055d020 — recursive binary tree dtor: conditional VirtualFreeHook + free (96 bytes)
// Ghidra entry at 0x710055d000; triage 0x710055d020 is interior
void FUN_710055d020(u64 *param_1)
{
    if (param_1 != nullptr) {
        FUN_710055d020((u64 *)*param_1);
        FUN_710055d020((u64 *)param_1[1]);
        if ((*(u8 *)(param_1 + 5) & 1) != 0) {
            void *ptr = (void *)param_1[7];
            if (PTR_VirtualFreeHook_71052a6a70 != nullptr) {
                nu::VirtualFreeHook(ptr);
            }
            free_default(ptr);
        }
        free_default(param_1);
    }
}

// 0x71006cb860 — InkPaintModule::~InkPaintModule: vtable + linked-list free + conditional free (96 bytes)
void FUN_71006cb860(s64 *param_1)
{
    *param_1 = (s64)&PTR_LAB_7104f6c4c0;
    u64 *ptr = (u64 *)*(void **)(param_1 + 4);  // field_0x20: linked list head
    while (ptr != nullptr) {
        void *pvVar1 = (void *)*ptr;
        free_default(ptr);
        ptr = (u64 *)pvVar1;
    }
    void *pvVar1 = *(void **)(param_1 + 2);  // field_0x10
    param_1[2] = 0;
    if (pvVar1 != nullptr) {
        free_default(pvVar1);
    }
}
