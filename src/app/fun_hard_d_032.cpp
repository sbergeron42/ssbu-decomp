#include "types.h"

// HARD-tier FUN_* functions — batch hard-d-032
// Pool-d worker: vtable dispatch, state machine, more -O2 targets

#define HIDDEN __attribute__((visibility("hidden")))

// ---- External functions ----

extern "C" void FUN_7100dbaf50(u64, s64);
extern "C" void FUN_7100048dd0(s64);    // AnimTransform sub-object cleanup
extern "C" void FUN_710007a0e0(s64, u32);  // Map sub-object dispatch
extern "C" s64* FUN_7100048db0(u64);    // allocator (returns node)
extern "C" void FUN_7100040e20(void);   // AnimatorEx parent ctor

// ---- External data ----

extern "C" u8* DAT_71052a3480 HIDDEN;  // [derived: Ghidra — AnimTransformBasic vtable base pointer]
extern "C" u8* DAT_71052a36d0 HIDDEN;  // [derived: Ghidra — AnimatorEx vtable base pointer]

// ════════════════════════════════════════════════════════════════════
// 0x710114c140 — vtable dispatch + tail-call (80 bytes, -O2)
// [derived: Ghidra decompilation — reads sub-module at +0x20 → +0x98,
//  calls vtable[0x37] with (obj, 0x12, 0), then tail-calls
//  FUN_7100dbaf50 with original params.
//  Chain: param_2+0x20 → WorkModule ptr → +0x98 → module sub-object]
// ════════════════════════════════════════════════════════════════════
extern "C"
void FUN_710114c140(u64 param_1, s64 param_2) {
    // +0x20 [inferred: sub-struct pointer in battle_object]
    // → +0x98 [inferred: sub-module, has vtable with method at slot 0x37]
    s64* obj = *(s64**)(*(s64*)(param_2 + 0x20) + 0x98);
    // vtable[0x37] = offset 0x1b8 [inferred: set_mode(mode_id, flag)]
    ((void(*)(s64*, s32, s32))(*(s64**)obj)[0x1b8 / 8])(obj, 0x12, 0);
    FUN_7100dbaf50(param_1, param_2);
}

// ════════════════════════════════════════════════════════════════════
// 0x71030f6950 — state machine dispatch (176 bytes, -O2)
// [derived: Ghidra decompilation — reads state byte at this+0x4891,
//  dispatches to vtable method based on state (4→slot 0x1F, 5→0x20, 6→0x21),
//  stores result code at +0x489c, clears state.
//  Second stage: if +0x489d == 4, copies +0x489c into +0x489d]
// ════════════════════════════════════════════════════════════════════
extern "C"
void FUN_71030f6950(s64* param_1) {
    u8* base = (u8*)param_1;
    u8 state = base[0x4891];  // +0x4891 [inferred: pending state transition command]
    u8 result;

    if (state == 4) {
        // vtable[0x1F] = offset 0xf8 [inferred: transition_to_phase_1()]
        ((void(*)(s64*))(*(s64**)param_1)[0xf8 / 8])(param_1);
        result = 1;
    } else if (state == 5) {
        // vtable[0x20] = offset 0x100 [inferred: transition_to_phase_2()]
        ((void(*)(s64*))(*(s64**)param_1)[0x100 / 8])(param_1);
        result = 2;
    } else if (state == 6) {
        // vtable[0x21] = offset 0x108 [inferred: transition_to_phase_3()]
        ((void(*)(s64*))(*(s64**)param_1)[0x108 / 8])(param_1);
        result = 3;
    } else {
        goto check_final;
    }

    base[0x489c] = result;  // +0x489c [inferred: current phase index]
    base[0x4891] = 0;       // clear pending command

check_final:
    // +0x489d [inferred: target phase — if still "wants phase 4", propagate current]
    if (base[0x489d] == 4) {
        base[0x489d] = base[0x489c];
    }
}

