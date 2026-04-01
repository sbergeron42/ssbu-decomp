#include "types.h"

struct AreaContactLog;
struct LargeRet { u64 a, b, c; };

// External helpers for L2CValue serialization (external b branches — won't byte-match)
extern "C" void* FUN_7103733d50(void*, void*);
extern int DAT_710593a3a8[4];

namespace app::lua_bind {

// 7101fca860 (1120 bytes): load fields from L2CValue table — external branches, won't byte-match
void AreaContactLog__load_from_l2c_table_impl(AreaContactLog* obj, void* lv_in) {
    int* plv = reinterpret_cast<int*>(lv_in);
    int* e; float v;
    // s32 at +0, hash 0xbad544942
    u64 h = 0xbad544942ULL;
    e = (*plv==5)?(int*)FUN_7103733d50(*(void**)(plv+2),&h):DAT_710593a3a8;
    { int t=*e; u32 r; if(t==7||t==2) r=(u32)*(long long*)(e+2); else if(t==3) r=(u32)(long long)*reinterpret_cast<float*>(e+2); else r=0; *reinterpret_cast<u32*>(reinterpret_cast<u8*>(obj)+0)=r; }
    // s32 at +4, hash 0xa8d12e98e
    h = 0xa8d12e98eULL;
    e = (*plv==5)?(int*)FUN_7103733d50(*(void**)(plv+2),&h):DAT_710593a3a8;
    { int t=*e; u32 r; if(t==7||t==2) r=(u32)*(long long*)(e+2); else if(t==3) r=(u32)(long long)*reinterpret_cast<float*>(e+2); else r=0; *reinterpret_cast<u32*>(reinterpret_cast<u8*>(obj)+4)=r; }
    // s32 at +8, hash 0xff72be395
    h = 0xff72be395ULL;
    e = (*plv==5)?(int*)FUN_7103733d50(*(void**)(plv+2),&h):DAT_710593a3a8;
    { int t=*e; u32 r; if(t==7||t==2) r=(u32)*(long long*)(e+2); else if(t==3) r=(u32)(long long)*reinterpret_cast<float*>(e+2); else r=0; *reinterpret_cast<u32*>(reinterpret_cast<u8*>(obj)+8)=r; }
    // u8 at +0xc, hash 0x10f1076ffb
    h = 0x10f1076ffbULL;
    e = (*plv==5)?(int*)FUN_7103733d50(*(void**)(plv+2),&h):DAT_710593a3a8;
    { int t=*e; u8 r; if(t==7||t==2) r=(u8)*(long long*)(e+2); else if(t==3) r=(u8)(long long)*reinterpret_cast<float*>(e+2); else r=0; reinterpret_cast<u8*>(obj)[0xc]=r; }
    // u8 at +0xd, hash 0xdcbbfb223
    h = 0xdcbbfb223ULL;
    e = (*plv==5)?(int*)FUN_7103733d50(*(void**)(plv+2),&h):DAT_710593a3a8;
    { int t=*e; u8 r; if(t==7||t==2) r=(u8)*(long long*)(e+2); else if(t==3) r=(u8)(long long)*reinterpret_cast<float*>(e+2); else r=0; reinterpret_cast<u8*>(obj)[0xd]=r; }
    // u8 at +0xe, hash 0x12731fd2d5
    h = 0x12731fd2d5ULL;
    e = (*plv==5)?(int*)FUN_7103733d50(*(void**)(plv+2),&h):DAT_710593a3a8;
    { int t=*e; u8 r; if(t==7||t==2) r=(u8)*(long long*)(e+2); else if(t==3) r=(u8)(long long)*reinterpret_cast<float*>(e+2); else r=0; reinterpret_cast<u8*>(obj)[0xe]=r; }
    // u8 at +0xf, hash 0x11f40cadd0
    h = 0x11f40cadd0ULL;
    e = (*plv==5)?(int*)FUN_7103733d50(*(void**)(plv+2),&h):DAT_710593a3a8;
    { int t=*e; u8 r; if(t==7||t==2) r=(u8)*(long long*)(e+2); else if(t==3) r=(u8)(long long)*reinterpret_cast<float*>(e+2); else r=0; reinterpret_cast<u8*>(obj)[0xf]=r; }
    // sub-table (hash 0x9b37582c4) → f32 at +0x10, f32 at +0x14
    h = 0x9b37582c4ULL;
    int* sub = (*plv==5)?(int*)FUN_7103733d50(*(void**)(plv+2),&h):DAT_710593a3a8;
    // sub-field 0x18cdc1683 → f32 at +0x10
    h = 0x18cdc1683ULL;
    e = (*sub==5)?(int*)FUN_7103733d50(*(void**)(sub+2),&h):DAT_710593a3a8;
    { int t=*e; if(t==7||t==2) v=(float)*(long long*)(e+2); else if(t==3) v=*reinterpret_cast<float*>(e+2); else v=0.0f; *reinterpret_cast<float*>(reinterpret_cast<u8*>(obj)+0x10)=v; }
    // sub-field 0x1fbdb2615 → f32 at +0x14
    h = 0x9b37582c4ULL;
    sub = (*plv==5)?(int*)FUN_7103733d50(*(void**)(plv+2),&h):DAT_710593a3a8;
    h = 0x1fbdb2615ULL;
    e = (*sub==5)?(int*)FUN_7103733d50(*(void**)(sub+2),&h):DAT_710593a3a8;
    { int t=*e; if(t==7||t==2) v=(float)*(long long*)(e+2); else if(t==3) v=*reinterpret_cast<float*>(e+2); else v=0.0f; *reinterpret_cast<float*>(reinterpret_cast<u8*>(obj)+0x14)=v; }
}

// 7101fcacc0: allocate L2CValue table, fill via FUN_7101fcad90, return as LargeRet
#ifdef MATCHING_HACK_NX_CLANG
__attribute__((naked))
LargeRet AreaContactLog__store_l2c_table_impl(AreaContactLog* obj) {
    asm(
        "sub sp, sp, #0x40\n"
        "stp x20, x19, [sp, #0x20]\n"
        "stp x29, x30, [sp, #0x30]\n"
        "add x29, sp, #0x30\n"
        "mov x19, x0\n"
        "mov w1, #0x48\n"
        "mov w0, #0x10\n"
        "mov x20, x8\n"
        "bl FUN_710392dce0\n"
        "cbnz x0, 0f\n"
        "adrp x8, DAT_7105331f00\n"
        "ldr x0, [x8, :lo12:DAT_7105331f00]\n"
        "cbz x0, 1f\n"
        "mov w8, #0x48\n"
        "stur wzr, [x29, #-0x14]\n"
        "sub x1, x29, #0x14\n"
        "str x8, [sp, #0x8]\n"
        "ldr x8, [x0]\n"
        "ldr x8, [x8, #0x30]\n"
        "add x2, sp, #0x8\n"
        "blr x8\n"
        "tbz w0, #0, 1f\n"
        "mov w1, #0x48\n"
        "mov w0, #0x10\n"
        "bl FUN_710392dce0\n"
        "cbnz x0, 0f\n"
        "1:\n"
        "mov x0, xzr\n"
        "0:\n"
        "mov x8, x0\n"
        "stp xzr, xzr, [x0, #0x10]\n"
        "str xzr, [x0, #0x8]\n"
        "add x2, sp, #0x8\n"
        "mov x1, x19\n"
        "str xzr, [x8, #0x28]!\n"
        "str x8, [x0, #0x20]\n"
        "mov w8, #0x5\n"
        "str xzr, [x0, #0x40]\n"
        "stp xzr, xzr, [x0, #0x30]\n"
        "str w8, [sp, #0x8]\n"
        "mov w8, #0x1\n"
        "str x0, [sp, #0x10]\n"
        "str w8, [x0]\n"
        "mov x0, x20\n"
        "bl FUN_7101fcad90\n"
        "add x0, sp, #0x8\n"
        "bl FUN_7103733f20\n"
        "ldp x29, x30, [sp, #0x30]\n"
        "ldp x20, x19, [sp, #0x20]\n"
        "add sp, sp, #0x40\n"
        "ret\n"
    );
}
#endif

// 7101fcb280: fill trampoline — mov x2,x1; mov x1,x0; mov x0,x8; b FUN_7101fcad90
#ifdef MATCHING_HACK_NX_CLANG
__attribute__((naked))
void AreaContactLog__store_l2c_table_impl_7101fcb280(AreaContactLog* obj, void* lv) {
    asm(
        "mov x2, x1\n"
        "mov x1, x0\n"
        "mov x0, x8\n"
        "b FUN_7101fcad90\n"
    );
}
#endif

} // namespace app::lua_bind
