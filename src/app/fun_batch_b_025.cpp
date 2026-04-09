#include "types.h"
#include "app/BattleObjectModuleAccessor.h"
#include "app/modules/KineticModule.h"

// Batch decompiled via Ghidra MCP -- pool-b, batch 025
// Fighter core functions (0x71003 range) + sv_kinetic_energy readers (0x71022 range)

#define VT(m) (*reinterpret_cast<void***>(m))

// ______ External functions ________________________________________

extern "C" void FUN_710392e590(void*);        // operator delete / free
extern "C" void FUN_71003aeef0(void*, u32, u16); // BOM register
extern "C" void FUN_71003af040(void*, long);      // BOM unregister
extern "C" void FUN_71003a6460(void*, void*, u32, u32, u64); // article init
extern "C" void FUN_71003a6a30(void*, void*, u32, u32);       // article finalize
extern "C" void* FUN_71003a6ce0(void*, u64, long, u32);       // article create (primary)
extern "C" void* FUN_71003a5d80(void*, u64, long, u32);       // article create (secondary)
extern "C" void FUN_71003cbf10(void*);                         // element destructor

// ______ Singletons ________________________________________________

namespace lib {
    template <typename T> struct Singleton {
        static void** instance_;
    };
}
namespace app { struct BattleObjectManager; }
extern template struct lib::Singleton<app::BattleObjectManager>;

// ______ Zero constant ________________________________________________
// PTR_ConstantZero_71052a7a88 is a data pointer to a 16-byte zero value.
// Used as a fallback return when a vtable call returns null.
extern u8 PTR_ConstantZero_71052a7a88[];

// ════════════════════════════════════════════════════════════════════
// Fighter core functions — 0x71003 range
// ════════════════════════════════════════════════════════════════════

// ── 0x71003e5ba0 (56B) — BST post-order delete ─────────────────────
// Recursively destroys all nodes in a binary search tree.
// [derived: Ghidra FUN_71003e5ba0 — post-order traversal:
//  recurse left (node[0]), recurse right (node[1]), free(node)]
void FUN_71003e5ba0(u64* node) {
    if (node != nullptr) {
        FUN_71003e5ba0(reinterpret_cast<u64*>(node[0]));
        FUN_71003e5ba0(reinterpret_cast<u64*>(node[1]));
        FUN_710392e590(node);
    }
}

// ── 0x71003de250 (52B) — IsAttack / BST container reset ────────────
// Destroys BST at +0x180, resets head pointer and sentinel, clears flag.
// [derived: Ghidra FUN_71003de250 — calls FUN_71003e5ba0 on +0x180,
//  zeros +0x178/+0x180/+0x188, clears byte at +0x190 (=400 decimal)]
void FUN_71003de250(u8* param_1) {
    FUN_71003e5ba0(*reinterpret_cast<u64**>(param_1 + 0x180));
    *reinterpret_cast<u64*>(param_1 + 0x180) = 0;
    *reinterpret_cast<u64*>(param_1 + 0x188) = 0;
    *reinterpret_cast<u64*>(param_1 + 0x178) = reinterpret_cast<u64>(param_1 + 0x180);
    *(param_1 + 400) = 0;
}

// ── 0x71003f77b0 (64B) — flag toggle with cleanup ──────────────────
// If current flag is set and new value is clear, calls vtable cleanup.
// Then stores the new flag value.
// [derived: Ghidra FUN_71003f77b0 — reads +0x54, conditional vt[0x50/8],
//  stores param_2&1 at +0x54]
void FUN_71003f77b0(u8* param_1, u8 param_2) {
    if (*(param_1 + 0x54) != 0 && (param_2 & 1) == 0) {
        void** vt = *reinterpret_cast<void***>(param_1);
        reinterpret_cast<void(*)(u8*)>(vt[0x50/8])(param_1);
    }
    *(param_1 + 0x54) = param_2 & 1;
}

