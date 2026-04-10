// res_remaining_medium.cpp — Resource service medium infrastructure functions
// Pool allocator, fiber scheduler, container operations for phx task system.
// See WORKER-pool-c.md for assignment details.

#include "types.h"
#include "resource/Fiber.h"
#include "resource/TaskInfra.h"

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

// Forward declaration
void pool_block_init(phx::PoolBlock* block, long elem_size, u32 count, long alloc_func_ptr, long* dealloc_func_ptr);

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
// OOM retry helper — attempts allocation, retries once via OOM handler if
// the first attempt fails and an OOM handler singleton is registered.
// [derived: pattern appears in pool_acquire, vector growth, and emplace_back]
// ============================================================================
static void* alloc_with_oom_retry(u64 alignment, u64 size) {
    void* ptr = je_aligned_alloc(alignment, size);
    if (ptr != nullptr) return ptr;

    if (DAT_7105331f00 != nullptr) {
        u32 unused = 0;
        long alloc_size = (long)size;
        u64 result = ((u64(*)(s64*, u32*, long*))(*(s64*)(*DAT_7105331f00 + 0x30)))
                     (DAT_7105331f00, &unused, &alloc_size);
        if ((result & 1) != 0) {
            ptr = je_aligned_alloc(alignment, size);
            if (ptr != nullptr) return ptr;
        }
    }
    return nullptr;
}

// ============================================================================
// std::function clone/destroy helpers — these operate on StdFunction32
// (libc++ std::function with 32-byte SBO buffer). The vtable layout is:
//   [2] = clone (heap), [3] = move_construct (SBO), [4] = destroy_local, [5] = destroy_heap
// [derived: pool_block_init at 0x7103546c40 uses all four vtable slots]
// ============================================================================

// Clone src function into local buffer + impl pointer.
// After return, local_buf holds SBO data and local_impl points to either
// local_buf (SBO), a heap clone, or nullptr (empty).
static void stdfunc32_clone(phx::StdFunction32* src, long* local_buf, long** local_impl) {
    long* src_impl = (long*)src->impl;
    if (src_impl == nullptr) {
        *local_impl = nullptr;
    } else if (src->buf == src_impl) {
        // SBO: move_construct into local buffer
        *local_impl = local_buf;
        ((void(*)(long*, long*))((long*)*src_impl)[3])(src_impl, local_buf);
    } else {
        // Heap: clone
        *local_impl = (long*)((long*(*)(void))((long*)*src_impl)[2])();
    }
}

// Destroy a locally-cloned std::function.
static void stdfunc32_destroy_local(long* local_buf, long* local_impl) {
    if (local_buf == local_impl) {
        ((void(*)(void))((long*)*local_impl)[4])();
    } else if (local_impl != nullptr) {
        ((void(*)(void))((long*)*local_impl)[5])();
    }
}

// Release a shared_ptr control block: decrement refcount, destroy + release_weak if zero.
static void shared_ptr_release(void* ctrl_raw) {
    long* ctrl = (long*)ctrl_raw;
    if (ctrl != nullptr) {
        long old = __atomic_fetch_sub(ctrl + 1, 1, __ATOMIC_RELAXED);
        if (old == 0) {
            ((void(*)(long*))((long*)*ctrl)[2])(ctrl);
            reinterpret_cast<std::__1::__shared_weak_count*>(ctrl)->__release_weak();
        }
    }
}

// ============================================================================
// pool_block_init — Initializes a pool block
// Stores element config, clones a std::function allocator, allocates
// count*element_size bytes via the allocator, zeroes the buffer,
// and builds a freelist through the allocated elements.
// Address: 0x7103546c40 (336 bytes)
// ============================================================================
void pool_block_init(phx::PoolBlock* block, long elem_size, u32 count, long alloc_func_ptr, long* dealloc_func_ptr) {
    long local_buf[4];
    long* local_impl = (long*)local_buf;

    block->element_size = (u32)elem_size;
    block->max_count = count;

    // Clone std::function from dealloc_func_ptr to local
    phx::StdFunction32* src_func = reinterpret_cast<phx::StdFunction32*>(dealloc_func_ptr);
    stdfunc32_clone(src_func, local_buf, &local_impl);

    // Move the cloned function to block+0x30
    FUN_7101f6f1f0(local_buf, &block->allocator);

    // Destroy the local clone
    stdfunc32_destroy_local(local_buf, local_impl);

    // Allocate buffer: count * element_size bytes
    u64 total_size = (u64)count * (u64)elem_size;
    long alignment = 8;
    phx::StdFunction32* alloc = reinterpret_cast<phx::StdFunction32*>(alloc_func_ptr);
    long* alloc_impl = *(long**)(alloc_func_ptr + 0x20);
    local_buf[0] = (long)total_size;
    if (alloc_impl == nullptr) {
        abort();
    }

    // Call allocator via vtable[6] (+0x30) = allocate(this, &size, &alignment)
    void* buf = (void*)((long*(*)(long*, long*, long*))((long*)*alloc_impl)[6])(alloc_impl, local_buf, &alignment);
    memset(buf, 0, total_size);
    void* end = (void*)((u64)buf + total_size);

    // Set pool block fields
    block->freelist_head = nullptr;
    block->base_ptr = buf;
    block->end_ptr = end;
    block->free_count = count;

    // Build freelist: chain elements from base to end
    u8* cursor = (u8*)buf;
    if (cursor + elem_size <= (u8*)end) {
        void* prev = nullptr;
        do {
            *(void**)cursor = prev;
            block->freelist_head = cursor;
            u8* next_cursor = cursor + elem_size;
            prev = cursor;
            cursor = next_cursor;
        } while (cursor + elem_size <= (u8*)end);
    }
}

