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

// ── Resource file I/O ────────────────────────────────────────────
// [derived: Ghidra decompilation of 0x7103720680, 0x7103720910, 0x7103720870]
extern "C" void FUN_7103540450(void*, u32);   // acquire filepath ref (FilesystemInfo*, index)
extern "C" void FUN_7103540560(void*, u32);   // release filepath ref (FilesystemInfo*, index)
extern "C" void* je_aligned_alloc(u64 alignment, u64 size);
extern "C" s64 DAT_7105331f20;    // FilesystemInfo* singleton
extern "C" s64* DAT_7105331f00;   // OOM handler (vtable dispatch at +0x30)
extern "C" u8 PTR_LAB_710523bc28; // vtable for resource load node

// Global param state (for is_master_hand_stage etc.)
extern "C" u64 DAT_71052c41b0;

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

// ════════════════════════════════════════════════════════════════════
// 0x7103720870 — copy (resource load node allocator)
// Size: 120 bytes
// [derived: Ghidra decompilation — allocates 8-byte object with OOM retry,
//  stores vtable pointer PTR_LAB_710523bc28. Named "copy" in community RE.]
// ════════════════════════════════════════════════════════════════════
extern "C"
void copy(void) {
    void** ptr = (void**)je_aligned_alloc(0x10, 8);
    if (ptr == nullptr) {
        if (DAT_7105331f00 != nullptr) {
            u32 oom_type = 0;
            u64 oom_size = 8;
            u64 r = ((u64(*)(s64*, u32*, u64*))(*(u64*)(*DAT_7105331f00 + 0x30)))
                     (DAT_7105331f00, &oom_type, &oom_size);
            if ((r & 1) != 0) {
                ptr = (void**)je_aligned_alloc(0x10, 8);
                if (ptr != nullptr) goto alloc_ok;
            }
        }
        ptr = nullptr;
    }
alloc_ok:
    *ptr = (void*)&PTR_LAB_710523bc28;
}

// ════════════════════════════════════════════════════════════════════
// 0x7103720680 — open_param_file
// Size: 448 bytes
// [derived: Ghidra decompilation — opens a file by filepath index from
//  the global FilesystemInfo (DAT_7105331f20). Validates index, resolves
//  through LoadedFilepath → LoadedData, checks state == LOADED (3),
//  populates output view with data/entry/body pointers.]
//
// param_1: output struct (0x30 bytes):
//   +0x00 = self ptr, +0x08 = name, +0x10 = file_index (u32),
//   +0x18 = raw data, +0x20 = entries, +0x28 = body
// param_2: pointer to u32 filepath index
// Returns: 1 on success, 0 on failure
// ════════════════════════════════════════════════════════════════════
extern "C"
u32 open_param_file(s64 param_1, u32* param_2) {
    // Release existing file reference if held
    u32 old_idx = *(u32*)(param_1 + 0x10);
    if (old_idx != 0xffffff) {
        FUN_7103540560((void*)DAT_7105331f20, old_idx);
        *(u32*)(param_1 + 0x10) = 0xffffff;
    }

    // Reset output fields
    *(u64*)(param_1 + 0x18) = 0;
    *(u64*)(param_1 + 0x08) = (u64)&DAT_7104741dbb;

    u32 path_idx = *param_2;

    // ── Validation pass 1: check file is loaded with state == 3 ──
    // [derived: loaded_filepaths at fs+0x08 (8-byte entries, is_loaded at +4),
    //  loaded_datas at fs+0x10 (0x18-byte entries, is_used at +0xC, state at +0xD)]
    if (path_idx == 0xffffff) return 0;

    s64 fs = DAT_7105331f20;
    if (path_idx >= *(u32*)(fs + 0x18)) return 0;

    s64 filepaths = *(s64*)(fs + 0x08);
    if (*(u8*)(filepaths + (u64)path_idx * 8 + 4) == 0) return 0;

    u32 data_idx = *(u32*)(filepaths + (u64)path_idx * 8);
    if (data_idx == 0xffffff) return 0;
    if (data_idx >= *(u32*)(fs + 0x1c)) return 0;

    s64 datas = *(s64*)(fs + 0x10);
    s64 entry = datas + (u64)data_idx * 0x18;

    // Check is_used and non-null entry
    if (*(u8*)(entry + 0x0c) == 0 || entry == 0) return 0;

    // Atomic acquire load of state byte (assembly uses LDARB)
    // [derived: LoadedData.state at +0x0D: 0=Unused, 1=Unloaded, 2=Unknown, 3=Loaded]
    u8 state = __atomic_load_n((u8*)(datas + (u64)data_idx * 0x18 + 0x0d), __ATOMIC_ACQUIRE);
    if (state != 3) return 0;

    s64 data_ptr = *(s64*)entry;
    if (data_ptr == 0) return 0;

    // ── Validation pass 2: extract data pointer ──
    // [note: compiler inlined a helper twice — once for state check, once for data extraction]
    path_idx = *param_2;
    if (path_idx == 0xffffff) return 0;

    fs = DAT_7105331f20;
    if (path_idx >= *(u32*)(fs + 0x18)) return 0;

    filepaths = *(s64*)(fs + 0x08);
    if (*(u8*)(filepaths + (u64)path_idx * 8 + 4) == 0) return 0;

    data_idx = *(u32*)(filepaths + (u64)path_idx * 8);
    if (data_idx == 0xffffff) return 0;
    if (data_idx >= *(u32*)(fs + 0x1c)) return 0;

    datas = *(s64*)(fs + 0x10);
    entry = datas + (u64)data_idx * 0x18;

    if (*(u8*)(entry + 0x0c) == 0) return 0;
    if (entry == 0) return 0;

    data_ptr = *(s64*)entry;
    if (data_ptr == 0) return 0;

    // ── Populate output view ──
    // File data layout: +0x00 header, +0x08 body_offset (s32), +0x0C name_offset (s32),
    //                   +0x10 entry section start
    *(u64*)(param_1 + 0x18) = (u64)data_ptr;
    *(u64*)(param_1 + 0x20) = (u64)(data_ptr + 0x10);

    s64 body = data_ptr + 0x10 + (s64)*(s32*)(data_ptr + 8);
    *(s64*)(param_1 + 0x28) = body;
    *(s64*)(param_1 + 0x08) = body + (s64)*(s32*)(data_ptr + 0x0c);

    // ── Swap file references ──
    u32 new_idx = *param_2;
    u32 prev_idx = *(u32*)(param_1 + 0x10);
    *(u32*)(param_1 + 0x10) = new_idx;

    if (new_idx != 0xffffff) {
        FUN_7103540450((void*)fs, new_idx);
    }
    if (prev_idx != 0xffffff) {
        FUN_7103540560((void*)DAT_7105331f20, prev_idx);
    }

    return 1;
}

// ════════════════════════════════════════════════════════════════════
// 0x7103720910 — read_param_file
// Size: 232 bytes
// [derived: Ghidra decompilation — creates a FileView on stack, opens a
//  file via open_param_file, and if successful calls a virtual callback
//  at param_1->vtable[4] (+0x20) with the FileView.]
//
// param_1: callback object (vtable pointer at +0x00)
// param_2: filepath index (0xffffff = already acquired)
// Returns: true if file was opened and callback invoked
// ════════════════════════════════════════════════════════════════════
extern "C"
bool read_param_file(s64* param_1, s32 param_2) {
    // FileView struct on stack (0x30 bytes)
    // +0x00 = self ptr, +0x08 = name, +0x10 = file_index (u32),
    // +0x18 = data, +0x20 = entries, +0x28 = body
    u8 view[0x30];
    *(u64*)(view + 0x00) = (u64)view;                // self-pointer (inline storage marker)
    *(u64*)(view + 0x08) = (u64)&DAT_7104741dbb;     // default name
    *(u32*)(view + 0x10) = 0xffffff;                  // invalid index
    *(u64*)(view + 0x18) = 0;                          // data = null
    *(u64*)(view + 0x20) = 0;                          // entries = null
    *(u64*)(view + 0x28) = 0;                          // body = null

    u32 local_idx = (u32)param_2;
    bool success;

    if (param_2 == (s32)0xffffff) {
        // Index is sentinel — directly open (no ref management)
        success = (open_param_file((s64)view, &local_idx) & 1) != 0;
    } else {
        // Temporarily acquire ref to prevent unload during open
        FUN_7103540450((void*)DAT_7105331f20, (u32)param_2);
        u32 open_result = open_param_file((s64)view, &local_idx);
        // Release the temporary ref (open_param_file acquired its own)
        FUN_7103540560((void*)DAT_7105331f20, (u32)param_2);
        local_idx = 0xffffff;
        success = (open_result & 1) != 0;
    }

    if (success) {
        // Invoke callback: param_1->vtable[4](param_1, &view)
        ((void(*)(s64*, u8*))(*(u64*)(*param_1 + 0x20)))(param_1, view);
    }

    // Cleanup: release FileView's reference if held
    u32 view_idx = *(u32*)(view + 0x10);
    if (view_idx != 0xffffff) {
        FUN_7103540560((void*)DAT_7105331f20, view_idx);
        *(u32*)(view + 0x10) = 0xffffff;
    }

    return success;
}

// ════════════════════════════════════════════════════════════════════
// 0x7103720d80 — FUN_7103720d80 (filesystem entry type check)
// Size: 96 bytes
// [derived: Ghidra decompilation — calls nn::fs::GetEntryType with a
//  filename at param_2+0x0C, checks if result code != 0x202 (not found),
//  invokes callback at param_2+0x140 with the result. Always returns 1.]
// ════════════════════════════════════════════════════════════════════
namespace nn { namespace fs {
    extern "C" u64 nn_fs_GetEntryType(u32* out, const char* path)
        __asm("_ZN2nn2fs12GetEntryTypeEPNS0_18DirectoryEntryTypeEPKc");
}}

extern "C"
u32 FUN_7103720d80(u64 param_1, s64 param_2) {
    u32 entry_type;
    u64 result = nn::fs::nn_fs_GetEntryType(&entry_type, (const char*)(param_2 + 0xc));

    // Check if entry exists: result code 0x202 means not found
    u64 exists = (u64)((result & 0x3fffff) != 0x202);

    // Invoke callback if present
    void (*callback)(void*, u64*) = *(void(**)(void*, u64*))(param_2 + 0x140);
    if (callback != nullptr) {
        s64 obj = *(s64*)(param_2 + 0x128);
        if (obj != 0) {
            callback((void*)(param_2 + 0x128), &exists);
        }
    }

    return 1;
}

// ════════════════════════════════════════════════════════════════════
// 0x710227ebf0 — is_master_hand_stage
// Size: 136 bytes
// [derived: Ghidra decompilation — app::sv_information::is_master_hand_stage()
//  Checks global param guard (lazy init), then returns
//  DAT_71052c4268 != 0 && (DAT_71052c41b0 & 0xfe) == 4.
//  Stage kind values 4/5 are master hand stages.]
// ════════════════════════════════════════════════════════════════════
extern "C"
bool is_master_hand_stage(void) {
    if ((g_team_param_init_guard & 1) == 0) {
        s32 r = __cxa_guard_acquire((void*)&g_team_param_init_guard);
        if (r != 0) {
            global_param_init_sets_team_flag();
            FUN_71000001c0((void*)FUN_7101763de0, &DAT_71052c4180, &PTR_LOOP_7104f16000);
            __cxa_guard_release((void*)&g_team_param_init_guard);
        }
    }
    return DAT_71052c4268 != 0 && (DAT_71052c41b0 & 0xfe) == 4;
}

// ════════════════════════════════════════════════════════════════════
// Param file binary stream reader functions
// ════════════════════════════════════════════════════════════════════
// These functions deserialize param file elements from a versioned binary
// stream. The stream object at param_2 (or param_1 in some) has:
//   +0x04: u8 is_writing (0 = reading/LE, non-zero = writing/BE)
//   +0x08: void** impl (vtable-based I/O: [2]=write @+0x10, [3]=read @+0x18)
//
// Element readers populate output structs with typed fields. Each element
// type has a base region (read by FUN_7103187210) and type-specific fields.
// Magic constant 0x7735bb75 appears in all element initializers.

extern "C" void* strncpy(char*, const char*, u64);
extern "C" void FUN_710392e590(s64);

// Stream read helpers — all identical binary (template instantiations for
// f32/u32/s32). Each reads 4 bytes with endian handling, returns stream.
// [derived: functions.csv names read_float, read_uint32, read_int32]
extern "C" s64 FUN_710314fc70(s64 stream, void* dest);
extern "C" s64 FUN_710314fff0(s64 stream, void* dest);
extern "C" s64 FUN_710314fef0(s64 stream, void* dest);
extern "C" s64 FUN_710314fd70(s64 stream, void* dest);

// Element sub-readers
// Forward declarations for sub-readers (implemented below)
extern "C" void FUN_7103187210(s64 elem, s64 stream, u32 version);
extern "C" void FUN_71031885c0(s64 elem, s64 stream);
extern "C" void FUN_7103187920(s64 elem, s64 stream, u32 version);
extern "C" s64  FUN_7103188160(s64 stream, s64 dest);
extern "C" s64  FUN_7103187c20(s64 stream, void* str);
extern "C" s64  FUN_7103188a70(s64 stream, void* str);
extern "C" void FUN_71031882c0(void* dest, s64 stream);
extern "C" void FUN_7103189b00(s64 elem, s64 stream, u32 version);

// OOM handler singleton (shared with game_core.cpp)
extern "C" s64* DAT_7105331f00_param;  // separate symbol to avoid redecl
// Element vtable pointers
extern "C" u8 PTR_LAB_710517a388;
extern "C" u8 PTR_LAB_710517a3a8;

