#include "types.h"

// MEDIUM-tier FUN_* functions — mixed 0x7100 ranges, batch d4-013
// Pool-d worker: auto-generated from Ghidra decompilation
// Includes: binary search, date/time calcs, init helpers, comparison, vtable calls

// ---- External declarations -----------------------------------------------

// nn::socket SDK
extern "C" long nnsocketRecv();
extern "C" int nnsocketGetLastErrno();

// Creator/factory helpers
extern "C" s64 FUN_71000b1b90();
extern "C" s64 FUN_7100130810(s64, s64);
extern "C" void FUN_7100194810(s64);
extern "C" void FUN_710017bb40(s64);
extern "C" void FUN_7100189a10(s64);
extern "C" void FUN_710019f980(s64);

// Misc helper externs
extern "C" s64 FUN_7100039590(u64);
extern "C" s64 FUN_71000399e0(u64);
extern "C" void FUN_71000bb5d0(u64 *);
extern "C" u16 FUN_710003e210(u32);
extern "C" void FUN_71002282c0(u64);
extern "C" s64 FUN_71002282f0(u64);
extern "C" s32 FUN_7100228310(u64);
extern "C" void FUN_7100228130(u64);
extern "C" u64 FUN_7100230c50();
extern "C" void FUN_7100230a20(u64);
extern "C" void FUN_71002ba5e0(u64);
extern "C" void FUN_71002c1d20(u64);
extern "C" s32 FUN_71001c4c40(u32, s64, s64, u64 *, u64, s32);
extern "C" void FUN_71001b4200(u8 *, u32 *);
extern "C" void FUN_71001e1770(u64, u32, u8 *);
extern "C" void FUN_71001f2180(s64);
extern "C" s64 FUN_71001beb00(s64);
extern "C" u64 FUN_71001b0fd0();
extern "C" void FUN_7100187f50();

// For FUN_7100130f30
extern "C" void FUN_7100133850(s64 *, u64, s32, s64 *, u64, s32, u32);
extern "C" s64 *FUN_71001352b0(u64);
extern "C" void FUN_710013ba30(s64 *);
extern "C" void FUN_710013ba40(s64 *);
extern "C" void FUN_7100131060(s64 *);

// Global data pointers
extern u64 PTR_DAT_71052a3f30;  // double-deref ulong* for FUN_71001b0960
extern u64 PTR_DAT_71052a4bd8;  // for FUN_7100130f30
extern u64 PTR_DAT_71052a4bb0;  // for FUN_7100130f30
extern u64 PTR_DAT_71052a4220;  // for FUN_71000f4d30
extern s64 *DAT_71052b60e8;     // base object pointer for FUN_710033ba50

// ---- Functions ---------------------------------------------------------------

// 0x710003a790 — return sum of two sub-object sizes
s64 FUN_710003a790(s64 self)
{
    s64 size_a;
    s64 size_b;

    size_a = FUN_7100039590(*(u64 *)(self + 8));
    size_b = FUN_71000399e0(*(u64 *)(self + 0x20));
    return size_b + size_a;
}

// 0x71000cf1d0 — set entry flag and store callback result (small-addr DAT pattern)
void FUN_71000cf1d0(s64 self)
{
    u64 callback_result;

    *(u8 *)(self + 0x1850) = 1;
    callback_result = 0;
    FUN_71000bb5d0(&callback_result);
    *(u64 *)(self + 0x1858) = callback_result;
}

// 0x71000f4d30 — init vtable pointer from global (PTR_DAT + 0x10)
void FUN_71000f4d30(s64 *self)
{
    FUN_7100187f50();
    *self = (s64)(PTR_DAT_71052a4220 + 0x10);
}

