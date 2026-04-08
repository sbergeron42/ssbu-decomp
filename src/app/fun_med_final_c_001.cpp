#include "types.h"
namespace std { namespace __1 {
template<bool> struct __vector_base_common {
    [[noreturn]] static void __throw_out_of_range();
};
}}

// MEDIUM-tier FUN_* decompilation -- pool-c range 0x7102000000-0x7103FFFFFF
// Batch 001: 18 functions (scene dispatch, readiness check, state machines,
//            fighter slot lookup, time calc, spirit names, sort helpers)

// ─── External globals ────────────────────────────────────────────────────
extern u64 DAT_7105324cc8;
extern u64 DAT_7105323fd8;
extern u64 DAT_7105324cb8;
extern u64 DAT_7105323fa0;
extern u64 DAT_710532e8f8;
extern u64 DAT_7105324c98;
extern u64 DAT_7105324cd0;
extern u64 DAT_710532e838;
extern u64 DAT_71052c3c58;
extern u8  DAT_7105328f58[];
extern u64 DAT_710532e730;
extern u64 DAT_7105328fa0;
extern u64 DAT_7104ad9bc0[];
extern u64 DAT_7105331f20;
extern u8  DAT_71043053b5[];
extern void* PTR_LAB_7104f613d8;
extern void* PTR_LAB_71050c4348;
extern void* PTR_LAB_71050b9f88;
extern s64 *lib_Singleton_FighterManager_instance_;

// ─── External functions ──────────────────────────────────────────────────
extern "C" void FUN_7102415ff0(u32*);
extern "C" void FUN_7102417470(u32*);
extern "C" u64  FUN_71032a3620(u64, u8);
extern "C" u16  FUN_71032a51a0(u64, u64);
extern "C" u32  FUN_71032a7250(s64, u64);
extern "C" void FUN_71032a4890(void*, u64, u64);
extern "C" void FUN_71003a4ca0(void*, const char*, u8);
extern "C" void FUN_7102523d70(u64, u64, void*);
extern "C" void FUN_7101609af0(void*, void*);
extern "C" void FUN_7103540450(u64);
extern "C" void FUN_7103540560(u64, s32);
extern "C" u64  FUN_710353d360(u32, const char*);
extern "C" void ui2d_apply_named_animation(u32, u64, void*);
extern "C" void FUN_7102523c10(void);
extern "C" void FUN_7102524ce0(void);
extern "C" void FUN_7102524e70(void);
extern "C" void FUN_7102525000(void);
extern "C" void FUN_7102525180(void);
extern "C" int  strcmp(const char*, const char*);
extern "C" void _ZNSt3__120__vector_base_commonILb1EE20__throw_out_of_rangeEv();

