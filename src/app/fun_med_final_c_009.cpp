// MEDIUM batch 009 (0x710219a34c – 0x7102302640)
// x9-chain functions, StageManager vtable calls, __cxa_guard init patterns, abort()

#include <stdint.h>
typedef uint8_t  u8;
typedef uint32_t u32;
typedef uint64_t u64;
typedef int32_t  s32;
typedef int64_t  s64;

// extern function declarations
extern "C" {
void FUN_710082a060(u64, u64);
void FUN_71015b0a00(u64);
void FUN_71015b8f40(u64, u64);
void FUN_71015ba050(u64, u64);
void FUN_71015b4d40(u64, u64);
void FUN_7102608770(u64);
int  __cxa_guard_acquire(u64 *);
void __cxa_guard_release(u64 *);
[[noreturn]] void abort(void);
}

struct lua_State;
namespace app {
struct BattleObjectModuleAccessor;
namespace item_other {
void apply_fighter_powerup_shoot(lua_State *, BattleObjectModuleAccessor *);
}
}

// singletons
extern s64 *lib_Singleton_StageManager_instance_;
extern s64 *lib_Singleton_ItemManager_instance_;

// DAT globals
extern u64 DAT_71052c2958;
// shared cxa_guard inner variables
extern u64 DAT_7105323748;
extern u64 DAT_7105323750;
extern u64 DAT_7105323758;
extern u64 DAT_7105323760;
extern u64 DAT_7105327150;
extern u64 DAT_7105327158;
// per-function cxa_guard outer variables
extern u64 DAT_71053237e8; extern u64 DAT_71053237f0;
extern u64 DAT_71053237a8; extern u64 DAT_71053237b0;
extern u64 DAT_71053237b8; extern u64 DAT_71053237c0;
extern u64 DAT_71053237c8; extern u64 DAT_71053237d0;
extern u64 DAT_7105323788; extern u64 DAT_7105323790;
extern u64 DAT_7105323778; extern u64 DAT_7105323780;
extern u64 DAT_71053237d8; extern u64 DAT_71053237e0;
extern u64 DAT_7105323798; extern u64 DAT_71053237a0;
extern u64 DAT_7105323808; extern u64 DAT_7105323810;
extern u64 DAT_71053237f8; extern u64 DAT_7105323800;
extern u64 DAT_7105327520; extern u64 DAT_7105327528;
extern u64 DAT_7105323828; extern u64 DAT_7105323830;
extern u64 DAT_7105323838; extern u64 DAT_7105323840;
extern u64 DAT_7105323848; extern u64 DAT_7105323850;
extern u64 DAT_7105323858; extern u64 DAT_7105323860;

// 0x710219a34c -- x9: FUN_710082a060(*(x9+0x50), *(x9+0x140))
u32 FUN_710219a34c(s64 param_1)
{
    register s64 in_x9 asm("x9");
    register u64 in_x10 asm("x10");
    asm volatile("" : "+r"(in_x9));
    asm volatile("" : "+r"(in_x10));
    *(u64 *)(param_1 + 0x10) = in_x10;
    FUN_710082a060(*(u64 *)(in_x9 + 0x50), *(u64 *)(in_x9 + 0x140));
    return 0;
}

// helper: shared chain from (param_1-8)
static inline u64 chain_from_neg8(s64 param_1) {
    return *(u64 *)(*(s64 *)(*(s64 *)(*(s64 *)(param_1 - 8) + 0x1a0) + 400) + 0x220);
}

// 0x71021fc598 -- stores in_x9; vtable call at chain+0x540
u32 FUN_71021fc598(s64 param_1)
{
    register s64 in_x9 asm("x9");
    asm volatile("" : "+r"(in_x9));
    *(s64 *)(param_1 + 0x10) = in_x9;
    s64 *obj = (s64 *)chain_from_neg8(param_1);
    (**(void (**)(void))(*obj + 0x540))();
    return 0;
}

// 0x71021fdc68 -- stores in_x9; FUN_71015b0a00(chain_val)
u32 FUN_71021fdc68(s64 param_1)
{
    register s64 in_x9 asm("x9");
    asm volatile("" : "+r"(in_x9));
    *(s64 *)(param_1 + 0x10) = in_x9;
    FUN_71015b0a00(chain_from_neg8(param_1));
    return 0;
}

// 0x710220bf70 -- FUN_71015b8f40(*DAT_71052c2958, chain_val)
u32 FUN_710220bf70(s64 param_1)
{
    FUN_71015b8f40(DAT_71052c2958, chain_from_neg8(param_1));
    return 0;
}

// 0x710220c248 -- stores in_x9; FUN_71015ba050(ItemManager+0xa8, chain_val)
u32 FUN_710220c248(s64 param_1)
{
    register s64 in_x9 asm("x9");
    asm volatile("" : "+r"(in_x9));
    *(s64 *)(param_1 + 0x10) = in_x9;
    FUN_71015ba050(*(u64 *)((u8 *)lib_Singleton_ItemManager_instance_ + 0xa8),
                   chain_from_neg8(param_1));
    return 0;
}