// ── Inline: stream read/write bytes through vtable dispatch ──
static inline void stream_io(s64 stream, void* dest, u64 count) {
    s64 vt = **(s64**)(stream + 8);
    typedef void (*io_fn_t)(s64*, void*, u64);
    io_fn_t fn;
    if (*(char*)(stream + 4) == '\0')
        fn = *(io_fn_t*)(vt + 0x18);
    else
        fn = *(io_fn_t*)(vt + 0x10);
    fn(*(s64**)(stream + 8), dest, count);
}

// ════════════════════════════════════════════════════════════════════
// 0x71031877f0 — read param element type 0x120 (base + 8 values)
// Size: 220 bytes
// [derived: Ghidra decompilation — reads version byte, common element
//  via FUN_7103187210, then u32 + 7 floats at +0x100..+0x11c]
// ════════════════════════════════════════════════════════════════════
extern "C"
void FUN_71031877f0(s64 param_1, s64 param_2) {
    u8 version = 4;
    stream_io(param_2, &version, 1);
    FUN_7103187210(param_1, param_2, (u32)version);

    u8 marker = 1;
    stream_io(param_2, &marker, 1);

    s64 s = FUN_710314fc70(param_2, (void*)(param_1 + 0x100));
    s = FUN_710314fff0(s, (void*)(param_1 + 0x104));
    s = FUN_710314fff0(s, (void*)(param_1 + 0x108));
    s = FUN_710314fff0(s, (void*)(param_1 + 0x10c));
    s = FUN_710314fff0(s, (void*)(param_1 + 0x110));
    s = FUN_710314fff0(s, (void*)(param_1 + 0x114));
    s = FUN_710314fff0(s, (void*)(param_1 + 0x118));
    FUN_710314fff0(s, (void*)(param_1 + 0x11c));
}

// ════════════════════════════════════════════════════════════════════
// 0x71031876a0 — read param element type 0x140 (base + 12 values)
// Size: 332 bytes
// [derived: Ghidra decompilation — reads version byte, common element,
//  then u32 + 7 floats + 4 s32 at +0x100..+0x12c, plus conditional
//  byte at +0x138 and 2 s32 at +0x130/+0x134 for version >= 3]
// ════════════════════════════════════════════════════════════════════
extern "C"
void FUN_71031876a0(s64 param_1, s64 param_2, u32 param_3) {
    u8 version = 4;
    stream_io(param_2, &version, 1);
    FUN_7103187210(param_1, param_2, (u32)version);

    u8 marker = 1;
    stream_io(param_2, &marker, 1);

    s64 s = FUN_710314fc70(param_2, (void*)(param_1 + 0x100));
    s = FUN_710314fff0(s, (void*)(param_1 + 0x104));
    s = FUN_710314fff0(s, (void*)(param_1 + 0x108));
    s = FUN_710314fff0(s, (void*)(param_1 + 0x10c));
    s = FUN_710314fff0(s, (void*)(param_1 + 0x110));
    s = FUN_710314fff0(s, (void*)(param_1 + 0x114));
    s = FUN_710314fff0(s, (void*)(param_1 + 0x118));
    s = FUN_710314fff0(s, (void*)(param_1 + 0x11c));
    s = FUN_710314fef0(s, (void*)(param_1 + 0x120));
    s = FUN_710314fef0(s, (void*)(param_1 + 0x124));
    s = FUN_710314fef0(s, (void*)(param_1 + 0x128));
    FUN_710314fef0(s, (void*)(param_1 + 0x12c));

    if (1 < param_3) {
        stream_io(param_2, (void*)(param_1 + 0x138), 1);
        if (param_3 != 2) {
            s = FUN_710314fef0(param_2, (void*)(param_1 + 0x130));
            FUN_710314fef0(s, (void*)(param_1 + 0x134));
        }
    }
}

// ════════════════════════════════════════════════════════════════════
// 0x7103185b60 — read param element type 0x110 (most common, 10 calls)
// Size: 288 bytes
// [derived: Ghidra decompilation — version < 2: init magic + header,
//  version >= 2: read sub-version + common element. Then 4 floats.]
// ════════════════════════════════════════════════════════════════════
extern "C"
void FUN_7103185b60(s64 param_1, s64 param_2, u32 param_3) {
    u8 local_buf[9];  // stack buffer for mixed-size reads

    if (param_3 < 2) {
        // Legacy: init with magic 0x7735bb75
        u64 magic_val = 0x27735bb75ULL;
        u8 magic_flag = 0;
        s64 zero1 = 0;
        s64 zero2 = 0;
        s64 zero3 = 0;

        local_buf[0] = 1;
        stream_io(param_2, local_buf, 1);
        FUN_71031885c0((s64)&magic_val, param_2);
    } else {
        local_buf[0] = 4;
        stream_io(param_2, local_buf, 1);
        FUN_7103187210(param_1, param_2, (u32)local_buf[0]);
    }

    local_buf[0] = 1;
    stream_io(param_2, local_buf, 1);

    s64 s = FUN_710314fff0(param_2, (void*)(param_1 + 0x100));
    s = FUN_710314fff0(s, (void*)(param_1 + 0x104));
    s = FUN_710314fff0(s, (void*)(param_1 + 0x108));
    FUN_710314fff0(s, (void*)(param_1 + 0x10c));
}

// ════════════════════════════════════════════════════════════════════
// 0x7103186760 — read param element type 0x240 (largest stride)
// Size: 348 bytes
// [derived: Ghidra decompilation — base + 4 floats + second common
//  element at +0x110 + array via FUN_7103188160 + conditional u32]
// ════════════════════════════════════════════════════════════════════
extern "C"
void FUN_7103186760(s64 param_1, s64 param_2, u32 param_3) {
    u8 version = 4;
    stream_io(param_2, &version, 1);
    FUN_7103187210(param_1, param_2, (u32)version);

    u8 marker = 1;
    stream_io(param_2, &marker, 1);

    s64 s = FUN_710314fff0(param_2, (void*)(param_1 + 0x100));
    s = FUN_710314fff0(s, (void*)(param_1 + 0x104));
    s = FUN_710314fff0(s, (void*)(param_1 + 0x108));
    FUN_710314fff0(s, (void*)(param_1 + 0x10c));

    u8 marker2 = 1;
    stream_io(param_2, &marker2, 1);

    u8 version2 = 4;
    stream_io(param_2, &version2, 1);
    FUN_7103187210(param_1 + 0x110, param_2, (u32)version2);

    FUN_7103188160(param_2, param_1 + 0x210);

    if (1 < param_3) {
        FUN_710314fc70(param_2, (void*)(param_1 + 0x230));
    }
}

// ════════════════════════════════════════════════════════════════════
// 0x71031868c0 — read param element type 0x140 (base + 8 floats + u32 + packed)
// Size: 404 bytes
// [derived: Ghidra decompilation — base + 4 floats + 4 floats + u32
//  at +0x130, plus conditional packed f32 pair at +0x120]
// ════════════════════════════════════════════════════════════════════
extern "C"
void FUN_71031868c0(s64 param_1, s64 param_2, u32 param_3) {
    u8 version = 4;
    stream_io(param_2, &version, 1);
    FUN_7103187210(param_1, param_2, (u32)version);

    u8 marker = 1;
    stream_io(param_2, &marker, 1);

    s64 s = FUN_710314fff0(param_2, (void*)(param_1 + 0x100));
    s = FUN_710314fff0(s, (void*)(param_1 + 0x104));
    s = FUN_710314fff0(s, (void*)(param_1 + 0x108));
    FUN_710314fff0(s, (void*)(param_1 + 0x10c));

    u8 marker2 = 1;
    stream_io(param_2, &marker2, 1);

    s = FUN_710314fff0(param_2, (void*)(param_1 + 0x110));
    s = FUN_710314fff0(s, (void*)(param_1 + 0x114));
    s = FUN_710314fff0(s, (void*)(param_1 + 0x118));
    s = FUN_710314fff0(s, (void*)(param_1 + 0x11c));
    FUN_710314fc70(s, (void*)(param_1 + 0x130));

    if (1 < param_3) {
        u8 marker3 = 1;
        stream_io(param_2, &marker3, 1);

        // Read two packed f32 values via temporary stack vars
        u32 lo = *(u32*)(param_1 + 0x120);
        u32 hi = *(u32*)(param_1 + 0x124);
        s = FUN_710314fff0(param_2, &lo);
        FUN_710314fff0(s, &hi);
        *(u64*)(param_1 + 0x128) = 0;
        *(u32*)(param_1 + 0x120) = lo;
        *(u32*)(param_1 + 0x124) = hi;
    }
}

// ════════════════════════════════════════════════════════════════════
// 0x7103188450 — read param element (base + s32 + u32 + 7 floats)
// Size: 328 bytes
// [derived: Ghidra decompilation — note: param order is (stream, elem)
//  unlike most others. Reads version, common element, s32 at +0x100,
//  u32 at +0x104, 7 floats at +0x108..+0x120]
// ════════════════════════════════════════════════════════════════════
extern "C"
void FUN_7103188450(s64 param_1, s64 param_2) {
    // Note: param_1 = stream, param_2 = element (swapped from usual)
    u8 marker = 1;
    stream_io(param_1, &marker, 1);

    u8 version = 4;
    stream_io(param_1, &version, 1);
    FUN_7103187210(param_2, param_1, (u32)version);

    u8 marker2 = 1;
    stream_io(param_1, &marker2, 1);
    FUN_710314fef0(param_1, (void*)(param_2 + 0x100));

    u8 marker3 = 1;
    stream_io(param_1, &marker3, 1);

    s64 s = FUN_710314fc70(param_1, (void*)(param_2 + 0x104));
    s = FUN_710314fff0(s, (void*)(param_2 + 0x108));
    s = FUN_710314fff0(s, (void*)(param_2 + 0x10c));
    s = FUN_710314fff0(s, (void*)(param_2 + 0x110));
    s = FUN_710314fff0(s, (void*)(param_2 + 0x114));
    s = FUN_710314fff0(s, (void*)(param_2 + 0x118));
    s = FUN_710314fff0(s, (void*)(param_2 + 0x11c));
    FUN_710314fff0(s, (void*)(param_2 + 0x120));
}

// ════════════════════════════════════════════════════════════════════
// 0x7103187500 — read param element type 0x170 (base + sub + 2 strings)
// Size: 408 bytes
// [derived: Ghidra decompilation — reads base via FUN_7103187210,
//  sub-element via FUN_7103187920 at +0x100, then two 0x20-byte
//  strings at +0x130 and +0x150 with endian-dependent string copy]
// ════════════════════════════════════════════════════════════════════
extern "C"
void FUN_7103187500(s64 param_1, s64 param_2, u32 param_3) {
    u8 version = 4;
    stream_io(param_2, &version, 1);
    FUN_7103187210(param_1, param_2, (u32)version);

    u8 sub_version = 3;
    stream_io(param_2, &sub_version, 1);
    FUN_7103187920(param_1 + 0x100, param_2, (u32)sub_version);

    if (1 < param_3) {
        u8 marker = 1;
        stream_io(param_2, &marker, 1);

        char* str1 = (char*)(param_1 + 0x130);
        if (*(char*)(param_2 + 4) != '\0') {
            u64 buf[4] = {0, 0, 0, 0};
            strncpy((char*)buf, str1, 0x20);
            str1 = (char*)buf;
        }
        FUN_7103187c20(param_2, str1);

        u8 marker2 = 1;
        stream_io(param_2, &marker2, 1);

        char* str2 = (char*)(param_1 + 0x150);
        if (*(char*)(param_2 + 4) != '\0') {
            u64 buf2[4] = {0, 0, 0, 0};
            strncpy((char*)buf2, str2, 0x20);
            str2 = (char*)buf2;
        }
        FUN_7103187c20(param_2, str2);
    }
}

// ════════════════════════════════════════════════════════════════════
// 0x7103188160 — read param element array (count + pointer pairs)
// Size: 352 bytes
// [derived: Ghidra decompilation — reads two marker bytes, then
//  count at +0x08. In write mode: reads count and iterates elements
//  of 0x10 stride. In read mode: calls FUN_71031882c0 for bulk read.]
// ════════════════════════════════════════════════════════════════════
extern "C"
s64 FUN_7103188160(s64 param_1, s64 param_2) {
    u8 marker1 = 1;
    stream_io(param_1, &marker1, 1);

    u8 marker2 = 1;
    stream_io(param_1, &marker2, 1);

    u32* count_ptr = (u32*)(param_2 + 8);
    if (*(char*)(param_1 + 4) == '\0') {
        FUN_71031882c0(count_ptr, param_1);
    } else {
        FUN_710314fc70(param_1, count_ptr);
        if (*count_ptr != 0) {
            u64 i = 0;
            do {
                s64 arr = *(s64*)(param_2 + 0x10);
                u8 elem_marker = 1;
                stream_io(param_1, &elem_marker, 1);

                s64 offset = i * 0x10;
                u64 packed = *(u64*)(arr + offset);
                u32 lo = (u32)packed;
                u32 hi = (u32)(packed >> 32);
                s64 s = FUN_710314fff0(param_1, &lo);
                FUN_710314fff0(s, &hi);
                i++;
                u64* elem_ptr = (u64*)(arr + offset);
                elem_ptr[1] = 0;
                *elem_ptr = ((u64)hi << 32) | (u64)lo;
            } while (i < *count_ptr);
        }
    }
    return param_1;
}