// ─────────────────────────────────────────────────────────────────────────
// FUN_71023668e0  size=1056
// Scene init-by-name: hashes the scene name, then initialises a scene
// config struct.  param_2[0] = hash of name, (char*)&param_2[2] = name.
// ─────────────────────────────────────────────────────────────────────────
u64 FUN_71023668e0(u8* param_1, u32* param_2)
{
    u32  uVar1 = param_2[0];
    const char* pcVar4;
    u32  uVar3;

    if (uVar1 < 0x4d1b6eabu) return 0;

    if (uVar1 == 0xe6c44dfeu) {
        if (strcmp((const char*)(param_2 + 2), "OptionButtonScene") != 0) return 0;
        *(u64*)(param_1 + 0x10) = 0;
        *(u64*)(param_1 + 0x18) = 0;
        *(u32*)(param_1 + 0x158) = 0;
        *(u64*)(param_1 + 0x160) = 0xffffffff;
        *(u32*)(param_1 + 0x168) = 0xffffffff;
        uVar3 = 4;
        goto LAB_init;
    }
    if (uVar1 == 0x4d1b6eabu) {
        if (strcmp((const char*)(param_2 + 2), "OptionTopScene") != 0) return 0;
        *(u64*)(param_1 + 0x10) = 0;
        *(u64*)(param_1 + 0x18) = 0;
        *(u32*)(param_1 + 0x158) = 0;
        *(u64*)(param_1 + 0x160) = 0xffffffff;
        *(u32*)(param_1 + 0x168) = 0xffffffff;
        uVar3 = 3;
        goto LAB_init;
    }
    if (uVar1 < 0xbc861f42u) {
        if ((s32)uVar1 < 0x5108b424) {
            if (uVar1 == 0xb7a388d9u) {
                if (strcmp((const char*)(param_2 + 2), "OptionVideoScene") != 0) return 0;
                *(u64*)(param_1 + 0x160) = 0xffffffff;
                *(u32*)(param_1 + 0x168) = 0xffffffff;
                uVar3 = 0xd;
                *(u64*)(param_1 + 0x10) = 0;
                *(u64*)(param_1 + 0x18) = 0;
                *(u32*)(param_1 + 0x158) = 0;
                goto LAB_init;
            }
            if (uVar1 != 0x4e29d243u) return 0;
            pcVar4 = "OptionSoundScene";
        } else {
            if (uVar1 != 0x535c066eu) {
                if (uVar1 != 0x5108b424u) return 0;
                pcVar4 = "OptionMeleeScene";
                goto LAB_cmp6;
            }
            pcVar4 = "SoundTestScene";
        }
    } else {
        if (uVar1 == 0xbc861f42u) {
            if (strcmp((const char*)(param_2 + 2), "OptionLanguageScene") != 0) return 0;
            *(u64*)(param_1 + 0x10) = 0;
            *(u64*)(param_1 + 0x18) = 0;
            *(u32*)(param_1 + 0x158) = 0;
            *(u64*)(param_1 + 0x160) = 0xffffffff;
            *(u32*)(param_1 + 0x168) = 0xffffffff;
            uVar3 = 5;
            goto LAB_init;
        }
        if (0xf8973ff8u < uVar1) {
            if (uVar1 == 0xff126b7au) {
                pcVar4 = "CharaSelectScene";
            } else {
                if (uVar1 != 0xf8973ff9u) return 0;
                pcVar4 = "MeleeRuleScene";
            }
            goto LAB_cmp6;
        }
        if (uVar1 < 0xe33b8f27u) {
            if (uVar1 != 0xbe42ef4fu) return 0;
            if (strcmp((const char*)(param_2 + 2), "OptionOnlineScene") != 0) return 0;
            *(u64*)(param_1 + 0x10) = 0;
            *(u64*)(param_1 + 0x18) = 0;
            *(u32*)(param_1 + 0x158) = 0;
            *(u64*)(param_1 + 0x160) = 0xffffffff;
            *(u32*)(param_1 + 0x168) = 0xffffffff;
            uVar3 = 0xc;
            goto LAB_init;
        }
        if (uVar1 != 0xe33b8f27u) return 0;
        pcVar4 = "StageSelectScene";
    }

    {
        s32 iVar2 = strcmp((const char*)(param_2 + 2), pcVar4);
        if (iVar2 != 0) return 0;
        *(u64*)(param_1 + 0x10) = 0;
        *(u64*)(param_1 + 0x18) = 0;
        *(u32*)(param_1 + 0x158) = 0;
        *(u64*)(param_1 + 0x160) = 0xffffffff;
        *(u32*)(param_1 + 0x168) = 0xffffffff;
        uVar3 = 9;
        goto LAB_init;
    }

LAB_cmp6:
    {
        s32 iVar2 = strcmp((const char*)(param_2 + 2), pcVar4);
        if (iVar2 != 0) return 0;
        *(u64*)(param_1 + 0x10) = 0;
        *(u64*)(param_1 + 0x18) = 0;
        *(u32*)(param_1 + 0x158) = 0;
        *(u64*)(param_1 + 0x160) = 0xffffffff;
        *(u32*)(param_1 + 0x168) = 0xffffffff;
        uVar3 = 6;
    }

LAB_init:
    *(u8*) (param_1 + 0x16c) = 0;
    *(u64*)(param_1 + 0x148) = 0;
    *(u64*)(param_1 + 0x150) = 0;
    *(u64*)(param_1 + 0x138) = 0;
    *(u64*)(param_1 + 0x140) = 0;
    *(u64*)(param_1 + 0x128) = 0;
    *(u64*)(param_1 + 0x130) = 0;
    *(u64*)(param_1 + 0x118) = 0;
    *(u64*)(param_1 + 0x120) = 0;
    *(u32*)(param_1 + 0x110) = uVar3;
    *(u32*)(param_1 + 0x15c) = 1;
    *(u32*)(param_1 + 0x114) = 2;
    return 1;
}

// ─────────────────────────────────────────────────────────────────────────
// FUN_7102389af0  size=288
// Global readiness check: returns false if any manager is still loading.
// ─────────────────────────────────────────────────────────────────────────
bool FUN_7102389af0(void)
{
    if (*(s32*)(*(s64*)(DAT_7105324cc8 + 8) + 0xb8) != 0) return false;
    if (*(s32*)(*(s64*)(DAT_7105323fd8 + 8) + 200) != 0) return false;
    if (*(s32*)(*(s64*)(DAT_7105324cb8 + 8) + 0xa8) != 0) return false;
    if (*(s32*)(*(s64*)(DAT_7105323fa0 + 8) + 0xa8) != 0) return false;
    if (*(s32*)(*(s64*)(DAT_710532e8f8 + 8) + 200) != 0) return false;
    if (*(s32*)(*(s64*)(DAT_7105324c98 + 8) + 0x108) != 0) return false;
    if (*(s32*)(*(s64*)(DAT_7105324cd0 + 8) + 0xa8) != 0) return false;
    if ((DAT_710532e838 != 0) &&
        (*(s8*)(*(s64*)(DAT_710532e838 + 8) + 0x170) != '\0')) return false;
    if (*(s8*)(*(s64*)(*(s64*)(DAT_71052c3c58 + 8) + 0x80) + 0x244) != '\0') {
        return *(s32*)(*(s64*)(*(s64*)(DAT_71052c3c58 + 8) + 0x90) + 0x10) == 0;
    }
    return true;
}

// ─────────────────────────────────────────────────────────────────────────
// FUN_7102407130  size=336
// Copy vtable+field from param_1 into param_2 struct.
// ─────────────────────────────────────────────────────────────────────────
void FUN_7102407130(u8* param_1, u64* param_2)
{
    *param_2     = (u64)&PTR_LAB_71050b9f88;
    param_2[1]   = *(u64*)(param_1 + 8);
}

