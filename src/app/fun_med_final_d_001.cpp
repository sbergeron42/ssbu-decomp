// SSBU 13.0.4 — MEDIUM-tier decompilation batch D-001
// Pool-d worker: functions decompiled from Ghidra
// Compiler: NX Clang 8.0.0, -O2 -target aarch64-none-elf

#include "types.h"

// ---------------------------------------------------------------------------
// 0x710007a9d0  size=352  FUN_710007a9d0
// Callback dispatch: call param_2(param_1+0x408, param_1+0x390), reset field
// ---------------------------------------------------------------------------
void FUN_710007a9d0(long param_1, void (*param_2)(long, long))
{
    param_2(param_1 + 0x408, param_1 + 0x390);
    *(u64 *)(param_1 + 0x408) = 0xffffffffffffffffULL;
}

// ---------------------------------------------------------------------------
// 0x71001b1400  size=144  FUN_71001b1400
// Singleton init: register list node, guard with __cxa_guard
// ---------------------------------------------------------------------------
extern u8   DAT_71052acc58;
extern long DAT_71052acc70;
extern long DAT_71052accd0;
extern long *DAT_71052accb0;
extern long *DAT_71052accb8;
extern long  DAT_71052accc0;
extern long  DAT_71052acca8;
extern long  DAT_71052accc8;
extern void *PTR_DAT_71052a4888;
extern void *PTR_LOOP_7104f15000;
extern void *PTR_LAB_71052a4890;
void FUN_71000001c0(void *, void *, void *);
int  __cxa_guard_acquire(u64 *);
void __cxa_guard_release(u64 *);

long *FUN_71001b1400(void)
{
    if ((DAT_71052acc58 & 1) == 0) {
        int r = __cxa_guard_acquire((u64 *)&DAT_71052acc58);
        if (r != 0) {
            DAT_71052accb0 = &DAT_71052acc70;
            DAT_71052accb8 = &DAT_71052accd0;
            DAT_71052accc0 = 0;
            DAT_71052acca8 = (long)((u8 *)PTR_DAT_71052a4888 + 0x10);
            DAT_71052accc8 = 1;
            FUN_71000001c0(&PTR_LAB_71052a4890, &DAT_71052acca8, &PTR_LOOP_7104f15000);
            __cxa_guard_release((u64 *)&DAT_71052acc58);
        }
    }
    return &DAT_71052acca8;
}

// ---------------------------------------------------------------------------
// 0x71000a0710  size=592  FUN_71000a0710
// Update UV/stripe particle entry; walk list, append to linked list
// ---------------------------------------------------------------------------
extern long PTR_g_pStripeSystem_71052a2b90;
void FUN_7100096200(u32, u32, long, void *, long, void *);
void FUN_7100096a30(u32, u32, long, void *, long, void *);
long FUN_71000880e0(long, u32, long);
void FUN_7100088090(long, int, int);

