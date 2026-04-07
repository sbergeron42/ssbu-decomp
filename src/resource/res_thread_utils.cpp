// res_thread_utils.cpp — Thread creation + utility functions for resource service
// [derived: Ghidra 13.0.4 decompilation + disassembly of FUN_710353d000]

#include "types.h"
#include "resource/ResServiceNX.h"

using namespace resource;

// PLT stubs
extern "C" void* je_aligned_alloc(unsigned long, unsigned long);
extern "C" void* memset(void*, int, unsigned long);
extern "C" unsigned long strlen(const char*);

// std::function swap
// [derived: same logic as FUN_710353cb90, compiler-deduplicated at 0x71003cb050]
extern "C" void FUN_71003cb050(long*, long*);

// OOM handler global
// [derived: OOM callback handler object, vtable+0x30 is retry method]
__attribute__((visibility("hidden"))) extern s64* DAT_7105331f00;

// GameThread vtable
// [derived: only set in FUN_710353d000, slot[0]=FUN_71037cc6c0 (dtor),
//  slot[2]=FUN_71037cc810 (init — creates nn::os::Thread)]
__attribute__((visibility("hidden"))) extern char PTR_FUN_710522e9f0[];

// ThreadCreateInfo — parameters passed to GameThread::init (vtable[2])
// [derived: stack layout in FUN_710353d000, field offsets from FUN_71037cc810 (init)]
// [derived: +0x30 priority from init's param_3[6], +0x38 core_mask from param_3[7]]
// [derived: +0x40 name from param_3+8, +0x81 length from (param_3+0x81),
//  +0x82 flag stored to thread+0x45, +0x88 stack_size from param_3[0x11]]
struct ThreadCreateInfo {
    long func_buf[4];    // +0x00 — [derived: std::function SBO storage, 32 bytes]
    long* func_impl;     // +0x20 — [derived: std::function __f_ pointer]
    u8 _pad28[8];        // +0x28
    u32 priority;        // +0x30 — [derived: priority enum, mapped to nn::os priority in init]
    u32 _pad34;          // +0x34
    s64 core_mask;       // +0x38 — [derived: 1 << core_id, or -1 for all cores]
    char name[65];       // +0x40 — [derived: thread name, max 64 chars + null]
    u8 name_length;      // +0x81 — [derived: name string length]
    u8 flag;             // +0x82 — [derived: stored to thread+0x45 in init]
    u8 _pad83[5];        // +0x83
    u64 stack_size;      // +0x88 — [derived: thread stack size, typically 0x40000]
};

// InitResult — return type of GameThread::init (vtable[2])
// [derived: FUN_71037cc810 writes u32 result (0 success, 0xf0006003 error) via x8]
// Non-trivial destructor forces indirect return (x8 register) on AArch64
struct InitResult {
    u32 code;
    ~InitResult() {}
};

