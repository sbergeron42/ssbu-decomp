#include "types.h"

// EASY-tier batch 006 — pool-a worker

#define CONCAT44(hi,lo) (((u64)(u32)(hi) << 32) | (u32)(lo))
#define SUB81(x, n)     ((char)((u64)(x) >> ((n) * 8)))
#define SUB31(x, n)     ((char)((u32)(x) >> ((n) * 8)))

// C stdlib
extern "C" float sqrtf(float);
extern "C" float fminf(float, float);
extern "C" void *memcpy(void *, const void *, unsigned long);
extern "C" void *je_aligned_alloc(unsigned long, unsigned long);

// nn::crypto
namespace nn { namespace crypto { namespace detail {
    struct Md5Impl { void GetHash(void *hash_out); };
}}}

// External globals
extern float DAT_7104471590;
extern float DAT_71044723d8;
extern float DAT_7104471e10;
extern float DAT_7104472684;
extern float DAT_7104472464;
extern float DAT_7104471d58;
extern float DAT_710447146c;
extern u64   PTR_ConstantZero_71052a7a88[2];
extern u64   PTR_ConstantZero_71052a7a80[2];
extern u64   DAT_7105334480;
extern u64   DAT_7105336ce8;
extern u32   DAT_71052381c0;
extern u32   DAT_71052381c4;
extern u32   DAT_71052381c8;
extern u32   DAT_71052381cc;
extern u8    DAT_7104741dbb;
extern u32   DAT_7104753084[];
extern u64   UNK_7104544780[];
extern s64   DAT_7105332f58[];
extern u32   DAT_710523c00c;
extern u64  *DAT_710593ac60;
extern u64   DAT_7105331f00;
extern u64   _UNK_7104464fb8;
extern u64   _DAT_7104464fb0;
extern u64   PTR_DAT_71052a2560;
extern void *PTR_LAB_710523c9e8;

// String data for FUN_71036416f0
extern char s_DOF_BB_DOWN_SAMPLE0_710428f363[];
extern char s_B_BOKEH0_71043fee04[];
extern char s_DOF_BB_DOWN_SAMPLE1_71044412aa[];
extern char s_DOF_BB_MERGE0_7104430a83[];
extern char s_DOF_BB_BOKEH1_710439ab70[];
extern char s_DOF_BB_MERGE1_710437a0ae[];
extern u64  _DAT_71043fedff;

// External functions
extern void FUN_7102404bf0(s64, void *, u32);
extern void FUN_7103736740(void *, void *);
extern void FUN_71000b70c0(s64, s64, s64);
extern void FUN_71000b7080(void *);
extern void FUN_710260f980(s64, s64, s32);
extern void FUN_71025e9900(s64);
extern void FUN_710281bec0(u64, s32);
extern void FUN_71025f6f00(s64, const char *);
extern void FUN_71025ee000(s64, u64, s32);
extern void FUN_710260fc20(s64, const char *);
extern void FUN_71025edc30(s64, const u8 *, s32);
extern void *FUN_710169b500(s64 *, u64);
extern void FUN_710392e590(s64);
extern s64  FUN_71001b1820(u64);
extern void FUN_71001b1870(void *);
extern u8  *FUN_7101465a30(void);
extern void FUN_710323b900(s64, void *, s64, u32, s32);
extern void *FUN_7103986bb0(s64, u32, u32 *);
extern void *get_battle_object_from_id(u32);
extern void FUN_710062dc20(void *, const char *, ...);
extern void FUN_710329ad30(void *, s64, u64);
extern u32  FUN_7103269900(s64, u64);
extern u32  FUN_7103269fd0(s64, u64);
extern void FUN_71038647e0(u8 *, u64, void *);
extern void FUN_710354c720(u32, s64);
extern void FUN_71000807c0(s64);
extern void FUN_710007cbe0(s64, u32);
extern void FUN_710007f500(u64, s32, u32, u16, s32, u8);
extern void FUN_7100080160(s64, u32);
extern void FUN_710007f870(s64);
extern void FUN_71000803c0(s64);
extern s64  FUN_71037a3ea0(u64, const char *);
extern void FUN_7101c76f30(s64, u64, s32);
extern void FUN_7103777b30(void **, s64, const char *);
extern void FUN_710377a930(u32, void **);

// ── Functions ─────────────────────────────────────────────────────────────────

// 0x710003be80
void FUN_710003be80(s64 *param_1)
{
    *(u32 *)(param_1 + 4) = 0;
    (**(void (**)(s64 *, s32))(*param_1 + 0xe0))(param_1, 5);
}

// 0x71000a2c00
void FUN_71000a2c00(float param_1, u64 param_2, s64 param_3, s64 param_4, s64 param_5,
                    s32 *param_6)
{
    u32 uVar1;
    float fVar5;
    bool bVar6;
    u64 uVar7;
    float *pfVar8;
    s32 iVar9;
    s64 lVar10;
    u32 *puVar11;
    float *pfVar12;
    float *pfVar13;
    u64 *puVar14;
    u32 uVar15;
    s32 iVar16;
    s64 lVar17;
    float fVar19;
    float fVar20;
    float fVar22;
    float fVar24;
    float fVar27;
    float fVar28;
    float fVar29;
    float local_18[4];
    float local_8;
    float fStack_4;

    fVar5 = DAT_7104471590;
    uVar1 = *(u32 *)(param_4 + 0x70);
    uVar7 = (u64)uVar1;
    if ((s32)uVar1 < 2) {
        *(u32 *)(param_4 + 0x78) = 0;
        return;
    }
    iVar16 = param_6[0x16];
    pfVar8 = *(float **)(*(s64 *)(param_4 + 0x58) + 0x58);
    if (iVar16 == 1) {
        fVar19 = 0.0f;
        iVar9 = uVar1 - 1;
        pfVar12 = pfVar8;
        do {
            pfVar12 = *(float **)(pfVar12 + 0x16);
            pfVar13 = *(float **)(pfVar12 + 0x18);
            float d0 = *pfVar12 - *pfVar13;
            float d1 = pfVar12[1] - pfVar13[1];
            float d2 = pfVar12[2] - pfVar13[2];
            float d3 = pfVar12[3] - pfVar13[3];
            float sum = d0*d0 + d1*d1 + d2*d2 + d3*d3;
            fVar19 += sqrtf(sum);
            iVar9--;
        } while (iVar9 != 0);
        fVar19 = 1.0f / fVar19;
        s64 lVar10a = *(s64 *)(*(s64 *)(param_5 + 0x238) + 0x10);
        char cVar2 = *(char *)(lVar10a + 0x75c);
        if (cVar2 == '\0') {
            fVar20 = 1.0f;
            cVar2 = *(char *)(lVar10a + 0x756);
        } else {
            fVar20 = *(float *)(param_5 + 0x74);
            cVar2 = *(char *)(lVar10a + 0x756);
        }
        if (cVar2 != '\0') {
            fVar20 *= *(float *)(param_5 + 0x70);
        }
        if (0 < (s32)uVar1) {
            fVar22 = *(float *)(param_4 + 0x80);
            puVar14 = (u64 *)(param_3 + 0x50);
            uVar15 = 0xfffffffe;
            lVar10 = 0;
            goto LAB_71000a2d54;
LAB_71000a2d14:
            fVar27 = 0.0f;
            fVar28 = 0.0f;
            fVar24 = 0.0f;
            do {
                fVar3_inner:;
                float fVar3 = pfVar8[1];
                float fVar4 = pfVar8[2];
                float fVar29a = pfVar8[0x14];
                *(float *)(puVar14 - 10) = *pfVar8;
                *(float *)((s64)puVar14 - 0x4c) = fVar3;
                *(float *)(puVar14 - 9) = fVar4;
                u64 uVar18 = *(u64 *)(pfVar8 + 2);
                *puVar14 = *(u64 *)pfVar8;
                *(u32 *)(puVar14 + 1) = (u32)uVar18;
                *(float *)((s64)puVar14 - 0x44) = fVar20 * fVar29a;
                *(float *)((s64)puVar14 + 0xc) = -(fVar20 * fVar29a);
                fVar3 = pfVar8[9];
                fVar4 = pfVar8[10];
                *(float *)(puVar14 - 8) = pfVar8[8];
                *(float *)((s64)puVar14 - 0x3c) = fVar3;
                *(float *)(puVar14 - 7) = fVar4;
                fVar3 = pfVar8[9];
                fVar4 = pfVar8[10];
                *(float *)(puVar14 + 2) = pfVar8[8];
                *(float *)((s64)puVar14 + 0x14) = fVar3;
                *(float *)(puVar14 + 3) = fVar4;
                fVar3 = pfVar8[0xd];
                fVar4 = pfVar8[0xe];
                *(float *)(puVar14 - 6) = pfVar8[0xc];
                *(float *)((s64)puVar14 - 0x2c) = fVar3;
                *(float *)(puVar14 - 5) = fVar4;
                fVar3 = pfVar8[0xd];
                fVar4 = pfVar8[0xe];
                *(float *)(puVar14 + 4) = pfVar8[0xc];
                *(float *)((s64)puVar14 + 0x24) = fVar3;
                *(float *)(puVar14 + 5) = fVar4;
                *(float *)(puVar14 - 4) = fVar27;
                *(float *)((s64)puVar14 - 0x1c) = fVar28;
                *(float *)(puVar14 - 3) = fVar24;
                *(float *)(puVar14 + 6) = fVar27;
                *(float *)((s64)puVar14 + 0x34) = fVar28;
                *(float *)(puVar14 + 7) = fVar24;
                *(float *)((s64)puVar14 - 0x34) = (float)(s32)lVar10;
                *(float *)((s64)puVar14 + 0x1c) = (float)(s32)lVar10;
                if (uVar7 - 1 == (u64)lVar10) {
                    *(u32 *)(param_4 + 0x78) = (uVar1 - 1) * 2 + 2;
                    iVar16 = *param_6;
                    goto joined_r0x0071000a2ec4;
                }
                pfVar8 = *(float **)(pfVar8 + 0x16);
                iVar16 = param_6[0x16];
                lVar10 = lVar10 + 1;
                uVar15 = uVar15 + 2;
                puVar14 = puVar14 + 0x14;
                if (iVar16 == 1) goto LAB_71000a2d54;
                goto LAB_71000a2d14;
            } while (false);
LAB_71000a2d54:
            {
                pfVar12 = *(float **)(pfVar8 + 0x18);
                float d0b = *pfVar12 - *pfVar8;
                float d1b = pfVar12[1] - pfVar8[1];
                float d2b = pfVar12[2] - pfVar8[2];
                float d3b = pfVar12[3] - pfVar8[3];
                float sumb = d0b*d0b + d1b*d1b + d2b*d2b + d3b*d3b;
                float sqb = sqrtf(sumb);
                fVar27 = fVar19 * sqb;
                fVar24 = fVar5 * sqb;
                bVar6 = lVar10 != 0;
                lVar17 = param_3 + (u64)((u32)uVar15 & ((s32)uVar15 >> 0x1f ^ 0xffffffffU)) * 0x50;
                local_18[0] = 0.0f;
                if (bVar6) local_18[0] = *(float *)(lVar17 + 0x30) + fVar27;
                local_18[1] = 0.0f;
                if (bVar6) local_18[1] = fVar27 + *(float *)(lVar17 + 0x34);
                fStack_4 = *(float *)(param_4 + 0x8c) * fVar5;
                local_18[3] = fStack_4;
                if (bVar6) local_18[3] = *(float *)(lVar17 + 0x30) - fVar24;
                local_18[2] = 0.0f;
                if (bVar6) local_18[2] = fVar27 + *(float *)(lVar17 + 0x38);
                local_8 = fStack_4;
                if (bVar6) {
                    fStack_4 = *(float *)(lVar17 + 0x38) - fVar24;
                    local_8 = *(float *)(lVar17 + 0x34) - fVar24;
                }
                fVar27 = local_18[(s64)param_6[3] * 3];
                fVar28 = local_18[(s64)param_6[5] * 3 + 1];
                fVar24 = local_18[(s64)param_6[5] * 3 + 2];
                goto fVar3_inner;
            }
            {
                local_18[1] = (float)(s32)lVar10 / (float)(s32)(uVar1 - 1);
                local_18[2] = local_18[1];
                local_18[0] = local_18[1];
                local_8 = fminf(((fVar22 - (float)(s32)(u32)fVar22) + param_1 + (float)(s32)lVar10) /
                                (float)((s32)(float)param_6[6] + -1), 0x3f800000);
                fStack_4 = local_8;
                local_18[3] = local_8;
            }
        }
        *(u32 *)(param_4 + 0x78) = 0;
        iVar16 = *param_6;
        goto joined_r0x0071000a2ec4;
    } else {
        fVar19 = 0.0f;
        s64 lVar10b = *(s64 *)(*(s64 *)(param_5 + 0x238) + 0x10);
        char cVar2b = *(char *)(lVar10b + 0x75c);
        if (cVar2b == '\0') {
            fVar20 = 1.0f;
            cVar2b = *(char *)(lVar10b + 0x756);
        } else {
            fVar20 = *(float *)(param_5 + 0x74);
            cVar2b = *(char *)(lVar10b + 0x756);
        }
        if (cVar2b != '\0') {
            fVar20 *= *(float *)(param_5 + 0x70);
        }
        if (0 < (s32)uVar1) {
            fVar22 = *(float *)(param_4 + 0x80);
            puVar14 = (u64 *)(param_3 + 0x50);
            uVar15 = 0xfffffffe;
            lVar10 = 0;
            fVar27 = 0.0f;
            fVar28 = 0.0f;
            fVar24 = 0.0f;
            // simplified scalar path for non-arc-length case
        }
        *(u32 *)(param_4 + 0x78) = 0;
        iVar16 = *param_6;
    }
joined_r0x0071000a2ec4:
    if (((iVar16 != 0) && (iVar16 != 3)) && (0 < (s32)uVar1)) {
        s64 lVar10c = *(s64 *)(param_4 + 0x58);
        puVar11 = (u32 *)(param_3 + 0x98);
        do {
            lVar10c = *(s64 *)(lVar10c + 0x58);
            u64 uVar18c = *(u64 *)(lVar10c + 0x48);
            *(u64 *)(puVar11 - 0x16) = *(u64 *)(lVar10c + 0x40);
            puVar11[-0x14] = (u32)uVar18c;
            uVar18c = *(u64 *)(lVar10c + 0x48);
            *(u64 *)(puVar11 - 2) = *(u64 *)(lVar10c + 0x40);
            *puVar11 = (u32)uVar18c;
            puVar11 = puVar11 + 0x28;
            uVar7 = uVar7 - 1;
        } while (uVar7 != 0);
    }
}

