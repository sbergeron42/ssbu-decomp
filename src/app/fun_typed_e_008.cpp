// pool-e: UI/CSS destructors, tree/list cleanup, mutex-locked clear
// 20 HARD-tier functions from the CSS/UI address range (0x71017xxxxx)
//
// Pattern: mostly D1/D0 destructor pairs for CSS scene classes,
// plus a mutex-locked list clear and recursive tree deletion.

#include "types.h"

// ---- External function declarations ----------------------------------------

extern "C" {
    void FUN_71001af8a0(void *p);       // operator delete
    void FUN_71001b4910(void *p);       // DeleteContent (container base dtor)
    void FUN_71001b1870(void *p);       // Free
    void FUN_71001d76e0(void *p);       // vector/container destructor
    void FUN_7101711810(void *p, void *root); // tree recursive destroy
    void FUN_7101713160(void *p, void *root); // tree recursive destroy variant
    void FUN_7101756f80(void *p);       // UI object cleanup
    void FUN_710392e590(void *p);       // free_default
    void FUN_71022b6f60(void *p);       // global resource release
    void FUN_71017e2ab0(void *p);       // linked list node recursive free
    void lock_71039c1410(void *p);      // mutex lock
    void unlock_71039c1420(void *p);    // mutex unlock
}

// ---- Vtable / RODATA symbols -----------------------------------------------
#define DAT_HIDDEN __attribute__((visibility("hidden")))

// Per-class vtables
extern "C" DAT_HIDDEN u64 DAT_710509c190;  // Class A
extern "C" DAT_HIDDEN u64 DAT_710509c210;  // Class C
extern "C" DAT_HIDDEN u64 DAT_710509c230;  // Class B
extern "C" DAT_HIDDEN u64 DAT_710509c2e8;  // Class D
extern "C" DAT_HIDDEN u64 DAT_710509c3e8;  // Class E
extern "C" DAT_HIDDEN u64 DAT_710509c638;  // Class F
extern "C" DAT_HIDDEN u64 DAT_710509c818;  // Class G
extern "C" DAT_HIDDEN u64 DAT_710509cc80;  // Class H
extern "C" DAT_HIDDEN u64 DAT_710509bc08;  // Dead/base vtable (shared sentinel)
extern "C" DAT_HIDDEN u64 DAT_710509da18;  // Class I vtable (multi-inh base)
extern "C" DAT_HIDDEN u64 DAT_7105326cd0;  // Global pointer (tree deletion)

// ===========================================================================
// Class A (vtable 710509c190): D1 + D0
// Members: +0x10 content, +0x38 content, +0x60 tree(root@+0x68), +0x80 content
// ===========================================================================

// 0x71017118d0  88B — D1 (complete object destructor)
void FUN_71017118d0(u64 *param_1)
{
    param_1[0] = (u64)&DAT_710509c190;
    param_1[0x10] = (u64)&DAT_710509bc08;
    FUN_71001b4910(&param_1[0x10]);
    FUN_7101711810(&param_1[0xc], (void *)param_1[0xd]);
    param_1[7] = (u64)&DAT_710509bc08;
    FUN_71001b4910(&param_1[7]);
    param_1[2] = (u64)&DAT_710509bc08;
    FUN_71001b4910(&param_1[2]);
}

// 0x7101711930  96B — D0 (deleting destructor)
void FUN_7101711930(u64 *param_1)
{
    param_1[0] = (u64)&DAT_710509c190;
    param_1[0x10] = (u64)&DAT_710509bc08;
    FUN_71001b4910(&param_1[0x10]);
    FUN_7101711810(&param_1[0xc], (void *)param_1[0xd]);
    param_1[7] = (u64)&DAT_710509bc08;
    FUN_71001b4910(&param_1[7]);
    param_1[2] = (u64)&DAT_710509bc08;
    FUN_71001b4910(&param_1[2]);
    FUN_71001af8a0(param_1);
}

// ===========================================================================
// Class B (vtable 710509c230): D1 + D0
// Members: +0x20 content, +0x48 content, +0x70 content
// ===========================================================================

// 0x7101711b30  80B — D1
void FUN_7101711b30(u64 *param_1)
{
    param_1[0] = (u64)&DAT_710509c230;
    param_1[0xe] = (u64)&DAT_710509bc08;
    FUN_71001b4910(&param_1[0xe]);
    param_1[9] = (u64)&DAT_710509bc08;
    FUN_71001b4910(&param_1[9]);
    param_1[4] = (u64)&DAT_710509bc08;
    FUN_71001b4910(&param_1[4]);
}

// 0x7101711b80  96B — D0
void FUN_7101711b80(u64 *param_1)
{
    param_1[0] = (u64)&DAT_710509c230;
    param_1[0xe] = (u64)&DAT_710509bc08;
    FUN_71001b4910(&param_1[0xe]);
    param_1[9] = (u64)&DAT_710509bc08;
    FUN_71001b4910(&param_1[9]);
    param_1[4] = (u64)&DAT_710509bc08;
    FUN_71001b4910(&param_1[4]);
    FUN_71001af8a0(param_1);
}

