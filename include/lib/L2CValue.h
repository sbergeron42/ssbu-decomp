#pragma once

#include "types.h"

namespace lib {

// L2CValue — tagged union used throughout the Lua/ACMD binding layer.
// sizeof(L2CValue) = 0x10
//
// Type tags [derived: L2CValue constructors at 0x7103733fd0-0x71037340c0]:
//   0 = void/nil     (no value)
//   1 = bool          (+0x08: u32, stores val & 1)
//   2 = integer       (+0x08: s64 or u64)
//   3 = float         (+0x08: f32)
//   4 = pointer       (+0x08: void*)
//   5 = table         (+0x08: L2CTable*)
//   6 = string        (+0x08: basic_string* — refcounted, see copy ctor)
//   7 = hash/enum     (treated as integer in load_from_l2c_table patterns)
//   8 = inner string  (copy ctor allocates 0x18 bytes, refcounted)
struct L2CValue {
    u32 type;       // +0x00 [derived: all constructors store type tag here]
    u32 pad_04;     // +0x04
    union {
        u64 raw;        // raw access
        s64 int_val;    // type==2: signed integer
        u64 uint_val;   // type==2: unsigned integer
        f32 float_val;  // type==3: float
        void* ptr_val;  // type==4: pointer, type==5: table*, type==6/8: string*
        u32 bool_val;   // type==1: boolean (val & 1)
    };              // +0x08
};
static_assert(sizeof(L2CValue) == 0x10, "L2CValue size mismatch");

} // namespace lib
