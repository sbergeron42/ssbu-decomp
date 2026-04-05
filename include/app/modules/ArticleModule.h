#pragma once
#include "types.h"

namespace app {

// ArticleModule virtual dispatch wrapper
// Vtable entries recovered from lua_bind dispatcher analysis
// All method names derived from .dynsym lua_bind::ArticleModule__*_impl dispatcher analysis.
// Module accessed via BattleObjectModuleAccessor +0x98
struct ArticleModule {
    void** _vt;

    // Vtable dispatchers — index = byte_offset / 8
    // Names: [confirmed: lua_bind API name]

    void* generate_article(u64 p1, bool p2, u64 p3) { return ((void*(*)(ArticleModule*,u64,bool,u64))_vt[0x78/8])(this,p1,p2,p3); }
    void* generate_article_enable(u64 p1, bool p2, u64 p3) { return ((void*(*)(ArticleModule*,u64,bool,u64))_vt[0x80/8])(this,p1,p2,p3); }
    void* generate_article_have_item(u64 p1, u64 p2, u64 p3) { return ((void*(*)(ArticleModule*,u64,u64,u64))_vt[0x88/8])(this,p1,p2,p3); }
    void* have(u64 p1, u64 p2, u64 p3, u64 p4, bool p5) { return ((void*(*)(ArticleModule*,u64,u64,u64,u64,bool))_vt[0x90/8])(this,p1,p2,p3,p4,p5); }
    void shoot(u64 p1, u64 p2, bool p3) { ((void(*)(ArticleModule*,u64,u64,bool))_vt[0x98/8])(this,p1,p2,p3); }
    void shoot_exist(u64 p1, u64 p2, bool p3) { ((void(*)(ArticleModule*,u64,u64,bool))_vt[0xa0/8])(this,p1,p2,p3); }
    void set_pos(u64 p1) { ((void(*)(ArticleModule*,u64))_vt[0xa8/8])(this,p1); }
    void* motion_kind(u64 p1, u64 p2) { return ((void*(*)(ArticleModule*,u64,u64))_vt[0xb0/8])(this,p1,p2); }
    void change_motion(u64 p1, u64 p2, bool p3) { ((void(*)(ArticleModule*,u64,u64,bool))_vt[0xb8/8])(this,p1,p2,p3); }
    void change_motion_from_no(u64 p1, u64 p2, u64 p3, bool p4) { ((void(*)(ArticleModule*,u64,u64,u64,bool))_vt[0xc0/8])(this,p1,p2,p3,p4); }
    void add_motion_2nd(u64 p1, u64 p2, bool p3) { ((void(*)(ArticleModule*,u64,u64,bool))_vt[0xc8/8])(this,p1,p2,p3); }
    void* motion_kind_2nd(u64 p1, u64 p2) { return ((void*(*)(ArticleModule*,u64,u64))_vt[0xd0/8])(this,p1,p2); }
    void set_weight(u64 p1, bool p2) { ((void(*)(ArticleModule*,u64,bool))_vt[0xd8/8])(this,p1,p2); }
    void add_motion_partial(u64 p1, u64 p2, u64 p3, bool p4, bool p5, bool p6, bool p7, bool p8) { ((void(*)(ArticleModule*,u64,u64,u64,bool,bool,bool,bool,bool))_vt[0xe8/8])(this,p1,p2,p3,p4,p5,p6,p7,p8); }
    void set_frame(u64 p1) { ((void(*)(ArticleModule*,u64))_vt[0xf0/8])(this,p1); }
    void set_frame_2nd(u64 p1, bool p2) { ((void(*)(ArticleModule*,u64,bool))_vt[0xf8/8])(this,p1,p2); }
    void set_rate(u64 p1) { ((void(*)(ArticleModule*,u64))_vt[0x100/8])(this,p1); }
    void* change_status(u64 p1, u64 p2, u64 p3) { return ((void*(*)(ArticleModule*,u64,u64,u64))_vt[0x108/8])(this,p1,p2,p3); }
    void* change_status_exist(u64 p1, u64 p2) { return ((void*(*)(ArticleModule*,u64,u64))_vt[0x110/8])(this,p1,p2); }
    void set_visibility_whole(u64 p1, bool p2, u64 p3) { ((void(*)(ArticleModule*,u64,bool,u64))_vt[0x118/8])(this,p1,p2,p3); }
    void set_visibility(u64 p1, u64 p2, u64 p3, u64 p4) { ((void(*)(ArticleModule*,u64,u64,u64,u64))_vt[0x128/8])(this,p1,p2,p3,p4); }
    void set_default_visibility(u64 p1, u64 p2, u64 p3) { ((void(*)(ArticleModule*,u64,u64,u64))_vt[0x130/8])(this,p1,p2,p3); }
    void set_situation_kind(u64 p1, u64 p2) { ((void(*)(ArticleModule*,u64,u64))_vt[0x140/8])(this,p1,p2); }
    void set_flag(u64 p1, bool p2, u64 p3) { ((void(*)(ArticleModule*,u64,bool,u64))_vt[0x148/8])(this,p1,p2,p3); }
    bool is_flag(u64 p1, u64 p2) { return ((bool(*)(ArticleModule*,u64,u64))_vt[0x150/8])(this,p1,p2); }
    bool is_flag_from_no(u64 p1, u64 p2, u64 p3) { return ((bool(*)(ArticleModule*,u64,u64,u64))_vt[0x158/8])(this,p1,p2,p3); }
    void set_int(u64 p1, u64 p2, u64 p3) { ((void(*)(ArticleModule*,u64,u64,u64))_vt[0x160/8])(this,p1,p2,p3); }
    void* get_int(u64 p1, u64 p2) { return ((void*(*)(ArticleModule*,u64,u64))_vt[0x168/8])(this,p1,p2); }
    void set_float_from_no(u64 p1, u64 p2, u64 p3) { ((void(*)(ArticleModule*,u64,u64,u64))_vt[0x170/8])(this,p1,p2,p3); }
    void set_float(u64 p1, u64 p2) { ((void(*)(ArticleModule*,u64,u64))_vt[0x180/8])(this,p1,p2); }
    void* get_float(u64 p1, u64 p2) { return ((void*(*)(ArticleModule*,u64,u64))_vt[0x188/8])(this,p1,p2); }
    void get_float_from_no(u64 p1, u64 p2) { ((void(*)(ArticleModule*,u64,u64))_vt[0x190/8])(this,p1,p2); }
    void* remove(u64 p1, u64 p2) { return ((void*(*)(ArticleModule*,u64,u64))_vt[0x1b0/8])(this,p1,p2); }
    void* remove_exist(u64 p1, u64 p2) { return ((void*(*)(ArticleModule*,u64,u64))_vt[0x1b8/8])(this,p1,p2); }
    void remove_exist_object_id(u64 p1) { ((void(*)(ArticleModule*,u64))_vt[0x1c0/8])(this,p1); }
    bool is_exist(u64 p1) { return ((bool(*)(ArticleModule*,u64))_vt[0x1c8/8])(this,p1); }
    u32 get_num(u64 p1) { return ((u32(*)(ArticleModule*,u64))_vt[0x1d0/8])(this,p1); }
    bool is_generatable(u64 p1) { return ((bool(*)(ArticleModule*,u64))_vt[0x1d8/8])(this,p1); }
    u32 get_active_num(u64 p1) { return ((u32(*)(ArticleModule*,u64))_vt[0x1e0/8])(this,p1); }
    void* get_article(u64 p1) { return ((void*(*)(ArticleModule*,u64))_vt[0x208/8])(this,p1); }
    u32 get_article_from_no(u64 p1, u64 p2) { return ((u32(*)(ArticleModule*,u64,u64))_vt[0x210/8])(this,p1,p2); }
    void* get_joint_pos(u64 p1, u64 p2, u64 p3) { return ((void*(*)(ArticleModule*,u64,u64,u64))_vt[0x258/8])(this,p1,p2,p3); }
    void* get_joint_rotate(u64 p1, u64 p2, u64 p3) { return ((void*(*)(ArticleModule*,u64,u64,u64))_vt[0x260/8])(this,p1,p2,p3); }
    void* get_joint_scale() { return ((void*(*)(ArticleModule*))_vt[0x278/8])(this); }
};

} // namespace app
