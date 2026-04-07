// res_scattered.cpp — Remaining scattered resource service functions
// Pool-E worker assignment: task worker pool + path lookup
// See WORKER.md for full target list.

#include "types.h"

// Memory management
extern "C" void* je_aligned_alloc(unsigned long, unsigned long);
extern "C" void FUN_710392e590(void*);  // je_free
extern "C" void* memset(void*, int, unsigned long);
extern "C" void* memcpy(void*, const void*, unsigned long);
extern "C" unsigned long strlen(const char*);

// std::__1 PLT stubs
extern "C" void FUN_71039c13f0(void*);   // std::__1::mutex::~mutex()

// nn::os PLT stubs
extern "C" void FUN_71039c6740(void*);           // nn::os::SignalLightEvent
extern "C" void FUN_71039c6750(void*, int, int); // nn::os::InitializeLightEvent
extern "C" void FUN_71039c6760(void*);           // nn::os::ClearLightEvent
extern "C" void FUN_71039c0690(u32);             // nn::os::FreeTlsSlot
extern "C" int FUN_71039c0500(u32*, void*);      // nn::os::AllocateTlsSlot
extern "C" void FUN_71039c07b0(u32, unsigned long);  // nn::os::SetTlsValue
extern "C" int FUN_71039c2190(u32*, void*);          // nn::os::AllocateTlsSlot

// Error handling
extern "C" [[noreturn]] void FUN_71039c0650(void*);  // __throw_length_error
extern "C" [[noreturn]] void abort();

// Worker/pool helpers (same TU or nearby)
extern "C" void FUN_710354b4b0(void*);   // worker finalize
extern "C" void FUN_710354b800(void*);   // shared_state cleanup
extern "C" void* FUN_7103549f00(long);   // create initial task for deque
extern "C" void FUN_710354a7e0(void*);   // deque grow

// std::function swap (deduplicated at PLT)
extern "C" void FUN_71003cb050(long*, long*);

// GameThread::init (vtable[2])
// Forward declaration — actual definition below
struct InitResult;
// GameThread::init returns InitResult via x8 on AArch64
extern "C" InitResult FUN_71037cc810(void*, long*);

// OOM handler singleton
// [derived: DAT_7105331f00 at 0x7105331f00, vtable dispatch at +0x30 for OOM retry]
__attribute__((visibility("hidden"))) extern s64* DAT_7105331f00;

// TaskWorkerThread vtable
// [derived: set on 0x260-byte GameThread objects created in FUN_7103549620]
__attribute__((visibility("hidden"))) extern char PTR_FUN_71052410c8[];

// std::function callable vtable for task worker thread lambda
// [derived: adrp+add to 0x710522ec50 in FUN_7103549620, stored into SBO buffer]
__attribute__((visibility("hidden"))) extern char DAT_710522ec50[];

// InitResult — non-trivially-destructible to force x8 indirect return on AArch64
// [derived: vtable[3] call in FUN_710354b370 uses hidden x8 for struct return,
//  producing 0x40 stack frame instead of 0x30. Same pattern as FUN_710353d000.]
struct InitResult {
    u32 code;
    ~InitResult() {}
};

