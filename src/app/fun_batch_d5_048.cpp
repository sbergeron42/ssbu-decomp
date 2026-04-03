#include "types.h"

extern "C" {
    void *memset(void *s, int c, u64 n);
    void *memcpy(void *dst, const void *src, u64 n);
    void *malloc(s64 size);
}

// MEDIUM-tier FUN_* functions — batch d5-048
// Pool-d worker: misc small functions from 0x71000* range
// FUN_71000313b0 FUN_71000313f0 FUN_71000314e0 FUN_7100031850 FUN_71000338f0
// FUN_7100037790 FUN_7100037d20 FUN_7100039e30 FUN_710003a240 FUN_710003a3c0
// FUN_710003a4e0 FUN_710003a5f0 FUN_710003aaa0 FUN_710003ac20 FUN_7100044c70
// FUN_7100044db0 FUN_7100047c70 FUN_710004c5e0 FUN_7100055470 FUN_7100060e80
// FUN_7100060f20 FUN_7100060f40 FUN_7100066040 FUN_710006fcc0 FUN_7100077eb0
// FUN_71000093f0 FUN_71000145a0 FUN_71000145c0 FUN_710002b800 FUN_71000c73d8
// FUN_7100113400 FUN_7100113480 FUN_71001133a0 FUN_71001133c0 FUN_71001133e0
// FUN_71001134a0 FUN_71001136c0 FUN_710012eb20 FUN_710012eb40 FUN_710012eb60
// FUN_710012eb80 FUN_7100130aa0 FUN_7100130ac0 FUN_710013bc98 FUN_710013bd08
// FUN_7100149270 FUN_710014f090 FUN_710014f150 FUN_71001579a0 FUN_71001604a0
// FUN_7100186270 FUN_710003bc80 FUN_710003a240 FUN_7100031390 FUN_7100013730
// FUN_71000b1940 FUN_71000b65e0 FUN_710013b910 FUN_7100182b30 FUN_7100177c90
// FUN_7100177cb0 FUN_7100044970

// ---- Struct initializers and field setters ----

// 0x7100031390 — 32B struct initializer
void FUN_7100031390(u8 *param_1) {
    *param_1 = 1;
    *(u64 *)(param_1 + 4) = 0;
    *(u16 *)(param_1 + 2) = 0;
    *(u32 *)(param_1 + 0xc) = 1;
    *(u64 *)(param_1 + 0x18) = 0;
}

// 0x71000313b0 — 32B struct initializer
void FUN_71000313b0(u8 *param_1) {
    *param_1 = 1;
    *(u16 *)(param_1 + 2) = 0;
    *(u64 *)(param_1 + 8) = 0x100000000ULL;
    *(u64 *)(param_1 + 0x18) = 0;
}

// 0x71000314e0 — 24B set with flag byte
void FUN_71000314e0(u8 *param_1, u64 param_2) {
    *param_1 = 1;
    param_1[1] = param_1[1] | 1;
    *(u64 *)(param_1 + 8) = param_2;
}

// 0x7100031850 — zero 9 u64 fields
void FUN_7100031850(u64 *param_1) {
    param_1[7] = 0;
    param_1[8] = 0;
    param_1[0] = 0;
    param_1[5] = 0;
    param_1[6] = 0;
    param_1[3] = 0;
    param_1[4] = 0;
    param_1[1] = 0;
    param_1[2] = 0;
}

// 0x71000338f0 — memset 0x120 bytes
void FUN_71000338f0(void *param_1) {
    memset(param_1, 0, 0x120);
}

// 0x7100037d20 — memset 0x2028 bytes
void FUN_7100037d20(void *param_1) {
    memset(param_1, 0, 0x2028);
}

// 0x710003a5f0 — memset 0x3018 bytes
void FUN_710003a5f0(void *param_1) {
    memset(param_1, 0, 0x3018);
}

// 0x7100039e30 — zero 9 u64 fields (identical to FUN_7100031850)
void FUN_7100039e30(u64 *param_1) {
    param_1[7] = 0;
    param_1[8] = 0;
    param_1[0] = 0;
    param_1[5] = 0;
    param_1[6] = 0;
    param_1[3] = 0;
    param_1[4] = 0;
    param_1[1] = 0;
    param_1[2] = 0;
}

