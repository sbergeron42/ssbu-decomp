// res_remaining_medium.cpp — Resource service medium infrastructure functions
// Pool-b assignment: pool allocator, fiber scheduler, container operations
// See WORKER.md for full target list.

#include "types.h"
#include "resource/Fiber.h"

// Memory management
extern "C" void* je_aligned_alloc(unsigned long, unsigned long);
extern "C" void FUN_710392e590(void*);  // je_free
extern "C" void* memset(void*, int, unsigned long);
extern "C" void* memcpy(void*, const void*, unsigned long);

// std::__1 PLT stubs
extern "C" void FUN_71039c1480(void*);   // std::__1::recursive_mutex::~recursive_mutex()
extern "C" void FUN_71039c14b0(void*);   // std::__1::mutex::lock()
extern "C" void FUN_71039c14c0(void*);   // std::__1::mutex::unlock()
extern "C" void FUN_71039c14d0(void*);   // std::__1::mutex::~mutex()

// For __shared_weak_count::__release_weak, use C++ declaration so compiler
// generates the correct Itanium-mangled BL target
namespace std { namespace __1 {
    class __shared_weak_count {
        long __shared_owners_;
        long __shared_weak_owners_;
    public:
        void __release_weak() noexcept;
        virtual ~__shared_weak_count();
    };
    [[noreturn]] void __throw_length_error(const char*);
}}

// nn::os
extern "C" u64 FUN_71039c0510(u32);      // nn::os::GetTlsValue
extern "C" void FUN_71039c0610(void*);    // nn::os::FinalizeLightEvent

// OOM handler singleton
// [derived: DAT_7105331f00 at 0x7105331f00, vtable dispatch at +0x30 for OOM retry]
__attribute__((visibility("hidden"))) extern s64* DAT_7105331f00;

// Free hook
__attribute__((visibility("hidden"))) extern void* PTR_VirtualFreeHook_71052a7a70;
extern "C" void FUN_71039c1400(void*);    // nu::VirtualFreeHook

// Shared ptr / std::function move helper
extern "C" void FUN_7101f6f1f0(void* dst, void* src);

// Fiber creation helper
extern "C" void* FUN_7103549f00(long);

// Deque push_back helper
extern "C" void FUN_710354a7e0(long);

// Pool init (defined in this file, called by pool_acquire)
void FUN_7103546c40_6c40(long* param_1, long param_2, u32 param_3, long param_4, long* param_5);

// libc error handlers
extern "C" [[noreturn]] void abort();

// Vtable externs
// [derived: Ghidra vtable pointer symbols in .data.rel.ro]
__attribute__((visibility("hidden"))) extern void* PTR_FUN_710522ed28;
__attribute__((visibility("hidden"))) extern void* PTR_FUN_710522eda8;

// Fiber destructor (defined in res_fiber_thread.cpp)
extern "C" void Fiber_dtor_353c210(phx::Fiber*);

// Fiber switch_to_fiber (defined in res_fiber_thread.cpp)
extern "C" void Fiber_switch_to_fiber_353c400(phx::Fiber*);

// ============================================================================
// FUN_7103546c40 — pool_block_init
// Initializes a pool block: stores element config, clones a std::function
// allocator from param_5 to the block at +0x30, then allocates
// count*element_size bytes via the allocator in param_4, zeroes the buffer,
// and builds a freelist through the allocated elements.
// [derived: pool block layout: +0x00=freelist_head, +0x08=element_size(u32),
//   +0x0C=count(u32), +0x10=base_ptr, +0x18=end_ptr, +0x20=count_copy(u32),
//   +0x30=std::function(allocator)]
// [derived: freelist built by chaining elements, each element[0]=prev_ptr]
// Address: 0x7103546c40 (336 bytes)
// ============================================================================
void FUN_7103546c40_6c40(long* param_1, long param_2, u32 param_3, long param_4, long* param_5) {
    long local_80[4];
    long* local_60 = (long*)local_80;

    *(u32*)((char*)param_1 + 8) = (u32)param_2;
    *(u32*)((char*)param_1 + 0xC) = param_3;

    // Clone std::function from param_5 to local
    // [derived: param_5[4] = __f_ pointer, param_5 = SBO inline buffer]
    long* plVar3 = (long*)param_5[4];
    if (plVar3 == nullptr) {
        local_60 = nullptr;
    } else if (param_5 == plVar3) {
        // Inline: vtable[3] (+0x18) = move_construct(src, dst)
        ((void(*)(long*, long*))((long*)*plVar3)[3])(plVar3, local_80);
    } else {
        // Heap: vtable[2] (+0x10) = clone()
        local_60 = (long*)((long*(*)(void))((long*)*plVar3)[2])();
    }

    // Move the cloned function to param_1+0x30
    FUN_7101f6f1f0(local_80, param_1 + 6);

    // Destroy the local clone
    if ((long*)local_80 == local_60) {
        ((void(*)(void))((long*)*local_60)[4])();
    } else if (local_60 != nullptr) {
        ((void(*)(void))((long*)*local_60)[5])();
    }

    // Allocate buffer: count * element_size bytes
    u64 n = (u64)param_3 * (u64)param_2;
    long local_48 = 8;  // alignment
    long* plVar = *(long**)(param_4 + 0x20);
    local_80[0] = (long)n;
    if (plVar == nullptr) {
        abort();
    }

    // Call allocator via vtable[6] (+0x30) = allocate(this, &size, &alignment)
    long* buf = (long*)((long*(*)(long*, long*, long*))((long*)*plVar)[6])(plVar, local_80, &local_48);
    memset(buf, 0, n);
    void* end = (void*)((long)buf + n);

    // Set pool block fields
    param_1[0] = 0;           // +0x00: freelist head
    param_1[2] = (long)buf;   // +0x10: base_ptr
    param_1[3] = (long)end;   // +0x18: end_ptr
    *(u32*)(param_1 + 4) = param_3;  // +0x20: count

    // Build freelist: chain elements from base to end
    if ((void*)((long)buf + param_2) <= end) {
        long* prev = nullptr;
        do {
            *buf = (long)prev;
            param_1[0] = (long)buf;
            long* next_buf = (long*)((long)buf + param_2);
            prev = buf;
            buf = next_buf;
        } while ((void*)((long)buf + param_2) <= end);
    }
}