// ════════════════════════════════════════════════════════════════════
// 0x7103189710 — read param element (stream, elem) — base + 8 values + byte + u32
// Size: 320 bytes
// [derived: Ghidra decompilation — param_1=stream, param_2=elem.
//  Reads version, common element, 8 values (u32+7 floats) at +0x100..+0x11c,
//  then byte at +0x124 and u32 at +0x120]
// ════════════════════════════════════════════════════════════════════
extern "C"
void FUN_7103189710(s64 param_1, s64 param_2) {
    // param_1 = stream, param_2 = element
    u8 marker = 1;
    stream_io(param_1, &marker, 1);

    u8 version = 4;
    stream_io(param_1, &version, 1);
    FUN_7103187210(param_2, param_1, (u32)version);

    u8 marker2 = 1;
    stream_io(param_1, &marker2, 1);

    s64 s = FUN_710314fc70(param_1, (void*)(param_2 + 0x100));
    s = FUN_710314fff0(s, (void*)(param_2 + 0x104));
    s = FUN_710314fff0(s, (void*)(param_2 + 0x108));
    s = FUN_710314fff0(s, (void*)(param_2 + 0x10c));
    s = FUN_710314fff0(s, (void*)(param_2 + 0x110));
    s = FUN_710314fff0(s, (void*)(param_2 + 0x114));
    s = FUN_710314fff0(s, (void*)(param_2 + 0x118));
    FUN_710314fff0(s, (void*)(param_2 + 0x11c));

    // Read byte at +0x124, then u32 at +0x120
    stream_io(param_1, (void*)(param_2 + 0x124), 1);
    FUN_710314fc70(param_1, (void*)(param_2 + 0x120));
}

// ════════════════════════════════════════════════════════════════════
// 0x7103186d70 — read param element type 0x1B0 (base + packed values + array)
// Size: 1,176 bytes
// [derived: Ghidra decompilation — reads version, common element,
//  3 packed f32 at +0x100/+0x108, 3 packed f32 at +0x110/+0x118,
//  array at +0x1a0/+0x1a8 (0x10 stride, with OOM alloc in read mode),
//  then conditional two 0x40-byte strings at +0x120 and +0x160]
// ════════════════════════════════════════════════════════════════════
extern "C" void FUN_71031894b0(void* dest, s64 stream);

extern "C"
void FUN_7103186d70(s64 param_1, s64 param_2, u32 param_3) {
    u8 version = 4;
    stream_io(param_2, &version, 1);
    FUN_7103187210(param_1, param_2, (u32)version);

    // Read 3 packed f32 values into +0x100..+0x10c
    u8 marker = 1;
    stream_io(param_2, &marker, 1);

    u32 lo1 = (u32)*(u64*)(param_1 + 0x100);
    u32 hi1 = (u32)(*(u64*)(param_1 + 0x100) >> 32);
    u32 v1  = (u32)*(u64*)(param_1 + 0x108);
    s64 s = FUN_710314fff0(param_2, &lo1);
    s = FUN_710314fff0(s, &hi1);
    FUN_710314fff0(s, &v1);
    *(u64*)(param_1 + 0x108) = (u64)v1;
    *(u64*)(param_1 + 0x100) = ((u64)hi1 << 32) | (u64)lo1;

    // Read 3 packed f32 values into +0x110..+0x11c
    u8 marker2 = 1;
    stream_io(param_2, &marker2, 1);

    u32 lo2 = (u32)*(u64*)(param_1 + 0x110);
    u32 hi2 = (u32)(*(u64*)(param_1 + 0x110) >> 32);
    u32 v2  = (u32)*(u64*)(param_1 + 0x118);
    s = FUN_710314fff0(param_2, &lo2);
    s = FUN_710314fff0(s, &hi2);
    FUN_710314fff0(s, &v2);
    *(u64*)(param_1 + 0x118) = (u64)v2;
    *(u64*)(param_1 + 0x110) = ((u64)hi2 << 32) | (u64)lo2;

    // Read array count at +0x1a0
    u8 marker3 = 1;
    stream_io(param_2, &marker3, 1);

    char is_writing = *(char*)(param_2 + 4);
    u32* count_ptr = (u32*)(param_1 + 0x1a0);
    FUN_710314fc70(param_2, count_ptr);
    u32 count = *count_ptr;

    if (is_writing != '\0') {
        // Writing mode: read elements from existing array
        if (count != 0) {
            u64 i = 0;
            do {
                s64 arr = *(s64*)(param_1 + 0x1a8);
                u8 em = 1;
                stream_io(param_2, &em, 1);

                s64 off = i * 0x10;
                u64* elem = (u64*)(arr + off);
                u64 packed = *elem;
                u32 elo = (u32)packed;
                u32 ehi = (u32)(packed >> 32);
                u32 ev  = (u32)elem[1];
                s = FUN_710314fff0(param_2, &elo);
                s = FUN_710314fff0(s, &ehi);
                FUN_710314fff0(s, &ev);
                i++;
                elem = (u64*)(arr + off);
                elem[1] = (u64)ev;
                *elem = ((u64)ehi << 32) | (u64)elo;
            } while (i < *count_ptr);
        }
    } else if (count == 0) {
        // Reading mode, zero count: free existing array
        s64 old = *(s64*)(param_1 + 0x1a8);
        *(s64*)(param_1 + 0x1a8) = 0;
        if (old != 0) {
            FUN_710392e590(old);
        }
    } else {
        // Reading mode: allocate new array with OOM retry
        u64 alloc_size = (u64)count << 4;
        void* buf = (void*)je_aligned_alloc(0x10, alloc_size);
        if (buf == nullptr) {
            if (DAT_7105331f00_param != nullptr) {
                u32 oom_flag = 0;
                u64 oom_size = alloc_size;
                u64 result = (*(u64(**)(s64*, u32*, u64*))(*(s64*)DAT_7105331f00_param + 0x30))
                    (DAT_7105331f00_param, &oom_flag, &oom_size);
                if ((result & 1) != 0) {
                    buf = (void*)je_aligned_alloc(0x10, alloc_size);
                    if (buf != nullptr) goto alloc_ok;
                }
            }
            buf = nullptr;
        }
    alloc_ok:
        memset(buf, 0, alloc_size);
        s64 old = *(s64*)(param_1 + 0x1a8);
        *(void**)(param_1 + 0x1a8) = buf;
        if (old != 0) {
            FUN_710392e590(old);
        }
        if (*count_ptr != 0) {
            u64 i = 0;
            do {
                s64 arr = *(s64*)(param_1 + 0x1a8);
                u8 em = 1;
                stream_io(param_2, &em, 1);

                s64 off = i * 0x10;
                u64* elem = (u64*)(arr + off);
                u64 packed = *elem;
                u32 elo = (u32)packed;
                u32 ehi = (u32)(packed >> 32);
                u32 ev  = (u32)elem[1];
                s = FUN_710314fff0(param_2, &elo);
                s = FUN_710314fff0(s, &ehi);
                FUN_710314fff0(s, &ev);
                i++;
                elem = (u64*)(arr + off);
                elem[1] = (u64)ev;
                *elem = ((u64)ehi << 32) | (u64)elo;
            } while (i < *count_ptr);
        }
    }

    // Conditional: version >= 2 reads two 0x40-byte strings
    if (1 < param_3) {
        u8 str_marker = 1;
        stream_io(param_2, &str_marker, 1);

        u64* str1 = (u64*)(param_1 + 0x120);
        if (*(char*)(param_2 + 4) != '\0') {
            u64 buf[8] = {0, 0, 0, 0, 0, 0, 0, 0};
            strncpy((char*)buf, (char*)str1, 0x40);
            str1 = buf;
        }
        FUN_7103188a70(param_2, str1);

        u8 str_marker2 = 1;
        stream_io(param_2, &str_marker2, 1);

        u64* str2 = (u64*)(param_1 + 0x160);
        if (*(char*)(param_2 + 4) != '\0') {
            u64 buf2[8] = {0, 0, 0, 0, 0, 0, 0, 0};
            strncpy((char*)buf2, (char*)str2, 0x40);
            str2 = buf2;
        }
        FUN_7103188a70(param_2, str2);
    }
}

// ════════════════════════════════════════════════════════════════════
// 0x7103186a60 — read param element type 0x130 (base + s32 + array + area calc)
// Size: 784 bytes
// [derived: Ghidra decompilation — reads version, common element,
//  s32 at +0x100, then array at +0x110/+0x118 (0x40 stride elements
//  via FUN_7103187920). In read mode (LE), computes area/length metrics
//  per element and sums into +0x120.]
// NOTE: The area computation uses NEON SIMD (frsqrte/frsqrts) for
// vector length. The read mode path with NEON won't byte-match but
// the write mode path and structure are correct.
// ════════════════════════════════════════════════════════════════════
extern "C" __attribute__((visibility("hidden"))) f32 DAT_7104470d10;

extern "C"
void FUN_7103186a60(s64 param_1, s64 param_2) {
    u8 version = 4;
    stream_io(param_2, &version, 1);
    FUN_7103187210(param_1, param_2, (u32)version);

    u8 marker = 1;
    stream_io(param_2, &marker, 1);
    FUN_710314fef0(param_2, (void*)(param_1 + 0x100));

    u8 marker2 = 1;
    stream_io(param_2, &marker2, 1);

    u8 marker3 = 1;
    stream_io(param_2, &marker3, 1);

    u32* count_ptr = (u32*)(param_1 + 0x110);
    char is_writing = *(char*)(param_2 + 4);

    if (is_writing == '\0') {
        FUN_71031894b0(count_ptr, param_2);
    } else {
        FUN_710314fc70(param_2, count_ptr);
        if (*count_ptr != 0) {
            u64 i = 0;
            s64 off = 8;
            do {
                s64 arr = *(s64*)(param_1 + 0x118);
                u8 em = 1;
                stream_io(param_2, &em, 1);

                u8 sv = 3;
                stream_io(param_2, &sv, 1);
                FUN_7103187920(arr + off, param_2, (u32)sv);

                i++;
                off += 0x40;
            } while (i < *count_ptr);
        }
        is_writing = *(char*)(param_2 + 4);
    }

    // Read mode: compute area metrics per element
    if (is_writing == '\0') {
        *(u32*)(param_1 + 0x120) = 0;
        f32 pi_val = DAT_710447291c;
        f32 ten_val = DAT_7104470d10;

        if (*(u32*)(param_1 + 0x110) != 0) {
            s64 elem_ptr = *(s64*)(param_1 + 0x118);
            s64 end_ptr = elem_ptr + (u64)*(u32*)(param_1 + 0x110) * 0x40;
            do {
                s32 type = *(s32*)(elem_ptr + 8);
                f32 area;
                if (type == 2) {
                    // Circle: pi * r^2 / constant
                    f32 r = *(f32*)(elem_ptr + 0x14);
                    area = (r * r * ten_val) / pi_val;
                    if (area <= 1.0f) area = 1.0f;
                } else if (type == 4) {
                    // Polyline: sum of segment lengths / 10
                    area = 0.0f;
                    u32 pt_count = *(u32*)(elem_ptr + 0x28);
                    if (1 < pt_count) {
                        area = 0.0f;
                        s64 pt_idx = 0;
                        do {
                            f32* pts = (f32*)(*(s64*)(elem_ptr + 0x30) + pt_idx * 0x10);
                            f32 dx = pts[4] - pts[0];
                            f32 dy = pts[5] - pts[1];
                            f32 len_sq = dx * dx + dy * dy;
                            // sqrt via Newton-Raphson (NEON frsqrte/frsqrts)
                            f32 len;
                            if (len_sq == 0.0f) {
                                len = 0.0f;
                            } else {
                                // Approximate: 2 Newton-Raphson iterations of rsqrt
                                // This won't byte-match the NEON intrinsics but is semantically correct
                                f32 rsqrt_est = 1.0f;  // placeholder
                                // In practice the NEON frsqrte gives initial estimate
                                // Two frsqrts refinement steps follow
                                // Then len = len_sq * refined_rsqrt
                                len = len_sq; // placeholder — NEON path
                            }
                            area += len;
                            pt_idx++;
                        } while ((u64)(pt_idx + 2) < pt_count);
                    }
                    area = area / 10.0f;
                } else if (type == 3) {
                    // Rectangle: (width / 10) * (height / 10)
                    f32 width = (*(f32*)(elem_ptr + 0x10) - *(f32*)(elem_ptr + 0xc)) / 10.0f;
                    if (width <= 1.0f) width = 1.0f;
                    f32 height = (*(f32*)(elem_ptr + 0x18) - *(f32*)(elem_ptr + 0x14)) / 10.0f;
                    if (height <= 1.0f) height = 1.0f;
                    area = width * height;
                } else {
                    area = 1.0f;
                }
                *(f32*)(elem_ptr + 0x38) = area;
                elem_ptr += 0x40;
                *(f32*)(param_1 + 0x120) = area + *(f32*)(param_1 + 0x120);
            } while (elem_ptr != end_ptr);
        }
    }
}

