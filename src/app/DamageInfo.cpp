#include "types.h"

struct DamageInfo;
struct LargeRet { u64 a, b, c; };

extern "C" void* FUN_7103733d50(void*, void*);
extern int DAT_710593a3a8[4];

namespace app::lua_bind {

// 71020112a0 (2096 bytes): load fields from L2CValue table — external branches, won't byte-match
void DamageInfo__load_from_l2c_table_impl(DamageInfo* obj, void* lv_in) {
    int* plv = reinterpret_cast<int*>(lv_in);
    int* e; int* sub; float v;
    // f32 at +0, hash 0x76dc346cf
    u64 h = 0x76dc346cfULL;
    e = (*plv==5)?(int*)FUN_7103733d50(*(void**)(plv+2),&h):DAT_710593a3a8;
    { int t=*e; if(t==7||t==2) v=(float)*(long long*)(e+2); else if(t==3) v=*reinterpret_cast<float*>(e+2); else v=0.0f; *reinterpret_cast<float*>(reinterpret_cast<u8*>(obj)+0)=v; }
    // f32 at +4, hash 0xb9ea8580a
    h = 0xb9ea8580aULL;
    e = (*plv==5)?(int*)FUN_7103733d50(*(void**)(plv+2),&h):DAT_710593a3a8;
    { int t=*e; if(t==7||t==2) v=(float)*(long long*)(e+2); else if(t==3) v=*reinterpret_cast<float*>(e+2); else v=0.0f; *reinterpret_cast<float*>(reinterpret_cast<u8*>(obj)+4)=v; }
    // f32 at +8, hash 0x144a6e9b87
    h = 0x144a6e9b87ULL;
    e = (*plv==5)?(int*)FUN_7103733d50(*(void**)(plv+2),&h):DAT_710593a3a8;
    { int t=*e; if(t==7||t==2) v=(float)*(long long*)(e+2); else if(t==3) v=*reinterpret_cast<float*>(e+2); else v=0.0f; *reinterpret_cast<float*>(reinterpret_cast<u8*>(obj)+8)=v; }
    // f32 at +0xc, hash 0xa89c09dd2
    h = 0xa89c09dd2ULL;
    e = (*plv==5)?(int*)FUN_7103733d50(*(void**)(plv+2),&h):DAT_710593a3a8;
    { int t=*e; if(t==7||t==2) v=(float)*(long long*)(e+2); else if(t==3) v=*reinterpret_cast<float*>(e+2); else v=0.0f; *reinterpret_cast<float*>(reinterpret_cast<u8*>(obj)+0xc)=v; }
    // f32 at +0x10, hash 0xdc56470f9
    h = 0xdc56470f9ULL;
    e = (*plv==5)?(int*)FUN_7103733d50(*(void**)(plv+2),&h):DAT_710593a3a8;
    { int t=*e; if(t==7||t==2) v=(float)*(long long*)(e+2); else if(t==3) v=*reinterpret_cast<float*>(e+2); else v=0.0f; *reinterpret_cast<float*>(reinterpret_cast<u8*>(obj)+0x10)=v; }
    // f32 at +0x160, hash 0xa66ec16de
    h = 0xa66ec16deULL;
    e = (*plv==5)?(int*)FUN_7103733d50(*(void**)(plv+2),&h):DAT_710593a3a8;
    { int t=*e; if(t==7||t==2) v=(float)*(long long*)(e+2); else if(t==3) v=*reinterpret_cast<float*>(e+2); else v=0.0f; *reinterpret_cast<float*>(reinterpret_cast<u8*>(obj)+0x160)=v; }
    // sub-table 0xb012d5420 → f32 x at +0x170, f32 y at +0x174, u32 at +0x178
    h = 0xb012d5420ULL;
    sub = (*plv==5)?(int*)FUN_7103733d50(*(void**)(plv+2),&h):DAT_710593a3a8;
    h = 0x18cdc1683ULL;
    e = (*sub==5)?(int*)FUN_7103733d50(*(void**)(sub+2),&h):DAT_710593a3a8;
    { int t=*e; if(t==7||t==2) v=(float)*(long long*)(e+2); else if(t==3) v=*reinterpret_cast<float*>(e+2); else v=0.0f; *reinterpret_cast<float*>(reinterpret_cast<u8*>(obj)+0x170)=v; }
    h = 0xb012d5420ULL;
    sub = (*plv==5)?(int*)FUN_7103733d50(*(void**)(plv+2),&h):DAT_710593a3a8;
    h = 0x1fbdb2615ULL;
    e = (*sub==5)?(int*)FUN_7103733d50(*(void**)(sub+2),&h):DAT_710593a3a8;
    { int t=*e; if(t==7||t==2) v=(float)*(long long*)(e+2); else if(t==3) v=*reinterpret_cast<float*>(e+2); else v=0.0f; *reinterpret_cast<float*>(reinterpret_cast<u8*>(obj)+0x174)=v; }
    h = 0xb012d5420ULL;
    sub = (*plv==5)?(int*)FUN_7103733d50(*(void**)(plv+2),&h):DAT_710593a3a8;
    h = 0x162d277afULL;
    e = (*sub==5)?(int*)FUN_7103733d50(*(void**)(sub+2),&h):DAT_710593a3a8;
    { int t=*e; u32 r; if(t==7||t==2) r=(u32)(float)*(long long*)(e+2); else if(t==3) r=(u32)e[2]; else r=0; *reinterpret_cast<u32*>(reinterpret_cast<u8*>(obj)+0x178)=r; }
    // sub-table 0xd7ab45aa3 → f32 x at +0x180, f32 y at +0x184
    h = 0xd7ab45aa3ULL;
    sub = (*plv==5)?(int*)FUN_7103733d50(*(void**)(plv+2),&h):DAT_710593a3a8;
    h = 0x18cdc1683ULL;
    e = (*sub==5)?(int*)FUN_7103733d50(*(void**)(sub+2),&h):DAT_710593a3a8;
    { int t=*e; if(t==7||t==2) v=(float)*(long long*)(e+2); else if(t==3) v=*reinterpret_cast<float*>(e+2); else v=0.0f; *reinterpret_cast<float*>(reinterpret_cast<u8*>(obj)+0x180)=v; }
    h = 0xd7ab45aa3ULL;
    sub = (*plv==5)?(int*)FUN_7103733d50(*(void**)(plv+2),&h):DAT_710593a3a8;
    h = 0x1fbdb2615ULL;
    e = (*sub==5)?(int*)FUN_7103733d50(*(void**)(sub+2),&h):DAT_710593a3a8;
    { int t=*e; if(t==7||t==2) v=(float)*(long long*)(e+2); else if(t==3) v=*reinterpret_cast<float*>(e+2); else v=0.0f; *reinterpret_cast<float*>(reinterpret_cast<u8*>(obj)+0x184)=v; }
    // f32 at +0x190, hash 0xfbf11fc14
    h = 0xfbf11fc14ULL;
    e = (*plv==5)?(int*)FUN_7103733d50(*(void**)(plv+2),&h):DAT_710593a3a8;
    { int t=*e; if(t==7||t==2) v=(float)*(long long*)(e+2); else if(t==3) v=*reinterpret_cast<float*>(e+2); else v=0.0f; *reinterpret_cast<float*>(reinterpret_cast<u8*>(obj)+0x190)=v; }
    // s32 at +0x194, hash 0x10d723eebb
    h = 0x10d723eebbULL;
    e = (*plv==5)?(int*)FUN_7103733d50(*(void**)(plv+2),&h):DAT_710593a3a8;
    { int t=*e; u32 r; if(t==7||t==2) r=(u32)*(long long*)(e+2); else if(t==3) r=(u32)(long long)*reinterpret_cast<float*>(e+2); else r=0; *reinterpret_cast<u32*>(reinterpret_cast<u8*>(obj)+0x194)=r; }
    // f32 at +0x198, hash 0xc1dbea6f7
    h = 0xc1dbea6f7ULL;
    e = (*plv==5)?(int*)FUN_7103733d50(*(void**)(plv+2),&h):DAT_710593a3a8;
    { int t=*e; if(t==7||t==2) v=(float)*(long long*)(e+2); else if(t==3) v=*reinterpret_cast<float*>(e+2); else v=0.0f; *reinterpret_cast<float*>(reinterpret_cast<u8*>(obj)+0x198)=v; }
    // bool at +0x19c, hash 0xf5fbadc81
    h = 0xf5fbadc81ULL;
    e = (*plv==5)?(int*)FUN_7103733d50(*(void**)(plv+2),&h):DAT_710593a3a8;
    { int t=*e; u8 r=0; if(t==1) r=(0<(int)e[2])?1:0; else if(t==7||t==2) r=(*(long long*)(e+2)!=0)?1:0; else if(t==3) r=((float)e[2]!=0.0f)?1:0; else if(t!=0) r=1; reinterpret_cast<u8*>(obj)[0x19c]=r; }
    // bool at +0x19d, hash 0x1a70c41677
    h = 0x1a70c41677ULL;
    e = (*plv==5)?(int*)FUN_7103733d50(*(void**)(plv+2),&h):DAT_710593a3a8;
    { int t=*e; u8 r=0; if(t==1) r=(0<(int)e[2])?1:0; else if(t==7||t==2) r=(*(long long*)(e+2)!=0)?1:0; else if(t==3) r=((float)e[2]!=0.0f)?1:0; else if(t!=0) r=1; reinterpret_cast<u8*>(obj)[0x19d]=r; }
}

// 7102011ad0: allocate L2CValue table, fill via FUN_7102011ba0, return as LargeRet
#ifdef MATCHING_HACK_NX_CLANG
__attribute__((naked))
LargeRet DamageInfo__store_l2c_table_impl(DamageInfo* obj) {
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
        "bl FUN_7102011ba0\n"
        "add x0, sp, #0x8\n"
        "bl FUN_7103733f20\n"
        "ldp x29, x30, [sp, #0x30]\n"
        "ldp x20, x19, [sp, #0x20]\n"
        "add sp, sp, #0x40\n"
        "ret\n"
    );
}
#endif

// 71020124e0: fill trampoline — mov x2,x1; mov x1,x0; mov x0,x8; b FUN_7102011ba0
#ifdef MATCHING_HACK_NX_CLANG
__attribute__((naked))
void DamageInfo__store_l2c_table_impl_71020124e0(DamageInfo* obj, void* lv) {
    asm(
        "mov x2, x1\n"
        "mov x1, x0\n"
        "mov x0, x8\n"
        "b FUN_7102011ba0\n"
    );
}
#endif

} // namespace app::lua_bind
