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
