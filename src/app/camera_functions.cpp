#include "types.h"

// ---- ~CameraQuake destructor ----
// 0x7100515190 (3,192 bytes)
// Releases 26 shared_ptr control blocks, 13 mutex-guarded effect handles, 13 simple effect handles.

#define HIDDEN __attribute__((visibility("hidden")))

// std::__1::__shared_weak_count — enough to generate correct mangled BL
namespace std { namespace __1 {
    class __shared_weak_count {
        long __shared_owners_;
        long __shared_weak_owners_;
    public:
        void __release_weak() noexcept;
        virtual ~__shared_weak_count();
    };
}}

// Singletons
extern "C" void* DAT_7105331f20 HIDDEN;  // [derived: FilesystemInfo* / EffectManager-like singleton]

// External functions
extern "C" void FUN_710353eff0(void*, void*);  // release loaded directory entry (mutex-guarded)
extern "C" void FUN_7103540560(void*, u32);      // release filepath entry (takes mgr + handle)

// Mutex PLT stubs
extern "C" void lock_71039c1490(void*);    // std::__1::recursive_mutex::lock()
extern "C" void unlock_71039c14a0(void*);  // std::__1::recursive_mutex::unlock()

// Shared ptr control block release — inlined pattern for matching.
// Ghidra shows: atomic fetch_sub refcount, if last ref call vtable[2] + __release_weak
#define RELEASE_SHARED_PTR(base, offset)                                          \
    do {                                                                          \
        long* ctrl = *(long**)((char*)(base) + (offset));                         \
        if (ctrl != nullptr) {                                                    \
            long old = __atomic_fetch_sub(ctrl + 1, 1, __ATOMIC_ACQ_REL);         \
            if (old == 0) {                                                       \
                ((void(*)(long*))((long*)*ctrl)[2])(ctrl);                        \
                reinterpret_cast<std::__1::__shared_weak_count*>(ctrl)->__release_weak(); \
            }                                                                     \
        }                                                                         \
    } while(0)

// Effect handle release with mutex guard — Ghidra pattern:
//   if handle != 0xffffff, check array bound, lock mutex, check valid bit, call release, unlock, set sentinel
#define RELEASE_EFFECT_HANDLE_MUTEX(base, offset)                                  \
    do {                                                                           \
        u32 handle = *(u32*)((char*)(base) + (offset));                            \
        if (handle != 0xffffff) {                                                  \
            void* mgr = DAT_7105331f20;                                            \
            if (handle < *(u32*)((char*)mgr + 0x48)) {                             \
                void* mutex_ptr = *(void**)mgr;                                    \
                lock_71039c1490(mutex_ptr);                                        \
                char* arr = *(char**)((char*)mgr + 0x40);                          \
                if ((*(u8*)(arr + (u64)handle * 0x48 + 8) & 1) != 0) {             \
                    FUN_710353eff0(mgr, arr + (u64)handle * 0x48);                 \
                }                                                                  \
                unlock_71039c14a0(mutex_ptr);                                      \
            }                                                                      \
            *(u32*)((char*)(base) + (offset)) = 0xffffff;                          \
        }                                                                          \
    } while(0)

// Simple effect handle release — Ghidra pattern:
//   if handle != 0xffffff, call FUN_7103540560, set sentinel
#define RELEASE_EFFECT_HANDLE_SIMPLE(base, offset)                                 \
    do {                                                                           \
        u32 handle = *(u32*)((char*)(base) + (offset));                            \
        if (handle != 0xffffff) {                                                  \
            void* mgr = DAT_7105331f20;                                            \
            FUN_7103540560(mgr, handle);                                           \
            *(u32*)((char*)(base) + (offset)) = 0xffffff;                          \
        }                                                                          \
    } while(0)

