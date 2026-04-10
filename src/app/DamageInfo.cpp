#include "types.h"
#include "app/DamageInfo.h"

using app::DamageInfo;
struct LargeRet { u64 a, b, c; };

extern "C" void* treeMapFindOrInsert_7103733d50(void*, void*);
extern int DAT_710593a3a8[4];

namespace app::lua_bind {

// 71020112a0 (2096 bytes): load fields from L2CValue table -- external branches, won't byte-match
void DamageInfo__load_from_l2c_table_impl(DamageInfo* obj, void* lv_in) {
    int* plv = reinterpret_cast<int*>(lv_in);
    int* e; int* sub; float v;
    // f32 at +0, hash 0x76dc346cf
    u64 h = 0x76dc346cfULL;
    e = (*plv==5)?(int*)treeMapFindOrInsert_7103733d50(*(void**)(plv+2),&h):DAT_710593a3a8;
    { int t=*e; if(t==7||t==2) v=(float)*(long long*)(e+2); else if(t==3) v=*reinterpret_cast<float*>(e+2); else v=0.0f; obj->field_0x00=v; }
    // f32 at +4, hash 0xb9ea8580a
    h = 0xb9ea8580aULL;
    e = (*plv==5)?(int*)treeMapFindOrInsert_7103733d50(*(void**)(plv+2),&h):DAT_710593a3a8;
    { int t=*e; if(t==7||t==2) v=(float)*(long long*)(e+2); else if(t==3) v=*reinterpret_cast<float*>(e+2); else v=0.0f; obj->field_0x04=v; }
    // f32 at +8, hash 0x144a6e9b87
    h = 0x144a6e9b87ULL;
    e = (*plv==5)?(int*)treeMapFindOrInsert_7103733d50(*(void**)(plv+2),&h):DAT_710593a3a8;
    { int t=*e; if(t==7||t==2) v=(float)*(long long*)(e+2); else if(t==3) v=*reinterpret_cast<float*>(e+2); else v=0.0f; obj->field_0x08=v; }
    // f32 at +0xc, hash 0xa89c09dd2
    h = 0xa89c09dd2ULL;
    e = (*plv==5)?(int*)treeMapFindOrInsert_7103733d50(*(void**)(plv+2),&h):DAT_710593a3a8;
    { int t=*e; if(t==7||t==2) v=(float)*(long long*)(e+2); else if(t==3) v=*reinterpret_cast<float*>(e+2); else v=0.0f; obj->field_0x0c=v; }
    // f32 at +0x10, hash 0xdc56470f9
    h = 0xdc56470f9ULL;
    e = (*plv==5)?(int*)treeMapFindOrInsert_7103733d50(*(void**)(plv+2),&h):DAT_710593a3a8;
    { int t=*e; if(t==7||t==2) v=(float)*(long long*)(e+2); else if(t==3) v=*reinterpret_cast<float*>(e+2); else v=0.0f; obj->field_0x10=v; }
    // f32 at +0x160, hash 0xa66ec16de
    h = 0xa66ec16deULL;
    e = (*plv==5)?(int*)treeMapFindOrInsert_7103733d50(*(void**)(plv+2),&h):DAT_710593a3a8;
    { int t=*e; if(t==7||t==2) v=(float)*(long long*)(e+2); else if(t==3) v=*reinterpret_cast<float*>(e+2); else v=0.0f; obj->field_0x160=v; }
    // sub-table 0xb012d5420 → f32 x at +0x170, f32 y at +0x174, u32 at +0x178
    h = 0xb012d5420ULL;
    sub = (*plv==5)?(int*)treeMapFindOrInsert_7103733d50(*(void**)(plv+2),&h):DAT_710593a3a8;
    h = 0x18cdc1683ULL;
    e = (*sub==5)?(int*)treeMapFindOrInsert_7103733d50(*(void**)(sub+2),&h):DAT_710593a3a8;
    { int t=*e; if(t==7||t==2) v=(float)*(long long*)(e+2); else if(t==3) v=*reinterpret_cast<float*>(e+2); else v=0.0f; obj->pos0_x=v; }
    h = 0xb012d5420ULL;
    sub = (*plv==5)?(int*)treeMapFindOrInsert_7103733d50(*(void**)(plv+2),&h):DAT_710593a3a8;
    h = 0x1fbdb2615ULL;
    e = (*sub==5)?(int*)treeMapFindOrInsert_7103733d50(*(void**)(sub+2),&h):DAT_710593a3a8;
    { int t=*e; if(t==7||t==2) v=(float)*(long long*)(e+2); else if(t==3) v=*reinterpret_cast<float*>(e+2); else v=0.0f; obj->pos0_y=v; }
    h = 0xb012d5420ULL;
    sub = (*plv==5)?(int*)treeMapFindOrInsert_7103733d50(*(void**)(plv+2),&h):DAT_710593a3a8;
    h = 0x162d277afULL;
    e = (*sub==5)?(int*)treeMapFindOrInsert_7103733d50(*(void**)(sub+2),&h):DAT_710593a3a8;
    { int t=*e; u32 r; if(t==7||t==2) r=(u32)(float)*(long long*)(e+2); else if(t==3) r=(u32)e[2]; else r=0; obj->pos0_kind=r; }
    // sub-table 0xd7ab45aa3 → f32 x at +0x180, f32 y at +0x184
    h = 0xd7ab45aa3ULL;
    sub = (*plv==5)?(int*)treeMapFindOrInsert_7103733d50(*(void**)(plv+2),&h):DAT_710593a3a8;
    h = 0x18cdc1683ULL;
    e = (*sub==5)?(int*)treeMapFindOrInsert_7103733d50(*(void**)(sub+2),&h):DAT_710593a3a8;
    { int t=*e; if(t==7||t==2) v=(float)*(long long*)(e+2); else if(t==3) v=*reinterpret_cast<float*>(e+2); else v=0.0f; obj->pos1_x=v; }
    h = 0xd7ab45aa3ULL;
    sub = (*plv==5)?(int*)treeMapFindOrInsert_7103733d50(*(void**)(plv+2),&h):DAT_710593a3a8;
    h = 0x1fbdb2615ULL;
    e = (*sub==5)?(int*)treeMapFindOrInsert_7103733d50(*(void**)(sub+2),&h):DAT_710593a3a8;
    { int t=*e; if(t==7||t==2) v=(float)*(long long*)(e+2); else if(t==3) v=*reinterpret_cast<float*>(e+2); else v=0.0f; obj->pos1_y=v; }
    // f32 at +0x190, hash 0xfbf11fc14
    h = 0xfbf11fc14ULL;
    e = (*plv==5)?(int*)treeMapFindOrInsert_7103733d50(*(void**)(plv+2),&h):DAT_710593a3a8;
    { int t=*e; if(t==7||t==2) v=(float)*(long long*)(e+2); else if(t==3) v=*reinterpret_cast<float*>(e+2); else v=0.0f; obj->field_0x190=v; }
    // s32 at +0x194, hash 0x10d723eebb
    h = 0x10d723eebbULL;
    e = (*plv==5)?(int*)treeMapFindOrInsert_7103733d50(*(void**)(plv+2),&h):DAT_710593a3a8;
    { int t=*e; u32 r; if(t==7||t==2) r=(u32)*(long long*)(e+2); else if(t==3) r=(u32)(long long)*reinterpret_cast<float*>(e+2); else r=0; obj->field_0x194=r; }
    // f32 at +0x198, hash 0xc1dbea6f7
    h = 0xc1dbea6f7ULL;
    e = (*plv==5)?(int*)treeMapFindOrInsert_7103733d50(*(void**)(plv+2),&h):DAT_710593a3a8;
    { int t=*e; if(t==7||t==2) v=(float)*(long long*)(e+2); else if(t==3) v=*reinterpret_cast<float*>(e+2); else v=0.0f; obj->field_0x198=v; }
    // bool at +0x19c, hash 0xf5fbadc81
    h = 0xf5fbadc81ULL;
    e = (*plv==5)?(int*)treeMapFindOrInsert_7103733d50(*(void**)(plv+2),&h):DAT_710593a3a8;
    { int t=*e; u8 r=0; if(t==1) r=(0<(int)e[2])?1:0; else if(t==7||t==2) r=(*(long long*)(e+2)!=0)?1:0; else if(t==3) r=((float)e[2]!=0.0f)?1:0; else if(t!=0) r=1; obj->flag_0x19c=r; }
    // bool at +0x19d, hash 0x1a70c41677
    h = 0x1a70c41677ULL;
    e = (*plv==5)?(int*)treeMapFindOrInsert_7103733d50(*(void**)(plv+2),&h):DAT_710593a3a8;
    { int t=*e; u8 r=0; if(t==1) r=(0<(int)e[2])?1:0; else if(t==7||t==2) r=(*(long long*)(e+2)!=0)?1:0; else if(t==3) r=((float)e[2]!=0.0f)?1:0; else if(t!=0) r=1; obj->flag_0x19d=r; }
}

} // namespace app::lua_bind
