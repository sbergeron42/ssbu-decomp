#include "types.h"

// HARD-tier FUN_* functions — 0x71000 address range, batch hard-d-001
// Pool-d worker: libcurl + nnsocket integration layer

// ---- External declarations -----------------------------------------------

extern "C" {
    // NintendoSDK socket / OS functions
    extern s32  nnsocketClose(s32 fd);
    extern s32  nnsocketResolverSetOption(void *opt);
    extern s32  nnsocketGetLastErrno(void);
    extern void nnosSleepThread(u64 ns);
    // libcurl internals
    extern void Curl_SigloFree(void *ptr);
    extern void Curl_llist_insert_next(void *list, void *after, void *elem, void *node_store);
}

// Game / internal FUN_* forward declarations
extern u64  FUN_71000065f0(u32, s64, u64, u64);
extern void FUN_71000086c0(u64, u64, u64);
extern void FUN_710000b540(s64, s32);
extern void FUN_7100027900(u64, u64, __builtin_va_list);
extern void FUN_7100004840(s64);

// ---- Functions ---------------------------------------------------------------

// 0x7100005ba0 — networking dispatcher: if type==2, forward to FUN_71000065f0 (48 bytes)
u64 FUN_7100005ba0(s64 param_1, u64 param_2, u64 param_3)
{
    if (*(s32 *)(param_1 + 4) == 2) {
        return FUN_71000065f0(2, *(s64 *)(param_1 + 0x20) + 4, param_2, param_3);
    }
    return 0;
}

// 0x710000f250 — Curl_SigloFree wrapper: free inner pointer then struct (48 bytes)
void FUN_710000f250(u64 *param_1)
{
    if (param_1 != nullptr) {
        Curl_SigloFree((void *)*param_1);
    }
    Curl_SigloFree(param_1);
}

// 0x7100014160 — curl llist insert: insert at +0x8d0, notify on head change (96 bytes)
u64 FUN_7100014160(s64 param_1, s64 param_2)
{
    u64 *puVar1 = *(u64 **)(param_2 + 0x8d0);
    Curl_llist_insert_next((void *)(param_2 + 0x8d0),
                           (void *)*(u64 *)(param_2 + 0x8d8),
                           (void *)param_1,
                           (void *)(param_1 + 0x30));
    u64 *puVar2 = *(u64 **)(param_2 + 0x8d0);
    if (puVar1 != puVar2) {
        *(u8 *)(param_2 + 0x8c9) = 0;
        FUN_71000086c0(*puVar2, 0ULL, 6ULL);
    }
    return 0;
}

// 0x7100004200 — flag setter at +0x811: param_2=1 set, =2 check bit9, else clear (112 bytes)
void FUN_7100004200(s64 param_1, s32 param_2)
{
    u32 uVar1;
    s8  cVar2;
    u8  bVar3;

    if (param_2 == 1) {
        bVar3 = 1;
        cVar2 = *(s8 *)(param_1 + 0x811);
    } else {
        if (param_2 != 2) {
            bVar3 = 0;
            if (*(s8 *)(param_1 + 0x811) == '\0') {
                return;
            }
            goto LAB_7100004264;
        }
        uVar1 = *(u32 *)(*(s64 *)(param_1 + 0x858) + 0x84);
        if ((uVar1 >> 9 & 1) != 0) {
            return;
        }
        bVar3 = (u8)(uVar1 >> 9) & 1 ^ 1;
        cVar2 = *(s8 *)(param_1 + 0x811);
    }
    if (cVar2 == '\x01') {
        return;
    }
LAB_7100004264:
    *(u8 *)(param_1 + 0x811) = bVar3;
}

// 0x7100003660 — socket close: call fn via +0x50 ptr or nnsocketClose (128 bytes)
s32 FUN_7100003660(s64 param_1, s32 param_2)
{
    s32 iVar1;

    if (param_1 != 0) {
        if (*(s64 *)(param_1 + 0x50) != 0) {
            if ((*(s32 *)(param_1 + 0x25c) != param_2) || (*(s8 *)(param_1 + 0x269) == '\0')) {
                FUN_710000b540(param_1, param_2);
                iVar1 = (*(s32 (**)(u64, s32))(param_1 + 0x50))(*(u64 *)(param_1 + 0x58), param_2);
                return iVar1;
            }
            *(u8 *)(param_1 + 0x269) = 0;
        }
        FUN_710000b540(param_1, param_2);
    }
    nnsocketClose(param_2);
    return 0;
}

// 0x7100008270 — varargs forwarder to FUN_7100027900 (128 bytes)
void FUN_7100008270(u64 param_1, u64 param_2, ...)
{
    __builtin_va_list ap;
    __builtin_va_start(ap, param_2);
    FUN_7100027900(param_1, param_2, ap);
    __builtin_va_end(ap);
}

// 0x71000002a0 — unrolled byte copy: 4 bytes/iter then remainder (144 bytes)
void FUN_71000002a0(s64 param_1, s64 param_2, u32 param_3)
{
    s64  lVar1;
    s64  lVar2;
    u8  *puVar3;
    u64  uVar4;
    u8  *puVar5;

    if (0 < (s32)param_3) {
        uVar4 = (u64)param_3;
        if (uVar4 - 1 < 3) {
            lVar2 = 0;
        } else {
            lVar2 = 0;
            do {
                puVar3 = (u8 *)(param_2 + 1 + lVar2);
                puVar5 = (u8 *)(param_1 + 1 + lVar2);
                lVar2  = lVar2 + 4;
                puVar5[-1] = puVar3[-1];
                *puVar5    = *puVar3;
                puVar5[1]  = puVar3[1];
                puVar5[2]  = puVar3[2];
            } while (uVar4 - (uVar4 & 3) != (u64)lVar2);
        }
        if ((param_3 & 3) != 0) {
            lVar1  = -(s64)(uVar4 & 3);
            puVar3 = (u8 *)(param_2 + lVar2);
            puVar5 = (u8 *)(param_1 + lVar2);
            do {
                lVar1  = lVar1 + 1;
                *puVar5 = *puVar3;
                puVar3++;
                puVar5++;
            } while (lVar1 != 0);
        }
    }
}

// 0x71000047b0 — set resolver option with EAGAIN retry, then cleanup (144 bytes)
// NOTE: ~3% match — NX Clang uses x19/x20 + sub/add frame; upstream picks x19/x21 + pre-index
void FUN_71000047b0(s64 param_1)
{
    s32 iVar1;
    u64 local_38;
    u64 local_30;
    s32 local_28;

    if ((*(s64 *)(param_1 + 0xa58) != 0) &&
        (iVar1 = *(s32 *)(*(s64 *)(param_1 + 0xa58) + 0x68), iVar1 != 0)) {
        local_38 = 0x6500004e21ULL;
        local_30 = 4;
        local_28 = iVar1;
        iVar1 = nnsocketResolverSetOption(&local_38);
        while ((iVar1 == -1 && (iVar1 = nnsocketGetLastErrno(), iVar1 == 0xb))) {
            nnosSleepThread(10000000);
            iVar1 = nnsocketResolverSetOption(&local_38);
        }
    }
    FUN_7100004840(param_1 + 0xa38);
}