// 0x7100515190 — ~CameraQuake destructor (3,192 bytes)
// [derived: Ghidra decompilation at 0x7100515190]
// Releases shared_ptr control blocks at +0x5e8..+0x778 (step 0x10),
// mutex-guarded effect handles at +0x5ac..+0x5dc (step 4),
// simple effect handles at +0x578..+0x5a8 (step 4).
extern "C" void FUN_7100515190(long param_1)
{
    // Release 26 shared_ptr control blocks (reverse order: 0x778 down to 0x5e8)
    RELEASE_SHARED_PTR(param_1, 0x778);
    RELEASE_SHARED_PTR(param_1, 0x768);
    RELEASE_SHARED_PTR(param_1, 0x758);
    RELEASE_SHARED_PTR(param_1, 0x748);
    RELEASE_SHARED_PTR(param_1, 0x738);
    RELEASE_SHARED_PTR(param_1, 0x728);
    RELEASE_SHARED_PTR(param_1, 0x718);
    RELEASE_SHARED_PTR(param_1, 0x708);
    RELEASE_SHARED_PTR(param_1, 0x6f8);
    RELEASE_SHARED_PTR(param_1, 0x6e8);
    RELEASE_SHARED_PTR(param_1, 0x6d8);
    RELEASE_SHARED_PTR(param_1, 0x6c8);
    RELEASE_SHARED_PTR(param_1, 0x6b8);
    RELEASE_SHARED_PTR(param_1, 0x6a8);
    RELEASE_SHARED_PTR(param_1, 0x698);
    RELEASE_SHARED_PTR(param_1, 0x688);
    RELEASE_SHARED_PTR(param_1, 0x678);
    RELEASE_SHARED_PTR(param_1, 0x668);
    RELEASE_SHARED_PTR(param_1, 0x658);
    RELEASE_SHARED_PTR(param_1, 0x648);
    RELEASE_SHARED_PTR(param_1, 0x638);
    RELEASE_SHARED_PTR(param_1, 0x628);
    RELEASE_SHARED_PTR(param_1, 0x618);
    RELEASE_SHARED_PTR(param_1, 0x608);
    RELEASE_SHARED_PTR(param_1, 0x5f8);
    RELEASE_SHARED_PTR(param_1, 0x5e8);

    // Release 13 mutex-guarded effect handles (0x5dc down to 0x5ac, step 4)
    RELEASE_EFFECT_HANDLE_MUTEX(param_1, 0x5dc);
    RELEASE_EFFECT_HANDLE_MUTEX(param_1, 0x5d8);
    RELEASE_EFFECT_HANDLE_MUTEX(param_1, 0x5d4);
    RELEASE_EFFECT_HANDLE_MUTEX(param_1, 0x5d0);
    RELEASE_EFFECT_HANDLE_MUTEX(param_1, 0x5cc);
    RELEASE_EFFECT_HANDLE_MUTEX(param_1, 0x5c8);
    RELEASE_EFFECT_HANDLE_MUTEX(param_1, 0x5c4);
    RELEASE_EFFECT_HANDLE_MUTEX(param_1, 0x5c0);
    RELEASE_EFFECT_HANDLE_MUTEX(param_1, 0x5bc);
    RELEASE_EFFECT_HANDLE_MUTEX(param_1, 0x5b8);
    RELEASE_EFFECT_HANDLE_MUTEX(param_1, 0x5b4);
    RELEASE_EFFECT_HANDLE_MUTEX(param_1, 0x5b0);
    RELEASE_EFFECT_HANDLE_MUTEX(param_1, 0x5ac);

    // Release 13 simple effect handles (0x5a8 down to 0x578, step 4)
    RELEASE_EFFECT_HANDLE_SIMPLE(param_1, 0x5a8);
    RELEASE_EFFECT_HANDLE_SIMPLE(param_1, 0x5a4);
    RELEASE_EFFECT_HANDLE_SIMPLE(param_1, 0x5a0);
    RELEASE_EFFECT_HANDLE_SIMPLE(param_1, 0x59c);
    RELEASE_EFFECT_HANDLE_SIMPLE(param_1, 0x598);
    RELEASE_EFFECT_HANDLE_SIMPLE(param_1, 0x594);
    RELEASE_EFFECT_HANDLE_SIMPLE(param_1, 0x590);
    RELEASE_EFFECT_HANDLE_SIMPLE(param_1, 0x58c);
    RELEASE_EFFECT_HANDLE_SIMPLE(param_1, 0x588);
    RELEASE_EFFECT_HANDLE_SIMPLE(param_1, 0x584);
    RELEASE_EFFECT_HANDLE_SIMPLE(param_1, 0x580);
    RELEASE_EFFECT_HANDLE_SIMPLE(param_1, 0x57c);
    RELEASE_EFFECT_HANDLE_SIMPLE(param_1, 0x578);
}

// ---- Small camera/stage functions ----

// Singletons used by small functions
// DAT_71052b7f00 [derived: camera/stage parameter singleton]
extern "C" void* DAT_71052b7f00 HIDDEN;
// StageManager singleton
namespace lib { extern "C" void* Singleton_app_StageManager_instance_ asm("_ZN3lib9SingletonIN3app12StageManagerEE9instance_E") HIDDEN; }
#define SM_INSTANCE lib::Singleton_app_StageManager_instance_
// FighterManager singleton
namespace lib { extern "C" void* Singleton_app_FighterManager_instance_ asm("_ZN3lib9SingletonIN3app14FighterManagerEE9instance_E") HIDDEN; }
#define FM_INSTANCE lib::Singleton_app_FighterManager_instance_

// External functions
extern "C" void FUN_71005162f0(void*, u32, u64);
extern "C" void FUN_710392e590(void*);   // operator delete / free

// ---- Stage query leaf functions (tail-call through stage_info vtable) ----

// 0x71015ce640 (28 bytes) — app::stage::get_stage_id
// Leaf tail-call: reads stage_info at +0x128, calls vtable[0] (get_stage_kind)
// [derived: disasm shows ldr x8,[SM+0x128]; ldr x9,[x8]; ldr x9,[x9]; br x9]
namespace app::stage {
extern "C" s32 get_stage_id(void) {
    u8* inner = *(u8**)SM_INSTANCE;
    u8* stage_info = inner + 0x128;
    void** vt = *(void***)stage_info;
    return reinterpret_cast<s32(*)(void*)>(vt[0])(stage_info);
}
} // namespace app::stage

// 0x71015ce690 (28 bytes) — app::stage::get_stage_position_delta
// Leaf tail-call: calls stage_info vtable[3] (offset 0x18)
namespace app::stage {
extern "C" void get_stage_position_delta(void) {
    u8* inner = *(u8**)SM_INSTANCE;
    u8* stage_info = inner + 0x128;
    void** vt = *(void***)stage_info;
    reinterpret_cast<void(*)(void*)>(vt[0x18/8])(stage_info);
}
} // namespace app::stage

