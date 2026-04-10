#pragma once
#include "types.h"

// Pipeline rendering types for cross2app material binding system
// These structs model the material parameter pipeline used for ink rendering
// ("UpdateInkThreshold", "UpdateInkColor", "UpdateResetInk").
//
// The pipeline manages:
//   1. A std::unordered_map<string, SharedValue> of material bindings
//   2. A vector of shared_ptr-like entries referencing material objects
//   3. A vector of 0x330-byte matrix elements with identity-initialized transforms
//   4. A state object with mutex-protected mutable state
//
// All libc++ struct layouts below match Clang 8.0.0 libc++ (the NX SDK version).

// ============================================================================
// libc++ internal types (Clang 8.0.0 / NX SDK 8.2.1)
// ============================================================================

// libc++ std::__1::basic_string<char> with SSO (Short String Optimization)
// [derived: libc++ source <string>, confirmed by SSO flag pattern in compiled code]
// When (raw[0] & 1) == 0: short mode — length = raw[0] >> 1, data at raw+1
// When (raw[0] & 1) == 1: long mode — cap at +0x00 (|1), length at +0x08, data at +0x10
struct LibcppString {
    u8 raw[0x18];   // +0x00 — SSO union (24 bytes total)

    bool is_long() const { return raw[0] & 1; }

    u64 length() const {
        if (is_long()) return *reinterpret_cast<const u64*>(raw + 8);
        return raw[0] >> 1;
    }

    const char* data() const {
        if (is_long()) return *reinterpret_cast<char* const*>(raw + 0x10);
        return reinterpret_cast<const char*>(raw + 1);
    }

    // Long mode accessors
    u64 long_cap() const { return *reinterpret_cast<const u64*>(raw); }
    u64 long_size() const { return *reinterpret_cast<const u64*>(raw + 8); }
    char* long_data() const { return *reinterpret_cast<char* const*>(raw + 0x10); }
};
static_assert(sizeof(LibcppString) == 0x18, "LibcppString must be 24 bytes");

// Red-black tree node for std::set<LibcppString>
// [derived: libc++ __tree_node_base + __tree_node layout, Clang 8.0.0]
// [inferred: 0x38 bytes allocated per node in FUN_710354f470 (tree_insert_unique)]
struct StringTreeNode {
    StringTreeNode* left;      // +0x00 — __left_ (or __end_node::__left_ for header)
    StringTreeNode* right;     // +0x08 — __right_
    StringTreeNode* parent;    // +0x10 — __parent_
    u64 color;                 // +0x18 — __is_black_ (bool, padded to 8 for alignment)
    LibcppString value;        // +0x20 — stored string value
};
static_assert(sizeof(StringTreeNode) == 0x38, "StringTreeNode must be 0x38 bytes");

// Red-black tree header (std::set<LibcppString> object)
// [derived: libc++ __tree header: __begin_node_, __pair1_ (end/root), __pair3_ (size)]
// [inferred: 3-long local in FUN_710354e4e0 — begin=&root, root=null, size=0]
struct StringTreeHeader {
    StringTreeNode* begin_node;  // +0x00 — leftmost node (or &end_node if empty)
    StringTreeNode* root;        // +0x08 — root of tree (null if empty)
    u64 size;                    // +0x10 — element count
};

// ============================================================================
// Hash map types (std::unordered_map<string, SharedValue>)
// ============================================================================

// Hash map node for material bindings
// [inferred: 0x48 bytes allocated in FUN_710354e4e0 pipeline_update]
// [inferred: layout from insert sequence — next, hash, key string, value fields]
struct MaterialHashNode {
    MaterialHashNode* next;    // +0x00 — next node in bucket chain
    u64 hash;                  // +0x08 — cached hash of key
    LibcppString key;          // +0x10 — key string (0x18 bytes)
    void* value_vtable;        // +0x28 — value object vtable (PTR_LAB_710522ee00)
    void* value_ptr;           // +0x30 — value: pointer to bound material object
    void* value_ctrl;          // +0x38 — value: shared_ptr control block
    u64 value_ref;             // +0x40 — value: cached reference count
};
static_assert(sizeof(MaterialHashNode) == 0x48, "MaterialHashNode must be 0x48 bytes");