// ============================================================================
// FUN_710354b370 — task_worker_pool_destructor
// Address: 0x710354b370 (320 bytes)
// Destroys a task worker pool: signals all workers to wake, joins all threads,
// finalizes and frees all workers, cleans up shared state, frees vectors,
// and releases the TLS slot.
// [derived: called from ResServiceNX shutdown at 0x7103753e0c]
//
// Pool struct layout (0x60 bytes, inferred from field access):
//   +0x00: u32 id
//   +0x08: void* shared_state (0xB0 bytes, has mutex at +0x90)
//   +0x10: u32 tls_slot (nn::os::TlsSlot)
//   +0x18: CppVector<void*> threads (GameThread pointers)
//   +0x30: CppVector<void*> worker_slots (TaskWorker pointers)
//   +0x48: void* task_worker (0x158-byte TaskWorker)
//   +0x50: u64 stack_size
//   +0x58: u8 is_running (atomic release store)
// ============================================================================
extern "C" void FUN_710354b370(long param_1)
{
#ifdef MATCHING_HACK_NX_CLANG
    asm("");
#endif
    // Atomic release store: clear running flag
    // [derived: stlrb wzr,[x0+0x58] at 0x710354b388]
    __atomic_store_n((u8*)(param_1 + 0x58), (u8)0, __ATOMIC_RELEASE);

    // Signal all workers to wake up
    // [derived: iterates worker_slots vector at +0x30, signals LightEvent at worker+0x148]
    long* ws = *(long**)(param_1 + 0x30);
    long* we = *(long**)(param_1 + 0x38);
    for (; ws != we; ws++) {
        long worker = *ws;
        if (worker != 0) {
            FUN_71039c6740((void*)(worker + 0x148));
        }
    }

    // Join and destroy all threads
    // [derived: iterates threads vector at +0x18]
    // [derived: vtable[3] (+0x18) = join, returns InitResult via x8]
    // [derived: vtable[1] (+0x08) = destroy]
    long* ts = *(long**)(param_1 + 0x18);
    long* te = *(long**)(param_1 + 0x20);
    for (; ts != te; ts++) {
        long thread = *ts;
        InitResult r = ((InitResult(*)(void*))(((void**)*(long*)thread)[3]))((void*)thread);
        if (thread != 0) {
            ((void(*)(void*))(((void**)*(long*)thread)[1]))((void*)thread);
        }
    }

    // Finalize and free each worker
    // [derived: re-loads worker_slots vector at +0x30]
    long* ws2 = *(long**)(param_1 + 0x30);
    long* we2 = *(long**)(param_1 + 0x38);
    for (; ws2 != we2; ws2++) {
        long worker = *ws2;
        if (worker != 0) {
            FUN_710354b4b0((void*)worker);
            FUN_710392e590((void*)worker);
        }
    }

    // Finalize and free task_worker at +0x48
    // [derived: ldr x20,[x19,#0x48] at 0x710354b42c]
    long tw = *(long*)(param_1 + 0x48);
    if (tw != 0) {
        FUN_710354b4b0((void*)tw);
        FUN_710392e590((void*)tw);
    }

    // Cleanup shared_state at +0x08
    // [derived: mutex::~mutex at shared_state+0x90, then cleanup + free]
    long ss = *(long*)(param_1 + 0x08);
    if (ss != 0) {
        FUN_71039c13f0((void*)(ss + 0x90));
        FUN_710354b800((void*)ss);
        FUN_710392e590((void*)ss);
    }

    // Free worker_slots buffer
    // [derived: stores start to end slot before freeing]
    void* ws_buf = *(void**)(param_1 + 0x30);
    if (ws_buf != nullptr) {
        *(long*)(param_1 + 0x38) = (long)ws_buf;
        FUN_710392e590(ws_buf);
    }

    // Free threads buffer
    void* ts_buf = *(void**)(param_1 + 0x18);
    if (ts_buf != nullptr) {
        *(long*)(param_1 + 0x20) = (long)ts_buf;
        FUN_710392e590(ts_buf);
    }

    // Free TLS slot at +0x10
    // [derived: ldr w0,[x19,#0x10]; cmn w0,#0x1 at 0x710354b484]
    u32 tls = *(u32*)(param_1 + 0x10);
    if (tls != 0xFFFFFFFF) {
        FUN_71039c0690(tls);
    }
}

