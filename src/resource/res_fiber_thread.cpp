// res_fiber_thread.cpp — phx::Fiber fiber/thread management functions
// Pool-e assignment: resource service fiber + thread infrastructure
// [derived: phx namespace from Ghidra symbols]

#include "types.h"
#include "resource/Fiber.h"

using namespace phx;

// nn::os fiber API (PLT stubs)
// [derived: functions.csv confirmed names, 16-byte PLT entries]
extern "C" void FUN_71039c66c0(void*);      // nn::os::FinalizeFiber
extern "C" void* FUN_71039c66d0();           // nn::os::GetCurrentFiber
extern "C" void FUN_71039c66e0(void*);       // nn::os::SwitchToFiber
extern "C" u64 FUN_71039c0510(u32);          // nn::os::GetTlsValue
extern "C" void FUN_71039c07b0(u32, u64);    // nn::os::SetTlsValue

// Memory management
extern "C" void* je_aligned_alloc(unsigned long, unsigned long);
extern "C" void FUN_710392e590(void*);       // je_free
extern "C" int FUN_710392dc40(void** out, u32 alignment, u64 size);  // je_memalign

// Hook notifications
extern "C" void FUN_71039c1400(void*);       // nu::VirtualFreeHook (PLT)
namespace nu { void VirtualAllocHook(u64 size, u32 alignment, void* ptr); }
__attribute__((visibility("hidden"))) extern void* PTR_VirtualFreeHook_71052a7a70;
__attribute__((visibility("hidden"))) extern char PTR_VirtualAllocHook_71052a7a78[];

// Globals
// [derived: DAT_7105331f10 is nn::os::TlsSlot (u32), 0xFFFFFFFF = uninitialized]
// [derived: used in switch_to_fiber to track current fiber per-thread]
__attribute__((visibility("hidden"))) extern u32 DAT_7105331f10;

// [derived: OOM callback handler, called when je_aligned_alloc returns null]
__attribute__((visibility("hidden"))) extern void* DAT_7105331f00;

// Fiber entry point trampoline
// [derived: passed to nn::os::InitializeFiber in setup at 0x710353c5b0]
extern "C" void FUN_71037cc4c0(void*);

// ============================================================================
// phx::Fiber::finalize()
// Address: 0x710353c350 (156 bytes)
// [derived: Ghidra "phx::Fiber::finalize"]
// Releases a fiber if not currently running (state != 2).
// Clears self->impl, calls FinalizeFiber, frees stack, destroys
// std::function callable, frees the FiberImpl allocation.
// ============================================================================
void Fiber_finalize_353c350(Fiber* self) {
    FiberImpl* impl = self->impl;
    if (impl == nullptr) {
        self->impl = nullptr;
        return;
    }
    if (impl->state == 2) {
        return;
    }
    self->impl = nullptr;
    FUN_71039c66c0(impl);                 // nn::os::FinalizeFiber
    impl->initialized = 0;
    void* stack = impl->stack;
    if (PTR_VirtualFreeHook_71052a7a70 != nullptr) {
        FUN_71039c1400(stack);            // nu::VirtualFreeHook
    }
    FUN_710392e590(stack);                // je_free(stack)
    // Destroy std::function: vtable dispatch on func_impl
    // [derived: +0x70 = SBO inline buffer, +0x90 = __f_ pointer]
    // [derived: vtable[4] (+0x20) = destroy_inline, vtable[5] (+0x28) = destroy_heap]
    typedef void (*StdFuncDtor)(void*);
    void* fi = impl->func_impl;
    if ((void*)impl->func_buf == fi) {
        StdFuncDtor fn = (*(StdFuncDtor**)fi)[4];
        fn(fi);
    } else if (fi != nullptr) {
        StdFuncDtor fn = (*(StdFuncDtor**)fi)[5];
        fn(fi);
    }
    FUN_710392e590(impl);                 // je_free(impl)
}