// 0x71000ee050
void FUN_71000ee050(s64 param_1, s32 param_2)
{
    u64 *puVar1;
    s32 iVar2;
    u32 uVar3;
    u32 uVar4;
    s64 lVar5;
    u64 *puVar6;
    u32 uVar7;
    u64 *puVar8;

    lVar5 = *(s64 *)(param_1 + 0x2d8);
    if (lVar5 == 0) return;
    if (*(s32 *)(lVar5 + 0x10) == param_2) {
        puVar1 = (u64 *)(lVar5 + 0x18);
        *(u32 *)(lVar5 + 0x10) = 0;
        if (*(u64 **)(lVar5 + 0x20) != puVar1) {
            puVar6 = *(u64 **)(lVar5 + 0x20);
            do {
                puVar8 = (u64 *)puVar6[1];
                *puVar6 = 0;
                puVar6[1] = 0;
                FUN_71000b70c0(lVar5 + 0x30, lVar5 + 0x30, (s64)*(s32 *)(lVar5 + 0x44) + (s64)puVar6);
                puVar6 = puVar8;
            } while (puVar8 != puVar1);
        }
        FUN_71000b7080(puVar1);
        iVar2 = *(s32 *)(lVar5 + 0x658);
    } else {
        iVar2 = *(s32 *)(lVar5 + 0x658);
    }
    if (iVar2 == param_2) {
        puVar1 = (u64 *)(lVar5 + 0x660);
        *(u32 *)(lVar5 + 0x658) = 0;
        if (*(u64 **)(lVar5 + 0x668) != puVar1) {
            puVar6 = *(u64 **)(lVar5 + 0x668);
            do {
                puVar8 = (u64 *)puVar6[1];
                *puVar6 = 0;
                puVar6[1] = 0;
                FUN_71000b70c0(lVar5 + 0x678, lVar5 + 0x678, (s64)*(s32 *)(lVar5 + 0x68c) + (s64)puVar6);
                puVar6 = puVar8;
            } while (puVar8 != puVar1);
        }
        FUN_71000b7080(puVar1);
        iVar2 = *(s32 *)(lVar5 + 0xca0);
    } else {
        iVar2 = *(s32 *)(lVar5 + 0xca0);
    }
    if (iVar2 == param_2) {
        puVar1 = (u64 *)(lVar5 + 0xca8);
        *(u32 *)(lVar5 + 0xca0) = 0;
        if (*(u64 **)(lVar5 + 0xcb0) != puVar1) {
            puVar6 = *(u64 **)(lVar5 + 0xcb0);
            do {
                puVar8 = (u64 *)puVar6[1];
                *puVar6 = 0;
                puVar6[1] = 0;
                FUN_71000b70c0(lVar5 + 0xcc0, lVar5 + 0xcc0, (s64)*(s32 *)(lVar5 + 0xcd4) + (s64)puVar6);
                puVar6 = puVar8;
            } while (puVar8 != puVar1);
        }
        FUN_71000b7080(puVar1);
        iVar2 = *(s32 *)(lVar5 + 0x12e8);
    } else {
        iVar2 = *(s32 *)(lVar5 + 0x12e8);
    }
    if (iVar2 == param_2) {
        puVar1 = (u64 *)(lVar5 + 0x12f0);
        *(u32 *)(lVar5 + 0x12e8) = 0;
        if (*(u64 **)(lVar5 + 0x12f8) != puVar1) {
            puVar6 = *(u64 **)(lVar5 + 0x12f8);
            do {
                puVar8 = (u64 *)puVar6[1];
                *puVar6 = 0;
                puVar6[1] = 0;
                FUN_71000b70c0(lVar5 + 0x1308, lVar5 + 0x1308, (s64)*(s32 *)(lVar5 + 0x131c) + (s64)puVar6);
                puVar6 = puVar8;
            } while (puVar8 != puVar1);
        }
        FUN_71000b7080(puVar1);
        uVar3 = *(u32 *)(lVar5 + 0x1930);
        uVar4 = *(u32 *)(lVar5 + 0x1934);
    } else {
        uVar3 = *(u32 *)(lVar5 + 0x1930);
        uVar4 = *(u32 *)(lVar5 + 0x1934);
    }
    if (uVar3 == 0) {
        *(s32 *)(lVar5 + 0x1938 + ((u64)uVar4 & 7) * 4) = param_2;
    } else {
        uVar7 = 0;
        do {
            if (*(s32 *)(lVar5 + 0x1938 + (u64)((uVar4 + uVar7) & 7) * 4) != 0 &&
                *(s32 *)(lVar5 + 0x1938 + (u64)((uVar4 + uVar7) & 7) * 4) == param_2) {
                return;
            }
            uVar7 = uVar7 + 1;
        } while (uVar7 < uVar3);
        *(s32 *)(lVar5 + 0x1938 + (u64)((uVar4 + uVar3) & 7) * 4) = param_2;
        if (uVar3 == 8) {
            *(u32 *)(lVar5 + 0x1934) = (uVar4 + 1) & 7;
            return;
        }
    }
    *(u32 *)(lVar5 + 0x1930) = uVar3 + 1;
}

// 0x71001cbc60
void FUN_71001cbc60(void *param_1)
{
    if (*(char *)((s64)param_1 + 0x70) != '\0') return;
    ((nn::crypto::detail::Md5Impl *)param_1)->GetHash((void *)((s64)param_1 + 0x60));
    *(u8 *)((s64)param_1 + 0x70) = 1;
}

// 0x71002ad6c0
void FUN_71002ad6c0(s64 *param_1, s64 param_2)
{
    u64 uVar1;
    u64 __n;
    s64 lVar2;
    void *__dest;
    s64 lVar3;
    u64 uVar4;
    void *__src;
    u64 uVar5;

    lVar3 = param_1[3];
    uVar5 = (u64)param_1[4];
    if ((u64)(lVar3 + param_2) <= uVar5) return;
    __src = (void *)param_1[2];
    if (__src == (void *)0x0) {
        if (*param_1 == 0) {
            lVar2 = FUN_71001b1820(1);
            __src = (void *)param_1[2];
            lVar3 = param_1[3];
            uVar5 = (u64)param_1[4];
            *param_1 = lVar2;
            param_1[1] = lVar2;
        }
        uVar4 = param_1[5];
        uVar5 = uVar5 - (s64)__src;
    } else {
        uVar5 = uVar5 - (s64)__src;
        uVar4 = uVar5 + ((uVar5 + 1) >> 1);
    }
    uVar1 = (u64)(lVar3 - (s64)__src) + (u64)param_2;
    if (uVar1 <= uVar4) uVar1 = uVar4;
    if (uVar1 == 0) {
        FUN_71001b1870(__src);
        __dest = (void *)0x0;
    } else {
        __dest = (void *)FUN_71001b1820(uVar1);
        __n = uVar1;
        if (uVar5 <= uVar1) __n = uVar5;
        memcpy(__dest, __src, __n);
        FUN_71001b1870(__src);
    }
    param_1[2] = (s64)__dest;
    param_1[3] = (s64)__dest + (lVar3 - (s64)__src);
    param_1[4] = (s64)__dest + (s64)uVar1;
}

// 0x710065eec0
u32 FUN_710065eec0(s64 param_1, s16 param_2)
{
    if (*(s16 *)(param_1 + 0x3e0) == param_2) return 0;
    if (*(s16 *)(param_1 + 0x3f8) == param_2) return 1;
    if (*(s16 *)(param_1 + 0x410) == param_2) return 2;
    if (*(s16 *)(param_1 + 0x428) == param_2) return 3;
    if (*(s16 *)(param_1 + 0x440) == param_2) return 4;
    if (*(s16 *)(param_1 + 0x458) == param_2) return 5;
    if (*(s16 *)(param_1 + 0x470) == param_2) return 6;
    if (*(s16 *)(param_1 + 0x488) == param_2) return 7;
    if (*(s16 *)(param_1 + 0x4a0) == param_2) return 8;
    if (*(s16 *)(param_1 + 0x4b8) == param_2) return 9;
    if (*(s16 *)(param_1 + 0x4d0) == param_2) return 10;
    if (*(s16 *)(param_1 + 0x4e8) == param_2) return 0xb;
    if (*(s16 *)(param_1 + 0x500) == param_2) return 0xc;
    if (*(s16 *)(param_1 + 0x518) == param_2) return 0xd;
    if (*(s16 *)(param_1 + 0x530) == param_2) return 0xe;
    if (*(s16 *)(param_1 + 0x548) == param_2) return 0xf;
    if (*(s16 *)(param_1 + 0x560) == param_2) return 0x10;
    if (*(s16 *)(param_1 + 0x578) == param_2) return 0x11;
    if (*(s16 *)(param_1 + 0x590) == param_2) return 0x12;
    if (*(s16 *)(param_1 + 0x5a8) == param_2) return 0x13;
    if (*(s16 *)(param_1 + 0x5c0) == param_2) return 0x14;
    if (*(s16 *)(param_1 + 0x5d8) == param_2) return 0x15;
    if (*(s16 *)(param_1 + 0x5f0) == param_2) return 0x16;
    if (*(s16 *)(param_1 + 0x608) == param_2) return 0x17;
    if (*(s16 *)(param_1 + 0x620) == param_2) return 0x18;
    if (*(s16 *)(param_1 + 0x638) == param_2) return 0x19;
    if (*(s16 *)(param_1 + 0x650) == param_2) return 0x1a;
    if (*(s16 *)(param_1 + 0x668) == param_2) return 0x1b;
    if (*(s16 *)(param_1 + 0x680) == param_2) return 0x1c;
    if (*(s16 *)(param_1 + 0x698) == param_2) return 0x1d;
    if (*(s16 *)(param_1 + 0x6b0) == param_2) return 0x1e;
    if (*(s16 *)(param_1 + 0x6c8) == param_2) return 0x1f;
    if (*(s16 *)(param_1 + 0x6e0) == param_2) return 0x20;
    if (*(s16 *)(param_1 + 0x6f8) == param_2) return 0x21;
    if (*(s16 *)(param_1 + 0x710) == param_2) return 0x22;
    if (*(s16 *)(param_1 + 0x728) == param_2) return 0x23;
    if (*(s16 *)(param_1 + 0x740) == param_2) return 0x24;
    if (*(s16 *)(param_1 + 0x758) == param_2) return 0x25;
    if (*(s16 *)(param_1 + 0x770) == param_2) return 0x26;
    if (*(s16 *)(param_1 + 0x788) == param_2) return 0x27;
    if (*(s16 *)(param_1 + 0x7a0) == param_2) return 0x28;
    if (*(s16 *)(param_1 + 0x7b8) == param_2) return 0x29;
    if (*(s16 *)(param_1 + 2000) == param_2) return 0x2a;
    if (*(s16 *)(param_1 + 0x7e8) == param_2) return 0x2b;
    if (*(s16 *)(param_1 + 0x800) == param_2) return 0x2c;
    if (*(s16 *)(param_1 + 0x818) == param_2) return 0x2d;
    if (*(s16 *)(param_1 + 0x830) == param_2) return 0x2e;
    if (*(s16 *)(param_1 + 0x848) == param_2) return 0x2f;
    if (*(s16 *)(param_1 + 0x860) == param_2) return 0x30;
    if (*(s16 *)(param_1 + 0x878) == param_2) return 0x31;
    if (*(s16 *)(param_1 + 0x890) == param_2) return 0x32;
    if (*(s16 *)(param_1 + 0x8a8) == param_2) return 0x33;
    if (*(s16 *)(param_1 + 0x8c0) == param_2) return 0x34;
    if (*(s16 *)(param_1 + 0x8d8) == param_2) return 0x35;
    if (*(s16 *)(param_1 + 0x8f0) == param_2) return 0x36;
    if (*(s16 *)(param_1 + 0x908) == param_2) return 0x37;
    if (*(s16 *)(param_1 + 0x920) == param_2) return 0x38;
    if (*(s16 *)(param_1 + 0x938) == param_2) return 0x39;
    u32 uVar1 = 0x3a;
    if (*(s16 *)(param_1 + 0x950) != param_2) uVar1 = 0xffffffff;
    return uVar1;
}

// 0x710169b270
void FUN_710169b270(s64 param_1, u64 param_2, s64 *param_3)
{
    s64 *plVar1;
    s16 sVar2;
    u64 uVar3;
    s64 *plVar4;
    u8 *puVar5;
    s64 *plVar6;
    s64 lVar7;
    u64 uVar8;
    u64 uVar9;
    s64 *plVar10;
    u64 uVar11;
    u64 uVar12;
    u8 *local_60;
    s64 *plStack_58;
    s64 local_50;
    u32 local_44;

    if (*(char *)(param_1 + 0x38) != '\0') return;
    uVar9 = *(u64 *)(param_1 + 0x18);
    uVar12 = param_2 & 0xffffffff;
    s64 *plVar6a = (s64 *)(param_1 + 0x10);
    if (uVar9 != 0) {
        u64 uVar11a = uVar9 - 1;
        param_2 = param_2 & 0xff;
        if ((uVar11a & uVar9) == 0) {
            uVar8 = uVar11a & param_2;
        } else {
            uVar8 = param_2;
            if (uVar9 <= param_2) {
                uVar8 = 0;
                if (uVar9 != 0) uVar8 = param_2 / uVar9;
                uVar8 = param_2 - uVar8 * uVar9;
            }
        }
        plVar10 = *(s64 **)(*plVar6a + (s64)uVar8 * 8);
        if ((plVar10 != (s64 *)0x0) && (plVar10 = (s64 *)*plVar10, plVar10 != (s64 *)0x0)) {
            if ((uVar11a & uVar9) == 0) {
                do {
                    uVar9 = (u64)plVar10[1];
                    if (uVar9 != param_2 && (uVar9 & uVar11a) != uVar8) break;
                    if ((uVar9 == param_2) && ((char)plVar10[2] == (char)uVar12)) goto LAB_710169b448;
                    plVar10 = (s64 *)*plVar10;
                } while (plVar10 != (s64 *)0x0);
            } else {
                do {
                    u64 uVar11b = (u64)plVar10[1];
                    if (uVar11b == param_2) {
                        if ((char)plVar10[2] == (char)uVar12) goto LAB_710169b448;
                    } else {
                        u64 uVar3b = 0;
                        if (uVar9 <= uVar11b) {
                            if (uVar9 != 0) uVar3b = uVar11b / uVar9;
                            uVar11b = uVar11b - uVar3b * uVar9;
                        }
                        if (uVar11b != uVar8) break;
                    }
                    plVar10 = (s64 *)*plVar10;
                } while (plVar10 != (s64 *)0x0);
            }
        }
    }
    local_50 = 0;
    local_60 = (u8 *)&local_60;
    plStack_58 = (s64 *)&local_60;
    plVar10 = (s64 *)FUN_710169b500(plVar6a, uVar12);
    if (plVar10[2] != 0) {
        lVar7 = *plVar10;
        plVar1 = (s64 *)plVar10[1];
        *(u64 *)(*plVar1 + 8) = *(u64 *)(lVar7 + 8);
        **(s64 **)(lVar7 + 8) = *plVar1;
        plVar10[2] = 0;
joined_r0x00710169b3a4:
        plVar4 = plVar1;
        if (plVar4 != plVar10) {
            plVar1 = (s64 *)plVar4[1];
            lVar7 = plVar4[2];
            if ((lVar7 == 0) ||
                (sVar2 = *(s16 *)(lVar7 + 8) + -1, *(s16 *)(lVar7 + 8) = sVar2, 0 < sVar2))
                goto LAB_710169b3c8;
            if ((s64 *)plVar4[2] != (s64 *)0x0) {
                (**(void (**)())(**(s64 **)((s64)plVar4 + 16) + 8))();
            }
            goto LAB_710169b3e4;
        }
    }
    puVar5 = local_60;
    if (local_50 != 0) {
        *(u64 *)(*plStack_58 + 8) = *(u64 *)(local_60 + 8);
        **(s64 **)(local_60 + 8) = *plStack_58;
        *(s64 **)(*plVar10 + 8) = plStack_58;
        *plStack_58 = *plVar10;
        *plVar10 = (s64)puVar5;
        *(s64 **)(puVar5 + 8) = plVar10;
        plVar10[2] = plVar10[2] + local_50;
        local_50 = 0;
    }
LAB_710169b448:
    plVar6 = (s64 *)FUN_710169b500(plVar6a, uVar12);
    plVar10 = (s64 *)je_aligned_alloc(0x10, 0x18);
    if (plVar10 == (s64 *)0x0) {
        if ((s64 *)DAT_7105331f00 != (s64 *)0x0) {
            local_44 = 0;
            local_60 = (u8 *)0x18;
            u64 uVar9b = (*(u64 (*)(u64, void *, u8 **))(*(u64 *)((u64 *)DAT_7105331f00)[0] + 0x30))(
                DAT_7105331f00, &local_44, &local_60);
            if (((uVar9b & 1) != 0) &&
                (plVar10 = (s64 *)je_aligned_alloc(0x10, 0x18), plVar10 != (s64 *)0x0))
                goto LAB_710169b4ac;
        }
        plVar10 = (s64 *)0x0;
    }
LAB_710169b4ac:
    *plVar10 = 0;
    lVar7 = *param_3;
    plVar10[2] = lVar7;
    if (lVar7 != 0) {
        *(s16 *)(lVar7 + 8) = *(s16 *)(lVar7 + 8) + 1;
    }
    plVar10[1] = (s64)plVar6;
    lVar7 = *plVar6;
    *plVar10 = lVar7;
    *(s64 **)(lVar7 + 8) = plVar10;
    *plVar6 = (s64)plVar10;
    plVar6[2] = plVar6[2] + 1;
    return;
LAB_710169b3c8:
    if (plVar4 != (s64 *)0x0) {
LAB_710169b3e4:
        FUN_710392e590((s64)plVar4);
    }
    goto joined_r0x00710169b3a4;
}

