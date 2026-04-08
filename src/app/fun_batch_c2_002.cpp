#include "types.h"

// Batch decompiled via Ghidra MCP -- pool-c, batch 002
// Range: 0x7102000000 -- 0x7102FFFFFF

// Forward declarations
[[noreturn]] extern "C" void abort();
extern u64 DAT_7104ad9bc0[];

// ── abort() / noreturn thunks ────────────────────────────────────────────────
// 0x7102528558
[[noreturn]] void FUN_7102528558()
{
  abort();
}

// 0x710274d788
[[noreturn]] void FUN_710274d788()
{
  abort();
}

// 0x7102a2aeb8
[[noreturn]] void FUN_7102a2aeb8()
{
  abort();
}

// 0x7102a662f8
[[noreturn]] void FUN_7102a662f8()
{
  abort();
}

// 0x7102c5ba04
[[noreturn]] void FUN_7102c5ba04()
{
  abort();
}

// 0x7102a667fc
[[noreturn]] void FUN_7102a667fc()
{
  abort();
}

// 0x7102752aac
[[noreturn]] void FUN_7102752aac()
{
  abort();
}

// 0x71028595b4
[[noreturn]] void FUN_71028595b4()
{
  abort();
}

// ── __throw_out_of_range thunks ───────────────────────────────────────────────

// 0x71024b39e8
[[noreturn]] void FUN_71024b39e8()
{
  abort();
}

// 0x71024b45f8
[[noreturn]] void FUN_71024b45f8()
{
  abort();
}

// 0x71024b4928
[[noreturn]] void FUN_71024b4928()
{
  abort();
}

// 0x710278fa0c
[[noreturn]] void FUN_710278fa0c()
{
  abort();
}

// 0x71028985fc
[[noreturn]] void FUN_71028985fc()
{
  abort();
}

// 0x71028987dc
[[noreturn]] void FUN_71028987dc()
{
  abort();
}

// 0x7102898b1c
[[noreturn]] void FUN_7102898b1c()
{
  abort();
}

// 0x7102898e2c
[[noreturn]] void FUN_7102898e2c()
{
  abort();
}

// 0x7102df750c
[[noreturn]] void FUN_7102df750c()
{
  abort();
}

// 0x710257e5ac
[[noreturn]] void FUN_710257e5ac()
{
  abort();
}

// 0x710257e97c
[[noreturn]] void FUN_710257e97c()
{
  abort();
}

// 0x710257ea5c
[[noreturn]] void FUN_710257ea5c()
{
  abort();
}

// 0x71025e97bc
[[noreturn]] void FUN_71025e97bc()
{
  abort();
}

// 0x7102692bcc
[[noreturn]] void FUN_7102692bcc()
{
  abort();
}

// 0x710272c28c
[[noreturn]] void FUN_710272c28c()
{
  abort();
}

// 0x710272c49c
[[noreturn]] void FUN_710272c49c()
{
  abort();
}

// 0x710272c6ac
[[noreturn]] void FUN_710272c6ac()
{
  abort();
}

// ── real functions ────────────────────────────────────────────────────────────

// 0x71025b2a60
// Table lookup: return one of 9 entries from DAT_7104ad9bc0[0..8], or sentinel

namespace std { namespace __1 {
template<bool> struct __vector_base_common {
    [[noreturn]] static void __throw_out_of_range();
};
}}

u64 FUN_71025b2a60(s32 param_1)
{
  if ((u32)(param_1 - 1) < 9) {
    return DAT_7104ad9bc0[(s64)(s32)((u32)(param_1 - 1))];
  }
  return 0x71ffff0000000000ULL;
}
