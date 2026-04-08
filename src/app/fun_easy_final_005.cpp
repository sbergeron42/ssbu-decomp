#include "types.h"

// EASY-tier batch 005 — pool-a worker

#define NAN(x)          ((x) != (x))
#define CONCAT44(hi,lo) (((u64)(u32)(hi) << 32) | (u32)(lo))

// ── C stdlib ──────────────────────────────────────────────────────────────────
extern "C" void *memset(void *, int, unsigned long);
extern "C" void *memcpy(void *, const void *, unsigned long);
extern "C" char *strncpy(char *, const char *, unsigned long);
extern "C" int   snprintf(char *, unsigned long, const char *, ...);
extern "C" float fminf(float, float);

// ── Allocator ─────────────────────────────────────────────────────────────────
extern "C" void *je_aligned_alloc(unsigned long, unsigned long);

// ── SDK forward declarations ───────────────────────────────────────────────────
namespace nn { namespace os  { struct EventType; void InitializeEvent(EventType *, bool, bool); } }
namespace nn { namespace socket { u32 InetNtohl(u32); u16 InetNtohs(u16); } }

// ── Mutex helpers ──────────────────────────────────────────────────────────────
extern void FUN_71039c1410(s64);   // mutex::lock
extern void FUN_71039c1420(s64);   // mutex::unlock
extern void FUN_71039c1490(s64);   // recursive_mutex::lock
extern void FUN_71039c14a0(s64);   // recursive_mutex::unlock

// ── External functions ─────────────────────────────────────────────────────────
extern void  FUN_71001d0460(s64, const void *, s32);
extern void  FUN_7103777b30(void *, s64, void *);
extern void  FUN_710392e590(s64);
extern void  FUN_71036635d0(u32);
extern void  FUN_71032e48f0(s64);
extern u32   FUN_71001c46c0(u64, u64, u64, s64);
extern u32   FUN_71001c04e0(s64, u32);
extern void  FUN_71025fdde0(u64);
extern void  FUN_710353eff0(s64, s64);
extern void  FUN_7102600d20();
extern float FUN_7100070140(float, float *);
extern u64   FUN_71001dc540(void *, u64);
extern void  FUN_71001b5de0(char *, s64, u64);
extern void  FUN_710376b3b0(u64);
extern void  ui2d_apply_named_animation(f32, u64, const char *);
extern void  FUN_7101b8e6e0(u64);
extern void  FUN_71016cce40(s64, u16);
extern void  FUN_71016cd070(s64, s32);
extern void  FUN_7102414dd0(void *);
extern void  FUN_7102415b40(void *, void *);
extern void  FUN_710377a930(u32, u64);
extern u32   FUN_71006d9cd0(u32);
extern s32   FUN_71006d9e00(s64, s64 *, s32);
extern void  FUN_7100031070(u64 *);
extern void  FUN_71000310a0(u64 *);
extern u64   FUN_7100031720(u64, u64 *);
extern u64   FUN_71000338d0(u64, u64 *);
extern s64   FUN_71000338e0(u64, u64 *);
extern void  FUN_7100033920(s64, u64, u64 *);
extern void  FUN_7100031880(s64, u64, u64 *, s64, s32, u64);

// ── External globals ───────────────────────────────────────────────────────────
extern s64   DAT_7105331f20;
extern s64  *DAT_7105331f00;
extern s64  *DAT_71052c25b0;
extern float DAT_7104472710;
extern float DAT_710447291c;
extern float DAT_7104471598;
extern float DAT_7104471e0c;
extern void *DAT_7104420055;
extern u8    PTR_LAB_710523c9e8;
extern u32   DAT_7104753084[];
extern s64   DAT_71052c40f0;
extern s64   DAT_71053388b0;
extern u64   DAT_7105338860[];
extern u64   DAT_7105338830;
extern u32   DAT_7104752de0[];
extern s64   DAT_710446f740[];
extern s64   DAT_7104470380[];
extern float DAT_7104471eb0;
extern float DAT_7104472be8;
extern float DAT_71044720b4;
extern float DAT_7104471074;
extern float DAT_7104472278;
extern u8    PTR_LAB_71052a5ae0;
extern s64  *DAT_71052b84f8;

// ── 112-byte ───────────────────────────────────────────────────────────────────

// 0x710022b0d0
void FUN_710022b0d0(s64 param_1, s64 param_2)
{
    char local_14[4];
    char local_18[4];
    u32 local_24;
    if (*(char *)(param_1 + 0x69) != '\0') return;
    local_14[0] = *(char *)(param_2 + 8);
    char *pcVar1 = local_14;
    if (local_14[0] != '\0') {
        pcVar1 = local_18;
    }
    local_18[0] = '\0';
    FUN_71001d0460(param_1, pcVar1, 1);
    local_24 = 0;
    FUN_71001d0460(param_1, &local_24, 4);
}

// ── 224-byte ───────────────────────────────────────────────────────────────────

// 0x71032e58b0
void FUN_71032e58b0(s64 param_1)
{
    u64 uVar1;
    s64 lVar2;
    u64 *puVar3;
    s64 lVar4;
    u64 uVar5;
    u16 local_24;
    u8  local_22;
    if (0 < *(s32 *)(param_1 + 0x64)) return;
    FUN_71039c1410(param_1 + 0x10);
    lVar2 = *(s64 *)(param_1 + 0x38);
    lVar4 = *(s64 *)(param_1 + 0x40);
    uVar1 = 0;
    if (lVar4 - lVar2 != 0) {
        uVar1 = (u64)(lVar4 - lVar2) * 0x20 - 1;
    }
    uVar5 = *(u64 *)(param_1 + 0x58) + *(u64 *)(param_1 + 0x50);
    if (uVar1 == uVar5) {
        FUN_71032e48f0(param_1 + 0x30);
        uVar5 = *(u64 *)(param_1 + 0x50) + *(u64 *)(param_1 + 0x58);
        lVar2 = *(s64 *)(param_1 + 0x38);
        lVar4 = *(s64 *)(param_1 + 0x40);
    }
    if (lVar4 == lVar2) {
        puVar3 = (u64 *)0;
    } else {
        puVar3 = (u64 *)(*(s64 *)(lVar2 + (uVar5 >> 5 & 0x7fffffffffffff8ULL)) +
                         (uVar5 & 0xff) * 0x10);
    }
    *puVar3 = 0xfffffffe00000001ULL;
    *(u32 *)(puVar3 + 1) = 0;
    *(u8 *)((s64)puVar3 + 0xc) = 0;
    *(u8 *)((s64)puVar3 + 0xf) = local_22;
    *(u16 *)((s64)puVar3 + 0xd) = local_24;
    *(u64 *)(param_1 + 0x58) = *(u64 *)(param_1 + 0x58) + 1;
    *(u16 *)(param_1 + 0x6a) = 0x100;
    FUN_71039c1420(param_1 + 0x10);
}

// ── 256-byte ───────────────────────────────────────────────────────────────────

// 0x71001c45c0
s32 FUN_71001c45c0(s64 param_1, u64 param_2, u64 param_3, s64 param_4)
{
    void *puVar1;
    u32 uVar2;
    u32 uVar3;
    s64 *plVar4;
    s64 lVar5;
    u32 local_50;
    u32 uStack_4c;
    u16 local_48;
    u64 uStack_38;

    if (*(s32 *)(param_1 + 0xc0) != 0) return -1;
    uStack_38 = 0;
    lVar5 = *(s64 *)(param_1 + 0xd0);
    if (lVar5 != 0) {
        puVar1 = (void *)0;
        if (*(s64 *)(lVar5 + 0x10) != 0) {
            puVar1 = (void *)&PTR_LAB_71052a5ae0;
        }
        if (puVar1 != (void *)0) {
            uVar2 = FUN_71001c46c0(*(u64 *)(lVar5 + 0x10), param_2, param_3, param_4);
            goto LAB_71001c4690;
        }
    }
    uVar2 = nn::socket::InetNtohl(*(u32 *)(param_4 + 0xc));
    local_48 = nn::socket::InetNtohs(*(u16 *)(param_4 + 10));
    uStack_4c = 0;
    plVar4 = *(s64 **)(*(s64 *)(param_1 + 0xb0) + 0x10);
    local_50 = uVar2;
    uVar2 = ((u32 (*)(s64 *, u64, u64, u32 *, u64 *))(*(s64 *)(*plVar4 + 0x28)))(
        plVar4, param_2, param_3, &local_50, &uStack_38);
LAB_71001c4690:
    uVar3 = FUN_71001c04e0(param_1, uVar2);
    return -(s32)((~uVar3) & 1);
}

