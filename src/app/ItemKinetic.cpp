#include "types.h"

// Item Kinetic Energy sub-object accessors
// All operate on an item-like base pointer, accessing the KineticModule
// via *(item-8)+0x1a0 → +0x68 (KineticModule*), then vtable dispatch.
//
// Pattern A (48B): get_sub(index) → read/write field on sub-object directly
// Pattern B (60B getter): get_sub(index) → vt[4](sub) → read f32 from data ptr
// Pattern C (60B setter): get_sub(index) → write f32 to sub-object field

#define VT(p) (*reinterpret_cast<void***>(p))

// Helper: get KineticModule from item base
#define KM(item) \
    (*reinterpret_cast<void**>( \
        *reinterpret_cast<u8**>( \
            *reinterpret_cast<u8**>(reinterpret_cast<u8*>(item) - 8) + 0x1a0) + 0x68))

// get_sub: KineticModule vtable[0x60/8](km, index)
#define KM_GET_SUB(item, idx) \
    reinterpret_cast<void*(*)(void*, int)>(VT(KM(item))[0x60/8])(KM(item), idx)

// get_data: sub vtable[0x20/8](sub) — returns data pointer for getters
#define KM_GET_DATA(sub) \
    reinterpret_cast<u8*>(reinterpret_cast<void*(*)(void*)>(VT(sub)[0x20/8])(sub))

// ============================================================
// Pattern A: 48-byte functions — single vtable call, direct field access
// ============================================================

// 71015d0730 — suspend: get_sub(5)->field_0x31 = 1
void suspend_71015d0730(void* item) {
    u8* sub = reinterpret_cast<u8*>(KM_GET_SUB(item, 5));
    sub[0x31] = 1;
}

// 71015d0770 — resume: get_sub(5)->field_0x31 = 0
void resume_71015d0770(void* item) {
    u8* sub = reinterpret_cast<u8*>(KM_GET_SUB(item, 5));
    sub[0x31] = 0;
}

// 71015d0a00 — is_enable: get_sub(7)->field_0x30
u8 is_enable_71015d0a00(void* item) {
    u8* sub = reinterpret_cast<u8*>(KM_GET_SUB(item, 7));
    return sub[0x30];
}

// 71015d0ef0 — is_enable: get_sub(13)->field_0x30
u8 is_enable_71015d0ef0(void* item) {
    u8* sub = reinterpret_cast<u8*>(KM_GET_SUB(item, 13));
    return sub[0x30];
}

// 71015d10a0 — get_rotation_z: get_sub(0)->field_0x28 (f32)
f32 get_rotation_z_71015d10a0(void* item) {
    u8* sub = reinterpret_cast<u8*>(KM_GET_SUB(item, 0));
    return *reinterpret_cast<f32*>(sub + 0x28);
}

// 71015d1140 — get_rotation: get_sub(5) → return ptr to +0x20
void* get_rotation_71015d1140(void* item) {
    u8* sub = reinterpret_cast<u8*>(KM_GET_SUB(item, 5));
    return sub + 0x20;
}

// 71015d1230 — get_brake: get_sub(4) → return ptr to +0x60
void* get_brake_71015d1230(void* item) {
    u8* sub = reinterpret_cast<u8*>(KM_GET_SUB(item, 4));
    return sub + 0x60;
}

// 71015d16f0 — get_accel: get_sub(1) → return ptr to +0x40
void* get_accel_71015d16f0(void* item) {
    u8* sub = reinterpret_cast<u8*>(KM_GET_SUB(item, 1));
    return sub + 0x40;
}

// 71015d1720 — get_limit_speed: get_sub(1) → return ptr to +0x70
void* get_limit_speed_71015d1720(void* item) {
    u8* sub = reinterpret_cast<u8*>(KM_GET_SUB(item, 1));
    return sub + 0x70;
}

// 71015d1ac0 — get_speed_1f: get_sub(2)->field_0x14 (f32)
f32 get_speed_1f_71015d1ac0(void* item) {
    u8* sub = reinterpret_cast<u8*>(KM_GET_SUB(item, 2));
    return *reinterpret_cast<f32*>(sub + 0x14);
}

// 71015d1af0 — get_accel: get_sub(2)->field_0x34 (f32)
f32 get_accel_71015d1af0(void* item) {
    u8* sub = reinterpret_cast<u8*>(KM_GET_SUB(item, 2));
    return *reinterpret_cast<f32*>(sub + 0x34);
}

// 71015d1b20 — get_limit_speed: get_sub(2)->field_0x40 (f32)
f32 get_limit_speed_71015d1b20(void* item) {
    u8* sub = reinterpret_cast<u8*>(KM_GET_SUB(item, 2));
    return *reinterpret_cast<f32*>(sub + 0x40);
}

