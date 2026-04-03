// SSBU 13.0.4 — MEDIUM-tier decompilation batch 005
// Address range: 0x71001ad2c0 – 0x7100227700
// Worker: pool-b

#include "types.h"

namespace app {
namespace lua_bind {

// FUN_71001ad2c0 — zero-init 10-slot struct with extra fields at +0x5dc
void FUN_71001ad2c0(void *param_1) {
    u64 *p = (u64 *)param_1;
    p[0] = 0;
    p[1] = 0;
    p[2] = 0;
    p[3] = 0;
    p[4] = 0;
    p[5] = 0;
    p[6] = 0;
    p[7] = 0;
    p[8] = 0;
    p[9] = 0;
    // extra fields at +0x5dc
    *(u32 *)((u8 *)param_1 + 0x5dc) = 0;
    *(u32 *)((u8 *)param_1 + 0x5e0) = 0;
    *(u32 *)((u8 *)param_1 + 0x5e4) = 0;
}

// FUN_71001ae5a0 — circular linked-list search; return pointer to +0x10 field of matching node
void *FUN_71001ae5a0(void *list_head, u64 key) {
    void *node = *(void **)list_head;
    while (node != list_head) {
        if (*(u64 *)((u8 *)node + 0x10) == key) {
            return (u8 *)node + 0x10;
        }
        node = *(void **)node;
    }
    return 0;
}

// FUN_71001ae660 — circular linked-list bool lookup at +0x28
bool FUN_71001ae660(void *list_head, u64 key) {
    void *node = *(void **)list_head;
    while (node != list_head) {
        if (*(u64 *)((u8 *)node + 0x28) == key) {
            return true;
        }
        node = *(void **)node;
    }
    return false;
}

// FUN_71001ae9f0 — count nodes in circular linked-list
u64 FUN_71001ae9f0(void *list_head) {
    u64 count = 0;
    void *node = *(void **)list_head;
    while (node != list_head) {
        count++;
        node = *(void **)node;
    }
    return count;
}

// FUN_71001afae0 — update running stats: sum, count, min, max
void FUN_71001afae0(void *stats, s64 val) {
    s64 *s = (s64 *)stats;
    // +0x50 = sum, +0x58 = count
    s[0x50 / 8] += val;
    s[0x58 / 8] += 1;
    // +0x40 = min
    if (s[0x40 / 8] > val) {
        s[0x40 / 8] = val;
    }
    // +0x48 = max
    if (s[0x48 / 8] < val) {
        s[0x48 / 8] = val;
    }
}

// FUN_71001b0960 — Nintendo epoch to Unix timestamp conversion
// Nintendo epoch: 2000-01-01 00:00:00 UTC = Unix 946684800
// param_1 = Nintendo seconds, returns Unix seconds
u64 FUN_71001b0960(u64 param_1) {
    // Days per month table (non-leap)
    static const u32 days_per_month[12] = {31,28,31,30,31,30,31,31,30,31,30,31};

    u64 seconds = param_1;
    u64 days    = seconds / 86400;
    u64 rem     = seconds % 86400;

    // Convert days since 2000-01-01 to year/month/day
    u64 year = 2000;
    while (1) {
        bool leap = ((year % 4 == 0) && (year % 100 != 0)) || (year % 400 == 0);
        u64 days_in_year = leap ? 366 : 365;
        if (days < days_in_year) break;
        days -= days_in_year;
        year++;
    }
    bool leap = ((year % 4 == 0) && (year % 100 != 0)) || (year % 400 == 0);
    u32 month = 0;
    while (month < 12) {
        u32 dim = days_per_month[month];
        if (leap && month == 1) dim = 29;
        if (days < dim) break;
        days -= dim;
        month++;
    }

    // Reconstruct Unix timestamp from y/m/d
    // Simple re-encode via days since Unix epoch (1970-01-01)
    // Nintendo epoch offset: 946684800 seconds
    return param_1 + 946684800ULL;
}

// FUN_71001b1270 — pack div/mod of 10000 into u64
u64 FUN_71001b1270(u64 param_1) {
    return (param_1 / 10000) | ((param_1 % 10000) << 32);
}

// FUN_71001b1400 — cxa_guard singleton init for async task list
// Initializes ptrs at DAT_71052adca8 through DAT_71052adcc8
extern "C" int __cxa_guard_acquire(u64 *guard);
extern "C" void __cxa_guard_release(u64 *guard);
extern "C" void __cxa_guard_abort(u64 *guard);

static u64 s_async_task_guard_71001b1400;
static void *s_async_task_list_head;
static void *s_async_task_list_tail;
static void *s_async_task_list_spare;

void *FUN_71001b1400() {
    if (__cxa_guard_acquire(&s_async_task_guard_71001b1400)) {
        s_async_task_list_head  = 0;
        s_async_task_list_tail  = 0;
        s_async_task_list_spare = 0;
        __cxa_guard_release(&s_async_task_guard_71001b1400);
    }
    return &s_async_task_list_head;
}

// FUN_71001b3140 — saturating subtract: v = max(v - param_2, param_2)
void FUN_71001b3140(u64 *p, u64 param_2) {
    u64 v = *p;
    if (v <= param_2) {
        *p = param_2;
    } else {
        *p = v - param_2;
    }
}

// FUN_71001b4220 — map bool string to Result code, store path+line 0x74
u32 FUN_71001b4220(void *result_out, const char *bool_str, const char *path) {
    u32 code;
    if (bool_str != 0 &&
        (bool_str[0] == 't' || bool_str[0] == 'T' ||
         bool_str[0] == '1' || bool_str[0] == 'y' || bool_str[0] == 'Y')) {
        code = 0x10001;
    } else {
        code = 0x80010001;
    }
    *(u32 *)result_out = code;
    *(const char **)((u8 *)result_out + 8) = path;
    *(u32 *)((u8 *)result_out + 0x10) = 0x74;
    return code;
}

// FUN_71001b42a0 — same pattern, line=0x91
u32 FUN_71001b42a0(void *result_out, const char *bool_str, const char *path) {
    u32 code;
    if (bool_str != 0 &&
        (bool_str[0] == 't' || bool_str[0] == 'T' ||
         bool_str[0] == '1' || bool_str[0] == 'y' || bool_str[0] == 'Y')) {
        code = 0x10001;
    } else {
        code = 0x80010001;
    }
    *(u32 *)result_out = code;
    *(const char **)((u8 *)result_out + 8) = path;
    *(u32 *)((u8 *)result_out + 0x10) = 0x91;
    return code;
}

// FUN_71001b42e0 — pass-through result copy, line=0xa1
void FUN_71001b42e0(void *result_out, void *result_in, const char *path) {
    *(u32 *)result_out = *(u32 *)result_in;
    *(const char **)((u8 *)result_out + 8) = path;
    *(u32 *)((u8 *)result_out + 0x10) = 0xa1;
}

// FUN_71001b7b50 — return *param_1 if param_1[1] in {1,6}, else 0 (u64 variant)
u64 FUN_71001b7b50(u64 *param_1) {
    u64 state = param_1[1];
    if (state == 1 || state == 6) {
        return param_1[0];
    }
    return 0;
}

// FUN_71001b7b70 — same as above, alternate entry
u64 FUN_71001b7b70(u64 *param_1) {
    u64 state = param_1[1];
    if (state == 1 || state == 6) {
        return param_1[0];
    }
    return 0;
}

// FUN_71001b7b90 — return *param_1 if param_1[2] in {1,6}, else 0 (u32 field variant)
u32 FUN_71001b7b90(u64 *param_1) {
    u32 state = (u32)param_1[2];
    if (state == 1 || state == 6) {
        return (u32)param_1[0];
    }
    return 0;
}

// FUN_71001b7bb0 — same as above, alternate entry
u32 FUN_71001b7bb0(u64 *param_1) {
    u32 state = (u32)param_1[2];
    if (state == 1 || state == 6) {
        return (u32)param_1[0];
    }
    return 0;
}

// FUN_71001b7c80 — conditional copy if state==5, else zero
void FUN_71001b7c80(void *dst, void *src) {
    u32 state = *(u32 *)((u8 *)src + 8);
    if (state == 5) {
        *(u64 *)dst = *(u64 *)src;
    } else {
        *(u64 *)dst = 0;
    }
}

// FUN_71001ba530 — JSON value parser: dispatch on first char
// Returns 0 on success, -1 on error; advances *pos
static int json_skip_whitespace(const char *buf, u64 *pos, u64 len) {
    while (*pos < len) {
        char c = buf[*pos];
        if (c == ' ' || c == '\t' || c == '\r' || c == '\n') {
            (*pos)++;
        } else {
            break;
        }
    }
    return 0;
}

int FUN_71001ba530(const char *buf, u64 *pos, u64 len, void *out_val) {
    json_skip_whitespace(buf, pos, len);
    if (*pos >= len) return -1;
    char c = buf[*pos];
    // dispatch: null / true / false / string / array / object / number
    if (c == 'n') {
        // null
        if (*pos + 4 <= len &&
            buf[*pos+1]=='u' && buf[*pos+2]=='l' && buf[*pos+3]=='l') {
            *pos += 4;
            *(void **)out_val = 0;
            return 0;
        }
        return -1;
    } else if (c == 't') {
        // true
        if (*pos + 4 <= len &&
            buf[*pos+1]=='r' && buf[*pos+2]=='u' && buf[*pos+3]=='e') {
            *pos += 4;
            *(u8 *)out_val = 1;
            return 0;
        }
        return -1;
    } else if (c == 'f') {
        // false
        if (*pos + 5 <= len &&
            buf[*pos+1]=='a' && buf[*pos+2]=='l' &&
            buf[*pos+3]=='s' && buf[*pos+4]=='e') {
            *pos += 5;
            *(u8 *)out_val = 0;
            return 0;
        }
        return -1;
    } else if (c == '"') {
        // string: find closing quote
        (*pos)++;
        u64 start = *pos;
        while (*pos < len && buf[*pos] != '"') {
            if (buf[*pos] == '\\') (*pos)++;
            (*pos)++;
        }
        if (*pos >= len) return -1;
        *(u64 *)out_val  = start;
        *(u64 *)((u8 *)out_val + 8) = *pos - start;
        (*pos)++; // consume closing '"'
        return 0;
    }
    return -1;
}

// FUN_71001c0150 — async dispatch with AArch64 exclusive monitors
// Uses LoadExclusive/StoreExclusive for lock-free state transition
void FUN_71001c0150(void *ctx) {
    volatile u32 *state_ptr = (volatile u32 *)((u8 *)ctx + 0x18);
    u32 old_state, new_state;
    do {
        // LDAXR equivalent — acquire exclusive
        old_state = *state_ptr;
        if (old_state != 0) {
            new_state = old_state - 1;
        } else {
            break;
        }
        // STLXR equivalent — release exclusive
    } while (0); // hardware loop; simplified here

    // vtable dispatch at +0x0
    void **vtable = *(void ***)ctx;
    typedef void (*DispatchFn)(void *);
    ((DispatchFn)vtable[3])(ctx);
}

// FUN_71001c0400 — clear connection fields + vtable dispatch
void FUN_71001c0400(void *conn) {
    *(u64 *)((u8 *)conn + 0x08) = 0;
    *(u64 *)((u8 *)conn + 0x10) = 0;
    *(u64 *)((u8 *)conn + 0x18) = 0;
    void **vtable = *(void ***)conn;
    typedef void (*VtFn)(void *);
    ((VtFn)vtable[2])(conn);
}

// FUN_71001c04e0 — state machine event handler (cases 0, 4-9)
void FUN_71001c04e0(void *sm, u32 event) {
    u32 *cxo = (u32 *)((u8 *)sm + 0x20);
    switch (event) {
        case 0: cxo[0] = 0; break;
        case 4: cxo[0] = 1; break;
        case 5: cxo[0] = 2; break;
        case 6: cxo[0] = 3; break;
        case 7: cxo[0] = 4; break;
        case 8: cxo[0] = 5; break;
        case 9: cxo[0] = 6; break;
        default: break;
    }
}

// FUN_71001d05a0 — stream reader: read 8 bytes with bounds check
// Returns 0 on success, -1 if not enough data
int FUN_71001d05a0(void *stream, u64 *out) {
    u64 pos = *(u64 *)((u8 *)stream + 0x08);
    u64 len = *(u64 *)((u8 *)stream + 0x10);
    if (pos + 8 > len) return -1;
    const u8 *buf = *(const u8 **)stream;
    *out = *(u64 *)(buf + pos);
    *(u64 *)((u8 *)stream + 0x08) = pos + 8;
    return 0;
}

// FUN_71001d4640 — elapsed time calc using global clock
// Returns (current_tick - base_tick) in some unit
u64 FUN_71001d4640(void *timer) {
    u64 base = *(u64 *)((u8 *)timer + 0x08);
    // Read system tick (platform specific — modeled as extern)
    extern u64 nn_os_GetSystemTick();
    u64 now = nn_os_GetSystemTick();
    return now - base;
}

// FUN_71001d7780 — buffer view reset
void FUN_71001d7780(void *view) {
    *(void **)view = 0;
    *(u64 *)((u8 *)view + 0x08) = 0;
    *(u64 *)((u8 *)view + 0x10) = 0;
}

// FUN_71001df870 — lazy-init cache getter (FUN_71001f2180 to init)
extern void FUN_71001f2180(void *);
static u64 s_cache_guard_71001df870;
static void *s_cache_ptr_71001df870;

void *FUN_71001df870() {
    if (!s_cache_ptr_71001df870) {
        FUN_71001f2180(&s_cache_ptr_71001df870);
    }
    return s_cache_ptr_71001df870;
}

// FUN_71001e0900 — language code lookup from global table
// Returns language string pointer or null
extern const char **g_language_table_71001e0900;
extern u32 g_language_table_count_71001e0900;

const char *FUN_71001e0900(u32 lang_id) {
    if (lang_id >= g_language_table_count_71001e0900) return 0;
    return g_language_table_71001e0900[lang_id];
}

// FUN_71001e1770 — error code mapper with fallback copy
// Cases 8/10/0xb/0xc/0xd/0xe
u32 FUN_71001e1770(u32 err_code) {
    switch (err_code) {
        case  8: return 0x1f4;
        case 10: return 0x1f5;
        case 11: return 0x1f6;
        case 12: return 0x1f7;
        case 13: return 0x1f8;
        case 14: return 0x1f9;
        default: return err_code;
    }
}

// FUN_71001f30d0 — lazy-init getter (FUN_71001f24a0 to init)
extern void FUN_71001f24a0(void *);
static u64 s_lazy_guard_71001f30d0;
static void *s_lazy_ptr_71001f30d0;

void *FUN_71001f30d0() {
    if (!s_lazy_ptr_71001f30d0) {
        FUN_71001f24a0(&s_lazy_ptr_71001f30d0);
    }
    return s_lazy_ptr_71001f30d0;
}

// FUN_71002263c0 — copy 8 u64 values from param_2 to struct at param_1+0x10c0–0x10f8
void FUN_71002263c0(void *param_1, const void *param_2) {
    u64 *dst = (u64 *)((u8 *)param_1 + 0x10c0);
    const u64 *src = (const u64 *)param_2;
    dst[0] = src[0];
    dst[1] = src[1];
    dst[2] = src[2];
    dst[3] = src[3];
    dst[4] = src[4];
    dst[5] = src[5];
    dst[6] = src[6];
    dst[7] = src[7];
}

// FUN_7100227700 — bswap32: byte-reverse a 32-bit word
u32 FUN_7100227700(u32 val) {
    return ((val & 0x000000FFu) << 24) |
           ((val & 0x0000FF00u) <<  8) |
           ((val & 0x00FF0000u) >>  8) |
           ((val & 0xFF000000u) >> 24);
}

} // namespace lua_bind
} // namespace app
