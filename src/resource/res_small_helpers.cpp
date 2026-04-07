// res_small_helpers.cpp — Small helper functions in the resource service area
// Pool-a assignment: operator new/delete, malloc/free/realloc/calloc/aligned_alloc,
// fiber dispatch, and object constructors.

#include "types.h"
#include "resource/ResServiceNX.h"
#include "resource/LoadedArc.h"

using namespace resource;

// jemalloc entry points (NintendoSDK 8.2.1 ships jemalloc 5.1.0)
// [derived: je_aligned_alloc at 0x710392dce0, je_free at 0x710392e590 — PLT stubs]
extern "C" void* je_aligned_alloc(unsigned long, unsigned long);
extern "C" void  je_free(void*);                         // FUN_710392e590
extern "C" void* je_realloc(void*, unsigned long);       // FUN_710392dd80
extern "C" void* memset(void*, int, unsigned long);
extern "C" int   je_posix_memalign(void**, unsigned long, unsigned long); // FUN_710392dc40

// nn::os TLS support
// [derived: nn::os::SetTlsValue PLT at 0x71039c07b0]
extern "C" void nn_os_SetTlsValue(u32, u64);

// nu:: virtual memory hooks
// [derived: PTR_VirtualAllocHook at 0x71052a7a78 — PLT stub at 0x71039c1430]
extern "C" void nu_VirtualAllocHook(u64, u32, void*);
__attribute__((visibility("hidden"))) extern void* PTR_VirtualAllocHook_71052a7a78;

// Abort (libc)
extern "C" [[noreturn]] void abort();

// nothrow_t (baremetal — no <new> header)
namespace std { struct nothrow_t {}; }

// OOM handler singleton (40+ refs in binary)
// [derived: DAT_7105331f00 at 0x7105331f00 — vtable dispatch at +0x30 returns bool (bit 0)]
__attribute__((visibility("hidden"))) extern s64* DAT_7105331f00;

// Virtual memory OOM handler (separate from DAT_7105331f00)
// [derived: DAT_710593c2b0 — used by je_posix_memalign OOM retry, vtable+0x30 with 1 param]
__attribute__((visibility("hidden"))) extern s64* DAT_710593c2b0;

// Fiber TLS key
// [derived: DAT_7105331f10 — checked against 0xffffffff before nn::os::SetTlsValue call]
__attribute__((visibility("hidden"))) extern u32 DAT_7105331f10;

// Vtable pointers for constructed objects
// [derived: vtable set in FUN_710353a790 constructor]
__attribute__((visibility("hidden"))) extern void* PTR_DAT_710522e910;
// [derived: vtable set in FUN_710353adf0 constructor]
__attribute__((visibility("hidden"))) extern void* PTR_DAT_710522e958;

// ============================================================================
// operator new(unsigned long) — 0x710353bc20 (120 bytes)
// Replaces global operator new with jemalloc, 16-byte aligned.
// OOM retry via DAT_7105331f00 handler singleton.
// [derived: Ghidra symbol "operator new(unsigned long)"]
// [derived: je_aligned_alloc alignment=0x10 from disassembly mov w0,#0x10]
// ============================================================================
void* operator new(unsigned long size) {
    if (size == 0) size = 1;
    void* p = je_aligned_alloc(0x10, size);
    if (p == nullptr) {
        if (DAT_7105331f00 != nullptr) {
            u32 flags = 0;
            u64 req_size = size;
            u64 r = ((u64(*)(s64*, u32*, u64*))(*(s64*)(*DAT_7105331f00 + 0x30)))
                     (DAT_7105331f00, &flags, &req_size);
            if (((r & 1) != 0) &&
                (p = je_aligned_alloc(0x10, size), p != nullptr))
                return p;
        }
        p = nullptr;
    }
    return p;
}

// ============================================================================
// operator new(unsigned long, std::nothrow_t const&) — 0x710353bd00 (112 bytes)
// Nothrow variant — identical logic, second param unused.
// [derived: Ghidra symbol "operator new(unsigned long, std::nothrow_t const&)"]
// ============================================================================
void* operator new(unsigned long size, const std::nothrow_t&) noexcept {
    if (size == 0) size = 1;
    void* p = je_aligned_alloc(0x10, size);
    if (p == nullptr) {
        if (DAT_7105331f00 != nullptr) {
            u32 flags = 0;
            u64 req_size = size;
            u64 r = ((u64(*)(s64*, u32*, u64*))(*(s64*)(*DAT_7105331f00 + 0x30)))
                     (DAT_7105331f00, &flags, &req_size);
            if (((r & 1) != 0) &&
                (p = je_aligned_alloc(0x10, size), p != nullptr))
                return p;
        }
        p = nullptr;
    }
    return p;
}

