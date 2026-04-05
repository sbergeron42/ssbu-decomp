#include "types.h"

// MEDIUM-tier FUN_* functions — 0x71001xxxxx range, batch d4-012
// Pool-d worker: auto-generated from Ghidra decompilation
// Includes: struct inits, bit ops, zero-fill, network ctx, vtable calls, bool checks

// ---- External declarations -----------------------------------------------

// Multiplier for time conversion (FUN_710015d240)
#pragma GCC visibility push(hidden)
extern u64 PTR_DAT_71052a3cd0;

// Network context pointer (FUN_7100162ce0 / 7100163d40)
extern u64 PTR_DAT_71052a3bd8;

// Vtable bases for struct inits
extern u64 PTR_DAT_71052a53d8;
extern u64 PTR_DAT_71052a53e0;
extern u64 PTR_DAT_71052a53e8;
extern u64 PTR_DAT_71052a5528;
#pragma GCC visibility pop

// FUN_710015e850 / FUN_710015e880 callees
extern "C" u64 FUN_710015f5c0(s64, s8);
extern "C" u64 FUN_710015f600(s64, s8, u32);

// FUN_7100181270 callees
extern "C" u64 FUN_71000b2850(s64);
extern "C" u64 FUN_71000b2b10(s64, s64);

// FUN_7100194e60 callee
extern "C" u64 FUN_7100157cf0(s64);

// ---- Functions ---------------------------------------------------------------

// 0x71001583c0 — write 3 u64 fields + 2 bit0 bytes into array entry at index field+0xa00
void FUN_71001583c0(s64 self, u64 value_a, u64 value_b, u64 value_c, u8 flag_c, u8 flag_a, u8 flag_b)
{
    s64 entry_base;
    u32 entry_count;

    entry_count = *(u32 *)(self + 0xa00);
    entry_base = self + (u64)entry_count * 0x20;
    *(u8 *)(entry_base + 0x638) = flag_a & 1;
    *(u64 *)(entry_base + 0x620) = value_a;
    *(u64 *)(entry_base + 0x628) = value_b;
    *(u64 *)(entry_base + 0x630) = value_c;
    *(u8 *)(entry_base + 0x639) = flag_b & 1;
    *(u8 *)(entry_base + 0x63a) = flag_c & 1;
    *(u32 *)(self + 0xa00) = entry_count + 1;
}

// 0x710015e850 — if ptr+0x50 != 0 and byte+0x38 != -3: call FUN_710015f5c0, else -1
u64 FUN_710015e850(s64 self)
{
    u64 result;

    if ((*(s64 *)(self + 0x50) != 0) && (*(s8 *)(self + 0x38) != -3)) {
        result = FUN_710015f5c0(*(s64 *)(self + 0x50), *(s8 *)(self + 0x38));
        return result;
    }
    return 0xffffffff;
}

// 0x710015fb50 — if *conn_state != 0: clear connection state fields (disconnect cleanup)
void FUN_710015fb50(s8 *conn_state)
{
    if (*conn_state != '\0') {
        *(u64 *)((u8 *)conn_state + 4) = 0xFFFFFFFFFFFFFFFFULL;
        *conn_state = '\0';
        *(u64 *)(conn_state + 0x10) = 0;
        *(u8 *)(conn_state + 0x18) = 0;
        *(u64 *)(conn_state + 0x48) = 0;
        *(u64 *)((u8 *)conn_state + 0x1c) = 0;
        *(u32 *)(conn_state + 0xc) = 0xFFFFFFFF;
        *(u32 *)(conn_state + 0x50) = 0;
    }
}

// 0x7100162ce0 — clamp field+0xa4 to [1..0xfe]→0xff, write to PTR_DAT+0x2b6
void FUN_7100162ce0(s64 self)
{
    s32 clamped_value;

    clamped_value = *(s32 *)(self + 0xa4);
    if (0xfd < clamped_value - 1U) {
        clamped_value = 0xff;
    }
    *(s8 *)(PTR_DAT_71052a3bd8 + 0x2b6) = (s8)clamped_value;
}

// 0x7100163d40 — clamp field+0xa4 to [1..0xfe]→0xff, write to PTR_DAT+0x2b7
void FUN_7100163d40(s64 self)
{
    s32 clamped_value;

    clamped_value = *(s32 *)(self + 0xa4);
    if (0xfd < clamped_value - 1U) {
        clamped_value = 0xff;
    }
    *(s8 *)(PTR_DAT_71052a3bd8 + 0x2b7) = (s8)clamped_value;
}

// 0x7100164070 — zero-fill 0x400-byte region in 0x20-byte blocks, then clear trailing u32
void FUN_7100164070(s64 base)
{
    u64 *block_ptr;
    s64 offset;

    offset = 0;
    do {
        block_ptr = (u64 *)(base + offset);
        offset = offset + 0x20;
        *block_ptr = 0;
        block_ptr[1] = 0;
        block_ptr[2] = 0;
        *(u32 *)(block_ptr + 3) = 0;
        *(u8 *)((s64)block_ptr + 0x1c) = 0;
#ifdef MATCHING_HACK_NX_CLANG
        asm("");
#endif
    } while (offset != 0x400);
    *(u32 *)(base + 0x400) = 0;
}

// 0x7100174530 — call vtable[0x30], then clear byte at self+9
void FUN_7100174530(s64 *self)
{
    (**(void(**)())(*self + 0x30))();
    *(u8 *)((s64)self + 9) = 0;
}

