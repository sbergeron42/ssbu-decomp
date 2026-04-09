#include "types.h"

// game_core.cpp — pool-d
// Contains: nnMain (0x71002c5620)
// File territory: src/app/game_core.cpp
//
// nnMain is the game's entry point. It:
// 1. Initializes SDK (nn::os::GetHostArgc/Argv)
// 2. Sets up config struct with engine name "nu::Final",
//    service name "C2ResourceServiceNX", data path "rom:/data.arc"
// 3. Calls game_ldn_initialize() for local wireless networking
// 4. Loads initial ARC resources via hash 0xecf7a127b (binary search)
// 5. Polls resource load status in a loop (nn::os::SleepThread 1ms)
// 6. Creates game application via FUN_7103723fa0 + FUN_7103747270
// 7. Runs two 94-case switch statements for resource type cleanup
//
// The 94-case switches (0x00-0x5d) each decrement refcounts on resource
// types in the ARC filesystem. These won't match without exact case data.

extern "C" void* memcpy(void*, const void*, u64);
extern "C" void* memset(void*, int, u64);

// NintendoSDK functions
extern "C" s32 nn_os_GetHostArgc() __asm("_ZN2nn2os11GetHostArgcEv");
extern "C" char** nn_os_GetHostArgv() __asm("_ZN2nn2os11GetHostArgvEv");
extern "C" void nn_os_SleepThread(s64) __asm("_ZN2nn2os11SleepThreadENS0_4TickE");

// std::recursive_mutex
extern "C" void std_recursive_mutex_lock(void*) __asm("_ZNSt3__115recursive_mutex4lockEv");
extern "C" void std_recursive_mutex_unlock(void*) __asm("_ZNSt3__115recursive_mutex6unlockEv");

// jemalloc
extern "C" void* je_aligned_alloc(u64 alignment, u64 size);

// Game init functions
extern "C" void game_ldn_initialize(void*);
extern "C" void FUN_7103723fa0(void*);
extern "C" s64* FUN_7103747270(void*);

// Resource service functions
extern "C" void* FUN_71035407a0(s64, u64);
extern "C" void FUN_71035427e0(s64, s32);
extern "C" void FUN_7103542d20(void*);
extern "C" void FUN_710353eff0(void*);
extern "C" s32 FUN_7103542ad0(void*);
extern "C" void FUN_7103540560(s64);

// Cleanup helpers
extern "C" void FUN_7103726910(void*);
extern "C" void FUN_710392e590(void*);

// Global state
extern "C" u8 DAT_710593a548;
extern "C" u64 DAT_710593a2d8;
extern "C" s64 DAT_7105331f20;   // Resource service singleton
extern "C" void* DAT_7105331f00; // OOM handler singleton

// Vtable for resource request nodes
extern "C" u8 PTR_FUN_710509fe90;

// Fallback resource entry
extern "C" u8 UNK_7104470f50;

// Default name for resource types
extern "C" u8 DAT_7104741dbb;

// Resource type registry
extern "C" void* DAT_71052b60e8;

// NintendoSDK filesystem allocator setup
extern "C" void nn_fs_SetAllocator(void*, void*) __asm("_ZN2nn2fs12SetAllocatorEPFPvmEPFvS1_mE");

// jemalloc config string pointer
extern "C" u64 DAT_71052b5f18;

// jemalloc config string "percpu_arena:percpu,dirty_decay_ms:1"
// [derived: Ghidra shows string at 0x710437ad07 in .rodata]
extern "C" char DAT_710437ad07[];

// Resource allocator/free function pointers (passed to nn::fs::SetAllocator)
extern "C" void LAB_710353bba0(void);
extern "C" void LAB_710353bc10(void);

