#include "types.h"
#include "app/placeholders/UnkType_7103974820.h"

// External functions
extern void FUN_71039839d0(void*, s32, s32);

// External vtable pointers for copy constructors
extern u64 PTR_LAB_71051824c0 __attribute__((visibility("hidden")));
extern u64 PTR_LAB_71051825a8 __attribute__((visibility("hidden")));
extern u64 DAT_7105184ee8 __attribute__((visibility("hidden")));

// ── FUN_71032db1c0 — struct copy with vtable initialization ─────────────────
// 0x71032db1c0  32 bytes  MEDIUM
// Copy constructor: sets vtable to PTR_LAB_71051824c0, copies 3 u64 fields
// from source (offsets +8, +0x10, +0x18) to dest (offsets +8, +0x10, +0x18).
// [derived: 8-instruction leaf, adrp+add for vtable, ldp/stp for field pairs]

void FUN_71032db1c0(u64* src, u64* dst)
{
    *dst = (u64)&PTR_LAB_71051824c0;
    u64 v1 = src[1];
    u64 v2 = src[2];
    u64 v3 = src[3];
    dst[1] = v1;
    dst[2] = v2;
    dst[3] = v3;
}

// ── FUN_71032e5c20 — struct copy with vtable initialization ─────────────────
// 0x71032e5c20  32 bytes  MEDIUM
// Same pattern as FUN_71032db1c0, vtable is PTR_LAB_71051825a8.

void FUN_71032e5c20(u64* src, u64* dst)
{
    *dst = (u64)&PTR_LAB_71051825a8;
    u64 v1 = src[1];
    u64 v2 = src[2];
    u64 v3 = src[3];
    dst[1] = v1;
    dst[2] = v2;
    dst[3] = v3;
}

// ── FUN_7103378c00 — struct copy with vtable initialization ─────────────────
// 0x7103378c00  32 bytes  MEDIUM
// Same pattern as FUN_71032db1c0, vtable is DAT_7105184ee8.

void FUN_7103378c00(u64* src, u64* dst)
{
    *dst = (u64)&DAT_7105184ee8;
    u64 v1 = src[1];
    u64 v2 = src[2];
    u64 v3 = src[3];
    dst[1] = v1;
    dst[2] = v2;
    dst[3] = v3;
}

// ── FUN_7103974820 — conditional field clearing with optional dispatch ───────
// 0x7103974820  100 bytes  EASY
// If param_2 is nonzero, dispatches to FUN_71039839d0 and returns 0.
// Otherwise clears field_0x510 and conditionally clears fields at 0x6e-0x70
// based on boolean flags at 0x6f, 0x70, 0x85 and int at 0x234.
// [derived: shrink-wrapped — no frame in the param_2==0 path]

u64 FUN_7103974820(UnkType_7103974820* self, s32 param_2)
{
    if (param_2 != 0) {
        FUN_71039839d0(self, param_2, 0);
        return 0;
    }
    self->field_0x510 = 0;
    if (self->field_0x6f != 0 || self->field_0x85 != 0) {
        if (self->field_0x70 == 0 &&
            (self->field_0x85 == 0 || self->field_0x234 != 0)) {
            *(u16*)&self->field_0x6e = 0;
            self->field_0x70 = 0;
        }
        return 0;
    }
    self->field_0x6e = 0;
    return 0;
}