// 0x710007bdc0 — binary search: find glyph ID in font cmap table
u32 FUN_710007bdc0(s64 font, u32 codepoint)
{
    s64 base;
    u32 *mid;
    s16 format;
    s32 exclusion_count;
    u32 range_start;
    u32 *node;
    u32 *lo;
    s64 half_dist;

    range_start = *(u32 *)(*(s64 *)(font + 0x20) + 0x14);
    if (range_start == 0) {
        return 0xffff;
    }
    while( true ) {
        node = (u32 *)(*(s64 *)(font + 0x18) + (u64)range_start);
        range_start = *node;
        if ((range_start <= codepoint) && (codepoint <= node[1])) break;
        range_start = node[3];
        if (range_start == 0) {
            return 0xffff;
        }
    }
    exclusion_count = *(s32 *)(font + 0x80);
    if (exclusion_count != 0) {
        if (exclusion_count < 1) {
            return 0xffff;
        }
        half_dist = 0;
        while ((base = font + half_dist * 4, codepoint < *(u32 *)(base + 0x84) ||
               (*(u32 *)(base + 0xc4) < codepoint))) {
            half_dist = half_dist + 1;
            if (exclusion_count <= half_dist) {
                return 0xffff;
            }
        }
    }
    format = (s16)node[2];
    if (format == 2) {
        lo = node + 5;
        node = lo + (u64)(u16)node[4] * 2 + -2;
        if (lo <= node) {
            do {
                while( true ) {
                    half_dist = (s64)node - (s64)lo >> 3;
                    if (half_dist < 0) {
                        half_dist = half_dist + 1;
                    }
                    mid = lo + (half_dist >> 1) * 2;
                    range_start = *mid;
                    if (codepoint <= range_start) break;
                    lo = mid + 2;
                    if (node < lo) {
                        return 0xffff;
                    }
                }
                if (codepoint > range_start || range_start == codepoint) {
                    return (u32)(u16)mid[1];
                }
                node = mid + -2;
            } while (lo <= node);
        }
    }
    else {
        if (format == 1) {
            return (u32)*(u16 *)((s64)node + (s64)(s32)(codepoint - range_start) * 2 + 0x10);
        }
        if (format == 0) {
            return (u32)(u16)node[4] + (codepoint - range_start);
        }
    }
    return 0xffff;
}

// 0x7100130f30 — allocate and init a stream/socket object
s64 *FUN_7100130f30(s64 *self, u64 size, u64 context, u32 flags)
{
    s32 mode;
    s64 *buffer;
    s64 *lock;

    if (0x128 < (size & 0xfffffffffffffff8ULL)) {
        FUN_7100133850(self, context, 0, self, size & 0xfffffffffffffff8ULL, 1, flags & 1);
        *(u32 *)((s64)self + 0xd4) = 0;
        *self = (s64)(PTR_DAT_71052a4bd8 + 0x10);
        self[0x1b] = (s64)(self + 0x1b);
        self[0x1c] = (s64)(self + 0x1b);
        self[0x1f] = (s64)(self + 0x1e);
        self[0x20] = -0x100000000LL;
        self[0x1d] = -0x100000000LL;
        self[0x1e] = (s64)(self + 0x1e);
        if ((*(u8 *)(self + 0x1a) & 1) == 0) {
            lock = (s64 *)0x0;
            *(u32 *)((s64)self + 0xec) = 0;
            *(u32 *)((s64)self + 0x104) = 0;
            mode = (s32)self[0x11];
        }
        else {
            lock = self + 0x12;
            FUN_710013ba30(lock);
            *(u32 *)((s64)self + 0xec) = 0;
            *(u32 *)((s64)self + 0x104) = 0;
            FUN_710013ba40(lock);
            if ((*(u8 *)(self + 0x1a) & 1) == 0) {
                lock = (s64 *)0x0;
                mode = (s32)self[0x11];
            }
            else {
                FUN_710013ba30(lock);
                mode = (s32)self[0x11];
            }
        }
        if (mode == 1) {
            buffer = self + 0x21;
        }
        else {
            buffer = (s64 *)self[6];
        }
        *buffer = 0;
        buffer[1] = 0;
        *(u32 *)(buffer + 2) = 0;
        buffer[3] = 0;
        buffer[3] = self[7] + -0x128;
        FUN_7100131060(self);
        if (lock != (s64 *)0x0) {
            FUN_710013ba40(lock);
        }
        return self;
    }
    return (s64 *)0x0;
}

// 0x7100179500 — create RPC session object (type 0x118)
s64 FUN_7100179500(void)
{
    u64 allocator;
    s64 session;

    allocator = (u64)FUN_71000b1b90();
    session = FUN_7100130810(0x118, (s64)allocator);
    if (session != 0) {
        FUN_7100194810(session);
    }
    return session;
}

// 0x7100179b30 — create RPC session object (type 0xb8)
s64 FUN_7100179b30(void)
{
    u64 allocator;
    s64 session;

    allocator = (u64)FUN_71000b1b90();
    session = FUN_7100130810(0xb8, (s64)allocator);
    if (session != 0) {
        FUN_710017bb40(session);
    }
    return session;
}

// 0x7100194390 — create RPC session object (type 0xf0)
s64 FUN_7100194390(void)
{
    u64 allocator;
    s64 session;

    allocator = (u64)FUN_71000b1b90();
    session = FUN_7100130810(0xf0, (s64)allocator);
    if (session != 0) {
        FUN_7100189a10(session);
    }
    return session;
}

