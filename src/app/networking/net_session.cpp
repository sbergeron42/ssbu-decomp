#include "types.h"

// HARD-tier networking session functions — 0x7100160000-0x7100168000 range
// LDN session management, transport setup, player state distribution

// ---- External globals -------------------------------------------------------

extern u64 PTR_DAT_71052a3dc8;    // Primary transport manager global
extern u64 PTR_DAT_71052a5028;    // Secondary transport global
extern u8  DAT_71052acd88;        // LDN session active flag
extern u8  DAT_71052acd89;        // LDN session cleanup needed flag
extern u64 PTR_DAT_71052a5088;    // Session vtable pointer

// ---- External functions -----------------------------------------------------

extern void FUN_71001613e0(void);
extern void FUN_7100156910(u64);
extern void FUN_7100130920(u64);
extern void FUN_71001308d0(u64);
extern void FUN_71001674b0(u8 *);
extern void FUN_71000b1ae0(int);
extern void FUN_71000bcda0(u8 *, int);
extern u64  FUN_7100161fa0(u64);
extern void FUN_71000b7080(void);
extern void FUN_71000b7080(long *);
extern void FUN_71000bce50(u64, u32 *);
extern u64  FUN_71000b2b10(long, long);
extern void FUN_7100154260(u32 *, u64, u64);
extern void FUN_71000bcf30(u32 *, u32 *);
extern void FUN_7100165480(void *, long, int *, u64);
extern void FUN_71000b1d10(void **, u32);
extern void FUN_71000b1cf0(void **);
extern u64  xorshift128_7100138620(long);
extern u64  PTR_DAT_71052a3c28;
extern u64  PTR_DAT_71052a3cf0;    // Debug/log transport global
extern "C" void* memset(void*, int, unsigned long);
extern "C" void* memcpy(void*, const void*, unsigned long);
extern u64  FUN_71000bc710(u64, int);
extern void FUN_71000bc730(u64, const char *);
extern void FUN_7100164df0(u32 *, long, const char *, u32, u32, u32, u32, int);
extern void FUN_7100163170(long, long);
extern void FUN_7100163180(long, long);
extern u64  FUN_71000bae40(long *);
extern u32  FUN_71000bae50(long *);
extern u32  FUN_710013c780(u64, u32);

extern u64  FUN_71001516f0(void);
extern u64  PTR_DAT_71052a3c80;
extern void FUN_71000b6560(u32 *, long, int);
extern void FUN_71001627a0(u32 *, u64);
extern void FUN_7100157000(u32 *, u64 *, u64, u64);
extern void FUN_71001644e0(u32 *, u64, u64, u64);
extern void FUN_71000b4820(u64, int);
extern void FUN_71001572a0(u32 *, u64 *);

namespace nn { namespace os {
    u64 GetSystemTick(void);
    u64 ConvertToTimeSpan(u64);
}}

namespace nn { namespace err {
    struct ErrorResultVariant;
    void ErrorResultVariant_ctor(ErrorResultVariant *);
    void ErrorResultVariant_assign(ErrorResultVariant *, u32 *);
}}

// =============================================================================
// FUN_7100161380 — Teardown transport managers
// Address: 0x7100161380 | Size: 96 bytes
//
// Shuts down both transport manager globals. For the primary transport,
// calls cleanup then frees the +0x10 sub-object. For the secondary,
// calls two-phase shutdown. Both pointers are nulled after cleanup.
// =============================================================================

void FUN_7100161380(void)
{
    u64 *p1 = (u64 *)&PTR_DAT_71052a3dc8;
    if (*p1 != 0) {
        FUN_71001613e0();
        FUN_7100156910(*p1 + 0x10);
        *p1 = 0;
    }
    u64 *p2 = (u64 *)&PTR_DAT_71052a5028;
    u64 val = *p2;
    if (val != 0) {
        FUN_7100130920(val);
        FUN_71001308d0(val);
        *p2 = 0;
    }
}