// ─────────────────────────────────────────────────────────────────────────
// FUN_7102416c00  size=240
// State machine step: advances *param_1 (state) through animation stages.
// ─────────────────────────────────────────────────────────────────────────
void FUN_7102416c00(u32* param_1)
{
    u32 uVar1;

    if (*(u8*)((u8*)param_1 + 4) == '\0') return;

    switch (*param_1) {
    case 0:
        if (*(u8*)(DAT_7105328f58 + (s64)(s32)param_1[2] * 5 + 3) == '\0') return;
        uVar1 = 1;
        break;
    default:
        return;
    case 2:
        FUN_7102415ff0(param_1 + 2);
        if (*(u8*)((u8*)param_1 + 5) == '\0') goto LAB_done;
        uVar1 = 6;
        break;
    case 3:
        FUN_7102415ff0(param_1 + 2);
        uVar1 = 4;
        break;
    case 4:
        if (*(u8*)(DAT_7105328f58 + (s64)(s32)param_1[2] * 5 + 2) == '\0') return;
        uVar1 = 5;
        break;
    case 6:
        if (*(u8*)(DAT_7105328f58 + (s64)(s32)param_1[2] * 5 + 2) != '\0') {
            *param_1 = 7;
        }
        // fallthrough
    case 7:
        if (*(u8*)((u8*)param_1 + 5) != '\0') return;
LAB_done:
        FUN_7102417470(param_1);
        uVar1 = 8;
        break;
    }
    *param_1 = uVar1;
}

// ─────────────────────────────────────────────────────────────────────────
// FUN_7102496c10  size=352
// Fighter slot lookup: returns a FighterObject* (or 0/1) for a given slot.
// ─────────────────────────────────────────────────────────────────────────
s64 FUN_7102496c10(u8* param_1, u32 param_2)
{
    if (param_1 == nullptr) return 0;
    if (*(u8*)(param_1 + 8) == '\0') return 0;

    if (*(u8*)(param_1 + 0xec) == '\0') {
        if (*(s64*)(param_1 + 0x78) == *(s64*)(param_1 + 0x70)) return 0;
        if (7 < param_2) return 0;
    } else {
        if (7 < param_2) return 0;
    }

    s64 lVar4 = *(s64*)(*lib_Singleton_FighterManager_instance_ +
                        (s64)(s32)((u64)param_2 << 0x20 >> 0x1d) + 0x20);
    if (lVar4 == 0) return 0;
    if (*(s32*)(*(s64*)(lVar4 + 0xf8) + 0x28) == 0) return 0;

    u64*  plVar5 = *(u64**)(param_1 + 0x70);
    u64*  plVar1 = *(u64**)(param_1 + 0x78);

    if (*(u8*)(param_1 + 0x49) == '\x01') {
        s64 result = 1;
        for (; plVar5 != plVar1; plVar5++) {
            u8 cVar2 = *(u8*)(*plVar5 + 0x78);
            if ((*(u8*)(*plVar5 + 0x10) == '\x01') &&
                (cVar2 == '\x01' || cVar2 == '\x06')) return 0;
        }
        return result;
    } else {
        if (plVar5 == plVar1) return 0;
        s64 result = 0;
        do {
            if (*(u8*)(*plVar5 + 0x78) != '\x01') {
                u32 uVar3 = *(u32*)(*plVar5 + 0x7c);
                if (uVar3 == 0xffffffff) return 1;
                if (7 < uVar3) __builtin_trap(); // abort()
                lVar4 = *(s64*)(*lib_Singleton_FighterManager_instance_ + (s64)(s32)uVar3 * 8 + 0x20);
                if ((lVar4 != 0) && (*(u8*)(lVar4 + 0x5920) != '\x06')) return 1;
            }
            plVar5++;
            result = 0;
        } while (plVar1 != plVar5);
        return result;
    }
}

// ─────────────────────────────────────────────────────────────────────────
// FUN_7102512800  size=240
// Decomposes a nanosecond timestamp into (hours, minutes) relative to
// a base time stored in param_1.  Returns {hours, minutes} in x0:x1.
// ─────────────────────────────────────────────────────────────────────────
struct TimePair { s64 hours; s64 minutes; };
TimePair FUN_7102512800(u8* param_1)
{
    if ((*(u8*)(param_1 + 0x80) == '\0') ||
        (*(s64*)(param_1 + 0x10) > *(s64*)(param_1 + 8)))
    {
        return {0, 0};
    }

    u64 uVar1 = (u64)((*(s64*)(param_1 + 8) - *(s64*)(param_1 + 0x10)) + 59000000000LL);
    // Divide by 3600000000000 to get hours
    u64 uVar5 = uVar1 & 0xffffffff;
    s64 lVar7 = (s64)uVar1 >> 32;
    u64 uVar2 = (u64)(lVar7 * (s64)0xed75ed55) +
                (uVar5 * (u64)0xed75ed55 >> 32);
    s64 lVar3 = -(s64)(uVar1 >> 63) +
                ((s64)(uVar1 + lVar7 * (s64)(-0x63a000daLL) +
                       ((s64)uVar2 >> 32) +
                       ((s64)(uVar5 * (u64)(-0x63a000daLL) +
                              (uVar2 & 0xffffffff)) >> 32)) >> 0x29);

    // Remainder / 60000000000 to get minutes
    uVar2 = (u64)(lVar7 * (s64)0x68fd3d1d) +
            (uVar5 * (u64)0x68fd3d1d >> 32);
    u64 uVar6 = (u64)lVar3 * 3600000000000ULL;
    u64 uVar4 = (u64)((s64)(uVar6 >> 32) * (s64)0x68fd3d1d) +
                (((uVar6 & 0xffffe000ULL) * (u64)0x68fd3d1d) >> 32);
    s64 minutes = (-(s64)(uVar1 >> 63) +
                   ((s64)((s64)(lVar7 * (s64)0x12533fe) +
                          ((s64)uVar2 >> 32) +
                          ((s64)(uVar5 * (u64)0x12533fe +
                                 (uVar2 & 0xffffffff)) >> 32)) >> 0x1c)) -
                  ((((s64)((s64)((s64)(uVar6 >> 32) * (s64)0x12533fe) +
                            ((s64)uVar4 >> 32) +
                            (s64)(((uVar6 & 0xffffe000ULL) * (u64)0x12533fe +
                                   (uVar4 & 0xffffffff)) >> 32)) >> 0x1c)) -
                   (s64)(uVar6 >> 63));
    return {lVar3, minutes};
}