// 0x7100194790 — create RPC session object (type 0x1130)
s64 FUN_7100194790(void)
{
    u64 allocator;
    s64 session;

    allocator = (u64)FUN_71000b1b90();
    session = FUN_7100130810(0x1130, (s64)allocator);
    if (session != 0) {
        FUN_710019f980(session);
    }
    return session;
}

// 0x71001ae0d0 — zero-fill transport struct fields
void FUN_71001ae0d0(u64 *transport)
{
    *transport = 0;
    transport[1] = 0;
    FUN_71000bb5d0(transport + 3);
    transport[3] = 0;
    transport[4] = 0;
    FUN_71000bb5d0(transport + 3);
    transport[6] = 0;
    *(u32 *)(transport + 7) = 0;
    *(u32 *)((s64)transport + 0x2c) = 0;
    transport[8] = 0;
    *(u32 *)(transport + 9) = 0;
}

// 0x71001b0960 — convert packed date/time fields to Unix timestamp
s64 FUN_71001b0960(u64 *packed_time)
{
    u32 year;
    s32 century_adj;
    s32 century_days;
    s32 year_days;
    u32 month;
    u64 raw;
    u32 is_leap;
    s32 month_adj;

    raw = *packed_time;
    if (raw == **(u64 **)PTR_DAT_71052a3f30) {
        return 0;
    }
    month = (u32)raw >> 0x16 & 0xf;
    month_adj = -0x7d1;
    if (2 < month) {
        month_adj = -2000;
    }
    year = month_adj + ((u32)(raw >> 0x1a) & 0x3fff);
    month_adj = 9;
    if (2 < month) {
        month_adj = -3;
    }
    is_leap = 1;
    if (((s32)year < 0) && ((s32)year % 400 != 0)) {
        if ((s32)year % 100 == 0) {
            is_leap = 0;
        }
        else {
            is_leap = (u32)(((s32)year & 3) == 0);
        }
    }
    century_days = ((s32)year / 100) * 0x23ab1;
    century_adj = century_days + 3;
    if (-1 < century_days) {
        century_adj = century_days;
    }
    year_days = ((s32)year % 100) * 0x5b5;
    century_days = year_days + 3;
    if (-1 < year_days) {
        century_days = year_days;
    }
    return (raw >> 6 & 0x3f) * 0x3c + (raw & 0x3f | 0x386d4380) +
           (raw >> 0xc & 0x1f) * 0xe10 +
           (s64)(s32)(((u32)raw >> 0x11 & 0x1f) + (century_days >> 2) + (century_adj >> 2) +
                      (s32)((month_adj + (s32)month) * 0x99 + 2) / 5 + is_leap + 0x3a) * 0x15180;
}

// 0x71001b0f80 — compute NTP offset with calendar correction
u64 FUN_71001b0f80(u32 *config)
{
    s32 base_offset;
    s32 raw_offset;
    u64 result;

    result = FUN_71001b0fd0();
    raw_offset = (s32)result;
    if (raw_offset != 0) {
        result = 0x15fde20;
        if (-1 < raw_offset) {
            base_offset = 0x1600530;
            if ((*config & 0x7ff0000) != 0x720000) {
                base_offset = 0x15fde20;
            }
            result = (u64)(u32)(base_offset + raw_offset);
        }
    }
    return result;
}

// 0x71001c04e0 — network state machine: set connection phase from event code
u64 FUN_71001c04e0(s64 self, u32 event_code)
{
    u64 result;
    u64 is_ready;

    result = 0;
    switch(event_code) {
    case 0:
        result = 1;
    default:
        return result;
    case 4:
        break;
    case 5:
        if (*(s32 *)(self + 0xc0) != 0) {
            return 0;
        }
        is_ready = (*(u64(**)())(*(s64 *)(*(s64 *)(*(s64 *)(self + 0xb0) + 0x10)) + 0x48))();
        if ((is_ready & 1) != 0) {
            return 0;
        }
        *(u32 *)(self + 0xc0) = 2;
        return 0;
    case 6:
        if (*(s32 *)(self + 0xc0) != 0) {
            return 0;
        }
        is_ready = (*(u64(**)())(*(s64 *)(*(s64 *)(*(s64 *)(self + 0xb0) + 0x10)) + 0x48))();
        if ((is_ready & 1) != 0) {
            return 0;
        }
        *(u32 *)(self + 0xc0) = 3;
        return 0;
    case 7:
        if (*(s32 *)(self + 0xc0) != 0) {
            return 0;
        }
        is_ready = (*(u64(**)())(*(s64 *)(*(s64 *)(*(s64 *)(self + 0xb0) + 0x10)) + 0x48))();
        if ((is_ready & 1) != 0) {
            return 0;
        }
        *(u32 *)(self + 0xc0) = 4;
        return 0;
    case 8:
        if (*(s32 *)(self + 0xc0) != 0) {
            return 0;
        }
        is_ready = (*(u64(**)())(*(s64 *)(*(s64 *)(*(s64 *)(self + 0xb0) + 0x10)) + 0x48))();
        if ((is_ready & 1) != 0) {
            return 0;
        }
        *(u32 *)(self + 0xc0) = 5;
        return 0;
    case 9:
        if (*(s32 *)(self + 0xc0) != 0) {
            return 0;
        }
        is_ready = (*(u64(**)())(*(s64 *)(*(s64 *)(*(s64 *)(self + 0xb0) + 0x10)) + 0x48))();
        if ((is_ready & 1) != 0) {
            return 0;
        }
        *(u32 *)(self + 0xc0) = 6;
        return 0;
    }
    if (*(s32 *)(self + 0xc0) != 0) {
        return 0;
    }
    is_ready = (*(u64(**)())(*(s64 *)(*(s64 *)(*(s64 *)(self + 0xb0) + 0x10)) + 0x48))();
    if ((is_ready & 1) != 0) {
        return 0;
    }
    *(u32 *)(self + 0xc0) = 1;
    return 0;
}

