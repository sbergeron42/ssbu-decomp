#include "types.h"

// Collision/overlap detection system — 0x71037b address range, batch d-012
//
// Functions operate on internal collision engine structs (NOT BattleObjectModuleAccessor).
// Struct relationships recovered from Ghidra analysis of callers
// FUN_71037b50c0, FUN_71037b6350, FUN_71037b8a60:
//
//   CollisionManager → owns linked list of ContactPair nodes
//   ContactPair → links body_a (CollidableBody*) and body_b (CollidableBody*)
//   CollidableBody → has shape_data pointer and per-body overlap list
//   OverlapResultSet → temp container with 3 arrays + counters for resolution pass

// ---- Local struct definitions -----------------------------------------------
// [ALL INFERRED — no .dynsym evidence; layout recovered from Ghidra caller analysis]

// ContactPair — collision contact linking two collidable bodies
// [inferred: doubly-linked list node in manager's global list (+0x10/+0x18),
//  also has embedded nodes for per-body overlap chains at +0x20..+0x5f — xref FUN_71037b50c0]
struct ContactPair {
    u8 pad_0x00[8];           // +0x00 [unknown]
    u32 contact_flags;        // +0x08 [inferred: bit 0=active, 1=marked, 2=valid, 3=dirty, 5=has_cached_toi — FUN_71037b8a60]
    u8 pad_0x0c[4];          // +0x0c
    s64 prev_global;          // +0x10 [inferred: prev in manager's global contact list — FUN_71037b50c0 unlinks]
    s64 next_global;          // +0x18 [inferred: next in manager's global contact list — FUN_71037b50c0 unlinks]
    u8 pad_0x20[0x40];       // +0x20 [inferred: two embedded list nodes for per-body overlap chains]
    void* body_a;             // +0x60 [inferred: first collidable body — getter FUN_71037b3130, xref FUN_71037b50c0]
    void* body_b;             // +0x68 [inferred: second collidable body — getter FUN_71037b3150, xref FUN_71037b50c0]
    u32 shape_index_a;        // +0x70 [inferred: shape index for body_a — getter FUN_71037b5570, xref FUN_71037b8a60]
    u32 shape_index_b;        // +0x74 [inferred: shape index for body_b — getter FUN_71037b5590, xref FUN_71037b8a60]
};

// CollidableBody — a body in the collision world
// [inferred: holds shape data and per-body overlap list — xref FUN_71037b50c0, FUN_71037b6350]
struct CollidableBody {
    u8 pad_0x00[0x10];       // +0x00 [unknown]
    void* shape_data;         // +0x10 [inferred: shape/proxy data — getter FUN_71037b52d0, xref FUN_71037b50c0]
    void* field_0x18;         // +0x18 [inferred: passed to FUN_71037af510 via FUN_71037b9be0, transform data?]
    u8 pad_0x20[0x1a];       // +0x20
    u8 body_flags;            // +0x3a [inferred: bit 0 = sleeping/frozen — FUN_71037b6750 checks, xref FUN_71037b6350]
    u8 pad_0x3b[0x4d];       // +0x3b
    void* overlap_list_head;  // +0x88 [inferred: head of per-body overlap chain — getter FUN_71037b6730, xref FUN_71037b6350]
};

// ShapeData — shape/proxy data attached to a CollidableBody
// [inferred: accessed via CollidableBody::shape_data, geometry at +0x1c..+0x3c — xref FUN_71037b8a60]
struct ShapeData {
    s32 type;                 // +0x00 [inferred: shape type, compared to 0 and 2 in FUN_71037b8a60]
    u16 shape_flags;          // +0x04 [inferred: bit 1 by FUN_71037b55d0, bit 3 by FUN_71037b9690, bit 5 by FUN_71037b3600]
    u8 pad_0x06[0x16];       // +0x06
    s32 field_0x1c;           // +0x1c [inferred: geometry data or sentinel, checked == -1 by FUN_71037b4430]
};