// ============================================================================
// operator new[](unsigned long) — 0x710353bd70 (112 bytes)
// Array variant — identical logic.
// [derived: Ghidra symbol "operator new[](unsigned long)"]
// ============================================================================
void* operator new[](unsigned long size) {
    if (size == 0) size = 1;
    void* p = je_aligned_alloc(0x10, size);
    if (p == nullptr) {
        if (DAT_7105331f00 != nullptr) {
            u32 flags = 0;
            u64 req_size = size;
            u64 r = ((u64(*)(s64*, u32*, u64*))(*(s64*)(*DAT_7105331f00 + 0x30)))
                     (DAT_7105331f00, &flags, &req_size);
            if (((r & 1) != 0) &&
                (p = je_aligned_alloc(0x10, size), p != nullptr))
                return p;
        }
        p = nullptr;
    }
    return p;
}

// ============================================================================
// operator new[](unsigned long, std::nothrow_t const&) — 0x710353bde0 (112 bytes)
// Array nothrow variant — identical logic.
// [derived: Ghidra symbol "operator new[](unsigned long, std::nothrow_t const&)"]
// ============================================================================
void* operator new[](unsigned long size, const std::nothrow_t&) noexcept {
    if (size == 0) size = 1;
    void* p = je_aligned_alloc(0x10, size);
    if (p == nullptr) {
        if (DAT_7105331f00 != nullptr) {
            u32 flags = 0;
            u64 req_size = size;
            u64 r = ((u64(*)(s64*, u32*, u64*))(*(s64*)(*DAT_7105331f00 + 0x30)))
                     (DAT_7105331f00, &flags, &req_size);
            if (((r & 1) != 0) &&
                (p = je_aligned_alloc(0x10, size), p != nullptr))
                return p;
        }
        p = nullptr;
    }
    return p;
}

// ============================================================================
// operator delete(void*) — 0x710353be20 (12 bytes)
// [derived: Ghidra symbol "operator delete(void*)"]
// ============================================================================
void operator delete(void* p) noexcept {
    if (p != nullptr) je_free(p);
}

// ============================================================================
// operator delete(void*, unsigned long) — 0x710353be30 (12 bytes)
// Sized delete — size param unused, just calls je_free.
// [derived: Ghidra symbol "operator delete(void*, unsigned long)"]
// ============================================================================
void operator delete(void* p, unsigned long) noexcept {
    if (p != nullptr) je_free(p);
}

// ============================================================================
// operator delete(void*, std::nothrow_t const&) — 0x710353be40 (12 bytes)
// [derived: Ghidra symbol "operator delete(void*, std::nothrow_t const&)"]
// ============================================================================
void operator delete(void* p, const std::nothrow_t&) noexcept {
    if (p != nullptr) je_free(p);
}

// ============================================================================
// operator delete[](void*) — 0x710353be50 (12 bytes)
// [derived: Ghidra symbol "operator delete[](void*)"]
// ============================================================================
void operator delete[](void* p) noexcept {
    if (p != nullptr) je_free(p);
}

// ============================================================================
// operator delete[](void*, unsigned long) — 0x710353be60 (12 bytes)
// [derived: Ghidra symbol "operator delete[](void*, unsigned long)"]
// ============================================================================
void operator delete[](void* p, unsigned long) noexcept {
    if (p != nullptr) je_free(p);
}

// ============================================================================
// operator delete[](void*, std::nothrow_t const&) — 0x710353be70 (12 bytes)
// [derived: Ghidra symbol "operator delete[](void*, std::nothrow_t const&)"]
// ============================================================================
void operator delete[](void* p, const std::nothrow_t&) noexcept {
    if (p != nullptr) je_free(p);
}

// ============================================================================
// malloc — 0x710353be80 (120 bytes)
// Custom malloc replacement routed through jemalloc with OOM retry.
// [derived: Ghidra symbol "malloc"]
// ============================================================================
extern "C" void* malloc(unsigned long size) {
    if (size == 0) size = 1;
    void* p = je_aligned_alloc(0x10, size);
    if (p == nullptr) {
        if (DAT_7105331f00 != nullptr) {
            u32 flags = 0;
            u64 req_size = size;
            u64 r = ((u64(*)(s64*, u32*, u64*))(*(s64*)(*DAT_7105331f00 + 0x30)))
                     (DAT_7105331f00, &flags, &req_size);
            if (((r & 1) != 0) &&
                (p = je_aligned_alloc(0x10, size), p != nullptr))
                return p;
        }
        p = nullptr;
    }
    return p;
}

