// MEDIUM batch 010 (0x7102302984 – 0x71023ed1e0)
// call-wrappers, __cxa_guard inits, std::__1::__vector_base_common<true>::__throw_out_of_range(), scene-type hash dispatch, bool checks

#include <stdint.h>
namespace std { namespace __1 {
template<bool> struct __vector_base_common {
    [[noreturn]] static void __throw_out_of_range();
};
}}
typedef uint8_t  u8;
typedef uint32_t u32;
typedef uint64_t u64;
typedef int32_t  s32;
typedef int64_t  s64;

extern "C" float sqrtf(float);
extern "C" int   strcmp(const char *, const char *);

extern "C" {
int  __cxa_guard_acquire(u64 *);
void __cxa_guard_release(u64 *);
[[noreturn]] void abort(void);
void FUN_7101af0740(void);
void FUN_7101d25b30(void);
void FUN_7101d11060(u64);
void FUN_71017cda90(void);
void FUN_71000001c0(void (*)(void), u64 *, u64 *);
void FUN_7101763de0(void);
void global_param_init_sets_team_flag(void);
}

// shared innermost cxa_guard DATs
extern u64 DAT_7105323748;
extern u64 DAT_7105323750;
extern u64 DAT_7105323758;
extern u64 DAT_7105323760;

// special mid-level guard DATs (used by FUN_710230bf20)
extern u64 DAT_71053277c8;
extern u64 DAT_71053277d0;
extern u64 DAT_7105327150;
extern u64 DAT_7105327158;

// per-function outer guard/data pairs for CXA_GUARD_3LEVEL
extern u64 DAT_7105323868; extern u64 DAT_7105323870;
extern u64 DAT_71053238a8; extern u64 DAT_71053238b0;
extern u64 DAT_71053238b8; extern u64 DAT_71053238c0;
extern u64 DAT_71053238c8; extern u64 DAT_71053238d0;
extern u64 DAT_7105323978; extern u64 DAT_7105323980;
extern u64 DAT_7105323998; extern u64 DAT_71053239a0;
extern u64 DAT_7105323988; extern u64 DAT_7105323990;
extern u64 DAT_71053239a8; extern u64 DAT_71053239b0;
extern u64 DAT_7105328948; extern u64 DAT_7105328950;
extern u64 DAT_7105323a48; extern u64 DAT_7105323a50;
extern u64 DAT_7105323a08; extern u64 DAT_7105323a10;
extern u64 DAT_7105323a18; extern u64 DAT_7105323a20;
extern u64 DAT_7105323a88; extern u64 DAT_7105323a90;

// singletons used by FUN_7102389af0
extern u64 DAT_7105324cc8;
extern u64 DAT_7105323fd8;
extern u64 DAT_7105324cb8;
extern u64 DAT_7105323fa0;
extern u64 DAT_710532e8f8;
extern u64 DAT_7105324c98;
extern u64 DAT_7105324cd0;
extern u64 DAT_710532e838;
extern u64 DAT_71052c3c58;

// singletons used by FUN_71023967d8
extern u64 DAT_7105324d80;

// symbols for FUN_71023ed1e0
extern u64 g_team_param_init_guard;
extern u64 DAT_71052c4180;
extern u64 PTR_LOOP_7104f16000;
extern u8  DAT_7105307343;

// ---- simple call-wrappers ----

// 0x7102302984
u32 FUN_7102302984(void)
{
    FUN_7101af0740();
    return 0;
}

// ---- 3-level __cxa_guard (standard: mid=DAT_7105323748/760) ----

#define CXA_GUARD_3LEVEL(fname, G, D) \
u64 *fname(void) { \
    int iVar1; \
    if (((G & 1) == 0) && (iVar1 = __cxa_guard_acquire(&G), iVar1 != 0)) { \
        if (((DAT_7105323748 & 1) == 0) && (iVar1 = __cxa_guard_acquire(&DAT_7105323748), iVar1 != 0)) { \
            if (((DAT_7105323750 & 1) == 0) && (iVar1 = __cxa_guard_acquire(&DAT_7105323750), iVar1 != 0)) { \
                DAT_7105323758 = 0; \
                __cxa_guard_release(&DAT_7105323750); \
            } \
            DAT_7105323760 = (u64)&DAT_7105323758; \
            __cxa_guard_release(&DAT_7105323748); \
        } \
        D = (u64)&DAT_7105323760; \
        __cxa_guard_release(&G); \
    } \
    return &D; \
}

// 0x7102307120
CXA_GUARD_3LEVEL(FUN_7102307120, DAT_7105323868, DAT_7105323870)

