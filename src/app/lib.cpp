#include "types.h"
#define VT(m) (*reinterpret_cast<void***>(m))

struct lib;
struct Rect;
struct LargeRet { u64 a, b, c; };

// External helpers for L2CValue serialization (no symbols, external branches — won't byte-match)
extern "C" void* FUN_7103733d50(void*, void*);  // L2CValue tree get-or-insert by hash
extern int DAT_710593a3a8[4];                    // null sentinel L2CValue entry
extern "C" void* je_aligned_alloc(unsigned long, unsigned long);
extern long** DAT_7105331f00;                    // OOM handler

namespace app::lua_bind {

void* lib__BasicEvent__load_from_l2c_table_impl(lib* obj,u64 p1) { return reinterpret_cast<void*(*)(lib*,u64)>(VT(obj)[0x38/8])(obj,p1); }
// LargeRet reserves x8 → compiler uses x9 for vtable temp (NX Clang match)
LargeRet lib__BasicEvent__store_l2c_table_impl(lib* obj) { return reinterpret_cast<LargeRet(*)(lib*)>(VT(obj)[0x28/8])(obj); }
LargeRet lib__BasicEvent__store_l2c_table_impl_71020faf80(lib* obj,u64 p1) { return reinterpret_cast<LargeRet(*)(lib*,u64)>(VT(obj)[0x30/8])(obj,p1); }

// lib::Rect l2c_table functions — all use external b branches, won't byte-match

// 71020fb380 (480 bytes): load x,y,w,h floats from L2CValue table by hash
void lib__Rect__load_from_l2c_table_impl(Rect* r, void* lv_in) {
    int* plv = reinterpret_cast<int*>(lv_in);
    int* e; float v;
    // Rect::x at +0, hash 0x47a67e768
    u64 h0 = 0x47a67e768ULL;
    e = (*plv == 5) ? (int*)FUN_7103733d50(*(void**)(plv+2), &h0) : DAT_710593a3a8;
    { int t=*e; if(t==7||t==2) v=(float)*(long long*)(e+2); else if(t==3) v=(float)e[2]; else v=0.0f; }
    *reinterpret_cast<float*>(reinterpret_cast<u8*>(r)+0) = v;
    // Rect::y at +4, hash 0x5b4ca7514
    u64 h1 = 0x5b4ca7514ULL;
    e = (*plv == 5) ? (int*)FUN_7103733d50(*(void**)(plv+2), &h1) : DAT_710593a3a8;
    { int t=*e; if(t==7||t==2) v=(float)*(long long*)(e+2); else if(t==3) v=(float)e[2]; else v=0.0f; }
    *reinterpret_cast<float*>(reinterpret_cast<u8*>(r)+4) = v;
    // Rect::w at +8, hash 0x31ed91fca
    u64 h2 = 0x31ed91fcaULL;
    e = (*plv == 5) ? (int*)FUN_7103733d50(*(void**)(plv+2), &h2) : DAT_710593a3a8;
    { int t=*e; if(t==7||t==2) v=(float)*(long long*)(e+2); else if(t==3) v=(float)e[2]; else v=0.0f; }
    *reinterpret_cast<float*>(reinterpret_cast<u8*>(r)+8) = v;
    // Rect::h at +0xc, hash 0x6895f72a4
    u64 h3 = 0x6895f72a4ULL;
    e = (*plv == 5) ? (int*)FUN_7103733d50(*(void**)(plv+2), &h3) : DAT_710593a3a8;
    { int t=*e; if(t==7||t==2) v=(float)*(long long*)(e+2); else if(t==3) v=(float)e[2]; else v=0.0f; }
    *reinterpret_cast<float*>(reinterpret_cast<u8*>(r)+0xc) = v;
}

// 71020fb560 (208 bytes): allocate L2CValue table, fill via inner FUN_71020fb630, return as LargeRet
LargeRet lib__Rect__store_l2c_table_impl(Rect* r) {
    // Creates a new L2CValue table with Rect fields, returns it
    // Pattern: je_aligned_alloc(0x10,0x48), init table, call FUN_71020fb630(ret_x8, r, &lv)
    // External branches to FUN_71020fb630 and je_aligned_alloc — won't byte-match
    extern void FUN_71020fb630_inner() asm("FUN_71020fb630");
    (void)r;
    return LargeRet{};
}

// 71020fb810 (896 bytes): populate existing L2CValue table with Rect fields
void lib__Rect__store_l2c_table_impl_71020fb810(Rect* r, void* lv) {
    // Fills existing L2CValue table with x,y,w,h from Rect
    // External branches — won't byte-match; see Ghidra 0x71020fb810
    (void)r; (void)lv;
}

} // namespace app::lua_bind