// ============================================================================
// FUN_7103549c40 — task_worker_init
// Address: 0x7103549c40 (704 bytes)
// Initializes a 0x158-byte TaskWorker object. Sets up fiber-like state,
// light event for wakeup signaling, deque for task queue, and pushes an
// initial task via FUN_7103549f00.
// [derived: called from FUN_7103549620 (pool constructor) at 0x7103549bf0]
//
// TaskWorker layout (0x158 bytes):
//   +0x000: void* pool_ptr (back-reference to owning pool)
//   +0x008: u32 state
//   +0x010: u8[0xA0] fiber_state (zeroed, u16 at +0xA0 = 1, u8 at +0xA2 = 0)
//   +0x0C0: u64[3] task_vec (zeroed)
//   +0x0D8: u32 sentinel = 0xFFFFFFFF
//   +0x0E0: u8[0x30] reserved (zeroed)
//   +0x110: deque state (6 u64s: map, map_start, map_end, ?, front, size)
//   +0x140: u64 stack_size
//   +0x148: LightEventType light_event (0x10 bytes)
// ============================================================================
extern "C" void FUN_7103549c40(long param_1, long param_2, long param_3)
{
#ifdef MATCHING_HACK_NX_CLANG
    asm("");
#endif
    // Store pool pointer, state, and stack_size
    *(long*)(param_1) = param_2;
    *(u32*)(param_1 + 0x08) = 0;
    *(long*)(param_1 + 0x140) = param_3;

    // Zero fiber state +0xB0..+0xBF
    *(long*)(param_1 + 0xB0) = 0;
    *(long*)(param_1 + 0xB8) = 0;

    // Zero +0xA0..+0xAF then set u16=1 at +0xA0, u8=0 at +0xA2
    *(long*)(param_1 + 0xA0) = 0;
    *(long*)(param_1 + 0xA8) = 0;
    *(u16*)(param_1 + 0xA0) = 1;
    *(u8*)(param_1 + 0xA2) = 0;

    // Zero +0x10..+0x9F (descending)
    *(long*)(param_1 + 0x90) = 0; *(long*)(param_1 + 0x98) = 0;
    *(long*)(param_1 + 0x80) = 0; *(long*)(param_1 + 0x88) = 0;
    *(long*)(param_1 + 0x70) = 0; *(long*)(param_1 + 0x78) = 0;
    *(long*)(param_1 + 0x60) = 0; *(long*)(param_1 + 0x68) = 0;
    *(long*)(param_1 + 0x50) = 0; *(long*)(param_1 + 0x58) = 0;
    *(long*)(param_1 + 0x40) = 0; *(long*)(param_1 + 0x48) = 0;
    *(long*)(param_1 + 0x30) = 0; *(long*)(param_1 + 0x38) = 0;
    *(long*)(param_1 + 0x20) = 0; *(long*)(param_1 + 0x28) = 0;
    *(long*)(param_1 + 0x10) = 0; *(long*)(param_1 + 0x18) = 0;

    // Zero deque state +0xE0..+0x13F (descending)
    *(long*)(param_1 + 0x130) = 0; *(long*)(param_1 + 0x138) = 0;
    *(long*)(param_1 + 0x120) = 0; *(long*)(param_1 + 0x128) = 0;
    *(long*)(param_1 + 0x110) = 0; *(long*)(param_1 + 0x118) = 0;
    *(long*)(param_1 + 0x100) = 0; *(long*)(param_1 + 0x108) = 0;
    *(long*)(param_1 + 0xF0) = 0; *(long*)(param_1 + 0xF8) = 0;
    *(long*)(param_1 + 0xE0) = 0; *(long*)(param_1 + 0xE8) = 0;

    // Initialize and clear light event at +0x148
    // [derived: InitializeLightEvent(event, false, ManualClear=1)]
    FUN_71039c6750((void*)(param_1 + 0x148), 0, 1);
    FUN_71039c6760((void*)(param_1 + 0x148));

    // Zero task_vec and set sentinel
    // [derived: original binary does str +0xC0 then stp +0xC8,+0xD0]
    *(long*)(param_1 + 0xC0) = 0;
#ifdef MATCHING_HACK_NX_CLANG
    asm("");
#endif
    *(long*)(param_1 + 0xC8) = 0;
    *(long*)(param_1 + 0xD0) = 0;
    *(u32*)(param_1 + 0xD8) = 0xFFFFFFFF;

    // Create and enqueue initial task
    // [derived: FUN_7103549f00 returns a task pointer to push into the deque]
    long task = (long)FUN_7103549f00(param_1);

    // Deque push_back
    // [derived: deque at +0x110 with block size 0x40 (64 entries * 8 bytes)]
    long map_start = *(long*)(param_1 + 0x118);
    long map_end = *(long*)(param_1 + 0x120);
    long diff = map_end - map_start;
    long cap = 0;
    if (diff != 0) {
        cap = (diff << 6) - 1;
    }

    long front = *(long*)(param_1 + 0x130);
    long size = *(long*)(param_1 + 0x138);
    long total = front + size;

    if (cap == total) {
        FUN_710354a7e0((void*)(param_1 + 0x110));
        front = *(long*)(param_1 + 0x130);
        map_start = *(long*)(param_1 + 0x118);
        size = *(long*)(param_1 + 0x138);
        total = front + size;
    }

    // [derived: deque block size = 512 elements (libc++ __deque_buf_size for 8-byte type)]
    // [derived: map_byte_off = (total>>6) & ~7 = (total/512) * 8, byte offset into map]
    // [derived: elem_off = total & 0x1FF = element index within 512-element block]
    u64 map_byte_off = (total >> 6) & 0x3FFFFFFFFFFFFF8ULL;
    u64 elem_off = total & 0x1FF;
    long page = *(long*)(map_start + map_byte_off);
    *(long*)(page + elem_off * 8) = task;
    *(long*)(param_1 + 0x138) = *(long*)(param_1 + 0x138) + 1;
}