// OverlapResultSet — temporary container for collision resolution
// [inferred: stack-allocated in FUN_71037b8a60, initialized by FUN_71037b9e40]
struct OverlapResultSet {
    u8 pad_0x00[0x10];       // +0x00 [unknown — set up by FUN_71037b9e40]
    s64* bodies_array;        // +0x10 [inferred: body pointers, indexed by bodies_count — FUN_71037b8980]
    s64* contacts_array;      // +0x18 [inferred: contact pair pointers, indexed by contacts_count — FUN_71037b89e0]
    s64* pairs_array;         // +0x20 [inferred: resolved pair pointers, indexed by pairs_count — FUN_71037b8a10]
    u8 pad_0x28[0x10];       // +0x28
    u32 bodies_count;         // +0x38 [inferred: count for bodies_array — cleared by FUN_71037b8960]
    u32 pairs_count;          // +0x3c [inferred: count for pairs_array — cleared by FUN_71037b8960]
    u32 contacts_count;       // +0x40 [inferred: count for contacts_array — cleared by FUN_71037b8960]
};

// ---- External declarations -----------------------------------------------

extern "C" float sqrtf(float);

extern void FUN_71037af510(u64);

// External data (vtable/label pointers)
extern u8 PTR_FUN_71052406a8[] __attribute__((visibility("hidden")));
extern u8 PTR_LAB_710517b8e0[] __attribute__((visibility("hidden")));

// ---- Functions ---------------------------------------------------------------

// === Generic utility (type not identified) ===

// 0x71037b0650 — indexed access: *(base+0x10)[index] with 8-byte stride (48 bytes)
__attribute__((optnone))
s64 FUN_71037b0650(s64 param_1, s32 param_2) { return *(s64*)(param_1 + 0x10) + (s64)param_2 * 8; }

// 0x71037b0c80 — copy u64 at +8 from src to dst (32 bytes)
__attribute__((optnone))
void FUN_71037b0c80(s64 param_1, s64 param_2) { *(u64*)(param_1 + 8) = *(u64*)(param_2 + 8); }

// 0x71037b0cb0 — write vtable pointer from PTR_FUN_71052406a8 (32 bytes)
__attribute__((optnone))
void FUN_71037b0cb0(u64 *param_1) { *param_1 = (u64)PTR_FUN_71052406a8; }

// 0x71037b3620 — init u16 triple: {1, 0xffff, 0} (48 bytes)
// [inferred: sentinel initialization for some small struct, no known type]
__attribute__((optnone))
void FUN_71037b3620(u16 *param_1)
{
    *param_1 = 1;
    param_1[1] = 0xffff;
    param_1[2] = 0;
}

// 0x71037b8940 — dereference u32 pointer (32 bytes)
__attribute__((optnone))
u64 FUN_71037b8940(u32 *param_1) { return *param_1; }

// 0x71037b9c10 — return pointer to inline data at +0xc (32 bytes)
__attribute__((optnone))
s64 FUN_71037b9c10(s64 param_1) { return param_1 + 0xc; }

// 0x71037bc690 — sqrtf(a * b), result discarded — compiler artifact (48 bytes)
__attribute__((optnone))
void FUN_71037bc690(float param_1, float param_2) { sqrtf(param_1 * param_2); }

// === ContactPair getters/setters ===

// 0x71037b3130 — ContactPair::get_body_a (32 bytes)
// [inferred: returns first body in collision pair — xref FUN_71037b50c0, FUN_71037b8a60]
__attribute__((optnone))
u64 FUN_71037b3130(s64 param_1)
{
    return (u64)reinterpret_cast<ContactPair*>(param_1)->body_a;
}

// 0x71037b3150 — ContactPair::get_body_b (32 bytes)
// [inferred: returns second body in collision pair — xref FUN_71037b50c0, FUN_71037b8a60]
__attribute__((optnone))
u64 FUN_71037b3150(s64 param_1)
{
    return (u64)reinterpret_cast<ContactPair*>(param_1)->body_b;
}

