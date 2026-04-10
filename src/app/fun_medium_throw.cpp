#include "types.h"
namespace std { namespace __1 {
template<bool> struct __vector_base_common {
    [[noreturn]] static void __throw_out_of_range();
};
}}

// FUN_* MEDIUM tier -- __throw_out_of_range wrappers (pool-e)
// These call FUN_71039c0d80 = std::__1::__vector_base_common<true>::__throw_out_of_range
//
// Patterns:
//   Group A: stp+mov+bl       (3 insns) -- pass x0 unchanged
//   Group B: stp+mov+add+bl   (4 insns) -- add offset to x0 before call
//   Group C: stp+mov+mov+bl   (4 insns) -- pass x8 or x9 as 'this'

extern "C" [[noreturn]] void FUN_71039c0d80(void*);

namespace app::lua_bind {

// ── Group A: x0 passed unchanged ────────────────────────────────────────────

// 7101b1c5fc
[[noreturn]] void FUN_7101b1c5fc(long param_1) { FUN_71039c0d80((void*)param_1); }
// 7101b3bc40
[[noreturn]] void FUN_7101b3bc40(long param_1) { FUN_71039c0d80((void*)param_1); }
// 7101c43a5c
[[noreturn]] void FUN_7101c43a5c(long param_1) { FUN_71039c0d80((void*)param_1); }
// 7101eacc50
[[noreturn]] void FUN_7101eacc50(long param_1) { FUN_71039c0d80((void*)param_1); }
// 7102e2a9fc
[[noreturn]] void FUN_7102e2a9fc(long param_1) { FUN_71039c0d80((void*)param_1); }
// 71032cb7ec
[[noreturn]] void FUN_71032cb7ec(long param_1) { FUN_71039c0d80((void*)param_1); }

// ── Group B: add offset to x0 ────────────────────────────────────────────

// 71019c2150
[[noreturn]] void FUN_71019c2150(long param_1) { FUN_71039c0d80((void*)((char*)param_1 + 0x128)); }
// 71019cd300
[[noreturn]] void FUN_71019cd300(long param_1) { FUN_71039c0d80((void*)((char*)param_1 + 0x128)); }
// 7101a4e400
[[noreturn]] void FUN_7101a4e400(long param_1) { FUN_71039c0d80((void*)((char*)param_1 + 0x3b0)); }

} // namespace app::lua_bind