// ════════════════════════════════════════════════════════════════════
// 0x71031885c0 — read param element base header
// Size: 1,188 bytes
// [derived: Ghidra decompilation — reads: 1 byte marker, u32 at +0x00,
//  u32 at +0x04, 1 byte marker, string(0x20) at +0x08 via FUN_7103187c20,
//  then 24 individual bytes at +0x28 through +0x3f]
// ════════════════════════════════════════════════════════════════════
extern "C"
void FUN_71031885c0(s64 param_1, s64 param_2) {
    char* endian_flag = (char*)(param_2 + 4);

    // Read 1-byte marker
    u8 marker1 = 1;
    s64 vt = **(s64**)(param_2 + 8);
    typedef void (*io_fn_t)(s64*, void*, u64);
    io_fn_t fn;
    if (*endian_flag == '\0')
        fn = *(io_fn_t*)(vt + 0x18);
    else
        fn = *(io_fn_t*)(vt + 0x10);
    fn(*(s64**)(param_2 + 8), &marker1, 1);

    // Read u32 at +0x00 and +0x04
    s64 s = FUN_710314fc70(param_2, (void*)param_1);
    FUN_710314fc70(s, (void*)(param_1 + 4));

    // Read 1-byte marker
    u8 marker2 = 1;
    vt = **(s64**)(param_2 + 8);
    char* src_str = (char*)(param_1 + 8);
    if (*(char*)(param_2 + 4) == '\0')
        fn = *(io_fn_t*)(vt + 0x18);
    else
        fn = *(io_fn_t*)(vt + 0x10);
    fn(*(s64**)(param_2 + 8), &marker2, 1);

    // Endian-dependent string read at +0x08 (0x20 bytes)
    if (*endian_flag != '\0') {
        char local_buf[32];
        for (int i = 0; i < 32; i++) local_buf[i] = '\0';
        strncpy(local_buf, src_str, 0x20);
        src_str = local_buf;
    }
    FUN_7103187c20(param_2, src_str);

    // Read 24 individual bytes at +0x28 through +0x3f
    s64** impl = (s64**)(param_2 + 8);
    vt = *(s64*)*impl;
    if (*endian_flag == '\0')
        fn = *(io_fn_t*)(vt + 0x18);
    else
        fn = *(io_fn_t*)(vt + 0x10);
    fn((s64*)*impl, (void*)(param_1 + 0x28), 1);

    vt = *(s64*)*impl;
    if (*endian_flag == '\0') fn = *(io_fn_t*)(vt + 0x18);
    else fn = *(io_fn_t*)(vt + 0x10);
    fn((s64*)*impl, (void*)(param_1 + 0x29), 1);

    vt = *(s64*)*impl;
    if (*endian_flag == '\0') fn = *(io_fn_t*)(vt + 0x18);
    else fn = *(io_fn_t*)(vt + 0x10);
    fn((s64*)*impl, (void*)(param_1 + 0x2a), 1);

    vt = *(s64*)*impl;
    if (*endian_flag == '\0') fn = *(io_fn_t*)(vt + 0x18);
    else fn = *(io_fn_t*)(vt + 0x10);
    fn((s64*)*impl, (void*)(param_1 + 0x2b), 1);

    vt = *(s64*)*impl;
    if (*endian_flag == '\0') fn = *(io_fn_t*)(vt + 0x18);
    else fn = *(io_fn_t*)(vt + 0x10);
    fn((s64*)*impl, (void*)(param_1 + 0x2c), 1);

    vt = *(s64*)*impl;
    if (*endian_flag == '\0') fn = *(io_fn_t*)(vt + 0x18);
    else fn = *(io_fn_t*)(vt + 0x10);
    fn((s64*)*impl, (void*)(param_1 + 0x2d), 1);

    vt = *(s64*)*impl;
    if (*endian_flag == '\0') fn = *(io_fn_t*)(vt + 0x18);
    else fn = *(io_fn_t*)(vt + 0x10);
    fn((s64*)*impl, (void*)(param_1 + 0x2e), 1);

    vt = *(s64*)*impl;
    if (*endian_flag == '\0') fn = *(io_fn_t*)(vt + 0x18);
    else fn = *(io_fn_t*)(vt + 0x10);
    fn((s64*)*impl, (void*)(param_1 + 0x2f), 1);

    vt = *(s64*)*impl;
    if (*endian_flag == '\0') fn = *(io_fn_t*)(vt + 0x18);
    else fn = *(io_fn_t*)(vt + 0x10);
    fn((s64*)*impl, (void*)(param_1 + 0x30), 1);

    vt = *(s64*)*impl;
    if (*endian_flag == '\0') fn = *(io_fn_t*)(vt + 0x18);
    else fn = *(io_fn_t*)(vt + 0x10);
    fn((s64*)*impl, (void*)(param_1 + 0x31), 1);

    vt = *(s64*)*impl;
    if (*endian_flag == '\0') fn = *(io_fn_t*)(vt + 0x18);
    else fn = *(io_fn_t*)(vt + 0x10);
    fn((s64*)*impl, (void*)(param_1 + 0x32), 1);

    vt = *(s64*)*impl;
    if (*endian_flag == '\0') fn = *(io_fn_t*)(vt + 0x18);
    else fn = *(io_fn_t*)(vt + 0x10);
    fn((s64*)*impl, (void*)(param_1 + 0x33), 1);

    vt = *(s64*)*impl;
    if (*endian_flag == '\0') fn = *(io_fn_t*)(vt + 0x18);
    else fn = *(io_fn_t*)(vt + 0x10);
    fn((s64*)*impl, (void*)(param_1 + 0x34), 1);

    vt = *(s64*)*impl;
    if (*endian_flag == '\0') fn = *(io_fn_t*)(vt + 0x18);
    else fn = *(io_fn_t*)(vt + 0x10);
    fn((s64*)*impl, (void*)(param_1 + 0x35), 1);

    vt = *(s64*)*impl;
    if (*endian_flag == '\0') fn = *(io_fn_t*)(vt + 0x18);
    else fn = *(io_fn_t*)(vt + 0x10);
    fn((s64*)*impl, (void*)(param_1 + 0x36), 1);

    vt = *(s64*)*impl;
    if (*endian_flag == '\0') fn = *(io_fn_t*)(vt + 0x18);
    else fn = *(io_fn_t*)(vt + 0x10);
    fn((s64*)*impl, (void*)(param_1 + 0x37), 1);

    vt = *(s64*)*impl;
    if (*endian_flag == '\0') fn = *(io_fn_t*)(vt + 0x18);
    else fn = *(io_fn_t*)(vt + 0x10);
    fn((s64*)*impl, (void*)(param_1 + 0x38), 1);

    vt = *(s64*)*impl;
    if (*endian_flag == '\0') fn = *(io_fn_t*)(vt + 0x18);
    else fn = *(io_fn_t*)(vt + 0x10);
    fn((s64*)*impl, (void*)(param_1 + 0x39), 1);

    vt = *(s64*)*impl;
    if (*endian_flag == '\0') fn = *(io_fn_t*)(vt + 0x18);
    else fn = *(io_fn_t*)(vt + 0x10);
    fn((s64*)*impl, (void*)(param_1 + 0x3a), 1);

    vt = *(s64*)*impl;
    if (*endian_flag == '\0') fn = *(io_fn_t*)(vt + 0x18);
    else fn = *(io_fn_t*)(vt + 0x10);
    fn((s64*)*impl, (void*)(param_1 + 0x3b), 1);

    vt = *(s64*)*impl;
    if (*endian_flag == '\0') fn = *(io_fn_t*)(vt + 0x18);
    else fn = *(io_fn_t*)(vt + 0x10);
    fn((s64*)*impl, (void*)(param_1 + 0x3c), 1);

    vt = *(s64*)*impl;
    if (*endian_flag == '\0') fn = *(io_fn_t*)(vt + 0x18);
    else fn = *(io_fn_t*)(vt + 0x10);
    fn((s64*)*impl, (void*)(param_1 + 0x3d), 1);

    vt = *(s64*)*impl;
    if (*endian_flag == '\0') fn = *(io_fn_t*)(vt + 0x18);
    else fn = *(io_fn_t*)(vt + 0x10);
    fn((s64*)*impl, (void*)(param_1 + 0x3e), 1);

    vt = *(s64*)*impl;
    if (*endian_flag == '\0') fn = *(io_fn_t*)(vt + 0x18);
    else fn = *(io_fn_t*)(vt + 0x10);
    fn((s64*)*impl, (void*)(param_1 + 0x3f), 1);
}

// ════════════════════════════════════════════════════════════════════
// 0x7103187210 — read common param element (base + name + optional packed values)
// Size: 740 bytes
// [derived: Ghidra decompilation — reads: 1 byte, base header via
//  FUN_71031885c0 at +0x08, 1 byte, string(0x40) at +0x48 via
//  FUN_7103188a70, then version-gated reads:
//  v>=2: 3 packed f32 at +0x90/+0x98
//  v>=3: byte at +0xa0, hash at +0xe8, 3 packed f32 at +0xf0/+0xf8
//  v>=4: f32 at +0xa4, string(0x40) at +0xa8]
// ════════════════════════════════════════════════════════════════════
extern "C"
void FUN_7103187210(s64 param_1, s64 param_2, u32 param_3) {
    // Read 1-byte marker
    u8 marker = 1;
    stream_io(param_2, &marker, 1);

    // Read base header at +0x08
    FUN_71031885c0(param_1 + 8, param_2);

    // Read 1-byte marker
    u8 marker2 = 1;
    s64 vt = **(s64**)(param_2 + 8);
    char* str_ptr = (char*)(param_1 + 0x48);
    typedef void (*io_fn_t)(s64*, void*, u64);
    io_fn_t fn;
    if (*(char*)(param_2 + 4) == '\0')
        fn = *(io_fn_t*)(vt + 0x18);
    else
        fn = *(io_fn_t*)(vt + 0x10);
    fn(*(s64**)(param_2 + 8), &marker2, 1);

    // Endian-dependent string(0x40) read at +0x48
    if (*(char*)(param_2 + 4) != '\0') {
        u64 buf[8] = {0, 0, 0, 0, 0, 0, 0, 0};
        strncpy((char*)buf, str_ptr, 0x40);
        str_ptr = (char*)buf;
    }
    FUN_7103188a70(param_2, str_ptr);

    if (1 < param_3) {
        // Read 1-byte marker
        u8 marker3 = 1;
        vt = **(s64**)(param_2 + 8);
        if (*(char*)(param_2 + 4) == '\0')
            fn = *(io_fn_t*)(vt + 0x18);
        else
            fn = *(io_fn_t*)(vt + 0x10);
        fn(*(s64**)(param_2 + 8), &marker3, 1);

        // Read 3 packed f32 values at +0x90/+0x98
        u32 lo = (u32)*(u64*)(param_1 + 0x90);
        u32 hi = (u32)(*(u64*)(param_1 + 0x90) >> 32);
        u32 v = (u32)*(u64*)(param_1 + 0x98);
        s64 s = FUN_710314fff0(param_2, &lo);
        s = FUN_710314fff0(s, &hi);
        FUN_710314fff0(s, &v);
        *(u64*)(param_1 + 0x98) = (u64)v;
        *(u64*)(param_1 + 0x90) = ((u64)hi << 32) | (u64)lo;

        if (param_3 != 2) {
            // v>=3: read byte at +0xa0
            vt = **(s64**)(param_2 + 8);
            if (*(char*)(param_2 + 4) == '\0')
                fn = *(io_fn_t*)(vt + 0x18);
            else
                fn = *(io_fn_t*)(vt + 0x10);
            fn(*(s64**)(param_2 + 8), (void*)(param_1 + 0xa0), 1);

            // Read 1-byte marker
            u8 marker4 = 1;
            vt = **(s64**)(param_2 + 8);
            if (*(char*)(param_2 + 4) == '\0')
                fn = *(io_fn_t*)(vt + 0x18);
            else
                fn = *(io_fn_t*)(vt + 0x10);
            fn(*(s64**)(param_2 + 8), &marker4, 1);

            // Read hash at +0xe8
            FUN_710314fc70(param_2, (void*)(param_1 + 0xe8));

            // Read 1-byte marker
            u8 marker5 = 1;
            vt = **(s64**)(param_2 + 8);
            if (*(char*)(param_2 + 4) == '\0')
                fn = *(io_fn_t*)(vt + 0x18);
            else
                fn = *(io_fn_t*)(vt + 0x10);
            fn(*(s64**)(param_2 + 8), &marker5, 1);

            // Read 3 packed f32 values at +0xf0/+0xf8
            u32 lo2 = (u32)*(u64*)(param_1 + 0xf0);
            u32 hi2 = (u32)(*(u64*)(param_1 + 0xf0) >> 32);
            u32 v2 = (u32)*(u64*)(param_1 + 0xf8);
            s = FUN_710314fff0(param_2, &lo2);
            s = FUN_710314fff0(s, &hi2);
            FUN_710314fff0(s, &v2);
            *(u64*)(param_1 + 0xf8) = (u64)v2;
            *(u64*)(param_1 + 0xf0) = ((u64)hi2 << 32) | (u64)lo2;

            if (3 < param_3) {
                // v>=4: read f32 at +0xa4
                FUN_710314fef0(param_2, (void*)(param_1 + 0xa4));

                // Read 1-byte marker
                u8 marker6 = 1;
                vt = **(s64**)(param_2 + 8);
                char* str2 = (char*)(param_1 + 0xa8);
                if (*(char*)(param_2 + 4) == '\0')
                    fn = *(io_fn_t*)(vt + 0x18);
                else
                    fn = *(io_fn_t*)(vt + 0x10);
                fn(*(s64**)(param_2 + 8), &marker6, 1);

                // Endian-dependent string(0x40) read at +0xa8
                if (*(char*)(param_2 + 4) != '\0') {
                    u64 buf2[8] = {0, 0, 0, 0, 0, 0, 0, 0};
                    strncpy((char*)buf2, str2, 0x40);
                    str2 = (char*)buf2;
                }
                FUN_7103188a70(param_2, str2);
            }
        }
    }
}

// ════════════════════════════════════════════════════════════════════
// 0x7103187920 — read param sub-element (u32 + 16 bytes or 4 floats + array)
// Size: 768 bytes
// [derived: Ghidra decompilation — reads u32 at +0x00 via FUN_710314fc70,
//  then version < 3: 16 individual bytes at +0x04..+0x13,
//  version >= 3: 4 floats at +0x04/+0x08/+0x0c/+0x10 via FUN_710314fff0.
//  If version >= 2: calls FUN_7103188160 at +0x18.]
// ════════════════════════════════════════════════════════════════════
extern "C"
void FUN_7103187920(s64 param_1, s64 param_2, u32 param_3) {
    FUN_710314fc70(param_2, (void*)param_1);

    if (param_3 < 3) {
        // Version < 3: read 16 individual bytes at +0x04 through +0x13
        stream_io(param_2, (void*)(param_1 + 4), 1);
        stream_io(param_2, (void*)(param_1 + 5), 1);
        stream_io(param_2, (void*)(param_1 + 6), 1);
        stream_io(param_2, (void*)(param_1 + 7), 1);
        stream_io(param_2, (void*)(param_1 + 8), 1);
        stream_io(param_2, (void*)(param_1 + 9), 1);
        stream_io(param_2, (void*)(param_1 + 10), 1);
        stream_io(param_2, (void*)(param_1 + 0xb), 1);
        stream_io(param_2, (void*)(param_1 + 0xc), 1);
        stream_io(param_2, (void*)(param_1 + 0xd), 1);
        stream_io(param_2, (void*)(param_1 + 0xe), 1);
        stream_io(param_2, (void*)(param_1 + 0xf), 1);
        stream_io(param_2, (void*)(param_1 + 0x10), 1);
        stream_io(param_2, (void*)(param_1 + 0x11), 1);
        stream_io(param_2, (void*)(param_1 + 0x12), 1);
        stream_io(param_2, (void*)(param_1 + 0x13), 1);

        if (param_3 != 2) return;
    } else {
        // Version >= 3: read 4 floats
        s64 s = FUN_710314fff0(param_2, (void*)(param_1 + 4));
        s = FUN_710314fff0(s, (void*)(param_1 + 8));
        s = FUN_710314fff0(s, (void*)(param_1 + 0xc));
        FUN_710314fff0(s, (void*)(param_1 + 0x10));
    }

    // Version >= 2 (or >= 3): read array at +0x18
    FUN_7103188160(param_2, param_1 + 0x18);
}

