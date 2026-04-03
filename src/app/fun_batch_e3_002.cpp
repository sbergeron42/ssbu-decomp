#include "types.h"

// MEDIUM-tier FUN_* functions â€” 0x7102 address range, batch e3-002
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

// FUN_71025b2a60 — defined in earlier batch file

// ---- Abort wrappers (various sizes) ----------------------------------------
// All call abort() directly; sizes vary due to alignment/gap to next function.

// FUN_7102853fd4 — defined in earlier batch file

// FUN_71027694c4 — defined in earlier batch file

// FUN_7102350de8 — defined in earlier batch file

// FUN_71023510e8 — defined in earlier batch file

// FUN_7102351178 — defined in earlier batch file

// FUN_7102351208 — defined in earlier batch file

// ---- std::__throw_out_of_range wrappers ------------------------------------
// All call std::__1::__vector_base_common<true>::__throw_out_of_range().
// Various sizes (96â€“132 bytes) due to different alignment/gap to next symbol.

// FUN_710253dc7c — defined in earlier batch file

// FUN_710253dd6c — defined in earlier batch file

// FUN_71025e989c — defined in earlier batch file

// FUN_71028787bc — defined in earlier batch file

// 0x7102931ae0 â€” NOTE: this is actually a vtable dispatch (not throw), moved to later batch
// Skipped here.

// FUN_7102a4109c — defined in earlier batch file

// FUN_7102d9de1c — defined in earlier batch file

// FUN_7102d9ebcc — defined in earlier batch file

// FUN_7102dc281c — defined in earlier batch file

// FUN_7102d51448 — defined in earlier batch file

// FUN_7102879834 — defined in earlier batch file

// FUN_710257e68c — defined in earlier batch file

// FUN_710287882c — defined in earlier batch file

// FUN_7102eb69cc — defined in earlier batch file

// FUN_7102588cfc — defined in earlier batch file

// FUN_7102d9ec3c — defined in earlier batch file

// FUN_710253e3ac — defined in earlier batch file