// 0x710227ece0 (28 bytes) — app::sv_information::is_stage_can_dead_back
// Leaf tail-call: calls stage_info vtable[0x188/8]
namespace app::sv_information {
extern "C" bool is_stage_can_dead_back(void) {
    u8* inner = *(u8**)SM_INSTANCE;
    u8* stage_info = inner + 0x128;
    void** vt = *(void***)stage_info;
    return reinterpret_cast<bool(*)(void*)>(vt[0x188/8])(stage_info);
}
} // namespace app::sv_information

// 0x710227eca0 (60 bytes) — app::sv_information::is_stage_can_dead_front
// Checks FighterManager +0xc0 byte == 0x20, returns 0 if so; else tail-calls stage_info vtable[0x180/8]
namespace app::sv_information {
extern "C" bool is_stage_can_dead_front(void) {
    if (*(u8*)(*(u8**)FM_INSTANCE + 0xc0) == 0x20) return false;
    u8* inner = *(u8**)SM_INSTANCE;
    u8* stage_info = inner + 0x128;
    void** vt = *(void***)stage_info;
    return reinterpret_cast<bool(*)(void*)>(vt[0x180/8])(stage_info);
}
} // namespace app::sv_information

// 0x71015cd4f0 (60 bytes) — app::fighter::is_final_status_or_stage_transition
// Checks FighterManager +0xbc > 0, or StageManager +0xbc != 0
namespace app::fighter {
extern "C" bool is_final_status_or_stage_transition(void) {
    if (*(s8*)(*(u8**)FM_INSTANCE + 0xbc) > 0) return true;
    return *(s32*)(*(u8**)SM_INSTANCE + 0xbc) != 0;
}
} // namespace app::fighter

// 0x7101647240 (80 bytes) — app::kozukatasight::is_large_stage
// Gets stage kind, returns true if kind == 0x29, 0xef, or 0xf8
namespace app::kozukatasight {
extern "C" bool is_large_stage(void) {
    u8* inner = *(u8**)SM_INSTANCE;
    u8* stage_info = inner + 0x128;
    void** vt = *(void***)stage_info;
    s32 kind = reinterpret_cast<s32(*)(void*)>(vt[0])(stage_info);
    if (kind == 0x29) return true;
    if (kind == 0xef) return true;
    if (kind == 0xf8) return true;
    return false;
}
} // namespace app::kozukatasight

// ---- Camera quake functions ----

// 0x71015c4670 (48 bytes) — app::item::stop_quake
// Clears quake entry and bitmask bit
// DAT_71052b7f00 +0x2dc: quake array (u32[]), +0x824: quake bitmask
namespace app::item {
extern "C" void stop_quake(u32 kind) {
    u8* base = *(u8**)DAT_71052b7f00;
    *(u32*)(base + (u64)kind * 4 + 0x2dc) = 0;
    *(u32*)(base + 0x824) &= ~(1u << ((kind - 1) & 0x1f));
}
} // namespace app::item

// 0x71015c4610 (84 bytes) — app::item::request_quake
// Gets posture position via vtable, dispatches to FUN_71005162f0
namespace app::item {
extern "C" void request_quake(u64 lua_state, u32 kind) {
    u8* base = *(u8**)DAT_71052b7f00;
    u8* battle_obj = *(u8**)(*(u8**)(lua_state - 8) + 0x1a0);
    void** posture = *(void***)(battle_obj + 0x38);
    u64 pos = reinterpret_cast<u64(*)(void**)>(((void**)*posture)[0x60/8])(posture);
    FUN_71005162f0(base + 0x2b0, kind, pos);
}
} // namespace app::item

// ---- ~StageEnd destructor ----
// 0x71028350b0 (112 bytes) — ~StageEnd
// Sets vtable, frees 3 fields, calls sub-dtors
extern "C" u8 PTR_LAB_71050e7a18;
extern "C" void FUN_7102837e00(void*);
extern "C" void FUN_7102834b90(void*);
extern "C" void FUN_71025e55a0(void*);

extern "C" void FUN_71028350b0(u64* param_1) {
    *param_1 = (u64)&PTR_LAB_71050e7a18;

    u64 p3 = param_1[0x123];
    param_1[0x123] = 0;
    if (p3 != 0) FUN_710392e590((void*)p3);

    u64 p2 = param_1[0x122];
    param_1[0x122] = 0;
    if (p2 != 0) FUN_710392e590((void*)p2);

    u64 p1 = param_1[0x121];
    param_1[0x121] = 0;
    if (p1 != 0) {
        FUN_7102837e00((void*)p1);
        FUN_710392e590((void*)p1);
    }

    FUN_7102834b90(param_1 + 0xef);
    FUN_71025e55a0(param_1);
}

// ---- Camera user operation functions ----

// 0x71015c4960 (68 bytes) — app::item::set_enabled_camera_user_operation
// Follows accessor chain from lua_state to camera sub-object, sets flag + increments counter
namespace app::item {
extern "C" void set_enabled_camera_user_operation(u64 lua_state) {
    u8* battle_obj = *(u8**)(*(u8**)(lua_state - 8) + 0x1a0);
    u8* cam = *(u8**)(*(u8**)(*(u8**)(battle_obj + 0x190) + 0x220) + 0x90);
    if (*(u8*)(cam + 0x168) != 0) return;
    *(u8*)(cam + 0x168) = 1;
    *(s32*)(*(u8**)DAT_71052b7f00 + 0xc9c) += 1;
}
} // namespace app::item

