#include "types.h"

// pool-b: HARD tier — LinkModule/PhysicsModule internal implementations
// These are implementation methods, not lua_bind dispatchers.

// External functions
extern "C" void FUN_71015b50b0(u64, u64, u64, u32);

// Singleton: lib::Singleton<app::ItemParamAccessor>::instance_
extern u8* lib_Singleton_ItemParamAccessor_instance_;

// ---------------------------------------------------------------------------
// 0x7100479590  96B  InitDamage — check link entry damage flag via vtable
// ---------------------------------------------------------------------------
bool InitDamage_479590(void* self, u32 index) {
    void** vt = *reinterpret_cast<void***>(self);
    if (!reinterpret_cast<bool(*)(void*)>(vt[0x70 / 8])(self))
        return false;
    // Reload vtable after call (NX Clang doesn't CSE this)
    vt = *reinterpret_cast<void***>(self);
    u8* entry = static_cast<u8*>(
        reinterpret_cast<void*(*)(void*, u32)>(vt[0x68 / 8])(self, index));
    return entry[0x30] != 0;
}

// ---------------------------------------------------------------------------
// 0x7100472bc0  112B  GetHaveItemSize — conditional tail call to FUN_71015b50b0
// ---------------------------------------------------------------------------
void GetHaveItemSize_472bc0(void* self, u64 p2, u64 p3, int index) {
    void** vt = *reinterpret_cast<void***>(self);
    if (!reinterpret_cast<bool(*)(void*, int)>(vt[0xc8 / 8])(self, index))
        return;
    u8* entries = *reinterpret_cast<u8**>(reinterpret_cast<u8*>(self) + 0x18);
    u64 val = *reinterpret_cast<u64*>(entries + (s64)index * 0x20 + 0x8);
    FUN_71015b50b0(val, p2, p3, 0);
}

// ---------------------------------------------------------------------------
// 0x7100471b30  176B  HaveItemInstance — ItemParamAccessor singleton lookup
// ---------------------------------------------------------------------------
u32 HaveItemInstance_471b30(void* self, int index) {
    void** vt = *reinterpret_cast<void***>(self);
    if (!reinterpret_cast<bool(*)(void*)>(vt[0xc8 / 8])(self))
        return 0;
    u8* entries = *reinterpret_cast<u8**>(reinterpret_cast<u8*>(self) + 0x18);
    u8* entry_data = *reinterpret_cast<u8**>(entries + (s64)index * 0x20 + 0x8);
    s32 param_idx = *reinterpret_cast<s32*>(entry_data + 0xc);
    u8* instance = *reinterpret_cast<u8**>(&lib_Singleton_ItemParamAccessor_instance_);
    return *reinterpret_cast<u32*>(instance + (s64)param_idx * 0xac + 0x4781c);
}

// ---------------------------------------------------------------------------
// 0x7100474330  248B  EjectAttach — iterate ring buffer, vtable call on matches
// ---------------------------------------------------------------------------
void EjectAttach_474330(void* self, int target_id, u32 p3, u32 p4) {
    u8* self_bytes = reinterpret_cast<u8*>(self);
    u8* rb = *reinterpret_cast<u8**>(self_bytes + 0x28);
    s32 count = static_cast<s32>(*reinterpret_cast<u64*>(rb + 0x10));
    int index = count - 1;
    if (count <= 0) return;

    s64 counter = static_cast<s64>(count);
    u32 b3 = p3 & 1;
    u32 b4 = p4 & 1;

    do {
        u64 base_idx = *reinterpret_cast<u64*>(rb + 0x18);
        u8* data = *reinterpret_cast<u8**>(rb + 0x28);
        u64 capacity = *reinterpret_cast<u64*>(rb + 0x8);
        u64 pos = static_cast<u64>(counter) + base_idx - 1;
        u64 mod = pos % capacity;
        s32 entry_id = *reinterpret_cast<s32*>(data + mod * 0x20);

        if (entry_id == target_id) {
            void** vt = *reinterpret_cast<void***>(self);
            reinterpret_cast<void(*)(void*, int, u32, u32, int)>(vt[0x248 / 8])(
                self, index, b3, b4, 0);
        }

        if (counter < 2) break;
        rb = *reinterpret_cast<u8**>(self_bytes + 0x28);
        counter--;
        index--;
    } while (true);
}