// 0x710003a240 — zero 9 u64 fields
void FUN_710003a240(u64 *param_1) {
    param_1[7] = 0;
    param_1[8] = 0;
    param_1[0] = 0;
    param_1[5] = 0;
    param_1[6] = 0;
    param_1[3] = 0;
    param_1[4] = 0;
    param_1[1] = 0;
    param_1[2] = 0;
}

// 0x710003a3c0 — zero 9 u64 fields
void FUN_710003a3c0(u64 *param_1) {
    param_1[7] = 0;
    param_1[8] = 0;
    param_1[0] = 0;
    param_1[5] = 0;
    param_1[6] = 0;
    param_1[3] = 0;
    param_1[4] = 0;
    param_1[1] = 0;
    param_1[2] = 0;
}

// 0x710003a4e0 — zero 9 u64 fields
void FUN_710003a4e0(u64 *param_1) {
    param_1[7] = 0;
    param_1[8] = 0;
    param_1[0] = 0;
    param_1[5] = 0;
    param_1[6] = 0;
    param_1[3] = 0;
    param_1[4] = 0;
    param_1[1] = 0;
    param_1[2] = 0;
}

// 0x710003aaa0 — conditional free via nn::mem::NumberLineAllocator::Free
extern void FUN_710003aab0(s32 param_1); // nn::mem::NumberLineAllocator::Free
void FUN_710003aaa0(s32 param_1, s32 param_2) {
    if (param_2 != -1) {
        FUN_710003aab0(param_1);
    }
}

// 0x710003ac20 — set format type fields
void FUN_710003ac20(s64 param_1, s32 param_2) {
    u32 uVar1 = 1;
    if (0xffff < param_2) {
        uVar1 = 2;
    }
    *(u32 *)(param_1 + 0x1c) = uVar1;
    *(s32 *)(param_1 + 0x28) = param_2;
}

// 0x710003bc80 — vtable + capacity init
extern u8 *PTR_DAT_71052a2390;
void FUN_710003bc80(s64 *param_1) {
    param_1[2] = 0;
    param_1[3] = 0;
    *param_1 = (s64)(PTR_DAT_71052a2390 + 0x10);
    param_1[1] = 0x1f00000000LL;
    *(u32 *)(param_1 + 4) = 0;
}

// 0x7100044c70 — init render state
void FUN_7100044c70(s64 param_1, u64 param_2) {
    *(u8 *)(param_1 + 0x18c) = 1;
    *(u64 *)(param_1 + 400) = 0;
    *(u16 *)(param_1 + 0x198) = 0;
    *(u64 *)(param_1 + 0xc0) = param_2;
}

// 0x7100047c70 — doubly-linked list splice
void FUN_7100047c70(s64 *param_1, s64 param_2) {
    s64 *plVar1 = (s64 *)(param_2 + 8);
    s64 lVar2 = *plVar1;
    *plVar1 = *param_1;
    *(s64 **)(lVar2 + 8) = param_1;
    *(s64 **)(param_1[0] + 8) = plVar1;
    *param_1 = lVar2;
}

// 0x710004c5e0 — reverse index access
u64 FUN_710004c5e0(s64 *param_1, u32 param_2) {
    return *(u64 *)(*param_1 + (s64)(s32)((s32)param_1[1] + ~(s32)param_2) * 8);
}

// 0x7100055470 — get base ptr with offset from nested struct
s64 FUN_7100055470(s64 param_1, s64 param_2) {
    s64 lVar1 = *(s64 *)(*(s64 *)(param_2 + 200) + 0x38);
    if (lVar1 != 0) {
        return lVar1 + (u64)*(u32 *)(param_1 + 0x34);
    }
    return 0;
}

// 0x7100060e80 — clear 4 u16 fields, set flags
void FUN_7100060e80(u16 *param_1) {
    param_1[4] = 0;
    param_1[5] = 0;
    param_1[6] = 0;
    param_1[7] = 0;
    *param_1 = (u16)(*param_1 & 0xe000 | 0x90);
}

// 0x7100060f20 — bit field write (2 bits each)
void FUN_7100060f20(u16 *param_1, u16 param_2, u32 param_3) {
    *param_1 = (u16)(param_2 & 3) | (u16)((param_3 & 3) << 2) | (*param_1 & 0xfff0);
}