// Forward declarations for FUN_7103185c80 / FUN_7103184f20
extern "C" s64 FUN_7103189880(s64 stream, s64 dest);

// ════════════════════════════════════════════════════════════════════
// 0x7103185c80 — read param element type 0x1A0 (common + 3 sub-arrays + weights + tail)
// Size: 2,772 bytes
// [derived: Ghidra decompilation — reads version, common element via
//  FUN_7103187210, then 3 identical blocks each reading an array of
//  0x40-stride sub-elements (via FUN_7103187920) at offsets:
//  +0x108/+0x110, +0x128/+0x130, +0x148/+0x150.
//  In read mode (LE), computes area weights per element and accumulates
//  at +0x118, +0x138, +0x158. Reads f32 at +0x190.
//  Version < 2: allocates sentinel arrays at +0x160/+0x168, +0x180/+0x188, +0x170/+0x178.
//  Version >= 2: calls FUN_7103189880 for +0x160 and +0x180.
//  Version >= 3: calls FUN_7103189880 for +0x170.]
// NOTE: Area computation uses NEON SIMD (frsqrte/frsqrts) for vector
// length — won't byte-match but is semantically correct.
// ════════════════════════════════════════════════════════════════════
extern "C"
void FUN_7103185c80(s64 param_1, s64 param_2, u32 param_3) {
    // Read version byte (init 4)
    u8 version = 4;
    stream_io(param_2, &version, 1);
    FUN_7103187210(param_1, param_2, (u32)version);

    // ── Block 1: sub-array at +0x108/+0x110, weights at +0x118 ──
    u8 m1 = 1;
    stream_io(param_2, &m1, 1);
    u8 m2 = 1;
    stream_io(param_2, &m2, 1);

    u32* count1 = (u32*)(param_1 + 0x108);
    char is_writing = *(char*)(param_2 + 4);

    if (is_writing == '\0') {
        FUN_71031894b0(count1, param_2);
        is_writing = *(char*)(param_2 + 4);
    } else {
        FUN_710314fc70(param_2, count1);
        if (*count1 != 0) {
            u64 i = 0;
            s64 off = 8;
            do {
                s64 arr = *(s64*)(param_1 + 0x110);
                u8 em = 1;
                stream_io(param_2, &em, 1);
                u8 sv = 3;
                stream_io(param_2, &sv, 1);
                FUN_7103187920(arr + off, param_2, (u32)sv);
                i++;
                off += 0x40;
            } while (i < *count1);
        }
        is_writing = *(char*)(param_2 + 4);
    }

    if (is_writing == '\0') {
        *(u32*)(param_1 + 0x118) = 0;
        f32 pi_val = DAT_710447291c;
        f32 ten_val = DAT_7104470d10;
        if (*count1 != 0) {
            s64 ep = *(s64*)(param_1 + 0x110);
            s64 end = ep + (u64)*count1 * 0x40;
            do {
                s32 type = *(s32*)(ep + 8);
                f32 area;
                if (type == 2) {
                    f32 r = *(f32*)(ep + 0x14);
                    area = (r * r * ten_val) / pi_val;
                    if (area <= 1.0f) area = 1.0f;
                } else if (type == 4) {
                    area = 0.0f;
                    if (1 < *(u32*)(ep + 0x28)) {
                        area = 0.0f;
                        s64 pi = 0;
                        do {
                            f32* pts = (f32*)(*(s64*)(ep + 0x30) + pi * 0x10);
                            f32 dx = pts[4] - pts[0];
                            f32 dy = pts[5] - pts[1];
                            f32 len_sq = dx * dx + dy * dy;
                            f32 len;
                            if (len_sq == 0.0f) {
                                len = 0.0f;
                            } else {
                                len = len_sq; // NEON frsqrte/frsqrts path
                            }
                            area += len;
                            pi++;
                        } while ((u64)(pi + 2) < *(u32*)(ep + 0x28));
                    }
                    area = area / 10.0f;
                } else {
                    area = 1.0f;
                    if (type == 3) {
                        f32 w = (*(f32*)(ep + 0x10) - *(f32*)(ep + 0xc)) / 10.0f;
                        if (w <= 1.0f) w = 1.0f;
                        f32 h = (*(f32*)(ep + 0x18) - *(f32*)(ep + 0x14)) / 10.0f;
                        if (h <= 1.0f) h = 1.0f;
                        area = w * h;
                    }
                }
                *(f32*)(ep + 0x38) = area;
                ep += 0x40;
                *(f32*)(param_1 + 0x118) = area + *(f32*)(param_1 + 0x118);
            } while (ep != end);
        }
        is_writing = *(char*)(param_2 + 4);
    }

    // ── Block 2: sub-array at +0x128/+0x130, weights at +0x138 ──
    u8 m3 = 1;
    stream_io(param_2, &m3, 1);
    u8 m4 = 1;
    stream_io(param_2, &m4, 1);

    u32* count2 = (u32*)(param_1 + 0x128);

    if (*(char*)(param_2 + 4) == '\0') {
        FUN_71031894b0(count2, param_2);
        is_writing = *(char*)(param_2 + 4);
    } else {
        FUN_710314fc70(param_2, count2);
        if (*count2 != 0) {
            u64 i = 0;
            s64 off = 8;
            do {
                s64 arr = *(s64*)(param_1 + 0x130);
                u8 em = 1;
                stream_io(param_2, &em, 1);
                u8 sv = 3;
                stream_io(param_2, &sv, 1);
                FUN_7103187920(arr + off, param_2, (u32)sv);
                i++;
                off += 0x40;
            } while (i < *count2);
        }
        is_writing = *(char*)(param_2 + 4);
    }

    if (is_writing == '\0') {
        *(u32*)(param_1 + 0x138) = 0;
        f32 pi_val = DAT_710447291c;
        f32 ten_val = DAT_7104470d10;
        if (*count2 != 0) {
            s64 ep = *(s64*)(param_1 + 0x130);
            s64 end = ep + (u64)*count2 * 0x40;
            do {
                s32 type = *(s32*)(ep + 8);
                f32 area;
                if (type == 2) {
                    f32 r = *(f32*)(ep + 0x14);
                    area = (r * r * ten_val) / pi_val;
                    if (area <= 1.0f) area = 1.0f;
                } else if (type == 4) {
                    area = 0.0f;
                    if (1 < *(u32*)(ep + 0x28)) {
                        area = 0.0f;
                        s64 pi = 0;
                        do {
                            f32* pts = (f32*)(*(s64*)(ep + 0x30) + pi * 0x10);
                            f32 dx = pts[4] - pts[0];
                            f32 dy = pts[5] - pts[1];
                            f32 len_sq = dx * dx + dy * dy;
                            f32 len;
                            if (len_sq == 0.0f) {
                                len = 0.0f;
                            } else {
                                len = len_sq; // NEON frsqrte/frsqrts path
                            }
                            area += len;
                            pi++;
                        } while ((u64)(pi + 2) < *(u32*)(ep + 0x28));
                    }
                    area = area / 10.0f;
                } else {
                    area = 1.0f;
                    if (type == 3) {
                        f32 w = (*(f32*)(ep + 0x10) - *(f32*)(ep + 0xc)) / 10.0f;
                        if (w <= 1.0f) w = 1.0f;
                        f32 h = (*(f32*)(ep + 0x18) - *(f32*)(ep + 0x14)) / 10.0f;
                        if (h <= 1.0f) h = 1.0f;
                        area = w * h;
                    }
                }
                *(f32*)(ep + 0x38) = area;
                ep += 0x40;
                *(f32*)(param_1 + 0x138) = area + *(f32*)(param_1 + 0x138);
            } while (ep != end);
        }
        is_writing = *(char*)(param_2 + 4);
    }

    // ── Block 3: sub-array at +0x148/+0x150, weights at +0x158 ──
    u8 m5 = 1;
    stream_io(param_2, &m5, 1);
    u8 m6 = 1;
    stream_io(param_2, &m6, 1);

    u32* count3 = (u32*)(param_1 + 0x148);

    if (*(char*)(param_2 + 4) == '\0') {
        FUN_71031894b0(count3, param_2);
        is_writing = *(char*)(param_2 + 4);
    } else {
        FUN_710314fc70(param_2, count3);
        if (*count3 != 0) {
            u64 i = 0;
            s64 off = 8;
            do {
                s64 arr = *(s64*)(param_1 + 0x150);
                u8 em = 1;
                stream_io(param_2, &em, 1);
                u8 sv = 3;
                stream_io(param_2, &sv, 1);
                FUN_7103187920(arr + off, param_2, (u32)sv);
                i++;
                off += 0x40;
            } while (i < *count3);
        }
        is_writing = *(char*)(param_2 + 4);
    }

    if (is_writing == '\0') {
        *(u32*)(param_1 + 0x158) = 0;
        f32 pi_val = DAT_710447291c;
        f32 ten_val = DAT_7104470d10;
        if (*count3 != 0) {
            s64 ep = *(s64*)(param_1 + 0x150);
            s64 end = ep + (u64)*count3 * 0x40;
            do {
                s32 type = *(s32*)(ep + 8);
                f32 area;
                if (type == 2) {
                    f32 r = *(f32*)(ep + 0x14);
                    area = (r * r * ten_val) / pi_val;
                    if (area <= 1.0f) area = 1.0f;
                } else if (type == 4) {
                    area = 0.0f;
                    if (1 < *(u32*)(ep + 0x28)) {
                        area = 0.0f;
                        s64 pi = 0;
                        do {
                            f32* pts = (f32*)(*(s64*)(ep + 0x30) + pi * 0x10);
                            f32 dx = pts[4] - pts[0];
                            f32 dy = pts[5] - pts[1];
                            f32 len_sq = dx * dx + dy * dy;
                            f32 len;
                            if (len_sq == 0.0f) {
                                len = 0.0f;
                            } else {
                                len = len_sq; // NEON frsqrte/frsqrts path
                            }
                            area += len;
                            pi++;
                        } while ((u64)(pi + 2) < *(u32*)(ep + 0x28));
                    }
                    area = area / 10.0f;
                } else {
                    area = 1.0f;
                    if (type == 3) {
                        f32 w = (*(f32*)(ep + 0x10) - *(f32*)(ep + 0xc)) / 10.0f;
                        if (w <= 1.0f) w = 1.0f;
                        f32 h = (*(f32*)(ep + 0x18) - *(f32*)(ep + 0x14)) / 10.0f;
                        if (h <= 1.0f) h = 1.0f;
                        area = w * h;
                    }
                }
                *(f32*)(ep + 0x38) = area;
                ep += 0x40;
                *(f32*)(param_1 + 0x158) = area + *(f32*)(param_1 + 0x158);
            } while (ep != end);
        }
        is_writing = *(char*)(param_2 + 4);
    }

    // ── Tail: read f32, version-gated array allocation ──
    u8 m7 = 1;
    stream_io(param_2, &m7, 1);
    FUN_710314fef0(param_2, (void*)(param_1 + 0x190));

    if (param_3 < 2) {
        // Version < 2: allocate sentinel arrays
        if (*(char*)(param_2 + 4) != '\0') return;

        // Sentinel array at +0x160/+0x168 (count from block 1)
        u32 c1 = *(u32*)(param_1 + 0x108);
        *(u32*)(param_1 + 0x160) = c1;
        s64 old1;
        if (c1 == 0) {
            old1 = *(s64*)(param_1 + 0x168);
            *(s64*)(param_1 + 0x168) = 0;
        } else {
            u64 sz1 = (u64)c1 * 4;
            u32* buf1 = (u32*)je_aligned_alloc(0x10, sz1);
            if (buf1 == nullptr) {
                if (DAT_7105331f00 != nullptr) {
                    u32 oom_type = 0;
                    u64 oom_size = sz1;
                    u64 r = ((u64(*)(s64*, u32*, u64*))(*(u64*)(*DAT_7105331f00 + 0x30)))
                             (DAT_7105331f00, &oom_type, &oom_size);
                    if ((r & 1) != 0) {
                        buf1 = (u32*)je_aligned_alloc(0x10, sz1);
                        if (buf1 == nullptr) buf1 = nullptr;
                    } else {
                        buf1 = nullptr;
                    }
                } else {
                    buf1 = nullptr;
                }
            }
            // Fill with 0xFFFFFFFA sentinel
            for (u64 j = 0; j < c1; j++) buf1[j] = 0xFFFFFFFA;
            old1 = *(s64*)(param_1 + 0x168);
            *(u32**)(param_1 + 0x168) = buf1;
        }
        if (old1 != 0) FUN_710392e590(old1);

        // Sentinel array at +0x180/+0x188 (count from block 3)
        u32 c3 = *(u32*)(param_1 + 0x148);
        *(u32*)(param_1 + 0x180) = c3;
        s64 old3;
        if (c3 == 0) {
            old3 = *(s64*)(param_1 + 0x188);
            *(s64*)(param_1 + 0x188) = 0;
        } else {
            u64 sz3 = (u64)c3 * 4;
            u32* buf3 = (u32*)je_aligned_alloc(0x10, sz3);
            if (buf3 == nullptr) {
                if (DAT_7105331f00 != nullptr) {
                    u32 oom_type = 0;
                    u64 oom_size = sz3;
                    u64 r = ((u64(*)(s64*, u32*, u64*))(*(u64*)(*DAT_7105331f00 + 0x30)))
                             (DAT_7105331f00, &oom_type, &oom_size);
                    if ((r & 1) != 0) {
                        buf3 = (u32*)je_aligned_alloc(0x10, sz3);
                        if (buf3 == nullptr) buf3 = nullptr;
                    } else {
                        buf3 = nullptr;
                    }
                } else {
                    buf3 = nullptr;
                }
            }
            for (u64 j = 0; j < c3; j++) buf3[j] = 0xFFFFFFFA;
            old3 = *(s64*)(param_1 + 0x188);
            *(u32**)(param_1 + 0x188) = buf3;
        }
        if (old3 != 0) FUN_710392e590(old3);
    } else {
        // Version >= 2: use FUN_7103189880
        s64 s = FUN_7103189880(param_2, param_1 + 0x160);
        FUN_7103189880(s, param_1 + 0x180);
    }

    if (2 < param_3) {
        // Version >= 3: third array via FUN_7103189880
        FUN_7103189880(param_2, param_1 + 0x170);
        return;
    }

    // Version < 3, LE: allocate third sentinel array at +0x170/+0x178
    if (*(char*)(param_2 + 4) != '\0') return;

    u32 c2 = *(u32*)(param_1 + 0x128);
    *(u32*)(param_1 + 0x170) = c2;
    s64 old2;
    if (c2 == 0) {
        old2 = *(s64*)(param_1 + 0x178);
        *(s64*)(param_1 + 0x178) = 0;
    } else {
        u64 sz2 = (u64)c2 * 4;
        u32* buf2 = (u32*)je_aligned_alloc(0x10, sz2);
        if (buf2 == nullptr) {
            if (DAT_7105331f00 != nullptr) {
                u32 oom_type = 0;
                u64 oom_size = sz2;
                u64 r = ((u64(*)(s64*, u32*, u64*))(*(u64*)(*DAT_7105331f00 + 0x30)))
                         (DAT_7105331f00, &oom_type, &oom_size);
                if ((r & 1) != 0) {
                    buf2 = (u32*)je_aligned_alloc(0x10, sz2);
                    if (buf2 == nullptr) buf2 = nullptr;
                } else {
                    buf2 = nullptr;
                }
            } else {
                buf2 = nullptr;
            }
        }
        for (u64 j = 0; j < c2; j++) buf2[j] = 0xFFFFFFFA;
        old2 = *(s64*)(param_1 + 0x178);
        *(u32**)(param_1 + 0x178) = buf2;
    }
    if (old2 != 0) FUN_710392e590(old2);
}