// =============================================================================
// FUN_7100167450 — LDN session shutdown
// Address: 0x7100167450 | Size: 96 bytes
//
// If LDN session is active (DAT_71052acd88 == 1):
//   - If cleanup needed (DAT_71052acd89 == 1), run cleanup via FUN_71001674b0
//   - Signal disconnect type 7
//   - Clear active flag
//   - Finalize via FUN_71000bcda0
// =============================================================================

void FUN_7100167450(void)
{
    u8 stack_buf[16];
    if (DAT_71052acd88 == 1) {
        if (DAT_71052acd89 == 1) {
            FUN_71001674b0(stack_buf);
        }
        FUN_71000b1ae0(7);
        DAT_71052acd88 = 0;
        FUN_71000bcda0(stack_buf, 7);
    }
}

// =============================================================================
// FUN_7100166d80 — Find peer by slot ID in linked list
// Address: 0x7100166d80 | Size: 128 bytes
//
// Calls vtable[0xa0] to check if session is active.
// If active, walks the linked list at param_1[4] (sentinel = param_1+3),
// searching for a node whose data+0x38 matches param_2.
// Returns the data pointer on match, 0 otherwise.
// =============================================================================

long FUN_7100166d80(long *param_1, char param_2)
{
    u64 active = (*(u64 (**)(void))(*param_1 + 0xa0))();
    if ((active & 1) == 0) {
        return 0;
    }
    long *node = (long *)param_1[4];
    if (node != param_1 + 3) {
        do {
            if (*(char *)(node[2] + 0x38) == param_2) {
                return node[2];
            }
            node = (long *)node[1];
        } while (node != param_1 + 3);
        return 0;
    }
    return 0;
}

// =============================================================================
// FUN_71001671d0 — Build active peer bitmask
// Address: 0x71001671d0 | Size: 144 bytes
//
// Walks the linked list at param_1+0x20 (sentinel = param_1+0x18).
// For each node where data+0x38 < 0x20 and data+0x48 == 5,
// sets the corresponding bit in the result bitmask.
// If param_2 bit 0 is clear AND param_1+0x98 has a valid entry,
// clears that entry's bit from the result (exclude self).
// =============================================================================

u32 FUN_71001671d0(long param_1, u32 param_2)
{
    u8 bVar1;
    u32 mask;
    long node;

    node = *(long *)(param_1 + 0x20);
    if (node == param_1 + 0x18) {
        mask = 0;
    }
    else {
        mask = 0;
        do {
            bVar1 = *(u8 *)(*(long *)(node + 0x10) + 0x38);
            if ((bVar1 < 0x20) && (*(int *)(*(long *)(node + 0x10) + 0x48) == 5)) {
                mask = (1u << (u32)(bVar1 & 0x1f)) | mask;
            }
            node = *(long *)(node + 8);
        } while (node != param_1 + 0x18);
    }
    if (((param_2 & 1) == 0) && (*(long *)(param_1 + 0x98) != 0) &&
        (bVar1 = *(u8 *)(*(long *)(param_1 + 0x98) + 0x38), bVar1 < 0x20)) {
        return mask & ((1u << (u32)(bVar1 & 0x1f)) ^ 0xFFFFFFFFu);
    }
    return mask;
}

// =============================================================================
// FUN_71001672e0 — Distribute value to peers by bitmask
// Address: 0x71001672e0 | Size: 144 bytes
//
// For each bit set in param_2, calls vtable[0x48] on the session manager
// to get the peer object, then writes param_3's value to peer+0x88.
// Only runs if param_2 != 0 and *param_1 != 0.
// =============================================================================