// ── 272-byte ───────────────────────────────────────────────────────────────────

// 0x7101e94d80
void FUN_7101e94d80(s64 *param_1)
{
    s64 lVar1;
    void **puVar2;
    u64 uVar3;
    s64 *plVar4;
    s64 lVar5;
    void **local_50;
    s64 local_48;
    u64 local_40;
    u32 local_34;

    if (*(char *)((s64)param_1 + 10) != '\0') return;
    lVar5 = *param_1;
    FUN_7103777b30(&local_50, lVar5, &DAT_7104420055);
    puVar2 = (void **)je_aligned_alloc(0x10, 0x10);
    if (puVar2 == (void **)0) {
        if (DAT_7105331f00 != (s64 *)0) {
            local_34 = 0;
            local_40 = 0x10;
            uVar3 = ((u64 (*)(s64 *, u32 *, u64 *))(*(s64 *)(*DAT_7105331f00 + 0x30)))(
                DAT_7105331f00, &local_34, &local_40);
            if (((uVar3 & 1) != 0) &&
                (puVar2 = (void **)je_aligned_alloc(0x10, 0x10), puVar2 != (void **)0))
                goto LAB_7101e94e14;
        }
        puVar2 = (void **)0;
    }
LAB_7101e94e14:
    lVar1 = local_48;
    *(void **)puVar2 = (void *)&PTR_LAB_710523c9e8;
    puVar2[1] = (void *)0;
    if ((void **)&local_50 != puVar2) {
        local_48 = 0;
        puVar2[1] = (void *)lVar1;
    }
    plVar4 = *(s64 **)(lVar5 + 0x48);
    *(void **)(lVar5 + 0x48) = puVar2;
    if (plVar4 != (s64 *)0) {
        (*(void (**)(s64 *))(*(s64 *)(*(s64 *)plVar4) + 8))(plVar4);
    }
    lVar1 = local_48;
    local_50 = (void **)&PTR_LAB_710523c9e8;
    local_48 = 0;
    if (lVar1 != 0) {
        FUN_710392e590(lVar1);
    }
    FUN_710377a930(0x3f800000, *(u64 *)(lVar5 + 0x48));
    *(u8 *)((s64)param_1 + 10) = 1;
}

// 0x71027a4bd0
u64 FUN_71027a4bd0(s64 *param_1)
{
    u32 uVar1;
    u32 uVar2;
    u32 uVar3;
    bool bVar4;
    bool bVar5;
    u32 *puVar6;
    float fVar7;
    float fVar8;
    float fVar9;

    if (*(s32 *)((s64)param_1 + 0x14) != 0) return 0;
    if ((s32)param_1[4] != 0) {
        uVar3 = (u32)((s32)param_1[4] - 1);
        uVar1 = *(u32 *)(param_1[1] + 0x1ec);
        if (uVar3 <= *(u32 *)(param_1[1] + 0x1ec)) {
            uVar1 = uVar3;
        }
        *(u32 *)((s64)param_1 + 0x20) = uVar1;
        return 0;
    }
    fVar7 = *(float *)(param_1[1] + 0x1e0);
    fVar9 = *(float *)(param_1[1] + 0x1e4);
    fVar8 = *(float *)((s64)param_1 + 0x10);
    if (fVar7 == fVar9 || (fVar7 < fVar9) != (NAN(fVar7) || NAN(fVar9))) {
        bVar4 = true;
        if ((fVar9 <= fVar8) && (bVar4 = false, !NAN(fVar7) && !NAN(fVar8))) {
            bVar4 = fVar7 < fVar8;
        }
        if (bVar4) return 0;
    } else {
        bVar4 = false;
        bVar5 = true;
        if (fVar9 <= fVar8) {
            bVar4 = false;
            bVar5 = true;
            if (!NAN(fVar8) && !NAN(fVar7)) {
                bVar4 = fVar8 == fVar7;
                bVar5 = fVar7 <= fVar8;
            }
        }
        if (!bVar5 || bVar4) return 0;
    }
    puVar6 = *(u32 **)(*(s64 *)param_1 + 0x340);
    uVar1 = *puVar6;
    *puVar6 = puVar6[1];
    uVar2 = puVar6[3];
    uVar1 = uVar1 ^ uVar1 << 0xb;
    uVar3 = uVar1 ^ uVar1 >> 8 ^ uVar2 ^ uVar2 >> 0x13;
    puVar6[1] = puVar6[2];
    puVar6[2] = uVar2;
    uVar1 = uVar3;
    if (uVar3 == 0xffffffff) {
        uVar1 = 0;
    }
    fVar7 = (float)uVar1 * DAT_7104472710 * DAT_710447291c;
    puVar6[3] = uVar3;
    if (*(float *)(param_1[1] + 0x1e8) < (float)(u32)(s32)(fVar7 + 0.0f)) {
        return 0;
    }
    *(u32 *)((s64)param_1 + 0x20) = *(u32 *)(param_1[1] + 0x1ec);
    return 1;
}

// ── 288-byte ───────────────────────────────────────────────────────────────────

// 0x7102600c00
void FUN_7102600c00(s64 param_1)
{
    u32 *puVar1;
    u32 uVar2;
    u32 *puVar3;
    s64 lVar4;
    u64 *puVar5;
    s64 puVar6;
    u32 *puVar7;

    if (*(s32 *)param_1 != 0) return;
    puVar6 = *(s64 *)(param_1 + 0x590);
    *(u8 *)(param_1 + 0x580) = 1;
    if (puVar6 != 0) {
        if (*(u32 *)(puVar6 + 0x50) != 0) {
            *(u8 *)(puVar6 + 0xc8) = 1;
        }
        puVar1 = *(u32 **)(puVar6 + 8);
        puVar7 = *(u32 **)(puVar6 + 0x10);
        lVar4 = DAT_7105331f20;
        while (puVar3 = puVar7, lVar4 = DAT_7105331f20, puVar3 != puVar1) {
            puVar7 = puVar3 - 1;
            uVar2 = *puVar7;
            if (uVar2 != 0xffffff) {
                if (uVar2 < *(u32 *)(lVar4 + 0x48)) {
                    FUN_71039c1490(*(s64 *)lVar4);
                    if ((*(u8 *)(*(s64 *)(lVar4 + 0x40) + (u64)uVar2 * 0x48 + 8) & 1) != 0) {
                        FUN_710353eff0(lVar4, *(s64 *)(lVar4 + 0x40) + (u64)uVar2 * 0x48);
                    }
                    FUN_71039c14a0(*(s64 *)lVar4);
                }
                puVar3[-1] = 0xffffff;
                lVar4 = DAT_7105331f20;
            }
        }
        *(u32 **)(puVar6 + 0x10) = puVar1;
        puVar5 = (u64 *)(puVar6 + 0x28);
        FUN_71025fdde0(*puVar5);
        *(u64 *)(puVar6 + 0x30) = 0;
        *(u64 **)(puVar6 + 0x20) = puVar5;
        *puVar5 = 0;
        *(u32 *)puVar6 = 3;
    }
    *(s32 *)param_1 = 2;
    *(void **)(param_1 + 0x10) = (void *)FUN_7102600d20;
    *(s64 *)(param_1 + 0x18) = 0;
}