// ============================================================================
// phx::Fiber::~Fiber()
// Address: 0x710353c210 (280 bytes)
// [derived: Ghidra "phx::Fiber::~Fiber"]
// Unconditional cleanup: if state != 2, runs finalize-cleanup then rechecks;
// if state == 2 (or recheck finds non-null), runs cleanup anyway.
// The first cleanup block is an inlined finalize(); the second handles
// the running-fiber case where finalize() would have returned early.
// ============================================================================
void Fiber_dtor_353c210(Fiber* self) {
    FiberImpl* impl = self->impl;
    if (impl == nullptr) {
        self->impl = nullptr;
        return;
    }
    u32 st = impl->state;
    self->impl = nullptr;
    if (st != 2) {
        // First cleanup (inlined finalize for non-running fiber)
        FUN_71039c66c0(impl);
        impl->initialized = 0;
        void* stack = impl->stack;
        if (PTR_VirtualFreeHook_71052a7a70 != nullptr) {
            FUN_71039c1400(stack);
        }
        FUN_710392e590(stack);
        typedef void (*StdFuncDtor)(void*);
        void* fi = impl->func_impl;
        if ((void*)impl->func_buf == fi) {
            StdFuncDtor fn = (*(StdFuncDtor**)fi)[4];
            fn(fi);
        } else if (fi != nullptr) {
            StdFuncDtor fn = (*(StdFuncDtor**)fi)[5];
            fn(fi);
        }
        FUN_710392e590(impl);
        // Re-read after cleanup (compiler artifact from inlined finalize)
        impl = self->impl;
        self->impl = nullptr;
        if (impl == nullptr) {
            return;
        }
    }
    // Second cleanup (handles running fiber or recheck)
    FUN_71039c66c0(impl);
    impl->initialized = 0;
    void* stack2 = impl->stack;
    if (PTR_VirtualFreeHook_71052a7a70 != nullptr) {
        FUN_71039c1400(stack2);
    }
    FUN_710392e590(stack2);
    {
        typedef void (*StdFuncDtor)(void*);
        void* fi2 = impl->func_impl;
        if ((void*)impl->func_buf == fi2) {
            StdFuncDtor fn = (*(StdFuncDtor**)fi2)[4];
            fn(fi2);
        } else if (fi2 != nullptr) {
            StdFuncDtor fn = (*(StdFuncDtor**)fi2)[5];
            fn(fi2);
        }
    }
    FUN_710392e590(impl);
}

// ============================================================================
// phx::Fiber::switch_to_fiber(phx::Fiber*)
// Address: 0x710353c400 (372 bytes)
// [derived: Ghidra "phx::Fiber::switch_to_fiber"]
// Static-like fiber context switch using TLS to track current fiber.
// Three cases converge to a single SwitchToFiber call at the end.
// DAT_7105331f10 is nn::os::TlsSlot (u32); 0xFFFFFFFF = not initialized.
// Status: logic matches (same size, same instructions), block placement differs.
//   Compiler block layout optimization produces different ordering than binary.
//   All non-prologue, non-relocation instructions are identical — 3/3 attempts.
// ============================================================================
void Fiber_switch_to_fiber_353c400(Fiber* param_1) {
    u32 slot = DAT_7105331f10;
    bool no_current;
    if (slot == 0xFFFFFFFF) {
        no_current = true;
    } else {
        u64 val = FUN_71039c0510(slot);  // GetTlsValue
        no_current = (val == 0);
    }

    FiberImpl* target_fiber;

    if (param_1 == nullptr) {
        // Case 1: switch FROM current fiber (no target)
        if (no_current) return;
        Fiber* cur = (Fiber*)(void*)FUN_71039c0510(DAT_7105331f10);
        if (DAT_7105331f10 != 0xFFFFFFFF) {
            FUN_71039c07b0(DAT_7105331f10, 0);
        }
        if (cur->impl->state != 3) {
            cur->impl->state = 1;
        }
        void* os_fib = FUN_71039c66d0();
        if (os_fib == nullptr) return;
        target_fiber = nullptr;
    } else if (no_current) {
        // Case 2: switch TO param_1 (no current fiber)
        if (DAT_7105331f10 != 0xFFFFFFFF) {
            FUN_71039c07b0(DAT_7105331f10, (u64)param_1);
        }
        param_1->impl->state = 2;
        target_fiber = param_1->impl;
        if (target_fiber->initialized == 0) return;
        FiberImpl* cur_os = (FiberImpl*)FUN_71039c66d0();
        if (target_fiber == cur_os) return;
    } else {
        // Case 3: swap fibers (both current and target exist)
        if (DAT_7105331f10 == 0xFFFFFFFF) {
            if (param_1 == nullptr) return;
        } else {
            Fiber* same = (Fiber*)(void*)FUN_71039c0510(DAT_7105331f10);
            if (same == param_1) return;
        }
        Fiber* cur;
        if (DAT_7105331f10 == 0xFFFFFFFF) {
            cur = nullptr;
        } else {
            cur = (Fiber*)(void*)FUN_71039c0510(DAT_7105331f10);
        }
        if (cur->impl->state != 3) {
            cur->impl->state = 1;
        }
        if (DAT_7105331f10 != 0xFFFFFFFF) {
            FUN_71039c07b0(DAT_7105331f10, (u64)param_1);
        }
        param_1->impl->state = 2;
        if (cur->impl->initialized == 0) return;
        target_fiber = param_1->impl;
        if (target_fiber->initialized == 0) return;
        if (target_fiber == cur->impl) return;
    }
    FUN_71039c66e0(target_fiber);  // SwitchToFiber
}