// ============================================================================
// free — 0x710353bf00 (12 bytes)
// Custom free replacement — null check + je_free.
// [derived: Ghidra symbol "free"]
// ============================================================================
extern "C" void free(void* p) {
    if (p != nullptr) je_free(p);
}

// ============================================================================
// realloc — 0x710353bf10 (224 bytes)
// Custom realloc replacement with OOM retry.
// ptr==null → malloc path; size==0 → free path; else → je_rallocx.
// [derived: Ghidra symbol "realloc"]
// [derived: FUN_710392dd80 = je_realloc — standard 2-arg realloc from jemalloc 5.1.0]
// ============================================================================
extern "C" void* realloc(void* ptr, unsigned long size) {
    void* p;
    if (ptr == nullptr) {
        if (size == 0) size = 1;
        p = je_aligned_alloc(0x10, size);
        if (p != nullptr) return p;
        if (DAT_7105331f00 == nullptr) return nullptr;
        u32 flags = 0;
        u64 req_size = size;
        u64 r = ((u64(*)(s64*, u32*, u64*))(*(s64*)(*DAT_7105331f00 + 0x30)))
                 (DAT_7105331f00, &flags, &req_size);
        if ((r & 1) == 0) return nullptr;
        p = je_aligned_alloc(0x10, size);
    } else {
        if (size == 0) {
            je_free(ptr);
            return nullptr;
        }
        p = je_realloc(ptr, size);
        if (p != nullptr) return p;
        if (DAT_7105331f00 == nullptr) return nullptr;
        u32 flags = 0;
        u64 req_size = size;
        u64 r = ((u64(*)(s64*, u32*, u64*))(*(s64*)(*DAT_7105331f00 + 0x30)))
                 (DAT_7105331f00, &flags, &req_size);
        if ((r & 1) == 0) return nullptr;
        p = je_realloc(ptr, size);
    }
    if (p == nullptr) return nullptr;
    return p;
}

// ============================================================================
// calloc — 0x710353c000 (168 bytes)
// Custom calloc replacement — allocates + zeroes.
// [derived: Ghidra symbol "calloc"]
// ============================================================================
extern "C" void* calloc(unsigned long nmemb, unsigned long size) {
    unsigned long total = size * nmemb;
    unsigned long alloc_size = total;
    if (total == 0) alloc_size = 1;
    void* p = je_aligned_alloc(0x10, alloc_size);
    if (p == nullptr) {
        if (DAT_7105331f00 != nullptr) {
            u32 flags = 0;
            u64 req_size = alloc_size;
            u64 r = ((u64(*)(s64*, u32*, u64*))(*(s64*)(*DAT_7105331f00 + 0x30)))
                     (DAT_7105331f00, &flags, &req_size);
            if ((r & 1) != 0) {
                p = je_aligned_alloc(0x10, alloc_size);
                if (p == nullptr) return nullptr;
                goto zero_fill;
            }
        }
        p = nullptr;
    } else {
zero_fill:
        memset(p, 0, total);
    }
    return p;
}

// ============================================================================
// aligned_alloc — 0x710353c0b0 (120 bytes)
// Custom aligned_alloc replacement — passes caller alignment through to jemalloc.
// [derived: Ghidra symbol "aligned_alloc"]
// ============================================================================
extern "C" void* aligned_alloc(unsigned long alignment, unsigned long size) {
    if (size == 0) size = 1;
    void* p = je_aligned_alloc(alignment, size);
    if (p == nullptr) {
        if (DAT_7105331f00 != nullptr) {
            u32 flags = 0;
            u64 req_size = size;
            u64 r = ((u64(*)(s64*, u32*, u64*))(*(s64*)(*DAT_7105331f00 + 0x30)))
                     (DAT_7105331f00, &flags, &req_size);
            if (((r & 1) != 0) &&
                (p = je_aligned_alloc(alignment, size), p != nullptr))
                return p;
        }
        p = nullptr;
    }
    return p;
}

