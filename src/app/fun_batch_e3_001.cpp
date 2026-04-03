#include "types.h"

// MEDIUM-tier FUN_* functions — 0x7102 address range, batch e3-001
// Pool-e worker: abort wrappers, singleton dispatchers, x9-register module dispatch

// ---- External declarations -----------------------------------------------

// abort() is [[noreturn]]; call wrappers omit epilogue so pattern = stp+mov+bl (12 bytes)
[[noreturn]] extern "C" void abort();

// Singleton global pointers
// lib::Singleton<app::StageManager>::instance_ at 0x7105329000+0x9d8
extern u64 DAT_71053299d8;
// lib::Singleton<app::ItemManager>::instance_ at 0x71052c3000+0x70
extern u64 DAT_71052c3070;

// External callees
extern void FUN_71015ba050(u64, u64);
extern void FUN_71034bcc80(u64, u32, u32);
extern void FUN_7102608770(u64);

// Vtable dispatch helper: *(void***)(obj)[slot]
#define VT(m) (*reinterpret_cast<void***>(m))

// ---- Abort wrappers (0x7102a66xxx / 0x71028595b4 / 0x7102853f6c) ---------
// Pattern: stp+mov+bl abort  (3 insns, no epilogue, caller never returns)

// 0x7102a66198
void FUN_7102a66198(void) { abort(); }

// 0x7102a661d8
void FUN_7102a661d8(void) { abort(); }

// 0x7102a66208
void FUN_7102a66208(void) { abort(); }

// 0x7102a66238
void FUN_7102a66238(void) { abort(); }

// 0x7102a66268
void FUN_7102a66268(void) { abort(); }

// 0x7102a66298
void FUN_7102a66298(void) { abort(); }

// 0x7102a662c8
void FUN_7102a662c8(void) { abort(); }

// 0x7102a666f8
void FUN_7102a666f8(void) { abort(); }

// 0x7102a66768
void FUN_7102a66768(void) { abort(); }

// 0x7102a667c8
void FUN_7102a667c8(void) { abort(); }

// 0x7102a66828
void FUN_7102a66828(void) { abort(); }

// 0x71028595b4
void FUN_71028595b4(void) { abort(); }

// 0x7102853f6c
void FUN_7102853f6c(void) { abort(); }

// ---- StageManager singleton dispatch (no params) --------------------------
// Global DAT_71053299d8 = StageManager** (double-indirect).
// Pattern:
//   SM = *(u64*)DAT_71053299d8     (= StageManager*)
//   sub = SM + 0x128               (embedded sub-object)
//   call sub->vtable[0x228/8](sub, arg, 0)

// 0x710225ac40 — call sub.vtable[0x228/8](sub, 0x2f, 0)
u64 FUN_710225ac40(void)
{
    u8 *SM = (u8 *)*(u64 *)DAT_71053299d8;
    void *sub = SM + 0x128;
    reinterpret_cast<void (*)(void *, u32, u32)>(VT(sub)[0x228 / 8])(sub, 0x2f, 0);
    return 0;
}

// 0x710225ac80 — call sub.vtable[0x228/8](sub, 0x30, 0)
u64 FUN_710225ac80(void)
{
    u8 *SM = (u8 *)*(u64 *)DAT_71053299d8;
    void *sub = SM + 0x128;
    reinterpret_cast<void (*)(void *, u32, u32)>(VT(sub)[0x228 / 8])(sub, 0x30, 0);
    return 0;
}

// 0x710225acc0 — call sub.vtable[0x228/8](sub, 0x31, 0)
u64 FUN_710225acc0(void)
{
    u8 *SM = (u8 *)*(u64 *)DAT_71053299d8;
    void *sub = SM + 0x128;
    reinterpret_cast<void (*)(void *, u32, u32)>(VT(sub)[0x228 / 8])(sub, 0x31, 0);
    return 0;
}

// 0x710225b1c0 — load StageManager*, call FUN_7102608770(SM)
// Disasm: adrp+ldr(global) → ldr x0,[x8] → bl FUN_7102608770 → return 0
u64 FUN_710225b1c0(void)
{
    u64 SM = *(u64 *)DAT_71053299d8;
    FUN_7102608770(SM);
    return 0;
}

// ---- x9-register module dispatch -----------------------------------------
// x9 = BattleObjectModuleAccessor* (implicit register param from caller)
// x10 = value to store at param_1+0x10 (continuation slot)
// These wrappers load a module from the accessor and call its vtable method.

// 0x7102250050 — link_module (acc+0xd0), vtable[0x3b0/8](mod, 0, 0) → return 0
// Disasm: str x10,[x0,#0x10]; ldr x0,[x9,#0xd0]; ldr x8,[x0]; ldr x8,[x8,#0x3b0];
//         mov x1,xzr; mov x2,xzr; blr x8; mov w0,wzr
u64 FUN_7102250050(u64 param_1)
{
    register u8 *acc asm("x9");
    register u64 in_x10 asm("x10");
    asm volatile("" : "+r"(acc), "+r"(in_x10));
    *(u64 *)(param_1 + 0x10) = in_x10;
    void *mod = *(void **)(acc + 0xd0);
    reinterpret_cast<void (*)(void *, u64, u64)>(VT(mod)[0x3b0 / 8])(mod, 0, 0);
    return 0;
}

