#include "types.h"
#include "app/Circle.h"

using app::Circle;
struct LargeRet { u64 a, b, c; };

extern "C" void* treeMapFindOrInsert_7103733d50(void*, void*);
extern int DAT_710593a3a8[4];

namespace app::lua_bind {

// 71020f1980 (480 bytes): load fields from L2CValue table -- external branches, won't byte-match
void Circle__load_from_l2c_table_impl(Circle* obj, void* lv_in) {
    int* plv = reinterpret_cast<int*>(lv_in);
    int* e; int* sub; float v;
    // sub-table 0x640f0eb24 → f32 x at +0, f32 y at +4
    u64 h = 0x640f0eb24ULL;
    sub = (*plv==5)?(int*)treeMapFindOrInsert_7103733d50(*(void**)(plv+2),&h):DAT_710593a3a8;
    h = 0x18cdc1683ULL;
    e = (*sub==5)?(int*)treeMapFindOrInsert_7103733d50(*(void**)(sub+2),&h):DAT_710593a3a8;
    { int t=*e; if(t==7||t==2) v=(float)*(long long*)(e+2); else if(t==3) v=*reinterpret_cast<float*>(e+2); else v=0.0f; obj->pos_x=v; }
    h = 0x640f0eb24ULL;
    sub = (*plv==5)?(int*)treeMapFindOrInsert_7103733d50(*(void**)(plv+2),&h):DAT_710593a3a8;
    h = 0x1fbdb2615ULL;
    e = (*sub==5)?(int*)treeMapFindOrInsert_7103733d50(*(void**)(sub+2),&h):DAT_710593a3a8;
    { int t=*e; if(t==7||t==2) v=(float)*(long long*)(e+2); else if(t==3) v=*reinterpret_cast<float*>(e+2); else v=0.0f; obj->pos_y=v; }
    // f32 at +0x10, hash 0x63b7c6e5a
    h = 0x63b7c6e5aULL;
    e = (*plv==5)?(int*)treeMapFindOrInsert_7103733d50(*(void**)(plv+2),&h):DAT_710593a3a8;
    { int t=*e; if(t==7||t==2) v=(float)*(long long*)(e+2); else if(t==3) v=*reinterpret_cast<float*>(e+2); else v=0.0f; obj->size=v; }
}

} // namespace app::lua_bind