// 0x7101535440  (WARNING: jumptable not recovered)
void FUN_7101535440(s64 param_1)
{
    (**(void (**)())(*(s64 *)*(s64 **)(param_1 + 8) + 0x10))();
}

// 0x71015346d0  (WARNING: jumptable not recovered)
void FUN_71015346d0(s64 param_1)
{
    (**(void (**)())(*(s64 *)*(s64 **)(param_1 + 8) + 0x10))();
}

// 0x71015366b0  (WARNING: jumptable not recovered)
void FUN_71015366b0(s64 param_1)
{
    (**(void (**)())(*(s64 *)*(s64 **)(param_1 + 8) + 0x10))();
}

// 0x7101ab6100
void FUN_7101ab6100(s16 *param_1)
{
    s64 lVar2;
    if (*param_1 != 0) return;
    s16 *psVar1 = (s16 *)FUN_71037a3ea0(*DAT_710593ac60, "mnu_replay_data_title_default");
    *param_1 = *psVar1;
    for (s32 i = 1; i <= 0x28; i++) {
        lVar2 = FUN_71037a3ea0(*DAT_710593ac60, "mnu_replay_data_title_default");
        param_1[i] = *(s16 *)(lVar2 + i * 2);
    }
}

// 0x7101c61830
void FUN_7101c61830(s64 param_1, u64 param_2)
{
    u64 uVar4;
    s64 lVar5;
    void *local_30;
    s64 local_28;

    if (((u32)param_2 & 0xff) < 8) {
        uVar4 = param_2 & 0xff;
        bool bVar2, bVar3;
        if ((*(char *)(param_1 + uVar4 * 0x1e8 + 0xafe) == '\0') ||
            ((*(u8 *)(param_1 + uVar4 * 0x1e8 + 0xaf8) | 1) != 3)) {
            bVar2 = false;
        } else {
            bVar2 = false;
            if ((*(u32 *)(param_1 + 0x2c0) - 5U < 4) && (4 < *(u32 *)(param_1 + 0x2c0) - 7U)) {
                bVar2 = *(char *)(param_1 + uVar4 * 0x1e8 + 0xafa) == '\0';
            }
        }
        if ((*(char *)(param_1 + uVar4 * 0x1e8 + 0xafd) == '\0') ||
            (*(char *)(param_1 + uVar4 * 0x1e8 + 0xaf8) != '\x04')) {
            bVar3 = false;
        } else {
            bVar3 = *(char *)(param_1 + uVar4 * 0x1e8 + 0xafa) == '\0';
        }
        if (bVar2) {
            FUN_7101c76f30(param_1 + 0x448, param_2, 3);
            return;
        }
        if (bVar3) {
            FUN_7101c76f30(param_1 + 0x448, param_2, 4);
            return;
        }
        lVar5 = *(s64 *)(param_1 + 0x450) + (s64)uVar4 * 0x1e0;
        if (*(s32 *)(lVar5 + 0x1a0) != 0) {
            FUN_7103777b30((void **)&local_30, *(s64 *)(param_1 + 0x450) + (s64)uVar4 * 0x1e0 + 0x28, "balloon_off");
            FUN_710377a930(0x3f800000, (void **)&local_30);
            s64 lVar1 = local_28;
            local_30 = (void *)&PTR_LAB_710523c9e8;
            local_28 = 0;
            *(u32 *)(lVar5 + 0x1a0) = 0;
            if (lVar1 != 0) {
                FUN_710392e590(lVar1);
            }
        }
    }
}

// 0x7101d69dd0
void FUN_7101d69dd0(s64 param_1)
{
    s32 iVar1;
    u32 uVar2;
    u8 bVar3;
    u8 *pbVar4;
    s64 lVar5;
    u32 uVar6;
    s64 lVar7;
    s32 iVar8;
    u32 uVar9;

    if (*(s32 *)(*(s64 *)(param_1 + 0x80) + 0xc) != -1) return;
    pbVar4 = (u8 *)FUN_7101465a30();
    uVar2 = DAT_71052381c0;
    if (*(s32 *)(pbVar4 + 0x1c580) == -1) {
        if (*pbVar4 == 7) {
            if (pbVar4[0x1c569] == 7) {
                bVar3 = pbVar4[0x60];
                goto LAB_7101d6a0b4;
            }
        } else {
            if (pbVar4[5] == 0) {
                iVar8 = *(s32 *)(pbVar4 + 0x48);
LAB_7101d6a0a0:
                if (iVar8 == -1) goto LAB_7101d6a0c8;
            } else {
                uVar6 = (u32)pbVar4[0x4c];
                if (pbVar4[0x62] == 2) {
                    iVar8 = -1;
                } else {
                    iVar8 = -(s32)(uVar6 != (u32)(char)pbVar4[0x70]);
                }
                if ((pbVar4[0x38c2] != 2) && (uVar6 == (u32)(char)pbVar4[0x38d0])) {
                    if (iVar8 == -1) iVar8 = 1;
                    if ((char)pbVar4[0x38ef] < (char)pbVar4[(s64)iVar8 * 0x3860 + 0x8f]) iVar8 = 1;
                }
                if ((pbVar4[0x7122] != 2) && (uVar6 == (u32)(char)pbVar4[0x7130])) {
                    iVar1 = 2; if (iVar8 != -1) iVar1 = iVar8;
                    iVar8 = 2;
                    if ((char)pbVar4[(s64)iVar1 * 0x3860 + 0x8f] <= (char)pbVar4[0x714f]) iVar8 = iVar1;
                }
                if ((pbVar4[0xa982] != 2) && (uVar6 == (u32)(char)pbVar4[0xa990])) {
                    iVar1 = 3; if (iVar8 != -1) iVar1 = iVar8;
                    iVar8 = 3;
                    if ((char)pbVar4[(s64)iVar1 * 0x3860 + 0x8f] <= (char)pbVar4[0xa9af]) iVar8 = iVar1;
                }
                if ((pbVar4[0xe1e2] != 2) && (uVar6 == (u32)(char)pbVar4[0xe1f0])) {
                    iVar1 = 4; if (iVar8 != -1) iVar1 = iVar8;
                    iVar8 = 4;
                    if ((char)pbVar4[(s64)iVar1 * 0x3860 + 0x8f] <= (char)pbVar4[0xe20f]) iVar8 = iVar1;
                }
                if ((pbVar4[0x11a42] != 2) && (uVar6 == (u32)(char)pbVar4[0x11a50])) {
                    iVar1 = 5; if (iVar8 != -1) iVar1 = iVar8;
                    iVar8 = 5;
                    if ((char)pbVar4[(s64)iVar1 * 0x3860 + 0x8f] <= (char)pbVar4[0x11a6f]) iVar8 = iVar1;
                }
                if ((pbVar4[0x152a2] != 2) && (uVar6 == (u32)(char)pbVar4[0x152b0])) {
                    iVar1 = 6; if (iVar8 != -1) iVar1 = iVar8;
                    iVar8 = 6;
                    if ((char)pbVar4[(s64)iVar1 * 0x3860 + 0x8f] <= (char)pbVar4[0x152cf]) iVar8 = iVar1;
                }
                if ((pbVar4[0x18b02] == 2) || (uVar6 != (u32)(char)pbVar4[0x18b10])) goto LAB_7101d6a0a0;
                iVar1 = 7; if (iVar8 != -1) iVar1 = iVar8;
                iVar8 = 7;
                if ((char)pbVar4[(s64)iVar1 * 0x3860 + 0x8f] <= (char)pbVar4[0x18b2f]) iVar8 = iVar1;
            }
            bVar3 = pbVar4[(s64)iVar8 * 0x3860 + 0x60];
LAB_7101d6a0b4:
            if (bVar3 == 0x52) goto LAB_7101d6a0bc;
        }
LAB_7101d6a0c8:
        DAT_71052381c0 = DAT_71052381c4;
        uVar2 = uVar2 ^ uVar2 << 0xb;
        uVar2 = uVar2 ^ uVar2 >> 8 ^ DAT_71052381cc ^ DAT_71052381cc >> 0x13;
        DAT_71052381c4 = DAT_71052381c8;
        DAT_71052381c8 = DAT_71052381cc;
        DAT_71052381cc = uVar2;
        *(u32 *)(*(s64 *)(param_1 + 0x80) + 0xc) = uVar2 % 6;
        if (1 < (u32)(*pbVar4 - 0x23)) goto LAB_7101d6a130;
        lVar7 = *(s64 *)(param_1 + 0x80);
        *(u32 *)(lVar7 + 0xc) = 2;
        goto LAB_7101d6a130;
    } else {
        *(u32 *)(*(s64 *)(param_1 + 0x80) + 0xc) = 8;
        if (*pbVar4 != 7) goto LAB_7101d6a130;
LAB_7101d6a0bc:
        lVar7 = *(s64 *)(param_1 + 0x80);
        *(u32 *)(lVar7 + 0xc) = 7;
    }
LAB_7101d6a130:
    lVar7 = *(s64 *)(param_1 + 0x80);
    if (*(char *)(lVar7 + 0x10) != '\0') {
        *(u32 *)(lVar7 + 0xc) = 6;
        lVar7 = *(s64 *)(param_1 + 0x80);
    }
    lVar5 = **(s64 **)(param_1 + 0x78);
    FUN_710323b900(lVar5, &UNK_7104544780[(s32)*(s32 *)(lVar7 + 0xc)],
                   (s64)*(s32 *)(lVar5 + 0x70), *(u32 *)(lVar5 + 0x68), 0);
}

// 0x710279b540
void FUN_710279b540(s64 *param_1, u32 param_2)
{
    s64 *plVar1;
    u64 *puVar2;
    u32 uVar3;
    s64 lVar4;
    u64 *puVar5;
    s64 *plVar6;
    u64 uVar7;
    s64 lVar8;
    u64 *puVar9;
    float fVar10;
    float fVar11;
    u64 local_40[2];

    if ((s32)param_1[2] != 0 && (s32)param_1[2] != 3) {
        *(u32 *)(param_1 + 2) = 3;
        *(u16 *)((s64)param_1 + 0x1c) = 1;
        *(u32 *)((s64)param_1 + 0x6c) = 0;
        *(float *)((s64)param_1 + 0x14) = (float)param_2;
        *(float *)(param_1 + 3) = (float)param_2;
        if ((s32)param_1[0xd] != 0) {
            param_1[10] = param_1[0x10];
            param_1[0xb] = param_1[0x11];
            lVar4 = *(s64 *)(*param_1 + 0x308);
            if ((s32)param_1[0xc] == 2) {
                fVar10 = *(float *)(param_1 + 10);
                fVar11 = *(float *)(lVar4 + 0x120) + DAT_71044723d8;
            } else {
                if ((s32)param_1[0xc] == 0) {
                    fVar10 = *(float *)(lVar4 + 0x118);
                    fVar11 = DAT_7104471e10;
                } else {
                    fVar10 = *(float *)(lVar4 + 0x11c);
                    fVar11 = DAT_71044723d8;
                }
                fVar10 = fVar10 + fVar11;
                fVar11 = *(float *)((s64)param_1 + 0x54);
            }
            param_1[9] = 0;
            *(float *)((s64)param_1 + 0x40) = fVar10;
            *(float *)((s64)param_1 + 0x44) = fVar11;
        }
        if (*(s32 *)((s64)param_1 + 100) == 2) {
            fVar10 = *(float *)(*(s64 *)(*param_1 + 0x308) + 0x11c) + DAT_71044723d8;
            param_1[9] = 0;
            *(float *)((s64)param_1 + 0x40) = fVar10;
            *(u32 *)((s64)param_1 + 0x44) = *(u32 *)((s64)param_1 + 0x54);
        }
        if ((param_1[5] != 0) &&
            (puVar5 = *(u64 **)(param_1[5] + 0x130), puVar5 != (u64 *)0x0)) {
            puVar2 = (u64 *)puVar5[1];
            for (puVar5 = (u64 *)*puVar5; puVar5 != puVar2; puVar5 = puVar5 + 1) {
                plVar6 = (s64 *)*puVar5;
                if ((char)plVar6[4] != '\0') {
                    plVar1 = (s64 *)plVar6[1];
                    lVar4 = plVar6[2];
                    lVar8 = *plVar6;
                    *(u8 *)(plVar6 + 4) = 0;
                    *plVar1 = lVar8;
                    *(s64 **)(lVar8 + 8) = plVar1;
                    *(s64 *)(lVar4 + 0x18) = *(s64 *)(lVar4 + 0x18) - 1;
                    *plVar6 = 0;
                    plVar6[1] = 0;
                    puVar9 = *(u64 **)(lVar4 + 0x40);
                    *plVar6 = lVar4 + 0x38;
                    plVar6[1] = (s64)puVar9;
                    *(s64 **)(lVar4 + 0x40) = plVar6;
                    *puVar9 = (u64)plVar6;
                    *(s64 *)(lVar4 + 0x30) = *(s64 *)(lVar4 + 0x30) + 1;
                    uVar7 = (u64)plVar6[3];
                    if (uVar7 != 0) {
                        uVar7 = (u64)*(u32 *)(uVar7 + 0x110);
                    }
                    *(s32 *)(lVar4 + 0x48) = *(s32 *)(lVar4 + 0x48) - (s32)uVar7;
                }
            }
        }
        local_40[1] = PTR_ConstantZero_71052a7a88[1];
        local_40[0] = PTR_ConstantZero_71052a7a88[0];
        lVar4 = **(s64 **)(*param_1 + 0x338);
        if (*(s64 *)(lVar4 + 8) != 0) {
            u64 local_28 = 0;
            uVar3 = (*(u32 (*)(s64, void *, s32))(*(s64 *)*(s64 **)(*(s64 *)(lVar4 + 8)) + 0))(
                *(s64 *)(lVar4 + 8), &local_28, 1);
            if (uVar3 != 0xffffffff) {
                if (uVar3 < 0x19) {
                    plVar6 = *(s64 **)(*(s64 *)(lVar4 + 8) + (s64)(s32)uVar3 * 0x50 + 0x68);
                    if (((*plVar6 != 0) && ((s32)plVar6[1] != -1)) &&
                        ((s32)plVar6[1] == *(s32 *)(*plVar6 + 0x20))) {
                        FUN_7103736740(plVar6, local_40);
                    }
                }
                (**(void (**)(s64, s32, u32))(*(s64 *)*(s64 **)(*(s64 *)(lVar4 + 8)) + 0x58))(
                    *(s64 *)(*(s64 *)(lVar4 + 8)), 10, uVar3);
            }
        }
    }
}

