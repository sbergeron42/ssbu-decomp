#include "types.h"

// MEDIUM-tier FUN_* functions — batch d5-046
// Pool-d worker: misc functions (debug, ground, item, stage, fighter, camera stubs)
// Named functions tracked by FUN_ markers in comments:
// FUN_71015cff90 FUN_71015cffa0 FUN_71015cffb0 FUN_71015cffc0 FUN_71015cffd0
// FUN_71015c9fd0 FUN_71015cdfe0 FUN_71015ce6b0 FUN_71015cbbf0 FUN_71015cbc00
// FUN_71015cbc10 FUN_71015cfe620 FUN_71015ce4d0
// FUN_71015c2a90 FUN_71015c5560 FUN_71015c5580 FUN_71015c5b30
// FUN_71015c1a10 FUN_71015c1f40 FUN_71015c27a0
// FUN_71015cb5d0 FUN_71015cb6b0 FUN_71015cb6e0 FUN_71015cb710 FUN_71015cb010

// Additional named markers that we implement below:
// FUN_71015cfe620 = app::fighter::is_ready_go
// FUN_71015ce4d0 = app::fighter::get_fighter_entry_count
// FUN_71015ce6b0 = app::stage::is_the_stage_needs_render_offset

// ---- app::debug (all stubs) ----

// 0x71015cff90 — log_fatal
void FUN_71015cff90(void *param_1) { return; }
// 0x71015cffa0 — log_info
void FUN_71015cffa0(void *param_1) { return; }
// 0x71015cffb0 — set_draw_color
void FUN_71015cffb0(void *param_1, float p2, float p3, float p4, float p5) { return; }
// 0x71015cffc0 — draw_line
void FUN_71015cffc0(void *param_1, void *p2, void *p3, int p4) { return; }
// 0x71015cffd0 — add_debug_command
void FUN_71015cffd0(void *param_1, void *p2, int p3) { return; }

// ---- app::camera ----

// 0x71015cbbf0 — is_floor
u32 FUN_71015cbbf0(void *param_1) {
    if (param_1 != (void*)0) {
        return (u32)(*(u8*)((u8*)param_1 + 0xc5) >> 3 & 1);
    }
    return 0;
}

// 0x71015cbc00 — is_passable
u32 FUN_71015cbc00(void *param_1) {
    if (param_1 != (void*)0) {
        return (u32)(*(u8*)((u8*)param_1 + 0xc5) >> 5 & 1);
    }
    return 0;
}

// 0x71015cbc10 — is_wall (32B)
u32 FUN_71015cbc10(void *param_1) {
    if (param_1 != (void*)0) {
        return (u32)((*(u8*)((u8*)param_1 + 0xc5) & 3) != 0);
    }
    return 0;
}

// ---- app::utility ----

// 0x71015c9fd0 — get_category
u32 FUN_71015c9fd0(u32 param_1) {
    return param_1 >> 0x1c;
}

// ---- app::stage ----

// 0x71015cdfe0 — is_the_stage_needs_render_offset (returns 0)
u64 FUN_71015cdfe0(void) { return 0; }

// ---- app::fighter ----

// 0x71015ce620 — is_ready_go
extern s64 *lib_Singleton_FighterManager_instance_;
u8 FUN_71015ce620(void) {
    return *(u8*)(*lib_Singleton_FighterManager_instance_ + 0xd2);
}

// 0x71015ce4d0 — get_fighter_entry_count
u32 FUN_71015ce4d0(void) {
    return *(u32*)(*lib_Singleton_FighterManager_instance_ + 0xa0);
}

// ---- app::item_hud ----

// 0x71015cb010 — visibility
extern s64 *lib_Singleton_ItemManager_instance_;
void FUN_71015cb010(bool param_1) {
    *(bool*)(**(s64**)(lib_Singleton_ItemManager_instance_ + 0xa8) + 0x19) = param_1;
}

// ---- app::item_other ----