// 0x710353d360
bool FUN_710353d360(u32 param_1, char *param_2)
{
    u32 uVar1;
    s64 lVar2;
    bool bVar3;
    u64 uVar4;
    u32 uVar5;
    u8 *pbVar6;
    u32 uVar7;
    u8 local_130[256];

    lVar2 = DAT_7105331f20;
    if (param_1 == 0xffffff) return false;
    if (param_2 == (char *)0) return false;
    if (*param_2 == '\0') return false;
    if (*param_2 == '.') {
        param_2 = param_2 + 1;
    }
    strncpy((char *)local_130, param_2, 0xff);
    uVar7 = (u32)local_130[0];
    if (local_130[0] == 0) {
        uVar4 = 0;
    } else {
        uVar4 = 0;
        uVar5 = 0xffffffff;
        pbVar6 = (u8 *)((u64)(u64)local_130 | 1);
        do {
            uVar1 = uVar7 + 0x20;
            if (0x19 < uVar7 - 0x41) {
                uVar1 = uVar7;
            }
            uVar5 = *(u32 *)(&DAT_7104753084[0] + (u64)((uVar1 ^ uVar5) & 0xff)) ^ uVar5 >> 8;
            uVar7 = (u32)*pbVar6;
            uVar4 = uVar4 + 0x100000000ULL;
            pbVar6 = pbVar6 + 1;
        } while (uVar7 != 0);
        uVar4 = uVar4 & 0xff00000000ULL | (u64)~uVar5;
    }
    if (param_1 < *(u32 *)(*(s64 *)(**(s64 **)(lVar2 + 0x78) + 0x40) + 4)) {
        bVar3 = (*(u64 *)(*(s64 *)(**(s64 **)(lVar2 + 0x78) + 0x60) +
                          (u64)param_1 * 0x20 + 8) & 0xffffffffffULL) == uVar4;
    } else {
        bVar3 = false;
    }
    return bVar3;
}

// 0x71036e8dc0
void FUN_71036e8dc0(s64 param_1, u32 param_2, u8 param_3, s32 param_4,
                    s32 param_5, void *param_6, u64 param_7)
{
    u64 sVar1;
    s64 lVar2;
    void *__s;
    u64 uVar3;
    u64 local_48;
    u32 local_34;

    if (*(s32 *)param_1 != 0) return;
    *(s32 *)param_1 = 1;
    *(s32 *)(param_1 + 0x120) = 0;
    *(u8 *)(param_1 + 4) = param_3 & 1;
    *(s32 *)(param_1 + 8) = param_4;
    *(s32 *)(param_1 + 0xc) = param_5;
    lVar2 = *(s64 *)(param_1 + 0x10);
    *(s32 *)(param_1 + 0x10) = 0;
    *(s32 *)(param_1 + 0x14) = 0;
    if (lVar2 != 0) {
        FUN_710392e590(lVar2);
    }
    *(u8 *)(param_1 + 0x20) = 0;
    *(s32 *)(param_1 + 0x18) = 0;
    *(s32 *)(param_1 + 0x1c) = 0;
    FUN_71036635d0(param_2);
    sVar1 = param_7;
    if (param_7 == 0) {
        sVar1 = 1;
    }
    *(u16 *)(param_1 + 0x124) = 0;
    __s = je_aligned_alloc(0x10, sVar1);
    if (__s == (void *)0) {
        if (DAT_7105331f00 != (s64 *)0) {
            local_34 = 0;
            local_48 = sVar1;
            uVar3 = ((u64 (*)(s64 *, u32 *, u64 *))(*(s64 *)(*DAT_7105331f00 + 0x30)))(
                DAT_7105331f00, &local_34, &local_48);
            if (((uVar3 & 1) != 0) &&
                (__s = je_aligned_alloc(0x10, sVar1), __s != (void *)0))
                goto LAB_71036e8e90;
        }
        __s = (void *)0;
    }
LAB_71036e8e90:
    memset(__s, 0, param_7);
    lVar2 = *(s64 *)(param_1 + 0x128);
    *(void **)(param_1 + 0x128) = __s;
    if (lVar2 != 0) {
        FUN_710392e590(lVar2);
        __s = *(void **)(param_1 + 0x128);
    }
    memcpy(__s, param_6, param_7);
    *(u64 *)(param_1 + 0x130) = param_7;
}

// ── 304-byte ───────────────────────────────────────────────────────────────────

// 0x71000af920
s64 FUN_71000af920(s64 param_1, u64 param_2, s64 *param_3, u32 param_4, u64 param_5)
{
    u64 uVar1;
    s64 lVar2;
    u64 uVar3;
    s64 lVar4;
    u64 local_70;
    s64 local_68;
    u64 local_60;
    u64 uStack_58;
    u64 local_50;
    u64 local_48;

    if (*(char *)(param_1 + 0x50) != '\0') return 1;
    local_48 = 0;
    *(u64 *)(param_1 + 0x48) = param_5;
    *(u64 *)(param_1 + 0x178) = 0;
    *(u64 *)(param_1 + 0x180) = 0;
    local_50 = 0;
    FUN_7100031070(&local_50);
    local_60 = 0;
    uStack_58 = 0;
    local_70 = 0;
    local_68 = 0;
    ((u32 *)&local_50)[1] = param_4;
    FUN_71000310a0(&local_70);
    local_70 = CONCAT44((u32)(local_70 >> 32), 0x22u);
    uVar1 = FUN_7100031720(param_2, &local_50);
    *(u64 *)(param_1 + 0x188) = uVar1;
    uVar1 = FUN_71000338d0(param_2, &local_70);
    lVar4 = *(s64 *)(param_1 + 0x48);
    *(s64 *)(param_1 + 0x180) = lVar4;
    lVar2 = FUN_71000338e0(param_2, &local_70);
    uVar3 = (u64)((lVar4 + lVar2) - 1) & (u64)(-lVar2);
    *(u64 *)(param_1 + 0x180) = uVar3;
    local_68 = (*(s64 (*)(s64 *, u64, u64))(*param_3 + 0x10))(param_3, uVar3, uVar1);
    *(s64 *)(param_1 + 0x178) = local_68;
    if (local_68 != 0) {
        local_70 = CONCAT44(*(u32 *)(param_1 + 0x180), (u32)local_70);
        FUN_7100033920(param_1 + 0x58, param_2, &local_70);
        local_50 = CONCAT44((u32)(local_50 >> 32), (u32)*(u64 *)(param_1 + 0x48));
        FUN_7100031880(param_1, param_2, &local_50, param_1 + 0x58, 0,
                       *(u64 *)(param_1 + 0x180));
        local_68 = 1;
        *(u8 *)(param_1 + 0x50) = 1;
    }
    return local_68;
}

// 0x71006da840
void FUN_71006da840(s64 param_1, s64 *param_2, s64 param_3)
{
    u32 uVar1;
    s32 iVar2;
    s64 lVar3;

    if (*(char *)(param_3 + 8) != '\0') return;
    lVar3 = param_2[1];
    if (**(s32 **)(lVar3 + 0x39a0) + **(s32 **)(lVar3 + 0x27f0) + **(s32 **)(lVar3 + 0x1640) <
        **(s32 **)(lVar3 + 0x3998) + **(s32 **)(lVar3 + 0x27e8) + **(s32 **)(lVar3 + 0x1638)) {
        uVar1 = FUN_71006d9cd0(*(u32 *)(param_1 + 8));
        (*(void (*)(s64 *, s32, s32, s32, u32))(*param_2 + 0xd8))(param_2, 1, 0xc, 0, uVar1);
        if (*(s32 *)(param_3 + 4) != 0) {
            iVar2 = *(s32 *)(param_3 + 4) - 1;
            uVar1 = FUN_71006d9cd0(*(u32 *)(param_1 + 8));
            (*(void (*)(s64 *, s32, s32, s32, u32))(*param_2 + 0xd8))(param_2, 1, 0x50, iVar2, uVar1);
            iVar2 = FUN_71006d9e00(param_1, param_2, iVar2);
            if (-1 < iVar2) {
                (*(void (*)(s64 *, s32, s32, s32, u32))(*param_2 + 0xd8))(param_2, 1, 0x50, iVar2, uVar1);
            }
        }
    }
    *(u8 *)(param_3 + 8) = 1;
}