// ─────────────────────────────────────────────────────────────────────────
// FUN_71025128f0  size=384
// Music ID lookup: returns the music index for a given type+slot pair.
// ─────────────────────────────────────────────────────────────────────────
u16 FUN_71025128f0(u8 param_1, u8 param_2)
{
    s64  lVar6;
    u64  uVar3;
    u64  uVar4;
    s64  lVar5;
    u64  uVar7;

    switch (param_1) {
    case 0:
        lVar6 = *(s64*)(*(s64*)(DAT_710532e730 + 8) + 0x1d8);
        uVar3 = *(u64*)(*((u64*)DAT_7105328fa0) + 0x7e8);
        break;
    case 1: {
        lVar6 = *(s64*)(DAT_710532e730 + 8);
        uVar4 = FUN_71032a3620(*(u64*)(lVar6 + 0x208), param_2);
        if ((uVar4 & 0xff00000000000000ULL) != 0x5200000000000000ULL ||
            (uVar4 & 0xffffffffffULL) == 0) return 0xffff;
        return FUN_71032a51a0(*(u64*)(lVar6 + 0x208), uVar4);
    }
    case 2: {
        uVar4 = (u64)param_2;
        lVar5 = *(s64*)(*((u64*)DAT_7105328fa0) + 0x858);
        uVar7 = (u64)((*(s64*)(*((u64*)DAT_7105328fa0) + 0x860) - lVar5) >> 4) *
                (u64)(-0x5555555555555555LL);
        if (uVar7 < uVar4 || uVar7 - uVar4 == 0) return 0xffff;
        lVar6 = *(s64*)(*(s64*)(DAT_710532e730 + 8) + 0x1d8);
        uVar3 = *(u64*)(lVar5 + (s64)uVar4 * 0x30);
        break;
    }
    case 3: {
        lVar6 = *(s64*)(*((u64*)DAT_7105328fa0) + 0x8d0);
        if ((u64)((*(s64*)(*((u64*)DAT_7105328fa0) + 0x8d8) - lVar6) >> 4) <= (u64)param_2)
            return 0xffff;
        uVar3 = *(u64*)(lVar6 + (u64)param_2 * 0x10);
        lVar6 = *(s64*)(*(s64*)(DAT_710532e730 + 8) + 0x1d8);
        break;
    }
    default:
        return 0xffff;
    }

    u32 uVar2 = FUN_71032a7250(lVar6, uVar3);
    if (uVar2 < (u32)((s32)((u64)(*(s64*)(lVar6 + 0x28) - *(s64*)(lVar6 + 0x20)) >> 6) *
                      (s32)(-0x33333333)))
    {
        return *(u16*)(*(s64*)(lVar6 + 0x20) + (u64)uVar2 * 0x140);
    }
    return 0xffff;
}

// ─────────────────────────────────────────────────────────────────────────
// FUN_7102512a70  size=192
// Writes a typed name identifier into *param_1 based on param_2.
// ─────────────────────────────────────────────────────────────────────────
void FUN_7102512a70(u64* param_1, u8 param_2, u8 param_3)
{
    switch (param_2) {
    case 1: {
        s64 lVar3 = *(s64*)(DAT_710532e730 + 8);
        u64 uVar1 = FUN_71032a3620(*(u64*)(lVar3 + 0x208), param_3);
        if ((uVar1 & 0xff00000000000000ULL) == 0x5200000000000000ULL &&
            (uVar1 & 0xffffffffffULL) != 0)
        {
            FUN_71032a4890(param_1, *(u64*)(lVar3 + 0x208), uVar1);
            return;
        }
        // fallthrough to default
    }
    default:
        *(u8*)(param_1 + 1) = 0;
        *param_1 = 0;
        return;
    case 2:
        FUN_71003a4ca0(param_1, "cam_searchfield%d_field_name", param_3);
        return;
    case 3:
        FUN_71003a4ca0(param_1, "cam_shop%d_shop_name", param_3);
        return;
    }
}

// ─────────────────────────────────────────────────────────────────────────
// FUN_7102528a50  size=160
// Dispatch: pick one of 5 callbacks by param_2, then call via FUN_7102523d70.
// ─────────────────────────────────────────────────────────────────────────
void FUN_7102528a50(u64* param_1, u8 param_2)
{
    void (*local_18)(void);
    u64  uVar2 = *param_1;
    u64  uVar1 = param_1[1];

    switch (param_2) {
    case 0: local_18 = FUN_7102523c10; break;
    case 1: local_18 = FUN_7102524ce0; break;
    case 2: local_18 = FUN_7102524e70; break;
    case 3: local_18 = FUN_7102525000; break;
    case 4: local_18 = FUN_7102525180; break;
    default: return;
    }
    FUN_7102523d70(uVar2, uVar1, &local_18);
}

// ─────────────────────────────────────────────────────────────────────────
// FUN_710253dcdc  size=144
// FUN_710253ddcc  size=144
// Returns an iterator range {begin=&PTR_LAB_7104f613d8, end=stack_sentinel}.
// Both functions are identical instantiations.
// ─────────────────────────────────────────────────────────────────────────
struct PtrRange { void* begin; void* end; };

