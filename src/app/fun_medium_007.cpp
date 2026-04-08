#include "types.h"

// MEDIUM-tier FUN_* functions -- mixed address range, batch 8
// Pool-d worker: auto-generated from Ghidra decompilation

// ---- External declarations -----------------------------------------------

namespace std { namespace __1 {
template<bool> struct __vector_base_common {
    [[noreturn]] static void __throw_out_of_range();
};
}}
extern "C" void* memset(void*, int, u64);

// nn::os
namespace nn {
namespace os {
    struct MessageQueueType;
    void SendMessageQueue(MessageQueueType*, u64);
    void JamMessageQueue(MessageQueueType*, u64);
    u64  GetSystemTickFrequency();
}
namespace detail {
    [[noreturn]] void UnexpectedDefaultImpl(const char*, const char*, int);
}
}

// External function forward declarations
extern "C" void FUN_710015ffc0(s64, s64);
extern "C" u8   FUN_7100175220(u64);
extern "C" void FUN_71001d2570();
extern "C" void FUN_71001d2830();
extern "C" void FUN_71001d90c0();
extern "C" u32  FUN_71001b34a0(void*);
extern "C" void FUN_71001f2ba0(u64, void*, s32);
extern "C" void FUN_710020f2b0();
extern "C" void FUN_71002105a0();
extern "C" void* FUN_7100228110(u64);
extern "C" u64  FUN_71001b4d20(u64);
extern "C" u64  FUN_71002b64f0();
extern "C" void FUN_71002bb530(s64);
extern "C" void FUN_71002bb540(s64);
extern "C" void FUN_71002c2e40(u64);
extern "C" void FUN_71002c3200(void*);

// External data
extern u64  PTR_DAT_71052a3cd0;
extern u8   DAT_710449be3e;
extern u8   DAT_710449be43;
extern u8   DAT_710449be5b;
extern u8   DAT_000048d8;
extern u8   DAT_00006e48;

// ---- Functions -----------------------------------------------------------

// 7100d9e8a4
[[noreturn]] void FUN_7100d9e8a4()
{
    std::__1::__vector_base_common<true>::__throw_out_of_range();
}

// 7100fbe214
[[noreturn]] void FUN_7100fbe214()
{
    std::__1::__vector_base_common<true>::__throw_out_of_range();
}

// 7100655f50
[[noreturn]] void FUN_7100655f50()
{
    std::__1::__vector_base_common<true>::__throw_out_of_range();
}

// 710065f6a0
[[noreturn]] void FUN_710065f6a0()
{
    std::__1::__vector_base_common<true>::__throw_out_of_range();
}

// 7100621458
[[noreturn]] void FUN_7100621458()
{
    std::__1::__vector_base_common<true>::__throw_out_of_range();
}

// 71000338f0
void FUN_71000338f0(void* param_1)
{
    memset(param_1, 0, 0x120);
}

// 7100037d20
void FUN_7100037d20(void* param_1)
{
    memset(param_1, 0, 0x2028);
}

// 710003a5f0
void FUN_710003a5f0(void* param_1)
{
    memset(param_1, 0, 0x3018);
}

// 710013b910 -- store system tick frequency to global
void FUN_710013b910()
{
    u64 uVar1 = nn::os::GetSystemTickFrequency();
    PTR_DAT_71052a3cd0 = uVar1;
}

// 71000c73d8 -- forward copy via FUN_710015ffc0
void FUN_71000c73d8(s64 param_1)
{
    FUN_710015ffc0(param_1 + 0x48, param_1 + 0x48);
}

// 7100177c90
u8 FUN_7100177c90(s64 param_1)
{
    return FUN_7100175220(*(u64*)(param_1 + 0x2a8));
}

// 7100177cb0 -- identical body to 7100177c90 (different callsite context)
u8 FUN_7100177cb0(s64 param_1)
{
    return FUN_7100175220(*(u64*)(param_1 + 0x2a8));
}

// 71001d90a0 -- calls sub, returns 0
u64 FUN_71001d90a0()
{
    FUN_71001d90c0();
    return 0;
}

// 710020f9f0 -- calls sub, returns 0
u64 FUN_710020f9f0()
{
    FUN_710020f2b0();
    return 0;
}

// 7100210e50 -- calls sub, returns 0
u64 FUN_7100210e50()
{
    FUN_71002105a0();
    return 0;
}

// 71001e0c60 -- error code XOR mask
u32 FUN_71001e0c60()
{
    u32 uVar1 = FUN_71001b34a0(&DAT_00006e48);
    return uVar1 ^ 0xffff8000;
}

// 71001f2d90
void FUN_71001f2d90(u64 param_1)
{
    FUN_71001f2ba0(param_1, &DAT_710449be3e, 0);
}

// 71001f2de0
void FUN_71001f2de0(u64 param_1)
{
    FUN_71001f2ba0(param_1, &DAT_710449be43, 0);
}

// 71001f2e90
void FUN_71001f2e90(u64 param_1)
{
    FUN_71001f2ba0(param_1, &DAT_710449be5b, 0);
}

// 7100228180 -- allocate 0x10 bytes, zero-initialize if successful
void FUN_7100228180()
{
    u64* puVar1 = (u64*)FUN_7100228110(0x10);
    if (puVar1 != nullptr) {
        puVar1[0] = 0;
        puVar1[1] = 0;
    }
}

// 71002549d0 -- bool: inner pointer is non-null
bool FUN_71002549d0(s64 param_1)
{
    s64 lVar1 = FUN_71001b4d20(*(u64*)(param_1 + 0x18));
    return lVar1 != 0;
}

// 71002b3670 -- return pointer if flag bit 0 set, else null
u8* FUN_71002b3670()
{
    u64 uVar2 = FUN_71002b64f0();
    if ((uVar2 & 1) == 0)
        return nullptr;
    return &DAT_000048d8;
}

// 71002b3690 -- return 8 if flag bit 0 set, else 0
u64 FUN_71002b3690()
{
    u64 uVar2 = FUN_71002b64f0();
    return (uVar2 & 1) ? (u64)8 : (u64)0;
}

// 71002b4e30 -- dereference pointer
u64 FUN_71002b4e30(u64* param_1)
{
    return *param_1;
}

// 71002b8120 -- forward to bb530 at +0x47a0
void FUN_71002b8120(s64 param_1)
{
    FUN_71002bb530(param_1 + 0x47a0);
}

// 71002b8140 -- forward to bb540 at +0x47a0
void FUN_71002b8140(s64 param_1)
{
    FUN_71002bb540(param_1 + 0x47a0);
}
