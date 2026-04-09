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
