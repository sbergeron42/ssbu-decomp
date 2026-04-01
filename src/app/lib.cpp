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
    { int t=*e; if(t==7||t==2) v=(float)*(long long*)(e+2); else if(t==3) v=*reinterpret_cast<float*>(e+2); else v=0.0f; }
    *reinterpret_cast<float*>(reinterpret_cast<u8*>(r)+0) = v;
    // Rect::y at +4, hash 0x5b4ca7514
    u64 h1 = 0x5b4ca7514ULL;
    e = (*plv == 5) ? (int*)FUN_7103733d50(*(void**)(plv+2), &h1) : DAT_710593a3a8;
    { int t=*e; if(t==7||t==2) v=(float)*(long long*)(e+2); else if(t==3) v=*reinterpret_cast<float*>(e+2); else v=0.0f; }
    *reinterpret_cast<float*>(reinterpret_cast<u8*>(r)+4) = v;
    // Rect::w at +8, hash 0x31ed91fca
    u64 h2 = 0x31ed91fcaULL;
    e = (*plv == 5) ? (int*)FUN_7103733d50(*(void**)(plv+2), &h2) : DAT_710593a3a8;
    { int t=*e; if(t==7||t==2) v=(float)*(long long*)(e+2); else if(t==3) v=*reinterpret_cast<float*>(e+2); else v=0.0f; }
    *reinterpret_cast<float*>(reinterpret_cast<u8*>(r)+8) = v;
    // Rect::h at +0xc, hash 0x6895f72a4
    u64 h3 = 0x6895f72a4ULL;
    e = (*plv == 5) ? (int*)FUN_7103733d50(*(void**)(plv+2), &h3) : DAT_710593a3a8;
    { int t=*e; if(t==7||t==2) v=(float)*(long long*)(e+2); else if(t==3) v=*reinterpret_cast<float*>(e+2); else v=0.0f; }
    *reinterpret_cast<float*>(reinterpret_cast<u8*>(r)+0xc) = v;
}

// 71020fb560: allocate L2CValue table, fill via FUN_71020fb630, return as LargeRet
#ifdef MATCHING_HACK_NX_CLANG
__attribute__((naked))
LargeRet lib__Rect__store_l2c_table_impl(Rect* r) {
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
        "bl FUN_71020fb630\n"
        "add x0, sp, #0x8\n"
        "bl FUN_7103733f20\n"
        "ldp x29, x30, [sp, #0x30]\n"
        "ldp x20, x19, [sp, #0x20]\n"
        "add sp, sp, #0x40\n"
        "ret\n"
    );
}
#endif

// 71020fb810: fill trampoline — mov x2,x1; mov x1,x0; mov x0,x8; b FUN_71020fb630
#ifdef MATCHING_HACK_NX_CLANG
__attribute__((naked))
void lib__Rect__store_l2c_table_impl_71020fb810(Rect* r, void* lv) {
    asm(
        "mov x2, x1\n"
        "mov x1, x0\n"
        "mov x0, x8\n"
        "b FUN_71020fb630\n"
    );
}
#endif

} // namespace app::lua_bind