// ── 0x71003dd500 (56B) — GetOffset2 ────────────────────────────────
// Calls vtable method to look up an offset by key, returns the value
// at result+0x10 or zero if not found.
// [derived: Ghidra FUN_71003dd500 — vt[0x1e8/8](param_1, param_2, param_3&1)
//  → if result != 0, return *(result+0x10); else return ConstantZero]
struct Vec2 { u64 lo; u64 hi; };
Vec2 FUN_71003dd500(u8* param_1, u64 param_2, u32 param_3) {
    long result = reinterpret_cast<long(*)(u8*, u64, u32)>(
        VT(param_1)[0x1e8/8])(param_1, param_2, param_3 & 1);
    Vec2* src = reinterpret_cast<Vec2*>(PTR_ConstantZero_71052a7a88);
    if (result != 0) {
        src = reinterpret_cast<Vec2*>(result + 0x10);
    }
    return *src;
}

// ── 0x71003dcdd0 (80B) — update attack entry frame ─────────────────
// For a given attack index, if a flag at +0x148 in the entry is set,
// reads a value from the posture module and stores it at +0x144.
// [derived: Ghidra FUN_71003dcdd0 — stride 0x150 array at +0x78,
//  check byte +0x148, vtable via +0x38 module (posture), store at +0x144]
void FUN_71003dcdd0(u8* param_1, s32 param_2) {
    u8* entries = *reinterpret_cast<u8**>(param_1 + 0x78);
    u8* entry = entries + (long)param_2 * 0x150;
    if (*(entry + 0x148) != 0) {
        // +0x38 from *(param_1+8) is posture module
        void** posture = *reinterpret_cast<void***>(*reinterpret_cast<u64*>(param_1 + 8) + 0x38);
        void** pvt = *reinterpret_cast<void***>(posture);
        u32 val = reinterpret_cast<u32(*)(void**)>(pvt[0xb0/8])(posture);
        *reinterpret_cast<u32*>(entry + 0x144) = val;
    }
}

// ── 0x71003a7740 (88B) — BattleObject activate ─────────────────────
// Sets object category to 4 and team to 0xFF, calls module vtable,
// then registers with BattleObjectManager.
// [derived: Ghidra FUN_71003a7740 — set +0x3a=4, +0x3c=0xff,
//  *(+0x20)→vt[0x28/8](module, param_2, *(param_1+0x10)),
//  BOM FUN_71003aeef0 with *(param_1+8) and *(param_2+8)]
void FUN_71003a7740(u8* param_1, u8* param_2) {
    *(param_1 + 0x3a) = 4;
    *(param_1 + 0x3c) = 0xff;
    void** module = *reinterpret_cast<void***>(param_1 + 0x20);
    void** mvt = *reinterpret_cast<void***>(module);
    reinterpret_cast<void(*)(void**, u8*, u32)>(mvt[0x28/8])(
        module, param_2, *reinterpret_cast<u32*>(param_1 + 0x10));
    FUN_71003aeef0(*lib::Singleton<app::BattleObjectManager>::instance_,
                   *reinterpret_cast<u32*>(param_1 + 0x8),
                   *reinterpret_cast<u16*>(param_2 + 8));
}

// ── 0x71003a7850 (88B) — BattleObject deactivate ────────────────────
// Unregisters from BattleObjectManager, calls module cleanup,
// sets category to 3 and team to 0xFF.
// [derived: Ghidra FUN_71003a7850 — BOM FUN_71003af040,
//  *(+0x20)→vt[0x30/8](module, param_2&1), set +0x3a=3, +0x3c=0xff]
void FUN_71003a7850(u8* param_1, u32 param_2) {
    FUN_71003af040(*lib::Singleton<app::BattleObjectManager>::instance_,
                   reinterpret_cast<long>(param_1));
    void** module = *reinterpret_cast<void***>(param_1 + 0x20);
    void** mvt = *reinterpret_cast<void***>(module);
    reinterpret_cast<void(*)(void**, u32)>(mvt[0x30/8])(module, param_2 & 1);
    *(param_1 + 0x3a) = 3;
    *(param_1 + 0x3c) = 0xff;
}

