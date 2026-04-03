#include "types.h"

// MEDIUM-tier FUN_* functions — 0x7102 address range, batch e3-009
// Pool-e worker: throw_out_of_range wrappers 0x710266cf8c–0x710272caa4

namespace std { namespace __1 {
    template<bool> struct __vector_base_common {
        [[noreturn]] static void __throw_out_of_range();
    };
}}

// FUN_710272c97c � defined in earlier batch file
// 0x710272caa4 (600 bytes)
void FUN_710272caa4(void) { std::__1::__vector_base_common<true>::__throw_out_of_range(); }