// ---------------------------------------------------------------------------
// 0x71004a0a90  288B  FUN_71004a0a90 — sub-module vtable dispatch with tail call
// ---------------------------------------------------------------------------
u32 FUN_71004a0a90(void* self, u64 param2, bool param3) {
    u8* sub1 = *reinterpret_cast<u8**>(reinterpret_cast<u8*>(self) + 0x10);
    void* sub2 = *reinterpret_cast<void**>(sub1 + 0x8);
    void** sub2_vt = *reinterpret_cast<void***>(sub2);
    u32 result = reinterpret_cast<u32(*)(void*, u64)>(sub2_vt[0x20 / 8])(
        sub2, param2 & 0xFFFFFFFFFFULL);
    if (result == 0xFFFFFFFF) return 0;
    if (param3) return result;
    void** self_vt = *reinterpret_cast<void***>(self);
    return reinterpret_cast<u32(*)(void*, u32)>(self_vt[0x650 / 8])(self, result);
}

// ---------------------------------------------------------------------------
// 0x71004a0fd0  288B  SetKeepPoseChangeMotion — phase accumulation + dispatch
// ---------------------------------------------------------------------------
void SetKeepPoseChangeMotion_4a0fd0(float rate, void* self) {
    u8* s = reinterpret_cast<u8*>(self);
    u8 flag1 = s[0x250];
    if (!flag1 && !s[0x252]) return;

    float speed = *reinterpret_cast<f32*>(s + 0x22c) * rate
                * *reinterpret_cast<f32*>(s + 0x204)
                * *reinterpret_cast<f32*>(s + 0x208);
    float current = *reinterpret_cast<f32*>(s + 0x224);

    if (speed > 0.0f) {
        current = speed + current;
        f32 limit = *reinterpret_cast<f32*>(s + 0x228);
        *reinterpret_cast<f32*>(s + 0x224) = current;
#ifdef MATCHING_HACK_NX_CLANG
        asm("");
#endif
        if (current >= limit) {
            current -= limit;
            *reinterpret_cast<f32*>(s + 0x224) = current;
        }
    }

    int int_val = static_cast<int>(current);
    f32 quantized = static_cast<f32>(int_val);
    u8 snap_flag = s[0x257];
    f32 result = snap_flag ? quantized : current;

    if (flag1) {
        u8* container = *reinterpret_cast<u8**>(s + 0x18);
        u8** begin = *reinterpret_cast<u8***>(container + 0x88);
        u8** end = *reinterpret_cast<u8***>(container + 0x90);
        while (begin != end) {
            u8* obj = *begin;
            if (obj[0x88]) {
                void* sub = *reinterpret_cast<void**>(obj + 0x70);
                void** svt = *reinterpret_cast<void***>(sub);
                reinterpret_cast<void(*)(void*, f32, int)>(svt[0x40 / 8])(sub, result, 0);
            }
            begin++;
        }
    }

    if (!s[0x252]) return;
    u8* container2 = *reinterpret_cast<u8**>(s + 0x20);
    u8** begin2 = *reinterpret_cast<u8***>(container2 + 0x88);
    u8** end2 = *reinterpret_cast<u8***>(container2 + 0x90);
    while (begin2 != end2) {
        u8* obj = *begin2;
        if (obj[0x88]) {
            void* sub = *reinterpret_cast<void**>(obj + 0x78);
            void** svt = *reinterpret_cast<void***>(sub);
            reinterpret_cast<void(*)(void*, f32, int)>(svt[0x40 / 8])(sub, result, 0);
        }
        begin2++;
    }
}

// ---------------------------------------------------------------------------
// 0x71004794f0  80B  SetAbsoluteLr — link entry set absolute lr flag
// ---------------------------------------------------------------------------
void SetAbsoluteLr_4794f0(void* self, u32 index) {
    void** vt = *reinterpret_cast<void***>(self);
    if (!reinterpret_cast<bool(*)(void*)>(vt[0x70 / 8])(self))
        return;
    vt = *reinterpret_cast<void***>(self);
    u8* entry = static_cast<u8*>(
        reinterpret_cast<void*(*)(void*, u32)>(vt[0x60 / 8])(self, index));
    entry[0x30] = 1;
}

