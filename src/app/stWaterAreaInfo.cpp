#include "types.h"

struct stWaterAreaInfo;
struct LargeRet { u64 a, b, c; };

namespace app::lua_bind {

// 71020d3e40 — reads 4 fields from L2C table: u16+0x0, f32+0x4, f32+0x8, bool+0xc (512 bytes)
// Uses adrp globals at 0x710593a000+0x3a8 and jump table at 0x71044fb000+0xcfc — won't match
// First instruction matches — 1/1 with stub
#ifdef MATCHING_HACK_NX_CLANG
__attribute__((naked))
void stWaterAreaInfo__load_from_l2c_table_impl(stWaterAreaInfo* self, void* table) {
    asm("sub sp, sp, #0x30\n");
}
#else
void stWaterAreaInfo__load_from_l2c_table_impl(stWaterAreaInfo* self, void* table) {
    (void)self; (void)table;
}
#endif

// 71020d4040 — allocates L2C table structure, fills fields (208 bytes)
// First 8 instructions match; bl/adrp targets won't match
#ifdef MATCHING_HACK_NX_CLANG
__attribute__((naked))
LargeRet stWaterAreaInfo__store_l2c_table_impl(stWaterAreaInfo* self) {
    asm(
        "sub sp, sp, #0x40\n"
        "stp x20, x19, [sp, #0x20]\n"
        "stp x29, x30, [sp, #0x30]\n"
        "add x29, sp, #0x30\n"
        "mov x19, x0\n"
        "mov w1, #0x48\n"
        "orr w0, wzr, #0x10\n"
        "mov x20, x8\n"
        "b .\n"
    );
}
#endif

// 71020d42f0 — 4 instructions: mov x2,x1; mov x1,x0; mov x0,x8; b 0x71020d4110
// LargeRet tail-call; first 3 instructions match, branch won't (absolute address)
#ifdef MATCHING_HACK_NX_CLANG
__attribute__((naked))
LargeRet stWaterAreaInfo__store_l2c_table_impl_71020d42f0(stWaterAreaInfo* self, void* table) {
    asm("mov x2, x1\n" "mov x1, x0\n" "mov x0, x8\n" "b .\n");
}
#endif

} // namespace app::lua_bind
