// SSBU 13.0.4 — MEDIUM-tier decompilation batch 007
// Address range: 0x7100255690 – 0x71002b3ed0
// Worker: pool-b

#include "types.h"

namespace app {
namespace lua_bind {

// Forward declarations
extern "C" {
    u64   FUN_71001b4e00(void *ctx, const char *name);
    void  FUN_71001b4200(void *out, void *in);
    void  FUN_71001b3cb0(void *a, void *b);
    void  FUN_71001b2f70(void *a, void *b);
    void  FUN_7100228650(long stream, void *out);
    void  FUN_7100255230(long stream, void *out);
    void  FUN_71001b0580(void *dst, void *src);
    void  FUN_71001dd4a0(void *buf, int len);
    u64   FUN_71001d0480(long stream, void *buf, int len);
    void  FUN_710024cc10(void *p1, long p2);
    u32   FUN_710025afd0(void *a, void *b, void *c);
    u32   FUN_710025cee0(void *a, void *b, void *c);
    u32   FUN_710026c2c0(void *a, void *b, void *c, void *d);
    u32   FUN_710026d770(void *a, void *b, void *c, void *d);
    u32   FUN_710026f290(void *a, void *b, void *c);
    u32   FUN_71002659f0();
    u32   FUN_71002aba40(void *a, void *b, void *c, void *d, void *e, void *f, u32 g);
    long  FUN_710170f2a0(void *a, void *b, void *c);
    long  FUN_710170d890(void *a, void *b, void *c);
    void  FUN_71002b7df0(void *p);
    void  FUN_71002b5920(void *p);
    void  FUN_71002b8120(void *p);
    void  FUN_71002b8140(void *p);
    void  FUN_71002b8160(void *p);
    void  FUN_71002b8450(void *p);
    void  FUN_7100031140();
    int   FUN_71002babe0();
    u64   FUN_71002babd0(u32 v);
    u64   FUN_71002babf0(u64 a, int b);
    u64   FUN_71002b64f0();
    void  FUN_71001aff70(void *dst, const char *fmt, ...);
    void  FUN_710024c6d0(void *a, void *b);
}

// FUN_7100255690 — check "MatchmakeSession" name, then delegate to FUN_710024cc10
u64 FUN_7100255690(void *param_1, long param_2) {
    u64 matched = FUN_71001b4e00(*(void **)(param_2 + 0x18), "MatchmakeSession");
    if (matched & 1) return 1;
    FUN_710024cc10(param_1, param_2);
    return 0;
}

// FUN_71002558e0 — format u32 into field at +0x28 using DAT_710427eedd format
extern char DAT_710427eedd; // "%u" format string
void FUN_71002558e0(long param_1, u32 param_2) {
    FUN_71001aff70((void *)(param_1 + 0x28), &DAT_710427eedd, param_2);
}

// FUN_7100255900 — format u32 into field at +0xa0
void FUN_7100255900(long param_1, u32 param_2) {
    FUN_71001aff70((void *)(param_1 + 0xa0), &DAT_710427eedd, param_2);
}

// FUN_7100255920 — format u16 into field at +0x50
void FUN_7100255920(long param_1, u16 param_2) {
    FUN_71001aff70((void *)(param_1 + 0x50), &DAT_710427eedd, param_2);
}

// FUN_7100255940 — format two u16 values into field at +0x50 as "%u,%u"
void FUN_7100255940(long param_1, u16 param_2, u16 param_3) {
    FUN_71001aff70((void *)(param_1 + 0x50), "%u,%u", param_2, param_3);
}

// FUN_7100255960 — format u16 into field at +0x78
void FUN_7100255960(long param_1, u16 param_2) {
    FUN_71001aff70((void *)(param_1 + 0x78), &DAT_710427eedd, param_2);
}

// FUN_7100255980 — format two u16 into field at +0x78 as "%u,%u"
void FUN_7100255980(long param_1, u16 param_2, u16 param_3) {
    FUN_71001aff70((void *)(param_1 + 0x78), "%u,%u", param_2, param_3);
}

// FUN_71002559a0 — format element at array[param_2]*0x28 into that element's slot
void FUN_71002559a0(long param_1, u64 param_2) {
    FUN_71001aff70((void *)(*(long *)(param_1 + 0x10) + (u32)param_2 * 0x28), &DAT_710427eedd);
}

// FUN_7100255af0 — format element at array[param_2]*0x28 as "%u,%u"
void FUN_7100255af0(long param_1, u64 param_2) {
    FUN_71001aff70((void *)(*(long *)(param_1 + 0x10) + (u32)param_2 * 0x28), "%u,%u");
}

// FUN_71002566a0 — second packet deserializer, similar structure to FUN_7100254d50
// Reads: version, tag, u32 at +100, FUN_7100228650, FUN_7100255230,
//        optional blob at +0xa8, two u64 via FUN_71001b0580, two u32 at +0xd0/+0xd4
void FUN_71002566a0(long param_1, long param_2) {
    FUN_710024c6d0((void *)param_1, (void *)param_2); // validate
    if (*(s8 *)(param_1 + 8)) return;

    *(u8 *)(param_2 + 0x60) = 0;

    bool fixed = *(u8 *)(param_1 + 0x69) != 0;
    u32 tag = 0;
    long base_pos = 0;
    u64 remaining;

    if (!fixed) {
        long buf  = *(long *)(param_1 + 0x10);
        long *pos = (long *)(param_1 + 0x18);
        if (*(long *)(buf + 0x18) == *pos) {
            *(u8 *)(param_1 + 8) = 1;
            *(u8 *)(param_2 + 0x60) = 0;
        } else {
            *(u8 *)(param_2 + 0x60) = *(u8 *)(*(long *)(buf + 0x10) + *(long *)(buf + 0x28) + *pos);
            *pos += 1;
        }
        if (*(s8 *)(param_1 + 8)) return;
        buf  = *(long *)(param_1 + 0x10);
        long pos2 = *(long *)(param_1 + 0x18);
        remaining = (u64)(*(long *)(buf + 0x18) - pos2);
        if (remaining < 4) goto eof;
        tag = *(u32 *)(*(long *)(buf + 0x10) + *(long *)(buf + 0x28) + pos2);
        base_pos = pos2 + 4;
        *(long *)(param_1 + 0x18) = base_pos;
        remaining = (u64)(*(long *)(buf + 0x18) - base_pos);
    } else {
        long pos2 = *(long *)(param_1 + 0x18);
        long buf  = *(long *)(param_1 + 0x10);
        remaining = (u64)(*(long *)(buf + 0x18) - pos2);
    }

    // u32 at +100
    if (remaining < 4) {
        *(u8 *)(param_1 + 8) = 1;
        *(u32 *)(param_2 + 100) = 0;
        return;
    }
    {
        long buf  = *(long *)(param_1 + 0x10);
        long pos3 = *(long *)(param_1 + 0x18);
        *(u32 *)(param_2 + 100) = *(u32 *)(*(long *)(buf + 0x10) + *(long *)(buf + 0x28) + pos3);
        *(long *)(param_1 + 0x18) = pos3 + 4;
    }

    FUN_7100228650(param_1, (void *)(param_2 + 0x68));
    if (*(s8 *)(param_1 + 8)) return;

    FUN_7100255230(param_1, (void *)(param_2 + 0x90));
    if (*(s8 *)(param_1 + 8)) return;

    // optional blob at +0xa8
    {
        *(void **)(param_2 + 0xb0) = *(void **)(param_2 + 0xa8);
        long buf  = *(long *)(param_1 + 0x10);
        long pos3 = *(long *)(param_1 + 0x18);
        if ((u64)(*(long *)(buf + 0x18) - pos3) > 3) {
            int blen = *(int *)(*(long *)(buf + 0x10) + *(long *)(buf + 0x28) + pos3);
            *(long *)(param_1 + 0x18) = pos3 + 4;
            if (blen) {
                FUN_71001dd4a0(*(void **)(param_2 + 0xa8), blen);
                u64 ok = FUN_71001d0480(param_1, *(void **)(param_2 + 0xa8), blen);
                if (!(ok & 1)) {
                    *(void **)(param_2 + 0xb0) = *(void **)(param_2 + 0xa8);
                }
            }
        }
    }
    if (*(s8 *)(param_1 + 8)) return;

    // u64 at +0xc0 via FUN_71001b0580
    {
        long buf  = *(long *)(param_1 + 0x10);
        long pos3 = *(long *)(param_1 + 0x18);
        u64 val8;
        if ((u64)(*(long *)(buf + 0x18) - pos3) < 8) {
            val8 = 0;
            *(u8 *)(param_1 + 8) = 1;
        } else {
            val8 = *(u64 *)(*(long *)(buf + 0x10) + *(long *)(buf + 0x28) + pos3);
            *(long *)(param_1 + 0x18) = pos3 + 8;
        }
        FUN_71001b0580((void *)(param_2 + 0xc0), &val8);
    }
    if (*(s8 *)(param_1 + 8)) return;

    // u64 at +0xc8
    {
        long buf  = *(long *)(param_1 + 0x10);
        long pos3 = *(long *)(param_1 + 0x18);
        u64 val8;
        if ((u64)(*(long *)(buf + 0x18) - pos3) < 8) {
            val8 = 0;
            *(u8 *)(param_1 + 8) = 1;
        } else {
            val8 = *(u64 *)(*(long *)(buf + 0x10) + *(long *)(buf + 0x28) + pos3);
            *(long *)(param_1 + 0x18) = pos3 + 8;
        }
        FUN_71001b0580((void *)(param_2 + 0xc8), &val8); // +200
    }
    if (*(s8 *)(param_1 + 8)) return;

    // u32 at +0xd0, u32 at +0xd4
    {
        long buf  = *(long *)(param_1 + 0x10);
        u64 lim   = (u64)*(long *)(buf + 0x18);
        u64 pos3  = (u64)*(long *)(param_1 + 0x18);
        if (lim - pos3 < 4) {
            *(u8 *)(param_1 + 8) = 1;
            *(u32 *)(param_2 + 0xd0) = 0;
            return;
        }
        u64 next = pos3 + 4;
        *(u32 *)(param_2 + 0xd0) = *(u32 *)(*(long *)(buf + 0x10) + *(long *)(buf + 0x28) + pos3);
        *(long *)(param_1 + 0x18) = (long)next;
        if (lim - next < 4) {
            *(u8 *)(param_1 + 8) = 1;
            *(u32 *)(param_2 + 0xd4) = 0;
            return;
        }
        *(u32 *)(param_2 + 0xd4) = *(u32 *)(*(long *)(buf + 0x10) + *(long *)(buf + 0x28) + next);
        *(long *)(param_1 + 0x18) = (long)(pos3 + 8);
    }

    // align to tag boundary in variable-length mode
    if (!fixed) {
        u64 target = (u64)base_pos + tag;
        u64 cur    = (u64)*(long *)(param_1 + 0x18);
        u64 lim    = (u64)*(long *)(*(long *)(param_1 + 0x10) + 0x18);
        if (target <= lim && cur <= target) {
            *(long *)(param_1 + 0x18) = (long)target;
        }
    }
    return;

eof:
    *(u8 *)(param_1 + 8) = 1;
}

// FUN_7100256ac0 — check "PersistentGathering", then delegate to FUN_710024cc10
u64 FUN_7100256ac0(void *param_1, long param_2) {
    u64 matched = FUN_71001b4e00(*(void **)(param_2 + 0x18), "PersistentGathering");
    if (matched & 1) return 1;
    FUN_710024cc10(param_1, param_2);
    return 0;
}

// FUN_710025afa0 — delegate to FUN_710025afd0 at param_1+0x20, u64 param, return low bit
u32 FUN_710025afa0(long param_1, void *param_2, u64 param_3) {
    u64 local = param_3;
    return FUN_710025afd0((void *)(param_1 + 0x20), param_2, &local) & 1;
}

// FUN_710025ceb0 — delegate to FUN_710025cee0 at param_1+0x20, u32 param, return low bit
u32 FUN_710025ceb0(long param_1, void *param_2, u32 param_3) {
    u32 local = param_3;
    return FUN_710025cee0((void *)(param_1 + 0x20), param_2, &local) & 1;
}

// FUN_71002611f0 — copy 3 fields: u8 at +8, u32 at +0xc, u32 at +0x10
void FUN_71002611f0(long param_1, long param_2) {
    *(u8  *)(param_1 + 0x08) = *(u8  *)(param_2 + 0x08);
    *(u32 *)(param_1 + 0x0c) = *(u32 *)(param_2 + 0x0c);
    *(u32 *)(param_1 + 0x10) = *(u32 *)(param_2 + 0x10);
}

// FUN_7100261490 — copy 3 fields + call FUN_710170f2a0 if src != dst
long FUN_7100261490(long param_1, long param_2) {
    *(u8  *)(param_1 + 0x08) = *(u8  *)(param_2 + 0x08);
    *(u32 *)(param_1 + 0x0c) = *(u32 *)(param_2 + 0x0c);
    *(u32 *)(param_1 + 0x10) = *(u32 *)(param_2 + 0x10);
    if (param_1 != param_2) {
        FUN_710170f2a0((void *)(param_1 + 0x18),
                       *(void **)(param_2 + 0x18),
                       *(void **)(param_2 + 0x20));
    }
    return param_1;
}

// FUN_7100265d20 — thin wrapper: call FUN_71002659f0, return low bit
u32 FUN_7100265d20() {
    return FUN_71002659f0() & 1;
}

// FUN_710026c5f0 — delegate to FUN_710026c2c0 at param_1+8, mask bool param, return low bit
u32 FUN_710026c5f0(long param_1, void *param_2, void *param_3, u8 param_4) {
    u8 flag[4] = { (u8)(param_4 & 1), 0, 0, 0 };
    return FUN_710026c2c0((void *)(param_1 + 8), param_2, param_3, flag) & 1;
}

// FUN_710026d730 — delegate to FUN_710026d770 at param_1+0x28, pack bool+u16, return low bit
u32 FUN_710026d730(long param_1, void *param_2, u16 param_3, u8 param_4) {
    u8  flag[4]  = { (u8)(param_4 & 1), 0, 0, 0 };
    u16 val2[2]  = { param_3, 0 };
    return FUN_710026d770((void *)(param_1 + 0x28), param_2, val2, flag) & 1;
}

// FUN_710026f260 — delegate to FUN_710026f290 at param_1+0x28, u64 param, return low bit
u32 FUN_710026f260(long param_1, void *param_2, u64 param_3) {
    u64 local = param_3;
    return FUN_710026f290((void *)(param_1 + 0x28), param_2, &local) & 1;
}

// FUN_7100282924 — call FUN_71001b2f70 with param_2+0x478
void FUN_7100282924(void *param_1, long param_2) {
    FUN_71001b2f70(param_1, (void *)(param_2 + 0x478));
}

// FUN_710028af20 — copy two bytes at +8/+9, call FUN_710170d890 if src != dst
long FUN_710028af20(long param_1, long param_2) {
    *(u8 *)(param_1 + 8) = *(u8 *)(param_2 + 8);
    *(u8 *)(param_1 + 9) = *(u8 *)(param_2 + 9);
    if (param_1 != param_2) {
        FUN_710170d890((void *)(param_1 + 0x10),
                       *(void **)(param_2 + 0x10),
                       *(void **)(param_2 + 0x18));
    }
    return param_1;
}

// FUN_710028b440 — copy u8 at +8, u16 at +10, u8 at +0xc
void FUN_710028b440(long param_1, long param_2) {
    *(u8  *)(param_1 + 0x8)  = *(u8  *)(param_2 + 0x8);
    *(u16 *)(param_1 + 0xa)  = *(u16 *)(param_2 + 0xa);
    *(u8  *)(param_1 + 0xc)  = *(u8  *)(param_2 + 0xc);
}

// FUN_710028b540 — copy u8 at +8, u64 at +0x10, u16 at +0x18
void FUN_710028b540(long param_1, long param_2) {
    *(u8  *)(param_1 + 0x8)  = *(u8  *)(param_2 + 0x8);
    *(u64 *)(param_1 + 0x10) = *(u64 *)(param_2 + 0x10);
    *(u16 *)(param_1 + 0x18) = *(u16 *)(param_2 + 0x18);
}

// FUN_71002a9850 — curl/network error code mapper (NNAS/NNID error codes → result codes)
void FUN_71002a9850(void *param_1, long param_2) {
    u32 code;
    switch (param_2) {
    case 0x24bb: case 0x24bc: code = 0x80720004; break;
    case 0x24bd:               code = 0x80720006; break;
    case 0x24be:               code = 0x80720005; break;
    case 0x24c0:               code = 0x80720007; break;
    case 0x24c1:               code = 0x8072000a; break;
    case 0x24c3:               code = 0x80720008; break;
    case 0x24c4:               code = 0x80720009; break;
    case 0x24ca:               code = 0x80720011; break;
    case 0x24cb:               code = 0x80720014; break;
    case 0x24d4:               code = 0x80720010; break;
    case 0x24ea:               code = 0x80720012; break;
    case 0x251b:               code = 0x8072000f; break;
    case 0x251c:               code = 0x8072000b; break;
    case 0x251d:               code = 0x8072000c; break;
    case 0x2527:               code = 0x8072000e; break;
    default:
        if (param_2 == 0x257f) { code = 0x8072000d; break; }
        if (param_2 == 0)      { code = 0x10001;    break; }
        code = 0x80720001; break;
    }
    FUN_71001b4200(param_1, &code);
}

// FUN_71002a9c60 — attempt network connection with atomic refcount management
// Uses exclusive-monitor atomics to safely acquire/release shared connection object
extern u8  *PTR_DAT_71052a7758;
extern u8  *PTR_LAB_71052a78d0;

u32 FUN_71002a9c60(long param_1, long param_2, void *param_3, void *param_4) {
    u32 result = 0;
    if (*(s32 *)(param_2 + 0x14) != 1 && *(long *)(param_1 + 0x10) != 0) {
        bool has_peer = *(long *)(*(long *)(param_1 + 0x10) + 0x10) != 0;
        if (has_peer) {
            void *local_ptr = PTR_DAT_71052a7758 + 0x10;
            long *conn_out  = 0;
            result = FUN_71002aba40(*(void **)(param_1 + 0x28), (void *)param_2,
                                    (void *)(param_1 + 8), param_3, param_4,
                                    &local_ptr, *(u32 *)(param_1 + 0x30));
            // release connection object via atomic decrement
            if (conn_out) {
                volatile int *rc = (volatile int *)(conn_out + 1);
                int old;
                do { old = *rc; } while (!__sync_bool_compare_and_swap(rc, old, old - 1));
                if (old - 1 == 0) {
                    int *pinner = (int *)((u8 *)conn_out + 0xc);
                    typedef void (*Fn)(long *);
                    ((Fn)(*(void ***)conn_out)[2])(conn_out);
                    int ov;
                    do { ov = *pinner; } while (!__sync_bool_compare_and_swap(pinner, ov, ov - 1));
                    if (ov - 1 == 0) {
                        ((Fn)(*(void ***)conn_out)[1])(conn_out);
                    }
                }
            }
        }
    }
    return result & 1;
}

// FUN_71002aeb40 — look up "personal" URL string by index (1-based, max 7)
extern void *PTR_s_personal_7104f60978;
u64 FUN_71002aeb40(long param_1, u32 param_2) {
    if (param_2 < 8 && param_2 - 1 < 7) {
        void **table = (void **)&PTR_s_personal_7104f60978;
        FUN_71001b3cb0((void *)(param_1 + 0x10), table[(int)(param_2 - 1)]);
        return 1;
    }
    return 0;
}

// FUN_71002aeb5c — look up "personal" URL by register-passed index (tail of FUN_71002aeb40)
u64 FUN_71002aeb5c(long param_1, int idx) {
    void **table = (void **)&PTR_s_personal_7104f60978;
    FUN_71001b3cb0((void *)(param_1 + 0x10), table[idx]);
    return 1;
}

// FUN_71002aedf0 — look up "playing_inactivity" URL string by index (1-based, max 6)
extern void *PTR_s_playing_inactivity_7104f609b0;
u64 FUN_71002aedf0(long param_1, u32 param_2) {
    if (param_2 < 7 && param_2 - 1 < 6) {
        void **table = (void **)&PTR_s_playing_inactivity_7104f609b0;
        FUN_71001b3cb0((void *)(param_1 + 0x10), table[(int)(param_2 - 1)]);
        return 1;
    }
    return 0;
}

// FUN_71002aee0c — look up "playing_inactivity" URL by register-passed index
u64 FUN_71002aee0c(long param_1, int idx) {
    void **table = (void **)&PTR_s_playing_inactivity_7104f609b0;
    FUN_71001b3cb0((void *)(param_1 + 0x10), table[idx]);
    return 1;
}

// FUN_71002b3510 — write AArch64 register-mapped constants into struct
// These look like capability/permission bitmasks packed as u64 pairs
extern u64 DAT_100000001; // external symbol
void FUN_71002b3510(u64 *param_1) {
    param_1[0] = 0x0b0100000b01ULL;
    param_1[1] = (u64)&DAT_100000001;
    param_1[2] = 0x0020000000200ULL;
    param_1[3] = 0x0000900000001ULL;
    param_1[4] = 0x001003f800000ULL;
    *(u32 *)(param_1 + 5) = 0x10000;
}

// FUN_71002b3670 — return ptr offset 0x48d8 from base if FUN_71002b64f0 succeeds
u8 *FUN_71002b3670() {
    u64 ok = FUN_71002b64f0();
    if (ok & 1) return (u8 *)0x48d8; // DAT_000048d8 literal addr
    return 0;
}

// FUN_71002b3690 — return 8 if FUN_71002b64f0 succeeds, else 0
u64 FUN_71002b3690() {
    u64 ok = FUN_71002b64f0();
    return (ok & 1) ? 8 : 0;
}

// FUN_71002b3830 — shutdown handle: call destroy + close, clear slot
void FUN_71002b3830(u64 *param_1) {
    FUN_71002b7df0((void *)*param_1);
    FUN_71002b5920((void *)*param_1);
    *param_1 = 0;
}

// FUN_71002b3860 — single-op handle release via FUN_71002b8120
void FUN_71002b3860(u64 *param_1) {
    FUN_71002b8120((void *)*param_1);
}

// FUN_71002b3880 — single-op handle release via FUN_71002b8140
void FUN_71002b3880(u64 *param_1) {
    FUN_71002b8140((void *)*param_1);
}

// FUN_71002b38a0 — single-op handle release via FUN_71002b8160
void FUN_71002b38a0(u64 *param_1) {
    FUN_71002b8160((void *)*param_1);
}

// FUN_71002b38e0 — single-op handle release via FUN_71002b8450
void FUN_71002b38e0(u64 *param_1) {
    FUN_71002b8450((void *)*param_1);
}

// FUN_71002b3940 — init struct: call FUN_7100031140, set port 0x29, flags 0x101, flag byte 1
void FUN_71002b3940(u16 *param_1) {
    FUN_7100031140();
    param_1[3] = 0x29;    // port
    *param_1   = 0x101;   // version flags
    *(u8 *)(param_1 + 1) = 1;
}

// FUN_71002b3e80 — translate value through endian-swap table or identity
u64 FUN_71002b3e80(u64 param_1) {
    int mode = FUN_71002babe0();
    if (mode == 1) return param_1 & 0xffffffff;
    u64 v = FUN_71002babd0((u32)param_1);
    return FUN_71002babf0(v, 1);
}

// FUN_71002b3ed0 — zero-init large struct: fields from +0 to +0x88 (u32 stride)
void FUN_71002b3ed0(u32 *param_1) {
    *param_1 = 0;
    param_1[0x18] = 0;
    *(u64 *)(param_1 + 0x14) = 0;
    *(u64 *)(param_1 + 0x16) = 0;
    param_1[0x22] = 3;
    *(u64 *)(param_1 + 2)    = 0;
    *(u64 *)(param_1 + 0x1e) = 0;
    *(u64 *)(param_1 + 0x20) = 0;
    *(u64 *)(param_1 + 0x1a) = 0;
    *(u64 *)(param_1 + 0x1c) = 0;
    *(u64 *)(param_1 + 0x10) = 0;
    *(u64 *)(param_1 + 0x12) = 0;
    *(u64 *)(param_1 + 0x0c) = 0;
    *(u64 *)(param_1 + 0x0e) = 0;
    *(u64 *)(param_1 + 0x08) = 0;
    *(u64 *)(param_1 + 0x0a) = 0;
    *(u64 *)(param_1 + 0x04) = 0;
    *(u64 *)(param_1 + 0x06) = 0;
}

} // namespace lua_bind
} // namespace app
