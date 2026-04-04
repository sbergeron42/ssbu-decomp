// HARD-tier FUN_* functions — 0x7102 address range, batch hard-c-001
// Destructor cluster + recursive-free helpers

#include "types.h"

// ---- External function declarations ----------------------------------------

extern "C" {
    void FUN_710392e590(void *p);
    void FUN_71022f25f0(void *p);
    void FUN_7103724110(void *p);
    void FUN_71037238c0(void *a, void *b);
    void FUN_7102326230(void *p);
    void FUN_710233c660(void *p);
    void FUN_710234e140(void *p);
    void FUN_710239c610(void *p);
}

// ---- Vtable / RODATA address symbols (DAT_ prefix → linker PROVIDE) --------
// hidden visibility → compiler uses ADRP+ADD (direct) instead of ADRP+LDR (GOT)
#define DAT_HIDDEN __attribute__((visibility("hidden")))
// Group-1 (param_1[0x1d] + FUN_7103724110 base-dtor pattern)
extern "C" DAT_HIDDEN u64 DAT_71050b58c8;   // vtable for FUN_71022f29f0/f2a50 class
extern "C" DAT_HIDDEN u64 DAT_71050b5cb0;   // vtable for FUN_71022fae60
extern "C" DAT_HIDDEN u64 DAT_71050b5d88;   // vtable for FUN_71022fb970
extern "C" DAT_HIDDEN u64 DAT_71050b5e60;   // vtable for FUN_71022fc4b0
extern "C" DAT_HIDDEN u64 DAT_71050b5f38;   // vtable for FUN_71022fd360
extern "C" DAT_HIDDEN u64 DAT_71050b6080;   // vtable for FUN_71022fe000
extern "C" DAT_HIDDEN u64 DAT_71050b62d0;   // vtable for FUN_71022ffee0
extern "C" DAT_HIDDEN u64 DAT_71050b6a78;   // vtable for FUN_71023264e0
extern "C" DAT_HIDDEN u64 DAT_71050b6b20;   // vtable for FUN_7102327be0
extern "C" DAT_HIDDEN u64 DAT_71050b6bc8;   // vtable for FUN_7102328130
extern "C" DAT_HIDDEN u64 DAT_71050b6f80;   // vtable for FUN_71023338b0
extern "C" DAT_HIDDEN u64 DAT_71050b7448;   // vtable for FUN_710233bdb0
extern "C" DAT_HIDDEN u64 DAT_71050b7b58;   // vtable for FUN_7102359f00
extern "C" DAT_HIDDEN u64 DAT_71050b52f0;   // base-class vtable (tail-called via FUN_7103724110)
// Group-2 (param_1[1] + stp pattern, self-frees)
extern "C" DAT_HIDDEN u64 DAT_71050b77a0;   // vtable for FUN_710234e0f0
extern "C" DAT_HIDDEN u64 DAT_71050b8a00;   // vtable for FUN_710239be50
extern "C" DAT_HIDDEN u64 DAT_71050b8a20;   // vtable for FUN_710239c5c0
// Data args passed to FUN_71037238c0
extern "C" DAT_HIDDEN u64 DAT_7105327428;
extern "C" DAT_HIDDEN u64 DAT_7105327458;
extern "C" DAT_HIDDEN u64 DAT_7105327488;
extern "C" DAT_HIDDEN u64 DAT_71053274b8;
extern "C" DAT_HIDDEN u64 DAT_71053274e8;
extern "C" DAT_HIDDEN u64 DAT_7105327580;
extern "C" DAT_HIDDEN u64 DAT_7105327878;
extern "C" DAT_HIDDEN u64 DAT_71053278c8;
extern "C" DAT_HIDDEN u64 DAT_71053278f0;
extern "C" DAT_HIDDEN u64 DAT_7105327a38;
extern "C" DAT_HIDDEN u64 DAT_7105328118;
// Global singleton pointer (FUN_710232a990)
extern "C" DAT_HIDDEN u64 *DAT_71052c26c8;

// ---- Helper: D1 destructor body, group 1A (cleanup fn + direct free) -------
//   lVar1 = param_1[0x1d]; set vtable; null member;
//   if (lVar1) { cleanup(lVar1); free(lVar1); }
//   set base vtable; tail-call FUN_7103724110(param_1+0x50)

// 0x71022f29f0
void FUN_71022f29f0(u64 *param_1)
{
    u64 *x20 = (u64 *)param_1[0x1d];
    param_1[0] = (u64)&DAT_71050b58c8;
    param_1[0x1d] = 0;
    if (x20 != nullptr) {
        FUN_71022f25f0(x20);
        FUN_710392e590(x20);
    }
    param_1[0] = (u64)&DAT_71050b52f0;
    FUN_7103724110(param_1 + 10);
}

