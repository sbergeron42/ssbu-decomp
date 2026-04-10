// fun_medium_016.cpp — Matched Curl timer function
// Cleaned: removed 8 unmatched Ghidra paste functions, kept 1 verified (M)

#include "types.h"

struct CurlTimeval { u64 tv_sec; u64 tv_usec; };
extern "C" CurlTimeval curlx_tvnow();

// 0x7100015110 — reset timer fields using curlx_tvnow (quality=M)
void FUN_7100015110(s64 param_1)
{
    *(u32*)(param_1 + 0xb58) = 0;
    *(CurlTimeval*)(param_1 + 0xa58) = curlx_tvnow();
    *(u64*)(param_1 + 0xa98) = 0;
    *(u32*)(param_1 + 0xaa0) = 0;
    *(u64*)(param_1 + 0xab0) = 0;
    *(u32*)(param_1 + 0xab8) = 0;
    *(u32*)(param_1 + 0xa08) = *(u32*)(param_1 + 0xa08) & 0x90;
}
