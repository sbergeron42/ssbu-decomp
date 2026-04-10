#pragma once
#include "types.h"
#include "resource/containers.h"

// C2ResourceServiceNX — the central resource loading service
// [derived: ARCropolis src/resource/types.rs — community RE since 2019]
// [derived: service name "C2ResourceServiceNX" at 0x710437acf3, referenced from nnMain]
// [derived: Ghidra 13.0.1 decompilation of FUN_710374f360 (19,552 bytes)]
// Validated by ARCropolis mod loader hooking these exact offsets in millions of installations
// Cross-referenced: ARCropolis field layout vs Ghidra 13.0.1 decompilation vs 13.0.4 disassembly

namespace resource {

// Forward declarations
struct FilesystemInfo;
struct FileNX;
struct LoadedArc;
struct PathInformation;

// File inflate result
// [derived: ARCropolis InflateFile]
struct InflateFile {
    u8* content;   // +0x00
    u64 size;      // +0x08
};

// Loaded file state
// [derived: ARCropolis LoadedData]
struct LoadedData {
    u8* data;         // +0x00
    u32 ref_count;    // +0x08 — atomic
    bool is_used;     // +0x0C
    u8 state;         // +0x0D — LoadState: 0=Unused, 1=Unloaded, 2=Unknown, 3=Loaded
    bool file_flags2; // +0x0E
    u8 flags;         // +0x0F
    u32 version;      // +0x10
    u8 unk;           // +0x14
};

// Loaded filepath mapping
// [derived: ARCropolis LoadedFilepath — repr(packed)]
struct LoadedFilepath {
    u32 loaded_data_index;  // +0x00
    u8 is_loaded;           // +0x04 [derived: Ghidra char access, original uses ldrb not ldr]
    u8 pad[3];              // +0x05
};

// Loaded directory state
// [derived: ARCropolis LoadedDirectory]
struct LoadedDirectory {
    u32 file_group_index;                       // +0x00
    u32 ref_count;                              // +0x04 — atomic
    u8 flags;                                   // +0x08
    u8 state;                                   // +0x09 — LoadState
    u8 pad[2];                                  // +0x0A
    u32 incoming_request_count;                 // +0x0C — atomic [inferred: "could be wrong" per ARCropolis]
    CppVector<u32> child_path_indices;          // +0x10
    CppVector<LoadedDirectory*> child_folders;  // +0x28
    LoadedDirectory* redirection_directory;     // +0x40
};

// Forward declaration for FilesystemInfo field
struct LoadedDataWrapper;

// Filesystem tracking structure
// [derived: ARCropolis FilesystemInfo]
struct FilesystemInfo {
    void* mutex;                                // +0x00 — nn::os::MutexType*
    LoadedFilepath* loaded_filepaths;            // +0x08
    LoadedData* loaded_datas;                   // +0x10
    u32 loaded_filepath_len;                    // +0x18
    u32 loaded_data_len;                        // +0x1C
    u32 loaded_filepath_count;                  // +0x20
    u32 loaded_data_count;                      // +0x24
    CppVector<u32> loaded_filepath_list;        // +0x28
    LoadedDirectory* loaded_directories;        // +0x40
    u32 loaded_directory_len;                   // +0x48
    u32 unk;                                    // +0x4C
    CppVector<u32> unk2;                        // +0x50
    u8 unk3;                                    // +0x68
    u8 unk4[7];                                 // +0x69
    LoadedDataWrapper* loaded_data;              // +0x70 [derived: Ghidra 13.0.1 loaded_tables->loaded_data]
    PathInformation* path_info;                  // +0x78 [derived: does_file_use_extension accesses arc via path_info->arc]
    u32 version;                                // +0x80
};

// File handle wrapper (NX filesystem)
// [derived: ARCropolis FileNX]
// [fixed: position is at +0x020, not +0x028 — confirmed by FUN_71037c58c0 disassembly
//  which accesses position via ldr x8,[x0,#0x20] and file_handle via ldr x0,[x0,#0x18].
//  The erroneous unk3 field at +0x020 did not exist; +0x028+516 = +0x22C matches
//  field14_0x22c in Ghidra's ResLoadingThread decompilation.]
struct FileNX {
    void* vtable;                    // +0x000
    void* unk1;                      // +0x008
    u32 unk2;                        // +0x010
    u32 is_open;                     // +0x014
    void* file_handle;               // +0x018 — nn::fs::FileHandle (u64 internally)
    s64 position;                    // +0x020 [fixed: was +0x028]
    char filename[516];              // +0x028 [fixed: was +0x030]
    u32 flags;                       // +0x22C [fixed: was unk4 at +0x234]
};

// Loaded filesystem search table
// [inferred: Ghidra 13.0.1 decompilation, allocated at 0x38 bytes in init — not in ARCropolis]
struct LoadedFsSearch {
    void* header;                    // +0x00 [inferred: FsSearchHeader*]
    void* body;                      // +0x08 [inferred: FsSearchBody*]
    void* file_path_to_idx;          // +0x10 [inferred: HashToIndex*]
    void* path_to_idx;               // +0x18 [inferred: HashToIndex*]
    void* idx_to_group;              // +0x20 [inferred: HashGroup*]
    void* path_group;                // +0x28 [inferred: HashGroup*]
    void* idx_to_path_group_idx;     // +0x30 [inferred: u32*]
};

// Loaded data wrapper — holds arc and search pointers
// [inferred: Ghidra 13.0.1 decompilation, allocated at 0x18 bytes in init — not in ARCropolis]
struct LoadedDataWrapper {
    LoadedArc* arc;                  // +0x00 [derived: Ghidra 13.0.1 loaded_data->arc access chain]
    LoadedFsSearch* search;          // +0x08 [derived: search section pointer, used in filepath lookups]
    void* unk;                       // +0x10 [unknown]
};

// LoadedTables — container for all loaded resource tables
// [inferred: Ghidra 13.0.1 decompilation, allocated at 0x88 bytes in init — not in ARCropolis]
// Note: ARCropolis calls this FilesystemInfo and accesses it at +0x0D0.
// This may be a wrapper around FilesystemInfo or a different struct at the same offset.
struct LoadedTables {
    u8 data[0x70];                   // +0x00 [unknown: various fields, not yet mapped]
    void* loaded_data;               // +0x70 [inferred: LoadedDataWrapper* — holds arc + search]
    u8 rest[0x10];                   // +0x78 [unknown: remaining fields]
};

// C2ResourceServiceNX — main resource service object
// [derived: ARCropolis src/resource/types.rs — ResServiceNX]
// [derived: Ghidra 13.0.1 decompilation of init function]
// [derived: 13.0.4 disassembly call graph analysis (287 calls, 54 targets)]
// Allocated size: 0x250 (592 bytes) [derived: je_aligned_alloc(0x10, 0x250) at 0x71037509d0]
// Thread names: "ResUpdateThread" (0x710439AAB7), "ResLoadingThread" (0x710426D64F),
//               "ResInflateThread" (0x71042D3CF2)
struct ResServiceNX {
    // --- Synchronization primitives (0x000–0x030) ---
    // [derived: Ghidra 13.0.1 shows je_aligned_alloc(0x10,0x20) + recursive_mutex::recursive_mutex()]
    // [derived: ARCropolis calls this nn::os::MutexType* — same thing, different abstraction level]
    void* mutex;                     // +0x000 — std::recursive_mutex* (= nn::os::MutexType internally)

