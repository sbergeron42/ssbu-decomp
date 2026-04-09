#pragma once
#include "types.h"
#include "resource/Fiber.h"

// phx task infrastructure — pool allocator, fiber scheduler, task containers
// Used by the resource service's internal thread pool and task dispatch system.
// [derived: all types from Ghidra 13.0.4 decompilation of functions at 0x7103546c40..0x710354e320]

namespace phx {

// StdFunction32 — libc++ std::function with 32-byte SBO inline buffer
// [derived: pool_block_init at 0x7103546c40 clones via vtable[2] (clone) / vtable[3] (move_construct)]
// [derived: SBO check: impl == buf means inline-stored; impl == nullptr means empty]
struct StdFunction32 {
    long buf[4];       // +0x00 — [derived: SBO inline storage, 32 bytes, compared to impl for SBO check]
    void* impl;        // +0x20 — [derived: __f_ pointer; null=empty, ==buf=SBO, else=heap-allocated]
};
static_assert(sizeof(StdFunction32) == 0x28, "StdFunction32 must be 0x28 bytes");

// PoolBlock — single block in a pool allocator, contains a freelist of fixed-size elements
// [derived: je_aligned_alloc(0x10, 0x60) in pool_acquire at 0x7103546d90]
// [derived: initialized by pool_block_init at 0x7103546c40]
struct PoolBlock {
    void* freelist_head;       // +0x00 — [derived: pool_block_init chains elements here, pool_acquire pops from here]
    u32 element_size;          // +0x08 — [derived: param_2 in pool_block_init, used for stride in freelist build]
    u32 max_count;             // +0x0C — [derived: param_3 in pool_block_init, total element capacity]
    void* base_ptr;            // +0x10 — [derived: je_aligned_alloc result, start of element buffer]
    void* end_ptr;             // +0x18 — [derived: base_ptr + max_count * element_size]
    u32 free_count;            // +0x20 — [derived: set to max_count on init, decremented in pool_acquire]
    u32 pad_24;                // +0x24
    u8 pad_28[8];              // +0x28
    StdFunction32 allocator;   // +0x30 — [derived: cloned from source in pool_block_init via std::function move]
    u8 pad_58[8];              // +0x58
};
static_assert(sizeof(PoolBlock) == 0x60, "PoolBlock must be 0x60 bytes");

// PoolManager — manages a dynamic array of PoolBlocks
// [derived: pool_acquire at 0x7103546d90 scans blocks for free elements, grows block array on demand]
struct PoolManager {
    u64 element_size;              // +0x00 — [derived: copied to PoolBlock::element_size in pool_acquire]
    u32 initial_count;             // +0x08 — [derived: copied to PoolBlock::max_count in pool_acquire]
    u32 pad_0c;                    // +0x0C
    PoolBlock** blocks_start;      // +0x10 — [derived: vector of PoolBlock*, iterated in pool_acquire]
    PoolBlock** blocks_end;        // +0x18 — [derived: vector end pointer]
    PoolBlock** blocks_capacity;   // +0x20 — [derived: vector capacity pointer, triggers growth when end==capacity]
    u8 pad_28[8];                  // +0x28
    StdFunction32 alloc_func;      // +0x30 — [derived: cloned to PoolBlock::allocator in pool_acquire]
    u8 pad_58[8];                  // +0x58
    StdFunction32 dealloc_func;    // +0x60 — [derived: second std::function in pool_acquire, passed to pool_block_init]
    u8 pad_88[8];                  // +0x88
};
static_assert(sizeof(PoolManager) == 0x90, "PoolManager must be 0x90 bytes");

// WorkEntry — entry in the fiber scheduler work vector (task + context snapshot)
// [derived: fiber_scheduler_push_task at 0x710354c720 stores 4 fields per entry]
struct WorkEntry {
    void* task;            // +0x00 — [derived: copied from scheduler current_task (+0xC0)]
    void* param;           // +0x08 — [derived: copied from scheduler current_param (+0xC8)]
    phx::Fiber* fiber;     // +0x10 — [derived: copied from scheduler current_fiber (+0xD0)]
    u64 id;                // +0x18 — [derived: copied from scheduler current_id (+0xD8), 0xFFFFFFFF=invalid]
};
static_assert(sizeof(WorkEntry) == 0x20, "WorkEntry must be 0x20 bytes");

// FiberSchedulerTLS — per-thread fiber scheduler context, accessed via TLS slot
// [derived: fiber_scheduler_push_task reads TLS via nn::os::GetTlsValue, then accesses these offsets]
// Note: only the tail portion (starting at +0xC0) is defined; earlier fields are opaque.
struct FiberSchedulerTLS {
    u8 unk_00[0xC0];              // +0x00 — [unknown: thread-local state before scheduler fields]
    void* current_task;            // +0xC0 — [derived: reset to 0 after fiber switch in push_task]
    void* current_param;           // +0xC8 — [derived: set to param_2 in push_task]
    phx::Fiber* current_fiber;     // +0xD0 — [derived: fiber created via FUN_7103549f00 in push_task]
    u32 current_id;                // +0xD8 — [derived: set to 0xFFFFFFFF on reset in push_task]
    u32 pad_dc;                    // +0xDC
    WorkEntry* work_start;         // +0xE0 — [derived: vector start for work entries]
    WorkEntry* work_end;           // +0xE8 — [derived: vector end]
    WorkEntry* work_capacity;      // +0xF0 — [derived: vector capacity]
};
static_assert(sizeof(FiberSchedulerTLS) == 0xF8, "FiberSchedulerTLS must be 0xF8 bytes");

// StdDeque8 — libc++ std::deque<T*> internals (element size = 8 bytes, block size = 4096 bytes)
// [derived: destroy_deque at 0x710354b800 uses block_size=0x1000, element_size=8, 512 elements/block]
// [derived: deque indexing: map[offset >> 9] + (offset & 0x1FF) * 8]
struct StdDeque8 {
    void* map_alloc;       // +0x00 — [derived: freed in destroy_deque cleanup, original map allocation]
    void** map_start;      // +0x08 — [derived: pointer to first active block pointer]
    void** map_end;        // +0x10 — [derived: pointer past last active block pointer]
    u64 pad_18;            // +0x18
    u64 start_offset;      // +0x20 — [derived: element index of first element, adjusted during shrink]
    u64 size;              // +0x28 — [derived: number of elements, set to 0 on clear]
};
static_assert(sizeof(StdDeque8) == 0x30, "StdDeque8 must be 0x30 bytes");

// TaskNode — node in a doubly-linked list used by task containers
// [derived: merge_sort_linked_list at 0x710354ce10 follows next/prev for sorting]
// [derived: container_destructor at 0x710354cc80 releases ctrl_block shared_ptr on destruction]
struct TaskNode {
    TaskNode* next;        // +0x00 — [derived: linked list next in merge_sort, followed via node[0]]
    TaskNode* prev;        // +0x08 — [derived: linked list prev in merge_sort, followed via node[1]]
    void* data;            // +0x10 — [derived: vtable object, merge_sort compares via vtable[0x55] priority]
    void* ctrl_block;      // +0x18 — [derived: shared_ptr control block, atomic refcount at ctrl+8]
};
static_assert(sizeof(TaskNode) == 0x20, "TaskNode must be 0x20 bytes");

// SharedPtrElement — element in shared_ptr vector (used by SharedPtrListContainer)
// [derived: vector_emplace_back at 0x710354d130 stores ptr+ctrl+flag per 0x18-byte entry]
struct SharedPtrElement {
    void* ptr;             // +0x00 — [derived: data pointer of shared_ptr]
    void* ctrl_block;      // +0x08 — [derived: __shared_weak_count*, atomic refcount at ctrl+8]
    u8 flag;               // +0x10 — [derived: copied in emplace_back, purpose unknown]
    u8 pad_11[7];          // +0x11
};
static_assert(sizeof(SharedPtrElement) == 0x18, "SharedPtrElement must be 0x18 bytes");

// SharedPtrListContainer — container with a doubly-linked list + vector of shared_ptrs
// [derived: destructor at 0x710354cc80 sets vtable, destroys mutex, releases shared_ptrs]
struct SharedPtrListContainer {
    void* vtable;                      // +0x00 — [derived: set to PTR_FUN_710522ed28 in destructor]
    TaskNode* list_head;               // +0x08 — [derived: first node in circular doubly-linked list]
    TaskNode* list_tail;               // +0x10 — [derived: last node, used for unlink]
    u64 list_size;                     // +0x18 — [derived: checked != 0 before list traversal, set to 0]
    SharedPtrElement* vec_start;       // +0x20 — [derived: vector of shared_ptr elements]
    SharedPtrElement* vec_end;         // +0x28 — [derived: vector end, iterated backward in destructor]
    SharedPtrElement* vec_capacity;    // +0x30 — [inferred: standard vector third field, not used in dtor]
    u8 recursive_mutex[0x40];          // +0x38 — [derived: std::recursive_mutex, destroyed via FUN_71039c1480]
};
// Note: actual size may be larger; only fields accessed in destructor are mapped

// TaskRequest — large task/request object inheriting from __shared_weak_count
// [derived: destructor at 0x710354e320, vtable PTR_FUN_710522eda8, 0x790+ bytes]
// [derived: mutex-lockable (lock/unlock at start/end of destructor)]
// Most fields are unknown; only destructor-touched offsets are mapped.
struct TaskRequest {
    void* vtable;              // +0x00 — [derived: set to PTR_FUN_710522eda8, inherited from __shared_weak_count]
    u8 unk_08[0xB8];          // +0x08 — [unknown: includes __shared_weak_count refcount fields]
    u16 status_flags;          // +0xC0 — [derived: cleared to 0 in destructor]
    u8 unk_c2[0x0E];          // +0xC2
    u64 state;                 // +0xD0 — [derived: reset to 1 in destructor]
    u8 unk_d8[0x28];          // +0xD8
    u64 sentinel;              // +0x100 — [derived: set to 0xFFFFFFFFFFFFFFFF in destructor]
    u8 unk_108[0x38];         // +0x108
    u64 field_140;             // +0x140 — [derived: zeroed in destructor]
    u8 unk_148[0x38];         // +0x148
    u64 field_180;             // +0x180 — [derived: zeroed in destructor]
    u8 unk_188[0x38];         // +0x188
    u64 field_1c0;             // +0x1C0 — [derived: zeroed in destructor]
    u8 unk_1c8[0x78];         // +0x1C8
    u64 field_240;             // +0x240 — [derived: zeroed in destructor]
    u8 unk_248[0x38];         // +0x248
    u64 field_280;             // +0x280 — [derived: zeroed in destructor]
    u8 unk_288[0x38];         // +0x288
    u64 field_2c0;             // +0x2C0 — [derived: zeroed in destructor]
    u8 unk_2c8[0x38];         // +0x2C8
    void* shared_ctrl;         // +0x300 — [derived: shared_ptr ctrl block, released if non-null in destructor]
    u8 unk_308[0x38];         // +0x308
    u64 field_340;             // +0x340 — [derived: zeroed in destructor]
    u8 unk_348[0x400];        // +0x348
    u64 field_748;             // +0x748 — [derived: zeroed in destructor]
    u8 unk_750[0x30];         // +0x750
    u8 internal_mutex[0x10];   // +0x780 — [derived: mutex::~mutex called here in destructor]
};
static_assert(sizeof(TaskRequest) == 0x790, "TaskRequest must be 0x790 bytes");

// HashNode — node in a hash map linked list
// [derived: container_destructor_with_vectors_and_hashmap at 0x710354e180]
struct HashNode {
    HashNode* next;        // +0x00 — [derived: linked list traversal in hash map cleanup]
    u8 unk_08[8];          // +0x08
    u16 flags;             // +0x10 — [derived: bit 0 checked for memory ownership in destructor]
    u8 pad_12[6];          // +0x12
    u64 unk_18;            // +0x18
    void* owned_ptr;       // +0x20 — [derived: freed via VirtualFreeHook + je_free if flags bit 0 set]
};
static_assert(sizeof(HashNode) == 0x28, "HashNode must be 0x28 bytes");

// VtableEntry — 0x20-byte vector element with vtable-based lifecycle
// [derived: container_destructor at 0x710354e180 destroys via vtable[0] and guards via vtable[1]]
struct VtableEntry {
    void* vtable;          // +0x00 — [derived: vtable[0] = destructor, vtable[1] = destroy guard]
    void* guard_vtable;    // +0x08 — [derived: vtable object for guard check]
    void* guard_ptr;       // +0x10 — [derived: pointer checked against expected_value]
    u64 expected_value;    // +0x18 — [derived: compared to *guard_ptr before calling destroy]
};
static_assert(sizeof(VtableEntry) == 0x20, "VtableEntry must be 0x20 bytes");

// HashVecContainer — container with hash map + vectors of VtableEntry elements
// [derived: destructor at 0x710354e180 clears vectors, frees hash nodes, zeroes buckets]
struct HashVecContainer {
    u8 unk_00[0x10];               // +0x00
    void** hash_buckets;           // +0x10 — [derived: array of pointers, zeroed in destructor]
    u64 hash_bucket_count;         // +0x18 — [derived: count of buckets, used for zeroing loop]
    HashNode* hash_head;           // +0x20 — [derived: linked list head, traversed to free all nodes]
    u64 hash_count;                // +0x28 — [derived: node count, checked != 0 before traversal]
    u8 unk_30[8];                  // +0x30
    VtableEntry* vec_a_start;      // +0x38 — [derived: vector A start, destroyed in reverse]
    VtableEntry* vec_a_end;        // +0x40 — [derived: vector A end]
    u8 unk_48[8];                  // +0x48
    VtableEntry* vec_b_start;      // +0x50 — [derived: vector B start, forward-iterated for guard check]
    VtableEntry* vec_b_end;        // +0x58 — [derived: vector B end]
};
// Note: actual size may be larger; only destructor-accessed fields mapped

// FiberScheduler — full fiber scheduler object (used by fiber_scheduler_destructor)
// [derived: destructor at 0x710354b4b0, drains task vectors into deque, destroys fibers]
struct FiberScheduler {
    u8 unk_00[0x10];               // +0x00
    StdDeque8 sub_deques[3];       // +0x10 — [derived: 3 deques destroyed by FUN_710354b800]
    u8 mutex[0x10];                // +0xA0 — [derived: mutex::~mutex called in destructor]
    u8 unk_b0[0x30];              // +0xB0
    WorkEntry* task_vec_a_start;   // +0xE0 — [derived: first task vector, drained into deque]
    WorkEntry* task_vec_a_end;     // +0xE8 — [derived: first task vector end]
    WorkEntry* task_vec_a_cap;     // +0xF0 — [inferred: vector capacity]
    WorkEntry* task_vec_b_start;   // +0xF8 — [derived: second task vector, drained into deque]
    WorkEntry* task_vec_b_end;     // +0x100 — [derived: second task vector end]
    u8 unk_108[8];                 // +0x108
    void* fiber_deque_alloc;       // +0x110 — [derived: deque map allocation, freed in destructor]
    void** fiber_deque_map_start;  // +0x118 — [derived: deque map start]
    void** fiber_deque_map_end;    // +0x120 — [derived: deque map end]
    u8 unk_128[8];                 // +0x128
    u64 fiber_deque_start_offset;  // +0x130 — [derived: deque element offset]
    u64 fiber_deque_size;          // +0x138 — [derived: deque element count]
    u8 unk_140[8];                 // +0x140
    u8 light_event[0x30];          // +0x148 — [derived: nn::os::FinalizeLightEvent called here]
};

} // namespace phx
