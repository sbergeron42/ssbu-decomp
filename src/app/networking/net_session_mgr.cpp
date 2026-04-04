#include "types.h"

// HARD-tier networking session manager functions — 0x710019xxxx range
// Session lifecycle, state updates, peer management

// ---- External globals -------------------------------------------------------

extern u64 PTR_DAT_71052a3dc8;    // Primary transport manager global
extern u8  PTR_DAT_71052a56e8;    // Session vtable base

// ---- External functions -----------------------------------------------------

extern void FUN_71001308d0(u64);
extern void FUN_710015e410(long *);
extern void FUN_710015e530(void);
extern u64  FUN_7100162480(u64);
extern u64  FUN_7100161fa0(u64);
extern void FUN_7100158060(long *, long);
extern void FUN_7100158070(long *, u64, int, int, u32);
extern void FUN_7100195ad0(long *, u32, u32, int, u32, u32, u32, u32);
extern void FUN_7100162150(int *, u64, u64 *, u32);
extern void FUN_7100155d20(u32 *, long, u8 *);
extern long FUN_71001559c0(long, u32 *, u64, int, int, int, int);

// =============================================================================
// FUN_710019b620 — Session destructor
// Address: 0x710019b620 | Size: 96 bytes
//
// Sets vtable pointer, destroys sub-object at [0x16] via its vtable[0]
// (virtual destructor), frees it, and calls base destructor FUN_710015e410.
// =============================================================================

void FUN_710019b620(long *param_1)
{
    u64 *sub = (u64 *)param_1[0x16];
    *param_1 = (long)(&PTR_DAT_71052a56e8 + 0x10);
    if (sub != (u64 *)0) {
        (*(void (**)(u64 *))(*sub))(sub);
        FUN_71001308d0((u64)sub);
        param_1[0x16] = 0;
    }
    FUN_710015e410(param_1);
}

// =============================================================================
// FUN_7100193120 — Set peer bit in connection mask
// Address: 0x7100193120 | Size: 96 bytes
//
// Given a peer index (param_2 < 0x20), sets the corresponding bit in
// the connection mask at param_1+200. Also propagates to a sub-object
// at param_1+0x48 if it exists (sub+0x78).
// =============================================================================

void FUN_7100193120(long param_1, u8 param_2)
{
    u32 bit;
    long sub;
    u16 i;

    if (param_2 < 0x20) {
        if (param_2 == 0) {
            bit = 1;
        }
        else {
            i = 0;
            bit = 1;
            do {
                i = i + 1;
                bit = bit << 1;
            } while (i < param_2);
        }
        *(u32 *)(param_1 + 200) = *(u32 *)(param_1 + 200) | bit;
        sub = *(long *)(param_1 + 0x48);
        if (sub != 0) {
            *(u32 *)(sub + 0x78) = *(u32 *)(sub + 0x78) | bit;
        }
    }
}

// =============================================================================
// FUN_7100190cb0 — Update session mode and notify listener
// Address: 0x7100190cb0 | Size: 96 bytes
//
// Sets the mode value at param_1+0xb0. If changed, notifies a listener
// object at param_1+0x120 via vtable[0x10] with a packed event struct.
// Event type: 0x11 for mode 1, 0x12 for other modes.
// =============================================================================

void FUN_7100190cb0(long param_1, int param_2)
{
    long *listener;
    u32 local_20;
    u8 local_1c;
    u64 local_18;

    if (*(int *)(param_1 + 0xb0) != param_2) {
        *(int *)(param_1 + 0xb0) = param_2;
        listener = *(long **)(param_1 + 0x120);
        if (listener != (long *)0) {
            if (param_2 != 1) {
                local_20 = 0x12;
            }
            else {
                local_20 = 0x11;
            }
            local_1c = 0xfd;
            local_18 = 0;
            (*(void (**)(long *, u32 *))(*listener + 0x10))(listener, &local_20);
        }
    }
}

// =============================================================================
// FUN_710019b7b0 — Teardown session transport handles
// Address: 0x710019b7b0 | Size: 112 bytes
//
// Calls FUN_710015e530, gets transport manager, then tears down two
// handles at param_1+0xa8 and param_1+0xa0 via vtable calls.
// Clears both handles and the base pointer at +0x98.
// =============================================================================

void FUN_710019b7b0(long param_1)
{
    long *mgr;

    FUN_710015e530();
    mgr = (long *)FUN_7100162480(*(u64 *)&PTR_DAT_71052a3dc8);
    if (*(long *)(param_1 + 0xa8) != 0) {
        (*(void (**)(long *))(*mgr + 400))(mgr);
        *(u64 *)(param_1 + 0xa8) = 0;
    }
    if (*(long *)(param_1 + 0xa0) != 0) {
        (*(void (**)(long *))(*mgr + 0x188))(mgr);
        *(u64 *)(param_1 + 0xa0) = 0;
    }
    *(u64 *)(param_1 + 0x98) = 0;
}

// =============================================================================
// FUN_710019ee10 — Send data to peer via transport
// Address: 0x710019ee10 | Size: 144 bytes
//
// Gets transport handle from param_1[1], calls vtable[0x18] to get local
// endpoint ID, then vtable[0x88] on the transport to send data.
// If the send returns non-zero (queued), calls FUN_7100155d20 with type=3.
// =============================================================================

void FUN_710019ee10(long *param_1, u32 param_2, u32 param_3)
{
    long *transport;
    long result;
    u32 local_40[4];
    u8 local_24[4];

    transport = (long *)param_1[1];
    local_40[0] = (*(u32 (**)(void))(*param_1 + 0x18))();
    result = (*(long (**)(long *, u32 *, u32, int, int, u32, int, int))(*transport + 0x88))
             (transport, local_40, param_2, 1, 0, param_3 & 1, 0, 1);
    if (result != 0) {
        local_24[0] = 3;
        FUN_7100155d20(local_40, (long)transport, local_24);
    }
}

