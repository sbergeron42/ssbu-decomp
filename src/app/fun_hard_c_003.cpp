#include "types.h"

// HARD-tier FUN_* functions — 0x7102 address range, batch hard-c-003

extern "C" {
    void FUN_710392e590(void *p);
    void FUN_7102682050(void *p);
    void FUN_710271fc10(void *p);
    void FUN_71027171a0(void *p);
    void FUN_71025d7310(void *p);
    void FUN_710273c6d0(void *p);
    void FUN_710273a4c0(void *p);
}

#define DAT_HIDDEN __attribute__((visibility("hidden")))

extern "C" DAT_HIDDEN u64 DAT_71050ca228;
extern "C" DAT_HIDDEN u64 DAT_71050ca398;
extern "C" DAT_HIDDEN u64 DAT_71050ca548;
extern "C" DAT_HIDDEN u64 DAT_71050d44c8;
extern "C" DAT_HIDDEN u64 DAT_71050d5f78;
extern "C" DAT_HIDDEN u64 DAT_71050dabb8;
extern "C" DAT_HIDDEN u64 DAT_71050dacb8;

// 0x71026808d0 — D0 destructor, group 2 + vtable call at inner+0x20
void FUN_71026808d0(u64 *param_1)
{
    u64 lVar2 = param_1[1];
    param_1[0] = (u64)&DAT_71050ca228;
    param_1[1] = 0;
    if (lVar2 != 0) {
        u64 *plVar1 = (u64 *)*(u64 *)(lVar2 + 0x20);
        *(u64 *)(lVar2 + 0x20) = 0;
        if (plVar1 != nullptr) {
            u64 *vtable = (u64 *)plVar1[0];
            ((void (*)(u64 *))vtable[1])(plVar1);
        }
        FUN_710392e590((void *)lVar2);
    }
    FUN_710392e590(param_1);
}

// 0x7102681ff0 — D0 destructor, group 2 + copy-then-free at inner+0x40 + sub-cleanup
void FUN_7102681ff0(u64 *param_1)
{
    u64 lVar1 = param_1[1];
    param_1[0] = (u64)&DAT_71050ca398;
    param_1[1] = 0;
    if (lVar1 != 0) {
        u64 tmp = *(u64 *)(lVar1 + 0x40);
        if (tmp != 0) {
            *(u64 *)(lVar1 + 0x48) = tmp;
            FUN_710392e590((void *)tmp);
        }
        FUN_7102682050((void *)(lVar1 + 0x20));
        FUN_710392e590((void *)lVar1);
    }
    FUN_710392e590(param_1);
}

// 0x7102685820 — D0 destructor, group 2 + vtable call at inner+0x20
void FUN_7102685820(u64 *param_1)
{
    u64 lVar2 = param_1[1];
    param_1[0] = (u64)&DAT_71050ca548;
    param_1[1] = 0;
    if (lVar2 != 0) {
        u64 *plVar1 = (u64 *)*(u64 *)(lVar2 + 0x20);
        *(u64 *)(lVar2 + 0x20) = 0;
        if (plVar1 != nullptr) {
            u64 *vtable = (u64 *)plVar1[0];
            ((void (*)(u64 *))vtable[1])(plVar1);
        }
        FUN_710392e590((void *)lVar2);
    }
    FUN_710392e590(param_1);
}

// 0x710268aba0 — linked list free (param_1[2] chain) + head free at param_1[0]
void FUN_710268aba0(u64 *param_1)
{
    u64 *cur = (u64 *)param_1[2];
    while (cur != nullptr) {
        u64 *next = (u64 *)cur[0];
        FUN_710392e590(cur);
        cur = next;
    }
    u64 tmp = param_1[0];
    param_1[0] = 0;
    if (tmp != 0)
        FUN_710392e590((void *)tmp);
}

// 0x71026af730 — linked list free (same pattern as FUN_710268aba0)
void FUN_71026af730(u64 *param_1)
{
    u64 *cur = (u64 *)param_1[2];
    while (cur != nullptr) {
        u64 *next = (u64 *)cur[0];
        FUN_710392e590(cur);
        cur = next;
    }
    u64 tmp = param_1[0];
    param_1[0] = 0;
    if (tmp != 0)
        FUN_710392e590((void *)tmp);
}

// 0x7102717350 — D1 destructor, param_1[0x150] field + sub-cleanup at param_1+0xe8
void FUN_7102717350(u64 *param_1)
{
    u64 lVar1 = param_1[0x150];
    param_1[0] = (u64)&DAT_71050d44c8;
    param_1[0x150] = 0;
    if (lVar1 != 0) {
        FUN_710271fc10((void *)lVar1);
        FUN_710392e590((void *)lVar1);
    }
    FUN_71027171a0(param_1 + 0xe8);
    FUN_71025d7310(param_1);
}