// ---------------------------------------------------------------------------
// 0x7100479540  80B  Sleep — link entry clear active flag
// ---------------------------------------------------------------------------
void Sleep_479540(void* self, u32 index) {
    void** vt = *reinterpret_cast<void***>(self);
    if (!reinterpret_cast<bool(*)(void*)>(vt[0x70 / 8])(self))
        return;
    vt = *reinterpret_cast<void***>(self);
    u8* entry = static_cast<u8*>(
        reinterpret_cast<void*(*)(void*, u32)>(vt[0x60 / 8])(self, index));
    entry[0x30] = 0;
}

// ---------------------------------------------------------------------------
// 0x71004795f0  80B  EnableEnergy — link entry set energy flag
// ---------------------------------------------------------------------------
void EnableEnergy_4795f0(void* self, u32 index) {
    void** vt = *reinterpret_cast<void***>(self);
    if (!reinterpret_cast<bool(*)(void*)>(vt[0x70 / 8])(self))
        return;
    vt = *reinterpret_cast<void***>(self);
    u8* entry = static_cast<u8*>(
        reinterpret_cast<void*(*)(void*, u32)>(vt[0x60 / 8])(self, index));
    entry[0x31] = 1;
}

// ---------------------------------------------------------------------------
// 0x7100479640  80B  DisableEnergy — link entry clear energy flag
// ---------------------------------------------------------------------------
void DisableEnergy_479640(void* self, u32 index) {
    void** vt = *reinterpret_cast<void***>(self);
    if (!reinterpret_cast<bool(*)(void*)>(vt[0x70 / 8])(self))
        return;
    vt = *reinterpret_cast<void***>(self);
    u8* entry = static_cast<u8*>(
        reinterpret_cast<void*(*)(void*, u32)>(vt[0x60 / 8])(self, index));
    entry[0x31] = 0;
}

// ---------------------------------------------------------------------------
// 0x7100479690  192B  GetWaterTaskId — check link entry energy flag
// ---------------------------------------------------------------------------
bool GetWaterTaskId_479690(void* self, u32 index) {
    void** vt = *reinterpret_cast<void***>(self);
    if (!reinterpret_cast<bool(*)(void*)>(vt[0x70 / 8])(self))
        return false;
    vt = *reinterpret_cast<void***>(self);
    u8* entry = static_cast<u8*>(
        reinterpret_cast<void*(*)(void*, u32)>(vt[0x68 / 8])(self, index));
    return entry[0x31] != 0;
}

// ---------------------------------------------------------------------------
// 0x710049d9c0  48B  TransTraEndFrame — check motion transition end flag
// ---------------------------------------------------------------------------
bool TransTraEndFrame_49d9c0(void* self) {
    void** vt = *reinterpret_cast<void***>(self);
    u8* result = static_cast<u8*>(
        reinterpret_cast<void*(*)(void*)>(vt[0x680 / 8])(self));
    return result[0x13] != 0;
}

// ---------------------------------------------------------------------------
// 0x710049e370  48B  IsFlagLink — check link flag bit in motion state
// ---------------------------------------------------------------------------
u8 IsFlagLink_49e370(void* self) {
    void** vt = *reinterpret_cast<void***>(self);
    u8* result = static_cast<u8*>(
        reinterpret_cast<void*(*)(void*)>(vt[0x680 / 8])(self));
    return (result[0x10] >> 3) & 1;
}

// ---------------------------------------------------------------------------
// 0x710049f570  72B  IsEnd2nd — check if 2nd physics sim has ended
// ---------------------------------------------------------------------------
u32 IsEnd2nd_49f570(void* self) {
    u8* s = reinterpret_cast<u8*>(self);
    void* posture = *reinterpret_cast<void**>(*reinterpret_cast<u8**>(s + 0x10) + 0x38);
    void** pvt = *reinterpret_cast<void***>(posture);
    void* sub = reinterpret_cast<void*(*)(void*, int)>(pvt[0x10 / 8])(posture, 0);
    void** svt = *reinterpret_cast<void***>(sub);
    u32 result = reinterpret_cast<u32(*)(void*)>(svt[0x78 / 8])(sub);
    return ~result & 1;
}