// ============================================================================
// FUN_710353cf40 — fiber_dispatch (112 bytes)
// Calls vtable+0x30 on the scheduler (field_40), sets fiber state to 3,
// updates TLS with current fiber, returns fiber's first field.
// [derived: vtable dispatch at +0x30 on field_40 object]
// [derived: state=3 written to *(field_10[0]) + 0xb0]
// [derived: DAT_7105331f10 = TLS key, nn::os::SetTlsValue at PLT 0x71039c07b0]
// ============================================================================
u64 FUN_710353cf40(long param_1) {
    if (*(long*)(param_1 + 0x40) != 0) {
        long* fiber_ptr = *(long**)(param_1 + 0x10);
        u64* result = (u64*)((u64(*)(void*))(*(s64*)(*(s64*)(*(long*)(param_1 + 0x40)) + 0x30)))
                      ((void*)*(long*)(param_1 + 0x40));
        *(u32*)(*fiber_ptr + 0xb0) = 3;
        if (DAT_7105331f10 != 0xffffffff) {
            nn_os_SetTlsValue(DAT_7105331f10, (u64)result);
        }
        if (result == nullptr) return 0;
        return *result;
    }
    abort();
}

// ============================================================================
// FUN_710353a790 — construct FileNX-like object (352 bytes)
// Allocates 0x238 bytes via je_posix_memalign, zeroes, sets vtable + fields.
// [derived: je_posix_memalign returns 12 (ENOMEM) on failure]
// [derived: vtable at PTR_DAT_710522e910]
// [derived: DAT_710593c2b0 = virtual memory OOM handler, separate from DAT_7105331f00]
// [derived: allocation size 0x238 from disasm]
// ============================================================================
void FUN_710353a790(u64* param_1) {
    u64* obj;
    int err = je_posix_memalign((void**)&obj, 0x10, 0x238);
    if ((err == 0xc) && (DAT_710593c2b0 != nullptr)) {
        u64 req_size = 0x238;
        u64 r = ((u64(*)(s64*, u64*))(*(s64*)(*DAT_710593c2b0 + 0x30)))
                 (DAT_710593c2b0, &req_size);
        if ((r & 1) != 0) {
            je_posix_memalign((void**)&obj, 0x10, 0x238);
        }
    }
    if (PTR_VirtualAllocHook_71052a7a78 != nullptr) {
        nu_VirtualAllocHook(0x238, 0x10, obj);
    }
    u64* p = obj;
    memset(p, 0, 0x238);
#ifdef MATCHING_HACK_NX_CLANG
    asm volatile("" : "+r"(p) :: "memory");
#endif
    *(u32*)((char*)p + 0x08) = 0;
    *(u16*)((char*)p + 0x232) = 0;
    *(u8*)((char*)p + 0x30) = 0;
    *(u64*)p = (u64)&PTR_DAT_710522e910;  // vtable
    *(u8*)((char*)p + 0x234) = 0;
    *(u64*)((char*)p + 0x20) = 0;
    *(u64*)((char*)p + 0x28) = 0;
    *(u64*)((char*)p + 0x10) = 0;
    *(u64*)((char*)p + 0x18) = 0;
    *param_1 = (u64)p;
}

// ============================================================================
// FUN_710353adf0 — construct FileNX-like object variant (320 bytes)
// Allocates 0x230 bytes via je_posix_memalign, zeroes, sets vtable + fields.
// [derived: vtable at PTR_DAT_710522e958]
// [derived: allocation size 0x230 from disasm]
// ============================================================================
void FUN_710353adf0(u64* param_1) {
    u64* obj;
    int err = je_posix_memalign((void**)&obj, 0x10, 0x230);
    if ((err == 0xc) && (DAT_710593c2b0 != nullptr)) {
        u64 req_size = 0x230;
        u64 r = ((u64(*)(s64*, u64*))(*(s64*)(*DAT_710593c2b0 + 0x30)))
                 (DAT_710593c2b0, &req_size);
        if ((r & 1) != 0) {
            je_posix_memalign((void**)&obj, 0x10, 0x230);
        }
    }
    if (PTR_VirtualAllocHook_71052a7a78 != nullptr) {
        nu_VirtualAllocHook(0x230, 0x10, obj);
    }
    u64* p = obj;
    memset(p, 0, 0x230);
#ifdef MATCHING_HACK_NX_CLANG
    asm volatile("" : "+r"(p) :: "memory");
#endif
    *(u16*)((char*)p + 0x22a) = 0;
    *(u64*)p = (u64)&PTR_DAT_710522e958;  // vtable at +0x00
    p[1] = 0;                              // +0x08 (stp with vtable)
    *(u8*)((char*)p + 0x28) = 0;
    *(u64*)((char*)p + 0x10) = 0;
    *(u8*)((char*)p + 0x22c) = 0;
    *(u64*)((char*)p + 0x18) = 0;
    *(u64*)((char*)p + 0x20) = 0;
    *param_1 = (u64)p;
}
