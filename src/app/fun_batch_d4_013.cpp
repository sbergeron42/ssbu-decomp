#include "types.h"

// MEDIUM-tier FUN_* functions — mixed 0x7100 ranges, batch d4-013
// Includes: binary search, date/time calcs, init helpers, comparison, vtable calls
// Key derivations: FUN_7100358c20 from is_sp_u_available (.dynsym), FUN_710033ba50 from stage manager

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
// self [unknown: container with two sub-objects]
//   +0x08 [unknown: sub-object A pointer, passed to FUN_7100039590 (size query)]
//   +0x20 [unknown: sub-object B pointer, passed to FUN_71000399e0 (size query)]
s64 FUN_710003a790(s64 self)
{
    s64 size_a;
    s64 size_b;

    size_a = FUN_7100039590(*(u64 *)(self + 8));
    size_b = FUN_71000399e0(*(u64 *)(self + 0x20));
    return size_b + size_a;
}

// 0x71000cf1d0 — set entry flag and store callback result
// self [unknown: large struct, likely a resource/asset object]
//   +0x1850 [unknown: initialized flag (u8), set to 1]
//   +0x1858 [unknown: stored result from FUN_71000bb5d0 callback]
void FUN_71000cf1d0(s64 self)
{
    u64 callback_result;

    *(u8 *)(self + 0x1850) = 1;
    callback_result = 0;
    FUN_71000bb5d0(&callback_result);
    *(u64 *)(self + 0x1858) = callback_result;
}

// 0x71000f4d30 — init vtable pointer from global (PTR_DAT_71052a4220 + 0x10)
// [inferred: constructor — sets vtable after calling static init FUN_7100187f50]
void FUN_71000f4d30(s64 *self)
{
    FUN_7100187f50();
    *self = (s64)(PTR_DAT_71052a4220 + 0x10);
}

// 0x710007bdc0 — binary search: find glyph ID in font cmap table
// font [unknown: font resource struct]
//   +0x18 [unknown: cmap data base pointer — node offsets are relative to this]
//   +0x20 [unknown: cmap index pointer]
//     +0x14 [unknown: root node offset (u32) — 0 = empty table]
//   +0x80 [unknown: exclusion count (s32) — number of excluded codepoint ranges]
//   +0x84 [unknown: start of exclusion range array (u32 pairs, start at +0x84, end at +0xC4)]
// node struct (at cmap_data + offset):
//   +0x00 [unknown: range_start (u32)]
//   +0x04 [unknown: range_end (u32)]
//   +0x08 [unknown: format (s16) — 0=linear, 1=direct, 2=binary search]
//   +0x0C [unknown: child/next node offset (u32)]
//   +0x10 [unknown: glyph data start (format 1: u16 array, format 2: u32+u16 pairs)]
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
// Returns null if aligned size <= 0x128
// self [unknown: stream buffer/socket struct — large, at least 0x108 bytes + variable tail]
//   +0x00 [unknown: vtable — set to PTR_DAT_71052a4bd8 + 0x10]
//   +0xD4 [unknown: state field (u32), cleared to 0]
//   +0xD8..+0x107 [unknown: linked list nodes at +0xD8, +0xE0, +0xF0, +0x100]
//   +0xEC [unknown: read offset (u32), cleared to 0]
//   +0x104 [unknown: write offset (u32), cleared to 0]
//   +0x88 [unknown: mode field (s32) — mode==1 uses internal buffer at +0x108]
//   +0x30 [unknown: data pointer for mode!=1]
//   +0x38 [unknown: capacity — set to size-0x128]
//   self+0x90..+0xD0 [unknown: lock at +0x90 — used if flags&1 set]
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

// 0x7100179500 — create RPC session object (size 0x118)
// [inferred: nn::nifm or nn::ldn RPC session — alloc via FUN_71000b1b90 + FUN_7100130810, then init]
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

// 0x7100179b30 — create RPC session object (size 0xB8)
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

// 0x7100194390 — create RPC session object (size 0xF0)
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

// 0x7100194790 — create RPC session object (size 0x1130)
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
// transport [unknown: network transport descriptor, ~0x50 bytes]
//   +0x00 [unknown: field 0 (u64)]
//   +0x08 [unknown: field 1 (u64)]
//   +0x18 [unknown: callback/handle — initialized via FUN_71000bb5d0, then cleared]
//   +0x20 [unknown: field 4 (u64)]
//   +0x30 [unknown: field 6 (u64)]
//   +0x38 [unknown: field 7a (u32)]
//   +0x2C [unknown: field 5b (u32)]
//   +0x40 [unknown: field 8 (u64)]
//   +0x48 [unknown: field 9 (u32)]
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
// [inferred: nn::time packed format — single u64 encodes year/month/day/hour/min/sec]
// Bit layout of *packed_time:
//   [5:0]   seconds
//   [11:6]  minutes
//   [16:12] hours
//   [21:17] day
//   [25:22] month (1-12)
//   [39:26] year (14-bit, offset by 2001 or 2000 depending on month)
// Returns 0 if value matches sentinel at **PTR_DAT_71052a3f30
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
// config [unknown: time configuration struct]
//   +0x00 [unknown: flags word — bits [22:16] checked for 0x720000 (region/timezone selector)]
// Returns seconds offset: 0x15FDE20 (23,060,000s ~267 days) or 0x1600530 if region match
// [inferred: calendar system epoch adjustment for different game regions]
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
// self [unknown: network connection controller]
//   +0xB0 [unknown: triple-deref to vtable — *(*(*(self+0xB0)+0x10))+0x48 calls is_ready check]
//   +0xC0 [unknown: connection_phase (s32) — 0=idle, 1..6=active phases]
// Event mapping: 0→return 1, 4→phase 1, 5→phase 2, 6→phase 3, 7→phase 4, 8→phase 5, 9→phase 6
// Guard: phase must be 0 (idle) AND is_ready must return false before setting new phase
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
// range [unknown: buffer descriptor struct]
//   +0x10 [unknown: base data pointer]
//   +0x18 [unknown: output size field — written with decompressed size on success]
//   +0x20 [unknown: total data length]
//   +0x28 [unknown: consumed offset — subtracted from length, added to base for remaining data]
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

