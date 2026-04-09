#include "types.h"

// param_loading.cpp — pool-d
// Contains: apply_lift_param (0x7100995040), get_magic_ball_param (0x710165fcb0),
//           UpdateParams (0x710008b480)
// File territory: src/app/param_loading.cpp

extern "C" void* memset(void*, int, u64);
extern "C" void* memcpy(void*, const void*, u64);
extern "C" float fabsf(float);

// CXA guard (static init)
extern "C" s32 __cxa_guard_acquire(void*);
extern "C" void __cxa_guard_release(void*);

// Called functions
extern "C" s64 get_battle_object_from_id(u32);
extern "C" void global_param_init_sets_team_flag(void);
extern "C" void FUN_71000001c0(void*, void*, void*);
extern "C" u64 FUN_710160efa0(u32);

// FUN_710160e340: applies velocity vector, returns float4 via registers
struct Float4Ret { f32 x, y, z, w; };
extern "C" Float4Ret FUN_710160e340(u64 param_1, f32* param_2);

// FUN_71015dc450: get default position on stage
extern "C" u64 FUN_71015dc450(u64* out);

// ItemParamAccessor singleton
extern "C" s64 lib_Singleton_ItemParamAccessor_instance_ __asm("_ZN3lib9SingletonIN3app17ItemParamAccessorEE9instance_E");

// Guard variables
extern "C" u64 DAT_71052b6100;
extern "C" u64 DAT_71052b60f8;
extern "C" u8 PTR_LAB_7104f61078;
extern "C" u64 DAT_71052b60f0;

// Team param init guard
extern "C" u64 g_team_param_init_guard;
extern "C" u8 DAT_71052c4268;
extern "C" u8 DAT_71052c4180;
extern "C" u8 PTR_LOOP_7104f16000;
extern "C" void FUN_7101763de0();

// PRNG state
extern "C" void* DAT_71052c25b0;

// Stage bounds
extern "C" void* DAT_71052b7f00;

// .rodata float constants
extern "C" __attribute__((visibility("hidden"))) f32 DAT_7104471970;
extern "C" __attribute__((visibility("hidden"))) f32 DAT_710447291c;
extern "C" __attribute__((visibility("hidden"))) f32 DAT_7104472710;
extern "C" __attribute__((visibility("hidden"))) u64 _DAT_7104469030;
extern "C" __attribute__((visibility("hidden"))) f32 _UNK_7104469038;
extern "C" __attribute__((visibility("hidden"))) f32 _UNK_710446903c;

// ── param tree binary search helper ──────────────────────────
// [derived: param accessor stores sorted hash40 array, binary searched]
// NOT a function in the original code — inlined at each call site.
// The compiler should inline this since it's static inline.
static inline f32 param_lookup_float(s64* param_acc, u64 target_hash) {
    if (param_acc == nullptr) return 0.0f;
    char* data = (char*)param_acc[1];
    if (*data != '\f') return 0.0f;
    s32 count = *(s32*)(data + 1);
    if (count <= 0) return 0.0f;

    s32 lo = 0;
    s32 hi = count - 1;
    const char* found = "";
    do {
        s32 sum = hi + lo;
        if (sum < 0) sum += 1;
        s32 mid = sum >> 1;
        u32* entry = (u32*)(*(s64*)(*(s64*)param_acc + 0x28)
                     + (s64)*(s32*)(data + 5)
                     + (s64)mid * 8);
        u64 hash = *(u64*)(*(s64*)(*(s64*)param_acc + 0x20) + (u64)entry[0] * 8);
        if (hash == target_hash) {
            u32 off = entry[1];
            if ((s32)off >= 0)
                found = data + (s32)off;
            break;
        }
        s32 new_hi = mid - 1;
        if (hash < target_hash + 1) {
            lo = mid + 1;
            new_hi = hi;
        }
        hi = new_hi;
    } while (lo <= hi);

    if (*found == '\b')
        return *(f32*)(found + 1);
    return 0.0f;
}

// ════════════════════════════════════════════════════════════════════
// 0x7100995040 — app::FighterSpecializer_Donkey::apply_lift_param
// Turns a WorkModule flag on/off, then tail-calls another module.
// Size: 92 bytes (0x5C)
// ════════════════════════════════════════════════════════════════════
// param_1: FighterModuleAccessor* (has WorkModule at +0x50, DK module at +0xf1c0)
// param_2: bool — true = on_flag, false = off_flag
// Flag index: 0x20000058 (FIGHTER_DONKEY_INSTANCE_WORK_ID_FLAG_LIFT)

extern "C"
void apply_lift_param(u8* param_1, bool param_2) {
    // Get WorkModule at +0x50
    // [derived: BattleObjectModuleAccessor +0x50 = WorkModule]
    s64* work_mod = *(s64**)(param_1 + 0x50);
    void** vt = *(void***)work_mod;

    if (param_2) {
        // WorkModule::on_flag(0x20000058)
        ((void(*)(s64*, u32))vt[0x110/8])(work_mod, 0x20000058);
    } else {
        // WorkModule::off_flag(0x20000058)
        ((void(*)(s64*, u32))vt[0x120/8])(work_mod, 0x20000058);
    }

    // Tail-call DK-specific module at +0xf1c0, vtable slot 0x280/8
    // [derived: param_1+0xf1c0 is DK fighter specializer module pointer]
    s64* dk_mod = *(s64**)(param_1 + 0xf1c0);
    ((void(*)(s64*, s32, s32))(*(void***)dk_mod)[0x280/8])(dk_mod, 0, 1);
}

// ════════════════════════════════════════════════════════════════════
// 0x7100937030 — app::FighterSpecializer_Demon::sub_rage_system
// Kazuya: reads rage modifier from FighterParamAccessor2 and applies
// via WorkModule. Size: 180 bytes (0xB4)
// ════════════════════════════════════════════════════════════════════
// param_1: Fighter* — Kazuya's fighter object
// param_2: bool — true = use offset +8 (enhanced), false = use offset +4 (base)

// FighterParamAccessor2 singleton
extern "C" __attribute__((visibility("hidden"))) void* DAT_71052bb3b0;
// Get damage level (clamped index into rage table)
extern "C" s32 FUN_71009320f0(s64*);
// __throw_out_of_range (noreturn)
[[noreturn]] extern "C" void _ZNSt3__120__vector_base_commonILb1EE20__throw_out_of_rangeEv();

extern "C"
void sub_rage_system(u8* param_1, bool param_2) {
    s64* accessor2 = (s64*)DAT_71052bb3b0;
    s64 rage_table = *(s64*)((u8*)accessor2 + 0x1490);
    if (rage_table == 0) return;

    // Get WorkModule from Fighter->+0x20->+0x50
    s64* work_mod = *(s64**)(*(s64*)(param_1 + 0x20) + 0x50);

    s32 damage_level = FUN_71009320f0(work_mod);

    // std::vector at rage_table+0x170: begin/end pointers, each entry 0x10 bytes
    s64 vec_begin = *(s64*)(rage_table + 0x170);
    s64 vec_end = *(s64*)(rage_table + 0x178);
    // [derived: ptrdiff_t division, must use asr not lsr]
    s64 vec_size = (vec_end - vec_begin) >> 4;

    // Clamp damage_level to [0, vec_size-1]
    s32 idx = damage_level - 1;
    s32 max_idx = (s32)vec_size - 1;
    if (idx > max_idx) idx = max_idx;
    if (damage_level < 1) idx = 0;

    if ((u64)(s64)idx >= (u64)vec_size) {
        // Out of range — calls noreturn __throw_out_of_range
        _ZNSt3__120__vector_base_commonILb1EE20__throw_out_of_rangeEv();
    }

    s64 entry = vec_begin + (s64)idx * 0x10;
    u32 value;
    if (param_2) {
        value = *(u32*)(entry + 8);  // Enhanced rage modifier
    } else {
        value = *(u32*)(entry + 4);  // Base rage modifier
    }

    // Tail-call WorkModule vtable[0xe0/8] (sub_int)
    // [derived: WorkModule::sub_int(rage_value, FIGHTER_DEMON_INSTANCE_WORK_ID)]
    void** vt = *(void***)work_mod;
    ((void(*)(s64*, u32, u32))vt[0xe0/8])(work_mod, value, 0x100000c9);
}

// ── Helper: ensure team params are initialized ───────────────
static inline void ensure_team_param_init() {
    if ((g_team_param_init_guard & 1) == 0) {
        s32 acq = __cxa_guard_acquire(&g_team_param_init_guard);
        if (acq != 0) {
            global_param_init_sets_team_flag();
            FUN_71000001c0((void*)FUN_7101763de0, &DAT_71052c4180, &PTR_LOOP_7104f16000);
            __cxa_guard_release(&g_team_param_init_guard);
        }
    }
}

// ════════════════════════════════════════════════════════════════════
// 0x710165fcb0 — app::magicball::get_magic_ball_param
// Computes magic ball trajectory with stage bounds clamping.
// Size: 3,184 bytes
// ════════════════════════════════════════════════════════════════════
// Returns 1 if trajectory hits within bounds, 0 with default pos otherwise.

extern "C"
u64 get_magic_ball_param(
    u8* param_1,     // ItemModuleAccessor*
    u32 param_2,     // battle object id
    f32* param_3,    // out: result position (4 floats)
    f32* param_4,    // in: direction vector (2 floats)
    f32* param_5     // in/out: velocity data (6 floats)
) {
    // All variable declarations up front to allow goto
    s64* item_param;
    s64* ground_mod;
    s64 obj;
    s32 acq;
    f32 pos[4];
    u32 obj_type;
    u64 pos_packed;
    f32 dir_x_abs;
    s64 prng_state;
    u32 prng_s3, prng_t;
    f32 epsilon;
    s64* pa;
    f32 random_range, random_offset;
    f32 vel_x, vel_y, dir_sign;
    f32 vert_range, vert_speed, lateral_speed;
    u32 saved_y, saved_z, saved_w;
    f32 vel_buf[4];
    Float4Ret applied;
    f32 max_dist;
    f32 result_pos[4];
    u64 hit;
    f32 end_x, end_y, end_z, end_w;
    s64 stage;
    f32 bound_left, bound_right, bound_top, bound_bottom;
    f32 start_x, start_y;
    bool in_x, in_y;
    f32 clamp_x, clamp_y;
    bool cx_needed;
    f32 dx, dy, dist_sq, max_dist_sq;
    u64 default_pos[2];
    u64 got_pos;
    f32 lookup_buf[4];
    s64* module_ptr;
    void (*vtable_fn)(s64*, u64, f32*, s32);
    u64 team_hash;
    f32 abs_val;

    item_param = (s64*)lib_Singleton_ItemParamAccessor_instance_;
    ground_mod = *(s64**)(param_1 + 0x58);

    // Get battle object from ID
    obj = get_battle_object_from_id(param_2);
    if ((obj == 0 || *(u8*)(obj + 0x3a) < 4) &&
        (obj = (s64)DAT_71052b60f8, (DAT_71052b6100 & 1) == 0)) {
        acq = __cxa_guard_acquire(&DAT_71052b6100);
        obj = (s64)DAT_71052b60f8;
        if (acq != 0) {
            FUN_71000001c0((void*)&DAT_71052b60f0, nullptr, nullptr);
            DAT_71052b60f0 = (u64)&PTR_LAB_7104f61078;
            __cxa_guard_release(&DAT_71052b6100);
            obj = (s64)DAT_71052b60f8;
        }
    }

    if (*(u8*)(obj + 0x3a) < 4) goto default_return;

    // Initialize position to zero
    pos[0] = 0.0f; pos[1] = 0.0f; pos[2] = 0.0f; pos[3] = 0.0f;
    obj_type = *(u32*)(obj + 8) >> 0x1c;

    if (obj_type == 0) {
        // Type 0: direct param lookup via vtable[0x150/8] with hash 0x4a7f3f69c
        lookup_buf[0] = 0.0f; lookup_buf[1] = 0.0f;
        lookup_buf[2] = 0.0f; lookup_buf[3] = 0.0f;
        module_ptr = *(s64**)(*(s64*)(obj + 0x20) + 0x78);
        vtable_fn = (void(*)(s64*, u64, f32*, s32))(*(void**)(*(s64*)module_ptr + 0x150));
        vtable_fn(module_ptr, 0x4a7f3f69cULL, lookup_buf, 1);
        pos[0] = lookup_buf[0];
        pos[1] = lookup_buf[1];
    } else if (obj_type == 4) {
        // Type 4: team mode conditional
        ensure_team_param_init();

        if (DAT_71052c4268 != 0) {
            // Team mode
            lookup_buf[0] = 0.0f; lookup_buf[1] = 0.0f;
            lookup_buf[2] = 0.0f; lookup_buf[3] = 0.0f;
            team_hash = FUN_710160efa0(param_2);
            module_ptr = *(s64**)(*(s64*)(obj + 0x20) + 0x78);
            vtable_fn = (void(*)(s64*, u64, f32*, s32))(*(void**)(*(s64*)module_ptr + 0x150));
            vtable_fn(module_ptr, team_hash, lookup_buf, 1);
            pos[0] = lookup_buf[0];
            pos[1] = lookup_buf[1];
        } else {
            // Non-team: get work module position
            // Call WorkModule vtable to get position
            s64 work_mod_ptr = *(s64*)(*(s64*)(obj + 0x20) + 0x38);
            u32* work_pos = (u32*)((*(u64(**)(s64))(*(s64*)work_mod_ptr + 0x60))(work_mod_ptr));
            vel_x = 0.0f; // y_offset default

            // Param lookup: hash 0x20f4f209e5 — y-axis offset
            pa = *(s64**)((u8*)*item_param + 0x20e8);
            vel_x = param_lookup_float(pa, 0x20f4f209e5ULL);

            pos[0] = *(f32*)work_pos;
            pos[1] = vel_x + *(f32*)(work_pos + 1);
        }
    }

    pos_packed = *(u64*)pos;

    // Absolute value of direction X component
    dir_x_abs = fabsf(param_4[0]);

    // PRNG: xoshiro256-like state update
    prng_state = *(s64*)*(s64*)DAT_71052c25b0;
    prng_s3 = *(u32*)(prng_state + 0x84);
    *(s32*)(prng_state + 0x88) = *(s32*)(prng_state + 0x88) + 1;
    prng_t = *(u32*)(prng_state + 0x78) ^ (*(u32*)(prng_state + 0x78) << 11);
    prng_t = prng_t ^ (prng_t >> 8) ^ prng_s3 ^ (prng_s3 >> 19);
    *(u32*)(prng_state + 0x78) = *(u32*)(prng_state + 0x7c);
    *(u32*)(prng_state + 0x7c) = *(u32*)(prng_state + 0x80);
    *(u32*)(prng_state + 0x80) = prng_s3;
    *(u32*)(prng_state + 0x84) = prng_t;

    epsilon = DAT_7104471970;
    pa = *(s64**)((u8*)*item_param + 0x20e8);
    random_range = 0.0f;
    random_offset = (f32)prng_t * DAT_710447291c * DAT_7104472710 + 0.0f;

    // Direction: check if X direction is near-zero (epsilon test)
    if (dir_x_abs == epsilon ||
        (dir_x_abs < epsilon) != (__builtin_isnan(dir_x_abs) || __builtin_isnan(epsilon))) {
        // X direction is near-zero → use Y direction for trajectory

        // Param lookup: hash 0x1cf16241f6 — random range threshold
        if (pa != nullptr) random_range = param_lookup_float(pa, 0x1cf16241f6ULL);

        dir_sign = -1.0f;
        if (0.0f <= param_4[1]) dir_sign = 1.0f;

        // Param lookup: hash 0x177fa1eb65 — lateral velocity magnitude
        if (pa != nullptr) {
            lateral_speed = param_lookup_float(pa, 0x177fa1eb65ULL);
        } else {
            lateral_speed = 0.0f;
        }

        vel_x = dir_sign * lateral_speed;
        if (random_range < random_offset) {
            vel_y = 0.0f - vel_x;
        } else {
            vel_y = vel_x + 0.0f;
            dir_sign = -dir_sign;
        }

        // Update param_5 velocity state
        vel_buf[0] = 0.0f; vel_buf[1] = 0.0f;
        vel_buf[2] = 0.0f; vel_buf[3] = 0.0f;
        param_5[4] = param_5[2];
        param_5[5] = param_5[3];
        *(u64*)param_5 = (u64)*(u32*)&dir_sign | ((u64)*(u32*)(param_5) << 32);
        // Actually: param_5[0] = dir_sign, param_5[1] keeps old value
        // Let me simplify:
        // In Ghidra: *(ulong *)param_5 = CONCAT44(fVar33,(int)*(undefined8 *)param_5);
        // This means: low 32 bits = *(u32*)&orig_param_5[0], high 32 bits = *(u32*)&dir_sign
        // Wait, CONCAT44(a, b) = (a << 32) | b
        // So *(u64*)param_5 = ((u64)*(u32*)&dir_sign << 32) | (u32)*(u64*)param_5
        // Which means: param_5[0] = low32 of old param_5[0..1] (unchanged)
        //              param_5[1] = dir_sign
        // Hmm, actually CONCAT44(fVar33, (int)*(undefined8*)param_5):
        // fVar33 goes in high 32 bits, low 32 from *(int*)param_5 (which is param_5[0] as int)
        // So: param_5[1] = dir_sign (fVar33), param_5[0] unchanged
        // Wait no. *(ulong*)param_5 writes 8 bytes starting at param_5.
        // CONCAT44(high, low) = (high << 32) | (low & 0xFFFFFFFF)
        // high = fVar33 = dir_sign
        // low = (int)*(undefined8*)param_5 = first 4 bytes of param_5 = param_5[0]
        // So param_5[0] stays, param_5[1] = dir_sign. No wait, little endian:
        // *(u64*)param_5 = low | (high << 32) where low = param_5[0], high = dir_sign
        // On LE: byte[0..3] = param_5[0] unchanged, byte[4..7] = dir_sign
        // So param_5[1] = dir_sign? That doesn't match the Ghidra where fVar33 = dir_sign
        // Let me re-read: fStack_7c = fVar29; which is vel_x or 0-vel_x
        // And the code is setting param_5 with CONCAT44(fVar33, (int)*(undefined8*)param_5)
        // In the horizontal case, fVar33 = -1 or +1 based on param_4[1]

        // I'll just write it simply:
        {
            u32 old_x = *(u32*)param_5;
            *(u32*)(param_5 + 0) = old_x;     // keep param_5[0]
            *(f32*)(param_5 + 1) = dir_sign;   // set param_5[1]
        }

        // Team mode check for velocity adjustment
        ensure_team_param_init();
        if (DAT_71052c4268 != 0) {
            saved_z = *(u32*)(param_5 + 2);
            saved_w = *(u32*)(param_5 + 3);
            param_5[4] = *(f32*)&saved_z;
            param_5[5] = *(f32*)&saved_w;
            param_5[0] = param_5[0]; // keep
            *(u32*)(param_5 + 1) = 0xbf800000; // -1.0f
            vel_y = vel_x;
        }
    } else {
        // X direction is NOT near-zero → use X direction for trajectory

        // Param lookup: hash 0x1aabe6836f — random range
        if (pa != nullptr) {
            random_range = param_lookup_float(pa, 0x1aabe6836fULL);
        }

        dir_sign = -1.0f;
        if (0.0f <= param_4[0]) dir_sign = 1.0f;

        // Param lookup: hash 0x1509d33ccb — vertical velocity magnitude
        if (pa != nullptr) {
            vert_speed = param_lookup_float(pa, 0x1509d33ccbULL);
        } else {
            vert_speed = 0.0f;
        }

        vel_x = dir_sign * vert_speed;
        if (random_range < random_offset) {
            vel_x = 0.0f - vel_x;
        } else {
            vel_x = vel_x + 0.0f;
            dir_sign = -dir_sign;
        }

        // Update param_5
        saved_y = *(u32*)(param_5 + 1);
        saved_z = *(u32*)(param_5 + 2);
        saved_w = *(u32*)(param_5 + 3);
        param_5[4] = *(f32*)&saved_z;
        param_5[5] = *(f32*)&saved_w;
        param_5[0] = dir_sign;
        *(u32*)(param_5 + 1) = saved_y;
    }

    // Apply velocity via FUN_710160e340
    vel_buf[0] = 0.0f; vel_buf[1] = 0.0f;
    vel_buf[2] = 0.0f; vel_buf[3] = 0.0f;
    applied = FUN_710160e340(pos_packed, vel_buf);
    vel_buf[0] = applied.x;
    vel_buf[1] = applied.y;
    vel_buf[2] = applied.z;
    vel_buf[3] = applied.w;

    // Param lookup: hash 0x2558cf62c7 — max trajectory distance
    pa = *(s64**)((u8*)*item_param + 0x20e8);
    max_dist = param_lookup_float(pa, 0x2558cf62c7ULL);

    // GroundModule intersection test (vtable slot 0x620/8)
    result_pos[0] = 0.0f; result_pos[1] = 0.0f;
    result_pos[2] = 0.0f; result_pos[3] = 0.0f;
    hit = (*(u64(**)(s64*, u64*, f32*, f32*, s32))(*(s64*)ground_mod + 0x620))
          (ground_mod, (u64*)pos, vel_buf, result_pos, 0);

    if ((hit & 1) == 0) {
        end_x = pos[0] + vel_buf[0];
        end_y = pos[1] + vel_buf[1];
        end_z = pos[2] + vel_buf[2];
        end_w = pos[3] + vel_buf[3];
    } else {
        end_x = result_pos[0];
        end_y = result_pos[1];
        end_z = result_pos[2];
        end_w = result_pos[3];
    }

    // Stage AABB bounds
    stage = *(s64*)DAT_71052b7f00;
    bound_left = *(f32*)(stage + 0xc20);
    bound_right = *(f32*)(stage + 0xc24);

    {
        u32 tmp0 = (u32)(pos_packed);
        u32 tmp1 = (u32)(pos_packed >> 32);
        start_x = *(f32*)&tmp0;
        start_y = *(f32*)&tmp1;
    }

    // Check: is endpoint within stage horizontal bounds?
    in_x = false;
    in_y = false;

    if (bound_left <= end_x) {
        in_x = false;
        if (!__builtin_isnan(end_x) && !__builtin_isnan(bound_right)) {
            in_x = end_x < bound_right;
            if (end_x == bound_right) in_x = true;
        }
    }

    if (in_x) {
        bound_top = *(f32*)(stage + 0xc28);
        bound_bottom = *(f32*)(stage + 0xc2c);
        if ((end_y == bound_top || (end_y < bound_top) != (__builtin_isnan(end_y) || __builtin_isnan(bound_top))) &&
            bound_bottom <= end_y) {
            in_y = true;
        }
    }

    if (in_x && in_y) {
        // Endpoint within bounds — clamp to boundary and check distance
        bound_top = *(f32*)(stage + 0xc28);
        bound_bottom = *(f32*)(stage + 0xc2c);

        if (end_x < bound_left) {
            cx_needed = true;
            clamp_x = bound_left;
        } else if (end_x != bound_right && (end_x < bound_right) == (__builtin_isnan(end_x) || __builtin_isnan(bound_right))) {
            cx_needed = false;
            clamp_x = end_x;
        } else {
            cx_needed = false;
            clamp_x = bound_right;
        }

        if (end_y < bound_bottom) {
            if (!cx_needed) {
                if (end_y - start_y == 0.0f) {
                    clamp_x = 0.0f;
                } else {
                    clamp_x = (bound_bottom - start_y) / (end_y - start_y);
                    clamp_x = start_x + (end_x - start_x) * clamp_x;
                }
            }
            clamp_y = bound_bottom;
        } else if (end_y != bound_top && (end_y < bound_top) == (__builtin_isnan(end_y) || __builtin_isnan(bound_top))) {
            clamp_y = end_y;
            if (cx_needed) {
                if (end_x - start_x == 0.0f) {
                    clamp_y = 0.0f;
                } else {
                    f32 t_val = (clamp_x - start_x) / (end_x - start_x);
                    clamp_y = start_y + (end_y - start_y) * t_val;
                }
            }
        } else {
            clamp_y = end_y;
        }

        dx = clamp_x - pos[0];
        dy = clamp_y - pos[1];
        dist_sq = dx * dx + dy * dy;
        max_dist_sq = max_dist * max_dist;
        if (dist_sq != max_dist_sq &&
            (dist_sq < max_dist_sq) == (__builtin_isnan(dist_sq) || __builtin_isnan(max_dist_sq))) {
            // Hit within range
            param_3[2] = end_z;
            param_3[3] = end_w;
            param_3[0] = clamp_x;
            param_3[1] = clamp_y;
            return 1;
        }
    } else {
        // Check if START is in bounds (and endpoint is out)
        bool start_in = false;
        if (bound_left <= start_x) {
            if (!__builtin_isnan(start_x) && !__builtin_isnan(bound_right)) {
                start_in = start_x <= bound_right;
            }
        }
        if (start_in) {
            bound_top = *(f32*)(stage + 0xc28);
            if ((start_y == bound_top || (start_y < bound_top) != (__builtin_isnan(start_y) || __builtin_isnan(bound_top)))) {
                bound_bottom = *(f32*)(stage + 0xc2c);
                if (bound_bottom <= start_y) {
                    // Start in bounds, end out — same clamping with endpoint
                    goto try_reverse;
                }
            }
        }
    }

    // Check if direction needs reflection
    abs_val = fabsf(param_4[0]);
    if (abs_val != epsilon && (abs_val < epsilon) == (__builtin_isnan(abs_val) || __builtin_isnan(epsilon))) {
        param_5[4] = param_5[2];
        param_5[5] = param_5[3];
        param_5[0] = -param_5[0];
    }
    abs_val = fabsf(param_4[1]);
    if (abs_val != epsilon && (abs_val < epsilon) == (__builtin_isnan(abs_val) || __builtin_isnan(epsilon))) {
        param_5[4] = param_5[2];
        param_5[5] = param_5[3];
        {
            u32 neg = *(u32*)(param_5 + 1) ^ 0x80000000;
            *(u32*)(param_5 + 1) = neg;
        }
    }

    // Reflect velocity
    abs_val = fabsf(vel_buf[0]);
    if (abs_val != epsilon && (abs_val < epsilon) == (__builtin_isnan(abs_val) || __builtin_isnan(epsilon))) {
        vel_buf[0] = -vel_buf[0];
    }
    abs_val = fabsf(vel_buf[1]);
    if (abs_val != epsilon && (abs_val < epsilon) == (__builtin_isnan(abs_val) || __builtin_isnan(epsilon))) {
        vel_buf[1] = -vel_buf[1];
    }

    // Second intersection test with reflected velocity
    result_pos[0] = 0.0f; result_pos[1] = 0.0f;
    result_pos[2] = 0.0f; result_pos[3] = 0.0f;
    hit = (*(u64(**)(s64*, u64*, f32*, f32*, s32))(*(s64*)ground_mod + 0x620))
          (ground_mod, (u64*)pos, vel_buf, result_pos, 0);

    if ((hit & 1) == 0) {
        end_x = pos[0] + vel_buf[0];
        end_y = pos[1] + vel_buf[1];
        end_z = pos[2] + vel_buf[2];
        end_w = pos[3] + vel_buf[3];
    } else {
        end_x = result_pos[0];
        end_y = result_pos[1];
        end_z = result_pos[2];
        end_w = result_pos[3];
    }

    stage = *(s64*)DAT_71052b7f00;
    bound_left = *(f32*)(stage + 0xc20);
    bound_right = *(f32*)(stage + 0xc24);

    // Check endpoint or start point in bounds after reflection
    {
        bool ep_ok = false;
        if (bound_left <= end_x &&
            (end_x == bound_right || (end_x < bound_right) != (__builtin_isnan(end_x) || __builtin_isnan(bound_right)))) {
            bound_top = *(f32*)(stage + 0xc28);
            if (end_y == bound_top || (end_y < bound_top) != (__builtin_isnan(end_y) || __builtin_isnan(bound_top))) {
                bound_bottom = *(f32*)(stage + 0xc2c);
                if (bound_bottom <= end_y) ep_ok = true;
            }
        }

        if (!ep_ok) {
            if (bound_left <= start_x &&
                (start_x == bound_right || (start_x < bound_right) != (__builtin_isnan(start_x) || __builtin_isnan(bound_right)))) {
                bound_top = *(f32*)(stage + 0xc28);
                bool sy_ok = (start_y == bound_top || (start_y < bound_top) != (__builtin_isnan(start_y) || __builtin_isnan(bound_top)));
                if (sy_ok) {
                    bound_bottom = *(f32*)(stage + 0xc2c);
                    if (bound_bottom <= start_y) ep_ok = true;
                }
            }
        }

        if (ep_ok) {
            bound_top = *(f32*)(stage + 0xc28);
            bound_bottom = *(f32*)(stage + 0xc2c);

            if (end_x < bound_left) {
                cx_needed = true;
                clamp_x = bound_left;
            } else if (end_x != bound_right && (end_x < bound_right) == (__builtin_isnan(end_x) || __builtin_isnan(bound_right))) {
                cx_needed = false;
                clamp_x = end_x;
            } else {
                cx_needed = false;
                clamp_x = bound_right;
            }

            if (end_y < bound_bottom) {
                if (!cx_needed) {
                    if (end_y - start_y == 0.0f) {
                        clamp_x = 0.0f;
                    } else {
                        clamp_x = (bound_bottom - start_y) / (end_y - start_y);
                        clamp_x = start_x + (end_x - start_x) * clamp_x;
                    }
                }
                clamp_y = bound_bottom;
            } else if (end_y != bound_top && (end_y < bound_top) == (__builtin_isnan(end_y) || __builtin_isnan(bound_top))) {
                clamp_y = end_y;
                if (cx_needed) {
                    if (end_x - start_x == 0.0f) {
                        clamp_y = 0.0f;
                    } else {
                        f32 t_val = (clamp_x - start_x) / (end_x - start_x);
                        clamp_y = start_y + (end_y - start_y) * t_val;
                    }
                }
            } else {
                clamp_y = end_y;
            }

            dx = clamp_x - pos[0];
            dy = clamp_y - pos[1];
            dist_sq = dx * dx + dy * dy;
            max_dist_sq = max_dist * max_dist;
            if (dist_sq != max_dist_sq &&
                (dist_sq < max_dist_sq) == (__builtin_isnan(dist_sq) || __builtin_isnan(max_dist_sq))) {
                param_3[2] = end_z;
                param_3[3] = end_w;
                param_3[0] = clamp_x;
                param_3[1] = clamp_y;
                return 1;
            }
        }
    }

try_reverse:
default_return:
    // Default return: set param_5 to default constants, return stage center
    {
        f32 c0 = *(f32*)&_DAT_7104469030;
        f32 c1 = *((f32*)&_DAT_7104469030 + 1);
        f32 p2 = param_5[2];
        f32 p3 = param_5[3];
        param_5[0] = c0;
        param_5[1] = c1;
        param_5[2] = p2;
        param_5[3] = p3;
    }

    default_pos[0] = 0;
    default_pos[1] = 0;
    got_pos = FUN_71015dc450(default_pos);
    if ((got_pos & 1) == 0) {
        stage = *(s64*)DAT_71052b7f00;
        f32 cx = *(f32*)(stage + 0xc20) +
                 (*(f32*)(stage + 0xc24) - *(f32*)(stage + 0xc20)) * 0.5f;
        f32 cy = *(f32*)(stage + 0xc28) +
                 (*(f32*)(stage + 0xc2c) - *(f32*)(stage + 0xc28)) * 0.5f;
        *(f32*)default_pos = cx;
        *((f32*)default_pos + 1) = cy;
    }

    *(u64*)(param_3 + 2) = 0;
    *(u64*)param_3 = default_pos[0];
    return 0;
}