// 0x710230bf20 -- variant: mid=DAT_7105327150/7158 (not the standard DAT_7105323748)
u64 *FUN_710230bf20(void)
{
    int iVar1;
    if (((DAT_71053277c8 & 1) == 0) && (iVar1 = __cxa_guard_acquire(&DAT_71053277c8), iVar1 != 0)) {
        if (((DAT_7105327150 & 1) == 0) && (iVar1 = __cxa_guard_acquire(&DAT_7105327150), iVar1 != 0)) {
            if (((DAT_7105323750 & 1) == 0) && (iVar1 = __cxa_guard_acquire(&DAT_7105323750), iVar1 != 0)) {
                DAT_7105323758 = 0;
                __cxa_guard_release(&DAT_7105323750);
            }
            DAT_7105327158 = (u64)&DAT_7105323758;
            __cxa_guard_release(&DAT_7105327150);
        }
        DAT_71053277d0 = (u64)&DAT_7105327158;
        __cxa_guard_release(&DAT_71053277c8);
    }
    return &DAT_71053277d0;
}

// 0x7102330180
CXA_GUARD_3LEVEL(FUN_7102330180, DAT_71053238a8, DAT_71053238b0)
// 0x7102330300
CXA_GUARD_3LEVEL(FUN_7102330300, DAT_71053238b8, DAT_71053238c0)

// ---- std::__1::__vector_base_common<true>::__throw_out_of_range() wrappers ----

// 0x7102338ffc
[[noreturn]] void FUN_7102338ffc(void) { std::__1::__vector_base_common<true>::__throw_out_of_range(); }
// 0x7102343934
[[noreturn]] void FUN_7102343934(void) { std::__1::__vector_base_common<true>::__throw_out_of_range(); }

// ---- float computation ----

// 0x710234fd88 -- ease-in sqrt: -(sqrtf(t) - 1.0)
float FUN_710234fd88(s64 /*unused*/[2], float param_2)
{
    float fVar1 = sqrtf(param_2);
    return -(fVar1 + -1.0f);
}

// ---- more std::__1::__vector_base_common<true>::__throw_out_of_range() wrappers ----

// 0x7102350de8
[[noreturn]] void FUN_7102350de8(void) { std::__1::__vector_base_common<true>::__throw_out_of_range(); }
// 0x71023510e8
[[noreturn]] void FUN_71023510e8(void) { std::__1::__vector_base_common<true>::__throw_out_of_range(); }
// 0x7102351178
[[noreturn]] void FUN_7102351178(void) { std::__1::__vector_base_common<true>::__throw_out_of_range(); }
// 0x7102351208
[[noreturn]] void FUN_7102351208(void) { std::__1::__vector_base_common<true>::__throw_out_of_range(); }
// 0x7102351298
[[noreturn]] void FUN_7102351298(void) { std::__1::__vector_base_common<true>::__throw_out_of_range(); }

// ---- more 3-level guards ----

// 0x7102363050
CXA_GUARD_3LEVEL(FUN_7102363050, DAT_71053238c8, DAT_71053238d0)

// ---- scene-type hash dispatch ----

