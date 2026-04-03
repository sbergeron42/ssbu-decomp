#include "types.h"

// MEDIUM-tier FUN_* functions â€” 0x7102 address range, batch e3-007
// Pool-e worker: abort wrappers, memcpy wrapper, throw_out_of_range cluster 0x710253de5câ€“0x710253fa8c

// ---- External declarations -----------------------------------------------

[[noreturn]] extern "C" void abort();
extern "C" void *memcpy(void *dst, const void *src, u64 n);

namespace std { namespace __1 {
    template<bool> struct __vector_base_common {
        [[noreturn]] static void __throw_out_of_range();
    };
}}

// ---- Abort wrappers -------------------------------------------------------

// FUN_71024a4c48 — defined in earlier batch file

// ---- Memcpy wrapper -------------------------------------------------------

// FUN_71024d702c — defined in earlier batch file

// ---- std::__throw_out_of_range wrappers (0x71024af2c8â€“0x710253fa8c) ------

// FUN_71024af2c8 — defined in earlier batch file

// 0x71024b27d8 (472 bytes)
void FUN_71024b27d8(void) {
    std::__1::__vector_base_common<true>::__throw_out_of_range();
}

// FUN_710253de5c — defined in earlier batch file

// FUN_710253df9c — defined in earlier batch file

// FUN_710253e09c — defined in earlier batch file

// FUN_710253e19c — defined in earlier batch file

// FUN_710253e29c — defined in earlier batch file

// FUN_710253e4ec — defined in earlier batch file

// FUN_710253e64c — defined in earlier batch file

// FUN_710253e74c — defined in earlier batch file

// FUN_710253e84c — defined in earlier batch file

// FUN_710253e94c — defined in earlier batch file

// FUN_710253ea4c — defined in earlier batch file

// FUN_710253eb4c — defined in earlier batch file

// FUN_710253ec4c — defined in earlier batch file

// FUN_710253ed4c — defined in earlier batch file

// FUN_710253ee4c — defined in earlier batch file

// FUN_710253ef8c — defined in earlier batch file

// FUN_710253f08c — defined in earlier batch file

// FUN_710253f18c — defined in earlier batch file

// FUN_710253f28c — defined in earlier batch file

// FUN_710253f38c — defined in earlier batch file

// FUN_710253f48c — defined in earlier batch file

// FUN_710253f58c — defined in earlier batch file

// FUN_710253f68c — defined in earlier batch file

// FUN_710253f78c — defined in earlier batch file

// FUN_710253f88c — defined in earlier batch file

// FUN_710253f98c — defined in earlier batch file

// FUN_710253fa8c — defined in earlier batch file