void FUN_71001672e0(char *param_1, u32 param_2, u64 *param_3)
{
    long *session;
    long peer;
    u32 i;

    if ((param_2 != 0) && (*param_1 != '\0')) {
        session = (long *)FUN_7100161fa0(*(u64 *)&PTR_DAT_71052a3dc8);
        i = 0;
        do {
            if (((1u << (i & 0x1f)) & param_2) != 0) {
                peer = (*(long (**)(long *, u32))(*session + 0x48))(session, i);
                if (peer != 0) {
                    *(u64 *)(peer + 0x88) = *param_3;
                }
            }
            i = i + 1;
        } while (i != 0x20);
    }
}

// =============================================================================
// FUN_71001666d0 — Initialize session object
// Address: 0x71001666d0 | Size: 144 bytes
//
// Zeros out a session struct and sets the vtable pointer from
// PTR_DAT_71052a5088+0x10. Calls FUN_71000b7080 to initialize
// several embedded sub-objects (likely mutexes or events).
// Sets the sentinel byte at +0xa0 to 0xfd.
// =============================================================================

void FUN_71001666d0(long *param_1)
{
    u8 *vtable = (u8 *)PTR_DAT_71052a5088 + 0x10;
    param_1[1] = 0;
    param_1[2] = 0;
    *param_1 = (long)vtable;
    param_1[3] = 0;
    param_1[4] = 0;
    FUN_71000b7080();
    param_1[6] = 0;
    param_1[7] = 0;
    FUN_71000b7080();
    param_1[9] = 0;
    *(u32 *)(param_1 + 10) = 0;
    *(u32 *)((long)param_1 + 0x44) = 0;
    param_1[0xb] = 0;
    param_1[0xc] = 0;
    FUN_71000b7080();
    param_1[0xe] = 0;
    param_1[0xf] = 0;
    FUN_71000b7080(param_1 + 0xe);
    param_1[0x11] = 0;
    *(u32 *)(param_1 + 0x12) = 0;
    *(u32 *)((long)param_1 + 0x84) = 0;
    param_1[0x13] = 0;
    *(u8 *)(param_1 + 0x14) = 0xfd;
}

// =============================================================================
// FUN_7100164480 — Clear error state on session
// Address: 0x7100164480 | Size: 96 bytes
//
// Constructs a zero ErrorResultVariant on the stack, assigns a zero Result
// to it, then passes both to FUN_71000bce50 to clear the session's error.
// =============================================================================

void FUN_7100164480(u64 param_1)
{
    u32 local_38[4];
    u32 local_28[2];

    local_38[0] = 0;
    // ErrorResultVariant::ErrorResultVariant at local_38+4
    *(u64 *)((u64)local_38 | 4) = 0;
    local_28[0] = 0;
    // ErrorResultVariant::operator= from Result
    *(u32 *)((u64)local_38 | 4) = local_28[0];
    FUN_71000bce50(param_1, local_38);
}

// =============================================================================
// FUN_7100160050 — Compare two session config structs for equality
// Address: 0x7100160050 | Size: 224 bytes
//
// Compares two 0x7C-byte session config structs field by field.
// Three sub-object comparisons via FUN_71000b2b10 (at +8, +0x28, +0x48),
// then direct field comparisons for the tail (long, int, int, char, byte&0x7f,
// char, char). Returns 1 if all match, 0 otherwise.
// =============================================================================

u64 FUN_7100160050(long param_1, long param_2)
{
    u64 r;

    r = FUN_71000b2b10(param_1 + 8, param_2 + 8);
    if (((((((r & 1) != 0) &&
           (r = FUN_71000b2b10(param_1 + 0x28, param_2 + 0x28), (r & 1) != 0)) &&
          (r = FUN_71000b2b10(param_1 + 0x48, param_2 + 0x48), (r & 1) != 0)) &&
         ((*(long *)(param_1 + 0x68) == *(long *)(param_2 + 0x68) &&
          (*(int *)(param_1 + 0x70) == *(int *)(param_2 + 0x70))))) &&
        ((*(int *)(param_1 + 0x74) == *(int *)(param_2 + 0x74) &&
         ((*(char *)(param_1 + 0x78) == *(char *)(param_2 + 0x78) &&
          (((*(u8 *)(param_2 + 0x79) ^ *(u8 *)(param_1 + 0x79)) & 0x7f) == 0)))))) &&
       ((*(char *)(param_1 + 0x7a) == *(char *)(param_2 + 0x7a) &&
        (*(char *)(param_1 + 0x7b) == *(char *)(param_2 + 0x7b))))) {
        return 1;
    }
    return 0;
}

