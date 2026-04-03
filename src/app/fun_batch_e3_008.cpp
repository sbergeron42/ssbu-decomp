#include "types.h"

// MEDIUM-tier FUN_* functions â€” 0x7102 address range, batch e3-008
// Pool-e worker: throw_out_of_range wrappers 0x710253fbecâ€“0x710259333c

namespace std { namespace __1 {
    template<bool> struct __vector_base_common {
        [[noreturn]] static void __throw_out_of_range();
    };
}}

// FUN_710255774c — defined in earlier batch file
// 0x710255788c (528 bytes)
void FUN_710255788c(void) { std::__1::__vector_base_common<true>::__throw_out_of_range(); }
// FUN_710255a174 — defined in earlier batch file
// 0x710255a31c (496 bytes)
void FUN_710255a31c(void) { std::__1::__vector_base_common<true>::__throw_out_of_range(); }
// FUN_710259333c — defined in earlier batch file