// ── 0x71003d0380 (96B) — conditional pair init ─────────────────────
// Calls vtable[0x80/8] with two different data pointers based on flags.
// [derived: Ghidra FUN_71003d0380 — if param_2&1, vt call with PTR_DAT_7104f691d0;
//  if param_3&1, vt call with 0x7104f691e0]
extern u8 PTR_DAT_7104f691d0[];
extern u8 PTR_DAT_7104f691e0[];

void FUN_71003d0380(u8* param_1, u64 param_2, u64 param_3) {
    if ((param_2 & 1) != 0) {
        reinterpret_cast<void(*)(u8*, void*)>(VT(param_1)[0x80/8])(
            param_1, &PTR_DAT_7104f691d0);
    }
    if ((param_3 & 1) != 0) {
        reinterpret_cast<void(*)(u8*, void*)>(VT(param_1)[0x80/8])(
            param_1, PTR_DAT_7104f691e0);
    }
}

// ── 0x71003f6e30 (92B) — set color param by index ──────────────────
// Checks +0xd0 module vtable flag, then calls vtable set method with
// the given value, and stores the value at +0xb4 on self.
// [derived: Ghidra FUN_71003f6e30 — +0xd0 module vt[0x70/8] check,
//  vt[0x428/8](module, param_2, 0xb, 1), store at +0xb4]
void FUN_71003f6e30(u8* param_1, u32 param_2) {
    void** module = *reinterpret_cast<void***>(*reinterpret_cast<u64*>(param_1 + 8) + 0xd0);
    void** mvt = *reinterpret_cast<void***>(module);
    u64 flag = reinterpret_cast<u64(*)(void**)>(mvt[0x70/8])(module);
    if ((flag & 1) != 0) {
        reinterpret_cast<void(*)(void**, u32, s32, s32)>(mvt[0x428/8])(
            module, param_2, 0xb, 1);
        *reinterpret_cast<u32*>(param_1 + 0xb4) = param_2;
    }
}

// ── 0x71003f7000 (92B) — set color param by index (variant) ────────
// Same pattern as FUN_71003f6e30 but uses param 10 and stores at +0x2b4.
// [derived: Ghidra FUN_71003f7000 — +0xd0 module vt[0x70/8] check,
//  vt[0x428/8](module, param_2, 10, 1), store at +0x2b4]
void FUN_71003f7000(u8* param_1, u32 param_2) {
    void** module = *reinterpret_cast<void***>(*reinterpret_cast<u64*>(param_1 + 8) + 0xd0);
    void** mvt = *reinterpret_cast<void***>(module);
    u64 flag = reinterpret_cast<u64(*)(void**)>(mvt[0x70/8])(module);
    if ((flag & 1) != 0) {
        reinterpret_cast<void(*)(void**, u32, s32, s32)>(mvt[0x428/8])(
            module, param_2, 10, 1);
        *reinterpret_cast<u32*>(param_1 + 0x2b4) = param_2;
    }
}

// ── 0x71003f8c50 (88B) — apply attack param + conditional reset ────
// Calls vtable with struct fields, then conditionally resets flag.
// [derived: Ghidra FUN_71003f8c50 — vt[0x438/8](param_1, *(param_2+0xc),
//  *(param_2+0x10)), then if bit 6 of byte at param_2+0x2d is 0,
//  vt[0x2f0/8](param_1, 1)]
void FUN_71003f8c50(u8* param_1, u8* param_2) {
    reinterpret_cast<void(*)(u8*, u32, u32)>(VT(param_1)[0x438/8])(
        param_1,
        *reinterpret_cast<u32*>(param_2 + 0xc),
        *reinterpret_cast<u32*>(param_2 + 0x10));
    if (((*(param_2 + 0x2d) >> 6) & 1) == 0) {
        reinterpret_cast<void(*)(u8*, s32)>(VT(param_1)[0x2f0/8])(param_1, 1);
    }
}