// ============================================================================
// FUN_7103546d90 — pool_acquire
// Acquires a free element from the pool. Scans the block array for a block
// with a non-empty freelist. If none found, allocates a new 0x60-byte block,
// initializes it with FUN_7103546c40, and adds it to the block array (with
// vector-style growth). Pops and returns the first free element.
// [derived: pool manager layout: +0x00=config_a(u64), +0x08=config_b(u32),
//   +0x10=blocks_start, +0x18=blocks_end, +0x20=blocks_capacity,
//   +0x30..+0x57=std::function_a, +0x60..+0x87=std::function_b]
// Address: 0x7103546d90 (816 bytes)
// ============================================================================
void* FUN_7103546d90_6d90(long* param_1) {
    long local_c0[4];
    long* local_a0;
    long local_90[4];
    long* local_70;
    long local_60;
    u32 local_54;

    long** puVar1 = (long**)param_1[2];  // blocks_start
    long* plVar8;
    long* plVar3;

    while (true) {
        if (puVar1 == (long**)param_1[3]) {  // blocks_end: no free slot found
            // Allocate new pool block (0x60 bytes)
            plVar8 = (long*)je_aligned_alloc(0x10, 0x60);
            if (plVar8 == nullptr) {
                if (DAT_7105331f00 != nullptr) {
                    local_c0[0] = 0;
                    local_90[0] = 0x60;
                    u64 r = ((u64(*)(s64*, long*, long*))(*(s64*)(*DAT_7105331f00 + 0x30)))
                             (DAT_7105331f00, local_c0, local_90);
                    if (((r & 1) != 0) &&
                        (plVar8 = (long*)je_aligned_alloc(0x10, 0x60), plVar8 != nullptr))
                        goto block_ok;
                }
                plVar8 = nullptr;
            }
block_ok:
            // Zero-init the new block
            plVar8[10] = 0;  // +0x50
            *(u32*)(plVar8 + 4) = 0;  // +0x20
            plVar8[2] = 0;  // +0x10
            plVar8[3] = 0;  // +0x18
            plVar8[0] = 0;  // +0x00
            plVar8[1] = 0;  // +0x08

            // Copy config from pool manager
            long uVar9 = param_1[0];                // +0x00 = element_size
            u32 uVar2 = *(u32*)(param_1 + 1);       // +0x08 = count

            // Clone std::function_a from param_1+0x30 (param_1[10]=+0x50 is __f_)
            plVar3 = (long*)param_1[10];
            if (plVar3 == nullptr) {
                local_70 = nullptr;
                plVar3 = (long*)param_1[16];  // +0x80 is __f_ of function_b
                if (plVar3 != nullptr) goto clone_b;
                local_a0 = nullptr;
            } else {
                if (param_1 + 6 == plVar3) {
                    local_70 = (long*)local_90;
                    ((void(*)(long*, long*))((long*)*plVar3)[3])(plVar3, local_90);
                    plVar3 = (long*)param_1[16];
                    if (plVar3 != nullptr) goto clone_b;
                    local_a0 = nullptr;
                } else {
                    local_70 = (long*)((long*(*)(void))((long*)*plVar3)[2])();
                    plVar3 = (long*)param_1[16];
                    if (plVar3 == nullptr) {
                        local_a0 = nullptr;
                    } else {
clone_b:
                        if (param_1 + 12 == plVar3) {
                            local_a0 = (long*)local_c0;
                            ((void(*)(long*, long*))((long*)*plVar3)[3])(plVar3, local_c0);
                        } else {
                            local_a0 = (long*)((long*(*)(void))((long*)*plVar3)[2])();
                        }
                    }
                }
            }

            // Init the new block via pool_init
            FUN_7103546c40_6c40(plVar8, uVar9, uVar2, (long)local_90, local_c0);

            // Destroy local clone of function_b
            if ((long*)local_c0 == local_a0) {
                ((void(*)(void))((long*)*local_a0)[4])();
            } else if (local_a0 != nullptr) {
                ((void(*)(void))((long*)*local_a0)[5])();
            }

            // Destroy local clone of function_a
            if ((long*)local_90 == local_70) {
                ((void(*)(void))((long*)*local_70)[4])();
            } else if (local_70 != nullptr) {
                ((void(*)(void))((long*)*local_70)[5])();
            }

            // Push new block pointer into blocks array
            puVar1 = (long**)param_1[3];  // blocks_end
            if (puVar1 == (long**)param_1[4]) {  // blocks_capacity: need to grow
                // Vector growth: allocate new array, copy, free old
                void* old_start = (void*)param_1[2];
                u64 old_n = (long)puVar1 - (long)old_start;
                u64 new_count = (old_n >> 3) + 1;
                if ((new_count >> 0x3d) != 0) {
                    std::__1::__throw_length_error("vector");
                }
                u64 old_cap = (long)param_1[4] - (long)old_start;
                u64 new_cap;
                if ((u64)(old_cap >> 3) < 0xfffffffffffffffULL) {
                    new_cap = old_cap >> 2;
                    if (new_count > new_cap) new_cap = new_count;
                    if (new_cap != 0) {
                        if ((new_cap >> 0x3d) != 0) abort();
                        goto do_alloc;
                    }
                    goto null_alloc;
                } else {
                    new_cap = 0x1fffffffffffffffULL;
do_alloc:;
                    u64 alloc_size = new_cap * 8;
                    if (alloc_size == 0) alloc_size = 1;
                    void* new_buf = je_aligned_alloc(0x10, alloc_size);
                    if (new_buf == nullptr) {
                        if (DAT_7105331f00 != nullptr) {
                            local_54 = 0;
                            local_60 = (long)alloc_size;
                            u64 r = ((u64(*)(s64*, u32*, long*))(*(s64*)(*DAT_7105331f00 + 0x30)))
                                     (DAT_7105331f00, &local_54, &local_60);
                            if (((r & 1) != 0) &&
                                (new_buf = je_aligned_alloc(0x10, alloc_size), new_buf != nullptr))
                                goto vec_alloc_ok;
                        }
                        goto null_alloc;
                    }
vec_alloc_ok:;
                    puVar1 = (long**)((long)new_buf + (old_n >> 3) * 8);
                    *puVar1 = plVar8;
                    if (0 < (long)old_n) {
                        memcpy(new_buf, old_start, old_n);
                    }
                    param_1[2] = (long)new_buf;
                    param_1[3] = (long)(puVar1 + 1);
                    param_1[4] = (long)new_buf + new_cap * 8;
                    if (old_start != nullptr) {
                        FUN_710392e590(old_start);
                    }
                    plVar3 = (long*)*plVar8;
                    goto check_freelist;
                }
null_alloc:;
                void* new_buf2 = nullptr;
                puVar1 = (long**)((long)new_buf2 + (old_n >> 3) * 8);
                *puVar1 = plVar8;
                if (0 < (long)old_n) {
                    memcpy(new_buf2, old_start, old_n);
                }
                param_1[2] = (long)new_buf2;
                param_1[3] = (long)(puVar1 + 1);
                param_1[4] = (long)new_buf2 + new_cap * 8;
                if (old_start != nullptr) {
                    FUN_710392e590(old_start);
                }
                plVar3 = (long*)*plVar8;
            } else {
                *puVar1 = plVar8;
                param_1[3] = param_1[3] + 8;
                plVar3 = (long*)*plVar8;
            }
check_freelist:
            if (plVar3 == nullptr) {
                return nullptr;
            }
            break;
        }

        plVar8 = *puVar1;       // dereference block pointer
        plVar3 = (long*)*plVar8; // freelist head
        puVar1++;
        if (plVar3 != nullptr) break;  // found a block with free elements
    }

    // Pop from freelist
    *plVar8 = *plVar3;                               // head = head->next
    *(u32*)(plVar8 + 4) = *(u32*)(plVar8 + 4) - 1;  // decrement free count

    return (void*)plVar3;
}