// ════════════════════════════════════════════════════════════════════
// 0x710008b480 — UpdateParams
// Reads latest parameter values from data block and propagates to
// derived/cached fields. Serializes results to shared memory buffers.
// Size: 4,564 bytes
// ════════════════════════════════════════════════════════════════════
// param_1: pointer to param update context struct
//   +0x10: pointer to inner ParamData (the large data block)
//   +0x20: shared memory handle
//   +0x28: offset for buffer 0
//   +0x30: offset for buffer 1
//   +0x38: offset for buffer 2
//   +0x40: offset for buffer 3
//   +0x60,+0x68,+0x70: animation lookup results
//   +0x1c0..+0x238: rotation matrices
//   +0x248..+0x288: pointers to param sub-structs
//   +0x300,+0x308: additional data buffer + size
//   +0x338: extra param pointer

// External functions for UpdateParams
extern "C" s64 FUN_71000af810(s64);           // Indexed param table lookup
extern "C" void FUN_710008c660(u64*, s64);     // Compute rotation offset
extern "C" s64 FUN_710009b3f0(u64, u64);       // SearchResTexture
extern "C" s64 FUN_71000319b0(u64);            // Shared memory lock/map
extern "C" void FUN_71000319e0(u64, u64, u64);  // Shared memory write-mark
extern "C" void FUN_71000319d0(u64);            // Shared memory unlock

// .rodata table entries for enum-indexed param lookups
extern "C" __attribute__((visibility("hidden"))) u8 DAT_7104466110;
extern "C" __attribute__((visibility("hidden"))) u8 DAT_7104468260;

// .rodata sin/cos polynomial coefficients
extern "C" __attribute__((visibility("hidden"))) f32 PTR_Float1Divided2Pi_71052a3758;
extern "C" __attribute__((visibility("hidden"))) f32 PTR_Float2Pi_71052a3750;
extern "C" __attribute__((visibility("hidden"))) f32 PTR_FloatPiDivided2_71052a3760;
extern "C" __attribute__((visibility("hidden"))) f32 PTR_FloatPi_71052a3338;
extern "C" __attribute__((visibility("hidden"))) u8 PTR_SinCoefficients_71052a3740;
extern "C" __attribute__((visibility("hidden"))) u8 PTR_CosCoefficients_71052a3748;

// .rodata rotation matrix constants
extern "C" __attribute__((visibility("hidden"))) u64 DAT_7104464218;
extern "C" __attribute__((visibility("hidden"))) u64 DAT_71044645c0;
extern "C" __attribute__((visibility("hidden"))) f32 _DAT_7104465b60;
extern "C" __attribute__((visibility("hidden"))) f32 _UNK_7104465b64;
extern "C" __attribute__((visibility("hidden"))) f32 _UNK_7104465b68;
extern "C" __attribute__((visibility("hidden"))) f32 _UNK_7104465b6c;
extern "C" __attribute__((visibility("hidden"))) f32 _DAT_71044687a0;
extern "C" __attribute__((visibility("hidden"))) f32 _UNK_71044687a4;
extern "C" __attribute__((visibility("hidden"))) f32 _UNK_71044687a8;
extern "C" __attribute__((visibility("hidden"))) f32 _UNK_71044687ac;

// Jump table for type-specific param updates (14 entries)
extern "C" __attribute__((visibility("hidden"))) u8 DAT_7104473f54;