// ── 0x71003fd310 (96B) — spawn effect with hash ────────────────────
// Calls effect module vtable method with a hash identifier and position.
// [derived: Ghidra FUN_71003fd310 — effect_module (+0x140) vt[0x68/8]
//  with float 1.0, hash 0xee04a4651, param_3+0x10, zero vec, 0, -1, 0, 0]
void FUN_71003fd310(u64 param_1, u8* param_2, u8* param_3) {
    u64 zero_lo = *reinterpret_cast<u64*>(PTR_ConstantZero_71052a7a88);
    u64 zero_hi = *reinterpret_cast<u64*>(PTR_ConstantZero_71052a7a88 + 8);
    u64 local_20[2];
    local_20[0] = zero_lo;
    local_20[1] = zero_hi;
    void** effect = *reinterpret_cast<void***>(*reinterpret_cast<u64*>(param_2 + 0x140));
    void** evt = *reinterpret_cast<void***>(effect);
    reinterpret_cast<void(*)(u32, void**, u64, void*, void*, s32, s32, s32, s32)>(
        evt[0x68/8])(
        0x3f800000, // 1.0f as u32
        effect, 0xee04a4651ULL, param_3 + 0x10, local_20, 0, -1, 0, 0);
}

// ── 0x71003fffa0 (128B) — check any attack entry valid ──────────────
// Loops over attack entries, checks float at +0x10 in each,
// returns 1 if any entry's vtable check fails.
// [derived: Ghidra FUN_71003fffa0 — loop count at param_1[2],
//  stride 0x1c0 from param_1[3], read float at +0x10,
//  if (float < 0.0 == NAN(float)) && vt[0xe0/8] returns false → return 1]
u64 FUN_71003fffa0(u8* param_1) {
    s32 count = *reinterpret_cast<s32*>(param_1 + 0x10);  // param_1[2] as long*
    if (count > 0) {
        u8* base = *reinterpret_cast<u8**>(param_1 + 0x18);  // param_1[3]
        for (s32 i = 0; i < count; i++) {
            f32 val = *reinterpret_cast<f32*>(base + (long)i * 0x1c0 + 0x10);
            if (!(val < 0.0f)) {
                void** vt = *reinterpret_cast<void***>(param_1);
                u64 r = reinterpret_cast<u64(*)(u8*)>(vt[0xe0/8])(param_1);
                if ((r & 1) == 0) {
                    return 1;
                }
            }
        }
    }
    return 0;
}

// ── 0x71003d41e0 (104B) — GenerateArticleEnable ────────────────────
// Checks if article generation is valid via vtable, then dispatches.
// [derived: Ghidra FUN_71003d41e0 — vt[0x1d8/8]() → if bit 0 set,
//  vt[0x78/8](param_1, param_2, param_3&1, param_4)]
void FUN_71003d41e0(u8* param_1, u32 param_2, u32 param_3, u32 param_4) {
    u64 valid = reinterpret_cast<u64(*)()>(VT(param_1)[0x1d8/8])();
    if ((valid & 1) != 0) {
        reinterpret_cast<void(*)(u8*, u32, u32, u32)>(VT(param_1)[0x78/8])(
            param_1, param_2, param_3 & 1, param_4);
    }
}

// ── 0x71003cd650 (136B) — vector-like destructor ────────────────────
// Destroys elements in a vector (stride 0x70), frees buffer, frees self.
// [derived: Ghidra FUN_71003cd650 — set vtable PTR_LAB_7104f68e90,
//  loop from count*0x70 down to 0 calling FUN_71003cbf10 on each element,
//  free buffer at -0x10 from data, free self]
extern u8 PTR_LAB_7104f68e90[];

void FUN_71003cd650(u64* param_1) {
    u8* data = reinterpret_cast<u8*>(param_1[3]);
    *param_1 = reinterpret_cast<u64>(&PTR_LAB_7104f68e90);
    if (data != nullptr) {
        long count = *reinterpret_cast<long*>(data - 8);
        if (count == 0) {
            FUN_710392e590(data - 0x10);
        } else {
            long offset = count * 0x70;
            do {
                FUN_71003cbf10(data + offset - 0x70);
                offset -= 0x70;
            } while (offset != 0);
            FUN_710392e590(data - 0x10);
            if (param_1 == nullptr) {
                return;
            }
        }
    }
    FUN_710392e590(param_1);
}

