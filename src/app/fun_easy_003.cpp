#include "types.h"

// EASY-tier FUN_* functions -- address range 0x7103xxxxxx (and nearby)
// Pool-b worker: manually decompiled from Ghidra

// External globals
extern u8  DAT_7106d4a591 __attribute__((visibility("hidden")));
extern u8  DAT_7106dd40b4 __attribute__((visibility("hidden")));
extern u64 DAT_7106dd3f10 __attribute__((visibility("hidden")));
extern u32 DAT_7106dd3f18 __attribute__((visibility("hidden")));
extern u64 DAT_7106dd45f8 __attribute__((visibility("hidden")));
extern u64 DAT_7106dd4600 __attribute__((visibility("hidden")));

// External labels (vtable/function pointers)
extern u64 PTR_LAB_710517b7c0 __attribute__((visibility("hidden")));
extern u64 PTR_LAB_71051852c8 __attribute__((visibility("hidden")));
extern u64 PTR_LAB_710523e688 __attribute__((visibility("hidden")));

// External functions
extern "C" void jeFree_710392e590(void*);

// ── 0x7101 range noops / simple (grouped here) ───────────────────────────────

// 71031758e0
void FUN_71031758e0(void) {}

// 7103176100
void FUN_7103176100(u64 param_1, u64 *param_2) {
    *param_2 = (u64)&PTR_LAB_710517b7c0;
}

// 7103176110
void FUN_7103176110(void) {}

// 710318c240
void FUN_710318c240(void) {}

// 710318c4d0
void FUN_710318c4d0(void) {}

// ── 0x7103 range ─────────────────────────────────────────────────────────────

// 710337e770
void FUN_710337e770(u64 param_1, u64 *param_2) {
    *param_2 = (u64)&PTR_LAB_71051852c8;
}

// 710337e780
void FUN_710337e780(void) {}

// 71035516e0
void FUN_71035516e0(void) {}

// 71036e8dc0 -- (complex: skipped -- misclassified triage entry)

// 7103715030
void FUN_7103715030(void) {}

// 7103715040
void FUN_7103715040(u64 param_1) { if (param_1 != 0) jeFree_710392e590((void*)param_1); }

// 71037153b0
void FUN_71037153b0(u64 param_1) { if (param_1 != 0) jeFree_710392e590((void*)param_1); }

// 71037160b0
void FUN_71037160b0(u64 param_1) { if (param_1 != 0) jeFree_710392e590((void*)param_1); }

// 7103716590
void FUN_7103716590(u64 param_1) { if (param_1 != 0) jeFree_710392e590((void*)param_1); }

// 7103716830
void FUN_7103716830(u64 param_1) { if (param_1 != 0) jeFree_710392e590((void*)param_1); }

// 7103716980
void FUN_7103716980(u64 param_1) { if (param_1 != 0) jeFree_710392e590((void*)param_1); }

// 7103716ad0
void FUN_7103716ad0(u64 param_1) { if (param_1 != 0) jeFree_710392e590((void*)param_1); }

// 7103716c80
void FUN_7103716c80(u64 param_1) { if (param_1 != 0) jeFree_710392e590((void*)param_1); }

// 7103716dd0
void FUN_7103716dd0(u64 param_1) { if (param_1 != 0) jeFree_710392e590((void*)param_1); }

// 7103716f20
void FUN_7103716f20(u64 param_1) { if (param_1 != 0) jeFree_710392e590((void*)param_1); }

// 7103717070
void FUN_7103717070(u64 param_1) { if (param_1 != 0) jeFree_710392e590((void*)param_1); }

// 7103717230
void FUN_7103717230(u64 param_1) { if (param_1 != 0) jeFree_710392e590((void*)param_1); }

// 7103717550
void FUN_7103717550(u64 param_1) { if (param_1 != 0) jeFree_710392e590((void*)param_1); }

// 710373e050
u32 FUN_710373e050(u64 param_1) { if (param_1 != 0) jeFree_710392e590((void*)param_1); return 0; }

