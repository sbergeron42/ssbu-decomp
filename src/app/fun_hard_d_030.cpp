#include "types.h"

// HARD-tier FUN_* functions — batch hard-d-030
// Pool-d worker: effect cleanup, destructors, jemalloc check
// All -O2

#define HIDDEN __attribute__((visibility("hidden")))

// ---- Singleton template (matches sv_animcmd_effect.cpp pattern) ----
namespace lib {
    template<typename T> struct Singleton { static T* instance_; };
    struct EffectManager;
}
extern template lib::EffectManager* lib::Singleton<lib::EffectManager>::instance_;

// ---- External functions ----

extern "C" void  FUN_71037759f0(u64);
extern "C" s32   FUN_710330a4a0(u64, void*);
extern "C" void  FUN_7103563720(u64, s32);
extern "C" void  FUN_71032e5640(u64);
extern "C" void  FUN_710392e590(void*);   // je_free
extern "C" void  FUN_7103607270(void*);   // sub-object cleanup
extern "C" void  FUN_71039c2140(void*);   // shared_weak_count destructor
extern "C" void  FUN_7103956fa0(s32, const char*);  // jemalloc message output

// ---- External data ----

extern "C" u64   DAT_710532e8b8 HIDDEN;  // [inferred: global manager pointer, +0x8 = sub-object]
extern "C" u64   DAT_710532e7c8 HIDDEN;
extern "C" u8    DAT_7104544980 HIDDEN;  // [derived: hash40 constant for effect lookup]
extern "C" u8    DAT_7106dd3f1d HIDDEN;  // [derived: jemalloc background_thread enabled flag]

// vtable pointers for destructors
extern "C" u8 PTR_LAB_71050655e0[] HIDDEN;  // [derived: Ghidra vtable for FUN_7101b799b0 target]
extern "C" u8 PTR_FUN_7105232ae8[] HIDDEN;  // [derived: Ghidra vtable for FUN_7103600360 target]
extern "C" u8 PTR_FUN_7105232cf8[] HIDDEN;  // [derived: Ghidra vtable for FUN_7103609340 target]

// ════════════════════════════════════════════════════════════════════
// 0x7101958da0 — effect cleanup: dereference module accessor chain,
//   call FUN_71037759f0, lookup effect by hash, remove from EffectManager,
//   tail-call FUN_71032e5640 (sound queue stop)
// Size: 96 bytes
// [derived: Ghidra decompilation — chain is +0x58 → +0x180 → +0x80 → +0x50 → deref.
//  DAT_710532e8b8+8 = effect database sub-object.
//  DAT_7104544980 = hash40 constant for effect identifier.
//  lib::Singleton<lib::EffectManager>::instance_ loaded for remove call.]
// ════════════════════════════════════════════════════════════════════
extern "C"
void FUN_7101958da0(s64 param_1) {
    // Chain through module accessor to get effect handle
    // +0x58 [inferred: sub-module pointer]
    // → +0x180 [inferred: effect data container]
    // → +0x80 [inferred: effect list/array]
    // → +0x50 [inferred: effect slot pointer]
    // → deref [inferred: effect handle value]
    u64 val = **(u64**)(*(s64*)(*(s64*)(*(s64*)(param_1 + 0x58) + 0x180) + 0x80) + 0x50);
    FUN_71037759f0(val);

    // Look up effect by hash in database
    s32 result = FUN_710330a4a0(*(u64*)(DAT_710532e8b8 + 8), &DAT_7104544980);
    if (result != 0) {
        // Remove from EffectManager
        FUN_7103563720(*(u64*)lib::Singleton<lib::EffectManager>::instance_, result);
    }

    // Tail-call: stop sound queue
    FUN_71032e5640(DAT_710532e7c8);
}

