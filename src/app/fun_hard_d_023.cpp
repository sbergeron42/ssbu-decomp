#include "types.h"

// HARD-tier FUN_* functions — 0x7100 address range, batch hard-d-023
// Pool-d worker: 64B constructors, assert helpers, singleton dispatch

#define HIDDEN __attribute__((visibility("hidden")))

// ---- External data -------------------------------------------------------

extern u8 *PTR_DAT_71052a2d20 HIDDEN;
extern u8 *PTR_DAT_71052a3d08 HIDDEN;
extern u8 *PTR_DAT_71052a3d60 HIDDEN;
extern u8 *PTR_DAT_71052a3d70 HIDDEN;
extern u8 *PTR_DAT_71052a3dc0 HIDDEN;
extern u8 *PTR_DAT_71052a46d0 HIDDEN;

// ---- External functions --------------------------------------------------

extern void FUN_710007a160(void);
extern void FUN_71000b1cf0(s64 *);
extern void FUN_71000b2890(s64 *);
extern s64  FUN_71000b30b0(void);
extern void FUN_71000b3150(u64, u8);
extern void FUN_7100134c90(s64 *, u64, s32);
extern void FUN_7100153310(s64 *);
extern void FUN_71001549d0(s64);
extern void FUN_7100165330(void);

namespace pead {
    void IDisposer_ctor(s64 *);
}

namespace nn {
namespace os {
    void InitializeMutex(void *, bool, s32);
}
}

namespace nn {
namespace pia {
namespace common {
    void StepSequenceJob_ctor(s64 *);
    void CallContext_ctor(s64 *);
    void CriticalSection_Lock(void *);
    void CriticalSection_Unlock(void *);
}
}
}

// ---- Functions ---------------------------------------------------------------

// 0x7100044d00 — assert: panic if two pointer fields are non-null (64 bytes)
void FUN_7100044d00(s64 param_1)
{
    if (*(s64 *)(param_1 + 0xc8) != 0) {
        FUN_710007a160();
    }
    if (*(s64 *)(param_1 + 0xd0) != 0) {
        FUN_710007a160();
    }
}

// 0x71000bf2b0 — install shared vtable into two sub-objects at +0x628 and +0x5f8 (64 bytes)
void FUN_71000bf2b0(s64 param_1)
{
    u8 *vtable = PTR_DAT_71052a2d20 + 0x10;
    *(u8 **)(param_1 + 0x628) = vtable;
    FUN_71000b1cf0((s64 *)(param_1 + 0x630));
    *(u8 **)(param_1 + 0x5f8) = vtable;
    FUN_71000b1cf0((s64 *)(param_1 + 0x600));
}

// 0x7100118510 — call FUN_71000b2890 on four consecutive 0x20-stride sub-objects (64 bytes)
void FUN_7100118510(s64 param_1)
{
    FUN_71000b2890((s64 *)(param_1 + 0x20));
    FUN_71000b2890((s64 *)(param_1 + 0x40));
    FUN_71000b2890((s64 *)(param_1 + 0x60));
    FUN_71000b2890((s64 *)(param_1 + 0x80));
}

// 0x710013b930 — ctor: pead::IDisposer base + vtable + recursive mutex (64 bytes)
void FUN_710013b930(s64 *param_1)
{
    pead::IDisposer_ctor(param_1);
    *param_1 = (s64)(PTR_DAT_71052a3d08 + 0x10);
    nn::os::InitializeMutex(param_1 + 4, true, 0);
}

// 0x710013b970 — ctor variant: delegate to FUN_7100134c90 + vtable + recursive mutex (64 bytes)
void FUN_710013b970(s64 *param_1, u64 param_2)
{
    FUN_7100134c90(param_1, param_2, 1);
    *param_1 = (s64)(PTR_DAT_71052a3d08 + 0x10);
    nn::os::InitializeMutex(param_1 + 4, true, 0);
}

// 0x710013ce70 — ctor: nn::pia StepSequenceJob + zero fields + vtable + CallContext (64 bytes)
void FUN_710013ce70(s64 *param_1)
{
    nn::pia::common::StepSequenceJob_ctor(param_1);
    *(u32 *)(param_1 + 0xb) = 0;
    param_1[0xc] = 0;
    *param_1 = (s64)(PTR_DAT_71052a3d60 + 0x10);
    nn::pia::common::CallContext_ctor(param_1 + 0xd);
}

// 0x710013d130 — ctor: StepSequenceJob subclass + zero field[0xb] + vtable + CallContext at [0xc] (64 bytes)
void FUN_710013d130(s64 *param_1)
{
    nn::pia::common::StepSequenceJob_ctor(param_1);
    param_1[0xb] = 0;
    *param_1 = (s64)(PTR_DAT_71052a3d70 + 0x10);
    nn::pia::common::CallContext_ctor(param_1 + 0xc);
}

// 0x710013e400 — ctor: StepSequenceJob subclass variant + two zero fields + vtable + CallContext at [0xd] (64 bytes)
void FUN_710013e400(s64 *param_1)
{
    nn::pia::common::StepSequenceJob_ctor(param_1);
    *(u32 *)(param_1 + 0xb) = 0;
    param_1[0xc] = 0;
    *param_1 = (s64)(PTR_DAT_71052a3dc0 + 0x10);
    nn::pia::common::CallContext_ctor(param_1 + 0xd);
}

// 0x7100154800 — CriticalSection lock + FUN_71001549d0 worker + unlock (64 bytes)
void FUN_7100154800(s64 param_1)
{
    nn::pia::common::CriticalSection_Lock((void *)(param_1 + 0x340));
    FUN_71001549d0(param_1);
    nn::pia::common::CriticalSection_Unlock((void *)(param_1 + 0x340));
}

// 0x71001628a0 — assert: panic if either pointer at +0x18 or +0x20 is non-null (64 bytes)
void FUN_71001628a0(s64 param_1)
{
    if (*(s64 *)(param_1 + 0x18) != 0) {
        FUN_7100165330();
    }
    if (*(s64 *)(param_1 + 0x20) != 0) {
        FUN_7100165330();
    }
}

// 0x7100193330 — singleton dispatch: get context twice, pass param_2 to setter (64 bytes)
void FUN_7100193330(u64 param_1, u8 param_2)
{
    s64 ctx = FUN_71000b30b0();
    if (ctx != 0) {
        u64 obj = (u64)FUN_71000b30b0();
        FUN_71000b3150(obj, param_2);
    }
}

// 0x7100194810 — ctor: base init + vtable + byte 0xFD + zero u32 + byte 1 (64 bytes)
void FUN_7100194810(s64 *param_1)
{
    FUN_7100153310(param_1);
    *((u8 *)param_1 + 0x10c) = 0xfd;
    *param_1 = (s64)(PTR_DAT_71052a46d0 + 0x10);
    *(u32 *)((u8 *)param_1 + 0x110) = 0;
    *((u8 *)param_1 + 0x114) = 1;
}