// 0x71001e1830 — build and dispatch error result with code 0x800300D2
// [inferred: nn::Result error 0x800300D2 — fixed error code for a specific network failure condition]
void FUN_71001e1830(u64 context, u32 tag)
{
    u32 error_code;
    u8 error_buf[24];

    error_code = 0x800300d2;
    FUN_71001b4200(error_buf, &error_code);
    FUN_71001e1770(context, tag, error_buf);
}

// 0x71001ecde0 — set connection mode field, clear flag if needed
// self [unknown: connection/session object]
//   +0x10 [unknown: mode field (u32) — set from param]
//   +0x68 [unknown: initialized flag (s8) — if 0, calls FUN_71001f2180 to init first]
//   +0x69 [unknown: pending flag (u8) — cleared after mode change]
void FUN_71001ecde0(s64 self, u32 mode)
{
    if (*(s8 *)(self + 0x68) == '\0') {
        FUN_71001f2180(self);
    }
    *(u32 *)(self + 0x10) = mode;
    *(u8 *)(self + 0x69) = 0;
}

// 0x710021a4f0 — compare two objects by timestamp then ID then flag
// a, b [unknown: timestamped message/event objects]
//   FUN_71001beb00(obj) [inferred: returns timestamp for ordering]
//   +0x88 [unknown: sequence_id (u32) — secondary sort key after timestamp]
//   +0x90 [unknown: priority (u8) — tertiary sort key when timestamp and id match]
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

// 0x71002263c0 — write 8 u64 fields from array into self
// self [unknown: network frame/buffer struct]
//   +0x10C0..+0x10F8 [unknown: 8 u64 fields (128 bytes), bulk-written from src array]
//   [inferred: likely a replay/rollback frame snapshot — writes exactly 8 u64 values]
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
// queue [unknown: frame queue struct]
//   +0x11 [unknown: flags byte — bit 1 selects between two dequeue paths]
//   +0x88 [unknown: queue handle/context — passed to FUN_7100228xxx family]
// Path A (bit 1 clear): pop immediately via FUN_71002282f0(0), consume via FUN_71002282c0
// Path B (bit 1 set): poll until count==0, skip non-type-8 frames (freeing them)
//   frame+0x01 [unknown: type byte — 0x08 means valid frame]
//   frame+0x08 [unknown: sub-resource pointer — freed via FUN_7100228130 on skip]
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
// [inferred: readiness gate — returns 1 if ready, else delegates to FUN_7100230a20 and returns 0]
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

// 0x71002b41f0 — forward cleanup to sub-object at *self
// self+0x00 → sub-object pointer [unknown: forwarded to FUN_71002ba5e0]
void FUN_71002b41f0(u64 *self)
{
    FUN_71002ba5e0(*self);
}

// 0x71002b4b30 — forward teardown to sub-object at *self
// self+0x00 → sub-object pointer [unknown: forwarded to FUN_71002c1d20]
void FUN_71002b4b30(u64 *self)
{
    FUN_71002c1d20(*self);
}

// 0x71002b8ca0 — stub (no-op, likely a vtable placeholder)
void FUN_71002b8ca0(void)
{
    return;
}

// 0x710033ba50 — look up stage/world object pointer by region slot index
// DAT_71052b60e8 [unknown: global stage/world manager pointer — deref gives world data]
// World data struct [unknown: contains 94 region slot pointers]
//   +0x728 [unknown: slot 0 base offset]
//   stride 0x50 per slot (0x728, 0x778, 0x7C8, ... up to slot 0x5D)
//   +0x6E8 [unknown: fallback/default region — returned when slot is null or index out of range]
// [inferred: stage region lookup — 94 slots (0..0x5D) maps to same count as FUN_710068d530's table]
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

// 0x7100358c20 — check if special move is executable given current action state
// [derived: called from is_sp_u_available (.dynsym) and is_sp_u_weaken_available (.dynsym)]
// state = *(void**)(BattleObject + 0x168) [derived: is_sp_u_available decompilation]
// state struct [unknown: action/move state — contains current action, flags, and sub-state bits]
//   +0x28 [unknown: current_action (u32) — switch dispatch key, 30+ recognized actions]
//   +0x58 [unknown: state_flags (u32)]
//     bit 4:  [unknown: blocks actions 0x25, 0x52, 0x56, 0x57]
//     bit 10: [unknown: attack_locked — checked when flags&1 for availability]
//     bit 12: [unknown: override mode — when set, early return with attack_locked check]
//     bit 13: [unknown: blocks action 0x40's normal path]
//   +0x68 [unknown: sub_state_bits (u8) — per-action enable/disable bits]
//     bit 0: actions 0x1C, 0x29 (blocks if set)
//     bit 1: actions 0x31, 0x4B (blocks if set), 0x40 (enables if set), 0x5A (blocks if set)
//     bit 2: actions 0x22, 0x38 (requires set), 0x27, 0x3A (blocks if set), 0x2D, 0x5C
//     bit 3: actions 0x2B, 0x30, 0x46, 0x54 (allows if clear), 0x37 (blocks if set)
//     bit 7: action 0x53 (enables if set)
//   +0x74 [unknown: sub_action_id (s32) — checked == 0x10 in action 0x40]
//   +0xCC [unknown: override_count (s16) — checked != 0 in action 0x40]
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
