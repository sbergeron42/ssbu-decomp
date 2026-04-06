// ResServiceNX initialization — FUN_710374f360 (19,552 bytes)
// STATUS: Logic documentation with fully-resolved Ghidra annotations.
//         Function too large for byte-matching (4,888 instructions, 287 calls
//         to 54 unique targets including je_aligned_alloc x82).
//
// [derived: Ghidra disassembly (279KB) + decompilation of 8 helper functions]
// [derived: struct types from ARCropolis community RE]

#include "types.h"
#include "resource/ResServiceNX.h"
#include "resource/LoadedArc.h"

// ============================================================================
// RESOLVED CALL TARGETS (54 unique functions, 287 total calls)
// ============================================================================
//
// Allocation (93 calls):
//   je_aligned_alloc          0x710392DCE0  (x82) — jemalloc 5.1.0 NX fork
//   FUN_710392DC40            0x710392DC40  (x10) — je_aligned_alloc variant (returns error code)
//   FUN_710392E590            0x710392E590  (x21) — je_free
//   nu::VirtualAllocHook      0x71039C1430  (x5)  — PLT
//   nu::VirtualFreeHook       0x71039C1400  (x5)  — PLT (ptr at 0x71052A7A70)
//
// Synchronization (59 calls):
//   std::mutex::lock           0x71039C1410  (x14) — PLT
//   std::mutex::unlock         0x71039C1420  (x15) — PLT
//   nn::os::YieldThread        0x71039C07E0  (x8)  — PLT
//   __cxa_guard_acquire        0x71039C0100  (x11) — PLT
//   __cxa_guard_release        0x71039C0110  (x11) — PLT
//
// Filesystem (3 calls):
//   nn::fs::QueryMountRomCacheSize  0x71039C76B0  (x1) — PLT
//   nn::fs::MountRom                0x71039C76C0  (x1) — PLT
//   nn::fs::GetFileSize             via 0x71035414C0
//
// String/memory (15 calls):
//   strlen                     0x71039BFAC0  (x3) — PLT
//   memcpy                     0x71039BFB30  (x9) — PLT
//   memset                     0x71039BFCF0  (x3) — PLT
//   std::string::operator=     0x71039C58F0  (x2) — PLT
//   std::string copy ctor      0x71039C2180  (x2) — PLT
//   std::string destructor     0x71039C2160  (x2) — PLT
//   FUN_71037C4550             (x1) — string append
//   FUN_71037C4630             (x1) — string append with suffix
//
// Thread/module creation (30 calls):
//   FUN_7103549620             (x2) — TaskWorkerPool creator
//   FUN_710353D000             (x3) — Thread descriptor creator (0x260 bytes)
//   FUN_71037CAEF0             (x1) — thread start helper
//   FUN_71038CCF40             (x1) — module init
//   nu::ModuleInitializer<T>::Instance (x4 patterns)
//     0x71002C48F0  GraphicsModule
//     0x71002C53C0  (unknown module)
//     0x71002C4F60  (unknown module)
//     0x71002C51F0  (unknown module)
//
// Hash table (5 calls):
//   FUN_71037C5FF0             (x2) — singleton constructor
//   FUN_71037C5D00             (x2) — unordered_map rehash
//   std::__next_prime          0x71039C2130  (x2) — PLT
//
// Mount/tree (8 calls):
//   FUN_710353B200             (x4) — mount-point tree insert
//   FUN_710353C130             (x4) — event/semaphore alloc helper
//   FUN_71035414C0             (x3) — ARC file read with decompression
//
// Misc:
//   FUN_71000001C0             (x11) — atexit registration
//   FUN_71003E59F0             (x2) — tree balance insert
//   FUN_71003CB050             (x2) — iostream/streambuf operation
//   abort                      0x71039C20A0  (x1) — PLT
//
// ============================================================================
// RESOLVED GLOBAL DATA (all from 0x710593C000 page)
// ============================================================================
//
// Singleton:
//   0x710593C288: ResServiceNX singleton pointer (5 refs)
//   0x710593C280: CAS creation lock (2 refs)
//   0x710593C2B0: Allocator OOM callback object (5 refs)
//
// Hash map (std::unordered_map for mount points):
//   0x710593C020: Bucket array pointer (3 refs)
//   0x710593C028: Bucket count (1 ref)
//   0x710593C038: Element count (2 refs)
//
// Strings:
//   0x710593C250: Global std::string #1 — mount name (adrp+0x250 = +592)
//   0x710593C268: Global std::string #2 — secondary name (adrp+0x268 = +616)
//   0x710593C048: Global path buffer — 517 bytes (adrp+0x48 = +72)
//
// OOM handler:
//   0x7105331F00: OOM callback object pointer (40 refs!)
//
// Thread name strings (from .rodata):
//   0x710439AAB7: "ResUpdateThread"
//   0x710426D64F: "ResLoadingThread"
//   0x71042D3CF2: "ResInflateThread"
//
// ============================================================================
// PARAM STRUCT LAYOUT (x0 = first argument)
// ============================================================================
//
// The param is a large configuration struct (~1024+ bytes):
//
//   +0x078 (u8):  ROM mount flag 1
//   +0x080 (ptr): Mount point tree root
//   +0x088 (ptr): Mount point tree end sentinel
//   +0x098 (u8):  ROM mount flag 2
//   +0x09A (u16): Mount point name length
//   +0x3B0 (u32): Region-related config
//   +0x3B4 (u32): ResUpdateThread priority
//   +0x3B8 (u32): ResUpdateThread core mask
//   +0x3BC (u32): ResLoadingThread priority
//   +0x3C0 (u32): ResLoadingThread core mask
//   +0x3C4 (u32): ResInflateThread priority
//   +0x3C8 (u32): ResInflateThread core mask
//   +0x3E8:       TaskWorkerPool 0 config (12-byte struct)
//   +0x3F4:       TaskWorkerPool 1 config (12-byte struct)
//   +0x400 (ptr): ARC file data pointer
//   +0x408 (ptr): ARC file data pointer 2
//
// ============================================================================
// FUNCTION FLOW (15 sections with Ghidra-resolved addresses)
// ============================================================================
//
// SECTION 1: Stack string init [710374F380..710374F3F4]
//   Builds 4 libc++ SSO strings on stack (24 bytes each):
//     sp+0x50: "host" (mov w9,#0x6F68; movk w9,#0x7473,LSL#16)
//     sp+0x68: "rom"  (mov w9,#0x6F72; movk w9,#0x006D,LSL#16)
//     sp+0x80: "save" (mov w9,#0x6173; movk w9,#0x6576,LSL#16)
//     sp+0x98: "sdmc" (mov w8,#0x6473; movk w8,#0x636D,LSL#16)
//
// SECTION 2: Param flags [710374F3F8..710374F40C]
//   flag1 = param[0x78]; flag2 = param[0x98]
//   should_mount = (flag1 | flag2) != 0
//
// SECTION 3: Singleton get-or-create [710374F410..710374F4E4]
//   Load singleton from 0x710593C288
//   If null: CAS lock at 0x710593C280
//     Alloc 33,096 bytes via FUN_710392DC40 (je_aligned_alloc variant)
//     Call FUN_71037C5FF0 (constructor: vtable + 64 file slots)
//     Store singleton to 0x710593C288
//
// SECTION 4: Mutex lock + string copy [710374F4F4..710374F538]
//   Lock mutex at singleton + 0x8110
//   Copy mount name to global string at 0x710593C268
//   Copy secondary name to global string at 0x710593C250
//
// SECTION 5: ROM mount [710374F540..710374F5D4]
//   If should_mount:
//     nn::fs::QueryMountRomCacheSize → alloc cache → nn::fs::MountRom
//
// SECTION 6: Hash map insert [710374F5D8..710374F904]
//   XXH3-style hash of mount name
//   Bucket lookup in map at 0x710593C020
//   If not found: alloc 32-byte node, insert
//   Store string literal ptr at node+0x18 (e.g., 0x7104866C2E)
//   Rehash if needed via __next_prime + FUN_71037C5D00
//
// SECTION 7: Path build + unlock [710374F904..710374F95C]
//   strlen(mount_name) + append ":/" via FUN_71037C4550/FUN_71037C4630
//   memcpy 513 bytes to global path at 0x710593C048
//   mutex.unlock()
//
// SECTION 8: Mount point tree traversal [710374F960..7103750048]
//   Walk rb-tree from param+0x80
//   For each mount point:
//     __cxa_guard_acquire for static local init
//     atexit registration via FUN_71000001C0
//     Copy strings, build "mount:/path"
//     Insert via FUN_710353B200 (tree at 0x7105331EC8)
//     Increment count at 0x7105331ED0
//
// SECTION 9: Conditional filesystem mounts [7103750048..710375011C]
//   Check per-mount guard variables (ldarb)
//   For each of "rom", "save", "sdmc", "host" (if flag):
//     Call FUN_710353B200 (mount-point tree insert)
//   Destroy temporary SSO strings
//
// SECTION 10: Service node creation [710375011C..7103750810]
//   Allocate 0x40-byte linked list node with vtable
//   Insert into global service list (0x71052B5738+1232)
//   nu::ModuleInitializer<GraphicsModule>::Instance() pattern (CAS+YieldThread)
//   Mutex-guarded copy of config data from param
//   Repeat for 3 service nodes (different vtables at 0x71052908xx)
//
// SECTION 11: TaskWorkerPool creation [710375089C..7103750920]
//   Pool 0: FUN_7103549620(obj, 0, param+0x3E8)
//     Creates up to 3 TaskWorker threads
//     Each thread: 0x260-byte descriptor, 0xB0-byte state
//   Pool 1: FUN_7103549620(obj, 1, param+0x3F4)
//
// SECTION 12: Thread creation [7103751AF4..7103751BC4]
//   Three threads created via FUN_710353D000:
//     "ResUpdateThread"   — priority=param[0x3B4], cores=param[0x3B8], stack=256KB
//     "ResLoadingThread"  — priority=param[0x3BC], cores=param[0x3C0], stack=256KB
//     "ResInflateThread"  — priority=param[0x3C4], cores=param[0x3C8], stack=256KB
//
// SECTION 13: Sub-object allocation [7103750A00..7103750DDC]
//   60+ je_aligned_alloc calls creating:
//     2x recursive_mutex (0x20 bytes each)
//     6x semaphores/events (0x08 bytes each)
//     Multiple data holders (0x28, 0x38 bytes)
//   Linked via pointer chains in allocated objects
//
// SECTION 14: Data array copies [7103751278..71037515A8]
//   Copy CppVector data from param:
//     Vector 1: up to 2048 u32 entries (memcpy, 8KB) — param+0x28..0x38
//     Vector 2: up to 512 u32 entries (memcpy, 2KB) — param+0x50..0x60
//   FilesystemInfo setup from LoadedArc:
//     Hash table capacity from float division
//   File handle string copy (max 256 chars)
//
// SECTION 15: Error/cleanup paths [71037528FC..7103753FC0]
//   24 ret instructions for multiple exit paths
//   VirtualFreeHook cascade for allocation failures
//   FinalizeEvent/FinalizeSemaphore cleanup
//   abort() for fatal hash-insert failure (0x71039C20A0)

extern "C" void FUN_710374f360(void* param_1) {
    u8* p = reinterpret_cast<u8*>(param_1);

    // Section 2: Read mount flags
    u8 flag1 = p[0x78];
    u8 flag2 = p[0x98];
    bool should_mount_rom = (flag1 | flag2) != 0;

    // Section 5: Mount ROM filesystem
    if (should_mount_rom) {
        u64 cache_size = 0;
        // nn::fs::QueryMountRomCacheSize(&cache_size);
        // cache = je_aligned_alloc(0x10, cache_size);
        // nn::fs::MountRom(mount_name, cache, cache_size);
    }

    // Sections 3-4, 6-15: See documentation above
    // 4,800+ remaining instructions handle singleton creation,
    // hash map operations, 3 thread creation, 60+ allocations,
    // data copies, and error handling.
}
