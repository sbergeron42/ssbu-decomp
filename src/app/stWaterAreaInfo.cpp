#include "types.h"
#include "app/stWaterAreaInfo.h"

using app::stWaterAreaInfo;
struct LargeRet { u64 a, b, c; };

extern "C" void* FUN_7103733d50(void*, void*);
extern int DAT_710593a3a8[4];

namespace app::lua_bind {

// 71020d3e40 (512 bytes): load fields from L2CValue table -- external branches, won't byte-match
void stWaterAreaInfo__load_from_l2c_table_impl(stWaterAreaInfo* obj, void* lv_in) {
    int* plv = reinterpret_cast<int*>(lv_in);
    int* e; float v;
    // u16 at +0, hash 0xce3c92dd1
    u64 h = 0xce3c92dd1ULL;
    e = (*plv==5)?(int*)FUN_7103733d50(*(void**)(plv+2),&h):DAT_710593a3a8;
    { int t=*e; u16 r; if(t==7||t==2) r=(u16)*(long long*)(e+2); else if(t==3) r=(u16)(long long)*reinterpret_cast<float*>(e+2); else r=0; obj->field_0x00=r; }
    // f32 at +4, hash 0x55ccf01c8
    h = 0x55ccf01c8ULL;
    e = (*plv==5)?(int*)FUN_7103733d50(*(void**)(plv+2),&h):DAT_710593a3a8;
    { int t=*e; if(t==7||t==2) v=(float)*(long long*)(e+2); else if(t==3) v=*reinterpret_cast<float*>(e+2); else v=0.0f; obj->field_0x04=v; }
    // f32 at +8, hash 0x7c71fe301
    h = 0x7c71fe301ULL;
    e = (*plv==5)?(int*)FUN_7103733d50(*(void**)(plv+2),&h):DAT_710593a3a8;
    { int t=*e; if(t==7||t==2) v=(float)*(long long*)(e+2); else if(t==3) v=*reinterpret_cast<float*>(e+2); else v=0.0f; obj->field_0x08=v; }
    // bool at +0xc, hash 0x999e35339
    h = 0x999e35339ULL;
    e = (*plv==5)?(int*)FUN_7103733d50(*(void**)(plv+2),&h):DAT_710593a3a8;
    { int t=*e; u8 r=0; if(t==1) r=(0<(int)e[2])?1:0; else if(t==7||t==2) r=(*(long long*)(e+2)!=0)?1:0; else if(t==3) r=((float)e[2]!=0.0f)?1:0; else if(t!=0) r=1; obj->is_active=r; }
}

} // namespace app::lua_bind