// 0x71022f2a50  — D0 (deleting) destructor: same but also frees self
void FUN_71022f2a50(u64 *param_1)
{
    u64 *x20 = (u64 *)param_1[0x1d];
    param_1[0] = (u64)&DAT_71050b58c8;
    param_1[0x1d] = 0;
    if (x20 != nullptr) {
        FUN_71022f25f0(x20);
        FUN_710392e590(x20);
    }
    param_1[0] = (u64)&DAT_71050b52f0;
    FUN_7103724110(param_1 + 10);
    FUN_710392e590(param_1);
}

// ---- Group 1B: D1 dtors that call FUN_71037238c0(*ptr, &DAT_*) -------------
//   puVar1 = param_1[0x1d]; set vtable; null member;
//   if (puVar1) { FUN_71037238c0(*puVar1, &DAT_xxx); free(puVar1); }
//   set base vtable; tail-call FUN_7103724110(param_1+0x50)

// 0x71022fae60
void FUN_71022fae60(u64 *param_1)
{
    u64 *puVar1 = (u64 *)param_1[0x1d];
    param_1[0] = (u64)&DAT_71050b5cb0;
    param_1[0x1d] = 0;
    if (puVar1 != nullptr) {
        FUN_71037238c0((void *)puVar1[0], &DAT_7105327428);
        FUN_710392e590(puVar1);
    }
    param_1[0] = (u64)&DAT_71050b52f0;
    FUN_7103724110(param_1 + 10);
}

// 0x71022fb970
void FUN_71022fb970(u64 *param_1)
{
    u64 *puVar1 = (u64 *)param_1[0x1d];
    param_1[0] = (u64)&DAT_71050b5d88;
    param_1[0x1d] = 0;
    if (puVar1 != nullptr) {
        FUN_71037238c0((void *)puVar1[0], &DAT_7105327458);
        FUN_710392e590(puVar1);
    }
    param_1[0] = (u64)&DAT_71050b52f0;
    FUN_7103724110(param_1 + 10);
}

// 0x71022fc4b0
void FUN_71022fc4b0(u64 *param_1)
{
    u64 *puVar1 = (u64 *)param_1[0x1d];
    param_1[0] = (u64)&DAT_71050b5e60;
    param_1[0x1d] = 0;
    if (puVar1 != nullptr) {
        FUN_71037238c0((void *)puVar1[0], &DAT_7105327488);
        FUN_710392e590(puVar1);
    }
    param_1[0] = (u64)&DAT_71050b52f0;
    FUN_7103724110(param_1 + 10);
}

// 0x71022fd360
void FUN_71022fd360(u64 *param_1)
{
    u64 *puVar1 = (u64 *)param_1[0x1d];
    param_1[0] = (u64)&DAT_71050b5f38;
    param_1[0x1d] = 0;
    if (puVar1 != nullptr) {
        FUN_71037238c0((void *)puVar1[0], &DAT_71053274b8);
        FUN_710392e590(puVar1);
    }
    param_1[0] = (u64)&DAT_71050b52f0;
    FUN_7103724110(param_1 + 10);
}

// 0x71022fe000
void FUN_71022fe000(u64 *param_1)
{
    u64 *puVar1 = (u64 *)param_1[0x1d];
    param_1[0] = (u64)&DAT_71050b6080;
    param_1[0x1d] = 0;
    if (puVar1 != nullptr) {
        FUN_71037238c0((void *)puVar1[0], &DAT_71053274e8);
        FUN_710392e590(puVar1);
    }
    param_1[0] = (u64)&DAT_71050b52f0;
    FUN_7103724110(param_1 + 10);
}

// 0x71022ffee0
void FUN_71022ffee0(u64 *param_1)
{
    u64 *puVar1 = (u64 *)param_1[0x1d];
    param_1[0] = (u64)&DAT_71050b62d0;
    param_1[0x1d] = 0;
    if (puVar1 != nullptr) {
        FUN_71037238c0((void *)puVar1[0], &DAT_7105327580);
        FUN_710392e590(puVar1);
    }
    param_1[0] = (u64)&DAT_71050b52f0;
    FUN_7103724110(param_1 + 10);
}

// 0x71023264e0 — group 1A variant (FUN_7102326230 cleanup)
void FUN_71023264e0(u64 *param_1)
{
    u64 lVar1 = param_1[0x1d];
    param_1[0] = (u64)&DAT_71050b6a78;
    param_1[0x1d] = 0;
    if (lVar1 != 0) {
        FUN_7102326230((void *)lVar1);
        FUN_710392e590((void *)lVar1);
    }
    param_1[0] = (u64)&DAT_71050b52f0;
    FUN_7103724110(param_1 + 10);
}

// 0x7102327be0
void FUN_7102327be0(u64 *param_1)
{
    u64 *puVar1 = (u64 *)param_1[0x1d];
    param_1[0] = (u64)&DAT_71050b6b20;
    param_1[0x1d] = 0;
    if (puVar1 != nullptr) {
        FUN_71037238c0((void *)puVar1[0], &DAT_7105327878);
        FUN_710392e590(puVar1);
    }
    param_1[0] = (u64)&DAT_71050b52f0;
    FUN_7103724110(param_1 + 10);
}