PtrRange FUN_710253dcdc(void)
{
    void* sentinel[1];
    return { &PTR_LAB_7104f613d8, sentinel };
}

PtrRange FUN_710253ddcc(void)
{
    void* sentinel[1];
    return { &PTR_LAB_7104f613d8, sentinel };
}

// ─────────────────────────────────────────────────────────────────────────
// FUN_710259f010  size=512
// Copy 4-field struct from param_1 into param_2.
// ─────────────────────────────────────────────────────────────────────────
void FUN_710259f010(u8* param_1, u64* param_2)
{
    *param_2     = (u64)&PTR_LAB_71050c4348;
    param_2[1]   = *(u64*)(param_1 + 8);
    param_2[2]   = *(u64*)(param_1 + 0x10);
    param_2[3]   = *(u64*)(param_1 + 0x18);
}

// ─────────────────────────────────────────────────────────────────────────
// FUN_71025b0c90  size=480
// Apply UI class animation string to the UI element at param_1+8.
// Classes: 0=none, 1=hope, 2=ace, 3=legend.
// ─────────────────────────────────────────────────────────────────────────
void FUN_71025b0c90(u8* param_1, u8 param_2)
{
    // Stack buffer for the class name string (max ~12 bytes)
    u64 uStack_50;
    u32 local_48;

    const char* pcVar3;
    switch (param_2) {
    case 0:
        uStack_50 = 0x6f6e5f7373616c63ULL; // "class_no"
        local_48  = (local_48 & 0xff000000u) | 0x656eu; // "ne\0"
        pcVar3 = (char*)((u8*)&uStack_50 + 1);
        while (*pcVar3++);
        break;
    case 1:
        uStack_50 = 0x6f685f7373616c63ULL; // "class_ho"
        local_48  = (local_48 & 0xff000000u) | 0x6570u; // "pe\0"
        pcVar3 = (char*)((u8*)&uStack_50 + 1);
        while (*pcVar3++);
        break;
    case 2:
        uStack_50 = 0x63615f7373616c63ULL; // "class_ac"
        local_48  = (local_48 & 0xffff0000u) | 0x65u;   // "e\0"
        pcVar3 = (char*)((u8*)&uStack_50 + 1);
        while (*pcVar3++);
        break;
    case 3:
        uStack_50 = 0x656c5f7373616c63ULL; // "class_le"
        local_48  = 0x646e6567u;                          // "gend\0"
        *(u8*)((u8*)&local_48 + 4) = 0;
        pcVar3 = (char*)((u8*)&uStack_50 + 1);
        while (*pcVar3++);
        break;
    default:
        uStack_50 = 0x6f6e5f7373616c63ULL;
        local_48  = (local_48 & 0xff000000u) | 0x656eu;
        pcVar3 = (char*)((u8*)&uStack_50 + 1);
        while (*pcVar3++);
        break;
    }
    ui2d_apply_named_animation(0x3f800000u, *(u64*)(param_1 + 8), &uStack_50);
}

// ─────────────────────────────────────────────────────────────────────────
// FUN_71025b2a60  size=48
// Stage ID table lookup by 1-based index; returns sentinel on out-of-range.
// ─────────────────────────────────────────────────────────────────────────
u64 FUN_71025b2a60(s32 param_1)
{
    if ((u32)(param_1 - 1) < 9u) {
        return DAT_7104ad9bc0[(s32)(u32)(param_1 - 1)];
    }
    return 0x71ffff0000000000ULL;
}

