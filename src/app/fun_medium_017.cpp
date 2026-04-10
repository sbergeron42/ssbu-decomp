// fun_medium_017.cpp — Matched nn::pia networking functions
// Cleaned: removed 16 unmatched Ghidra paste functions, kept 5 verified (M)

#include "types.h"

// placement new (not available without <new> in this toolchain; size_t = unsigned long on AArch64)
inline void* operator new(unsigned long, void* p) noexcept { return p; }
inline void  operator delete(void*, void*) noexcept {}

namespace nn { namespace pia { namespace common {
    struct StepSequenceJob { StepSequenceJob(); };
    namespace HeapManager { u64 GetHeap(); }
}}}

namespace pead { s64 allocateFromSeadHeap(u64 size, u64 heap); }

extern "C" void FUN_7100165090();
extern "C" void FUN_7100170470(s64, u64);

extern u8 PTR_DAT_71052a4f40[];   // StepSequenceJob vtable
extern u8 PTR_DAT_71052a51e0[];   // StepSequenceJob vtable
extern u8 PTR_DAT_71052a5210[];   // StepSequenceJob vtable

// 0x710014f1c0 — construct StepSequenceJob base, override vtable (quality=M)
void FUN_710014f1c0(s64* param_1)
{
    new (param_1) nn::pia::common::StepSequenceJob();
    *param_1 = (s64)(PTR_DAT_71052a4f40 + 0x10);
}

// 0x7100163b10 — call setup, zero field at +0x4d0 (quality=M)
void FUN_7100163b10(s64 param_1)
{
    FUN_7100165090();
    *(u64*)(param_1 + 0x4d0) = 0;
}

// 0x7100173e80 — construct StepSequenceJob, zero/store fields, set vtable (quality=M)
void FUN_7100173e80(s64* param_1, s64 param_2)
{
    new (param_1) nn::pia::common::StepSequenceJob();
    param_1[0xb] = 0;
    param_1[0xc] = param_2;
    *param_1     = (s64)(PTR_DAT_71052a51e0 + 0x10);
}

// 0x71001758d0 — same as 7100173e80 but different vtable (quality=M)
void FUN_71001758d0(s64* param_1, s64 param_2)
{
    new (param_1) nn::pia::common::StepSequenceJob();
    param_1[0xb] = 0;
    param_1[0xc] = param_2;
    *param_1     = (s64)(PTR_DAT_71052a5210 + 0x10);
}

// 0x710016bb30 — GetHeap + alloc 0xa8 bytes + call init (quality=M)
s64 FUN_710016bb30(u64 param_1)
{
    u64 heap = nn::pia::common::HeapManager::GetHeap();
    s64 obj = pead::allocateFromSeadHeap(0xa8, heap);
    if (obj != 0) {
        FUN_7100170470(obj, param_1);
    }
    return obj;
}
