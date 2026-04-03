#include "types.h"

// MEDIUM-tier FUN_* functions — 0x7100-0x7101 range, batch d5-016
// Pool-d worker: auto-generated from Ghidra decompilation
// All 224-byte framed_vtable_call functions are __throw_out_of_range thunks,
// plus one sv_animcmd lua_bind wrapper.

[[noreturn]] extern "C" void abort();

struct lua_State;
namespace app {
    namespace sv_animcmd {
        void CHECK_FINISH_CAMERA_IF_NOT_HP_MODE(lua_State *);
    }
}

// ---- __throw_out_of_range thunks (224 bytes each) -------------------------

// 0x71005a57cc
[[noreturn]] void FUN_71005a57cc(void) { abort(); }
// 0x71005f2cbc
[[noreturn]] void FUN_71005f2cbc(void) { abort(); }
// 0x71005f359c
[[noreturn]] void FUN_71005f359c(void) { abort(); }
// 0x71007725bc
[[noreturn]] void FUN_71007725bc(void) { abort(); }
// 0x710077269c
[[noreturn]] void FUN_710077269c(void) { abort(); }
// 0x710086609c
[[noreturn]] void FUN_710086609c(void) { abort(); }
// 0x710093d5bc
[[noreturn]] void FUN_710093d5bc(void) { abort(); }
// 0x710096219c
[[noreturn]] void FUN_710096219c(void) { abort(); }
// 0x71009b740c
[[noreturn]] void FUN_71009b740c(void) { abort(); }
// 0x7100a114bc
[[noreturn]] void FUN_7100a114bc(void) { abort(); }
// 0x7100a280bc
[[noreturn]] void FUN_7100a280bc(void) { abort(); }
// 0x7100a3185c
[[noreturn]] void FUN_7100a3185c(void) { abort(); }
// 0x7100a540bc
[[noreturn]] void FUN_7100a540bc(void) { abort(); }
// 0x7100a7140c
[[noreturn]] void FUN_7100a7140c(void) { abort(); }
// 0x7100ae5c6c
[[noreturn]] void FUN_7100ae5c6c(void) { abort(); }
// 0x7100b19a8c
[[noreturn]] void FUN_7100b19a8c(void) { abort(); }
// 0x7100b1affc
[[noreturn]] void FUN_7100b1affc(void) { abort(); }
// 0x7100b8086c
[[noreturn]] void FUN_7100b8086c(void) { abort(); }
// 0x7100c4e2bc
[[noreturn]] void FUN_7100c4e2bc(void) { abort(); }
// 0x7100c63b4c
[[noreturn]] void FUN_7100c63b4c(void) { abort(); }
// 0x7100ca883c
[[noreturn]] void FUN_7100ca883c(void) { abort(); }
// 0x7100cbd8ec
[[noreturn]] void FUN_7100cbd8ec(void) { abort(); }
// 0x7100ccfe0c
[[noreturn]] void FUN_7100ccfe0c(void) { abort(); }
// 0x7100d2ebcc
[[noreturn]] void FUN_7100d2ebcc(void) { abort(); }
// 0x7100e677ac
[[noreturn]] void FUN_7100e677ac(void) { abort(); }
// 0x7100e92d9c
[[noreturn]] void FUN_7100e92d9c(void) { abort(); }
// 0x7100ea4afc
[[noreturn]] void FUN_7100ea4afc(void) { abort(); }
// 0x7100ea5c0c
[[noreturn]] void FUN_7100ea5c0c(void) { abort(); }
// 0x7100ebfdbc
[[noreturn]] void FUN_7100ebfdbc(void) { abort(); }
// 0x7100ec118c
[[noreturn]] void FUN_7100ec118c(void) { abort(); }
// 0x7100f1d42c
[[noreturn]] void FUN_7100f1d42c(void) { abort(); }
// 0x7100f1e56c
[[noreturn]] void FUN_7100f1e56c(void) { abort(); }
// 0x7100f8643c
[[noreturn]] void FUN_7100f8643c(void) { abort(); }
// 0x7100fd3f7c
[[noreturn]] void FUN_7100fd3f7c(void) { abort(); }
// 0x7100fe39bc
[[noreturn]] void FUN_7100fe39bc(void) { abort(); }
// 0x7100fe4bfc
[[noreturn]] void FUN_7100fe4bfc(void) { abort(); }
// 0x71010137dc
[[noreturn]] void FUN_71010137dc(void) { abort(); }
// 0x710104acdc
[[noreturn]] void FUN_710104acdc(void) { abort(); }
// 0x710117b67c
[[noreturn]] void FUN_710117b67c(void) { abort(); }
// 0x71011e396c
[[noreturn]] void FUN_71011e396c(void) { abort(); }
// 0x710124efbc
[[noreturn]] void FUN_710124efbc(void) { abort(); }
// 0x710127548c
[[noreturn]] void FUN_710127548c(void) { abort(); }
// 0x710129681c
[[noreturn]] void FUN_710129681c(void) { abort(); }
// 0x71012c94fc
[[noreturn]] void FUN_71012c94fc(void) { abort(); }
// 0x7101499e4c
[[noreturn]] void FUN_7101499e4c(void) { abort(); }
// 0x71014aa6ec
[[noreturn]] void FUN_71014aa6ec(void) { abort(); }
// 0x71014aa7cc
[[noreturn]] void FUN_71014aa7cc(void) { abort(); }

// ---- sv_animcmd lua_bind wrapper -----------------------------------------

// 0x7101fc11c0
u32 FUN_7101fc11c0(lua_State *param_1) { app::sv_animcmd::CHECK_FINISH_CAMERA_IF_NOT_HP_MODE(param_1); return 0; }