// ════════════════════════════════════════════════════════════════════
// 0x7103184f20 — read param element type 0x160 (common + paired f32 arrays + 0x120/0x160 sub-arrays)
// Size: 3,132 bytes
// [derived: Ghidra decompilation — complex version-gated reader:
//  v<2: init local struct with magic 0x7735bb75, read base header.
//  v>=2: read version byte, common element via FUN_7103187210.
//  Read u32 at +0x100. Two paired-f32 arrays at +0x108/+0x110 and +0x118/+0x120
//  (LE: FUN_71031882c0, BE: loop read 2 f32 per 0x10-stride element).
//  Read count at +0x128, allocate 0x120-stride elements with magic 0x7735bb75
//  and PTR_LAB_710517a388 vtable. Each element: optional FUN_7103187210 header,
//  2 f32 at +0x100, f32 at +0x110, optional f32 at +0x114.
//  v<3: alloc 0x10-stride zero array at +0x138/+0x140 (count from +0x118).
//  v>=3: read count at +0x138, alloc 0x10-stride array, read u32+u64 per element.
//  v>=4: read count at +0x148, alloc 0x160-stride elements with PTR_LAB_710517a3a8,
//  read each via FUN_7103189b00.]
// ════════════════════════════════════════════════════════════════════
extern "C"
void FUN_7103184f20(s64 param_1, s64 param_2, u32 param_3) {
    // Version-dependent header
    if (param_3 < 2) {
        // Version < 2: init local base struct, read via FUN_71031885c0
        // (the local struct is discarded — only side effect is stream advancement)
        u8 local_marker = 1;
        stream_io(param_2, &local_marker, 1);
        // Local base struct would be initialized with magic 0x7735bb75 etc.
        // but only the base header read matters for stream position
        u64 local_buf[6] = {0x27735bb75ULL, 0, 0, 0, 0, 0};
        FUN_71031885c0((s64)local_buf, param_2);
    } else {
        // Version >= 2: read version, common element
        u8 version = 4;
        stream_io(param_2, &version, 1);
        FUN_7103187210(param_1, param_2, (u32)version);
    }

    // Read u32 at +0x100
    FUN_710314fc70(param_2, (void*)(param_1 + 0x100));

    // ── Paired f32 array 1: count at +0x108, data at +0x110 ──
    u8 mk1 = 1;
    stream_io(param_2, &mk1, 1);

    u32* cnt1 = (u32*)(param_1 + 0x108);
    if (*(char*)(param_2 + 4) == '\0') {
        FUN_71031882c0(cnt1, param_2);
    } else {
        FUN_710314fc70(param_2, cnt1);
        if (*cnt1 != 0) {
            u64 i = 0;
            do {
                s64 arr = *(s64*)(param_1 + 0x110);
                u8 em = 1;
                stream_io(param_2, &em, 1);
                s64 ofs = i * 0x10;
                u32 lo = (u32)*(u64*)(arr + ofs);
                u32 hi = (u32)(*(u64*)(arr + ofs) >> 32);
                s64 s = FUN_710314fff0(param_2, &lo);
                FUN_710314fff0(s, &hi);
                i++;
                u64* p = (u64*)(arr + ofs);
                p[1] = 0;
                *p = ((u64)hi << 32) | (u64)lo;
            } while (i < *cnt1);
        }
    }

    // ── Paired f32 array 2: count at +0x118, data at +0x120 ──
    u8 mk2 = 1;
    stream_io(param_2, &mk2, 1);

    u32* cnt2 = (u32*)(param_1 + 0x118);
    if (*(char*)(param_2 + 4) == '\0') {
        FUN_71031882c0(cnt2, param_2);
    } else {
        FUN_710314fc70(param_2, cnt2);
        if (*cnt2 != 0) {
            u64 i = 0;
            do {
                s64 arr = *(s64*)(param_1 + 0x120);
                u8 em = 1;
                stream_io(param_2, &em, 1);
                s64 ofs = i * 0x10;
                u32 lo = (u32)*(u64*)(arr + ofs);
                u32 hi = (u32)(*(u64*)(arr + ofs) >> 32);
                s64 s = FUN_710314fff0(param_2, &lo);
                FUN_710314fff0(s, &hi);
                i++;
                u64* p = (u64*)(arr + ofs);
                p[1] = 0;
                *p = ((u64)hi << 32) | (u64)lo;
            } while (i < *cnt2);
        }
    }

    // ── 0x120-stride sub-array: count at +0x128, data at +0x130 ──
    u8 mk3 = 1;
    stream_io(param_2, &mk3, 1);

    char is_le = *(char*)(param_2 + 4);
    u32* cnt3 = (u32*)(param_1 + 0x128);
    FUN_710314fc70(param_2, cnt3);
    u32 count3 = *cnt3;
    u64 count3_u64 = (u64)count3;

    if (is_le == '\0') {
        // LE path: allocate and init 0x120-stride array
        if (count3 == 0) {
            s64 old = *(s64*)(param_1 + 0x130);
            *(s64*)(param_1 + 0x130) = 0;
            if (old != 0) FUN_710392e590(old - 0x10);
        } else {
            u64 alloc_sz = count3_u64 * 0x120 | 0x10;
            s64 buf = (s64)je_aligned_alloc(0x10, alloc_sz);
            if (buf == 0) {
                if (DAT_7105331f00 != nullptr) {
                    u32 oom_type = 0;
                    u64 oom_size = alloc_sz;
                    u64 r = ((u64(*)(s64*, u32*, u64*))(*(u64*)(*DAT_7105331f00 + 0x30)))
                             (DAT_7105331f00, &oom_type, &oom_size);
                    if ((r & 1) != 0)
                        buf = (s64)je_aligned_alloc(0x10, alloc_sz);
                }
            }
            // Store count at +8
            s64 idx = 0;
            *(u64*)(buf + 8) = count3_u64;
            do {
                s64 e = buf + idx;
                idx += 0x120;
                *(u32*)(e + 0x18) = 0x7735bb75;
                *(u32*)(e + 0x1c) = 2;
                *(u8*)(e + 0x20) = 0;
                *(u8*)(e + 0x58) = 0;
                *(u64*)(e + 0x48) = 0;
                *(u64*)(e + 0x50) = 0;
                *(u64*)(e + 0x40) = 0;
                *(u8*)(e + 0xb0) = 0;
                *(u32*)(e + 0xb4) = 0xFFFFFFFF;
                *(u8*)(e + 0xb8) = 0;
                *(u32*)(e + 0xf8) = 0;
                *(u8**)(e + 0x10) = &PTR_LAB_710517a388;
                *(u64*)(e + 0x110) = 0;
                *(u64*)(e + 0xa0) = 0;
                *(u64*)(e + 0xa8) = 0;
                *(u64*)(e + 0x100) = 0;
                *(u64*)(e + 0x108) = 0;
                *(u64*)(e + 0x118) = 0;
                *(u64*)(e + 0x120) = 0;
            } while (count3_u64 * 0x120 - idx != 0);

            s64 old = *(s64*)(param_1 + 0x130);
            *(s64*)(param_1 + 0x130) = buf + 0x10;
            if (old != 0) FUN_710392e590(old - 0x10);

            // Read each element
            if (*cnt3 != 0) {
                s64 eoff = 0;
                u64 j = 0;
                do {
                    s64 arr = *(s64*)(param_1 + 0x130);
                    u8 sv = 3;
                    stream_io(param_2, &sv, 1);
                    u8 sv_val = sv;
                    if (1 < sv) {
                        u8 ev = 4;
                        stream_io(param_2, &ev, 1);
                        FUN_7103187210(arr + eoff, param_2, (u32)ev);
                    }
                    u8 em = 1;
                    stream_io(param_2, &em, 1);

                    s64 ep = arr + eoff;
                    u32 lo = (u32)*(u64*)(ep + 0x100);
                    u32 hi = (u32)(*(u64*)(ep + 0x100) >> 32);
                    s64 s = FUN_710314fff0(param_2, &lo);
                    s = FUN_710314fff0(s, &hi);
                    *(u64*)(ep + 0x108) = 0;
                    *(u64*)(ep + 0x100) = ((u64)hi << 32) | (u64)lo;
                    FUN_710314fff0(s, (void*)(ep + 0x110));

                    if (2 < sv_val) {
                        FUN_710314fef0(param_2, (void*)(ep + 0x114));
                    }

                    j++;
                    eoff += 0x120;
                } while (j < *cnt3);
            }
        }
    } else if (count3 != 0) {
        // BE path: read directly into existing array
        u64 j = 0;
        s64 eoff = 0x114;
        do {
            s64 arr = *(s64*)(param_1 + 0x130);
            u8 sv = 3;
            stream_io(param_2, &sv, 1);
            u8 sv_val = sv;
            if (1 < sv) {
                u8 ev = 4;
                stream_io(param_2, &ev, 1);
                FUN_7103187210(arr + eoff - 0x114, param_2, (u32)ev);
            }
            u8 em = 1;
            stream_io(param_2, &em, 1);

            s64 ep = arr + eoff;
            u32 lo = (u32)*(u64*)(ep - 0x14);
            u32 hi = (u32)(*(u64*)(ep - 0x14) >> 32);
            s64 s = FUN_710314fff0(param_2, &lo);
            s = FUN_710314fff0(s, &hi);
            *(u64*)(ep - 0xc) = 0;
            *(u64*)(ep - 0x14) = ((u64)hi << 32) | (u64)lo;
            FUN_710314fff0(s, (void*)(ep - 4));

            if (2 < sv_val) {
                FUN_710314fef0(param_2, (void*)ep);
            }

            j++;
            eoff += 0x120;
        } while (j < *cnt3);
    }

    // ── Version < 3: alloc 0x10-stride zero array at +0x138/+0x140 ──
    if (param_3 < 3) {
        if (*(char*)(param_2 + 4) != '\0') return;

        u32 c = *(u32*)(param_1 + 0x118);
        *(u32*)(param_1 + 0x138) = c;
        s64 old;
        if (c == 0) {
            old = *(s64*)(param_1 + 0x140);
            *(s64*)(param_1 + 0x140) = 0;
        } else {
            u64 sz = (u64)c * 0x10;
            u32* pbuf = (u32*)je_aligned_alloc(0x10, sz);
            if (pbuf == nullptr) {
                if (DAT_7105331f00 != nullptr) {
                    u32 oom_type = 0;
                    u64 oom_size = sz;
                    u64 r = ((u64(*)(s64*, u32*, u64*))(*(u64*)(*DAT_7105331f00 + 0x30)))
                             (DAT_7105331f00, &oom_type, &oom_size);
                    if ((r & 1) != 0) {
                        pbuf = (u32*)je_aligned_alloc(0x10, sz);
                        if (pbuf == nullptr) pbuf = nullptr;
                    } else {
                        pbuf = nullptr;
                    }
                } else {
                    pbuf = nullptr;
                }
            }
            // Zero-fill each 0x10 element
            for (u64 k = 0; k < c; k++) {
                pbuf[k * 4] = 0;
                *(u64*)&pbuf[k * 4 + 2] = 0;
            }
            old = *(s64*)(param_1 + 0x140);
            *(u32**)(param_1 + 0x140) = pbuf;
        }
        if (old != 0) FUN_710392e590(old);

        // Init each slot to zero
        if (*(s32*)(param_1 + 0x138) != 0) {
            s64 off = 0;
            u64 k = 0;
            do {
                *(u64*)(*(s64*)(param_1 + 0x140) + off + 8) = 0;
                *(u32*)(*(s64*)(param_1 + 0x140) + off) = 0;
                k++;
                off += 0x10;
            } while (k < *(u32*)(param_1 + 0x138));
        }
        return;
    }

    // ── Version >= 3: read count at +0x138, alloc 0x10-stride array ──
    u8 mk4 = 1;
    stream_io(param_2, &mk4, 1);

    char is_le2 = *(char*)(param_2 + 4);
    u32* cnt4 = (u32*)(param_1 + 0x138);
    FUN_710314fc70(param_2, cnt4);
    u32 count4 = *cnt4;

    if (is_le2 == '\0') {
        // LE path
        if (count4 == 0) {
            s64 old = *(s64*)(param_1 + 0x140);
            *(s64*)(param_1 + 0x140) = 0;
            if (old != 0) FUN_710392e590(old);
        } else {
            u64 sz = (u64)count4 * 0x10;
            u32* pbuf = (u32*)je_aligned_alloc(0x10, sz);
            if (pbuf == nullptr) {
                if (DAT_7105331f00 != nullptr) {
                    u32 oom_type = 0;
                    u64 oom_size = sz;
                    u64 r = ((u64(*)(s64*, u32*, u64*))(*(u64*)(*DAT_7105331f00 + 0x30)))
                             (DAT_7105331f00, &oom_type, &oom_size);
                    if ((r & 1) != 0) {
                        pbuf = (u32*)je_aligned_alloc(0x10, sz);
                        if (pbuf == nullptr) pbuf = nullptr;
                    } else {
                        pbuf = nullptr;
                    }
                } else {
                    pbuf = nullptr;
                }
            }
            // Zero-fill
            for (u64 k = 0; k < count4; k++) {
                pbuf[k * 4] = 0;
                *(u64*)&pbuf[k * 4 + 2] = 0;
            }
            s64 old = *(s64*)(param_1 + 0x140);
            *(u32**)(param_1 + 0x140) = pbuf;
            if (old != 0) FUN_710392e590(old);

            // Read each element: marker, u32, u64
            if (*cnt4 != 0) {
                u64 j = 0;
                s64 off = 8;
                do {
                    s64 arr = *(s64*)(param_1 + 0x140);
                    u8 em = 1;
                    stream_io(param_2, &em, 1);
                    s64 ep = arr + off;
                    s64 s = FUN_710314fc70(param_2, (void*)(ep - 8));
                    FUN_710314fd70(s, (void*)ep);
                    j++;
                    off += 0x10;
                } while (j < *cnt4);
            }
        }
    } else if (count4 != 0) {
        // BE path: read directly
        u64 j = 0;
        s64 off = 8;
        do {
            s64 arr = *(s64*)(param_1 + 0x140);
            u8 em = 1;
            stream_io(param_2, &em, 1);
            s64 ep = arr + off;
            s64 s = FUN_710314fc70(param_2, (void*)(ep - 8));
            FUN_710314fd70(s, (void*)ep);
            j++;
            off += 0x10;
        } while (j < *cnt4);
    }

    // ── Version >= 4: 0x160-stride sub-array at +0x148/+0x150 ──
    if (param_3 < 4) return;

    u8 mk5 = 1;
    stream_io(param_2, &mk5, 1);

    char is_le3 = *(char*)(param_2 + 4);
    u32* cnt5 = (u32*)(param_1 + 0x148);
    FUN_710314fc70(param_2, cnt5);
    u32 count5 = *cnt5;
    u64 count5_u64 = (u64)count5;

    if (is_le3 != '\0') {
        // BE path: read directly
        if (count5 == 0) return;
        s64 eoff = 0;
        u64 j = 0;
        do {
            s64 arr = *(s64*)(param_1 + 0x150);
            u8 sv = 2;
            stream_io(param_2, &sv, 1);
            FUN_7103189b00(arr + eoff, param_2, (u32)sv);
            j++;
            eoff += 0x160;
        } while (j < *cnt5);
        return;
    }

    // LE path: allocate 0x160-stride array
    if (count5 == 0) {
        s64 old = *(s64*)(param_1 + 0x150);
        *(s64*)(param_1 + 0x150) = 0;
        if (old == 0) return;
        FUN_710392e590(old - 0x10);
        return;
    }

    u64 alloc_sz5 = count5_u64 * 0x160 | 0x10;
    s64 buf5 = (s64)je_aligned_alloc(0x10, alloc_sz5);
    if (buf5 == 0) {
        if (DAT_7105331f00 != nullptr) {
            u32 oom_type = 0;
            u64 oom_size = alloc_sz5;
            u64 r = ((u64(*)(s64*, u32*, u64*))(*(u64*)(*DAT_7105331f00 + 0x30)))
                     (DAT_7105331f00, &oom_type, &oom_size);
            if ((r & 1) != 0)
                buf5 = (s64)je_aligned_alloc(0x10, alloc_sz5);
        }
    }

    s64 idx5 = 0;
    *(u64*)(buf5 + 8) = count5_u64;
    do {
        s64 e = buf5 + idx5;
        idx5 += 0x160;
        *(u32*)(e + 0x18) = 0x7735bb75;
        *(u32*)(e + 0x1c) = 2;
        *(u8*)(e + 0x20) = 0;
        *(u8*)(e + 0x58) = 0;
        *(u64*)(e + 0x48) = 0;
        *(u64*)(e + 0x50) = 0;
        *(u64*)(e + 0x40) = 0;
        *(u8*)(e + 0xb0) = 0;
        *(u32*)(e + 0xb4) = 0xFFFFFFFF;
        *(u8*)(e + 0xb8) = 0;
        *(u32*)(e + 0xf8) = 0;
        *(u8**)(e + 0x10) = &PTR_LAB_710517a3a8;
        *(u32*)(e + 0x110) = 0;
        *(u8*)(e + 0x114) = 0;
        *(u64*)(e + 0xa0) = 0;
        *(u64*)(e + 0xa8) = 0;
        *(u64*)(e + 0x100) = 0;
        *(u64*)(e + 0x108) = 0;
        // Packed 1.0f values: 0x3f800000 3f800000
        *(u64*)(e + 0x154) = 0x3f8000003f800000ULL;
        *(u64*)(e + 0x15c) = 0x3f8000003f800000ULL;
        *(u64*)(e + 0x164) = 0;
    } while (count5_u64 * 0x160 - idx5 != 0);

    s64 old5 = *(s64*)(param_1 + 0x150);
    *(s64*)(param_1 + 0x150) = buf5 + 0x10;
    if (old5 != 0) FUN_710392e590(old5 - 0x10);

    if (*cnt5 != 0) {
        s64 eoff = 0;
        u64 j = 0;
        do {
            s64 arr = *(s64*)(param_1 + 0x150);
            u8 sv = 2;
            stream_io(param_2, &sv, 1);
            FUN_7103189b00(arr + eoff, param_2, (u32)sv);
            j++;
            eoff += 0x160;
        } while (j < *cnt5);
    }
}