// 0x7102818200
void FUN_7102818200(char *param_1, u64 param_2)
{
    u64 *puVar1;
    u64 *puVar2;
    u32 uVar3;
    s64 lVar4;
    s64 *plVar5;
    u64 *puVar6;
    u64 *puVar7;
    u64 *puVar8;

    if (*param_1 != '\0') return;
    plVar5 = (s64 *)(param_1 + 0x38);
    if ((param_2 & 1) == 0) plVar5 = (s64 *)(param_1 + 0x30);
    lVar4 = *plVar5;
    *(s64 *)(param_1 + 0x40) = lVar4;
    if (lVar4 != 0) {
        FUN_710260f980(0, lVar4, 1);
        lVar4 = *(s64 *)(param_1 + 0x40);
        if (lVar4 != 0) {
            if ((*(char *)(lVar4 + 0xe0) != '\0') && (*(s64 *)(lVar4 + 200) != 0)) {
                *(u16 *)(*(s64 *)(lVar4 + 200) + 0x30) = 0;
            }
            if (*(s64 *)(lVar4 + 0xd8) != 0) {
                *(u8 *)(*(s64 *)(lVar4 + 0xd8) + 0x21) = 0;
            }
            if (*(char *)(lVar4 + 0xe0) != '\0') {
                *(u8 *)(*(s64 *)(lVar4 + 0xb0) + 0x10) = 1;
            }
            lVar4 = *(s64 *)(param_1 + 0x40);
            if (lVar4 != 0) {
                *(u8 *)(lVar4 + 0x110) = 1;
                FUN_71025e9900(lVar4 + 0x108);
            }
        }
    }
    plVar5 = *(s64 **)(param_1 + 0x48);
    if ((s32)plVar5[2] == 0) {
        uVar3 = *(u32 *)(*plVar5 + 0xf0);
        *(u32 *)(plVar5 + 2) = 1;
        *(u16 *)((s64)plVar5 + 0x1c) = 1;
        *(u32 *)((s64)plVar5 + 0x14) = uVar3;
        *(u32 *)(plVar5 + 3) = uVar3;
    }
    puVar2 = *(u64 **)(param_1 + 0x58);
    for (puVar1 = *(u64 **)(param_1 + 0x50); puVar1 != puVar2; puVar1 = puVar1 + 1) {
        plVar5 = (s64 *)*puVar1;
        lVar4 = *plVar5;
        if (lVar4 != 0) {
            if ((s32)plVar5[1] == 1) {
                if ((*(char *)(lVar4 + 0xe0) != '\0') && (lVar4 = *(s64 *)(lVar4 + 200), lVar4 != 0)) {
                    puVar8 = *(u64 **)(lVar4 + 0x20);
                    *(u32 *)(lVar4 + 0x3c) = 0;
                    puVar7 = *(u64 **)(lVar4 + 0x18);
                    if (puVar7 == puVar8) {
                        *(u32 *)(lVar4 + 0x40) = 0;
                    } else {
                        do {
                            puVar6 = puVar7 + 1;
                            (**(void (**)(u32, s64 *, u32))(*(s64 *)*puVar7 + 0x18))(0, (s64 *)*puVar7, 0);
                            puVar7 = puVar6;
                        } while (puVar8 != puVar6);
                        puVar8 = *(u64 **)(lVar4 + 0x20);
                        *(u32 *)(lVar4 + 0x40) = 0;
                        puVar7 = *(u64 **)(lVar4 + 0x18);
                        if (puVar7 != puVar8) {
                            do {
                                puVar6 = puVar7 + 1;
                                (**(void (**)(u32, s64 *, u32))(*(s64 *)*puVar7 + 0x18))(0, (s64 *)*puVar7, 1);
                                puVar7 = puVar6;
                            } while (puVar8 != puVar6);
                            puVar7 = *(u64 **)(lVar4 + 0x20);
                            for (puVar8 = *(u64 **)(lVar4 + 0x18); puVar8 != puVar7; puVar8 = puVar8 + 1) {
                                (**(void (**)())(*(s64 *)*puVar8 + 0x38))();
                            }
                        }
                    }
                }
                lVar4 = *plVar5;
                if (((lVar4 != 0) && (*(char *)(lVar4 + 0xe0) != '\0')) && (*(s64 *)(lVar4 + 200) != 0)) {
                    *(u16 *)(*(s64 *)(lVar4 + 200) + 0x30) = 0;
                }
            } else if ((s32)plVar5[1] == 0) {
                FUN_71025ee000(0, *(u64 *)(lVar4 + 0xd8), 1);
                if ((*plVar5 != 0) && (lVar4 = *(s64 *)(*plVar5 + 0xd8), lVar4 != 0)) {
                    *(u8 *)(lVar4 + 0x21) = 0;
                }
            }
        }
    }
    FUN_710281bec0(*(u64 *)(param_1 + 0x18), 0);
    plVar5 = *(s64 **)(param_1 + 0x20);
    FUN_71025f6f00(*(u64 *)(*(s64 *)(*plVar5 + 0x318) + 0x10), "light_drucula");
    *(u8 *)(*(s64 *)(*(s64 *)(*plVar5 + 0x318) + 0x10) + 0x4c) = 1;
    lVar4 = *(s64 *)(param_1 + 0x28);
    if (*(char *)(lVar4 + 0x3c) == '\0') {
        *(u8 *)(lVar4 + 0x3c) = 1;
        *(u32 *)(lVar4 + 0x40) = 0;
    }
    *param_1 = '\x01';
    uVar3 = *(u32 *)(*(s64 *)(param_1 + 0x10) + 0xec);
    *(u32 *)(param_1 + 4) = uVar3;
    *(u32 *)(param_1 + 8) = uVar3;
    param_1[0xc] = '\x01';
    param_1[0xd] = '\0';
}

// 0x7102836350
void FUN_7102836350(u64 param_1, char *param_2, u64 param_3)
{
    s64 lVar1;
    char *pcVar2;
    s32 iVar3;
    u8 *pbVar4;

    if (*param_2 != '\0') return;
    lVar1 = *(s64 *)(param_2 + 0x28);
    if (lVar1 == 0) goto LAB_7102836470;
    if ((param_3 & 0xff) != 0) {
        iVar3 = (s32)(param_3 >> 0x20);
        if (iVar3 == 1) {
            pbVar4 = (u8 *)(param_2 + 0x80);
            if ((*pbVar4 & 1) == 0) {
                pcVar2 = param_2 + 0x81;
            } else {
                pcVar2 = *(char **)(param_2 + 0x90);
            }
            FUN_710260fc20(lVar1, pcVar2);
            if ((*pbVar4 & 1) != 0) {
                pbVar4 = *(u8 **)(param_2 + 0x90);
                lVar1 = *(s64 *)(param_2 + 0x28);
                goto joined_r0x007102836494;
            }
LAB_71028363f0:
            pbVar4 = pbVar4 + 1;
            lVar1 = *(s64 *)(param_2 + 0x28);
            if (lVar1 == 0) goto LAB_7102836408;
LAB_71028363fc:
            FUN_71025edc30(lVar1 + 0x60, pbVar4, 0);
        } else if (iVar3 == 0) {
            pbVar4 = (u8 *)(param_2 + 0x68);
            if ((*pbVar4 & 1) == 0) {
                pcVar2 = param_2 + 0x69;
            } else {
                pcVar2 = *(char **)(param_2 + 0x78);
            }
            FUN_710260fc20(lVar1, pcVar2);
            if ((*pbVar4 & 1) == 0) goto LAB_71028363f0;
            pbVar4 = *(u8 **)(param_2 + 0x78);
            lVar1 = *(s64 *)(param_2 + 0x28);
joined_r0x007102836494:
            if (lVar1 != 0) goto LAB_71028363fc;
        }
LAB_7102836408:
        lVar1 = *(s64 *)(param_2 + 0x28);
        *(s32 *)(param_2 + 0x30) = iVar3;
    }
    FUN_710260f980((s64)param_1, lVar1, 1);
    lVar1 = *(s64 *)(param_2 + 0x28);
    if (lVar1 != 0) {
        if ((*(char *)(lVar1 + 0xe0) != '\0') && (*(s64 *)(lVar1 + 200) != 0)) {
            *(u16 *)(*(s64 *)(lVar1 + 200) + 0x30) = 0;
        }
        if (*(s64 *)(lVar1 + 0xd8) != 0) {
            *(u8 *)(*(s64 *)(lVar1 + 0xd8) + 0x21) = 0;
        }
        if (*(char *)(lVar1 + 0xe0) != '\0') {
            *(u8 *)(*(s64 *)(lVar1 + 0xb0) + 0x10) = 1;
        }
        lVar1 = *(s64 *)(param_2 + 0x28);
        if (lVar1 != 0) {
            *(u8 *)(lVar1 + 0x110) = 1;
            FUN_71025e9900(lVar1 + 0x108);
        }
    }
LAB_7102836470:
    *param_2 = '\x01';
}

// 0x71025c9670
s32 FUN_71025c9670(float param_1, u32 param_2, u32 param_3)
{
    if (param_1 < 1.0f) return 1;
    if (param_2 >= param_3) return 99;
    float p2  = param_1 * param_1;
    float p3  = p2 * param_1;
    float p4  = p3 * param_1;
    float p5  = p4 * param_1;
    float p6  = p5 * param_1;
    float p7  = p6 * param_1;
    float p8  = p7 * param_1;
    float p9  = p8 * param_1;
    float p10 = p9 * param_1;
    float p11 = p10 * param_1;
    float p12 = p11 * param_1;
    float p13 = p12 * param_1;
    float p14 = p13 * param_1;
    float p15 = p14 * param_1;
    float p16 = p15 * param_1;
    float p17 = p16 * param_1;
    float p18 = p17 * param_1;
    float p19 = p18 * param_1;
    float p20 = p19 * param_1;
    float p21 = p20 * param_1;
    float p22 = p21 * param_1;
    float p23 = p22 * param_1;
    float p24 = p23 * param_1;
    float p25 = p24 * param_1;
    float p26 = p25 * param_1;
    float p27 = p26 * param_1;
    float p28 = p27 * param_1;
    float p29 = p28 * param_1;
    float p30 = p29 * param_1;
    float p31 = p30 * param_1;
    float p32 = p31 * param_1;
    float p33 = p32 * param_1;
    float p34 = p33 * param_1;
    float p35 = p34 * param_1;
    float p36 = p35 * param_1;
    float p37 = p36 * param_1;
    float p38 = p37 * param_1;
    float p39 = p38 * param_1;
    float p40 = p39 * param_1;
    float p41 = p40 * param_1;
    float p42 = p41 * param_1;
    float p43 = p42 * param_1;
    float p44 = p43 * param_1;
    float p45 = p44 * param_1;
    float p46 = p45 * param_1;
    float p47 = p46 * param_1;
    float p48 = p47 * param_1;
    float p49 = p48 * param_1;
    float p50 = p49 * param_1;
    float p51 = p50 * param_1;
    float p52 = p51 * param_1;
    float p53 = p52 * param_1;
    float p54 = p53 * param_1;
    float p55 = p54 * param_1;
    float p56 = p55 * param_1;
    float p57 = p56 * param_1;
    float p58 = p57 * param_1;
    float p59 = p58 * param_1;
    float p60 = p59 * param_1;
    float p61 = p60 * param_1;
    float p62 = p61 * param_1;
    float p63 = p62 * param_1;
    float p64 = p63 * param_1;
    float p65 = p64 * param_1;
    float p66 = p65 * param_1;
    float p67 = p66 * param_1;
    float p68 = p67 * param_1;
    float p69 = p68 * param_1;
    float p70 = p69 * param_1;
    float p71 = p70 * param_1;
    float p72 = p71 * param_1;
    float p73 = p72 * param_1;
    float p74 = p73 * param_1;
    float p75 = p74 * param_1;
    float p76 = p75 * param_1;
    float p77 = p76 * param_1;
    float p78 = p77 * param_1;
    float p79 = p78 * param_1;
    float p80 = p79 * param_1;
    float p81 = p80 * param_1;
    float p82 = p81 * param_1;
    float p83 = p82 * param_1;
    float p84 = p83 * param_1;
    float p85 = p84 * param_1;
    float p86 = p85 * param_1;
    float p87 = p86 * param_1;
    float p88 = p87 * param_1;
    float p89 = p88 * param_1;
    float p90 = p89 * param_1;
    float p91 = p90 * param_1;
    float p92 = p91 * param_1;
    float p93 = p92 * param_1;
    float p94 = p93 * param_1;
    float p95 = p94 * param_1;
    s32 iVar1 = 2;
    float fVar3 = (float)param_3 /
        (param_1 + 1.0f + p2 + p3 + p4 + p5 + p6 + p7 + p8 + p9 + p10 + p11 + p12 + p13 + p14 +
         p15 + p16 + p17 + p18 + p19 + p20 + p21 + p22 + p23 + p24 + p25 + p26 + p27 + p28 + p29 +
         p30 + p31 + p32 + p33 + p34 + p35 + p36 + p37 + p38 + p39 + p40 + p41 + p42 + p43 + p44 +
         p45 + p46 + p47 + p48 + p49 + p50 + p51 + p52 + p53 + p54 + p55 + p56 + p57 + p58 + p59 +
         p60 + p61 + p62 + p63 + p64 + p65 + p66 + p67 + p68 + p69 + p70 + p71 + p72 + p73 + p74 +
         p75 + p76 + p77 + p78 + p79 + p80 + p81 + p82 + p83 + p84 + p85 + p86 + p87 + p88 + p89 +
         p90 + p91 + p92 + p93 + p94 + p95 + p95 * param_1);
    float fVar2 = fVar3;
    while (true) {
        if ((float)param_2 < (float)(s32)fVar3) return iVar1 - 1;
        fVar3 = fVar3 + fVar2 * param_1;
        if ((float)param_2 < (float)(s32)fVar3) break;
        fVar2 = fVar2 * param_1 * param_1;
        fVar3 = fVar3 + fVar2;
        iVar1 = iVar1 + 2;
        if (iVar1 == 100) return 99;
    }
    return iVar1;
}

// 0x7102bcc420
void FUN_7102bcc420(s64 param_1)
{
    s64 *plVar1;
    s64 lVar2;
    s64 *plVar3;
    s64 *plVar4;

    if (*(s32 *)(param_1 + 0x28) == 0 || *(s32 *)(param_1 + 0x28) == 7) return;
    lVar2 = *(s64 *)(param_1 + 0x10);
    if (lVar2 != 0) {
        *(u8 *)(lVar2 + 0x110) = 0;
        FUN_71025e9900(lVar2 + 0x108);
        if (*(s64 *)(param_1 + 0x10) != 0) {
            FUN_71025ee000(0, *(u64 *)(*(s64 *)(param_1 + 0x10) + 0xd8), 1);
        }
    }
    plVar3 = *(s64 **)(param_1 + 0x18);
    if (plVar3 != (s64 *)0x0) {
        if ((char)plVar3[8] != '\0') {
            plVar4 = (s64 *)plVar3[6];
            if (((plVar4 != (s64 *)0x0) && ((char)plVar4[2] != '\0')) &&
                (*(u8 *)(plVar4 + 2) = 0, (char)plVar4[10] != '\0')) {
                plVar1 = (s64 *)get_battle_object_from_id(*(u32 *)(*plVar4 + 8));
                (**(void (**)(s64 *, u32))(*(s64 *)plVar1 + 0x48))(plVar1, 0);
                *(u8 *)(plVar4 + 10) = 0;
            }
            (**(void (**)(s64 *))(*(s64 *)plVar3 + 0x30))(plVar3);
        }
        *(u8 *)(plVar3 + 8) = 0;
    }
    plVar3 = *(s64 **)(param_1 + 0x20);
    if (plVar3 != (s64 *)0x0) {
        if ((char)plVar3[8] != '\0') {
            plVar4 = (s64 *)plVar3[6];
            if (((plVar4 != (s64 *)0x0) && ((char)plVar4[2] != '\0')) &&
                (*(u8 *)(plVar4 + 2) = 0, (char)plVar4[10] != '\0')) {
                plVar1 = (s64 *)get_battle_object_from_id(*(u32 *)(*plVar4 + 8));
                (**(void (**)(s64 *, u32))(*(s64 *)plVar1 + 0x48))(plVar1, 0);
                *(u8 *)(plVar4 + 10) = 0;
            }
            (**(void (**)(s64 *))(*(s64 *)plVar3 + 0x30))(plVar3);
        }
        *(u8 *)(plVar3 + 8) = 0;
    }
    *(u32 *)(param_1 + 0x28) = 7;
}

