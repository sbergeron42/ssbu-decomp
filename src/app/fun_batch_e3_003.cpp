#include "types.h"

// MEDIUM-tier FUN_* functions — 0x7102 address range, batch e3-003
// Pool-e worker: sound dispatch, singleton guard init, vtable dispatch, throw_out_of_range wrappers

// ---- External declarations -----------------------------------------------

namespace std { namespace __1 {
    template<bool> struct __vector_base_common {
        [[noreturn]] static void __throw_out_of_range();
    };
}}

// Vtable dispatch helper
#define VT(m) (*reinterpret_cast<void***>(m))

// Sound module callee
extern void FUN_71006eadc0(u64);

// Singleton guard for FUN_71023ed1e0/250
extern u64 DAT_71053134d8;  // guard at 0x7105313000+0x4d8
extern u8  DAT_7105307343;  // init flag
extern s32 FUN_71039c0100(u64 *);  // __cxa_guard_acquire
extern void FUN_71039c0110(u64 *); // __cxa_guard_release
extern void FUN_71017641a0(void);
extern void FUN_71000001c0(void *, void *, void *);
extern u8  DAT_7101763de0;
extern u64 DAT_71052c4180;
extern u8  PTR_LOOP_7104f16000;

// ---- x9-register sound_module dispatch -----------------------------------

// 0x71020c6690 (192 bytes) — sound_module (acc+0x148), call FUN_71006eadc0(mod)
// Disasm: str x10,[x0,#0x10]; ldr x0,[x9,#0x148]; bl FUN_71006eadc0; mov w0,wzr; ldp; ret
u64 FUN_71020c6690(u64 param_1)
{
    register u8 *acc asm("x9");
    register u64 in_x10 asm("x10");
    asm volatile("" : "+r"(acc), "+r"(in_x10));
    *(u64 *)(param_1 + 0x10) = in_x10;
    FUN_71006eadc0(*(u64 *)(acc + 0x148));
    return 0;
}

// ---- Singleton guard init ------------------------------------------------
// Pattern: ldarb guard_byte; if non-zero, skip; __cxa_guard_acquire; init; __cxa_guard_release

// 0x71023ed1e0 (112 bytes) — init DAT_7105307343 = 1
// Disasm: adrp+ldr(guard)→ ldarb; cbnz skip; bl __cxa_guard_acquire; cbz skip;
//         bl FUN_71017641a0; adrp+add(DAT_7101763de0); adrp+add(DAT_71052c4180);
//         adrp+add(PTR_LOOP_7104f16000); bl FUN_71000001c0;
//         adrp+ldr(guard); bl __cxa_guard_release;
//         adrp+ldr(DAT_7105307343); mov w8,#1; strb w8,[x8]; ret
void FUN_71023ed1e0(void)
{
    u8 guard_byte;
    __atomic_load(&((u8 *)&DAT_71053134d8)[0], &guard_byte, __ATOMIC_ACQUIRE);
    if (guard_byte == 0) {
        if (FUN_71039c0100(&DAT_71053134d8) != 0) {
            FUN_71017641a0();
            FUN_71000001c0(&DAT_7101763de0, &DAT_71052c4180, &PTR_LOOP_7104f16000);
            FUN_71039c0110(&DAT_71053134d8);
        }
    }
    DAT_7105307343 = 1;
}

// 0x71023ed250 (112 bytes) — init DAT_7105307343 = 0
// Same pattern as above but stores 0 instead of 1
void FUN_71023ed250(void)
{
    u8 guard_byte;
    __atomic_load(&((u8 *)&DAT_71053134d8)[0], &guard_byte, __ATOMIC_ACQUIRE);
    if (guard_byte == 0) {
        if (FUN_71039c0100(&DAT_71053134d8) != 0) {
            FUN_71017641a0();
            FUN_71000001c0(&DAT_7101763de0, &DAT_71052c4180, &PTR_LOOP_7104f16000);
            FUN_71039c0110(&DAT_71053134d8);
        }
    }
    DAT_7105307343 = 0;
}

// ---- Vtable dispatch + conditional store ---------------------------------

// 0x7102931ae0 (112 bytes) — vtable[0x30/8]() → if result bit0 clear, store param_2 at +0x15d8
// Disasm: stp x20,x19,[sp,#-0x20]!; stp x29,x30,[sp,#0x10]; add x29,sp,#0x10
//         ldr x8,[x0]; ldr x8,[x8,#0x30]; mov w19,w1; mov x20,x0; blr x8
//         tbnz w0,#0x0,skip; str w19,[x20,#0x15d8]
//         skip: ldp x29,x30,[sp,#0x10]; ldp x20,x19,[sp,#0x20]; ldp; ret
void FUN_7102931ae0(u64 *param_1, u32 param_2)
{
    u32 r = reinterpret_cast<u32 (*)(u64 *)>(VT(param_1)[0x30 / 8])(param_1);
    if ((r & 1) == 0) {
        *(u32 *)((u8 *)param_1 + 0x15d8) = param_2;
    }
}

// ---- std::__throw_out_of_range wrappers ----------------------------------

// 0x710257eb3c (96 bytes)
void FUN_710257eb3c(void) {
    std::__1::__vector_base_common<true>::__throw_out_of_range();
}

// 0x7102ce204c (96 bytes)
void FUN_7102ce204c(void) {
    std::__1::__vector_base_common<true>::__throw_out_of_range();
}

// 0x7102898d6c (96 bytes)
void FUN_7102898d6c(void) {
    std::__1::__vector_base_common<true>::__throw_out_of_range();
}

// 0x7102898efc (96 bytes)
void FUN_7102898efc(void) {
    std::__1::__vector_base_common<true>::__throw_out_of_range();
}

// 0x71027cea9c (96 bytes)
void FUN_71027cea9c(void) {
    std::__1::__vector_base_common<true>::__throw_out_of_range();
}

// 0x710293a80c (96 bytes)
void FUN_710293a80c(void) {
    std::__1::__vector_base_common<true>::__throw_out_of_range();
}

// 0x7102cbf3cc (96 bytes)
void FUN_7102cbf3cc(void) {
    std::__1::__vector_base_common<true>::__throw_out_of_range();
}

// 0x7102c7aa8c (96 bytes)
void FUN_7102c7aa8c(void) {
    std::__1::__vector_base_common<true>::__throw_out_of_range();
}

// 0x7102df744c (96 bytes)
void FUN_7102df744c(void) {
    std::__1::__vector_base_common<true>::__throw_out_of_range();
}

// 0x710287787c (96 bytes)
void FUN_710287787c(void) {
    std::__1::__vector_base_common<true>::__throw_out_of_range();
}

// 0x7102f408ec (96 bytes)
void FUN_7102f408ec(void) {
    std::__1::__vector_base_common<true>::__throw_out_of_range();
}