// ════════════════════════════════════════════════════════════════════
// 0x710195f150 — effect cleanup: same as FUN_7101958da0 but offset +0x170
// Size: 96 bytes
// [derived: Ghidra decompilation — identical structure, +0x170 instead of +0x180
//  in the accessor chain. Different sub-module slot in the same container.]
// ════════════════════════════════════════════════════════════════════
extern "C"
void FUN_710195f150(s64 param_1) {
    u64 val = **(u64**)(*(s64*)(*(s64*)(*(s64*)(param_1 + 0x58) + 0x170) + 0x80) + 0x50);
    FUN_71037759f0(val);

    s32 result = FUN_710330a4a0(*(u64*)(DAT_710532e8b8 + 8), &DAT_7104544980);
    if (result != 0) {
        FUN_7103563720(*(u64*)lib::Singleton<lib::EffectManager>::instance_, result);
    }

    FUN_71032e5640(DAT_710532e7c8);
}

// ════════════════════════════════════════════════════════════════════
// 0x7101b799b0 — destructor: reset vtable, cleanup sub-objects, free self
// Size: 80 bytes
// [derived: Ghidra decompilation — sets vtable to PTR_LAB_71050655e0,
//  nulls field +0x8, cleans inner object if present, tail-calls je_free]
// ════════════════════════════════════════════════════════════════════
extern "C"
void FUN_7101b799b0(u64* param_1) {
    s64 sub = (s64)param_1[1];   // +0x8 [inferred: sub-object pointer]
    param_1[0] = (u64)PTR_LAB_71050655e0;  // reset vtable
    param_1[1] = 0;                         // null sub-object
    if (sub != 0) {
        s64 inner = *(s64*)(sub + 8);  // sub+0x8 [inferred: inner resource]
        if (inner != 0) {
            *(s64*)(sub + 0x10) = inner;  // sub+0x10 [inferred: cleanup target]
            FUN_710392e590((void*)inner);
        }
        FUN_710392e590((void*)sub);
    }
    FUN_710392e590(param_1);  // free self (tail-call)
}

// ════════════════════════════════════════════════════════════════════
// 0x7103600360 — destructor: reset vtable, cleanup via FUN_7103607270, free
// Size: 80 bytes
// [derived: Ghidra decompilation — __shared_weak_count destructor pattern.
//  Sets vtable to PTR_FUN_7105232ae8, nulls field +0x18, cleans sub-object
//  if present, tail-calls FUN_71039c2140 (__shared_weak_count::~)]
// ════════════════════════════════════════════════════════════════════
extern "C"
void FUN_7103600360(s64* param_1) {
    s64 sub = *(s64*)((u8*)param_1 + 0x18);  // +0x18 [inferred: owned resource]
    *(u8**)param_1 = PTR_FUN_7105232ae8;     // reset vtable
    *(s64*)((u8*)param_1 + 0x18) = 0;        // null resource
    if (sub != 0) {
        FUN_7103607270((void*)sub);
        FUN_710392e590((void*)sub);
    }
    FUN_71039c2140(param_1);  // tail-call parent destructor
}

// ════════════════════════════════════════════════════════════════════
// 0x7103609340 — destructor: same pattern as FUN_7103600360, different vtable
// Size: 80 bytes
// [derived: Ghidra decompilation — identical structure, vtable = PTR_FUN_7105232cf8]
// ════════════════════════════════════════════════════════════════════
extern "C"
void FUN_7103609340(s64* param_1) {
    s64 sub = *(s64*)((u8*)param_1 + 0x18);
    *(u8**)param_1 = PTR_FUN_7105232cf8;
    *(s64*)((u8*)param_1 + 0x18) = 0;
    if (sub != 0) {
        FUN_7103607270((void*)sub);
        FUN_710392e590((void*)sub);
    }
    FUN_71039c2140(param_1);
}

// ════════════════════════════════════════════════════════════════════
// 0x7103946160 — jemalloc: check background_thread support
// Size: 80 bytes
// [derived: Ghidra decompilation — checks DAT_7106dd3f1d == 1,
//  if true prints warning about pthread requirement, returns bool]
// ════════════════════════════════════════════════════════════════════
extern "C"
bool FUN_7103946160(void) {
    bool enabled = (DAT_7106dd3f1d == 1);
    if (enabled) {
        FUN_7103956fa0(0, "<jemalloc>: option background_thread currently supports pthread only\n");
    }
    return enabled;
}
