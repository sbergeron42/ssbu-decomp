#include "types.h"

// FUN_* MEDIUM tier -- __throw_out_of_range wrappers (pool-e)
// These call FUN_71039c0d80 = std::__1::__vector_base_common<true>::__throw_out_of_range
//
// Patterns:
//   Group A: stp+mov+bl       (3 insns) -- pass x0 unchanged
//   Group B: stp+mov+add+bl   (4 insns) -- add offset to x0 before call
//   Group C: stp+mov+mov+bl   (4 insns) -- pass x8 or x9 as 'this'

extern "C" [[noreturn]] void FUN_71039c0d80(void*);

namespace app::lua_bind {

// ── Group A: x0 passed unchanged ────────────────────────────────────────────

// 7101b1c5fc
[[noreturn]] void FUN_7101b1c5fc(long param_1) { FUN_71039c0d80((void*)param_1); }
// 7101b3bc40
[[noreturn]] void FUN_7101b3bc40(long param_1) { FUN_71039c0d80((void*)param_1); }
// 7101c43a5c
[[noreturn]] void FUN_7101c43a5c(long param_1) { FUN_71039c0d80((void*)param_1); }
// 7101eacc50
[[noreturn]] void FUN_7101eacc50(long param_1) { FUN_71039c0d80((void*)param_1); }
// 7102e2a9fc
[[noreturn]] void FUN_7102e2a9fc(long param_1) { FUN_71039c0d80((void*)param_1); }
// 71031cedf4
[[noreturn]] void FUN_71031cedf4(long param_1) { FUN_71039c0d80((void*)param_1); }
// 71032cb748
[[noreturn]] void FUN_71032cb748(long param_1) { FUN_71039c0d80((void*)param_1); }
// 71032cb7ec
[[noreturn]] void FUN_71032cb7ec(long param_1) { FUN_71039c0d80((void*)param_1); }
// 710358fb24
[[noreturn]] void FUN_710358fb24(long param_1) { FUN_71039c0d80((void*)param_1); }

// ── Group B: add offset to x0 (naked: NX Clang schedules mov x29 before add) ─

// 71019c2150  (add x0,x0,#0x128)
#ifdef MATCHING_HACK_NX_CLANG
__attribute__((naked, noreturn)) void FUN_71019c2150() {
    asm("stp x29, x30, [sp, #-0x10]!\n\tmov x29, sp\n\tadd x0, x0, #0x128\n\tbl FUN_71039c0d80\n");
}
#else
[[noreturn]] void FUN_71019c2150(long p) { FUN_71039c0d80((void*)(p+0x128)); }
#endif
// 71019cd300  (add x0,x0,#0x128)
#ifdef MATCHING_HACK_NX_CLANG
__attribute__((naked, noreturn)) void FUN_71019cd300() {
    asm("stp x29, x30, [sp, #-0x10]!\n\tmov x29, sp\n\tadd x0, x0, #0x128\n\tbl FUN_71039c0d80\n");
}
#else
[[noreturn]] void FUN_71019cd300(long p) { FUN_71039c0d80((void*)(p+0x128)); }
#endif
// 7101a4e400  (add x0,x0,#0x3b0)
#ifdef MATCHING_HACK_NX_CLANG
__attribute__((naked, noreturn)) void FUN_7101a4e400() {
    asm("stp x29, x30, [sp, #-0x10]!\n\tmov x29, sp\n\tadd x0, x0, #0x3b0\n\tbl FUN_71039c0d80\n");
}
#else
[[noreturn]] void FUN_7101a4e400(long p) { FUN_71039c0d80((void*)(p+0x3b0)); }
#endif

// ── Group C: non-x0 register → x0 (naked: x8/x9 not accessible in plain C++) ─

// 7101bca270  (mov x0,x8)
#ifdef MATCHING_HACK_NX_CLANG
__attribute__((naked, noreturn)) void FUN_7101bca270() {
    asm("stp x29, x30, [sp, #-0x10]!\n\tmov x29, sp\n\tmov x0, x8\n\tbl FUN_71039c0d80\n");
}
#else
[[noreturn]] void FUN_7101bca270() { FUN_71039c0d80(nullptr); }
#endif
// 7102b398a0  (mov x0,x8)
#ifdef MATCHING_HACK_NX_CLANG
__attribute__((naked, noreturn)) void FUN_7102b398a0() {
    asm("stp x29, x30, [sp, #-0x10]!\n\tmov x29, sp\n\tmov x0, x8\n\tbl FUN_71039c0d80\n");
}
#else
[[noreturn]] void FUN_7102b398a0() { FUN_71039c0d80(nullptr); }
#endif
// 7102baccd0  (mov x0,x9)
#ifdef MATCHING_HACK_NX_CLANG
__attribute__((naked, noreturn)) void FUN_7102baccd0() {
    asm("stp x29, x30, [sp, #-0x10]!\n\tmov x29, sp\n\tmov x0, x9\n\tbl FUN_71039c0d80\n");
}
#else
[[noreturn]] void FUN_7102baccd0() { FUN_71039c0d80(nullptr); }
#endif
// 7102f53a60  (mov x0,x8)
#ifdef MATCHING_HACK_NX_CLANG
__attribute__((naked, noreturn)) void FUN_7102f53a60() {
    asm("stp x29, x30, [sp, #-0x10]!\n\tmov x29, sp\n\tmov x0, x8\n\tbl FUN_71039c0d80\n");
}
#else
[[noreturn]] void FUN_7102f53a60() { FUN_71039c0d80(nullptr); }
#endif
// 710304ac2c  (mov x0,x8)
#ifdef MATCHING_HACK_NX_CLANG
__attribute__((naked, noreturn)) void FUN_710304ac2c() {
    asm("stp x29, x30, [sp, #-0x10]!\n\tmov x29, sp\n\tmov x0, x8\n\tbl FUN_71039c0d80\n");
}
#else
[[noreturn]] void FUN_710304ac2c() { FUN_71039c0d80(nullptr); }
#endif
// 7102a2b28c  (add x0,x9,#0x3d0)
#ifdef MATCHING_HACK_NX_CLANG
__attribute__((naked, noreturn)) void FUN_7102a2b28c() {
    asm("stp x29, x30, [sp, #-0x10]!\n\tmov x29, sp\n\tadd x0, x9, #0x3d0\n\tbl FUN_71039c0d80\n");
}
#else
[[noreturn]] void FUN_7102a2b28c() { FUN_71039c0d80(nullptr); }
#endif

} // namespace app::lua_bind