// ============================================================================
// pool_acquire — Acquires a free element from the pool
// Scans the block array for a block with a non-empty freelist. If none found,
// allocates a new PoolBlock, initializes it, and adds it to the block array
// (with vector-style growth). Pops and returns the first free element.
// Address: 0x7103546d90 (816 bytes)
// ============================================================================
void* FUN_7103546d90_6d90(phx::PoolManager* mgr) {
    long alloc_clone_buf[4];
    long* alloc_clone_impl;
    long dealloc_clone_buf[4];
    long* dealloc_clone_impl;
    long grow_size;
    u32 grow_unused;

    phx::PoolBlock** scan = mgr->blocks_start;
    phx::PoolBlock* found_block;
    void* freelist;

    while (true) {
        if (scan == mgr->blocks_end) {
            // No free slot in any existing block — allocate a new one
            phx::PoolBlock* new_block = (phx::PoolBlock*)alloc_with_oom_retry(0x10, 0x60);

            if (new_block == nullptr) {
                new_block = nullptr;
            }

            // Zero-init the new block
            new_block->allocator.impl = nullptr;  // +0x50
            new_block->free_count = 0;
            new_block->base_ptr = nullptr;
            new_block->end_ptr = nullptr;
            new_block->freelist_head = nullptr;
            *(u64*)&new_block->element_size = 0;   // zeroes both element_size and max_count

            // Copy config from pool manager
            u64 elem_size = mgr->element_size;
            u32 init_count = mgr->initial_count;

            // Clone alloc_func from manager
            long* alloc_impl = (long*)mgr->alloc_func.impl;
            long* dealloc_impl;
            if (alloc_impl == nullptr) {
                alloc_clone_impl = nullptr;
                dealloc_impl = (long*)mgr->dealloc_func.impl;
                if (dealloc_impl != nullptr) goto clone_dealloc;
                dealloc_clone_impl = nullptr;
            } else {
                if ((long*)mgr->alloc_func.buf == alloc_impl) {
                    alloc_clone_impl = (long*)dealloc_clone_buf;
                    ((void(*)(long*, long*))((long*)*alloc_impl)[3])(alloc_impl, dealloc_clone_buf);
                    dealloc_impl = (long*)mgr->dealloc_func.impl;
                    if (dealloc_impl != nullptr) goto clone_dealloc;
                    dealloc_clone_impl = nullptr;
                } else {
                    alloc_clone_impl = (long*)((long*(*)(void))((long*)*alloc_impl)[2])();
                    dealloc_impl = (long*)mgr->dealloc_func.impl;
                    if (dealloc_impl == nullptr) {
                        dealloc_clone_impl = nullptr;
                    } else {
clone_dealloc:
                        if ((long*)mgr->dealloc_func.buf == dealloc_impl) {
                            dealloc_clone_impl = (long*)alloc_clone_buf;
                            ((void(*)(long*, long*))((long*)*dealloc_impl)[3])(dealloc_impl, alloc_clone_buf);
                        } else {
                            dealloc_clone_impl = (long*)((long*(*)(void))((long*)*dealloc_impl)[2])();
                        }
                    }
                }
            }

            // Init the new block
            pool_block_init(new_block, elem_size, init_count, (long)dealloc_clone_buf, alloc_clone_buf);

            // Destroy local clone of dealloc function
            stdfunc32_destroy_local(alloc_clone_buf, dealloc_clone_impl);

            // Destroy local clone of alloc function
            stdfunc32_destroy_local(dealloc_clone_buf, alloc_clone_impl);

            // Push new block pointer into blocks array
            scan = mgr->blocks_end;
            if (scan == mgr->blocks_capacity) {
                // Vector growth: allocate new array, copy, free old
                void* old_start = (void*)mgr->blocks_start;
                u64 old_byte_count = (u64)scan - (u64)old_start;
                u64 new_count = (old_byte_count >> 3) + 1;
                if ((new_count >> 0x3d) != 0) {
                    std::__1::__throw_length_error("vector");
                }
                u64 old_cap_bytes = (u64)mgr->blocks_capacity - (u64)old_start;
                u64 new_cap;
                if ((u64)(old_cap_bytes >> 3) < 0xfffffffffffffffULL) {
                    new_cap = old_cap_bytes >> 2;
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
                    void* new_buf = alloc_with_oom_retry(0x10, alloc_size);
                    if (new_buf != nullptr) {
                        scan = (phx::PoolBlock**)((u64)new_buf + (old_byte_count >> 3) * 8);
                        *scan = new_block;
                        if (0 < (long)old_byte_count) {
                            memcpy(new_buf, old_start, old_byte_count);
                        }
                        mgr->blocks_start = (phx::PoolBlock**)new_buf;
                        mgr->blocks_end = scan + 1;
                        mgr->blocks_capacity = (phx::PoolBlock**)((u64)new_buf + new_cap * 8);
                        if (old_start != nullptr) {
                            FUN_710392e590(old_start);
                        }
                        freelist = new_block->freelist_head;
                        goto check_freelist;
                    }
                }
null_alloc:;
                void* null_buf = nullptr;
                scan = (phx::PoolBlock**)((u64)null_buf + (old_byte_count >> 3) * 8);
                *scan = new_block;
                if (0 < (long)old_byte_count) {
                    memcpy(null_buf, old_start, old_byte_count);
                }
                mgr->blocks_start = (phx::PoolBlock**)null_buf;
                mgr->blocks_end = scan + 1;
                mgr->blocks_capacity = (phx::PoolBlock**)((u64)null_buf + new_cap * 8);
                if (old_start != nullptr) {
                    FUN_710392e590(old_start);
                }
                freelist = new_block->freelist_head;
            } else {
                *scan = new_block;
                mgr->blocks_end = (phx::PoolBlock**)((u64)mgr->blocks_end + 8);
                freelist = new_block->freelist_head;
            }
check_freelist:
            if (freelist == nullptr) {
                return nullptr;
            }
            found_block = new_block;
            break;
        }

        found_block = *scan;
        freelist = found_block->freelist_head;
        scan++;
        if (freelist != nullptr) break;
    }

    // Pop from freelist
    found_block->freelist_head = *(void**)freelist;
    found_block->free_count = found_block->free_count - 1;

    return freelist;
}