    // [derived: ARCropolis res_update_event; Ghidra 13.0.1 shows EventType* init pattern]
    void* res_update_event;          // +0x008 — nn::os::EventType*
    void* unk_event1;                // +0x010 [inferred: Ghidra shows EventType* init with 0]
    // [derived: ARCropolis io_swap_event, confirmed by both Ghidra instances]
    void* io_swap_event;             // +0x018 — nn::os::EventType*
    void* unk_event2;                // +0x020 [inferred: Ghidra shows EventType* init with 0]

    // [derived: Ghidra 13.0.1 shows SemaphoreType init with (2,2) and (1,1)]
    void* semaphore1;                // +0x028 — nn::os::SemaphoreType* init(2,2)
    void* semaphore2;                // +0x030 — nn::os::SemaphoreType* init(1,1)

    // --- Thread pointers (0x038–0x048) ---
    // [derived: ARCropolis + Ghidra — 8-byte allocs, zeroed, later set to thread handles]
    void* res_update_thread;         // +0x038 — nn::os::ThreadType*
    void* res_loading_thread;        // +0x040 — nn::os::ThreadType*
    void* res_inflate_thread;        // +0x048 — nn::os::ThreadType*

    // --- Task dispatch (0x050) ---
    // [inferred: Ghidra 13.0.1 shows 0x90-byte object allocation at this offset]
    void* task_dispatch;             // +0x050