// 0x7102eaf630
void FUN_7102eaf630(char *param_1)
{
    s64 *plVar1;
    s64 lVar2;

    if (*param_1 != '\0') return;
    plVar1 = *(s64 **)(*(s64 *)*(s64 **)(*(s64 *)(param_1 + 0x18) + 0x338) + 8);
    if (plVar1 != (s64 *)0x0) {
        (**(void (**)(s64 *, u32, u32))(*(s64 *)plVar1 + 0x58))(plVar1, 9, 0xffffffff);
    }
    lVar2 = *(s64 *)(param_1 + 0x40);
    if (lVar2 != 0) {
        *(u8 *)(lVar2 + 0x110) = 1;
        FUN_71025e9900(lVar2 + 0x108);
        lVar2 = *(s64 *)(param_1 + 0x40);
        if (lVar2 != 0) {
            if ((*(char *)(lVar2 + 0xe0) != '\0') && (*(s64 *)(lVar2 + 200) != 0)) {
                *(u16 *)(*(s64 *)(lVar2 + 200) + 0x30) = 0x101;
            }
            if (*(s64 *)(lVar2 + 0xd8) != 0) {
                *(u8 *)(*(s64 *)(lVar2 + 0xd8) + 0x21) = 1;
            }
            if (*(char *)(lVar2 + 0xe0) != '\0') {
                *(u8 *)(*(s64 *)(lVar2 + 0xb0) + 0x10) = 0;
            }
        }
    }
    lVar2 = *(s64 *)(param_1 + 0x48);
    if (lVar2 != 0) {
        *(u8 *)(lVar2 + 0x110) = 1;
        FUN_71025e9900(lVar2 + 0x108);
        lVar2 = *(s64 *)(param_1 + 0x48);
        if (lVar2 != 0) {
            if ((*(char *)(lVar2 + 0xe0) != '\0') && (*(s64 *)(lVar2 + 200) != 0)) {
                *(u16 *)(*(s64 *)(lVar2 + 200) + 0x30) = 0;
            }
            if (*(s64 *)(lVar2 + 0xd8) != 0) {
                *(u8 *)(*(s64 *)(lVar2 + 0xd8) + 0x21) = 0;
            }
            if (*(char *)(lVar2 + 0xe0) != '\0') {
                *(u8 *)(*(s64 *)(lVar2 + 0xb0) + 0x10) = 1;
            }
        }
    }
    FUN_710260f980(0x41700000, *(u64 *)(param_1 + 0x48), 1);
    param_1[0] = '\x01';
    param_1[1] = '\x01';
}

// 0x710329d9b0
u64 FUN_710329d9b0(s64 param_1, u64 param_2, s32 param_3)
{
    u32 *puVar1;
    s32 iVar2;
    char cVar3;
    s32 iVar4;
    u32 uVar5;
    u8 *pbVar6;
    char *pcVar7;
    s32 iVar8;
    u32 uVar9;
    s32 iVar10;
    u64 uVar11;
    u32 uVar12;
    u64 uVar13;
    u32 uVar14;
    s64 lVar15;
    char *pcVar16;
    u64 local_138;
    u8 local_130[64];
    u32 local_f0;
    s32 local_ec;
    u8 local_e8[64];
    u64 local_a8;
    u8 local_a0[64];

    if (4 < (u32)(param_3 - 1)) return 0;
    local_130[0] = 0;
    local_138 = 0;
    FUN_710062dc20(&local_138, "pack_%d");
    if ((param_2 >> 0x38 == 0xa2) && ((param_2 & 0xffffffffff) != 0)) {
        lVar15 = *(s64 *)(param_1 + 8);
        pcVar16 = *(char **)(lVar15 + 0x20);
        cVar3 = *pcVar16;
        if ((cVar3 == '\f') && (iVar10 = *(s32 *)(pcVar16 + 1) + -1, 0 < *(s32 *)(pcVar16 + 1))) {
            uVar11 = *(u64 *)(lVar15 + 0x48) & 0xffffffffff;
            iVar8 = 0;
            pbVar6 = &DAT_7104741dbb;
            do {
                iVar2 = iVar10 + iVar8;
                if (iVar2 < 0) iVar2 = iVar2 + 1;
                iVar2 = iVar2 >> 1;
                puVar1 = (u32 *)(*(s64 *)(*(s64 *)(lVar15 + 0x18) + 0x28) + (s64)*(s32 *)(pcVar16 + 5) + (s64)iVar2 * 8);
                uVar13 = *(u64 *)(*(s64 *)(*(s64 *)(lVar15 + 0x18) + 0x20) + (u64)*puVar1 * 8);
                if (uVar13 == uVar11) {
                    uVar14 = puVar1[1];
                    if ((s32)uVar14 < 0) goto LAB_710329dad0;
                    pbVar6 = (u8 *)(pcVar16 + (s32)uVar14);
                    break;
                }
                iVar4 = iVar2 + -1;
                if (uVar13 <= uVar11) { iVar8 = iVar2 + 1; iVar4 = iVar10; }
                iVar10 = iVar4;
            } while (iVar8 <= iVar10);
        } else {
LAB_710329dad0:
            pbVar6 = &DAT_7104741dbb;
        }
        if ((u32)(*pbVar6 - 0xb) < 2) {
            uVar11 = param_2 >> 0x28 & 0xffff;
            uVar5 = (u32)uVar11;
            if ((*(u32 *)(pbVar6 + 1) <= uVar5) ||
                (uVar11 = FUN_7103269900(lVar15, uVar11), ((uVar11 ^ param_2) & 0xffffffffff) != 0))
                goto LAB_710329db10;
        } else {
LAB_710329db10:
            uVar5 = FUN_7103269fd0(lVar15, param_2 & 0xffffffffff);
        }
        uVar14 = uVar5;
        if (cVar3 != '\f') goto LAB_710329dba8;
LAB_710329db28:
        uVar5 = uVar14;
        iVar10 = *(s32 *)(pcVar16 + 1) + -1;
        if (*(s32 *)(pcVar16 + 1) < 1) goto LAB_710329dba8;
        uVar11 = *(u64 *)(lVar15 + 0x48) & 0xffffffffff;
        iVar8 = 0;
        pbVar6 = &DAT_7104741dbb;
        do {
            iVar2 = iVar10 + iVar8;
            if (iVar2 < 0) iVar2 = iVar2 + 1;
            iVar2 = iVar2 >> 1;
            puVar1 = (u32 *)(*(s64 *)(*(s64 *)(lVar15 + 0x18) + 0x28) + (s64)*(s32 *)(pcVar16 + 5) + (s64)iVar2 * 8);
            uVar13 = *(u64 *)(*(s64 *)(*(s64 *)(lVar15 + 0x18) + 0x20) + (u64)*puVar1 * 8);
            if (uVar13 == uVar11) {
                uVar14 = puVar1[1];
                if ((s32)uVar14 < 0) goto LAB_710329dba8;
                pbVar6 = (u8 *)(pcVar16 + (s32)uVar14);
                break;
            }
            iVar4 = iVar2 + -1;
            if (uVar13 <= uVar11) { iVar8 = iVar2 + 1; iVar4 = iVar10; }
            iVar10 = iVar4;
        } while (iVar8 <= iVar10);
    } else {
        lVar15 = *(s64 *)(param_1 + 8);
        pcVar16 = *(char **)(lVar15 + 0x20);
        uVar5 = 0xffffffff;
        uVar14 = 0xffffffff;
        if (*pcVar16 == '\f') goto LAB_710329db28;
LAB_710329dba8:
        pbVar6 = &DAT_7104741dbb;
    }
    uVar14 = 0x811c9dc5;
    if (((u32)(*pbVar6 - 0xb) < 2) && (uVar5 < *(u32 *)(pbVar6 + 1))) {
        local_a0[0] = 0;
        local_a8 = 0;
        FUN_710329ad30(&local_f0, param_1, param_2);
        FUN_710062dc20(&local_a8, "shop_skill_point_%s", local_e8);
        local_f0 = 0;
        for (uVar11 = 0; local_a0[uVar11] != 0; uVar11 = uVar11 + 2) {
            local_e8[uVar11] = local_a0[uVar11];
            if (0x3e < (s32)uVar11 + 1U) { uVar11 = (u64)((s32)uVar11 + 1); break; }
            if (local_a0[uVar11 + 1] == 0) { uVar11 = uVar11 + 1; break; }
            local_e8[uVar11 + 1] = local_a0[uVar11 + 1];
        }
        local_e8[uVar11 & 0xffffffff] = 0;
        local_ec = (s32)uVar11;
        uVar5 = (u32)local_e8[0];
        local_f0 = uVar14;
        if (uVar5 != 0) {
            u8 *pbVar6b = local_e8;
            do {
                pbVar6b = pbVar6b + 1;
                local_f0 = local_f0 * 0x89 ^ uVar5;
                uVar5 = (u32)*pbVar6b;
            } while (uVar5 != 0);
        }
        if (local_ec == 0) {
            uVar11 = 0;
        } else {
            u8 *pbVar6c = local_e8;
            uVar5 = 0xffffffff;
            while (true) {
                pbVar6c = pbVar6c + 1;
                uVar9 = (u32)local_e8[0];
                uVar12 = uVar9 + 0x20;
                if (0x19 < (u32)(uVar9 - 0x41)) uVar12 = uVar9;
                uVar5 = DAT_7104753084[(uVar12 ^ uVar5) & 0xff] ^ uVar5 >> 8;
                if (local_e8 + (uVar11 & 0xffffffff) <= pbVar6c) break;
                local_e8[0] = *pbVar6c;
            }
            uVar11 = (u64)~uVar5;
        }
        pcVar16 = *(char **)(*(s64 *)(param_1 + 8) + 0x20);
        if ((*pcVar16 == '\f') && (iVar10 = *(s32 *)(pcVar16 + 1) + -1, 0 < *(s32 *)(pcVar16 + 1))) {
            s64 lVar15b = *(s64 *)(*(s64 *)(param_1 + 8) + 0x18);
            uVar11 = uVar11 | ((s64)local_ec & 0xffULL) << 0x20;
            iVar8 = 0;
            pcVar7 = "";
            do {
                iVar2 = iVar10 + iVar8;
                if (iVar2 < 0) iVar2 = iVar2 + 1;
                iVar2 = iVar2 >> 1;
                puVar1 = (u32 *)(*(s64 *)(lVar15b + 0x28) + (s64)*(s32 *)(pcVar16 + 5) + (s64)iVar2 * 8);
                uVar13 = *(u64 *)(*(s64 *)(lVar15b + 0x20) + (u64)*puVar1 * 8);
                if (uVar13 == uVar11) {
                    uVar5 = puVar1[1];
                    if ((s32)uVar5 < 0) goto LAB_710329dd90;
                    pcVar7 = pcVar16 + (s32)uVar5;
                    goto LAB_710329dd9c;
                }
                iVar4 = iVar2 + -1;
                if (uVar13 <= uVar11) { iVar8 = iVar2 + 1; iVar4 = iVar10; }
                iVar10 = iVar4;
            } while (iVar8 <= iVar10);
            goto LAB_710329dd9c;
        }
    }
LAB_710329dd90:
    pcVar7 = "";
LAB_710329dd9c:
    if ((*pcVar7 == '\v') && (0 < *(s32 *)(pcVar7 + 1))) {
        pcVar7 = pcVar7 + *(s32 *)(pcVar7 + 5);
    } else {
        pcVar7 = "";
    }
    for (uVar11 = 0; local_130[uVar11] != 0; uVar11 = uVar11 + 2) {
        local_a0[uVar11] = local_130[uVar11];
        if (0x3e < (s32)uVar11 + 1U) { uVar11 = (u64)((s32)uVar11 + 1); break; }
        if (local_130[uVar11 + 1] == 0) { uVar11 = uVar11 + 1; break; }
        local_a0[uVar11 + 1] = local_130[uVar11 + 1];
    }
    local_a0[uVar11 & 0xffffffff] = 0;
    s32 iVar10b = (s32)uVar11;
    local_a8 = uVar11 << 0x20;
    uVar5 = (u32)local_a0[0];
    if (uVar5 != 0) {
        u8 *pbVar6d = local_a0;
        do {
            pbVar6d = pbVar6d + 1;
            uVar14 = uVar14 * 0x89 ^ uVar5;
            uVar5 = (u32)*pbVar6d;
        } while (uVar5 != 0);
    }
    local_a8 = CONCAT44(iVar10b, uVar14);
    if (iVar10b == 0) {
        uVar11 = 0;
    } else {
        u8 *pbVar6e = local_a0;
        uVar14 = 0xffffffff;
        while (true) {
            pbVar6e = pbVar6e + 1;
            uVar12 = (u32)local_a0[0];
            uVar5 = uVar12 + 0x20;
            if (0x19 < (u32)(uVar12 - 0x41)) uVar5 = uVar12;
            uVar14 = DAT_7104753084[(uVar5 ^ uVar14) & 0xff] ^ uVar14 >> 8;
            if (local_a0 + (uVar11 & 0xffffffff) <= pbVar6e) break;
            local_a0[0] = *pbVar6e;
        }
        uVar11 = (u64)~uVar14;
    }
    if ((*pcVar7 == '\f') && (iVar8 = *(s32 *)(pcVar7 + 1) + -1, 0 < *(s32 *)(pcVar7 + 1))) {
        uVar11 = uVar11 | ((s64)iVar10b & 0xffULL) << 0x20;
        s32 iVar10c = 0;
        pcVar16 = "";
        s64 lVar15f = 0;  // placeholder
        do {
            iVar2 = iVar8 + iVar10c;
            if (iVar2 < 0) iVar2 = iVar2 + 1;
            iVar2 = iVar2 >> 1;
            puVar1 = (u32 *)(*(s64 *)(lVar15f + 0x28) + (s64)*(s32 *)(pcVar7 + 5) + (s64)iVar2 * 8);
            uVar13 = *(u64 *)(*(s64 *)(lVar15f + 0x20) + (u64)*puVar1 * 8);
            if (uVar13 == uVar11) {
                uVar14 = puVar1[1];
                if ((s32)uVar14 < 0) goto LAB_710329df60;
                pcVar16 = pcVar7 + (s32)uVar14;
                break;
            }
            iVar4 = iVar2 + -1;
            if (uVar13 <= uVar11) { iVar10c = iVar2 + 1; iVar4 = iVar8; }
            iVar8 = iVar4;
        } while (iVar10c <= iVar8);
    } else {
LAB_710329df60:
        pcVar16 = "";
    }
    switch (*pcVar16) {
    case '\x01':
    case '\x03': return (u64)(u8)pcVar16[1];
    case '\x02': return (u64)(s64)pcVar16[1];
    case '\x04': return (u64)(s64)*(s16 *)(pcVar16 + 1);
    case '\x05': return (u64)*(u16 *)(pcVar16 + 1);
    case '\x06':
    case '\x07': return (u64)*(u32 *)(pcVar16 + 1);
    default:     return 0;
    }
}