// ════════════════════════════════════════════════════════════════════
// 0x71002c55e0 — nninitStartup (SDK early init, called before nnMain)
// Size: 60 bytes
// [derived: Ghidra decompilation — sets jemalloc config, calls GetHostArgc/Argv,
//  sets nn::fs allocator. This is the NintendoSDK startup hook.]
// ════════════════════════════════════════════════════════════════════
extern "C"
void nninitStartup(void) {
    // Set jemalloc configuration string
    // [derived: DAT_71052b5f18 = je_malloc_conf pointer, set to
    //  "percpu_arena:percpu,dirty_decay_ms:1" for per-CPU arenas and 1ms dirty decay]
    DAT_71052b5f18 = (u64)DAT_710437ad07;

    // SDK initialization (required before any other SDK calls)
    nn_os_GetHostArgc();
    nn_os_GetHostArgv();

    // Set filesystem allocator functions
    // [derived: LAB_710353bba0 = alloc, LAB_710353bc10 = free]
    nn_fs_SetAllocator((void*)&LAB_710353bba0, (void*)&LAB_710353bc10);
}

// ════════════════════════════════════════════════════════════════════
// 0x71002c5620 — nnMain (game entry point)
// Size: 1,744 bytes (0x6D0)
// ════════════════════════════════════════════════════════════════════
// NOTE: This function contains two 94-case switch statements for
// resource type cleanup. These are the bulk of the code (~80% of
// the function) and won't match without exact jump table data.
// The pre-switch initialization sequence is documented here.

extern "C"
void nnMain(void) {
    // ── 1. SDK Initialization ──
    nn_os_GetHostArgc();
    nn_os_GetHostArgv();
    DAT_710593a548 = 1;

    // ── 2. Build config struct on stack (~0xAB0 bytes) ──
    // [derived: engine name "nu::Final", service "C2ResourceServiceNX",
    //  data archive "rom:/data.arc", content path "/content/hosts/nx"]
    // Config includes: memory pool sizes, thread counts, string paths.
    // Stack layout is too large and fragile to reproduce — the exact
    // byte layout depends on compiler stack frame decisions.
    u8 config[0xAB0];
    memset(config, 0, sizeof(config));

    // Key config values (offsets documented from Ghidra analysis):
    // +0x000: mode = 0
    // +0x010: scale = 1.0f (0x3f800000)
    // +0x018: flags = 0x10
    // +0x5c0: thread_count = 6
    // +0x5b4: priority = 7
    // +0x5b8: stack_size = 0x10000
    // +0x5ac: heap_size = 0x80000
    // ... many more fields

    // ── 3. LDN (Local Data Network) initialization ──
    game_ldn_initialize(config);

    // ── 4. ARC resource loading ──
    // Binary search for hash 0xecf7a127b in the ARC hash table.
    // This is a critical boot resource needed before game startup.
    // The search accesses DAT_7105331f20 (resource service singleton):
    //   +0x78 → hash table container → +0x70 hash entries
    //   Each entry: lower 40 bits = hash, upper 24 bits = file index

    // Allocate resource load node via je_aligned_alloc(0x10, 0x18)
    // with OOM retry pattern, then insert into doubly-linked list.

    // ── 5. Main polling loop ──
    // do {
    //     for each resource in linked list:
    //         check load status via mutex-protected query
    //         if status == 3 (complete): advance to next
    //     if all loaded: break
    //     nn::os::SleepThread(1000000);  // 1ms
    // } while (true);

    // ── 6. Game application creation ──
    // FUN_7103723fa0(config_out) — initialize app framework
    // FUN_7103747270(config_out) — create game application object
    // Returns large struct (~0xC08 bytes)

    // ── 7. Resource cleanup (two 94-case switches) ──
    // Switch discriminant at application_object + 0xC04
    // Each case decrements refcount for a resource type.
    // If refcount reaches 0: release smart pointer, call destructor,
    // invalidate handle (0xffffff), zero size, reset name.
    //
    // Base offset for type slots: 0x728 in *DAT_71052b60e8
    // Stride per type: 0x50 bytes
    //
    // These switches cannot be written in C++ without the exact
    // case targets from the binary jump table.

    // STUB: The actual implementation requires exact stack layout
    // and the 94-case switch tables. Left as documentation.
    // The function does not return — it's the game's main function
    // and the last code to run is the resource cleanup before exit.
}