// 0x71027173a0 — D0 destructor (same as FUN_7102717350 + free self)
void FUN_71027173a0(u64 *param_1)
{
    u64 lVar1 = param_1[0x150];
    param_1[0] = (u64)&DAT_71050d44c8;
    param_1[0x150] = 0;
    if (lVar1 != 0) {
        FUN_710271fc10((void *)lVar1);
        FUN_710392e590((void *)lVar1);
    }
    FUN_71027171a0(param_1 + 0xe8);
    FUN_71025d7310(param_1);
    FUN_710392e590(param_1);
}

// 0x710273a570 — D1 destructor, param_1[0x128] field + sub-cleanup at param_1+0xe7
void FUN_710273a570(u64 *param_1)
{
    u64 lVar1 = param_1[0x128];
    param_1[0] = (u64)&DAT_71050d5f78;
    param_1[0x128] = 0;
    if (lVar1 != 0) {
        FUN_710273c6d0((void *)lVar1);
        FUN_710392e590((void *)lVar1);
    }
    FUN_710273a4c0(param_1 + 0xe7);
    FUN_71025d7310(param_1);
}

// 0x710273a5c0 — D0 destructor (same as FUN_710273a570 + free self)
void FUN_710273a5c0(u64 *param_1)
{
    u64 lVar1 = param_1[0x128];
    param_1[0] = (u64)&DAT_71050d5f78;
    param_1[0x128] = 0;
    if (lVar1 != 0) {
        FUN_710273c6d0((void *)lVar1);
        FUN_710392e590((void *)lVar1);
    }
    FUN_710273a4c0(param_1 + 0xe7);
    FUN_71025d7310(param_1);
    FUN_710392e590(param_1);
}

// 0x7102752380 — D0 destructor, group 2 + vtable call at inner+0x10
void FUN_7102752380(u64 *param_1)
{
    u64 lVar2 = param_1[1];
    param_1[0] = (u64)&DAT_71050dabb8;
    param_1[1] = 0;
    if (lVar2 != 0) {
        u64 *plVar1 = (u64 *)*(u64 *)(lVar2 + 0x10);
        *(u64 *)(lVar2 + 0x10) = 0;
        if (plVar1 != nullptr) {
            u64 *vtable = (u64 *)plVar1[0];
            ((void (*)(u64 *))vtable[1])(plVar1);
        }
        FUN_710392e590((void *)lVar2);
    }
    FUN_710392e590(param_1);
}

// 0x71027526c0 — binary tree recursive delete
void FUN_71027526c0(u64 *p)
{
    if (p) {
        FUN_71027526c0((u64 *)p[0]);
        FUN_71027526c0((u64 *)p[1]);
        FUN_710392e590(p);
    }
}

// 0x710275a640 — recursive tree delete + two copy-then-free fields
void FUN_710275a640(u64 *param_1)
{
    if (param_1) {
        FUN_710275a640((u64 *)param_1[0]);
        FUN_710275a640((u64 *)param_1[1]);
        u64 tmp8 = param_1[8];
        if (tmp8 != 0) {
            param_1[9] = tmp8;
            FUN_710392e590((void *)tmp8);
        }
        u64 tmp5 = param_1[5];
        if (tmp5 != 0) {
            param_1[6] = tmp5;
            FUN_710392e590((void *)tmp5);
        }
        FUN_710392e590(param_1);
    }
}

// 0x710275ac60 — D0 destructor, group 2 + copy-then-free at inner[0]/inner[1]
void FUN_710275ac60(u64 *param_1)
{
    u64 *plVar1 = (u64 *)param_1[1];
    param_1[0] = (u64)&DAT_71050dacb8;
    param_1[1] = 0;
    if (plVar1 != nullptr) {
        u64 tmp = plVar1[0];
        if (tmp != 0) {
            plVar1[1] = tmp;
            FUN_710392e590((void *)tmp);
        }
        FUN_710392e590(plVar1);
    }
    FUN_710392e590(param_1);
}

// 0x710275b4c0 — binary tree recursive delete
void FUN_710275b4c0(u64 *p)
{
    if (p) {
        FUN_710275b4c0((u64 *)p[0]);
        FUN_710275b4c0((u64 *)p[1]);
        FUN_710392e590(p);
    }
}

// 0x710275d810 — binary tree recursive delete
void FUN_710275d810(u64 *p)
{
    if (p) {
        FUN_710275d810((u64 *)p[0]);
        FUN_710275d810((u64 *)p[1]);
        FUN_710392e590(p);
    }
}