// ─────────────────────────────────────────────────────────────────────────
// FUN_71025b2e80  size=1648
// Spirit battle rule name lookup.
// param_1 = rule category, param_2 = rule hash/id.
// Returns a "nam_spirits_rule_*" string or "".
// ─────────────────────────────────────────────────────────────────────────
const char* FUN_71025b2e80(u8 param_1, u64 param_2)
{
    const char* pcVar4 = "nam_spirits_rule_pokemon_fix";

    switch (param_1) {
    case 1: {
        s64 lVar5 = *(s64*)(*((u64*)DAT_7105328fa0) + 0x2f8);
        u64 uVar7 = (u64)((*(s64*)(*((u64*)DAT_7105328fa0) + 0x300) - lVar5) >> 4);
        u32 uVar6 = (u32)uVar7;
        if (uVar6 == 0) { pcVar4 = ""; break; }
        for (u32 uVar3 = 0; uVar3 < uVar6; uVar3++) {
            u64 uVar9 = (u64)uVar3;
            if (uVar9 >= uVar7) {
                // __throw_out_of_range
                _ZNSt3__120__vector_base_commonILb1EE20__throw_out_of_rangeEv();
            }
            if (((*(u64*)(lVar5 + (s64)uVar9 * 0x10) ^ param_2) & 0xffffffffffULL) == 0) {
                s64 lVar1 = lVar5 + (s64)uVar9 * 0x10;
                s32 sign  = *(s32*)(lVar1 + 0xc);
                u8  axis  = *(u8*)(lVar1 + 10);
                if (sign >= 0) {
                    if (sign < 1) { pcVar4 = ""; break; }
                    switch (axis) {
                    case 0: return "nam_spirits_rule_mov_up";
                    case 1: return "nam_spirits_rule_jump_up";
                    case 2: pcVar4 = ""; break;
                    case 5: return "nam_spirits_rule_defense_up";
                    default: pcVar4 = ""; break;
                    }
                } else {
                    switch (axis) {
                    case 0: return "nam_spirits_rule_mov_down";
                    case 1: return "nam_spirits_rule_jump_down";
                    case 2: pcVar4 = ""; break;
                    case 5: return "nam_spirits_rule_defense_down";
                    default: pcVar4 = ""; break;
                    }
                }
            }
            pcVar4 = "";
        }
        return pcVar4;
    }
    case 2: {
        s64 lVar5 = *(s64*)(*((u64*)DAT_7105328fa0) + 0x310);
        u64 uVar7 = (u64)((*(s64*)(*((u64*)DAT_7105328fa0) + 0x318) - lVar5) >> 4);
        u32 uVar6 = (u32)uVar7;
        if (uVar6 == 0) { pcVar4 = ""; break; }
        for (u32 uVar3 = 0; ; uVar3++) {
            u64 uVar9 = (u64)uVar3;
            if (uVar9 >= uVar7) {
                _ZNSt3__120__vector_base_commonILb1EE20__throw_out_of_rangeEv();
            }
            if (((*(u64*)(lVar5 + (s64)uVar9 * 0x10) ^ param_2) & 0xffffffffffULL) == 0) {
                s64 lOff = lVar5 + (s64)uVar9 * 0x10;
                if (*(s8*)(lOff + 10) == '\0')
                    return "nam_spirits_rule_small";
                return "nam_spirits_rule_big";
            }
            uVar3++;
            if (uVar6 <= uVar3) return "";
        }
    }
    case 3:  return "nam_spirits_rule_damage";
    case 4:  return "nam_spirits_rule_suddendeath";
    case 5:  return "nam_spirits_rule_invincible";
    case 6:  return "nam_spirits_rule_heal";
    case 7: {
        s64 lVar5 = *(s64*)(*((u64*)DAT_7105328fa0) + 0x5e0);
        u64 uVar7 = (u64)((*(s64*)(*((u64*)DAT_7105328fa0) + 0x5e8) - lVar5) >> 3) *
                    (u64)(-0x5555555555555555LL);
        if ((u32)uVar7 == 0) { pcVar4 = nullptr; break; }
        u32 uVar3 = 0;
        for (u32 uVar6 = 0; ; uVar6++) {
            u64 uVar9 = (u64)uVar6;
            if (uVar9 > uVar7 || uVar7 - uVar9 == 0) {
                _ZNSt3__120__vector_base_commonILb1EE20__throw_out_of_rangeEv();
            }
            if (((*(u64*)(lVar5 + (s64)uVar9 * 0x18) ^ param_2) & 0xffffffffffULL) == 0) {
                uVar3 = *(u32*)(lVar5 + (s64)uVar9 * 0x18 + 0x14);
            }
            uVar6++;
            if ((u32)uVar7 <= uVar6) {
                if (1 < uVar3) return "nam_spirits_rule_item_outbreak";
                return nullptr;
            }
        }
    }
    case 8:  return "nam_spirits_rule_bomb";
    case 9:  return "nam_spirits_rule_charge_max";
    case 10: return "nam_spirits_rule_metal";
    case 0xb: return "nam_spirits_rule_dark";
    case 0xc: return "nam_spirits_rule_wind_suddenly";
    case 0xe: {
        s64 lVar5 = *(s64*)(*((u64*)DAT_7105328fa0) + 0x5c8);
        u64 uVar7 = (u64)((*(s64*)(*((u64*)DAT_7105328fa0) + 0x5d0) - lVar5) >> 4);
        u32 uVar6 = (u32)uVar7;
        if (uVar6 == 0) { pcVar4 = ""; break; }
        for (u32 uVar3 = 0; ; uVar3++) {
            u64 uVar9 = (u64)uVar3;
            if (uVar9 >= uVar7) {
                _ZNSt3__120__vector_base_commonILb1EE20__throw_out_of_rangeEv();
            }
            if (((*(u64*)(lVar5 + (s64)uVar9 * 0x10) ^ param_2) & 0xffffffffffULL) == 0) {
                s64 lVar1 = lVar5 + (s64)uVar9 * 0x10;
                s8 cVar2  = *(s8*)(lVar1 + 8);
                bool up   = *(s8*)(lVar1 + 9) != '\0';
                if (!up) {
                    if (cVar2 == 1) return "nam_spirits_rule_type_attack_down";
                    if (cVar2 == 0) return "nam_spirits_rule_type_none_down";
                    if (cVar2 == 2) return "nam_spirits_rule_type_throw_down";
                    if (cVar2 == 3) return "nam_spirits_rule_type_guard_down";
                } else {
                    if (cVar2 == 1) return "nam_spirits_rule_type_attack_up";
                    if (cVar2 == 0) return "nam_spirits_rule_type_none_up";
                    if (cVar2 == 2) return "nam_spirits_rule_type_throw_up";
                    if (cVar2 == 3) return "nam_spirits_rule_type_guard_up";
                }
            }
            uVar3++;
            if (uVar6 <= uVar3) return "";
        }
    }
    case 0xf: return "nam_spirits_rule_earthquake";
    case 0x10: return "nam_spirits_rule_flower";
    case 0x11: return "nam_spirits_rule_curry";
    case 0x12: return "nam_spirits_rule_transparence";
    case 0x13: return "nam_spirits_rule_shield_down";
    case 0x14: {
        s64 lVar5 = *(s64*)(*((u64*)DAT_7105328fa0) + 0x3d0);
        u64 uVar7 = (u64)((*(s64*)(*((u64*)DAT_7105328fa0) + 0x3d8) - lVar5) >> 4);
        u32 uVar6 = (u32)uVar7;
        if (uVar6 == 0) { pcVar4 = ""; break; }
        for (u32 uVar3 = 0; ; uVar3++) {
            u64 uVar9 = (u64)uVar3;
            if (uVar9 >= uVar7) {
                _ZNSt3__120__vector_base_commonILb1EE20__throw_out_of_rangeEv();
            }
            if (((*(u64*)(lVar5 + (s64)uVar9 * 0x10) ^ param_2) & 0xffffffffffULL) == 0) {
                s64 lOff = lVar5 + (s64)uVar9 * 0x10;
                if (*(s8*)(lOff + 10) == '\0')
                    return "nam_spirits_rule_gravity_down";
                return "nam_spirits_rule_gravity_up";
            }
            uVar3++;
            if (uVar6 <= uVar3) return "";
        }
    }
    case 0x15: return "nam_spirits_rule_speed_wild";
    case 0x16: return "nam_spirits_rule_magic_up";
    case 0x17: return "nam_spirits_rule_energy_charge";
    case 0x18: return "nam_spirits_rule_weapon_offense_up";
    case 0x19: return "nam_spirits_rule_drown_up";
    case 0x1a: return "nam_spirits_rule_advantage_reverse";
    case 0x1b: return "nam_spirits_rule_advantage_double";
    case 0x1c: return "nam_spirits_rule_screen_flip";
    case 0x1d: return "nam_spirits_rule_horizontal_controller_flip";
    case 0x20: {
        s64 lVar5 = *(s64*)(*((u64*)DAT_7105328fa0) + 0x4f0);
        u64 uVar7 = (u64)((*(s64*)(*((u64*)DAT_7105328fa0) + 0x4f8) - lVar5) >> 4);
        u32 uVar6 = (u32)uVar7;
        if (uVar6 == 0) { pcVar4 = ""; break; }
        for (u32 uVar3 = 0; ; uVar3++) {
            u64 uVar9 = (u64)uVar3;
            if (uVar9 >= uVar7) {
                _ZNSt3__120__vector_base_commonILb1EE20__throw_out_of_rangeEv();
            }
            if (((*(u64*)(lVar5 + (s64)uVar9 * 0x10) ^ param_2) & 0xffffffffffULL) == 0) {
                s64 lOff = lVar5 + (s64)uVar9 * 0x10;
                if (*(s8*)(lOff + 10) == '\0')
                    return "nam_spirits_rule_launch_down";
                return "nam_spirits_rule_launch_up";
            }
            uVar3++;
            if (uVar6 <= uVar3) return "";
        }
        pcVar4 = "";
        break;
    }
    case 0x21: return "nam_spirits_rule_balloon";
    case 0x22: return "nam_spirits_rule_slippery";
    case 0x23: return "nam_spirits_rule_smash_attack_up";
    case 0x24: return "nam_spirits_rule_no_hold";
    case 0x25: return "nam_spirits_rule_unity_damage";
    case 0x26: return "nam_spirits_rule_heal_seal";
    case 0x27: return "nam_spirits_rule_electric_up";
    case 0x28: return "nam_spirits_rule_reflect_damage_up";
    case 0x29: return "nam_spirits_rule_jump_seal";
    case 0x2a: return "nam_spirits_rule_normal_seal";
    case 0x2b: return "nam_spirits_rule_sp_move_seal";
    case 0x2c: return "nam_spirits_rule_shield_seal";
    case 0x2d: return "nam_spirits_rule_assist";
    case 0x2e: break;
    case 0x2f: return "nam_spirits_rule_sleep";
    default:   pcVar4 = nullptr; break;
    }
    return pcVar4;
}