// =============================================================================
// FUN_710019eea0 — Send data to peer (alternate path)
// Address: 0x710019eea0 | Size: 112 bytes
//
// Similar to FUN_710019ee10 but calls FUN_71001559c0 instead of vtable[0x88].
// No param_3 bitmask handling.
// =============================================================================

void FUN_710019eea0(long *param_1, u64 param_2)
{
    long transport;
    long result;
    u32 local_38[5];
    u8 local_24[4];

    transport = param_1[1];
    local_38[0] = (*(u32 (**)(void))(*param_1 + 0x18))();
    result = FUN_71001559c0(transport, local_38, param_2, 1, 0, 0, 0);
    if (result != 0) {
        local_24[0] = 3;
        FUN_7100155d20(local_38, transport, local_24);
    }
}

// =============================================================================
// FUN_7100190d10 — Handle peer state change
// Address: 0x7100190d10 | Size: 240 bytes
//
// If param_2 == 0 (connect): looks up transport, calls vtable[0x48](param_3).
// Then if sub-object at +0x58 exists, resolves address and dispatches via it.
// Checks +0xe3 flag to compute a "ready" bitmask.
// Notifies listener at +0x120 via vtable[0x10] with packed event.
// =============================================================================

void FUN_7100190d10(long param_1, int param_2, u32 param_3)
{
    long *session;
    long sub;
    int local_40;
    u8 local_3c;
    u64 local_38;
    u64 local_28;

    if (param_2 == 0) {
        session = (long *)FUN_7100161fa0(*(u64 *)&PTR_DAT_71052a3dc8);
        (*(void (**)(long *, u32))(*session + 0x48))(session, param_3);
        sub = *(long *)(param_1 + 0x58);
    }
    else {
        sub = *(long *)(param_1 + 0x58);
    }
    if (sub != 0) {
        FUN_7100162150(&local_40, *(u64 *)&PTR_DAT_71052a3dc8, &local_28, param_3);
        (*(void (**)(int, u64))(param_1 + 0x58))(param_2, local_28);
    }
    long *listener;
    if (*(char *)(param_1 + 0xe3) == '\0') {
        local_38 = 0;
        listener = *(long **)(param_1 + 0x120);
    }
    else {
        local_38 = (u64)(param_2 == 0 && *(char *)(param_1 + 0xc0) != '\0');
        listener = *(long **)(param_1 + 0x120);
    }
    if (listener != (long *)0) {
        local_3c = (u8)param_3;
        local_40 = param_2;
        (*(void (**)(long *, int *))(*listener + 0x10))(listener, &local_40);
    }
}

// =============================================================================
// FUN_7100196240 — Prepare data for send buffer
// Address: 0x7100196240 | Size: 288 bytes
//
// Validates the session can send (param_1[6] != 0, no pending error at [0x147]).
// Computes aligned size, checks against max capacity at param_1[2].
// Calls vtable[0xa8] to acquire the buffer, then sets up the send via
// FUN_7100158060/70 and FUN_7100195ad0.
// Returns pointer to buffer (param_1+7) or null on failure.
// =============================================================================

long * FUN_7100196240(long *param_1, u64 param_2, u32 param_3, int param_4,
                      u32 param_5, u32 param_6, u32 param_7, u32 param_8)
{
    long *buffer;
    u32 aligned_size;
    long base;
    int remaining;

    if (((param_1[6] != 0) && ((int)param_1[0x147] == 0)) &&
        (aligned_size = (u32)(param_4 + 0x1b) & 0xfffffffcu, aligned_size <= *(u32 *)(param_1 + 2))) {
        base = param_1[1];
        remaining = *(int *)((long)param_1 + 0x14);
        (*(void (**)(long *))(*param_1 + 0xa8))(param_1);
        if ((char)param_1[0x153] != (char)-3) {
            buffer = param_1 + 7;
            FUN_7100158060(buffer, base);
            FUN_7100158070(buffer, param_2, param_4, 0, param_6 & 1);
            FUN_7100195ad0(param_1, param_3, aligned_size, remaining - (int)aligned_size,
                           param_5 & 1, param_6 & 1, param_7 & 1, param_8 & 1);
            if ((int)param_1[0x147] == 0) {
                return (long *)0;
            }
            return buffer;
        }
    }
    return (long *)0;
}

// =============================================================================
// FUN_7100193590 — Assign peer to transport slot
// Address: 0x7100193590 | Size: 320 bytes
//
// Looks up the transport manager via FUN_7100161fa0, calls vtable[0x58]
// to register the peer (param_2). If registration succeeds (lVar2 != 0),
// sets the peer's state to 6 at offset +0x48. Either way, calls
// vtable[0x28] on param_2 with a timeout value (0x80000000000).
// =============================================================================

void FUN_7100193590(u64 param_1, long *param_2)
{
    long *mgr;
    long result;
    u64 local_30;
    u32 local_28;

    mgr = (long *)FUN_7100161fa0(*(u64 *)&PTR_DAT_71052a3dc8);
    result = (*(long (**)(long *, long *))(*mgr + 0x58))(mgr, param_2);
    if (result != 0) {
        local_30 = 0x80000000000ULL;
        local_28 = 0;
        (*(void (**)(long *, u64 *))(*param_2 + 0x28))(param_2, &local_30);
        *(u32 *)(result + 0x48) = 6;
        return;
    }
    local_30 = 0x80000000000ULL;
    local_28 = 0;
    (*(void (**)(long *, u64 *))(*param_2 + 0x28))(param_2, &local_30);
}