extern "C"
void FUN_710008b480(s64 param_1, u64 param_2)
{
    s64* plVar18 = (s64*)(param_1 + 0x10);
    s64 data = *plVar18;

    // ── Section 1: Animation handle lookups via FUN_71000af810 ──
    // [derived: packed 3-byte tuple at data+0x9f0..+0xa30 indexes into anim table]
    if (*(s64*)(data + 0x9f0) != -1) {
        u64 r = (u64)FUN_71000af810(data + 0x9f0);
        data = *plVar18;
        *(u64*)(param_1 + 0x60) = r;
    }
    if (*(s64*)(data + 0xa10) != -1) {
        u64 r = (u64)FUN_71000af810(data + 0xa10);
        data = *plVar18;
        *(u64*)(param_1 + 0x68) = r;
    }
    if (*(s64*)(data + 0xa30) != -1) {
        u64 r = (u64)FUN_71000af810(data + 0xa30);
        data = *plVar18;
        *(u64*)(param_1 + 0x70) = r;
    }

    // ── Section 2: Override flag checks ──
    // [derived: flag bytes at +0x99c..0x99f control whether default values are applied]
    char cVar7;

    if (*(char*)(data + 0x99c) == '\0') {
        // Copy vec3 from override source to destination
        *(u64*)(data + 0x3c0) = *(u64*)(data + 0x9a0);
        *(u32*)(data + 0x3c8) = *(u32*)(data + 0x9a8);
        data = *plVar18;
        cVar7 = *(char*)(data + 0x99e);
    } else {
        cVar7 = *(char*)(data + 0x99e);
    }

    if (cVar7 == '\0') {
        *(u32*)(data + 0x440) = *(u32*)(data + 0x9ac);
        data = *plVar18;
        cVar7 = *(char*)(data + 0x99d);
    } else {
        cVar7 = *(char*)(data + 0x99d);
    }

    if (cVar7 == '\0') {
        *(u64*)(data + 0x4c0) = *(u64*)(data + 0x9b0);
        *(u32*)(data + 0x4c8) = *(u32*)(data + 0x9b8);
        data = *plVar18;
        cVar7 = *(char*)(data + 0x99f);
    } else {
        cVar7 = *(char*)(data + 0x99f);
    }

    if (cVar7 == '\0') {
        *(u32*)(data + 0x540) = *(u32*)(data + 0x9bc);
        data = *plVar18;
        cVar7 = *(char*)(data + 0xa54);
    } else {
        cVar7 = *(char*)(data + 0xa54);
    }

    // ── Section 3: Enum-indexed table lookups ──
    // [derived: bytes at +0xa54/0xa64/0xa74 index into DAT_7104466110 and DAT_7104468260]
    if ((u64)(s64)cVar7 < 4) {
        s64 idx = (s64)cVar7 * 4;
        u32 val = *(u32*)(&DAT_7104466110 + idx);
        *(u32*)(data + 0x300) = *(u32*)(&DAT_7104468260 + idx);
        *((u32*)(*plVar18 + 0x304)) = val;
        data = *plVar18;
        cVar7 = *(char*)(data + 0xa64);
    } else {
        data = *plVar18;
        cVar7 = *(char*)(data + 0xa64);
    }

    if ((u64)(s64)cVar7 < 4) {
        s64 idx = (s64)cVar7 * 4;
        u32 val = *(u32*)(&DAT_7104466110 + idx);
        *(u32*)(data + 0x350) = *(u32*)(&DAT_7104468260 + idx);
        *(u32*)(*plVar18 + 0x354) = val;
        data = *plVar18;
        cVar7 = *(char*)(data + 0xa74);
    } else {
        data = *plVar18;
        cVar7 = *(char*)(data + 0xa74);
    }

    if ((u64)(s64)cVar7 < 4) {
        s64 idx = (s64)cVar7 * 4;
        u32 val = *(u32*)(&DAT_7104466110 + idx);
        *(u32*)(data + 0x3a0) = *(u32*)(&DAT_7104468260 + idx);
        *(u32*)(*plVar18 + 0x3a4) = val;
        data = *plVar18;
        cVar7 = *(char*)(data + 0xa51);
    } else {
        data = *plVar18;
        cVar7 = *(char*)(data + 0xa51);
    }

    // ── Section 4: Zero-fill groups ──
    // Group A: 6-u32 zero fills (offsets +0x2c0, +0x310, +0x360)
    if (cVar7 == '\0') {
        *(u32*)(data + 0x2c8) = 0; *(u32*)(*plVar18 + 0x2cc) = 0;
        *(u32*)(*plVar18 + 0x2c0) = 0; *(u32*)(*plVar18 + 0x2c4) = 0;
        *(u32*)(*plVar18 + 0x2d0) = 0; *(u32*)(*plVar18 + 0x2d4) = 0;
        data = *plVar18;
        cVar7 = *(char*)(data + 0xa61);
    } else {
        cVar7 = *(char*)(data + 0xa61);
    }

    if (cVar7 == '\0') {
        *(u32*)(data + 0x318) = 0; *(u32*)(*plVar18 + 0x31c) = 0;
        *(u32*)(*plVar18 + 0x310) = 0; *(u32*)(*plVar18 + 0x314) = 0;
        *(u32*)(*plVar18 + 800) = 0; *(u32*)(*plVar18 + 0x324) = 0;
        data = *plVar18;
        cVar7 = *(char*)(data + 0xa71);
    } else {
        cVar7 = *(char*)(data + 0xa71);
    }

    if (cVar7 == '\0') {
        *(u32*)(data + 0x368) = 0; *(u32*)(*plVar18 + 0x36c) = 0;
        *(u32*)(*plVar18 + 0x360) = 0; *(u32*)(*plVar18 + 0x364) = 0;
        *(u32*)(*plVar18 + 0x370) = 0; *(u32*)(*plVar18 + 0x374) = 0;
        data = *plVar18;
        cVar7 = *(char*)(data + 0xa52);
    } else {
        cVar7 = *(char*)(data + 0xa52);
    }

    // Group B: 3-u32 zero fills (offsets +0x2f0, +0x340, +0x390)
    if (cVar7 == '\0') {
        *(u32*)(data + 0x2f0) = 0;
        *(u32*)(*plVar18 + 0x2f4) = 0;
        *(u32*)(*plVar18 + 0x2f8) = 0;
        data = *plVar18;
        cVar7 = *(char*)(data + 0xa62);
    } else {
        cVar7 = *(char*)(data + 0xa62);
    }

    if (cVar7 == '\0') {
        *(u32*)(data + 0x340) = 0;
        *(u32*)(*plVar18 + 0x344) = 0;
        *(u32*)(*plVar18 + 0x348) = 0;
        data = *plVar18;
        cVar7 = *(char*)(data + 0xa72);
    } else {
        cVar7 = *(char*)(data + 0xa72);
    }

    if (cVar7 == '\0') {
        *(u32*)(data + 0x390) = 0;
        *(u32*)(*plVar18 + 0x394) = 0;
        *(u32*)(*plVar18 + 0x398) = 0;
        data = *plVar18;
        cVar7 = *(char*)(data + 0xa53);
    } else {
        cVar7 = *(char*)(data + 0xa53);
    }

    // Group C: scale defaults {1.0f, 1.0f, 0, 0, 0, 0} (offsets +0x2d8, +0x328, +0x378)
    if (cVar7 == '\0') {
        *(u32*)(data + 0x2e0) = 0x3f800000; // 1.0f
        *(u32*)(*plVar18 + 0x2e4) = 0x3f800000;
        *(u32*)(*plVar18 + 0x2d8) = 0;
        *(u32*)(*plVar18 + 0x2dc) = 0;
        *(u32*)(*plVar18 + 0x2e8) = 0;
        *(u32*)(*plVar18 + 0x2ec) = 0;
        data = *plVar18;
        cVar7 = *(char*)(data + 0xa63);
    } else {
        cVar7 = *(char*)(data + 0xa63);
    }

    if (cVar7 == '\0') {
        *(u32*)(data + 0x330) = 0x3f800000;
        *(u32*)(*plVar18 + 0x334) = 0x3f800000;
        *(u32*)(*plVar18 + 0x328) = 0;
        *(u32*)(*plVar18 + 0x32c) = 0;
        *(u32*)(*plVar18 + 0x338) = 0;
        *(u32*)(*plVar18 + 0x33c) = 0;
        data = *plVar18;
        cVar7 = *(char*)(data + 0xa73);
    } else {
        cVar7 = *(char*)(data + 0xa73);
    }

    if (cVar7 == '\0') {
        *(u32*)(data + 0x380) = 0x3f800000;
        *(u32*)(*plVar18 + 900) = 0x3f800000;
        *(u32*)(*plVar18 + 0x378) = 0;
        *(u32*)(*plVar18 + 0x37c) = 0;
        *(u32*)(*plVar18 + 0x388) = 0;
        *(u32*)(*plVar18 + 0x38c) = 0;
        data = *plVar18;
        cVar7 = *(char*)(data + 0x8b0);
    } else {
        cVar7 = *(char*)(data + 0x8b0);
    }

    // ── Section 5: Stride-16 zero fills for rendering slots ──
    if (cVar7 == '\0') {
        *(u32*)(data + 0x700) = 0; *(u32*)(*plVar18 + 0x710) = 0;
        *(u32*)(*plVar18 + 0x720) = 0; *(u32*)(*plVar18 + 0x730) = 0;
        data = *plVar18;
        cVar7 = *(char*)(data + 0x8b1);
    } else {
        cVar7 = *(char*)(data + 0x8b1);
    }

    if (cVar7 == '\0') {
        *(u32*)(data + 0x704) = 0; *(u32*)(*plVar18 + 0x714) = 0;
        *(u32*)(*plVar18 + 0x724) = 0; *(u32*)(*plVar18 + 0x734) = 0;
        data = *plVar18;
        cVar7 = *(char*)(data + 0x8b2);
    } else {
        cVar7 = *(char*)(data + 0x8b2);
    }

    if (cVar7 == '\0') {
        *(u32*)(data + 0x708) = 0; *(u32*)(*plVar18 + 0x718) = 0;
        *(u32*)(*plVar18 + 0x728) = 0; *(u32*)(*plVar18 + 0x738) = 0;
        data = *plVar18;
        cVar7 = *(char*)(data + 0xa50);
    } else {
        cVar7 = *(char*)(data + 0xa50);
    }

    // ── Section 6: Resource texture lookups ──
    // [derived: SearchResTexture converts resource handle to float size]
    if (cVar7 == '\x05') {
        s64 res = FUN_710009b3f0(param_2, *(u64*)(data + 0x9f0));
        if (res != 0) {
            *(f32*)(*plVar18 + 0x110) = (f32)*(s32*)(res + 0x30);
        }
        data = *plVar18;
        cVar7 = *(char*)(data + 0xa60);
    } else {
        data = *plVar18;
        cVar7 = *(char*)(data + 0xa60);
    }

    if (cVar7 == '\x05') {
        s64 res = FUN_710009b3f0(param_2, *(u64*)(data + 0xa10));
        if (res != 0) {
            *(f32*)(*plVar18 + 0x1a0) = (f32)*(s32*)(res + 0x30);
        }
    }

    if (*(char*)(*plVar18 + 0xa70) == '\x05') {
        s64 res = FUN_710009b3f0(param_2, *(u64*)(*plVar18 + 0xa30));
        if (res != 0) {
            *(f32*)(*plVar18 + 0x230) = (f32)*(s32*)(res + 0x30);
        }
    }

    // ── Section 7: Slot copy loops ──
    // [derived: 6 groups of animation slot data, each indexed by field at +0x60..+0x74]
    // Each slot: if (index-1 < 7), copy src→dst with float accumulation
    // Pattern: copy 16 bytes from base+index*16+src_off to base+index*16+dst_off
    //          then fill remaining slots up to 7 with accumulated float values
    data = *plVar18;
    s32 slot_idx;
    s64 slot_off;

    // Slot group 0 (src: +0x3b0, dst: +0x3c0, index at +0x60)
    slot_idx = *(s32*)(data + 0x60);
    if ((u32)(slot_idx - 1) < 7) {
        slot_off = (s64)slot_idx * 0x10;
        s64 base = data + slot_off;
        *(u64*)(base + 0x3c8) = *(u64*)(base + 0x3b8);
        *(u64*)(base + 0x3c0) = *(u64*)(base + 0x3b0);
        *(f32*)(*plVar18 + slot_off + 0x3cc) = *(f32*)(*plVar18 + slot_off + 0x3cc) + (f32)slot_idx;
        if (slot_idx < 7) {
            s64 i = (s64)slot_idx - 1;
            s64 off = slot_off + 0x3dc;
            do {
                slot_idx++;
                s64 d = *plVar18;
                s64 src_base = d + (s64)*(s32*)(d + 0x60) * 0x10;
                u64 v = *(u64*)(src_base + 0x3b0);
                *(u64*)(d + off - 4) = *(u64*)(src_base + 0x3b8);
                *(u64*)(d + off - 0xc) = v;
                i++;
                *(f32*)(*plVar18 + off) = *(f32*)(*plVar18 + off) + (f32)slot_idx;
                off += 0x10;
            } while (i < 6);
        }
        data = *plVar18;
        slot_idx = *(s32*)(data + 0x68);
    } else {
        slot_idx = *(s32*)(data + 0x68);
    }

    // Slot group 1 (src: +0x4b0, dst: +0x4c0, index at +0x68)
    if ((u32)(slot_idx - 1) < 7) {
        slot_off = (s64)slot_idx * 0x10;
        s64 base = data + slot_off;
        *(u64*)(base + 0x4c8) = *(u64*)(base + 0x4b8);
        *(u64*)(base + 0x4c0) = *(u64*)(base + 0x4b0);
        *(f32*)(*plVar18 + slot_off + 0x4cc) = *(f32*)(*plVar18 + slot_off + 0x4cc) + (f32)slot_idx;
        if (slot_idx < 7) {
            s64 i = (s64)slot_idx - 1;
            s64 off = slot_off + 0x4dc;
            do {
                slot_idx++;
                s64 d = *plVar18;
                s64 src_base = d + (s64)*(s32*)(d + 0x68) * 0x10;
                u64 v = *(u64*)(src_base + 0x4b0);
                *(u64*)(d + off - 4) = *(u64*)(src_base + 0x4b8);
                *(u64*)(d + off - 0xc) = v;
                i++;
                *(f32*)(*plVar18 + off) = *(f32*)(*plVar18 + off) + (f32)slot_idx;
                off += 0x10;
            } while (i < 6);
        }
        data = *plVar18;
        slot_idx = *(s32*)(data + 100);
    } else {
        slot_idx = *(s32*)(data + 100);
    }

    // Slot groups 2-5 follow the same pattern at offsets:
    // Group 2: src=+0x430, dst=+0x440, idx=+0x64
    // Group 3: src=+0x530, dst=+0x540, idx=+0x6c
    // Group 4: src=+0x5f0, dst=+0x600, idx=+0x70
    // Group 5: src=+0x670, dst=+0x680, idx=+0x74

    // Group 2
    if ((u32)(slot_idx - 1) < 7) {
        slot_off = (s64)slot_idx * 0x10;
        s64 base = data + slot_off;
        *(u64*)(base + 0x448) = *(u64*)(base + 0x438);
        *(u64*)(base + 0x440) = *(u64*)(base + 0x430);
        *(f32*)(*plVar18 + slot_off + 0x44c) = *(f32*)(*plVar18 + slot_off + 0x44c) + (f32)slot_idx;
        if (slot_idx < 7) {
            s64 i = (s64)slot_idx - 1;
            s64 off = slot_off + 0x45c;
            do {
                slot_idx++;
                s64 d = *plVar18;
                s64 src_base = d + (s64)*(s32*)(d + 100) * 0x10;
                u64 v = *(u64*)(src_base + 0x430);
                *(u64*)(d + off - 4) = *(u64*)(src_base + 0x438);
                *(u64*)(d + off - 0xc) = v;
                i++;
                *(f32*)(*plVar18 + off) = *(f32*)(*plVar18 + off) + (f32)slot_idx;
                off += 0x10;
            } while (i < 6);
        }
        data = *plVar18;
        slot_idx = *(s32*)(data + 0x6c);
    } else {
        slot_idx = *(s32*)(data + 0x6c);
    }

    // Group 3
    if ((u32)(slot_idx - 1) < 7) {
        slot_off = (s64)slot_idx * 0x10;
        s64 base = data + slot_off;
        *(u64*)(base + 0x548) = *(u64*)(base + 0x538);
        *(u64*)(base + 0x540) = *(u64*)(base + 0x530);
        *(f32*)(*plVar18 + slot_off + 0x54c) = *(f32*)(*plVar18 + slot_off + 0x54c) + (f32)slot_idx;
        if (slot_idx < 7) {
            s64 i = (s64)slot_idx - 1;
            s64 off = slot_off + 0x55c;
            do {
                slot_idx++;
                s64 d = *plVar18;
                s64 src_base = d + (s64)*(s32*)(d + 0x6c) * 0x10;
                u64 v = *(u64*)(src_base + 0x530);
                *(u64*)(d + off - 4) = *(u64*)(src_base + 0x538);
                *(u64*)(d + off - 0xc) = v;
                i++;
                *(f32*)(*plVar18 + off) = *(f32*)(*plVar18 + off) + (f32)slot_idx;
                off += 0x10;
            } while (i < 6);
        }
        data = *plVar18;
        slot_idx = *(s32*)(data + 0x70);
    } else {
        slot_idx = *(s32*)(data + 0x70);
    }

    // Group 4
    if ((u32)(slot_idx - 1) < 7) {
        slot_off = (s64)slot_idx * 0x10;
        s64 base = data + slot_off;
        *(u64*)(base + 0x608) = *(u64*)(base + 0x5f8);
        *(u64*)(base + 0x600) = *(u64*)(base + 0x5f0);
        *(f32*)(*plVar18 + slot_off + 0x60c) = *(f32*)(*plVar18 + slot_off + 0x60c) + (f32)slot_idx;
        if (slot_idx < 7) {
            s64 i = (s64)slot_idx - 1;
            s64 off = slot_off + 0x61c;
            do {
                slot_idx++;
                s64 d = *plVar18;
                s64 src_base = d + (s64)*(s32*)(d + 0x70) * 0x10;
                u64 v = *(u64*)(src_base + 0x5f0);
                *(u64*)(d + off - 4) = *(u64*)(src_base + 0x5f8);
                *(u64*)(d + off - 0xc) = v;
                i++;
                *(f32*)(*plVar18 + off) = *(f32*)(*plVar18 + off) + (f32)slot_idx;
                off += 0x10;
            } while (i < 6);
        }
        data = *plVar18;
        slot_idx = *(s32*)(data + 0x74);
    } else {
        slot_idx = *(s32*)(data + 0x74);
    }

    // Group 5
    if ((u32)(slot_idx - 1) < 7) {
        slot_off = (s64)slot_idx * 0x10;
        s64 base = data + slot_off;
        *(u64*)(base + 0x688) = *(u64*)(base + 0x678);
        *(u64*)(base + 0x680) = *(u64*)(base + 0x670);
        *(f32*)(*plVar18 + slot_off + 0x68c) = *(f32*)(*plVar18 + slot_off + 0x68c) + (f32)slot_idx;
        if (slot_idx < 7) {
            s64 i = (s64)slot_idx - 1;
            s64 off = slot_off + 0x69c;
            do {
                slot_idx++;
                s64 d = *plVar18;
                s64 src_base = d + (s64)*(s32*)(d + 0x74) * 0x10;
                u64 v = *(u64*)(src_base + 0x670);
                *(u64*)(d + off - 4) = *(u64*)(src_base + 0x678);
                *(u64*)(d + off - 0xc) = v;
                i++;
                *(f32*)(*plVar18 + off) = *(f32*)(*plVar18 + off) + (f32)slot_idx;
                off += 0x10;
            } while (i < 6);
        }
        data = *plVar18;
        cVar7 = *(char*)(data + 0x8d8);
    } else {
        cVar7 = *(char*)(data + 0x8d8);
    }

    // ── Section 8: Float from int conversions ──
    // [derived: 5 pairs of (flag byte, int value) → (float dest, enable dest)]
    f32 fVal = 0.0f;
    if (cVar7 != '\0') {
        fVal = (f32)*(s32*)(data + 0x8e4);
    }
    *(f32*)(data + 0x80) = fVal;

    u32 enable = 0;
    if (*(char*)(*plVar18 + 0x8dd) != '\0') enable = 0x3f800000; // 1.0f
    *(u32*)(*plVar18 + 0x94) = enable;

    data = *plVar18;
    fVal = 0.0f;
    if (*(char*)(data + 0x8d9) != '\0') fVal = (f32)*(s32*)(data + 0x8e8);
    *(f32*)(data + 0x84) = fVal;

    enable = 0;
    if (*(char*)(*plVar18 + 0x8de) != '\0') enable = 0x3f800000;
    *(u32*)(*plVar18 + 0x98) = enable;

    data = *plVar18;
    fVal = 0.0f;
    if (*(char*)(data + 0x8da) != '\0') fVal = (f32)*(s32*)(data + 0x8ec);
    *(f32*)(data + 0x88) = fVal;

    enable = 0;
    if (*(char*)(*plVar18 + 0x8df) != '\0') enable = 0x3f800000;
    *(u32*)(*plVar18 + 0x9c) = enable;

    data = *plVar18;
    fVal = 0.0f;
    if (*(char*)(data + 0x8db) != '\0') fVal = (f32)*(s32*)(data + 0x8f0);
    *(f32*)(data + 0x8c) = fVal;

    enable = 0;
    if (*(char*)(*plVar18 + 0x8e0) != '\0') enable = 0x3f800000;
    *(u32*)(*plVar18 + 0xa0) = enable;

    data = *plVar18;
    f32 fVal2 = 0.0f;
    if (*(char*)(data + 0x8dc) != '\0') fVal2 = (f32)*(s32*)(data + 0x8f4);
    *(f32*)(data + 0x90) = fVal2;

    enable = 0;
    if (*(char*)(*plVar18 + 0x8e1) != '\0') enable = 0x3f800000;
    *(u32*)(*plVar18 + 0xa4) = enable;

    // ── Section 9: Bitmask check + type dispatch ──
    // [derived: byte at +0x838 is a type enum; bitmask 0xa064 marks valid types]
    u8 type_byte = *(u8*)(*plVar18 + 0x838);
    u32 type_val = (u32)type_byte;
    if (type_byte > 0xf || ((1u << (type_val & 0x1f)) & 0xa064u) == 0) {
        *(u32*)(*plVar18 + 0x874) = 0xffffffff;
        type_val = (u32)*(u8*)(*plVar18 + 0x838);
    }

    if (type_val - 2 > 0xd) {
        // Default path: compute rotation matrix and serialize to shared memory
        // [NOTE: This contains complex NEON sin/cos polynomial computation and
        //  memcpy to shared memory buffers. Full implementation requires NEON
        //  intrinsics and is deferred to matching iteration.]

        u64 local_28 = 0;
        FUN_710008c660(&local_28, param_1);
        *(u32*)(*(s64*)(param_1 + 0x10) + 0x50) = (u32)local_28;
        *(u32*)(*(s64*)(param_1 + 0x10) + 0x54) = (u32)(local_28 >> 32);

        if (*(u32**)(param_1 + 0x288) != nullptr) {
            *(u32*)(*plVar18 + 0x5c) = **(u32**)(param_1 + 0x288);
        }

        // TODO: Rotation matrix computation (NEON sin/cos polynomial)
        // and memcpy to shared memory buffers. Requires NEON intrinsics
        // for byte-matching. Skipped for now.

        s64 lVar11 = *(s64*)(param_1 + 0x10);
        // ... rotation matrix from euler angles at lVar11 + 0x788 ...
        // ... writes to param_1 + 0x1c0..0x238 (two 4x4 submatrices) ...
        // ... writes to param_1 + 0x320..0x328 ...

        // Serialize ParamData to shared memory buffer 0
        s64 shmem_base = FUN_71000319b0(*(u64*)(param_1 + 0x20));
        void* dest = (void*)(shmem_base + *(s64*)(param_1 + 0x28));
        if (dest != nullptr) {
            memcpy(dest, *(void**)(param_1 + 0x10), 0x750);
            u64 handle = *(u64*)(param_1 + 0x20);
            FUN_71000319e0(handle, *(u64*)(param_1 + 0x28), 0x750);
            FUN_71000319d0(handle);
        }

        // Serialize extra data to shared memory buffer 1
        if (*(s64*)(param_1 + 0x338) != 0) {
            s64 off1 = *(s64*)(param_1 + 0x30);
            shmem_base = FUN_71000319b0(*(u64*)(param_1 + 0x20));
            u64* dest2 = (u64*)(shmem_base + off1);
            if (dest2 != nullptr) {
                u64* src = *(u64**)(param_1 + 0x338);
                // Copy 128 bytes (16 u64s) — likely a 4x4 matrix
                dest2[0] = src[0]; dest2[1] = src[1];
                dest2[2] = src[2]; dest2[3] = src[3];
                dest2[4] = src[4]; dest2[5] = src[5];
                dest2[6] = src[6]; dest2[7] = src[7];
                dest2[8] = src[8]; dest2[9] = src[9];
                dest2[10] = src[10]; dest2[11] = src[11];
                dest2[12] = src[12]; dest2[13] = src[13];
                dest2[14] = src[14]; dest2[15] = src[15];
                u64 handle = *(u64*)(param_1 + 0x20);
                FUN_71000319e0(handle, *(u64*)(param_1 + 0x30), 0x80);
                FUN_71000319d0(handle);
            }
        }

        // Serialize variable-length data to shared memory buffer 2
        if (*(s64*)(param_1 + 0x300) != 0) {
            s64 off2 = *(s64*)(param_1 + 0x38);
            shmem_base = FUN_71000319b0(*(u64*)(param_1 + 0x20));
            void* dest3 = (void*)(shmem_base + off2);
            if (dest3 != nullptr) {
                memcpy(dest3, *(void**)(param_1 + 0x300), *(u64*)(param_1 + 0x308));
                u64 handle = *(u64*)(param_1 + 0x20);
                FUN_71000319e0(handle, *(u64*)(param_1 + 0x38), *(u64*)(param_1 + 0x308));
                FUN_71000319d0(handle);
            }
        }

        // Serialize rendering params to shared memory buffer 3
        if (*(char*)(param_1 + 3) != '\0') {
            s64 off3 = *(s64*)(param_1 + 0x40);
            shmem_base = FUN_71000319b0(*(u64*)(param_1 + 0x20));
            u32* dest4 = (u32*)(shmem_base + off3);
            if (dest4 != nullptr) {
                // Copy from multiple param sub-struct pointers
                // param_1+0x248: material colors
                // param_1+0x250: specular params
                // param_1+0x258..0x288: additional rendering parameters
                s64 p248 = *(s64*)(param_1 + 0x248);
                if (p248 != 0) {
                    dest4[0] = *(u32*)(p248 + 4);
                    dest4[1] = *(u32*)(p248 + 8);
                    dest4[2] = *(u32*)(p248 + 0xc);
                    dest4[3] = (f32)*(s32*)(p248 + 0x10);
                    // More fields from p248...
                }
                // ... more sub-struct copies omitted for brevity ...

                u64 handle = *(u64*)(param_1 + 0x20);
                FUN_71000319e0(handle, *(u64*)(param_1 + 0x40), 0x120);
                FUN_71000319d0(handle);
            }
        }
        return;
    }

    // Type-specific dispatch via jump table (types 2-15)
    // [NOTE: Ghidra could not recover jump table at 0x710008bb1c]
    // Each case handles a specific rendering/param type.
    // TODO: Analyze assembly to recover jump table targets.
    (*(void(*)())(&DAT_7104473f54 + *(s32*)(&DAT_7104473f54 + (u64)(type_val - 2) * 4)))();
}