    // --- Load request queues (0x058–0x0CF) ---
    // [derived: ARCropolis res_lists: [ResList; 5] — 5 doubly-linked lists, 0x18 each]
    // [note: Ghidra 13.0.1 showed 4 CppVector + separate fields, but ARCropolis's 5 ReLists
    //  is confirmed by: 5 * 0x18 = 0x78, and +0x058 + 0x78 = +0x0D0 = filesystem_info.
    //  Ghidra miscounted because the 5th list is initialized differently.]
    ResList res_lists[5];            // +0x058 — 5 load request queues, 0x78 bytes total

    // --- Filesystem data (0x0D0) ---
    // [derived: ARCropolis filesystem_info at +0x0D0]
    // [note: Ghidra 13.0.1 calls this LoadedTables* and shows 0x88-byte allocation.
    //  ARCropolis calls it FilesystemInfo*. Both point to the same object — the wrapper
    //  that holds all loaded resource table pointers.]
    FilesystemInfo* filesystem_info; // +0x0D0

    // --- Configuration (0x0D8–0x0E7) ---
    u32 region_idx;                  // +0x0D8 [derived: ARCropolis]
    u32 language_idx;                // +0x0DC [derived: ARCropolis]
    u32 unk4;                        // +0x0E0 [derived: loading_thread_state, set to 2/3/0xFFFFFFFF]
    u8 state;                        // +0x0E4 [derived: processing state counter, byte access only]
    u8 pad_e5;                       // +0x0E5
    bool is_loader_thread_running;   // +0x0E6 [derived: ARCropolis]
    u8 unk5;                         // +0x0E7 [unknown]

    // --- ARC file path (0x0E8–0x1E9) ---
    // [derived: FUN_7103541200 reads u16 length at +0x1E8 and char data at +0xE8]
    FixedString256 arc_string;       // +0x0E8 [derived: ARCropolis data_arc_string — "rom:/data.arc" etc.]

    // --- I/O state (0x1F0–0x244) ---
    // [note: 6 bytes implicit padding between arc_string.length (+0x1EA) and data_arc_filenx (+0x1F0)]
    FileNX** data_arc_filenx;        // +0x1F0 [derived: ARCropolis]
    u64 buffer_size;                 // +0x1F8 [derived: ARCropolis]
    u8* buffer_array[2];             // +0x200 [derived: ARCropolis — double-buffered I/O]
    u32 buffer_array_idx;            // +0x210 [derived: ARCropolis]
    u32 unk12;                       // +0x214 [unknown]
    u8* data_ptr;                    // +0x218 [derived: ARCropolis]
    u64 offset_into_read;            // +0x220 [derived: ARCropolis]
    u32 processing_file_idx_curr;    // +0x228 [derived: ARCropolis]
    u32 processing_file_idx_count;   // +0x22C [derived: ARCropolis]
    u32 processing_file_idx_start;   // +0x230 [derived: ARCropolis]
    u32 processing_type;             // +0x234 [derived: ARCropolis — LoadingType enum]
    u32 processing_dir_idx_start;    // +0x238 [derived: ARCropolis]
    u32 processing_dir_idx_single;   // +0x23C [derived: ARCropolis]
    u32 current_index;               // +0x240 [derived: ARCropolis]
    u32 current_dir_index;           // +0x244 [derived: ARCropolis]
    u8 pad[8];                       // +0x248 [derived: pad to 0x250 total, confirmed by alloc size]
};

} // namespace resource