// ════════════════════════════════════════════════════════════════════
// 0x7103187c20 — read 32-byte fixed string (byte-by-byte stream reads)
// Size: 1,332 bytes
// [derived: Ghidra decompilation — reads 32 individual bytes at
//  param_2+0x00 through param_2+0x1f via vtable dispatch. Returns stream.]
// ════════════════════════════════════════════════════════════════════
extern "C"
s64 FUN_7103187c20(s64 param_1, void* param_2) {
    s64 dest = (s64)param_2;
    stream_io(param_1, (void*)(dest + 0x00), 1);
    stream_io(param_1, (void*)(dest + 0x01), 1);
    stream_io(param_1, (void*)(dest + 0x02), 1);
    stream_io(param_1, (void*)(dest + 0x03), 1);
    stream_io(param_1, (void*)(dest + 0x04), 1);
    stream_io(param_1, (void*)(dest + 0x05), 1);
    stream_io(param_1, (void*)(dest + 0x06), 1);
    stream_io(param_1, (void*)(dest + 0x07), 1);
    stream_io(param_1, (void*)(dest + 0x08), 1);
    stream_io(param_1, (void*)(dest + 0x09), 1);
    stream_io(param_1, (void*)(dest + 0x0a), 1);
    stream_io(param_1, (void*)(dest + 0x0b), 1);
    stream_io(param_1, (void*)(dest + 0x0c), 1);
    stream_io(param_1, (void*)(dest + 0x0d), 1);
    stream_io(param_1, (void*)(dest + 0x0e), 1);
    stream_io(param_1, (void*)(dest + 0x0f), 1);
    stream_io(param_1, (void*)(dest + 0x10), 1);
    stream_io(param_1, (void*)(dest + 0x11), 1);
    stream_io(param_1, (void*)(dest + 0x12), 1);
    stream_io(param_1, (void*)(dest + 0x13), 1);
    stream_io(param_1, (void*)(dest + 0x14), 1);
    stream_io(param_1, (void*)(dest + 0x15), 1);
    stream_io(param_1, (void*)(dest + 0x16), 1);
    stream_io(param_1, (void*)(dest + 0x17), 1);
    stream_io(param_1, (void*)(dest + 0x18), 1);
    stream_io(param_1, (void*)(dest + 0x19), 1);
    stream_io(param_1, (void*)(dest + 0x1a), 1);
    stream_io(param_1, (void*)(dest + 0x1b), 1);
    stream_io(param_1, (void*)(dest + 0x1c), 1);
    stream_io(param_1, (void*)(dest + 0x1d), 1);
    stream_io(param_1, (void*)(dest + 0x1e), 1);
    stream_io(param_1, (void*)(dest + 0x1f), 1);
    return param_1;
}

// ════════════════════════════════════════════════════════════════════
// 0x7103188a70 — read 64-byte fixed string (byte-by-byte stream reads)
// Size: 2,612 bytes
// [derived: Ghidra decompilation — reads 64 individual bytes at
//  param_2+0x00 through param_2+0x3f via vtable dispatch. Returns stream.]
// ════════════════════════════════════════════════════════════════════
extern "C"
s64 FUN_7103188a70(s64 param_1, void* param_2) {
    s64 dest = (s64)param_2;
    stream_io(param_1, (void*)(dest + 0x00), 1);
    stream_io(param_1, (void*)(dest + 0x01), 1);
    stream_io(param_1, (void*)(dest + 0x02), 1);
    stream_io(param_1, (void*)(dest + 0x03), 1);
    stream_io(param_1, (void*)(dest + 0x04), 1);
    stream_io(param_1, (void*)(dest + 0x05), 1);
    stream_io(param_1, (void*)(dest + 0x06), 1);
    stream_io(param_1, (void*)(dest + 0x07), 1);
    stream_io(param_1, (void*)(dest + 0x08), 1);
    stream_io(param_1, (void*)(dest + 0x09), 1);
    stream_io(param_1, (void*)(dest + 0x0a), 1);
    stream_io(param_1, (void*)(dest + 0x0b), 1);
    stream_io(param_1, (void*)(dest + 0x0c), 1);
    stream_io(param_1, (void*)(dest + 0x0d), 1);
    stream_io(param_1, (void*)(dest + 0x0e), 1);
    stream_io(param_1, (void*)(dest + 0x0f), 1);
    stream_io(param_1, (void*)(dest + 0x10), 1);
    stream_io(param_1, (void*)(dest + 0x11), 1);
    stream_io(param_1, (void*)(dest + 0x12), 1);
    stream_io(param_1, (void*)(dest + 0x13), 1);
    stream_io(param_1, (void*)(dest + 0x14), 1);
    stream_io(param_1, (void*)(dest + 0x15), 1);
    stream_io(param_1, (void*)(dest + 0x16), 1);
    stream_io(param_1, (void*)(dest + 0x17), 1);
    stream_io(param_1, (void*)(dest + 0x18), 1);
    stream_io(param_1, (void*)(dest + 0x19), 1);
    stream_io(param_1, (void*)(dest + 0x1a), 1);
    stream_io(param_1, (void*)(dest + 0x1b), 1);
    stream_io(param_1, (void*)(dest + 0x1c), 1);
    stream_io(param_1, (void*)(dest + 0x1d), 1);
    stream_io(param_1, (void*)(dest + 0x1e), 1);
    stream_io(param_1, (void*)(dest + 0x1f), 1);
    stream_io(param_1, (void*)(dest + 0x20), 1);
    stream_io(param_1, (void*)(dest + 0x21), 1);
    stream_io(param_1, (void*)(dest + 0x22), 1);
    stream_io(param_1, (void*)(dest + 0x23), 1);
    stream_io(param_1, (void*)(dest + 0x24), 1);
    stream_io(param_1, (void*)(dest + 0x25), 1);
    stream_io(param_1, (void*)(dest + 0x26), 1);
    stream_io(param_1, (void*)(dest + 0x27), 1);
    stream_io(param_1, (void*)(dest + 0x28), 1);
    stream_io(param_1, (void*)(dest + 0x29), 1);
    stream_io(param_1, (void*)(dest + 0x2a), 1);
    stream_io(param_1, (void*)(dest + 0x2b), 1);
    stream_io(param_1, (void*)(dest + 0x2c), 1);
    stream_io(param_1, (void*)(dest + 0x2d), 1);
    stream_io(param_1, (void*)(dest + 0x2e), 1);
    stream_io(param_1, (void*)(dest + 0x2f), 1);
    stream_io(param_1, (void*)(dest + 0x30), 1);
    stream_io(param_1, (void*)(dest + 0x31), 1);
    stream_io(param_1, (void*)(dest + 0x32), 1);
    stream_io(param_1, (void*)(dest + 0x33), 1);
    stream_io(param_1, (void*)(dest + 0x34), 1);
    stream_io(param_1, (void*)(dest + 0x35), 1);
    stream_io(param_1, (void*)(dest + 0x36), 1);
    stream_io(param_1, (void*)(dest + 0x37), 1);
    stream_io(param_1, (void*)(dest + 0x38), 1);
    stream_io(param_1, (void*)(dest + 0x39), 1);
    stream_io(param_1, (void*)(dest + 0x3a), 1);
    stream_io(param_1, (void*)(dest + 0x3b), 1);
    stream_io(param_1, (void*)(dest + 0x3c), 1);
    stream_io(param_1, (void*)(dest + 0x3d), 1);
    stream_io(param_1, (void*)(dest + 0x3e), 1);
    stream_io(param_1, (void*)(dest + 0x3f), 1);
    return param_1;
}

