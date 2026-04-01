#include "types.h"

struct AttackAbsoluteData;
struct LargeRet { u64 a, b, c; };

extern "C" void* FUN_7103733d50(void*, void*);
extern int DAT_710593a3a8[4];

namespace app::lua_bind {

// 7101febaa0 (1888 bytes): load fields from L2CValue table — external branches, won't byte-match
void AttackAbsoluteData__load_from_l2c_table_impl(AttackAbsoluteData* obj, void* lv_in) {
    int* plv = reinterpret_cast<int*>(lv_in);
    int* e; float v;
    // f32 at +0, hash 0x6ffab8a01
    u64 h = 0x6ffab8a01ULL;
    e = (*plv==5)?(int*)FUN_7103733d50(*(void**)(plv+2),&h):DAT_710593a3a8;
    { int t=*e; if(t==7||t==2) v=(float)*(long long*)(e+2); else if(t==3) v=*reinterpret_cast<float*>(e+2); else v=0.0f; *reinterpret_cast<float*>(reinterpret_cast<u8*>(obj)+0)=v; }
    // s32 at +4, hash 0x7d57445dc
    h = 0x7d57445dcULL;
    e = (*plv==5)?(int*)FUN_7103733d50(*(void**)(plv+2),&h):DAT_710593a3a8;
    { int t=*e; u32 r; if(t==7||t==2) r=(u32)*(long long*)(e+2); else if(t==3) r=(u32)(long long)*reinterpret_cast<float*>(e+2); else r=0; *reinterpret_cast<u32*>(reinterpret_cast<u8*>(obj)+4)=r; }
    // s32 at +8, hash 0x6c5ba6594
    h = 0x6c5ba6594ULL;
    e = (*plv==5)?(int*)FUN_7103733d50(*(void**)(plv+2),&h):DAT_710593a3a8;
    { int t=*e; u32 r; if(t==7||t==2) r=(u32)*(long long*)(e+2); else if(t==3) r=(u32)(long long)*reinterpret_cast<float*>(e+2); else r=0; *reinterpret_cast<u32*>(reinterpret_cast<u8*>(obj)+8)=r; }
    // s32 at +0xc, hash 0x60812b298
    h = 0x60812b298ULL;
    e = (*plv==5)?(int*)FUN_7103733d50(*(void**)(plv+2),&h):DAT_710593a3a8;
    { int t=*e; u32 r; if(t==7||t==2) r=(u32)*(long long*)(e+2); else if(t==3) r=(u32)(long long)*reinterpret_cast<float*>(e+2); else r=0; *reinterpret_cast<u32*>(reinterpret_cast<u8*>(obj)+0xc)=r; }
    // s32 at +0x10, hash 0x67b6a442f
    h = 0x67b6a442fULL;
    e = (*plv==5)?(int*)FUN_7103733d50(*(void**)(plv+2),&h):DAT_710593a3a8;
    { int t=*e; u32 r; if(t==7||t==2) r=(u32)*(long long*)(e+2); else if(t==3) r=(u32)(long long)*reinterpret_cast<float*>(e+2); else r=0; *reinterpret_cast<u32*>(reinterpret_cast<u8*>(obj)+0x10)=r; }
    // f32 at +0x14, hash 0x59a4de085
    h = 0x59a4de085ULL;
    e = (*plv==5)?(int*)FUN_7103733d50(*(void**)(plv+2),&h):DAT_710593a3a8;
    { int t=*e; if(t==7||t==2) v=(float)*(long long*)(e+2); else if(t==3) v=*reinterpret_cast<float*>(e+2); else v=0.0f; *reinterpret_cast<float*>(reinterpret_cast<u8*>(obj)+0x14)=v; }
    // f32 at +0x18, hash 0xb7486a23d
    h = 0xb7486a23dULL;
    e = (*plv==5)?(int*)FUN_7103733d50(*(void**)(plv+2),&h):DAT_710593a3a8;
    { int t=*e; if(t==7||t==2) v=(float)*(long long*)(e+2); else if(t==3) v=*reinterpret_cast<float*>(e+2); else v=0.0f; *reinterpret_cast<float*>(reinterpret_cast<u8*>(obj)+0x18)=v; }
    // f32 at +0x1c, hash 0xbf6893440
    h = 0xbf6893440ULL;
    e = (*plv==5)?(int*)FUN_7103733d50(*(void**)(plv+2),&h):DAT_710593a3a8;
    { int t=*e; if(t==7||t==2) v=(float)*(long long*)(e+2); else if(t==3) v=*reinterpret_cast<float*>(e+2); else v=0.0f; *reinterpret_cast<float*>(reinterpret_cast<u8*>(obj)+0x1c)=v; }
    // s64 at +0x20, hash 0x5330809b6
    h = 0x5330809b6ULL;
    e = (*plv==5)?(int*)FUN_7103733d50(*(void**)(plv+2),&h):DAT_710593a3a8;
    { int t=*e; long long r; if(t==7||t==2) r=*(long long*)(e+2); else if(t==3) r=(long long)*reinterpret_cast<float*>(e+2); else r=0; *reinterpret_cast<long long*>(reinterpret_cast<u8*>(obj)+0x20)=r; }
    // u8 at +0x28, hash 0xcf2e07d39
    h = 0xcf2e07d39ULL;
    e = (*plv==5)?(int*)FUN_7103733d50(*(void**)(plv+2),&h):DAT_710593a3a8;
    { int t=*e; u8 r; if(t==7||t==2) r=(u8)*(long long*)(e+2); else if(t==3) r=(u8)(long long)*reinterpret_cast<float*>(e+2); else r=0; reinterpret_cast<u8*>(obj)[0x28]=r; }
    // u8 at +0x29, hash 0xb24f5c28f
    h = 0xb24f5c28fULL;
    e = (*plv==5)?(int*)FUN_7103733d50(*(void**)(plv+2),&h):DAT_710593a3a8;
    { int t=*e; u8 r; if(t==7||t==2) r=(u8)*(long long*)(e+2); else if(t==3) r=(u8)(long long)*reinterpret_cast<float*>(e+2); else r=0; reinterpret_cast<u8*>(obj)[0x29]=r; }
    // u8 at +0x2a, hash 0x97b20a494
    h = 0x97b20a494ULL;
    e = (*plv==5)?(int*)FUN_7103733d50(*(void**)(plv+2),&h):DAT_710593a3a8;
    { int t=*e; u8 r; if(t==7||t==2) r=(u8)*(long long*)(e+2); else if(t==3) r=(u8)(long long)*reinterpret_cast<float*>(e+2); else r=0; reinterpret_cast<u8*>(obj)[0x2a]=r; }
    // bool at +0x2b, hash 0x8ed2aff94
    h = 0x8ed2aff94ULL;
    e = (*plv==5)?(int*)FUN_7103733d50(*(void**)(plv+2),&h):DAT_710593a3a8;
    { int t=*e; u8 r=0; if(t==1) r=(0<(int)e[2])?1:0; else if(t==7||t==2) r=(*(long long*)(e+2)!=0)?1:0; else if(t==3) r=((float)e[2]!=0.0f)?1:0; else if(t!=0) r=1; reinterpret_cast<u8*>(obj)[0x2b]=r; }
    // bool at +0x2c, hash 0xac4c77c9d
    h = 0xac4c77c9dULL;
    e = (*plv==5)?(int*)FUN_7103733d50(*(void**)(plv+2),&h):DAT_710593a3a8;
    { int t=*e; u8 r=0; if(t==1) r=(0<(int)e[2])?1:0; else if(t==7||t==2) r=(*(long long*)(e+2)!=0)?1:0; else if(t==3) r=((float)e[2]!=0.0f)?1:0; else if(t!=0) r=1; reinterpret_cast<u8*>(obj)[0x2c]=r; }
    // u8 at +0x2e, hash 0x790bf1510
    h = 0x790bf1510ULL;
    e = (*plv==5)?(int*)FUN_7103733d50(*(void**)(plv+2),&h):DAT_710593a3a8;
    { int t=*e; u8 r; if(t==7||t==2) r=(u8)*(long long*)(e+2); else if(t==3) r=(u8)(long long)*reinterpret_cast<float*>(e+2); else r=0; reinterpret_cast<u8*>(obj)[0x2e]=r; }
    // bool at +0x2f, hash 0x663cc6dd2
    h = 0x663cc6dd2ULL;
    e = (*plv==5)?(int*)FUN_7103733d50(*(void**)(plv+2),&h):DAT_710593a3a8;
    { int t=*e; u8 r=0; if(t==1) r=(0<(int)e[2])?1:0; else if(t==7||t==2) r=(*(long long*)(e+2)!=0)?1:0; else if(t==3) r=((float)e[2]!=0.0f)?1:0; else if(t!=0) r=1; reinterpret_cast<u8*>(obj)[0x2f]=r; }
}

// 7101fec200: allocate L2CValue table, fill via FUN_7101fec2d0, return as LargeRet
#ifdef MATCHING_HACK_NX_CLANG
__attribute__((naked))
LargeRet AttackAbsoluteData__store_l2c_table_impl(AttackAbsoluteData* obj) {
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
        "bl FUN_7101fec2d0\n"
        "add x0, sp, #0x8\n"
        "bl FUN_7103733f20\n"
        "ldp x29, x30, [sp, #0x30]\n"
        "ldp x20, x19, [sp, #0x20]\n"
        "add sp, sp, #0x40\n"
        "ret\n"
    );
}
#endif

// 7101fec920: fill trampoline — mov x2,x1; mov x1,x0; mov x0,x8; b FUN_7101fec2d0
#ifdef MATCHING_HACK_NX_CLANG
__attribute__((naked))
void AttackAbsoluteData__store_l2c_table_impl_7101fec920(AttackAbsoluteData* obj, void* lv) {
    asm(
        "mov x2, x1\n"
        "mov x1, x0\n"
        "mov x0, x8\n"
        "b FUN_7101fec2d0\n"
    );
}
#endif

} // namespace app::lua_bind