// 0x7100060f40 — bit field write (3+1 bits)
void FUN_7100060f40(u16 *param_1, u32 param_2, u32 param_3) {
    *param_1 = (u16)((param_2 & 7) << 4) | (u16)((param_3 & 1) << 7) | (*param_1 & 0xff0f);
}

// 0x7100066040 — check nested char flag
u64 FUN_7100066040(u64 param_1) {
    if (param_1 != 0) {
        param_1 = (u64)(**(char **)(param_1 + 0x68) != '\0');
    }
    return param_1;
}

// 0x710006fcc0 — write 4 fields to struct
void FUN_710006fcc0(u32 param_1, u32 param_2, u64 param_3, s64 param_4) {
    *(u32 *)(param_4 + 0x24) = param_1;
    *(u32 *)(param_4 + 0x28) = param_2;
    *(u32 *)(param_4 + 0x30) = 0;
    *(u8 *)(param_4 + 0x34) = 1;
}

// 0x7100077eb0 — SNPrintf with format "%s_%d"
extern int FUN_7100a85650(char *buf, s64 sz, const char *fmt, ...); // nn::util::SNPrintf
int FUN_7100077eb0(char *param_1, s32 param_2, u64 param_3, s64 param_4) {
    return FUN_7100a85650(param_1, (s64)param_2, "%s_%d", param_3, (u64)*(u32 *)(param_4 + 4));
}

// 0x71000093f0 — check flags bitfield
u64 FUN_71000093f0(u64 param_1, s32 param_2) {
    if (param_1 != 0) {
        param_1 = (u64)((*(u64 *)(param_1 + 0xe8) & (s64)param_2) != 0);
    }
    return param_1;
}

// 0x71000145a0 — compare obj ptr at +0x8f0
bool FUN_71000145a0(s64 param_1, s64 param_2) {
    if (*(s64 **)(param_2 + 0x8f0) != (s64 *)0) {
        return **(s64 **)(param_2 + 0x8f0) == param_1;
    }
    return false;
}

// 0x71000145c0 — compare obj ptr at +0x8d0
bool FUN_71000145c0(s64 param_1, s64 param_2) {
    if (*(s64 **)(param_2 + 0x8d0) != (s64 *)0) {
        return **(s64 **)(param_2 + 0x8d0) == param_1;
    }
    return false;
}

// 0x710002b800 — malloc product of two dims
void FUN_710002b800(u64 param_1, s32 param_2, s32 param_3) {
    malloc((u32)(param_3 * param_2));
}

// 0x71000c73d8 — call FUN_710015ffc0 with offset
extern void FUN_710015ffc0(s64 param_1);
void FUN_71000c73d8(s64 param_1) {
    FUN_710015ffc0(param_1 + 0x48);
}

// 0x7100013730 — socket fcntl set nonblocking
extern s32 FUN_71001a9ba0(u64 sock, s32 cmd, u32 flags); // nnsocketFcntl
void FUN_7100013730(u64 param_1, s32 param_2) {
    u32 uVar1 = 2;
    if (param_2 != 0) {
        uVar1 = 0x802;
    }
    FUN_71001a9ba0(param_1, 4, uVar1);
}

// 0x71000b1940 — SDK version symbol reference
extern void FUN_71000b1950(const char *sym); // nn::util::ReferSymbol
void FUN_71000b1940(void) {
    FUN_71000b1950("SDK MW+Nintendo+PiaCommon-5_19_1");
}

// 0x71000b65e0 — init Pia timestamp entry
extern void FUN_71000b65f0(u32 *param_1); // nn::pia::common::Time::SetNow
void FUN_71000b65e0(u32 *param_1) {
    *param_1 = 0xffffffff;
    *(u64 *)(param_1 + 2) = 0;
    *(u8 *)(param_1 + 4) = 1;
    FUN_71000b65f0(param_1 + 2);
}

// 0x710013b910 — store system tick frequency
extern u64 FUN_710013b920(void); // nn::os::GetSystemTickFrequency
extern u64 *PTR_cFrequency_71052a2cd0;
void FUN_710013b910(void) {
    *PTR_cFrequency_71052a2cd0 = FUN_710013b920();
}