// 0x710220c588 -- x9: FUN_71015b4d40(*(*(x9+400)+0x220), chain_val)
u32 FUN_710220c588(s64 param_1)
{
    register s64 in_x9 asm("x9");
    asm volatile("" : "+r"(in_x9));
    FUN_71015b4d40(*(u64 *)(*(s64 *)(in_x9 + 400) + 0x220),
                   chain_from_neg8(param_1));
    return 0;
}

// 0x710220c660 -- item_other::apply_fighter_powerup_shoot; stores x9
u32 FUN_710220c660(lua_State *param_1, app::BattleObjectModuleAccessor *param_2)
{
    register s64 in_x9 asm("x9");
    asm volatile("" : "+r"(in_x9));
    *(u64 *)((u8 *)param_1 + 0x10) = (u64)in_x9;
    app::item_other::apply_fighter_powerup_shoot(param_1, param_2);
    return 0;
}

// 0x710220cc08 -- void(); x9 vtable at *(x9+400)+0x220, method +0x520
u32 FUN_710220cc08(void)
{
    register s64 in_x9 asm("x9");
    asm volatile("" : "+r"(in_x9));
    s64 *obj = *(s64 **)(*(s64 *)(in_x9 + 400) + 0x220);
    (**(void (**)(s64 *, int))(*obj + 0x520))(obj, 0);
    return 0;
}

// 0x7102250050 -- x9+x10; vtable on *(x9+0xd0) at +0x3b0 with (obj,0,0)
u32 FUN_7102250050(s64 param_1)
{
    register s64 in_x9 asm("x9");
    register u64 in_x10 asm("x10");
    asm volatile("" : "+r"(in_x9));
    asm volatile("" : "+r"(in_x10));
    *(u64 *)(param_1 + 0x10) = in_x10;
    s64 *obj = *(s64 **)(in_x9 + 0xd0);
    (**(void (**)(s64 *, int, int))(*obj + 0x3b0))(obj, 0, 0);
    return 0;
}

// 0x7102259440 -- same pattern as FUN_7102250050
u32 FUN_7102259440(s64 param_1)
{
    register s64 in_x9 asm("x9");
    register u64 in_x10 asm("x10");
    asm volatile("" : "+r"(in_x9));
    asm volatile("" : "+r"(in_x10));
    *(u64 *)(param_1 + 0x10) = in_x10;
    s64 *obj = *(s64 **)(in_x9 + 0xd0);
    (**(void (**)(s64 *, int, int))(*obj + 0x3b0))(obj, 0, 0);
    return 0;
}

// StageManager vtable helper
static inline void sm_vtable_228(int arg) {
    u8 *sm_base = (u8 *)lib_Singleton_StageManager_instance_;
    s64 lVar1 = *(s64 *)(sm_base + 0x128);
    (**(void (**)(u8 *, int, int))(lVar1 + 0x228))(sm_base + 0x128, arg, 0);
}

// 0x710225ac40 -- StageManager vtable+0x228, arg 0x2f
u32 FUN_710225ac40(void) { sm_vtable_228(0x2f); return 0; }
// 0x710225ac80 -- arg 0x30
u32 FUN_710225ac80(void) { sm_vtable_228(0x30); return 0; }
// 0x710225acc0 -- arg 0x31
u32 FUN_710225acc0(void) { sm_vtable_228(0x31); return 0; }
// 0x710225ad00 -- arg 0x32
u32 FUN_710225ad00(void) { sm_vtable_228(0x32); return 0; }

// 0x710225b1c0 -- FUN_7102608770(StageManager)
u32 FUN_710225b1c0(void) {
    FUN_7102608770((u64)*lib_Singleton_StageManager_instance_); return 0; }

// 0x710226f314 -- x9: vtable at *(x9+0x58), call +0x178 no-arg
u32 FUN_710226f314(s64 param_1)
{
    register s64 in_x9 asm("x9");
    register u64 in_x10 asm("x10");
    asm volatile("" : "+r"(in_x9));
    asm volatile("" : "+r"(in_x10));
    *(u64 *)(param_1 + 0x10) = in_x10;
    (**(void (**)(void))(**(s64 **)(in_x9 + 0x58) + 0x178))();
    return 0;
}

// ---- __cxa_guard singleton init functions ----

// 0x71022dece0 -- 2-level guard: DAT_7105327150/7158
u64 *FUN_71022dece0(void)
{
    int iVar1;
    if (((DAT_7105327150 & 1) == 0) && (iVar1 = __cxa_guard_acquire(&DAT_7105327150), iVar1 != 0)) {
        if (((DAT_7105323750 & 1) == 0) && (iVar1 = __cxa_guard_acquire(&DAT_7105323750), iVar1 != 0)) {
            DAT_7105323758 = 0;
            __cxa_guard_release(&DAT_7105323750);
        }
        DAT_7105327158 = (u64)&DAT_7105323758;
        __cxa_guard_release(&DAT_7105327150);
    }
    return &DAT_7105327158;
}

