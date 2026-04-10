// fun_medium_014.cpp — Matched functions from misc range
// Cleaned: removed 17 unmatched Ghidra paste functions, kept 2 verified (M)

#include "types.h"

extern "C" void FUN_7100140e60(s64*);
extern u8 PTR_DAT_71052a49d0[];

namespace pead { void freeToSeadHeap(s64); }

// 0x710011efd0 — call base dtor, overwrite vtable (quality=M)
void FUN_710011efd0(s64* param_1)
{
    FUN_7100140e60(param_1);
    *param_1 = (s64)(PTR_DAT_71052a49d0 + 0x10);
}

// 0x710013b7a0 — vtable delete sub-object at +0x80, free, zero ptr (quality=M)
void FUN_710013b7a0(s64 param_1)
{
    u64* obj = *(u64**)(param_1 + 0x80);
    if (obj != nullptr) {
        (*(void(**)(u64*))*obj)(obj);
        pead::freeToSeadHeap((s64)obj);
        *(u64*)(param_1 + 0x80) = 0;
    }
}
