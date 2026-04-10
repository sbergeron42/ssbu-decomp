// fun_medium_013.cpp — Matched functions from nn::pia networking range
// Cleaned: removed 17 unmatched Ghidra paste functions, kept 2 verified (M)

#include "types.h"

extern "C" s32 FUN_71001354c0(u32);

namespace nn { namespace pia { namespace common { namespace CallContext {
    void SignalCancel(s32*);
    void Reset(s32*);
}}}}

// 0x71000b4000 — conditional SignalCancel, then Reset, zero field (quality=M)
void FUN_71000b4000(s64 param_1)
{
    s32* ctx = (s32*)(param_1 + 0x58);
    if (*ctx == 1)
        nn::pia::common::CallContext::SignalCancel(ctx);
    nn::pia::common::CallContext::Reset(ctx);
    *(u64*)(param_1 + 0x88) = 0;
}

// 0x71000bf770 — FUN_71001354c0 result, floor to min 1 (quality=M)
s32 FUN_71000bf770(s64 param_1)
{
    s32 result = FUN_71001354c0(*(u32*)(param_1 + 0x5f0));
    if (result < 2)
        result = 1;
    return result;
}