// ============================================================================
// fiber_scheduler_push_task — Pushes a task onto the fiber scheduler work queue
// Gets the scheduler context from TLS, stores task data into a 0x20-byte
// WorkEntry in the work vector. If no active fiber exists, creates one and
// switches to it.
// Address: 0x710354c720 (544 bytes)
// ============================================================================
void FUN_710354c720_c720(u32 tls_slot, int* task_count) {
    phx::FiberSchedulerTLS* sched;
    if (tls_slot == 0xFFFFFFFF) {
        sched = nullptr;
    } else {
        sched = (phx::FiberSchedulerTLS*)FUN_71039c0510(tls_slot);
    }

    if (*task_count < 1) return;

    phx::WorkEntry* vec_end = sched->work_end;
    void** current_task_ptr = (void**)&sched->current_task;
    sched->current_param = task_count;

    if (vec_end != sched->work_capacity) {
        // Append to existing vector
        void* saved_task = sched->current_task;
        void* saved_param = sched->current_param;
        u64 saved_id = *(u64*)&sched->current_id;
        vec_end->fiber = sched->current_fiber;
        *(u64*)&vec_end->id = saved_id;
        vec_end->task = saved_task;
        vec_end->param = saved_param;
        sched->work_end = vec_end + 1;
    } else {
        // Vector full — grow with OOM retry
        void* old_start = (void*)sched->work_start;
        u64 old_byte_count = (u64)vec_end - (u64)old_start;
        u64 new_count = (old_byte_count >> 5) + 1;
        if ((new_count >> 0x3b) != 0) {
            std::__1::__throw_length_error("vector");
        }
        u64 old_cap_bytes = (u64)sched->work_capacity - (u64)old_start;
        void* new_buf;
        u64 new_cap;
        if ((u64)(old_cap_bytes >> 5) < 0x3fffffffffffffffULL) {
            new_cap = old_cap_bytes >> 4;
            if (new_count > new_cap) new_cap = new_count;
            if (new_cap != 0) {
                if ((new_cap >> 0x3b) != 0) abort();
                goto grow_alloc;
            }
            new_buf = nullptr;
        } else {
            new_cap = 0x7fffffffffffffffULL;
grow_alloc:;
            u64 alloc_size = new_cap * 0x20;
            if (alloc_size == 0) alloc_size = 1;
            new_buf = alloc_with_oom_retry(0x10, alloc_size);
            if (new_buf == nullptr) {
                new_buf = nullptr;
            }
        }
        void* saved_task = sched->current_task;
        void* saved_param = sched->current_param;
        phx::WorkEntry* dest = (phx::WorkEntry*)((u64)new_buf + (old_byte_count >> 5) * 0x20);
        u64 saved_id = *(u64*)&sched->current_id;
        dest->fiber = sched->current_fiber;
        *(u64*)&dest->id = saved_id;
        dest->task = saved_task;
        dest->param = saved_param;
        if (0 < (long)old_byte_count) {
            memcpy(new_buf, old_start, old_byte_count);
        }
        sched->work_start = (phx::WorkEntry*)new_buf;
        sched->work_end = dest + 1;
        sched->work_capacity = (phx::WorkEntry*)((u64)new_buf + new_cap * 0x20);
        if (old_start != nullptr) {
            FUN_710392e590(old_start);
        }
    }

    phx::Fiber* fiber = sched->current_fiber;
    if (fiber == nullptr) {
        phx::Fiber* new_fiber = (phx::Fiber*)FUN_7103549f00((long)sched);
        sched->current_fiber = new_fiber;
        Fiber_switch_to_fiber_353c400(new_fiber);
        sched->current_param = nullptr;
        sched->current_fiber = nullptr;
        sched->current_task = nullptr;
        sched->current_id = 0xFFFFFFFF;
        return;
    }
    sched->current_task = nullptr;
    sched->current_param = nullptr;
    sched->current_fiber = nullptr;
    sched->current_id = 0xFFFFFFFF;
    phx::Fiber* new_fiber = (phx::Fiber*)FUN_7103549f00((long)sched);
    sched->current_fiber = new_fiber;
    Fiber_switch_to_fiber_353c400(new_fiber);
}

// ============================================================================
// task_request_destructor — Destructor for TaskRequest (~0x790 bytes)
// Inherits from std::__1::__shared_weak_count. Sets vtable, locks internal
// mutex, resets all task fields to defaults, releases shared_ptr if held,
// unlocks, then destroys mutex and calls ~__shared_weak_count.
// Address: 0x710354e320 (448 bytes)
// ============================================================================
void FUN_710354e320_e320(phx::TaskRequest* req) {
    req->vtable = &PTR_FUN_710522eda8;

    FUN_71039c14b0(req);  // mutex::lock

    req->state = 1;
    req->status_flags = 0;
    req->sentinel = (u64)-1LL;

    // Release shared_ptr control block at +0x300 if held
    if (req->shared_ctrl != nullptr) {
        long* ctrl = (long*)req->shared_ctrl;
        ((void(*)(void))((long*)*ctrl)[1])();
        req->shared_ctrl = nullptr;
    }

    req->field_748 = 0;
    req->field_140 = 0;
    req->field_180 = 0;
    req->field_1c0 = 0;
    req->field_340 = 0;
    req->field_2c0 = 0;
    req->shared_ctrl = nullptr;
    req->field_240 = 0;
    req->field_280 = 0;

    FUN_71039c14c0(req);  // mutex::unlock

    FUN_71039c14d0(req->internal_mutex);  // mutex::~mutex at +0x780

    reinterpret_cast<std::__1::__shared_weak_count*>(req)->~__shared_weak_count();
}