// Hash map object (embedded in PipelineContainer)
// [derived: libc++ unordered_map layout: bucket_list, element_count, max_load_factor]
// [inferred: fields at pipeline +0x98..+0xBC]
struct MaterialHashMap {
    MaterialHashNode** buckets;   // +0x00 — bucket array
    u64 bucket_count;             // +0x08 — number of buckets
    MaterialHashNode* head;       // +0x10 — linked list of all entries
    u64 size;                     // +0x18 — element count
    f32 max_load_factor;          // +0x20 — max load factor for rehash
    u32 pad;                      // +0x24
};
static_assert(sizeof(MaterialHashMap) == 0x28, "MaterialHashMap must be 0x28 bytes");

// ============================================================================
// Pipeline-specific types
// ============================================================================

// Shared-pointer-like entry in the pipeline's binding vector (0x20 bytes per slot)
// [inferred: stride 0x20 in vector at PipelineContainer +0xC0]
// [inferred: layout from pipeline_update — vtable, obj_ptr, ctrl_ptr, ref_copy]
struct PipelineBindingEntry {
    void* vtable;      // +0x00 — entry vtable (PTR_LAB_710522ede0)
    void* obj_ptr;     // +0x08 — bound object pointer
    void* ctrl_ptr;    // +0x10 — shared_ptr control block
    u64 ref_copy;      // +0x18 — cached ref count or version
};
static_assert(sizeof(PipelineBindingEntry) == 0x20, "PipelineBindingEntry must be 0x20 bytes");

// Matrix element (0x330 bytes) — material instance with 4x identity matrices
// [inferred: stride 0x330 in vector at PipelineContainer +0xE0]
// [inferred: memset(0, 0x1D0), then 4 identity 4x4 matrices at +0x1D0..+0x30C]
// [inferred: packed float render constants at various sub-offsets]
struct PipelineMatrixElement {
    u8 base_data[0x1D0];          // +0x000 — zeroed material parameters
    f32 matrices[4 * 16];         // +0x1D0 — 4 identity 4x4 float matrices (0x100 bytes)
    u8 render_constants[0x60];    // +0x2D0 — packed float render constants
};
static_assert(sizeof(PipelineMatrixElement) == 0x330, "PipelineMatrixElement must be 0x330 bytes");

// Node link hash map (maps hash → material entry)
// [inferred: fields at PipelineContainer +0x108..+0x128]
// Same libc++ unordered_map layout but with different node type
struct NodeLinkHashMap {
    void** buckets;       // +0x00 — bucket array
    u64 bucket_count;     // +0x08
    void* head;           // +0x10 — linked list head
    u64 size;             // +0x18 — element count
};

// Sub-object pool manager
// [inferred: accessed via PipelineContainer +0x90, stride 0x80 per element]
struct SubPoolManager {
    void* pool_vec_start;     // +0x00 — vector of pointers: start
    void* pool_vec_end;       // +0x08 — vector of pointers: end
    void* pool_vec_eos;       // +0x10 — vector of pointers: end-of-storage
    u64 next_free;            // +0x18 — next free index
    u64 unk_0x20;             // +0x20
    u64 capacity;             // +0x28 — max element count
    void* pool_base;          // +0x30 — base pointer to allocated pool memory
};

