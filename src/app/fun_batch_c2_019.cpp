#include "types.h"
#include "app/BattleObjectModuleAccessor.h"

// Batch decompiled -- pool-c, batch 019
// Non-accessor vtable dispatch thunks (16B)

#define VT(m) (*reinterpret_cast<void***>(m))

namespace app::lua_bind {

// 0x00000071020542a0
u64 LinkEvent__load_from_l2c_table_impl(void* s, u64 p1) { void** v=*(void***)((u8*)s+0x0); return reinterpret_cast<u64(*)(void*,u64)>(v[0x38/8])(s,p1); }
// 0x00000071020542b0
u64 LinkEvent__store_l2c_table_impl(void* s) { void** v=*(void***)((u8*)s+0x0); return reinterpret_cast<u64(*)(void*)>(v[0x28/8])(s); }
// 0x0000007102054780
u64 LinkEventPos__load_from_l2c_table_impl(void* s, u64 p1) { void** v=*(void***)((u8*)s+0x0); return reinterpret_cast<u64(*)(void*,u64)>(v[0x38/8])(s,p1); }
// 0x0000007102054790
u64 LinkEventPos__store_l2c_table_impl(void* s) { void** v=*(void***)((u8*)s+0x0); return reinterpret_cast<u64(*)(void*)>(v[0x28/8])(s); }
// 0x0000007102055a30
u64 LinkEventMask__load_from_l2c_table_impl(void* s, u64 p1) { void** v=*(void***)((u8*)s+0x0); return reinterpret_cast<u64(*)(void*,u64)>(v[0x38/8])(s,p1); }
// 0x0000007102055a40
u64 LinkEventMask__store_l2c_table_impl(void* s) { void** v=*(void***)((u8*)s+0x0); return reinterpret_cast<u64(*)(void*)>(v[0x28/8])(s); }
// 0x00000071020b1920
u64 LinkEventFinal__load_from_l2c_table_impl(void* s, u64 p1) { void** v=*(void***)((u8*)s+0x0); return reinterpret_cast<u64(*)(void*,u64)>(v[0x38/8])(s,p1); }
// 0x00000071020b1930
u64 LinkEventFinal__store_l2c_table_impl(void* s) { void** v=*(void***)((u8*)s+0x0); return reinterpret_cast<u64(*)(void*)>(v[0x28/8])(s); }
// 0x00000071020b38a0
u64 LinkEventStarShot__load_from_l2c_table_impl(void* s, u64 p1) { void** v=*(void***)((u8*)s+0x0); return reinterpret_cast<u64(*)(void*,u64)>(v[0x38/8])(s,p1); }
// 0x00000071020b38b0
u64 LinkEventStarShot__store_l2c_table_impl(void* s) { void** v=*(void***)((u8*)s+0x0); return reinterpret_cast<u64(*)(void*)>(v[0x28/8])(s); }
// 0x00000071020b49e0
u64 LinkEventCapturePulled__load_from_l2c_table_impl(void* s, u64 p1) { void** v=*(void***)((u8*)s+0x0); return reinterpret_cast<u64(*)(void*,u64)>(v[0x38/8])(s,p1); }
// 0x00000071020b49f0
u64 LinkEventCapturePulled__store_l2c_table_impl(void* s) { void** v=*(void***)((u8*)s+0x0); return reinterpret_cast<u64(*)(void*)>(v[0x28/8])(s); }
// 0x00000071020b60e0
u64 LinkEventCaptureItem__load_from_l2c_table_impl(void* s, u64 p1) { void** v=*(void***)((u8*)s+0x0); return reinterpret_cast<u64(*)(void*,u64)>(v[0x38/8])(s,p1); }
// 0x00000071020b60f0
u64 LinkEventCaptureItem__store_l2c_table_impl(void* s) { void** v=*(void***)((u8*)s+0x0); return reinterpret_cast<u64(*)(void*)>(v[0x28/8])(s); }
// 0x00000071020b8970
u64 LinkEventCaptureMimikkyu__load_from_l2c_table_impl(void* s, u64 p1) { void** v=*(void***)((u8*)s+0x0); return reinterpret_cast<u64(*)(void*,u64)>(v[0x38/8])(s,p1); }
// 0x00000071020b8980
u64 LinkEventCaptureMimikkyu__store_l2c_table_impl(void* s) { void** v=*(void***)((u8*)s+0x0); return reinterpret_cast<u64(*)(void*)>(v[0x28/8])(s); }
// 0x00000071020b9550
u64 LinkEventCaptureDriver__load_from_l2c_table_impl(void* s, u64 p1) { void** v=*(void***)((u8*)s+0x0); return reinterpret_cast<u64(*)(void*,u64)>(v[0x38/8])(s,p1); }
// 0x00000071020b9560
u64 LinkEventCaptureDriver__store_l2c_table_impl(void* s) { void** v=*(void***)((u8*)s+0x0); return reinterpret_cast<u64(*)(void*)>(v[0x28/8])(s); }
// 0x00000071020bbed0
u64 OnCalcParamEvent__load_from_l2c_table_impl(void* s, u64 p1) { void** v=*(void***)((u8*)s+0x0); return reinterpret_cast<u64(*)(void*,u64)>(v[0x38/8])(s,p1); }
// 0x00000071020bbee0
u64 OnCalcParamEvent__store_l2c_table_impl(void* s) { void** v=*(void***)((u8*)s+0x0); return reinterpret_cast<u64(*)(void*)>(v[0x28/8])(s); }
// 0x00000071020d4740
u64 GimmickEvent__load_from_l2c_table_impl(void* s, u64 p1) { void** v=*(void***)((u8*)s+0x0); return reinterpret_cast<u64(*)(void*,u64)>(v[0x38/8])(s,p1); }
// 0x00000071020d4750
u64 GimmickEvent__store_l2c_table_impl(void* s) { void** v=*(void***)((u8*)s+0x0); return reinterpret_cast<u64(*)(void*)>(v[0x28/8])(s); }
// 0x00000071020d5850
u64 GimmickEventPos__load_from_l2c_table_impl(void* s, u64 p1) { void** v=*(void***)((u8*)s+0x0); return reinterpret_cast<u64(*)(void*,u64)>(v[0x38/8])(s,p1); }
// 0x00000071020d5860
u64 GimmickEventPos__store_l2c_table_impl(void* s) { void** v=*(void***)((u8*)s+0x0); return reinterpret_cast<u64(*)(void*)>(v[0x28/8])(s); }
// 0x00000071020d69f0
u64 GimmickEventNotify__load_from_l2c_table_impl(void* s, u64 p1) { void** v=*(void***)((u8*)s+0x0); return reinterpret_cast<u64(*)(void*,u64)>(v[0x38/8])(s,p1); }
// 0x00000071020d6a00
u64 GimmickEventNotify__store_l2c_table_impl(void* s) { void** v=*(void***)((u8*)s+0x0); return reinterpret_cast<u64(*)(void*)>(v[0x28/8])(s); }
// 0x00000071020d7520
u64 GimmickEventWarp__load_from_l2c_table_impl(void* s, u64 p1) { void** v=*(void***)((u8*)s+0x0); return reinterpret_cast<u64(*)(void*,u64)>(v[0x38/8])(s,p1); }
// 0x00000071020d7530
u64 GimmickEventWarp__store_l2c_table_impl(void* s) { void** v=*(void***)((u8*)s+0x0); return reinterpret_cast<u64(*)(void*)>(v[0x28/8])(s); }
// 0x00000071020d8050
u64 GimmickEventBarrel__load_from_l2c_table_impl(void* s, u64 p1) { void** v=*(void***)((u8*)s+0x0); return reinterpret_cast<u64(*)(void*,u64)>(v[0x38/8])(s,p1); }
// 0x00000071020d8060
u64 GimmickEventBarrel__store_l2c_table_impl(void* s) { void** v=*(void***)((u8*)s+0x0); return reinterpret_cast<u64(*)(void*)>(v[0x28/8])(s); }
// 0x00000071020dcfa0
u64 GimmickEventSpring__load_from_l2c_table_impl(void* s, u64 p1) { void** v=*(void***)((u8*)s+0x0); return reinterpret_cast<u64(*)(void*,u64)>(v[0x38/8])(s,p1); }
// 0x00000071020dcfb0
u64 GimmickEventSpring__store_l2c_table_impl(void* s) { void** v=*(void***)((u8*)s+0x0); return reinterpret_cast<u64(*)(void*)>(v[0x28/8])(s); }
// 0x00000071020df790
u64 GimmickEventPipe__load_from_l2c_table_impl(void* s, u64 p1) { void** v=*(void***)((u8*)s+0x0); return reinterpret_cast<u64(*)(void*,u64)>(v[0x38/8])(s,p1); }
// 0x00000071020df7a0
u64 GimmickEventPipe__store_l2c_table_impl(void* s) { void** v=*(void***)((u8*)s+0x0); return reinterpret_cast<u64(*)(void*)>(v[0x28/8])(s); }
// 0x00000071020e1bb0
u64 GimmickEventTornadoMoveInfo__load_from_l2c_table_impl(void* s, u64 p1) { void** v=*(void***)((u8*)s+0x0); return reinterpret_cast<u64(*)(void*,u64)>(v[0x38/8])(s,p1); }
// 0x00000071020e1bc0
u64 GimmickEventTornadoMoveInfo__store_l2c_table_impl(void* s) { void** v=*(void***)((u8*)s+0x0); return reinterpret_cast<u64(*)(void*)>(v[0x28/8])(s); }
// 0x00000071020e3560
u64 GimmickEventTornadoShootInfo__load_from_l2c_table_impl(void* s, u64 p1) { void** v=*(void***)((u8*)s+0x0); return reinterpret_cast<u64(*)(void*,u64)>(v[0x38/8])(s,p1); }
// 0x00000071020e3570
u64 GimmickEventTornadoShootInfo__store_l2c_table_impl(void* s) { void** v=*(void***)((u8*)s+0x0); return reinterpret_cast<u64(*)(void*)>(v[0x28/8])(s); }
// 0x00000071020e4fe0
u64 GimmickEventTornadoEscape__load_from_l2c_table_impl(void* s, u64 p1) { void** v=*(void***)((u8*)s+0x0); return reinterpret_cast<u64(*)(void*,u64)>(v[0x38/8])(s,p1); }
// 0x00000071020e4ff0
u64 GimmickEventTornadoEscape__store_l2c_table_impl(void* s) { void** v=*(void***)((u8*)s+0x0); return reinterpret_cast<u64(*)(void*)>(v[0x28/8])(s); }
// 0x00000071020e5990
u64 GimmickEventLadder__load_from_l2c_table_impl(void* s, u64 p1) { void** v=*(void***)((u8*)s+0x0); return reinterpret_cast<u64(*)(void*,u64)>(v[0x38/8])(s,p1); }
// 0x00000071020e59a0
u64 GimmickEventLadder__store_l2c_table_impl(void* s) { void** v=*(void***)((u8*)s+0x0); return reinterpret_cast<u64(*)(void*)>(v[0x28/8])(s); }
// 0x00000071020e7920
u64 GimmickEventCatch__load_from_l2c_table_impl(void* s, u64 p1) { void** v=*(void***)((u8*)s+0x0); return reinterpret_cast<u64(*)(void*,u64)>(v[0x38/8])(s,p1); }
// 0x00000071020e7930
u64 GimmickEventCatch__store_l2c_table_impl(void* s) { void** v=*(void***)((u8*)s+0x0); return reinterpret_cast<u64(*)(void*)>(v[0x28/8])(s); }
// 0x00000071020e9440
u64 GimmickEventDrumCheckNeedLock__load_from_l2c_table_impl(void* s, u64 p1) { void** v=*(void***)((u8*)s+0x0); return reinterpret_cast<u64(*)(void*,u64)>(v[0x38/8])(s,p1); }
// 0x00000071020e9450
u64 GimmickEventDrumCheckNeedLock__store_l2c_table_impl(void* s) { void** v=*(void***)((u8*)s+0x0); return reinterpret_cast<u64(*)(void*)>(v[0x28/8])(s); }
// 0x00000071020e9f50
u64 GimmickEventDrumCheckNeedHide__load_from_l2c_table_impl(void* s, u64 p1) { void** v=*(void***)((u8*)s+0x0); return reinterpret_cast<u64(*)(void*,u64)>(v[0x38/8])(s,p1); }
// 0x00000071020e9f60
u64 GimmickEventDrumCheckNeedHide__store_l2c_table_impl(void* s) { void** v=*(void***)((u8*)s+0x0); return reinterpret_cast<u64(*)(void*)>(v[0x28/8])(s); }
// 0x00000071020eabf0
u64 GimmickEventDrumPos__load_from_l2c_table_impl(void* s, u64 p1) { void** v=*(void***)((u8*)s+0x0); return reinterpret_cast<u64(*)(void*,u64)>(v[0x38/8])(s,p1); }
// 0x00000071020eac00
u64 GimmickEventDrumPos__store_l2c_table_impl(void* s) { void** v=*(void***)((u8*)s+0x0); return reinterpret_cast<u64(*)(void*)>(v[0x28/8])(s); }
// 0x00000071020ebd80
u64 GimmickEventDrumShake__load_from_l2c_table_impl(void* s, u64 p1) { void** v=*(void***)((u8*)s+0x0); return reinterpret_cast<u64(*)(void*,u64)>(v[0x38/8])(s,p1); }
// 0x00000071020ebd90
u64 GimmickEventDrumShake__store_l2c_table_impl(void* s) { void** v=*(void***)((u8*)s+0x0); return reinterpret_cast<u64(*)(void*)>(v[0x28/8])(s); }
// 0x00000071020ec730
u64 GimmickEventDrumEscape__load_from_l2c_table_impl(void* s, u64 p1) { void** v=*(void***)((u8*)s+0x0); return reinterpret_cast<u64(*)(void*,u64)>(v[0x38/8])(s,p1); }
// 0x00000071020ec740
u64 GimmickEventDrumEscape__store_l2c_table_impl(void* s) { void** v=*(void***)((u8*)s+0x0); return reinterpret_cast<u64(*)(void*)>(v[0x28/8])(s); }
// 0x00000071020ed0e0
u64 GimmickEventDrumRelease__load_from_l2c_table_impl(void* s, u64 p1) { void** v=*(void***)((u8*)s+0x0); return reinterpret_cast<u64(*)(void*,u64)>(v[0x38/8])(s,p1); }
// 0x00000071020ed0f0
u64 GimmickEventDrumRelease__store_l2c_table_impl(void* s) { void** v=*(void***)((u8*)s+0x0); return reinterpret_cast<u64(*)(void*)>(v[0x28/8])(s); }
// 0x00000071020edbf0
u64 GimmickEventSlashLockInfo__load_from_l2c_table_impl(void* s, u64 p1) { void** v=*(void***)((u8*)s+0x0); return reinterpret_cast<u64(*)(void*,u64)>(v[0x38/8])(s,p1); }
// 0x00000071020edc00
u64 GimmickEventSlashLockInfo__store_l2c_table_impl(void* s) { void** v=*(void***)((u8*)s+0x0); return reinterpret_cast<u64(*)(void*)>(v[0x28/8])(s); }
// 0x00000071020eef10
u64 GimmickEventSlashEscape__load_from_l2c_table_impl(void* s, u64 p1) { void** v=*(void***)((u8*)s+0x0); return reinterpret_cast<u64(*)(void*,u64)>(v[0x38/8])(s,p1); }
// 0x00000071020eef20
u64 GimmickEventSlashEscape__store_l2c_table_impl(void* s) { void** v=*(void***)((u8*)s+0x0); return reinterpret_cast<u64(*)(void*)>(v[0x28/8])(s); }
// 0x00000071020f2e80
u64 LinkEventTouchItem__load_from_l2c_table_impl(void* s, u64 p1) { void** v=*(void***)((u8*)s+0x0); return reinterpret_cast<u64(*)(void*,u64)>(v[0x38/8])(s,p1); }
// 0x00000071020f2e90
u64 LinkEventTouchItem__store_l2c_table_impl(void* s) { void** v=*(void***)((u8*)s+0x0); return reinterpret_cast<u64(*)(void*)>(v[0x28/8])(s); }
// 0x00000071020f4430
u64 Item__start_inhaled_impl(void* s) { void** v=*(void***)((u8*)s+0x0); return reinterpret_cast<u64(*)(void*)>(v[0x70/8])(s); }
// 0x00000071020f4440
u64 Item__end_hooked_impl(void* s) { void** v=*(void***)((u8*)s+0x0); return reinterpret_cast<u64(*)(void*)>(v[0x108/8])(s); }
// 0x00000071020f4450
u64 Item__get_battle_object_id_impl(void* s) { void** v=*(void***)((u8*)s+0x0); return reinterpret_cast<u64(*)(void*)>(v[0x528/8])(s); }
// 0x00000071020f4460
u64 Item__action_impl(void* s, u64 p1) { void** v=*(void***)((u8*)s+0x0); return reinterpret_cast<u64(*)(void*,u64)>(v[0x548/8])(s,p1); }
// 0x0000007102122060
u64 FighterSpiritsSupportSkill__is_unsync_vis_whole_effect_impl(void* s) { void** v=*(void***)((u8*)s+0x0); return reinterpret_cast<u64(*)(void*)>(v[0x148/8])(s); }
// 0x0000007102122370
u64 LinkEventLassoHang__load_from_l2c_table_impl(void* s, u64 p1) { void** v=*(void***)((u8*)s+0x0); return reinterpret_cast<u64(*)(void*,u64)>(v[0x38/8])(s,p1); }
// 0x0000007102122380
u64 LinkEventLassoHang__store_l2c_table_impl(void* s) { void** v=*(void***)((u8*)s+0x0); return reinterpret_cast<u64(*)(void*)>(v[0x28/8])(s); }
// 0x0000007102148ad0
u64 LinkEventYoshiTamagoDamageEffect__load_from_l2c_table_impl(void* s, u64 p1) { void** v=*(void***)((u8*)s+0x0); return reinterpret_cast<u64(*)(void*,u64)>(v[0x38/8])(s,p1); }
// 0x0000007102148ae0
u64 LinkEventYoshiTamagoDamageEffect__store_l2c_table_impl(void* s) { void** v=*(void***)((u8*)s+0x0); return reinterpret_cast<u64(*)(void*)>(v[0x28/8])(s); }
// 0x000000710216b2e0
u64 FighterPikminLinkEventWeaponPikminChangeStatus__load_from_l2c_table_impl(void* s, u64 p1) { void** v=*(void***)((u8*)s+0x0); return reinterpret_cast<u64(*)(void*,u64)>(v[0x38/8])(s,p1); }
// 0x000000710216b2f0
u64 FighterPikminLinkEventWeaponPikminChangeStatus__store_l2c_table_impl(void* s) { void** v=*(void***)((u8*)s+0x0); return reinterpret_cast<u64(*)(void*)>(v[0x28/8])(s); }
// 0x000000710216be00
u64 FighterPikminLinkEventWeaponPikminChangeMotion__load_from_l2c_table_impl(void* s, u64 p1) { void** v=*(void***)((u8*)s+0x0); return reinterpret_cast<u64(*)(void*,u64)>(v[0x38/8])(s,p1); }
// 0x000000710216be10
u64 FighterPikminLinkEventWeaponPikminChangeMotion__store_l2c_table_impl(void* s) { void** v=*(void***)((u8*)s+0x0); return reinterpret_cast<u64(*)(void*)>(v[0x28/8])(s); }
// 0x000000710216cec0
u64 FighterPikminLinkEventWeaponPikminSyncLR__load_from_l2c_table_impl(void* s, u64 p1) { void** v=*(void***)((u8*)s+0x0); return reinterpret_cast<u64(*)(void*,u64)>(v[0x38/8])(s,p1); }
// 0x000000710216ced0
u64 FighterPikminLinkEventWeaponPikminSyncLR__store_l2c_table_impl(void* s) { void** v=*(void***)((u8*)s+0x0); return reinterpret_cast<u64(*)(void*)>(v[0x28/8])(s); }
// 0x000000710216d9e0
u64 FighterPikminLinkEventWeaponPikminSyncPos__load_from_l2c_table_impl(void* s, u64 p1) { void** v=*(void***)((u8*)s+0x0); return reinterpret_cast<u64(*)(void*,u64)>(v[0x38/8])(s,p1); }
// 0x000000710216d9f0
u64 FighterPikminLinkEventWeaponPikminSyncPos__store_l2c_table_impl(void* s) { void** v=*(void***)((u8*)s+0x0); return reinterpret_cast<u64(*)(void*)>(v[0x28/8])(s); }
// 0x000000710216e6b0
u64 FighterPikminLinkEventWeaponPikminConstraint__load_from_l2c_table_impl(void* s, u64 p1) { void** v=*(void***)((u8*)s+0x0); return reinterpret_cast<u64(*)(void*,u64)>(v[0x38/8])(s,p1); }
// 0x000000710216e6c0
u64 FighterPikminLinkEventWeaponPikminConstraint__store_l2c_table_impl(void* s) { void** v=*(void***)((u8*)s+0x0); return reinterpret_cast<u64(*)(void*)>(v[0x28/8])(s); }
// 0x000000710216f3b0
u64 FighterPikminLinkEventWeaponPikminOnFlag__load_from_l2c_table_impl(void* s, u64 p1) { void** v=*(void***)((u8*)s+0x0); return reinterpret_cast<u64(*)(void*,u64)>(v[0x38/8])(s,p1); }
// 0x000000710216f3c0
u64 FighterPikminLinkEventWeaponPikminOnFlag__store_l2c_table_impl(void* s) { void** v=*(void***)((u8*)s+0x0); return reinterpret_cast<u64(*)(void*)>(v[0x28/8])(s); }
// 0x000000710216fed0
u64 FighterPikminLinkEventWeaponPikminSetInt__load_from_l2c_table_impl(void* s, u64 p1) { void** v=*(void***)((u8*)s+0x0); return reinterpret_cast<u64(*)(void*,u64)>(v[0x38/8])(s,p1); }
// 0x000000710216fee0
u64 FighterPikminLinkEventWeaponPikminSetInt__store_l2c_table_impl(void* s) { void** v=*(void***)((u8*)s+0x0); return reinterpret_cast<u64(*)(void*)>(v[0x28/8])(s); }
// 0x0000007102170bd0
u64 FighterPikminLinkEventWeaponPikminSetFloat__load_from_l2c_table_impl(void* s, u64 p1) { void** v=*(void***)((u8*)s+0x0); return reinterpret_cast<u64(*)(void*,u64)>(v[0x38/8])(s,p1); }
// 0x0000007102170be0
u64 FighterPikminLinkEventWeaponPikminSetFloat__store_l2c_table_impl(void* s) { void** v=*(void***)((u8*)s+0x0); return reinterpret_cast<u64(*)(void*)>(v[0x28/8])(s); }
// 0x00000071021718c0
u64 FighterPikminLinkEventWeaponPikminSetPowerMulStatus__load_from_l2c_table_impl(void* s, u64 p1) { void** v=*(void***)((u8*)s+0x0); return reinterpret_cast<u64(*)(void*,u64)>(v[0x38/8])(s,p1); }
// 0x00000071021718d0
u64 FighterPikminLinkEventWeaponPikminSetPowerMulStatus__store_l2c_table_impl(void* s) { void** v=*(void***)((u8*)s+0x0); return reinterpret_cast<u64(*)(void*)>(v[0x28/8])(s); }
// 0x000000710217c490
u64 WeaponRobotHominglaserLinkEventSearch__load_from_l2c_table_impl(void* s, u64 p1) { void** v=*(void***)((u8*)s+0x0); return reinterpret_cast<u64(*)(void*,u64)>(v[0x38/8])(s,p1); }
// 0x000000710217c4a0
u64 WeaponRobotHominglaserLinkEventSearch__store_l2c_table_impl(void* s) { void** v=*(void***)((u8*)s+0x0); return reinterpret_cast<u64(*)(void*)>(v[0x28/8])(s); }
// 0x000000710217d450
u64 WeaponRobotHominglaserLinkEventBurst__load_from_l2c_table_impl(void* s, u64 p1) { void** v=*(void***)((u8*)s+0x0); return reinterpret_cast<u64(*)(void*,u64)>(v[0x38/8])(s,p1); }
// 0x000000710217d460
u64 WeaponRobotHominglaserLinkEventBurst__store_l2c_table_impl(void* s) { void** v=*(void***)((u8*)s+0x0); return reinterpret_cast<u64(*)(void*)>(v[0x28/8])(s); }
// 0x0000007102195b20
u64 FighterRyuLinkEventFinalDeadDamage__load_from_l2c_table_impl(void* s, u64 p1) { void** v=*(void***)((u8*)s+0x0); return reinterpret_cast<u64(*)(void*,u64)>(v[0x38/8])(s,p1); }
// 0x0000007102195b30
u64 FighterRyuLinkEventFinalDeadDamage__store_l2c_table_impl(void* s) { void** v=*(void***)((u8*)s+0x0); return reinterpret_cast<u64(*)(void*)>(v[0x28/8])(s); }
// 0x0000007102196640
u64 FighterRyuLinkEventFinalMoveTarget__load_from_l2c_table_impl(void* s, u64 p1) { void** v=*(void***)((u8*)s+0x0); return reinterpret_cast<u64(*)(void*,u64)>(v[0x38/8])(s,p1); }
// 0x0000007102196650
u64 FighterRyuLinkEventFinalMoveTarget__store_l2c_table_impl(void* s) { void** v=*(void***)((u8*)s+0x0); return reinterpret_cast<u64(*)(void*)>(v[0x28/8])(s); }
// 0x00000071021992c0
u64 FighterCloudLinkEventFinal__load_from_l2c_table_impl(void* s, u64 p1) { void** v=*(void***)((u8*)s+0x0); return reinterpret_cast<u64(*)(void*,u64)>(v[0x38/8])(s,p1); }
// 0x00000071021992d0
u64 FighterCloudLinkEventFinal__store_l2c_table_impl(void* s) { void** v=*(void***)((u8*)s+0x0); return reinterpret_cast<u64(*)(void*)>(v[0x28/8])(s); }
// 0x000000710219f210
u64 FighterInklingLinkEventPaint__load_from_l2c_table_impl(void* s, u64 p1) { void** v=*(void***)((u8*)s+0x0); return reinterpret_cast<u64(*)(void*,u64)>(v[0x38/8])(s,p1); }
// 0x000000710219f220
u64 FighterInklingLinkEventPaint__store_l2c_table_impl(void* s) { void** v=*(void***)((u8*)s+0x0); return reinterpret_cast<u64(*)(void*)>(v[0x28/8])(s); }
// 0x00000071021a2fe0
u64 WeaponShizueFishingrodLinkEventCliff__load_from_l2c_table_impl(void* s, u64 p1) { void** v=*(void***)((u8*)s+0x0); return reinterpret_cast<u64(*)(void*,u64)>(v[0x38/8])(s,p1); }
// 0x00000071021a2ff0
u64 WeaponShizueFishingrodLinkEventCliff__store_l2c_table_impl(void* s) { void** v=*(void***)((u8*)s+0x0); return reinterpret_cast<u64(*)(void*)>(v[0x28/8])(s); }
// 0x00000071021a3b00
u64 WeaponShizueFishingrodLinkEventShoot__load_from_l2c_table_impl(void* s, u64 p1) { void** v=*(void***)((u8*)s+0x0); return reinterpret_cast<u64(*)(void*,u64)>(v[0x38/8])(s,p1); }
// 0x00000071021a3b10
u64 WeaponShizueFishingrodLinkEventShoot__store_l2c_table_impl(void* s) { void** v=*(void***)((u8*)s+0x0); return reinterpret_cast<u64(*)(void*)>(v[0x28/8])(s); }
// 0x00000071021a4620
u64 WeaponShizueFishingrodLinkEventReel__load_from_l2c_table_impl(void* s, u64 p1) { void** v=*(void***)((u8*)s+0x0); return reinterpret_cast<u64(*)(void*,u64)>(v[0x38/8])(s,p1); }
// 0x00000071021a4630
u64 WeaponShizueFishingrodLinkEventReel__store_l2c_table_impl(void* s) { void** v=*(void***)((u8*)s+0x0); return reinterpret_cast<u64(*)(void*)>(v[0x28/8])(s); }
// 0x00000071021a5700
u64 WeaponShizueFishingrodLinkEventCut__load_from_l2c_table_impl(void* s, u64 p1) { void** v=*(void***)((u8*)s+0x0); return reinterpret_cast<u64(*)(void*,u64)>(v[0x38/8])(s,p1); }
// 0x00000071021a5710
u64 WeaponShizueFishingrodLinkEventCut__store_l2c_table_impl(void* s) { void** v=*(void***)((u8*)s+0x0); return reinterpret_cast<u64(*)(void*)>(v[0x28/8])(s); }
// 0x00000071021a6280
u64 LinkEventCaptureFishingrodDamage__load_from_l2c_table_impl(void* s, u64 p1) { void** v=*(void***)((u8*)s+0x0); return reinterpret_cast<u64(*)(void*,u64)>(v[0x38/8])(s,p1); }
// 0x00000071021a6290
u64 LinkEventCaptureFishingrodDamage__store_l2c_table_impl(void* s) { void** v=*(void***)((u8*)s+0x0); return reinterpret_cast<u64(*)(void*)>(v[0x28/8])(s); }
// 0x00000071021aa530
u64 FighterRidleyLinkEventMotion__load_from_l2c_table_impl(void* s, u64 p1) { void** v=*(void***)((u8*)s+0x0); return reinterpret_cast<u64(*)(void*,u64)>(v[0x38/8])(s,p1); }
// 0x00000071021aa540
u64 FighterRidleyLinkEventMotion__store_l2c_table_impl(void* s) { void** v=*(void***)((u8*)s+0x0); return reinterpret_cast<u64(*)(void*)>(v[0x28/8])(s); }
// 0x00000071021aff50
u64 FighterPokemonLinkEventChange__load_from_l2c_table_impl(void* s, u64 p1) { void** v=*(void***)((u8*)s+0x0); return reinterpret_cast<u64(*)(void*,u64)>(v[0x38/8])(s,p1); }
// 0x00000071021aff60
u64 FighterPokemonLinkEventChange__store_l2c_table_impl(void* s) { void** v=*(void***)((u8*)s+0x0); return reinterpret_cast<u64(*)(void*)>(v[0x28/8])(s); }
// 0x00000071022846c0
u64 end_hooked(void* s) { void** v=*(void***)((u8*)s+0x0); return reinterpret_cast<u64(*)(void*)>(v[0x108/8])(s); }

} // namespace app::lua_bind