// 0x71037b5570 — ContactPair::get_shape_index_a (32 bytes)
// [inferred: shape index for body_a — xref FUN_71037b8a60 passes to FUN_71037af3a0]
__attribute__((optnone))
u64 FUN_71037b5570(s64 param_1)
{
    return reinterpret_cast<ContactPair*>(param_1)->shape_index_a;
}

// 0x71037b5590 — ContactPair::get_shape_index_b (32 bytes)
// [inferred: shape index for body_b — xref FUN_71037b8a60 passes to FUN_71037af3a0]
__attribute__((optnone))
u64 FUN_71037b5590(s64 param_1)
{
    return reinterpret_cast<ContactPair*>(param_1)->shape_index_b;
}

// 0x71037b55b0 — return linked list next pointer at +0x18 (32 bytes)
// [inferred: likely ContactPair::next_global for iteration — offset matches]
__attribute__((optnone))
u64 FUN_71037b55b0(s64 param_1)
{
    return (u64)reinterpret_cast<ContactPair*>(param_1)->next_global;
}

// 0x71037b52f0 — ContactPair: check bit 1 of contact_flags byte (32 bytes)
// [inferred: bit 1 = marked for processing — xref FUN_71037b50c0, FUN_71037b8a60]
// NOTE: byte access to u32 field — kept as raw *(u8*) to match ldrb instruction
__attribute__((optnone))
u8 FUN_71037b52f0(s64 param_1)
{
    // +0x08 → contact_flags (byte access)
    return *(u8*)(param_1 + 8) >> 1 & 1;
}

// 0x71037b89c0 — ContactPair: check bit 2 of contact_flags byte (32 bytes)
// [inferred: bit 2 = valid/needs resolution — xref FUN_71037b8a60 checks before processing]
// NOTE: byte access to u32 field — kept as raw *(u8*) to match ldrb instruction
__attribute__((optnone))
u8 FUN_71037b89c0(s64 param_1)
{
    // +0x08 → contact_flags (byte access)
    return *(u8*)(param_1 + 8) >> 2 & 1;
}

// 0x71037b7970 — ContactPair::set_dirty — set bit 3 of contact_flags (32 bytes)
// [inferred: marks pair for recheck in next resolution pass]
__attribute__((optnone))
void FUN_71037b7970(s64 param_1)
{
    reinterpret_cast<ContactPair*>(param_1)->contact_flags |= 8;
}

// 0x71037b8a40 — return *(u64*)(p+0x68) (32 bytes)
// [inferred: same offset as ContactPair::body_b — may be same or different struct]
__attribute__((optnone))
u64 FUN_71037b8a40(s64 param_1)
{
    return (u64)reinterpret_cast<ContactPair*>(param_1)->body_b;
}

// === CollidableBody getters ===

// 0x71037b52d0 — CollidableBody::get_shape_data (32 bytes)
// [inferred: returns shape/proxy data pointer — xref FUN_71037b50c0, FUN_71037b8a60]
__attribute__((optnone))
u64 FUN_71037b52d0(s64 param_1)
{
    return (u64)reinterpret_cast<CollidableBody*>(param_1)->shape_data;
}

// 0x71037b6730 — CollidableBody::get_overlap_list_head (32 bytes)
// [inferred: per-body overlap chain head — xref FUN_71037b6350 manipulates this list]
__attribute__((optnone))
u64 FUN_71037b6730(s64 param_1)
{
    return (u64)reinterpret_cast<CollidableBody*>(param_1)->overlap_list_head;
}

// 0x71037b6750 — CollidableBody::is_sleeping — bit 0 of body_flags at +0x3a (32 bytes)
// [inferred: xref FUN_71037b6350 skips pair creation if both bodies sleeping]
__attribute__((optnone))
u8 FUN_71037b6750(s64 param_1)
{
    return reinterpret_cast<CollidableBody*>(param_1)->body_flags & 1;
}