// 0x71001c5010 — decompress range into output field
void FUN_71001c5010(u32 codec, s64 range, u64 dst_capacity)
{
    s32 err;
    u64 out_size;

    out_size = 0;
    err = FUN_71001c4c40(codec,
                         *(s64 *)(range + 0x10) + *(s64 *)(range + 0x28),
                         *(s64 *)(range + 0x20) - *(s64 *)(range + 0x28),
                         &out_size, dst_capacity, 1);
    if (err != 0) {
        return;
    }
    *(u64 *)(range + 0x18) = out_size;
}

// 0x71001e1830 — build and dispatch error result with code 0x800300d2
void FUN_71001e1830(u64 context, u32 tag)
{
    u32 error_code;
    u8 error_buf[24];

    error_code = 0x800300d2;
    FUN_71001b4200(error_buf, &error_code);
    FUN_71001e1770(context, tag, error_buf);
}

// 0x71001ecde0 — set connection mode field, clear flag if needed
void FUN_71001ecde0(s64 self, u32 mode)
{
    if (*(s8 *)(self + 0x68) == '\0') {
        FUN_71001f2180(self);
    }
    *(u32 *)(self + 0x10) = mode;
    *(u8 *)(self + 0x69) = 0;
}

// 0x710021a4f0 — compare two objects by timestamp then ID then flag
u8 FUN_710021a4f0(s64 a, s64 b)
{
    s64 time_a;
    s64 time_b;

    time_a = FUN_71001beb00(a);
    time_b = FUN_71001beb00(b);
    if (time_a < time_b) {
        return 1;
    }
    time_a = FUN_71001beb00(a);
    time_b = FUN_71001beb00(b);
    if ((time_a == time_b) && (*(u32 *)(a + 0x88) < *(u32 *)(b + 0x88))) {
        return 1;
    }
    time_a = FUN_71001beb00(a);
    time_b = FUN_71001beb00(b);
    if (time_a != time_b) {
        return 0;
    }
    if (*(s32 *)(a + 0x88) == *(s32 *)(b + 0x88)) {
        return *(u8 *)(a + 0x90) < *(u8 *)(b + 0x90);
    }
    return 0;
}

// 0x71002263c0 — write 8 u64 fields from array into small-addr offsets
void FUN_71002263c0(s64 self, u64 *src)
{
    u64 val0;
    u64 val1;
    u64 val2;

    val0 = *src;
    val2 = src[1];
    val1 = src[2];
    *(u64 *)(self + 0x10d8) = src[3];
    *(u64 *)(self + 0x10d0) = val1;
    *(u64 *)(self + 0x10c8) = val2;
    *(u64 *)(self + 0x10c0) = val0;
    val0 = src[4];
    val2 = src[5];
    val1 = src[6];
    *(u64 *)(self + 0x10f8) = src[7];
    *(u64 *)(self + 0x10f0) = val1;
    *(u64 *)(self + 0x10e8) = val2;
    *(u64 *)(self + 0x10e0) = val0;
}

// 0x7100227510 — pop next pending frame from queue
s64 FUN_7100227510(s64 queue)
{
    s32 count;
    s64 frame;

    if ((*(u8 *)(queue + 0x11) >> 1 & 1) == 0) {
        frame = FUN_71002282f0(0);
        FUN_71002282c0(*(u64 *)(queue + 0x88));
        return frame;
    }
    count = FUN_7100228310(*(u64 *)(queue + 0x88));
    if (count == 0) {
        do {
            frame = FUN_71002282f0(*(u64 *)(queue + 0x88));
            FUN_71002282c0(*(u64 *)(queue + 0x88));
            if (*(s8 *)(frame + 1) == '\b') {
                return frame;
            }
            if (frame != 0) {
                FUN_7100228130(*(u64 *)(frame + 8));
                FUN_7100228130(frame);
            }
            count = FUN_7100228310(*(u64 *)(queue + 0x88));
        } while (count == 0);
        return 0;
    }
    return 0;
}