// ============================================================================
// FUN_710354c720 — fiber_scheduler_push_task
// Pushes a task onto the fiber scheduler's work queue. Gets the scheduler
// from TLS, stores task data into a 0x20-byte entry in the work vector.
// If no active fiber exists, creates one and switches to it.
// [derived: scheduler layout at TLS: +0xC0=current_task, +0xC8=current_param,
//   +0xD0=current_fiber, +0xD8=current_id(u32), +0xE0=work_vector_start,
//   +0xE8=work_vector_end, +0xF0=work_vector_capacity]
// Address: 0x710354c720 (544 bytes)
// ============================================================================
void FUN_710354c720_c720(u32 param_1, int* param_2) {
    long lVar6;
    if (param_1 == 0xFFFFFFFF) {
        lVar6 = 0;
    } else {
        lVar6 = (long)FUN_71039c0510(param_1);
    }

    if (*param_2 < 1) return;

    long* puVar2 = *(long**)(lVar6 + 0xe8);
    long* puVar1 = (long*)(lVar6 + 0xc0);
    *(int**)(lVar6 + 0xc8) = param_2;
    long lVar8;

    if (puVar2 != *(long**)(lVar6 + 0xf0)) {
        long uVar3 = *puVar1;
        long uVar4 = *(long*)(lVar6 + 0xc8);
        long uVar5 = *(long*)(lVar6 + 0xd8);
        puVar2[2] = *(long*)(lVar6 + 0xd0);
        puVar2[3] = uVar5;
        puVar2[0] = uVar3;
        puVar2[1] = uVar4;
        *(long*)(lVar6 + 0xe8) = *(long*)(lVar6 + 0xe8) + 0x20;
        lVar8 = *(long*)(lVar6 + 0xd0);
    } else {
        void* __src = *(void**)(lVar6 + 0xe0);
        u64 __n = (long)puVar2 - (long)__src;
        u64 uVar10 = (__n >> 5) + 1;
        if ((uVar10 >> 0x3b) != 0) {
            std::__1::__throw_length_error("vector");
        }
        long lVar8b = *(long*)(lVar6 + 0xf0) - (long)__src;
        void* __dest;
        u64 uVar9;
        if ((u64)(lVar8b >> 5) < 0x3fffffffffffffffULL) {
            uVar9 = lVar8b >> 4;
            if (uVar10 > uVar9) uVar9 = uVar10;
            if (uVar9 != 0) {
                if ((uVar9 >> 0x3b) != 0) abort();
                goto LAB_c7f4;
            }
            __dest = nullptr;
        } else {
            uVar9 = 0x7fffffffffffffffULL;
LAB_c7f4:
            lVar8b = (long)(uVar9 * 0x20);
            if (lVar8b == 0) lVar8b = 1;
            __dest = je_aligned_alloc(0x10, lVar8b);
            if (__dest == nullptr) {
                if (DAT_7105331f00 != nullptr) {
                    u32 local_54 = 0;
                    long local_60 = lVar8b;
                    uVar9 = ((u64(*)(s64*, u32*, long*))(*(s64*)(*DAT_7105331f00 + 0x30)))
                             (DAT_7105331f00, &local_54, &local_60);
                    if (((uVar9 & 1) != 0) &&
                        (__dest = je_aligned_alloc(0x10, lVar8b), __dest != nullptr))
                        goto LAB_c858;
                }
                __dest = nullptr;
            }
        }
LAB_c858:;
        long uVar3 = *puVar1;
        long uVar4 = *(long*)(lVar6 + 0xc8);
        puVar2 = (long*)((long)__dest + (__n >> 5) * 0x20);
        long uVar5 = *(long*)(lVar6 + 0xd8);
        puVar2[2] = *(long*)(lVar6 + 0xd0);
        puVar2[3] = uVar5;
        puVar2[0] = uVar3;
        puVar2[1] = uVar4;
        if (0 < (long)__n) {
            memcpy(__dest, __src, __n);
        }
        *(void**)(lVar6 + 0xe0) = __dest;
        *(long**)(lVar6 + 0xe8) = puVar2 + 4;
        *(void**)(lVar6 + 0xf0) = (void*)((long)__dest + uVar9 * 0x20);
        if (__src != nullptr) {
            FUN_710392e590(__src);
        }
        lVar8 = *(long*)(lVar6 + 0xd0);
    }

    if (lVar8 == 0) {
        phx::Fiber* pFVar7 = (phx::Fiber*)FUN_7103549f00(lVar6);
        *(phx::Fiber**)(lVar6 + 0xd0) = pFVar7;
        Fiber_switch_to_fiber_353c400(pFVar7);
        *(long*)(lVar6 + 0xc8) = 0;
        *(long*)(lVar6 + 0xd0) = 0;
        *puVar1 = 0;
        *(u32*)(lVar6 + 0xd8) = 0xFFFFFFFF;
        return;
    }
    *puVar1 = 0;
    *(long*)(lVar6 + 0xc8) = 0;
    *(long*)(lVar6 + 0xd0) = 0;
    *(u32*)(lVar6 + 0xd8) = 0xFFFFFFFF;
    phx::Fiber* pFVar7 = (phx::Fiber*)FUN_7103549f00(lVar6);
    *(phx::Fiber**)(lVar6 + 0xd0) = pFVar7;
    Fiber_switch_to_fiber_353c400(pFVar7);
}