// ============================================================================
// shared_ptr_list_container_destructor — Destructor for SharedPtrListContainer
// Sets vtable, destroys recursive_mutex, releases shared_ptrs in the vector
// (with atomic ref count decrement), then unlinks and frees all nodes in the
// doubly-linked list.
// Address: 0x710354cc80 (400 bytes)
// ============================================================================
void FUN_710354cc80_cc80(phx::SharedPtrListContainer* container) {
    container->vtable = &PTR_FUN_710522ed28;

    // Destroy recursive mutex at +0x38
    FUN_71039c1480(&container->recursive_mutex);

    // Release shared_ptrs in vector at +0x20..+0x28
    phx::SharedPtrElement* vec_start = container->vec_start;
    if (vec_start != nullptr) {
        phx::SharedPtrElement* vec_end = container->vec_end;

        if (vec_end == vec_start) {
            container->vec_end = vec_start;
        } else {
            // Release each shared_ptr in reverse order
            phx::SharedPtrElement* cursor = vec_end;
            do {
                cursor--;
                shared_ptr_release(cursor->ctrl_block);
            } while (cursor != vec_start);
            container->vec_end = vec_start;
            vec_end = container->vec_start;
        }

        if (vec_end != nullptr) {
            FUN_710392e590(vec_end);
        }
    }

    // Unlink and free doubly-linked list at +0x08..+0x18
    if (container->list_size != 0) {
        phx::TaskNode* first = container->list_head;
        phx::TaskNode* last = container->list_tail;

        // Unlink this range from the circular list
        last->next->prev = first->prev;
        *(phx::TaskNode**)first->prev = last->next;

        container->list_size = 0;

        // Free all nodes in the list
        phx::TaskNode* sentinel = reinterpret_cast<phx::TaskNode*>(&container->list_head);
        phx::TaskNode* node = last;
        while (node != sentinel) {
            phx::TaskNode* next_node = node->prev;
            shared_ptr_release(node->ctrl_block);
            if (node != nullptr) {
                FUN_710392e590(node);
            }
            node = next_node;
        }
    }
}

// ============================================================================
// vector_emplace_back_shared_ptr — Grows a vector of SharedPtrElement by one
// Allocates new storage with OOM retry, copies the new element, moves existing
// elements, and releases old storage. Includes atomic refcount increment for
// the shared_ptr control block.
// Address: 0x710354d130 (720 bytes)
// ============================================================================
void FUN_710354d130_d130(long* vec_fields, phx::SharedPtrElement* new_elem) {
    long vec_start = vec_fields[0];
    long vec_end = vec_fields[1];
    long elem_count = (vec_end - vec_start) / sizeof(phx::SharedPtrElement);
    u64 max_capacity = 0xaaaaaaaaaaaaaaaULL;
    u64 needed = (u64)elem_count + 1;

    if (0xaaaaaaaaaaaaaaaULL < needed) {
        std::__1::__throw_length_error("vector");
    }

    long vec_cap = vec_fields[2] - vec_start;
    long new_buf_base;
    u64 new_cap;

    u64 cap_elems = (u64)vec_cap / sizeof(phx::SharedPtrElement);
    if (cap_elems < 0x555555555555555ULL) {
        new_cap = cap_elems * 2;
        if (needed > new_cap) new_cap = needed;
        if (new_cap != 0) goto do_alloc;
    } else {
do_alloc:
        if (new_cap == 0) new_cap = max_capacity;
        long alloc_size = (long)(new_cap * sizeof(phx::SharedPtrElement));
        if (alloc_size == 0) alloc_size = 1;

        new_buf_base = (long)alloc_with_oom_retry(0x10, alloc_size);
        if (new_buf_base != 0) goto alloc_ok;
    }
    new_buf_base = 0;
alloc_ok:;
    phx::SharedPtrElement* insert_pos = (phx::SharedPtrElement*)(new_buf_base + elem_count * sizeof(phx::SharedPtrElement));
    insert_pos->ptr = new_elem->ptr;
    long ctrl = (long)new_elem->ctrl_block;
    insert_pos->ctrl_block = (void*)ctrl;

    if (ctrl != 0) {
        // Atomic increment refcount of shared_ptr control block
        __atomic_fetch_add((long*)(ctrl + 8), 1, __ATOMIC_RELAXED);
        vec_start = vec_fields[0];
        vec_end = vec_fields[1];
    }

    insert_pos->flag = new_elem->flag;
    phx::SharedPtrElement* after_insert = insert_pos + 1;

    // Move existing elements from old to new buffer (reverse order)
    long move_end = vec_end;
    long move_offset = 0;
    if (vec_end != vec_start) {
        long offset = 0;
        do {
            long src_pos = vec_end + offset;
            phx::SharedPtrElement* dst = (phx::SharedPtrElement*)((long)insert_pos + offset - sizeof(phx::SharedPtrElement));
            phx::SharedPtrElement* src = (phx::SharedPtrElement*)(src_pos - sizeof(phx::SharedPtrElement));
            dst->ptr = src->ptr;
            dst->ctrl_block = src->ctrl_block;
            src->ptr = nullptr;
            src->ctrl_block = nullptr;
            *(u8*)((long)insert_pos + offset - 8) = *(u8*)(src_pos - 8);
            move_offset = offset - (long)sizeof(phx::SharedPtrElement);
            offset = move_offset;
        } while (vec_start - vec_end != move_offset);
        vec_end = vec_fields[0];
        insert_pos = (phx::SharedPtrElement*)((long)insert_pos + move_offset);
        move_end = vec_fields[1];
    }

    vec_fields[0] = (long)insert_pos;
    vec_fields[1] = (long)after_insert;
    vec_fields[2] = new_buf_base + (long)(new_cap * sizeof(phx::SharedPtrElement));

    // Release old shared_ptrs and free old buffer
    while (move_end != vec_end) {
        long* old_ctrl = *(long**)(move_end - 0x10);
        move_end -= sizeof(phx::SharedPtrElement);
        shared_ptr_release(old_ctrl);
    }

    if (vec_end != 0) {
        FUN_710392e590((void*)vec_end);
    }
}