// 0x7100230c10 — check condition and delegate on failure
u64 FUN_7100230c10(u64 context)
{
    u64 ready;

    ready = FUN_7100230c50();
    if ((ready & 1) != 0) {
        return 1;
    }
    FUN_7100230a20(context);
    return 0;
}

// 0x71002b41f0 — forward call to sub-object's cleanup
void FUN_71002b41f0(u64 *self)
{
    FUN_71002ba5e0(*self);
}

// 0x71002b4b30 — forward call to sub-object's teardown
void FUN_71002b4b30(u64 *self)
{
    FUN_71002c1d20(*self);
}

// 0x71002b8ca0 — stub (no-op)
void FUN_71002b8ca0(void)
{
    return;
}

// 0x710033ba50 — look up stage/world object pointer by region slot index
s64 FUN_710033ba50(u32 slot_index)
{
    s64 slot_ptr;
    s64 world;

    switch(slot_index) {
    case 0:
        world = *DAT_71052b60e8;
        slot_ptr = *(s64 *)(world + 0x728);
        goto joined_r0x00710033baa8;
    case 1:
        world = *DAT_71052b60e8;
        slot_ptr = *(s64 *)(world + 0x778);
joined_r0x00710033baa8:
        if (slot_ptr != 0) {
            return slot_ptr;
        }
        goto LAB_710033baac;
    case 2:
        world = *DAT_71052b60e8;
        slot_ptr = *(s64 *)(world + 0x7c8);
        break;
    case 3:
        world = *DAT_71052b60e8;
        slot_ptr = *(s64 *)(world + 0x818);
        break;
    case 4:
        world = *DAT_71052b60e8;
        slot_ptr = *(s64 *)(world + 0x868);
        break;
    case 5:
        world = *DAT_71052b60e8;
        slot_ptr = *(s64 *)(world + 0x8b8);
        break;
    case 6:
        world = *DAT_71052b60e8;
        slot_ptr = *(s64 *)(world + 0x908);
        break;
    case 7:
        world = *DAT_71052b60e8;
        slot_ptr = *(s64 *)(world + 0x958);
        break;
    case 8:
        world = *DAT_71052b60e8;
        slot_ptr = *(s64 *)(world + 0x9a8);
        break;
    case 9:
        world = *DAT_71052b60e8;
        slot_ptr = *(s64 *)(world + 0x9f8);
        break;
    case 10:
        world = *DAT_71052b60e8;
        slot_ptr = *(s64 *)(world + 0xa48);
        break;
    case 0xb:
        world = *DAT_71052b60e8;
        slot_ptr = *(s64 *)(world + 0xa98);
        break;
    case 0xc:
        world = *DAT_71052b60e8;
        slot_ptr = *(s64 *)(world + 0xae8);
        break;
    case 0xd:
        world = *DAT_71052b60e8;
        slot_ptr = *(s64 *)(world + 0xb38);
        break;
    case 0xe:
        world = *DAT_71052b60e8;
        slot_ptr = *(s64 *)(world + 0xb88);
        break;
    case 0xf:
        world = *DAT_71052b60e8;
        slot_ptr = *(s64 *)(world + 0xbd8);
        break;
    case 0x10:
        world = *DAT_71052b60e8;
        slot_ptr = *(s64 *)(world + 0xc28);
        break;
    case 0x11:
        world = *DAT_71052b60e8;
        slot_ptr = *(s64 *)(world + 0xc78);
        break;
    case 0x12:
        world = *DAT_71052b60e8;
        slot_ptr = *(s64 *)(world + 0xcc8);
        break;
    case 0x13:
        world = *DAT_71052b60e8;
        slot_ptr = *(s64 *)(world + 0xd18);
        break;
    case 0x14:
        world = *DAT_71052b60e8;
        slot_ptr = *(s64 *)(world + 0xd68);
        break;
    case 0x15:
        world = *DAT_71052b60e8;
        slot_ptr = *(s64 *)(world + 0xdb8);
        break;
    case 0x16:
        world = *DAT_71052b60e8;
        slot_ptr = *(s64 *)(world + 0xe08);
        break;
    case 0x17:
        world = *DAT_71052b60e8;
        slot_ptr = *(s64 *)(world + 0xe58);
        break;
    case 0x18:
        world = *DAT_71052b60e8;
        slot_ptr = *(s64 *)(world + 0xea8);
        break;
    case 0x19:
        world = *DAT_71052b60e8;
        slot_ptr = *(s64 *)(world + 0xef8);
        break;
    case 0x1a:
        world = *DAT_71052b60e8;
        slot_ptr = *(s64 *)(world + 0xf48);
        break;
    case 0x1b:
        world = *DAT_71052b60e8;
        slot_ptr = *(s64 *)(world + 0xf98);
        break;
    case 0x1c:
        world = *DAT_71052b60e8;
        slot_ptr = *(s64 *)(world + 0xfe8);
        break;
    case 0x1d:
        world = *DAT_71052b60e8;
        slot_ptr = *(s64 *)(world + 0x1038);
        break;
    case 0x1e:
        world = *DAT_71052b60e8;
        slot_ptr = *(s64 *)(world + 0x1088);
        break;
    case 0x1f:
        world = *DAT_71052b60e8;
        slot_ptr = *(s64 *)(world + 0x10d8);
        break;
    case 0x20:
        world = *DAT_71052b60e8;
        slot_ptr = *(s64 *)(world + 0x1128);
        break;
    case 0x21:
        world = *DAT_71052b60e8;
        slot_ptr = *(s64 *)(world + 0x1178);
        break;
    case 0x22:
        world = *DAT_71052b60e8;
        slot_ptr = *(s64 *)(world + 0x11c8);
        break;
    case 0x23:
        world = *DAT_71052b60e8;
        slot_ptr = *(s64 *)(world + 0x1218);
        break;
    case 0x24:
        world = *DAT_71052b60e8;
        slot_ptr = *(s64 *)(world + 0x1268);
        break;
    case 0x25:
        world = *DAT_71052b60e8;
        slot_ptr = *(s64 *)(world + 0x12b8);
        break;
    case 0x26:
        world = *DAT_71052b60e8;
        slot_ptr = *(s64 *)(world + 0x1308);
        break;
    case 0x27:
        world = *DAT_71052b60e8;
        slot_ptr = *(s64 *)(world + 0x1358);
        break;
    case 0x28:
        world = *DAT_71052b60e8;
        slot_ptr = *(s64 *)(world + 0x13a8);
        break;
    case 0x29:
        world = *DAT_71052b60e8;
        slot_ptr = *(s64 *)(world + 0x13f8);
        break;
    case 0x2a:
        world = *DAT_71052b60e8;
        slot_ptr = *(s64 *)(world + 0x1448);
        break;
    case 0x2b:
        world = *DAT_71052b60e8;
        slot_ptr = *(s64 *)(world + 0x1498);
        break;
    case 0x2c:
        world = *DAT_71052b60e8;
        slot_ptr = *(s64 *)(world + 0x14e8);
        break;
    case 0x2d:
        world = *DAT_71052b60e8;
        slot_ptr = *(s64 *)(world + 0x1538);
        break;
    case 0x2e:
        world = *DAT_71052b60e8;
        slot_ptr = *(s64 *)(world + 0x1588);
        break;
    case 0x2f:
        world = *DAT_71052b60e8;
        slot_ptr = *(s64 *)(world + 0x15d8);
        break;
    case 0x30:
        world = *DAT_71052b60e8;
        slot_ptr = *(s64 *)(world + 0x1628);
        break;
    case 0x31:
        world = *DAT_71052b60e8;
        slot_ptr = *(s64 *)(world + 0x1678);
        break;
    case 0x32:
        world = *DAT_71052b60e8;
        slot_ptr = *(s64 *)(world + 0x16c8);
        break;
    case 0x33:
        world = *DAT_71052b60e8;
        slot_ptr = *(s64 *)(world + 0x1718);
        break;
    case 0x34:
        world = *DAT_71052b60e8;
        slot_ptr = *(s64 *)(world + 0x1768);
        break;
    case 0x35:
        world = *DAT_71052b60e8;
        slot_ptr = *(s64 *)(world + 0x17b8);
        break;
    case 0x36:
        world = *DAT_71052b60e8;
        slot_ptr = *(s64 *)(world + 0x1808);
        break;
    case 0x37:
        world = *DAT_71052b60e8;
        slot_ptr = *(s64 *)(world + 0x1858);
        break;
    case 0x38:
        world = *DAT_71052b60e8;
        slot_ptr = *(s64 *)(world + 0x18a8);
        break;
    case 0x39:
        world = *DAT_71052b60e8;
        slot_ptr = *(s64 *)(world + 0x18f8);
        break;
    case 0x3a:
        world = *DAT_71052b60e8;
        slot_ptr = *(s64 *)(world + 0x1948);
        break;
    case 0x3b:
        world = *DAT_71052b60e8;
        slot_ptr = *(s64 *)(world + 0x1998);
        break;
    case 0x3c:
        world = *DAT_71052b60e8;
        slot_ptr = *(s64 *)(world + 0x19e8);
        break;
    case 0x3d:
        world = *DAT_71052b60e8;
        slot_ptr = *(s64 *)(world + 0x1a38);
        break;
    case 0x3e:
        world = *DAT_71052b60e8;
        slot_ptr = *(s64 *)(world + 0x1a88);
        break;
    case 0x3f:
        world = *DAT_71052b60e8;
        slot_ptr = *(s64 *)(world + 0x1ad8);
        break;
    case 0x40:
        world = *DAT_71052b60e8;
        slot_ptr = *(s64 *)(world + 0x1b28);
        break;
    case 0x41:
        world = *DAT_71052b60e8;
        slot_ptr = *(s64 *)(world + 0x1b78);
        break;
    case 0x42:
        world = *DAT_71052b60e8;
        slot_ptr = *(s64 *)(world + 0x1bc8);
        break;
    case 0x43:
        world = *DAT_71052b60e8;
        slot_ptr = *(s64 *)(world + 0x1c18);
        break;
    case 0x44:
        world = *DAT_71052b60e8;
        slot_ptr = *(s64 *)(world + 0x1c68);
        break;
    case 0x45:
        world = *DAT_71052b60e8;
        slot_ptr = *(s64 *)(world + 0x1cb8);
        break;
    case 0x46:
        world = *DAT_71052b60e8;
        slot_ptr = *(s64 *)(world + 0x1d08);
        break;
    case 0x47:
        world = *DAT_71052b60e8;
        slot_ptr = *(s64 *)(world + 0x1d58);
        break;
    case 0x48:
        world = *DAT_71052b60e8;
        slot_ptr = *(s64 *)(world + 0x1da8);
        break;
    case 0x49:
        world = *DAT_71052b60e8;
        slot_ptr = *(s64 *)(world + 0x1df8);
        break;
    case 0x4a:
        world = *DAT_71052b60e8;
        slot_ptr = *(s64 *)(world + 0x1e48);
        break;
    case 0x4b:
        world = *DAT_71052b60e8;
        slot_ptr = *(s64 *)(world + 0x1e98);
        break;
    case 0x4c:
        world = *DAT_71052b60e8;
        slot_ptr = *(s64 *)(world + 0x1ee8);
        break;
    case 0x4d:
        world = *DAT_71052b60e8;
        slot_ptr = *(s64 *)(world + 0x1f38);
        break;
    case 0x4e:
        world = *DAT_71052b60e8;
        slot_ptr = *(s64 *)(world + 0x1f88);
        break;
    case 0x4f:
        world = *DAT_71052b60e8;
        slot_ptr = *(s64 *)(world + 0x1fd8);
        break;
    case 0x50:
        world = *DAT_71052b60e8;
        slot_ptr = *(s64 *)(world + 0x2028);
        break;
    case 0x51:
        world = *DAT_71052b60e8;
        slot_ptr = *(s64 *)(world + 0x2078);
        break;
    case 0x52:
        world = *DAT_71052b60e8;
        slot_ptr = *(s64 *)(world + 0x20c8);
        break;
    case 0x53:
        world = *DAT_71052b60e8;
        slot_ptr = *(s64 *)(world + 0x2118);
        break;
    case 0x54:
        world = *DAT_71052b60e8;
        slot_ptr = *(s64 *)(world + 0x2168);
        break;
    case 0x55:
        world = *DAT_71052b60e8;
        slot_ptr = *(s64 *)(world + 0x21b8);
        break;
    case 0x56:
        world = *DAT_71052b60e8;
        slot_ptr = *(s64 *)(world + 0x2208);
        break;
    case 0x57:
        world = *DAT_71052b60e8;
        slot_ptr = *(s64 *)(world + 0x2258);
        break;
    case 0x58:
        world = *DAT_71052b60e8;
        slot_ptr = *(s64 *)(world + 0x22a8);
        break;
    case 0x59:
        world = *DAT_71052b60e8;
        slot_ptr = *(s64 *)(world + 0x22f8);
        break;
    case 0x5a:
        world = *DAT_71052b60e8;
        slot_ptr = *(s64 *)(world + 0x2348);
        break;
    case 0x5b:
        world = *DAT_71052b60e8;
        slot_ptr = *(s64 *)(world + 0x2398);
        break;
    case 0x5c:
        world = *DAT_71052b60e8;
        slot_ptr = *(s64 *)(world + 0x23e8);
        break;
    case 0x5d:
        world = *DAT_71052b60e8;
        slot_ptr = *(s64 *)(world + 0x2438);
        break;
    default:
        world = *DAT_71052b60e8;
        goto LAB_710033baac;
    }
    if (slot_ptr == 0) {
LAB_710033baac:
        slot_ptr = world + 0x6e8;
    }
    return slot_ptr;
}