// ===========================================================================
// Class C (vtable 710509c210): D1 + D0 + D0 variant
// Members: +0x10 content, +0x38 content, +0x68 tree(root@+0x70)
// ===========================================================================

// 0x7101711be0  80B — D1
void FUN_7101711be0(u64 *param_1)
{
    param_1[0] = (u64)&DAT_710509c210;
    FUN_7101711810(&param_1[0xd], (void *)param_1[0xe]);
    param_1[7] = (u64)&DAT_710509bc08;
    FUN_71001b4910(&param_1[7]);
    param_1[2] = (u64)&DAT_710509bc08;
    FUN_71001b4910(&param_1[2]);
}

// 0x7101711c30  96B — D0
void FUN_7101711c30(u64 *param_1)
{
    param_1[0] = (u64)&DAT_710509c210;
    FUN_7101711810(&param_1[0xd], (void *)param_1[0xe]);
    param_1[7] = (u64)&DAT_710509bc08;
    FUN_71001b4910(&param_1[7]);
    param_1[2] = (u64)&DAT_710509bc08;
    FUN_71001b4910(&param_1[2]);
    FUN_71001af8a0(param_1);
}

// 0x7101711c90  96B — D0 variant (identical bytes to 7101711c30)
void FUN_7101711c90(u64 *param_1)
{
    param_1[0] = (u64)&DAT_710509c210;
    FUN_7101711810(&param_1[0xd], (void *)param_1[0xe]);
    param_1[7] = (u64)&DAT_710509bc08;
    FUN_71001b4910(&param_1[7]);
    param_1[2] = (u64)&DAT_710509bc08;
    FUN_71001b4910(&param_1[2]);
    FUN_71001af8a0(param_1);
}

// ===========================================================================
// Class D (vtable 710509c2e8): D1 + D0
// Members: +0x10 content, +0x38 content
// ===========================================================================

// 0x71017123a0  64B — D1
void FUN_71017123a0(u64 *param_1)
{
    param_1[0] = (u64)&DAT_710509c2e8;
    param_1[7] = (u64)&DAT_710509bc08;
    FUN_71001b4910(&param_1[7]);
    param_1[2] = (u64)&DAT_710509bc08;
    FUN_71001b4910(&param_1[2]);
}

// 0x71017123e0  80B — D0
void FUN_71017123e0(u64 *param_1)
{
    param_1[0] = (u64)&DAT_710509c2e8;
    param_1[7] = (u64)&DAT_710509bc08;
    FUN_71001b4910(&param_1[7]);
    param_1[2] = (u64)&DAT_710509bc08;
    FUN_71001b4910(&param_1[2]);
    FUN_71001af8a0(param_1);
}

// ===========================================================================
// Class E (vtable 710509c3e8): D1 + D0
// Members: +0x10 content, +0x38 content, +0x60 content, +0x88 content
// ===========================================================================

// 0x7101712e60  96B — D1
void FUN_7101712e60(u64 *param_1)
{
    param_1[0] = (u64)&DAT_710509c3e8;
    param_1[0x11] = (u64)&DAT_710509bc08;
    FUN_71001b4910(&param_1[0x11]);
    param_1[0xc] = (u64)&DAT_710509bc08;
    FUN_71001b4910(&param_1[0xc]);
    param_1[7] = (u64)&DAT_710509bc08;
    FUN_71001b4910(&param_1[7]);
    param_1[2] = (u64)&DAT_710509bc08;
    FUN_71001b4910(&param_1[2]);
}

// 0x7101712ec0  96B — D0
void FUN_7101712ec0(u64 *param_1)
{
    param_1[0] = (u64)&DAT_710509c3e8;
    param_1[0x11] = (u64)&DAT_710509bc08;
    FUN_71001b4910(&param_1[0x11]);
    param_1[0xc] = (u64)&DAT_710509bc08;
    FUN_71001b4910(&param_1[0xc]);
    param_1[7] = (u64)&DAT_710509bc08;
    FUN_71001b4910(&param_1[7]);
    param_1[2] = (u64)&DAT_710509bc08;
    FUN_71001b4910(&param_1[2]);
    FUN_71001af8a0(param_1);
}

// ===========================================================================
// Class F (vtable 710509c638): D1 + D0
// Members: +0x10 ptr (cond free), +0x50 content, +0x78 tree(root@+0x80)
// ===========================================================================

// 0x7101714740  96B — D1
void FUN_7101714740(u64 *param_1)
{
    param_1[0] = (u64)&DAT_710509c638;
    FUN_7101713160(&param_1[0xf], (void *)param_1[0x10]);
    param_1[0xa] = (u64)&DAT_710509bc08;
    FUN_71001b4910(&param_1[0xa]);
    if (param_1[2] != 0) {
        param_1[3] = param_1[2];
        FUN_71001b1870((void *)param_1[2]);
    }
}

