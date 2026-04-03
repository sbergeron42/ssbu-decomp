#include "types.h"

// EASY-tier batch 003 — pool-a worker

// SDK type forward declarations
namespace nn { namespace os {
    struct MutexType;
    struct EventType;
    void InitializeMutex(MutexType*, bool, int);
    void WaitEvent(EventType*);
    void ClearEvent(EventType*);
    void LockMutex(MutexType*);
    void UnlockMutex(MutexType*);
} }
namespace nn { namespace util { void ReferSymbol(const void*); } }

// External function forward declarations
extern void FUN_7100099520(s64);
extern void FUN_71000b2850(s64);
extern void FUN_71000b2b10(s64, s64);
extern void FUN_7100127500(u64);
extern void FUN_7100181270(void);
extern void FUN_710017f100(u64);
extern void FUN_710017f1d0(u64);
extern void FUN_710015ffc0(s64);
extern void FUN_71000c7460(void);
extern void FUN_71039c0db0(void*, u64);
extern void FUN_71039c0da0(s64);
extern void FUN_71001cf300(u64, u64, s64);
extern void FUN_71001efaf0(s64);

extern "C" void *memset(void*, int, unsigned long);
extern "C" void free(void*);

// ── 16-byte functions ────────────────────────────────────────────────────────

// 0x710008a740
void FUN_710008a740(s64 param_1)
{
    FUN_7100099520(param_1 + 0x118);
}

// 0x71000b3840
void FUN_71000b3840(s64 param_1, u64 param_2)
{
    *(u64 *)(param_1 + 0x598) = param_2;
}

// 0x71000b3850
void FUN_71000b3850(s64 param_1)
{
    *(u64 *)(param_1 + 0x598) = 0;
}

// 0x71000b4150
void FUN_71000b4150(s64 param_1, u64 param_2, u64 param_3)
{
    *(u64 *)(param_1 + 0x18) = param_2;
    *(u64 *)(param_1 + 0x20) = param_3;
}

// 0x71000b4c30
void FUN_71000b4c30(nn::os::MutexType *param_1)
{
    nn::os::InitializeMutex(param_1, true, 0);
}

// 0x71000b50c0
void FUN_71000b50c0(void *param_1)
{
    memset(param_1, 0, 0x188);
}

// 0x71000bb9d0
void FUN_71000bb9d0(u8 *param_1, u8 param_2)
{
    *param_1 = param_2;
}

// 0x71000bccc0
void FUN_71000bccc0(void)
{
    nn::util::ReferSymbol("SDK MW+Nintendo+Pia-5_19_1");
}

// 0x71000beb20
void FUN_71000beb20(s64 param_1)
{
    FUN_71000b2850(param_1 + 8);
}

// 0x71000beb30
void FUN_71000beb30(s64 param_1, s64 param_2)
{
    FUN_71000b2b10(param_1 + 8, param_2 + 8);
}

// 0x71000bfa90
void FUN_71000bfa90(u64 *param_1)
{
    *param_1 = 0;
}

// 0x71000c4cc0
void FUN_71000c4cc0(s64 param_1, u32 param_2)
{
    *(u32 *)(param_1 + 0x58) = param_2;
}

// 0x71001129a0
void FUN_71001129a0(s64 param_1, u32 param_2)
{
    *(u32 *)(param_1 + 8) = param_2;
}

// 0x71001129b0
void FUN_71001129b0(s64 param_1, u32 param_2)
{
    *(u32 *)(param_1 + 0xc) = param_2;
}

// 0x71001129c0
void FUN_71001129c0(s64 param_1, u32 param_2)
{
    *(u32 *)(param_1 + 0x268) = param_2;
}

// 0x71001129d0
void FUN_71001129d0(s64 param_1, u16 param_2)
{
    *(u16 *)(param_1 + 0x10) = param_2;
}

// 0x71001129e0
void FUN_71001129e0(s64 param_1, u16 param_2)
{
    *(u16 *)(param_1 + 0x12) = param_2;
}

// 0x71001129f0
void FUN_71001129f0(s64 param_1, u16 param_2)
{
    *(u16 *)(param_1 + 0x14) = param_2;
}

// 0x7100112c10
void FUN_7100112c10(s64 param_1, u64 param_2)
{
    *(u64 *)(param_1 + 0x240) = param_2;
}

// 0x7100112c20
void FUN_7100112c20(s64 param_1, u64 param_2)
{
    *(u64 *)(param_1 + 0x248) = param_2;
}

// 0x71001170c0
void FUN_71001170c0(u64 *param_1)
{
    FUN_7100127500(*param_1);
}