// 0x71037cc390
void FUN_71037cc390(s64 *param_1, u32 param_2)
{
    nn::os::EventType *pEVar1;
    u64 uVar2;
    u64 local_38;
    u32 local_24;

    if (*param_1 != 0) return;
    pEVar1 = (nn::os::EventType *)je_aligned_alloc(0x10, 0x28);
    if (pEVar1 == (nn::os::EventType *)0) {
        if (DAT_7105331f00 != (s64 *)0) {
            local_24 = 0;
            local_38 = 0x28;
            uVar2 = ((u64 (*)(s64 *, u32 *, u64 *))(*(s64 *)(*DAT_7105331f00 + 0x30)))(
                DAT_7105331f00, &local_24, (u64*)&local_38);
            if (((uVar2 & 1) != 0) &&
                (pEVar1 = (nn::os::EventType *)je_aligned_alloc(0x10, 0x28),
                 pEVar1 != (nn::os::EventType *)0))
                goto LAB_71037cc414;
        }
        pEVar1 = (nn::os::EventType *)0;
    }
LAB_71037cc414:
    nn::os::InitializeEvent(pEVar1, false, (bool)((param_2 & 1) ^ 1));
    *param_1 = (s64)pEVar1;
}

// ── 320-byte ───────────────────────────────────────────────────────────────────

// 0x7100070340
float FUN_7100070340(float param_1, u16 *param_2)
{
    s64 lVar1;
    float *pfVar2;
    bool bVar3;
    bool bVar4;
    u64 uVar5;
    s64 lVar6;
    float *pfVar7;
    float uVar8;
    float fVar9;
    float fVar10;

    uVar5 = (u64)*param_2;
    lVar1 = (s64)(uVar5 - 1);
    if (uVar5 == 0 || lVar1 == 0) {
        return *(float *)(param_2 + 4);
    }
    pfVar7 = *(float **)(param_2 + 4);
    fVar9 = *pfVar7;
    if ((fVar9 < param_1) != (NAN(fVar9) || NAN(param_1))) {
        if (pfVar7[lVar1 * 8] <= param_1) {
            lVar6 = -2;
            if (((u32)pfVar7[lVar1 * 8 + 7] & 1) != 0) {
                lVar6 = -1;
            }
            pfVar7 = pfVar7 + (lVar6 + (s64)uVar5) * 8;
            fVar9 = 1.0f;
            goto joined_r0x0071000703f0;
        }
        lVar6 = 0;
        pfVar2 = pfVar7;
        do {
            pfVar7 = pfVar2;
            fVar10 = pfVar7[8];
            bVar3 = false;
            bVar4 = true;
            if (fVar10 != param_1 && (fVar10 < param_1) == (NAN(fVar10) || NAN(param_1))) {
                bVar3 = false;
                bVar4 = true;
                if (!NAN(fVar9) && !NAN(param_1)) {
                    bVar3 = fVar9 == param_1;
                    bVar4 = param_1 <= fVar9;
                }
            }
            if (!bVar4 || bVar3) {
                fVar9 = (param_1 - fVar9) / (fVar10 - fVar9);
                if (fVar9 <= 0.0f) fVar9 = 0.0f;
                uVar8 = fminf(fVar9, 1.0f);
                fVar9 = FUN_7100070140(uVar8, pfVar7);
                fVar10 = 1.0f - fVar9;
                fVar9 = fVar9 * fVar9 * fVar9 +
                        pfVar7[4] * fVar10 * fVar9 * 3.0f * fVar10 +
                        pfVar7[2] * fVar10 * fVar9 * fVar9 * 3.0f;
                goto LAB_7100070458;
            }
            lVar6 = lVar6 + 1;
            pfVar2 = pfVar7 + 8;
            fVar9 = fVar10;
        } while (lVar6 < (s64)lVar1);
    }
    fVar9 = 0.0f;
joined_r0x0071000703f0:
    if (pfVar7 == (float *)0) return 0.0f;
LAB_7100070458:
    return pfVar7[5] + fVar9 * (pfVar7[6] - pfVar7[5]);
}

// 0x710160db40
u64 FUN_710160db40(u64 *param_1)
{
    u32 uVar1;
    float *pfVar2;
    float *pfVar3;
    u32 uVar4;
    s32 iVar5;
    float *pfVar6;
    u64 uVar7;
    s64 lVar8;
    float fVar9;
    float fVar10;
    float fVar11;

    pfVar3 = (float *)*param_1;
    pfVar6 = (float *)param_1[1];
    if ((s64)pfVar6 - (s64)pfVar3 == 0) return 0xffffffff;
    fVar9 = 0.0f;
    if (pfVar3 != pfVar6) {
        uVar7 = ((u64)((s64)pfVar6 - (s64)pfVar3) - 4U) >> 2;
        uVar1 = (u32)(s32)uVar7 + 1;
        if (uVar7 == 0) {
            fVar9 = 0.0f;
        } else {
            pfVar6 = (float *)0;
            s64 lVar8b = (s64)(((u64)uVar1 & 1) - 1) - (s64)uVar7;
            pfVar2 = pfVar3;
            do {
                lVar8b = lVar8b + 2;
                pfVar3 = pfVar2 + 2;
                uVar4 = (u32)(s32)(pfVar2[1] + (float)(s32)(*pfVar2 + (float)(s32)(u64)pfVar6));
                pfVar6 = (float *)(u64)uVar4;
                pfVar2 = pfVar3;
            } while (lVar8b != 0);
            fVar9 = (float)(s32)uVar4;
        }
        iVar5 = (s32)(u64)pfVar6;
        if ((uVar1 & 1) != 0) {
            iVar5 = (s32)(*pfVar3 + fVar9);
        }
        fVar9 = (float)iVar5;
    }
    lVar8 = *(s64 *)*DAT_71052c25b0;
    uVar4 = *(u32 *)(lVar8 + 0x84);
    *(s32 *)(lVar8 + 0x88) = *(s32 *)(lVar8 + 0x88) + 1;
    uVar1 = *(u32 *)(lVar8 + 0x78) ^ *(u32 *)(lVar8 + 0x78) << 0xb;
    *(u32 *)(lVar8 + 0x78) = *(u32 *)(lVar8 + 0x7c);
    *(u32 *)(lVar8 + 0x7c) = *(u32 *)(lVar8 + 0x80);
    *(u32 *)(lVar8 + 0x80) = uVar4;
    uVar1 = uVar1 ^ uVar1 >> 8 ^ uVar4 ^ uVar4 >> 0x13;
    *(u32 *)(lVar8 + 0x84) = uVar1;
    lVar8 = (s64)(param_1[1] - *param_1);
    if (lVar8 != 0) {
        fVar10 = 0.0f;
        uVar7 = 0;
        while ((fVar11 = *(float *)(*param_1 + uVar7 * 4),
                fVar11 == 0.0f || (fVar11 < 0.0f) != NAN(fVar11) ||
                (fVar10 = fVar10 + fVar11,
                 fVar10 < fVar9 * (float)uVar1 * DAT_7104472710 + 0.0f))) {
            uVar7 = uVar7 + 1;
            if ((u64)(lVar8 >> 2) <= uVar7) {
                return 0xffffffff;
            }
        }
        return uVar7 & 0xffffffff;
    }
    return 0xffffffff;
}

// ── 368-byte ───────────────────────────────────────────────────────────────────