// 71015d1e10 — is_sleep_speed: get_sub(12)->field_0xb8 (u8)
u8 is_sleep_speed_71015d1e10(void* item) {
    u8* sub = reinterpret_cast<u8*>(KM_GET_SUB(item, 12));
    return sub[0xb8];
}

// 71015d2090 — get_speed_length: get_sub(13)->field_0xa0 (f32)
f32 get_speed_length_71015d2090(void* item) {
    u8* sub = reinterpret_cast<u8*>(KM_GET_SUB(item, 13));
    return *reinterpret_cast<f32*>(sub + 0xa0);
}

// 71015d20c0 — get_speed_angle: get_sub(13)->field_0xa4 (f32)
f32 get_speed_angle_71015d20c0(void* item) {
    u8* sub = reinterpret_cast<u8*>(KM_GET_SUB(item, 13));
    return *reinterpret_cast<f32*>(sub + 0xa4);
}

// 71015d2130 — is_sleep_speed: get_sub(13)->field_0xb8 (u8)
u8 is_sleep_speed_71015d2130(void* item) {
    u8* sub = reinterpret_cast<u8*>(KM_GET_SUB(item, 13));
    return sub[0xb8];
}

// ============================================================
// Pattern B: 60-byte getter — get_sub(index) → vt[4](sub) → ldr s0
// These call a second vtable method on the sub-object to get a data ptr
// ============================================================

// 71015d0280 — get_speed_y: sub(2) → data → +0x4
f32 get_speed_y_71015d0280(void* item) {
    void* sub = KM_GET_SUB(item, 2);
    u8* data = KM_GET_DATA(sub);
    return *reinterpret_cast<f32*>(data + 0x4);
}

// 71015d03b0 — get_speed_y: sub(3) → data → +0x4
f32 get_speed_y_71015d03b0(void* item) {
    void* sub = KM_GET_SUB(item, 3);
    u8* data = KM_GET_DATA(sub);
    return *reinterpret_cast<f32*>(data + 0x4);
}

// 71015d0470 — get_speed_x: sub(4) → data → +0x0
f32 get_speed_x_71015d0470(void* item) {
    void* sub = KM_GET_SUB(item, 4);
    u8* data = KM_GET_DATA(sub);
    return *reinterpret_cast<f32*>(data);
}

// 71015d04b0 — get_speed_y: sub(4) → data → +0x4
f32 get_speed_y_71015d04b0(void* item) {
    void* sub = KM_GET_SUB(item, 4);
    u8* data = KM_GET_DATA(sub);
    return *reinterpret_cast<f32*>(data + 0x4);
}

// 71015d07f0 — get_speed_x: sub(6) → data → +0x0
f32 get_speed_x_71015d07f0(void* item) {
    void* sub = KM_GET_SUB(item, 6);
    u8* data = KM_GET_DATA(sub);
    return *reinterpret_cast<f32*>(data);
}

// 71015d0830 — get_speed_y: sub(6) → data → +0x4
f32 get_speed_y_71015d0830(void* item) {
    void* sub = KM_GET_SUB(item, 6);
    u8* data = KM_GET_DATA(sub);
    return *reinterpret_cast<f32*>(data + 0x4);
}

// 71015d0900 — get_speed_x: sub(7) → data → +0x0
f32 get_speed_x_71015d0900(void* item) {
    void* sub = KM_GET_SUB(item, 7);
    u8* data = KM_GET_DATA(sub);
    return *reinterpret_cast<f32*>(data);
}

// 71015d0a30 — get_speed_x: sub(9) → data → +0x0
f32 get_speed_x_71015d0a30(void* item) {
    void* sub = KM_GET_SUB(item, 9);
    u8* data = KM_GET_DATA(sub);
    return *reinterpret_cast<f32*>(data);
}

// 71015d0b30 — get_speed_x: sub(10) → data → +0x0
f32 get_speed_x_71015d0b30(void* item) {
    void* sub = KM_GET_SUB(item, 10);
    u8* data = KM_GET_DATA(sub);
    return *reinterpret_cast<f32*>(data);
}

// 71015d0be0 — get_speed_x: sub(8) → data → +0x0
f32 get_speed_x_71015d0be0(void* item) {
    void* sub = KM_GET_SUB(item, 8);
    u8* data = KM_GET_DATA(sub);
    return *reinterpret_cast<f32*>(data);
}

// 71015d0cc0 — get_speed_x: sub(12) → data → +0x0
f32 get_speed_x_71015d0cc0(void* item) {
    void* sub = KM_GET_SUB(item, 12);
    u8* data = KM_GET_DATA(sub);
    return *reinterpret_cast<f32*>(data);
}

// 71015d0d00 — get_speed_y: sub(12) → data → +0x4
f32 get_speed_y_71015d0d00(void* item) {
    void* sub = KM_GET_SUB(item, 12);
    u8* data = KM_GET_DATA(sub);
    return *reinterpret_cast<f32*>(data + 0x4);
}

