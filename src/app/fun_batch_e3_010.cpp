#include "types.h"

// MEDIUM-tier FUN_* functions â€” 0x7102 address range, batch e3-010
// Pool-e worker: abort wrappers + throw_out_of_range wrappers 0x7102740dbcâ€“0x71027ced7c

[[noreturn]] extern "C" void abort();

namespace std { namespace __1 {
    template<bool> struct __vector_base_common {
        [[noreturn]] static void __throw_out_of_range();
    };
}}

// ---- Abort wrappers -------------------------------------------------------

// FUN_7102752aac — defined in earlier batch file

// ---- throw_out_of_range wrappers -----------------------------------------

// FUN_710276febc — defined in earlier batch file
// 0x710276ffbc (496 bytes)
void FUN_710276ffbc(void) { std::__1::__vector_base_common<true>::__throw_out_of_range(); }
// FUN_71027702fc — defined in earlier batch file
// 0x710277049c (480 bytes)
void FUN_710277049c(void) { std::__1::__vector_base_common<true>::__throw_out_of_range(); }
// FUN_71027708ec — defined in earlier batch file
// 0x7102771bac (480 bytes)
void FUN_7102771bac(void) { std::__1::__vector_base_common<true>::__throw_out_of_range(); }
// FUN_710278fadc — defined in earlier batch file
// 0x710278fc64 (472 bytes)
void FUN_710278fc64(void) { std::__1::__vector_base_common<true>::__throw_out_of_range(); }
// 0x710279eb00 (416 bytes)
void FUN_710279eb00(void) { std::__1::__vector_base_common<true>::__throw_out_of_range(); }
// 0x71027a7860 (400 bytes)
void FUN_71027a7860(void) { std::__1::__vector_base_common<true>::__throw_out_of_range(); }
// FUN_71027b0b6c — defined in earlier batch file
// 0x71027b0cec (512 bytes)
void FUN_71027b0cec(void) { std::__1::__vector_base_common<true>::__throw_out_of_range(); }
// FUN_71027ced7c — defined in earlier batch file