// =============================================================================
// FUN_7100160130 — Compare two session config structs for inequality
// Address: 0x7100160130 | Size: 224 bytes
//
// Same comparison as FUN_7100160050, but returns 0 on match, 1 on mismatch.
// =============================================================================

u64 FUN_7100160130(long param_1, long param_2)
{
    u64 r;

    r = FUN_71000b2b10(param_1 + 8, param_2 + 8);
    if (((((((r & 1) != 0) &&
           (r = FUN_71000b2b10(param_1 + 0x28, param_2 + 0x28), (r & 1) != 0)) &&
          (r = FUN_71000b2b10(param_1 + 0x48, param_2 + 0x48), (r & 1) != 0)) &&
         ((*(long *)(param_1 + 0x68) == *(long *)(param_2 + 0x68) &&
          (*(int *)(param_1 + 0x70) == *(int *)(param_2 + 0x70))))) &&
        ((*(int *)(param_1 + 0x74) == *(int *)(param_2 + 0x74) &&
         ((*(char *)(param_1 + 0x78) == *(char *)(param_2 + 0x78) &&
          (((*(u8 *)(param_2 + 0x79) ^ *(u8 *)(param_1 + 0x79)) & 0x7f) == 0)))))) &&
       ((*(char *)(param_1 + 0x7a) == *(char *)(param_2 + 0x7a) &&
        (*(char *)(param_1 + 0x7b) == *(char *)(param_2 + 0x7b))))) {
        return 0;
    }
    return 1;
}

// =============================================================================
// FUN_710016de30 — Get combined player count from two vtable calls
// Address: 0x710016de30 | Size: 240 bytes
//
// Calls vtable[0xb0] and vtable[0xb8] on the session object, returns sum.
// Likely: local_player_count + remote_player_count.
// =============================================================================

int FUN_710016de30(long *param_1)
{
    int count1 = (*(int (**)(void))(*param_1 + 0xb0))();
    int count2 = (*(int (**)(long *))(*param_1 + 0xb8))(param_1);
    return count2 + count1;
}

// =============================================================================
// FUN_71001686e0 — Call vtable[0x50] on each entry in a pointer array
// Address: 0x71001686e0 | Size: 304 bytes
//
// Resets a counter at param_1+8 to 0, then for each of *(short*)(param_1+10)
// entries in the pointer array at *(param_1+0x10), calls vtable[0x50].
// Likely a "reset all sub-sessions" or "flush all transport entries".
// =============================================================================

void FUN_71001686e0(long param_1)
{
    u64 i;

    *(u16 *)(param_1 + 8) = 0;
    if ((*(u64 **)(param_1 + 0x10) != (u64 *)0) && (*(s16 *)(param_1 + 10) != 0)) {
        (*(void (**)(void))(*(long *)**(u64 **)(param_1 + 0x10) + 0x50))();
        if (1 < *(u16 *)(param_1 + 10)) {
            i = 1;
            do {
                (*(void (**)(void))(*(*(long **)(*(long *)(param_1 + 0x10) + i * 8)) + 0x50))();
                i = i + 1;
            } while (i < *(u16 *)(param_1 + 10));
        }
    }
}

// =============================================================================
// FUN_71001694a0 — Update session state from packet header
// Address: 0x71001694a0 | Size: 304 bytes
//
// Calls vtable[0x50] on the sub-object at param_1+0x558, then copies
// two fields from param_2 into the sub-object:
//   +0xa6a = *(u16*)(param_2+0x12)
//   +0xa60 = (u32)*(u16*)(param_2+0x10)
// =============================================================================