// 0x71023668e0 -- init scene struct from hash+name pair
u64 FUN_71023668e0(s64 param_1, u32 *param_2)
{
    u32  uVar1;
    int  iVar2;
    u32 *__s1;
    u32  uVar3;
    const char *pcVar4;

    __s1 = param_2 + 2;
    uVar1 = *param_2;
    if (uVar1 < 0x4d1b6eab) {
        return 0;
    }
    if (uVar1 == 0xe6c44dfe) {
        iVar2 = strcmp((char *)__s1, "OptionButtonScene");
        if (iVar2 != 0) {
            return 0;
        }
        *(u64 *)(param_1 + 0x10) = 0;
        *(u64 *)(param_1 + 0x18) = 0;
        *(u32 *)(param_1 + 0x158) = 0;
        *(u64 *)(param_1 + 0x160) = 0xffffffff;
        *(u32 *)(param_1 + 0x168) = 0xffffffff;
        uVar3 = 4;
        goto LAB_done;
    }
    if (uVar1 == 0x4d1b6eab) {
        iVar2 = strcmp((char *)__s1, "OptionTopScene");
        if (iVar2 != 0) {
            return 0;
        }
        *(u64 *)(param_1 + 0x10) = 0;
        *(u64 *)(param_1 + 0x18) = 0;
        *(u32 *)(param_1 + 0x158) = 0;
        *(u64 *)(param_1 + 0x160) = 0xffffffff;
        *(u32 *)(param_1 + 0x168) = 0xffffffff;
        uVar3 = 3;
        goto LAB_done;
    }
    if (uVar1 < 0xbc861f42) {
        if ((s32)uVar1 < 0x5108b424) {
            if (uVar1 == 0xb7a388d9) {
                iVar2 = strcmp((char *)__s1, "OptionVideoScene");
                if (iVar2 != 0) {
                    return 0;
                }
                *(u64 *)(param_1 + 0x160) = 0xffffffff;
                *(u32 *)(param_1 + 0x168) = 0xffffffff;
                uVar3 = 0xd;
                *(u64 *)(param_1 + 0x10) = 0;
                *(u64 *)(param_1 + 0x18) = 0;
                *(u32 *)(param_1 + 0x158) = 0;
                goto LAB_done;
            }
            if (uVar1 != 0x4e29d243) {
                return 0;
            }
            pcVar4 = "OptionSoundScene";
        } else {
            if (uVar1 != 0x535c066e) {
                if (uVar1 != 0x5108b424) {
                    return 0;
                }
                pcVar4 = "OptionMeleeScene";
LAB_strcmp_type6:
                iVar2 = strcmp((char *)__s1, pcVar4);
                if (iVar2 != 0) {
                    return 0;
                }
                *(u64 *)(param_1 + 0x10) = 0;
                *(u64 *)(param_1 + 0x18) = 0;
                *(u32 *)(param_1 + 0x158) = 0;
                *(u64 *)(param_1 + 0x160) = 0xffffffff;
                *(u32 *)(param_1 + 0x168) = 0xffffffff;
                uVar3 = 6;
                goto LAB_done;
            }
            pcVar4 = "SoundTestScene";
        }
    } else {
        if (uVar1 == 0xbc861f42) {
            iVar2 = strcmp((char *)__s1, "OptionLanguageScene");
            if (iVar2 != 0) {
                return 0;
            }
            *(u64 *)(param_1 + 0x10) = 0;
            *(u64 *)(param_1 + 0x18) = 0;
            *(u32 *)(param_1 + 0x158) = 0;
            *(u64 *)(param_1 + 0x160) = 0xffffffff;
            *(u32 *)(param_1 + 0x168) = 0xffffffff;
            uVar3 = 5;
            goto LAB_done;
        }
        if (0xf8973ff8 < uVar1) {
            if (uVar1 == 0xff126b7a) {
                pcVar4 = "CharaSelectScene";
            } else {
                if (uVar1 != 0xf8973ff9) {
                    return 0;
                }
                pcVar4 = "MeleeRuleScene";
            }
            goto LAB_strcmp_type6;
        }
        if (uVar1 < 0xe33b8f27) {
            if (uVar1 != 0xbe42ef4f) {
                return 0;
            }
            iVar2 = strcmp((char *)__s1, "OptionOnlineScene");
            if (iVar2 != 0) {
                return 0;
            }
            *(u64 *)(param_1 + 0x10) = 0;
            *(u64 *)(param_1 + 0x18) = 0;
            *(u32 *)(param_1 + 0x158) = 0;
            *(u64 *)(param_1 + 0x160) = 0xffffffff;
            *(u32 *)(param_1 + 0x168) = 0xffffffff;
            uVar3 = 0xc;
            goto LAB_done;
        }
        if (uVar1 != 0xe33b8f27) {
            return 0;
        }
        pcVar4 = "StageSelectScene";
    }
    iVar2 = strcmp((char *)__s1, pcVar4);
    if (iVar2 != 0) {
        return 0;
    }
    *(u64 *)(param_1 + 0x10) = 0;
    *(u64 *)(param_1 + 0x18) = 0;
    *(u32 *)(param_1 + 0x158) = 0;
    *(u64 *)(param_1 + 0x160) = 0xffffffff;
    *(u32 *)(param_1 + 0x168) = 0xffffffff;
    uVar3 = 9;
LAB_done:
    *(u8  *)(param_1 + 0x16c) = 0;
    *(u64 *)(param_1 + 0x148) = 0;
    *(u64 *)(param_1 + 0x150) = 0;
    *(u64 *)(param_1 + 0x138) = 0;
    *(u64 *)(param_1 + 0x140) = 0;
    *(u64 *)(param_1 + 0x128) = 0;
    *(u64 *)(param_1 + 0x130) = 0;
    *(u64 *)(param_1 + 0x118) = 0;
    *(u64 *)(param_1 + 0x120) = 0;
    *(u32 *)(param_1 + 0x110) = uVar3;
    *(u32 *)(param_1 + 0x15c) = 1;
    *(u32 *)(param_1 + 0x114) = 2;
    return 1;
}