// 0x71015c49b0 (60 bytes) — app::item::set_disabled_camera_user_operation
namespace app::item {
extern "C" void set_disabled_camera_user_operation(u64 lua_state) {
    u8* battle_obj = *(u8**)(*(u8**)(lua_state - 8) + 0x1a0);
    u8* cam = *(u8**)(*(u8**)(*(u8**)(battle_obj + 0x190) + 0x220) + 0x90);
    if (*(u8*)(cam + 0x168) == 0) return;
    *(u8*)(cam + 0x168) = 0;
    *(s32*)(*(u8**)DAT_71052b7f00 + 0xc9c) -= 1;
}
} // namespace app::item

// ---- Additional simple stage/camera leaf functions ----

// 0x7101644600 (28 bytes) — app::devil::is_camera_mode_melee
// Checks if camera mode field == 1
namespace app::devil {
extern "C" bool is_camera_mode_melee(void) {
    return *(s32*)(*(u8**)DAT_71052b7f00 + 4) == 1;
}
} // namespace app::devil

// 0x7101642ac0 (28 bytes) — app::andross::get_stage_andross_position
// Tail-call: stage_info vtable[0x118/8]
namespace app::andross {
extern "C" void get_stage_andross_position(void) {
    u8* inner = *(u8**)SM_INSTANCE;
    u8* stage_info = inner + 0x128;
    void** vt = *(void***)stage_info;
    reinterpret_cast<void(*)(void*)>(vt[0x118/8])(stage_info);
}
} // namespace app::andross

// 0x7101648830 (28 bytes) — app::nightmare::get_stage_nightmare_position
// Tail-call: stage_info vtable[0x110/8]
namespace app::nightmare {
extern "C" void get_stage_nightmare_position(void) {
    u8* inner = *(u8**)SM_INSTANCE;
    u8* stage_info = inner + 0x128;
    void** vt = *(void***)stage_info;
    reinterpret_cast<void(*)(void*)>(vt[0x110/8])(stage_info);
}
} // namespace app::nightmare

// 0x7101648850 (28 bytes) — app::nightmare::get_stage_nightmare_scale
// Tail-call: stage_info vtable[0x108/8]
namespace app::nightmare {
extern "C" void get_stage_nightmare_scale(void) {
    u8* inner = *(u8**)SM_INSTANCE;
    u8* stage_info = inner + 0x128;
    void** vt = *(void***)stage_info;
    reinterpret_cast<void(*)(void*)>(vt[0x108/8])(stage_info);
}
} // namespace app::nightmare

// 0x71034a50a0 (60 bytes) — get_camera_clip_bounds
// Computes camera clip from parameters at DAT_71052b7f00
extern "C" float get_camera_clip_bounds(void) {
    u8* base = *(u8**)DAT_71052b7f00;
    float val = (float)*(u64*)(base + 0xd20);
    float a = *(float*)(base + 0xda8);
    float b = *(float*)(base + 0xdd8);
    float c = *(float*)(base + 0xdc8);
    return val - a * b * c;
}

// 0x7101644820 (52 bytes) — app::devil::get_stage_devil_position
// Tail-call: stage_info vtable[0x120/8]
namespace app::devil {
extern "C" void get_stage_devil_position(void) {
    u8* inner = *(u8**)SM_INSTANCE;
    u8* stage_info = inner + 0x128;
    void** vt = *(void***)stage_info;
    reinterpret_cast<void(*)(void*)>(vt[0x120/8])(stage_info);
}
} // namespace app::devil

// 0x7101653890 (52 bytes) — app::kiiladarzmanager::set_stage_floating_plates_visibility
// Conditional tail-call: stage_info vtable[0x228/8] with different args
namespace app::kiiladarzmanager {
extern "C" void set_stage_floating_plates_visibility(bool show, s32 param_2) {
    u8* inner = *(u8**)SM_INSTANCE;
    u8* stage_info = inner + 0x128;
    void** vt = *(void***)stage_info;
    if (show) {
        reinterpret_cast<void(*)(void*, s32)>(vt[0x228/8])(stage_info, 7);
    } else {
        reinterpret_cast<void(*)(void*, s32, s32)>(vt[0x228/8])(stage_info, 6, param_2);
    }
}
} // namespace app::kiiladarzmanager

// 0x710165cad0 (56 bytes) — app::dragoonset::get_stage_dragoon_camera_rectangle
// Tail-call: stage_info vtable[0x128/8]
namespace app::dragoonset {
extern "C" void get_stage_dragoon_camera_rectangle(void) {
    u8* inner = *(u8**)SM_INSTANCE;
    u8* stage_info = inner + 0x128;
    void** vt = *(void***)stage_info;
    reinterpret_cast<void(*)(void*)>(vt[0x128/8])(stage_info);
}
} // namespace app::dragoonset

// 0x71015c8d50 (44 bytes) — app::boss_private::set_stage_sh
// Gets module at +0x78 from battle object, calls vtable[0x330/8] with arg=1
namespace app::boss_private {
extern "C" void set_stage_sh(u64 lua_state) {
    u8* battle_obj = *(u8**)(*(u8**)(lua_state - 8) + 0x1a0);
    void** module = *(void***)(battle_obj + 0x78);
    reinterpret_cast<void(*)(void**, s32)>(((void**)*module)[0x330/8])(module, 1);
}
} // namespace app::boss_private

// ---- Boss energy wrapper functions ----