// 0x71023edf50
void FUN_71023edf50(s64 param_1, s32 param_2, u64 *param_3)
{
    s64 lVar1;
    u32 uVar2;
    char cVar3;
    bool bVar4;
    u32 uVar5;
    u32 uVar6;
    s64 lVar7;
    u64 local_28;

    if (*(char *)(param_1 + 0x20) != '\0') return;
    FUN_71039c1490(param_1);
    if (param_2 != -1) {
        bVar4 = (*param_3 & 0xff) == 0;
        if (bVar4) {
            local_28 = 0;
        } else {
            local_28 = (u64)(u32)(s32)(((float)(*param_3 >> 0x20) * DAT_7104471598) / DAT_7104471e0c)
                       << 0x20;
        }
        local_28 = local_28 | (u64)(!bVar4);
        lVar1 = *(s64 *)(param_1 + 0x28) + 0x1a0;
        for (lVar7 = *(s64 *)(*(s64 *)(param_1 + 0x28) + 0x1a8); lVar1 != lVar7;
             lVar7 = *(s64 *)(lVar7 + 8)) {
            if (*(s32 *)(lVar7 + 0xe0) == param_2) {
                if (lVar1 == lVar7) break;
                uVar2 = *(u32 *)(lVar7 + 0x10);
                if (uVar2 < 0xc) {
                    if ((1u << (uVar2 & 0x1f) & 0xf0u) != 0) {
                        FUN_7102414dd0((void *)(lVar7 + 0x18));
                        goto LAB_71023ee060;
                    }
                    uVar2 = 1u << (uVar2 & 0x1f);
                    if ((uVar2 & 0xb00u) == 0) {
                        if ((uVar2 & 3u) == 0) goto LAB_71023ee060;
                        FUN_7102415b40((void *)(lVar7 + 0x18), &local_28);
                        break;
                    }
                    FUN_7102415b40((void *)(lVar7 + 0x18), &local_28);
                    uVar6 = 0;
                    uVar5 = 0;
                    cVar3 = *(char *)(lVar7 + 0xf0);
                } else {
LAB_71023ee060:
                    uVar6 = 1;
                    uVar5 = 1;
                    cVar3 = *(char *)(lVar7 + 0xf0);
                }
                if (cVar3 != '\0') {
                    *(u8 *)(lVar7 + 0xf0) = 0;
                    uVar5 = uVar6;
                }
                if (*(char *)(lVar7 + 0x100) != '\0') {
                    *(u8 *)(lVar7 + 0x100) = 0;
                }
                if (*(char *)(lVar7 + 0x198) != '\0') {
                    *(u8 *)(lVar7 + 0x198) = 0;
                }
                *(u32 *)(lVar7 + 0x10) = uVar5;
                break;
            }
        }
    }
    FUN_71039c14a0(param_1);
}

// ── 384-byte ───────────────────────────────────────────────────────────────────

// 0x7100224e50
bool FUN_7100224e50(s64 param_1, s64 param_2, u64 param_3, s64 param_4, s64 param_5)
{
    bool bVar1;
    u64 uVar2;
    u64 local_9a8[10];
    s64 local_978;
    char local_950[1279];
    char acStack_450[1024];

    if (param_3 < 0x400) return false;
    memset(acStack_450, 0, 0x400);
    memset(local_950 + 0x100, 0, 0x400);
    memset(local_950, 0, 0x100);
    local_978 = 0;
    memset(local_9a8, 0, sizeof(local_9a8));
    uVar2 = FUN_71001dc540(local_9a8, *(u64 *)(param_4 + 0x18));
    bVar1 = (uVar2 & 1) != 0;
    if (bVar1) {
        snprintf(local_950 + 0x100, 0x400, "%s", local_978);
        local_950[local_978 - (s64)local_9a8] = '\0';
        snprintf(local_950, (u64)(local_978 + 1 - (s64)local_9a8), "%s");
        local_950[local_978 - (s64)local_9a8] = '\0';
        snprintf(acStack_450, 0x400,
                 "GET %s HTTP/1.1\r\nHost: %s\r\nUpgrade: websocket\r\nConnection: upgrade\r\n"
                 "Sec-WebSocket-Key: %s\r\nSec-WebSocket-Version: 13\r\n"
                 "Sec-WebSocket-Protocol: %s\r\n\r\n",
                 local_950 + 0x100, local_950,
                 *(u64 *)(param_1 + 0x20), *(u64 *)(param_5 + 0x18));
        FUN_71001b5de0(acStack_450, param_2, param_3);
        *(u8 *)(param_2 + (s64)param_3 - 1) = 0;
    }
    return bVar1;
}

// 0x7101c591b0
void FUN_7101c591b0(s64 param_1, u32 param_2, u8 param_3, u8 param_4)
{
    bool bVar1;
    s64 *plVar2;
    s64 lVar3;
    s64 lVar4;

    if (*(s32 *)(*(s64 *)(param_1 + 0x1b70) + 0xe8) != 0) return;
    lVar3 = *(s64 *)(param_1 + 0x460);
    lVar4 = *(s64 *)(*(s64 *)(lVar3 + 0xf8) + 0x38);
    param_4 = param_4 & 1;
    if (lVar4 != 0) {
        *(u8 *)(lVar4 + 0x58) = (u8)(*(u8 *)(lVar4 + 0x58) & 0xfe) | param_4;
    }
    *(u8 *)(lVar3 + 0x15a) = param_4;
    lVar3 = *(s64 *)(param_1 + 0x460);
    plVar2 = *(s64 **)(lVar3 + 0xf8);
    (*(void (**)(s64 *, u8))(*plVar2 + 0x60))(plVar2, param_4);
    *(u8 *)(lVar3 + 0x159) = param_4;
    (*(void (**)( s64 *, u32))(**(s64 **)(param_1 + 0x300) + 0x70))(*(s64 **)(param_1 + 0x300), param_2 & 1);
    (*(void (**)( s64 *, u32))(**(s64 **)(param_1 + 0x300) + 0x60))(*(s64 **)(param_1 + 0x300), param_2 & 1);
    FUN_710376b3b0(*(u64 *)(param_1 + 0x300));
    plVar2 = *(s64 **)(param_1 + 0x2f8);
    lVar3 = *plVar2;
    if ((s64 *)**(s64 **)(lVar3 + 0x18) != (s64 *)0) {
        (*(void (**)(s64 *, s64))(*(s64 *)**(s64 **)(lVar3 + 0x18) + 0x2f8))(
            **(s64 ***)(lVar3 + 0x18), 0);
        lVar3 = *plVar2;
    }
    ui2d_apply_named_animation(1.0f, *(u64 *)(lVar3 + 8), "sel_off");
    *(u8 *)(param_1 + 0x431) = 0;
    *(u8 *)(param_1 + 0x422) = 0;
    *(u8 *)(param_1 + 0x424) = 0;
    if (((param_2 & 1) == 0) && (*(s32 *)(param_1 + 0x178) != 0xd)) {
        bVar1 = *(s32 *)(param_1 + 0x178) == 0xc;
    } else {
        bVar1 = true;
    }
    *(bool *)(param_1 + 0x1ca9) = bVar1;
    *(u8 *)(param_1 + 0x1b26) = param_3 & 1;
    *(u8 *)(param_1 + 0x651) = param_3 & 1;
    if ((param_3 & 1) == 0) {
        bVar1 = false;
    } else {
        bVar1 = *(char *)(param_1 + 0x652) != '\0';
    }
    FUN_710376b3b0(*(u64 *)(param_1 + 0x488));
    (*(void (**)( s64 *, bool))(**(s64 **)(param_1 + 0x488) + 0x70))(*(s64 **)(param_1 + 0x488), bVar1);
    (*(void (**)( s64 *, bool))(**(s64 **)(param_1 + 0x488) + 0x60))(*(s64 **)(param_1 + 0x488), bVar1);
}

// ── 400-byte ───────────────────────────────────────────────────────────────────

