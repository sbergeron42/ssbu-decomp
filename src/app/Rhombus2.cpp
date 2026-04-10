#include "types.h"
#include "app/Rhombus2.h"

using app::Rhombus2;
struct LargeRet { u64 a, b, c; };

extern "C" void* FUN_7103733d50(void*, void*);
extern int DAT_710593a3a8[4];

namespace app::lua_bind {

// 71020f0250 (1280 bytes): load fields from L2CValue table -- external branches, won't byte-match
// Rhombus2 has 4 Vec2 sub-tables (each with x,y sub-fields 0x18cdc1683, 0x1fbdb2615)
void Rhombus2__load_from_l2c_table_impl(Rhombus2* obj, void* lv_in) {
    int* plv = reinterpret_cast<int*>(lv_in);
    int* e; int* sub; float v;
    // sub-table 0x24394ee70 → f32 x at +0, f32 y at +4
    u64 h = 0x24394ee70ULL;
    sub = (*plv==5)?(int*)FUN_7103733d50(*(void**)(plv+2),&h):DAT_710593a3a8;
    h = 0x18cdc1683ULL;
    e = (*sub==5)?(int*)FUN_7103733d50(*(void**)(sub+2),&h):DAT_710593a3a8;
    { int t=*e; if(t==7||t==2) v=(float)*(long long*)(e+2); else if(t==3) v=*reinterpret_cast<float*>(e+2); else v=0.0f; obj->corner0_x=v; }
    h = 0x24394ee70ULL;
    sub = (*plv==5)?(int*)FUN_7103733d50(*(void**)(plv+2),&h):DAT_710593a3a8;
    h = 0x1fbdb2615ULL;
    e = (*sub==5)?(int*)FUN_7103733d50(*(void**)(sub+2),&h):DAT_710593a3a8;
    { int t=*e; if(t==7||t==2) v=(float)*(long long*)(e+2); else if(t==3) v=*reinterpret_cast<float*>(e+2); else v=0.0f; obj->corner0_y=v; }
    // sub-table 0x41cff903b → f32 x at +0x10, f32 y at +0x14
    h = 0x41cff903bULL;
    sub = (*plv==5)?(int*)FUN_7103733d50(*(void**)(plv+2),&h):DAT_710593a3a8;
    h = 0x18cdc1683ULL;
    e = (*sub==5)?(int*)FUN_7103733d50(*(void**)(sub+2),&h):DAT_710593a3a8;
    { int t=*e; if(t==7||t==2) v=(float)*(long long*)(e+2); else if(t==3) v=*reinterpret_cast<float*>(e+2); else v=0.0f; obj->corner1_x=v; }
    h = 0x41cff903bULL;
    sub = (*plv==5)?(int*)FUN_7103733d50(*(void**)(plv+2),&h):DAT_710593a3a8;
    h = 0x1fbdb2615ULL;
    e = (*sub==5)?(int*)FUN_7103733d50(*(void**)(sub+2),&h):DAT_710593a3a8;
    { int t=*e; if(t==7||t==2) v=(float)*(long long*)(e+2); else if(t==3) v=*reinterpret_cast<float*>(e+2); else v=0.0f; obj->corner1_y=v; }
    // sub-table 0x47a67e768 → f32 x at +0x20, f32 y at +0x24
    h = 0x47a67e768ULL;
    sub = (*plv==5)?(int*)FUN_7103733d50(*(void**)(plv+2),&h):DAT_710593a3a8;
    h = 0x18cdc1683ULL;
    e = (*sub==5)?(int*)FUN_7103733d50(*(void**)(sub+2),&h):DAT_710593a3a8;
    { int t=*e; if(t==7||t==2) v=(float)*(long long*)(e+2); else if(t==3) v=*reinterpret_cast<float*>(e+2); else v=0.0f; obj->corner2_x=v; }
    h = 0x47a67e768ULL;
    sub = (*plv==5)?(int*)FUN_7103733d50(*(void**)(plv+2),&h):DAT_710593a3a8;
    h = 0x1fbdb2615ULL;
    e = (*sub==5)?(int*)FUN_7103733d50(*(void**)(sub+2),&h):DAT_710593a3a8;
    { int t=*e; if(t==7||t==2) v=(float)*(long long*)(e+2); else if(t==3) v=*reinterpret_cast<float*>(e+2); else v=0.0f; obj->corner2_y=v; }
    // sub-table 0x5b4ca7514 → f32 x at +0x30, f32 y at +0x34
    h = 0x5b4ca7514ULL;
    sub = (*plv==5)?(int*)FUN_7103733d50(*(void**)(plv+2),&h):DAT_710593a3a8;
    h = 0x18cdc1683ULL;
    e = (*sub==5)?(int*)FUN_7103733d50(*(void**)(sub+2),&h):DAT_710593a3a8;
    { int t=*e; if(t==7||t==2) v=(float)*(long long*)(e+2); else if(t==3) v=*reinterpret_cast<float*>(e+2); else v=0.0f; obj->corner3_x=v; }
    h = 0x5b4ca7514ULL;
    sub = (*plv==5)?(int*)FUN_7103733d50(*(void**)(plv+2),&h):DAT_710593a3a8;
    h = 0x1fbdb2615ULL;
    e = (*sub==5)?(int*)FUN_7103733d50(*(void**)(sub+2),&h):DAT_710593a3a8;
    { int t=*e; if(t==7||t==2) v=(float)*(long long*)(e+2); else if(t==3) v=*reinterpret_cast<float*>(e+2); else v=0.0f; obj->corner3_y=v; }
}

} // namespace app::lua_bind