// Inner function for boss energy initialization
// [derived: called by all energy_from_param_* wrappers with different constant combos]
// Signature: 8 GPR args (x0-x7) + 1 FPR (s0) + 1 bool on stack
extern "C" void FUN_71015c7aa0(u64, u32, u64, s32, s32, s32, s32, s32, float, bool);

// 0x71015c8140 (56 bytes) — app::boss_private::main_energy_from_param_no_boss
// Wrapper: passes through lua_state/kind/hash/float, sets fixed int args
namespace app::boss_private {
extern "C" void main_energy_from_param_no_boss(u64 lua_state, u32 kind, u64 hash, float param_4) {
    FUN_71015c7aa0(lua_state, kind, hash, 0, 0, 0xc, 0, 0, param_4, true);
}
} // namespace app::boss_private

// 0x71015c8180 (56 bytes) — app::boss_private::sub1_energy_from_param_no_boss
namespace app::boss_private {
extern "C" void sub1_energy_from_param_no_boss(u64 lua_state, u32 kind, u64 hash, float param_4) {
    FUN_71015c7aa0(lua_state, kind, hash, 0, 0, 0xd, 0, 0, param_4, true);
}
} // namespace app::boss_private

// 0x71015c81c0 (60 bytes) — app::boss_private::main_energy_from_param_inherit_no_boss
// Inherit variant: s0=0.0f, w3=1 (inherit flag)
namespace app::boss_private {
extern "C" void main_energy_from_param_inherit_no_boss(u64 lua_state, u32 kind, u64 hash) {
    FUN_71015c7aa0(lua_state, kind, hash, 1, 0, 0xc, 0, 0, 0.0f, true);
}
} // namespace app::boss_private

// 0x71015c8200 (60 bytes) — app::boss_private::sub1_energy_from_param_inherit_no_boss
namespace app::boss_private {
extern "C" void sub1_energy_from_param_inherit_no_boss(u64 lua_state, u32 kind, u64 hash) {
    FUN_71015c7aa0(lua_state, kind, hash, 1, 0, 0xd, 0, 0, 0.0f, true);
}
} // namespace app::boss_private

// 0x71015c8240 (60 bytes) — app::boss_private::sub1_energy_from_param_inherit_all_no_boss
// Same as inherit but w4=1 (inherit_all flag)
namespace app::boss_private {
extern "C" void sub1_energy_from_param_inherit_all_no_boss(u64 lua_state, u32 kind, u64 hash) {
    FUN_71015c7aa0(lua_state, kind, hash, 1, 1, 0xd, 0, 0, 0.0f, true);
}
} // namespace app::boss_private

// ---- FighterParamAccessor2 camera param getters ----

// FighterParamAccessor2 singleton
// [derived: lib::Singleton<app::FighterParamAccessor2>::instance_, adrp 0x71052bb000+0x3b0]
extern "C" void* DAT_71052bb3b0 HIDDEN;

// 0x710166e190 (32 bytes) — app::pickelobject::camera_range_damag_mul_start_rate
// Leaf: reads float from FighterParamAccessor2 → [+0x13b0] → [+0x530]
namespace app::pickelobject {
extern "C" float camera_range_damag_mul_start_rate(void) {
    u8* sub = *(u8**)((u8*)DAT_71052bb3b0 + 0x13b0);
    return *(float*)(sub + 0x530);
}
} // namespace app::pickelobject

// 0x710166e1b0 (32 bytes) — app::pickelobject::camera_range_damag_mul_end_rate
namespace app::pickelobject {
extern "C" float camera_range_damag_mul_end_rate(void) {
    u8* sub = *(u8**)((u8*)DAT_71052bb3b0 + 0x13b0);
    return *(float*)(sub + 0x534);
}
} // namespace app::pickelobject

// 0x710166e1d0 (32 bytes) — app::pickelobject::camera_range_damag_mul_min
namespace app::pickelobject {
extern "C" float camera_range_damag_mul_min(void) {
    u8* sub = *(u8**)((u8*)DAT_71052bb3b0 + 0x13b0);
    return *(float*)(sub + 0x538);
}
} // namespace app::pickelobject

// 0x710166e1f0 (32 bytes) — app::pickelobject::camera_range_damag_mul_max
namespace app::pickelobject {
extern "C" float camera_range_damag_mul_max(void) {
    u8* sub = *(u8**)((u8*)DAT_71052bb3b0 + 0x13b0);
    return *(float*)(sub + 0x53c);
}
} // namespace app::pickelobject

// NEON vector return type — 4 floats packed in v0
typedef float float4 __attribute__((vector_size(16)));

// ---- Camera range center position ----

// 0x71016459d0 (72 bytes) — app::flyandhand::get_camera_range_center_pos
// Leaf: computes center of camera range rect at +0xc00..+0xc0c, returns float4
// DAT_71052b7f00 [derived: camera/stage parameter singleton]
// +0xc00 camera_range left, +0xc04 right, +0xc08 top, +0xc0c bottom
namespace app::flyandhand {
extern "C" float4 get_camera_range_center_pos(void) {
    u8* inner = *(u8**)DAT_71052b7f00;
    float left   = *(float*)(inner + 0xc00);
    float right  = *(float*)(inner + 0xc04);
    float top    = *(float*)(inner + 0xc08);
    float bottom = *(float*)(inner + 0xc0c);
    float cx = left + (right - left) * 0.5f;
    float cy = top + (bottom - top) * 0.5f;
    float4 r = {0};
    r[0] = cx;
    r[1] = cy;
    return r;
}
} // namespace app::flyandhand

// ---- Camera subject range ----