// 0x71001925f0
u32 FUN_71001925f0(s64 param_1)
{
    u32 uVar1 = *(u32 *)(param_1 + 0xc8);
    if ((uVar1 & 1) == 0) return 0;
    if ((uVar1 >> 1  & 1) == 0) return 1;
    if ((uVar1 >> 2  & 1) == 0) return 2;
    if ((uVar1 >> 3  & 1) == 0) return 3;
    if ((uVar1 >> 4  & 1) == 0) return 4;
    if ((uVar1 >> 5  & 1) == 0) return 5;
    if ((uVar1 >> 6  & 1) == 0) return 6;
    if ((uVar1 >> 7  & 1) == 0) return 7;
    if ((uVar1 >> 8  & 1) == 0) return 8;
    if ((uVar1 >> 9  & 1) == 0) return 9;
    if ((uVar1 >> 10 & 1) == 0) return 10;
    if ((uVar1 >> 11 & 1) == 0) return 0xb;
    if ((uVar1 >> 12 & 1) == 0) return 0xc;
    if ((uVar1 >> 13 & 1) == 0) return 0xd;
    if ((uVar1 >> 14 & 1) == 0) return 0xe;
    if ((uVar1 >> 15 & 1) == 0) return 0xf;
    if ((uVar1 >> 16 & 1) == 0) return 0x10;
    if ((uVar1 >> 17 & 1) == 0) return 0x11;
    if ((uVar1 >> 18 & 1) == 0) return 0x12;
    if ((uVar1 >> 19 & 1) == 0) return 0x13;
    if ((uVar1 >> 20 & 1) == 0) return 0x14;
    if ((uVar1 >> 21 & 1) == 0) return 0x15;
    if ((uVar1 >> 22 & 1) == 0) return 0x16;
    if ((uVar1 >> 23 & 1) == 0) return 0x17;
    if ((uVar1 >> 24 & 1) == 0) return 0x18;
    if ((uVar1 >> 25 & 1) == 0) return 0x19;
    if ((uVar1 >> 26 & 1) == 0) return 0x1a;
    if ((uVar1 >> 27 & 1) == 0) return 0x1b;
    if ((uVar1 >> 28 & 1) == 0) return 0x1c;
    if ((uVar1 >> 29 & 1) == 0) return 0x1d;
    if ((uVar1 >> 30 & 1) == 0) return 0x1e;
    return (s32)uVar1 >= 0 ? 0x1f : 0xfffffffdU;
}

// 0x71001dfee0
void FUN_71001dfee0(s64 param_1)
{
    s64 obj = *(s64 *)(param_1 + 8);
    ((void (*)(s64, s64))(*(s64 *)(*(s64 *)obj + 0x80)))(obj, param_1);
}

// ── 416-byte ───────────────────────────────────────────────────────────────────

// 0x7102d9aa60
void FUN_7102d9aa60(s64 *param_1)
{
    s16 sVar1;
    s64 *plVar2;
    u64 uVar3;
    void **puVar4;
    s64 *plVar5;
    u32 *puVar6;
    s64 lVar7;
    s64 lVar8;
    u64 local_48;
    u32 local_34;

    if (*(char *)((s64)param_1 + 0xc) != '\0') return;
    puVar6 = (u32 *)*DAT_71052b84f8;
    if (*puVar6 < 4) goto LAB_7102d9abd8;
    if (puVar6[6] == 0) {
        lVar7 = *(s64 *)(puVar6 + 2);
        plVar2 = (s64 *)*param_1;
        lVar8 = *plVar2;
        if ((((s64 *)(lVar7 + 0x50) == plVar2) || (*(s64 **)(lVar8 + 8) != plVar2)) ||
            (plVar5 = (s64 *)plVar2[1], (s64 *)*plVar5 != plVar2)) {
            plVar5 = (s64 *)plVar2[1];
        }
        *plVar5 = lVar8;
        *(s64 **)(lVar8 + 8) = plVar5;
        *(s64 *)(lVar7 + 0x48) = *(s64 *)(lVar7 + 0x48) - 1;
        lVar7 = plVar2[2];
        if (lVar7 != 0) {
            sVar1 = *(s16 *)(lVar7 + 8) - 1;
            *(s16 *)(lVar7 + 8) = sVar1;
            if ((sVar1 < 1) && ((s64 *)plVar2[2] != (s64 *)0)) {
                (*(void (**)(void))(*(s64 *)plVar2[2] + 8))();
            }
            plVar2[2] = 0;
        }
        if (plVar2 != (s64 *)0) {
            FUN_710392e590((s64)plVar2);
        }
        goto LAB_7102d9abd8;
    }
    lVar7 = *(s64 *)(puVar6 + 4);
    lVar8 = *param_1;
    plVar2 = (s64 *)je_aligned_alloc(0x10, 0x18);
    if (plVar2 == (s64 *)0) {
        if (DAT_7105331f00 != (s64 *)0) {
            local_34 = 0;
            local_48 = 0x18;
            uVar3 = ((u64 (*)(s64 *, u32 *, u64 *))(*(s64 *)(*DAT_7105331f00 + 0x30)))(
                DAT_7105331f00, &local_34, &local_48);
            if (((uVar3 & 1) != 0) &&
                (plVar2 = (s64 *)je_aligned_alloc(0x10, 0x18), plVar2 != (s64 *)0))
                goto LAB_7102d9ab08;
        }
        plVar2 = (s64 *)0;
    }
LAB_7102d9ab08:
    lVar8 = *(s64 *)(lVar8 + 0x10);
    plVar2[2] = lVar8;
    if (lVar8 != 0) {
        *(s16 *)(lVar8 + 8) = *(s16 *)(lVar8 + 8) + 1;
    }
    puVar4 = *(void ***)(lVar7 + 0x58);
    *plVar2 = lVar7 + 0x50;
    plVar2[1] = (s64)puVar4;
    *(s64 **)(lVar7 + 0x58) = plVar2;
    *puVar4 = plVar2;
    *(s64 *)(lVar7 + 0x48) = *(s64 *)(lVar7 + 0x48) + 1;
    puVar6[7] = puVar6[7] + 1;
LAB_7102d9abd8:
    *(u8 *)((s64)param_1 + 0xc) = 1;
}

// ── 432-byte ───────────────────────────────────────────────────────────────────

// 0x71013c1330
u64 FUN_71013c1330(s64 param_1)
{
    u32 uVar1;
    s64 lVar2;
    u32 uVar3;
    u32 uVar4;
    u64 *puVar5;

    if (*(char *)(param_1 + 8) != '\0') return 0;
    uVar3 = *(u32 *)(param_1 + 0x1cc);
    if (uVar3 == 0xffffffff) {
        uVar3 = *(u32 *)(param_1 + 0x1d0);
    } else {
        if (uVar3 < 8) {
            uVar3 = *(u32 *)(DAT_71052c40f0 + (s64)(s32)uVar3 * 4 + 0x298);
        } else {
            uVar3 = 0xffffffff;
        }
        if (*(u32 *)(param_1 + 0x1d0) != uVar3) {
            *(u32 *)(param_1 + 0x1d0) = uVar3;
        }
    }
    lVar2 = DAT_71053388b0;
    if (DAT_71053388b0 != 0) {
        if (uVar3 < 10) {
            puVar5 = (u64 *)DAT_7105338860[(s32)uVar3];
            if (puVar5 == (u64 *)0) goto LAB_71013c13c0;
        } else {
            puVar5 = (u64 *)&DAT_7105338830;
        }
        if (*(char *)(puVar5[2] + 0xb8) == '\0') {
            if (*(s32 *)(param_1 + 0x1d4) == -1) return 0;
            uVar4 = 0;
            *(s32 *)(param_1 + 0x1d4) = 0xffffffff;
            goto LAB_71013c14b4;
        }
    }
LAB_71013c13c0:
    if (uVar3 == *(u32 *)(param_1 + 0x1d4)) {
        if (uVar3 == 0xffffffff) {
LAB_71013c1428:
            puVar5 = (u64 *)0;
        } else {
            puVar5 = (u64 *)&DAT_7105338830;
            if (((9 < uVar3) || (*(char *)(DAT_71053388b0 + 8) == '\0')) ||
                (puVar5 = (u64 *)DAT_7105338860[(s32)uVar3], puVar5 != (u64 *)0)) {
                uVar1 = *(u32 *)(puVar5[2] + 0x9c) - 1;
                if (6 < uVar1) goto LAB_71013c1428;
                puVar5 = (u64 *)(u64)*(u32 *)(&DAT_7104752de0[0] + (s64)(s32)uVar1 * 4);
            }
        }
        if ((s32)(u64)puVar5 == *(s32 *)(param_1 + 0x1d8)) return 0;
    } else {
        *(u32 *)(param_1 + 0x1d4) = uVar3;
    }
    if (((uVar3 == 0xffffffff) ||
         (((puVar5 = (u64 *)&DAT_7105338830,
            uVar3 < 10 && (*(char *)(lVar2 + 8) != '\0')) &&
           (puVar5 = (u64 *)DAT_7105338860[(s32)uVar3], puVar5 == (u64 *)0)))) ||
        (uVar3 = *(u32 *)(puVar5[2] + 0x9c) - 1, 6 < uVar3)) {
        uVar4 = 0;
    } else {
        uVar4 = *(u32 *)(&DAT_7104752de0[0] + (s64)(s32)uVar3 * 4);
    }
LAB_71013c14b4:
    *(u32 *)(param_1 + 0x1d8) = uVar4;
    FUN_7101b8e6e0(*(u64 *)(*(s64 *)(param_1 + 0x1e8) + 0x80));
    return 1;
}