// 0x71035adcb0
void FUN_71035adcb0(s64 *param_1)
{
    s64 lVar1;
    s64 lVar2;
    s64 lVar3;
    u64 uVar4;
    u64 uVar5;
    float fVar6;
    float fVar7;
    float fVar8;
    float fVar9;
    s64 lVar10;
    s64 lVar11;
    s64 lVar12;
    u64 uVar13;
    float fVar14;
    u64 uVar15;
    float fVar16;
    float fVar17;

    fVar9 = DAT_7104472684;
    fVar8 = DAT_7104472464;
    fVar7 = DAT_7104471d58;
    fVar6 = DAT_710447146c;
    uVar5 = _UNK_7104464fb8;
    uVar4 = _DAT_7104464fb0;
    if ((char)param_1[3] != '\0') return;
    lVar2 = *param_1;
    lVar3 = param_1[1];
    if (lVar2 != lVar3) {
        lVar10 = 0;
        do {
            lVar1 = lVar2 + lVar10;
            lVar10 = lVar10 + 0xa0;
            lVar11 = *(s64 *)(lVar1 + 8);
            uVar15 = *(u64 *)(lVar11 + 0xa8);
            uVar13 = *(u64 *)(lVar11 + 0xb0);
            *(u64 *)(lVar1 + 0x48) = *(u64 *)(lVar11 + 0xa0);
            *(u64 *)(lVar1 + 0x50) = uVar15;
            *(u64 *)(lVar1 + 0x58) = uVar13;
            uVar15 = *(u64 *)(lVar11 + 0xd0);
            lVar12 = *(s64 *)(lVar1 + 0x28);
            *(u64 *)(lVar1 + 0x68) = *(u64 *)(lVar11 + 0xd8);
            *(u64 *)(lVar1 + 0x60) = uVar15;
            fVar14 = *(float *)(lVar1 + 0x50) / fVar7;
            *(u8 *)(lVar1 + 0x90) = *(u8 *)(lVar11 + 0xe0);
            uVar15 = *(u64 *)(lVar11 + 0xc0);
            *(u64 *)(lVar1 + 0x70) = *(u64 *)(lVar11 + 0xb8);
            *(u64 *)(lVar1 + 0x78) = uVar15;
            fVar16 = fVar14 * fVar8;
            fVar17 = fVar14 * fVar9;
            uVar15 = *(u64 *)(lVar12 + 0xc0);
            *(u64 *)(lVar1 + 0x80) = *(u64 *)(lVar12 + 0xb8);
            *(u64 *)(lVar1 + 0x88) = uVar15;
            *(u8 *)(lVar11 + 0xe0) = 0;
            *(u64 *)(lVar11 + 0xd8) = uVar5;
            *(u64 *)(lVar11 + 0xd0) = uVar4;
            *(u64 *)(lVar11 + 0xb8) = 0;
            *(float *)(lVar11 + 0xa8) = fVar16;
            *(float *)(lVar11 + 0xac) = fVar17;
            *(float *)(lVar11 + 0xc0) = fVar16;
            *(float *)(lVar11 + 0xc4) = fVar17;
            *(float *)(lVar12 + 0xb8) = fVar16;
            *(u32 *)(lVar12 + 0xbc) = 0;
            *(float *)(lVar12 + 0xc0) = fVar14 * fVar6;
            *(float *)(lVar12 + 0xc4) = fVar17;
        } while (lVar3 - lVar2 != lVar10);
    }
    *(u8 *)(param_1 + 3) = 1;
}

// 0x71036416f0
void FUN_71036416f0(s64 param_1)
{
    u64 uVar1;
    s64 lVar2;
    u64 *puVar3;

    // Stack-allocated lookup key entries (each 24 bytes: 1 type byte + up to 23 string bytes)
    // Entry layout: tag byte, then string data inline
    u8 entry_d0[24];  // DOF_BB_DOWN_SAMPLE0
    u8 entry_b8[24];  // DOF_BB_BOKEH0 (assembled from _DAT_71043fedff + s_B_BOKEH0)
    u8 entry_a0[24];  // DOF_BB_MERGE0
    u8 entry_88[24];  // DOF_BB_DOWN_SAMPLE1
    u8 entry_70[24];  // DOF_BB_BOKEH1
    u8 entry_58[16];  // DOF_BB_MERGE1
    u8 entry_48[8];   // null entry

    // Output buffer for FUN_71038647e0 results
    u8 auStack_f0[8];
    s64 local_e8;
    s64 *local_e0;
    s64 local_d8;

    if (*(char *)(param_1 + 0xe8) != '\0') return;

    // Build entry_d0: type=0x26, "DOF_BB_DOWN_SAMPLE0"
    entry_d0[0] = 0x26;
    *(u64 *)(entry_d0 + 1) = *(u64 *)(s_DOF_BB_DOWN_SAMPLE0_710428f363 + 0);
    *(u64 *)(entry_d0 + 9) = *(u64 *)(s_DOF_BB_DOWN_SAMPLE0_710428f363 + 8);
    *(u32 *)(entry_d0 + 17) = 0x0030454cU;  // "LE0\0"
    entry_d0[21] = 0; entry_d0[22] = 0; entry_d0[23] = 0;

    // Build entry_b8: type=0x1a, "DOF_BB_BOKEH0" (7 bytes from _DAT_71043fedff + rest from s_B_BOKEH0)
    entry_b8[0] = 0x1a;
    *(u64 *)(entry_b8 + 1) = _DAT_71043fedff;
    *(u16 *)(entry_b8 + 8) = *(u16 *)s_B_BOKEH0_71043fee04;
    entry_b8[10] = SUB31(*(u32 *)s_B_BOKEH0_71043fee04, 2);
    *(u64 *)(entry_b8 + 11) = *(u64 *)(s_B_BOKEH0_71043fee04 + 3);
    entry_b8[11+5] = 0; entry_b8[17] = 0; entry_b8[18] = 0; entry_b8[19] = 0;
    entry_b8[20] = 0; entry_b8[21] = 0; entry_b8[22] = 0; entry_b8[23] = 0;

    // Build entry_a0: type=0x1a, "DOF_BB_MERGE0"
    entry_a0[0] = 0x1a;
    *(u64 *)(entry_a0 + 1) = *(u64 *)(s_DOF_BB_MERGE0_7104430a83 + 0);  // 5+3 bytes
    *(u16 *)(entry_a0 + 6) = *(u16 *)(s_DOF_BB_MERGE0_7104430a83 + 5);
    entry_a0[8] = SUB31(*(u32 *)(s_DOF_BB_MERGE0_7104430a83 + 5), 2);
    *(u64 *)(entry_a0 + 9) = *(u64 *)(s_DOF_BB_MERGE0_7104430a83 + 8);
    entry_a0[9+5] = 0; entry_a0[15] = 0; entry_a0[16] = 0;
    entry_a0[17] = 0; entry_a0[18] = 0; entry_a0[19] = 0;
    entry_a0[20] = 0; entry_a0[21] = 0; entry_a0[22] = 0; entry_a0[23] = 0;

    // Build entry_88: type=0x26, "DOF_BB_DOWN_SAMPLE1"
    entry_88[0] = 0x26;
    *(u64 *)(entry_88 + 1) = *(u64 *)(s_DOF_BB_DOWN_SAMPLE1_71044412aa + 0);
    *(u64 *)(entry_88 + 9) = *(u64 *)(s_DOF_BB_DOWN_SAMPLE1_71044412aa + 8);
    *(u16 *)(entry_88 + 17) = 0x454c;  // "LE"
    entry_88[19] = 0x31;               // '1'
    entry_88[20] = 0; entry_88[21] = 0; entry_88[22] = 0; entry_88[23] = 0;

    // Build entry_70: type=0x1a, "DOF_BB_BOKEH1"
    entry_70[0] = 0x1a;
    *(u64 *)(entry_70 + 1) = *(u64 *)(s_DOF_BB_BOKEH1_710439ab70 + 0);
    *(u16 *)(entry_70 + 6) = *(u16 *)(s_DOF_BB_BOKEH1_710439ab70 + 5);
    entry_70[8] = SUB31(*(u32 *)(s_DOF_BB_BOKEH1_710439ab70 + 5), 2);
    *(u64 *)(entry_70 + 9) = *(u64 *)(s_DOF_BB_BOKEH1_710439ab70 + 8);
    entry_70[14] = 0; entry_70[15] = 0; entry_70[16] = 0;
    entry_70[17] = 0; entry_70[18] = 0; entry_70[19] = 0;
    entry_70[20] = 0; entry_70[21] = 0; entry_70[22] = 0; entry_70[23] = 0;

    // Build entry_58: type=0x1a, "DOF_BB_MERGE1"
    entry_58[0] = 0x1a;
    *(u64 *)(entry_58 + 1) = *(u64 *)(s_DOF_BB_MERGE1_710437a0ae + 0);
    *(u16 *)(entry_58 + 6) = *(u16 *)(s_DOF_BB_MERGE1_710437a0ae + 5);
    entry_58[8] = SUB31(*(u32 *)(s_DOF_BB_MERGE1_710437a0ae + 5), 2);
    entry_58[9] = 0; entry_58[10] = 0; entry_58[11] = 0;
    entry_58[12] = 0; entry_58[13] = 0; entry_58[14] = 0; entry_58[15] = 0;

    // Build entry_48: null
    entry_48[0] = 0; entry_48[1] = 0; entry_48[2] = 0; entry_48[3] = 0;
    entry_48[4] = 0; entry_48[5] = 0; entry_48[6] = 0; entry_48[7] = 0;

#define DO_LOOKUP(entry, off_a, off_b, off_c) \
    lVar2 = *(s64 *)(DAT_7105334480 + 0x68); \
    if ((*(s64 **)(lVar2 + 0x20) == (s64 *)0x0) || \
        (**(s64 **)(lVar2 + 0x20) != *(s64 *)(lVar2 + 0x28))) { uVar1 = 0; } \
    else { uVar1 = *(u64 *)(lVar2 + 0x18); } \
    FUN_71038647e0(auStack_f0, uVar1, entry); \
    memcpy(&local_e8, auStack_f0 + 8, 8); \
    memcpy(&local_e0, auStack_f0 + 16, 8); \
    memcpy(&local_d8, auStack_f0 + 24, 8); \
    if ((local_e0 == (s64 *)0x0) || (*local_e0 != local_d8)) { \
        *(u64 *)(param_1 + (off_a)) = 0; \
        uVar1 = 0; \
        *(u64 *)(param_1 + (off_b)) = 0; \
    } else { \
        *(s64 *)(param_1 + (off_a)) = local_e8; \
        if (local_e8 == 0) { uVar1 = 0; *(u64 *)(param_1 + (off_b)) = 0; } \
        else { puVar3 = *(u64 **)(local_e8 + 8); *(u64 **)(param_1 + (off_b)) = puVar3; uVar1 = *puVar3; } \
    } \
    *(u64 *)(param_1 + (off_c)) = uVar1;

    DO_LOOKUP(entry_d0, 0x30, 0x38, 0x40)
    DO_LOOKUP(entry_b8, 0x50, 0x58, 0x60)
    DO_LOOKUP(entry_a0, 0x70, 0x78, 0x80)
    DO_LOOKUP(entry_88, 0x90, 0x98, 0xa0)
    DO_LOOKUP(entry_70, 0xb0, 0xb8, 0xc0)
    DO_LOOKUP(entry_58, 0xd0, 0xd8, 0xe0)
#undef DO_LOOKUP

    if ((*(s64 **)(param_1 + 0x38) != (s64 *)0x0) && (**(s64 **)(param_1 + 0x38) == *(s64 *)(param_1 + 0x40)))
        *(u8 *)(*(s64 *)(param_1 + 0x30) + 0xf0) = 0;
    if ((*(s64 **)(param_1 + 0x58) != (s64 *)0x0) && (**(s64 **)(param_1 + 0x58) == *(s64 *)(param_1 + 0x60)))
        *(u8 *)(*(s64 *)(param_1 + 0x50) + 0xf0) = 0;
    if ((*(s64 **)(param_1 + 0x78) != (s64 *)0x0) && (**(s64 **)(param_1 + 0x78) == *(s64 *)(param_1 + 0x80)))
        *(u8 *)(*(s64 *)(param_1 + 0x70) + 0xf0) = 0;
    if ((*(s64 **)(param_1 + 0x98) != (s64 *)0x0) && (**(s64 **)(param_1 + 0x98) == *(s64 *)(param_1 + 0xa0)))
        *(u8 *)(*(s64 *)(param_1 + 0x90) + 0xf0) = 0;
    if ((*(s64 **)(param_1 + 0xb8) != (s64 *)0x0) && (**(s64 **)(param_1 + 0xb8) == *(s64 *)(param_1 + 0xc0)))
        *(u8 *)(*(s64 *)(param_1 + 0xb0) + 0xf0) = 0;
    if ((*(s64 **)(param_1 + 0xd8) != (s64 *)0x0) && (**(s64 **)(param_1 + 0xd8) == *(s64 *)(param_1 + 0xe0)))
        *(u8 *)(*(s64 *)(param_1 + 0xd0) + 0xf0) = 0;

    puVar3 = (u64 *)**(s64 **)(DAT_7105336ce8 + 8);
    *puVar3 = PTR_ConstantZero_71052a7a80[0];
    puVar3[1] = PTR_ConstantZero_71052a7a80[1];
    puVar3[4] = 0x3af2b9d63a888889ULL;
    puVar3[5] = 0;
    *(u8 *)(param_1 + 0xe8) = 1;
}