// ============================================================================
// merge_sort_linked_list — Merge sort on a doubly-linked list of TaskNodes
// Compares elements via vtable call at vtable[0x55] (+0x2a8) on node->data,
// which returns a u8 priority. Returns the new head of the sorted list.
// Address: 0x710354ce10 (704 bytes)
// ============================================================================
phx::TaskNode* FUN_710354ce10_ce10(phx::TaskNode* head, phx::TaskNode* sentinel, u64 count) {
    if (count < 2) {
        return head;
    }

    if (count == 2) {
        // Base case: 2 elements, swap if needed
        phx::TaskNode* second = (phx::TaskNode*)sentinel->next;
        u8 second_priority = ((u8(*)(void))((long*)(*(long*)(long)second->data))[0x55])();
        u8 head_priority = ((u8(*)(void))((long*)(*(long*)(long)head->data))[0x55])();
        if (second_priority < head_priority) {
            second->next->prev = second->prev;
            *(phx::TaskNode**)second->prev = second->next;
            head->next->prev = second;
            second->next = head->next;
            head->next = (phx::TaskNode*)second;
            second->prev = (phx::TaskNode*)head;
            head = second;
        }
        return head;
    }

    // Recursive case: split, sort halves, merge
    u64 half = count >> 1;
    phx::TaskNode* mid = head;
    if (half != 0) {
        long steps = (long)half + 1;
        do {
            mid = mid->prev;
            steps--;
        } while (1 < steps);
        head = FUN_710354ce10_ce10(head, mid, half);
    }
    mid = FUN_710354ce10_ce10(mid, sentinel, count - half);

    // Merge two sorted halves
    u8 mid_priority = ((u8(*)(void))((long*)(*(long*)(long)mid->data))[0x55])();
    u8 head_priority = ((u8(*)(void))((long*)(*(long*)(long)head->data))[0x55])();

    phx::TaskNode* merge_cursor;
    phx::TaskNode* right_cursor;
    phx::TaskNode* splice_end;
    phx::TaskNode* tracked;

    if (mid_priority < head_priority) {
        // mid's head is smaller — splice it before head
        phx::TaskNode* scan;
        for (scan = mid->prev; splice_end = sentinel, scan != sentinel;
             scan = scan->prev) {
            mid_priority = ((u8(*)(void))((long*)(*(long*)(long)scan->data))[0x55])();
            head_priority = ((u8(*)(void))((long*)(*(long*)(long)head->data))[0x55])();
            splice_end = scan;
            if (head_priority <= mid_priority) break;
        }
        phx::TaskNode* after_splice = splice_end->next;
        mid->next->prev = (phx::TaskNode*)((long)after_splice->prev);
        *(phx::TaskNode**)after_splice->prev = mid->next;
        merge_cursor = head->prev;
        head->next->prev = mid;
        mid->next = head->next;
        head->next = after_splice;
        after_splice->prev = (phx::TaskNode*)head;
        tracked = scan;
        head = mid;
        if (splice_end == merge_cursor) {
            return mid;
        }
    } else {
        merge_cursor = head->prev;
        right_cursor = mid;
        splice_end = mid;
        tracked = mid;
        if (mid == merge_cursor) {
            return head;
        }
    }

    // Continue merging
    right_cursor = tracked;
    do {
        if (right_cursor == sentinel) {
            return head;
        }
        u8 right_pri = ((u8(*)(void))((long*)(*(long*)(long)right_cursor->data))[0x55])();
        u8 left_pri = ((u8(*)(void))((long*)(*(long*)(long)merge_cursor->data))[0x55])();
        if (right_pri < left_pri) {
            phx::TaskNode* scan2;
            phx::TaskNode* splice_end2;
            for (scan2 = right_cursor->prev; splice_end2 = sentinel, scan2 != sentinel;
                 scan2 = scan2->prev) {
                right_pri = ((u8(*)(void))((long*)(*(long*)(long)scan2->data))[0x55])();
                left_pri = ((u8(*)(void))((long*)(*(long*)(long)merge_cursor->data))[0x55])();
                splice_end2 = scan2;
                if (left_pri <= right_pri) break;
            }
            phx::TaskNode* after = splice_end2->next;
            phx::TaskNode* new_tracked;
            if (splice_end != right_cursor) {
                new_tracked = tracked;
            } else {
                new_tracked = scan2;
            }
            right_cursor->next->prev = (phx::TaskNode*)((long)after->prev);
            *(phx::TaskNode**)after->prev = right_cursor->next;
            phx::TaskNode* next_merge = merge_cursor->prev;
            merge_cursor->next->prev = right_cursor;
            right_cursor->next = merge_cursor->next;
            merge_cursor->next = after;
            after->prev = (phx::TaskNode*)merge_cursor;
            right_cursor = scan2;
            tracked = new_tracked;
        } else {
            merge_cursor = merge_cursor->prev;
        }
        splice_end = tracked;
    } while (merge_cursor != tracked);

    return head;
}

