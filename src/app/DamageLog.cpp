#include "types.h"

struct DamageLog;
struct LargeRet { u64 a, b, c; };

extern "C" void* FUN_7103733d50(void*, void*);
extern int DAT_710593a3a8[4];

namespace app::lua_bind {

// 7102013080 (4896 bytes): load fields from L2CValue table — external branches, won't byte-match
void DamageLog__load_from_l2c_table_impl(DamageLog* obj, void* lv_in) {
    int* plv = reinterpret_cast<int*>(lv_in);
    int* e; int* sub; float v;
    // f32 at +0, hash 0x90aab1350
    u64 h = 0x90aab1350ULL;
    e = (*plv==5)?(int*)FUN_7103733d50(*(void**)(plv+2),&h):DAT_710593a3a8;
    { int t=*e; if(t==7||t==2) v=(float)*(long long*)(e+2); else if(t==3) v=(float)e[2]; else v=0.0f; *reinterpret_cast<float*>(reinterpret_cast<u8*>(obj)+0)=v; }
    // s32 at +4, hash 0x6adf208fa
    h = 0x6adf208faULL;
    e = (*plv==5)?(int*)FUN_7103733d50(*(void**)(plv+2),&h):DAT_710593a3a8;
    { int t=*e; u32 r; if(t==7||t==2) r=(u32)*(long long*)(e+2); else if(t==3) r=(u32)(long long)(float)e[2]; else r=0; *reinterpret_cast<u32*>(reinterpret_cast<u8*>(obj)+4)=r; }
    // s32 at +8, hash 0x7b99cf39c
    h = 0x7b99cf39cULL;
    e = (*plv==5)?(int*)FUN_7103733d50(*(void**)(plv+2),&h):DAT_710593a3a8;
    { int t=*e; u32 r; if(t==7||t==2) r=(u32)*(long long*)(e+2); else if(t==3) r=(u32)(long long)(float)e[2]; else r=0; *reinterpret_cast<u32*>(reinterpret_cast<u8*>(obj)+8)=r; }
    // sub-table 0xad3b8cf79 → f32 x at +0x10, f32 y at +0x14
    h = 0xad3b8cf79ULL;
    sub = (*plv==5)?(int*)FUN_7103733d50(*(void**)(plv+2),&h):DAT_710593a3a8;
    h = 0x18cdc1683ULL;
    e = (*sub==5)?(int*)FUN_7103733d50(*(void**)(sub+2),&h):DAT_710593a3a8;
    { int t=*e; if(t==7||t==2) v=(float)*(long long*)(e+2); else if(t==3) v=(float)e[2]; else v=0.0f; *reinterpret_cast<float*>(reinterpret_cast<u8*>(obj)+0x10)=v; }
    h = 0xad3b8cf79ULL;
    sub = (*plv==5)?(int*)FUN_7103733d50(*(void**)(plv+2),&h):DAT_710593a3a8;
    h = 0x1fbdb2615ULL;
    e = (*sub==5)?(int*)FUN_7103733d50(*(void**)(sub+2),&h):DAT_710593a3a8;
    { int t=*e; if(t==7||t==2) v=(float)*(long long*)(e+2); else if(t==3) v=(float)e[2]; else v=0.0f; *reinterpret_cast<float*>(reinterpret_cast<u8*>(obj)+0x14)=v; }
    // sub-table 0xb012d5420 → f32 x at +0x20, f32 y at +0x24, u32 at +0x28
    h = 0xb012d5420ULL;
    sub = (*plv==5)?(int*)FUN_7103733d50(*(void**)(plv+2),&h):DAT_710593a3a8;
    h = 0x18cdc1683ULL;
    e = (*sub==5)?(int*)FUN_7103733d50(*(void**)(sub+2),&h):DAT_710593a3a8;
    { int t=*e; if(t==7||t==2) v=(float)*(long long*)(e+2); else if(t==3) v=(float)e[2]; else v=0.0f; *reinterpret_cast<float*>(reinterpret_cast<u8*>(obj)+0x20)=v; }
    h = 0xb012d5420ULL;
    sub = (*plv==5)?(int*)FUN_7103733d50(*(void**)(plv+2),&h):DAT_710593a3a8;
    h = 0x1fbdb2615ULL;
    e = (*sub==5)?(int*)FUN_7103733d50(*(void**)(sub+2),&h):DAT_710593a3a8;
    { int t=*e; if(t==7||t==2) v=(float)*(long long*)(e+2); else if(t==3) v=(float)e[2]; else v=0.0f; *reinterpret_cast<float*>(reinterpret_cast<u8*>(obj)+0x24)=v; }
    h = 0xb012d5420ULL;
    sub = (*plv==5)?(int*)FUN_7103733d50(*(void**)(plv+2),&h):DAT_710593a3a8;
    h = 0x162d277afULL;
    e = (*sub==5)?(int*)FUN_7103733d50(*(void**)(sub+2),&h):DAT_710593a3a8;
    { int t=*e; u32 r; if(t==7||t==2) r=(u32)(float)*(long long*)(e+2); else if(t==3) r=(u32)e[2]; else r=0; *reinterpret_cast<u32*>(reinterpret_cast<u8*>(obj)+0x28)=r; }
    // sub-table 0xd7ab45aa3 → f32 x at +0x30, f32 y at +0x34
    h = 0xd7ab45aa3ULL;
    sub = (*plv==5)?(int*)FUN_7103733d50(*(void**)(plv+2),&h):DAT_710593a3a8;
    h = 0x18cdc1683ULL;
    e = (*sub==5)?(int*)FUN_7103733d50(*(void**)(sub+2),&h):DAT_710593a3a8;
    { int t=*e; if(t==7||t==2) v=(float)*(long long*)(e+2); else if(t==3) v=(float)e[2]; else v=0.0f; *reinterpret_cast<float*>(reinterpret_cast<u8*>(obj)+0x30)=v; }
    h = 0xd7ab45aa3ULL;
    sub = (*plv==5)?(int*)FUN_7103733d50(*(void**)(plv+2),&h):DAT_710593a3a8;
    h = 0x1fbdb2615ULL;
    e = (*sub==5)?(int*)FUN_7103733d50(*(void**)(sub+2),&h):DAT_710593a3a8;
    { int t=*e; if(t==7||t==2) v=(float)*(long long*)(e+2); else if(t==3) v=(float)e[2]; else v=0.0f; *reinterpret_cast<float*>(reinterpret_cast<u8*>(obj)+0x34)=v; }
    // f32 at +0x40, hash 0x6500a9a09
    h = 0x6500a9a09ULL;
    e = (*plv==5)?(int*)FUN_7103733d50(*(void**)(plv+2),&h):DAT_710593a3a8;
    { int t=*e; if(t==7||t==2) v=(float)*(long long*)(e+2); else if(t==3) v=(float)e[2]; else v=0.0f; *reinterpret_cast<float*>(reinterpret_cast<u8*>(obj)+0x40)=v; }
    // f32 at +0x44, hash 0x35851bc47
    h = 0x35851bc47ULL;
    e = (*plv==5)?(int*)FUN_7103733d50(*(void**)(plv+2),&h):DAT_710593a3a8;
    { int t=*e; if(t==7||t==2) v=(float)*(long long*)(e+2); else if(t==3) v=(float)e[2]; else v=0.0f; *reinterpret_cast<float*>(reinterpret_cast<u8*>(obj)+0x44)=v; }
    // f32 at +0x48, hash 0xf70851bae
    h = 0xf70851baeULL;
    e = (*plv==5)?(int*)FUN_7103733d50(*(void**)(plv+2),&h):DAT_710593a3a8;
    { int t=*e; if(t==7||t==2) v=(float)*(long long*)(e+2); else if(t==3) v=(float)e[2]; else v=0.0f; *reinterpret_cast<float*>(reinterpret_cast<u8*>(obj)+0x48)=v; }
    // s32 at +0x4c, hash 0xedf149134
    h = 0xedf149134ULL;
    e = (*plv==5)?(int*)FUN_7103733d50(*(void**)(plv+2),&h):DAT_710593a3a8;
    { int t=*e; u32 r; if(t==7||t==2) r=(u32)*(long long*)(e+2); else if(t==3) r=(u32)(long long)(float)e[2]; else r=0; *reinterpret_cast<u32*>(reinterpret_cast<u8*>(obj)+0x4c)=r; }
    // u64 at +0x50, hash 0x5330809b6
    h = 0x5330809b6ULL;
    e = (*plv==5)?(int*)FUN_7103733d50(*(void**)(plv+2),&h):DAT_710593a3a8;
    { int t=*e; long long r; if(t==7||t==2) r=*(long long*)(e+2); else if(t==3) r=(long long)(float)e[2]; else r=0; *reinterpret_cast<long long*>(reinterpret_cast<u8*>(obj)+0x50)=r; }
    // f32 at +0x58, hash 0xb9ea8580a
    h = 0xb9ea8580aULL;
    e = (*plv==5)?(int*)FUN_7103733d50(*(void**)(plv+2),&h):DAT_710593a3a8;
    { int t=*e; if(t==7||t==2) v=(float)*(long long*)(e+2); else if(t==3) v=(float)e[2]; else v=0.0f; *reinterpret_cast<float*>(reinterpret_cast<u8*>(obj)+0x58)=v; }
    // s32 at +0x5c, hash 0x5a41a4ebb
    h = 0x5a41a4ebbULL;
    e = (*plv==5)?(int*)FUN_7103733d50(*(void**)(plv+2),&h):DAT_710593a3a8;
    { int t=*e; u32 r; if(t==7||t==2) r=(u32)*(long long*)(e+2); else if(t==3) r=(u32)(long long)(float)e[2]; else r=0; *reinterpret_cast<u32*>(reinterpret_cast<u8*>(obj)+0x5c)=r; }
    // f32 at +0x60, hash 0xbf6893440
    h = 0xbf6893440ULL;
    e = (*plv==5)?(int*)FUN_7103733d50(*(void**)(plv+2),&h):DAT_710593a3a8;
    { int t=*e; if(t==7||t==2) v=(float)*(long long*)(e+2); else if(t==3) v=(float)e[2]; else v=0.0f; *reinterpret_cast<float*>(reinterpret_cast<u8*>(obj)+0x60)=v; }
    // sub-table 0xe66eb42b7 → f32 x at +0x70, f32 y at +0x74
    h = 0xe66eb42b7ULL;
    sub = (*plv==5)?(int*)FUN_7103733d50(*(void**)(plv+2),&h):DAT_710593a3a8;
    h = 0x18cdc1683ULL;
    e = (*sub==5)?(int*)FUN_7103733d50(*(void**)(sub+2),&h):DAT_710593a3a8;
    { int t=*e; if(t==7||t==2) v=(float)*(long long*)(e+2); else if(t==3) v=(float)e[2]; else v=0.0f; *reinterpret_cast<float*>(reinterpret_cast<u8*>(obj)+0x70)=v; }
    h = 0xe66eb42b7ULL;
    sub = (*plv==5)?(int*)FUN_7103733d50(*(void**)(plv+2),&h):DAT_710593a3a8;
    h = 0x1fbdb2615ULL;
    e = (*sub==5)?(int*)FUN_7103733d50(*(void**)(sub+2),&h):DAT_710593a3a8;
    { int t=*e; if(t==7||t==2) v=(float)*(long long*)(e+2); else if(t==3) v=(float)e[2]; else v=0.0f; *reinterpret_cast<float*>(reinterpret_cast<u8*>(obj)+0x74)=v; }
    // s32 at +0x80, hash 0xa854977fe
    h = 0xa854977feULL;
    e = (*plv==5)?(int*)FUN_7103733d50(*(void**)(plv+2),&h):DAT_710593a3a8;
    { int t=*e; u32 r; if(t==7||t==2) r=(u32)*(long long*)(e+2); else if(t==3) r=(u32)(long long)(float)e[2]; else r=0; *reinterpret_cast<u32*>(reinterpret_cast<u8*>(obj)+0x80)=r; }
    // s32 at +0x84, hash 0x10d723eebb
    h = 0x10d723eebbULL;
    e = (*plv==5)?(int*)FUN_7103733d50(*(void**)(plv+2),&h):DAT_710593a3a8;
    { int t=*e; u32 r; if(t==7||t==2) r=(u32)*(long long*)(e+2); else if(t==3) r=(u32)(long long)(float)e[2]; else r=0; *reinterpret_cast<u32*>(reinterpret_cast<u8*>(obj)+0x84)=r; }
    // u8 at +0x88, hash 0x10860c2250
    h = 0x10860c2250ULL;
    e = (*plv==5)?(int*)FUN_7103733d50(*(void**)(plv+2),&h):DAT_710593a3a8;
    { int t=*e; u8 r; if(t==7||t==2) r=(u8)*(long long*)(e+2); else if(t==3) r=(u8)(long long)(float)e[2]; else r=0; reinterpret_cast<u8*>(obj)[0x88]=r; }
    // bool at +0x89, hash 0xb3b034550
    h = 0xb3b034550ULL;
    e = (*plv==5)?(int*)FUN_7103733d50(*(void**)(plv+2),&h):DAT_710593a3a8;
    { int t=*e; u8 r=0; if(t==1) r=(0<(int)e[2])?1:0; else if(t==7||t==2) r=(*(long long*)(e+2)!=0)?1:0; else if(t==3) r=((float)e[2]!=0.0f)?1:0; else if(t!=0) r=1; reinterpret_cast<u8*>(obj)[0x89]=r; }
    // bool at +0x8a, hash 0x130ca46a01
    h = 0x130ca46a01ULL;
    e = (*plv==5)?(int*)FUN_7103733d50(*(void**)(plv+2),&h):DAT_710593a3a8;
    { int t=*e; u8 r=0; if(t==1) r=(0<(int)e[2])?1:0; else if(t==7||t==2) r=(*(long long*)(e+2)!=0)?1:0; else if(t==3) r=((float)e[2]!=0.0f)?1:0; else if(t!=0) r=1; reinterpret_cast<u8*>(obj)[0x8a]=r; }
    // bool at +0x8b, hash 0xe85b80499
    h = 0xe85b80499ULL;
    e = (*plv==5)?(int*)FUN_7103733d50(*(void**)(plv+2),&h):DAT_710593a3a8;
    { int t=*e; u8 r=0; if(t==1) r=(0<(int)e[2])?1:0; else if(t==7||t==2) r=(*(long long*)(e+2)!=0)?1:0; else if(t==3) r=((float)e[2]!=0.0f)?1:0; else if(t!=0) r=1; reinterpret_cast<u8*>(obj)[0x8b]=r; }
    // bool at +0x8c, hash 0x9ab78885f
    h = 0x9ab78885fULL;
    e = (*plv==5)?(int*)FUN_7103733d50(*(void**)(plv+2),&h):DAT_710593a3a8;
    { int t=*e; u8 r=0; if(t==1) r=(0<(int)e[2])?1:0; else if(t==7||t==2) r=(*(long long*)(e+2)!=0)?1:0; else if(t==3) r=((float)e[2]!=0.0f)?1:0; else if(t!=0) r=1; reinterpret_cast<u8*>(obj)[0x8c]=r; }
    // bool at +0x8d, hash 0x78ac8f680
    h = 0x78ac8f680ULL;
    e = (*plv==5)?(int*)FUN_7103733d50(*(void**)(plv+2),&h):DAT_710593a3a8;
    { int t=*e; u8 r=0; if(t==1) r=(0<(int)e[2])?1:0; else if(t==7||t==2) r=(*(long long*)(e+2)!=0)?1:0; else if(t==3) r=((float)e[2]!=0.0f)?1:0; else if(t!=0) r=1; reinterpret_cast<u8*>(obj)[0x8d]=r; }
    // bool at +0x8e, hash 0x7b892d86a
    h = 0x7b892d86aULL;
    e = (*plv==5)?(int*)FUN_7103733d50(*(void**)(plv+2),&h):DAT_710593a3a8;
    { int t=*e; u8 r=0; if(t==1) r=(0<(int)e[2])?1:0; else if(t==7||t==2) r=(*(long long*)(e+2)!=0)?1:0; else if(t==3) r=((float)e[2]!=0.0f)?1:0; else if(t!=0) r=1; reinterpret_cast<u8*>(obj)[0x8e]=r; }
    // bool at +0x8f, hash 0xbd5863ce0
    h = 0xbd5863ce0ULL;
    e = (*plv==5)?(int*)FUN_7103733d50(*(void**)(plv+2),&h):DAT_710593a3a8;
    { int t=*e; u8 r=0; if(t==1) r=(0<(int)e[2])?1:0; else if(t==7||t==2) r=(*(long long*)(e+2)!=0)?1:0; else if(t==3) r=((float)e[2]!=0.0f)?1:0; else if(t!=0) r=1; reinterpret_cast<u8*>(obj)[0x8f]=r; }
    // bool at +0x90, hash 0xb3241670f
    h = 0xb3241670fULL;
    e = (*plv==5)?(int*)FUN_7103733d50(*(void**)(plv+2),&h):DAT_710593a3a8;
    { int t=*e; u8 r=0; if(t==1) r=(0<(int)e[2])?1:0; else if(t==7||t==2) r=(*(long long*)(e+2)!=0)?1:0; else if(t==3) r=((float)e[2]!=0.0f)?1:0; else if(t!=0) r=1; reinterpret_cast<u8*>(obj)[0x90]=r; }
    // bool at +0x91, hash 0x510401df6
    h = 0x510401df6ULL;
    e = (*plv==5)?(int*)FUN_7103733d50(*(void**)(plv+2),&h):DAT_710593a3a8;
    { int t=*e; u8 r=0; if(t==1) r=(0<(int)e[2])?1:0; else if(t==7||t==2) r=(*(long long*)(e+2)!=0)?1:0; else if(t==3) r=((float)e[2]!=0.0f)?1:0; else if(t!=0) r=1; reinterpret_cast<u8*>(obj)[0x91]=r; }
    // bool at +0x92, hash 0x60812b298
    h = 0x60812b298ULL;
    e = (*plv==5)?(int*)FUN_7103733d50(*(void**)(plv+2),&h):DAT_710593a3a8;
    { int t=*e; u8 r=0; if(t==1) r=(0<(int)e[2])?1:0; else if(t==7||t==2) r=(*(long long*)(e+2)!=0)?1:0; else if(t==3) r=((float)e[2]!=0.0f)?1:0; else if(t!=0) r=1; reinterpret_cast<u8*>(obj)[0x92]=r; }
    // bool at +0x93, hash 0x16846ecfc7
    h = 0x16846ecfc7ULL;
    e = (*plv==5)?(int*)FUN_7103733d50(*(void**)(plv+2),&h):DAT_710593a3a8;
    { int t=*e; u8 r=0; if(t==1) r=(0<(int)e[2])?1:0; else if(t==7||t==2) r=(*(long long*)(e+2)!=0)?1:0; else if(t==3) r=((float)e[2]!=0.0f)?1:0; else if(t!=0) r=1; reinterpret_cast<u8*>(obj)[0x93]=r; }
    // bool at +0x94, hash 0x1a70c41677
    h = 0x1a70c41677ULL;
    e = (*plv==5)?(int*)FUN_7103733d50(*(void**)(plv+2),&h):DAT_710593a3a8;
    { int t=*e; u8 r=0; if(t==1) r=(0<(int)e[2])?1:0; else if(t==7||t==2) r=(*(long long*)(e+2)!=0)?1:0; else if(t==3) r=((float)e[2]!=0.0f)?1:0; else if(t!=0) r=1; reinterpret_cast<u8*>(obj)[0x94]=r; }
    // s32 at +0x98, hash 0x119f7207bb
    h = 0x119f7207bbULL;
    e = (*plv==5)?(int*)FUN_7103733d50(*(void**)(plv+2),&h):DAT_710593a3a8;
    { int t=*e; u32 r; if(t==7||t==2) r=(u32)*(long long*)(e+2); else if(t==3) r=(u32)(long long)(float)e[2]; else r=0; *reinterpret_cast<u32*>(reinterpret_cast<u8*>(obj)+0x98)=r; }
    // u8 at +0x9c, hash 0x12d255714f
    h = 0x12d255714fULL;
    e = (*plv==5)?(int*)FUN_7103733d50(*(void**)(plv+2),&h):DAT_710593a3a8;
    { int t=*e; u8 r; if(t==7||t==2) r=(u8)*(long long*)(e+2); else if(t==3) r=(u8)(long long)(float)e[2]; else r=0; reinterpret_cast<u8*>(obj)[0x9c]=r; }
}

// 71020143a0 (208 bytes): allocate L2CValue table, return as LargeRet
LargeRet DamageLog__store_l2c_table_impl(DamageLog* obj) {
    (void)obj;
    return LargeRet{};
}

// 7102015430 (8080 bytes): fill existing L2CValue table
void DamageLog__store_l2c_table_impl_7102015430(DamageLog* obj, void* lv) {
    (void)obj; (void)lv;
}

} // namespace app::lua_bind