void FUN_71001694a0(long param_1, long param_2)
{
    (*(void (**)(void))(*(*(long **)(param_1 + 0x558)) + 0x50))();
    long sub = *(long *)(param_1 + 0x558);
    *(u16 *)(sub + 0xa6a) = *(u16 *)(param_2 + 0x12);
    *(u32 *)(sub + 0xa60) = (u32)*(u16 *)(param_2 + 0x10);
}

// =============================================================================
// FUN_7100165540 — Check packet loss threshold
// Address: 0x7100165540 | Size: 256 bytes
//
// Returns false if session flag at +0x4c8 is clear.
// Calls FUN_7100165480 to compute error state; if error, retries with
// a default address (PTR_DAT_71052a3c28+0x10) and merges results.
// If local_14 (loss percentage?) is non-zero, generates a random number
// and returns true if (rand * 100 >> 32) < local_14 (probabilistic drop).
// =============================================================================

bool FUN_7100165540(long param_1, u64 param_2)
{
    u64 uVar1;
    void *local_60[3];
    u16 local_48;
    u8 auStack_40[16];
    u32 local_30[4];
    int local_14;

    if (*(char *)(param_1 + 0x4c8) == '\0') {
        return false;
    }
    FUN_7100165480(local_30, param_1, &local_14, param_2);
    if (local_30[0] != 0) {
        local_60[0] = (void *)(PTR_DAT_71052a3c28 + 0x10);
        FUN_71000b1d10(local_60, 0xFFFFFFFF);
        local_48 = 0;
        FUN_7100165480(auStack_40, param_1, &local_14, (u64)local_60);
        FUN_71000bcf30(local_30, (u32 *)auStack_40);
        FUN_71000b1cf0(local_60);
    }
    if (local_14 != 0) {
        uVar1 = xorshift128_7100138620(param_1 + 0x4b8);
        return (int)((uVar1 & 0xFFFFFFFF) * 100 >> 0x20) < local_14;
    }
    return false;
}

// =============================================================================
// FUN_71001629b0 — Initialize send thread stream
// Address: 0x71001629b0 | Size: 336 bytes
//
// Sets up a send thread stream buffer. Checks if +0x4d0 is already set
// (returns error 0x10c02 if so). Validates param_3 (buffer pointer),
// optionally logs via debug transport, then initializes the stream.
// On success, stores the buffer pointer and zeros out counters.
// =============================================================================

void FUN_71001629b0(u64 param_1, long param_2, long param_3, u32 param_4,
                    u32 param_5, u32 param_6, u32 param_7)
{
    u32 *result;
    u32 local_70[4];
    u32 local_60[4];
    u32 local_48[2];

    result = local_70;
    if (*(long *)(param_2 + 0x4d0) == 0) {
        if (param_3 == 0) {
            local_60[0] = 0x10c07;
            goto LAB_error;
        }
        if (*(long *)&PTR_DAT_71052a3cf0 != 0) {
            u64 log = FUN_71000bc710(*(long *)&PTR_DAT_71052a3cf0, 0);
            FUN_71000bc730(log, "SendThreadStream buffer num");
        }
        FUN_7100164df0(local_60, param_2, "Pia SendThreadStream",
                       param_5, param_4, param_6, param_7 & 1, 0);
        if (local_60[0] == 0) {
            if (*(long *)(param_2 + 0xb8) != 0) {
                FUN_7100163170(*(long *)(param_2 + 0xb8), param_3);
            }
            *(long *)(param_2 + 0x4d0) = param_3;
            *(u32 *)(param_2 + 0x4d8) = 0;
            *(u64 *)(param_2 + 0x4e0) = 0;
            local_70[0] = 0;
            *(u64 *)((u64)local_70 | 4) = 0;
            local_48[0] = 0;
            *(u32 *)((u64)local_70 | 4) = local_48[0];
            goto LAB_done;
        }
    }
    else {
        local_60[0] = 0x10c02;
    LAB_error:
        *(u64 *)((u64)local_60 | 4) = 0;
        local_70[0] = 0;
        *(u32 *)((u64)local_60 | 4) = local_70[0];
    }
    result = local_60;
LAB_done:
    FUN_71000bce50(param_1, result);
}

