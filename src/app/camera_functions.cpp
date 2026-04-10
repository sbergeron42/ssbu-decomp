#include "types.h"
#include "app/ItemManager.h"
#include "app/BattleObjectWorld.h"
#include "app/GroundCollisionLine.h"
#include "app/modules/WorkModule.h"
#include "app/BattleObjectModuleAccessor.h"
#include "app/CameraController.h"
#include "app/placeholders/StageBase.h"

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
extern "C" void FUN_71025e55a0(StageBase*);

extern "C" void FUN_71028350b0(StageBase* param_1) {
    u64* p = reinterpret_cast<u64*>(param_1);
    param_1->vtable = reinterpret_cast<void**>(&PTR_LAB_71050e7a18);

    // +0x918 [derived: StageEnd owned ptr]
    u64 p3 = p[0x123];
    p[0x123] = 0;
    if (p3 != 0) FUN_710392e590((void*)p3);

    // +0x910 [derived: StageEnd owned ptr]
    u64 p2 = p[0x122];
    p[0x122] = 0;
    if (p2 != 0) FUN_710392e590((void*)p2);

    // +0x908 [derived: StageEnd owned object, cleanup via FUN_7102837e00]
    u64 p1 = p[0x121];
    p[0x121] = 0;
    if (p1 != 0) {
        FUN_7102837e00((void*)p1);
        FUN_710392e590((void*)p1);
    }

    FUN_7102834b90(p + 0xef);  // +0x778 [derived: StageEnd embedded sub-object]
    FUN_71025e55a0(param_1);   // [derived: ~StageBattleBase (intermediate dtor)]
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

// ---- Camera/stage dead area and range getters (leaf, vector return in v0) ----

// 0x71015cb9e0 (44 bytes) — app::camera::get_dead_area
// Leaf: returns 4 floats from camera data at +0xc30..+0xc3c
// [derived: disasm shows ldr s0 + ld1 {v0.s}[1-3] per-element load pattern]
namespace app::camera {
extern "C" float4 get_dead_area(void) {
    u8* inner = *(u8**)DAT_71052b7f00;
    float4 r;
    r[0] = *(float*)(inner + 0xc30);
    r[1] = *(float*)(inner + 0xc34);
    r[2] = *(float*)(inner + 0xc38);
    r[3] = *(float*)(inner + 0xc3c);
    return r;
}
} // namespace app::camera

// 0x710164c1d0 (44 bytes) — app::shiokarazu::get_dead_range
// [derived: same per-element pattern, reads +0xc30..+0xc3c]
namespace app::shiokarazu {
extern "C" float4 get_dead_range(void) {
    u8* inner = *(u8**)DAT_71052b7f00;
    float4 r;
    r[0] = *(float*)(inner + 0xc30);
    r[1] = *(float*)(inner + 0xc34);
    r[2] = *(float*)(inner + 0xc38);
    r[3] = *(float*)(inner + 0xc3c);
    return r;
}
} // namespace app::shiokarazu

// 0x710164c230 (44 bytes) — app::shiokarazu::get_shrinked_dead_range
// [derived: reads +0xc50..+0xc5c]
namespace app::shiokarazu {
extern "C" float4 get_shrinked_dead_range(void) {
    u8* inner = *(u8**)DAT_71052b7f00;
    float4 r;
    r[0] = *(float*)(inner + 0xc50);
    r[1] = *(float*)(inner + 0xc54);
    r[2] = *(float*)(inner + 0xc58);
    r[3] = *(float*)(inner + 0xc5c);
    return r;
}
} // namespace app::shiokarazu

// ---- Stage info tail-call functions ----

// 0x71015cf0d0 (56 bytes) — app::stage::get_smashball_rect
// Calls stage_info vtable[0x130/8] which returns CameraRect (HFA: s0-s3),
// packs result into float4 (v0) for return.
// [derived: disasm shows blr to vtable, then mov v0.s[1..3] to pack HFA into v0]
namespace app::stage {
extern "C" float4 get_smashball_rect(void) {
    u8* inner = *(u8**)SM_INSTANCE;
    u8* stage_info = inner + 0x128;
    void** vt = *(void***)stage_info;
    struct R4f { float a, b, c, d; };
    R4f result = reinterpret_cast<R4f(*)(void*)>(vt[0x130/8])(stage_info);
    float4 r;
    r[0] = result.a;
    r[1] = result.b;
    r[2] = result.c;
    r[3] = result.d;
    return r;
}
} // namespace app::stage

// ---- Camera position and z-axis functions ----

// 0x7101642f90 (32 bytes) — app::androssshot::is_valid_pos_z
// Leaf: checks if param_1 < cam_data[0xec8] - param_2
// [derived: disasm shows ldr from DAT_71052b7f00+0xec8, fsub, fcmp]
namespace app::androssshot {
extern "C" bool is_valid_pos_z(float param_1, float param_2) {
    u8* cam = *(u8**)DAT_71052b7f00;
    return param_1 < *(float*)(cam + 0xec8) - param_2;
}
} // namespace app::androssshot

// ---- Item/Boss module accessor leaf functions ----

// 0x7101647870 (40 bytes) — app::lioleus::get_area_down
// Gets module at +0xc0, calls vtable[0x1d8/8](mod, 0), returns result+4 (float)
// [derived: disasm shows ldr x0,[x0,#0xc0]; vtable[0x1d8/8](mod,0); ldr s0,[x0,#4]]
namespace app::lioleus {
extern "C" float get_area_down(u64 accessor) {
    void** mod = *(void***)(accessor + 0xc0);
    u8* result = reinterpret_cast<u8*(*)(void**, s32)>(
        ((void**)*mod)[0x1d8/8])(mod, 0);
    return *(float*)(result + 4);
}
} // namespace app::lioleus

// 0x7101655410 (40 bytes) — app::masterhand::get_rhombus_down_y
// Gets ground module at +0x58, calls vtable[0xb8/8](mod, 1), returns result+0x14 (float)
// [derived: disasm shows ldr x0,[x0,#0x58]; vtable[0xb8/8](mod,1); ldr s0,[x0,#0x14]]
namespace app::masterhand {
extern "C" float get_rhombus_down_y(u64 accessor) {
    void** mod = *(void***)(accessor + 0x58);
    u8* result = reinterpret_cast<u8*(*)(void**, s32)>(
        ((void**)*mod)[0xb8/8])(mod, 1);
    return *(float*)(result + 0x14);
}
} // namespace app::masterhand

// 0x71016433a0 (44 bytes) — app::baitocrane::is_enable_capture_baitocrane
// Gets posture module at +0x38, calls vtable[0x118/8](), checks result <= 1.0
// [derived: disasm shows ldr x0,[x0,#0x38]; vtable[0x118/8]; fcmp s0,#1.0; cset w0,ls]
namespace app::baitocrane {
extern "C" bool is_enable_capture_baitocrane(u64 accessor) {
    void** posture = *(void***)(accessor + 0x38);
    float val = reinterpret_cast<float(*)(void**)>(
        ((void**)*posture)[0x118/8])(posture);
    return val <= 1.0f;
}
} // namespace app::baitocrane

// ---- Ground collision line getters ----

// Zero constant vector for null-check fallback
// PTR_ConstantZero_71052a7a80 [derived: 128-bit zero constant, used by ground functions]
extern "C" u8 PTR_ConstantZero_71052a7a80 HIDDEN;

// 0x71015cbc40 (28 bytes) — app::ground::get_normal
// Returns vector at GroundCollisionLine+0xa0, or zero if null
// [derived: disasm shows cbz for null check, ldr q0,[x0,#0xa0] or ldr q0,[PTR_Zero]]
namespace app::ground {
extern "C" float4 get_normal(u8* line) {
    u8* p = (u8*)&PTR_ConstantZero_71052a7a80;
    if (line != nullptr) {
        p = line + 0xa0;
    }
    return *(float4*)p;
}
} // namespace app::ground

// 0x71015ccf90 (32 bytes) — app::ground::get_left_point
// Returns vector at *(line+0x88)+0x10, or zero if null
namespace app::ground {
extern "C" float4 get_left_point(u8* line) {
    if (line != nullptr) {
        return *(float4*)(*(u8**)(line + 0x88) + 0x10);
    }
    return *(float4*)&PTR_ConstantZero_71052a7a80;
}
} // namespace app::ground

// 0x71015ccfb0 (32 bytes) — app::ground::get_right_point
// Returns vector at *(line+0x90)+0x10, or zero if null
namespace app::ground {
extern "C" float4 get_right_point(u8* line) {
    if (line != nullptr) {
        return *(float4*)(*(u8**)(line + 0x90) + 0x10);
    }
    return *(float4*)&PTR_ConstantZero_71052a7a80;
}
} // namespace app::ground

// 0x71015ccfd0 (48 bytes) — app::ground::get_up_point
// Returns point from left or right endpoint — whichever has higher y
// [derived: disasm shows fcmp of +0x14 offsets (y-coordinate), fcsel with gt condition]
namespace app::ground {
extern "C" float4 get_up_point(u8* line) {
    if (line != nullptr) {
        u8* left = *(u8**)(line + 0x88);
        u8* right = *(u8**)(line + 0x90);
        float left_y = *(float*)(left + 0x14);
        float right_y = *(float*)(right + 0x14);
        u8* result = left;
        if (left_y > right_y) {
            result = right;
        }
        return *(float4*)(result + 0x10);
    }
    return *(float4*)&PTR_ConstantZero_71052a7a80;
}
} // namespace app::ground

// 0x71015cd000 (48 bytes) — app::ground::get_down_point
// Returns point from left or right endpoint — whichever has lower y
// [derived: disasm shows opposite condition from get_up_point]
namespace app::ground {
extern "C" float4 get_down_point(u8* line) {
    if (line != nullptr) {
        u8* left = *(u8**)(line + 0x88);
        u8* right = *(u8**)(line + 0x90);
        float left_y = *(float*)(left + 0x14);
        float right_y = *(float*)(right + 0x14);
        u8* result = right;
        if (left_y > right_y) {
            result = left;
        }
        return *(float4*)(result + 0x10);
    }
    return *(float4*)&PTR_ConstantZero_71052a7a80;
}
} // namespace app::ground

// ---- Camera off / final camera functions ----

// DAT_71045497e8 [inferred: stage kind lookup table base, stride 0x48 per entry, u32 at +8 = category]
extern "C" u8 DAT_71045497e8 HIDDEN;

// 0x71008df3f0 (188 bytes) — app::FighterSpecializer_Cloud::is_camera_off_final2
// Checks if current stage is in the "camera off for final2" hash list.
// [derived: disasm at 0x71008df3f0]
// Gets stage kind via StageManager singleton stage_info vtable[0], checks category table,
// then looks up stage hash via stage_info vtable[1] and searches a hash list in FighterParamAccessor2.
namespace app::FighterSpecializer_Cloud {
extern "C" bool is_camera_off_final2(void) {
    u8* sm_inner = *(u8**)SM_INSTANCE;
    u8* stage_info = sm_inner + 0x128;
    u32 kind = reinterpret_cast<u32(*)(void*)>((*(void***)stage_info)[0])(stage_info);
    // [derived: kind > 0x16b → out-of-table, always proceed to hash check]
    // [derived: table at DAT_71045497e8, stride 0x48, u32 at +8 is category; (cat-1) < 2 → return false]
    if (kind <= 0x16bu) {
        u32 val = *(u32*)(&DAT_71045497e8 + (s64)(s32)kind * 0x48 + 8);
        if ((u32)(val - 1) < 2u) return false;
    }
    // [derived: FighterParamAccessor2 → [+0xe00] sub-struct, loaded before second SM call]
    u8* param_sub = *(u8**)((u8*)DAT_71052bb3b0 + 0xe00);
    // [derived: reload SM for second vtable call — stage_info vtable[1] returns stage hash]
    sm_inner = *(u8**)SM_INSTANCE;
    stage_info = sm_inner + 0x128;
    u64 stage_hash = reinterpret_cast<u64(*)(void*)>((*(void***)stage_info)[1])(stage_info);
    // [derived: param_sub+0x1c0 = hash list start, +0x1c8 = hash list end (ldp pair)]
    u8* list_start = *(u8**)(param_sub + 0x1c0);
    s64 list_size = *(s64*)(param_sub + 0x1c8) - (s64)list_start;
    if (list_size != 0) {
        u64 i = 0;
        s64 count = list_size >> 3;
        // [derived: do-while loop — b.eq on size guarantees count > 0]
        do {
            // [derived: hash comparison masks to 40 bits (& 0xffffffffff)]
            if (((*(u64*)(list_start + i * 8) ^ stage_hash) & 0xffffffffffULL) == 0) {
                return true;
            }
            i++;
        } while ((u64)count > i);
    }
    return false;
}
} // namespace app::FighterSpecializer_Cloud

// 0x7100e2ce80 (196 bytes) — app::FighterSpecializer_Pacman::get_final_camera_pos
// Computes final camera position by interpolating a param table based on camera scale.
// [derived: Ghidra decompilation at 0x7100e2ce80]
// DAT_71052b7f00+0xa94 [inferred: camera data scale factor]
// DAT_7104471fbc [inferred: radians-to-degrees or unit conversion constant]
// DAT_7104470d10 [inferred: degree scale divisor]
// FighterParamAccessor2+0xc78 [inferred: final camera param sub-struct]
// +0x4c8 [inferred: interpolation table start ptr], +0x4d0 [inferred: table end ptr]
// Each table entry: { float threshold, float value, float slope } (12 bytes, stride 3 floats)
// DAT_71052b7f00+0xec8 [inferred: camera min clamp], +0xa64 [inferred: camera max clamp]
namespace app::FighterSpecializer_Pacman {
extern "C" float get_final_camera_pos(void) {
    u8* cam = *(u8**)DAT_71052b7f00;
    float scale = (*(float*)(cam + 0xa94) * DAT_7104471fbc) / DAT_7104470d10;
    u8* param_sub = *(u8**)((u8*)DAT_71052bb3b0 + 0xc78);
    float cam_max = *(float*)(cam + 0xa64);
    float cam_min = *(float*)(cam + 0xec8);
    u8* table_start = *(u8**)(param_sub + 0x4c8);
    s64 table_len = *(s64*)(param_sub + 0x4d0) - (s64)table_start;
    float best_val = 0.0f;
    float best_slope = 0.0f;
    float best_thresh = 0.0f;
    if (table_len != 0) {
        // [derived: entry count = (len >> 2) * 0xAAAAAAAAAAAAAAAB ≡ len/12]
        u64 count = (u64)(table_len >> 2) * 0xAAAAAAAAAAAAAAABULL;
        u64 i = 0;
        float* ptr = (float*)(table_start + 8);
        // [derived: do-while with count-up — b.ne on size guarantees at least 1 entry]
#pragma clang loop unroll(disable)
        do {
            float thresh = ptr[-2];
            // [derived: fcmp scale,thresh; b.le — update only when scale > thresh]
            if (scale > thresh) {
                best_val = ptr[-1];
                best_slope = ptr[0];
                best_thresh = thresh;
            }
            i++;
            ptr += 3;
        } while (count > i);
    }
    float result = (scale - best_thresh) * best_slope + best_val;
    // [derived: fcmp+fcsel mi → clamp: max(cam_min, result), then min(cam_max, that)]
    if (result < cam_min) result = cam_min;
    if (result > cam_max) result = cam_max;
    return result;
}
} // namespace app::FighterSpecializer_Pacman

// ---- Dead-up camera hit distance update ----

// 0x71006977f0 [inferred: get dead-up camera hit distance params, returns bool, writes int+float outputs]
extern "C" u64 FUN_71006977f0(void**, u32*, float*);

// 0x7102280370 (124 bytes) — app::sv_fighter_util::update_dead_up_camera_hit_first_distance_group
// Gets work module, calls FUN_71006977f0 for distance params, then sets work int + work float.
// [derived: disasm at 0x7102280370]
// [derived: vtable[0xa0/8] = set_work_int, vtable[0x60/8] = set_work_float]
namespace app::sv_fighter_util {
extern "C" bool update_dead_up_camera_hit_first_distance_group(u64 lua_state) {
    u8* battle_obj = *(u8**)(*(u8**)(lua_state - 8) + 0x1a0);
    void** work = *(void***)(battle_obj + 0x50);
    u32 param_int;
    float param_float;
    u64 result = FUN_71006977f0(work, &param_int, &param_float);
    // [derived: tbz w0,#0 — branch away on failure, fall through on success]
    if (__builtin_expect(result & 1, 1)) {
        // [derived: reload work from battle_obj+0x50 after call]
        work = *(void***)(battle_obj + 0x50);
        reinterpret_cast<void(*)(void**, u32, u32)>(
            ((void**)*work)[0xa0/8])(work, param_int, 0x1100000du);
        reinterpret_cast<void(*)(void**, u32, float)>(
            ((void**)*work)[0x60/8])(work, 0x1000010u, param_float);
        return true;
    }
    return false;
}
} // namespace app::sv_fighter_util

// ---- Camera module accessor ----

// 0x71003cb840 [derived: camera module accessor dispatch, takes module ptr + param struct]
extern "C" void FUN_71003cb840(void*, void*);

// 0x710227dbf0 (180 bytes) — app::sv_module_access::camera
// Lua module accessor: checks battle_obj, builds param struct, dispatches to camera module.
// [derived: disasm at 0x710227dbf0]
// [derived: early return before prologue when battle_obj is null]
namespace app::sv_module_access {
extern "C" u32 camera(u64 lua_state) {
    u64 battle_obj = *(u64*)(*(u8**)(lua_state - 8) + 0x1a0);
    if (battle_obj == 0) return 0;
    // [derived: stack layout: sp+0=val_ptr, sp+8=result(u32), sp+10=val(u64),
    //  sp+18=argc(u32), sp+20=state(u64), sp+28=done(u8)]
    u64 ctx[5];
    u8* p = (u8*)ctx;
    *(u64*)(p + 0x10) = 0;
    *(u64*)(p + 0x20) = lua_state;
    *(u8*)(p + 0x28) = 0;
    *(u32*)(p + 0x08) = 0;
    u64 base = *(u64*)*(u64*)(lua_state + 0x20);
    base += 0x10;
#ifdef MATCHING_HACK_NX_CLANG
    asm("" : "+r"(base));
#endif
    *(u32*)(p + 0x18) = (u32)((*(u64*)(lua_state + 0x10) - base) >> 4);
    *(u64*)(p + 0x00) = (u64)(p + 0x10);
    FUN_71003cb840(*(void**)(battle_obj + 0x60), p);
    u32 ret = *(u32*)(p + 0x08);
    if (*(u8*)(p + 0x28) != 0 && *(u64*)(p + 0x20) != 0) {
        u64 L = *(u64*)(p + 0x20);
        base = *(u64*)*(u64*)(L + 0x20) + 0x10;
        u64 top = *(u64*)(L + 0x10);
#ifdef MATCHING_HACK_NX_CLANG
        asm("" : "+r"(top), "+r"(base));
#endif
        if (top < base) {
            do {
                *(u64*)(L + 0x10) = top + 0x10;
                *(u32*)(top + 8) = 0;
                top = *(u64*)(L + 0x10);
            } while (top < base);
        }
        *(u64*)(L + 0x10) = base;
    }
    return ret;
}
} // namespace app::sv_module_access

// ---- Allocator hook wrappers ----

// DAT_71052b4450 [derived: custom malloc hook function pointer, nullable]
extern "C" void* DAT_71052b4450 HIDDEN;
// DAT_71052b4458 [derived: custom free hook function pointer, nullable]
extern "C" void* DAT_71052b4458 HIDDEN;

extern "C" void* malloc(unsigned long);
extern "C" void free(void*);

// 0x7100228110 (20 bytes) — malloc wrapper with hook
// [derived: disasm shows adrp+ldr of hook pointer, cbz to fallthrough malloc, br for hook]
extern "C" void* FUN_7100228110(unsigned long size) {
    void* hook = DAT_71052b4450;
    if (hook != nullptr) {
        return reinterpret_cast<void*(*)(unsigned long)>(hook)(size);
    }
    return malloc(size);
}

// 0x7100228130 (20 bytes) — free wrapper with hook
// [derived: disasm shows same pattern with DAT_71052b4458]
extern "C" void FUN_7100228130(void* ptr) {
    void* hook = DAT_71052b4458;
    if (hook != nullptr) {
        reinterpret_cast<void(*)(void*)>(hook)(ptr);
        return;
    }
    free(ptr);
}

// ---- Camera type change / revert ----

// change_active_camera [derived: at 0x71004ee480, takes (cam_data, mode, flags, stack_struct, extra)]
extern "C" void change_active_camera(u64, u32, u32, void*, u32);

// PTR_LAB_7104f73ca0 [derived: camera cleanup/release vtable, used by change_camera_type_melee and revert_camera]
extern "C" u8 PTR_LAB_7104f73ca0 HIDDEN;

// 0x7101649b90 (124 bytes) — app::nintendogshi::change_camera_type_melee
// Builds a stack object with cleanup vtable, calls change_active_camera(cam_data, 1, 0, obj, 0).
// Post-call: dispatches through the stack object's vtable for cleanup.
// [derived: disasm shows sp-local struct, vtable at PTR_LAB_7104f73ca0]
// [derived: post-call cleanup: if local_30==sp (inline), vtable[4]; else if non-null, vtable[5]]
namespace app::nintendogshi {
extern "C" void change_camera_type_melee(void) {
    u8* cam_data = *(u8**)DAT_71052b7f00;
    struct { void* vt; u8 pad[0x18]; void* self; } local;
    local.vt = &PTR_LAB_7104f73ca0;
    local.self = &local;
    change_active_camera((u64)cam_data, 1, 0, &local, 0);
    void* p = local.self;
    if (p == &local) {
        reinterpret_cast<void(*)(void*)>((*(void***)p)[0x20/8])(p);
    } else if (p != nullptr) {
        reinterpret_cast<void(*)(void*)>((*(void***)p)[0x28/8])(p);
    }
}
} // namespace app::nintendogshi

// 0x7101654b60 (136 bytes) — app::marx::revert_camera
// Checks if camera mode at *(cam_data+4) == 0x11; if not, returns immediately (before prologue).
// If mode matches, loads *(cam_data+8) as the sub-mode, calls change_active_camera.
// [derived: disasm shows early-return cmp w8,#0x11 + b.ne to ret before prologue setup]
namespace app::marx {
extern "C" void revert_camera_7101654b60(void) {
    u8* cam_data = *(u8**)DAT_71052b7f00;
    if (*(s32*)(cam_data + 4) != 0x11) return;
    u32 sub_mode = *(u32*)(cam_data + 8);
    struct { void* vt; u8 pad[0x18]; void* self; } local;
    local.vt = &PTR_LAB_7104f73ca0;
    local.self = &local;
    change_active_camera((u64)cam_data, sub_mode, 0, &local, 0);
    void* p = local.self;
    if (p == &local) {
        reinterpret_cast<void(*)(void*)>((*(void***)p)[0x20/8])(p);
    } else if (p != nullptr) {
        reinterpret_cast<void(*)(void*)>((*(void***)p)[0x28/8])(p);
    }
}
} // namespace app::marx

// ---- Stage destructors ----

// FUN_71025d7310 [derived: StageBase::~StageBase common destructor chain, tail-called by all stage dtors]
extern "C" void FUN_71025d7310(StageBase*);

// ---- ~StageNintendogs (0x7102ccf720, 136 bytes) ----
// Sets vtable, releases sub-object at +0x738 (3 inner ptrs at +0x790, +0x788, +0x780),
// calls FUN_7102ccf300 for sub-object cleanup, frees, then tail-calls StageBase dtor.
// [derived: disasm at 0x7102ccf720]

// PTR_LAB_710512e5e0 [derived: StageNintendogs vtable]
extern "C" u8 PTR_LAB_710512e5e0 HIDDEN;
extern "C" void FUN_7102ccf300(u64);

extern "C" void FUN_7102ccf720(StageBase* param_1)
{
    u64* p = reinterpret_cast<u64*>(param_1);
    u64 sub = p[0xe7];  // +0x738 [derived: StageNintendogs sub-object]
    param_1->vtable = reinterpret_cast<void**>(&PTR_LAB_710512e5e0);
    p[0xe7] = 0;
    if (sub != 0) {
        // Release sub-objects at +0x790, +0x788 via vtable[1]
        u64 p790 = *(u64*)(sub + 0x790);
        *(u64*)(sub + 0x790) = 0;
        if (p790 != 0) {
            reinterpret_cast<void(*)(u64)>((*(void***)(u64*)p790)[1])(p790);
        }
        u64 p788 = *(u64*)(sub + 0x788);
        *(u64*)(sub + 0x788) = 0;
        if (p788 != 0) {
            reinterpret_cast<void(*)(u64)>((*(void***)(u64*)p788)[1])(p788);
        }
        // Free allocation at +0x780
        u64 p780 = *(u64*)(sub + 0x780);
        *(u64*)(sub + 0x780) = 0;
        if (p780 != 0) {
            FUN_710392e590((void*)p780);
        }
        // Cleanup sub-object
        FUN_7102ccf300(sub + 0x10);
        FUN_710392e590((void*)sub);
    }
    FUN_71025d7310(param_1);
}

// ---- ~StageFlatZoneX (0x71029240a0, 176 bytes) ----
// Sets vtable, releases unique_ptr at +0xc78, destroys vector at [+0x850..+0x858],
// frees allocation at +0x830, tail-calls StageBase dtor.
// [derived: disasm at 0x71029240a0]

// PTR_LAB_71050f2f78 [derived: StageFlatZoneX vtable]
extern "C" u8 PTR_LAB_71050f2f78 HIDDEN;

extern "C" void FUN_71029240a0(StageBase* param_1)
{
    u64* p = reinterpret_cast<u64*>(param_1);
    param_1->vtable = reinterpret_cast<void**>(&PTR_LAB_71050f2f78);

    // Release unique_ptr at +0xc78 [derived: StageFlatZoneX field]
    u64 uptr = p[0xc78 / 8];
    p[0xc78 / 8] = 0;
    if (uptr != 0) {
        reinterpret_cast<void(*)(u64)>((*(void***)(u64*)uptr)[1])(uptr);
    }

    // Destroy vector at +0x850..+0x858 (elements are 0x18 bytes each)
    // [derived: Ghidra shows plVar1/plVar2 reuse pattern, plVar1 used as final free arg]
    u64* plVar2 = (u64*)p[0x850 / 8];
    if (plVar2 != nullptr) {
        u64* plVar1 = (u64*)p[0x858 / 8];
        if (plVar1 == plVar2) {
            p[0x858 / 8] = (u64)plVar2;
            plVar1 = plVar2;
        } else {
            u64* iter = plVar1;
            do {
                u64* plVar3 = iter - 3;
                u64 elem = *plVar3;
                if (elem != 0) {
                    iter[-2] = elem;
                    FUN_710392e590((void*)elem);
                }
                iter = plVar3;
            } while (plVar2 != iter);
            plVar1 = (u64*)p[0x850 / 8];
            p[0x858 / 8] = (u64)plVar2;
        }
        if (plVar1 != nullptr) {
            FUN_710392e590(plVar1);
        }
    }

    // Free allocation at +0x830 [derived: StageFlatZoneX field]
    u64 alloc = p[0x830 / 8];
    if (alloc != 0) {
        p[0x838 / 8] = alloc;
        FUN_710392e590((void*)alloc);
    }

    FUN_71025d7310(param_1);
}

// ---- ~StageStreetPass (0x7102f33f20, 192 bytes) ----
// Sets vtable, releases unique_ptr at +0x950, destroys vector at [+0x908..+0x910],
// frees allocations at +0x8b8 and +0x898, tail-calls StageBase dtor.
// [derived: disasm at 0x7102f33f20]

// PTR_LAB_71051520f8 [derived: StageStreetPass vtable]
extern "C" u8 PTR_LAB_71051520f8 HIDDEN;

extern "C" void FUN_7102f33f20(StageBase* param_1)
{
    u64* p = reinterpret_cast<u64*>(param_1);
    param_1->vtable = reinterpret_cast<void**>(&PTR_LAB_71051520f8);

    // Release unique_ptr at +0x950 [derived: StageStreetPass field]
    u64 uptr = p[0x950 / 8];
    if (uptr != 0) {
        reinterpret_cast<void(*)(u64)>((*(void***)(u64*)uptr)[1])(uptr);
        p[0x950 / 8] = 0;
    }

    // Destroy vector at +0x908..+0x910 (elements 0x18 bytes) [derived: StageStreetPass field]
    u64* plVar2 = (u64*)p[0x908 / 8];
    if (plVar2 != nullptr) {
        u64* plVar1 = (u64*)p[0x910 / 8];
        if (plVar1 == plVar2) {
            p[0x910 / 8] = (u64)plVar2;
            plVar1 = plVar2;
        } else {
            u64* iter = plVar1;
            do {
                u64* plVar3 = iter - 3;
                u64 elem = *plVar3;
                if (elem != 0) {
                    iter[-2] = elem;
                    FUN_710392e590((void*)elem);
                }
                iter = plVar3;
            } while (plVar2 != iter);
            plVar1 = (u64*)p[0x908 / 8];
            p[0x910 / 8] = (u64)plVar2;
        }
        if (plVar1 != nullptr) {
            FUN_710392e590(plVar1);
        }
    }

    // Free allocation at +0x8b8 [derived: StageStreetPass field]
    u64 alloc1 = p[0x8b8 / 8];
    if (alloc1 != 0) {
        p[0x8c0 / 8] = alloc1;
        FUN_710392e590((void*)alloc1);
    }

    // Free allocation at +0x898 [derived: StageStreetPass field]
    u64 alloc2 = p[0x898 / 8];
    if (alloc2 != 0) {
        p[0x8a0 / 8] = alloc2;
        FUN_710392e590((void*)alloc2);
    }

    FUN_71025d7310(param_1);
}

// ---- Additional leaf functions (batch 2) ----

// 0x710135dd10 (60 bytes) — coordinate_axes_replay_camera
// Sets thread priority to 0xf and enables effect manager flag.
// DAT_7106dd4cc0 [derived: nn::os::ThreadType for replay camera thread]
// DAT_7105333920 [derived: lib::Singleton<lib::EffectManager>::instance_]
// +0x194c1 [inferred: coordinate axes enable flag, u8]
// [derived: disasm at 0x710135dd10]
extern "C" u8 DAT_7106dd4cc0 HIDDEN;
extern "C" void* DAT_7105333920 HIDDEN;
extern "C" void nn_os_ChangeThreadPriority(void*, s32);

extern "C" void FUN_710135dd10(void) {
    nn_os_ChangeThreadPriority(&DAT_7106dd4cc0, 0xf);
    *(u8*)(*(u8**)DAT_7105333920 + 0x194c1) = 1;
}

// 0x7101651b00 (44 bytes) — app::crazyhand::get_dead_range
// Leaf: returns 4 floats from camera data at +0xc30..+0xc3c (same as shiokarazu variant)
namespace app { namespace crazyhand {
extern "C" float4 get_dead_range_7101651b00(void) {
    u8* inner = *(u8**)DAT_71052b7f00;
    float4 r;
    r[0] = *(float*)(inner + 0xc30);
    r[1] = *(float*)(inner + 0xc34);
    r[2] = *(float*)(inner + 0xc38);
    r[3] = *(float*)(inner + 0xc3c);
    return r;
}
}} // namespace app::crazyhand

// 0x7101651b60 (44 bytes) — app::crazyhand::get_shrinked_dead_range
// Leaf: returns 4 floats from camera data at +0xc50..+0xc5c
namespace app { namespace crazyhand {
extern "C" float4 get_shrinked_dead_range_7101651b60(void) {
    u8* inner = *(u8**)DAT_71052b7f00;
    float4 r;
    r[0] = *(float*)(inner + 0xc50);
    r[1] = *(float*)(inner + 0xc54);
    r[2] = *(float*)(inner + 0xc58);
    r[3] = *(float*)(inner + 0xc5c);
    return r;
}
}} // namespace app::crazyhand

// 0x71022820f0 (28 bytes) — app::sv_fighter_util::get_item_lift_motion_rate_mul
// Tail-call: passes battle_obj to FUN_710068e1c0
// [derived: disasm shows ldr x0,[x8,#0x1a0]; b FUN_710068e1c0]
extern "C" void FUN_710068e1c0(u64);

namespace app { namespace sv_fighter_util {
extern "C" void get_item_lift_motion_rate_mul(u64 lua_state) {
    u64 battle_obj = *(u64*)(*(u8**)(lua_state - 8) + 0x1a0);
    FUN_710068e1c0(battle_obj);
}
}} // namespace app::sv_fighter_util

// HFA (Homogeneous Float Aggregate) for camera rect — 4 floats returned in s0-s3
struct CameraRect { float x0, y0, x1, y1; };

// 0x7102282810 (32 bytes) — app::sv_camera_manager::dead_range
// Leaf: returns 4 floats from camera data at +0xc30..+0xc3c as CameraRect HFA (s0-s3)
// [derived: disasm shows 4x ldr s0-s3 pattern, same as camera_range]
namespace app { namespace sv_camera_manager {
extern "C" CameraRect dead_range(void) {
    u8* inner = *(u8**)DAT_71052b7f00;
    CameraRect r;
    r.x0 = *(float*)(inner + 0xc30);
    r.y0 = *(float*)(inner + 0xc34);
    r.x1 = *(float*)(inner + 0xc38);
    r.y1 = *(float*)(inner + 0xc3c);
    return r;
}
}} // namespace app::sv_camera_manager

// 0x71015ce830 (40 bytes) — app::stage::item_generate_position
// Returns float4 result from FUN_71015dc450 (passed stack pointer for output)
// [derived: disasm shows stack-local zero-init, bl to helper, ldp result from stack]
extern "C" void FUN_71015dc450(void*);

namespace app { namespace stage {
extern "C" float4 item_generate_position(void) {
    u64 result[2];
    result[0] = 0;
    result[1] = 0;
    FUN_71015dc450(result);
    return *(float4*)result;
}
}} // namespace app::stage

// ---- set_camera_range_from_param (0x71015c4830, 304 bytes) ----
// Gets ItemParamAccessor singleton, reads 4 param floats by hash,
// subtracts camera subject position, calls camera module set_range.
// [derived: Ghidra decompilation at 0x71015c4830]
// DAT_71052c34c8 [derived: lib::Singleton<app::ItemParamAccessor>::instance_]
extern "C" void* DAT_71052c34c8 HIDDEN;
extern "C" float FUN_7101602f50(void*, u32, u64, u64);

namespace app { namespace item {
extern "C" void set_camera_range_from_param(u64 lua_state, u32 kind, u64 hash) {
    void* ipa = DAT_71052c34c8;
    void** cam = *(void***)(*(u64*)(*(u8**)(lua_state - 8) + 0x1a0) + 0x60);
    float f0 = FUN_7101602f50(ipa, kind, hash, 0x47a67e768ULL);
    float f1 = FUN_7101602f50(ipa, kind, hash, 0x5b4ca7514ULL);
    float f2 = FUN_7101602f50(ipa, kind, hash, 0x31ed91fcaULL);
    float f3 = FUN_7101602f50(ipa, kind, hash, 0x6895f72a4ULL);
    float local[4];
    local[0] = f0;
    local[1] = f1;
    local[2] = f2;
    local[3] = f3;
    // Get camera subject position via vtable[0xb0/8](cam, 0)
    float* pos = reinterpret_cast<float*(*)(void**, s32)>(
        ((void**)*cam)[0xb0/8])(cam, 0);
    local[0] = f0 - pos[2];
    local[1] = f1 - pos[1];
    local[3] = f3 - pos[4];
    local[2] = f2 - pos[3];
    // Set camera range: vtable[0xd0/8](cam, &local, 0)
    reinterpret_cast<void(*)(void**, float*, s32)>(
        ((void**)*cam)[0xd0/8])(cam, local, 0);
}
}} // namespace app::item

// ---- Boss/Item camera leaf functions (batch 3) ----

// ---- kozukatasight screen helpers ----

// DAT_710744601c [derived: Ghidra float global, screen resolution width override]
extern "C" float DAT_710744601c HIDDEN;
// DAT_7107446020 [derived: Ghidra float global, screen resolution height override]
extern "C" float DAT_7107446020 HIDDEN;

// 0x7101646f00 (28 bytes) — app::kozukatasight::screen_width
// Returns screen width as int. Default 1920 (0x780) if the override float is 0.
// [derived: Ghidra decompilation at 0x7101646f00]
namespace app { namespace kozukatasight {
extern "C" u32 screen_width(void) {
    float w = DAT_710744601c;
    return w != 0.0f ? (u32)w : 0x780U;
}
}} // namespace app::kozukatasight

// 0x7101646f20 (28 bytes) — app::kozukatasight::screen_height
// Returns screen height as int. Default 1080 (0x438) if the override float is 0.
// [derived: Ghidra decompilation at 0x7101646f20]
namespace app { namespace kozukatasight {
extern "C" u32 screen_height(void) {
    float h = DAT_7107446020;
    return h != 0.0f ? (u32)h : 0x438U;
}
}} // namespace app::kozukatasight

// 0x7101646ed0 (48 bytes) — app::kozukatasight::screen_to_world
// Converts screen coordinates to world coordinates via FUN_7101341670.
// [derived: Ghidra decompilation at 0x7101646ed0]
extern "C" void FUN_7101341670(float, void*, void*, s32);

namespace app { namespace kozukatasight {
extern "C" float4 screen_to_world(void* vec2_in, float depth) {
    u64 local[2];
    local[0] = 0;
    local[1] = 0;
    FUN_7101341670(depth, local, vec2_in, 1);
    return *(float4*)local;
}
}} // namespace app::kozukatasight

// ---- can_exist checks ----

// DAT_71052c25b0 [derived: lib::Singleton<app::ItemManager>::instance_ pointer]
extern "C" void* DAT_71052c25b0 HIDDEN;

// 0x710164bb20 (28 bytes) — app::shiokarazu::can_exist
// Returns true if ItemManager stage data +0x708 == 0 (no existing instance).
// [derived: Ghidra decompilation at 0x710164bb20]
namespace app { namespace shiokarazu {
extern "C" bool can_exist_710164bb20(void) {
    u8* inst = (u8*)DAT_71052c25b0;
    return *(u64*)(*(u8**)(inst + 0x58) + 0x708) == 0;
}
}} // namespace app::shiokarazu

// 0x71016523a0 (28 bytes) — app::darz::can_exist
// Returns true if ItemManager stage data +0xcd0 == 0 (no existing instance).
// [derived: Ghidra decompilation at 0x71016523a0]
namespace app { namespace darz {
extern "C" bool can_exist_71016523a0(void) {
    u8* inst = (u8*)DAT_71052c25b0;
    return *(u64*)(*(u8**)(inst + 0x58) + 0xcd0) == 0;
}
}} // namespace app::darz

// ---- start_zoom_out variants ----

// FUN_710160dc80 [derived: camera zoom-out helper, takes (int mode, Vector4f* rect)]
extern "C" void FUN_710160dc80(s32, void*);

// 0x7101645980 (56 bytes) — app::flyandhand::start_zoom_out
// Copies camera rect from cam_data+0xc00 to stack, calls zoom-out helper.
// [derived: Ghidra decompilation at 0x7101645980]
namespace app { namespace flyandhand {
extern "C" void start_zoom_out_7101645980(s32 mode) {
    u8* cam = *(u8**)DAT_71052b7f00;
    u64 local[2];
    local[0] = *(u64*)(cam + 0xc00);
    local[1] = *(u64*)(cam + 0xc08);
    FUN_710160dc80(mode, local);
}
}} // namespace app::flyandhand

// 0x710164c420 (48 bytes) — app::shiokarazu::start_zoom_out
// Copies input Vector4f to stack, calls zoom-out helper.
// [derived: Ghidra decompilation at 0x710164c420]
namespace app { namespace shiokarazu {
extern "C" void start_zoom_out_710164c420(s32 mode, void* rect) {
    struct { u64 lo; u64 hi; } local;
    local = *(decltype(local)*)rect;
    FUN_710160dc80(mode, &local);
}
}} // namespace app::shiokarazu

// 0x7101651d50 (48 bytes) — app::crazyhand::start_zoom_out
// Identical to shiokarazu::start_zoom_out.
// [derived: Ghidra decompilation at 0x7101651d50]
namespace app { namespace crazyhand {
extern "C" void start_zoom_out_7101651d50(s32 mode, void* rect) {
    struct { u64 lo; u64 hi; } local;
    local = *(decltype(local)*)rect;
    FUN_710160dc80(mode, &local);
}
}} // namespace app::crazyhand

// ---- BGM functions ----

// DAT_7105328f38 [derived: BGM/sound manager singleton]
extern "C" void* DAT_7105328f38 HIDDEN;
// DAT_7104464590 [derived: BGM hash for shiokarazu track 0]
extern "C" u64 DAT_7104464590 HIDDEN;
// DAT_7104464328 [derived: BGM hash for shiokarazu track 1]
extern "C" u64 DAT_7104464328 HIDDEN;

// FUN_71023edd60 [derived: BGM play function, takes (mgr, hash, flags)]
extern "C" u64 FUN_71023edd60(void*, u64, s32);
// FUN_71023edf50 [derived: BGM stop function, takes (mgr, handle, params)]
extern "C" void FUN_71023edf50(void*, s32, void*);

// 0x710164bdc0 (76 bytes) — app::shiokarazu::start_bgm
// Plays a BGM track based on index (0 or 1). Returns handle or -1 on invalid index.
// [derived: Ghidra decompilation at 0x710164bdc0]
namespace app { namespace shiokarazu {
extern "C" u64 start_bgm(s32 index) {
    u64 hash;
    if (index == 0) {
        hash = DAT_7104464590;
    } else if (index == 1) {
        hash = DAT_7104464328;
    } else {
        return 0xffffffff;
    }
    u64 result = FUN_71023edd60(DAT_7105328f38, hash, 0);
#ifdef MATCHING_HACK_NX_CLANG
    asm("");  // prevent tail-call optimization
#endif
    return result;
}
}} // namespace app::shiokarazu

// 0x710164be10 (68 bytes) — app::shiokarazu::end_bgm
// Stops a BGM track by handle. No-op if handle is -1.
// [derived: Ghidra decompilation at 0x710164be10]
namespace app { namespace shiokarazu {
extern "C" void end_bgm(s32 handle, s32 fade_frames) {
    if (handle != -1) {
        struct { u8 flag; u8 pad[3]; s32 fade; } params;
        params.flag = 1;
        params.fade = fade_frames;
        FUN_71023edf50(DAT_7105328f38, handle, &params);
    }
}
}} // namespace app::shiokarazu

// ---- BGM RNG ----

// DAT_7104464220 [derived: BGM kind lookup table, 2 entries]
extern "C" u32 DAT_7104464220 HIDDEN;

// 0x710164bd60 (84 bytes) — app::shiokarazu::get_bgm_kind
// XorShift128 RNG to pick one of 2 BGM tracks. Advances RNG state at *(DAT_71052c25b0)+0x78..0x88.
// [derived: Ghidra decompilation at 0x710164bd60]
namespace app { namespace shiokarazu {
extern "C" u32 get_bgm_kind(void) {
    u64 rng_base = *(u64*)DAT_71052c25b0;
    u32* state = (u32*)(rng_base + 0x78);
    // Increment call counter
    *(u32*)(rng_base + 0x88) += 1;
    // XorShift128
    u32 s0 = state[0];
    u32 s3 = state[3];
    u32 t = s0 ^ (s0 << 11);
    state[0] = state[1];
    state[1] = state[2];
    state[2] = s3;
    u32 result = t ^ (t >> 8) ^ s3 ^ (s3 >> 19);
    state[3] = result;
    return (&DAT_7104464220)[result & 1];
}
}} // namespace app::shiokarazu

// ---- set_dead_range variants ----

// 0x710164c390 (140 bytes) — app::shiokarazu::set_dead_range
// Transforms input Vector4f by subtracting camera origin and adding extents to compute dead range rect.
// [derived: Ghidra decompilation at 0x710164c390]
// cam_data+0xa80: camera origin (x, y as float pair)
// cam_data+0xc60: camera extents (x_ext, y_ext as float pair)
// cam_data+0xc10..0xc3c: dead range output (left, right, bottom, top, left+ext, right+ext, bottom+ext, top+ext)
namespace app { namespace shiokarazu {
extern "C" void set_dead_range_710164c390(float4* param_1) {
    u8* cam = *(u8**)DAT_71052b7f00;
    float origin_x = *(float*)(cam + 0xa80);
    float origin_y = *(float*)(cam + 0xa84);
    float ext_x = *(float*)(cam + 0xc60);
    float ext_y = *(float*)(cam + 0xc64);
    float* input = (float*)param_1;
    float neg_ox = -origin_x;
    float neg_oy = -origin_y;
    float sum_ext_x = origin_x + ext_x;
    float sum_ext_y = origin_y + ext_y;
    float left = input[0] + neg_ox;
    float right = input[1] + neg_ox;
    float bottom = input[2] + neg_oy;
    float top = input[3] + neg_oy;
    *(float*)(cam + 0xc10) = left;
    *(float*)(cam + 0xc14) = right;
    *(float*)(cam + 0xc18) = bottom;
    *(float*)(cam + 0xc1c) = top;
    *(float*)(cam + 0xc30) = left + sum_ext_x;
    *(float*)(cam + 0xc34) = right + sum_ext_x;
    *(float*)(cam + 0xc38) = bottom + sum_ext_y;
    *(float*)(cam + 0xc3c) = top + sum_ext_y;
}
}} // namespace app::shiokarazu

// 0x7101651cc0 (140 bytes) — app::crazyhand::set_dead_range
// Identical to shiokarazu::set_dead_range.
// [derived: Ghidra decompilation at 0x7101651cc0]
namespace app { namespace crazyhand {
extern "C" void set_dead_range_7101651cc0(float4* param_1) {
    u8* cam = *(u8**)DAT_71052b7f00;
    float origin_x = *(float*)(cam + 0xa80);
    float origin_y = *(float*)(cam + 0xa84);
    float ext_x = *(float*)(cam + 0xc60);
    float ext_y = *(float*)(cam + 0xc64);
    float* input = (float*)param_1;
    float neg_ox = -origin_x;
    float neg_oy = -origin_y;
    float sum_ext_x = origin_x + ext_x;
    float sum_ext_y = origin_y + ext_y;
    float left = input[0] + neg_ox;
    float right = input[1] + neg_ox;
    float bottom = input[2] + neg_oy;
    float top = input[3] + neg_oy;
    *(float*)(cam + 0xc10) = left;
    *(float*)(cam + 0xc14) = right;
    *(float*)(cam + 0xc18) = bottom;
    *(float*)(cam + 0xc1c) = top;
    *(float*)(cam + 0xc30) = left + sum_ext_x;
    *(float*)(cam + 0xc34) = right + sum_ext_x;
    *(float*)(cam + 0xc38) = bottom + sum_ext_y;
    *(float*)(cam + 0xc3c) = top + sum_ext_y;
}
}} // namespace app::crazyhand

// ---- wanwan (Chain Chomp) ground movement ----

// 0x71016514c0 (60 bytes) — app::wanwan::add_movement
// Dispatches movement vector to pile ground module via vtable.
// [derived: Ghidra decompilation at 0x71016514c0]
// ItemModuleAccessor+0x68: KineticModule*
// KineticModule vtable[0x60/8](mod, 10) → pile ground object
// pile vtable[0xa0/8](pile, vec2) → add_movement
namespace app { namespace wanwan {
extern "C" void add_movement(u8* acc, void* vec2) {
    void** kinetic = *(void***)(acc + 0x68);
    void** pile = reinterpret_cast<void**(*)(void**, s32)>(
        (*(void***)kinetic)[0x60/8])(kinetic, 10);
    reinterpret_cast<void(*)(void**, void*)>(
        (*(void***)pile)[0xa0/8])(pile, vec2);
}
}} // namespace app::wanwan

// 0x7101651480 (60 bytes) — app::wanwan::get_pile_ground_movement_speed
// Returns the pile ground movement speed as a Vector4f (speed, 0).
// [derived: Ghidra decompilation at 0x7101651480]
namespace app { namespace wanwan {
extern "C" float4 get_pile_ground_movement_speed(u8* acc) {
    void** kinetic = *(void***)(acc + 0x68);
    void** pile = reinterpret_cast<void**(*)(void**, s32)>(
        (*(void***)kinetic)[0x60/8])(kinetic, 10);
    u64* speed = reinterpret_cast<u64*(*)(void**)>(
        (*(void***)pile)[0x20/8])(pile);
    u64 result[2];
    result[0] = *speed;
    result[1] = 0;
    return *(float4*)result;
}
}} // namespace app::wanwan

// ---- Tiny wrapper functions ----

// 0x71015c3060 (8 bytes) — app::item::get_assist_respawn_position
// Tail-calls FUN_710160e690 with an extra param=1.
// [derived: Ghidra decompilation at 0x71015c3060]
extern "C" void FUN_710160e690(void*, s32, s32);

namespace app { namespace item {
extern "C" void get_assist_respawn_position(void* vec3, s32 param_2) {
    FUN_710160e690(vec3, param_2, 1);
}
}} // namespace app::item

// 0x71015c8ed0 (8 bytes) — app::boss_private::create_weapon
// Tail-calls create_weapon_with_variation with variation=-1.
// [derived: Ghidra decompilation at 0x71015c8ed0]
extern "C" void create_weapon_with_variation(void*, s32, s32, float, float, float, float);

namespace app { namespace boss_private {
extern "C" void create_weapon_71015c8ed0(void* lua_state, s32 kind, float x, float y, float z, float w) {
    create_weapon_with_variation(lua_state, kind, -1, x, y, z, w);
}
}} // namespace app::boss_private

// 0x71015ce6c0 (8 bytes) — app::stage::calc_offset_with_gravity
// Tail-calls FUN_710160e340 forwarding vec3 as u64.
// [derived: Ghidra decompilation at 0x71015ce6c0]
extern "C" void FUN_710160e340(u64, void*);

namespace app { namespace stage {
extern "C" void calc_offset_with_gravity_71015ce6c0(void* vec2, void* vec3) {
    FUN_710160e340(*(u64*)vec2, vec3);
}
}} // namespace app::stage

// 0x71015c5c40 (16 bytes) — app::target::search_range
// Calls FUN_71015c5c50 with fixed params (5, param_6, 1).
// [derived: Ghidra decompilation at 0x71015c5c40]
extern "C" void FUN_71015c5c50(void*, s32, bool, s32);

namespace app { namespace target {
extern "C" void search_range(void* lua_state, float f1, float f2, float f3, float f4, bool flag) {
    FUN_71015c5c50(lua_state, 5, flag, 1);
}
}} // namespace app::target

// ---- Batch 4: more item/stage leaf functions ----

// 0x71015c1750 (28 bytes) — app::item::request_cut_in_from_param
// Tail-calls FUN_71015c1770 adding default params (0x50000000, vec2, hash, 1).
// [derived: Ghidra decompilation at 0x71015c1750]
extern "C" void FUN_71015c1770(void*, s32, u64, u32, void*, u64, s32);

namespace app { namespace item {
extern "C" void request_cut_in_from_param(void* lua_state, s32 kind, u64 hash, void* vec2) {
    FUN_71015c1770(lua_state, kind, hash, 0x50000000, vec2, 0x7fb997a80ULL, 1);
}
}} // namespace app::item

// 0x71015ce790 (48 bytes) — app::stage::back_line_z
// Returns -10.0f (0xc1200000) normally, or -1.0f (0xbf800000) if BattleObjectWorld
// has gravity disabled and stage depth < threshold.
// [derived: Ghidra decompilation at 0x71015ce790]
// lib::Singleton<app::BattleObjectWorld>::instance_ [derived: Ghidra label]
extern "C" void* DAT_71052bb390 HIDDEN;  // BattleObjectWorld instance
extern "C" float DAT_7104471590 HIDDEN;  // back_line_z threshold

namespace app { namespace stage {
extern "C" float back_line_z(void) {
    u8* world = (u8*)DAT_71052bb390;
    float result = -10.0f;
    if (*(char*)(world + 0xc) == 0 && *(float*)(world + 8) < DAT_7104471590) {
        result = -1.0f;
    }
    return result;
}
}} // namespace app::stage

// 0x71015c79e0 (64 bytes) — app::boss_private::common_param_float
// Reads float from ItemParamAccessor lookup table indexed by (kind, param_type).
// Returns 0 if param array for this kind is null.
// [derived: Ghidra decompilation at 0x71015c79e0]
// lib::Singleton<app::ItemParamAccessor>::instance_ [derived: Ghidra label]
extern "C" void* DAT_71052c34c0 HIDDEN;  // ItemParamAccessor instance

namespace app { namespace boss_private {
extern "C" u32 common_param_float(s32 kind, u32 param_type) {
    u8* ipa = (u8*)DAT_71052c34c0;
    if (*(u64*)(ipa + (s64)kind * 8 + 0xef8) != 0) {
        return *(u32*)(ipa + (s64)kind * 100 + (u64)param_type * 4 + 0x73188);
    }
    return 0;
}
}} // namespace app::boss_private

// 0x71015c11a0 (52 bytes) — app::item::begin_scale_animation
// Gets item scale data from lua accessor chain, calls FUN_71015b58e0 with animation params.
// [derived: Ghidra decompilation at 0x71015c11a0]
extern "C" float DAT_7104472918 HIDDEN;  // default scale animation rate
extern "C" void FUN_71015b58e0(float, u32, u64, s32, s32);

namespace app { namespace item {
extern "C" void begin_scale_animation(void* lua_state, s32 anim_type) {
    u8* boma = *(u8**)(*(u8**)((u8*)lua_state - 8) + 0x1a0);
    u64 scale_data = *(u64*)(*(u8**)(*(u8**)(boma + 400) + 0x220));
    FUN_71015b58e0(DAT_7104472918, 0x3f800000, scale_data, anim_type, -1);
}
}} // namespace app::item

// 0x71015c1d80 (80 bytes) — app::item::set_scale_speed_mul
// Sets scale speed multiplier on item, dispatches vtable call based on whether mul == 1.0.
// [derived: Ghidra decompilation at 0x71015c1d80]
namespace app { namespace item {
extern "C" void set_scale_speed_mul(void* lua_state, float mul) {
    u8* boma = *(u8**)(*(u8**)((u8*)lua_state - 8) + 0x1a0);
    u8* item_data = *(u8**)(*(u8**)(boma + 400) + 0x220);
    void** module = *(void***)(item_data + 0xe8);
    *(float*)(item_data + 0x27c) = mul;
    void* vt = *(void**)module;
    void (*func)(void**, u32);
    if (mul == 1.0f) {
        func = reinterpret_cast<void(*)(void**, u32)>(((void**)vt)[0x120/8]);
    } else {
        func = reinterpret_cast<void(*)(void**, u32)>(((void**)vt)[0x110/8]);
    }
    func(module, 0x20000014);
#ifdef MATCHING_HACK_NX_CLANG
    asm("");  // prevent tail-call
#endif
}
}} // namespace app::item

// 0x71015c22f0 (64 bytes) — app::item::calc_offset_with_gravity (lua_State version)
// Gets posture module from accessor, calls FUN_710160e340 with pos + vec2.
// [derived: Ghidra decompilation at 0x71015c22f0]
namespace app { namespace item {
extern "C" void calc_offset_with_gravity_71015c22f0(void* lua_state, void* vec2) {
    u8* boma = *(u8**)(*(u8**)((u8*)lua_state - 8) + 0x1a0);
    void** posture = *(void***)(boma + 0x38);
    u64* pos = reinterpret_cast<u64*(*)(void**)>(
        (*(void***)posture)[0x60/8])(posture);
    FUN_710160e340(*pos, vec2);
#ifdef MATCHING_HACK_NX_CLANG
    asm("");  // prevent tail-call
#endif
}
}} // namespace app::item

// ---- Batch 5: trivial return-value functions ----

// 0x71022821a0 (8 bytes) — app::sv_fighter_util::get_walk_speed_mul
// Returns 1.0f (hardcoded). Simplified-mode fallback.
// [derived: Ghidra decompilation at 0x71022821a0]
namespace app { namespace sv_fighter_util {
extern "C" float get_walk_speed_mul(void* lua_state) {
    return 1.0f;
}
}} // namespace app::sv_fighter_util

// 0x7102282800 (8 bytes) — app::sv_fighter_util::is_free_move_rot_legacy
// Always returns false. Legacy stub.
// [derived: Ghidra decompilation at 0x7102282800]
namespace app { namespace sv_fighter_util {
extern "C" u64 is_free_move_rot_legacy(void) {
    return 0;
}
}} // namespace app::sv_fighter_util

// 0x7102282290 (24 bytes) — app::sv_fighter_util::get_world_move_seed
// Returns {BattleObjectWorld+0x20, 0} as a 16-byte value.
// [derived: Ghidra decompilation at 0x7102282290]
namespace app { namespace sv_fighter_util {
extern "C" float4 get_world_move_seed(void) {
    u8* world = (u8*)DAT_71052bb390;
    u64 result[2];
    result[0] = *(u64*)(world + 0x20);
    result[1] = 0;
    return *(float4*)result;
}
}} // namespace app::sv_fighter_util

// ---- sv_camera_manager position getters ----

// 0x7102283240 (20 bytes) — app::sv_camera_manager::get_pos
// Returns camera position from cam_data+0xd30.
// [derived: Ghidra decompilation at 0x7102283240]
namespace app { namespace sv_camera_manager {
extern "C" float4 get_pos_7102283240(void) {
    u8* cam = *(u8**)DAT_71052b7f00;
    return *(float4*)(cam + 0xd30);
}
}} // namespace app::sv_camera_manager

// 0x7102283260 (20 bytes) — app::sv_camera_manager::get_target
// Returns camera target from cam_data+0xd20.
// [derived: Ghidra decompilation at 0x7102283260]
namespace app { namespace sv_camera_manager {
extern "C" float4 get_target_7102283260(void) {
    u8* cam = *(u8**)DAT_71052b7f00;
    return *(float4*)(cam + 0xd20);
}
}} // namespace app::sv_camera_manager

// 0x7102283280 (20 bytes) — app::sv_camera_manager::get_internal_pos
// Returns internal camera position from cam_data+0xec0.
// [derived: Ghidra decompilation at 0x7102283280]
namespace app { namespace sv_camera_manager {
extern "C" float4 get_internal_pos(void) {
    u8* cam = *(u8**)DAT_71052b7f00;
    return *(float4*)(cam + 0xec0);
}
}} // namespace app::sv_camera_manager

// 0x71022832a0 (20 bytes) — app::sv_camera_manager::get_internal_target
// Returns internal camera target from cam_data+0xeb0.
// [derived: Ghidra decompilation at 0x71022832a0]
namespace app { namespace sv_camera_manager {
extern "C" float4 get_internal_target(void) {
    u8* cam = *(u8**)DAT_71052b7f00;
    return *(float4*)(cam + 0xeb0);
}
}} // namespace app::sv_camera_manager

// ---- Batch 6: more boss/item leaf functions ----

// 0x7101652f20 (28 bytes) — app::kiila::can_exist
// Returns true if ItemManager stage data +0xc78 == 0.
// [derived: Ghidra decompilation at 0x7101652f20]
namespace app { namespace kiila {
extern "C" bool can_exist_7101652f20(void) {
    u8* inst = (u8*)DAT_71052c25b0;
    return *(u64*)(*(u8**)(inst + 0x58) + 0xc78) == 0;
}
}} // namespace app::kiila

// 0x71016538e0 (24 bytes) — app::kiiladarzmanager::stop_ingame_se
// Sets a flag byte at DAT_7105328f50+1 to 1.
// [derived: Ghidra decompilation at 0x71016538e0]
extern "C" void* DAT_7105328f50 HIDDEN;

namespace app { namespace kiiladarzmanager {
extern "C" void stop_ingame_se(void) {
    *(u8*)(*(u8**)DAT_7105328f50 + 1) = 1;
}
}} // namespace app::kiiladarzmanager

// 0x7101654bf0 (24 bytes) — app::marxchaseeye::adjust_model_constraint_posture
// Dispatches ModelModule vtable[0x3b0/8] with (module, 0, 0).
// [derived: Ghidra decompilation at 0x7101654bf0]
// ItemModuleAccessor+0xd0: ModelModule*
namespace app { namespace marxchaseeye {
extern "C" void adjust_model_constraint_posture(u8* acc) {
    void** model = *(void***)(acc + 0xd0);
    reinterpret_cast<void(*)(void**, s32, s32)>(
        (*(void***)model)[0x3b0/8])(model, 0, 0);
}
}} // namespace app::marxchaseeye

// 0x7101655110 (24 bytes) — app::masterhand::adjust_model_constraint_posture
// Identical to marxchaseeye variant.
// [derived: Ghidra decompilation at 0x7101655110]
namespace app { namespace masterhand {
extern "C" void adjust_model_constraint_posture_7101655110(u8* acc) {
    void** model = *(void***)(acc + 0xd0);
    reinterpret_cast<void(*)(void**, s32, s32)>(
        (*(void***)model)[0x3b0/8])(model, 0, 0);
}
}} // namespace app::masterhand

// ---- buddybomb param readers ----
// All read from FighterParamAccessor2 singleton at instance+0x12d0 pointer + field offset.
// [derived: Ghidra decompilations at 0x71016593a0..0x7101659400]

// FighterParamAccessor2::instance_ [derived: Ghidra singleton label]
extern "C" void* DAT_71052b5fc8 HIDDEN;  // lib::Singleton<app::FighterParamAccessor2>::instance_

// 0x71016593a0 (20 bytes) — app::buddybomb::init_bound_frame
namespace app { namespace buddybomb {
extern "C" u32 init_bound_frame(void) {
    u8* fpa = (u8*)DAT_71052b5fc8;
    return *(u32*)(*(u8**)(fpa + 0x12d0) + 0x230);
}
}} // namespace app::buddybomb

// 0x71016593c0 (20 bytes) — app::buddybomb::special_lw_gravity
namespace app { namespace buddybomb {
extern "C" u32 special_lw_gravity(void) {
    u8* fpa = (u8*)DAT_71052b5fc8;
    return *(u32*)(*(u8**)(fpa + 0x12d0) + 0x234);
}
}} // namespace app::buddybomb

// 0x71016593e0 (20 bytes) — app::buddybomb::special_lw_speed_y_max
namespace app { namespace buddybomb {
extern "C" u32 special_lw_speed_y_max(void) {
    u8* fpa = (u8*)DAT_71052b5fc8;
    return *(u32*)(*(u8**)(fpa + 0x12d0) + 0x238);
}
}} // namespace app::buddybomb

// 0x7101659400 (20 bytes) — app::buddybomb::length_gravity
namespace app { namespace buddybomb {
extern "C" u32 length_gravity(void) {
    u8* fpa = (u8*)DAT_71052b5fc8;
    return *(u32*)(*(u8**)(fpa + 0x12d0) + 0x240);
}
}} // namespace app::buddybomb

// ---- Batch 7: camera/stage/item functions ----

// ---- camera::target_pos ----

// 0x71015cbb60 (36 bytes) — app::camera::target_pos
// Returns camera target position from singleton+0xeb0, zeroing the w component.
// Assembly: ext v2,v0,v0,#8 → mov v2.S[1],0 → mov v0.D[1],v2.D[0] = zero w of float4.
// DAT_71052b7f00 [derived: camera/stage parameter singleton]
// +0xeb0 [inferred: camera target position, Vector4f {x,y,z,w}]
// [derived: Ghidra disasm at 0x71015cbb60]
namespace app { namespace camera {
extern "C" float4 target_pos(void) {
    u8* inner = *(u8**)DAT_71052b7f00;
    float4 v = *(float4*)(inner + 0xeb0);
    v[3] = 0.0f;
    return v;
}
}} // namespace app::camera

// ---- math2::reflection_2d ----

// 0x71015cfc70 (36 bytes) — app::math2::reflection_2d
// NEON vector reflection: result = v - 2*(v·n)*n
// Computes 2D dot product (faddp on lower 2 lanes) then applies to all 4 components.
// Uses full float4 vector ops: fmul.4S, faddp.2S, fadd.4S, fmul.4S, fsub.4S.
// [derived: Ghidra disasm at 0x71015cfc70]
namespace app { namespace math2 {
extern "C" float4 reflection_2d(const float4* v_ptr, const float4* n_ptr) {
    float4 v = *v_ptr;
    float4 n = *n_ptr;
    float4 prod = v * n;
    float dot = prod[0] + prod[1];
    float two_dot = dot + dot;
    float4 scale = {two_dot, two_dot, two_dot, two_dot};
    return v - n * scale;
}
}} // namespace app::math2

// ---- math2::bezier_curve ----

// 0x71015cfcb0 (80 bytes) — app::math2::bezier_curve
// Cubic Bezier: B(t) = (1-t)³p0 + 3(1-t)²t·p1 + 3(1-t)t²·p2 + t³p3
// Computation order from disasm: t³, 3t, s=1-t, then accumulate terms in reverse.
// [derived: Ghidra disasm at 0x71015cfcb0]
namespace app { namespace math2 {
extern "C" float bezier_curve(float p0, float p1, float p2, float p3, float t) {
    float t2 = t * t;
    float t3 = t2 * t;
    float three_t = t * 3.0f;
    float s = 1.0f - t;
    // t³ * p3
    float acc = t3 * p3;
    // s * 3t² * p2
    float three_t2 = three_t * t;
    acc += s * three_t2 * p2;
    // s² * 3t * p1
    float s_three_t = three_t * s;
    acc += s * s_three_t * p1;
    // s³ * p0
    float s2 = s * s;
    acc += s * s2 * p0;
    return acc;
}
}} // namespace app::math2

// ---- boss_private::send_event_on_start_boss_entry ----

// 0x71015c8450 (84 bytes) — app::boss_private::send_event_on_start_boss_entry
// Iterates ItemManager active item list (+0x28..+0x30 as u64*[]),
// finds item with matching battle_object_id, dispatches event.
// +0x90 → +0x18 [inferred: is_dead/removed flag, u8 — skip if set]
// +0x8 [derived: battle_object_id, u32 — matches against param]
// FUN_71015b52c0 [inferred: on_start_boss_entry event handler]
// [derived: Ghidra decompilation at 0x71015c8450]
extern "C" void FUN_71015b52c0(void*);

namespace app { namespace boss_private {
extern "C" void send_event_on_start_boss_entry(u32 battle_object_id) {
    if (battle_object_id == 0x50000000) return;
    app::ItemManager* im = (app::ItemManager*)DAT_71052c25b0;
    app::ItemEntry** begin = im->active_begin;
    app::ItemEntry** end   = im->active_end;
    for (app::ItemEntry** it = begin; it != end; ++it) {
        app::ItemEntry* item = *it;
        if (item->state_info->is_removed != 0) continue;
        if (item->battle_object_id == battle_object_id) {
            FUN_71015b52c0(item);
            return;
        }
    }
}
}} // namespace app::boss_private

// ---- boss_private::send_event_on_boss_finish ----

// 0x71015c84b0 (84 bytes) — app::boss_private::send_event_on_boss_finish
// Gets battle object from lua accessor chain, dispatches to BossManager.
// FUN_71003ab390 [inferred: get_battle_object_from_accessor — takes output buf + entry_id]
// DAT_71052b7ef8 [derived: lib::Singleton<app::BossManager>::instance_, adrp 0x71052b7000+0xef8]
// FUN_71004eb4b0 [inferred: BossManager::on_boss_finish dispatch]
// [derived: Ghidra disasm at 0x71015c84b0]
extern "C" void FUN_71003ab390(void*, u32);
extern "C" void* DAT_71052b7ef8 HIDDEN;  // lib::Singleton<app::BossManager>::instance_
extern "C" void FUN_71004eb4b0(void*, u32, u32, u64);

namespace app { namespace boss_private {
extern "C" void send_event_on_boss_finish(u8* lua_state, u64 hash40) {
    u8 buf[16];
    u8* accessor = *(u8**)(lua_state - 8);
    FUN_71003ab390(buf, *(u32*)(accessor + 0x190));
    u8* boss_mgr = (u8*)DAT_71052b7ef8;
    if (boss_mgr != 0) {
        u8* obj = *(u8**)(buf + 8);
        u32 w1 = *(u32*)(obj + 8);
        u32 w2 = *(u32*)(obj + 0xc);
#ifdef MATCHING_HACK_NX_CLANG
        asm("");
#endif
        FUN_71004eb4b0(*(void**)(boss_mgr + 8), w1, w2, hash40);
    }
}
}} // namespace app::boss_private

// ---- item_manager::find_active_item_from_id ----

// 0x71015ca930 (92 bytes) — app::item_manager::find_active_item_from_id
// Iterates ItemManager active list (+0x28..+0x30), finds item by battle_object_id.
// Returns item+0x98 (BattleObjectModuleAccessor*) or 0 if not found.
// +0x90 → +0x18 [inferred: is_dead flag, skip if set]
// +0x8 [derived: battle_object_id]
// [derived: Ghidra decompilation at 0x71015ca930]
namespace app { namespace item_manager {
extern "C" u64 find_active_item_from_id(u32 battle_object_id) {
    app::ItemEntry* found = 0;
    if (battle_object_id != 0x50000000) {
        app::ItemManager* im = (app::ItemManager*)DAT_71052c25b0;
        app::ItemEntry** begin = im->active_begin;
        app::ItemEntry** end   = im->active_end;
        for (app::ItemEntry** it = begin; it != end; ++it) {
            app::ItemEntry* item = *it;
            if (item->state_info->is_removed != 0) continue;
            if (item->battle_object_id == battle_object_id) {
                found = item;
                break;
            }
        }
    }
    if (!found) return 0;
    return (u64)&found->module_accessor;
}
}} // namespace app::item_manager

// ---- item_manager::remove_item_from_id ----

// 0x71015ca990 (88 bytes) — app::item_manager::remove_item_from_id
// Iterates ItemManager pending remove list (+0x10..+0x18), finds by battle_object_id.
// Calls vtable[0x520/8](item, 0) to trigger removal.
// +0x10 [inferred: pending item list begin pointer]
// +0x18 [inferred: pending item list end pointer]
// *(item+8) == battle_object_id [derived: id comparison pattern]
// [derived: Ghidra decompilation at 0x71015ca990]
namespace app { namespace item_manager {
extern "C" void remove_item_from_id(u32 battle_object_id) {
    if (battle_object_id == 0x50000000) return;
    app::ItemManager* im = (app::ItemManager*)DAT_71052c25b0;
    app::ItemEntry** begin = im->pending_begin;
    app::ItemEntry** end   = im->pending_end;
    for (app::ItemEntry** it = begin; it != end; ++it) {
        app::ItemEntry* item = *it;
        if (item->battle_object_id == battle_object_id) {
            if (item != 0) {
                item->remove(0);
            }
            return;
        }
    }
}
}} // namespace app::item_manager

// ---- ground::get_near_pos ----

// 0x71015cbd50 (76 bytes) — app::ground::get_near_pos
// Returns the closer of two collision line endpoints to a given position.
// Uses NEON float4 ops for distance: fsub.4S, fmul.4S, faddp.2S, fcmp, csel on pointers.
// line+0x88/+0x90 [derived: endpoint struct pointers], +0x10 [derived: position within endpoint]
// PTR_ConstantZero_71052a7a80 [derived: pointer to 128-bit zero constant]
// [derived: Ghidra disasm at 0x71015cbd50]
namespace app { namespace ground {
extern "C" float4 get_near_pos(app::GroundCollisionLine* line, const float4* pos) {
    if (!line) {
        return *(float4*)&PTR_ConstantZero_71052a7a80;
    }
    float4* p0 = (float4*)line->endpoint0->position;
    float4* p1 = (float4*)line->endpoint1->position;
    float4 d0 = *p0 - *pos;
    float4 d1 = *p1 - *pos;
    d0 = d0 * d0;
    d1 = d1 * d1;
    float dist0 = d0[0] + d0[1];
    float dist1 = d1[0] + d1[1];
    if (dist0 < dist1) {
        return *p0;
    }
    return *p1;
}
}} // namespace app::ground

// ---- sv_camera_manager::restore_pos_dead_range_gravity ----

// DAT_71052b7558 [derived: lib::Singleton<app::BattleObjectWorld>::instance_, adrp 0x71052b7000+0x558]
// Used by convert/restore_pos_dead_range_gravity and is_flat_stage.
extern "C" void* DAT_71052b7558 HIDDEN;

// 0x7102283020 (196 bytes) — app::sv_camera_manager::restore_pos_dead_range_gravity
// Reverses gravity rotation: given (angle, radius) in gravity space,
// converts back to world-space (x, y) using sin/cos.
// If gravity not active (BattleObjectWorld+0x5c!=0 || +0x59!=0), passes through unchanged.
// Then dispatches to WorkModule vtable[0x60/8] (set_float).
// DAT_71052b7558 [derived: lib::Singleton<app::BattleObjectWorld>::instance_, adrp 0x71052b7000+0x558]
// +0x5c [inferred: gravity disabled flag], +0x59 [inferred: gravity override flag]
// +0x14 [inferred: gravity_y, float — vertical component of gravity origin]
// [derived: Ghidra disasm at 0x7102283020]
extern "C" float sinf(float);
extern "C" float cosf(float);

namespace app { namespace sv_camera_manager {
extern "C" float4 restore_pos_dead_range_gravity(u8* lua_state, float x, float y, s32 param_4) {
    u8* acc_ptr = *(u8**)(lua_state - 8);
    app::BattleObjectModuleAccessor* accessor = *(app::BattleObjectModuleAccessor**)(acc_ptr + 0x1a0);
    float4 result = {0.0f, 0.0f, 0.0f, 0.0f};
    result[0] = x;
    result[1] = y;
    app::BattleObjectWorld* bow = (app::BattleObjectWorld*)DAT_71052b7558;
    if (bow->gravity_disabled_flag == 0 && bow->gravity_override_flag == 0) {
        float gravity_y = bow->gravity_origin_y;
        float diff = y - gravity_y;
        float angle = x / -gravity_y;
        float s = sinf(angle);
        result[0] = s * diff;
        float c = cosf(angle);
        result[1] = gravity_y + diff * c;
    }
    accessor->work_module->set_float(param_4, result[1]);
    return result;
}
}} // namespace app::sv_camera_manager

// ---- sv_camera_manager::convert_pos_dead_range_gravity ----

// 0x7102282ef0 (296 bytes) — app::sv_camera_manager::convert_pos_dead_range_gravity
// Converts world-space (x, y) to gravity-space (angle, radius) for dead range.
// Uses atan2f for angle, NEON frsqrte/frsqrts Newton-Raphson sqrt for distance.
// If gravity not active, passes through unchanged.
// DAT_71052b7558 [derived: lib::Singleton<app::BattleObjectWorld>::instance_]
// DAT_710447198c [inferred: float constant, angle reference (pi/2 or similar)]
// +0x10 [inferred: gravity origin, packed as {x:f32, y:f32}]
// +0xc30 [inferred: dead range negative extent], +0xc34 [inferred: dead range positive extent]
// [derived: Ghidra disasm at 0x7102282ef0]
extern "C" float DAT_710447198c HIDDEN;

namespace app { namespace sv_camera_manager {
extern "C" float4 convert_pos_dead_range_gravity(u8* lua_state, float x, float y, s32 param_4) {
    u8* acc_ptr = *(u8**)(lua_state - 8);
    app::BattleObjectModuleAccessor* accessor = *(app::BattleObjectModuleAccessor**)(acc_ptr + 0x1a0);
    float4 disp = {0.0f, 0.0f, 0.0f, 0.0f};
    float4 result = {0.0f, 0.0f, 0.0f, 0.0f};
    result[0] = x;
    result[1] = y;
    app::BattleObjectWorld* bow = (app::BattleObjectWorld*)DAT_71052b7558;
    if (bow->gravity_disabled_flag == 0 && bow->gravity_override_flag == 0) {
        // Subtract gravity origin
        float ox = bow->gravity_origin_x;
        float oy = bow->gravity_origin_y;
        float dx = x - ox;
        float dy = y - oy;
        disp[0] = dx;
        disp[1] = dy;
        app::CameraController* cam = *(app::CameraController**)DAT_71052b7f00;
        // Compute angle
        float angle = atan2f(dy, dx);
        angle = DAT_710447198c - angle;
        // Select extent based on angle sign
        float neg_ext = -cam->dead_range_neg;
        float pos_ext = cam->dead_range_pos;
        float extent = (angle < 0.0f) ? neg_ext : pos_ext;
        float gravity_y = bow->gravity_origin_y;
        float neg_gravity = -gravity_y;
        float ratio = extent / neg_gravity;
        float scaled_angle = angle / ratio;
        result[0] = extent * scaled_angle;
        // Compute magnitude via Newton-Raphson rsqrt (NEON frsqrte + 2x frsqrts)
        float dist_sq = dx * dx + dy * dy;
        float magnitude = __builtin_sqrtf(dist_sq);
        result[1] = gravity_y + magnitude;
    }
    accessor->work_module->set_float(param_4, result[1]);
    return result;
}
}} // namespace app::sv_camera_manager