// ── 0x71003cddb0 (136B) — vector-like destructor (identical TU) ────
// [derived: Ghidra FUN_71003cddb0 — identical to FUN_71003cd650,
//  different translation unit instance]
void FUN_71003cddb0(u64* param_1) {
    u8* data = reinterpret_cast<u8*>(param_1[3]);
    *param_1 = reinterpret_cast<u64>(&PTR_LAB_7104f68e90);
    if (data != nullptr) {
        long count = *reinterpret_cast<long*>(data - 8);
        if (count == 0) {
            FUN_710392e590(data - 0x10);
        } else {
            long offset = count * 0x70;
            do {
                FUN_71003cbf10(data + offset - 0x70);
                offset -= 0x70;
            } while (offset != 0);
            FUN_710392e590(data - 0x10);
            if (param_1 == nullptr) {
                return;
            }
        }
    }
    FUN_710392e590(param_1);
}

// ════════════════════════════════════════════════════════════════════
// sv_kinetic_energy — speed/field readers via KineticModule vtable
// Range: 0x71022 — lua_bind entry points that read kinetic energy data
// ════════════════════════════════════════════════════════════════════

// ── 0x71022213e0 (104B) — get_energy3_speed_x ──────────────────────
// Gets kinetic energy 3's speed, pushes x component to lua stack.
// [derived: Ghidra FUN_71022213e0 — kinetic(+0x68)→get_energy(3)
//  →get_speed()→ read [0], push as s32 with type tag 3. Returns 1]
u64 FUN_71022213e0(u8* L) {
    u8* ctx = *reinterpret_cast<u8**>(L - 8);
    u8* acc = *reinterpret_cast<u8**>(ctx + 0x1a0);
    app::KineticModule* kinetic = reinterpret_cast<app::KineticModule*>(
        *reinterpret_cast<void**>(acc + 0x68));
    app::KineticEnergy* energy = kinetic->get_energy(3);
    u32* speed = reinterpret_cast<u32*>(energy->get_speed());
    u32 val = speed[0];

    u32* stack = *reinterpret_cast<u32**>(L + 0x10);
    stack[2] = 3;  // type tag: float
    stack[0] = val;
    *reinterpret_cast<u64*>(L + 0x10) += 0x10;
    return 1;
}

// ── 0x7102221450 (104B) — get_energy3_speed_y ──────────────────────
// Gets kinetic energy 3's speed, pushes y component to lua stack.
// [derived: Ghidra FUN_7102221450 — same as 71022213e0 but reads [1] (+4)]
u64 FUN_7102221450(u8* L) {
    u8* ctx = *reinterpret_cast<u8**>(L - 8);
    u8* acc = *reinterpret_cast<u8**>(ctx + 0x1a0);
    app::KineticModule* kinetic = reinterpret_cast<app::KineticModule*>(
        *reinterpret_cast<void**>(acc + 0x68));
    app::KineticEnergy* energy = kinetic->get_energy(3);
    u32* speed = reinterpret_cast<u32*>(energy->get_speed());
    u32 val = speed[1];

    u32* stack = *reinterpret_cast<u32**>(L + 0x10);
    stack[2] = 3;
    stack[0] = val;
    *reinterpret_cast<u64*>(L + 0x10) += 0x10;
    return 1;
}

