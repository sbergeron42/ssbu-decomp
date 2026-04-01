#include "types.h"

struct AttackData;
struct LargeRet { u64 a, b, c; };

extern "C" void* FUN_7103733d50(void*, void*);
extern int DAT_710593a3a8[4];

namespace app::lua_bind {

// 7101fed120 (7088 bytes): load fields from L2CValue table — external branches, won't byte-match
void AttackData__load_from_l2c_table_impl(AttackData* obj, void* lv_in) {
    int* plv = reinterpret_cast<int*>(lv_in);
    int* e; int* sub; float v;
    // sub-table 0x7af5c7bf6 → f32 x at +0, f32 y at +4, u32 at +8
    u64 h = 0x7af5c7bf6ULL;
    sub = (*plv==5)?(int*)FUN_7103733d50(*(void**)(plv+2),&h):DAT_710593a3a8;
    h = 0x18cdc1683ULL;
    e = (*sub==5)?(int*)FUN_7103733d50(*(void**)(sub+2),&h):DAT_710593a3a8;
    { int t=*e; if(t==7||t==2) v=(float)*(long long*)(e+2); else if(t==3) v=(float)e[2]; else v=0.0f; *reinterpret_cast<float*>(reinterpret_cast<u8*>(obj)+0)=v; }
    h = 0x7af5c7bf6ULL;
    sub = (*plv==5)?(int*)FUN_7103733d50(*(void**)(plv+2),&h):DAT_710593a3a8;
    h = 0x1fbdb2615ULL;
    e = (*sub==5)?(int*)FUN_7103733d50(*(void**)(sub+2),&h):DAT_710593a3a8;
    { int t=*e; if(t==7||t==2) v=(float)*(long long*)(e+2); else if(t==3) v=(float)e[2]; else v=0.0f; *reinterpret_cast<float*>(reinterpret_cast<u8*>(obj)+4)=v; }
    h = 0x7af5c7bf6ULL;
    sub = (*plv==5)?(int*)FUN_7103733d50(*(void**)(plv+2),&h):DAT_710593a3a8;
    h = 0x162d277afULL;
    e = (*sub==5)?(int*)FUN_7103733d50(*(void**)(sub+2),&h):DAT_710593a3a8;
    { int t=*e; u32 r; if(t==7||t==2) r=(u32)(float)*(long long*)(e+2); else if(t==3) r=(u32)e[2]; else r=0; *reinterpret_cast<u32*>(reinterpret_cast<u8*>(obj)+8)=r; }
    // sub-table 0x8adf4bd50 → f32 x at +0x10, f32 y at +0x14, u32 at +0x18
    h = 0x8adf4bd50ULL;
    sub = (*plv==5)?(int*)FUN_7103733d50(*(void**)(plv+2),&h):DAT_710593a3a8;
    h = 0x18cdc1683ULL;
    e = (*sub==5)?(int*)FUN_7103733d50(*(void**)(sub+2),&h):DAT_710593a3a8;
    { int t=*e; if(t==7||t==2) v=(float)*(long long*)(e+2); else if(t==3) v=(float)e[2]; else v=0.0f; *reinterpret_cast<float*>(reinterpret_cast<u8*>(obj)+0x10)=v; }
    h = 0x8adf4bd50ULL;
    sub = (*plv==5)?(int*)FUN_7103733d50(*(void**)(plv+2),&h):DAT_710593a3a8;
    h = 0x1fbdb2615ULL;
    e = (*sub==5)?(int*)FUN_7103733d50(*(void**)(sub+2),&h):DAT_710593a3a8;
    { int t=*e; if(t==7||t==2) v=(float)*(long long*)(e+2); else if(t==3) v=(float)e[2]; else v=0.0f; *reinterpret_cast<float*>(reinterpret_cast<u8*>(obj)+0x14)=v; }
    h = 0x8adf4bd50ULL;
    sub = (*plv==5)?(int*)FUN_7103733d50(*(void**)(plv+2),&h):DAT_710593a3a8;
    h = 0x162d277afULL;
    e = (*sub==5)?(int*)FUN_7103733d50(*(void**)(sub+2),&h):DAT_710593a3a8;
    { int t=*e; u32 r; if(t==7||t==2) r=(u32)(float)*(long long*)(e+2); else if(t==3) r=(u32)e[2]; else r=0; *reinterpret_cast<u32*>(reinterpret_cast<u8*>(obj)+0x18)=r; }
    // f32 at +0x20, hash 0x6ffab8a01
    h = 0x6ffab8a01ULL;
    e = (*plv==5)?(int*)FUN_7103733d50(*(void**)(plv+2),&h):DAT_710593a3a8;
    { int t=*e; if(t==7||t==2) v=(float)*(long long*)(e+2); else if(t==3) v=(float)e[2]; else v=0.0f; *reinterpret_cast<float*>(reinterpret_cast<u8*>(obj)+0x20)=v; }
    // f32 at +0x24, hash 0x58446eb8a
    h = 0x58446eb8aULL;
    e = (*plv==5)?(int*)FUN_7103733d50(*(void**)(plv+2),&h):DAT_710593a3a8;
    { int t=*e; if(t==7||t==2) v=(float)*(long long*)(e+2); else if(t==3) v=(float)e[2]; else v=0.0f; *reinterpret_cast<float*>(reinterpret_cast<u8*>(obj)+0x24)=v; }
    // s32 at +0x28, hash 0x7d57445dc
    h = 0x7d57445dcULL;
    e = (*plv==5)?(int*)FUN_7103733d50(*(void**)(plv+2),&h):DAT_710593a3a8;
    { int t=*e; u32 r; if(t==7||t==2) r=(u32)*(long long*)(e+2); else if(t==3) r=(u32)(long long)(float)e[2]; else r=0; *reinterpret_cast<u32*>(reinterpret_cast<u8*>(obj)+0x28)=r; }
    // s32 at +0x2c, hash 0x6c5ba6594
    h = 0x6c5ba6594ULL;
    e = (*plv==5)?(int*)FUN_7103733d50(*(void**)(plv+2),&h):DAT_710593a3a8;
    { int t=*e; u32 r; if(t==7||t==2) r=(u32)*(long long*)(e+2); else if(t==3) r=(u32)(long long)(float)e[2]; else r=0; *reinterpret_cast<u32*>(reinterpret_cast<u8*>(obj)+0x2c)=r; }
    // s32 at +0x30, hash 0x60812b298
    h = 0x60812b298ULL;
    e = (*plv==5)?(int*)FUN_7103733d50(*(void**)(plv+2),&h):DAT_710593a3a8;
    { int t=*e; u32 r; if(t==7||t==2) r=(u32)*(long long*)(e+2); else if(t==3) r=(u32)(long long)(float)e[2]; else r=0; *reinterpret_cast<u32*>(reinterpret_cast<u8*>(obj)+0x30)=r; }
    // s32 at +0x34, hash 0x67b6a442f
    h = 0x67b6a442fULL;
    e = (*plv==5)?(int*)FUN_7103733d50(*(void**)(plv+2),&h):DAT_710593a3a8;
    { int t=*e; u32 r; if(t==7||t==2) r=(u32)*(long long*)(e+2); else if(t==3) r=(u32)(long long)(float)e[2]; else r=0; *reinterpret_cast<u32*>(reinterpret_cast<u8*>(obj)+0x34)=r; }
    // f32 at +0x38, hash 0x59a4de085
    h = 0x59a4de085ULL;
    e = (*plv==5)?(int*)FUN_7103733d50(*(void**)(plv+2),&h):DAT_710593a3a8;
    { int t=*e; if(t==7||t==2) v=(float)*(long long*)(e+2); else if(t==3) v=(float)e[2]; else v=0.0f; *reinterpret_cast<float*>(reinterpret_cast<u8*>(obj)+0x38)=v; }
    // f32 at +0x3c, hash 0xb7486a23d
    h = 0xb7486a23dULL;
    e = (*plv==5)?(int*)FUN_7103733d50(*(void**)(plv+2),&h):DAT_710593a3a8;
    { int t=*e; if(t==7||t==2) v=(float)*(long long*)(e+2); else if(t==3) v=(float)e[2]; else v=0.0f; *reinterpret_cast<float*>(reinterpret_cast<u8*>(obj)+0x3c)=v; }
    // f32 at +0x40, hash 0xbf6893440
    h = 0xbf6893440ULL;
    e = (*plv==5)?(int*)FUN_7103733d50(*(void**)(plv+2),&h):DAT_710593a3a8;
    { int t=*e; if(t==7||t==2) v=(float)*(long long*)(e+2); else if(t==3) v=(float)e[2]; else v=0.0f; *reinterpret_cast<float*>(reinterpret_cast<u8*>(obj)+0x40)=v; }
    // u64 at +0x48, hash 0x52fe5691f
    h = 0x52fe5691fULL;
    e = (*plv==5)?(int*)FUN_7103733d50(*(void**)(plv+2),&h):DAT_710593a3a8;
    { int t=*e; long long r; if(t==7||t==2) r=*(long long*)(e+2); else if(t==3) r=(long long)(float)e[2]; else r=0; *reinterpret_cast<long long*>(reinterpret_cast<u8*>(obj)+0x48)=r; }
    // u16 at +0x50, hash 0x10f1076ffb
    h = 0x10f1076ffbULL;
    e = (*plv==5)?(int*)FUN_7103733d50(*(void**)(plv+2),&h):DAT_710593a3a8;
    { int t=*e; u16 r; if(t==7||t==2) r=(u16)*(long long*)(e+2); else if(t==3) r=(u16)(long long)(float)e[2]; else r=0; *reinterpret_cast<u16*>(reinterpret_cast<u8*>(obj)+0x50)=r; }
    // u8 at +0x52, hash 0x1160677d4d
    h = 0x1160677d4dULL;
    e = (*plv==5)?(int*)FUN_7103733d50(*(void**)(plv+2),&h):DAT_710593a3a8;
    { int t=*e; u8 r; if(t==7||t==2) r=(u8)*(long long*)(e+2); else if(t==3) r=(u8)(long long)(float)e[2]; else r=0; reinterpret_cast<u8*>(obj)[0x52]=r; }
    // bool at +0x53, hash 0xa97419eb2
    h = 0xa97419eb2ULL;
    e = (*plv==5)?(int*)FUN_7103733d50(*(void**)(plv+2),&h):DAT_710593a3a8;
    { int t=*e; u8 r=0; if(t==1) r=(0<(int)e[2])?1:0; else if(t==7||t==2) r=(*(long long*)(e+2)!=0)?1:0; else if(t==3) r=((float)e[2]!=0.0f)?1:0; else if(t!=0) r=1; reinterpret_cast<u8*>(obj)[0x53]=r; }
    // u8 at +0x54, hash 0xce7335011
    h = 0xce7335011ULL;
    e = (*plv==5)?(int*)FUN_7103733d50(*(void**)(plv+2),&h):DAT_710593a3a8;
    { int t=*e; u8 r; if(t==7||t==2) r=(u8)*(long long*)(e+2); else if(t==3) r=(u8)(long long)(float)e[2]; else r=0; reinterpret_cast<u8*>(obj)[0x54]=r; }
    // u64 at +0x58, hash 0x5330809b6
    h = 0x5330809b6ULL;
    e = (*plv==5)?(int*)FUN_7103733d50(*(void**)(plv+2),&h):DAT_710593a3a8;
    { int t=*e; long long r; if(t==7||t==2) r=*(long long*)(e+2); else if(t==3) r=(long long)(float)e[2]; else r=0; *reinterpret_cast<long long*>(reinterpret_cast<u8*>(obj)+0x58)=r; }
    // u8 at +0x60, hash 0xcf2e07d39
    h = 0xcf2e07d39ULL;
    e = (*plv==5)?(int*)FUN_7103733d50(*(void**)(plv+2),&h):DAT_710593a3a8;
    { int t=*e; u8 r; if(t==7||t==2) r=(u8)*(long long*)(e+2); else if(t==3) r=(u8)(long long)(float)e[2]; else r=0; reinterpret_cast<u8*>(obj)[0x60]=r; }
    // u8 at +0x61, hash 0xb24f5c28f
    h = 0xb24f5c28fULL;
    e = (*plv==5)?(int*)FUN_7103733d50(*(void**)(plv+2),&h):DAT_710593a3a8;
    { int t=*e; u8 r; if(t==7||t==2) r=(u8)*(long long*)(e+2); else if(t==3) r=(u8)(long long)(float)e[2]; else r=0; reinterpret_cast<u8*>(obj)[0x61]=r; }
    // u8 at +0x62, hash 0x853efed16
    h = 0x853efed16ULL;
    e = (*plv==5)?(int*)FUN_7103733d50(*(void**)(plv+2),&h):DAT_710593a3a8;
    { int t=*e; u8 r; if(t==7||t==2) r=(u8)*(long long*)(e+2); else if(t==3) r=(u8)(long long)(float)e[2]; else r=0; reinterpret_cast<u8*>(obj)[0x62]=r; }
    // bool at +0x63, hash 0x9dcd36686
    h = 0x9dcd36686ULL;
    e = (*plv==5)?(int*)FUN_7103733d50(*(void**)(plv+2),&h):DAT_710593a3a8;
    { int t=*e; u8 r=0; if(t==1) r=(0<(int)e[2])?1:0; else if(t==7||t==2) r=(*(long long*)(e+2)!=0)?1:0; else if(t==3) r=((float)e[2]!=0.0f)?1:0; else if(t!=0) r=1; reinterpret_cast<u8*>(obj)[0x63]=r; }
    // bool at +0x64, hash 0x787195a70
    h = 0x787195a70ULL;
    e = (*plv==5)?(int*)FUN_7103733d50(*(void**)(plv+2),&h):DAT_710593a3a8;
    { int t=*e; u8 r=0; if(t==1) r=(0<(int)e[2])?1:0; else if(t==7||t==2) r=(*(long long*)(e+2)!=0)?1:0; else if(t==3) r=((float)e[2]!=0.0f)?1:0; else if(t!=0) r=1; reinterpret_cast<u8*>(obj)[0x64]=r; }
    // bool at +0x65, hash 0xa9af00926
    h = 0xa9af00926ULL;
    e = (*plv==5)?(int*)FUN_7103733d50(*(void**)(plv+2),&h):DAT_710593a3a8;
    { int t=*e; u8 r=0; if(t==1) r=(0<(int)e[2])?1:0; else if(t==7||t==2) r=(*(long long*)(e+2)!=0)?1:0; else if(t==3) r=((float)e[2]!=0.0f)?1:0; else if(t!=0) r=1; reinterpret_cast<u8*>(obj)[0x65]=r; }
    // bool at +0x66, hash 0x9a101834b
    h = 0x9a101834bULL;
    e = (*plv==5)?(int*)FUN_7103733d50(*(void**)(plv+2),&h):DAT_710593a3a8;
    { int t=*e; u8 r=0; if(t==1) r=(0<(int)e[2])?1:0; else if(t==7||t==2) r=(*(long long*)(e+2)!=0)?1:0; else if(t==3) r=((float)e[2]!=0.0f)?1:0; else if(t!=0) r=1; reinterpret_cast<u8*>(obj)[0x66]=r; }
    // bool at +0x67, hash 0x7b892d86a
    h = 0x7b892d86aULL;
    e = (*plv==5)?(int*)FUN_7103733d50(*(void**)(plv+2),&h):DAT_710593a3a8;
    { int t=*e; u8 r=0; if(t==1) r=(0<(int)e[2])?1:0; else if(t==7||t==2) r=(*(long long*)(e+2)!=0)?1:0; else if(t==3) r=((float)e[2]!=0.0f)?1:0; else if(t!=0) r=1; reinterpret_cast<u8*>(obj)[0x67]=r; }
    // bool at +0x68, hash 0xeab4c75f2
    h = 0xeab4c75f2ULL;
    e = (*plv==5)?(int*)FUN_7103733d50(*(void**)(plv+2),&h):DAT_710593a3a8;
    { int t=*e; u8 r=0; if(t==1) r=(0<(int)e[2])?1:0; else if(t==7||t==2) r=(*(long long*)(e+2)!=0)?1:0; else if(t==3) r=((float)e[2]!=0.0f)?1:0; else if(t!=0) r=1; reinterpret_cast<u8*>(obj)[0x68]=r; }
    // bool at +0x69, hash 0x743de76b2
    h = 0x743de76b2ULL;
    e = (*plv==5)?(int*)FUN_7103733d50(*(void**)(plv+2),&h):DAT_710593a3a8;
    { int t=*e; u8 r=0; if(t==1) r=(0<(int)e[2])?1:0; else if(t==7||t==2) r=(*(long long*)(e+2)!=0)?1:0; else if(t==3) r=((float)e[2]!=0.0f)?1:0; else if(t!=0) r=1; reinterpret_cast<u8*>(obj)[0x69]=r; }
    // u8 at +0x6a, hash 0x97b20a494
    h = 0x97b20a494ULL;
    e = (*plv==5)?(int*)FUN_7103733d50(*(void**)(plv+2),&h):DAT_710593a3a8;
    { int t=*e; u8 r; if(t==7||t==2) r=(u8)*(long long*)(e+2); else if(t==3) r=(u8)(long long)(float)e[2]; else r=0; reinterpret_cast<u8*>(obj)[0x6a]=r; }
    // bool at +0x6b, hash 0x663cc6dd2
    h = 0x663cc6dd2ULL;
    e = (*plv==5)?(int*)FUN_7103733d50(*(void**)(plv+2),&h):DAT_710593a3a8;
    { int t=*e; u8 r=0; if(t==1) r=(0<(int)e[2])?1:0; else if(t==7||t==2) r=(*(long long*)(e+2)!=0)?1:0; else if(t==3) r=((float)e[2]!=0.0f)?1:0; else if(t!=0) r=1; reinterpret_cast<u8*>(obj)[0x6b]=r; }
    // bool at +0x6c, hash 0x8425d5268
    h = 0x8425d5268ULL;
    e = (*plv==5)?(int*)FUN_7103733d50(*(void**)(plv+2),&h):DAT_710593a3a8;
    { int t=*e; u8 r=0; if(t==1) r=(0<(int)e[2])?1:0; else if(t==7||t==2) r=(*(long long*)(e+2)!=0)?1:0; else if(t==3) r=((float)e[2]!=0.0f)?1:0; else if(t!=0) r=1; reinterpret_cast<u8*>(obj)[0x6c]=r; }
    // bool at +0x6d, hash 0x8ed2aff94
    h = 0x8ed2aff94ULL;
    e = (*plv==5)?(int*)FUN_7103733d50(*(void**)(plv+2),&h):DAT_710593a3a8;
    { int t=*e; u8 r=0; if(t==1) r=(0<(int)e[2])?1:0; else if(t==7||t==2) r=(*(long long*)(e+2)!=0)?1:0; else if(t==3) r=((float)e[2]!=0.0f)?1:0; else if(t!=0) r=1; reinterpret_cast<u8*>(obj)[0x6d]=r; }
    // bool at +0x6e, hash 0xac4c77c9d
    h = 0xac4c77c9dULL;
    e = (*plv==5)?(int*)FUN_7103733d50(*(void**)(plv+2),&h):DAT_710593a3a8;
    { int t=*e; u8 r=0; if(t==1) r=(0<(int)e[2])?1:0; else if(t==7||t==2) r=(*(long long*)(e+2)!=0)?1:0; else if(t==3) r=((float)e[2]!=0.0f)?1:0; else if(t!=0) r=1; reinterpret_cast<u8*>(obj)[0x6e]=r; }
    // bool at +0x70, hash 0x67d07d23f
    h = 0x67d07d23fULL;
    e = (*plv==5)?(int*)FUN_7103733d50(*(void**)(plv+2),&h):DAT_710593a3a8;
    { int t=*e; u8 r=0; if(t==1) r=(0<(int)e[2])?1:0; else if(t==7||t==2) r=(*(long long*)(e+2)!=0)?1:0; else if(t==3) r=((float)e[2]!=0.0f)?1:0; else if(t!=0) r=1; reinterpret_cast<u8*>(obj)[0x70]=r; }
    // u8 at +0x71, hash 0x790bf1510
    h = 0x790bf1510ULL;
    e = (*plv==5)?(int*)FUN_7103733d50(*(void**)(plv+2),&h):DAT_710593a3a8;
    { int t=*e; u8 r; if(t==7||t==2) r=(u8)*(long long*)(e+2); else if(t==3) r=(u8)(long long)(float)e[2]; else r=0; reinterpret_cast<u8*>(obj)[0x71]=r; }
    // bool at +0x72, hash 0xc6ff56437
    h = 0xc6ff56437ULL;
    e = (*plv==5)?(int*)FUN_7103733d50(*(void**)(plv+2),&h):DAT_710593a3a8;
    { int t=*e; u8 r=0; if(t==1) r=(0<(int)e[2])?1:0; else if(t==7||t==2) r=(*(long long*)(e+2)!=0)?1:0; else if(t==3) r=((float)e[2]!=0.0f)?1:0; else if(t!=0) r=1; reinterpret_cast<u8*>(obj)[0x72]=r; }
    // u8 at +0x73, hash 0xbf1b2d611
    h = 0xbf1b2d611ULL;
    e = (*plv==5)?(int*)FUN_7103733d50(*(void**)(plv+2),&h):DAT_710593a3a8;
    { int t=*e; u8 r; if(t==7||t==2) r=(u8)*(long long*)(e+2); else if(t==3) r=(u8)(long long)(float)e[2]; else r=0; reinterpret_cast<u8*>(obj)[0x73]=r; }
    // u16 at +0x74, hash 0xbf8c10684
    h = 0xbf8c10684ULL;
    e = (*plv==5)?(int*)FUN_7103733d50(*(void**)(plv+2),&h):DAT_710593a3a8;
    { int t=*e; u16 r; if(t==7||t==2) r=(u16)*(long long*)(e+2); else if(t==3) r=(u16)(long long)(float)e[2]; else r=0; *reinterpret_cast<u16*>(reinterpret_cast<u8*>(obj)+0x74)=r; }
    // u8 at +0x76, hash 0xd61b7c0ad
    h = 0xd61b7c0adULL;
    e = (*plv==5)?(int*)FUN_7103733d50(*(void**)(plv+2),&h):DAT_710593a3a8;
    { int t=*e; u8 r; if(t==7||t==2) r=(u8)*(long long*)(e+2); else if(t==3) r=(u8)(long long)(float)e[2]; else r=0; reinterpret_cast<u8*>(obj)[0x76]=r; }
    // s32 at +0x78, hash 0x1196f0150a
    h = 0x1196f0150aULL;
    e = (*plv==5)?(int*)FUN_7103733d50(*(void**)(plv+2),&h):DAT_710593a3a8;
    { int t=*e; u32 r; if(t==7||t==2) r=(u32)*(long long*)(e+2); else if(t==3) r=(u32)(long long)(float)e[2]; else r=0; *reinterpret_cast<u32*>(reinterpret_cast<u8*>(obj)+0x78)=r; }
    // bool at +0x7c, hash 0xf6d043e5f
    h = 0xf6d043e5fULL;
    e = (*plv==5)?(int*)FUN_7103733d50(*(void**)(plv+2),&h):DAT_710593a3a8;
    { int t=*e; u8 r=0; if(t==1) r=(0<(int)e[2])?1:0; else if(t==7||t==2) r=(*(long long*)(e+2)!=0)?1:0; else if(t==3) r=((float)e[2]!=0.0f)?1:0; else if(t!=0) r=1; reinterpret_cast<u8*>(obj)[0x7c]=r; }
    // bool at +0x7d, hash 0x1038fdddbe
    h = 0x1038fdddbEULL;
    e = (*plv==5)?(int*)FUN_7103733d50(*(void**)(plv+2),&h):DAT_710593a3a8;
    { int t=*e; u8 r=0; if(t==1) r=(0<(int)e[2])?1:0; else if(t==7||t==2) r=(*(long long*)(e+2)!=0)?1:0; else if(t==3) r=((float)e[2]!=0.0f)?1:0; else if(t!=0) r=1; reinterpret_cast<u8*>(obj)[0x7d]=r; }
    // u8 at +0x7e, hash 0x137eed1b76
    h = 0x137eed1b76ULL;
    e = (*plv==5)?(int*)FUN_7103733d50(*(void**)(plv+2),&h):DAT_710593a3a8;
    { int t=*e; u8 r; if(t==7||t==2) r=(u8)*(long long*)(e+2); else if(t==3) r=(u8)(long long)(float)e[2]; else r=0; reinterpret_cast<u8*>(obj)[0x7e]=r; }
    // u8 at +0x7f, hash 0x13fb6e1fed
    h = 0x13fb6e1fedULL;
    e = (*plv==5)?(int*)FUN_7103733d50(*(void**)(plv+2),&h):DAT_710593a3a8;
    { int t=*e; u8 r; if(t==7||t==2) r=(u8)*(long long*)(e+2); else if(t==3) r=(u8)(long long)(float)e[2]; else r=0; reinterpret_cast<u8*>(obj)[0x7f]=r; }
    // bool at +0x80, hash 0xc3afbe95f
    h = 0xc3afbe95fULL;
    e = (*plv==5)?(int*)FUN_7103733d50(*(void**)(plv+2),&h):DAT_710593a3a8;
    { int t=*e; u8 r=0; if(t==1) r=(0<(int)e[2])?1:0; else if(t==7||t==2) r=(*(long long*)(e+2)!=0)?1:0; else if(t==3) r=((float)e[2]!=0.0f)?1:0; else if(t!=0) r=1; reinterpret_cast<u8*>(obj)[0x80]=r; }
    // bool at +0x81, hash 0x12bd00ce2f
    h = 0x12bd00ce2fULL;
    e = (*plv==5)?(int*)FUN_7103733d50(*(void**)(plv+2),&h):DAT_710593a3a8;
    { int t=*e; u8 r=0; if(t==1) r=(0<(int)e[2])?1:0; else if(t==7||t==2) r=(*(long long*)(e+2)!=0)?1:0; else if(t==3) r=((float)e[2]!=0.0f)?1:0; else if(t!=0) r=1; reinterpret_cast<u8*>(obj)[0x81]=r; }
    // u64 at +0x88, hash 0x10e24af9d6
    h = 0x10e24af9d6ULL;
    e = (*plv==5)?(int*)FUN_7103733d50(*(void**)(plv+2),&h):DAT_710593a3a8;
    { int t=*e; long long r; if(t==7||t==2) r=*(long long*)(e+2); else if(t==3) r=(long long)(float)e[2]; else r=0; *reinterpret_cast<long long*>(reinterpret_cast<u8*>(obj)+0x88)=r; }
    // sub-table 0x12456b491a → f32 x at +0x90, f32 y at +0x94
    h = 0x12456b491aULL;
    sub = (*plv==5)?(int*)FUN_7103733d50(*(void**)(plv+2),&h):DAT_710593a3a8;
    h = 0x18cdc1683ULL;
    e = (*sub==5)?(int*)FUN_7103733d50(*(void**)(sub+2),&h):DAT_710593a3a8;
    { int t=*e; if(t==7||t==2) v=(float)*(long long*)(e+2); else if(t==3) v=(float)e[2]; else v=0.0f; *reinterpret_cast<float*>(reinterpret_cast<u8*>(obj)+0x90)=v; }
    h = 0x12456b491aULL;
    sub = (*plv==5)?(int*)FUN_7103733d50(*(void**)(plv+2),&h):DAT_710593a3a8;
    h = 0x1fbdb2615ULL;
    e = (*sub==5)?(int*)FUN_7103733d50(*(void**)(sub+2),&h):DAT_710593a3a8;
    { int t=*e; if(t==7||t==2) v=(float)*(long long*)(e+2); else if(t==3) v=(float)e[2]; else v=0.0f; *reinterpret_cast<float*>(reinterpret_cast<u8*>(obj)+0x94)=v; }
    // s32 at +0xa0, hash 0x112ec3305d
    h = 0x112ec3305dULL;
    e = (*plv==5)?(int*)FUN_7103733d50(*(void**)(plv+2),&h):DAT_710593a3a8;
    { int t=*e; u32 r; if(t==7||t==2) r=(u32)*(long long*)(e+2); else if(t==3) r=(u32)(long long)(float)e[2]; else r=0; *reinterpret_cast<u32*>(reinterpret_cast<u8*>(obj)+0xa0)=r; }
    // bool at +0xa4, hash 0x16846ecfc7
    h = 0x16846ecfc7ULL;
    e = (*plv==5)?(int*)FUN_7103733d50(*(void**)(plv+2),&h):DAT_710593a3a8;
    { int t=*e; u8 r=0; if(t==1) r=(0<(int)e[2])?1:0; else if(t==7||t==2) r=(*(long long*)(e+2)!=0)?1:0; else if(t==3) r=((float)e[2]!=0.0f)?1:0; else if(t!=0) r=1; reinterpret_cast<u8*>(obj)[0xa4]=r; }
    // bool at +0xa6, hash 0x19b408f9eb
    h = 0x19b408f9ebULL;
    e = (*plv==5)?(int*)FUN_7103733d50(*(void**)(plv+2),&h):DAT_710593a3a8;
    { int t=*e; u8 r=0; if(t==1) r=(0<(int)e[2])?1:0; else if(t==7||t==2) r=(*(long long*)(e+2)!=0)?1:0; else if(t==3) r=((float)e[2]!=0.0f)?1:0; else if(t!=0) r=1; reinterpret_cast<u8*>(obj)[0xa6]=r; }
}

// 7101feecd0: allocate L2CValue table, fill via FUN_7101feeda0, return as LargeRet
#ifdef MATCHING_HACK_NX_CLANG
__attribute__((naked))
LargeRet AttackData__store_l2c_table_impl(AttackData* obj) {
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
        "bl FUN_7101feeda0\n"
        "add x0, sp, #0x8\n"
        "bl FUN_7103733f20\n"
        "ldp x29, x30, [sp, #0x30]\n"
        "ldp x20, x19, [sp, #0x20]\n"
        "add sp, sp, #0x40\n"
        "ret\n"
    );
}
#endif

// 7101ff0280: fill trampoline — mov x2,x1; mov x1,x0; mov x0,x8; b FUN_7101feeda0
#ifdef MATCHING_HACK_NX_CLANG
__attribute__((naked))
void AttackData__store_l2c_table_impl_7101ff0280(AttackData* obj, void* lv) {
    asm(
        "mov x2, x1\n"
        "mov x1, x0\n"
        "mov x0, x8\n"
        "b FUN_7101feeda0\n"
    );
}
#endif

} // namespace app::lua_bind