// 0x71017147a0  96B — D0
void FUN_71017147a0(u64 *param_1)
{
    param_1[0] = (u64)&DAT_710509c638;
    FUN_7101713160(&param_1[0xf], (void *)param_1[0x10]);
    param_1[0xa] = (u64)&DAT_710509bc08;
    FUN_71001b4910(&param_1[0xa]);
    if (param_1[2] != 0) {
        param_1[3] = param_1[2];
        FUN_71001b1870((void *)param_1[2]);
    }
    FUN_71001af8a0(param_1);
}

// ===========================================================================
// Class G (vtable 710509c818): D1 + D0
// Members: +0x10 content, +0x38 content, +0x60 content
// ===========================================================================

// 0x7101717d40  80B — D1
void FUN_7101717d40(u64 *param_1)
{
    param_1[0] = (u64)&DAT_710509c818;
    param_1[0xc] = (u64)&DAT_710509bc08;
    FUN_71001b4910(&param_1[0xc]);
    param_1[7] = (u64)&DAT_710509bc08;
    FUN_71001b4910(&param_1[7]);
    param_1[2] = (u64)&DAT_710509bc08;
    FUN_71001b4910(&param_1[2]);
}

// 0x7101717d90  96B — D0
void FUN_7101717d90(u64 *param_1)
{
    param_1[0] = (u64)&DAT_710509c818;
    param_1[0xc] = (u64)&DAT_710509bc08;
    FUN_71001b4910(&param_1[0xc]);
    param_1[7] = (u64)&DAT_710509bc08;
    FUN_71001b4910(&param_1[7]);
    param_1[2] = (u64)&DAT_710509bc08;
    FUN_71001b4910(&param_1[2]);
    FUN_71001af8a0(param_1);
}

// ===========================================================================
// Class H (vtable 710509cc80): D1 + D0
// Members: +0x10 content, +0x38 vector, +0x70 vector, +0xa8 vector
// ===========================================================================

// 0x710171df30  96B — D1
void FUN_710171df30(u64 *param_1)
{
    param_1[0] = (u64)&DAT_710509cc80;
    FUN_71001d76e0(&param_1[0x15]);
    FUN_71001d76e0(&param_1[0xe]);
    FUN_71001d76e0(&param_1[7]);
    param_1[2] = (u64)&DAT_710509bc08;
    FUN_71001b4910(&param_1[2]);
}

// 0x710171df90  96B — D0
void FUN_710171df90(u64 *param_1)
{
    param_1[0] = (u64)&DAT_710509cc80;
    FUN_71001d76e0(&param_1[0x15]);
    FUN_71001d76e0(&param_1[0xe]);
    FUN_71001d76e0(&param_1[7]);
    param_1[2] = (u64)&DAT_710509bc08;
    FUN_71001b4910(&param_1[2]);
    FUN_71001af8a0(param_1);
}

// ===========================================================================
// Class I (multi-inheritance, 3 vtables): deleting destructor
// vtable0=710509da18, vtable1=+0x38, vtable2=+0x58
// Member: +0x18 ptr → cleanup via offset 0x600028
// ===========================================================================

// 0x7101758ba0  96B
void FUN_7101758ba0(u64 *param_1)
{
    u64 old = param_1[3];
    u64 base = (u64)&DAT_710509da18;
    param_1[0] = base;
    param_1[1] = base + 0x38;
    param_1[2] = base + 0x58;
    param_1[3] = 0;
    if (old != 0) {
        FUN_7101756f80(*(void **)((u8 *)old + 0x600028));
        FUN_710392e590((void *)old);
    }
    FUN_710392e590(param_1);
}

// ===========================================================================
// Mutex-locked list clear
// ===========================================================================

// 0x71017e2840  64B
void FUN_71017e2840(u64 *param_1)
{
    lock_71039c1410((void *)((u8 *)param_1 + 0x28));
    u64 head = param_1[2];
    *(u8 *)((u8 *)param_1 + 0x20) = 0;
    FUN_71017e2ab0((void *)head);
    param_1[2] = 0;
    param_1[3] = 0;
    param_1[1] = (u64)&param_1[2];
    unlock_71039c1420((void *)((u8 *)param_1 + 0x28));
}

// ===========================================================================
// Recursive binary tree node deletion
// ===========================================================================

// 0x71017e48e0  96B
void FUN_71017e48e0(u64 *param_1)
{
    if (param_1 == nullptr) return;
    FUN_71017e48e0((u64 *)param_1[0]);
    FUN_71017e48e0((u64 *)param_1[1]);
    if ((param_1[5] & 0xffffffffffULL) != 0) {
        FUN_71022b6f60(*(void **)DAT_7105326cd0);
    }
    FUN_710392e590(param_1);
}
