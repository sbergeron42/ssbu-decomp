// ResServiceNX initialization — FUN_710374f360 (19,552 bytes)
// STATUS: Logic documentation only. 19KB function with 387 calls,
//         64+ allocation sites, inlined STL (unordered_map, string).
//         Byte-matching is not feasible for this function size.
//
// [derived: disassembly 374f360..3753FC0 + Ghidra decompilation of helpers]
// [derived: struct types from ARCropolis community RE]

#include "types.h"
#include "resource/ResServiceNX.h"
#include "resource/LoadedArc.h"

// nn::fs functions called from init
// [derived: PLT calls at 374f54c (QueryMountRomCacheSize) and 374f5cc (MountRom)]
namespace nn { namespace fs {
    int QueryMountRomCacheSize(u64* size);
    int MountRom(const char* name, void* cache, u64 cache_size);
} }

// nn::os functions called from init
// [derived: PLT calls for YieldThread, SignalEvent, FinalizeEvent, FinalizeSemaphore]
namespace nn { namespace os {
    void YieldThread();
} }

// Custom allocator hooks
// [derived: PLT calls for VirtualAllocHook/VirtualFreeHook at 374f4a8 etc]
namespace nu {
    void* VirtualAllocHook(u64 size, u64 align, void* hint);
    void  VirtualFreeHook(void* ptr);
}

// Internal allocator (called ~64 times, inlined everywhere)
// [derived: bl #1959924 etc — these are all je_aligned_alloc from jemalloc]
extern "C" int je_aligned_alloc_internal(void** out, u64 align, u64 size);

// Singleton constructor — initializes 64 file handle slots
// [derived: Ghidra decompilation of FUN_71037c5ff0]
// Sets vtable, zeros 64 entries of 0x204 bytes each, inits trailing state
extern "C" void singleton_constructor(void* obj);

// Hash table rehash — std::unordered_map bucket reallocation
// [derived: Ghidra decompilation of FUN_71037c5d00]
extern "C" void hash_table_rehash(u64 new_bucket_count);

// Mount-point tree insert
// [derived: Ghidra decompilation of FUN_710353b200]
extern "C" void mount_tree_insert(void* key, void* parent_node);

