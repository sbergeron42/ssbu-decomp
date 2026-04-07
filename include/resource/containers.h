#pragma once
#include "types.h"

// Resource service container types used by C2ResourceServiceNX
// [derived: ARCropolis src/resource/containers.rs — community RE, validated by mod loader hooks]

namespace resource {

// Game's std::vector equivalent (3 pointers, 0x18 bytes)
// [derived: ARCropolis CppVector<T>, confirmed by sizeof checks in mod hooks]
template<typename T>
struct CppVector {
    T* start;     // +0x00
    T* end;       // +0x08
    T* eos;       // +0x10 — end of storage (capacity)

    u64 size() const { return end - start; }
    u64 capacity() const { return eos - start; }
};

// Load request type
// [derived: ARCropolis LoadInfo, field names from inflate/loading thread hook analysis]
struct LoadInfo {
    u32 ty;              // +0x00 — LoadType: 0=Directory, 1=File
    u32 filepath_index;  // +0x04
    u32 directory_index; // +0x08
    u32 files_to_load;   // +0x0C
};

// Doubly-linked list node for load request queues
// [derived: ARCropolis ListNode, confirmed by res_load_loop traversal hooks]
struct ListNode {
    ListNode* next;  // +0x00
    ListNode* prev;  // +0x08
    LoadInfo data;   // +0x10
};

// Load request queue (doubly-linked list, 0x18 bytes)
// [derived: ARCropolis ResList, 5 instances in ResServiceNX at +0x58]
struct ResList {
    u64 size;        // +0x00
    ListNode* next;  // +0x08
    ListNode* end;   // +0x10
};

// Fixed-length string with inline storage (256 bytes + u16 length)
// [derived: FUN_7103541200 accesses out_path[0x100] as u16 length, data at [0x00..0xFF]]
// [derived: ResServiceNX+0xE8 has matching layout — char[256] followed by u16 length at +0x1E8]
struct FixedString256 {
    char data[256];  // +0x000
    u16 length;      // +0x100
};

} // namespace resource