// 0x71037b97a0 — CollidableBody::get_field_0x18 (32 bytes)
// [inferred: passed to FUN_71037af3a0 as transform/position data in FUN_71037b8a60]
__attribute__((optnone))
u64 FUN_71037b97a0(s64 param_1)
{
    return (u64)reinterpret_cast<CollidableBody*>(param_1)->field_0x18;
}

// 0x71037b9be0 — call FUN_71037af510 with field at +0x18 (48 bytes)
// [inferred: likely CollidableBody, same +0x18 offset as FUN_71037b97a0]
__attribute__((optnone))
void FUN_71037b9be0(s64 param_1) { FUN_71037af510(*(u64*)(param_1 + 0x18)); }

// === ShapeData getters ===

// 0x71037b3600 — ShapeData: check bit 5 of shape_flags (32 bytes)
// [inferred: same +0x04 u16 pattern as FUN_71037b55d0/FUN_71037b9690, likely ShapeData]
__attribute__((optnone))
u16 FUN_71037b3600(s64 param_1)
{
    return reinterpret_cast<ShapeData*>(param_1)->shape_flags >> 5 & 1;
}

// 0x71037b55d0 — ShapeData: check bit 1 of shape_flags (32 bytes)
// [inferred: xref FUN_71037b8a60 checks this on shape_data from CollidableBody]
__attribute__((optnone))
u16 FUN_71037b55d0(s64 param_1)
{
    return reinterpret_cast<ShapeData*>(param_1)->shape_flags >> 1 & 1;
}

// 0x71037b9690 — ShapeData: check bit 3 of shape_flags (32 bytes)
// [inferred: xref FUN_71037b8a60 checks this during TOI resolution]
__attribute__((optnone))
u16 FUN_71037b9690(s64 param_1)
{
    return reinterpret_cast<ShapeData*>(param_1)->shape_flags >> 3 & 1;
}

// 0x71037b4430 — check if ShapeData::field_0x1c equals -1 (32 bytes)
// [inferred: sentinel check on geometry data — same +0x1c as save/restore region in FUN_71037b8a60]
__attribute__((optnone))
u8 FUN_71037b4430(s64 param_1)
{
    return (u8)(reinterpret_cast<ShapeData*>(param_1)->field_0x1c == -1);
}

// === OverlapResultSet operations ===

// 0x71037b8960 — OverlapResultSet::clear — reset all three counters (48 bytes)
// [inferred: called at start of resolution pass in FUN_71037b8a60]
__attribute__((optnone))
void FUN_71037b8960(s64 param_1)
{
    *(u32*)(param_1 + 0x38) = 0;
    *(u32*)(param_1 + 0x40) = 0;
    *(u32*)(param_1 + 0x3c) = 0;
}

// 0x71037b8980 — OverlapResultSet::push_body — push body ptr to bodies_array (48 bytes)
// [inferred: stores body and records index at param_2+8 — xref FUN_71037b8a60]
// NOTE: kept as raw access due to mixed s32/u32 reads on bodies_count
__attribute__((optnone))
void FUN_71037b8980(s64 param_1, s64 param_2)
{
    // +0x38 → bodies_count, +0x10 → bodies_array
    *(u32*)(param_2 + 8) = *(u32*)(param_1 + 0x38);
    *(s64*)(*(s64*)(param_1 + 0x10) + (s64)*(s32*)(param_1 + 0x38) * 8) = param_2;
    *(s32*)(param_1 + 0x38) = *(s32*)(param_1 + 0x38) + 1;
}

// 0x71037b89e0 — OverlapResultSet::push_contact — append to contacts_array (48 bytes)
// [inferred: xref FUN_71037b8a60 pushes resolved contact pairs here]
__attribute__((optnone))
void FUN_71037b89e0(s64 param_1, u64 param_2)
{
    // +0x40 → contacts_count, +0x18 → contacts_array
    s32 idx = *(s32*)(param_1 + 0x40);
    *(s32*)(param_1 + 0x40) = idx + 1;
    *(u64*)(*(s64*)(param_1 + 0x18) + (s64)idx * 8) = param_2;
}