// ════════════════════════════════════════════════════════════════════
// 0x710003e2b0 — ~AnimTransformBasic destructor (76 bytes, -O2)
// [derived: Ghidra decompilation — sets vtable from global base + 0x10,
//  cleans two sub-objects at +0x30 and +0x28 via FUN_7100048dd0.
//  Second cleanup is tail-call.]
// ════════════════════════════════════════════════════════════════════
extern "C"
void FUN_710003e2b0(s64* param_1) {
    // Reset vtable: DAT_71052a3480 holds base, add 0x10
    // [derived: Ghidra — PTR_DAT_71052a3480 is typeinfo/vtable base for AnimTransformBasic]
    *param_1 = (s64)(DAT_71052a3480 + 0x10);
    if (param_1[6] != 0) {  // +0x30 [inferred: child animation resource]
        FUN_7100048dd0(param_1[6]);
    }
    if (param_1[5] != 0) {  // +0x28 [inferred: parent animation resource]
        FUN_7100048dd0(param_1[5]);  // tail-call
    }
}

// ════════════════════════════════════════════════════════════════════
// 0x7100044cb0 — Map: dispatch to two optional sub-objects (72 bytes, -O2)
// [derived: Ghidra decompilation — calls FUN_710007a0e0 on sub-objects
//  at +0xC8 and +0xD0 if non-null. Second call is tail-call.]
// ════════════════════════════════════════════════════════════════════
extern "C"
void FUN_7100044cb0(s64 param_1, u32 param_2) {
    if (*(s64*)(param_1 + 0xC8) != 0) {  // +0xC8 [inferred: primary child view]
        FUN_710007a0e0(*(s64*)(param_1 + 0xC8), param_2);
    }
    if (*(s64*)(param_1 + 0xD0) != 0) {  // +0xD0 [inferred: secondary child view]
        FUN_710007a0e0(*(s64*)(param_1 + 0xD0), param_2);  // tail-call
    }
}

// ════════════════════════════════════════════════════════════════════
// 0x7100047990 — AppendPane: allocate node and insert into circular list (72 bytes, -O2)
// [derived: Ghidra decompilation — allocates 0x18-byte node via FUN_7100048db0,
//  initializes as self-linked, stores data param, inserts at head of list
//  rooted at param_1+0x18. Standard doubly-linked list insert.]
// ════════════════════════════════════════════════════════════════════
extern "C"
void FUN_7100047990(s64 param_1, s64 param_2) {
    s64* node = FUN_7100048db0(0x18);
    if (node != nullptr) {
        // Init as self-linked circular node
        node[0] = (s64)node;  // prev = self
        node[1] = (s64)node;  // next = self
        node[2] = param_2;    // data payload

        // Insert at head of circular list at param_1+0x18
        s64* head = (s64*)(param_1 + 0x18);
        node[0] = *head;           // node->prev = old first
        node[1] = (s64)head;       // node->next = sentinel
        *(s64*)(*head + 8) = (s64)node;  // old_first->back = node
        *head = (s64)node;         // head = node
    }
}

// ════════════════════════════════════════════════════════════════════
// 0x7100050020 — AnimatorEx constructor (64 bytes, -O2)
// [derived: Ghidra decompilation — calls parent ctor FUN_7100040e20,
//  initializes self-linked list node at +0x48, zeros fields,
//  sets vtable from global base + 0x10]
// ════════════════════════════════════════════════════════════════════
extern "C"
void FUN_7100050020(s64* param_1) {
    FUN_7100040e20();  // parent ctor (no params visible)

    // Init self-linked circular list at +0x48
    // +0x48 [inferred: pane list head, circular self-ref]
    param_1[9] = (s64)(param_1 + 9);   // +0x48 → self
    param_1[10] = (s64)(param_1 + 9);  // +0x50 → self

    // Zero fields
    param_1[11] = 0;  // +0x58
    param_1[12] = 0;  // +0x60

    // Set vtable: DAT_71052a36d0 holds base, add 0x10
    *param_1 = (s64)(DAT_71052a36d0 + 0x10);

    // Zero trailing field
    *(u32*)(param_1 + 13) = 0;  // +0x68
}