// 7103793ad0
void FUN_7103793ad0(u64 param_1, u64 *param_2) {
    *param_2 = (u64)&PTR_LAB_710523e688;
}

// 71037aeec0
__attribute__((optnone))
void noop_71037aeec0(u64 param_1) {}

// 71037af350
__attribute__((optnone))
void FUN_71037af350(u64 param_1) {}

// 71037b0cd0
__attribute__((optnone))
void FUN_71037b0cd0(u64 param_1) {}

// 71037b0d40
__attribute__((optnone))
u32 FUN_71037b0d40(u64 param_1) { return 1; }

// 71037b1300
__attribute__((optnone))
u32 FUN_71037b1300(u64 param_1) { return 1; }

// 71037b2bb0
__attribute__((optnone))
void FUN_71037b2bb0(u64 param_1) {}

// 71037b4ff0
__attribute__((optnone))
void FUN_71037b4ff0(u64 param_1, u64 param_2) {}

// 71037b9c70
__attribute__((optnone))
void FUN_71037b9c70(u64 param_1) {}

// 71037baef0
__attribute__((optnone))
void FUN_71037baef0(u64 param_1) {}

// 71037baf00
__attribute__((optnone))
void FUN_71037baf00(u64 param_1) {}

// 71037baf10
__attribute__((optnone))
void FUN_71037baf10(u64 param_1) {}

// 71037bc730
__attribute__((optnone))
void FUN_71037bc730(u64 param_1) {}

// 71037c9230
void FUN_71037c9230(void) {}

// 71037fee50
void FUN_71037fee50(void) {}

// 7103800f20
void FUN_7103800f20(void) {}

// 7103801170
void FUN_7103801170(void) {}

// 71038013c0
void FUN_71038013c0(void) {}

// 710380f790
void FUN_710380f790(void) {}

// 710380f920
void FUN_710380f920(void) {}

// 710380fa40
void FUN_710380fa40(void) {}

// 71039296b0
__attribute__((optnone))
void FUN_71039296b0(u64 param_1, u64 param_2) { u64 l0; u64 l1; u64 l2; u64 l3; }

// 7103929450
__attribute__((optnone))
void FUN_7103929450(u64 param_1, u64 param_2) { u64 l0; u64 l1; }

// 7103929640
__attribute__((optnone))
void FUN_7103929640(u64 param_1, u64 param_2) { u64 l0; u64 l1; u64 l2; u64 l3; }

// 7103929690
__attribute__((optnone))
void FUN_7103929690(u64 param_1, u64 param_2) {}

// 710392ae00
void FUN_710392ae00(void) {}

// 710392af80
__attribute__((optnone))
void FUN_710392af80(u64 param_1) {}

// 710392c0f0
__attribute__((optnone))
u16 FUN_710392c0f0(u64 param_1) { return (u16)(param_1 >> 0x30); }

// 710392d9d0
__attribute__((optnone))
u64 FUN_710392d9d0(u64 param_1) { return param_1; }

// 710392da50
void FUN_710392da50(void) { DAT_7106d4a591 = 1; }

// 710392dc20
__attribute__((optnone))
void FUN_710392dc20(u64 param_1, u64 param_2) { u64 l0; u64 l1; }

// 710392fde0
__attribute__((optnone))
void FUN_710392fde0(u64 param_1, u64 param_2) { u64 l0; u64 l1; }

// 710392fe00
__attribute__((optnone))
void FUN_710392fe00(u64 param_1, u64 param_2) { u64 l0; u64 l1; u64 l2; u64 l3; }

// 710392fe50
__attribute__((optnone))
void FUN_710392fe50(u64 param_1, u64 param_2) {}

// 710392fe70
__attribute__((optnone))
void FUN_710392fe70(u64 param_1, u64 param_2) { u64 l0; u64 l1; u64 l2; u64 l3; }

