#include "types.h"

struct stWaterAreaInfo;
struct LargeRet { u64 a, b, c; };

extern "C" void* FUN_7103733d50(void*, void*);
extern int DAT_710593a3a8[4];

namespace app::lua_bind {

// 71020d3e40 (512 bytes): load fields from L2CValue table — external branches, won't byte-match
void stWaterAreaInfo__load_from_l2c_table_impl(stWaterAreaInfo* obj, void* lv_in) {
    int* plv = reinterpret_cast<int*>(lv_in);
    int* e; float v;
    // u16 at +0, hash 0xce3c92dd1
    u64 h = 0xce3c92dd1ULL;
    e = (*plv==5)?(int*)FUN_7103733d50(*(void**)(plv+2),&h):DAT_710593a3a8;
    { int t=*e; u16 r; if(t==7||t==2) r=(u16)*(long long*)(e+2); else if(t==3) r=(u16)(long long)(float)e[2]; else r=0; *reinterpret_cast<u16*>(reinterpret_cast<u8*>(obj)+0)=r; }
    // f32 at +4, hash 0x55ccf01c8
    h = 0x55ccf01c8ULL;
    e = (*plv==5)?(int*)FUN_7103733d50(*(void**)(plv+2),&h):DAT_710593a3a8;
    { int t=*e; if(t==7||t==2) v=(float)*(long long*)(e+2); else if(t==3) v=(float)e[2]; else v=0.0f; *reinterpret_cast<float*>(reinterpret_cast<u8*>(obj)+4)=v; }
    // f32 at +8, hash 0x7c71fe301
    h = 0x7c71fe301ULL;
    e = (*plv==5)?(int*)FUN_7103733d50(*(void**)(plv+2),&h):DAT_710593a3a8;
    { int t=*e; if(t==7||t==2) v=(float)*(long long*)(e+2); else if(t==3) v=(float)e[2]; else v=0.0f; *reinterpret_cast<float*>(reinterpret_cast<u8*>(obj)+8)=v; }
    // bool at +0xc, hash 0x999e35339
    h = 0x999e35339ULL;
    e = (*plv==5)?(int*)FUN_7103733d50(*(void**)(plv+2),&h):DAT_710593a3a8;
    { int t=*e; u8 r=0; if(t==1) r=(0<(int)e[2])?1:0; else if(t==7||t==2) r=(*(long long*)(e+2)!=0)?1:0; else if(t==3) r=((float)e[2]!=0.0f)?1:0; else if(t!=0) r=1; reinterpret_cast<u8*>(obj)[0xc]=r; }
}

// 71020d4040 (208 bytes): allocate L2CValue table, return as LargeRet
LargeRet stWaterAreaInfo__store_l2c_table_impl(stWaterAreaInfo* obj) {
    (void)obj;
    return LargeRet{};
}

// 71020d42f0 (160 bytes): fill existing L2CValue table
void stWaterAreaInfo__store_l2c_table_impl_71020d42f0(stWaterAreaInfo* obj, void* lv) {
    (void)obj; (void)lv;
}

} // namespace app::lua_bind