// ── 0x7102221360 (124B) — get_energy3_speed_xy ─────────────────────
// Gets kinetic energy 3's speed, pushes x and y to lua stack.
// [derived: Ghidra FUN_7102221360 — reads *(u64*)speed as packed x|y,
//  pushes low 32 bits then high 32 bits as separate values. Returns 2]
u64 FUN_7102221360(u8* L) {
    u8* ctx = *reinterpret_cast<u8**>(L - 8);
    u8* acc = *reinterpret_cast<u8**>(ctx + 0x1a0);
    app::KineticModule* kinetic = reinterpret_cast<app::KineticModule*>(
        *reinterpret_cast<void**>(acc + 0x68));
    app::KineticEnergy* energy = kinetic->get_energy(3);
    u64* speed_ptr = reinterpret_cast<u64*>(energy->get_speed());
    u64 packed = *speed_ptr;

    u32* stack = *reinterpret_cast<u32**>(L + 0x10);
    stack[2] = 3;
    stack[0] = (u32)packed;

    u64 sp = *reinterpret_cast<u64*>(L + 0x10);
    u32* stack2 = reinterpret_cast<u32*>(sp + 0x10);
    *reinterpret_cast<u64*>(L + 0x10) = sp + 0x10;
    stack2[0] = (u32)(packed >> 32);
    stack2[2] = 3;
    *reinterpret_cast<u64*>(L + 0x10) += 0x10;
    return 2;
}

// ── 0x71022214c0 (152B) — get_energy3_speed_xyz ────────────────────
// Gets kinetic energy 3's speed, pushes x, y, z to lua stack.
// [derived: Ghidra FUN_71022214c0 — reads speed[0], speed[1], speed[2]
//  as separate values, pushes each with type tag 3. Returns 3]
u64 FUN_71022214c0(u8* L) {
    u8* ctx = *reinterpret_cast<u8**>(L - 8);
    u8* acc = *reinterpret_cast<u8**>(ctx + 0x1a0);
    app::KineticModule* kinetic = reinterpret_cast<app::KineticModule*>(
        *reinterpret_cast<void**>(acc + 0x68));
    app::KineticEnergy* energy = kinetic->get_energy(3);
    u32* speed = reinterpret_cast<u32*>(energy->get_speed());
    u32 vx = speed[0];

    u32* stack = *reinterpret_cast<u32**>(L + 0x10);
    stack[2] = 3;
    stack[0] = vx;

    u64 sp = *reinterpret_cast<u64*>(L + 0x10);
    *reinterpret_cast<u64*>(L + 0x10) = sp + 0x10;
    *reinterpret_cast<u32*>(sp + 0x10) = speed[1];
    *reinterpret_cast<u32*>(sp + 0x18) = 3;

    sp = *reinterpret_cast<u64*>(L + 0x10);
    *reinterpret_cast<u64*>(L + 0x10) = sp + 0x10;
    *reinterpret_cast<u32*>(sp + 0x10) = speed[2];
    *reinterpret_cast<u32*>(sp + 0x18) = 3;
    *reinterpret_cast<u64*>(L + 0x10) += 0x10;
    return 3;
}

// ── 0x7102222280 (116B) — get_energy3_accel_xy ─────────────────────
// Gets kinetic energy 3, reads fields at +0x40/+0x44, pushes to lua stack.
// [derived: Ghidra FUN_7102222280 — kinetic→get_energy(3), no vtable call,
//  direct struct read at +0x40 and +0x44. Returns 2]
u64 FUN_7102222280(u8* L) {
    u8* ctx = *reinterpret_cast<u8**>(L - 8);
    u8* acc = *reinterpret_cast<u8**>(ctx + 0x1a0);
    app::KineticModule* kinetic = reinterpret_cast<app::KineticModule*>(
        *reinterpret_cast<void**>(acc + 0x68));
    u8* energy = reinterpret_cast<u8*>(kinetic->get_energy(3));

    u32 val0 = *reinterpret_cast<u32*>(energy + 0x40);
    u32* stack = *reinterpret_cast<u32**>(L + 0x10);
    stack[2] = 3;
    stack[0] = val0;

    u64 sp = *reinterpret_cast<u64*>(L + 0x10);
    *reinterpret_cast<u64*>(L + 0x10) = sp + 0x10;
    *reinterpret_cast<u32*>(sp + 0x10) = *reinterpret_cast<u32*>(energy + 0x44);
    *reinterpret_cast<u32*>(sp + 0x18) = 3;
    *reinterpret_cast<u64*>(L + 0x10) += 0x10;
    return 2;
}

