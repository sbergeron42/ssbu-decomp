#include "types.h"

// MEDIUM-tier FUN_* functions — 0x7102 address range, batch e3-010
// Pool-e worker: abort wrappers + throw_out_of_range wrappers 0x7102740dbc–0x71027ced7c

[[noreturn]] extern "C" void abort();

namespace std { namespace __1 {
    template<bool> struct __vector_base_common {
        [[noreturn]] static void __throw_out_of_range();
    };
}}

// ---- Abort wrappers -------------------------------------------------------

// 0x7102752aac (84 bytes)
void FUN_7102752aac(void) { abort(); }

// ---- throw_out_of_range wrappers -----------------------------------------

// 0x7102740dbc (320 bytes)
void FUN_7102740dbc(void) { std::__1::__vector_base_common<true>::__throw_out_of_range(); }
// 0x710276ec8c (304 bytes)
void FUN_710276ec8c(void) { std::__1::__vector_base_common<true>::__throw_out_of_range(); }
// 0x710276f75c (392 bytes)
void FUN_710276f75c(void) { std::__1::__vector_base_common<true>::__throw_out_of_range(); }
// 0x710276fc4c (352 bytes)
void FUN_710276fc4c(void) { std::__1::__vector_base_common<true>::__throw_out_of_range(); }
// 0x710276fdac (272 bytes)
void FUN_710276fdac(void) { std::__1::__vector_base_common<true>::__throw_out_of_range(); }
// 0x710276febc (256 bytes)
void FUN_710276febc(void) { std::__1::__vector_base_common<true>::__throw_out_of_range(); }
// 0x710276ffbc (496 bytes)
void FUN_710276ffbc(void) { std::__1::__vector_base_common<true>::__throw_out_of_range(); }
// 0x71027701ac (336 bytes)
void FUN_71027701ac(void) { std::__1::__vector_base_common<true>::__throw_out_of_range(); }
// 0x71027702fc (416 bytes)
void FUN_71027702fc(void) { std::__1::__vector_base_common<true>::__throw_out_of_range(); }
// 0x710277049c (480 bytes)
void FUN_710277049c(void) { std::__1::__vector_base_common<true>::__throw_out_of_range(); }
// 0x710277067c (368 bytes)
void FUN_710277067c(void) { std::__1::__vector_base_common<true>::__throw_out_of_range(); }
// 0x71027707ec (256 bytes)
void FUN_71027707ec(void) { std::__1::__vector_base_common<true>::__throw_out_of_range(); }
// 0x71027708ec (240 bytes)
void FUN_71027708ec(void) { std::__1::__vector_base_common<true>::__throw_out_of_range(); }
// 0x7102771bac (480 bytes)
void FUN_7102771bac(void) { std::__1::__vector_base_common<true>::__throw_out_of_range(); }
// 0x710278fa0c (208 bytes)
void FUN_710278fa0c(void) { std::__1::__vector_base_common<true>::__throw_out_of_range(); }
// 0x710278fadc (392 bytes)
void FUN_710278fadc(void) { std::__1::__vector_base_common<true>::__throw_out_of_range(); }
// 0x710278fc64 (472 bytes)
void FUN_710278fc64(void) { std::__1::__vector_base_common<true>::__throw_out_of_range(); }
// 0x710279eb00 (416 bytes)
void FUN_710279eb00(void) { std::__1::__vector_base_common<true>::__throw_out_of_range(); }
// 0x71027a7860 (400 bytes)
void FUN_71027a7860(void) { std::__1::__vector_base_common<true>::__throw_out_of_range(); }
// 0x71027b08fc (240 bytes)
void FUN_71027b08fc(void) { std::__1::__vector_base_common<true>::__throw_out_of_range(); }
// 0x71027b09ec (384 bytes)
void FUN_71027b09ec(void) { std::__1::__vector_base_common<true>::__throw_out_of_range(); }
// 0x71027b0b6c (384 bytes)
void FUN_71027b0b6c(void) { std::__1::__vector_base_common<true>::__throw_out_of_range(); }
// 0x71027b0cec (512 bytes)
void FUN_71027b0cec(void) { std::__1::__vector_base_common<true>::__throw_out_of_range(); }
// 0x71027b0eec (240 bytes)
void FUN_71027b0eec(void) { std::__1::__vector_base_common<true>::__throw_out_of_range(); }
// 0x71027b0fdc (400 bytes)
void FUN_71027b0fdc(void) { std::__1::__vector_base_common<true>::__throw_out_of_range(); }
// 0x71027b116c (224 bytes)
void FUN_71027b116c(void) { std::__1::__vector_base_common<true>::__throw_out_of_range(); }
// 0x71027cdf0c (320 bytes)
void FUN_71027cdf0c(void) { std::__1::__vector_base_common<true>::__throw_out_of_range(); }
// 0x71027ce04c (232 bytes)
void FUN_71027ce04c(void) { std::__1::__vector_base_common<true>::__throw_out_of_range(); }
// 0x71027ce51c (272 bytes)
void FUN_71027ce51c(void) { std::__1::__vector_base_common<true>::__throw_out_of_range(); }
// 0x71027ce62c (272 bytes)
void FUN_71027ce62c(void) { std::__1::__vector_base_common<true>::__throw_out_of_range(); }
// 0x71027ceb5c (304 bytes)
void FUN_71027ceb5c(void) { std::__1::__vector_base_common<true>::__throw_out_of_range(); }
// 0x71027cec8c (240 bytes)
void FUN_71027cec8c(void) { std::__1::__vector_base_common<true>::__throw_out_of_range(); }
// 0x71027ced7c (208 bytes)
void FUN_71027ced7c(void) { std::__1::__vector_base_common<true>::__throw_out_of_range(); }