// 0x7101679010 (100 bytes) — app::kasey::get_camera_subject_range
// Calls camera module vtable[0x110/8] with arg=0, returns 4 floats from result pointer
// [derived: disasm shows ldr x0,[x0,#0x60]; vtable call [0x110]; load 4 floats from ret ptr]
namespace app::kasey {
extern "C" float4 get_camera_subject_range(void* accessor) {
    void** cam = *(void***)(reinterpret_cast<u8*>(accessor) + 0x60);
    float* result = reinterpret_cast<float*(*)(void**, s32)>(
        ((void**)*cam)[0x110/8])(cam, 0);
    float4 r;
    r[0] = result[0];
    r[1] = result[1];
    r[2] = result[2];
    r[3] = result[3];
    return r;
}
} // namespace app::kasey

// ---- Camera sleep ----

// 0x71015c4490 (104 bytes) — app::item::camera_sleep
// Gets battle object, checks camera module vtable[2] (is_camera_sleeping),
// if not sleeping, writes 1 to *(battle_obj + 0x1a8) + 0x7608
// [derived: disasm shows ldr x19,[x8,#0x1a0]; camera module at +0x60; vtable[0x10/8] check]
namespace app::item {
extern "C" void camera_sleep(u64 lua_state) {
    u8* battle_obj = *(u8**)(*(u8**)(lua_state - 8) + 0x1a0);
    void** cam = *(void***)(battle_obj + 0x60);
    u64 res = reinterpret_cast<u64(*)(void**)>(((void**)*cam)[0x10/8])(cam);
    if ((res & 1) == 0) {
        *(u32*)(*(u8**)(battle_obj + 0x1a8) + 0x7608) = 1;
    }
}
} // namespace app::item

// ---- Camera range (computed from params) ----

// 0x71015cb960 (114 bytes) — app::camera::get_camera_range
// Leaf: computes camera range from scale/aspect params and center position
// DAT_71052b7f00 [derived: camera/stage parameter singleton]
// +0xf38 [inferred: camera half-height scale], +0xf68 [inferred: aspect ratio],
// +0xf58 [inferred: width-to-height ratio], +0xeb0 [inferred: camera center pos (x,y) packed]
namespace app::camera {
extern "C" float4 get_camera_range(void) {
    u8* inner = *(u8**)DAT_71052b7f00;
    float half_h_scale = *(float*)(inner + 0xf38);
    float aspect       = *(float*)(inner + 0xf68);
    float half_h = half_h_scale * aspect;
    float ratio  = *(float*)(inner + 0xf58);
    float half_w = half_h * ratio;
#ifdef MATCHING_HACK_NX_CLANG
    asm("" :: "w"(half_w));
#endif
    // Vector load of center position — expected codegen: ldr q3,[x8,#0xeb0]
    float4 center = *(float4*)(inner + 0xeb0);
    float center_y = center[1];
    float bottom = center_y - half_h;
    float top = half_h + center_y;
#ifdef MATCHING_HACK_NX_CLANG
    asm("" :: "w"(bottom), "w"(top));
#endif
    float left = center[0] - half_w;
    float right = half_w + center[0];
    float4 r;
    r[0] = left;
    r[1] = right;
    r[2] = top;
    r[3] = bottom;
    return r;
}
} // namespace app::camera

// ---- Dead-up camera hit functions ----

// 0x7102281950 (80 bytes) — app::sv_fighter_util::set_dead_up_camera_hit_vis_change
// Checks status field at *(lua_state-8)+0x198, if 8 or 6, calls module+0x150 vtable[0x50/8]
// [derived: Ghidra shows check of iVar1 == 8 || 6, then module at +0x150, vtable[0x50/8]]
namespace app::sv_fighter_util {
extern "C" void set_dead_up_camera_hit_vis_change(u64 lua_state) {
    u8* ctx = *(u8**)(lua_state - 8);
    s32 status = *(s32*)(ctx + 0x198);
    if (status == 8 || status == 6) {
        void** mod = *(void***)(*(u8**)(ctx + 0x1a0) + 0x150);
        reinterpret_cast<void(*)(void**, u64, u64)>(
            ((void**)*mod)[0x50/8])(mod, 0x4dba80bb2ULL, 0xf4c200029ULL);
#ifdef MATCHING_HACK_NX_CLANG
        asm("" ::: "x29", "x30");
#endif
    }
}
} // namespace app::sv_fighter_util

// 0x71022818f0 (84 bytes) — app::sv_fighter_util::get_dead_up_camera_hit_prob
// Gets work module at +0x50, calls vtable[0x98/8](mod, 0x10000000),
// indexes into FighterManager to read u32
// [derived: disasm shows ldr w0 (integer return, not float)]
extern "C" __attribute__((noreturn)) void abort(void);
namespace app::sv_fighter_util {
extern "C" u32 get_dead_up_camera_hit_prob(u64 lua_state) {
    u8* battle_obj = *(u8**)(*(u8**)(lua_state - 8) + 0x1a0);
    void** work = *(void***)(battle_obj + 0x50);
    u32 idx = reinterpret_cast<u32(*)(void**, u32)>(
        ((void**)*work)[0x98/8])(work, 0x10000000);
    if (idx >= 8u) {
        abort();
    }
    u8* fm = *(u8**)FM_INSTANCE;
    u8* entry = *(u8**)(fm + (s64)(s32)idx * 8 + 0x20);
    u8* info = *(u8**)(entry + 0xf8);
    return *(u32*)(info + 0x80);
}
} // namespace app::sv_fighter_util