// ════════════════════════════════════════════════════════════════════
// 0x71032ed9c0 — populate_parameters_for_hash40
// Populates a parameter struct from PRC (param resource config) data
// by looking up param_2's hash40 in the PRC tree and reading ~15
// named parameters via binary search.
// Size: 13,536 bytes (0x34E0)
// ════════════════════════════════════════════════════════════════════
// param_1: output parameter struct (at least 0x1A0 bytes, addressed as u32*)
// param_2: hash40 key (40-bit hash in low bits, type tag in bits 56-63,
//          index in bits 40-55)

// PRC database root
extern "C" s64 DAT_710532e730;
// Team param default value
extern "C" u32 DAT_7105306b6c;
// Default/sentinel byte for failed PRC searches
extern "C" u8 DAT_7104741dbb;
// CRC32 lookup table (256 entries × 4 bytes)
extern "C" u8 DAT_7104753084;

// PRC tree navigation
// [derived: fast index lookup — uses bits 40-55 of hash40 as direct index]
extern "C" u64 FUN_7103269900(s64 node, u64 index);
// [derived: slow hash lookup — binary search by full 40-bit hash]
extern "C" u32 FUN_7103269fd0(s64 node, u64 hash40);
// [derived: resolve child node by index, fills {u32 lo, u32 hi, char* data}]
extern "C" void FUN_7103269e30(void* out, s64 node, u32 index);

// String parameter extractors (each fills a {u32 lo, u32 hi, char* data} struct)
extern "C" void FUN_7103290db0(void* out, u64 prc_tree, u64 param_hash);
extern "C" void FUN_7103291140(void* out, u64 prc_tree, u64 param_hash);
extern "C" void FUN_71032914d0(void* out, u64 prc_tree, u64 param_hash);
extern "C" void FUN_7103291860(void* out, u64 prc_tree, u64 param_hash);

// Auxiliary path data extractor
extern "C" void FUN_7103291bf0(void* out, s64 prc_tree, u64 param_hash);

// Path/mode helpers
extern "C" s32 FUN_7103238e80(void);
extern "C" void FUN_7103239370(void* out, s32 mode, bool flag);
extern "C" void FUN_7103239770(void* out, const char* fmt, char* str);
extern "C" u64 FUN_7103238300(u64 hash, s32 mode, s32 param);

// ── PRC integer decode helper ───────────────────────────────────
// [derived: PRC stores integers with type tag at byte 0]
// Type tags: \x01/\x03 = u8, \x02 = s8, \x04 = s16, \x05 = u16, \x06/\x07 = u32
static inline u32 prc_read_int(const char* data) {
    switch (*data) {
    case '\x01':
    case '\x03':
        return (u32)(u8)data[1];
    case '\x02':
        return (u32)(s8)data[1];
    case '\x04':
        return (u32)*(s16*)(data + 1);
    case '\x05':
        return (u32)*(u16*)(data + 1);
    case '\x06':
    case '\x07':
        return *(u32*)(data + 1);
    default:
        return 0;
    }
}

