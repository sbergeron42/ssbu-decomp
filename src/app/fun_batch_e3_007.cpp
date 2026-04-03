#include "types.h"

// MEDIUM-tier FUN_* functions — 0x7102 address range, batch e3-007
// Pool-e worker: abort wrappers, memcpy wrapper, throw_out_of_range cluster 0x710253de5c–0x710253fa8c

// ---- External declarations -----------------------------------------------

[[noreturn]] extern "C" void abort();
extern "C" void *memcpy(void *dst, const void *src, u64 n);

namespace std { namespace __1 {
    template<bool> struct __vector_base_common {
        [[noreturn]] static void __throw_out_of_range();
    };
}}

// ---- Abort wrappers -------------------------------------------------------

// 0x71024a4c48 (408 bytes)
void FUN_71024a4c48(void) { abort(); }

// ---- Memcpy wrapper -------------------------------------------------------

// 0x71024d702c (388 bytes) — memcpy(param_1, param_2, 0xa0)
// Disasm: stp x29,x30; mov w2,#0xa0; bl memcpy@0x71039bfb30; ldp; ret
void FUN_71024d702c(void *param_1, void *param_2)
{
    memcpy(param_1, param_2, 0xa0);
}

// ---- std::__throw_out_of_range wrappers (0x71024af2c8–0x710253fa8c) ------

// 0x71024af2c8 (472 bytes)
void FUN_71024af2c8(void) {
    std::__1::__vector_base_common<true>::__throw_out_of_range();
}

// 0x71024b27d8 (472 bytes)
void FUN_71024b27d8(void) {
    std::__1::__vector_base_common<true>::__throw_out_of_range();
}

// 0x710253de5c (320 bytes)
void FUN_710253de5c(void) {
    std::__1::__vector_base_common<true>::__throw_out_of_range();
}

// 0x710253df9c (256 bytes)
void FUN_710253df9c(void) {
    std::__1::__vector_base_common<true>::__throw_out_of_range();
}

// 0x710253e09c (256 bytes)
void FUN_710253e09c(void) {
    std::__1::__vector_base_common<true>::__throw_out_of_range();
}

// 0x710253e19c (256 bytes)
void FUN_710253e19c(void) {
    std::__1::__vector_base_common<true>::__throw_out_of_range();
}

// 0x710253e29c (272 bytes)
void FUN_710253e29c(void) {
    std::__1::__vector_base_common<true>::__throw_out_of_range();
}

// 0x710253e4ec (352 bytes)
void FUN_710253e4ec(void) {
    std::__1::__vector_base_common<true>::__throw_out_of_range();
}

// 0x710253e64c (256 bytes)
void FUN_710253e64c(void) {
    std::__1::__vector_base_common<true>::__throw_out_of_range();
}

// 0x710253e74c (256 bytes)
void FUN_710253e74c(void) {
    std::__1::__vector_base_common<true>::__throw_out_of_range();
}

// 0x710253e84c (256 bytes)
void FUN_710253e84c(void) {
    std::__1::__vector_base_common<true>::__throw_out_of_range();
}

// 0x710253e94c (256 bytes)
void FUN_710253e94c(void) {
    std::__1::__vector_base_common<true>::__throw_out_of_range();
}

// 0x710253ea4c (256 bytes)
void FUN_710253ea4c(void) {
    std::__1::__vector_base_common<true>::__throw_out_of_range();
}

// 0x710253eb4c (256 bytes)
void FUN_710253eb4c(void) {
    std::__1::__vector_base_common<true>::__throw_out_of_range();
}

// 0x710253ec4c (256 bytes)
void FUN_710253ec4c(void) {
    std::__1::__vector_base_common<true>::__throw_out_of_range();
}

// 0x710253ed4c (256 bytes)
void FUN_710253ed4c(void) {
    std::__1::__vector_base_common<true>::__throw_out_of_range();
}

// 0x710253ee4c (320 bytes)
void FUN_710253ee4c(void) {
    std::__1::__vector_base_common<true>::__throw_out_of_range();
}

// 0x710253ef8c (256 bytes)
void FUN_710253ef8c(void) {
    std::__1::__vector_base_common<true>::__throw_out_of_range();
}

// 0x710253f08c (256 bytes)
void FUN_710253f08c(void) {
    std::__1::__vector_base_common<true>::__throw_out_of_range();
}

// 0x710253f18c (256 bytes)
void FUN_710253f18c(void) {
    std::__1::__vector_base_common<true>::__throw_out_of_range();
}

// 0x710253f28c (256 bytes)
void FUN_710253f28c(void) {
    std::__1::__vector_base_common<true>::__throw_out_of_range();
}

// 0x710253f38c (256 bytes)
void FUN_710253f38c(void) {
    std::__1::__vector_base_common<true>::__throw_out_of_range();
}

// 0x710253f48c (256 bytes)
void FUN_710253f48c(void) {
    std::__1::__vector_base_common<true>::__throw_out_of_range();
}

// 0x710253f58c (256 bytes)
void FUN_710253f58c(void) {
    std::__1::__vector_base_common<true>::__throw_out_of_range();
}

// 0x710253f68c (256 bytes)
void FUN_710253f68c(void) {
    std::__1::__vector_base_common<true>::__throw_out_of_range();
}

// 0x710253f78c (256 bytes)
void FUN_710253f78c(void) {
    std::__1::__vector_base_common<true>::__throw_out_of_range();
}

// 0x710253f88c (256 bytes)
void FUN_710253f88c(void) {
    std::__1::__vector_base_common<true>::__throw_out_of_range();
}

// 0x710253f98c (256 bytes)
void FUN_710253f98c(void) {
    std::__1::__vector_base_common<true>::__throw_out_of_range();
}

// 0x710253fa8c (352 bytes)
void FUN_710253fa8c(void) {
    std::__1::__vector_base_common<true>::__throw_out_of_range();
}