// ─────────────────────────────────────────────────────────────────────────
// FUN_71025c6520  size=2448
// Build FNV-1a hash for spirits sort UI key "mnu_spirits_sort_XX".
// Writes hash+len+str into param_1[0..6].
// ─────────────────────────────────────────────────────────────────────────
void FUN_71025c6520(u32* param_1, u32 param_2)
{
    // String suffix bytes for each case (last 3 chars before null)
    u32 suffix;
    switch (param_2) {
    case  1: suffix = 0x31305f; break; // "_01"
    case  2: suffix = 0x30305f; break; // "_00"
    case  3: suffix = 0x32305f; break; // "_02"
    case  4: suffix = 0x38315f; break; // "_18"
    case  5: suffix = 0x33305f; break; // "_03"
    case  6: suffix = 0x34305f; break; // "_04"
    case  7: suffix = 0x35305f; break; // "_05"
    case  8: suffix = 0x36305f; break; // "_06"
    case  9: suffix = 0x37305f; break; // "_07"
    case 10: suffix = 0x38305f; break; // "_08"
    case 11: suffix = 0x39305f; break; // "_09"
    case 12: suffix = 0x30315f; break; // "_10"
    case 13: suffix = 0x31315f; break; // "_11"
    case 14: suffix = 0x32315f; break; // "_12"
    case 15: suffix = 0x33315f; break; // "_13"
    case 16: suffix = 0x34315f; break; // "_14"
    case 17: suffix = 0x35315f; break; // "_15"
    case 18: suffix = 0x36315f; break; // "_16"
    case 19: suffix = 0x37315f; break; // "_17"
    case 20: suffix = 0x39315f; break; // "_19"
    case 21: suffix = 0x32325f; break; // "_22"
    case 22: suffix = 0x34325f; break; // "_24"
    case 23: suffix = 0x31325f; break; // "_21"
    default:
        *(u8*)(param_1 + 2) = 0;
        param_1[0] = 0;
        param_1[1] = 0;
        return;
    }

    // Build the string buffer: "mnu_spirits_sort_XX\0" (19 chars + null)
    param_1[0] = 0;          // hash (computed below)
    param_1[1] = 0x13;       // length = 19
    param_1[2] = 0x5f756e6d; // "mnu_"
    param_1[3] = 0x72697073; // "spir"
    param_1[4] = 0x5f737469; // "its_"
    param_1[5] = 0x74726f73; // "sort"
    param_1[6] = suffix;     // "_XX\0"

    // FNV-1a hash (seed 0x811c9dc5, mul 0x89)
    u32 uVar1 = 0x811c9dc5u;
    u32 uVar3 = 0x6d; // 'm'
    u8* pbVar2 = (u8*)param_1 + 9;
    do {
        uVar1 = uVar1 * 0x89u ^ uVar3;
        uVar3 = (u32)*pbVar2;
        pbVar2++;
    } while (uVar3 != 0);
    param_1[0] = uVar1;
}