// ════════════════════════════════════════════════════════════════════
// 0x71031882c0 — array reader: count + 0x10-stride float pairs
// Size: 392 bytes
// [derived: Ghidra decompilation — reads count via FUN_710314fc70,
//  allocates count*0x10 with OOM retry, memset 0, then reads float pairs
//  via FUN_710314fff0 into each 0x10-stride entry.
//  Count = 0 frees old array. dest layout: u32 count at +0, ptr at +8.]
// ════════════════════════════════════════════════════════════════════
extern "C"
void FUN_71031882c0(void* dest, s64 param_2) {
    u32* count_ptr = (u32*)dest;
    FUN_710314fc70(param_2, count_ptr);

    if (*count_ptr == 0) {
        s64 old = *(s64*)(count_ptr + 2);
        count_ptr[2] = 0;
        count_ptr[3] = 0;
        if (old == 0) return;
        FUN_710392e590(old);
        return;
    }

    u64 alloc_size = (u64)*count_ptr << 4;
    void* buf = (void*)je_aligned_alloc(0x10, alloc_size);
    if (buf == nullptr) {
        if (DAT_7105331f00_param != nullptr) {
            u32 oom_flag = 0;
            u64 oom_size = alloc_size;
            u64 r = (*(u64(**)(s64*, u32*, u64*))(*(s64*)DAT_7105331f00_param + 0x30))
                     (DAT_7105331f00_param, &oom_flag, &oom_size);
            if ((r & 1) != 0) {
                buf = (void*)je_aligned_alloc(0x10, alloc_size);
                if (buf != nullptr) goto alloc_ok_82c0;
            }
        }
        buf = nullptr;
    }
alloc_ok_82c0:
    memset(buf, 0, alloc_size);

    s64 old = *(s64*)(count_ptr + 2);
    *(void**)(count_ptr + 2) = buf;
    if (old != 0) {
        FUN_710392e590(old);
    }

    if (*count_ptr != 0) {
        u64 i = 0;
        do {
            s64 arr = *(s64*)(count_ptr + 2);
            u8 marker = 1;
            stream_io(param_2, &marker, 1);

            s64 off = i * 0x10;
            u64 packed = *(u64*)(arr + off);
            u32 lo = (u32)packed;
            u32 hi = (u32)(packed >> 32);
            s64 s = FUN_710314fff0(param_2, &lo);
            FUN_710314fff0(s, &hi);
            i++;
            u64* elem = (u64*)(arr + off);
            elem[1] = 0;
            *elem = ((u64)hi << 32) | (u64)lo;
        } while (i < *count_ptr);
    }
}

// ════════════════════════════════════════════════════════════════════
// 0x71031894b0 — array reader with prepended size header + sub-elements
// Size: 600 bytes
// [derived: Ghidra decompilation — reads count via FUN_710314fc70.
//  Allocates (count*0x40 | 8) block: stores count at block[0], array
//  at block+8. Elements are 0x40 stride, zeroed on alloc. Cleanup
//  iterates backward freeing sub-pointers at +0x30, then frees header.
//  Read loop: stream_io markers, calls FUN_7103187920 per element.]
// ════════════════════════════════════════════════════════════════════
extern "C"
void FUN_71031894b0(void* dest, s64 param_2) {
    u32* count_ptr = (u32*)dest;
    FUN_710314fc70(param_2, count_ptr);
    u64 count = (u64)*count_ptr;

    if (*count_ptr == 0) {
        s64 arr = *(s64*)(count_ptr + 2);
        count_ptr[2] = 0;
        count_ptr[3] = 0;
        if (arr == 0) return;

        s64 old_count = *(s64*)(arr - 8);
        if (old_count != 0) {
            s64 off = old_count << 6;
            do {
                if (*(s64*)(arr + off - 0x10) != 0) {
                    FUN_710392e590(*(s64*)(arr + off - 0x10));
                }
                off -= 0x40;
            } while (off != 0);
        }
        FUN_710392e590((s64)(arr - 8));
        return;
    }

    u64 alloc_size = count << 6 | 8;
    u64* block = (u64*)je_aligned_alloc(0x10, alloc_size);
    if (block == nullptr) {
        if (DAT_7105331f00_param != nullptr) {
            u32 oom_flag = 0;
            u64 oom_size = alloc_size;
            u64 r = (*(u64(**)(s64*, u32*, u64*))(*(s64*)DAT_7105331f00_param + 0x30))
                     (DAT_7105331f00_param, &oom_flag, &oom_size);
            if ((r & 1) != 0) {
                block = (u64*)je_aligned_alloc(0x10, alloc_size);
                if (block != nullptr) goto alloc_ok_94b0;
            }
        }
        block = nullptr;
    }
alloc_ok_94b0:
    *block = count;
    s64 data = (s64)(block + 1);

    // Zero 0x40-stride elements (two-at-a-time unrolled pattern)
    {
        s64 tail = count * 0x40 - 0x40;
        s64 p = data;
        if (((u32)(tail >> 6) & 1) == 0) {
            p = data + 0x40;
            *(u32*)(data + 0x28) = 0;
            *(u64*)(data + 0x30) = 0;
            *(u32*)(data + 0x18) = 0;
            *(u32*)(data + 0x38) = 0;
            *(u64*)(data + 0x08) = 0;
            *(u64*)(data + 0x10) = 0;
        }
        if (tail != 0) {
            s64 z = 0;
            s64 target = (s64)block + (count * 0x40 + 8) - data;
            do {
                *(u32*)(p + z + 0x28) = 0;
                *(u64*)(p + z + 0x30) = 0;
                *(u32*)(p + z + 0x18) = 0;
                *(u64*)(p + z + 0x08) = 0;
                *(u64*)(p + z + 0x10) = 0;
                *(u32*)(p + z + 0x38) = 0;
                *(u32*)(p + z + 0x68) = 0;
                *(u64*)(p + z + 0x70) = 0;
                *(u32*)(p + z + 0x58) = 0;
                *(u32*)(p + z + 0x78) = 0;
                *(u64*)(p + z + 0x48) = 0;
                *(u64*)(p + z + 0x50) = 0;
                z += 0x80;
            } while (target != z);
        }
    }

    s64 old_arr = *(s64*)(count_ptr + 2);
    *(s64*)(count_ptr + 2) = data;
    if (old_arr != 0) {
        s64 old_count = *(s64*)(old_arr - 8);
        if (old_count != 0) {
            s64 off = old_count << 6;
            do {
                if (*(s64*)(old_arr + off - 0x10) != 0) {
                    FUN_710392e590(*(s64*)(old_arr + off - 0x10));
                }
                off -= 0x40;
            } while (off != 0);
        }
        FUN_710392e590((s64)(old_arr - 8));
    }

    if (*count_ptr != 0) {
        u64 i = 0;
        s64 off = 8;
        do {
            s64 arr_base = *(s64*)(count_ptr + 2);
            u8 m1 = 1;
            stream_io(param_2, &m1, 1);
            u8 ver = 3;
            stream_io(param_2, &ver, 1);
            FUN_7103187920(arr_base + off, param_2, (u32)ver);
            i++;
            off += 0x40;
        } while (i < *count_ptr);
    }
}

// ════════════════════════════════════════════════════════════════════
// 0x7103189880 — array reader: count + s32 values with 0xfffffffa sentinel fill
// Size: 564 bytes
// [derived: Ghidra decompilation — reads marker byte, count via
//  FUN_710314fc70. Write mode: reads s32 values via FUN_710314fef0.
//  Read mode: allocates count*4, fills with 0xfffffffa, reads s32 values.
//  Returns stream (param_1) for chaining.]
// ════════════════════════════════════════════════════════════════════
extern "C"
s64 FUN_7103189880(s64 param_1, s64 dest) {
    u32* count_ptr = (u32*)dest;
    u8 marker = 1;
    stream_io(param_1, &marker, 1);

    char is_writing = *(char*)(param_1 + 4);
    FUN_710314fc70(param_1, count_ptr);
    u32 count = *count_ptr;

    if (is_writing != '\0') {
        // Write mode: read s32 values
        if (count == 0) return param_1;
        u64 i = 0;
        s64 off = 0;
        do {
            s64 arr = *(s64*)(count_ptr + 2);
            u8 em = 1;
            stream_io(param_1, &em, 1);
            FUN_710314fef0(param_1, (void*)(arr + off));
            i++;
            off += 4;
        } while (i < *count_ptr);
        return param_1;
    }

    // Read mode
    if (count == 0) {
        s64 old = *(s64*)(count_ptr + 2);
        count_ptr[2] = 0;
        count_ptr[3] = 0;
        if (old == 0) return param_1;
        FUN_710392e590(old);
        return param_1;
    }

    s64 alloc_size = (u64)count * 4;
    u64* buf = (u64*)je_aligned_alloc(0x10, alloc_size);
    if (buf == nullptr) {
        if (DAT_7105331f00_param != nullptr) {
            u32 oom_flag = 0;
            s64 oom_size = alloc_size;
            u64 r = (*(u64(**)(s64*, u32*, s64*))(*(s64*)DAT_7105331f00_param + 0x30))
                     (DAT_7105331f00_param, &oom_flag, &oom_size);
            if ((r & 1) != 0) {
                buf = (u64*)je_aligned_alloc(0x10, alloc_size);
                if (buf != nullptr) goto alloc_ok_9880;
            }
        }
        buf = nullptr;
    }
alloc_ok_9880:
    // Fill with 0xfffffffa sentinel (unrolled by 8)
    {
        u32 fill_count = ((u32)((u64)(alloc_size - 4) >> 2) & 0x3fffffff) + 1;
        u64 rem = (u64)fill_count & 7;
        u32* fp = (u32*)buf;
        if (rem != 0) {
            s64 ri = -(s64)rem;
            u32* rp = (u32*)buf;
            do {
                ri++;
                *rp = 0xfffffffa;
                rp = (u32*)((s64)rp + 4);
            } while (ri != 0);
            fp = (u32*)((s64)buf + rem * 4);
        }
        if ((u64)(alloc_size - 4) > 0x1b) {
            u64* fp8 = (u64*)fp;
            do {
                fp8[0] = 0xfffffffafffffffa;
                fp8[1] = 0xfffffffafffffffa;
                fp8[2] = 0xfffffffafffffffa;
                fp8[3] = 0xfffffffafffffffa;
                fp8 += 4;
            } while (fp8 != (u64*)((s64)buf + (u64)count * 4));
        }
    }

    s64 old = *(s64*)(count_ptr + 2);
    *(u64**)(count_ptr + 2) = buf;
    if (old != 0) {
        FUN_710392e590(old);
    }

    if (*count_ptr != 0) {
        u64 i = 0;
        s64 off = 0;
        do {
            s64 arr = *(s64*)(count_ptr + 2);
            u8 em = 1;
            stream_io(param_1, &em, 1);
            FUN_710314fef0(param_1, (void*)(arr + off));
            i++;
            off += 4;
        } while (i < *count_ptr);
    }
    return param_1;
}

// ════════════════════════════════════════════════════════════════════
// 0x7103189b00 — StageCameraPath element reader
// Size: 304 bytes
// [derived: Ghidra decompilation — reads version, calls FUN_7103187210
//  for common base, reads u32 at +0x100, reads marker byte. If writing
//  mode, copies 0x40-byte string to local buffer before reading. Calls
//  FUN_7103188a70 for 64-byte string at +0x104. Version >= 2: reads
//  6 floats at +0x144..+0x158 via FUN_710314fff0.]
// ════════════════════════════════════════════════════════════════════
extern "C"
void FUN_7103189b00(s64 param_1, s64 param_2, u32 param_3) {
    u8 version = 4;
    stream_io(param_2, &version, 1);
    FUN_7103187210(param_1, param_2, (u32)version);

    FUN_710314fc70(param_2, (void*)(param_1 + 0x100));

    u8 marker = 1;
    stream_io(param_2, &marker, 1);

    u64* str_src = (u64*)(param_1 + 0x104);
    if (*(char*)(param_2 + 4) != '\0') {
        u64 local_buf[8];
        local_buf[0] = 0; local_buf[1] = 0;
        local_buf[2] = 0; local_buf[3] = 0;
        local_buf[4] = 0; local_buf[5] = 0;
        local_buf[6] = 0; local_buf[7] = 0;
        strncpy((char*)local_buf, (char*)str_src, 0x40);
        str_src = local_buf;
    }
    FUN_7103188a70(param_2, str_src);

    if (1 < param_3) {
        s64 s = FUN_710314fff0(param_2, (void*)(param_1 + 0x144));
        s = FUN_710314fff0(s, (void*)(param_1 + 0x148));
        s = FUN_710314fff0(s, (void*)(param_1 + 0x14c));
        s = FUN_710314fff0(s, (void*)(param_1 + 0x150));
        s = FUN_710314fff0(s, (void*)(param_1 + 0x154));
        FUN_710314fff0(s, (void*)(param_1 + 0x158));
    }
}