// ── 464-byte ───────────────────────────────────────────────────────────────────

// 0x71016ccc70
void FUN_71016ccc70(s64 param_1)
{
    if (*(char *)(param_1 + 99) != '\0') return;
    *(u8 *)(param_1 + 0x3d) = 1;
    *(u32 *)(param_1 + 0x4a) = 0;
    *(u16 *)(param_1 + 0x4e) = 0;
    *(u16 *)(param_1 + 0xa0) = 0;
    FUN_71016cce40(param_1, *(u16 *)(param_1 + 0x5a));
    *(u8 *)(param_1 + 0x9763) = 0;
    *(u8 *)(param_1 + 0xd73b) = 0;
    *(u8 *)(param_1 + 0x11713) = 0;
    *(u8 *)(param_1 + 0x156eb) = 0;
    *(u8 *)(param_1 + 0x196c3) = 0;
    *(u8 *)(param_1 + 0x1d69b) = 0;
    *(u8 *)(param_1 + 0x21673) = 0;
    *(u8 *)(param_1 + 0x2564b) = 0;
    *(u8 *)(param_1 + 0x29623) = 0;
    *(u8 *)(param_1 + 0x2d5fb) = 0;
    *(u8 *)(param_1 + 0x315d3) = 0;
    *(u8 *)(param_1 + 0x355ab) = 0;
    *(u8 *)(param_1 + 0x39583) = 0;
    *(u8 *)(param_1 + 0x3d55b) = 0;
    *(u8 *)(param_1 + 0x41533) = 0;
    *(u8 *)(param_1 + 0x4550b) = 0;
    *(u16 *)(param_1 + 0x494c8) = 0xff;
    *(u32 *)(param_1 + 0x494cc) = 0;
    *(u16 *)(param_1 + 0x494d0) = 0xff;
    *(u32 *)(param_1 + 0x494d4) = 0;
    *(u16 *)(param_1 + 0x494d8) = 0xff;
    *(u32 *)(param_1 + 0x494dc) = 0;
    *(u16 *)(param_1 + 0x494e0) = 0xff;
    *(u32 *)(param_1 + 0x494e4) = 0;
    *(u16 *)(param_1 + 0x494e8) = 0xff;
    *(u32 *)(param_1 + 0x494ec) = 0;
    *(u16 *)(param_1 + 0x494f0) = 0xff;
    *(u32 *)(param_1 + 0x494f4) = 0;
    *(u16 *)(param_1 + 0x494f8) = 0xff;
    *(u32 *)(param_1 + 0x494fc) = 0;
    *(u16 *)(param_1 + 0x49500) = 0xff;
    *(u32 *)(param_1 + 0x49504) = 0;
    FUN_71016cd070(param_1, 1);
}

// ── 496-byte ───────────────────────────────────────────────────────────────────

// 0x7102fece10
void FUN_7102fece10(f32 param_1, s64 param_2)
{
    s64 lVar1;
    float fVar2;
    float fVar3;
    float fVar4;
    float fVar5;

    if (*(float *)(param_2 + 0xe8) == 0.0f) return;
    fVar2 = fminf(*(float *)(param_2 + 0xe8) * param_1 + *(float *)(param_2 + 0xf0), 1.0f);
    *(float *)(param_2 + 0xf0) = fVar2;
    lVar1 = *(s64 *)(param_2 + 0x40);
    fVar3 = DAT_7104471eb0;
    if (lVar1 != 0) {
        fVar4 = (float)*(s32 *)(lVar1 + 0x40) * DAT_7104472be8;
        fVar5 = (float)*(s32 *)(lVar1 + 0x44) * DAT_71044720b4;
        *(u8 *)(lVar1 + 0x49) = 1;
        *(u64 *)(lVar1 + 0x38) = 0;
        *(float *)(lVar1 + 0x30) = fVar4 + fVar3;
        *(float *)(lVar1 + 0x34) = fVar5 - fVar2;
    }
    fVar3 = DAT_7104471eb0;
    lVar1 = *(s64 *)(param_2 + 0x48);
    if (lVar1 != 0) {
        fVar4 = (float)*(s32 *)(lVar1 + 0x44) * DAT_71044720b4;
        fVar2 = (float)*(s32 *)(lVar1 + 0x40) * DAT_7104472be8;
        fVar5 = *(float *)(param_2 + 0xf0) * DAT_71044720b4;
        *(u8 *)(lVar1 + 0x49) = 1;
        *(u64 *)(lVar1 + 0x38) = 0;
        *(float *)(lVar1 + 0x30) = fVar2 + fVar3;
        *(float *)(lVar1 + 0x34) = fVar4 - fVar5;
    }
    fVar3 = DAT_7104471eb0;
    lVar1 = *(s64 *)(param_2 + 0x50);
    if (lVar1 != 0) {
        fVar4 = (float)*(s32 *)(lVar1 + 0x44) * DAT_71044720b4;
        fVar2 = (float)*(s32 *)(lVar1 + 0x40) * DAT_7104472be8;
        fVar5 = *(float *)(param_2 + 0xf0) * DAT_71044720b4;
        *(u8 *)(lVar1 + 0x49) = 1;
        *(u64 *)(lVar1 + 0x38) = 0;
        *(float *)(lVar1 + 0x30) = fVar2 + fVar3;
        *(float *)(lVar1 + 0x34) = fVar4 - fVar5;
    }
    fVar3 = DAT_7104471eb0;
    lVar1 = *(s64 *)(param_2 + 0x58);
    if (lVar1 != 0) {
        fVar4 = (float)*(s32 *)(lVar1 + 0x44) * DAT_71044720b4;
        fVar2 = (float)*(s32 *)(lVar1 + 0x40) * DAT_7104472be8;
        fVar5 = *(float *)(param_2 + 0xf0) * DAT_71044720b4;
        *(u8 *)(lVar1 + 0x49) = 1;
        *(u64 *)(lVar1 + 0x38) = 0;
        *(float *)(lVar1 + 0x30) = fVar2 + fVar3;
        *(float *)(lVar1 + 0x34) = fVar4 - fVar5;
    }
    lVar1 = *(s64 *)(param_2 + 0xc0);
    fVar3 = (float)*(s32 *)(lVar1 + 0x30) * DAT_7104471074 + DAT_7104472278;
    fVar2 = (float)*(s32 *)(lVar1 + 0x34) * DAT_71044720b4;
    fVar4 = *(float *)(param_2 + 0xf0) * DAT_71044720b4;
    *(u64 *)(lVar1 + 0x28) = 0;
    *(float *)(lVar1 + 0x20) = fVar3;
    *(float *)(lVar1 + 0x24) = fVar2 - fVar4;
}

