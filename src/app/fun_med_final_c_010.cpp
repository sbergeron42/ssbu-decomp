// fun_med_final_c_010.cpp — Matched functions from 0x71023–0x71023d range
// Cleaned: removed 19 unmatched Ghidra paste functions, kept 11 verified (M)
// Mostly __throw_out_of_range thunks + simple call wrappers

#include <stdint.h>
namespace std { namespace __1 {
template<bool> struct __vector_base_common {
    [[noreturn]] static void __throw_out_of_range();
};
}}
typedef uint8_t  u8;
typedef uint32_t u32;
typedef uint64_t u64;
typedef int32_t  s32;
typedef int64_t  s64;

extern "C" {
void FUN_7101af0740(void);
void FUN_71017cda90(void);
}

// 0x7102302984 — call wrapper, returns 0 (quality=M)
u32 FUN_7102302984(void)
{
    FUN_7101af0740();
    return 0;
}

// ── __throw_out_of_range thunks (all quality=M) ─────────────────────────────

// 0x7102338ffc
[[noreturn]] void FUN_7102338ffc(void) { std::__1::__vector_base_common<true>::__throw_out_of_range(); }
// 0x7102343934
[[noreturn]] void FUN_7102343934(void) { std::__1::__vector_base_common<true>::__throw_out_of_range(); }
// 0x7102350de8
[[noreturn]] void FUN_7102350de8(void) { std::__1::__vector_base_common<true>::__throw_out_of_range(); }
// 0x71023510e8
[[noreturn]] void FUN_71023510e8(void) { std::__1::__vector_base_common<true>::__throw_out_of_range(); }
// 0x7102351178
[[noreturn]] void FUN_7102351178(void) { std::__1::__vector_base_common<true>::__throw_out_of_range(); }
// 0x7102351208
[[noreturn]] void FUN_7102351208(void) { std::__1::__vector_base_common<true>::__throw_out_of_range(); }
// 0x7102351298
[[noreturn]] void FUN_7102351298(void) { std::__1::__vector_base_common<true>::__throw_out_of_range(); }
// 0x710239e04c
[[noreturn]] void FUN_710239e04c(void) { std::__1::__vector_base_common<true>::__throw_out_of_range(); }
// 0x71023c8f6c
[[noreturn]] void FUN_71023c8f6c(void) { std::__1::__vector_base_common<true>::__throw_out_of_range(); }

// 0x71023d2ac0 — call wrapper, returns 1 (quality=M)
u64 FUN_71023d2ac0(void)
{
    FUN_71017cda90();
    return 1;
}