// ---- more 3-level guards ----

// 0x7102378bc0
CXA_GUARD_3LEVEL(FUN_7102378bc0, DAT_7105323978, DAT_7105323980)
// 0x7102384f50
CXA_GUARD_3LEVEL(FUN_7102384f50, DAT_7105323998, DAT_71053239a0)
// 0x71023893f0
CXA_GUARD_3LEVEL(FUN_71023893f0, DAT_7105323988, DAT_7105323990)

// ---- bool singleton-state check ----

// 0x7102389af0 -- returns true iff all key subsystems are idle
bool FUN_7102389af0(void)
{
    if (*(s32 *)(*(s64 *)(DAT_7105324cc8 + 8) + 0xb8) != 0) {
        return false;
    }
    if (*(s32 *)(*(s64 *)(DAT_7105323fd8 + 8) + 200) != 0) {
        return false;
    }
    if (*(s32 *)(*(s64 *)(DAT_7105324cb8 + 8) + 0xa8) != 0) {
        return false;
    }
    if (*(s32 *)(*(s64 *)(DAT_7105323fa0 + 8) + 0xa8) != 0) {
        return false;
    }
    if (*(s32 *)(*(s64 *)(DAT_710532e8f8 + 8) + 200) != 0) {
        return false;
    }
    if (*(s32 *)(*(s64 *)(DAT_7105324c98 + 8) + 0x108) != 0) {
        return false;
    }
    if (*(s32 *)(*(s64 *)(DAT_7105324cd0 + 8) + 0xa8) != 0) {
        return false;
    }
    if ((DAT_710532e838 != 0) &&
        (*(char *)(*(s64 *)(DAT_710532e838 + 8) + 0x170) != '\0')) {
        return false;
    }
    if (*(char *)(*(s64 *)(*(s64 *)(DAT_71052c3c58 + 8) + 0x80) + 0x244) != '\0') {
        return *(s32 *)(*(s64 *)(*(s64 *)(DAT_71052c3c58 + 8) + 0x90) + 0x10) == 0;
    }
    return true;
}

// ---- more 3-level guards ----

// 0x7102395a20
CXA_GUARD_3LEVEL(FUN_7102395a20, DAT_71053239a8, DAT_71053239b0)

// ---- call wrappers ----

// 0x71023967d8
u32 FUN_71023967d8(void)
{
    FUN_7101d25b30();
    FUN_7101d11060(*(u64 *)(DAT_7105324d80 + 8));
    return 0;
}

// ---- std::__1::__vector_base_common<true>::__throw_out_of_range() ----

// 0x710239e04c
[[noreturn]] void FUN_710239e04c(void) { std::__1::__vector_base_common<true>::__throw_out_of_range(); }

// ---- more 3-level guards ----

// 0x71023a4da0
CXA_GUARD_3LEVEL(FUN_71023a4da0, DAT_7105328948, DAT_7105328950)
// 0x71023afd60
CXA_GUARD_3LEVEL(FUN_71023afd60, DAT_7105323a48, DAT_7105323a50)
// 0x71023afee0
CXA_GUARD_3LEVEL(FUN_71023afee0, DAT_7105323a08, DAT_7105323a10)
// 0x71023b0060
CXA_GUARD_3LEVEL(FUN_71023b0060, DAT_7105323a18, DAT_7105323a20)
// 0x71023b6b90
CXA_GUARD_3LEVEL(FUN_71023b6b90, DAT_7105323a88, DAT_7105323a90)

// ---- std::__1::__vector_base_common<true>::__throw_out_of_range() ----

// 0x71023c8f6c
[[noreturn]] void FUN_71023c8f6c(void) { std::__1::__vector_base_common<true>::__throw_out_of_range(); }

// ---- simple call-wrappers ----

// 0x71023d2ac0
u64 FUN_71023d2ac0(void)
{
    FUN_71017cda90();
    return 1;
}

// ---- 1-level guard with named global init ----

// 0x71023ed1e0 -- global param init for team flag
void FUN_71023ed1e0(void)
{
    int iVar1;
    if (((g_team_param_init_guard & 1) == 0) &&
        (iVar1 = __cxa_guard_acquire(&g_team_param_init_guard), iVar1 != 0)) {
        global_param_init_sets_team_flag();
        FUN_71000001c0(FUN_7101763de0, &DAT_71052c4180, &PTR_LOOP_7104f16000);
        __cxa_guard_release(&g_team_param_init_guard);
    }
    DAT_7105307343 = 1;
}