// 0x71039bc200
u64 FUN_71039bc200(u64 *param_1, u32 *param_2, u64 param_3)
{
    u32 uVar1;
    u8 bVar2;
    u8 bVar3;
    u32 uVar4;
    u32 uVar5;
    s64 lVar6;
    u64 uVar7;

    if (param_3 < 5) return 5;
    if (*param_2 != 0xfd2fb527) {
        if (*param_2 >> 4 != 0x184d2a5) {
            return 0xfffffffffffffff6ULL;
        }
        if (param_3 < 8) return 8;
        param_1[1] = 0;
        param_1[2] = 0;
        *param_1 = 0;
        *param_1 = (u64)param_2[1];
        *(u32 *)(param_1 + 1) = 0;
        return 0;
    }
    bVar2 = (u8)param_2[1];
    lVar6 = 5;
    if ((bVar2 & 0x20) == 0) lVar6 = 6;
    uVar7 = (u64)*(s64 *)(&DAT_710446f740[0] + (u64)(bVar2 >> 6) * 8) +
            (u64)*(s64 *)(&DAT_7104470380[0] + ((u64)bVar2 & 3) * 8) + (u64)lVar6 +
            (u64)((bVar2 >> 6 == 0) & (bVar2 >> 5));
    if (param_3 < uVar7) return uVar7;
    if ((bVar2 >> 3 & 1) != 0) return 0xfffffffffffffff2ULL;
    if ((bVar2 >> 5 & 1) == 0) {
        uVar4 = (u32)(*(u8 *)((s64)param_2 + 5) >> 3);
        if (0x1b < uVar4 + 10) return 0xfffffffffffffff2ULL;
        uVar4 = 0x400u << (u64)uVar4;
        uVar4 = uVar4 + (uVar4 >> 3) * (*(u8 *)((s64)param_2 + 5) & 7);
        lVar6 = 6;
    } else {
        uVar4 = 0;
        lVar6 = 5;
    }
    bVar3 = bVar2 & 3;
    if (bVar3 == 3) {
        uVar5 = *(u32 *)((s64)param_2 + lVar6);
        lVar6 = lVar6 + 4;
    } else if (bVar3 == 2) {
        uVar5 = (u32)*(u16 *)((s64)param_2 + lVar6);
        lVar6 = lVar6 + 2;
    } else if (bVar3 == 1) {
        uVar5 = (u32)*(u8 *)((s64)param_2 + lVar6);
        lVar6 = lVar6 + 1;
    } else {
        uVar5 = 0;
    }
    bVar3 = bVar2 >> 6;
    if (bVar3 == 1) {
        uVar7 = (u64)*(u16 *)((s64)param_2 + lVar6) + 0x100;
    } else if (bVar3 == 2) {
        uVar7 = (u64)*(u32 *)((s64)param_2 + lVar6);
    } else if (bVar3 == 3) {
        uVar7 = *(u64 *)((s64)param_2 + lVar6);
    } else if ((bVar2 >> 5 & 1) == 0) {
        uVar7 = 0;
    } else {
        uVar7 = (u64)*(u8 *)((s64)param_2 + lVar6);
    }
    uVar1 = (u32)uVar7;
    if (uVar4 != 0) uVar1 = uVar4;
    if (0x8000000 < uVar1) return 0xfffffffffffffff2ULL;
    *param_1 = uVar7;
    *(u32 *)(param_1 + 1) = uVar1;
    *(u32 *)((s64)param_1 + 0xc) = uVar5;
    *(u32 *)(param_1 + 2) = (u32)(bVar2 >> 2 & 1);
    return 0;
}

// ── 528-byte ───────────────────────────────────────────────────────────────────

// 0x71023ee0c0
void FUN_71023ee0c0(s64 param_1, u64 param_2)
{
    u8 *puVar1;
    char cVar2;
    u8 *puVar3;
    u32 uVar4;
    u32 uVar5;
    u32 uVar6;
    u32 uVar7;
    u8 *puVar8;
    u64 *puVar9;
    s32 iVar10;
    u8 *puVar11;

    if (*(char *)(param_1 + 0x20) != '\0') return;
    FUN_71039c1490(param_1);
    puVar8 = *(u8 **)(param_1 + 0x28);
    iVar10 = 1;
    puVar9 = (u64 *)(puVar8 + 0x1a8);
LAB_71023ee138:
    puVar11 = (u8 *)*puVar9;
LAB_71023ee148:
    puVar3 = puVar8;
    if (iVar10 != 1) {
        puVar3 = puVar11;
    }
    puVar1 = puVar3 + 0x18;
    do {
        if (iVar10 == 2) {
            if (puVar8 + 0x1a0 == puVar11) {
                *(u8 *)puVar8 = 0;
                FUN_71039c14a0(param_1);
                return;
            }
            if (*(u32 *)(puVar11 + 0x10) < 0xc) {
                uVar4 = 1u << (*(u32 *)(puVar11 + 0x10) & 0x1f);
                if ((uVar4 & 0xf0u) != 0) {
                    FUN_7102414dd0((void *)(puVar11 + 0x18));
                    goto LAB_71023ee258;
                }
                if ((uVar4 & 0xb00u) != 0) {
                    FUN_7102415b40((void *)(puVar11 + 0x18), (void *)param_2);
                    uVar7 = 0;
                    uVar6 = 0;
                    cVar2 = (char)puVar11[0xf0];
                    goto joined_r0x0071023ee244;
                }
                if ((uVar4 & 3u) == 0) goto LAB_71023ee258;
                FUN_7102415b40((void *)(puVar11 + 0x18), (void *)param_2);
            } else {
LAB_71023ee258:
                uVar7 = 1;
                uVar6 = 1;
                cVar2 = (char)puVar11[0xf0];
joined_r0x0071023ee244:
                if (cVar2 != '\0') {
                    puVar11[0xf0] = 0;
                    uVar6 = uVar7;
                }
                if (puVar11[0x100] != '\0') puVar11[0x100] = 0;
                if (puVar11[0x198] != '\0') puVar11[0x198] = 0;
                *(u32 *)(puVar11 + 0x10) = uVar6;
            }
            puVar9 = (u64 *)(puVar11 + 8);
            iVar10 = 2;
            goto LAB_71023ee138;
        }
        uVar4 = *(u32 *)(puVar3 + 0x10);
        if (uVar4 < 0xc) {
            uVar4 = 1u << (uVar4 & 0x1f);
            if ((uVar4 & 0xf0u) != 0) {
                FUN_7102414dd0((void *)puVar1);
                goto LAB_71023ee1a8;
            }
            if ((uVar4 & 0xb00u) != 0) {
                FUN_7102415b40((void *)puVar1, (void *)param_2);
                uVar5 = 0;
                uVar4 = 0;
                cVar2 = (char)puVar3[0xf0];
                goto joined_r0x0071023ee194;
            }
            if ((uVar4 & 3u) == 0) goto LAB_71023ee1a8;
            FUN_7102415b40((void *)puVar1, (void *)param_2);
        } else {
LAB_71023ee1a8:
            uVar5 = 1;
            uVar4 = 1;
            cVar2 = (char)puVar3[0xf0];
joined_r0x0071023ee194:
            if (cVar2 != '\0') {
                puVar3[0xf0] = 0;
                uVar4 = uVar5;
            }
            if (puVar3[0x100] != '\0') puVar3[0x100] = 0;
            if (puVar3[0x198] != '\0') puVar3[0x198] = 0;
            *(u32 *)(puVar3 + 0x10) = uVar4;
        }
        if (iVar10 == 0) break;
        if (iVar10 == 1) {
            iVar10 = 2;
            puVar9 = (u64 *)(puVar8 + 0x1a8);
            goto LAB_71023ee138;
        }
    } while (true);
    iVar10 = 1;
    goto LAB_71023ee148;
}