// ============================================================================
// FUN_710353cb90 — std::function swap (used by phx::Fiber::setup)
// Address: 0x710353cb90 (312 bytes)
// [derived: Ghidra decompilation shows std::function internal swap]
// Swaps two std::function objects stored as 5-long (40-byte) blocks.
// Layout: long[0..3] = inline buffer (32 bytes), long[4] = __f_ pointer.
// __f_ == self means inline; __f_ != self means heap-allocated callable.
// vtable[3] (+0x18) = move_construct(src, dst)
// vtable[4] (+0x20) = destroy(obj)
// ============================================================================
void FUN_710353cb90_353cb90(long* a, long* b) {
    if (b == a) return;

    long* a_f = (long*)a[4];

    if (a_f == a) {
        // a is inline
        long* b_f = (long*)b[4];
        if (b_f == b) {
            // CASE 4: both inline — 3-way swap through stack temp
            long temp[4];
            // move a → temp
            ((void(*)(void*, void*))(*(void***)a_f)[3])(a_f, temp);
            // destroy a
            ((void(*)(void*))(*(void***)(void*)a[4])[4])((void*)a[4]);
            a[4] = 0;
            // move b → a
            ((void(*)(void*, void*))(*(void***)(void*)b[4])[3])((void*)b[4], a);
            // destroy b
            ((void(*)(void*))(*(void***)(void*)b[4])[4])((void*)b[4]);
            b[4] = 0;
            a[4] = (long)a;
            // move temp → b
            ((void(*)(void*, void*))(*(void***)temp)[3])(temp, b);
            // destroy temp
            ((void(*)(void*))(*(void***)temp)[4])(temp);
        } else {
            // CASE 2: a inline, b heap — move a to b's inline, a takes b's heap
            ((void(*)(void*, void*))(*(void***)a_f)[3])(a_f, b);
            ((void(*)(void*))(*(void***)(void*)a[4])[4])((void*)a[4]);
            a[4] = b[4];
        }
        b[4] = (long)b;  // shared: mark b as inline
    } else {
        // a is heap
        long* b_f = (long*)b[4];
        if (b_f == b) {
            // CASE 3: a heap, b inline — move b to a's inline, b takes a's heap
            ((void(*)(void*, void*))(*(void***)b_f)[3])(b_f, a);
            ((void(*)(void*))(*(void***)(void*)b[4])[4])((void*)b[4]);
            b[4] = a[4];  // re-read a[4] (original heap ptr, unchanged by move)
            a[4] = (long)a;
        } else {
            // CASE 1: both heap — swap __f_ pointers
            a[4] = (long)b_f;
            b[4] = (long)a_f;
        }
    }
}