// ---- Stage entry function ----

// 0x7101675fd0 (88 bytes) — app::st_shell::entry_to_stage
// Constructs event data struct on stack, dispatches to stage manager
// DAT_71050b3828 [inferred: stage event vtable/type descriptor]
extern "C" u8 DAT_71050b3828 HIDDEN;
extern "C" void FUN_710315f230(u64, void*);

namespace app::st_shell {
extern "C" void entry_to_stage(u32 param_1) {
    struct {
        void* type;
        u64 field1;
        u64 field2;
        u32 param;
    } event;
    event.type = &DAT_71050b3828;
    event.field1 = 0x5000000000000001ULL;
    event.field2 = 0x500000000000004aULL;
    event.param = param_1;
    FUN_710315f230(*(u64*)(*(u8**)SM_INSTANCE + 0x1e0), &event);
}
} // namespace app::st_shell

// ---- Stage center / facing utility functions ----

// 0x71015cf110 (124 bytes) — app::stage::lr_to_stage_center
// Gets battle object posture, computes stage center from stage_info vtable[0x140/8],
// returns 1.0f if position <= center, -1.0f if position > center.
// [derived: disasm shows posture at +0x38, vtable[0x60/8] for pos, vtable[0x140/8] for stage bounds]
// [derived: fcsel s0,s1,s0,gt — ordered greater-than check, returns -1.0f when pos > center]
namespace app::stage {
extern "C" float lr_to_stage_center(u64 lua_state) {
    u8* battle_obj = *(u8**)(*(u8**)(lua_state - 8) + 0x1a0);
    void** posture = *(void***)(battle_obj + 0x38);
    u8* stage_info = *(u8**)SM_INSTANCE + 0x128;
    void** si_vt = *(void***)stage_info;
    float* bounds = reinterpret_cast<float*(*)(void*)>(si_vt[0x140/8])(stage_info);
    float* pos = reinterpret_cast<float*(*)(void**)>(((void**)*posture)[0x60/8])(posture);
    float px = *pos;
    float center = *bounds + (bounds[1] - *bounds) * 0.5f;
    if (px > center) {
        return -1.0f;
    }
    return 1.0f;
}
} // namespace app::stage

// 0x71015cf190 (156 bytes) — app::stage::is_looking_at_stage_center
// Same center computation, checks if facing direction matches the lr toward center.
// [derived: disasm shows fcsel s8,s1,s0,gt — saves lr in d8 across vtable[0xb0/8] call]
namespace app::stage {
extern "C" bool is_looking_at_stage_center(u64 lua_state) {
    u8* battle_obj = *(u8**)(*(u8**)(lua_state - 8) + 0x1a0);
    void** posture = *(void***)(battle_obj + 0x38);
    u8* stage_info = *(u8**)SM_INSTANCE + 0x128;
    void** si_vt = *(void***)stage_info;
    float* bounds = reinterpret_cast<float*(*)(void*)>(si_vt[0x140/8])(stage_info);
    float* pos = reinterpret_cast<float*(*)(void**)>(((void**)*posture)[0x60/8])(posture);
    float px = *pos;
    float center = *bounds + (bounds[1] - *bounds) * 0.5f;
    float lr;
    if (px > center) {
        lr = -1.0f;
    } else {
        lr = 1.0f;
    }
    float facing = reinterpret_cast<float(*)(void**)>(((void**)*posture)[0xb0/8])(posture);
    return facing == lr;
}
} // namespace app::stage

// ---- Dead-up camera hit distance group ----

// 0x71022802f0 (120 bytes) — app::sv_fighter_util::get_dead_up_camera_hit_my_distance_group
// Gets work module float, compares against FighterParamAccessor2 thresholds to return group 0/1/2.
// [derived: disasm shows FighterParamAccessor2 → [+0x50] → [+0x10c8] for threshold pair]
// [derived: fcmp+b.pl for >=thresh_lo, fcmp+b.le (!gt) for <=thresh_hi]
namespace app::sv_fighter_util {
extern "C" u64 get_dead_up_camera_hit_my_distance_group(u64 lua_state) {
    u8* battle_obj = *(u8**)(*(u8**)(lua_state - 8) + 0x1a0);
    void** work = *(void***)(battle_obj + 0x50);
    u8* param_sub = *(u8**)((u8*)DAT_71052bb3b0 + 0x50);
    float* thresholds = *(float**)(param_sub + 0x10c8);
    float thresh_lo = thresholds[0];
    float thresh_hi = thresholds[1];
    float val = reinterpret_cast<float(*)(void**, u64, s32)>(
        ((void**)*work)[0x270/8])(work, 0x1bf2c4c8e6ULL, 0);
    if (val < thresh_lo) {
        return 0;
    }
#ifdef MATCHING_HACK_NX_CLANG
    asm("");
#endif
    if (val > thresh_hi) {
        return 2;
    }
    return 1;
}
} // namespace app::sv_fighter_util

// ---- Stage restart scroll ----

