#pragma once
#include "types.h"

// In-memory parsed ARC archive structures
// [derived: smash-arc (jam1garner/smash-arc) + ARCropolis LoadedArc]
// Community RE by ultimate-research group, validated by ARCropolis file replacement hooks

namespace resource {

// Hash-to-index lookup entry (8 bytes, bitfield)
// [derived: smash-arc HashToIndex — hash:32, length:8, index:24]
struct HashToIndex {
    u64 raw;

    u32 hash() const { return (u32)(raw); }
    u8 length() const { return (u8)(raw >> 32); }
    u32 index() const { return (u32)(raw >> 40); }
};

// File path entry (32 bytes = 4 * HashToIndex)
// [derived: smash-arc FilePath]
struct FilePath {
    HashToIndex path;       // +0x00
    HashToIndex ext;        // +0x08
    HashToIndex parent;     // +0x10
    HashToIndex file_name;  // +0x18
};

// File info bucket for hash table lookup
// [derived: smash-arc FileInfoBucket]
struct FileInfoBucket {
    u32 start;  // +0x00
    u32 count;  // +0x04
};

// File info index — maps to directory offset and file info
// [derived: smash-arc FileInfoIndex]
struct FileInfoIndex {
    u32 dir_offset_index;  // +0x00
    u32 file_info_index;   // +0x04
};

// Directory info (also called MassLoadingGroup)
// [derived: smash-arc DirInfo, field names from community filesystem analysis]
struct DirInfo {
    HashToIndex path;               // +0x00
    u64 name;                       // +0x08 — Hash40
    u64 parent;                     // +0x10 — Hash40
    u32 extra_dis_re;               // +0x18
    u32 extra_dis_re_length;        // +0x1C
    u32 file_info_start_index;      // +0x20
    u32 file_count;                 // +0x24
    u32 child_dir_start_index;      // +0x28
    u32 child_dir_count;            // +0x2C
    u32 flags;                      // +0x30 — DirInfoFlags bitfield
};

// Directory offset (also called MassLoadingData)
// [derived: smash-arc DirectoryOffset]
struct DirectoryOffset {
    u64 offset;            // +0x00
    u32 decomp_size;       // +0x08
    u32 size;              // +0x0C
    u32 file_start_index;  // +0x10
    u32 file_count;        // +0x14
    u32 directory_index;   // +0x18
};

// File info entry
// [derived: smash-arc FileInfo]
struct FileInfo {
    u32 file_path_index;          // +0x00
    u32 file_info_indice_index;   // +0x04
    u32 info_to_data_index;       // +0x08
    u32 flags;                    // +0x0C — FileInfoFlags bitfield
};

// Maps file info to actual file data location
// [derived: smash-arc FileInfoToFileData]
struct FileInfoToFileData {
    u32 folder_offset_index;              // +0x00
    u32 file_data_index;                  // +0x04
    u32 file_info_index_and_load_type;    // +0x08 — bitfield: idx:24, load_type:8
};

// On-disk file data descriptor
// [derived: smash-arc FileData]
struct FileData {
    u32 offset_in_folder;  // +0x00
    u32 comp_size;         // +0x04
    u32 decomp_size;       // +0x08
    u32 flags;             // +0x0C — bit 0: compressed, bit 1: use_zstd
};

// Stream data entry
// [derived: smash-arc StreamData]
struct StreamData {
    u64 size;    // +0x00
    u64 offset;  // +0x08
};

// Stream section header
// [derived: smash-arc StreamHeader]
struct StreamHeader {
    u32 quick_dir_count;           // +0x00
    u32 stream_hash_count;         // +0x04
    u32 stream_file_index_count;   // +0x08
    u32 stream_offset_entry_count; // +0x0C
};

// Stream entry (HashToIndex alias)
using StreamEntry = HashToIndex;
using QuickDir = HashToIndex;

// Filesystem header (on-disk, at start of parsed ARC data)
// [derived: smash-arc FileSystemHeader]
struct FileSystemHeader {
    u32 table_filesize;           // +0x00
    u32 file_info_path_count;     // +0x04
    u32 file_info_index_count;    // +0x08
    u32 folder_count;             // +0x0C
    u32 folder_offset_count_1;    // +0x10
    u32 hash_folder_count;        // +0x14
    u32 file_info_count;          // +0x18
    u32 file_info_sub_index_count;// +0x1C
    u32 file_data_count;          // +0x20
    u32 folder_offset_count_2;    // +0x24
    u32 file_data_count_2;        // +0x28
    u32 padding;                  // +0x2C
    u32 unk1_10;                  // +0x30 — always 0x10
    u32 unk2_10;                  // +0x34 — always 0x10
    u8 regional_count_1;          // +0x38
    u8 regional_count_2;          // +0x39
    u16 padding2;                 // +0x3A
    u32 version;                  // +0x3C
    u32 extra_folder;             // +0x40
    u32 extra_count;              // +0x44
    u32 unk[2];                   // +0x48
    u32 extra_count_2;            // +0x50
    u32 extra_sub_count;          // +0x54
};

// Forward declarations
struct LoadedSearchSection;

// In-memory parsed ARC archive — all table pointers
// [derived: smash-arc LoadedArc + ARCropolis PathInformation.arc]
struct LoadedArc {
    u64 magic;                                  // +0x000
    u64 stream_section_offset;                  // +0x008
    u64 file_section_offset;                    // +0x010
    u64 shared_section_offset;                  // +0x018
    u64 file_system_offset;                     // +0x020
    u64 file_system_search_offset;              // +0x028
    u64 padding;                                // +0x030
    FileSystemHeader* uncompressed_fs;          // +0x038
    FileSystemHeader* fs_header;                // +0x040
    u64 region_entry;                           // +0x048
    FileInfoBucket* file_info_buckets;          // +0x050
    HashToIndex* file_hash_to_path_index;       // +0x058
    FilePath* file_paths;                       // +0x060
    FileInfoIndex* file_info_indices;           // +0x068
    HashToIndex* dir_hash_to_info_index;        // +0x070
    DirInfo* dir_infos;                         // +0x078
    DirectoryOffset* folder_offsets;            // +0x080
    HashToIndex* folder_child_hashes;           // +0x088
    FileInfo* file_infos;                       // +0x090
    FileInfoToFileData* file_info_to_datas;     // +0x098
    FileData* file_datas;                       // +0x0A0
    u64 unk_section;                            // +0x0A8
    StreamHeader* stream_header;                // +0x0B0
    QuickDir* quick_dirs;                       // +0x0B8
    HashToIndex* stream_hash_to_entries;        // +0x0C0
    StreamEntry* stream_entries;                // +0x0C8
    u32* stream_file_indices;                   // +0x0D0
    StreamData* stream_datas;                   // +0x0D8
    FileInfoBucket* extra_buckets;              // +0x0E0
    u64 extra_entries;                          // +0x0E8
    DirectoryOffset* extra_folder_offsets;      // +0x0F0
    u64 extra_entry_vector[3];                  // +0x0F8 — CppVector<T>
    u32 version;                                // +0x110
    u32 extra_count;                            // +0x114
    LoadedSearchSection* loaded_file_system_search; // +0x118
};

// PathInformation — wrapper for the parsed ARC and search section
// [derived: ARCropolis PathInformation = { arc, search }]
struct PathInformation {
    LoadedArc* arc;                         // +0x00
    LoadedSearchSection* search;            // +0x08
};

} // namespace resource
