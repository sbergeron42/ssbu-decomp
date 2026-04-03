#include "types.h"

// MEDIUM-tier FUN_* functions — 0x7100-0x7101 range, batch d5-018
// Pool-d worker: auto-generated from Ghidra decompilation
// 240-byte (0xF0) group part 1: 82 abort thunks + 2 simple wrappers

// ---- External declarations -----------------------------------------------

[[noreturn]] extern "C" void abort();
extern "C" void FUN_71004d8c70();
extern "C" void FUN_71017982b0(u64);

// ---- Simple wrappers --------------------------------------------------------

// 0x71006ea040 — call FUN_71004d8c70, clear byte at param_1+0x855 if param_2+0x40 nonzero
void FUN_71006ea040(s64 param_1, s64 param_2)
{
    FUN_71004d8c70();
    if (*(s8*)(param_2 + 0x40) != 0) {
        *(u8*)(param_1 + 0x855) = 0;
    }
}

// 0x7101beed30 — call FUN_71017982b0 with hash constant, return 0
u32 FUN_7101beed30(void)
{
    FUN_71017982b0(0x4bffff1be50309a6ULL);
    return 0;
}

// ---- abort() / __throw_out_of_range thunks (240 bytes each) ----------------

// 0x710055a48c
[[noreturn]] void FUN_710055a48c(void) { abort(); }
// 0x710055a57c
[[noreturn]] void FUN_710055a57c(void) { abort(); }
// 0x710055a66c
[[noreturn]] void FUN_710055a66c(void) { abort(); }
// 0x710055a75c
[[noreturn]] void FUN_710055a75c(void) { abort(); }
// 0x710055a84c
[[noreturn]] void FUN_710055a84c(void) { abort(); }
// 0x7100837d3c
[[noreturn]] void FUN_7100837d3c(void) { abort(); }
// 0x710083b03c
[[noreturn]] void FUN_710083b03c(void) { abort(); }
// 0x710086520c
[[noreturn]] void FUN_710086520c(void) { abort(); }
// 0x710086a4ec
[[noreturn]] void FUN_710086a4ec(void) { abort(); }
// 0x710089bdac
[[noreturn]] void FUN_710089bdac(void) { abort(); }
// 0x71008c272c
[[noreturn]] void FUN_71008c272c(void) { abort(); }
// 0x71008d040c
[[noreturn]] void FUN_71008d040c(void) { abort(); }
// 0x71008d1b7c
[[noreturn]] void FUN_71008d1b7c(void) { abort(); }
// 0x71008e3f1c
[[noreturn]] void FUN_71008e3f1c(void) { abort(); }
// 0x71008e5f3c
[[noreturn]] void FUN_71008e5f3c(void) { abort(); }
// 0x71008f690c
[[noreturn]] void FUN_71008f690c(void) { abort(); }
// 0x71008f85dc
[[noreturn]] void FUN_71008f85dc(void) { abort(); }
// 0x7100919c0c
[[noreturn]] void FUN_7100919c0c(void) { abort(); }
// 0x710091ca2c
[[noreturn]] void FUN_710091ca2c(void) { abort(); }
// 0x710095f9ac
[[noreturn]] void FUN_710095f9ac(void) { abort(); }
// 0x7100961edc
[[noreturn]] void FUN_7100961edc(void) { abort(); }
// 0x710097c1ec
[[noreturn]] void FUN_710097c1ec(void) { abort(); }
// 0x7100998bcc
[[noreturn]] void FUN_7100998bcc(void) { abort(); }
// 0x71009b355c
[[noreturn]] void FUN_71009b355c(void) { abort(); }
// 0x71009b714c
[[noreturn]] void FUN_71009b714c(void) { abort(); }
// 0x71009eb09c
[[noreturn]] void FUN_71009eb09c(void) { abort(); }
// 0x71009ed94c
[[noreturn]] void FUN_71009ed94c(void) { abort(); }
// 0x71009ee88c
[[noreturn]] void FUN_71009ee88c(void) { abort(); }
// 0x71009ef3ec
[[noreturn]] void FUN_71009ef3ec(void) { abort(); }
// 0x7100a5276c
[[noreturn]] void FUN_7100a5276c(void) { abort(); }
// 0x7100a548fc
[[noreturn]] void FUN_7100a548fc(void) { abort(); }
// 0x7100a6f9fc
[[noreturn]] void FUN_7100a6f9fc(void) { abort(); }
// 0x7100a71c7c
[[noreturn]] void FUN_7100a71c7c(void) { abort(); }
// 0x7100a8539c
[[noreturn]] void FUN_7100a8539c(void) { abort(); }
// 0x7100a90fcc
[[noreturn]] void FUN_7100a90fcc(void) { abort(); }
// 0x7100aac13c
[[noreturn]] void FUN_7100aac13c(void) { abort(); }
// 0x7100aadb9c
[[noreturn]] void FUN_7100aadb9c(void) { abort(); }
// 0x7100ac5dcc
[[noreturn]] void FUN_7100ac5dcc(void) { abort(); }
// 0x7100ac83bc
[[noreturn]] void FUN_7100ac83bc(void) { abort(); }
// 0x7100ae2e6c
[[noreturn]] void FUN_7100ae2e6c(void) { abort(); }
// 0x7100ae59ac
[[noreturn]] void FUN_7100ae59ac(void) { abort(); }
// 0x7100afea5c
[[noreturn]] void FUN_7100afea5c(void) { abort(); }
// 0x7100b0050c
[[noreturn]] void FUN_7100b0050c(void) { abort(); }
// 0x7100b17e3c
[[noreturn]] void FUN_7100b17e3c(void) { abort(); }
// 0x7100b1ad3c
[[noreturn]] void FUN_7100b1ad3c(void) { abort(); }
// 0x7100b3e09c
[[noreturn]] void FUN_7100b3e09c(void) { abort(); }
// 0x7100b41bac
[[noreturn]] void FUN_7100b41bac(void) { abort(); }
// 0x7100b6c15c
[[noreturn]] void FUN_7100b6c15c(void) { abort(); }
// 0x7100b6e6bc
[[noreturn]] void FUN_7100b6e6bc(void) { abort(); }
// 0x7100b82cdc
[[noreturn]] void FUN_7100b82cdc(void) { abort(); }
// 0x7100ba658c
[[noreturn]] void FUN_7100ba658c(void) { abort(); }
// 0x7100bb139c
[[noreturn]] void FUN_7100bb139c(void) { abort(); }
// 0x7100bc793c
[[noreturn]] void FUN_7100bc793c(void) { abort(); }
// 0x7100bd849c
[[noreturn]] void FUN_7100bd849c(void) { abort(); }
// 0x7100bee1bc
[[noreturn]] void FUN_7100bee1bc(void) { abort(); }
// 0x7100bf0a4c
[[noreturn]] void FUN_7100bf0a4c(void) { abort(); }
// 0x7100c13b0c
[[noreturn]] void FUN_7100c13b0c(void) { abort(); }
// 0x7100c16a0c
[[noreturn]] void FUN_7100c16a0c(void) { abort(); }
// 0x7100c321cc
[[noreturn]] void FUN_7100c321cc(void) { abort(); }
// 0x7100c3491c
[[noreturn]] void FUN_7100c3491c(void) { abort(); }
// 0x7100c4c39c
[[noreturn]] void FUN_7100c4c39c(void) { abort(); }
// 0x7100c4e39c
[[noreturn]] void FUN_7100c4e39c(void) { abort(); }
// 0x7100c61a9c
[[noreturn]] void FUN_7100c61a9c(void) { abort(); }
// 0x7100c6388c
[[noreturn]] void FUN_7100c6388c(void) { abort(); }
// 0x7100c7adec
[[noreturn]] void FUN_7100c7adec(void) { abort(); }
// 0x7100c7ddcc
[[noreturn]] void FUN_7100c7ddcc(void) { abort(); }
// 0x7100c96ebc
[[noreturn]] void FUN_7100c96ebc(void) { abort(); }
// 0x7100c9848c
[[noreturn]] void FUN_7100c9848c(void) { abort(); }
// 0x7100ca67fc
[[noreturn]] void FUN_7100ca67fc(void) { abort(); }
// 0x7100ca857c
[[noreturn]] void FUN_7100ca857c(void) { abort(); }
// 0x7100cbe9cc
[[noreturn]] void FUN_7100cbe9cc(void) { abort(); }
// 0x7100ccf41c
[[noreturn]] void FUN_7100ccf41c(void) { abort(); }
// 0x7100cd0a9c
[[noreturn]] void FUN_7100cd0a9c(void) { abort(); }
// 0x7100cdf30c
[[noreturn]] void FUN_7100cdf30c(void) { abort(); }
// 0x7100ce08dc
[[noreturn]] void FUN_7100ce08dc(void) { abort(); }
// 0x7100cf567c
[[noreturn]] void FUN_7100cf567c(void) { abort(); }
// 0x7100d1b99c
[[noreturn]] void FUN_7100d1b99c(void) { abort(); }
// 0x7100d1d4bc
[[noreturn]] void FUN_7100d1d4bc(void) { abort(); }
// 0x7100d2f31c
[[noreturn]] void FUN_7100d2f31c(void) { abort(); }
// 0x7100d302ac
[[noreturn]] void FUN_7100d302ac(void) { abort(); }
// 0x7100d5fdac
[[noreturn]] void FUN_7100d5fdac(void) { abort(); }
// 0x7100d7b6bc
[[noreturn]] void FUN_7100d7b6bc(void) { abort(); }