// 71015d0e00 — get_speed_x: sub(13) → data → +0x0
f32 get_speed_x_71015d0e00(void* item) {
    void* sub = KM_GET_SUB(item, 13);
    u8* data = KM_GET_DATA(sub);
    return *reinterpret_cast<f32*>(data);
}

// 71015d0e40 — get_speed_y: sub(13) → data → +0x4
f32 get_speed_y_71015d0e40(void* item) {
    void* sub = KM_GET_SUB(item, 13);
    u8* data = KM_GET_DATA(sub);
    return *reinterpret_cast<f32*>(data + 0x4);
}

// ============================================================
// Pattern C: 60-byte setter — get_sub(index) → str s8 directly
// These save the float arg in d8 across the vtable call
// ============================================================

// 71015d1ba0 — set_accel: sub(2)->field_0x34 = val
void set_accel_71015d1ba0(void* item, f32 val) {
    u8* sub = reinterpret_cast<u8*>(KM_GET_SUB(item, 2));
    *reinterpret_cast<f32*>(sub + 0x34) = val;
}

// 71015d1be0 — set_stable_speed: sub(2)->field_0x38 = val
void set_stable_speed_71015d1be0(void* item, f32 val) {
    u8* sub = reinterpret_cast<u8*>(KM_GET_SUB(item, 2));
    *reinterpret_cast<f32*>(sub + 0x38) = val;
}

// 71015d1c20 — set_brake: sub(2)->field_0x3c = val
void set_brake_71015d1c20(void* item, f32 val) {
    u8* sub = reinterpret_cast<u8*>(KM_GET_SUB(item, 2));
    *reinterpret_cast<f32*>(sub + 0x3c) = val;
}

// 71015d1c60 — set_limit_speed: sub(2)->field_0x40 = val
void set_limit_speed_71015d1c60(void* item, f32 val) {
    u8* sub = reinterpret_cast<u8*>(KM_GET_SUB(item, 2));
    *reinterpret_cast<f32*>(sub + 0x40) = val;
}

// 71015d1d90 — set_speed_angle: sub(12)->field_0xa4 = val
void set_speed_angle_71015d1d90(void* item, f32 val) {
    u8* sub = reinterpret_cast<u8*>(KM_GET_SUB(item, 12));
    *reinterpret_cast<f32*>(sub + 0xa4) = val;
}

// 71015d1f50 — set_speed_length: sub(13)->field_0xa0 = val
void set_speed_length_71015d1f50(void* item, f32 val) {
    u8* sub = reinterpret_cast<u8*>(KM_GET_SUB(item, 13));
    *reinterpret_cast<f32*>(sub + 0xa0) = val;
}

// 71015d1f90 — set_speed_angle: sub(13)->field_0xa4 = val
void set_speed_angle_71015d1f90(void* item, f32 val) {
    u8* sub = reinterpret_cast<u8*>(KM_GET_SUB(item, 13));
    *reinterpret_cast<f32*>(sub + 0xa4) = val;
}

// 71015d1fd0 — set_speed_accel: sub(13)->field_0xa8 = val
void set_speed_accel_71015d1fd0(void* item, f32 val) {
    u8* sub = reinterpret_cast<u8*>(KM_GET_SUB(item, 13));
    *reinterpret_cast<f32*>(sub + 0xa8) = val;
}

// 71015d2010 — set_speed_length_min: sub(13)->field_0xac = val
void set_speed_length_min_71015d2010(void* item, f32 val) {
    u8* sub = reinterpret_cast<u8*>(KM_GET_SUB(item, 13));
    *reinterpret_cast<f32*>(sub + 0xac) = val;
}

// 71015d2050 — set_speed_length_max: sub(13)->field_0xb0 = val
void set_speed_length_max_71015d2050(void* item, f32 val) {
    u8* sub = reinterpret_cast<u8*>(KM_GET_SUB(item, 13));
    *reinterpret_cast<f32*>(sub + 0xb0) = val;
}

// 71015d2220 — set_speed_lr: sub(13)->field_0xb4 = val
void set_speed_lr_71015d2220(void* item, f32 val) {
    u8* sub = reinterpret_cast<u8*>(KM_GET_SUB(item, 13));
    *reinterpret_cast<f32*>(sub + 0xb4) = val;
}

// ============================================================
// Pattern A extra: 56-byte function — get_sub + clear multiple fields
// ============================================================

// 71015d1170 — clear_rot_speed: get_sub(5), zero 3 fields
void clear_rot_speed_71015d1170(void* item) {
    u8* sub = reinterpret_cast<u8*>(KM_GET_SUB(item, 5));
    *reinterpret_cast<f32*>(sub + 0x20) = 0.0f;
    *reinterpret_cast<f32*>(sub + 0x24) = 0.0f;
    *reinterpret_cast<f32*>(sub + 0x28) = 0.0f;
}