// 0x710226f314 — ground_module (acc+0x58), vtable[0x178/8](mod) → return 0
// Disasm: str x10,[x0,#0x10]; ldr x0,[x9,#0x58]; ldr x8,[x0]; ldr x8,[x8,#0x178]; blr x8
u64 FUN_710226f314(u64 param_1)
{
    register u8 *acc asm("x9");
    register u64 in_x10 asm("x10");
    asm volatile("" : "+r"(acc), "+r"(in_x10));
    *(u64 *)(param_1 + 0x10) = in_x10;
    void *mod = *(void **)(acc + 0x58);
    reinterpret_cast<void (*)(void *)>(VT(mod)[0x178 / 8])(mod);
    return 0;
}

// 0x710217b524 — work_module (acc+0x50), vtable[0x130/8](mod, param_2, 0x200000e2) → return 0
// Disasm: str x10,[x0,#0x10]; ldr x0,[x9,#0x50]; ldr x8,[x0]; ldr x8,[x8,#0x130];
//         mov w2,#0xe2; movk w2,#0x2000,LSL#16; blr x8; mov w0,wzr
u64 FUN_710217b524(u64 param_1, u64 param_2)
{
    register u8 *acc asm("x9");
    register u64 in_x10 asm("x10");
    asm volatile("" : "+r"(acc), "+r"(in_x10));
    *(u64 *)(param_1 + 0x10) = in_x10;
    void *mod = *(void **)(acc + 0x50);
    reinterpret_cast<void (*)(void *, u64, u32)>(VT(mod)[0x130 / 8])(mod, param_2, 0x200000e2);
    return 0;
}

// 0x71020ad4e0 — double-deref: *(*(acc+0x10)+0x8), vtable[0xa0/8](mod) → return 0
// Disasm: str x10,[x0,#0x10]; ldr x8,[x9,#0x10]; ldr x0,[x8,#0x8]; ldr x8,[x0]; ldr x8,[x8,#0xa0]; blr x8
// Note: NX Clang epilogue scheduling: ldp before mov w0,wzr
u64 FUN_71020ad4e0(u64 param_1)
{
    register u8 *acc asm("x9");
    register u64 in_x10 asm("x10");
    asm volatile("" : "+r"(acc), "+r"(in_x10));
    *(u64 *)(param_1 + 0x10) = in_x10;
    u8 *inner = (u8 *)*(u64 *)(acc + 0x10);
    void *mod = *(void **)(inner + 0x8);
    reinterpret_cast<void (*)(void *)>(VT(mod)[0xa0 / 8])(mod);
    return 0;
}

// 0x710216af30 — work_module (acc+0x50), vtable[0xb0/8](mod, 0x100000c0), then FUN_71034bcc80(result, 0, 0)
// Disasm: str x10,[x0,#0x10]; ldr x0,[x9,#0x50]; ldr x8,[x0]; ldr x8,[x8,#0xb0];
//         mov w1,#0xc0; movk w1,#0x1000,LSL#16; blr x8;
//         mov w1,wzr; mov w2,wzr; bl FUN_71034bcc80; mov w0,wzr
u64 FUN_710216af30(u64 param_1)
{
    register u8 *acc asm("x9");
    register u64 in_x10 asm("x10");
    asm volatile("" : "+r"(acc), "+r"(in_x10));
    *(u64 *)(param_1 + 0x10) = in_x10;
    void *mod = *(void **)(acc + 0x50);
    u64 result = reinterpret_cast<u64 (*)(void *, u32)>(VT(mod)[0xb0 / 8])(mod, 0x100000c0);
    FUN_71034bcc80(result, 0, 0);
    return 0;
}

// ---- ItemManager singleton dispatch ---------------------------------------
// 0x710220c248 — load param chain, load ItemManager member, call FUN_71015ba050
// Disasm: ldur x8,[x0,#-8]; str x9,[x0,#0x10]; ldr x8,[x8,#0x1a0]; ldr x8,[x8,#0x190];
//         ldr x1,[x8,#0x220]; adrp+ldr(DAT_71052c3070) → ldr x0,[x8,#0xa8]; bl FUN_71015ba050
u64 FUN_710220c248(u64 param_1)
{
    register u64 in_x9 asm("x9");
    asm volatile("" : "+r"(in_x9));
    u64 base = *(u64 *)(param_1 - 8);
    *(u64 *)(param_1 + 0x10) = in_x9;
    u64 x8 = *(u64 *)(base + 0x1a0);
    x8 = *(u64 *)(x8 + 0x190);
    u64 x1 = *(u64 *)(x8 + 0x220);
    u64 x0 = *(u64 *)(DAT_71052c3070 + 0xa8);
    FUN_71015ba050(x0, x1);
    return 0;
}
