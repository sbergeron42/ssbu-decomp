#include "types.h"

// FUN_* MEDIUM tier -- abort wrapper functions (pool-e)
//
// The real abort() lives at 0x71039c20a0 (symbol: abortWrapper_71039c20a0).
// Using the FUN_ name ensures gen_linker_script.py gives it the right address.
//
// Three patterns:
//   Group 1: [[noreturn]] void F() { abortWrapper_71039c20a0(); }    → 3 insns (stp+mov+bl abort)
//   Group 2: void F() { abort_710356bb30(); }                 → 3 insns + 4 zero bytes
//   Group 3: see fun_medium_abort3.cpp

extern "C" [[noreturn]] void abortWrapper_71039c20a0();  // abort
extern "C" [[noreturn]] void abort_710356bb30();  // panic (defined in fun_batch_e2_012.cpp)

namespace app::lua_bind {

// ── Group 1: direct abort wrappers ───────────────────────────────────────────

// 71013a05bc
[[noreturn]] void FUN_71013a05bc() { abortWrapper_71039c20a0(); }
// 71013a2a60
[[noreturn]] void FUN_71013a2a60() { abortWrapper_71039c20a0(); }
// 71013cd860
[[noreturn]] void FUN_71013cd860() { abortWrapper_71039c20a0(); }
// 71013d9a10
[[noreturn]] void FUN_71013d9a10() { abortWrapper_71039c20a0(); }
// 71013e41f0
[[noreturn]] void FUN_71013e41f0() { abortWrapper_71039c20a0(); }
// 71013e9594
[[noreturn]] void FUN_71013e9594() { abortWrapper_71039c20a0(); }
// 71013ea584
[[noreturn]] void FUN_71013ea584() { abortWrapper_71039c20a0(); }
// 7101482d2c
[[noreturn]] void FUN_7101482d2c() { abortWrapper_71039c20a0(); }
// 7101485e70
[[noreturn]] void FUN_7101485e70() { abortWrapper_71039c20a0(); }
// 710148a400
[[noreturn]] void FUN_710148a400() { abortWrapper_71039c20a0(); }
// 710148ae6c
[[noreturn]] void FUN_710148ae6c() { abortWrapper_71039c20a0(); }
// 710148d440
[[noreturn]] void FUN_710148d440() { abortWrapper_71039c20a0(); }
// 710148e9ac
[[noreturn]] void FUN_710148e9ac() { abortWrapper_71039c20a0(); }
// 710148ff20
[[noreturn]] void FUN_710148ff20() { abortWrapper_71039c20a0(); }
// 710156d194
[[noreturn]] void FUN_710156d194() { abortWrapper_71039c20a0(); }
// 71016ed7b0
[[noreturn]] void FUN_71016ed7b0() { abortWrapper_71039c20a0(); }
// 710179a9fc
[[noreturn]] void FUN_710179a9fc() { abortWrapper_71039c20a0(); }
// 710180a024
[[noreturn]] void FUN_710180a024() { abortWrapper_71039c20a0(); }
// 7101810834
[[noreturn]] void FUN_7101810834() { abortWrapper_71039c20a0(); }
// 710182f32c
[[noreturn]] void FUN_710182f32c() { abortWrapper_71039c20a0(); }
// 71018516f4
[[noreturn]] void FUN_71018516f4() { abortWrapper_71039c20a0(); }
// 71018f702c
[[noreturn]] void FUN_71018f702c() { abortWrapper_71039c20a0(); }
// 7101914464
[[noreturn]] void FUN_7101914464() { abortWrapper_71039c20a0(); }
// 7101961e80
[[noreturn]] void FUN_7101961e80() { abortWrapper_71039c20a0(); }
// 7101a88420
[[noreturn]] void FUN_7101a88420() { abortWrapper_71039c20a0(); }
// 7101aa840c
[[noreturn]] void FUN_7101aa840c() { abortWrapper_71039c20a0(); }
// 7101ad9e84
[[noreturn]] void FUN_7101ad9e84() { abortWrapper_71039c20a0(); }
// 7101b338cc
[[noreturn]] void FUN_7101b338cc() { abortWrapper_71039c20a0(); }
// 7101b79d20
[[noreturn]] void FUN_7101b79d20() { abortWrapper_71039c20a0(); }
// 7101b7fe5c
[[noreturn]] void FUN_7101b7fe5c() { abortWrapper_71039c20a0(); }
// 7101b9af1c
[[noreturn]] void FUN_7101b9af1c() { abortWrapper_71039c20a0(); }
// 7101c31f04
[[noreturn]] void FUN_7101c31f04() { abortWrapper_71039c20a0(); }
// 7101c7692c
[[noreturn]] void FUN_7101c7692c() { abortWrapper_71039c20a0(); }
// 7101cad46c
[[noreturn]] void FUN_7101cad46c() { abortWrapper_71039c20a0(); }
// 7101cdacfc
[[noreturn]] void FUN_7101cdacfc() { abortWrapper_71039c20a0(); }
// 7101d11690
[[noreturn]] void FUN_7101d11690() { abortWrapper_71039c20a0(); }
// 7101d2585c
[[noreturn]] void FUN_7101d2585c() { abortWrapper_71039c20a0(); }
// 7101d2595c
[[noreturn]] void FUN_7101d2595c() { abortWrapper_71039c20a0(); }
// 7101d6ae10
[[noreturn]] void FUN_7101d6ae10() { abortWrapper_71039c20a0(); }
// 7101d7f02c
[[noreturn]] void FUN_7101d7f02c() { abortWrapper_71039c20a0(); }
// 7101ecdeb4
[[noreturn]] void FUN_7101ecdeb4() { abortWrapper_71039c20a0(); }
// 7101efbde4
[[noreturn]] void FUN_7101efbde4() { abortWrapper_71039c20a0(); }
// 7101f3842c
[[noreturn]] void FUN_7101f3842c() { abortWrapper_71039c20a0(); }
// 7101fa4afc
[[noreturn]] void FUN_7101fa4afc() { abortWrapper_71039c20a0(); }
// 71031534d0
[[noreturn]] void FUN_71031534d0() { abortWrapper_71039c20a0(); }
// 71031535c0
[[noreturn]] void FUN_71031535c0() { abortWrapper_71039c20a0(); }
// 71031591e0
[[noreturn]] void FUN_71031591e0() { abortWrapper_71039c20a0(); }
// 71031597bc
[[noreturn]] void FUN_71031597bc() { abortWrapper_71039c20a0(); }
// 7103169e0c
[[noreturn]] void FUN_7103169e0c() { abortWrapper_71039c20a0(); }
// 7103169f30
[[noreturn]] void FUN_7103169f30() { abortWrapper_71039c20a0(); }
// 710316a038
[[noreturn]] void FUN_710316a038() { abortWrapper_71039c20a0(); }
// 710316a12c
[[noreturn]] void FUN_710316a12c() { abortWrapper_71039c20a0(); }
// 710316a5dc
[[noreturn]] void FUN_710316a5dc() { abortWrapper_71039c20a0(); }
// 7103176f58
[[noreturn]] void FUN_7103176f58() { abortWrapper_71039c20a0(); }
// 710317704c
[[noreturn]] void FUN_710317704c() { abortWrapper_71039c20a0(); }
// 7103177240
[[noreturn]] void FUN_7103177240() { abortWrapper_71039c20a0(); }
// 7103177420
[[noreturn]] void FUN_7103177420() { abortWrapper_71039c20a0(); }
// 710317750c
[[noreturn]] void FUN_710317750c() { abortWrapper_71039c20a0(); }
// 7103177600
[[noreturn]] void FUN_7103177600() { abortWrapper_71039c20a0(); }
// 7103177954
[[noreturn]] void FUN_7103177954() { abortWrapper_71039c20a0(); }
// 710317c0d4
[[noreturn]] void FUN_710317c0d4() { abortWrapper_71039c20a0(); }
// 71032f142c
[[noreturn]] void FUN_71032f142c() { abortWrapper_71039c20a0(); }

// ── Group 2: call abort_710356bb30 (defined above as [[noreturn]]) ─────────────
// Since abort_710356bb30 is [[noreturn]] and defined in this TU, the compiler
// generates bl+nothing (3 insns = 12 bytes); linker zero-pads to CSV size 16.

// 710356bb20
void FUN_710356bb20() { abort_710356bb30(); }
// 71038aba20
void FUN_71038aba20() { abort_710356bb30(); }
// 71038aba30
void FUN_71038aba30() { abort_710356bb30(); }
// 71038aba40
void FUN_71038aba40() { abort_710356bb30(); }
// 71038aba50
void FUN_71038aba50() { abort_710356bb30(); }
// 71038aba60
void FUN_71038aba60() { abort_710356bb30(); }
// 71038aba70
void FUN_71038aba70() { abort_710356bb30(); }
// 71038aba80
void FUN_71038aba80() { abort_710356bb30(); }
// 71038aba90
void FUN_71038aba90() { abort_710356bb30(); }
// 71038abaa0
void FUN_71038abaa0() { abort_710356bb30(); }
// 71038abab0
void FUN_71038abab0() { abort_710356bb30(); }
// 71038abac0
void FUN_71038abac0() { abort_710356bb30(); }
// 71038abad0
void FUN_71038abad0() { abort_710356bb30(); }
// 71038abae0
void FUN_71038abae0() { abort_710356bb30(); }
// 71038abaf0
void FUN_71038abaf0() { abort_710356bb30(); }
// 71038abb00
void FUN_71038abb00() { abort_710356bb30(); }
// 71038abb10
void FUN_71038abb10() { abort_710356bb30(); }
// 71038abb20
void FUN_71038abb20() { abort_710356bb30(); }
// 71038abb30
void FUN_71038abb30() { abort_710356bb30(); }
// 71038abb40
void FUN_71038abb40() { abort_710356bb30(); }
// 71038344a0
void FUN_71038344a0() { abort_710356bb30(); }
// 71038d70e0
void FUN_71038d70e0() { abort_710356bb30(); }
// 71038e0640
void FUN_71038e0640() { abort_710356bb30(); }
// 71038e0690
void FUN_71038e0690() { abort_710356bb30(); }
// 71038cef60
void FUN_71038cef60() { abort_710356bb30(); }
// 710388e230
void FUN_710388e230() { abort_710356bb30(); }
// 7103834b10
void FUN_7103834b10() { abort_710356bb30(); }

} // namespace app::lua_bind