// ============================================================================
// FUN_710353d000 — create_game_thread
// Address: 0x710353d000 (688 bytes)
// Allocates and initializes a GameThread object (0x260 bytes), sets up thread
// parameters (function, priority, core mask, name, stack size), and calls the
// thread's virtual init method to create and start the nn::os::Thread.
// Called 3 times from ResServiceNX::init (FUN_710374f360):
//   - "ResUpdateThread"  → ResServiceNX+0x38
//   - "ResLoadingThread" → ResServiceNX+0x40
//   - "ResInflateThread" → ResServiceNX+0x48
// [derived: 14 total callers across engine/networking/game init]
//
// Status: COMPILED, NOT MATCHING (3/3 attempts)
//   Upstream Clang 8.0.0 diverges from NX Clang on:
//   - Memset dead store elimination (merges +0x87/+0x88 stores into second memset)
//   - Loop unrolling (NX unrolls string copy 2x, upstream doesn't)
//   - Stack layout (ThreadCreateInfo at sp+0x30 vs sp+0x00)
//   - Register allocation (w22/w23 swapped for priority/core_id)
// ============================================================================
void FUN_710353d000(void** out_thread, long* thread_func, u32 priority, u32 core_id,
                    const char* name, u64 stack_size)
{
#ifdef MATCHING_HACK_NX_CLANG
    asm("");
#endif
    // Allocate thread object (0x260 bytes, 16-byte aligned) with OOM retry
    // [derived: je_aligned_alloc(0x10, 0x260) at 0x710353d040]
    u8* thread = (u8*)je_aligned_alloc(0x10, 0x260);
    if (thread == nullptr) {
        if (DAT_7105331f00 != nullptr) {
            u32 flags = 0;
            u64 req_size = 0x260;
            u64 r = ((u64(*)(s64*, u32*, u64*))(*(s64*)(*DAT_7105331f00 + 0x30)))
                     (DAT_7105331f00, &flags, &req_size);
            if (((r & 1) != 0) &&
                (thread = (u8*)je_aligned_alloc(0x10, 0x260), thread != nullptr))
                goto init_thread;
        }
        thread = nullptr;
    }
init_thread:
    // Zero entire 0x260-byte object
    memset(thread, 0, 0x260);

    // Initialize specific fields (binary has these between two memset calls)
    // [derived: stores at 0x710353d0b4..0x710353d0c8]
    *(u64*)(thread + 0x30) = 0;    // +0x30: std::function __f_ = null
    *(u32*)(thread + 0x40) = 3;    // +0x40: state = CREATED
    *(u16*)(thread + 0x44) = 0;    // +0x44: is_initialized
    *(thread + 0x87) = 0;          // +0x87: unknown flag
    *(thread + 0x46) = 0;          // +0x46: unknown flag
    *(u64*)(thread + 0x88) = 0;    // +0x88: nn::os::ThreadType* = null
    memset(thread + 0x90, 0, 0x1C8); // +0x90: clear ThreadType inline storage

    // Set vtable
    // [derived: vtable at 0x710522e9f0]
    *(void**)thread = PTR_FUN_710522e9f0;

    // Store to output
    *out_thread = thread;

    // Build ThreadCreateInfo on stack
    ThreadCreateInfo info;
    info.func_impl = nullptr;
    info.core_mask = -1;
    info.priority = 3;
    *(u16*)&info.name_length = 0;  // [derived: sturh at sp+0x81 clears both name_length and flag]
    info.name[0] = '\0';
    info.stack_size = 0x40000;

    // Clone thread_func's std::function into temporary
    // [derived: std::function copy-and-swap idiom from libc++]
    // temp[0..3] = SBO buffer, temp[4] = __f_ pointer
    long temp[5];
    long* src_impl = (long*)thread_func[4]; // thread_func.__f_
    if (src_impl == nullptr) {
        temp[4] = 0;
    } else if (thread_func == src_impl) {
        // SBO: copy construct callable into temp buffer
        // [derived: vtable[3] (+0x18) = copy_construct_into]
        temp[4] = (long)temp;
        ((void(*)(void*, void*))(*(void***)src_impl)[3])(src_impl, temp);
    } else {
        // Heap: clone callable
        // [derived: vtable[2] (+0x10) = clone]
        temp[4] = (long)((void*(*)(void*))(*(void***)src_impl)[2])(src_impl);
    }

    // Swap cloned function into info's std::function slot
    FUN_71003cb050(temp, (long*)&info);

    // Destroy temporary (after swap, holds info's old null value)
    // [derived: vtable[4] (+0x20) = destroy_inline, vtable[5] (+0x28) = destroy_heap]
    long* temp_impl = (long*)temp[4];
    if (temp == temp_impl) {
        ((void(*)(void*))(*(void***)temp_impl)[4])(temp_impl);
    } else if (temp_impl != nullptr) {
        ((void(*)(void*))(*(void***)temp_impl)[5])(temp_impl);
    }

    // Set core affinity mask
    // [derived: 1 << core_id for single core, -1 for all cores when core_id < 0]
    info.core_mask = ((s32)core_id < 0) ? (s64)-1 : (1LL << core_id);

    // Default to empty string if name is null
    // [derived: csel to 0x7104866c2e ("") when name is null]
    const char* thread_name = (name != nullptr) ? name : "";

    // Set priority
    info.priority = priority;

    // Copy name into info (char-by-char with length tracking)
    // [note: binary has this loop unrolled 2x by NX Clang; upstream Clang 8 does not unroll]
    unsigned long slen = strlen(thread_name);
    info.name_length = 0;
    if (slen != 0) {
        for (unsigned long i = 0; i < slen; i++) {
            info.name[info.name_length] = thread_name[i];
            info.name_length++;
        }
    }
    info.name[info.name_length] = '\0';

    // Clear flag and set stack size
    info.flag = 0;
    info.stack_size = stack_size;

    // Call virtual init method (vtable[2] = FUN_71037cc810)
    // [derived: creates nn::os::Thread, sets core mask, name, starts thread]
    typedef InitResult (*InitFn)(void*, long*);
    void* obj = *out_thread;
    InitFn init_fn = (InitFn)((void**)(*(void**)obj))[2];
    init_fn(obj, (long*)&info);

    // Destroy info's std::function (cleanup after init copied it to thread object)
    long* impl = info.func_impl;
    if (info.func_buf == impl) {
        ((void(*)(void*))(*(void***)impl)[4])(impl);
    } else if (impl != nullptr) {
        ((void(*)(void*))(*(void***)impl)[5])(impl);
    }
}