// 710392fe90
__attribute__((optnone))
void FUN_710392fe90(u64 param_1, u64 param_2) { u64 l0; u64 l1; }

// 7103931300
__attribute__((optnone))
u64 FUN_7103931300(u64 param_1) { return param_1; }

// 7103931690
__attribute__((optnone))
u16 FUN_7103931690(u64 param_1) { return (u16)(param_1 >> 0x30); }

// 71039388d0
__attribute__((optnone))
void FUN_71039388d0(u64 param_1, u64 param_2) { u64 l0; u64 l1; }

// 7103938980
__attribute__((optnone))
void FUN_7103938980(u64 param_1, u64 param_2) { u64 l0; u64 l1; u64 l2; u64 l3; }

// 71039389d0
__attribute__((optnone))
void FUN_71039389d0(u64 param_1, u64 param_2) {}

// 71039389f0
__attribute__((optnone))
void FUN_71039389f0(u64 param_1, u64 param_2) { u64 l0; u64 l1; u64 l2; u64 l3; }

// 710393e700
__attribute__((optnone))
void FUN_710393e700(u64 param_1, u64 param_2) { u64 l0; u64 l1; }

// 710393ede0
__attribute__((optnone))
void FUN_710393ede0(u64 param_1, u64 param_2) {}

// 710393fc80
void FUN_710393fc80(void) {}

// 710393fe20
__attribute__((optnone))
u64 FUN_710393fe20(u64 param_1) { return param_1; }

// 7103940490
u32 FUN_7103940490(void) { return (u32)DAT_7106dd40b4; }

// 7103941a30
__attribute__((optnone))
u16 FUN_7103941a30(u64 param_1) { return (u16)(param_1 >> 0x30); }

// 7103943c00
u64 FUN_7103943c00(void) { return DAT_7106dd3f10; }

// 7103944980
bool FUN_7103944980(void) { return DAT_7106dd3f18 != 0; }

// 7103944b90
void FUN_7103944b90(void) {}

// 7103945570
__attribute__((optnone))
void FUN_7103945570(u64 param_1, u64 param_2) { u64 l0; u64 l1; }

// 71039456a0
__attribute__((optnone))
void FUN_71039456a0(u64 param_1, u64 param_2) { u64 l0; u64 l1; }

// 71039456c0
__attribute__((optnone))
void FUN_71039456c0(u64 param_1, u64 param_2) { u64 l0; u64 l1; u64 l2; u64 l3; }

// 7103945710
__attribute__((optnone))
void FUN_7103945710(u64 param_1, u64 param_2) {}

// 7103945730
__attribute__((optnone))
void FUN_7103945730(u64 param_1, u64 param_2) { u64 l0; u64 l1; u64 l2; u64 l3; }

// 7103945fd0
__attribute__((optnone))
void FUN_7103945fd0(void) { u64 l0; u64 l1; }

// 71039461b0
__attribute__((optnone))
void FUN_71039461b0(u64 param_1) {}

// 7103946490
__attribute__((optnone))
u64 FUN_7103946490(u64 param_1) { return param_1; }

// 7103947020
__attribute__((optnone))
void FUN_7103947020(u64 param_1, u64 param_2) { u64 l0; u64 l1; }

// 7103949790
void FUN_7103949790(void) {}

// 7103949910
__attribute__((optnone))
void FUN_7103949910(u64 param_1, u64 param_2) { u64 l0; u64 l1; u64 l2; u64 l3; }

// 7103949960
__attribute__((optnone))
void FUN_7103949960(u64 param_1, u64 param_2) {}

// 7103949980
__attribute__((optnone))
void FUN_7103949980(u64 param_1, u64 param_2) { u64 l0; u64 l1; u64 l2; u64 l3; }

// 710394d130
__attribute__((optnone))
void FUN_710394d130(u64 param_1, u32 param_2) {}

// 710394d1c0
__attribute__((optnone))
void FUN_710394d1c0(u64 param_1, u32 param_2) {}