extern "C"
void populate_parameters_for_hash40(u32* param_1, u64 param_2)
{
    u32* puVar1;
    u32* puVar2;
    s32 iVar3;
    char cVar5;
    bool bVar7;
    bool bVar8;
    bool bVar9;
    u32 uVar10;
    s32 iVar11;
    u32 uVar12;
    u32* puVar13;
    u8* pbVar14;
    u32 uVar15;
    u64 uVar16;
    s32 iVar17;
    s32 iVar18;
    u64 uVar20;
    u64 uVar21;
    u64 uVar22;
    u32* puVar24;
    s64 lVar25;
    u32* puVar26;
    s64 lVar27;
    u32* puVar28;
    s64 lVar29;
    char* pcVar30;

    // Stack locals matching Ghidra layout
    u32 local_208;
    u32 uStack_204;
    char* local_200;   // undefined8 in Ghidra, used as char*

    u8 auStack_f8[8];
    char auStack_f0[64];
    u8 auStack_b0[4];
    s32 local_ac;

    // ── Initialize output struct ──────────────────────────────────
    *(u8*)(param_1 + 4) = 1;
    param_1[0] = 0;
    param_1[1] = 0;
    param_1[2] = 0;
    param_1[3] = 0;
    puVar24 = param_1 + 5;
    puVar24[0] = 0;
    puVar24[1] = 0;
    puVar28 = param_1 + 0x19;
    puVar28[0] = 0;
    puVar28[1] = 0;
    *(u8*)(param_1 + 0x1b) = 0;
    *(u8*)(param_1 + 0x2d) = 0;
    puVar13 = param_1 + 0x2b;
    puVar13[0] = 0;
    puVar13[1] = 0;
    puVar26 = param_1 + 0x3d;
    puVar26[0] = 0;
    puVar26[1] = 0;
    *(u64*)(param_1 + 0x52) = *(u64*)(param_1 + 0x50);
    *(u8*)(param_1 + 0x3f) = 0;
    param_1[0x56] = 0;
    param_1[0x57] = 1;
    *(u8*)(param_1 + 9) = 0;
    param_1[7] = 0;
    param_1[8] = 0;

    // ── Static init guard (team params) ───────────────────────────
    ensure_team_param_init();

    param_1[0x57] = DAT_7105306b6c;
    param_1[0x58] = 1;
    param_1[0x5b] = 0;
    param_1[0x5c] = 0;
    puVar2 = param_1 + 0x59;
    *(u16*)(param_1 + 0x5d) = 0;
    puVar2[0] = 0;
    puVar2[1] = 0;

    // Extract hash40 components
    uVar16 = param_2 & 0xFFFFFFFFFFULL;
    bVar7 = (param_2 & 0xFFFFFFFFFFULL) != 0;
    param_1[0x66] = 0;
    param_1[0x67] = 0x58ffff00;
    lVar29 = *(s64*)(DAT_710532e730 + 8);
    bVar8 = param_2 >> 0x38 == 0x58;

    // ══════════════════════════════════════════════════════════════
    // Block 1: param_1[0] — item type enum (hash 0x533bdb86a)
    // ══════════════════════════════════════════════════════════════
    if (bVar8 && bVar7) {
        lVar25 = *(s64*)(*(s64*)(lVar29 + 0x1c8) + 8);
        pcVar30 = *(char**)(lVar25 + 0x20);
        cVar5 = *pcVar30;
        if ((cVar5 == '\f') && (iVar11 = *(s32*)(pcVar30 + 1) + -1, 0 < *(s32*)(pcVar30 + 1))) {
            uVar20 = *(u64*)(lVar25 + 0x48) & 0xFFFFFFFFFFULL;
            iVar17 = 0;
            pbVar14 = &DAT_7104741dbb;
            do {
                iVar18 = iVar11 + iVar17;
                if (iVar18 < 0) iVar18 = iVar18 + 1;
                iVar18 = iVar18 >> 1;
                puVar1 = (u32*)(*(s64*)(*(s64*)(lVar25 + 0x18) + 0x28) + (s64)*(s32*)(pcVar30 + 5) + (s64)iVar18 * 8);
                uVar21 = *(u64*)(*(s64*)(*(s64*)(lVar25 + 0x18) + 0x20) + (u64)*puVar1 * 8);
                if (uVar21 == uVar20) {
                    uVar12 = puVar1[1];
                    if ((s32)uVar12 < 0) goto block1_fallback;
                    pbVar14 = (u8*)(pcVar30 + (s32)uVar12);
                    break;
                }
                iVar3 = iVar18 + -1;
                if (uVar21 <= uVar20) { iVar17 = iVar18 + 1; iVar3 = iVar11; }
                iVar11 = iVar3;
            } while (iVar17 <= iVar11);
        } else {
        block1_fallback:
            pbVar14 = &DAT_7104741dbb;
        }
        if (*pbVar14 - 0xb < 2) {
            uVar20 = param_2 >> 0x28 & 0xffff;
            uVar10 = (u32)uVar20;
            if ((*(u32*)(pbVar14 + 1) <= uVar10) ||
                (uVar20 = FUN_7103269900(lVar25, uVar20), ((uVar20 ^ param_2) & 0xFFFFFFFFFFULL) != 0))
                goto block1_slow;
        } else {
        block1_slow:
            uVar10 = FUN_7103269fd0(lVar25, uVar16);
        }
        uVar12 = uVar10;
        if (cVar5 != '\f') goto block1_sentinel;
    block1_search2:
        uVar10 = uVar12;
        iVar11 = *(s32*)(pcVar30 + 1) + -1;
        if (*(s32*)(pcVar30 + 1) < 1) goto block1_sentinel;
        uVar20 = *(u64*)(lVar25 + 0x48) & 0xFFFFFFFFFFULL;
        iVar17 = 0;
        pbVar14 = &DAT_7104741dbb;
        do {
            iVar18 = iVar11 + iVar17;
            if (iVar18 < 0) iVar18 = iVar18 + 1;
            iVar18 = iVar18 >> 1;
            puVar1 = (u32*)(*(s64*)(*(s64*)(lVar25 + 0x18) + 0x28) + (s64)*(s32*)(pcVar30 + 5) + (s64)iVar18 * 8);
            uVar21 = *(u64*)(*(s64*)(*(s64*)(lVar25 + 0x18) + 0x20) + (u64)*puVar1 * 8);
            if (uVar21 == uVar20) {
                uVar12 = puVar1[1];
                if ((s32)uVar12 < 0) goto block1_sentinel;
                pbVar14 = (u8*)(pcVar30 + (s32)uVar12);
                break;
            }
            iVar3 = iVar18 + -1;
            if (uVar21 <= uVar20) { iVar17 = iVar18 + 1; iVar3 = iVar11; }
            iVar11 = iVar3;
        } while (iVar17 <= iVar11);
    } else {
        lVar25 = *(s64*)(*(s64*)(lVar29 + 0x1c8) + 8);
        pcVar30 = *(char**)(lVar25 + 0x20);
        uVar10 = 0xffffffff;
        uVar12 = 0xffffffff;
        if (*pcVar30 == '\f') goto block1_search2;
    block1_sentinel:
        pbVar14 = &DAT_7104741dbb;
    }
    if ((*pbVar14 - 0xb < 2) && (uVar10 < *(u32*)(pbVar14 + 1))) {
        FUN_7103269e30(&local_208, lVar25, uVar10);
        if ((*local_200 == '\f') && (iVar11 = *(s32*)(local_200 + 1) + -1, 0 < *(s32*)(local_200 + 1))) {
            lVar25 = ((s64)uStack_204 << 32) | local_208;
            iVar17 = 0;
            pcVar30 = "";
            do {
                iVar18 = iVar11 + iVar17;
                if (iVar18 < 0) iVar18 = iVar18 + 1;
                iVar18 = iVar18 >> 1;
                puVar1 = (u32*)(*(s64*)(lVar25 + 0x28) + (s64)*(s32*)(local_200 + 5) + (s64)iVar18 * 8);
                uVar20 = *(u64*)(*(s64*)(lVar25 + 0x20) + (u64)*puVar1 * 8);
                if (uVar20 == 0x533bdb86aULL) {
                    uVar12 = puVar1[1];
                    if ((s32)uVar12 < 0) goto block1_inner_fail;
                    pcVar30 = local_200 + (s32)uVar12;
                    goto block1_inner_done;
                }
                iVar3 = iVar18 + -1;
                if (uVar20 < 0x533bdb86bULL) { iVar17 = iVar18 + 1; iVar3 = iVar11; }
                iVar11 = iVar3;
            } while (iVar17 <= iVar11);
            lVar25 = 0;
        } else {
        block1_inner_fail:
            lVar25 = 0;
            pcVar30 = "";
        }
    block1_inner_done:
        if (*pcVar30 != '\t') goto block1_default;
        uVar20 = *(u64*)(*(s64*)(lVar25 + 0x20) + (s64)*(s32*)(pcVar30 + 1) * 8) & 0xFFFFFFFFFFULL;
        if (uVar20 < 0xd90e74a8bULL) {
            if (uVar20 == 0xd16733825ULL) { uVar12 = 2; }
            else if (uVar20 == 0xd4de6005aULL) { uVar12 = 6; }
            else { if (uVar20 != 0xd86bad3ffULL) goto block1_default; uVar12 = 7; }
        } else if (uVar20 < 0xddd2feb80ULL) {
            if (uVar20 == 0xd90e74a8bULL) { uVar12 = 1; }
            else { if (uVar20 != 0xdcb7272f4ULL) goto block1_default; uVar12 = 5; }
        } else if (uVar20 == 0xddd2feb80ULL) { uVar12 = 3; }
        else { if (uVar20 != 0xec89fb9b0ULL) goto block1_default; uVar12 = 4; }
    } else {
    block1_default:
        uVar12 = 0;
    }
    *param_1 = uVar12;

    // ══════════════════════════════════════════════════════════════
    // Block 2: param_1[1] — result type enum (hash 0x7b816b0fe)
    // ══════════════════════════════════════════════════════════════
    if (bVar8 && bVar7) {
        lVar25 = *(s64*)(*(s64*)(lVar29 + 0x1c8) + 8);
        pcVar30 = *(char**)(lVar25 + 0x20);
        cVar5 = *pcVar30;
        if ((cVar5 == '\f') && (iVar11 = *(s32*)(pcVar30 + 1) + -1, 0 < *(s32*)(pcVar30 + 1))) {
            uVar20 = *(u64*)(lVar25 + 0x48) & 0xFFFFFFFFFFULL;
            iVar17 = 0;
            pbVar14 = &DAT_7104741dbb;
            do {
                iVar18 = iVar11 + iVar17;
                if (iVar18 < 0) iVar18 = iVar18 + 1;
                iVar18 = iVar18 >> 1;
                puVar1 = (u32*)(*(s64*)(*(s64*)(lVar25 + 0x18) + 0x28) + (s64)*(s32*)(pcVar30 + 5) + (s64)iVar18 * 8);
                uVar21 = *(u64*)(*(s64*)(*(s64*)(lVar25 + 0x18) + 0x20) + (u64)*puVar1 * 8);
                if (uVar21 == uVar20) {
                    uVar12 = puVar1[1];
                    if ((s32)uVar12 < 0) goto block2_fallback;
                    pbVar14 = (u8*)(pcVar30 + (s32)uVar12);
                    break;
                }
                iVar3 = iVar18 + -1;
                if (uVar21 <= uVar20) { iVar17 = iVar18 + 1; iVar3 = iVar11; }
                iVar11 = iVar3;
            } while (iVar17 <= iVar11);
        } else {
        block2_fallback:
            pbVar14 = &DAT_7104741dbb;
        }
        if (*pbVar14 - 0xb < 2) {
            uVar20 = param_2 >> 0x28 & 0xffff;
            uVar10 = (u32)uVar20;
            if ((*(u32*)(pbVar14 + 1) <= uVar10) ||
                (uVar20 = FUN_7103269900(lVar25, uVar20), ((uVar20 ^ param_2) & 0xFFFFFFFFFFULL) != 0))
                goto block2_slow;
        } else {
        block2_slow:
            uVar10 = FUN_7103269fd0(lVar25, uVar16);
        }
        uVar12 = uVar10;
        if (cVar5 != '\f') goto block2_sentinel;
    block2_search2:
        uVar10 = uVar12;
        iVar11 = *(s32*)(pcVar30 + 1) + -1;
        if (*(s32*)(pcVar30 + 1) < 1) goto block2_sentinel;
        uVar20 = *(u64*)(lVar25 + 0x48) & 0xFFFFFFFFFFULL;
        iVar17 = 0;
        pbVar14 = &DAT_7104741dbb;
        do {
            iVar18 = iVar11 + iVar17;
            if (iVar18 < 0) iVar18 = iVar18 + 1;
            iVar18 = iVar18 >> 1;
            puVar1 = (u32*)(*(s64*)(*(s64*)(lVar25 + 0x18) + 0x28) + (s64)*(s32*)(pcVar30 + 5) + (s64)iVar18 * 8);
            uVar21 = *(u64*)(*(s64*)(*(s64*)(lVar25 + 0x18) + 0x20) + (u64)*puVar1 * 8);
            if (uVar21 == uVar20) {
                uVar12 = puVar1[1];
                if ((s32)uVar12 < 0) goto block2_sentinel;
                pbVar14 = (u8*)(pcVar30 + (s32)uVar12);
                break;
            }
            iVar3 = iVar18 + -1;
            if (uVar21 <= uVar20) { iVar17 = iVar18 + 1; iVar3 = iVar11; }
            iVar11 = iVar3;
        } while (iVar17 <= iVar11);
    } else {
        lVar25 = *(s64*)(*(s64*)(lVar29 + 0x1c8) + 8);
        pcVar30 = *(char**)(lVar25 + 0x20);
        uVar10 = 0xffffffff;
        uVar12 = 0xffffffff;
        if (*pcVar30 == '\f') goto block2_search2;
    block2_sentinel:
        pbVar14 = &DAT_7104741dbb;
    }
    if ((*pbVar14 - 0xb < 2) && (uVar10 < *(u32*)(pbVar14 + 1))) {
        FUN_7103269e30(&local_208, lVar25, uVar10);
        if ((*local_200 == '\f') && (iVar11 = *(s32*)(local_200 + 1) + -1, 0 < *(s32*)(local_200 + 1))) {
            lVar25 = ((s64)uStack_204 << 32) | local_208;
            iVar17 = 0;
            pcVar30 = "";
            do {
                iVar18 = iVar11 + iVar17;
                if (iVar18 < 0) iVar18 = iVar18 + 1;
                iVar18 = iVar18 >> 1;
                puVar1 = (u32*)(*(s64*)(lVar25 + 0x28) + (s64)*(s32*)(local_200 + 5) + (s64)iVar18 * 8);
                uVar20 = *(u64*)(*(s64*)(lVar25 + 0x20) + (u64)*puVar1 * 8);
                if (uVar20 == 0x7b816b0feULL) {
                    uVar12 = puVar1[1];
                    if ((s32)uVar12 < 0) goto block2_inner_fail;
                    pcVar30 = local_200 + (s32)uVar12;
                    goto block2_inner_done;
                }
                iVar3 = iVar18 + -1;
                if (uVar20 < 0x7b816b0ffULL) { iVar17 = iVar18 + 1; iVar3 = iVar11; }
                iVar11 = iVar3;
            } while (iVar17 <= iVar11);
            lVar25 = 0;
        } else {
        block2_inner_fail:
            lVar25 = 0;
            pcVar30 = "";
        }
    block2_inner_done:
        if (*pcVar30 != '\t') goto block2_default;
        uVar20 = *(u64*)(*(s64*)(lVar25 + 0x20) + (s64)*(s32*)(pcVar30 + 1) * 8);
    } else {
    block2_default:
        uVar20 = 0;
    }
    uVar12 = 2;
    if ((uVar20 & 0xFFFFFFFFFFULL) != 0x455663adeULL) {
        uVar12 = (u32)((uVar20 & 0xFFFFFFFFFFULL) == 0x63a127c87ULL);
    }
    param_1[1] = uVar12;

    // ══════════════════════════════════════════════════════════════
    // Block 3: param_1[2] — bool (hash 0xe31430812 == 0x58985ba28)
    // ══════════════════════════════════════════════════════════════
    if (bVar8 && bVar7) {
        lVar25 = *(s64*)(*(s64*)(lVar29 + 0x1c8) + 8);
        pcVar30 = *(char**)(lVar25 + 0x20);
        cVar5 = *pcVar30;
        if ((cVar5 == '\f') && (iVar11 = *(s32*)(pcVar30 + 1) + -1, 0 < *(s32*)(pcVar30 + 1))) {
            uVar20 = *(u64*)(lVar25 + 0x48) & 0xFFFFFFFFFFULL;
            iVar17 = 0;
            pbVar14 = &DAT_7104741dbb;
            do {
                iVar18 = iVar11 + iVar17;
                if (iVar18 < 0) iVar18 = iVar18 + 1;
                iVar18 = iVar18 >> 1;
                puVar1 = (u32*)(*(s64*)(*(s64*)(lVar25 + 0x18) + 0x28) + (s64)*(s32*)(pcVar30 + 5) + (s64)iVar18 * 8);
                uVar21 = *(u64*)(*(s64*)(*(s64*)(lVar25 + 0x18) + 0x20) + (u64)*puVar1 * 8);
                if (uVar21 == uVar20) {
                    uVar12 = puVar1[1];
                    if ((s32)uVar12 < 0) goto block3_fallback;
                    pbVar14 = (u8*)(pcVar30 + (s32)uVar12);
                    break;
                }
                iVar3 = iVar18 + -1;
                if (uVar21 <= uVar20) { iVar17 = iVar18 + 1; iVar3 = iVar11; }
                iVar11 = iVar3;
            } while (iVar17 <= iVar11);
        } else {
        block3_fallback:
            pbVar14 = &DAT_7104741dbb;
        }
        if (*pbVar14 - 0xb < 2) {
            uVar20 = param_2 >> 0x28 & 0xffff;
            uVar10 = (u32)uVar20;
            if ((*(u32*)(pbVar14 + 1) <= uVar10) ||
                (uVar20 = FUN_7103269900(lVar25, uVar20), ((uVar20 ^ param_2) & 0xFFFFFFFFFFULL) != 0))
                goto block3_slow;
        } else {
        block3_slow:
            uVar10 = FUN_7103269fd0(lVar25, uVar16);
        }
        uVar12 = uVar10;
        if (cVar5 != '\f') goto block3_sentinel;
    block3_search2:
        uVar10 = uVar12;
        iVar11 = *(s32*)(pcVar30 + 1) + -1;
        if (*(s32*)(pcVar30 + 1) < 1) goto block3_sentinel;
        uVar20 = *(u64*)(lVar25 + 0x48) & 0xFFFFFFFFFFULL;
        iVar17 = 0;
        pbVar14 = &DAT_7104741dbb;
        do {
            iVar18 = iVar11 + iVar17;
            if (iVar18 < 0) iVar18 = iVar18 + 1;
            iVar18 = iVar18 >> 1;
            puVar1 = (u32*)(*(s64*)(*(s64*)(lVar25 + 0x18) + 0x28) + (s64)*(s32*)(pcVar30 + 5) + (s64)iVar18 * 8);
            uVar21 = *(u64*)(*(s64*)(*(s64*)(lVar25 + 0x18) + 0x20) + (u64)*puVar1 * 8);
            if (uVar21 == uVar20) {
                uVar12 = puVar1[1];
                if ((s32)uVar12 < 0) goto block3_sentinel;
                pbVar14 = (u8*)(pcVar30 + (s32)uVar12);
                break;
            }
            iVar3 = iVar18 + -1;
            if (uVar21 <= uVar20) { iVar17 = iVar18 + 1; iVar3 = iVar11; }
            iVar11 = iVar3;
        } while (iVar17 <= iVar11);
    } else {
        lVar25 = *(s64*)(*(s64*)(lVar29 + 0x1c8) + 8);
        pcVar30 = *(char**)(lVar25 + 0x20);
        uVar10 = 0xffffffff;
        uVar12 = 0xffffffff;
        if (*pcVar30 == '\f') goto block3_search2;
    block3_sentinel:
        pbVar14 = &DAT_7104741dbb;
    }
    if ((*pbVar14 - 0xb < 2) && (uVar10 < *(u32*)(pbVar14 + 1))) {
        FUN_7103269e30(&local_208, lVar25, uVar10);
        if ((*local_200 == '\f') && (iVar11 = *(s32*)(local_200 + 1) + -1, 0 < *(s32*)(local_200 + 1))) {
            lVar25 = ((s64)uStack_204 << 32) | local_208;
            iVar17 = 0;
            pcVar30 = "";
            do {
                iVar18 = iVar11 + iVar17;
                if (iVar18 < 0) iVar18 = iVar18 + 1;
                iVar18 = iVar18 >> 1;
                puVar1 = (u32*)(*(s64*)(lVar25 + 0x28) + (s64)*(s32*)(local_200 + 5) + (s64)iVar18 * 8);
                uVar20 = *(u64*)(*(s64*)(lVar25 + 0x20) + (u64)*puVar1 * 8);
                if (uVar20 == 0xe31430812ULL) {
                    uVar12 = puVar1[1];
                    if ((s32)uVar12 < 0) goto block3_inner_fail;
                    pcVar30 = local_200 + (s32)uVar12;
                    goto block3_inner_done;
                }
                iVar3 = iVar18 + -1;
                if (uVar20 < 0xe31430813ULL) { iVar17 = iVar18 + 1; iVar3 = iVar11; }
                iVar11 = iVar3;
            } while (iVar17 <= iVar11);
            lVar25 = 0;
        } else {
        block3_inner_fail:
            lVar25 = 0;
            pcVar30 = "";
        }
    block3_inner_done:
        if (*pcVar30 != '\t') goto block3_default;
        uVar20 = *(u64*)(*(s64*)(lVar25 + 0x20) + (s64)*(s32*)(pcVar30 + 1) * 8);
    } else {
    block3_default:
        uVar20 = 0;
    }
    param_1[2] = (u32)((uVar20 & 0xFFFFFFFFFFULL) == 0x58985ba28ULL);

    // ══════════════════════════════════════════════════════════════
    // Block 4: param_1[3] — bool (hash 0xdf0986663 == 0x61dc5b178)
    // ══════════════════════════════════════════════════════════════
    if (bVar8 && bVar7) {
        lVar25 = *(s64*)(*(s64*)(lVar29 + 0x1c8) + 8);
        pcVar30 = *(char**)(lVar25 + 0x20);
        cVar5 = *pcVar30;
        if ((cVar5 == '\f') && (iVar11 = *(s32*)(pcVar30 + 1) + -1, 0 < *(s32*)(pcVar30 + 1))) {
            uVar20 = *(u64*)(lVar25 + 0x48) & 0xFFFFFFFFFFULL;
            iVar17 = 0;
            pbVar14 = &DAT_7104741dbb;
            do {
                iVar18 = iVar11 + iVar17;
                if (iVar18 < 0) iVar18 = iVar18 + 1;
                iVar18 = iVar18 >> 1;
                puVar1 = (u32*)(*(s64*)(*(s64*)(lVar25 + 0x18) + 0x28) + (s64)*(s32*)(pcVar30 + 5) + (s64)iVar18 * 8);
                uVar21 = *(u64*)(*(s64*)(*(s64*)(lVar25 + 0x18) + 0x20) + (u64)*puVar1 * 8);
                if (uVar21 == uVar20) {
                    uVar12 = puVar1[1];
                    if ((s32)uVar12 < 0) goto block4_fallback;
                    pbVar14 = (u8*)(pcVar30 + (s32)uVar12);
                    break;
                }
                iVar3 = iVar18 + -1;
                if (uVar21 <= uVar20) { iVar17 = iVar18 + 1; iVar3 = iVar11; }
                iVar11 = iVar3;
            } while (iVar17 <= iVar11);
        } else {
        block4_fallback:
            pbVar14 = &DAT_7104741dbb;
        }
        if (*pbVar14 - 0xb < 2) {
            uVar20 = param_2 >> 0x28 & 0xffff;
            uVar10 = (u32)uVar20;
            if ((*(u32*)(pbVar14 + 1) <= uVar10) ||
                (uVar20 = FUN_7103269900(lVar25, uVar20), ((uVar20 ^ param_2) & 0xFFFFFFFFFFULL) != 0))
                goto block4_slow;
        } else {
        block4_slow:
            uVar10 = FUN_7103269fd0(lVar25, uVar16);
        }
        uVar12 = uVar10;
        if (cVar5 != '\f') goto block4_sentinel;
    block4_search2:
        uVar10 = uVar12;
        iVar11 = *(s32*)(pcVar30 + 1) + -1;
        if (*(s32*)(pcVar30 + 1) < 1) goto block4_sentinel;
        uVar20 = *(u64*)(lVar25 + 0x48) & 0xFFFFFFFFFFULL;
        iVar17 = 0;
        pbVar14 = &DAT_7104741dbb;
        do {
            iVar18 = iVar11 + iVar17;
            if (iVar18 < 0) iVar18 = iVar18 + 1;
            iVar18 = iVar18 >> 1;
            puVar1 = (u32*)(*(s64*)(*(s64*)(lVar25 + 0x18) + 0x28) + (s64)*(s32*)(pcVar30 + 5) + (s64)iVar18 * 8);
            uVar21 = *(u64*)(*(s64*)(*(s64*)(lVar25 + 0x18) + 0x20) + (u64)*puVar1 * 8);
            if (uVar21 == uVar20) {
                uVar12 = puVar1[1];
                if ((s32)uVar12 < 0) goto block4_sentinel;
                pbVar14 = (u8*)(pcVar30 + (s32)uVar12);
                break;
            }
            iVar3 = iVar18 + -1;
            if (uVar21 <= uVar20) { iVar17 = iVar18 + 1; iVar3 = iVar11; }
            iVar11 = iVar3;
        } while (iVar17 <= iVar11);
    } else {
        lVar25 = *(s64*)(*(s64*)(lVar29 + 0x1c8) + 8);
        pcVar30 = *(char**)(lVar25 + 0x20);
        uVar10 = 0xffffffff;
        uVar12 = 0xffffffff;
        if (*pcVar30 == '\f') goto block4_search2;
    block4_sentinel:
        pbVar14 = &DAT_7104741dbb;
    }
    if ((*pbVar14 - 0xb < 2) && (uVar10 < *(u32*)(pbVar14 + 1))) {
        FUN_7103269e30(&local_208, lVar25, uVar10);
        if ((*local_200 == '\f') && (iVar11 = *(s32*)(local_200 + 1) + -1, 0 < *(s32*)(local_200 + 1))) {
            lVar25 = ((s64)uStack_204 << 32) | local_208;
            iVar17 = 0;
            pcVar30 = "";
            do {
                iVar18 = iVar11 + iVar17;
                if (iVar18 < 0) iVar18 = iVar18 + 1;
                iVar18 = iVar18 >> 1;
                puVar1 = (u32*)(*(s64*)(lVar25 + 0x28) + (s64)*(s32*)(local_200 + 5) + (s64)iVar18 * 8);
                uVar20 = *(u64*)(*(s64*)(lVar25 + 0x20) + (u64)*puVar1 * 8);
                if (uVar20 == 0xdf0986663ULL) {
                    uVar12 = puVar1[1];
                    if ((s32)uVar12 < 0) goto block4_inner_fail;
                    pcVar30 = local_200 + (s32)uVar12;
                    goto block4_inner_done;
                }
                iVar3 = iVar18 + -1;
                if (uVar20 < 0xdf0986664ULL) { iVar17 = iVar18 + 1; iVar3 = iVar11; }
                iVar11 = iVar3;
            } while (iVar17 <= iVar11);
            lVar25 = 0;
        } else {
        block4_inner_fail:
            lVar25 = 0;
            pcVar30 = "";
        }
    block4_inner_done:
        if (*pcVar30 != '\t') goto block4_default;
        uVar20 = *(u64*)(*(s64*)(lVar25 + 0x20) + (s64)*(s32*)(pcVar30 + 1) * 8);
    } else {
    block4_default:
        uVar20 = 0;
    }
    param_1[3] = (u32)((uVar20 & 0xFFFFFFFFFFULL) == 0x61dc5b178ULL);

    // ══════════════════════════════════════════════════════════════
    // Block 5: *(bool*)(param_1+4) — bool from int (hash 0x882c9dcb7)
    // Defaults to true, set to (int != 0)
    // ══════════════════════════════════════════════════════════════
    if (bVar8 && bVar7) {
        lVar25 = *(s64*)(*(s64*)(lVar29 + 0x1c8) + 8);
        pcVar30 = *(char**)(lVar25 + 0x20);
        cVar5 = *pcVar30;
        if ((cVar5 == '\f') && (iVar11 = *(s32*)(pcVar30 + 1) + -1, 0 < *(s32*)(pcVar30 + 1))) {
            uVar20 = *(u64*)(lVar25 + 0x48) & 0xFFFFFFFFFFULL;
            iVar17 = 0;
            pbVar14 = &DAT_7104741dbb;
            do {
                iVar18 = iVar11 + iVar17;
                if (iVar18 < 0) iVar18 = iVar18 + 1;
                iVar18 = iVar18 >> 1;
                puVar1 = (u32*)(*(s64*)(*(s64*)(lVar25 + 0x18) + 0x28) + (s64)*(s32*)(pcVar30 + 5) + (s64)iVar18 * 8);
                uVar21 = *(u64*)(*(s64*)(*(s64*)(lVar25 + 0x18) + 0x20) + (u64)*puVar1 * 8);
                if (uVar21 == uVar20) {
                    uVar12 = puVar1[1];
                    if ((s32)uVar12 < 0) goto block5_fallback;
                    pbVar14 = (u8*)(pcVar30 + (s32)uVar12);
                    break;
                }
                iVar3 = iVar18 + -1;
                if (uVar21 <= uVar20) { iVar17 = iVar18 + 1; iVar3 = iVar11; }
                iVar11 = iVar3;
            } while (iVar17 <= iVar11);
        } else {
        block5_fallback:
            pbVar14 = &DAT_7104741dbb;
        }
        if (*pbVar14 - 0xb < 2) {
            uVar20 = param_2 >> 0x28 & 0xffff;
            uVar10 = (u32)uVar20;
            if ((*(u32*)(pbVar14 + 1) <= uVar10) ||
                (uVar20 = FUN_7103269900(lVar25, uVar20), ((uVar20 ^ param_2) & 0xFFFFFFFFFFULL) != 0))
                goto block5_slow;
        } else {
        block5_slow:
            uVar10 = FUN_7103269fd0(lVar25, uVar16);
        }
        uVar12 = uVar10;
        if (cVar5 != '\f') goto block5_sentinel;
    block5_search2:
        uVar10 = uVar12;
        iVar11 = *(s32*)(pcVar30 + 1) + -1;
        if (*(s32*)(pcVar30 + 1) < 1) goto block5_sentinel;
        uVar20 = *(u64*)(lVar25 + 0x48) & 0xFFFFFFFFFFULL;
        iVar17 = 0;
        pbVar14 = &DAT_7104741dbb;
        do {
            iVar18 = iVar11 + iVar17;
            if (iVar18 < 0) iVar18 = iVar18 + 1;
            iVar18 = iVar18 >> 1;
            puVar1 = (u32*)(*(s64*)(*(s64*)(lVar25 + 0x18) + 0x28) + (s64)*(s32*)(pcVar30 + 5) + (s64)iVar18 * 8);
            uVar21 = *(u64*)(*(s64*)(*(s64*)(lVar25 + 0x18) + 0x20) + (u64)*puVar1 * 8);
            if (uVar21 == uVar20) {
                uVar12 = puVar1[1];
                if ((s32)uVar12 < 0) goto block5_sentinel;
                pbVar14 = (u8*)(pcVar30 + (s32)uVar12);
                break;
            }
            iVar3 = iVar18 + -1;
            if (uVar21 <= uVar20) { iVar17 = iVar18 + 1; iVar3 = iVar11; }
            iVar11 = iVar3;
        } while (iVar17 <= iVar11);
    } else {
        lVar25 = *(s64*)(*(s64*)(lVar29 + 0x1c8) + 8);
        pcVar30 = *(char**)(lVar25 + 0x20);
        uVar10 = 0xffffffff;
        uVar12 = 0xffffffff;
        if (*pcVar30 == '\f') goto block5_search2;
    block5_sentinel:
        pbVar14 = &DAT_7104741dbb;
    }
    if ((*pbVar14 - 0xb < 2) && (uVar10 < *(u32*)(pbVar14 + 1))) {
        FUN_7103269e30(&local_208, lVar25, uVar10);
        if ((*local_200 == '\f') && (iVar11 = *(s32*)(local_200 + 1) + -1, 0 < *(s32*)(local_200 + 1))) {
            iVar17 = 0;
            pcVar30 = "";
            do {
                iVar18 = iVar11 + iVar17;
                if (iVar18 < 0) iVar18 = iVar18 + 1;
                iVar18 = iVar18 >> 1;
                puVar1 = (u32*)(*(s64*)(((s64)uStack_204 << 32 | local_208) + 0x28) + (s64)*(s32*)(local_200 + 5) + (s64)iVar18 * 8);
                uVar20 = *(u64*)(*(s64*)(((s64)uStack_204 << 32 | local_208) + 0x20) + (u64)*puVar1 * 8);
                if (uVar20 == 0x882c9dcb7ULL) {
                    uVar12 = puVar1[1];
                    if ((s32)uVar12 < 0) goto block5_inner_fail;
                    pcVar30 = local_200 + (s32)uVar12;
                    break;
                }
                iVar3 = iVar18 + -1;
                if (uVar20 < 0x882c9dcb8ULL) { iVar17 = iVar18 + 1; iVar3 = iVar11; }
                iVar11 = iVar3;
            } while (iVar17 <= iVar11);
        } else {
        block5_inner_fail:
            pcVar30 = "";
        }
        uVar12 = prc_read_int(pcVar30);
        bVar9 = uVar12 != 0;
    } else {
        bVar9 = true;
    }
    *(bool*)(param_1 + 4) = bVar9;

    // ══════════════════════════════════════════════════════════════
    // Block 6: *puVar24 (param_1[5]) — enum (hash 0xb24f83cc3)
    // ══════════════════════════════════════════════════════════════
    if (bVar8 && bVar7) {
        lVar25 = *(s64*)(*(s64*)(lVar29 + 0x1c8) + 8);
        pcVar30 = *(char**)(lVar25 + 0x20);
        cVar5 = *pcVar30;
        if ((cVar5 == '\f') && (iVar11 = *(s32*)(pcVar30 + 1) + -1, 0 < *(s32*)(pcVar30 + 1))) {
            uVar20 = *(u64*)(lVar25 + 0x48) & 0xFFFFFFFFFFULL;
            iVar17 = 0;
            pbVar14 = &DAT_7104741dbb;
            do {
                iVar18 = iVar11 + iVar17;
                if (iVar18 < 0) iVar18 = iVar18 + 1;
                iVar18 = iVar18 >> 1;
                puVar1 = (u32*)(*(s64*)(*(s64*)(lVar25 + 0x18) + 0x28) + (s64)*(s32*)(pcVar30 + 5) + (s64)iVar18 * 8);
                uVar21 = *(u64*)(*(s64*)(*(s64*)(lVar25 + 0x18) + 0x20) + (u64)*puVar1 * 8);
                if (uVar21 == uVar20) {
                    uVar12 = puVar1[1];
                    if ((s32)uVar12 < 0) goto block6_fallback;
                    pbVar14 = (u8*)(pcVar30 + (s32)uVar12);
                    break;
                }
                iVar3 = iVar18 + -1;
                if (uVar21 <= uVar20) { iVar17 = iVar18 + 1; iVar3 = iVar11; }
                iVar11 = iVar3;
            } while (iVar17 <= iVar11);
        } else {
        block6_fallback:
            pbVar14 = &DAT_7104741dbb;
        }
        if (*pbVar14 - 0xb < 2) {
            uVar20 = param_2 >> 0x28 & 0xffff;
            uVar10 = (u32)uVar20;
            if ((*(u32*)(pbVar14 + 1) <= uVar10) ||
                (uVar20 = FUN_7103269900(lVar25, uVar20), ((uVar20 ^ param_2) & 0xFFFFFFFFFFULL) != 0))
                goto block6_slow;
        } else {
        block6_slow:
            uVar10 = FUN_7103269fd0(lVar25, uVar16);
        }
        uVar12 = uVar10;
        if (cVar5 != '\f') goto block6_sentinel;
    block6_search2:
        uVar10 = uVar12;
        iVar11 = *(s32*)(pcVar30 + 1) + -1;
        if (*(s32*)(pcVar30 + 1) < 1) goto block6_sentinel;
        uVar20 = *(u64*)(lVar25 + 0x48) & 0xFFFFFFFFFFULL;
        iVar17 = 0;
        pbVar14 = &DAT_7104741dbb;
        do {
            iVar18 = iVar11 + iVar17;
            if (iVar18 < 0) iVar18 = iVar18 + 1;
            iVar18 = iVar18 >> 1;
            puVar1 = (u32*)(*(s64*)(*(s64*)(lVar25 + 0x18) + 0x28) + (s64)*(s32*)(pcVar30 + 5) + (s64)iVar18 * 8);
            uVar21 = *(u64*)(*(s64*)(*(s64*)(lVar25 + 0x18) + 0x20) + (u64)*puVar1 * 8);
            if (uVar21 == uVar20) {
                uVar12 = puVar1[1];
                if ((s32)uVar12 < 0) goto block6_sentinel;
                pbVar14 = (u8*)(pcVar30 + (s32)uVar12);
                break;
            }
            iVar3 = iVar18 + -1;
            if (uVar21 <= uVar20) { iVar17 = iVar18 + 1; iVar3 = iVar11; }
            iVar11 = iVar3;
        } while (iVar17 <= iVar11);
    } else {
        lVar25 = *(s64*)(*(s64*)(lVar29 + 0x1c8) + 8);
        pcVar30 = *(char**)(lVar25 + 0x20);
        uVar10 = 0xffffffff;
        uVar12 = 0xffffffff;
        if (*pcVar30 == '\f') goto block6_search2;
    block6_sentinel:
        pbVar14 = &DAT_7104741dbb;
    }
    if ((*pbVar14 - 0xb < 2) && (uVar10 < *(u32*)(pbVar14 + 1))) {
        FUN_7103269e30(&local_208, lVar25, uVar10);
        if ((*local_200 == '\f') && (iVar11 = *(s32*)(local_200 + 1) + -1, 0 < *(s32*)(local_200 + 1))) {
            lVar25 = ((s64)uStack_204 << 32) | local_208;
            iVar17 = 0;
            pcVar30 = "";
            do {
                iVar18 = iVar11 + iVar17;
                if (iVar18 < 0) iVar18 = iVar18 + 1;
                iVar18 = iVar18 >> 1;
                puVar1 = (u32*)(*(s64*)(lVar25 + 0x28) + (s64)*(s32*)(local_200 + 5) + (s64)iVar18 * 8);
                uVar20 = *(u64*)(*(s64*)(lVar25 + 0x20) + (u64)*puVar1 * 8);
                if (uVar20 == 0xb24f83cc3ULL) {
                    uVar12 = puVar1[1];
                    if ((s32)uVar12 < 0) goto block6_inner_fail;
                    pcVar30 = local_200 + (s32)uVar12;
                    goto block6_inner_done;
                }
                iVar3 = iVar18 + -1;
                if (uVar20 < 0xb24f83cc4ULL) { iVar17 = iVar18 + 1; iVar3 = iVar11; }
                iVar11 = iVar3;
            } while (iVar17 <= iVar11);
            lVar25 = 0;
        } else {
        block6_inner_fail:
            lVar25 = 0;
            pcVar30 = "";
        }
    block6_inner_done:
        if (*pcVar30 != '\t') goto block6_default;
        uVar20 = *(u64*)(*(s64*)(lVar25 + 0x20) + (s64)*(s32*)(pcVar30 + 1) * 8) & 0xFFFFFFFFFFULL;
        if (uVar20 == 0x4601e9fb8ULL) { uVar12 = 3; }
        else if (uVar20 == 0x5c9b670b8ULL) { uVar12 = 1; }
        else { if (uVar20 != 0x586b7d523ULL) goto block6_default; uVar12 = 2; }
    } else {
    block6_default:
        uVar12 = 0;
    }
    *puVar24 = uVar12;

    // ══════════════════════════════════════════════════════════════
    // Block 7: param_1[6] — bool (hash 0xcbbf5afa5 == 0xad032eacc)
    // ══════════════════════════════════════════════════════════════
    if (bVar8 && bVar7) {
        lVar25 = *(s64*)(*(s64*)(lVar29 + 0x1c8) + 8);
        pcVar30 = *(char**)(lVar25 + 0x20);
        cVar5 = *pcVar30;
        if ((cVar5 == '\f') && (iVar11 = *(s32*)(pcVar30 + 1) + -1, 0 < *(s32*)(pcVar30 + 1))) {
            uVar20 = *(u64*)(lVar25 + 0x48) & 0xFFFFFFFFFFULL;
            iVar17 = 0;
            pbVar14 = &DAT_7104741dbb;
            do {
                iVar18 = iVar11 + iVar17;
                if (iVar18 < 0) iVar18 = iVar18 + 1;
                iVar18 = iVar18 >> 1;
                puVar24 = (u32*)(*(s64*)(*(s64*)(lVar25 + 0x18) + 0x28) + (s64)*(s32*)(pcVar30 + 5) + (s64)iVar18 * 8);
                uVar21 = *(u64*)(*(s64*)(*(s64*)(lVar25 + 0x18) + 0x20) + (u64)*puVar24 * 8);
                if (uVar21 == uVar20) {
                    uVar12 = puVar24[1];
                    if ((s32)uVar12 < 0) goto block7_fallback;
                    pbVar14 = (u8*)(pcVar30 + (s32)uVar12);
                    break;
                }
                iVar3 = iVar18 + -1;
                if (uVar21 <= uVar20) { iVar17 = iVar18 + 1; iVar3 = iVar11; }
                iVar11 = iVar3;
            } while (iVar17 <= iVar11);
        } else {
        block7_fallback:
            pbVar14 = &DAT_7104741dbb;
        }
        if (*pbVar14 - 0xb < 2) {
            uVar20 = param_2 >> 0x28 & 0xffff;
            uVar10 = (u32)uVar20;
            if ((*(u32*)(pbVar14 + 1) <= uVar10) ||
                (uVar20 = FUN_7103269900(lVar25, uVar20), ((uVar20 ^ param_2) & 0xFFFFFFFFFFULL) != 0))
                goto block7_slow;
        } else {
        block7_slow:
            uVar10 = FUN_7103269fd0(lVar25, uVar16);
        }
        uVar12 = uVar10;
        if (cVar5 != '\f') goto block7_sentinel;
    block7_search2:
        uVar10 = uVar12;
        iVar11 = *(s32*)(pcVar30 + 1) + -1;
        if (*(s32*)(pcVar30 + 1) < 1) goto block7_sentinel;
        uVar20 = *(u64*)(lVar25 + 0x48) & 0xFFFFFFFFFFULL;
        iVar17 = 0;
        pbVar14 = &DAT_7104741dbb;
        do {
            iVar18 = iVar11 + iVar17;
            if (iVar18 < 0) iVar18 = iVar18 + 1;
            iVar18 = iVar18 >> 1;
            puVar24 = (u32*)(*(s64*)(*(s64*)(lVar25 + 0x18) + 0x28) + (s64)*(s32*)(pcVar30 + 5) + (s64)iVar18 * 8);
            uVar21 = *(u64*)(*(s64*)(*(s64*)(lVar25 + 0x18) + 0x20) + (u64)*puVar24 * 8);
            if (uVar21 == uVar20) {
                uVar12 = puVar24[1];
                if ((s32)uVar12 < 0) goto block7_sentinel;
                pbVar14 = (u8*)(pcVar30 + (s32)uVar12);
                break;
            }
            iVar3 = iVar18 + -1;
            if (uVar21 <= uVar20) { iVar17 = iVar18 + 1; iVar3 = iVar11; }
            iVar11 = iVar3;
        } while (iVar17 <= iVar11);
    } else {
        lVar25 = *(s64*)(*(s64*)(lVar29 + 0x1c8) + 8);
        pcVar30 = *(char**)(lVar25 + 0x20);
        uVar10 = 0xffffffff;
        uVar12 = 0xffffffff;
        if (*pcVar30 == '\f') goto block7_search2;
    block7_sentinel:
        pbVar14 = &DAT_7104741dbb;
    }
    if ((*pbVar14 - 0xb < 2) && (uVar10 < *(u32*)(pbVar14 + 1))) {
        FUN_7103269e30(&local_208, lVar25, uVar10);
        if ((*local_200 == '\f') && (iVar11 = *(s32*)(local_200 + 1) + -1, 0 < *(s32*)(local_200 + 1))) {
            lVar25 = ((s64)uStack_204 << 32) | local_208;
            iVar17 = 0;
            pcVar30 = "";
            do {
                iVar18 = iVar11 + iVar17;
                if (iVar18 < 0) iVar18 = iVar18 + 1;
                iVar18 = iVar18 >> 1;
                puVar24 = (u32*)(*(s64*)(lVar25 + 0x28) + (s64)*(s32*)(local_200 + 5) + (s64)iVar18 * 8);
                uVar20 = *(u64*)(*(s64*)(lVar25 + 0x20) + (u64)*puVar24 * 8);
                if (uVar20 == 0xcbbf5afa5ULL) {
                    uVar12 = puVar24[1];
                    if ((s32)uVar12 < 0) goto block7_inner_fail;
                    pcVar30 = local_200 + (s32)uVar12;
                    goto block7_inner_done;
                }
                iVar3 = iVar18 + -1;
                if (uVar20 < 0xcbbf5afa6ULL) { iVar17 = iVar18 + 1; iVar3 = iVar11; }
                iVar11 = iVar3;
            } while (iVar17 <= iVar11);
            lVar25 = 0;
        } else {
        block7_inner_fail:
            lVar25 = 0;
            pcVar30 = "";
        }
    block7_inner_done:
        if (*pcVar30 != '\t') goto block7_default;
        uVar20 = *(u64*)(*(s64*)(lVar25 + 0x20) + (s64)*(s32*)(pcVar30 + 1) * 8);
    } else {
    block7_default:
        uVar20 = 0;
    }
    param_1[6] = (u32)((uVar20 & 0xFFFFFFFFFFULL) == 0xad032eaccULL);

    // ══════════════════════════════════════════════════════════════
    // String copies with FNV-1 hash (4 strings)
    // ══════════════════════════════════════════════════════════════
    uVar12 = 0x811c9dc5;

    // String 0: FUN_7103290db0 → param_1+7 (hash), param_1+8 (length), bytes 0x24+ (data)
    FUN_7103290db0(&local_208, *(u64*)(lVar29 + 0x1c8), param_2);
    if (param_1 + 7 != &local_208) {
        for (uVar20 = 0; *(char*)((s64)&local_200 + uVar20) != '\0'; uVar20 = uVar20 + 2) {
            *(char*)((s64)param_1 + uVar20 + 0x24) = *(char*)((s64)&local_200 + uVar20);
            if (0x3e < (s32)uVar20 + 1U) { uVar20 = (u64)((s32)uVar20 + 1); break; }
            cVar5 = *(char*)((s64)&local_200 + uVar20 + 1);
            if (cVar5 == '\0') { uVar20 = uVar20 + 1; break; }
            *(char*)((s64)param_1 + uVar20 + 0x25) = cVar5;
        }
        *(u8*)((s64)param_1 + (uVar20 & 0xffffffff) + 0x24) = 0;
        param_1[8] = (u32)uVar20;
        uVar15 = (u32)(u8)param_1[9];
        uVar10 = uVar12;
        if ((u8)param_1[9] != 0) {
            pbVar14 = (u8*)((s64)param_1 + 0x25);
            do {
                uVar10 = uVar10 * 0x89 ^ uVar15;
                uVar15 = (u32)*pbVar14;
                pbVar14 = pbVar14 + 1;
            } while (uVar15 != 0);
        }
        param_1[7] = uVar10;
    }

    // String 1: FUN_7103291140 → puVar28 (hash), param_1+0x1a (length), bytes 0x6c+ (data)
    FUN_7103291140(&local_208, *(u64*)(lVar29 + 0x1c8), param_2);
    if (puVar28 != &local_208) {
        for (uVar20 = 0; *(char*)((s64)&local_200 + uVar20) != '\0'; uVar20 = uVar20 + 2) {
            *(char*)((s64)param_1 + uVar20 + 0x6c) = *(char*)((s64)&local_200 + uVar20);
            if (0x3e < (s32)uVar20 + 1U) { uVar20 = (u64)((s32)uVar20 + 1); break; }
            cVar5 = *(char*)((s64)&local_200 + uVar20 + 1);
            if (cVar5 == '\0') { uVar20 = uVar20 + 1; break; }
            *(char*)((s64)param_1 + uVar20 + 0x6d) = cVar5;
        }
        *(u8*)((s64)param_1 + (uVar20 & 0xffffffff) + 0x6c) = 0;
        param_1[0x1a] = (u32)uVar20;
        uVar15 = (u32)(u8)param_1[0x1b];
        uVar10 = uVar12;
        if ((u8)param_1[0x1b] != 0) {
            pbVar14 = (u8*)((s64)param_1 + 0x6d);
            do {
                uVar10 = uVar10 * 0x89 ^ uVar15;
                uVar15 = (u32)*pbVar14;
                pbVar14 = pbVar14 + 1;
            } while (uVar15 != 0);
        }
        *puVar28 = uVar10;
    }

    // String 2: FUN_71032914d0 → puVar13 (hash), param_1+0x2c (length), bytes 0xb4+ (data)
    FUN_71032914d0(&local_208, *(u64*)(lVar29 + 0x1c8), param_2);
    if (puVar13 != &local_208) {
        for (uVar20 = 0; *(char*)((s64)&local_200 + uVar20) != '\0'; uVar20 = uVar20 + 2) {
            *(char*)((s64)param_1 + uVar20 + 0xb4) = *(char*)((s64)&local_200 + uVar20);
            if (0x3e < (s32)uVar20 + 1U) { uVar20 = (u64)((s32)uVar20 + 1); break; }
            cVar5 = *(char*)((s64)&local_200 + uVar20 + 1);
            if (cVar5 == '\0') { uVar20 = uVar20 + 1; break; }
            *(char*)((s64)param_1 + uVar20 + 0xb5) = cVar5;
        }
        *(u8*)((s64)param_1 + (uVar20 & 0xffffffff) + 0xb4) = 0;
        param_1[0x2c] = (u32)uVar20;
        uVar15 = (u32)(u8)param_1[0x2d];
        uVar10 = uVar12;
        if ((u8)param_1[0x2d] != 0) {
            pbVar14 = (u8*)((s64)param_1 + 0xb5);
            do {
                uVar10 = uVar10 * 0x89 ^ uVar15;
                uVar15 = (u32)*pbVar14;
                pbVar14 = pbVar14 + 1;
            } while (uVar15 != 0);
        }
        *puVar13 = uVar10;
    }

    // String 3: FUN_7103291860 → puVar26 (hash), param_1+0x3e (length), bytes 0xfc+ (data)
    FUN_7103291860(&local_208, *(u64*)(lVar29 + 0x1c8), param_2);
    if (puVar26 != &local_208) {
        for (uVar20 = 0; *(char*)((s64)&local_200 + uVar20) != '\0'; uVar20 = uVar20 + 2) {
            *(char*)((s64)param_1 + uVar20 + 0xfc) = *(char*)((s64)&local_200 + uVar20);
            if (0x3e < (s32)uVar20 + 1U) { uVar20 = (u64)((s32)uVar20 + 1); break; }
            cVar5 = *(char*)((s64)&local_200 + uVar20 + 1);
            if (cVar5 == '\0') { uVar20 = uVar20 + 1; break; }
            *(char*)((s64)param_1 + uVar20 + 0xfd) = cVar5;
        }
        *(u8*)((s64)param_1 + (uVar20 & 0xffffffff) + 0xfc) = 0;
        uVar10 = (u32)(u8)param_1[0x3f];
        param_1[0x3e] = (u32)uVar20;
        if ((u8)param_1[0x3f] != 0) {
            pbVar14 = (u8*)((s64)param_1 + 0xfd);
            do {
                uVar12 = uVar12 * 0x89 ^ uVar10;
                uVar10 = (u32)*pbVar14;
                pbVar14 = pbVar14 + 1;
            } while (uVar10 != 0);
        }
        *puVar26 = uVar12;
    }

    // ══════════════════════════════════════════════════════════════
    // Block 8: param_1[0x56] — float from int (hash 0xdbb634436)
    // ══════════════════════════════════════════════════════════════
    if (bVar8 && bVar7) {
        lVar25 = *(s64*)(*(s64*)(lVar29 + 0x1c8) + 8);
        pcVar30 = *(char**)(lVar25 + 0x20);
        cVar5 = *pcVar30;
        if ((cVar5 == '\f') && (iVar11 = *(s32*)(pcVar30 + 1) + -1, 0 < *(s32*)(pcVar30 + 1))) {
            uVar20 = *(u64*)(lVar25 + 0x48) & 0xFFFFFFFFFFULL;
            iVar17 = 0;
            pbVar14 = &DAT_7104741dbb;
            do {
                iVar18 = iVar11 + iVar17;
                if (iVar18 < 0) iVar18 = iVar18 + 1;
                iVar18 = iVar18 >> 1;
                puVar13 = (u32*)(*(s64*)(*(s64*)(lVar25 + 0x18) + 0x28) + (s64)*(s32*)(pcVar30 + 5) + (s64)iVar18 * 8);
                uVar21 = *(u64*)(*(s64*)(*(s64*)(lVar25 + 0x18) + 0x20) + (u64)*puVar13 * 8);
                if (uVar21 == uVar20) {
                    uVar12 = puVar13[1];
                    if ((s32)uVar12 < 0) goto block8_fallback;
                    pbVar14 = (u8*)(pcVar30 + (s32)uVar12);
                    break;
                }
                iVar3 = iVar18 + -1;
                if (uVar21 <= uVar20) { iVar17 = iVar18 + 1; iVar3 = iVar11; }
                iVar11 = iVar3;
            } while (iVar17 <= iVar11);
        } else {
        block8_fallback:
            pbVar14 = &DAT_7104741dbb;
        }
        if (*pbVar14 - 0xb < 2) {
            uVar20 = param_2 >> 0x28 & 0xffff;
            uVar10 = (u32)uVar20;
            if ((*(u32*)(pbVar14 + 1) <= uVar10) ||
                (uVar20 = FUN_7103269900(lVar25, uVar20), ((uVar20 ^ param_2) & 0xFFFFFFFFFFULL) != 0))
                goto block8_slow;
        } else {
        block8_slow:
            uVar10 = FUN_7103269fd0(lVar25, uVar16);
        }
        uVar12 = uVar10;
        if (cVar5 != '\f') goto block8_sentinel;
    block8_search2:
        uVar10 = uVar12;
        iVar11 = *(s32*)(pcVar30 + 1) + -1;
        if (*(s32*)(pcVar30 + 1) < 1) goto block8_sentinel;
        uVar20 = *(u64*)(lVar25 + 0x48) & 0xFFFFFFFFFFULL;
        iVar17 = 0;
        pbVar14 = &DAT_7104741dbb;
        do {
            iVar18 = iVar11 + iVar17;
            if (iVar18 < 0) iVar18 = iVar18 + 1;
            iVar18 = iVar18 >> 1;
            puVar13 = (u32*)(*(s64*)(*(s64*)(lVar25 + 0x18) + 0x28) + (s64)*(s32*)(pcVar30 + 5) + (s64)iVar18 * 8);
            uVar21 = *(u64*)(*(s64*)(*(s64*)(lVar25 + 0x18) + 0x20) + (u64)*puVar13 * 8);
            if (uVar21 == uVar20) {
                uVar12 = puVar13[1];
                if ((s32)uVar12 < 0) goto block8_sentinel;
                pbVar14 = (u8*)(pcVar30 + (s32)uVar12);
                break;
            }
            iVar3 = iVar18 + -1;
            if (uVar21 <= uVar20) { iVar17 = iVar18 + 1; iVar3 = iVar11; }
            iVar11 = iVar3;
        } while (iVar17 <= iVar11);
    } else {
        lVar25 = *(s64*)(*(s64*)(lVar29 + 0x1c8) + 8);
        pcVar30 = *(char**)(lVar25 + 0x20);
        uVar10 = 0xffffffff;
        uVar12 = 0xffffffff;
        if (*pcVar30 == '\f') goto block8_search2;
    block8_sentinel:
        pbVar14 = &DAT_7104741dbb;
    }
    if ((*pbVar14 - 0xb < 2) && (uVar10 < *(u32*)(pbVar14 + 1))) {
        FUN_7103269e30(&local_208, lVar25, uVar10);
        if ((*local_200 == '\f') && (iVar11 = *(s32*)(local_200 + 1) + -1, 0 < *(s32*)(local_200 + 1))) {
            iVar17 = 0;
            pcVar30 = "";
            do {
                iVar18 = iVar11 + iVar17;
                if (iVar18 < 0) iVar18 = iVar18 + 1;
                iVar18 = iVar18 >> 1;
                puVar13 = (u32*)(*(s64*)(((s64)uStack_204 << 32 | local_208) + 0x28) + (s64)*(s32*)(local_200 + 5) + (s64)iVar18 * 8);
                uVar20 = *(u64*)(*(s64*)(((s64)uStack_204 << 32 | local_208) + 0x20) + (u64)*puVar13 * 8);
                if (uVar20 == 0xdbb634436ULL) {
                    uVar12 = puVar13[1];
                    if ((s32)uVar12 < 0) goto block8_inner_fail;
                    pcVar30 = local_200 + (s32)uVar12;
                    break;
                }
                iVar3 = iVar18 + -1;
                if (uVar20 < 0xdbb634437ULL) { iVar17 = iVar18 + 1; iVar3 = iVar11; }
                iVar11 = iVar3;
            } while (iVar17 <= iVar11);
        } else {
        block8_inner_fail:
            pcVar30 = "";
        }
        uVar12 = prc_read_int(pcVar30);
    } else {
        uVar12 = 0;
    }
    param_1[0x56] = (u32)(f32)(s32)uVar12;

    // ══════════════════════════════════════════════════════════════
    // Block 9: param_1[0x58] — enum (hash 0xedd57a76e, default 1)
    // ══════════════════════════════════════════════════════════════
    if (bVar8 && bVar7) {
        lVar25 = *(s64*)(*(s64*)(lVar29 + 0x1c8) + 8);
        pcVar30 = *(char**)(lVar25 + 0x20);
        cVar5 = *pcVar30;
        if ((cVar5 == '\f') && (iVar11 = *(s32*)(pcVar30 + 1) + -1, 0 < *(s32*)(pcVar30 + 1))) {
            uVar20 = *(u64*)(lVar25 + 0x48) & 0xFFFFFFFFFFULL;
            iVar17 = 0;
            pbVar14 = &DAT_7104741dbb;
            do {
                iVar18 = iVar11 + iVar17;
                if (iVar18 < 0) iVar18 = iVar18 + 1;
                iVar18 = iVar18 >> 1;
                puVar13 = (u32*)(*(s64*)(*(s64*)(lVar25 + 0x18) + 0x28) + (s64)*(s32*)(pcVar30 + 5) + (s64)iVar18 * 8);
                uVar21 = *(u64*)(*(s64*)(*(s64*)(lVar25 + 0x18) + 0x20) + (u64)*puVar13 * 8);
                if (uVar21 == uVar20) {
                    uVar12 = puVar13[1];
                    if ((s32)uVar12 < 0) goto block9_fallback;
                    pbVar14 = (u8*)(pcVar30 + (s32)uVar12);
                    break;
                }
                iVar3 = iVar18 + -1;
                if (uVar21 <= uVar20) { iVar17 = iVar18 + 1; iVar3 = iVar11; }
                iVar11 = iVar3;
            } while (iVar17 <= iVar11);
        } else {
        block9_fallback:
            pbVar14 = &DAT_7104741dbb;
        }
        if (*pbVar14 - 0xb < 2) {
            uVar20 = param_2 >> 0x28 & 0xffff;
            uVar10 = (u32)uVar20;
            if ((*(u32*)(pbVar14 + 1) <= uVar10) ||
                (uVar20 = FUN_7103269900(lVar25, uVar20), ((uVar20 ^ param_2) & 0xFFFFFFFFFFULL) != 0))
                goto block9_slow;
        } else {
        block9_slow:
            uVar10 = FUN_7103269fd0(lVar25, uVar16);
        }
        uVar12 = uVar10;
        if (cVar5 != '\f') goto block9_sentinel;
    block9_search2:
        uVar10 = uVar12;
        iVar11 = *(s32*)(pcVar30 + 1) + -1;
        if (*(s32*)(pcVar30 + 1) < 1) goto block9_sentinel;
        uVar20 = *(u64*)(lVar25 + 0x48) & 0xFFFFFFFFFFULL;
        iVar17 = 0;
        pbVar14 = &DAT_7104741dbb;
        do {
            iVar18 = iVar11 + iVar17;
            if (iVar18 < 0) iVar18 = iVar18 + 1;
            iVar18 = iVar18 >> 1;
            puVar13 = (u32*)(*(s64*)(*(s64*)(lVar25 + 0x18) + 0x28) + (s64)*(s32*)(pcVar30 + 5) + (s64)iVar18 * 8);
            uVar21 = *(u64*)(*(s64*)(*(s64*)(lVar25 + 0x18) + 0x20) + (u64)*puVar13 * 8);
            if (uVar21 == uVar20) {
                uVar12 = puVar13[1];
                if ((s32)uVar12 < 0) goto block9_sentinel;
                pbVar14 = (u8*)(pcVar30 + (s32)uVar12);
                break;
            }
            iVar3 = iVar18 + -1;
            if (uVar21 <= uVar20) { iVar17 = iVar18 + 1; iVar3 = iVar11; }
            iVar11 = iVar3;
        } while (iVar17 <= iVar11);
    } else {
        lVar25 = *(s64*)(*(s64*)(lVar29 + 0x1c8) + 8);
        pcVar30 = *(char**)(lVar25 + 0x20);
        uVar10 = 0xffffffff;
        uVar12 = 0xffffffff;
        if (*pcVar30 == '\f') goto block9_search2;
    block9_sentinel:
        pbVar14 = &DAT_7104741dbb;
    }
    if ((*pbVar14 - 0xb < 2) && (uVar10 < *(u32*)(pbVar14 + 1))) {
        FUN_7103269e30(&local_208, lVar25, uVar10);
        if ((*local_200 == '\f') && (iVar11 = *(s32*)(local_200 + 1) + -1, 0 < *(s32*)(local_200 + 1))) {
            lVar25 = ((s64)uStack_204 << 32) | local_208;
            iVar17 = 0;
            pcVar30 = "";
            do {
                iVar18 = iVar11 + iVar17;
                if (iVar18 < 0) iVar18 = iVar18 + 1;
                iVar18 = iVar18 >> 1;
                puVar13 = (u32*)(*(s64*)(lVar25 + 0x28) + (s64)*(s32*)(local_200 + 5) + (s64)iVar18 * 8);
                uVar20 = *(u64*)(*(s64*)(lVar25 + 0x20) + (u64)*puVar13 * 8);
                if (uVar20 == 0xedd57a76eULL) {
                    uVar12 = puVar13[1];
                    if ((s32)uVar12 < 0) goto block9_inner_fail;
                    pcVar30 = local_200 + (s32)uVar12;
                    goto block9_inner_done;
                }
                iVar3 = iVar18 + -1;
                if (uVar20 < 0xedd57a76fULL) { iVar17 = iVar18 + 1; iVar3 = iVar11; }
                iVar11 = iVar3;
            } while (iVar17 <= iVar11);
            lVar25 = 0;
        } else {
        block9_inner_fail:
            lVar25 = 0;
            pcVar30 = "";
        }
    block9_inner_done:
        if (*pcVar30 != '\t') goto block9_default;
        uVar20 = *(u64*)(*(s64*)(lVar25 + 0x20) + (s64)*(s32*)(pcVar30 + 1) * 8);
    } else {
    block9_default:
        uVar20 = 0;
    }
    uVar12 = 1;
    if ((uVar20 & 0xFFFFFFFFFFULL) == 0x801a59f9fULL) { uVar12 = 2; }
    uVar10 = 3;
    if ((uVar20 & 0xFFFFFFFFFFULL) != 0x876a2af09ULL) { uVar10 = uVar12; }
    param_1[0x58] = uVar10;

    // ══════════════════════════════════════════════════════════════
    // Block 10: *puVar2 (param_1[0x59]) — int (hash 0xe0ce7eed4)
    // ══════════════════════════════════════════════════════════════
    if (bVar8 && bVar7) {
        lVar25 = *(s64*)(*(s64*)(lVar29 + 0x1c8) + 8);
        pcVar30 = *(char**)(lVar25 + 0x20);
        cVar5 = *pcVar30;
        if ((cVar5 == '\f') && (iVar11 = *(s32*)(pcVar30 + 1) + -1, 0 < *(s32*)(pcVar30 + 1))) {
            uVar20 = *(u64*)(lVar25 + 0x48) & 0xFFFFFFFFFFULL;
            iVar17 = 0;
            pbVar14 = &DAT_7104741dbb;
            do {
                iVar18 = iVar11 + iVar17;
                if (iVar18 < 0) iVar18 = iVar18 + 1;
                iVar18 = iVar18 >> 1;
                puVar13 = (u32*)(*(s64*)(*(s64*)(lVar25 + 0x18) + 0x28) + (s64)*(s32*)(pcVar30 + 5) + (s64)iVar18 * 8);
                uVar21 = *(u64*)(*(s64*)(*(s64*)(lVar25 + 0x18) + 0x20) + (u64)*puVar13 * 8);
                if (uVar21 == uVar20) {
                    uVar12 = puVar13[1];
                    if ((s32)uVar12 < 0) goto block10_fallback;
                    pbVar14 = (u8*)(pcVar30 + (s32)uVar12);
                    break;
                }
                iVar3 = iVar18 + -1;
                if (uVar21 <= uVar20) { iVar17 = iVar18 + 1; iVar3 = iVar11; }
                iVar11 = iVar3;
            } while (iVar17 <= iVar11);
        } else {
        block10_fallback:
            pbVar14 = &DAT_7104741dbb;
        }
        if (*pbVar14 - 0xb < 2) {
            uVar20 = param_2 >> 0x28 & 0xffff;
            uVar10 = (u32)uVar20;
            if ((*(u32*)(pbVar14 + 1) <= uVar10) ||
                (uVar20 = FUN_7103269900(lVar25, uVar20), ((uVar20 ^ param_2) & 0xFFFFFFFFFFULL) != 0))
                goto block10_slow;
        } else {
        block10_slow:
            uVar10 = FUN_7103269fd0(lVar25, uVar16);
        }
        uVar12 = uVar10;
        if (cVar5 != '\f') goto block10_sentinel;
    block10_search2:
        uVar10 = uVar12;
        iVar11 = *(s32*)(pcVar30 + 1) + -1;
        if (*(s32*)(pcVar30 + 1) < 1) goto block10_sentinel;
        uVar20 = *(u64*)(lVar25 + 0x48) & 0xFFFFFFFFFFULL;
        iVar17 = 0;
        pbVar14 = &DAT_7104741dbb;
        do {
            iVar18 = iVar11 + iVar17;
            if (iVar18 < 0) iVar18 = iVar18 + 1;
            iVar18 = iVar18 >> 1;
            puVar13 = (u32*)(*(s64*)(*(s64*)(lVar25 + 0x18) + 0x28) + (s64)*(s32*)(pcVar30 + 5) + (s64)iVar18 * 8);
            uVar21 = *(u64*)(*(s64*)(*(s64*)(lVar25 + 0x18) + 0x20) + (u64)*puVar13 * 8);
            if (uVar21 == uVar20) {
                uVar12 = puVar13[1];
                if ((s32)uVar12 < 0) goto block10_sentinel;
                pbVar14 = (u8*)(pcVar30 + (s32)uVar12);
                break;
            }
            iVar3 = iVar18 + -1;
            if (uVar21 <= uVar20) { iVar17 = iVar18 + 1; iVar3 = iVar11; }
            iVar11 = iVar3;
        } while (iVar17 <= iVar11);
    } else {
        lVar25 = *(s64*)(*(s64*)(lVar29 + 0x1c8) + 8);
        pcVar30 = *(char**)(lVar25 + 0x20);
        uVar10 = 0xffffffff;
        uVar12 = 0xffffffff;
        if (*pcVar30 == '\f') goto block10_search2;
    block10_sentinel:
        pbVar14 = &DAT_7104741dbb;
    }
    if ((*pbVar14 - 0xb < 2) && (uVar10 < *(u32*)(pbVar14 + 1))) {
        FUN_7103269e30(&local_208, lVar25, uVar10);
        if ((*local_200 == '\f') && (iVar11 = *(s32*)(local_200 + 1) + -1, 0 < *(s32*)(local_200 + 1))) {
            iVar17 = 0;
            pcVar30 = "";
            do {
                iVar18 = iVar11 + iVar17;
                if (iVar18 < 0) iVar18 = iVar18 + 1;
                iVar18 = iVar18 >> 1;
                puVar13 = (u32*)(*(s64*)(((s64)uStack_204 << 32 | local_208) + 0x28) + (s64)*(s32*)(local_200 + 5) + (s64)iVar18 * 8);
                uVar20 = *(u64*)(*(s64*)(((s64)uStack_204 << 32 | local_208) + 0x20) + (u64)*puVar13 * 8);
                if (uVar20 == 0xe0ce7eed4ULL) {
                    uVar12 = puVar13[1];
                    if ((s32)uVar12 < 0) goto block10_inner_fail;
                    pcVar30 = local_200 + (s32)uVar12;
                    break;
                }
                iVar3 = iVar18 + -1;
                if (uVar20 < 0xe0ce7eed5ULL) { iVar17 = iVar18 + 1; iVar3 = iVar11; }
                iVar11 = iVar3;
            } while (iVar17 <= iVar11);
        } else {
        block10_inner_fail:
            pcVar30 = "";
        }
        uVar12 = prc_read_int(pcVar30);
    } else {
        uVar12 = 0;
    }
    *puVar2 = uVar12;

    // ══════════════════════════════════════════════════════════════
    // Block 11: param_1[0x5a] — int (hash 0x10207e4f7d)
    // ══════════════════════════════════════════════════════════════
    if (bVar8 && bVar7) {
        lVar25 = *(s64*)(*(s64*)(lVar29 + 0x1c8) + 8);
        pcVar30 = *(char**)(lVar25 + 0x20);
        cVar5 = *pcVar30;
        if ((cVar5 == '\f') && (iVar11 = *(s32*)(pcVar30 + 1) + -1, 0 < *(s32*)(pcVar30 + 1))) {
            uVar20 = *(u64*)(lVar25 + 0x48) & 0xFFFFFFFFFFULL;
            iVar17 = 0;
            pbVar14 = &DAT_7104741dbb;
            do {
                iVar18 = iVar11 + iVar17;
                if (iVar18 < 0) iVar18 = iVar18 + 1;
                iVar18 = iVar18 >> 1;
                puVar13 = (u32*)(*(s64*)(*(s64*)(lVar25 + 0x18) + 0x28) + (s64)*(s32*)(pcVar30 + 5) + (s64)iVar18 * 8);
                uVar21 = *(u64*)(*(s64*)(*(s64*)(lVar25 + 0x18) + 0x20) + (u64)*puVar13 * 8);
                if (uVar21 == uVar20) {
                    uVar12 = puVar13[1];
                    if ((s32)uVar12 < 0) goto block11_fallback;
                    pbVar14 = (u8*)(pcVar30 + (s32)uVar12);
                    break;
                }
                iVar3 = iVar18 + -1;
                if (uVar21 <= uVar20) { iVar17 = iVar18 + 1; iVar3 = iVar11; }
                iVar11 = iVar3;
            } while (iVar17 <= iVar11);
        } else {
        block11_fallback:
            pbVar14 = &DAT_7104741dbb;
        }
        if (*pbVar14 - 0xb < 2) {
            uVar20 = param_2 >> 0x28 & 0xffff;
            uVar10 = (u32)uVar20;
            if ((*(u32*)(pbVar14 + 1) <= uVar10) ||
                (uVar20 = FUN_7103269900(lVar25, uVar20), ((uVar20 ^ param_2) & 0xFFFFFFFFFFULL) != 0))
                goto block11_slow;
        } else {
        block11_slow:
            uVar10 = FUN_7103269fd0(lVar25, uVar16);
        }
        uVar12 = uVar10;
        if (cVar5 != '\f') goto block11_sentinel;
    block11_search2:
        uVar10 = uVar12;
        iVar11 = *(s32*)(pcVar30 + 1) + -1;
        if (*(s32*)(pcVar30 + 1) < 1) goto block11_sentinel;
        uVar20 = *(u64*)(lVar25 + 0x48) & 0xFFFFFFFFFFULL;
        iVar17 = 0;
        pbVar14 = &DAT_7104741dbb;
        do {
            iVar18 = iVar11 + iVar17;
            if (iVar18 < 0) iVar18 = iVar18 + 1;
            iVar18 = iVar18 >> 1;
            puVar13 = (u32*)(*(s64*)(*(s64*)(lVar25 + 0x18) + 0x28) + (s64)*(s32*)(pcVar30 + 5) + (s64)iVar18 * 8);
            uVar21 = *(u64*)(*(s64*)(*(s64*)(lVar25 + 0x18) + 0x20) + (u64)*puVar13 * 8);
            if (uVar21 == uVar20) {
                uVar12 = puVar13[1];
                if ((s32)uVar12 < 0) goto block11_sentinel;
                pbVar14 = (u8*)(pcVar30 + (s32)uVar12);
                break;
            }
            iVar3 = iVar18 + -1;
            if (uVar21 <= uVar20) { iVar17 = iVar18 + 1; iVar3 = iVar11; }
            iVar11 = iVar3;
        } while (iVar17 <= iVar11);
    } else {
        lVar25 = *(s64*)(*(s64*)(lVar29 + 0x1c8) + 8);
        pcVar30 = *(char**)(lVar25 + 0x20);
        uVar10 = 0xffffffff;
        uVar12 = 0xffffffff;
        if (*pcVar30 == '\f') goto block11_search2;
    block11_sentinel:
        pbVar14 = &DAT_7104741dbb;
    }
    if ((*pbVar14 - 0xb < 2) && (uVar10 < *(u32*)(pbVar14 + 1))) {
        FUN_7103269e30(&local_208, lVar25, uVar10);
        if ((*local_200 == '\f') && (iVar11 = *(s32*)(local_200 + 1) + -1, 0 < *(s32*)(local_200 + 1))) {
            iVar17 = 0;
            pcVar30 = "";
            do {
                iVar18 = iVar11 + iVar17;
                if (iVar18 < 0) iVar18 = iVar18 + 1;
                iVar18 = iVar18 >> 1;
                puVar13 = (u32*)(*(s64*)(((s64)uStack_204 << 32 | local_208) + 0x28) + (s64)*(s32*)(local_200 + 5) + (s64)iVar18 * 8);
                uVar20 = *(u64*)(*(s64*)(((s64)uStack_204 << 32 | local_208) + 0x20) + (u64)*puVar13 * 8);
                if (uVar20 == 0x10207e4f7dULL) {
                    uVar12 = puVar13[1];
                    if ((s32)uVar12 < 0) goto block11_inner_fail;
                    pcVar30 = local_200 + (s32)uVar12;
                    break;
                }
                iVar3 = iVar18 + -1;
                if (uVar20 < 0x10207e4f7eULL) { iVar17 = iVar18 + 1; iVar3 = iVar11; }
                iVar11 = iVar3;
            } while (iVar17 <= iVar11);
        } else {
        block11_inner_fail:
            pcVar30 = "";
        }
        uVar12 = prc_read_int(pcVar30);
    } else {
        uVar12 = 0;
    }
    param_1[0x5a] = uVar12;
    param_1[0x5b] = 0;

    // ══════════════════════════════════════════════════════════════
    // Block 12: param_1[0x5c] — enum (hash 0xf27a105ce)
    // Note: lVar29 is consumed here (overwritten)
    // ══════════════════════════════════════════════════════════════
    if (bVar8 && bVar7) {
        lVar29 = *(s64*)(*(s64*)(lVar29 + 0x1c8) + 8);
        pcVar30 = *(char**)(lVar29 + 0x20);
        cVar5 = *pcVar30;
        if ((cVar5 == '\f') && (iVar11 = *(s32*)(pcVar30 + 1) + -1, 0 < *(s32*)(pcVar30 + 1))) {
            uVar20 = *(u64*)(lVar29 + 0x48) & 0xFFFFFFFFFFULL;
            iVar17 = 0;
            pbVar14 = &DAT_7104741dbb;
            do {
                iVar18 = iVar11 + iVar17;
                if (iVar18 < 0) iVar18 = iVar18 + 1;
                iVar18 = iVar18 >> 1;
                puVar13 = (u32*)(*(s64*)(*(s64*)(lVar29 + 0x18) + 0x28) + (s64)*(s32*)(pcVar30 + 5) + (s64)iVar18 * 8);
                uVar21 = *(u64*)(*(s64*)(*(s64*)(lVar29 + 0x18) + 0x20) + (u64)*puVar13 * 8);
                if (uVar21 == uVar20) {
                    uVar12 = puVar13[1];
                    if ((s32)uVar12 < 0) goto block12_fallback;
                    pbVar14 = (u8*)(pcVar30 + (s32)uVar12);
                    break;
                }
                iVar3 = iVar18 + -1;
                if (uVar21 <= uVar20) { iVar17 = iVar18 + 1; iVar3 = iVar11; }
                iVar11 = iVar3;
            } while (iVar17 <= iVar11);
        } else {
        block12_fallback:
            pbVar14 = &DAT_7104741dbb;
        }
        if (*pbVar14 - 0xb < 2) {
            uVar20 = param_2 >> 0x28 & 0xffff;
            uVar10 = (u32)uVar20;
            if ((*(u32*)(pbVar14 + 1) <= uVar10) ||
                (uVar20 = FUN_7103269900(lVar29, uVar20), ((uVar20 ^ param_2) & 0xFFFFFFFFFFULL) != 0))
                goto block12_slow;
        } else {
        block12_slow:
            uVar10 = FUN_7103269fd0(lVar29, uVar16);
        }
        uVar12 = uVar10;
        if (cVar5 != '\f') goto block12_sentinel;
    block12_search2:
        uVar10 = uVar12;
        iVar11 = *(s32*)(pcVar30 + 1) + -1;
        if (*(s32*)(pcVar30 + 1) < 1) goto block12_sentinel;
        uVar20 = *(u64*)(lVar29 + 0x48) & 0xFFFFFFFFFFULL;
        iVar17 = 0;
        pbVar14 = &DAT_7104741dbb;
        do {
            iVar18 = iVar11 + iVar17;
            if (iVar18 < 0) iVar18 = iVar18 + 1;
            iVar18 = iVar18 >> 1;
            puVar13 = (u32*)(*(s64*)(*(s64*)(lVar29 + 0x18) + 0x28) + (s64)*(s32*)(pcVar30 + 5) + (s64)iVar18 * 8);
            uVar21 = *(u64*)(*(s64*)(*(s64*)(lVar29 + 0x18) + 0x20) + (u64)*puVar13 * 8);
            if (uVar21 == uVar20) {
                uVar12 = puVar13[1];
                if ((s32)uVar12 < 0) goto block12_sentinel;
                pbVar14 = (u8*)(pcVar30 + (s32)uVar12);
                break;
            }
            iVar3 = iVar18 + -1;
            if (uVar21 <= uVar20) { iVar17 = iVar18 + 1; iVar3 = iVar11; }
            iVar11 = iVar3;
        } while (iVar17 <= iVar11);
    } else {
        lVar29 = *(s64*)(*(s64*)(lVar29 + 0x1c8) + 8);
        pcVar30 = *(char**)(lVar29 + 0x20);
        uVar10 = 0xffffffff;
        uVar12 = 0xffffffff;
        if (*pcVar30 == '\f') goto block12_search2;
    block12_sentinel:
        pbVar14 = &DAT_7104741dbb;
    }
    if ((*pbVar14 - 0xb < 2) && (uVar10 < *(u32*)(pbVar14 + 1))) {
        FUN_7103269e30(&local_208, lVar29, uVar10);
        if ((*local_200 == '\f') && (iVar11 = *(s32*)(local_200 + 1) + -1, 0 < *(s32*)(local_200 + 1))) {
            lVar29 = ((s64)uStack_204 << 32) | local_208;
            iVar17 = 0;
            pcVar30 = "";
            do {
                iVar18 = iVar11 + iVar17;
                if (iVar18 < 0) iVar18 = iVar18 + 1;
                iVar18 = iVar18 >> 1;
                puVar13 = (u32*)(*(s64*)(lVar29 + 0x28) + (s64)*(s32*)(local_200 + 5) + (s64)iVar18 * 8);
                uVar20 = *(u64*)(*(s64*)(lVar29 + 0x20) + (u64)*puVar13 * 8);
                if (uVar20 == 0xf27a105ceULL) {
                    uVar12 = puVar13[1];
                    if ((s32)uVar12 < 0) goto block12_inner_fail;
                    pcVar30 = local_200 + (s32)uVar12;
                    goto block12_inner_done;
                }
                iVar3 = iVar18 + -1;
                if (uVar20 < 0xf27a105cfULL) { iVar17 = iVar18 + 1; iVar3 = iVar11; }
                iVar11 = iVar3;
            } while (iVar17 <= iVar11);
            lVar29 = 0;
        } else {
        block12_inner_fail:
            lVar29 = 0;
            pcVar30 = "";
        }
    block12_inner_done:
        if (*pcVar30 != '\t') goto block12_default;
        uVar20 = *(u64*)(*(s64*)(lVar29 + 0x20) + (s64)*(s32*)(pcVar30 + 1) * 8) & 0xFFFFFFFFFFULL;
        if (uVar20 < 0x876a2af09ULL) {
            if (uVar20 == 0x47f9000cfULL) { param_1[0x5c] = 1; }
            else { if (uVar20 != 0x801a59f9fULL) goto block12_default; param_1[0x5c] = 3; }
        } else if (uVar20 == 0x876a2af09ULL) { param_1[0x5c] = 4; }
        else { if (uVar20 != 0x898acce25ULL) goto block12_default; param_1[0x5c] = 2; }
    } else {
    block12_default:
        param_1[0x5c] = 0;
    }

    // ══════════════════════════════════════════════════════════════
    // Path block: param_1[0x5e] — complex path hash resolution
    // Uses hashes 0xc80dc473d, 0xd8fe20293, 0x8aed77546
    // ══════════════════════════════════════════════════════════════
    if (bVar8 && bVar7) {
        lVar29 = *(s64*)(DAT_710532e730 + 8);
        lVar25 = *(s64*)(lVar29 + 0x1c8);
        lVar27 = *(s64*)(lVar25 + 8);
        pcVar30 = *(char**)(lVar27 + 0x20);
        if ((*pcVar30 == '\f') && (iVar11 = *(s32*)(pcVar30 + 1) + -1, 0 < *(s32*)(pcVar30 + 1))) {
            uVar20 = *(u64*)(lVar27 + 0x48) & 0xFFFFFFFFFFULL;
            iVar17 = 0;
            pbVar14 = &DAT_7104741dbb;
            do {
                iVar18 = iVar11 + iVar17;
                if (iVar18 < 0) iVar18 = iVar18 + 1;
                iVar18 = iVar18 >> 1;
                puVar13 = (u32*)(*(s64*)(*(s64*)(lVar27 + 0x18) + 0x28) + (s64)*(s32*)(pcVar30 + 5) + (s64)iVar18 * 8);
                uVar21 = *(u64*)(*(s64*)(*(s64*)(lVar27 + 0x18) + 0x20) + (u64)*puVar13 * 8);
                if (uVar21 == uVar20) {
                    uVar12 = puVar13[1];
                    if ((s32)uVar12 < 0) goto path_fallback1;
                    pbVar14 = (u8*)(pcVar30 + (s32)uVar12);
                    break;
                }
                iVar3 = iVar18 + -1;
                if (uVar21 <= uVar20) { iVar17 = iVar18 + 1; iVar3 = iVar11; }
                iVar11 = iVar3;
            } while (iVar17 <= iVar11);
        } else {
        path_fallback1:
            pbVar14 = &DAT_7104741dbb;
        }
        uVar20 = param_2 >> 0x28 & 0xffff;
        uVar12 = (u32)uVar20;
        if (((1 < *pbVar14 - 0xb) || (*(u32*)(pbVar14 + 1) <= uVar12)) ||
            (uVar21 = FUN_7103269900(lVar27, uVar20), uVar10 = uVar12,
             ((uVar21 ^ param_2) & 0xFFFFFFFFFFULL) != 0)) {
            uVar10 = FUN_7103269fd0(lVar27, uVar16);
        }
        if ((*pcVar30 == '\f') && (iVar11 = *(s32*)(pcVar30 + 1) + -1, 0 < *(s32*)(pcVar30 + 1))) {
            uVar21 = *(u64*)(lVar27 + 0x48) & 0xFFFFFFFFFFULL;
            iVar17 = 0;
            pbVar14 = &DAT_7104741dbb;
            do {
                iVar18 = iVar11 + iVar17;
                if (iVar18 < 0) iVar18 = iVar18 + 1;
                iVar18 = iVar18 >> 1;
                puVar13 = (u32*)(*(s64*)(*(s64*)(lVar27 + 0x18) + 0x28) + (s64)*(s32*)(pcVar30 + 5) + (s64)iVar18 * 8);
                uVar22 = *(u64*)(*(s64*)(*(s64*)(lVar27 + 0x18) + 0x20) + (u64)*puVar13 * 8);
                if (uVar22 == uVar21) {
                    uVar15 = puVar13[1];
                    if ((s32)uVar15 < 0) goto path_sentinel1;
                    pbVar14 = (u8*)(pcVar30 + (s32)uVar15);
                    break;
                }
                iVar3 = iVar18 + -1;
                if (uVar22 <= uVar21) { iVar17 = iVar18 + 1; iVar3 = iVar11; }
                iVar11 = iVar3;
            } while (iVar17 <= iVar11);
        } else {
        path_sentinel1:
            pbVar14 = &DAT_7104741dbb;
        }
        if ((*pbVar14 - 0xb < 2) && (uVar10 < *(u32*)(pbVar14 + 1))) {
            FUN_7103269e30(&local_208, lVar27, uVar10);
            if ((*local_200 == '\f') && (iVar11 = *(s32*)(local_200 + 1) + -1, 0 < *(s32*)(local_200 + 1))) {
                lVar25 = ((s64)uStack_204 << 32) | local_208;
                iVar17 = 0;
                pcVar30 = "";
                do {
                    iVar18 = iVar11 + iVar17;
                    if (iVar18 < 0) iVar18 = iVar18 + 1;
                    iVar18 = iVar18 >> 1;
                    puVar13 = (u32*)(*(s64*)(lVar25 + 0x28) + (s64)*(s32*)(local_200 + 5) + (s64)iVar18 * 8);
                    uVar21 = *(u64*)(*(s64*)(lVar25 + 0x20) + (u64)*puVar13 * 8);
                    if (uVar21 == 0xc80dc473dULL) {
                        uVar10 = puVar13[1];
                        if ((s32)uVar10 < 0) goto path_inner1_fail;
                        pcVar30 = local_200 + (s32)uVar10;
                        goto path_inner1_done;
                    }
                    iVar3 = iVar18 + -1;
                    if (uVar21 < 0xc80dc473eULL) { iVar17 = iVar18 + 1; iVar3 = iVar11; }
                    iVar11 = iVar3;
                } while (iVar17 <= iVar11);
                lVar25 = 0;
            } else {
            path_inner1_fail:
                lVar25 = 0;
                pcVar30 = "";
            }
        path_inner1_done:
            if (*pcVar30 == '\t') {
                uVar21 = *(u64*)(*(s64*)(lVar25 + 0x20) + (s64)*(s32*)(pcVar30 + 1) * 8);
            } else {
                uVar21 = 0;
            }
            lVar25 = *(s64*)(lVar29 + 0x1c8);
        } else {
            uVar21 = 0;
        }

        // Second path lookup: hash 0xd8fe20293
        lVar27 = *(s64*)(lVar25 + 8);
        pcVar30 = *(char**)(lVar27 + 0x20);
        if ((*pcVar30 == '\f') && (iVar11 = *(s32*)(pcVar30 + 1) + -1, 0 < *(s32*)(pcVar30 + 1))) {
            uVar22 = *(u64*)(lVar27 + 0x48) & 0xFFFFFFFFFFULL;
            iVar17 = 0;
            pbVar14 = &DAT_7104741dbb;
            do {
                iVar18 = iVar11 + iVar17;
                if (iVar18 < 0) iVar18 = iVar18 + 1;
                iVar18 = iVar18 >> 1;
                puVar13 = (u32*)(*(s64*)(*(s64*)(lVar27 + 0x18) + 0x28) + (s64)*(s32*)(pcVar30 + 5) + (s64)iVar18 * 8);
                u64 uVar23 = *(u64*)(*(s64*)(*(s64*)(lVar27 + 0x18) + 0x20) + (u64)*puVar13 * 8);
                if (uVar23 == uVar22) {
                    uVar10 = puVar13[1];
                    if ((s32)uVar10 < 0) goto path_fallback2;
                    pbVar14 = (u8*)(pcVar30 + (s32)uVar10);
                    break;
                }
                iVar3 = iVar18 + -1;
                if (uVar23 <= uVar22) { iVar17 = iVar18 + 1; iVar3 = iVar11; }
                iVar11 = iVar3;
            } while (iVar17 <= iVar11);
        } else {
        path_fallback2:
            pbVar14 = &DAT_7104741dbb;
        }
        if (((1 < *pbVar14 - 0xb) || (*(u32*)(pbVar14 + 1) <= uVar12)) ||
            (uVar22 = FUN_7103269900(lVar27, uVar20), uVar10 = uVar12,
             ((uVar22 ^ param_2) & 0xFFFFFFFFFFULL) != 0)) {
            uVar10 = FUN_7103269fd0(lVar27, uVar16);
        }
        if ((*pcVar30 == '\f') && (iVar11 = *(s32*)(pcVar30 + 1) + -1, 0 < *(s32*)(pcVar30 + 1))) {
            uVar22 = *(u64*)(lVar27 + 0x48) & 0xFFFFFFFFFFULL;
            iVar17 = 0;
            pbVar14 = &DAT_7104741dbb;
            do {
                iVar18 = iVar11 + iVar17;
                if (iVar18 < 0) iVar18 = iVar18 + 1;
                iVar18 = iVar18 >> 1;
                puVar13 = (u32*)(*(s64*)(*(s64*)(lVar27 + 0x18) + 0x28) + (s64)*(s32*)(pcVar30 + 5) + (s64)iVar18 * 8);
                u64 uVar23 = *(u64*)(*(s64*)(*(s64*)(lVar27 + 0x18) + 0x20) + (u64)*puVar13 * 8);
                if (uVar23 == uVar22) {
                    uVar15 = puVar13[1];
                    if ((s32)uVar15 < 0) goto path_sentinel2;
                    pbVar14 = (u8*)(pcVar30 + (s32)uVar15);
                    break;
                }
                iVar3 = iVar18 + -1;
                if (uVar23 <= uVar22) { iVar17 = iVar18 + 1; iVar3 = iVar11; }
                iVar11 = iVar3;
            } while (iVar17 <= iVar11);
        } else {
        path_sentinel2:
            pbVar14 = &DAT_7104741dbb;
        }
        if ((*pbVar14 - 0xb < 2) && (uVar10 < *(u32*)(pbVar14 + 1))) {
            FUN_7103269e30(&local_208, lVar27, uVar10);
            if ((*local_200 == '\f') && (iVar11 = *(s32*)(local_200 + 1) + -1, 0 < *(s32*)(local_200 + 1))) {
                lVar25 = ((s64)uStack_204 << 32) | local_208;
                iVar17 = 0;
                pcVar30 = "";
                do {
                    iVar18 = iVar11 + iVar17;
                    if (iVar18 < 0) iVar18 = iVar18 + 1;
                    iVar18 = iVar18 >> 1;
                    puVar13 = (u32*)(*(s64*)(lVar25 + 0x28) + (s64)*(s32*)(local_200 + 5) + (s64)iVar18 * 8);
                    uVar22 = *(u64*)(*(s64*)(lVar25 + 0x20) + (u64)*puVar13 * 8);
                    if (uVar22 == 0xd8fe20293ULL) {
                        uVar10 = puVar13[1];
                        if ((s32)uVar10 < 0) goto path_inner2_fail;
                        pcVar30 = local_200 + (s32)uVar10;
                        goto path_inner2_done;
                    }
                    iVar3 = iVar18 + -1;
                    if (uVar22 < 0xd8fe20294ULL) { iVar17 = iVar18 + 1; iVar3 = iVar11; }
                    iVar11 = iVar3;
                } while (iVar17 <= iVar11);
                lVar25 = 0;
            } else {
            path_inner2_fail:
                lVar25 = 0;
                pcVar30 = "";
            }
        path_inner2_done:
            if (*pcVar30 == '\t') {
                uVar22 = *(u64*)(*(s64*)(lVar25 + 0x20) + (s64)*(s32*)(pcVar30 + 1) * 8);
            } else {
                uVar22 = 0;
            }
            lVar25 = *(s64*)(lVar29 + 0x1c8);
        } else {
            uVar22 = 0;
        }

        // Path resolution using auxiliary data
        FUN_7103291bf0(auStack_b0, lVar25, param_2);
        uVar21 = uVar21 & 0xFFFFFFFFFFULL;
        if (uVar21 == 0) goto path_store;
        if ((((uVar22 & 0xFFFFFFFFFFULL) != 0) || (local_ac != 0)) &&
            (iVar11 = FUN_7103238e80(), iVar11 != 0x2f)) {
            if ((u32)(iVar11 - 0x21) < 2) {
                // Mode 0x21-0x22: build BNTX texture path
                FUN_7103291bf0(auStack_f8, *(u64*)(lVar29 + 0x1c8), param_2);

                // Inner block: hash 0x8aed77546 (bool from int)
                lVar29 = *(s64*)(*(s64*)(lVar29 + 0x1c8) + 8);
                pcVar30 = *(char**)(lVar29 + 0x20);
                cVar5 = *pcVar30;
                if ((cVar5 == '\f') && (iVar17 = *(s32*)(pcVar30 + 1) + -1, 0 < *(s32*)(pcVar30 + 1))) {
                    uVar21 = *(u64*)(lVar29 + 0x48) & 0xFFFFFFFFFFULL;
                    iVar18 = 0;
                    pbVar14 = &DAT_7104741dbb;
                    do {
                        iVar3 = iVar17 + iVar18;
                        if (iVar3 < 0) iVar3 = iVar3 + 1;
                        iVar3 = iVar3 >> 1;
                        puVar13 = (u32*)(*(s64*)(*(s64*)(lVar29 + 0x18) + 0x28) + (s64)*(s32*)(pcVar30 + 5) + (s64)iVar3 * 8);
                        uVar22 = *(u64*)(*(s64*)(*(s64*)(lVar29 + 0x18) + 0x20) + (u64)*puVar13 * 8);
                        if (uVar22 == uVar21) {
                            uVar10 = puVar13[1];
                            if ((s32)uVar10 < 0) goto path_inner3_fallback;
                            pbVar14 = (u8*)(pcVar30 + (s32)uVar10);
                            break;
                        }
                        s32 iVar6 = iVar3 + -1;
                        if (uVar22 <= uVar21) { iVar18 = iVar3 + 1; iVar6 = iVar17; }
                        iVar17 = iVar6;
                    } while (iVar18 <= iVar17);
                } else {
                path_inner3_fallback:
                    pbVar14 = &DAT_7104741dbb;
                }
                if (((1 < *pbVar14 - 0xb) || (*(u32*)(pbVar14 + 1) <= uVar12)) ||
                    (uVar20 = FUN_7103269900(lVar29, uVar20), ((uVar20 ^ param_2) & 0xFFFFFFFFFFULL) != 0)) {
                    uVar12 = FUN_7103269fd0(lVar29, uVar16);
                }
                if ((cVar5 == '\f') && (iVar17 = *(s32*)(pcVar30 + 1) + -1, 0 < *(s32*)(pcVar30 + 1))) {
                    uVar16 = *(u64*)(lVar29 + 0x48) & 0xFFFFFFFFFFULL;
                    iVar18 = 0;
                    pbVar14 = &DAT_7104741dbb;
                    do {
                        iVar3 = iVar17 + iVar18;
                        if (iVar3 < 0) iVar3 = iVar3 + 1;
                        iVar3 = iVar3 >> 1;
                        puVar13 = (u32*)(*(s64*)(*(s64*)(lVar29 + 0x18) + 0x28) + (s64)*(s32*)(pcVar30 + 5) + (s64)iVar3 * 8);
                        uVar20 = *(u64*)(*(s64*)(*(s64*)(lVar29 + 0x18) + 0x20) + (u64)*puVar13 * 8);
                        if (uVar20 == uVar16) {
                            uVar10 = puVar13[1];
                            if ((s32)uVar10 < 0) goto path_inner3_sentinel;
                            pbVar14 = (u8*)(pcVar30 + (s32)uVar10);
                            break;
                        }
                        s32 iVar6 = iVar3 + -1;
                        if (uVar20 <= uVar16) { iVar18 = iVar3 + 1; iVar6 = iVar17; }
                        iVar17 = iVar6;
                    } while (iVar18 <= iVar17);
                } else {
                path_inner3_sentinel:
                    pbVar14 = &DAT_7104741dbb;
                }
                if ((*pbVar14 - 0xb < 2) && (uVar12 < *(u32*)(pbVar14 + 1))) {
                    FUN_7103269e30(&local_208, lVar29, uVar12);
                    if ((*local_200 == '\f') && (iVar17 = *(s32*)(local_200 + 1) + -1, 0 < *(s32*)(local_200 + 1))) {
                        iVar18 = 0;
                        pcVar30 = "";
                        do {
                            iVar3 = iVar17 + iVar18;
                            if (iVar3 < 0) iVar3 = iVar3 + 1;
                            iVar3 = iVar3 >> 1;
                            puVar13 = (u32*)(*(s64*)(((s64)uStack_204 << 32 | local_208) + 0x28) + (s64)*(s32*)(local_200 + 5) + (s64)iVar3 * 8);
                            uVar16 = *(u64*)(*(s64*)(((s64)uStack_204 << 32 | local_208) + 0x20) + (u64)*puVar13 * 8);
                            if (uVar16 == 0x8aed77546ULL) {
                                uVar12 = puVar13[1];
                                if ((s32)uVar12 < 0) goto path_inner3_inner_fail;
                                pcVar30 = local_200 + (s32)uVar12;
                                break;
                            }
                            s32 iVar6 = iVar3 + -1;
                            if (uVar16 < 0x8aed77547ULL) { iVar18 = iVar3 + 1; iVar6 = iVar17; }
                            iVar17 = iVar6;
                        } while (iVar18 <= iVar17);
                    } else {
                    path_inner3_inner_fail:
                        pcVar30 = "";
                    }
                    uVar12 = prc_read_int(pcVar30);
                    bVar7 = uVar12 != 0;
                } else {
                    bVar7 = false;
                }

                // Build BNTX path and compute CRC32 hash
                FUN_7103239370(&local_208, iVar11, bVar7);
                FUN_7103239770(&local_208, "%s.bntx", auStack_f0);
                if (uStack_204 == 0) {
                    uVar21 = 0;
                } else {
                    // Case-insensitive CRC32 hash
                    uVar12 = 0xffffffff;
                    u8* pbVar19;
                    pbVar14 = (u8*)&local_200;
                    do {
                        pbVar19 = pbVar14 + 1;
                        u8 bVar4 = *pbVar14;
                        uVar10 = bVar4 + 0x20;
                        if (0x19 < (u8)(bVar4 - 0x41)) {
                            uVar10 = (u32)bVar4;
                        }
                        uVar12 = *(u32*)(&DAT_7104753084 + (u64)((uVar10 ^ uVar12) & 0xff) * 4) ^ uVar12 >> 8;
                        pbVar14 = pbVar19;
                    } while (pbVar19 < (u8*)((s64)&local_200 + (u64)uStack_204));
                    uVar21 = (u64)~uVar12;
                }
                uVar21 = uVar21 | ((s64)(s32)uStack_204 & 0xffULL) << 0x20;
            } else {
                uVar21 = FUN_7103238300(uVar22, iVar11, 0);
            }
            goto path_store;
        }
    }
    uVar21 = 0;
path_store:
    *(u64*)(param_1 + 0x5e) = uVar21;

    // ── Epilogue ──────────────────────────────────────────────────
    *(u64*)(param_1 + 0x66) = param_2;
    if (((*param_1 | 4) == 4) && ((s32)*puVar2 < 1)) {
        *(u8*)((s64)param_1 + 0x175) = 1;
    }
}