// 0x71037b8a10 — OverlapResultSet::push_pair — append to pairs_array (48 bytes)
// [inferred: xref FUN_71037b8a60 pushes pair data here]
__attribute__((optnone))
void FUN_71037b8a10(s64 param_1, u64 param_2)
{
    // +0x3c → pairs_count, +0x20 → pairs_array
    s32 idx = *(s32*)(param_1 + 0x3c);
    *(s32*)(param_1 + 0x3c) = idx + 1;
    *(u64*)(*(s64*)(param_1 + 0x20) + (s64)idx * 8) = param_2;
}

// === CollisionManager fields (large struct, +0x19xxx offsets) ===

// 0x71037b2bc0 — CollisionManager: check bit 1 at +0x19298 (32 bytes)
// [inferred: large offset suggests top-level manager — purpose unknown]
__attribute__((optnone))
u8 FUN_71037b2bc0(s64 param_1)
{
    // +0x19298 [unknown: bit 1 flag on CollisionManager]
    return *(u8*)(param_1 + 0x19298) >> 1 & 1;
}

// 0x71037b7c60 — CollisionManager: store u64 at +0x19308 (32 bytes)
__attribute__((optnone))
void FUN_71037b7c60(s64 param_1, u64 param_2) { *(u64*)(param_1 + 0x19308) = param_2; }

// 0x71037b7c90 — CollisionManager: store u64 at +0x19310 (32 bytes)
// [inferred: xref FUN_71037b8a60 uses +0x19310 value as context for FUN_71037bc750]
__attribute__((optnone))
void FUN_71037b7c90(s64 param_1, u64 param_2) { *(u64*)(param_1 + 0x19310) = param_2; }

// === Stack/pool allocator ===

// 0x71037b72b0 — stack allocator init: self-ref head + counters (48 bytes)
// [inferred: pool with element storage starting at +0x08, capacity 0x100]
__attribute__((optnone))
void FUN_71037b72b0(s64 *param_1)
{
    // +0x00 → head ptr (self-ref to +0x08) [inferred: sentinel]
    *param_1 = (s64)(param_1 + 1);
    // +0x408 → count [inferred: current stack depth, zeroed on init]
    *(u32*)(param_1 + 0x81) = 0;
    // +0x40c → capacity [inferred: max elements = 0x100]
    *(u32*)((s64)param_1 + 0x40c) = 0x100;
}

// 0x71037b73a0 — stack allocator: return count at +0x408 (32 bytes)
__attribute__((optnone))
u64 FUN_71037b73a0(s64 param_1) { return *(u32*)(param_1 + 0x408); }

// 0x71037b73c0 — stack allocator: pop — decrement count, return element (48 bytes)
__attribute__((optnone))
u64 FUN_71037b73c0(s64 *param_1)
{
    // +0x408 → count; decrement then index into array at +0x00
    s32 count = (s32)param_1[0x81] + -1;
    *(s32*)(param_1 + 0x81) = count;
    return *(u32*)(*param_1 + (s64)count * 4);
}

// === Indexed collection (0x28-byte stride) ===

// 0x71037b5650 — indexed element base: array[index] with stride 0x28 (48 bytes)
// [inferred: array pointer at +0x08, element size 0x28 bytes]
__attribute__((optnone))
s64 FUN_71037b5650(s64 param_1, s32 param_2) { return *(s64*)(param_1 + 8) + (s64)param_2 * 0x28; }

// 0x71037b6320 — indexed element field: array[index].field_0x10 (48 bytes)
// [inferred: returns u64 at +0x10 within 0x28-stride element]
__attribute__((optnone))
u64 FUN_71037b6320(s64 param_1, s32 param_2)
{
    return *(u64*)(*(s64*)(param_1 + 8) + (s64)param_2 * 0x28 + 0x10);
}

// FUN_71031758c0 is defined in fun_batch_d_001.cpp