// ============================================================================
// hash_vec_container_destructor — Destructor that clears vectors of VtableEntry
// elements (destroying each via vtable), frees nodes from a hash map linked
// list, zeroes the hash buckets, then destroys two more reversed vectors.
// Address: 0x710354e180 (416 bytes)
// ============================================================================
void FUN_710354e180_e180(phx::HashVecContainer* container) {
    // Clear forward vector B at +0x50..+0x58
    phx::VtableEntry* vec_b_end = container->vec_b_end;
    void* free_hook = PTR_VirtualFreeHook_71052a7a70;

    for (phx::VtableEntry* entry = container->vec_b_start; entry != vec_b_end; entry++) {
        PTR_VirtualFreeHook_71052a7a70 = free_hook;
        void* guard_vtable = entry->guard_vtable;
        void* guard_ptr = entry->guard_ptr;
        u64 expected = entry->expected_value;
        entry->guard_vtable = nullptr;
        entry->guard_ptr = nullptr;
        entry->expected_value = 0;
        if (guard_ptr != nullptr && guard_vtable != nullptr && *(u64*)guard_ptr == expected) {
            ((void(*)(void))((long*)*(long*)guard_vtable)[1])();
        }
        free_hook = PTR_VirtualFreeHook_71052a7a70;
    }

    // Free hash map nodes at +0x20 if count > 0
    if (container->hash_count != 0) {
        phx::HashNode* node = container->hash_head;
        while (node != nullptr) {
            phx::HashNode* next = node->next;
            if ((node->flags & 1) != 0) {
                void* owned = node->owned_ptr;
                if (free_hook != nullptr) {
                    FUN_71039c1400(owned);  // VirtualFreeHook
                }
                FUN_710392e590(owned);
            }
            FUN_710392e590(node);
            node = next;
        }

        // Zero hash buckets
        u64 bucket_count = container->hash_bucket_count;
        container->hash_head = nullptr;
        if (bucket_count != 0) {
            u64 remainder = bucket_count & 3;
            u64 idx;
            if (bucket_count - 1 < 3) {
                idx = 0;
            } else {
                idx = 0;
                do {
                    u64 byte_offset = idx * 8;
                    idx += 4;
                    container->hash_buckets[byte_offset / 8] = nullptr;
                    container->hash_buckets[byte_offset / 8 + 1] = nullptr;
                    container->hash_buckets[byte_offset / 8 + 2] = nullptr;
                    container->hash_buckets[byte_offset / 8 + 3] = nullptr;
                } while (bucket_count - remainder != idx);
            }
            if (remainder != 0) {
                u64 byte_idx = idx;
                long remaining = -(long)remainder;
                do {
                    container->hash_buckets[byte_idx] = nullptr;
                    byte_idx++;
                    remaining++;
                } while (remaining != 0);
            }
        }
        container->hash_count = 0;
    }

    // Destroy reversed vector B at +0x50..+0x58
    phx::VtableEntry* vec_b_start = container->vec_b_start;
    phx::VtableEntry* cursor = container->vec_b_end;
    while (cursor != vec_b_start) {
        cursor--;
        ((void(*)(phx::VtableEntry*))((long*)*(long*)cursor)[0])(cursor);
    }
    container->vec_b_end = vec_b_start;

    // Destroy reversed vector A at +0x38..+0x40
    phx::VtableEntry* vec_a_start = container->vec_a_start;
    cursor = container->vec_a_end;
    while (cursor != vec_a_start) {
        cursor--;
        ((void(*)(phx::VtableEntry*))((long*)*(long*)cursor)[0])(cursor);
    }
    container->vec_a_end = vec_a_start;
}

// ============================================================================
// destroy_deque — Destroys a single StdDeque8 (std::deque<T*> with 4096-byte
// blocks and 512 8-byte elements per block). Clears elements, shrinks map,
// frees blocks and map allocation.
// Address: part of 0x710354b800
// ============================================================================
static void destroy_deque(phx::StdDeque8* deque) {
    void** map_cur = deque->map_start;
    void** map_end = deque->map_end;
    long map_byte_size = (long)map_end - (long)map_cur;

    if (map_byte_size != 0) {
        u64 start = deque->start_offset;
        void** block_ptr = (void**)((u64)map_cur + (start >> 6 & 0x3fffffffffffff8ULL));
        long elem_addr = (long)*block_ptr + (start & 0x1ff) * 8;
        u64 end_offset = deque->size + start;
        long end_addr = *(long*)((u64)map_cur + (end_offset >> 6 & 0x3fffffffffffff8ULL)) +
                        (long)(end_offset & 0x1ff) * 8;
        while (end_addr != elem_addr) {
            elem_addr += 8;
            if (elem_addr - (long)*block_ptr == 0x1000) {
                block_ptr++;
                elem_addr = (long)*block_ptr;
            }
        }
    }

    deque->size = 0;

    u64 block_count;
    while (block_count = (u64)map_byte_size >> 3, 2 < block_count) {
        if (*map_cur != nullptr) {
            FUN_710392e590(*map_cur);
            map_cur = deque->map_start;
            map_end = deque->map_end;
        }
        map_cur++;
        deque->map_start = map_cur;
        map_byte_size = (long)map_end - (long)map_cur;
    }

    if (block_count == 1) {
        deque->start_offset = 0x100;
    } else if (block_count == 2) {
        deque->start_offset = 0x200;
    }

    if (map_cur != map_end) {
        do {
            if (*map_cur != nullptr) {
                FUN_710392e590(*map_cur);
            }
            map_cur++;
        } while (map_end != map_cur);
        long end_val = (long)deque->map_end;
        if (end_val != (long)deque->map_start) {
            deque->map_end = (void**)(end_val + (~((end_val - 8) - (long)deque->map_start) & 0xfffffffffffffff8ULL));
        }
    }

    if (deque->map_alloc != nullptr) {
        FUN_710392e590(deque->map_alloc);
    }
}