// 0x710012fd50
void FUN_710012fd50(s64 param_1, u64 param_2)
{
    *(u64 *)(param_1 + 0x60) = param_2;
}

// 0x710013bb20
void FUN_710013bb20(s64 param_1)
{
    nn::os::WaitEvent((nn::os::EventType *)(param_1 + 0x20));
}

// 0x710013bb70
void FUN_710013bb70(s64 param_1)
{
    nn::os::ClearEvent((nn::os::EventType *)(param_1 + 0x20));
}

// 0x710013bde0
void FUN_710013bde0(s64 param_1)
{
    nn::os::LockMutex((nn::os::MutexType *)(param_1 + 0x20));
}

// 0x710013bdf0
void FUN_710013bdf0(s64 param_1)
{
    nn::os::UnlockMutex((nn::os::MutexType *)(param_1 + 0x20));
}

// 0x710013e3f0
void FUN_710013e3f0(void)
{
    nn::util::ReferSymbol("SDK MW+Nintendo+PiaSession-5_19_1");
}

// 0x7100146c00
u16 FUN_7100146c00(s64 param_1)
{
    return *(u16 *)(param_1 + 0x208);
}

// 0x7100147350
void FUN_7100147350(s64 param_1)
{
    *(u64 *)(param_1 + 0xa0) = 0;
    *(u64 *)(param_1 + 0xa8) = 0;
}

// 0x7100147820
void FUN_7100147820(s64 param_1)
{
    *(u64 *)(param_1 + 0xb0) = 0;
}

// 0x710014f190
void FUN_710014f190(s64 param_1)
{
    *(u32 *)(param_1 + 8) = 0;
}

// 0x710014f1a0
void FUN_710014f1a0(s64 param_1, u32 param_2)
{
    *(u32 *)(param_1 + 8) = param_2;
}

// 0x71001531b0
void FUN_71001531b0(void)
{
    nn::util::ReferSymbol("SDK MW+Nintendo+PiaTransport-5_19_1");
}

// 0x7100158060
void FUN_7100158060(s64 param_1, u64 param_2)
{
    *(u64 *)(param_1 + 0x610) = param_2;
}

// 0x710015e540
void FUN_710015e540(s64 param_1, u8 param_2)
{
    *(u8 *)(param_1 + 0x38) = param_2;
}

// 0x710015e550
void FUN_710015e550(s64 param_1, u64 param_2)
{
    *(u64 *)(param_1 + 0x40) = param_2;
}

// 0x7100160480
void FUN_7100160480(s64 param_1, u32 param_2)
{
    *(u32 *)(param_1 + 0x70) = param_2;
}

// 0x71001604e0
void FUN_71001604e0(s64 param_1, u8 param_2)
{
    *(u8 *)(param_1 + 0x79) = param_2;
}

// 0x7100160b20
void FUN_7100160b20(s64 param_1)
{
    FUN_710015ffc0(param_1 + 0x88);
}

// 0x7100162470
void FUN_7100162470(s64 param_1)
{
    (*(void (**)())(*(s64 *)(*(s64 *)(param_1 + 0x60)) + 0x80))();
}

// 0x7100163170
void FUN_7100163170(s64 param_1, u64 param_2)
{
    *(u64 *)(param_1 + 0x50) = param_2;
}

// 0x7100163180
void FUN_7100163180(s64 param_1, u64 param_2)
{
    *(u64 *)(param_1 + 0x48) = param_2;
}

// 0x7100175240
void FUN_7100175240(s64 param_1)
{
    if (*(s64 *)(param_1 + 0x18) != 0) {
        FUN_7100181270();
    }
}

// 0x7100175780
void FUN_7100175780(s64 param_1)
{
    FUN_710017f100(*(u64 *)(param_1 + 0x18));
}

// 0x7100175790
void FUN_7100175790(s64 param_1)
{
    FUN_710017f1d0(*(u64 *)(param_1 + 0x18));
}

// 0x7100177110
void FUN_7100177110(s64 param_1, u64 param_2)
{
    *(u64 *)(param_1 + 8) = param_2;
}

// 0x710017dde0
void FUN_710017dde0(s64 param_1, u32 param_2)
{
    *(u32 *)(param_1 + 0x46c) = param_2;
}

// 0x7100193200
void FUN_7100193200(s64 param_1, u64 param_2)
{
    *(u64 *)(param_1 + 0x60) = param_2;
}

// 0x7100193210
void FUN_7100193210(s64 param_1)
{
    *(u64 *)(param_1 + 0x60) = 0;
}

// 0x71001932a0
void FUN_71001932a0(s64 param_1)
{
    *(u64 *)(param_1 + 0x68) = 0;
}

