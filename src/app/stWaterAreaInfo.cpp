#include "types.h"

struct stWaterAreaInfo;
struct LargeRet { u64 a, b, c; };

namespace app::lua_bind {

// 71020d3e40 — reads 4 fields from L2C table: u16+0x0, f32+0x4, f32+0x8, bool+0xc (512 bytes)
// Uses adrp globals at 0x710593a000+0x3a8 and jump table at 0x71044fb000+0xcfc — won't match
void stWaterAreaInfo__load_from_l2c_table_impl(stWaterAreaInfo* self, void* table) {
    (void)self; (void)table;
}

// 71020d4040 — allocates L2C table structure, fills fields, calls 0x71020d4110 (208 bytes)
// Uses adrp globals and absolute call targets — won't match
LargeRet stWaterAreaInfo__store_l2c_table_impl(stWaterAreaInfo* self) {
    (void)self;
    return {};
}

// 71020d42f0 — 4 instructions: mov x2,x1; mov x1,x0; mov x0,x8; b 0x71020d4110
// LargeRet tail-call rearranges args — absolute branch won't match
LargeRet stWaterAreaInfo__store_l2c_table_impl_71020d42f0(stWaterAreaInfo* self, void* table) {
    (void)self; (void)table;
    return {};
}

} // namespace app::lua_bind
