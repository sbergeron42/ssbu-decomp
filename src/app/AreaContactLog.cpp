#include "types.h"
#include "app/AreaContactLog.h"

using app::AreaContactLog;
struct LargeRet { u64 a, b, c; };

// External helpers for L2CValue serialization (external b branches -- won't byte-match)
extern "C" void* treeMapFindOrInsert_7103733d50(void*, void*);
extern int DAT_710593a3a8[4];

namespace app::lua_bind {

// 7101fca860 (1120 bytes): load fields from L2CValue table -- external branches, won't byte-match
void AreaContactLog__load_from_l2c_table_impl(AreaContactLog* obj, void* lv_in) {
    int* plv = reinterpret_cast<int*>(lv_in);
    int* e; float v;
    // s32 at +0, hash 0xbad544942
    u64 h = 0xbad544942ULL;
    e = (*plv==5)?(int*)treeMapFindOrInsert_7103733d50(*(void**)(plv+2),&h):DAT_710593a3a8;
    { int t=*e; u32 r; if(t==7||t==2) r=(u32)*(long long*)(e+2); else if(t==3) r=(u32)(long long)*reinterpret_cast<float*>(e+2); else r=0; obj->field_0x00=r; }
    // s32 at +4, hash 0xa8d12e98e
    h = 0xa8d12e98eULL;
    e = (*plv==5)?(int*)treeMapFindOrInsert_7103733d50(*(void**)(plv+2),&h):DAT_710593a3a8;
    { int t=*e; u32 r; if(t==7||t==2) r=(u32)*(long long*)(e+2); else if(t==3) r=(u32)(long long)*reinterpret_cast<float*>(e+2); else r=0; obj->field_0x04=r; }
    // s32 at +8, hash 0xff72be395
    h = 0xff72be395ULL;
    e = (*plv==5)?(int*)treeMapFindOrInsert_7103733d50(*(void**)(plv+2),&h):DAT_710593a3a8;
    { int t=*e; u32 r; if(t==7||t==2) r=(u32)*(long long*)(e+2); else if(t==3) r=(u32)(long long)*reinterpret_cast<float*>(e+2); else r=0; obj->field_0x08=r; }
    // u8 at +0xc, hash 0x10f1076ffb
    h = 0x10f1076ffbULL;
    e = (*plv==5)?(int*)treeMapFindOrInsert_7103733d50(*(void**)(plv+2),&h):DAT_710593a3a8;
    { int t=*e; u8 r; if(t==7||t==2) r=(u8)*(long long*)(e+2); else if(t==3) r=(u8)(long long)*reinterpret_cast<float*>(e+2); else r=0; obj->field_0x0c=r; }
    // u8 at +0xd, hash 0xdcbbfb223
    h = 0xdcbbfb223ULL;
    e = (*plv==5)?(int*)treeMapFindOrInsert_7103733d50(*(void**)(plv+2),&h):DAT_710593a3a8;
    { int t=*e; u8 r; if(t==7||t==2) r=(u8)*(long long*)(e+2); else if(t==3) r=(u8)(long long)*reinterpret_cast<float*>(e+2); else r=0; obj->field_0x0d=r; }
    // u8 at +0xe, hash 0x12731fd2d5
    h = 0x12731fd2d5ULL;
    e = (*plv==5)?(int*)treeMapFindOrInsert_7103733d50(*(void**)(plv+2),&h):DAT_710593a3a8;
    { int t=*e; u8 r; if(t==7||t==2) r=(u8)*(long long*)(e+2); else if(t==3) r=(u8)(long long)*reinterpret_cast<float*>(e+2); else r=0; obj->field_0x0e=r; }
    // u8 at +0xf, hash 0x11f40cadd0
    h = 0x11f40cadd0ULL;
    e = (*plv==5)?(int*)treeMapFindOrInsert_7103733d50(*(void**)(plv+2),&h):DAT_710593a3a8;
    { int t=*e; u8 r; if(t==7||t==2) r=(u8)*(long long*)(e+2); else if(t==3) r=(u8)(long long)*reinterpret_cast<float*>(e+2); else r=0; obj->field_0x0f=r; }
    // sub-table (hash 0x9b37582c4) → f32 at +0x10, f32 at +0x14
    h = 0x9b37582c4ULL;
    int* sub = (*plv==5)?(int*)treeMapFindOrInsert_7103733d50(*(void**)(plv+2),&h):DAT_710593a3a8;
    // sub-field 0x18cdc1683 → f32 at +0x10
    h = 0x18cdc1683ULL;
    e = (*sub==5)?(int*)treeMapFindOrInsert_7103733d50(*(void**)(sub+2),&h):DAT_710593a3a8;
    { int t=*e; if(t==7||t==2) v=(float)*(long long*)(e+2); else if(t==3) v=*reinterpret_cast<float*>(e+2); else v=0.0f; obj->pos_x=v; }
    // sub-field 0x1fbdb2615 → f32 at +0x14
    h = 0x9b37582c4ULL;
    sub = (*plv==5)?(int*)treeMapFindOrInsert_7103733d50(*(void**)(plv+2),&h):DAT_710593a3a8;
    h = 0x1fbdb2615ULL;
    e = (*sub==5)?(int*)treeMapFindOrInsert_7103733d50(*(void**)(sub+2),&h):DAT_710593a3a8;
    { int t=*e; if(t==7||t==2) v=(float)*(long long*)(e+2); else if(t==3) v=*reinterpret_cast<float*>(e+2); else v=0.0f; obj->pos_y=v; }
}

} // namespace app::lua_bind