// 0x7100174cb0 — true if byte+8 != 0 and nested ptr field+0x418 != 0
u8 FUN_7100174cb0(s64 self)
{
    if (*(s8 *)(self + 8) == '\0') {
        return 0;
    }
    if (*(s64 *)(self + 0x18) != 0) {
        return *(s32 *)(*(s64 *)(self + 0x18) + 0x418) != 0;
    }
    return 0;
}

// 0x7100174ff0 — store target ptr, then call vtable[0x178] with local buffer
void FUN_7100174ff0(s64 self, s64 *target)
{
    u8 local_buf[16];

    *(s64 **)(self + 0x18) = target;
    (**(void(**)(u8 *, s64 *, u64))(*target + 0x178))(local_buf, target, *(u64 *)(self + 0x10));
}

// 0x7100181270 — check network protocol readiness via b2850/b2b10 chain, return field+0x46c
u32 FUN_7100181270(s64 self)
{
    s64 protocol_ctx;
    u64 is_ready;

    if (*(s32 *)(self + 0x418) == 0) {
        protocol_ctx = self + 0x2c0;
        is_ready = FUN_71000b2850(protocol_ctx);
        if ((is_ready & 1) != 0) {
            is_ready = FUN_71000b2850(self + 0x2a0);
            if (((is_ready & 1) != 0) && (is_ready = FUN_71000b2b10(self + 0x2a0, protocol_ctx), (is_ready & 1) != 0))
                goto LAB_710018128c;
        }
        is_ready = FUN_71000b2850(protocol_ctx);
        if ((is_ready & 1) == 0) {
            return 0;
        }
        is_ready = FUN_71000b2850(self + 0x2a0);
        if ((is_ready & 1) == 0) {
            return 0;
        }
        is_ready = FUN_71000b2b10(self + 0x2a0, protocol_ctx);
        if ((is_ready & 1) != 0) {
            return 0;
        }
    }
LAB_710018128c:
    return *(u32 *)(self + 0x46c);
}

// 0x7100182c70 — init event descriptor: vtable PTR+0x10, owner, event_id, type=0x12, size=0x10
void FUN_7100182c70(s64 *descriptor, s64 owner, u16 event_id)
{
    *(u16 *)(descriptor + 2) = event_id;
    *(u16 *)(descriptor + 3) = 0;
    *descriptor = (s64)(PTR_DAT_71052a53d8 + 0x10);
    descriptor[1] = owner;
    *(u8 *)((s64)descriptor + 0x12) = 0x12;
    *(u32 *)((s64)descriptor + 0x14) = 0x10;
}

// 0x7100182d10 — init event descriptor: vtable PTR+0x10, owner, event_id, type=0x13, size=0x10
void FUN_7100182d10(s64 *descriptor, s64 owner, u16 event_id)
{
    *(u16 *)(descriptor + 2) = event_id;
    *(u16 *)(descriptor + 3) = 0;
    *descriptor = (s64)(PTR_DAT_71052a53e0 + 0x10);
    descriptor[1] = owner;
    *(u8 *)((s64)descriptor + 0x12) = 0x13;
    *(u32 *)((s64)descriptor + 0x14) = 0x10;
}

// 0x7100182db0 — init event descriptor: vtable PTR+0x10, owner, event_id, event_type, extra_data, size=0x14
void FUN_7100182db0(s64 *descriptor, s64 owner, u16 event_id, u8 event_type, u32 extra_data)
{
    *(u16 *)(descriptor + 2) = event_id;
    *(u16 *)(descriptor + 3) = 0;
    *(u32 *)((s64)descriptor + 0x1c) = extra_data;
    *descriptor = (s64)(PTR_DAT_71052a53e8 + 0x10);
    descriptor[1] = owner;
    *(u8 *)((s64)descriptor + 0x12) = event_type;
    *(u32 *)((s64)descriptor + 0x14) = 0x14;
}

// 0x7100185e30 — clear bit (bit_index & 0x1f) in u32 field at self+0x5c
void FUN_7100185e30(s64 self, u32 bit_index)
{
    *(u32 *)(self + 0x5c) = *(u32 *)(self + 0x5c) & (1 << (u64)(bit_index & 0x1f) ^ 0xffffffffU);
}

// 0x7100186270 — init vtable ptr in self[0] to PTR_DAT+0x10, zero self[1] low 32b
void FUN_7100186270(s64 *self)
{
    *(u32 *)(self + 1) = 0;
    *self = (s64)(PTR_DAT_71052a5528 + 0x10);
}

// 0x7100191f90 — true if field+0x118 == 2 and field+0xe8 in [2..4]
u8 FUN_7100191f90(s64 self)
{
    if (*(s32 *)(self + 0x118) == 2) {
        return *(s32 *)(self + 0xe8) - 2U < 3;
    }
    return 0;
}

// 0x7100192260 — true if field+0x118 == 3 and field+0xe8 in [2..4]
u8 FUN_7100192260(s64 self)
{
    if (*(s32 *)(self + 0x118) == 3) {
        return *(s32 *)(self + 0xe8) - 2U < 3;
    }
    return 0;
}

// 0x7100192ce0 — true if field+0x118 == 5 and field+0xe8 in [2..4]
u8 FUN_7100192ce0(s64 self)
{
    if (*(s32 *)(self + 0x118) == 5) {
        return *(s32 *)(self + 0xe8) - 2U < 3;
    }
    return 0;
}

// 0x7100193740 — true if nested ptr at +0x38 is non-null and byte+0x84 is non-zero
u8 FUN_7100193740(s64 self)
{
    if (*(s64 *)(self + 0x38) != 0) {
        return *(s8 *)(*(s64 *)(self + 0x38) + 0x84) != '\0';
    }
    return 0;
}