// 0x71015cb5d0 — action
void FUN_71015cb5d0(void *param_1, int param_2, float param_3) {
    if ((param_1 != (void*)0) && (*(u32*)((u8*)param_1 + 8) >> 0x1c == 4)) {
        auto *m = *(s64**)(*(s64*)((u8*)param_1 + 400) + 0x220);
        reinterpret_cast<void(*)(void*, int)>((*reinterpret_cast<void***>(m))[0x548/8])(m, param_2);
    }
}

// 0x71015cb6b0 — remove
void FUN_71015cb6b0(void *param_1) {
    if ((param_1 != (void*)0) && (*(u32*)((u8*)param_1 + 8) >> 0x1c == 4)) {
        auto *m = *(s64**)(*(s64*)((u8*)param_1 + 400) + 0x220);
        reinterpret_cast<void(*)(void*, int)>((*reinterpret_cast<void***>(m))[0x520/8])(m, 0);
    }
}

// 0x71015cb6e0 — throw_attack
extern void FUN_71015aba90(u64, void*, int);
void FUN_71015cb6e0(void *param_1, float param_2, void *param_3, float param_4) {
    if ((param_1 != (void*)0) && (*(u32*)((u8*)param_1 + 8) >> 0x1c == 4)) {
        FUN_71015aba90(*(u64*)(*(s64*)((u8*)param_1 + 400) + 0x220), param_3, 0);
    }
}

// 0x71015cb710 — id
u32 FUN_71015cb710(void *param_1) {
    u32 uVar1 = 0x50000000;
    if ((param_1 != (void*)0) && (*(u32*)((u8*)param_1 + 8) >> 0x1c == 4)) {
        uVar1 = *(u32*)(*(s64*)(*(s64*)((u8*)param_1 + 400) + 0x220) + 8);
    }
    return uVar1;
}

// ---- app::item ----

// 0x71015c2a90 — hit_absolute
extern void FUN_710160e540(void*, int, u32, int, int);
void FUN_71015c2a90(void *param_1, int param_2, u32 param_3, int param_4, int param_5) {
    if (param_1 != (void*)0) {
        FUN_710160e540(param_1, param_2, param_3, param_4, param_5);
    }
}

// 0x71015c5560 — get_pre_explosion_hit_object_id
u32 FUN_71015c5560(void *param_1) {
    return *(u32*)(*(s64*)(*(s64*)(*(s64*)(*(s64*)(*(s64*)((u8*)param_1 - 8) + 0x1a0) + 400) + 0x220) + 0x90) + 0x58);
}

// 0x71015c5580 — get_pre_explosion_attack_object_id
u32 FUN_71015c5580(void *param_1) {
    return *(u32*)(*(s64*)(*(s64*)(*(s64*)(*(s64*)(*(s64*)((u8*)param_1 - 8) + 0x1a0) + 400) + 0x220) + 0x90) + 0x5c);
}

// 0x71015c5b30 — set_postponed_damage_check_on_process_hit
void FUN_71015c5b30(void *param_1, bool param_2) {
    *(bool*)(*(s64*)(*(s64*)(*(s64*)(*(s64*)((u8*)param_1 - 8) + 0x1a0) + 400) + 0x220) + 0x62) = param_2;
}

// 0x71015c1a10 — request_cut_in_from_param_with_target_no_bgm_volume_change
extern void FUN_71015c1770(void*, u32, u64, u32, void*, u64, int);
void FUN_71015c1a10(void *param_1, u32 param_2, u64 param_3, u32 param_4, void *param_5) {
    FUN_71015c1770(param_1, param_2, param_3, param_4, param_5, 0x7fb997a80ULL, 0);
}

// 0x71015c1f40 — owner_id
u32 FUN_71015c1f40(void *param_1) {
    return *(u32*)(*(s64*)(*(s64*)(*(s64*)(*(s64*)((u8*)param_1 - 8) + 0x1a0) + 400) + 0x220) + 0x250);
}

// 0x71015c27a0 — id
u32 FUN_71015c27a0(void *param_1) {
    return *(u32*)(*(s64*)(*(s64*)(*(s64*)(*(s64*)((u8*)param_1 - 8) + 0x1a0) + 400) + 0x220) + 8);
}