// =============================================================================
// FUN_71001639c0 — Initialize receive thread stream
// Address: 0x71001639c0 | Size: 336 bytes
//
// Identical to FUN_71001629b0 except:
//   - Log message is "ReceiveThreadStream buffer num"
//   - Debug log arg is 1 (not 0)
//   - Calls FUN_7100163180 instead of FUN_7100163170
//   - FUN_7100164df0 last arg is 1 (receive mode)
// =============================================================================

void FUN_71001639c0(u64 param_1, long param_2, long param_3, u32 param_4,
                    u32 param_5, u32 param_6, u32 param_7)
{
    u32 *result;
    u32 local_70[4];
    u32 local_60[4];
    u32 local_48[2];

    result = local_70;
    if (*(long *)(param_2 + 0x4d0) == 0) {
        if (param_3 == 0) {
            local_60[0] = 0x10c07;
            goto LAB_error;
        }
        if (*(long *)&PTR_DAT_71052a3cf0 != 0) {
            u64 log = FUN_71000bc710(*(long *)&PTR_DAT_71052a3cf0, 1);
            FUN_71000bc730(log, "ReceiveThreadStream buffer num");
        }
        FUN_7100164df0(local_60, param_2, "Pia ReceiveThreadStream",
                       param_5, param_4, param_6, param_7 & 1, 1);
        if (local_60[0] == 0) {
            if (*(long *)(param_2 + 0xb8) != 0) {
                FUN_7100163180(*(long *)(param_2 + 0xb8), param_3);
            }
            *(long *)(param_2 + 0x4d0) = param_3;
            *(u32 *)(param_2 + 0x4d8) = 0;
            *(u64 *)(param_2 + 0x4e0) = 0;
            local_70[0] = 0;
            *(u64 *)((u64)local_70 | 4) = 0;
            local_48[0] = 0;
            *(u32 *)((u64)local_70 | 4) = local_48[0];
            goto LAB_done;
        }
    }
    else {
        local_60[0] = 0x10c02;
    LAB_error:
        *(u64 *)((u64)local_60 | 4) = 0;
        local_70[0] = 0;
        *(u32 *)((u64)local_60 | 4) = local_70[0];
    }
    result = local_60;
LAB_done:
    FUN_71000bce50(param_1, result);
}

// =============================================================================
// FUN_710016d3b0 — Get current time in milliseconds
// Address: 0x710016d3b0 | Size: 416 bytes
//
// Gets system tick, converts to timespan (nanoseconds), then divides by
// 1,000,000,000 using compiler-optimized 128-bit multiplication
// (magic constant 0x20c49ba5e353f7cf, shift 7).
// Returns time in seconds as int.
// =============================================================================

int FUN_710016d3b0(void)
{
    u64 tick = nn::os::GetSystemTick();
    u64 ns = nn::os::ConvertToTimeSpan(tick);
    u64 hi = ((s64)ns >> 0x20) * (u64)0xe353f7cf + ((ns & 0xffffffff) * (u64)0xe353f7cf >> 0x20);
    return (int)(((s64)ns >> 0x20) * (u64)0x20c49ba5 + ((s64)hi >> 0x20) +
                 ((ns & 0xffffffff) * (u64)0x20c49ba5 + (hi & 0xffffffff) >> 0x20) >> 7) -
           (int)((s64)ns >> 0x3f);
}