// 0x710227ffd0 (160 bytes) — app::sv_fighter_util::stage_restart_scroll
// Gets posture position, adds stage_info scroll offset (returned as float4 in v0),
// builds new position on stack, calls set_pos.
// [derived: disasm shows posture+0x38 vtable[0x60/8] for pos (returns ptr),
//  stage_info vtable[0x58/8] returns offset as float4 in v0,
//  ldr q1 loads pos as vector, component-wise fadd, posture vtable[0x70/8] sets pos]
namespace app::sv_fighter_util {
extern "C" void stage_restart_scroll(u64 lua_state) {
    u8* battle_obj = *(u8**)(*(u8**)(lua_state - 8) + 0x1a0);
    void** posture = *(void***)(battle_obj + 0x38);
    float4* pos = reinterpret_cast<float4*(*)(void**)>(((void**)*posture)[0x60/8])(posture);
    u8* stage_info = *(u8**)SM_INSTANCE + 0x128;
    void** si_vt = *(void***)stage_info;
    float4 offset = reinterpret_cast<float4(*)(void*)>(si_vt[0x58/8])(stage_info);
    float4 p = *pos;
    float4 new_pos = {0};
    new_pos[0] = p[0] + offset[0];
    new_pos[1] = p[1] + offset[1];
    new_pos[2] = p[2] + offset[2];
    reinterpret_cast<void(*)(void**, float4*)>(((void**)*posture)[0x70/8])(posture, &new_pos);
}
} // namespace app::sv_fighter_util

// ---- CHECK_VALID_START_CAMERA wrappers ----

// 0x71022b1740 — inner implementation (2812 bytes, complex)
extern "C" void FUN_71022b1740(void*, u64);

// 0x71022b2240 (144 bytes) — app::sv_animcmd::CHECK_VALID_START_CAMERA
// Lua wrapper: sets up param struct on stack, calls FUN_71022b1740, cleans lua stack.
// [derived: disasm shows pre-check + do-while loop pattern for stack cleanup,
//  base computed as **(L+0x20)+0x10, argc = (top - base) >> 4]
namespace app::sv_animcmd {
extern "C" void CHECK_VALID_START_CAMERA(u64 lua_state) {
    struct {
        u64 val;        // +0x00
        u32 argc;       // +0x08
        u64 state;      // +0x10
        u8 done;        // +0x18
    } params;
    params.val = 0;
    u64 base = *(u64*)*(u64*)(lua_state + 0x20) + 0x10;
    params.state = lua_state;
    params.done = 0;
    params.argc = (u32)((*(u64*)(lua_state + 0x10) - base) >> 4);
    FUN_71022b1740(&params, *(u64*)(*(u8**)(lua_state - 8) + 0x1a0));
    base = *(u64*)*(u64*)(lua_state + 0x20) + 0x10;
    u64 top = *(u64*)(lua_state + 0x10);
    if (top < base) {
        do {
            *(u64*)(lua_state + 0x10) = top + 0x10;
            *(u32*)(top + 8) = 0;
            top = *(u64*)(lua_state + 0x10);
        } while (top < base);
    }
    *(u64*)(lua_state + 0x10) = base;
}
} // namespace app::sv_animcmd

// 0x71022b22d0 (144 bytes) — app::sv_animcmd::CHECK_VALID_START_CAMERA_arg8
// Identical structure to CHECK_VALID_START_CAMERA
namespace app::sv_animcmd {
extern "C" void CHECK_VALID_START_CAMERA_arg8(u64 lua_state) {
    struct {
        u64 val;
        u32 argc;
        u64 state;
        u8 done;
    } params;
    params.val = 0;
    u64 base = *(u64*)*(u64*)(lua_state + 0x20) + 0x10;
    params.state = lua_state;
    params.done = 0;
    params.argc = (u32)((*(u64*)(lua_state + 0x10) - base) >> 4);
    FUN_71022b1740(&params, *(u64*)(*(u8**)(lua_state - 8) + 0x1a0));
    base = *(u64*)*(u64*)(lua_state + 0x20) + 0x10;
    u64 top = *(u64*)(lua_state + 0x10);
    if (top < base) {
        do {
            *(u64*)(lua_state + 0x10) = top + 0x10;
            *(u32*)(top + 8) = 0;
            top = *(u64*)(lua_state + 0x10);
        } while (top < base);
    }
    *(u64*)(lua_state + 0x10) = base;
}
} // namespace app::sv_animcmd

// ---- Camera direction calculation ----

// 0x710165d190 (132 bytes) — app::dragoonsight::get_rotation_with_calc_camera_direction
// Computes rotation from camera direction vector using atan2f.
// [derived: disasm shows ldr q1,[x19,#0xed0] for vector load, dup s0,v1.s[1] for dy,
//  dup s1,v1.s[2] for dz, fabs s1 for |dz|, bl atan2f, then reload and negate dx]
extern "C" float DAT_7104471fbc HIDDEN;  // [inferred: radians-to-degrees conversion constant]
extern "C" float DAT_7104470d10 HIDDEN;  // [inferred: degree scale divisor]
extern "C" float atan2f(float, float);

namespace app::dragoonsight {
extern "C" float4 get_rotation_with_calc_camera_direction(void) {
    u8* cam = *(u8**)DAT_71052b7f00;
    float4 v = *(float4*)(cam + 0xed0);
    float angle_y = atan2f(v[1], __builtin_fabsf(v[2]));
    v = *(float4*)(cam + 0xed0);
    float angle_x = atan2f(-v[0], __builtin_fabsf(v[2]));
    float4 r = {0};
    r[0] = (angle_y * DAT_7104471fbc) / DAT_7104470d10;
    r[1] = (angle_x * DAT_7104471fbc) / DAT_7104470d10;
    return r;
}
} // namespace app::dragoonsight
