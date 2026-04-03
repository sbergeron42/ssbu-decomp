#include "types.h"

// MEDIUM-tier FUN_* functions — 0x7102 address range, batch e3-002
// Pool-e worker: table lookup, abort wrappers, throw_out_of_range wrappers

// ---- External declarations -----------------------------------------------

[[noreturn]] extern "C" void abort();

namespace std { namespace __1 {
    template<bool> struct __vector_base_common {
        [[noreturn]] static void __throw_out_of_range();
    };
}}

// Table base for FUN_71025b2a60 (9 u64 entries at 0x7104ad9bc0)
extern u64 DAT_7104ad9bc0;

// ---- Table lookup (leaf, no frame) ---------------------------------------

// 0x71025b2a60 — return table[param_1-1] if param_1 in [1..9], else 0x71ffff0000000000
// Disasm (leaf): sub w8,w0,#1; cmp w8,#8; b.hi; adrp+add(table); ldr x0,[x9,w8,SXTW#3]; ret
//                out-of-range: mov+movk(0x71ffff0000000000); ret
u64 FUN_71025b2a60(s32 param_1)
{
    u32 idx = (u32)(param_1 - 1);
    if (idx < 9u) {
        return ((u64 *)&DAT_7104ad9bc0)[(s32)idx];
    }
    return 0x71ffff0000000000ULL;
}

// ---- Abort wrappers (various sizes) ----------------------------------------
// All call abort() directly; sizes vary due to alignment/gap to next function.

// 0x7102853fd4 (76 bytes)
void FUN_7102853fd4(void) { abort(); }

// 0x71027694c4 (108 bytes)
void FUN_71027694c4(void) { abort(); }

// 0x7102350de8 (144 bytes)
void FUN_7102350de8(void) { abort(); }

// 0x71023510e8 (144 bytes)
void FUN_71023510e8(void) { abort(); }

// 0x7102351178 (144 bytes)
void FUN_7102351178(void) { abort(); }

// 0x7102351208 (144 bytes)
void FUN_7102351208(void) { abort(); }

// ---- std::__throw_out_of_range wrappers ------------------------------------
// All call std::__1::__vector_base_common<true>::__throw_out_of_range().
// Various sizes (96–132 bytes) due to different alignment/gap to next symbol.

// 0x710253dc7c (96 bytes)
void FUN_710253dc7c(void) {
    std::__1::__vector_base_common<true>::__throw_out_of_range();
}

// 0x710253dd6c (96 bytes)
void FUN_710253dd6c(void) {
    std::__1::__vector_base_common<true>::__throw_out_of_range();
}

// 0x71025e989c (100 bytes)
void FUN_71025e989c(void) {
    std::__1::__vector_base_common<true>::__throw_out_of_range();
}

// 0x71028787bc (112 bytes)
void FUN_71028787bc(void) {
    std::__1::__vector_base_common<true>::__throw_out_of_range();
}

// 0x7102931ae0 — NOTE: this is actually a vtable dispatch (not throw), moved to later batch
// Skipped here.

// 0x7102a4109c (112 bytes)
void FUN_7102a4109c(void) {
    std::__1::__vector_base_common<true>::__throw_out_of_range();
}

// 0x7102d9de1c (112 bytes)
void FUN_7102d9de1c(void) {
    std::__1::__vector_base_common<true>::__throw_out_of_range();
}

// 0x7102d9ebcc (112 bytes)
void FUN_7102d9ebcc(void) {
    std::__1::__vector_base_common<true>::__throw_out_of_range();
}

// 0x7102dc281c (112 bytes)
void FUN_7102dc281c(void) {
    std::__1::__vector_base_common<true>::__throw_out_of_range();
}

// 0x7102d51448 (116 bytes)
void FUN_7102d51448(void) {
    std::__1::__vector_base_common<true>::__throw_out_of_range();
}

// 0x7102879834 (120 bytes)
void FUN_7102879834(void) {
    std::__1::__vector_base_common<true>::__throw_out_of_range();
}

// 0x710257e68c (128 bytes)
void FUN_710257e68c(void) {
    std::__1::__vector_base_common<true>::__throw_out_of_range();
}

// 0x710287882c (128 bytes)
void FUN_710287882c(void) {
    std::__1::__vector_base_common<true>::__throw_out_of_range();
}

// 0x7102eb69cc (128 bytes)
void FUN_7102eb69cc(void) {
    std::__1::__vector_base_common<true>::__throw_out_of_range();
}

// 0x7102588cfc (132 bytes)
void FUN_7102588cfc(void) {
    std::__1::__vector_base_common<true>::__throw_out_of_range();
}

// 0x7102d9ec3c (132 bytes)
void FUN_7102d9ec3c(void) {
    std::__1::__vector_base_common<true>::__throw_out_of_range();
}

// 0x710253e3ac (144 bytes)
void FUN_710253e3ac(void) {
    std::__1::__vector_base_common<true>::__throw_out_of_range();
}