// ============================================================================
// destroy_three_deques — Destroys 3 consecutive StdDeque8 structures
// Address: 0x710354b800 (912 bytes)
// ============================================================================
void FUN_710354b800_b800(phx::StdDeque8* deques) {
    // Deque 3 (at offset +0x60 from base = deques[2])
    destroy_deque(&deques[2]);

    // Deque 2 (at offset +0x30 from base = deques[1])
    {
        phx::StdDeque8* dq = &deques[1];
        void** map_cur = dq->map_start;
        void** map_end = dq->map_end;
        long map_byte_size = (long)map_end - (long)map_cur;

        if (map_byte_size != 0) {
            u64 start = dq->start_offset;
            void** block_ptr = (void**)((u64)map_cur + (start >> 6 & 0x3fffffffffffff8ULL));
            long elem_addr = (long)*block_ptr + (start & 0x1ff) * 8;
            u64 end_offset = dq->size + start;
            long end_addr = *(long*)((u64)map_cur + (end_offset >> 6 & 0x3fffffffffffff8ULL)) +
                            (long)(end_offset & 0x1ff) * 8;
            while (end_addr != elem_addr) {
                elem_addr += 8;
                if (elem_addr - (long)*block_ptr == 0x1000) {
                    block_ptr++;
                    elem_addr = (long)*block_ptr;
                }
            }
        }

        dq->size = 0;

        u64 block_count;
        while (block_count = (u64)map_byte_size >> 3, 2 < block_count) {
            if (*map_cur != nullptr) {
                FUN_710392e590(*map_cur);
                map_cur = dq->map_start;
                map_end = dq->map_end;
            }
            map_cur++;
            dq->map_start = map_cur;
            map_byte_size = (long)map_end - (long)map_cur;
        }

        if (block_count == 1) {
            dq->start_offset = 0x100;
        } else if (block_count == 2) {
            dq->start_offset = 0x200;
        }

        if (map_cur != map_end) {
            do {
                if (*map_cur != nullptr) FUN_710392e590(*map_cur);
                map_cur++;
            } while (map_end != map_cur);
            long end_val = (long)dq->map_end;
            if (end_val != (long)dq->map_start) {
                dq->map_end = (void**)(end_val + (~((end_val - 8) - (long)dq->map_start) & 0xfffffffffffffff8ULL));
            }
        }

        if (dq->map_alloc != nullptr) FUN_710392e590(dq->map_alloc);
    }

    // Deque 1 (at offset +0x00 from base = deques[0])
    {
        phx::StdDeque8* dq = &deques[0];
        void** map_cur = dq->map_start;
        void** map_end = dq->map_end;
        long map_byte_size = (long)map_end - (long)map_cur;

        if (map_byte_size != 0) {
            u64 start = dq->start_offset;
            void** block_ptr = (void**)((u64)map_cur + (start >> 6 & 0x3fffffffffffff8ULL));
            long elem_addr = (long)*block_ptr + (start & 0x1ff) * 8;
            u64 end_offset = dq->size + start;
            long end_addr = *(long*)((u64)map_cur + (end_offset >> 6 & 0x3fffffffffffff8ULL)) +
                            (long)(end_offset & 0x1ff) * 8;
            while (end_addr != elem_addr) {
                elem_addr += 8;
                if (elem_addr - (long)*block_ptr == 0x1000) {
                    block_ptr++;
                    elem_addr = (long)*block_ptr;
                }
            }
        }

        dq->size = 0;

        u64 block_count;
        while (block_count = (u64)map_byte_size >> 3, 2 < block_count) {
            if (*map_cur != nullptr) {
                FUN_710392e590(*map_cur);
                map_cur = dq->map_start;
                map_end = dq->map_end;
            }
            map_cur++;
            dq->map_start = map_cur;
            map_byte_size = (long)map_end - (long)map_cur;
        }

        long offset_reset;
        if (block_count == 1) {
            offset_reset = 0x100;
        } else if (block_count != 2) {
            goto skip_offset;
        } else {
            offset_reset = 0x200;
        }
        dq->start_offset = offset_reset;

skip_offset:
        if (map_cur != map_end) {
            do {
                if (*map_cur != nullptr) FUN_710392e590(*map_cur);
                map_cur++;
            } while (map_end != map_cur);
            long end_val = (long)dq->map_end;
            if (end_val != (long)dq->map_start) {
                dq->map_end = (void**)(end_val + (~((end_val - 8) - (long)dq->map_start) & 0xfffffffffffffff8ULL));
            }
        }

        if (dq->map_alloc != nullptr) FUN_710392e590(dq->map_alloc);
    }
}