long FUN_71000a0710(long param_1)
{
    long lVar2;
    long lVar3;
    float fVar5;

    if ((*(char *)(*(long *)(*(long *)(param_1 + 0x10) + 0xa0) + 0x752) == '\0') &&
        (*(long **)(param_1 + 8) != (long *)0)) {
        long *puVar4 = *(long **)(param_1 + 8);
        *(u32 *)((long)puVar4 + 0x74) = *(u32 *)(puVar4 + 0xe);
        lVar2 = *(long *)(param_1 + 0x10);
        long *puVar1 = (long *)(*(long *)(lVar2 + 0x1f0) + (long)*(int *)(param_1 + 0x20) * 0x10);
        long uStack_28 = puVar1[1];
        long local_30 = *puVar1;
        FUN_7100096200(*(u32 *)(param_1 + 0x1c), *(u32 *)(param_1 + 0x18),
                       *(long *)(lVar2 + 0x98), puVar4, *(long *)(lVar2 + 0x238), &local_30);
        FUN_7100096a30(*(u32 *)(param_1 + 0x1c), *(u32 *)(param_1 + 0x18),
                       *(long *)(*(long *)(param_1 + 0x10) + 0x98), puVar4 + 2,
                       *(long *)(*(long *)(param_1 + 0x10) + 0x238), &local_30);
        fVar5 = *(float *)(*(long *)(*(long *)(*(long *)(param_1 + 0x10) + 0x238) + 0x18) + 0x360);
        puVar4[1] = (long)(((u64)puVar4[1] >> 32) << 32) | (u32)(fVar5 * (float)puVar4[1]);
        *puVar4 = (long)(((u64)(u32)(fVar5 * (float)((u64)*puVar4 >> 32)) << 32) |
                  (u64)(u32)(fVar5 * (float)*puVar4));
        puVar4[3] = (long)((((u64)puVar4[3] >> 32) << 32) | (u64)(u32)(fVar5 * (float)puVar4[3]));
        puVar4[2] = (long)(((u64)(u32)(fVar5 * (float)((u64)puVar4[2] >> 32)) << 32) |
                    (u64)(u32)(fVar5 * (float)puVar4[2]));
        lVar3 = *(long *)(*(long *)(param_1 + 0x10) + 0x418);
        lVar2 = *(long *)(lVar3 + 0x18);
        if (lVar2 == 0) {
            *(long **)(lVar3 + 0x18) = puVar4;
        } else {
            do {
                lVar3 = lVar2;
                lVar2 = *(long *)(lVar3 + 0x68);
            } while (lVar2 != 0);
            *(long **)(lVar3 + 0x68) = puVar4;
        }
    }
    return 0;
}

// ---------------------------------------------------------------------------
// 0x71000ac910  size=944  FUN_71000ac910
// Allocate stripe particle, init with random values
// ---------------------------------------------------------------------------
extern long *PTR_g_pStripeSystem2_71052a2b90;
extern float RAND_STEP;
void FUN_7100088090(long, int, int);

long *FUN_71000ac910(long *param_1)
{
    u32  uVar2;
    float fVar3;
    long lVar6;
    long lVar7;

    lVar6 = *param_1;
    if (*(char *)(*(long *)(lVar6 + 0xa0) + 0x752) == '\0') {
        lVar7 = *(long *)(*(long *)(lVar6 + 0x238) + 0x338);
        typedef long *(*alloc_fn_t)(long, int, int);
        alloc_fn_t alloc_fn = *(alloc_fn_t *)(*(long *)(lVar6 + 0x828) + 0x10);
        long *puVar4 = alloc_fn(lVar6 + 0x828, 0x2c, 0x80);
        if (puVar4 != (long *)0) {
            *(u32 *)(puVar4 + 5) = 0;
            puVar4[3] = 0;
            puVar4[4] = 0;
            puVar4[1] = 0;
            puVar4[2] = 0;
            *puVar4 = 0;
            *(long **)(*param_1 + 0x418) = puVar4;
            *(u32 *)puVar4 = *(u32 *)(lVar7 + 0x18);
            *(u32 *)((long)puVar4 + 4) = *(u32 *)(lVar7 + 0x1c);
            uVar2 = *(u32 *)(*param_1 + 0xac);
            *(u32 *)(*param_1 + 0xac) = uVar2 * 0x41c64e6d + 0x3039;
            fVar3 = RAND_STEP;
            *(float *)(puVar4 + 2) = (float)uVar2 * RAND_STEP;
            uVar2 = *(u32 *)(*param_1 + 0xac);
            *(u32 *)(*param_1 + 0xac) = uVar2 * 0x41c64e6d + 0x3039;
            *(float *)((long)puVar4 + 0x14) = (float)uVar2 * fVar3;
            uVar2 = *(u32 *)(*param_1 + 0xac);
            *(u32 *)(*param_1 + 0xac) = uVar2 * 0x41c64e6d + 0x3039;
            *(float *)(puVar4 + 3) = (float)uVar2 * fVar3;
            uVar2 = *(u32 *)(*param_1 + 0xac);
            *(u32 *)(*param_1 + 0xac) = uVar2 * 0x41c64e6d + 0x3039;
            *(float *)((long)puVar4 + 0x1c) = (float)uVar2 * fVar3;
            FUN_7100088090(*param_1, 4, 0x60);
            lVar6 = *param_1;
            int iVar1 = (*(int *)(lVar6 + 0x230) +
                         *(int *)(*(long *)(*(long *)(lVar6 + 0x238) + 0x338) + 0x10) *
                         *(int *)(lVar6 + 0x230)) * 0xa0 + 0xa0;
            if (iVar1 == 0)
                return (long *)0x1;
            lVar7 = *(long *)(lVar6 + 0x418);
            u64 uVar5 = FUN_71000880e0(lVar6,
                         *(u32 *)(*(long *)PTR_g_pStripeSystem_71052a2b90 + 0x20),
                         (long)iVar1);
            if ((uVar5 & 1) != 0) {
                *(u8 *)(lVar7 + 0x20) = 1;
                return (long *)0x1;
            }
        }
    } else {
        return (long *)0;
    }
    return (long *)0;
}