// 71039514d0
__attribute__((optnone))
void FUN_71039514d0(u64 param_1, u64 param_2) { u64 l0; u64 l1; u64 l2; u64 l3; }

// 7103951540
__attribute__((optnone))
void FUN_7103951540(u64 param_1, u64 param_2) { u64 l0; u64 l1; }

// 7103951590
__attribute__((optnone))
void FUN_7103951590(u64 param_1, u64 param_2) {}

// 71039515b0
__attribute__((optnone))
void FUN_71039515b0(u64 param_1, u64 param_2) { u64 l0; u64 l1; u64 l2; u64 l3; }

// 7103951810
__attribute__((optnone))
u64 FUN_7103951810(u64 param_1) { return param_1; }

// 7103952ee0
__attribute__((optnone))
u16 FUN_7103952ee0(u64 param_1) { return (u16)(param_1 >> 0x30); }

// 7103953d40
__attribute__((optnone))
void FUN_7103953d40(u64 param_1, u64 param_2) { u64 l0; u64 l1; }

// 7103953d60
__attribute__((optnone))
void FUN_7103953d60(u64 param_1, u64 param_2) {}

// 71039575b0
void FUN_71039575b0(void) {}

// 7103957fb0
bool FUN_7103957fb0(void) { return DAT_7106dd3f18 != 0; }

// 7103957fd0
__attribute__((optnone))
void FUN_7103957fd0(u64 param_1) {}

// 71039586b0
__attribute__((optnone))
void FUN_71039586b0(u64 param_1, u64 param_2) { u64 l0; u64 l1; }

// 71039587b0
__attribute__((optnone))
void FUN_71039587b0(u64 param_1, u64 param_2) { u64 l0; u64 l1; u64 l2; u64 l3; }

// 7103958800
__attribute__((optnone))
void FUN_7103958800(u64 param_1, u64 param_2) {}

// 7103958820
__attribute__((optnone))
void FUN_7103958820(u64 param_1, u64 param_2) { u64 l0; u64 l1; u64 l2; u64 l3; }

// 710395b620
__attribute__((optnone))
u64 FUN_710395b620(u64 param_1) { return param_1; }

// 710395bc00
__attribute__((optnone))
void FUN_710395bc00(u64 param_1, u64 param_2) { u64 l0; u64 l1; }

// 710395bc70
__attribute__((optnone))
void FUN_710395bc70(u64 param_1, u64 param_2) { u64 l0; u64 l1; u64 l2; u64 l3; }

// 710395bcc0
__attribute__((optnone))
void FUN_710395bcc0(u64 param_1, u64 param_2) {}

// 710395bce0
__attribute__((optnone))
void FUN_710395bce0(u64 param_1, u64 param_2) { u64 l0; u64 l1; u64 l2; u64 l3; }

// 710395e110
__attribute__((optnone))
u16 FUN_710395e110(u64 param_1) { return (u16)(param_1 >> 0x30); }

// 710395f420
__attribute__((optnone))
void FUN_710395f420(u64 param_1, u64 param_2) { u64 l0; u64 l1; }

// 710395f4d0
__attribute__((optnone))
void FUN_710395f4d0(u64 param_1, u64 param_2) { u64 l0; u64 l1; u64 l2; u64 l3; }

// 710395f520
__attribute__((optnone))
void FUN_710395f520(u64 param_1, u64 param_2) {}

// 710395f540
__attribute__((optnone))
void FUN_710395f540(u64 param_1, u64 param_2) { u64 l0; u64 l1; u64 l2; u64 l3; }

// 710395f880
void FUN_710395f880(void) {}

// 710395fc70
__attribute__((optnone))
u64 FUN_710395fc70(u64 param_1) { return param_1; }

// 71039647e0
// NOTE: binary uses x5 for fn ptr, upstream Clang uses x1 — NX register alloc diff
void FUN_71039647e0(void) {
    typedef void (*fn_t)(u64);
    ((fn_t)DAT_7106dd45f8)(DAT_7106dd4600);
}