// ============================================================================
// fiber_scheduler_destructor — Destructor for FiberScheduler
// Drains pending task vectors into a deque, destroys all fibers in the deque,
// cleans up deques, destroys mutex, and calls destroy_three_deques for sub-deques.
// Address: 0x710354b4b0 (848 bytes)
// ============================================================================
void FUN_710354b4b0_b4b0(phx::FiberScheduler* sched) {
    // Drain task vector A at +0xE0..+0xE8 into fiber deque
    phx::WorkEntry* task_a_cur = sched->task_vec_a_start;
    phx::WorkEntry* task_a_end = sched->task_vec_a_end;
    if (task_a_cur != task_a_end) {
        u64 deque_size = sched->fiber_deque_size;
        do {
            void** deque_map = sched->fiber_deque_map_start;
            long map_span = (long)sched->fiber_deque_map_end - (long)deque_map;
            phx::Fiber* fiber = (phx::Fiber*)task_a_cur->fiber;
            u64 total_offset = deque_size + sched->fiber_deque_start_offset;
            u64 max_idx = 0;
            if (map_span != 0) max_idx = (u64)map_span * 0x40 - 1;
            if (max_idx == total_offset) {
                FUN_710354a7e0((long)&sched->fiber_deque_alloc);
                deque_map = sched->fiber_deque_map_start;
                total_offset = sched->fiber_deque_start_offset + sched->fiber_deque_size;
            }
            task_a_cur++;
            *(phx::Fiber**)(*(long*)((long)deque_map + (total_offset >> 6 & 0x3fffffffffffff8ULL)) + (long)(total_offset & 0x1ff) * 8) = fiber;
            deque_size = sched->fiber_deque_size + 1;
            sched->fiber_deque_size = deque_size;
        } while (task_a_end != task_a_cur);
    }

    // Drain task vector B at +0xF8..+0x100 into same deque
    phx::WorkEntry* task_b_cur = sched->task_vec_b_start;
    phx::WorkEntry* task_b_end = sched->task_vec_b_end;
    u64* deque_size_ptr = &sched->fiber_deque_size;
    u64 deque_size;
    if (task_b_cur == task_b_end) {
        deque_size = sched->fiber_deque_size;
    } else {
        deque_size = sched->fiber_deque_size;
        do {
            void** deque_map = sched->fiber_deque_map_start;
            long map_span = (long)sched->fiber_deque_map_end - (long)deque_map;
            phx::Fiber* fiber = (phx::Fiber*)task_b_cur->fiber;
            u64 total_offset = deque_size + sched->fiber_deque_start_offset;
            u64 max_idx = 0;
            if (map_span != 0) max_idx = (u64)map_span * 0x40 - 1;
            if (max_idx == total_offset) {
                FUN_710354a7e0((long)&sched->fiber_deque_alloc);
                deque_map = sched->fiber_deque_map_start;
                total_offset = sched->fiber_deque_start_offset + sched->fiber_deque_size;
            }
            task_b_cur++;
            *(phx::Fiber**)(*(long*)((long)deque_map + (total_offset >> 6 & 0x3fffffffffffff8ULL)) + (long)(total_offset & 0x1ff) * 8) = fiber;
            deque_size = *deque_size_ptr + 1;
            *deque_size_ptr = deque_size;
        } while (task_b_end != task_b_cur);
    }

    // Pop and destroy fibers from deque
    if (deque_size != 0) {
        void*** deque_map_end_ptr = &sched->fiber_deque_map_end;
        do {
            u64 start_off = sched->fiber_deque_start_offset;
            u64 back_idx = deque_size - 1;
            void** deque_map = sched->fiber_deque_map_start;
            phx::Fiber* fiber = *(phx::Fiber**)
                (*(long*)((long)deque_map + ((u64)(back_idx + start_off) >> 6 & 0x3fffffffffffff8ULL)) +
                (u64)(back_idx + start_off & 0x1ff) * 8);
            if (fiber != nullptr) {
                Fiber_dtor_353c210(fiber);
                FUN_710392e590(fiber);
                deque_size = *deque_size_ptr;
                start_off = sched->fiber_deque_start_offset;
                back_idx = deque_size - 1;
                deque_map = sched->fiber_deque_map_start;
            }
            *deque_size_ptr = back_idx;
            long map_span = (long)*deque_map_end_ptr - (long)deque_map;
            long underflow = 1 - (long)deque_size;
            long max_idx = 0;
            if (map_span != 0) max_idx = map_span * 0x40 - 1;
            deque_size = back_idx;
            if (0x3ff < (u64)((underflow - (long)start_off) + max_idx)) {
                void** last_block = (void**)((long)*deque_map_end_ptr - 8);
                if (*last_block != nullptr) {
                    FUN_710392e590(*last_block);
                    back_idx = *deque_size_ptr;
                    last_block = (void**)((long)*deque_map_end_ptr - 8);
                }
                *deque_map_end_ptr = last_block;
                deque_size = back_idx;
            }
        } while (deque_size != 0);
    }

    // Finalize light event at +0x148
    FUN_71039c0610(sched->light_event);

    // Cleanup deque internals at +0x118..+0x138
    {
        void** map_base = sched->fiber_deque_map_start;
        void** map_cur = map_base;
        void** map_end = sched->fiber_deque_map_end;
        long map_byte_size = (long)map_end - (long)map_base;

        if (map_byte_size != 0) {
            u64 start = sched->fiber_deque_start_offset;
            void** block_ptr = (void**)((u64)map_base + (start >> 6 & 0x3fffffffffffff8ULL));
            long elem_addr = (long)*block_ptr + (start & 0x1ff) * 8;
            u64 end_offset = *deque_size_ptr + start;
            long end_addr = *(long*)((u64)map_base + (end_offset >> 6 & 0x3fffffffffffff8ULL)) +
                            (long)(end_offset & 0x1ff) * 8;
            while (end_addr != elem_addr) {
                elem_addr += 8;
                if (elem_addr - (long)*block_ptr == 0x1000) {
                    block_ptr++;
                    elem_addr = (long)*block_ptr;
                }
            }
        }

        *deque_size_ptr = 0;
        u64 block_count;
        while (block_count = (u64)map_byte_size >> 3, 2 < block_count) {
            if (*map_cur != nullptr) {
                FUN_710392e590(*map_cur);
                map_cur = sched->fiber_deque_map_start;
                map_end = sched->fiber_deque_map_end;
            }
            map_cur++;
            sched->fiber_deque_map_start = map_cur;
            map_byte_size = (long)map_end - (long)map_cur;
        }

        u64 offset_reset;
        if (block_count == 1) {
            offset_reset = 0x100;
        } else if (block_count == 2) {
            offset_reset = 0x200;
        } else {
            goto skip_set;
        }
        sched->fiber_deque_start_offset = offset_reset;

skip_set:
        if (map_cur != map_end) {
            do {
                if (*map_cur != nullptr) FUN_710392e590(*map_cur);
                map_cur++;
            } while (map_end != map_cur);
            long end_val = (long)sched->fiber_deque_map_end;
            if (end_val != (long)sched->fiber_deque_map_start) {
                sched->fiber_deque_map_end = (void**)(end_val + (~((end_val - 8) - (long)sched->fiber_deque_map_start) & 0xfffffffffffffff8ULL));
            }
        }

        if (sched->fiber_deque_alloc != nullptr) FUN_710392e590(sched->fiber_deque_alloc);
    }

    // Free task vectors
    if (sched->task_vec_b_start != nullptr) {
        sched->task_vec_b_end = sched->task_vec_b_start;
        FUN_710392e590(sched->task_vec_b_start);
    }
    if (sched->task_vec_a_start != nullptr) {
        sched->task_vec_a_end = sched->task_vec_a_start;
        FUN_710392e590(sched->task_vec_a_start);
    }

    // Destroy mutex at +0xA0
    FUN_71039c14d0(sched->mutex);

    // Destroy sub-deques via destroy_three_deques
    FUN_710354b800_b800(sched->sub_deques);
}

// End of file