// 0x710013bc98 — SendMessageQueue wrapper returning 1
extern void FUN_710013bc00(void *q, u64 val); // nn::os::SendMessageQueue
u64 FUN_710013bc98(void *param_1, u64 param_2) {
    FUN_710013bc00(param_1, param_2);
    return 1;
}

// 0x710013bd08 — JamMessageQueue wrapper returning 1
extern void FUN_710013bd20(void *q, u64 val); // nn::os::JamMessageQueue
u64 FUN_710013bd08(void *param_1, u64 param_2) {
    FUN_710013bd20(param_1, param_2);
    return 1;
}

// 0x7100113400 — set byte field + set bit 3 in flags
void FUN_7100113400(s64 param_1, u8 param_2) {
    *(u8 *)(param_1 + 0xa3d) = param_2 & 1;
    *(u32 *)(param_1 + 0xd30) = *(u32 *)(param_1 + 0xd30) | 8;
}

// 0x7100113480 — set byte field + set bit 0x1000 in flags
void FUN_7100113480(s64 param_1, u8 param_2) {
    *(u8 *)(param_1 + 0x9ca) = param_2 & 1;
    *(u32 *)(param_1 + 0xd30) = *(u32 *)(param_1 + 0xd30) | 0x1000;
}

// 0x71001133a0 — set u16 pair + bit 2 in flags
void FUN_71001133a0(s64 param_1, u16 param_2) {
    *(u16 *)(param_1 + 0xa38) = 0xffff;
    *(u16 *)(param_1 + 0xa3a) = param_2;
    *(u32 *)(param_1 + 0xd30) = *(u32 *)(param_1 + 0xd30) | 2;
}

// 0x71001133c0 — set u16 pair (both params) + bit 2 in flags
void FUN_71001133c0(s64 param_1, u16 param_2, u16 param_3) {
    *(u16 *)(param_1 + 0xa38) = param_3;
    *(u16 *)(param_1 + 0xa3a) = param_2;
    *(u32 *)(param_1 + 0xd30) = *(u32 *)(param_1 + 0xd30) | 2;
}

// 0x71001133e0 — set byte field + bit 4 in flags
void FUN_71001133e0(s64 param_1, u8 param_2) {
    *(u8 *)(param_1 + 0xa3c) = param_2 & 1;
    *(u32 *)(param_1 + 0xd30) = *(u32 *)(param_1 + 0xd30) | 4;
}

// 0x71001134a0 — set byte field + bit 0x2000 in flags
void FUN_71001134a0(s64 param_1, u8 param_2) {
    *(u8 *)(param_1 + 0x9cb) = param_2 & 1;
    *(u32 *)(param_1 + 0xd30) = *(u32 *)(param_1 + 0xd30) | 0x2000;
}

// 0x71001136c0 — set byte field + bit 0x100000 in flags
void FUN_71001136c0(s64 param_1, u8 param_2) {
    *(u8 *)(param_1 + 0xa08) = param_2 & 1;
    *(u32 *)(param_1 + 0xd30) = *(u32 *)(param_1 + 0xd30) | 0x100000;
}

// 0x710012eb20 — set two u16 fields + bit 1 in flags
void FUN_710012eb20(s64 param_1, u16 param_2) {
    *(u16 *)(param_1 + 0x256) = param_2;
    *(u16 *)(param_1 + 600) = param_2;
    *(u32 *)(param_1 + 0x260) = *(u32 *)(param_1 + 0x260) | 1;
}

// 0x710012eb40 — set two u16 fields + bit 2 in flags
void FUN_710012eb40(s64 param_1, u16 param_2) {
    *(u16 *)(param_1 + 0x25a) = param_2;
    *(u16 *)(param_1 + 0x25c) = param_2;
    *(u32 *)(param_1 + 0x260) = *(u32 *)(param_1 + 0x260) | 2;
}

// 0x710012eb60 — set bool field + bit 4 in flags
void FUN_710012eb60(s64 param_1, u8 param_2) {
    *(u8 *)(param_1 + 0x25e) = param_2 & 1;
    *(u32 *)(param_1 + 0x260) = *(u32 *)(param_1 + 0x260) | 4;
}

// 0x710012eb80 — set bool field + bit 8 in flags
void FUN_710012eb80(s64 param_1, u8 param_2) {
    *(u8 *)(param_1 + 0x25f) = param_2 & 1;
    *(u32 *)(param_1 + 0x260) = *(u32 *)(param_1 + 0x260) | 8;
}