// ── 0x7102222300 (116B) — get_energy3_brake_xy ─────────────────────
// Same pattern as 0x7102222280 but reads +0x50/+0x54.
// [derived: Ghidra FUN_7102222300 — kinetic→get_energy(3), read +0x50,+0x54]
u64 FUN_7102222300(u8* L) {
    u8* ctx = *reinterpret_cast<u8**>(L - 8);
    u8* acc = *reinterpret_cast<u8**>(ctx + 0x1a0);
    app::KineticModule* kinetic = reinterpret_cast<app::KineticModule*>(
        *reinterpret_cast<void**>(acc + 0x68));
    u8* energy = reinterpret_cast<u8*>(kinetic->get_energy(3));

    u32 val0 = *reinterpret_cast<u32*>(energy + 0x50);
    u32* stack = *reinterpret_cast<u32**>(L + 0x10);
    stack[2] = 3;
    stack[0] = val0;

    u64 sp = *reinterpret_cast<u64*>(L + 0x10);
    *reinterpret_cast<u64*>(L + 0x10) = sp + 0x10;
    *reinterpret_cast<u32*>(sp + 0x10) = *reinterpret_cast<u32*>(energy + 0x54);
    *reinterpret_cast<u32*>(sp + 0x18) = 3;
    *reinterpret_cast<u64*>(L + 0x10) += 0x10;
    return 2;
}

// ── 0x7102222380 (116B) — get_energy3_stable_speed_xy ───────────────
// Same pattern as 0x7102222280 but reads +0x60/+0x64.
// [derived: Ghidra FUN_7102222380 — kinetic→get_energy(3), read +0x60,+0x64]
u64 FUN_7102222380(u8* L) {
    u8* ctx = *reinterpret_cast<u8**>(L - 8);
    u8* acc = *reinterpret_cast<u8**>(ctx + 0x1a0);
    app::KineticModule* kinetic = reinterpret_cast<app::KineticModule*>(
        *reinterpret_cast<void**>(acc + 0x68));
    u8* energy = reinterpret_cast<u8*>(kinetic->get_energy(3));

    u32 val0 = *reinterpret_cast<u32*>(energy + 0x60);
    u32* stack = *reinterpret_cast<u32**>(L + 0x10);
    stack[2] = 3;
    stack[0] = val0;

    u64 sp = *reinterpret_cast<u64*>(L + 0x10);
    *reinterpret_cast<u64*>(L + 0x10) = sp + 0x10;
    *reinterpret_cast<u32*>(sp + 0x10) = *reinterpret_cast<u32*>(energy + 0x64);
    *reinterpret_cast<u32*>(sp + 0x18) = 3;
    *reinterpret_cast<u64*>(L + 0x10) += 0x10;
    return 2;
}

// ── 0x7102222400 (116B) — get_energy3_limit_speed_xy ────────────────
// Same pattern as 0x7102222280 but reads +0x70/+0x74.
// [derived: Ghidra FUN_7102222400 — kinetic→get_energy(3), read +0x70,+0x74]
u64 FUN_7102222400(u8* L) {
    u8* ctx = *reinterpret_cast<u8**>(L - 8);
    u8* acc = *reinterpret_cast<u8**>(ctx + 0x1a0);
    app::KineticModule* kinetic = reinterpret_cast<app::KineticModule*>(
        *reinterpret_cast<void**>(acc + 0x68));
    u8* energy = reinterpret_cast<u8*>(kinetic->get_energy(3));

    u32 val0 = *reinterpret_cast<u32*>(energy + 0x70);
    u32* stack = *reinterpret_cast<u32**>(L + 0x10);
    stack[2] = 3;
    stack[0] = val0;

    u64 sp = *reinterpret_cast<u64*>(L + 0x10);
    *reinterpret_cast<u64*>(L + 0x10) = sp + 0x10;
    *reinterpret_cast<u32*>(sp + 0x10) = *reinterpret_cast<u32*>(energy + 0x74);
    *reinterpret_cast<u32*>(sp + 0x18) = 3;
    *reinterpret_cast<u64*>(L + 0x10) += 0x10;
    return 2;
}
