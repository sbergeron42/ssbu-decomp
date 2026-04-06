#pragma once
#include "types.h"
#include "resource/containers.h"

// C2ResourceServiceNX — the central resource loading service
// [derived: ARCropolis src/resource/types.rs — community RE since 2019]
// [derived: service name "C2ResourceServiceNX" at 0x710437acf3, referenced from nnMain]
// Validated by ARCropolis mod loader hooking these exact offsets in millions of installations

namespace resource {

// Forward declarations
struct FilesystemInfo;
struct FileNX;

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
    u32 is_loaded;          // +0x04
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
    void* addr;                                 // +0x70
    void* path_info;                            // +0x78 — PathInformation*
    u32 version;                                // +0x80
};

// File handle wrapper (NX filesystem)
// [derived: ARCropolis FileNX]
struct FileNX {
    void* vtable;                    // +0x000
    void* unk1;                      // +0x008
    u32 unk2;                        // +0x010
    u32 is_open;                     // +0x014
    void* file_handle;               // +0x018 — nn::fs::FileHandle*
    u32 unk3;                        // +0x020
    u64 position;                    // +0x028
    char filename[516];              // +0x030 — fixed-length string
    u32 unk4;                        // +0x234
};

// LoadedData wrapper — holds arc and search pointers
// [derived: Ghidra 13.0.1 decompilation, allocated at 0x18 bytes in init]
struct LoadedDataWrapper {
    void* arc;                       // +0x00 — LoadedArc*
    void* search;                    // +0x08 — LoadedFsSearch*
    void* unk;                       // +0x10
};

// Loaded filesystem search table
// [derived: Ghidra 13.0.1 decompilation, allocated at 0x38 bytes in init]
struct LoadedFsSearch {
    void* header;                    // +0x00 — FsSearchHeader*
    void* body;                      // +0x08 — FsSearchBody*
    void* file_path_to_idx;          // +0x10 — HashToIndex*
    void* path_to_idx;               // +0x18 — HashToIndex*
    void* idx_to_group;              // +0x20 — HashGroup*
    void* path_group;                // +0x28 — HashGroup*
    void* idx_to_path_group_idx;     // +0x30 — u32*
};

// LoadedTables — container for all loaded resource tables
// [derived: Ghidra 13.0.1 decompilation, allocated at 0x88 bytes in init]
struct LoadedTables {
    u8 data[0x70];                   // +0x00 — various fields
    void* loaded_data;               // +0x70 — LoadedDataWrapper* (holds arc + search)
    u8 rest[0x10];                   // +0x78 — remaining fields
};

// C2ResourceServiceNX — main resource service object (ResServiceState in Ghidra)
// [derived: ARCropolis ResServiceNX, init at FUN_710374f360 (19,552 bytes)]
// [corrected: Ghidra 13.0.1 decompilation resolves types and field names]
// Thread names: "ResUpdateThread", "ResLoadingThread", "ResInflateThread"
// Allocated size: 0x250 (592 bytes) via je_aligned_alloc
struct ResServiceNX {
    void* mutex;                     // +0x000 — std::recursive_mutex* [corrected: was MutexType*]
    void* res_update_event;          // +0x008 — EventType* "update_performed" [derived: Ghidra]
    void* unk_event1;                // +0x010 — EventType* [derived: Ghidra init with 0]
    void* io_swap_event;             // +0x018 — EventType* [derived: ARCropolis + Ghidra match]
    void* unk_event2;                // +0x020 — EventType* [derived: Ghidra init with 0]
    void* semaphore1;                // +0x028 — SemaphoreType* init(2,2) [derived: Ghidra]
    void* semaphore2;                // +0x030 — SemaphoreType* init(1,1) [derived: Ghidra]
    void* res_update_thread;         // +0x038 — 8-byte alloc, zeroed [derived: Ghidra + ARCropolis]
    void* res_loading_thread;        // +0x040 — 8-byte alloc, zeroed
    void* res_inflate_thread;        // +0x048 — 8-byte alloc, zeroed
    void* task_dispatch;             // +0x050 — 0x90-byte dispatch object [derived: Ghidra]
    CppVector<u32> queues[4];        // +0x058 — 4 queues, NOT 5 ResList [corrected: Ghidra]
    void* unk_ptr_b8;               // +0x0B8 — null initially [derived: Ghidra]
    void* queue_head;                // +0x0C0 — self-referencing linked list [derived: Ghidra]
    void* queue_tail;                // +0x0C8 — points to queue_head [derived: Ghidra]
    LoadedTables* loaded_tables;     // +0x0D0 — 0x88-byte LoadedTables [derived: Ghidra]
    u32 region_idx;                  // +0x0D8
    u32 language_idx;                // +0x0DC
    u32 unk4;                        // +0x0E0
    s16 state;                       // +0x0E4
    bool is_loader_thread_running;   // +0x0E6
    u8 unk5;                         // +0x0E7
    char data_arc_string[256];       // +0x0E8
    void* unk6;                      // +0x1E8 — short field, checked != 0 before ARC open
    FileNX** data_arc_filenx;        // +0x1F0
    u64 buffer_size;                 // +0x1F8
    u8* buffer_array[2];             // +0x200
    u32 buffer_array_idx;            // +0x210
    u32 unk12;                       // +0x214
    u8* data_ptr;                    // +0x218
    u64 offset_into_read;            // +0x220
    u32 processing_file_idx_curr;    // +0x228
    u32 processing_file_idx_count;   // +0x22C
    u32 processing_file_idx_start;   // +0x230
    u32 processing_type;             // +0x234 — LoadingType enum
    u32 processing_dir_idx_start;    // +0x238
    u32 processing_dir_idx_single;   // +0x23C
    u32 current_index;               // +0x240
    u32 current_dir_index;           // +0x244
    u8 pad[8];                       // +0x248 — pad to 0x250
};

} // namespace resource