// 0x71022f1e30 -- 1-level guard: DAT_7105323750/7758 (innermost only)
u64 *FUN_71022f1e30(void)
{
    int iVar1;
    if (((DAT_7105323750 & 1) == 0) && (iVar1 = __cxa_guard_acquire(&DAT_7105323750), iVar1 != 0)) {
        DAT_7105323758 = 0;
        __cxa_guard_release(&DAT_7105323750);
    }
    return &DAT_7105323758;
}

// Macro for the common 3-level guard pattern:
// outer guard: G, outer data: D
// inner guard: DAT_7105323748 (mid), DAT_7105323750 (inner)
// inner data: DAT_7105323758, DAT_7105323760
#define CXA_GUARD_3LEVEL(fname, G, D) \
u64 *fname(void) { \
    int iVar1; \
    if (((G & 1) == 0) && (iVar1 = __cxa_guard_acquire(&G), iVar1 != 0)) { \
        if (((DAT_7105323748 & 1) == 0) && (iVar1 = __cxa_guard_acquire(&DAT_7105323748), iVar1 != 0)) { \
            if (((DAT_7105323750 & 1) == 0) && (iVar1 = __cxa_guard_acquire(&DAT_7105323750), iVar1 != 0)) { \
                DAT_7105323758 = 0; \
                __cxa_guard_release(&DAT_7105323750); \
            } \
            DAT_7105323760 = (u64)&DAT_7105323758; \
            __cxa_guard_release(&DAT_7105323748); \
        } \
        D = (u64)&DAT_7105323760; \
        __cxa_guard_release(&G); \
    } \
    return &D; \
}

// 0x71022f1520
CXA_GUARD_3LEVEL(FUN_71022f1520, DAT_71053237e8, DAT_71053237f0)
// 0x71022f19b0
CXA_GUARD_3LEVEL(FUN_71022f19b0, DAT_71053237a8, DAT_71053237b0)
// 0x71022f1b30
CXA_GUARD_3LEVEL(FUN_71022f1b30, DAT_71053237b8, DAT_71053237c0)
// 0x71022f1cb0
CXA_GUARD_3LEVEL(FUN_71022f1cb0, DAT_71053237c8, DAT_71053237d0)
// 0x71022f1f50
CXA_GUARD_3LEVEL(FUN_71022f1f50, DAT_7105323788, DAT_7105323790)
// 0x71022f20d0
CXA_GUARD_3LEVEL(FUN_71022f20d0, DAT_7105323778, DAT_7105323780)
// 0x71022f2250
CXA_GUARD_3LEVEL(FUN_71022f2250, DAT_71053237d8, DAT_71053237e0)
// 0x71022f23d0
CXA_GUARD_3LEVEL(FUN_71022f23d0, DAT_7105323798, DAT_71053237a0)
// 0x71022f71e0
CXA_GUARD_3LEVEL(FUN_71022f71e0, DAT_7105323808, DAT_7105323810)
// 0x71022f7360
CXA_GUARD_3LEVEL(FUN_71022f7360, DAT_71053237f8, DAT_7105323800)
// 0x71022fde80
CXA_GUARD_3LEVEL(FUN_71022fde80, DAT_7105323828, DAT_7105323830)
// 0x71022feef0
CXA_GUARD_3LEVEL(FUN_71022feef0, DAT_7105323838, DAT_7105323840)
// 0x71022ff070
CXA_GUARD_3LEVEL(FUN_71022ff070, DAT_7105323848, DAT_7105323850)
// 0x7102302640
CXA_GUARD_3LEVEL(FUN_7102302640, DAT_7105323858, DAT_7105323860)

// 0x71022fd770 -- 3-level via different inner chain (uses 7105327150/7158 as mid)
u64 *FUN_71022fd770(void)
{
    int iVar1;
    if (((DAT_7105327520 & 1) == 0) && (iVar1 = __cxa_guard_acquire(&DAT_7105327520), iVar1 != 0)) {
        if (((DAT_7105327150 & 1) == 0) && (iVar1 = __cxa_guard_acquire(&DAT_7105327150), iVar1 != 0)) {
            if (((DAT_7105323750 & 1) == 0) && (iVar1 = __cxa_guard_acquire(&DAT_7105323750), iVar1 != 0)) {
                DAT_7105323758 = 0;
                __cxa_guard_release(&DAT_7105323750);
            }
            DAT_7105327158 = (u64)&DAT_7105323758;
            __cxa_guard_release(&DAT_7105327150);
        }
        DAT_7105327528 = (u64)&DAT_7105327158;
        __cxa_guard_release(&DAT_7105327520);
    }
    return &DAT_7105327528;
}

// 0x7102300a6c -- abort
void FUN_7102300a6c(void) { abort(); }

// 0x710230146c -- abort
void FUN_710230146c(void) { abort(); }