// ============================================================================
// FUN_710354e320 — task_object_destructor
// Destructor for a large task/request object (~0x790 bytes). Inherits from
// std::__1::__shared_weak_count. Sets vtable, locks internal mutex, resets
// all task fields to defaults, releases shared_ptr if held, unlocks,
// then destroys mutex and calls ~__shared_weak_count.
// [derived: vtable at PTR_FUN_710522eda8, object inherits __shared_weak_count]
// [derived: field at +0x300 holds optional shared_ptr control block]
// Address: 0x710354e320 (448 bytes)
// ============================================================================
void FUN_710354e320_e320(long* param_1) {
    // Set vtable (base class destructor vtable)
    *(void**)param_1 = &PTR_FUN_710522eda8;

    // Lock internal mutex (location inferred from Ghidra — register analysis)
    FUN_71039c14b0(param_1);  // mutex::lock on the object itself

    param_1[0x1a] = 1;                          // +0xD0: reset state to 1
    *(u16*)(param_1 + 0x18) = 0;                 // +0xC0: clear u16 field
    *(long*)(param_1 + 0x20) = -1LL;            // +0x100: set to 0xFFFFFFFFFFFFFFFF

    // Release shared_ptr at +0x300 if held
    if (*(long**)(param_1 + 0x60) != nullptr) {
        // Call release method via vtable: vtable[1] (+0x08)
        ((void(*)(void))((long*)(**(long**)(param_1 + 0x60)))[1])();
        *(long*)(param_1 + 0x60) = 0;
    }

    param_1[0xe9] = 0;                          // +0x748
    *(long*)(param_1 + 0x28) = 0;               // +0x140
    *(long*)(param_1 + 0x30) = 0;               // +0x180
    *(long*)(param_1 + 0x38) = 0;               // +0x1C0
    param_1[0x68] = 0;                          // +0x340
    *(long*)(param_1 + 0x58) = 0;               // +0x2C0
    *(long*)(param_1 + 0x60) = 0;               // +0x300
    *(long*)(param_1 + 0x48) = 0;               // +0x240
    *(long*)(param_1 + 0x50) = 0;               // +0x280

    FUN_71039c14c0(param_1);  // mutex::unlock

    FUN_71039c14d0(param_1 + 0xf0);  // mutex::~mutex at +0x780

    // ~__shared_weak_count()
    reinterpret_cast<std::__1::__shared_weak_count*>(param_1)->~__shared_weak_count();
}

// ============================================================================
// FUN_710354cc80 — container_destructor_with_recursive_mutex
// Destructor for a container holding a vector of shared_ptrs and a doubly-
// linked list. Sets vtable, destroys recursive_mutex, releases shared_ptrs
// in the vector (with atomic ref count decrement), then unlinks and frees
// all nodes in the doubly-linked list.
// [derived: vtable at PTR_FUN_710522ed28]
// [derived: vector at +0x20..+0x28 (start/end), list at +0x08..+0x18]
// Address: 0x710354cc80 (400 bytes)
// ============================================================================
void FUN_710354cc80_cc80(long* param_1) {
    *param_1 = (long)&PTR_FUN_710522ed28;

    // Destroy recursive mutex at +0x38 (param_1[7])
    FUN_71039c1480(param_1 + 7);

    // Release shared_ptrs in vector at +0x20..+0x28
    long lVar8 = param_1[4];   // +0x20: vector start
    if (lVar8 != 0) {
        long lVar9 = param_1[5];  // +0x28: vector end

        if (lVar9 == lVar8) {
            param_1[5] = lVar8;
            lVar9 = lVar8;
        } else {
            do {
                long* plVar7 = *(long**)(lVar9 - 0x10);
                lVar9 -= 0x18;
                if (plVar7 != nullptr) {
                    long old = __atomic_fetch_sub(plVar7 + 1, 1, __ATOMIC_RELAXED);
                    if (old == 0) {
                        ((void(*)(long*))((long*)*plVar7)[2])(plVar7);
                        reinterpret_cast<std::__1::__shared_weak_count*>(plVar7)->__release_weak();
                    }
                }
            } while (lVar9 != lVar8);
            lVar9 = param_1[4];
            param_1[5] = lVar8;
        }

        if (lVar9 != 0) {
            FUN_710392e590((void*)lVar9);
        }
    }

    // Unlink and free doubly-linked list at +0x08..+0x18
    if (param_1[3] != 0) {  // +0x18: list size
        long lVar8b = param_1[1];  // +0x08: first node
        long* plVar7 = (long*)param_1[2];  // +0x10: last node

        // Unlink this container from the list
        *(long*)(*plVar7 + 8) = *(long*)(lVar8b + 8);
        **(long**)(lVar8b + 8) = *plVar7;

        param_1[3] = 0;

        // Free all nodes in the list
        long* plVar1;
        while (plVar1 = plVar7, plVar1 != param_1 + 1) {
            plVar7 = (long*)plVar1[1];  // next node
            long* plVar6 = (long*)plVar1[3];  // shared_ptr control block

            if (plVar6 != nullptr) {
                long old = __atomic_fetch_sub(plVar6 + 1, 1, __ATOMIC_RELAXED);
                if (old == 0) {
                    ((void(*)(long*))((long*)*plVar6)[2])(plVar6);
                    reinterpret_cast<std::__1::__shared_weak_count*>(plVar6)->__release_weak();
                }
            }

            if (plVar1 != nullptr) {
                FUN_710392e590(plVar1);
            }
        }
    }
}

// ============================================================================
// FUN_710354d130 — vector_emplace_back_shared_ptr
// Grows a vector of 0x18-byte elements (shared_ptr + bool flag) by one.
// Allocates new storage with OOM retry, copies the new element, moves
// existing elements, and releases old storage. Includes atomic refcount
// increment for the shared_ptr control block.
// [derived: each element = { void* ptr, __shared_weak_count* ctrl, u8 flag }]
// Address: 0x710354d130 (720 bytes)
// ============================================================================
void FUN_710354d130_d130(long* param_1, long* param_2) {
    long lVar10 = *param_1;         // vector start
    long lVar14 = param_1[1];       // vector end
    long lVar7 = (lVar14 - lVar10) >> 3;
    u64 uVar15 = 0xaaaaaaaaaaaaaaaULL;
    u64 uVar6 = lVar7 * (-0x5555555555555555LL) + 1;

    if (0xaaaaaaaaaaaaaaaULL < uVar6) {
        std::__1::__throw_length_error("vector");
    }

    long lVar11 = param_1[2] - lVar10;
    long lVar5;
    u64 uVar9;

    if ((u64)(lVar11 * (-0x5555555555555555LL)) < 0x555555555555555ULL) {
        uVar9 = lVar11 * 0x5555555555555556LL;
        uVar15 = uVar6;
        if (uVar6 <= uVar9) uVar15 = uVar9;
        if (uVar15 != 0) goto do_alloc;
    } else {
do_alloc:
        lVar11 = (long)(uVar15 * 0x18);
        if (lVar11 == 0) lVar11 = 1;

        lVar5 = (long)je_aligned_alloc(0x10, lVar11);
        if (lVar5 == 0) {
            if (DAT_7105331f00 != nullptr) {
                u32 local_44 = 0;
                long local_58 = lVar11;
                uVar6 = ((u64(*)(s64*, u32*, long*))(*(s64*)(*DAT_7105331f00 + 0x30)))
                         (DAT_7105331f00, &local_44, &local_58);
                if (((uVar6 & 1) != 0) &&
                    (lVar5 = (long)je_aligned_alloc(0x10, lVar11), lVar5 != 0))
                    goto alloc_ok;
            }
        } else {
            goto alloc_ok;
        }
    }
    lVar5 = 0;
alloc_ok:;
    long* puVar8 = (long*)(lVar5 + lVar7 * 8);
    *puVar8 = *param_2;
    lVar11 = param_2[1];
    puVar8[1] = lVar11;

    if (lVar11 != 0) {
        // Atomic increment refcount of shared_ptr control block
        __atomic_fetch_add((long*)(lVar11 + 8), 1, __ATOMIC_RELAXED);
        lVar10 = *param_1;
        lVar14 = param_1[1];
    }

    *(u8*)(lVar5 + lVar7 * 8 + 0x10) = *(u8*)(param_2 + 2);
    long* puVar1 = puVar8 + 3;

    // Move existing elements from old to new buffer
    long lVar7b = lVar14;
    long lVar12 = 0;
    if (lVar14 != lVar10) {
        lVar7b = 0;
        do {
            long lVar11b = lVar14 + lVar7b;
            lVar12 = lVar7b - 0x18;
            *(long*)((long)puVar8 + lVar7b - 0x18) = *(long*)(lVar11b - 0x18);
            *(long*)((long)puVar8 + lVar7b - 0x10) = *(long*)(lVar11b - 0x10);
            *(long*)(lVar11b - 0x18) = 0;
            *(long*)(lVar11b - 0x10) = 0;
            *(u8*)((long)puVar8 + lVar7b - 8) = *(u8*)(lVar11b - 8);
            lVar7b = lVar12;
        } while (lVar10 - lVar14 != lVar12);
        lVar14 = *param_1;
        puVar8 = (long*)((long)puVar8 + lVar12);
        lVar7b = param_1[1];
    }

    *param_1 = (long)puVar8;
    param_1[1] = (long)puVar1;
    param_1[2] = lVar5 + (long)(uVar15 * 0x18);

    // Release old shared_ptrs and free old buffer
    while (lVar7b != lVar14) {
        long* plVar13 = *(long**)(lVar7b - 0x10);
        lVar7b -= 0x18;
        if (plVar13 != nullptr) {
            long old = __atomic_fetch_sub(plVar13 + 1, 1, __ATOMIC_RELAXED);
            if (old == 0) {
                ((void(*)(long*))((long*)*plVar13)[2])(plVar13);
                reinterpret_cast<std::__1::__shared_weak_count*>(plVar13)->__release_weak();
            }
        }
    }

    if (lVar14 != 0) {
        FUN_710392e590((void*)lVar14);
    }
}

