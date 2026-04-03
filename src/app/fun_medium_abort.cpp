#include "types.h"

// FUN_* MEDIUM tier -- abort wrapper functions (pool-e)
//
// The real abort() lives at 0x71039c20a0 (symbol: FUN_71039c20a0).
// Using the FUN_ name ensures gen_linker_script.py gives it the right address.
//
// Three patterns:
//   Group 1: [[noreturn]] void F() { FUN_71039c20a0(); }    → 3 insns (stp+mov+bl abort)
//   Group 2: void F() { FUN_710356bb30(); }                 → 3 insns + 4 zero bytes
//   Group 3: see fun_medium_abort3.cpp

extern "C" [[noreturn]] void FUN_71039c20a0();  // abort
extern "C" [[noreturn]] void FUN_710356bb30();  // panic (defined in fun_batch_e2_012.cpp)

namespace app::lua_bind {

// ── Group 1: direct abort wrappers ───────────────────────────────────────────

// 71013a05bc
[[noreturn]] void FUN_71013a05bc() { FUN_71039c20a0(); }
// 71013a2a60
[[noreturn]] void FUN_71013a2a60() { FUN_71039c20a0(); }
// 71013cd860
[[noreturn]] void FUN_71013cd860() { FUN_71039c20a0(); }
// 71013d9a10
[[noreturn]] void FUN_71013d9a10() { FUN_71039c20a0(); }
// 71013e41f0
[[noreturn]] void FUN_71013e41f0() { FUN_71039c20a0(); }
// 71013e9594
[[noreturn]] void FUN_71013e9594() { FUN_71039c20a0(); }
// 71013ea584
[[noreturn]] void FUN_71013ea584() { FUN_71039c20a0(); }
// 7101482d2c
[[noreturn]] void FUN_7101482d2c() { FUN_71039c20a0(); }
// 7101485e70
[[noreturn]] void FUN_7101485e70() { FUN_71039c20a0(); }
// 710148a400
[[noreturn]] void FUN_710148a400() { FUN_71039c20a0(); }
// 710148ae6c
[[noreturn]] void FUN_710148ae6c() { FUN_71039c20a0(); }
// 710148d440
[[noreturn]] void FUN_710148d440() { FUN_71039c20a0(); }
// 710148e9ac
[[noreturn]] void FUN_710148e9ac() { FUN_71039c20a0(); }
// 710148ff20
[[noreturn]] void FUN_710148ff20() { FUN_71039c20a0(); }
// 710156d194
[[noreturn]] void FUN_710156d194() { FUN_71039c20a0(); }
// 71016ed7b0
[[noreturn]] void FUN_71016ed7b0() { FUN_71039c20a0(); }
// 710179a9fc
[[noreturn]] void FUN_710179a9fc() { FUN_71039c20a0(); }
// 710180a024
[[noreturn]] void FUN_710180a024() { FUN_71039c20a0(); }
// 7101810834
[[noreturn]] void FUN_7101810834() { FUN_71039c20a0(); }
// 710182f32c
[[noreturn]] void FUN_710182f32c() { FUN_71039c20a0(); }
// 71018516f4
[[noreturn]] void FUN_71018516f4() { FUN_71039c20a0(); }
// 71018f702c
[[noreturn]] void FUN_71018f702c() { FUN_71039c20a0(); }
// 7101914464
[[noreturn]] void FUN_7101914464() { FUN_71039c20a0(); }
// 7101961e80
[[noreturn]] void FUN_7101961e80() { FUN_71039c20a0(); }
// 7101a88420
[[noreturn]] void FUN_7101a88420() { FUN_71039c20a0(); }
// 7101aa840c
[[noreturn]] void FUN_7101aa840c() { FUN_71039c20a0(); }
// 7101ad9e84
[[noreturn]] void FUN_7101ad9e84() { FUN_71039c20a0(); }
// 7101b338cc
[[noreturn]] void FUN_7101b338cc() { FUN_71039c20a0(); }
// 7101b79d20
[[noreturn]] void FUN_7101b79d20() { FUN_71039c20a0(); }
// 7101b7fe5c
[[noreturn]] void FUN_7101b7fe5c() { FUN_71039c20a0(); }
// 7101b9af1c
[[noreturn]] void FUN_7101b9af1c() { FUN_71039c20a0(); }
// 7101c31f04
[[noreturn]] void FUN_7101c31f04() { FUN_71039c20a0(); }
// 7101c7692c
[[noreturn]] void FUN_7101c7692c() { FUN_71039c20a0(); }
// 7101cad46c
[[noreturn]] void FUN_7101cad46c() { FUN_71039c20a0(); }
// 7101cdacfc
[[noreturn]] void FUN_7101cdacfc() { FUN_71039c20a0(); }
// 7101d11690
[[noreturn]] void FUN_7101d11690() { FUN_71039c20a0(); }
// 7101d2585c
[[noreturn]] void FUN_7101d2585c() { FUN_71039c20a0(); }
// 7101d2595c
[[noreturn]] void FUN_7101d2595c() { FUN_71039c20a0(); }
// 7101d6ae10
[[noreturn]] void FUN_7101d6ae10() { FUN_71039c20a0(); }
// 7101d7f02c
[[noreturn]] void FUN_7101d7f02c() { FUN_71039c20a0(); }
// 7101ecdeb4
[[noreturn]] void FUN_7101ecdeb4() { FUN_71039c20a0(); }
// 7101efbde4
[[noreturn]] void FUN_7101efbde4() { FUN_71039c20a0(); }
// 7101f3842c
[[noreturn]] void FUN_7101f3842c() { FUN_71039c20a0(); }
// 7101fa4afc
[[noreturn]] void FUN_7101fa4afc() { FUN_71039c20a0(); }
// 71031534d0
[[noreturn]] void FUN_71031534d0() { FUN_71039c20a0(); }
// 71031535c0
[[noreturn]] void FUN_71031535c0() { FUN_71039c20a0(); }
// 71031591e0
[[noreturn]] void FUN_71031591e0() { FUN_71039c20a0(); }
// 71031597bc
[[noreturn]] void FUN_71031597bc() { FUN_71039c20a0(); }
// 7103169e0c
[[noreturn]] void FUN_7103169e0c() { FUN_71039c20a0(); }
// 7103169f30
[[noreturn]] void FUN_7103169f30() { FUN_71039c20a0(); }
// 710316a038
[[noreturn]] void FUN_710316a038() { FUN_71039c20a0(); }
// 710316a12c
[[noreturn]] void FUN_710316a12c() { FUN_71039c20a0(); }
// 710316a5dc
[[noreturn]] void FUN_710316a5dc() { FUN_71039c20a0(); }
// 7103176f58
[[noreturn]] void FUN_7103176f58() { FUN_71039c20a0(); }
// 710317704c
[[noreturn]] void FUN_710317704c() { FUN_71039c20a0(); }
// 7103177240
[[noreturn]] void FUN_7103177240() { FUN_71039c20a0(); }
// 7103177420
[[noreturn]] void FUN_7103177420() { FUN_71039c20a0(); }
// 710317750c
[[noreturn]] void FUN_710317750c() { FUN_71039c20a0(); }
// 7103177600
[[noreturn]] void FUN_7103177600() { FUN_71039c20a0(); }
// 7103177954
[[noreturn]] void FUN_7103177954() { FUN_71039c20a0(); }
// 710317c0d4
[[noreturn]] void FUN_710317c0d4() { FUN_71039c20a0(); }
// 71032f142c
[[noreturn]] void FUN_71032f142c() { FUN_71039c20a0(); }

// ── Group 2: call FUN_710356bb30 (defined above as [[noreturn]]) ─────────────
// Since FUN_710356bb30 is [[noreturn]] and defined in this TU, the compiler
// generates bl+nothing (3 insns = 12 bytes); linker zero-pads to CSV size 16.

// 710356bb20
void FUN_710356bb20() { FUN_710356bb30(); }
// 71038aba20
void FUN_71038aba20() { FUN_710356bb30(); }
// 71038aba30
void FUN_71038aba30() { FUN_710356bb30(); }
// 71038aba40
void FUN_71038aba40() { FUN_710356bb30(); }
// 71038aba50
void FUN_71038aba50() { FUN_710356bb30(); }
// 71038aba60
void FUN_71038aba60() { FUN_710356bb30(); }
// 71038aba70
void FUN_71038aba70() { FUN_710356bb30(); }
// 71038aba80
void FUN_71038aba80() { FUN_710356bb30(); }
// 71038aba90
void FUN_71038aba90() { FUN_710356bb30(); }
// 71038abaa0
void FUN_71038abaa0() { FUN_710356bb30(); }
// 71038abab0
void FUN_71038abab0() { FUN_710356bb30(); }
// 71038abac0
void FUN_71038abac0() { FUN_710356bb30(); }
// 71038abad0
void FUN_71038abad0() { FUN_710356bb30(); }
// 71038abae0
void FUN_71038abae0() { FUN_710356bb30(); }
// 71038abaf0
void FUN_71038abaf0() { FUN_710356bb30(); }
// 71038abb00
void FUN_71038abb00() { FUN_710356bb30(); }
// 71038abb10
void FUN_71038abb10() { FUN_710356bb30(); }
// 71038abb20
void FUN_71038abb20() { FUN_710356bb30(); }
// 71038abb30
void FUN_71038abb30() { FUN_710356bb30(); }
// 71038abb40
void FUN_71038abb40() { FUN_710356bb30(); }
// 71038344a0
void FUN_71038344a0() { FUN_710356bb30(); }
// 71038d70e0
void FUN_71038d70e0() { FUN_710356bb30(); }
// 71038e0640
void FUN_71038e0640() { FUN_710356bb30(); }
// 71038e0690
void FUN_71038e0690() { FUN_710356bb30(); }
// 71038cef60
void FUN_71038cef60() { FUN_710356bb30(); }
// 710388e230
void FUN_710388e230() { FUN_710356bb30(); }
// 7103834b10
void FUN_7103834b10() { FUN_710356bb30(); }

} // namespace app::lua_bind