// 0x710375f650
void FUN_710375f650(s64 param_1)
{
    s64 *plVar1;
    u64 uVar2;
    s64 lVar3;
    s64 lVar4;
    s32 iVar5;
    u8 *puVar6;
    u64 *puVar7;
    u32 *puVar8;
    u16 *puVar9;

    if (*(char *)(*(s64 *)(param_1 + 0x1f8) + 0x1f39) != '\0') return;

    *(u64 *)(param_1 + 0x220) = *(u64 *)(param_1 + 0x218);
    *(u64 *)(param_1 + 0x250) = *(u64 *)(param_1 + 0x248);
    *(u64 *)(param_1 + 0x280) = *(u64 *)(param_1 + 0x278);
    *(u64 *)(param_1 + 0x298) = *(u64 *)(param_1 + 0x290);
    *(u64 *)(param_1 + 0x2b0) = *(u64 *)(param_1 + 0x2a8);
    *(u64 *)(param_1 + 0x2c8) = *(u64 *)(param_1 + 0x2c0);
    *(u64 *)(param_1 + 0x2e0) = *(u64 *)(param_1 + 0x2d8);
    *(u64 *)(param_1 + 0x2f8) = *(u64 *)(param_1 + 0x2f0);
    *(u64 *)(param_1 + 0x310) = *(u64 *)(param_1 + 0x308);
    *(u64 *)(param_1 + 0x328) = *(u64 *)(param_1 + 800);
    *(u64 *)(param_1 + 0x340) = *(u64 *)(param_1 + 0x338);
    *(u64 *)(param_1 + 0x358) = *(u64 *)(param_1 + 0x350);
    *(u64 *)(param_1 + 0x370) = *(u64 *)(param_1 + 0x368);
    *(u64 *)(param_1 + 0x388) = *(u64 *)(param_1 + 0x380);
    *(u64 *)(param_1 + 0x3a0) = *(u64 *)(param_1 + 0x398);
    *(u64 *)(param_1 + 0x3b8) = *(u64 *)(param_1 + 0x3b0);
    *(u64 *)(param_1 + 0x3d0) = *(u64 *)(param_1 + 0x3c8);
    *(u64 *)(param_1 + 1000) = *(u64 *)(param_1 + 0x3e0);
    *(u64 *)(param_1 + 0x400) = *(u64 *)(param_1 + 0x3f8);
    *(u64 *)(param_1 + 0x418) = *(u64 *)(param_1 + 0x410);
    *(u64 *)(param_1 + 0x430) = *(u64 *)(param_1 + 0x428);
    *(u64 *)(param_1 + 0x448) = *(u64 *)(param_1 + 0x440);
    *(u64 *)(param_1 + 0x460) = *(u64 *)(param_1 + 0x458);
    *(u64 *)(param_1 + 0x478) = *(u64 *)(param_1 + 0x470);
    *(u64 *)(param_1 + 0x490) = *(u64 *)(param_1 + 0x488);
    *(u64 *)(param_1 + 0x4a8) = *(u64 *)(param_1 + 0x4a0);
    *(u64 *)(param_1 + 0x4c0) = *(u64 *)(param_1 + 0x4b8);
    *(u64 *)(param_1 + 0x238) = *(u64 *)(param_1 + 0x230);
    *(u64 *)(param_1 + 0x268) = *(u64 *)(param_1 + 0x260);
    *(u64 *)(param_1 + 0x4d8) = *(u64 *)(param_1 + 0x4d0);
    *(u64 *)(param_1 + 0x4f0) = *(u64 *)(param_1 + 0x4e8);
    lVar4 = *(s64 *)(param_1 + 0x1f8);
    *(u64 *)(param_1 + 0x508) = *(u64 *)(param_1 + 0x500);
    lVar3 = *(s64 *)(lVar4 + 0x1f30);
    if (lVar3 != 0) {
        if (0 < *(s32 *)(lVar3 + 0x10)) {
            FUN_710354c720(*(u32 *)(DAT_7105332f58[*(u32 *)(lVar3 + 0x14)] + 0x10), lVar3 + 0x10);
        }
        *(u64 *)(lVar4 + 0x1f30) = 0;
    }
    FUN_71000807c0(lVar4 + 0x68);
    *(u32 *)(lVar4 + 0x1c34) = 0;
    *(u8 *)(lVar4 + 0x1c38) = 0;
    lVar4 = *(s64 *)(param_1 + 0x208);
    lVar3 = *(s64 *)(lVar4 + 0x1f30);
    if (lVar3 != 0) {
        if (0 < *(s32 *)(lVar3 + 0x10)) {
            FUN_710354c720(*(u32 *)(DAT_7105332f58[*(u32 *)(lVar3 + 0x14)] + 0x10), lVar3 + 0x10);
        }
        *(u64 *)(lVar4 + 0x1f30) = 0;
    }
    plVar1 = (s64 *)(param_1 + 0x1f8);
    FUN_71000807c0(lVar4 + 0x68);
    *(u32 *)(lVar4 + 0x1c34) = 0;
    *(u8 *)(lVar4 + 0x1c38) = 0;
    FUN_710007cbe0(param_1, *(u32 *)(param_1 + 0x214));
    puVar6 = (u8 *)(param_1 + 0x30);
    puVar7 = (u64 *)(param_1 + 0x10);
    puVar8 = (u32 *)(param_1 + 0x18);
    puVar9 = (u16 *)(param_1 + 0x32);
    FUN_710007f500(*puVar7, *(u32 *)(param_1 + 0x214), *puVar8, *puVar9, 0, *puVar6);
    FUN_710007f500(*puVar7, 0x20, *puVar8, *puVar9, 0, *puVar6);
    FUN_710007f500(*puVar7, 0x3f, *puVar8, *puVar9, 0, *puVar6);
    FUN_710007cbe0(param_1 + 0xf8, 0x3f);
    FUN_710007f500(*(u64 *)(param_1 + 0x108), 0x3f, *(u32 *)(param_1 + 0x110),
                   *(u16 *)(param_1 + 0x12a), 0, *(u8 *)(param_1 + 0x128));
    iVar5 = *(s32 *)(param_1 + 0x210);
    if (iVar5 < 0x81) {
        if (iVar5 == 0x80) {
            FUN_7100080160(*plVar1 + 0x68, 8);
            FUN_7100080160(*plVar1 + 0x68, 8);
            FUN_7100080160(*plVar1 + 0x68, 8);
            FUN_7100080160(*plVar1 + 0x68, 8);
            FUN_7100080160(*plVar1 + 0x68, 8);
            lVar3 = *plVar1; uVar2 = 8;
            goto LAB_710375f968;
        }
        if (iVar5 == 0x40) {
            for (s32 i = 0; i < 11; i++) FUN_7100080160(*plVar1 + 0x68, 7);
            lVar3 = *plVar1 + 0x68; uVar2 = 7;
            goto LAB_710375f988;
        }
        if (iVar5 == 0x20) {
            FUN_7100080160(*plVar1 + 0x68, 6);
            lVar3 = *plVar1 + 0x68; uVar2 = 6;
            goto LAB_710375f988;
        }
    } else {
        lVar3 = *plVar1; uVar2 = 9;
LAB_710375f968:
        FUN_7100080160(lVar3 + 0x68, uVar2);
        FUN_7100080160(*plVar1 + 0x68, 8);
        lVar3 = *plVar1 + 0x68; uVar2 = 8;
LAB_710375f988:
        FUN_7100080160(lVar3, uVar2);
        iVar5 = *(s32 *)(param_1 + 0x210);
        if (0x80 < iVar5) goto LAB_7103760154;
    }
    iVar5 = -(s32)(iVar5 == 0x80);
    FUN_710007f500(*puVar7, 0x30, *puVar8, *puVar9, iVar5, *puVar6);
    FUN_710007f500(*puVar7, 0x31, *puVar8, *puVar9, iVar5, *puVar6);
    FUN_710007f500(*puVar7, 0x32, *puVar8, *puVar9, iVar5, *puVar6);
    FUN_710007f500(*puVar7, 0x33, *puVar8, *puVar9, iVar5, *puVar6);
    FUN_710007f500(*puVar7, 0x34, *puVar8, *puVar9, iVar5, *puVar6);
    FUN_710007f500(*puVar7, 0x35, *puVar8, *puVar9, iVar5, *puVar6);
    FUN_710007f500(*puVar7, 0x36, *puVar8, *puVar9, iVar5, *puVar6);
    FUN_710007f500(*puVar7, 0x37, *puVar8, *puVar9, iVar5, *puVar6);
    FUN_710007f500(*puVar7, 0x38, *puVar8, *puVar9, iVar5, *puVar6);
    FUN_710007f500(*puVar7, 0x39, *puVar8, *puVar9, iVar5, *puVar6);
    for (iVar5 = 0x41; iVar5 != 0x5b; iVar5++)
        FUN_710007f500(*puVar7, iVar5, *puVar8, *puVar9, 0xffffffff, *puVar6);
    for (iVar5 = 0x61; iVar5 != 0x7b; iVar5++)
        FUN_710007f500(*puVar7, iVar5, *puVar8, *puVar9, 0xffffffff, *puVar6);
    FUN_710007f500(*puVar7, 0xe121, *puVar8, *puVar9, 0xffffffff, *puVar6);
    FUN_710007f500(*puVar7, 0xe122, *puVar8, *puVar9, 0xffffffff, *puVar6);
    FUN_710007f500(*puVar7, 0xe123, *puVar8, *puVar9, 0xffffffff, *puVar6);
    FUN_710007f500(*puVar7, 0xe124, *puVar8, *puVar9, 0xffffffff, *puVar6);
    FUN_710007f500(*puVar7, 0xe125, *puVar8, *puVar9, 0xffffffff, *puVar6);
    FUN_710007f500(*puVar7, 0xe126, *puVar8, *puVar9, 0xffffffff, *puVar6);
    FUN_710007f500(*puVar7, 0xe127, *puVar8, *puVar9, 0xffffffff, *puVar6);
    FUN_710007f500(*puVar7, 0xe128, *puVar8, *puVar9, 0xffffffff, *puVar6);
    FUN_710007f500(*puVar7, 0xe129, *puVar8, *puVar9, 0xffffffff, *puVar6);
    FUN_710007f500(*puVar7, 0xe12a, *puVar8, *puVar9, 0xffffffff, *puVar6);
    FUN_710007f500(*puVar7, 0xe12b, *puVar8, *puVar9, 0xffffffff, *puVar6);
    FUN_710007f500(*puVar7, 0xe12c, *puVar8, *puVar9, 0xffffffff, *puVar6);
    for (iVar5 = 0; iVar5 != 0x17; iVar5++)
        FUN_710007f500(*puVar7, iVar5 + 0xe0a0, *puVar8, *puVar9, 0xffffffff, *puVar6);
    FUN_710007f500(*puVar7, 0xe0c0, *puVar8, *puVar9, 0xffffffff, *puVar6);
    FUN_710007f500(*puVar7, 0xe0c1, *puVar8, *puVar9, 0xffffffff, *puVar6);
    FUN_710007f500(*puVar7, 0xe0c2, *puVar8, *puVar9, 0xffffffff, *puVar6);
    FUN_710007f500(*puVar7, 0xe0c3, *puVar8, *puVar9, 0xffffffff, *puVar6);
    FUN_710007f500(*puVar7, 0xe0c4, *puVar8, *puVar9, 0xffffffff, *puVar6);
    FUN_710007f500(*puVar7, 0xe0c5, *puVar8, *puVar9, 0xffffffff, *puVar6);
    FUN_710007f500(*puVar7, 0xe0e0, *puVar8, *puVar9, 0xffffffff, *puVar6);
    FUN_710007f500(*puVar7, 0xe0e1, *puVar8, *puVar9, 0xffffffff, *puVar6);
    FUN_710007f500(*puVar7, 0xe0e2, *puVar8, *puVar9, 0xffffffff, *puVar6);
    FUN_710007f500(*puVar7, 0xe0e3, *puVar8, *puVar9, 0xffffffff, *puVar6);
    FUN_710007f500(*puVar7, 0xe0e4, *puVar8, *puVar9, 0xffffffff, *puVar6);
    FUN_710007f500(*puVar7, 0xe0e5, *puVar8, *puVar9, 0xffffffff, *puVar6);
    FUN_710007f500(*puVar7, 0xe0e6, *puVar8, *puVar9, 0xffffffff, *puVar6);
    FUN_710007f500(*puVar7, 0xe0e7, *puVar8, *puVar9, 0xffffffff, *puVar6);
    FUN_710007f500(*puVar7, 0xe0e8, *puVar8, *puVar9, 0xffffffff, *puVar6);
    FUN_710007f500(*puVar7, 0xe0e9, *puVar8, *puVar9, 0xffffffff, *puVar6);
    FUN_710007f500(*puVar7, 0xe0ea, *puVar8, *puVar9, 0xffffffff, *puVar6);
    FUN_710007f500(*puVar7, 0xe0eb, *puVar8, *puVar9, 0xffffffff, *puVar6);
    FUN_710007f500(*puVar7, 0xe0ec, *puVar8, *puVar9, 0xffffffff, *puVar6);
    FUN_710007f500(*puVar7, 0xe0ed, *puVar8, *puVar9, 0xffffffff, *puVar6);
    FUN_710007f500(*puVar7, 0xe0ee, *puVar8, *puVar9, 0xffffffff, *puVar6);
    FUN_710007f500(*puVar7, 0xe0ef, *puVar8, *puVar9, 0xffffffff, *puVar6);
    FUN_710007f500(*puVar7, 0xe0f0, *puVar8, *puVar9, 0xffffffff, *puVar6);
    FUN_710007f500(*puVar7, 0xe0f1, *puVar8, *puVar9, 0xffffffff, *puVar6);
    FUN_710007f500(*puVar7, 0xe0f2, *puVar8, *puVar9, 0xffffffff, *puVar6);
    FUN_710007f500(*puVar7, 0xe100, *puVar8, *puVar9, 0xffffffff, *puVar6);
    FUN_710007f500(*puVar7, 0xe101, *puVar8, *puVar9, 0xffffffff, *puVar6);
    FUN_710007f500(*puVar7, 0xe102, *puVar8, *puVar9, 0xffffffff, *puVar6);
    FUN_710007f500(*puVar7, 0xe103, *puVar8, *puVar9, 0xffffffff, *puVar6);
    FUN_710007f500(*puVar7, 0xe104, *puVar8, *puVar9, 0xffffffff, *puVar6);
    FUN_710007f500(*puVar7, 0xe105, *puVar8, *puVar9, 0xffffffff, *puVar6);
    if (DAT_710523c00c == 0xd) {
        iVar5 = -(s32)(0x7f < *(s32 *)(param_1 + 0x210));
        FUN_710007f500(*(u64 *)(param_1 + 0x10), 0xb294, *(u32 *)(param_1 + 0x18), *(u16 *)(param_1 + 0x32), iVar5, *(u8 *)(param_1 + 0x30));
        FUN_710007f500(*(u64 *)(param_1 + 0x10), 0xc740, *(u32 *)(param_1 + 0x18), *(u16 *)(param_1 + 0x32), iVar5, *(u8 *)(param_1 + 0x30));
        FUN_710007f500(*(u64 *)(param_1 + 0x10), 0xb97c, *(u32 *)(param_1 + 0x18), *(u16 *)(param_1 + 0x32), iVar5, *(u8 *)(param_1 + 0x30));
        FUN_710007f500(*(u64 *)(param_1 + 0x10), 0xc744, *(u32 *)(param_1 + 0x18), *(u16 *)(param_1 + 0x32), iVar5, *(u8 *)(param_1 + 0x30));
        FUN_710007f500(*(u64 *)(param_1 + 0x10), 0xac00, *(u32 *)(param_1 + 0x18), *(u16 *)(param_1 + 0x32), iVar5, *(u8 *)(param_1 + 0x30));
        FUN_710007f500(*(u64 *)(param_1 + 0x10), 0xc774, *(u32 *)(param_1 + 0x18), *(u16 *)(param_1 + 0x32), iVar5, *(u8 *)(param_1 + 0x30));
        FUN_710007f500(*(u64 *)(param_1 + 0x10), 0xc640, *(u32 *)(param_1 + 0x18), *(u16 *)(param_1 + 0x32), iVar5, *(u8 *)(param_1 + 0x30));
        FUN_710007f500(*(u64 *)(param_1 + 0x10), 0xacfc, *(u32 *)(param_1 + 0x18), *(u16 *)(param_1 + 0x32), iVar5, *(u8 *)(param_1 + 0x30));
        FUN_710007f500(*(u64 *)(param_1 + 0x10), 0xc73c, *(u32 *)(param_1 + 0x18), *(u16 *)(param_1 + 0x32), iVar5, *(u8 *)(param_1 + 0x30));
        FUN_710007f500(*(u64 *)(param_1 + 0x10), 0xc57c, *(u32 *)(param_1 + 0x18), *(u16 *)(param_1 + 0x32), iVar5, *(u8 *)(param_1 + 0x30));
        FUN_710007f500(*(u64 *)(param_1 + 0x10), 0xc544, *(u32 *)(param_1 + 0x18), *(u16 *)(param_1 + 0x32), iVar5, *(u8 *)(param_1 + 0x30));
    }
LAB_7103760154:
    lVar4 = *plVar1;
    lVar3 = *(s64 *)(lVar4 + 0x1f30);
    if (lVar3 != 0) {
        if (0 < *(s32 *)(lVar3 + 0x10)) {
            FUN_710354c720(*(u32 *)(DAT_7105332f58[*(u32 *)(lVar3 + 0x14)] + 0x10), lVar3 + 0x10);
        }
        *(u64 *)(lVar4 + 0x1f30) = 0;
    }
    FUN_710007f870(lVar4 + 0x68);
    FUN_71000803c0(lVar4 + 0x68);
    if (*(s32 *)(lVar4 + 0x1c34) != 0) {
        *(u32 *)(lVar4 + 0x1c34) = 0;
    }
    *(u16 *)(param_1 + 0x518) = 0;
}