// ============================================================================
// FUN_710354ce10 — merge_sort_linked_list
// Merge sort on a doubly-linked list, comparing elements via vtable call
// at vtable offset 0x2a8 (slot 85). Returns the new head of the sorted list.
// [derived: node layout: [0]=next, [1]=prev, [2]=data_with_vtable]
// [derived: comparison via vtable[85] (+0x2a8) returns a priority byte]
// Address: 0x710354ce10 (704 bytes)
// ============================================================================
long* FUN_710354ce10_ce10(long* param_1, long* param_2, u64 param_3) {
    if (param_3 < 2) {
        return param_1;
    }

    if (param_3 == 2) {
        // Base case: 2 elements, swap if needed
        param_2 = (long*)*param_2;
        u8 bVar2 = ((u8(*)(void))((long*)(*(long*)param_2[2]))[0x55])();
        u8 bVar3 = ((u8(*)(void))((long*)(*(long*)param_1[2]))[0x55])();
        if (bVar2 < bVar3) {
            *(long*)(*param_2 + 8) = param_2[1];
            *(long*)param_2[1] = *param_2;
            *(long**)(*param_1 + 8) = param_2;
            *param_2 = *param_1;
            *param_1 = (long)param_2;
            param_2[1] = (long)param_1;
            param_1 = param_2;
        }
        return param_1;
    }

    // Recursive case: split, sort halves, merge
    u64 uVar5 = param_3 >> 1;
    long* plVar7 = param_1;
    if (uVar5 != 0) {
        long lVar4 = (long)uVar5 + 1;
        do {
            plVar7 = (long*)plVar7[1];
            lVar4--;
        } while (1 < lVar4);
        param_1 = FUN_710354ce10_ce10(param_1, plVar7, uVar5);
    }
    plVar7 = FUN_710354ce10_ce10(plVar7, param_2, param_3 - uVar5);

    // Merge two sorted halves
    u8 bVar2 = ((u8(*)(void))((long*)(*(long*)plVar7[2]))[0x55])();
    u8 bVar3 = ((u8(*)(void))((long*)(*(long*)param_1[2]))[0x55])();

    long* plVar8;
    long* plVar9;
    long* plVar6;
    long* plVar10;

    if (bVar2 < bVar3) {
        // plVar7's head is smaller — splice it before param_1's head
        for (plVar9 = (long*)plVar7[1]; plVar6 = param_2, plVar9 != param_2;
             plVar9 = (long*)plVar9[1]) {
            bVar2 = ((u8(*)(void))((long*)(*(long*)plVar9[2]))[0x55])();
            bVar3 = ((u8(*)(void))((long*)(*(long*)param_1[2]))[0x55])();
            plVar6 = plVar9;
            if (bVar3 <= bVar2) break;
        }
        long lVar4 = *plVar6;
        *(long*)(*plVar7 + 8) = *(long*)(lVar4 + 8);
        **(long**)(lVar4 + 8) = *plVar7;
        plVar8 = (long*)param_1[1];
        *(long**)(*param_1 + 8) = plVar7;
        *plVar7 = *param_1;
        *param_1 = lVar4;
        *(long**)(lVar4 + 8) = param_1;
        plVar10 = plVar9;
        param_1 = plVar7;
        if (plVar6 == plVar8) {
            return plVar7;
        }
    } else {
        plVar8 = (long*)param_1[1];
        plVar9 = plVar7;
        plVar6 = plVar7;
        plVar10 = plVar7;
        if (plVar7 == plVar8) {
            return param_1;
        }
    }

    // Continue merging
    do {
        if (plVar9 == param_2) {
            return param_1;
        }
        bVar2 = ((u8(*)(void))((long*)(*(long*)plVar9[2]))[0x55])();
        bVar3 = ((u8(*)(void))((long*)(*(long*)plVar8[2]))[0x55])();
        if (bVar2 < bVar3) {
            long* plVar11;
            long* plVar7b;
            for (plVar11 = (long*)plVar9[1]; plVar7b = param_2, plVar11 != param_2;
                 plVar11 = (long*)plVar11[1]) {
                bVar2 = ((u8(*)(void))((long*)(*(long*)plVar11[2]))[0x55])();
                bVar3 = ((u8(*)(void))((long*)(*(long*)plVar8[2]))[0x55])();
                plVar7b = plVar11;
                if (bVar3 <= bVar2) break;
            }
            long lVar4 = *plVar7b;
            long* plVar1;
            if (plVar6 != plVar9) {
                plVar1 = plVar10;
            } else {
                plVar1 = plVar11;
            }
            *(long*)(*plVar9 + 8) = *(long*)(lVar4 + 8);
            **(long**)(lVar4 + 8) = *plVar9;
            long* plVar7c = (long*)plVar8[1];
            *(long**)(*plVar8 + 8) = plVar9;
            *plVar9 = *plVar8;
            *plVar8 = lVar4;
            *(long**)(lVar4 + 8) = plVar8;
            plVar9 = plVar11;
            plVar10 = plVar1;
        } else {
            long* plVar7c = (long*)plVar8[1];
            plVar8 = plVar7c;
        }
        plVar6 = plVar10;
        // Ghidra: plVar8 = plVar7c (already set above)
    } while (plVar8 != plVar10);

    return param_1;
}

