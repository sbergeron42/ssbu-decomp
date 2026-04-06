#pragma once
#include "types.h"

// zlib 1.2.11.f-NINTENDO-SDK-v1 — Nintendo's proprietary fork
// [derived: version string at 0x7100012ef0 callers, state magic 0x3f34]
// [derived: Ghidra decompilation of FUN_71000281d0 (inflateInit2_)]

// Return codes (standard zlib)
#define Z_OK            0
#define Z_STREAM_ERROR  (-2)
#define Z_MEM_ERROR     (-4)
#define Z_VERSION_ERROR (-6)

// Nintendo state magic — replaces standard INIT_STATE=42
// [derived: inflateInit2_ sets state+8 = 0x3f34, validates (status - 0x3f34) < 0x20]
#define NX_INIT_STATE   0x3f34

// z_stream — standard zlib on AArch64 (sizeof = 0x70 = 112)
// [derived: inflateInit2_ checks stream_size == 0x70]
// [derived: field offsets from Ghidra FUN_71000281d0 pointer arithmetic]
typedef void* (*alloc_func)(void* opaque, u32 items, u32 size);
typedef void  (*free_func)(void* opaque, void* address);

struct z_stream_s {
    void*       next_in;     // +0x00
    u32         avail_in;    // +0x08
    u32         _pad0;       // +0x0C
    u64         total_in;    // +0x10
    void*       next_out;    // +0x18
    u32         avail_out;   // +0x20
    u32         _pad1;       // +0x24
    u64         total_out;   // +0x28
    char*       msg;         // +0x30
    void*       state;       // +0x38 — struct inflate_state* or struct deflate_state*
    alloc_func  zalloc;      // +0x40
    free_func   zfree;       // +0x48
    void*       opaque;      // +0x50
    s32         data_type;   // +0x58
    u32         _pad2;       // +0x5C
    u64         adler;       // +0x60
    u64         reserved;    // +0x68
};
// static_assert: sizeof(z_stream_s) == 0x70

typedef struct z_stream_s z_stream;

// inflate_state — Nintendo fork, 0x1bf8 bytes
// [derived: zalloc(opaque, 1, 0x1bf8) in inflateInit2_]
// Only fields accessed by inflateInit2_ are mapped; rest is padding.
struct inflate_state {
    z_stream*   strm;       // +0x000 [derived: *state = strm]
    u32         status;     // +0x008 [derived: state+8 = 0x3f34]
    u32         _pad0;      // +0x00C
    s32         wrap;       // +0x010 [derived: state+0x10 = iVar8]
    u32         field_14;   // +0x014 [derived: set to 0]
    u32         _pad1;      // +0x018
    u32         field_1c;   // +0x01C [derived: set to 0x8000]
    u64         _pad2;      // +0x020
    u64         field_28;   // +0x028 [derived: set to 0]
    u64         field_30;   // +0x030 [derived: set to 0]
    u32         wbits;      // +0x038 [derived: window bits]
    u32         field_3c;   // +0x03C [derived: set to 0, from offset 0x3c]
    u32         field_40;   // +0x040
    u32         field_44;   // +0x044 [derived: set to 0]
    u64         window;     // +0x048 [derived: state+0x48 = window ptr]
    u64         field_50;   // +0x050 [derived: set to 0]
    u32         field_58;   // +0x058 [derived: set to 0]
    u32         _pad3;      // +0x05C
    u64         _pad4;      // +0x060
    u64         field_68;   // +0x068 [derived: set to &state[0xab] = state+0x558]
    u64         field_70;   // +0x070 [derived: set to &state[0xab] = state+0x558]
    u8          _gap78[0x18]; // +0x078
    u64         field_90;   // +0x090 [derived: set to &state[0xab] = state+0x558]
    u8          _gap98[0x4C0]; // +0x098 to +0x558
    u8          codes[0x1690]; // +0x558 — internal codes area
    u8          _gapBE8[0x1000]; // pad to +0x1BE8
    u64         field_1be8; // +0x1BE8 [derived: set to 1]
    u8          _pad_end[8]; // +0x1BF0 to 0x1BF8
};
// static_assert: sizeof(inflate_state) == 0x1bf8

// Default alloc/free function pointers
// [derived: PTR_FUN_71052a2290 = default zalloc, PTR_LAB_71052a2298 = default zfree]
extern alloc_func zcalloc_ptr;
extern free_func  zcfree_ptr;