// 0x7102328130
void FUN_7102328130(u64 *param_1)
{
    u64 *puVar1 = (u64 *)param_1[0x1d];
    param_1[0] = (u64)&DAT_71050b6bc8;
    param_1[0x1d] = 0;
    if (puVar1 != nullptr) {
        FUN_71037238c0((void *)puVar1[0], &DAT_71053278c8);
        FUN_710392e590(puVar1);
    }
    param_1[0] = (u64)&DAT_71050b52f0;
    FUN_7103724110(param_1 + 10);
}

// 0x710232a990 — global-singleton cleanup + free
void FUN_710232a990(u64 *param_1)
{
    u64 *ptr = (u64 *)param_1[0x1d];
    param_1[0x1d] = 0;
    if (ptr == nullptr) return;

    FUN_71037238c0((void *)ptr[0], &DAT_71053278f0);

    u64 *obj = DAT_71052c26c8;
    if (obj != nullptr) {
        u64 *vtable = (u64 *)obj[0];
        void (*fn)(u64 *) = (void (*)(u64 *))vtable[1];
        fn(obj);
        DAT_71052c26c8 = nullptr;
    }

    FUN_710392e590(ptr);
}

// 0x71023338b0
void FUN_71023338b0(u64 *param_1)
{
    u64 *puVar1 = (u64 *)param_1[0x1d];
    param_1[0] = (u64)&DAT_71050b6f80;
    param_1[0x1d] = 0;
    if (puVar1 != nullptr) {
        FUN_71037238c0((void *)puVar1[0], &DAT_7105327a38);
        FUN_710392e590(puVar1);
    }
    param_1[0] = (u64)&DAT_71050b52f0;
    FUN_7103724110(param_1 + 10);
}

// 0x710233bdb0 — group 1A (FUN_710233c660 cleanup)
void FUN_710233bdb0(u64 *param_1)
{
    u64 lVar1 = param_1[0x1d];
    param_1[0] = (u64)&DAT_71050b7448;
    param_1[0x1d] = 0;
    if (lVar1 != 0) {
        FUN_710233c660((void *)lVar1);
        FUN_710392e590((void *)lVar1);
    }
    param_1[0] = (u64)&DAT_71050b52f0;
    FUN_7103724110(param_1 + 10);
}

// ---- Group 2: param_1[1] with stp(vtable,0,[x0]) + self-free ---------------

// 0x710234e0f0
void FUN_710234e0f0(u64 *param_1)
{
    u64 *x20 = (u64 *)param_1[1];
    param_1[0] = (u64)&DAT_71050b77a0;
    param_1[1] = 0;
    if (x20 != nullptr) {
        FUN_710234e140(x20);
        FUN_710392e590(x20);
    }
    FUN_710392e590(param_1);
}

// 0x710239be50 — group 2 with nested inner ptr
void FUN_710239be50(u64 *param_1)
{
    u64 *x20 = (u64 *)param_1[1];
    param_1[0] = (u64)&DAT_71050b8a00;
    param_1[1] = 0;
    if (x20 != nullptr) {
        u64 inner = *(u64 *)((char *)x20 + 0xb0);
        *(u64 *)((char *)x20 + 0xb0) = 0;
        if (inner != 0) {
            FUN_710392e590((void *)inner);
        }
        FUN_710392e590(x20);
    }
    FUN_710392e590(param_1);
}

// 0x710239c5c0
void FUN_710239c5c0(u64 *param_1)
{
    u64 *x20 = (u64 *)param_1[1];
    param_1[0] = (u64)&DAT_71050b8a20;
    param_1[1] = 0;
    if (x20 != nullptr) {
        FUN_710239c610(x20);
        FUN_710392e590(x20);
    }
    FUN_710392e590(param_1);
}

// 0x7102359f00 — group 1B
void FUN_7102359f00(u64 *param_1)
{
    u64 *puVar1 = (u64 *)param_1[0x1d];
    param_1[0] = (u64)&DAT_71050b7b58;
    param_1[0x1d] = 0;
    if (puVar1 != nullptr) {
        FUN_71037238c0((void *)puVar1[0], &DAT_7105328118);
        FUN_710392e590(puVar1);
    }
    param_1[0] = (u64)&DAT_71050b52f0;
    FUN_7103724110(param_1 + 10);
}

// ---- Recursive free helpers ------------------------------------------------

// 0x71022b5980 — binary tree node recursive delete
void FUN_71022b5980(u64 *p)
{
    if (p) {
        FUN_71022b5980((u64 *)p[0]);
        FUN_71022b5980((u64 *)p[1]);
        FUN_710392e590(p);
    }
}

// 0x7102358360 — tree node recursive delete with extra field
void FUN_7102358360(u64 *p)
{
    if (p) {
        FUN_7102358360((u64 *)p[0]);
        FUN_7102358360((u64 *)p[1]);
        u64 p5 = p[5];
        if (p5 != 0) {
            p[6] = p5;
            FUN_710392e590((void *)p5);
        }
        FUN_710392e590(p);
    }
}
