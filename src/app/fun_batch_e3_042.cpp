#include "types.h"

// MEDIUM-tier FUN_* functions — 0x7103 address range, batch e3-042
// Category: framed wrappers returning u64 (zero-extended u32 result)
// Pattern: stp/mov-x29 + arg-adjust + bl + and-x0-0xffffffff + ldp/ret
// Subcategories:
//   A) nn::nfp API wrappers — add x0,x0,#0x84 then call nn::nfp::<func>
//   B) pass-through with u32→u64 extension
//   C) param_2+0xc reindex wrappers
//
// Targets declared as u64 so the compiler emits and x0,x0,#0xffffffff
// (zero-extend via 64-bit AND) rather than mov w0,w0 (32-bit ORR).

// nn::nfp targets (from fun_region_039.cpp, placed at correct addresses by linker)
extern "C" u64 FUN_71039c7260(void*);    // nn::nfp::StartDetection
extern "C" u64 FUN_71039c7270(void*);    // nn::nfp::StopDetection
extern "C" u64 FUN_71039c7280(void*, u32); // nn::nfp::Mount
extern "C" u64 FUN_71039c7290(void*);    // nn::nfp::Unmount
extern "C" u64 FUN_71039c72e0(void*);    // nn::nfp::Flush
extern "C" u64 FUN_71039c72f0(void*);    // nn::nfp::Restore
extern "C" u64 FUN_71039c7300(void*, void*); // nn::nfp::CreateApplicationArea

// other targets
extern "C" u64 FUN_7103300dd0(void);
extern "C" u64 FUN_71037223f0(u64);
extern "C" u64 FUN_7103721ea0(u64, u32);

// ---- nn::nfp wrappers (add x0,x0,#0x84) ----

// 0x71037162f0 — nn::nfp::StartDetection wrapper
u64 FUN_71037162f0(u64 param_1) {
    return FUN_71039c7260((void*)(param_1 + 0x84)) & 0xffffffffULL;
}

// 0x7103716310 — nn::nfp::StopDetection wrapper
u64 FUN_7103716310(u64 param_1) {
    return FUN_71039c7270((void*)(param_1 + 0x84)) & 0xffffffffULL;
}

// 0x7103716330 — nn::nfp::Mount wrapper (second arg = 0)
u64 FUN_7103716330(u64 param_1) {
    return FUN_71039c7280((void*)(param_1 + 0x84), 0) & 0xffffffffULL;
}

// 0x7103716350 — nn::nfp::Unmount wrapper
u64 FUN_7103716350(u64 param_1) {
    return FUN_71039c7290((void*)(param_1 + 0x84)) & 0xffffffffULL;
}

// 0x7103716b20 — nn::nfp::Flush wrapper
u64 FUN_7103716b20(u64 param_1) {
    return FUN_71039c72e0((void*)(param_1 + 0x84)) & 0xffffffffULL;
}

// 0x7103716b40 — nn::nfp::Restore wrapper
u64 FUN_7103716b40(u64 param_1) {
    return FUN_71039c72f0((void*)(param_1 + 0x84)) & 0xffffffffULL;
}

// 0x7103716b60 — nn::nfp::CreateApplicationArea wrapper (x1 = param_2 passed through)
u64 FUN_7103716b60(u64 param_1, u64 param_2) {
    return FUN_71039c7300((void*)(param_1 + 0x84), (void*)param_2) & 0xffffffffULL;
}

// ---- pass-through returning u64 ----

// 0x71033011cc — bl FUN_7103300dd0, return zero-extended u32
u64 FUN_71033011cc(void) {
    return FUN_7103300dd0() & 0xffffffffULL;
}

// ---- param_2+0xc reindex wrappers ----

// 0x7103720de0 — add x0,x1,#0xc; bl FUN_71037223f0
u64 FUN_7103720de0(u64 param_1, u64 param_2) {
    return FUN_71037223f0(param_2 + 0xc) & 0xffffffffULL;
}

// 0x7103720e00 — add x0,x1,#0xc; ldrb w1,[x1,#0x158]; bl FUN_7103721ea0
u64 FUN_7103720e00(u64 param_1, u64 param_2) {
    return FUN_7103721ea0(param_2 + 0xc, *(u8*)(param_2 + 0x158)) & 0xffffffffULL;
}