// =============================================================================
// FUN_710016d550 — Build and copy session info packet
// Address: 0x710016d550 | Size: 688 bytes
//
// Constructs a 0x18-byte packet header on the stack from session fields,
// then memcpy's it to the output buffer. Reads fields from the session
// object at various offsets and calls helper functions for sub-fields.
// =============================================================================

void FUN_710016d550(long *param_1, void *param_2)
{
    u8 uVar1;
    u32 uVar2;
    u64 uVar3;
    u64 local_48;
    u16 local_40;
    u8 auStack_3e[2];
    u32 local_3c;
    u8 auStack_38[8];

    local_48 = 0;
    local_40 = 6;
    local_3c = 0;
    memset(auStack_3e, 0, 2);
    memset(auStack_38, 0, 8);
    local_48 = ((local_48 >> 32) << 32) | (u32)(int)param_1[0x6f];
    local_3c = (u32)param_1[0x99];
    uVar1 = (*(u8 (**)(long *))(*param_1 + 0xb0))(param_1);
    local_40 = (u16)((u16)uVar1 << 8) | (local_40 & 0xFF);
    uVar3 = FUN_71000bae40(param_1 + 0x70);
    uVar2 = FUN_71000bae50(param_1 + 0x70);
    uVar2 = FUN_710013c780(uVar3, uVar2);
    local_48 = ((u64)uVar2 << 32) | (local_48 & 0xFFFFFFFF);
    memcpy(param_2, &local_48, 0x18);
}

// =============================================================================
// FUN_71001657b0 — Cleanup transport sub-objects
// Address: 0x71001657b0 | Size: 1248 bytes
//
// Calls vtable[0x48] on the session, then tears down two sub-objects
// at param_1[9] and param_1[10] via FUN_7100130920/FUN_71001308d0.
// NOTE: Ghidra decompilation may be incomplete for 1248-byte function.
// =============================================================================

void FUN_71001657b0(long *param_1)
{
    long lVar1;

    (*(void (**)(void))(*param_1 + 0x48))();
    if (param_1[10] != 0) {
        FUN_71001308d0((u64)param_1[10]);
        param_1[10] = 0;
    }
    lVar1 = param_1[9];
    if (lVar1 != 0) {
        FUN_7100130920((u64)lVar1);
        FUN_71001308d0((u64)lVar1);
        param_1[9] = 0;
    }
}

// =============================================================================
// FUN_710016e380 — Validate session parameters
// Address: 0x710016e380 | Size: 960 bytes
//
// Validates multiple fields of a session config struct at param_2:
//   +0xC2: must be < 9 (max players?)
//   +0x104: must be in range [0x10, 0x40] (packet size?)
//   +0x28C: must be < 0x31 and match a bitmask (transport mode?)
//   +0x288: must be < 0x169 (timeout?)
//   +0x70: checked via FUN_710017f1b0 OR +0xB8 must be non-null
// Sets error 0x10c07 on validation failure, 0 on success.
// =============================================================================

extern u64 FUN_710017f1b0(u64);

// =============================================================================
// FUN_71001615b0 — Initialize transport layer
// Address: 0x71001615b0 | Size: 576 bytes
//
// Multi-step transport initialization with ErrorResultVariant error chaining.
// Checks if transport is already initialized (returns 0x10c08 if so).
// Then: adjusts buffer size, sets up send/receive streams via vtable calls,
// initializes sub-objects, and marks transport as active.
// =============================================================================