// 0x71001932b0
void FUN_71001932b0(s64 param_1, u64 param_2)
{
    *(u64 *)(param_1 + 0x70) = param_2;
}

// 0x7100193540
void FUN_7100193540(s64 param_1, u64 param_2)
{
    *(u64 *)(param_1 + 0x120) = param_2;
}

// 0x7100193550
void FUN_7100193550(s64 param_1)
{
    *(u64 *)(param_1 + 0x120) = 0;
}

// 0x7100193a80
u16 FUN_7100193a80(s64 param_1)
{
    return *(u16 *)(param_1 + 0x35a);
}

// 0x7100193a90
u16 FUN_7100193a90(s64 param_1)
{
    return *(u16 *)(param_1 + 0x35c);
}

// 0x710019b540
void FUN_710019b540(s64 param_1, u64 param_2)
{
    *(u64 *)(param_1 + 0x48) = param_2;
}

// 0x710019b550
void FUN_710019b550(s64 param_1, u64 param_2)
{
    *(u64 *)(param_1 + 0x50) = param_2;
}

// 0x71001a87c0
void FUN_71001a87c0(s64 param_1)
{
    *(u32 *)(param_1 + 0xf8) = 0;
}

// 0x71001beae0
u64 FUN_71001beae0(void)
{
    return 1;
}

// 0x71001beaf0
u64 FUN_71001beaf0(void)
{
    return 1;
}

// 0x71001bef90
void FUN_71001bef90(s64 param_1, u32 param_2)
{
    *(u32 *)(param_1 + 0xc) = param_2;
}

// 0x71001cbc50
void FUN_71001cbc50(void *param_1, u64 param_2)
{
    if (*(u8 *)((s64)param_1 + 0x70) != 0) {
        return;
    }
    FUN_71039c0db0(param_1, param_2);
}

// 0x71001cde00
void FUN_71001cde00(s64 param_1)
{
    *(u32 *)(param_1 + 0x58) = 0;
    *(u8 *)(param_1 + 0x70) = 0;
    FUN_71039c0da0(param_1);
}

// 0x71001cf560
void FUN_71001cf560(u64 param_1, u64 param_2, s64 param_3, s64 param_4)
{
    FUN_71001cf300(param_1, param_2, param_3 * param_4 * 8);
}

// 0x71001dc780
u64 FUN_71001dc780(void)
{
    return 4;
}

// 0x71001dc790
u64 FUN_71001dc790(void)
{
    return 6;
}

// 0x71001dc7a0
u64 FUN_71001dc7a0(void)
{
    return 0xd;
}

// 0x71001e1010
void FUN_71001e1010(s64 param_1)
{
    FUN_71001efaf0(param_1 + 0x80);
}

// 0x71001f30c0
u64 FUN_71001f30c0(void)
{
    return 3;
}

// 0x710022e6a0
void FUN_710022e6a0(s64 param_1, u64 param_2)
{
    *(u64 *)(param_1 + 0x50) = param_2;
}

// 0x710024d060
void FUN_710024d060(s64 param_1, u32 param_2, u32 param_3)
{
    *(u32 *)(param_1 + 0x24) = param_2;
    *(u32 *)(param_1 + 0x28) = param_3;
}

// 0x7100255b60
void FUN_7100255b60(s64 param_1, u32 param_2)
{
    *(u32 *)(param_1 + 0xcc) = param_2;
}

// 0x71004eb620
f32 FUN_71004eb620(void)
{
    return 0.0f;
}

// 0x71004eb630
f32 FUN_71004eb630(void)
{
    return 0.0f;
}

// ── 32-byte functions ────────────────────────────────────────────────────────

// 0x71000c74b0
u16 FUN_71000c74b0(s64 param_1)
{
    return *(u16 *)(param_1 + 0x22);
}

// 0x7100130530
u64 FUN_7100130530(void)
{
    return 0x32;
}

// 0x7100160300
bool FUN_7100160300(s64 param_1)
{
    return (*(u8 *)(param_1 + 0x78) & 0xc) == 8;
}

// 0x71001603c0
bool FUN_71001603c0(s64 param_1, s64 param_2)
{
    return *(s64 *)(param_1 + 0x68) == *(s64 *)(param_2 + 0x68);
}

// 0x71001603e0
bool FUN_71001603e0(s64 param_1, s64 param_2)
{
    return *(s32 *)(param_1 + 0x74) == *(s32 *)(param_2 + 0x74);
}

// 0x7100160400
bool FUN_7100160400(s64 param_1, s64 param_2)
{
    return *(s32 *)(param_1 + 0x70) == *(s32 *)(param_2 + 0x70);
}