// ---------------------------------------------------------------------------
// 0x71000e940  size=848  FUN_710000e940
// HTTP response code processing (curl)
// ---------------------------------------------------------------------------
extern long DAT_00004d00;
extern long DAT_00004ce0;
extern long DAT_00004cf0;
extern long DAT_00004cc0;
extern long DAT_00004cd0;
extern long DAT_00004ce8;
extern long DAT_00004cc8;
extern long DAT_00004cd8;
extern long DAT_00004fb8;
void Curl_SigloFree(long);
long Curl_SigloStrdup(long);
void Curl_failf(long, const char *, int);
void FUN_7100004200(long *, int);
long FUN_71000179b0(long *);

u64 FUN_710000e940(long *param_1)
{
    int  iVar1;
    long lVar2;
    u32  uVar4;
    long lVar7;
    long lVar8;
    long lVar9;

    lVar7 = *param_1;
    iVar1 = *(int *)(lVar7 + 0x170);
    if ((u32)(iVar1 - 100) < 100)
        return 0;

    if (*(char *)(&DAT_00004d00 + lVar7) != '\0') {
        uVar4 = 0;
        if (*(char *)(lVar7 + 0x6b8) != '\0')
            uVar4 = 0x16;
        return (u64)uVar4;
    }

    char cVar6 = (char)param_1[0x103];
    if (cVar6 != '\0' && iVar1 == 0x191) {
        // handled in else branch
    }
    if ((cVar6 == '\0') ||
        (iVar1 != 0x191 && (cVar6 = '\0', (299 < iVar1 ||
                             (*(char *)((long)param_1 + 0x822) == '\0')))))
    {
        // LAB_710000ea44
        if (*(char *)((long)param_1 + 0x819) == '\0')
            goto lab_ea98;

        // LAB_710000ea4c
        if ((iVar1 != 0x197) && ((299 < iVar1 || (*(char *)((long)param_1 + 0x822) == '\0'))))
            goto lab_ea98;

        uVar4 = (u32)(*(u64 *)(&DAT_00004ce0 + lVar7) & *(u64 *)(&DAT_00004cf0 + lVar7));
        u64 uVar5;
        if (uVar4 >> 2 & 1)       uVar5 = 4;
        else if (uVar4 >> 1 & 1)  uVar5 = 2;
        else if (uVar4 >> 3 & 1)  uVar5 = 8;
        else if (uVar4 >> 5 & 1)  uVar5 = 0x20;
        else if (*(u64 *)(&DAT_00004ce0 + lVar7) & *(u64 *)(&DAT_00004cf0 + lVar7) & 1)
            uVar5 = 1;
        else {
            *(u64 *)(&DAT_00004ce8 + lVar7) = 0x40000000;
            *(u64 *)(&DAT_00004cf0 + lVar7) = 0;
            *(char *)(&DAT_00004d00 + lVar7) = 1;
            goto lab_ea98;
        }
        *(u64 *)(&DAT_00004ce8 + lVar7) = uVar5;
        *(u64 *)(&DAT_00004cf0 + lVar7) = 0;
        goto lab_eb0c;
    } else {
        uVar4 = (u32)(*(u64 *)(&DAT_00004cc0 + lVar7) & *(u64 *)(&DAT_00004cd0 + lVar7));
        u64 uVar5;
        if (uVar4 >> 2 & 1)       uVar5 = 4;
        else if (uVar4 >> 1 & 1)  uVar5 = 2;
        else if (uVar4 >> 3 & 1)  uVar5 = 8;
        else if (uVar4 >> 5 & 1)  uVar5 = 0x20;
        else if (*(u64 *)(&DAT_00004cc0 + lVar7) & *(u64 *)(&DAT_00004cd0 + lVar7) & 1)
            uVar5 = 1;
        else {
            cVar6 = '\0';
            *(u64 *)(&DAT_00004cd0 + lVar7) = 0;
            *(u64 *)(&DAT_00004cc8 + lVar7) = 0x40000000;
            *(char *)(&DAT_00004d00 + lVar7) = 1;
            if (*(char *)((long)param_1 + 0x819) == '\0')
                goto lab_ea98;
            if ((iVar1 != 0x197) && ((299 < iVar1 || (*(char *)((long)param_1 + 0x822) == '\0'))))
                goto lab_ea98;
            uVar4 = (u32)(*(u64 *)(&DAT_00004ce0 + lVar7) & *(u64 *)(&DAT_00004cf0 + lVar7));
            if (uVar4 >> 2 & 1)       uVar5 = 4;
            else if (uVar4 >> 1 & 1)  uVar5 = 2;
            else if (uVar4 >> 3 & 1)  uVar5 = 8;
            else if (uVar4 >> 5 & 1)  uVar5 = 0x20;
            else if (*(u64 *)(&DAT_00004ce0 + lVar7) & *(u64 *)(&DAT_00004cf0 + lVar7) & 1)
                uVar5 = 1;
            else {
                *(u64 *)(&DAT_00004ce8 + lVar7) = 0x40000000;
                *(u64 *)(&DAT_00004cf0 + lVar7) = 0;
                *(char *)(&DAT_00004d00 + lVar7) = 1;
                goto lab_ea98;
            }
            *(u64 *)(&DAT_00004ce8 + lVar7) = uVar5;
            *(u64 *)(&DAT_00004cf0 + lVar7) = 0;
            goto lab_eb0c;
        }
        cVar6 = '\x01';
        *(u64 *)(&DAT_00004cc8 + lVar7) = uVar5;
        *(u64 *)(&DAT_00004cd0 + lVar7) = 0;
        // fall through to LAB_710000ea44
        if (*(char *)((long)param_1 + 0x819) == '\0')
            goto lab_ea98;
        if ((iVar1 != 0x197) && ((299 < iVar1 || (*(char *)((long)param_1 + 0x822) == '\0'))))
            goto lab_ea98;
        uVar4 = (u32)(*(u64 *)(&DAT_00004ce0 + lVar7) & *(u64 *)(&DAT_00004cf0 + lVar7));
        if (uVar4 >> 2 & 1)       uVar5 = 4;
        else if (uVar4 >> 1 & 1)  uVar5 = 2;
        else if (uVar4 >> 3 & 1)  uVar5 = 8;
        else if (uVar4 >> 5 & 1)  uVar5 = 0x20;
        else if (*(u64 *)(&DAT_00004ce0 + lVar7) & *(u64 *)(&DAT_00004cf0 + lVar7) & 1)
            uVar5 = 1;
        else {
            *(u64 *)(&DAT_00004ce8 + lVar7) = 0x40000000;
            *(u64 *)(&DAT_00004cf0 + lVar7) = 0;
            *(char *)(&DAT_00004d00 + lVar7) = 1;
            goto lab_ea98;
        }
        *(u64 *)(&DAT_00004ce8 + lVar7) = uVar5;
        *(u64 *)(&DAT_00004cf0 + lVar7) = 0;
        if (cVar6 == '\0') {
            goto lab_ea98;
        }
    }

lab_eb0c:
    Curl_SigloFree(*(long *)(lVar7 + 0x238));
    *(long *)(lVar7 + 0x238) = 0;
    lVar2 = Curl_SigloStrdup(*(long *)(lVar7 + 0x998));
    *(long *)(lVar7 + 0x238) = lVar2;
    if (lVar2 == 0)
        return 0x1b;

    if (((*(u32 *)(lVar7 + 0x480) | 4) != 5) && (*(char *)((long)param_1 + 0x823) == '\0')) {
        lVar8 = *param_1;
        lVar2 = *(long *)(lVar8 + 600);
        if ((lVar2 != 0) && ((*(u32 *)(lVar8 + 0x480) | 4) != 5)) {
            lVar9 = *(long *)(lVar2 + 0x30);
            uVar4 = *(u32 *)(lVar8 + 0x480);
            if ((*(char *)((long)param_1 + 0x822) == '\0') &&
                (*(char *)((long)param_1 + 0x81f) != '\0')) {
                if (uVar4 == 2) {
                    lVar2 = *(long *)(&DAT_00004fb8 + lVar8);
                    *(u8 *)((long)param_1 + 0x823) = 0;
                    if (lVar2 != -1)
                        goto lab_ec00;
                } else if (uVar4 == 3) {
                    lVar2 = *(long *)(lVar2 + 8);
                    *(u8 *)((long)param_1 + 0x823) = 0;
                    if (lVar2 != -1)
                        goto lab_ec00;
                } else if (uVar4 == 4) {
                    lVar2 = *(long *)(&DAT_00004fb8 + lVar8);
                    *(u8 *)((long)param_1 + 0x823) = 0;
                    if (lVar2 != -1)
                        goto lab_ec00;
                } else {
                    *(u8 *)((long)param_1 + 0x823) = 0;
                }
                FUN_7100004200(param_1, 2);
                *(long *)(lVar8 + 0xc0) = 0;
                goto after_ec6c;
lab_ec00:
                if (lVar9 < lVar2)
                    goto after_ec6c;
                FUN_7100004200(param_1, 2);
                *(long *)(lVar8 + 0xc0) = 0;
            } else {
                lVar2 = 0;
                *(u8 *)((long)param_1 + 0x823) = 0;
                if (lVar9 >= lVar2)
                    goto after_ec6c;
                FUN_7100004200(param_1, 2);
                *(long *)(lVar8 + 0xc0) = 0;
            }
after_ec6c:
            if ((lVar9 != 0) && (FUN_71000179b0(param_1) != 0))
                return FUN_71000179b0(param_1);
        }
    }
    goto after_eb0c;

lab_ea98:
    if (cVar6 != '\0')
        goto lab_eb0c;
    {
        lVar7 = *param_1;
        if (((*(int *)(lVar7 + 0x170) < 300) && (*(char *)(&DAT_00004cd8 + lVar7) == '\0')) &&
            (*(char *)((long)param_1 + 0x822) != '\0') &&
            ((*(u32 *)(lVar7 + 0x480) | 4) != 5)) {
            lVar2 = Curl_SigloStrdup(*(long *)(lVar7 + 0x998));
            *(long *)(lVar7 + 0x238) = lVar2;
            if (lVar2 == 0)
                return 0x1b;
            *(char *)(&DAT_00004cd8 + lVar7) = '\x01';
        }
    }

after_eb0c:
    lVar2 = *param_1;
    iVar1 = *(int *)(lVar2 + 0x170);
    if ((iVar1 < 400) || (*(char *)(lVar2 + 0x6b8) == '\0'))
        return 0;
    if (iVar1 == 0x197) {
        char cVar6b = *(char *)((long)param_1 + 0x819);
        if ((cVar6b != '\0') && (*(char *)(&DAT_00004d00 + lVar2) == '\0'))
            return 0;
    } else if (iVar1 == 0x191) {
        char cVar6b = (char)param_1[0x103];
        if ((cVar6b != '\0') && (*(char *)(&DAT_00004d00 + lVar2) == '\0'))
            return 0;
    }
    Curl_failf(lVar7, "The requested URL returned error: %d", *(int *)(lVar7 + 0x170));
    return 0x16;
}
