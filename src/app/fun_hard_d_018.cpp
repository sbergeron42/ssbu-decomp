#include "types.h"

// HARD-tier FUN_* functions — 0x7100/0x7103 address range, batch hard-d-018
// Pool-d worker: OS timing wrapper, bitfield extract, jemalloc arena helper (48B each)

#define HIDDEN __attribute__((visibility("hidden")))

// ---- External data -------------------------------------------------------

extern u8 DAT_7106d49678 HIDDEN;

// ---- External functions --------------------------------------------------

// nn::os SDK
typedef u64 Tick;
typedef s64 TimeSpan;

namespace nn {
namespace os {
    TimeSpan ConvertToTimeSpan(Tick);
    void     TimedWaitEvent(void *, TimeSpan);
}
}

// jemalloc arena helpers
extern u64  FUN_7103930530(u64, u8 *, u64, u64, u32);
extern u64  FUN_71039305c0(u64, u8 *, u64, u32);
extern u32  FUN_7103930610(u64);
extern u8   FUN_7103930630(u64);

// ---- Functions ---------------------------------------------------------------

// 0x710013bb30 — ConvertToTimeSpan + TimedWaitEvent (48 bytes)
void FUN_710013bb30(s64 param_1, Tick param_2)
{
    TimeSpan TVar1 = nn::os::ConvertToTimeSpan(param_2);
    nn::os::TimedWaitEvent((void *)(param_1 + 0x20), TVar1);
}

// 0x710392af50 — extract 4-bit field from upper word (bits 32-35) (48 bytes)
u64 FUN_710392af50(u64 param_1)
{
    return (param_1 >> 0x20) & 0xf;
}

// 0x7103930300 — jemalloc arena setup: chain 4 helpers into param_4/param_5 outputs (48 bytes)
void FUN_7103930300(u64 param_1, u64 param_2, u64 param_3, u32 *param_4, u8 *param_5)
{
    u64 uVar3 = FUN_7103930530(param_1, &DAT_7106d49678, param_2, param_3, 1);
    uVar3 = FUN_71039305c0(param_1, &DAT_7106d49678, uVar3, 1);
    *param_4 = FUN_7103930610(uVar3);
    *param_5 = FUN_7103930630(uVar3) & 1;
}