// ============================================================================
// FUN_710354e180 — container_destructor_with_vectors_and_hashmap
// Destructor that clears a vector of 0x20-byte entries (destroying each via
// vtable), frees nodes from a hash map linked list, zeroes the hash buckets,
// then destroys two more reversed vectors of entries.
// [derived: field layout: +0x20=hash_head, +0x28=hash_count, +0x10=hash_buckets,
//   +0x18=hash_bucket_count, +0x38/+0x40=vector_a, +0x50/+0x58=vector_b]
// Address: 0x710354e180 (416 bytes)
// ============================================================================
void FUN_710354e180_e180(long param_1) {
    // Clear forward vector at +0x50..+0x58
    long lVar6 = *(long*)(param_1 + 0x58);
    void* puVar4 = PTR_VirtualFreeHook_71052a7a70;

    for (long lVar11 = *(long*)(param_1 + 0x50); lVar11 != lVar6; lVar11 += 0x20) {
        PTR_VirtualFreeHook_71052a7a70 = puVar4;
        long* plVar1 = *(long**)(lVar11 + 8);
        long* plVar3 = *(long**)(lVar11 + 0x10);
        long lVar7 = *(long*)(lVar11 + 0x18);
        *(long*)(lVar11 + 8) = 0;
        *(long*)(lVar11 + 0x10) = 0;
        *(long*)(lVar11 + 0x18) = 0;
        if (plVar3 != nullptr && plVar1 != nullptr && *plVar3 == lVar7) {
            ((void(*)(void))((long*)*plVar1)[1])();
        }
        puVar4 = PTR_VirtualFreeHook_71052a7a70;
    }

    // Free hash map nodes at +0x20 if count > 0
    if (*(long*)(param_1 + 0x28) != 0) {
        long* plVar1 = *(long**)(param_1 + 0x20);
        while (plVar1 != nullptr) {
            long lVar11 = *plVar1;
            if ((*(u8*)(plVar1 + 2) & 1) != 0) {
                void* pvVar10 = (void*)plVar1[4];
                if (puVar4 != nullptr) {
                    FUN_71039c1400(pvVar10);  // VirtualFreeHook
                }
                FUN_710392e590(pvVar10);
            }
            FUN_710392e590(plVar1);
            plVar1 = (long*)lVar11;
        }

        // Zero hash buckets
        u64 uVar8 = *(u64*)(param_1 + 0x18);
        *(long*)(param_1 + 0x20) = 0;
        if (uVar8 != 0) {
            u64 uVar5 = uVar8 & 3;
            long lVar11;
            if (uVar8 - 1 < 3) {
                lVar11 = 0;
            } else {
                lVar11 = 0;
                do {
                    long lVar6b = lVar11 * 8;
                    lVar11 += 4;
                    *(long*)(*(long*)(param_1 + 0x10) + lVar6b) = 0;
                    *(long*)(*(long*)(param_1 + 0x10) + lVar6b + 8) = 0;
                    *(long*)(*(long*)(param_1 + 0x10) + lVar6b + 0x10) = 0;
                    *(long*)(*(long*)(param_1 + 0x10) + lVar6b + 0x18) = 0;
                } while (uVar8 - uVar5 != (u64)lVar11);
            }
            if (uVar5 != 0) {
                lVar11 <<= 3;
                long lVar6b = -(long)uVar5;
                do {
                    *(long*)(*(long*)(param_1 + 0x10) + lVar11) = 0;
                    lVar11 += 8;
                    lVar6b++;
                } while (lVar6b != 0);
            }
        }
        *(long*)(param_1 + 0x28) = 0;
    }

    // Destroy reversed vector_b at +0x50..+0x58
    long* puVar2 = *(long**)(param_1 + 0x50);
    long* puVar9 = *(long**)(param_1 + 0x58);
    while (puVar9 != puVar2) {
        puVar9 -= 4;
        ((void(*)(long*))((long*)*puVar9)[0])(puVar9);
    }
    *(long**)(param_1 + 0x58) = puVar2;

    // Destroy reversed vector_a at +0x38..+0x40
    puVar2 = *(long**)(param_1 + 0x38);
    puVar9 = *(long**)(param_1 + 0x40);
    while (puVar9 != puVar2) {
        puVar9 -= 4;
        ((void(*)(long*))((long*)*puVar9)[0])(puVar9);
    }
    *(long**)(param_1 + 0x40) = puVar2;
}

// ============================================================================
// FUN_710354b800 — destroy_three_deques
// Destroys 3 std::deque-like structures stored at consecutive offsets in
// param_1. Each deque uses a map of 4096-byte blocks with 512 8-byte elements.
// Pattern: clear iterator, shrink map, free blocks and map.
// [derived: deque layout per instance = 6 longs: [0]=allocator, [1..2]=map_start/end,
//   [3]=unused, [4]=start_offset, [5]=size]
// Address: 0x710354b800 (912 bytes)
// ============================================================================
static void destroy_deque(long* base) {
    // base: pointer to deque internal fields
    // layout: [0xd]=map_start, [0xe]=map_end, [0x10]=start_offset, [0x11]=size
    // But for clarity, we use the same raw offsets as Ghidra
    long* plVar5 = (long*)base[0xd];
    long* plVar6 = (long*)base[0xe];
    long lVar1 = (long)plVar6 - (long)plVar5;

    if (lVar1 != 0) {
        u64 uVar4 = base[0x10];
        long* plVar2 = (long*)((long)plVar5 + (uVar4 >> 6 & 0x3fffffffffffff8ULL));
        long lVar3 = *plVar2 + (uVar4 & 0x1ff) * 8;
        while (*(long*)((long)plVar5 + (base[0x11] + uVar4 >> 6 & 0x3fffffffffffff8ULL)) +
               (base[0x11] + uVar4 & 0x1ff) * 8 != lVar3) {
            lVar3 += 8;
            if (lVar3 - *plVar2 == 0x1000) {
                plVar2++;
                lVar3 = *plVar2;
            }
        }
    }

    base[0x11] = 0;

    u64 uVar4;
    while (uVar4 = lVar1 >> 3, 2 < uVar4) {
        if (*plVar5 != 0) {
            FUN_710392e590((void*)*plVar5);
            plVar5 = (long*)base[0xd];
            plVar6 = (long*)base[0xe];
        }
        plVar5++;
        base[0xd] = (long)plVar5;
        lVar1 = (long)plVar6 - (long)plVar5;
    }

    if (uVar4 == 1) {
        base[0x10] = 0x100;
    } else if (uVar4 == 2) {
        base[0x10] = 0x200;
    }

    if (plVar5 != plVar6) {
        do {
            if (*plVar5 != 0) {
                FUN_710392e590((void*)*plVar5);
            }
            plVar5++;
        } while (plVar6 != plVar5);
        lVar1 = base[0xe];
        if (lVar1 != base[0xd]) {
            base[0xe] = lVar1 + (~((lVar1 - 8) - base[0xd]) & 0xfffffffffffffff8ULL);
        }
    }

    if (base[0xc] != 0) {
        FUN_710392e590((void*)base[0xc]);
    }
}

