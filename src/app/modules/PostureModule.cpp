#include "app/BattleObjectModuleAccessor.h"
#define VT(m) (*reinterpret_cast<void***>(m))

namespace app::lua_bind {

// All PostureModule dispatchers -- accessor+0x38

// 710206aeb0 -- set_pos_2d
void PostureModule__set_pos_2d_impl(BattleObjectModuleAccessor* accessor, void* pos) {
    auto* module = accessor->posture_module;
    auto* vtable = *reinterpret_cast<void***>(module);
    reinterpret_cast<void (*)(void*, void*)>(vtable[0x78 / 8])(module, pos);
}

// 710206aec0 -- add_pos
void PostureModule__add_pos_impl(BattleObjectModuleAccessor* accessor, void* pos) {
    auto* module = accessor->posture_module;
    auto* vtable = *reinterpret_cast<void***>(module);
    reinterpret_cast<void (*)(void*, void*)>(vtable[0x80 / 8])(module, pos);
}

// 710206aed0 -- add_pos_2d
void PostureModule__add_pos_2d_impl(BattleObjectModuleAccessor* accessor, void* pos) {
    auto* module = accessor->posture_module;
    auto* vtable = *reinterpret_cast<void***>(module);
    reinterpret_cast<void (*)(void*, void*)>(vtable[0x88 / 8])(module, pos);
}

// 710206aee0 -- prev_pos
void* PostureModule__prev_pos_impl(BattleObjectModuleAccessor* a) { auto* m=reinterpret_cast<void*>(*reinterpret_cast<u64*>(reinterpret_cast<u8*>(a)+0x38)); void* ret = reinterpret_cast<void*(*)(void*)>(VT(m)[0x90/8])(m); asm(""); return ret; }

// 710206af00 -- prev_pos_2d
void* PostureModule__prev_pos_2d_impl(BattleObjectModuleAccessor* accessor) {
    auto* module = accessor->posture_module;
    auto* vtable = *reinterpret_cast<void***>(module);
    return reinterpret_cast<void* (*)(void*)>(vtable[0x98 / 8])(module);
}

// 710206af10 -- lr
f32 PostureModule__lr_impl(BattleObjectModuleAccessor* accessor) {
    auto* module = accessor->posture_module;
    auto* vtable = *reinterpret_cast<void***>(module);
    return reinterpret_cast<f32 (*)(void*)>(vtable[0xb0 / 8])(module);
}

// 710206af20 -- set_lr
void PostureModule__set_lr_impl(BattleObjectModuleAccessor* accessor, f32 lr) {
    auto* module = accessor->posture_module;
    auto* vtable = *reinterpret_cast<void***>(module);
    reinterpret_cast<void (*)(void*, f32)>(vtable[0xb8 / 8])(module, lr);
}

// 710206af30 -- reverse_lr
void PostureModule__reverse_lr_impl(BattleObjectModuleAccessor* accessor) {
    auto* module = accessor->posture_module;
    auto* vtable = *reinterpret_cast<void***>(module);
    reinterpret_cast<void (*)(void*)>(vtable[0xc0 / 8])(module);
}

// 710206af40 -- init_rot
void* PostureModule__init_rot_impl(BattleObjectModuleAccessor* a) { auto* m=reinterpret_cast<void*>(*reinterpret_cast<u64*>(reinterpret_cast<u8*>(a)+0x38)); return reinterpret_cast<void*(*)(void*)>(VT(m)[0xc8/8])(m); }

// Remaining pure dispatchers
void PostureModule__init_pos_impl(BattleObjectModuleAccessor* a,void* p1,bool p2,bool p3) { auto* m=a->posture_module; auto* vt=*reinterpret_cast<void***>(m); reinterpret_cast<void(*)(void*,void*,bool,bool)>(vt[0x58/8])(m,p1,p2,p3); }
void* PostureModule__pos_2d_impl(BattleObjectModuleAccessor* a) { auto* m=a->posture_module; auto* vt=*reinterpret_cast<void***>(m); return reinterpret_cast<void*(*)(void*)>(vt[0x68/8])(m); }
void PostureModule__set_pos_impl(BattleObjectModuleAccessor* a,void* p1) { auto* m=a->posture_module; auto* vt=*reinterpret_cast<void***>(m); reinterpret_cast<void(*)(void*,void*)>(vt[0x70/8])(m,p1); }
void PostureModule__init_rot_2_impl(BattleObjectModuleAccessor* a,void* p1) { auto* m=a->posture_module; auto* vt=*reinterpret_cast<void***>(m); reinterpret_cast<void(*)(void*,void*)>(vt[0xd0/8])(m,p1); }
void PostureModule__set_rot_impl(BattleObjectModuleAccessor* a,u64 p1,u64 p2) { auto* m=reinterpret_cast<void*>(*reinterpret_cast<u64*>(reinterpret_cast<u8*>(a)+0x38)); reinterpret_cast<void(*)(void*,u64,u64)>(VT(m)[0xe0/8])(m,p1,p2); }
void PostureModule__init_rot_y_lr_impl(BattleObjectModuleAccessor* a) { auto* m=a->posture_module; auto* vt=*reinterpret_cast<void***>(m); reinterpret_cast<void(*)(void*)>(vt[0xe8/8])(m); }
bool PostureModule__is_rot_y_lr_different_inner_lr_impl(BattleObjectModuleAccessor* a) { auto* m=a->posture_module; auto* vt=*reinterpret_cast<void***>(m); return reinterpret_cast<bool(*)(void*)>(vt[0xf0/8])(m); }
f32 PostureModule__rot_y_lr_impl(BattleObjectModuleAccessor* a) { auto* m=a->posture_module; auto* vt=*reinterpret_cast<void***>(m); return reinterpret_cast<f32(*)(void*)>(vt[0xf8/8])(m); }
void PostureModule__reverse_rot_y_lr_impl(BattleObjectModuleAccessor* a) { auto* m=a->posture_module; auto* vt=*reinterpret_cast<void***>(m); reinterpret_cast<void(*)(void*)>(vt[0x108/8])(m); }
f32 PostureModule__base_scale_impl(BattleObjectModuleAccessor* a) { auto* m=a->posture_module; auto* vt=*reinterpret_cast<void***>(m); return reinterpret_cast<f32(*)(void*)>(vt[0x110/8])(m); }
void* PostureModule__scale_impl(BattleObjectModuleAccessor* a) { auto* m=a->posture_module; auto* vt=*reinterpret_cast<void***>(m); return reinterpret_cast<void*(*)(void*)>(vt[0x118/8])(m); }
void* PostureModule__init_scale_impl(BattleObjectModuleAccessor* a) { auto* m=reinterpret_cast<void*>(*reinterpret_cast<u64*>(reinterpret_cast<u8*>(a)+0x38)); return reinterpret_cast<void*(*)(void*)>(VT(m)[0x138/8])(m); }
f32 PostureModule__owner_scale_impl(BattleObjectModuleAccessor* a) { auto* m=a->posture_module; auto* vt=*reinterpret_cast<void***>(m); return reinterpret_cast<f32(*)(void*)>(vt[0x140/8])(m); }
void PostureModule__set_owner_scale_impl(BattleObjectModuleAccessor* a) { auto* m=reinterpret_cast<void*>(*reinterpret_cast<u64*>(reinterpret_cast<u8*>(a)+0x38)); reinterpret_cast<void(*)(void*)>(VT(m)[0x148/8])(m); }
void PostureModule__set_link_scale_impl(BattleObjectModuleAccessor* a,bool p1) { auto* m=a->posture_module; auto* vt=*reinterpret_cast<void***>(m); reinterpret_cast<void(*)(void*,bool)>(vt[0x150/8])(m,p1); }
void PostureModule__set_stick_lr_impl(BattleObjectModuleAccessor* a) { auto* m=reinterpret_cast<void*>(*reinterpret_cast<u64*>(reinterpret_cast<u8*>(a)+0x38)); reinterpret_cast<void(*)(void*)>(VT(m)[0x178/8])(m); }
void PostureModule__set_sync_constraint_joint_impl(BattleObjectModuleAccessor* a,u64 p1) { auto* m=a->posture_module; auto* vt=*reinterpret_cast<void***>(m); reinterpret_cast<void(*)(void*,u64)>(vt[0x180/8])(m,p1); }
// blr wrappers -- call vtable method returning Vector3f*, then extract component
// pos_impl calls vtable[0x60/8] and returns the pointer directly (8 insns)
void* PostureModule__pos_impl(BattleObjectModuleAccessor* a) { auto* m=reinterpret_cast<void*>(*reinterpret_cast<u64*>(reinterpret_cast<u8*>(a)+0x38)); void* ret = reinterpret_cast<void*(*)(void*)>(VT(m)[0x60/8])(m); asm(""); return ret; }
// pos_x calls vtable[0x60/8] then returns result[0] (9 insns)
f32 PostureModule__pos_x_impl(BattleObjectModuleAccessor* a) {
    auto* m = a->posture_module; auto* vt = *reinterpret_cast<void***>(m);
    auto* v = reinterpret_cast<f32*>(reinterpret_cast<void*(*)(void*)>(vt[0x60/8])(m));
    return v[0];
}
// pos_y calls vtable[0x60/8] then returns result[1] (9 insns)
f32 PostureModule__pos_y_impl(BattleObjectModuleAccessor* a) {
    auto* m = a->posture_module; auto* vt = *reinterpret_cast<void***>(m);
    auto* v = reinterpret_cast<f32*>(reinterpret_cast<void*(*)(void*)>(vt[0x60/8])(m));
    return v[1];
}
// pos_z calls vtable[0x60/8] then returns result[2] (9 insns)
f32 PostureModule__pos_z_impl(BattleObjectModuleAccessor* a) {
    auto* m = a->posture_module; auto* vt = *reinterpret_cast<void***>(m);
    auto* v = reinterpret_cast<f32*>(reinterpret_cast<void*(*)(void*)>(vt[0x60/8])(m));
    return v[2];
}
// rot_impl calls vtable[0xd8/8] and returns pointer (8 insns)
void* PostureModule__rot_impl(BattleObjectModuleAccessor* a) { auto* m=reinterpret_cast<void*>(*reinterpret_cast<u64*>(reinterpret_cast<u8*>(a)+0x38)); void* ret = reinterpret_cast<void*(*)(void*)>(VT(m)[0xd8/8])(m); asm(""); return ret; }
// rot_x calls vtable[0xd8/8] then returns result[0] (9 insns)
f32 PostureModule__rot_x_impl(BattleObjectModuleAccessor* a) {
    auto* m = a->posture_module; auto* vt = *reinterpret_cast<void***>(m);
    auto* v = reinterpret_cast<f32*>(reinterpret_cast<void*(*)(void*)>(vt[0xd8/8])(m));
    return v[0];
}
// rot_y calls vtable[0xd8/8] then returns result[1] (9 insns)
f32 PostureModule__rot_y_impl(BattleObjectModuleAccessor* a) {
    auto* m = a->posture_module; auto* vt = *reinterpret_cast<void***>(m);
    auto* v = reinterpret_cast<f32*>(reinterpret_cast<void*(*)(void*)>(vt[0xd8/8])(m));
    return v[1];
}
// rot_z calls vtable[0xd8/8] then returns result[2] (9 insns)
f32 PostureModule__rot_z_impl(BattleObjectModuleAccessor* a) {
    auto* m = a->posture_module; auto* vt = *reinterpret_cast<void***>(m);
    auto* v = reinterpret_cast<f32*>(reinterpret_cast<void*(*)(void*)>(vt[0xd8/8])(m));
    return v[2];
}
void PostureModule__update_rot_y_lr_impl(BattleObjectModuleAccessor* a) { auto* m=a->posture_module; auto* vt=*reinterpret_cast<void***>(m); reinterpret_cast<void(*)(void*)>(vt[0x100/8])(m); }
void PostureModule__set_scale_2_impl(BattleObjectModuleAccessor* a,bool p1) { auto* m=a->posture_module; auto* vt=*reinterpret_cast<void***>(m); reinterpret_cast<void(*)(void*,bool)>(vt[0x120/8])(m,p1); }
void PostureModule__set_scale_status_impl(BattleObjectModuleAccessor* a) { auto* m=reinterpret_cast<void*>(*reinterpret_cast<u64*>(reinterpret_cast<u8*>(a)+0x38)); reinterpret_cast<void(*)(void*)>(VT(m)[0x130/8])(m); }
} // namespace app::lua_bind