// 0x71001623f0
u64 FUN_71001623f0(s64 param_1)
{
    if (*(s64 *)(param_1 + 0xa8) != 0) {
        return *(u64 *)(*(s64 *)(param_1 + 0xa8) + 8);
    }
    return 0;
}

// 0x7100162410
u64 FUN_7100162410(s64 param_1)
{
    if (*(s64 *)(param_1 + 0xa8) != 0) {
        return *(u64 *)(*(s64 *)(param_1 + 0xa8) + 0x10);
    }
    return 0;
}

// 0x7100165690
s32 FUN_7100165690(s64 param_1)
{
    if (*(s64 *)(param_1 + 8) != 0) {
        return *(s32 *)(*(s64 *)(param_1 + 8) + 0x10) + -0x18;
    }
    return 0;
}

// 0x71001b0910
u8 FUN_71001b0910(u8 *param_1)
{
    return *param_1 & 0x3f;
}

// 0x71001b4560
void FUN_71001b4560(s64 param_1)
{
    void (*func)() = *(void (**)())(param_1 - 0x10);
    if (func != nullptr) {
        func();
        return;
    }
    free((void *)(param_1 - 0x10));
}

// 0x71001cd870
void FUN_71001cd870(s64 param_1)
{
    *(u32 *)(param_1 + 0x40) = 5;
    if (*(void (**)())(param_1 + 0x28) != nullptr) {
        ((void (*)(s64, s64))(*(u64 *)(param_1 + 0x28)))(param_1, param_1 + 0x30);
    }
}

// 0x71001e16f0
void FUN_71001e16f0(s64 param_1)
{
    s64 *obj = *(s64 **)(param_1 + 8);
    ((void (*)(s64 *, s64))(*(u64 *)(*obj + 0x58)))(obj, param_1);
}

// 0x71002275c0
void FUN_71002275c0(s64 param_1, u32 param_2)
{
    *(u32 *)(param_1 + 0x70) = param_2;
}

// ── 48-byte functions ────────────────────────────────────────────────────────

// 0x71000c8800
void FUN_71000c8800(void) {}

// 0x710012cf40
void FUN_710012cf40(s64 param_1, u16 param_2)
{
    *(u16 *)(param_1 + 0x18) = param_2;
}

// 0x71001b4730
void FUN_71001b4730(void) {}

// 0x71001d6410
void FUN_71001d6410(s64 param_1, s32 param_2)
{
    *(s32 *)(param_1 + 0x40) = param_2;
    if ((param_2 == 5) && (*(void (**)())(param_1 + 0x28) != nullptr)) {
        ((void (*)(s64, s64))(*(u64 *)(param_1 + 0x28)))(param_1, param_1 + 0x30);
    }
}

// ── 56-byte functions ────────────────────────────────────────────────────────

// 0x71000c5330
void FUN_71000c5330(s64 param_1)
{
    if (*(s64 *)(param_1 + 0x90) != 0) {
        FUN_71000c7460();
    }
}

// ── 64-byte functions ────────────────────────────────────────────────────────

// 0x71000d3390
void FUN_71000d3390(s64 param_1, u64 param_2)
{
    *(u64 *)(param_1 + 0x258) = param_2;
}

// 0x710015fb10
void FUN_710015fb10(u8 *param_1)
{
    if (*param_1 != 0) {
        return;
    }
    *param_1 = 1;
    *(u64 *)(param_1 + 4) = (u64)-1;
    *(u64 *)(param_1 + 0x10) = 0;
    *(u8 *)(param_1 + 0x18) = 0;
    *(u64 *)(param_1 + 0x48) = 0;
    *(u64 *)(param_1 + 0x1c) = 0;
    *(u32 *)(param_1 + 0xc) = 0xffffffff;
    *(u32 *)(param_1 + 0x50) = 0;
}

// 0x71001ae560
void FUN_71001ae560(s64 param_1, s64 param_2, u8 param_3)
{
    s64 lVar1 = *(s64 *)(param_1 + 8);
    while (true) {
        if (lVar1 == param_1) {
            return;
        }
        if (*(s64 *)(lVar1 + 0x10) == param_2) break;
        lVar1 = *(s64 *)(lVar1 + 8);
    }
    *(u8 *)(lVar1 + 0x28) = param_3 & 1;
}

// ── 80-byte functions ────────────────────────────────────────────────────────

// 0x71003cb410
void FUN_71003cb410(s64 param_1)
{
    s64 *obj = *(s64 **)(param_1 + 0x40);
    ((void (*)(s64 *, s64))(*(u64 *)(*obj + 0x148)))(obj, 0);
}