void FUN_710354b800_b800(long* param_1) {
    // Deque 1: at param_1 offsets [0xd..0x11] → byte offsets +0x68..+0x88
    destroy_deque(param_1);

    // Deque 2: at param_1 offsets [7..0xb] → byte offsets +0x38..+0x58
    {
        long* plVar5 = (long*)param_1[7];
        long* plVar6 = (long*)param_1[8];
        long lVar1 = (long)plVar6 - (long)plVar5;

        if (lVar1 != 0) {
            u64 uVar4 = param_1[10];
            long* plVar2 = (long*)((long)plVar5 + (uVar4 >> 6 & 0x3fffffffffffff8ULL));
            long lVar3 = *plVar2 + (uVar4 & 0x1ff) * 8;
            while (*(long*)((long)plVar5 + (param_1[0xb] + uVar4 >> 6 & 0x3fffffffffffff8ULL)) +
                   (param_1[0xb] + uVar4 & 0x1ff) * 8 != lVar3) {
                lVar3 += 8;
                if (lVar3 - *plVar2 == 0x1000) {
                    plVar2++;
                    lVar3 = *plVar2;
                }
            }
        }

        param_1[0xb] = 0;

        u64 uVar4b;
        while (uVar4b = lVar1 >> 3, 2 < uVar4b) {
            if (*plVar5 != 0) {
                FUN_710392e590((void*)*plVar5);
                plVar5 = (long*)param_1[7];
                plVar6 = (long*)param_1[8];
            }
            plVar5++;
            param_1[7] = (long)plVar5;
            lVar1 = (long)plVar6 - (long)plVar5;
        }

        if (uVar4b == 1) {
            param_1[10] = 0x100;
        } else if (uVar4b == 2) {
            param_1[10] = 0x200;
        }

        if (plVar5 != plVar6) {
            do {
                if (*plVar5 != 0) FUN_710392e590((void*)*plVar5);
                plVar5++;
            } while (plVar6 != plVar5);
            long lVar1b = param_1[8];
            if (lVar1b != param_1[7]) {
                param_1[8] = lVar1b + (~((lVar1b - 8) - param_1[7]) & 0xfffffffffffffff8ULL);
            }
        }

        if (param_1[6] != 0) FUN_710392e590((void*)param_1[6]);
    }

    // Deque 3: at param_1 offsets [1..5] → byte offsets +0x08..+0x28
    {
        long* plVar5 = (long*)param_1[1];
        long* plVar6 = (long*)param_1[2];
        long lVar1 = (long)plVar6 - (long)plVar5;

        if (lVar1 != 0) {
            u64 uVar4 = param_1[4];
            long* plVar2 = (long*)((long)plVar5 + (uVar4 >> 6 & 0x3fffffffffffff8ULL));
            long lVar3 = *plVar2 + (uVar4 & 0x1ff) * 8;
            while (*(long*)((long)plVar5 + (param_1[5] + uVar4 >> 6 & 0x3fffffffffffff8ULL)) +
                   (param_1[5] + uVar4 & 0x1ff) * 8 != lVar3) {
                lVar3 += 8;
                if (lVar3 - *plVar2 == 0x1000) {
                    plVar2++;
                    lVar3 = *plVar2;
                }
            }
        }

        param_1[5] = 0;

        u64 uVar4b;
        while (uVar4b = lVar1 >> 3, 2 < uVar4b) {
            if (*plVar5 != 0) {
                FUN_710392e590((void*)*plVar5);
                plVar5 = (long*)param_1[1];
                plVar6 = (long*)param_1[2];
            }
            plVar5++;
            param_1[1] = (long)plVar5;
            lVar1 = (long)plVar6 - (long)plVar5;
        }

        if (uVar4b == 1) {
            lVar1 = 0x100;
        } else if (uVar4b != 2) {
            goto skip_offset;
        } else {
            lVar1 = 0x200;
        }
        param_1[4] = lVar1;

skip_offset:
        if (plVar5 != plVar6) {
            do {
                if (*plVar5 != 0) FUN_710392e590((void*)*plVar5);
                plVar5++;
            } while (plVar6 != plVar5);
            lVar1 = param_1[2];
            if (lVar1 != param_1[1]) {
                param_1[2] = lVar1 + (~((lVar1 - 8) - param_1[1]) & 0xfffffffffffffff8ULL);
            }
        }

        if (*param_1 != 0) FUN_710392e590((void*)*param_1);
    }
}