// 0x7100130aa0 — intrusive list insert after
void FUN_7100130aa0(s64 param_1, s64 *param_2) {
    s64 *puVar1 = *(s64 **)(param_1 + 8);
    *(s64 **)(param_1 + 8) = param_2;
    *param_2 = param_1;
    param_2[1] = (s64)puVar1;
    if (puVar1 != (s64 *)0) {
        *puVar1 = (s64)param_2;
    }
}

// 0x7100130ac0 — intrusive list insert before (head)
void FUN_7100130ac0(s64 *param_1, s64 *param_2) {
    s64 lVar1 = *param_1;
    *param_1 = (s64)param_2;
    *param_2 = lVar1;
    param_2[1] = (s64)param_1;
    if (lVar1 != 0) {
        *(s64 **)(lVar1 + 8) = param_2;
    }
}

// 0x7100149270 — store value at indexed position, update global
extern s32 *PTR_g_SessionBeginMonitoringContent_71052a2bd0;
void FUN_7100149270(s64 param_1, s32 param_2) {
    *(s32 *)(param_1 + (u64)*(u8 *)(param_1 + 0x162) * 4 + 0x180) = param_2;
    if (param_2 != 0) {
        *(s32 *)(PTR_g_SessionBeginMonitoringContent_71052a2bd0 + 0x124/4) = param_2;
    }
}

// 0x710014f090 — copy 3 u32 fields from src to dst
void FUN_710014f090(s64 param_1, s64 param_2) {
    *(u32 *)(param_1 + 0x10) = *(u32 *)(param_2 + 0x10);
    *(u32 *)(param_1 + 8) = *(u32 *)(param_2 + 8);
    *(u32 *)(param_1 + 0xc) = *(u32 *)(param_2 + 0xc);
}

// 0x710014f150 — vtable + zero field init
extern u8 *PTR_DAT_71052a3f38;
void FUN_710014f150(s64 *param_1) {
    *(u32 *)(param_1 + 1) = 0;
    *param_1 = (s64)(PTR_DAT_71052a3f38 + 0x10);
}

// 0x71001579a0 — vtable + sub-init
extern u8 *PTR_DAT_71052a2d20;
extern void FUN_71000b1cf0(s64 param_1);
void FUN_71001579a0(s64 param_1) {
    *(u8 **)(param_1 + 0x50) = PTR_DAT_71052a2d20 + 0x10;
    FUN_71000b1cf0(param_1 + 0x58);
}

// 0x71001604a0 — set 2-bit field in byte
void FUN_71001604a0(s64 param_1, u32 param_2) {
    *(u8 *)(param_1 + 0x78) = (u8)(*(u8 *)(param_1 + 0x78) & 0xf3 | (u8)((param_2 & 3) << 2));
}

// 0x7100182b30 — memcpy with u16 size from struct
void FUN_7100182b30(s64 param_1, void *param_2, s32 param_3, u64 param_4) {
    memcpy(param_2,
           (void *)(*(s64 *)(param_1 + 8) + (u64)*(u16 *)(param_1 + 0x14) + (s64)param_3),
           param_4 & 0xffff);
}

// 0x71001186270 — vtable + zero field init (same pattern as FUN_710014f150)
extern u8 *PTR_DAT_71052a4528;
void FUN_7100186270(s64 *param_1) {
    *(u32 *)(param_1 + 1) = 0;
    *param_1 = (s64)(PTR_DAT_71052a4528 + 0x10);
}

// 0x7100177c90 — delegate to FUN_7100175220
extern u8 FUN_7100175220(s64 param_1);
u8 FUN_7100177c90(s64 param_1) {
    return FUN_7100175220(*(s64 *)(param_1 + 0x2a8));
}

// 0x7100177cb0 — delegate to FUN_7100175220 (same as above)
u8 FUN_7100177cb0(s64 param_1) {
    return FUN_7100175220(*(s64 *)(param_1 + 0x2a8));
}

// 0x7100037790 — table lookup (u32 at stride 8)
extern u8 DAT_710446f5bc;
u32 FUN_7100037790(u64 param_1) {
    return *(u32 *)(&DAT_710446f5bc + (param_1 & 0xffffffff) * 8);
}