// ─────────────────────────────────────────────────────────────────────────
// FUN_7102618f50  size=944
// Push file IDs into per-slot lists in a loadlist struct.
// param_1 = loadlist, param_2 = slot type (0-6), param_3 = file id ptr.
// ─────────────────────────────────────────────────────────────────────────
void FUN_7102618f50(u8* param_1, s32 param_2, u32* param_3)
{
    if (*param_3 == 0xffffffu) return;

    s64 lVar5 = (s64)param_1 + (s64)param_2 * 0x30;
    u32** plVar6 = (u32**)(lVar5 + 0xd0);
    u32*  puVar4 = *plVar6;

    if (puVar4 == *(u32**)(lVar5 + 0xd8)) {
        FUN_7101609af0((void*)(param_1 + (s64)param_2 * 0x30 + 200), param_3);
    } else {
        *puVar4 = 0xffffff;
        u32 uVar1 = *param_3;
        *puVar4 = uVar1;
        if (uVar1 != 0xffffff) FUN_7103540450(DAT_7105331f20);
        *plVar6 = *plVar6 + 1; // advance pointer
    }

    if (param_2 == 2) {
        u32 uVar1 = *param_3;
        if ((uVar1 != 0xffffff) &&
            (uVar1 < *(u32*)(*(s64*)(**(s64**)(DAT_7105331f20 + 0x78) + 0x40) + 4)) &&
            (*(s64*)(*(s64*)(**(s64**)(DAT_7105331f20 + 0x78) + 0x60) +
                     (u64)uVar1 * 0x20 + 0x18) == 0x126776a84fLL))
        {
            s32 iVar2 = *(s32*)(param_1 + 0x398);
            *(u32*)(param_1 + 0x398) = uVar1;
            FUN_7103540450(0);
            if (iVar2 != (s32)0xffffff) {
                FUN_7103540560(DAT_7105331f20, iVar2);
            }
        }
    } else if (param_2 == 6) {
        u64 uVar3 = FUN_710353d360(*param_3, ".nutexb");
        if ((uVar3 & 1) != 0) {
            u32* puVar4b = *(u32**)(param_1 + 0x358);
            if (puVar4b == *(u32**)(param_1 + 0x360)) {
                FUN_7101609af0((void*)(param_1 + 0x350), param_3);
                return;
            }
            *puVar4b = 0xffffff;
            u32 uVar1 = *param_3;
            *puVar4b = uVar1;
            if (uVar1 != 0xffffff) FUN_7103540450(DAT_7105331f20);
            *(s64*)(param_1 + 0x358) = *(s64*)(param_1 + 0x358) + 4;
        }
    } else if (param_2 == 3) {
        u64 uVar3 = FUN_710353d360(*param_3, ".stprm");
        if ((uVar3 & 1) == 0) {
            uVar3 = FUN_710353d360(*param_3, (const char*)DAT_71043053b5);
            if ((uVar3 & 1) != 0) {
                u32* puVar4b = *(u32**)(param_1 + 0x2e0);
                if (puVar4b == *(u32**)(param_1 + 0x2e8)) {
                    FUN_7101609af0((void*)(param_1 + 0x2d8), param_3);
                    return;
                }
                *puVar4b = 0xffffff;
                u32 uVar1 = *param_3;
                *puVar4b = uVar1;
                if (uVar1 != 0xffffff) FUN_7103540450(DAT_7105331f20);
                *(s64*)(param_1 + 0x2e0) = *(s64*)(param_1 + 0x2e0) + 4;
            }
        } else {
            u32* puVar4b = *(u32**)(param_1 + 0x2c8);
            if (puVar4b == *(u32**)(param_1 + 0x2d0)) {
                FUN_7101609af0((void*)(param_1 + 0x2c0), param_3);
                return;
            }
            *puVar4b = 0xffffff;
            u32 uVar1 = *param_3;
            *puVar4b = uVar1;
            if (uVar1 != 0xffffff) FUN_7103540450(DAT_7105331f20);
            *(s64*)(param_1 + 0x2c8) = *(s64*)(param_1 + 0x2c8) + 4;
        }
    }
}

// ─────────────────────────────────────────────────────────────────────────
// FUN_710261d790  size=48
// Returns 1 if param_1 is one of the special motion type IDs, else 0.
// ─────────────────────────────────────────────────────────────────────────
u64 FUN_710261d790(u32 param_1)
{
    switch (param_1) {
    case 0x9b: case 0x9c: case 0x9d:
    case 0xda: case 0xdb: case 0xdc:
    case 0xe0: case 0xe1: case 0xe2:
    case 0x113: case 0x114: case 0x115: case 0x116:
    case 0x117: case 0x118: case 0x119: case 0x11a: case 0x11b:
    case 0x11f: case 0x120: case 0x121:
        return 1;
    default:
        return 0;
    }
}