// Pipeline state object (0x110 bytes)
// [inferred: allocated in FUN_710354d400 pipeline_init, has mutex at +0x68]
// [inferred: "ErrorDummy" string written at +0x50..+0x5A]
struct PipelineStateObject {
    void* vtable;              // +0x00 — state vtable (PTR_FUN_710522eda8)
    u64 field_0x08;            // +0x08
    u64 field_0x10;            // +0x10
    u16 field_0x18;            // +0x18 — init state (set to 0 then 1)
    u8 field_0x1A;             // +0x1A — flag (set to 1)
    u8 pad_0x1B[5];            // +0x1B
    s64 field_0x20;            // +0x20 — set to -1
    u64 field_0x28;            // +0x28 — object pointer (vtable-dispatched destroy)
    u64 field_0x30;            // +0x30
    u64 field_0x38;            // +0x38
    void* vtable2;             // +0x40 — secondary vtable (PTR_LAB_710522ef60)
    u64 field_0x48;            // +0x48
    u64 field_0x50;            // +0x50
    u64 field_0x58;            // +0x58
    u64 field_0x60;            // +0x60
    u8 mutex[0x28];            // +0x68 — std::mutex (NX: nn::os::MutexType, ~40 bytes)
    u64 field_0x90;            // +0x90
    u64 field_0x98;            // +0x98
    u8 field_0xA0;             // +0xA0
    u8 pad_0xA1[7];            // +0xA1
    u64 field_0xA8;            // +0xA8
    u64 field_0xB0;            // +0xB0
    u64 field_0xB8;            // +0xB8
    u64 field_0xC0;            // +0xC0
    u64 field_0xC8;            // +0xC8
    u8 field_0xD0;             // +0xD0
    u8 field_0xD1;             // +0xD1 — "ErrorDummy" string length byte
    u8 pad_0xD2[6];            // +0xD2
    u8 unk_0xD8[0x20];         // +0xD8
    u16 field_0xF0;            // +0xF0 — set to 1
    u8 field_0xF2;             // +0xF2 — flag byte
    u8 pad_0xF3[5];            // +0xF3
    u64 field_0xF8;            // +0xF8
    u64 field_0x100;           // +0x100
    u64 field_0x108;           // +0x108
};
// Note: sizeof not validated yet — field layout needs refinement
// static_assert(sizeof(PipelineStateObject) == 0x110, "PipelineStateObject must be 0x110 bytes");

// ============================================================================
// PipelineContainer — main rendering pipeline object
// ============================================================================

// [inferred: param_1 type in pipeline_init, pipeline_update, pipeline_clear, pipeline_link]
// [inferred: field offsets from decompiled access patterns across all 4 functions]
struct PipelineContainer {
    u8 unk_0x00[0x68];                              // +0x000

    // Sub-pipeline vector (vtable-dispatched objects, 0x20 bytes each)
    // [inferred: reverse-iterated in pipeline_init, calling dtor via vtable]
    PipelineBindingEntry* sub_pipelines_start;       // +0x068
    PipelineBindingEntry* sub_pipelines_end;         // +0x070
    PipelineBindingEntry* sub_pipelines_eos;         // +0x078

    u8 unk_0x80[0x10];                               // +0x080

    // Sub-object pool manager
    // [inferred: allocated with param_2 * 0x80 elements in pipeline_init]
    SubPoolManager* sub_pool;                        // +0x090

    // Material binding hash map (std::unordered_map<string, SharedValue>)
    // [inferred: cleared in pipeline_clear, populated in pipeline_update]
    MaterialHashMap material_map;                    // +0x098

    // Shared-pointer binding vector
    // [inferred: appended in pipeline_update, cleared in pipeline_clear]
    PipelineBindingEntry* binding_vec_start;          // +0x0C0
    PipelineBindingEntry* binding_vec_end;            // +0x0C8
    PipelineBindingEntry* binding_vec_eos;            // +0x0D0

    // Matrix element count and vector (0x330-byte elements)
    // [inferred: resized in pipeline_init with param_3 count, identity matrices]
    u64 matrix_count;                                // +0x0D8
    PipelineMatrixElement* matrix_vec_start;          // +0x0E0
    PipelineMatrixElement* matrix_vec_end;            // +0x0E8
    PipelineMatrixElement* matrix_vec_eos;            // +0x0F0

    // Reference pointer (stored from param_4 in pipeline_init)
    // [inferred: opaque reference, not dereferenced in these functions]
    void* reference;                                 // +0x0F8

    u8 unk_0x100[0x08];                              // +0x100

    // Node link hash map (maps node hashes to matrix elements)
    // [inferred: searched in pipeline_link_nodes, cleared in pipeline_init]
    NodeLinkHashMap link_map;                        // +0x108

    u8 unk_0x128[0x08];                              // +0x128

    // State shared_ptr (mutex-protected state object)
    // [inferred: allocated/swapped in pipeline_init, dereferenced for state access]
    void* state_ptr;                                 // +0x130
    void* state_ctrl;                                // +0x138
};