// ============================================================================
// FUN_7103549620 — task_worker_pool_constructor
// Address: 0x7103549620 (1,568 bytes)
// Creates a TaskWorkerPool: allocates shared state, TLS slot, pre-allocates
// worker slot vector, creates up to 3 task worker threads based on core_mask,
// then creates the main TaskWorker and sets it as TLS value.
// [derived: called twice from ResServiceNX::init (FUN_710374f360)]
//
// param_1 = pool, param_2 = pool ID (u32)
// param_3 = config: +0x00=core_mask(u32), +0x04=priority_base(u8), +0x08=stack_size(u32)
//
// Stack layout (0x150 bytes):
//   sp+0x00: &threads_header, &worker_slots_header (saved pool field ptrs)
//   sp+0x10: saved config pointer
//   sp+0x18: InitResult return buffer (8 bytes)
//   sp+0x20: ThreadCreateInfo (0x90 bytes, reused each loop iteration)
//     +0x20: func_buf[4] (32 bytes)
//     +0x40: func_impl (8 bytes)
//     +0x50: priority (u32)
//     +0x58: core_mask (s64)
//     +0x60: name[33+]
//     +0xA1: name_length, +0xA2: flag
//     +0xA8: stack_size
//   sp+0xB0: temp std::function for clone (0x30 bytes)
//   sp+0xE0..0xEF: OOM scratch
//   sp+0xF0..0x14F: saved registers
// ============================================================================
extern "C" void FUN_7103549620(u32* param_1, u32 param_2, u32* param_3)
{
#ifdef MATCHING_HACK_NX_CLANG
    asm("");
#endif
    *param_1 = param_2;

    // Allocate shared_state (0xB0 bytes) with OOM retry
    long* puVar4 = (long*)je_aligned_alloc(0x10, 0xB0);
    if (puVar4 == nullptr) {
        if (DAT_7105331f00 != nullptr) {
            u32 flags = 0;
            long size = 0xB0;
            u64 r = ((u64(*)(s64*, u32*, long*))(*(s64*)(*DAT_7105331f00 + 0x30)))
                      (DAT_7105331f00, &flags, &size);
            if ((r & 1) != 0) {
                puVar4 = (long*)je_aligned_alloc(0x10, 0xB0);
                if (puVar4 != nullptr) goto lab_ss;
            }
        }
        puVar4 = nullptr;
    }
lab_ss:
    // Init shared_state: zero all, u16=1 at +0x90, u8=0 at +0x92
    *(long*)((u8*)puVar4 + 0xA0) = 0; *(long*)((u8*)puVar4 + 0xA8) = 0;
    *(long*)((u8*)puVar4 + 0x90) = 0; *(long*)((u8*)puVar4 + 0x98) = 0;
    *(u16*)((u8*)puVar4 + 0x90) = 1;
    *(u8*)((u8*)puVar4 + 0x92) = 0;
    *(long*)((u8*)puVar4 + 0x80) = 0; *(long*)((u8*)puVar4 + 0x88) = 0;
    *(long*)((u8*)puVar4 + 0x70) = 0; *(long*)((u8*)puVar4 + 0x78) = 0;
    *(long*)((u8*)puVar4 + 0x60) = 0; *(long*)((u8*)puVar4 + 0x68) = 0;
    *(long*)((u8*)puVar4 + 0x50) = 0; *(long*)((u8*)puVar4 + 0x58) = 0;
    *(long*)((u8*)puVar4 + 0x40) = 0; *(long*)((u8*)puVar4 + 0x48) = 0;
    *(long*)((u8*)puVar4 + 0x30) = 0; *(long*)((u8*)puVar4 + 0x38) = 0;
    *(long*)((u8*)puVar4 + 0x20) = 0; *(long*)((u8*)puVar4 + 0x28) = 0;
    *(long*)((u8*)puVar4 + 0x10) = 0; *(long*)((u8*)puVar4 + 0x18) = 0;
    puVar4[0] = 0; puVar4[1] = 0;

    *(long**)(param_1 + 2) = puVar4;    // +0x08
    param_1[4] = 0xFFFFFFFF;            // +0x10

    // Allocate TLS slot
    u32 tls_val;
    int tls_err = FUN_71039c2190(&tls_val, nullptr);
    if (tls_err != 0) tls_val = 0xFFFFFFFF;
    param_1[4] = tls_val;

    // Zero pool vectors
    *(long*)(param_1 + 0xC) = 0;   // +0x30
    *(long*)(param_1 + 6) = 0;     // +0x18
    *(long*)(param_1 + 0xE) = 0;   // +0x38
    *(long*)(param_1 + 0x10) = 0;  // +0x40
    *(long*)(param_1 + 8) = 0;     // +0x20
    *(long*)(param_1 + 0xA) = 0;   // +0x28

    *(u64*)(param_1 + 0x14) = (u64)param_3[2]; // +0x50 = stack_size
    *(u8*)(param_1 + 0x16) = 1;                 // +0x58 = is_running

    // Allocate worker_slots buffer (0x18 bytes = 3 slots)
    puVar4 = (long*)je_aligned_alloc(0x10, 0x18);
    if (puVar4 == nullptr) {
        if (DAT_7105331f00 != nullptr) {
            u32 flags = 0;
            long size = 0x18;
            u64 r = ((u64(*)(s64*, u32*, long*))(*(s64*)(*DAT_7105331f00 + 0x30)))
                      (DAT_7105331f00, &flags, &size);
            if ((r & 1) != 0) {
                puVar4 = (long*)je_aligned_alloc(0x10, 0x18);
                if (puVar4 != nullptr) goto lab_wb;
            }
        }
        puVar4 = nullptr;
    }
lab_wb:;
    u64 uVar5 = 0;
    long* puVar8 = puVar4 + 3;
    *(long**)(param_1 + 0x10) = puVar8;    // +0x40 = cap
    *(long**)(param_1 + 0xC) = puVar4;     // +0x30 = start
    *(long**)(param_1 + 0xE) = puVar4;     // +0x38 = end

    if (puVar4 >= puVar8) goto lab_grow_ws;
    goto lab_push_ws;

lab_loop:
    puVar4 = *(long**)(param_1 + 0xE);  // reload end
    puVar8 = *(long**)(param_1 + 0x10); // reload cap
    if (puVar4 < puVar8) goto lab_push_ws;

lab_grow_ws:
    {
        // Grow worker_slots vector
        long* pvVar13 = *(long**)(param_1 + 0xC);  // start
        long sVar14 = (long)puVar4 - (long)pvVar13;
        u64 uVar7 = ((long)sVar14 >> 3) + 1;
        if (uVar7 >> 61 != 0) {
            FUN_71039c0650((void*)(param_1 + 0xC));
        }
        long cap_diff = (long)puVar8 - (long)pvVar13;
        if ((u64)(cap_diff >> 3) < 0xFFFFFFFFFFFFFFFULL) {
            u64 uVar9 = (u64)(cap_diff >> 2);
            if (uVar7 <= uVar9) uVar7 = uVar9;
            if (uVar7 == 0) goto lab_ws_zero;
        } else {
            uVar7 = 0x1FFFFFFFFFFFFFFFULL;
        }
        {
            long lVar10;
            void* pvVar6;
            lVar10 = (long)(uVar7 << 3);
            if (lVar10 == 0) lVar10 = 1;
            pvVar6 = (void*)je_aligned_alloc(0x10, lVar10);
            if (pvVar6 == nullptr) {
                if (DAT_7105331f00 != nullptr) {
                    u32 flags = 0;
                    long sz = lVar10;
                    u64 r = ((u64(*)(s64*, u32*, long*))(*(s64*)(*DAT_7105331f00 + 0x30)))
                              (DAT_7105331f00, &flags, &sz);
                    if ((r & 1) != 0) {
                        pvVar6 = (void*)je_aligned_alloc(0x10, lVar10);
                        if (pvVar6 != nullptr) goto lab_ws_ok;
                    }
                }
lab_ws_zero:
                pvVar6 = nullptr;
            }
lab_ws_ok:
            puVar4 = (long*)((long)pvVar6 + ((long)sVar14 >> 3) * 8);
            *puVar4 = 0;
            if (0 < (long)sVar14) {
                memcpy(pvVar6, pvVar13, sVar14);
            }
            *(void**)(param_1 + 0xC) = pvVar6;
            *(long**)(param_1 + 0xE) = puVar4 + 1;
            *(void**)(param_1 + 0x10) = (void*)((long)pvVar6 + uVar7 * 8);
            if (pvVar13 != nullptr) {
                FUN_710392e590(pvVar13);
            }
        }
    }
    goto lab_bitchk;

lab_push_ws:
    *(long*)puVar4 = 0;
    *(long*)(param_1 + 0xE) = *(long*)(param_1 + 0xE) + 8;

lab_bitchk:
    {
        u32 uVar2 = 1u << ((u32)uVar5 & 0x1F);
        if (*(u32*)param_3 & uVar2) {
            // Set up ThreadCreateInfo defaults
            long info[12];  // ThreadCreateInfo (0x90 bytes, using long[12] = 96 bytes)
            info[4] = 0;                       // func_impl = null
            *(u32*)&info[6] = 3;               // priority = 3
            info[7] = -1LL;                    // core_mask = -1
            *(u64*)&info[0x11] = 0x40000;      // stack_size
            *(u16*)((u8*)info + 0x81) = 0;     // name_length + flag
            *(u8*)((u8*)info + 0x40) = 0;      // name[0] = '\0'

            // Construct SBO std::function temp
            long temp[5];
            temp[0] = (long)DAT_710522ec50;
            temp[1] = (long)param_1;
            temp[2] = (long)uVar5;
            temp[4] = (long)temp;  // self-ref = SBO

            FUN_71003cb050(temp, info);

            // Destroy temp (holds old null from swap)
            long* impl = (long*)temp[4];
            if (temp == impl) {
                ((void(*)(void*))(*(void***)impl)[4])(impl);
            } else if (impl != nullptr) {
                ((void(*)(void*))(*(void***)impl)[5])(impl);
            }

            // Update flag
            *(u8*)((u8*)info + 0x82) = 0;

            // Set priority from config
            if ((u8)param_3[1] < 3) {
                *(u32*)&info[6] = (u8)param_3[1] + 2;
            }

            // Set core mask and stack size
            info[7] = (long)(u64)uVar2;
            *(u64*)&info[0x11] = (u64)param_3[2];

            // Build thread name "TaskWorkerN"
            *(u64*)((u8*)info + 0x40) = 0x6b726f576b736154ULL;
            *(u8*)((u8*)info + 0x4A) = (u8)uVar5 + '0';
            *(u8*)((u8*)info + 0x4B) = 0;
            *(u16*)((u8*)info + 0x48) = 0x7265;
            *(u8*)((u8*)info + 0x81) = 11;

            // Allocate GameThread (0x260 bytes) with OOM retry
            puVar4 = (long*)je_aligned_alloc(0x10, 0x260);
            if (puVar4 == nullptr) {
                if (DAT_7105331f00 != nullptr) {
                    u32 flags = 0;
                    long sz = 0x260;
                    u64 r = ((u64(*)(s64*, u32*, long*))(*(s64*)(*DAT_7105331f00 + 0x30)))
                              (DAT_7105331f00, &flags, &sz);
                    if ((r & 1) != 0) {
                        puVar4 = (long*)je_aligned_alloc(0x10, 0x260);
                        if (puVar4 != nullptr) goto lab_th;
                    }
                }
                puVar4 = nullptr;
            }
lab_th:
            // Initialize GameThread
            *(u32*)((u8*)puVar4 + 0x40) = 3;
            *(long*)((u8*)puVar4 + 0x30) = 0;
            *(u16*)((u8*)puVar4 + 0x44) = 0;
            *(u8*)((u8*)puVar4 + 0x87) = 0;
            *(u8*)((u8*)puVar4 + 0x46) = 0;
            *(long*)((u8*)puVar4 + 0x88) = 0;
            *(void**)puVar4 = PTR_FUN_71052410c8;
            memset((u8*)puVar4 + 0x90, 0, 0x1C8);

            // Call GameThread::init
            FUN_71037cc810(puVar4, info);

            // Push thread to threads vector (at param_1+6..+0xA)
            puVar8 = *(long**)(param_1 + 8);   // +0x20 = end
            if (puVar8 == *(long**)(param_1 + 0xA)) { // +0x28 = cap
                // Grow threads vector
                long* pvVar13 = *(long**)(param_1 + 6); // +0x18 = start
                long sVar14 = (long)puVar8 - (long)pvVar13;
                u64 uVar7 = ((long)sVar14 >> 3) + 1;
                if (uVar7 >> 61 != 0) {
                    FUN_71039c0650((void*)(param_1 + 6));
                }
                long lVar10 = (long)*(long**)(param_1 + 0xA) - (long)pvVar13;
                u64 uVar9;
                if ((u64)(lVar10 >> 3) < 0xFFFFFFFFFFFFFFFULL) {
                    uVar9 = (u64)(lVar10 >> 2);
                    if (uVar7 <= uVar9) uVar7 = uVar9;
                    if (uVar7 != 0) {
                        if (uVar7 >> 61 != 0) goto lab_abort;
                        goto lab_th_alloc;
                    }
                    goto lab_th_zero;
                } else {
                    uVar7 = 0x1FFFFFFFFFFFFFFFULL;
lab_th_alloc:;
                    u64 alloc_sz;
                    void* pvVar6;
                    alloc_sz = uVar7 * 8;
                    if (alloc_sz == 0) alloc_sz = 1;
                    pvVar6 = (void*)je_aligned_alloc(0x10, alloc_sz);
                    if (pvVar6 == nullptr) {
                        if (DAT_7105331f00 != nullptr) {
                            u32 flags = 0;
                            u64 sz2 = alloc_sz;
                            uVar9 = ((u64(*)(s64*, u32*, u64*))(*(s64*)(*DAT_7105331f00 + 0x30)))
                                      (DAT_7105331f00, &flags, &sz2);
                            if ((uVar9 & 1) != 0) {
                                pvVar6 = (void*)je_aligned_alloc(0x10, alloc_sz);
                                if (pvVar6 != nullptr) goto lab_th_ok;
                            }
                        }
lab_th_zero:
                        pvVar6 = nullptr;
                    }
lab_th_ok:
                    puVar8 = (long*)((long)pvVar6 + ((long)sVar14 >> 3) * 8);
                    *puVar8 = (long)puVar4;
                    if (0 < (long)sVar14) {
                        memcpy(pvVar6, pvVar13, sVar14);
                    }
                    *(void**)(param_1 + 6) = pvVar6;
                    *(long**)(param_1 + 8) = puVar8 + 1;
                    *(void**)(param_1 + 0xA) = (void*)((long)pvVar6 + uVar7 * 8);
                    if (pvVar13 != nullptr) {
                        FUN_710392e590(pvVar13);
                    }
                }
            } else {
                *puVar8 = (long)puVar4;
                *(long*)(param_1 + 8) = *(long*)(param_1 + 8) + 8;
            }

            // Destroy info std::function
            impl = (long*)info[4];
            if (info == impl) {
                ((void(*)(void*))(*(void***)impl)[4])(impl);
            } else if (impl != nullptr) {
                ((void(*)(void*))(*(void***)impl)[5])(impl);
            }
        }
    }

    uVar5++;
    if (uVar5 <= 2) goto lab_loop;

    // After loop: allocate TaskWorker (0x158 bytes)
    uVar5 = (u64)je_aligned_alloc(0x10, 0x158);
    if (uVar5 == 0) {
        if (DAT_7105331f00 != nullptr) {
            u32 flags = 0;
            long sz = 0x158;
            u64 r = ((u64(*)(s64*, u32*, long*))(*(s64*)(*DAT_7105331f00 + 0x30)))
                      (DAT_7105331f00, &flags, &sz);
            if ((r & 1) != 0) {
                uVar5 = (u64)je_aligned_alloc(0x10, 0x158);
                if (uVar5 != 0) goto lab_wk;
            }
        }
        uVar5 = 0;
    }
lab_wk:
    FUN_7103549c40((long)uVar5, (long)param_1, *(long*)(param_1 + 0x14));
    *(u64*)(param_1 + 0x12) = uVar5;   // +0x48
    if (param_1[4] != 0xFFFFFFFF) {     // +0x10 = tls_slot
        FUN_71039c07b0(param_1[4], uVar5);
    }
    return;

lab_abort:
    abort();
}