// ============================================================================
// FUN_710354b4b0 — fiber_scheduler_destructor
// Destructor for a fiber-based task scheduler. Drains pending task vectors
// into a deque, destroys all fibers in the deque, cleans up deques, destroys
// mutex, and calls FUN_710354b800 to destroy sub-deques.
// [derived: scheduler layout: +0xA0=mutex, +0xE0..+0xF0=task_vector_a,
//   +0xF8..+0x100=task_vector_b, +0x110..=deque(s), +0x148=LightEvent]
// Address: 0x710354b4b0 (848 bytes)
// ============================================================================
void FUN_710354b4b0_b4b0(long param_1) {
    // Drain task vector at +0xE0..+0xE8 into deque
    long lVar11 = *(long*)(param_1 + 0xe0);
    long lVar9 = *(long*)(param_1 + 0xe8);
    if (lVar11 != lVar9) {
        long lVar6 = *(long*)(param_1 + 0x138);
        do {
            long lVar8 = *(long*)(param_1 + 0x118);
            long lVar5 = *(long*)(param_1 + 0x120) - lVar8;
            long uVar14 = *(long*)(lVar11 + 0x10);
            u64 uVar12 = lVar6 + *(long*)(param_1 + 0x130);
            u64 uVar3 = 0;
            if (lVar5 != 0) uVar3 = (u64)lVar5 * 0x40 - 1;
            if (uVar3 == uVar12) {
                FUN_710354a7e0(param_1 + 0x110);
                lVar8 = *(long*)(param_1 + 0x118);
                uVar12 = *(long*)(param_1 + 0x130) + *(long*)(param_1 + 0x138);
            }
            lVar11 += 0x20;
            *(long*)(*(long*)(lVar8 + (uVar12 >> 6 & 0x3fffffffffffff8ULL)) + (uVar12 & 0x1ff) * 8) = uVar14;
            lVar6 = *(long*)(param_1 + 0x138) + 1;
            *(long*)(param_1 + 0x138) = lVar6;
        } while (lVar9 != lVar11);
    }

    // Drain task vector at +0xF8..+0x100 into same deque
    lVar11 = *(long*)(param_1 + 0xf8);
    lVar9 = *(long*)(param_1 + 0x100);
    long* plVar1 = (long*)(param_1 + 0x138);
    long lVar6;
    if (lVar11 == lVar9) {
        lVar6 = *(long*)(param_1 + 0x138);
    } else {
        lVar6 = *(long*)(param_1 + 0x138);
        do {
            long lVar8 = *(long*)(param_1 + 0x118);
            long lVar5 = *(long*)(param_1 + 0x120) - lVar8;
            long uVar14 = *(long*)(lVar11 + 0x10);
            u64 uVar12 = lVar6 + *(long*)(param_1 + 0x130);
            u64 uVar3 = 0;
            if (lVar5 != 0) uVar3 = (u64)lVar5 * 0x40 - 1;
            if (uVar3 == uVar12) {
                FUN_710354a7e0(param_1 + 0x110);
                lVar8 = *(long*)(param_1 + 0x118);
                uVar12 = *(long*)(param_1 + 0x130) + *(long*)(param_1 + 0x138);
            }
            lVar11 += 0x20;
            *(long*)(*(long*)(lVar8 + (uVar12 >> 6 & 0x3fffffffffffff8ULL)) + (uVar12 & 0x1ff) * 8) = uVar14;
            lVar6 = *plVar1 + 1;
            *plVar1 = lVar6;
        } while (lVar9 != lVar11);
    }

    // Pop and destroy fibers from deque
    if (lVar6 != 0) {
        long* plVar2 = (long*)(param_1 + 0x120);
        do {
            long lVar8 = *(long*)(param_1 + 0x130);
            long lVar9b = lVar6 - 1;
            lVar11 = *(long*)(param_1 + 0x118);
            phx::Fiber* fiber = *(phx::Fiber**)
                (*(long*)(lVar11 + ((u64)(lVar9b + lVar8) >> 6 & 0x3fffffffffffff8ULL)) +
                (u64)(lVar9b + lVar8 & 0x1ff) * 8);
            if (fiber != nullptr) {
                Fiber_dtor_353c210(fiber);
                FUN_710392e590(fiber);
                lVar6 = *plVar1;
                lVar8 = *(long*)(param_1 + 0x130);
                lVar9b = lVar6 - 1;
                lVar11 = *(long*)(param_1 + 0x118);
            }
            *plVar1 = lVar9b;
            lVar11 = *plVar2 - lVar11;
            long lVar7 = 1 - lVar6;
            long lVar5 = 0;
            if (lVar11 != 0) lVar5 = lVar11 * 0x40 - 1;
            lVar6 = lVar9b;
            if (0x3ff < (u64)((lVar7 - lVar8) + lVar5)) {
                long* plVar13 = (long*)(*plVar2 - 8);
                if (*plVar13 != 0) {
                    FUN_710392e590((void*)*plVar13);
                    lVar9b = *plVar1;
                    plVar13 = (long*)(*plVar2 - 8);
                }
                *plVar2 = (long)plVar13;
                lVar6 = lVar9b;
            }
        } while (lVar6 != 0);
    }

    // Finalize light event at +0x148
    FUN_71039c0610((void*)(param_1 + 0x148));

    // Cleanup deque internals at +0x118..+0x138
    {
        long* plVar13 = *(long**)(param_1 + 0x118);
        long* plVar4 = plVar13;
        long* plVar15 = *(long**)(param_1 + 0x120);
        lVar11 = (long)plVar15 - (long)plVar13;

        if (lVar11 != 0) {
            u64 uVar12 = *(u64*)(param_1 + 0x130);
            long* plVar10 = (long*)((long)plVar13 + (uVar12 >> 6 & 0x3fffffffffffff8ULL));
            long lVar9c = *plVar10 + (uVar12 & 0x1ff) * 8;
            while (*(long*)((long)plVar13 + (*plVar1 + uVar12 >> 6 & 0x3fffffffffffff8ULL)) +
                   (*plVar1 + uVar12 & 0x1ff) * 8 != lVar9c) {
                lVar9c += 8;
                if (lVar9c - *plVar10 == 0x1000) {
                    plVar10++;
                    lVar9c = *plVar10;
                }
            }
        }

        *plVar1 = 0;
        u64 uVar12;
        while (uVar12 = lVar11 >> 3, 2 < uVar12) {
            if (*plVar4 != 0) {
                FUN_710392e590((void*)*plVar4);
                plVar4 = *(long**)(param_1 + 0x118);
                plVar15 = *(long**)(param_1 + 0x120);
            }
            plVar4++;
            *(long*)(param_1 + 0x118) = (long)plVar4;
            lVar11 = (long)plVar15 - (long)plVar4;
        }

        long uVar14;
        if (uVar12 == 1) {
            uVar14 = 0x100;
        } else if (uVar12 == 2) {
            uVar14 = 0x200;
        } else {
            goto skip_set;
        }
        *(long*)(param_1 + 0x130) = uVar14;

skip_set:
        if (plVar4 != plVar15) {
            do {
                if (*plVar4 != 0) FUN_710392e590((void*)*plVar4);
                plVar4++;
            } while (plVar15 != plVar4);
            lVar11 = *(long*)(param_1 + 0x120);
            if (lVar11 != *(long*)(param_1 + 0x118)) {
                *(long*)(param_1 + 0x120) = lVar11 + (~((lVar11 - 8) - *(long*)(param_1 + 0x118)) & 0xfffffffffffffff8ULL);
            }
        }

        if (*(long*)(param_1 + 0x110) != 0) FUN_710392e590(*(void**)(param_1 + 0x110));
    }

    // Free task vectors
    if (*(long*)(param_1 + 0xf8) != 0) {
        *(long*)(param_1 + 0x100) = *(long*)(param_1 + 0xf8);
        FUN_710392e590(*(void**)(param_1 + 0xf8));
    }
    if (*(long*)(param_1 + 0xe0) != 0) {
        *(long*)(param_1 + 0xe8) = *(long*)(param_1 + 0xe0);
        FUN_710392e590(*(void**)(param_1 + 0xe0));
    }

    // Destroy mutex at +0xA0
    FUN_71039c14d0((void*)(param_1 + 0xa0));

    // Destroy sub-deques via FUN_710354b800
    FUN_710354b800_b800((long*)(param_1 + 0x10));
}

// End of file