void FUN_71001615b0(u64 param_1, u64 *param_2, int param_3, u64 param_4)
{
    u64 uVar1;
    u32 *result;
    u32 local_70[4];
    u32 local_60[4];
    u32 local_50[4];
    u32 local_38[2];

    result = local_70;
    uVar1 = FUN_71001516f0();
    if (((uVar1 & 1) == 0) && (*(char *)((long)param_2 + 0x72) == '\0')) {
        local_50[0] = 0;
        *(u64 *)((u64)local_50 | 4) = 0;
        local_60[0] = 0;
        *(u32 *)((u64)local_50 | 4) = local_60[0];
        FUN_71000b6560(local_60, *(long *)&PTR_DAT_71052a3c80,
                       param_3 - *(int *)(*(long *)&PTR_DAT_71052a3c80 + 0xc));
        FUN_71000bcf30(local_50, local_60);
        if (local_50[0] == 0) {
            FUN_71001627a0(local_60, param_2[0x15]);
            FUN_71000bcf30(local_50, local_60);
            (*(void (**)(u32 *, long *, u64, long, u64))(*(long *)(long)param_2[0xc] + 0x78))
                (local_60, (long *)param_2[0xc], param_4,
                 *(long *)(param_2[0x15] + 0x20) + 8,
                 *(u64 *)(param_2[0x15] + 0x10));
            FUN_71000bcf30(local_50, local_60);
            (*(void (**)(u32 *, long *, u64, long, u64, u64))(*(long *)(long)param_2[0xd] + 0x78))
                (local_60, (long *)param_2[0xd], param_4,
                 *(long *)(param_2[0x15] + 0x18) + 8,
                 *(u64 *)(param_2[0x15] + 8), param_2[0xc]);
            FUN_71000bcf30(local_50, local_60);
            FUN_7100157000(local_60, param_2 + 2, param_2[0xc], param_2[0xd]);
            FUN_71000bcf30(local_50, local_60);
            if (param_2[0x14] != 0) {
                FUN_71001644e0(local_60, param_2[0x14], param_2[0xc], param_2[0xd]);
                FUN_71000bcf30(local_50, local_60);
            }
            FUN_71000b4820(param_2[0x11], 0);
            *(u32 *)((long)param_2 + 0xc4) = 0;
            param_2[0x17] = *param_2;
            *(u16 *)((long)param_2 + 0x72) = 1;
            local_60[0] = 0;
            *(u64 *)((u64)local_60 | 4) = 0;
            local_70[0] = 0;
            *(u32 *)((u64)local_60 | 4) = local_70[0];
            FUN_71000bcf30((u32 *)((long)param_2 + 0x74), local_60);
            FUN_71001572a0(local_60, param_2 + 2);
            if (local_60[0] == 0) {
                local_70[0] = 0;
                *(u64 *)((u64)local_70 | 4) = 0;
                local_38[0] = 0;
                *(u32 *)((u64)local_70 | 4) = local_38[0];
            }
            else {
                result = local_60;
            }
            goto LAB_done;
        }
    }
    else {
        local_50[0] = 0x10c08;
        *(u64 *)((u64)local_50 | 4) = 0;
        local_60[0] = 0;
        *(u32 *)((u64)local_50 | 4) = local_60[0];
    }
    result = local_50;
LAB_done:
    FUN_71000bce50(param_1, result);
}

void FUN_710016e380(u64 param_1, long param_2)
{
    u64 uVar1;
    u32 local_38[4];
    u32 local_28[2];

    if ((((*(u16 *)(param_2 + 0xc2) < 9) && (*(u8 *)(param_2 + 0x104) - 0x10 < 0x31)) &&
        (*(u16 *)(param_2 + 0x28c) < 0x31)) &&
       ((((1L << ((u64)*(u16 *)(param_2 + 0x28c) & 0x3f) & 0x1111000000843ULL) != 0 &&
         (*(u32 *)(param_2 + 0x288) < 0x169)) &&
        ((uVar1 = FUN_710017f1b0(*(u64 *)(param_2 + 0x70)), (uVar1 & 1) != 0 ||
         (*(long *)(param_2 + 0xb8) != 0)))))) {
        local_38[0] = 0;
    }
    else {
        local_38[0] = 0x10c07;
    }
    *(u64 *)((u64)local_38 | 4) = 0;
    local_28[0] = 0;
    *(u32 *)((u64)local_38 | 4) = local_28[0];
    FUN_71000bce50(param_1, local_38);
}