// ============================================================================
// Init function — reconstructed logic
// ============================================================================
//
// Prologue: saves x19-x28, x29, x30; allocates 1168 bytes of locals
// Total stack frame: 1264 bytes
//
// Stack layout (derived from store instructions in 374f380..374f3f4):
//   sp+48..55:   saved temporaries
//   sp+56..63:   saved w23 (mount_flags)
//   sp+64..71:   saved x22 (param_1)
//   sp+72..79:   saved address
//   sp+80..103:  SSO string "host"  (24 bytes, libc++ short string)
//   sp+104..127: SSO string "rom"   (24 bytes)
//   sp+128..151: SSO string "save"  (24 bytes)
//   sp+152..175: SSO string "sdmc"  (24 bytes)
//   sp+176:      byte flag (zeroed)
//   sp+177:      should_mount_rom (cset ne)
//   sp+178..179: u16 zeroed
//   sp+192...:   allocation result / temp storage
//   sp+720..975: large path buffer (256 bytes)
//   sp+976..977: u16 string length counter
//
// Function flow:
//
// 1. Build mount name SSO strings on stack
//    [374f380..374f3f4]
//    mov w9, #0x6F68; movk w9, #0x7473, lsl #16  → "host"
//    mov w9, #0x6F72; movk w9, #0x006D, lsl #16  → "rom"
//    mov w9, #0x6173; movk w9, #0x6576, lsl #16  → "save"
//    mov w8, #0x6473; movk w8, #0x636D, lsl #16  → "sdmc"
//
// 2. Read param flags and compute mount decision
//    [374f3f8..374f40c]
//    flag1 = param[0x78]  (ldrb w8, [x0, #120])
//    flag2 = param[0x98]  (ldrb w9, [x0, #152])
//    mount_flags = flag1 | flag2
//    should_mount = (mount_flags != 0)
//
// 3. Get-or-create singleton (33096 bytes = 0x8148)
//    [374f410..374f4e4]
//    Global pointer at adrp + 648
//    If null: CAS lock, allocate 33096 bytes, call constructor, store
//    Constructor: vtable + 64 * 516-byte entries zeroed
//
// 4. Lock global mutex at singleton+0x8110
//    [374f4f4..374f500]
//    std::mutex::lock()
//
// 5. Copy mount name strings to global string objects
//    [374f504..374f538]
//    global_str_616 = mount_name_str  (std::string::operator=)
//    global_str_592 = secondary_str   (std::string::operator=)
//
// 6. Mount ROM filesystem (if should_mount)
//    [374f540..374f5d4]
//    nn::fs::QueryMountRomCacheSize(&cache_size)
//    cache = alloc(cache_size)
//    nn::fs::MountRom(mount_name, cache, cache_size)
//
// 7. Insert mount name into std::unordered_map
//    [374f5d8..374f904]
//    XXH3-style hash of mount name
//    Bucket lookup, chain walk
//    If not found: allocate node (32 bytes), insert
//    If load factor exceeded: rehash via __next_prime
//
// 8. Build path string (e.g. "rom:/") and store to global buffer
//    [374f904..374f95c]
//    strlen(mount_name) + append ":/" + memcpy to global buffer
//    mutex.unlock()
//
// 9. Iterate mount points from param struct (rb-tree)
//    [374f960..3750048]
//    For each node in tree starting at param+0x80:
//      __cxa_guard_acquire for static local
//      Copy mount name and path strings
//      Build combined path ("mount:/path")
//      Insert into global mount tree
//      Free temporaries
//
// 10. Conditional mounts for "rom", "save", "sdmc", "host"
//     [3750048..375011c]
//     Check per-mount static guard variables (ldarb)
//     Call mount helper for each enabled mount
//
// 11. Allocate and wire service sub-objects
//     [375011c..3750ddc]
//     60+ allocation calls creating:
//       - Linked list nodes (vtable-based, sizes 0x40, 0x60, 0x120, 0x250)
//       - 2x recursive_mutex (std::recursive_mutex::ctor)
//       - Semaphores (size 0x8, init counts 0/1/2)
//       - Events (size 0x8, for signal coordination)
//       - Worker thread contexts (hold config data, mutex pointers)
//     CAS spin-wait + YieldThread pattern for thread-safe lazy init
//     Mutex-guarded copies from param struct to new objects
//
// 12. Copy CppVector data arrays from param
//     [3751278..37513e4]
//     Vector 1: up to 2048 u32 entries from param+0x28..0x38 (memcpy, 8KB max)
//     Vector 2: up to 512 u32 entries from param+0x50..0x60 (memcpy, 2KB max)
//     Old buffers freed after copy
//
// 13. FilesystemInfo setup from LoadedArc
//     [37513e8..37514cc]
//     Float division for capacity: (float_literal / loaded_arc[+0x50]) → fcvtpu
//     Hash table init for file path lookups
//     Iterator-based entry insertion
//
// 14. File handle string copy + state init
//     [37514d0..37515a8]
//     Copy mount name (up to 256 chars) into handle descriptor
//     Set initial processing state fields
//
// 15. Further sub-object init + data copies
//     [37515a8..37528fc]
//     More allocation + memcpy + memset for:
//       LoadedFilepath arrays, LoadedData arrays, LoadedDirectory arrays
//       data_arc path string (strlen + alloc + memcpy)
//       Final mutex lock/unlock for path registration
//     First ret at 37528fc
//
// 16. Error/cleanup paths + exception landing pads
//     [37528fc..3753FC0]
//     Multiple ret instructions (24 total)
//     VirtualFreeHook cascade for allocation failures
//     FinalizeEvent/FinalizeSemaphore cleanup
//     _Unwind_Resume for exception propagation
//     abort() for fatal hash-insert failure
//
// Key findings:
//   - Singleton object: 33,096 bytes = vtable + 64 * FileNX-like entries (516 bytes each)
//   - Global mutex at singleton + 0x8110 (33040)
//   - Mount names: "host" (debug), "rom" (game data), "save", "sdmc"
//   - Hash table uses XXH3/murmur-style hashing with std::__next_prime
//   - CAS spin-wait pattern: ldaxr/stlxr + loop { YieldThread(); load; cbz; }
//   - Custom allocator: je_aligned_alloc (jemalloc 5.1.0 NX fork) + VirtualAllocHook
//   - Service registers into global linked list with vtable-based node types
//   - Data vectors copied from LoadedArc: file path indices, directory indices

extern "C" void FUN_710374f360(void* param_1) {
    u8* p = reinterpret_cast<u8*>(param_1);

    // Read mount flags from param
    // [374f3f8] ldrb w8, [x0, #120]  — offset 0x78
    // [374f3fc] ldrb w9, [x0, #152]  — offset 0x98
    u8 flag1 = p[0x78];
    u8 flag2 = p[0x98];
    bool should_mount_rom = (flag1 | flag2) != 0;

    if (should_mount_rom) {
        // [374f54c] nn::fs::QueryMountRomCacheSize
        u64 cache_size = 0;
        nn::fs::QueryMountRomCacheSize(&cache_size);

        // [374f5cc] nn::fs::MountRom — mounts "rom" filesystem
        // MountRom(mount_name, cache_buffer, cache_size);
    }

    // The remaining ~4800 instructions handle:
    // - Hash table insert for mount name
    // - Mount point tree traversal and node creation
    // - 60+ sub-object allocations (mutexes, semaphores, events, contexts)
    // - CppVector data copies from LoadedArc
    // - FilesystemInfo hash table initialization
    // - File handle pool setup
    // - Error handling and cleanup paths
    //
    // See detailed flow documentation above.
}
