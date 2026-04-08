#include "types.h"

extern "C" void* memcpy(void*, const void*, u64);

// Batch decompiled via Ghidra MCP -- pool-c, batch 015
// Range: 0x7102000000 -- 0x7102FFFFFF

// Forward declarations
[[noreturn]] extern "C" void abort();

// ── abort() / noreturn thunks ─────────────────────────────────────────────────

// 0x71024a4c48
[[noreturn]] void FUN_71024a4c48()
{
  abort();
}

// 0x7102f25f4c
[[noreturn]] void FUN_7102f25f4c()
{
  abort();
}

namespace std { namespace __1 {
template<bool> struct __vector_base_common {
    [[noreturn]] static void __throw_out_of_range();
};
}}


// ── __throw_out_of_range thunks ───────────────────────────────────────────────

// 0x710276f75c
[[noreturn]] void FUN_710276f75c()
{
  std::__1::__vector_base_common<true>::__throw_out_of_range();
}

// 0x710278fadc
[[noreturn]] void FUN_710278fadc()
{
  std::__1::__vector_base_common<true>::__throw_out_of_range();
}

// 0x71026f50ec
[[noreturn]] void FUN_71026f50ec()
{
  std::__1::__vector_base_common<true>::__throw_out_of_range();
}

// 0x71027b0fdc
[[noreturn]] void FUN_71027b0fdc()
{
  std::__1::__vector_base_common<true>::__throw_out_of_range();
}

// 0x71028b8aac
[[noreturn]] void FUN_71028b8aac()
{
  std::__1::__vector_base_common<true>::__throw_out_of_range();
}

// 0x7102b113dc
[[noreturn]] void FUN_7102b113dc()
{
  std::__1::__vector_base_common<true>::__throw_out_of_range();
}

// 0x7102baf2ec
[[noreturn]] void FUN_7102baf2ec()
{
  std::__1::__vector_base_common<true>::__throw_out_of_range();
}

// 0x7102bd657c
[[noreturn]] void FUN_7102bd657c()
{
  std::__1::__vector_base_common<true>::__throw_out_of_range();
}

// 0x7102ce1acc
[[noreturn]] void FUN_7102ce1acc()
{
  std::__1::__vector_base_common<true>::__throw_out_of_range();
}

// 0x7102d9e17c
[[noreturn]] void FUN_7102d9e17c()
{
  std::__1::__vector_base_common<true>::__throw_out_of_range();
}

// 0x7102d9e83c
[[noreturn]] void FUN_7102d9e83c()
{
  std::__1::__vector_base_common<true>::__throw_out_of_range();
}

// 0x7102e9fd5c
[[noreturn]] void FUN_7102e9fd5c()
{
  std::__1::__vector_base_common<true>::__throw_out_of_range();
}

// 0x7102eb684c
[[noreturn]] void FUN_7102eb684c()
{
  std::__1::__vector_base_common<true>::__throw_out_of_range();
}

// 0x7102f7b0ac
[[noreturn]] void FUN_7102f7b0ac()
{
  std::__1::__vector_base_common<true>::__throw_out_of_range();
}

// 0x7102f954cc
[[noreturn]] void FUN_7102f954cc()
{
  std::__1::__vector_base_common<true>::__throw_out_of_range();
}

// 0x7102f9508c
[[noreturn]] void FUN_7102f9508c()
{
  std::__1::__vector_base_common<true>::__throw_out_of_range();
}

// ── real functions ────────────────────────────────────────────────────────────

// 0x71024d702c
// Copies 0xa0 bytes from param_2 to param_1
void FUN_71024d702c(void *param_1, void *param_2)
{
  memcpy(param_1, param_2, 0xa0);
  return;
}