// 0x7100358c20 — check if move/attack is executable given state flags
u32 FUN_7100358c20(s64 state, u32 flags)
{
    u32 state_flags;
    u8 bit;
    u32 result;

    state_flags = *(u32 *)(state + 0x58);
    if ((state_flags >> 0xc & 1) != 0) {
        result = 0;
        if ((flags & 1) != 0) {
            result = (u32)((state_flags & 0x400) == 0);
        }
        return result;
    }
    result = 0;
    switch(*(u32 *)(state + 0x28)) {
    case 5:
        bit = *(u8 *)(state + 0x68);
        goto joined_r0x007100358dd4;
    case 0xc:
        goto switchD_7100358c4c_caseD_c;
    case 0x1c:
        if ((*(u8 *)(state + 0x68) & 1) != 0) {
            return 0;
        }
        break;
    case 0x22:
        if ((*(u8 *)(state + 0x68) >> 2 & 1) == 0) {
            return 0;
        }
        break;
    case 0x25:
        if ((state_flags >> 4 & 1) != 0) {
            return 0;
        }
        break;
    case 0x27:
        if ((*(u8 *)(state + 0x68) >> 2 & 1) != 0) {
            return 0;
        }
        break;
    case 0x29:
        if ((*(u8 *)(state + 0x68) & 1) != 0) {
            return 0;
        }
        break;
    case 0x2b:
    case 0x30:
    case 0x46:
        bit = *(u8 *)(state + 0x68) >> 3;
        goto joined_r0x007100358dd4;
    case 0x2d:
        bit = *(u8 *)(state + 0x68) >> 2;
        goto joined_r0x007100358dd4;
    case 0x31:
        if ((*(u8 *)(state + 0x68) >> 1 & 1) != 0) {
            return 0;
        }
        break;
    case 0x37:
        if ((*(u8 *)(state + 0x68) >> 3 & 1) != 0) {
            return 0;
        }
        break;
    case 0x38:
        if ((*(u8 *)(state + 0x68) >> 2 & 1) == 0) {
            return 0;
        }
        break;
    case 0x3a:
        if ((*(u8 *)(state + 0x68) >> 2 & 1) != 0) {
            return 0;
        }
        break;
    case 0x40:
        if ((*(u8 *)(state + 0x68) >> 1 & 1) != 0) {
            return 1;
        }
        result = 0;
        if (((state_flags >> 0xd & 1) == 0) && (*(s32 *)(state + 0x74) != 0x10)) {
            if (*(s16 *)(state + 0xcc) != 0) {
                return 1;
            }
            result = 0;
        }
        goto switchD_7100358c4c_caseD_c;
    case 0x4b:
        bit = *(u8 *)(state + 0x68) >> 1;
        goto joined_r0x007100358dd4;
    case 0x52:
        if (((state_flags >> 4 & 1) != 0) && ((*(u32 *)(state + 0x68) & 1) == 0)) {
            return 0;
        }
        break;
    case 0x53:
        result = flags;
        if (*(s8 *)(state + 0x68) < '\0') {
            return 1;
        }
        goto switchD_7100358c4c_caseD_c;
    case 0x54:
        bit = *(u8 *)(state + 0x68) >> 3;
joined_r0x007100358dd4:
        result = flags;
        if ((bit & 1) == 0) {
switchD_7100358c4c_caseD_c:
            return result & 1;
        }
        break;
    case 0x56:
        if ((state_flags >> 4 & 1) != 0) {
            return 0;
        }
        break;
    case 0x57:
        if ((state_flags >> 4 & 1) != 0) {
            return 0;
        }
        break;
    case 0x5a:
        if ((*(u8 *)(state + 0x68) >> 1 & 1) != 0) {
            if ((flags & 1) != 0) {
                return (u32)((state_flags & 0x400) == 0);
            }
            return 0;
        }
        break;
    case 0x5c:
        result = *(u32 *)(state + 0x68) >> 2 & 1;
        if ((*(u32 *)(state + 0x68) >> 2 & 1) == 0) {
            if ((flags & 1) != 0) {
                result = (u32)((state_flags & 0x400) == 0);
            }
            return result;
        }
        goto switchD_7100358c4c_caseD_c;
    }
    return 1;
}