// PLT stubs for mutex
extern "C" void lock_71039c1490(void*);    // std::__1::recursive_mutex::lock()
extern "C" void unlock_71039c14a0(void*);  // std::__1::recursive_mutex::unlock()

// ListNode pool allocator
// [derived: allocates from a pool at svc->task_dispatch, 0x20-byte ListNodes]
extern "C" void* FUN_7103546d90(void*);

// Globals
__attribute__((visibility("hidden"))) extern FilesystemInfo* DAT_7105331f20;

// ============================================================================
// FUN_7103546000 — queue_filepath_load_request
// Address: 0x7103546000 (384 bytes)
// Validates a filepath index against the loaded filepath/data tables, and if
// the file needs loading (data==null, state allows it), queues a load request
// into the appropriate ResList based on queue_priority.
// [derived: 96 callers across game/engine — primary entry point for file load requests]
// [derived: accesses ResServiceNX+0xD0 (filesystem_info), +0x50 (task_dispatch)]
// [derived: accesses FilesystemInfo loaded_filepaths (+0x08) and loaded_datas (+0x10)]
// [derived: LoadedData state at +0x0D uses acquire/release atomics (ldarb/stlrb)]
// [derived: inserts into res_lists[queue_priority] doubly-linked list]
// ============================================================================
void FUN_7103546000(ResServiceNX* svc, u32 filepath_index, u32 queue_priority)
{
#ifdef MATCHING_HACK_NX_CLANG
    asm("");
#endif
    // Early return for sentinel filepath index
    if (filepath_index == 0xFFFFFF) {
        return;
    }

    // Load filesystem info and lock
    FilesystemInfo* fs = svc->filesystem_info;
    void* mutex = fs->mutex;
    lock_71039c1490(mutex);

    // Validate filepath_index and look up loaded data
    LoadedData* loaded_data = nullptr;
    bool invalid = true;

    if (filepath_index < fs->loaded_filepath_len) {
        // [derived: loaded_filepaths[i] is 8 bytes: u32 loaded_data_index + u8 is_loaded + pad]
        LoadedFilepath* fp = &fs->loaded_filepaths[filepath_index];
        if (fp->is_loaded != 0) {
            // [derived: loaded_datas[i] is 0x18 bytes (LoadedData struct)]
            u32 ldi = fp->loaded_data_index;
            LoadedData* ld = &fs->loaded_datas[ldi];
            if (ld->is_used != 0) {
                // [derived: sentinel check — 0xFFFFFF means invalid data index]
                loaded_data = (ldi == 0xFFFFFF) ? nullptr : ld;
                invalid = (fp == nullptr);  // [derived: cmp x8,#0x0; always false for valid array access]
                goto after_check;
            }
        }
    }
    loaded_data = nullptr;
    invalid = true;

after_check:
    // Unlock mutex
    unlock_71039c14a0(mutex);

    // Return if invalid or no loaded data
    if (invalid) return;
    if (loaded_data == nullptr) return;

    // Return if data is already loaded
    if (*(u64*)loaded_data != 0) return;  // loaded_data->data != null

    // Read state with acquire semantics
    // [derived: ldarb at loaded_data+0x0D = LoadedData.state]
    u8 state = __atomic_load_n(&loaded_data->state, __ATOMIC_ACQUIRE);

    if (state != 0) {
        if (state != 1) return;  // only state 0 (Unused) and 1 (Unloaded) can be queued
        // State 1: check if current queue priority allows re-queue
        // [derived: flags lower 3 bits = current queue priority]
        if ((loaded_data->flags & 7) <= (int)queue_priority) return;
    }

    // Update service state
    // [derived: svc+0xE0 = processing_type or similar state field]
    if (svc->unk4 != 2) {
        svc->unk4 = 1;
    }

    // If state was 0 (Unused), mark as 1 (Unloaded/requested) with release semantics
    // [derived: stlrb at loaded_data+0x0D]
    if (state == 0) {
        __atomic_store_n(&loaded_data->state, (u8)1, __ATOMIC_RELEASE);
    }

    // Allocate a ListNode from the task dispatch pool
    // [derived: FUN_7103546d90 returns a 0x20-byte ListNode from pool at svc->task_dispatch]
    ListNode* node = (ListNode*)FUN_7103546d90(svc->task_dispatch);

    // Initialize load request
    // [derived: stp xzr,xzr,[x0] → next=null, prev=null]
    // [derived: stp x9,x8,[x0,#0x10] → LoadInfo{ty=1, filepath_index=0xFFFFFF, directory_index=0xFFFFFF, files_to_load=0}]
    node->next = nullptr;
    node->prev = nullptr;
    node->data.ty = 1;                       // LoadType::File
    node->data.filepath_index = 0xFFFFFF;    // overwritten below
    node->data.directory_index = 0xFFFFFF;   // sentinel
    node->data.files_to_load = 0xFFFFFF;     // sentinel

    // Update flags: set lower 3 bits to queue_priority
    // [derived: bfxil w9,w21,#0,#3 — insert queue_priority bits 0-2 into flags]
    u8 old_flags = loaded_data->flags;
    loaded_data->flags = (old_flags & 0xF8) | (queue_priority & 7);

    // Set actual filepath index
    node->data.filepath_index = filepath_index;

    // Calculate list base address
    // [derived: res_lists[queue_priority] at svc + 0x58 + queue_priority * 0x18]
    // Sentinel node is at &list->next (= svc + 0x58 + queue_priority*0x18 + 0x08)
    u8* list_base = (u8*)svc + (u64)queue_priority * 0x18;
    ListNode* sentinel = (ListNode*)(list_base + 0x60);  // &res_lists[qp].next
    ListNode* old_end = *(ListNode**)(list_base + 0x68);  // res_lists[qp].end

    // Insert node at tail of doubly-linked list
    // [derived: node->next = sentinel, node->prev = old_end]
    node->next = sentinel;
    node->prev = old_end;
    *(ListNode**)(list_base + 0x68) = node;  // list->end = node
    *(ListNode**)old_end = node;             // old_end->next = node

    // Increment list size
    u64 size = *(u64*)(list_base + 0x58);
    *(u64*)(list_base + 0x58) = size + 1;

    // Set flags on service
    // [derived: svc+0xE7 and svc+0xE4 set to 1 — signals pending work]
    svc->unk5 = 1;
    *(u8*)&svc->state = 1;
}