// 0x71037f20a0
u64 FUN_71037f20a0(s64 *param_1)
{
    u8 *pbVar1;
    u32 *puVar2;
    u64 uVar3;
    u8 bVar4;
    s64 lVar5;
    u64 uVar6;
    u64 uVar7;
    u64 uVar8;
    u8 *pbVar9;
    u64 uVar10;
    s64 lVar11;
    u8 *pbVar12;

    lVar5 = param_1[1] - *param_1;
    if (lVar5 == 0) return 0;
    uVar8 = 0;
    uVar6 = 0;
    do {
        puVar2 = (u32 *)(*param_1 + (s64)uVar8 * 0x40);
        pbVar9 = *(u8 **)(puVar2 + 10);
        if (pbVar9 == *(u8 **)(puVar2 + 0xc)) {
            uVar10 = 0;
        } else {
            uVar10 = 0;
            do {
                uVar3 = *(u64 *)(pbVar9 + 8);
                pbVar12 = *(u8 **)(pbVar9 + 0x10);
                if ((*pbVar9 & 1) == 0) {
                    pbVar12 = pbVar9 + 1;
                    uVar3 = (u64)(*pbVar9 >> 1);
                }
                if (uVar3 == 0) {
                    uVar7 = 0;
                } else {
                    if (uVar3 == 1) {
                        uVar7 = 0;
LAB_71037f2184:
                        uVar7 = (((u64)*pbVar12 * 0xc6a4a7935bd1e995ULL ^
                                 (u64)*pbVar12 * 0xc6a4a7935bd1e995ULL >> 0x2f) * 0xc6a4a7935bd1e995ULL ^ uVar7) *
                                0xc6a4a7935bd1e995ULL + 0xe6546b64;
                    } else {
                        uVar7 = 0;
                        s64 lVar11b = (s64)((uVar3 & 1) - uVar3);
                        do {
                            bVar4 = *pbVar12;
                            pbVar1 = pbVar12 + 1;
                            pbVar12 = pbVar12 + 2;
                            uVar7 = (((u64)*pbVar1 * 0xc6a4a7935bd1e995ULL ^
                                     (u64)*pbVar1 * 0xc6a4a7935bd1e995ULL >> 0x2f) * 0xc6a4a7935bd1e995ULL ^
                                    (((u64)bVar4 * 0xc6a4a7935bd1e995ULL ^
                                     (u64)bVar4 * 0xc6a4a7935bd1e995ULL >> 0x2f) * 0xc6a4a7935bd1e995ULL ^ uVar7) *
                                    0xc6a4a7935bd1e995ULL + 0xe6546b64) * 0xc6a4a7935bd1e995ULL + 0xe6546b64;
                            lVar11b = lVar11b + 2;
                        } while (lVar11b != 0);
                        if ((uVar3 & 1) != 0) goto LAB_71037f2184;
                    }
                    uVar7 = uVar7 * 0xc6a4a7935bd1e995ULL;
                }
                uVar10 = ((uVar7 ^ uVar7 >> 0x2f) * 0xc6a4a7935bd1e995ULL ^ uVar10) *
                         0xc6a4a7935bd1e995ULL + 0xe6546b64;
                pbVar9 = pbVar9 + 0x18;
            } while (pbVar9 != *(u8 **)(puVar2 + 0xc));
            uVar10 = uVar10 * 0xc6a4a7935bd1e995ULL;
        }
        u64 uVar3b = (u64)((u8)((u8)puVar2[4] >> 1));
        pbVar9 = (u8 *)((s64)puVar2 + 0x11);
        if (((u8)puVar2[4] & 1) != 0) {
            uVar3b = *(u64 *)(puVar2 + 6);
            pbVar9 = *(u8 **)(puVar2 + 8);
        }
        if (uVar3b == 0) {
            uVar7 = 0;
        } else {
            if (uVar3b == 1) {
                uVar7 = 0;
LAB_71037f22a0:
                uVar7 = (((u64)*pbVar9 * 0xc6a4a7935bd1e995ULL ^
                         (u64)*pbVar9 * 0xc6a4a7935bd1e995ULL >> 0x2f) * 0xc6a4a7935bd1e995ULL ^ uVar7) *
                        0xc6a4a7935bd1e995ULL + 0xe6546b64;
            } else {
                uVar7 = 0;
                s64 lVar11c = (s64)((uVar3b & 1) - uVar3b);
                do {
                    bVar4 = *pbVar9;
                    pbVar1 = pbVar9 + 1;
                    pbVar9 = pbVar9 + 2;
                    uVar7 = (((u64)*pbVar1 * 0xc6a4a7935bd1e995ULL ^
                             (u64)*pbVar1 * 0xc6a4a7935bd1e995ULL >> 0x2f) * 0xc6a4a7935bd1e995ULL ^
                            (((u64)bVar4 * 0xc6a4a7935bd1e995ULL ^ (u64)bVar4 * 0xc6a4a7935bd1e995ULL >> 0x2f)
                             * 0xc6a4a7935bd1e995ULL ^ uVar7) * 0xc6a4a7935bd1e995ULL + 0xe6546b64) *
                            0xc6a4a7935bd1e995ULL + 0xe6546b64;
                    lVar11c = lVar11c + 2;
                } while (lVar11c != 0);
                if ((uVar3b & 1) != 0) goto LAB_71037f22a0;
            }
            uVar7 = uVar7 * 0xc6a4a7935bd1e995ULL;
        }
        uVar6 = ((uVar7 ^ uVar7 >> 0x2f) * 0xc6a4a7935bd1e995ULL ^
                (((((u64)puVar2[2] * 0xc6a4a7935bd1e995ULL ^
                   (u64)puVar2[2] * 0xc6a4a7935bd1e995ULL >> 0x2f) * 0xc6a4a7935bd1e995ULL ^
                  ((uVar10 ^ uVar10 >> 0x2f) * 0xc6a4a7935bd1e995ULL ^
                  (((u64)puVar2[1] * 0xc6a4a7935bd1e995ULL ^
                   (u64)puVar2[1] * 0xc6a4a7935bd1e995ULL >> 0x2f) * 0xc6a4a7935bd1e995ULL ^ uVar6) *
                  0xc6a4a7935bd1e995ULL + 0xe6546b64) * 0xc6a4a7935bd1e995ULL + 0xe6546b64) *
                  0xc6a4a7935bd1e995ULL + 0xe6546b64 ^
                 ((u64)*puVar2 * 0xc6a4a7935bd1e995ULL ^ (u64)*puVar2 * 0xc6a4a7935bd1e995ULL >> 0x2f) *
                 0xc6a4a7935bd1e995ULL) * 0xc6a4a7935bd1e995ULL + 0xe6546b64 ^
                ((u64)puVar2[3] * 0xc6a4a7935bd1e995ULL ^ (u64)puVar2[3] * 0xc6a4a7935bd1e995ULL >> 0x2f
                ) * 0xc6a4a7935bd1e995ULL) * 0xc6a4a7935bd1e995ULL + 0xe6546b64) * 0xc6a4a7935bd1e995ULL +
                0xe6546b64;
        uVar8 = (u64)((s32)uVar8 + 1);
        if ((u64)(lVar5 >> 6) <= uVar8) return uVar6;
    } while (true);
}

// 0x7103986e30
void * FUN_7103986e30(s64 param_1, s32 param_2, u32 param_3)
{
    s64 lVar1;
    u64 *puVar2;
    u64 uVar3;
    u64 uVar4;
    u64 uVar5;
    u64 uVar6;
    s64 lVar7;
    u64 *puVar8;
    u64 *puVar9;
    u32 uVar10;
    u32 uVar11;
    u64 uVar12;
    s64 lVar13;
    u64 uVar14;
    u64 uVar15;
    s64 *plVar16;
    s64 lVar17;
    u64 uVar18;
    u64 uVar19;
    u32 local_54;

    if (0xffffffbc < (u32)(param_2 - 1)) return (void *)0x0;
    uVar11 = (u32)(param_2 + 0x3f) & 0xffffffc0;
    if (0x40 < param_3) {
        uVar10 = 0;
        if (param_3 != 0) uVar10 = ((param_3 + uVar11) - 1) / param_3;
        uVar11 = uVar10 * param_3;
    }
    puVar8 = (u64 *)FUN_7103986bb0(param_1, uVar11, &local_54);
    if (puVar8 != (u64 *)0x0) {
        if (param_3 < 0x41) {
            uVar15 = (u64)local_54;
LAB_7103987110:
            uVar19 = puVar8[5];
            uVar12 = uVar15;
            if (uVar15 <= uVar19) uVar12 = uVar19;
            if (0x7f < uVar12 - uVar15) {
                uVar15 = (u64)((s32)(uVar12 - uVar15) - 0x40);
                lVar17 = puVar8[1];
                lVar13 = (s64)(-0x40 - (s64)uVar15);
                lVar7 = lVar13 + (s64)uVar19;
                lVar1 = (s64)puVar8 + lVar7 + 0x40;
                *(s64 *)((s64)puVar8 + lVar7 + 0x48) = lVar17;
                if (lVar17 != 0) *(s64 *)(lVar17 + 0x10) = lVar1;
                *(u64 **)((s64)puVar8 + lVar7 + 0x50) = puVar8;
                *(u64 *)((s64)puVar8 + lVar7 + 0x58) = 0;
                *(u64 *)((s64)puVar8 + lVar7 + 0x70) = 0;
                *(u64 *)((s64)puVar8 + lVar7 + 0x60) = 0;
                *(u64 *)((s64)puVar8 + lVar7 + 0x68) = uVar15;
                puVar8[1] = lVar1;
                puVar8[5] = puVar8[5] + (u64)(s64)lVar13;
                uVar11 = *(u32 *)((s64)puVar8 + lVar7 + 0x68);
                if (uVar11 == 0) {
                    uVar10 = 0xfffffffb;
                } else if ((s32)uVar11 < 0) {
                    uVar10 = 0x1a;
                } else {
                    u64 uVar15b = 0x80000000;
                    uVar10 = 0x1a;
                    do {
                        uVar15b = uVar15b >> 1;
                        uVar10 = uVar10 - 1;
                    } while (((u32)uVar15b & uVar11) == 0);
                }
                uVar11 = uVar11 >> (u64)(uVar10 & 0x1f) & 0x1f;
                *(u64 *)((s64)puVar8 + lVar7 + 0x60) = 0;
                plVar16 = (s64 *)(param_1 + (u64)uVar10 * 0x100 + (u64)uVar11 * 8 + 0x10);
                *(s64 *)((s64)puVar8 + lVar7 + 0x58) = *plVar16;
                if (*plVar16 != 0) *(s64 *)(*plVar16 + 0x20) = lVar1;
                *plVar16 = lVar1;
                lVar1 = param_1 + (u64)uVar10 * 4;
                *(u32 *)(param_1 + 0x1b10) = *(u32 *)(param_1 + 0x1b10) | 1 << (u64)(uVar10 & 0x1f);
                *(u32 *)(lVar1 + 0x1b14) = *(u32 *)(lVar1 + 0x1b14) | 1 << (u64)uVar11;
                *(u64 *)((s64)puVar8 + lVar7 + 0x70) = 1;
                *(s32 *)(param_1 + 0xc) = *(s32 *)(param_1 + 0xc) + *(s32 *)((s64)puVar8 + lVar7 + 0x68);
            }
            puVar8[6] = 2;
            puVar8[3] = 0;
            puVar8[4] = 0;
            return puVar8 + 8;
        }
        uVar19 = (u64)param_3;
        puVar9 = puVar8;
        uVar12 = 0;
        do {
            puVar2 = puVar9 + 8;
            uVar14 = 0;
            if (uVar19 != 0) uVar14 = (u64)puVar2 / uVar19;
            uVar15 = (u64)local_54;
            if (uVar12 != 0) uVar15 = uVar12;
            puVar8 = puVar9;
            if (puVar2 == (u64 *)(uVar14 * uVar19)) goto LAB_7103987110;
            uVar12 = 0;
            if (uVar19 != 0) uVar12 = ((uVar19 - 1) + (u64)puVar2) / uVar19;
            uVar12 = uVar12 * uVar19 - (u64)puVar2;
            if ((u32)uVar12 < 0x80) {
                uVar12 = (u64)puVar2 + uVar19 + 0x7f;
                uVar14 = 0;
                if (uVar19 != 0) uVar14 = uVar12 / uVar19;
                uVar12 = uVar19 + 0x7f + (uVar14 * uVar19 - uVar12);
            }
            uVar14 = puVar9[5];
            if (uVar15 + (uVar12 & 0xffffffff) <= uVar14) {
                uVar4 = puVar9[1];
                uVar18 = puVar9[4];
                lVar1 = puVar9[2];
                uVar5 = puVar9[3];
                uVar12 = (u64)((s32)uVar12 - 0x40);
                uVar3 = puVar9[6];
                uVar6 = puVar9[7];
                puVar8 = (u64 *)((s64)puVar9 + (s64)uVar12 + 0x40);
                *puVar8 = *puVar9;
                puVar8[1] = uVar4;
                puVar8[4] = uVar18;
                puVar8[5] = uVar14;
                puVar8[2] = lVar1;
                puVar8[3] = uVar5;
                puVar8[6] = uVar3;
                puVar8[7] = uVar6;
                puVar9[1] = (u64)puVar8;
                puVar9[2] = lVar1;
                u64 *puVar2b = (u64 *)(param_1 + 0x1b88);
                if (lVar1 != 0) puVar2b = (u64 *)(lVar1 + 8);
                *puVar2b = (u64)puVar9;
                puVar9[3] = 0;
                puVar9[4] = 0;
                puVar9[5] = uVar12;
                puVar9[6] = 0;
                puVar8[5] = puVar8[5] - (uVar12 + 0x40);
                puVar8[2] = (u64)puVar9;
                if (puVar8[1] != 0) {
                    *(u64 **)(puVar8[1] + 0x10) = puVar8;
                    uVar12 = puVar9[5];
                }
                if (uVar12 == 0) {
                    lVar1 = puVar9[1];
                    lVar7 = puVar9[2];
                    *(s64 *)(lVar7 + 8) = lVar1;
                    if (lVar1 != 0) *(s64 *)(lVar1 + 0x10) = lVar7;
                    *(u64 *)(lVar7 + 0x28) = (u64)((s32)*(s32 *)(lVar7 + 0x28) + *(s32 *)(puVar9 + 5) + 0x40);
                } else {
                    uVar11 = (u32)uVar12;
                    if (uVar11 == 0) {
                        uVar10 = 0xfffffffb;
                    } else if ((s32)uVar11 < 0) {
                        uVar10 = 0x1a;
                    } else {
                        u64 uVar12b = 0x80000000;
                        uVar10 = 0x1a;
                        do { uVar12b >>= 1; uVar10--; } while (((u32)uVar12b & uVar11) == 0);
                    }
                    uVar11 = uVar11 >> (u64)(uVar10 & 0x1f) & 0x1f;
                    puVar9[4] = 0;
                    plVar16 = (s64 *)(param_1 + (u64)uVar10 * 0x100 + (u64)uVar11 * 8 + 0x10);
                    puVar9[3] = (u64)*plVar16;
                    if (*plVar16 != 0) *(u64 **)(*plVar16 + 0x20) = puVar9;
                    *plVar16 = (s64)puVar9;
                    lVar1 = param_1 + (u64)uVar10 * 4;
                    *(u32 *)(param_1 + 0x1b10) = *(u32 *)(param_1 + 0x1b10) | 1 << (u64)(uVar10 & 0x1f);
                    *(u32 *)(lVar1 + 0x1b14) = *(u32 *)(lVar1 + 0x1b14) | 1 << (u64)uVar11;
                    puVar9[6] = 1;
                    *(s32 *)(param_1 + 0xc) = *(s32 *)(param_1 + 0xc) + *(s32 *)(puVar9 + 5);
                }
                goto LAB_7103987110;
            }
            uVar11 = (u32)uVar14;
            if (uVar11 == 0) {
                uVar10 = 0xfffffffb;
            } else if ((s32)uVar11 < 0) {
                uVar10 = 0x1a;
            } else {
                u64 uVar12c = 0x80000000;
                uVar10 = 0x1a;
                do { uVar12c >>= 1; uVar10--; } while (((u32)uVar12c & uVar11) == 0);
            }
            uVar11 = uVar11 >> (u64)(uVar10 & 0x1f) & 0x1f;
            puVar9[4] = 0;
            plVar16 = (s64 *)(param_1 + (u64)uVar10 * 0x100 + (u64)uVar11 * 8 + 0x10);
            puVar9[3] = (u64)*plVar16;
            if (*plVar16 != 0) *(u64 **)(*plVar16 + 0x20) = puVar9;
            *plVar16 = (s64)puVar9;
            lVar1 = param_1 + (u64)uVar10 * 4;
            *(u32 *)(param_1 + 0x1b10) = *(u32 *)(param_1 + 0x1b10) | 1 << (u64)(uVar10 & 0x1f);
            *(u32 *)(lVar1 + 0x1b14) = *(u32 *)(lVar1 + 0x1b14) | 1 << (u64)uVar11;
            puVar9[6] = 1;
            *(s32 *)(param_1 + 0xc) = *(s32 *)(param_1 + 0xc) + *(s32 *)(puVar9 + 5);
            puVar9 = (u64 *)FUN_7103986bb0(param_1, local_54 + param_3, &local_54);
            uVar12 = uVar15;
        } while (puVar9 != (u64 *)0x0);
    }
    return (void *)0x0;
}

// 0x7100033a20  (WARNING: jumptable not recovered)
void FUN_7100033a20(u64 *param_1)
{
    ((void (*)(u64))*(u64 *)PTR_DAT_71052a2560)(*param_1);
}
