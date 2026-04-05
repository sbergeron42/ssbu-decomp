#include "types.h"

#define HIDDEN __attribute__((visibility("hidden")))

// ---- External declarations -----------------------------------------------

extern u64 PTR_DAT_71052a4ec0 HIDDEN;
extern u8  PTR_FUN_71052a5728[] HIDDEN;
extern u8  PTR_DAT_71052a5868[] HIDDEN;
extern u8  PTR_DAT_71052a5870[] HIDDEN;
extern u64 PTR_DAT_71052a5970 HIDDEN;
extern u64 PTR_DAT_71052a5d00 HIDDEN;
extern u8  DAT_710449be6f HIDDEN;

extern u64  FUN_71000b1b90();
extern s64  FUN_7100130810(u64, u64);
extern void FUN_71000baa20();
extern void FUN_71000bce50(s64 *, s64);
extern u64  FUN_71000bb680();
extern void FUN_7100156220(s64);
extern void FUN_7100168450(s64, u32);
extern void FUN_710016df20(s64, u64);
extern void FUN_710016e170(s64, u64);
extern void FUN_7100170d50(s64, u64);
extern void FUN_71001712c0(s64, u64);
extern void FUN_71001b1870();
extern void FUN_71001b6a50(s64 *);
extern void FUN_71001b68a0(s64 *, s32);
extern s64  FUN_71001f2ba0(u64, const char *, s32);
extern void FUN_71001dd4a0(s64 *, u64);

// ---- Functions ---------------------------------------------------------------

// 0x7100149540 — Constructor: parent init, clear +0xec/+0xf0, set vtable (128 bytes)
void FUN_7100149540(s64 *this_ptr)
{
    u64 vtable_base;

    FUN_71000baa20();
    vtable_base = PTR_DAT_71052a4ec0;
    *(u8 *)((s64)this_ptr + 0xec) = 0;
    this_ptr[0x1e] = 0;
    *this_ptr = (s64)(vtable_base + 0x10);
}

// 0x7100161d00 — Forwards sub-object at +0x60 to FUN_7100156220 at sub+0xa4c (176 bytes)
void FUN_7100161d00(s64 this_ptr)
{
    FUN_7100156220(*(s64 *)(this_ptr + 0x60) + 0xa4c);
}

// 0x7100168310 — Factory: alloc 0x18-byte object, init with FUN_7100168450 (144 bytes)
s64 FUN_7100168310(u64 param_1, u32 param_2)
{
    u64 heap_id;
    s64 obj;

    heap_id = FUN_71000b1b90();
    obj = FUN_7100130810(0x18, heap_id);
    if (obj != 0) {
        FUN_7100168450(obj, param_2);
    }
    return obj;
}

// 0x710016b5f0 — Factory: alloc 0x70-byte object, init with FUN_710016df20 (144 bytes)
s64 FUN_710016b5f0(u64 param_1)
{
    u64 heap_id;
    s64 obj;

    heap_id = FUN_71000b1b90();
    obj = FUN_7100130810(0x70, heap_id);
    if (obj != 0) {
        FUN_710016df20(obj, param_1);
    }
    return obj;
}

// 0x710016b680 — Factory: alloc 0x70-byte object, init with FUN_71001712c0 (144 bytes)
s64 FUN_710016b680(u64 param_1)
{
    u64 heap_id;
    s64 obj;

    heap_id = FUN_71000b1b90();
    obj = FUN_7100130810(0x70, heap_id);
    if (obj != 0) {
        FUN_71001712c0(obj, param_1);
    }
    return obj;
}

// 0x710016b710 — Factory: alloc 0x310-byte object, init with FUN_710016e170 (144 bytes)
s64 FUN_710016b710(u64 param_1)
{
    u64 heap_id;
    s64 obj;

    heap_id = FUN_71000b1b90();
    obj = FUN_7100130810(0x310, heap_id);
    if (obj != 0) {
        FUN_710016e170(obj, param_1);
    }
    return obj;
}

// 0x710016bbc0 — Factory: alloc 0x68-byte object, init with FUN_7100170d50 (160 bytes)
s64 FUN_710016bbc0(u64 param_1)
{
    u64 heap_id;
    s64 obj;

    heap_id = FUN_71000b1b90();
    obj = FUN_7100130810(0x68, heap_id);
    if (obj != 0) {
        FUN_7100170d50(obj, param_1);
    }
    return obj;
}

// 0x71001a0590 — Connection request handler: check state, compute time delta, set job vtable+name (208 bytes)
u64 FUN_71001a0590(s64 this_ptr)
{
    s32  state;
    s64  time_now;
    s64 *tick_rate_ptr;
    s64  time_elapsed;
    s64  delta_ticks;
    s64  stack_obj[2];

    state = **(s32 **)(this_ptr + 0x78);
    if (state == 1) {
        return 5;
    }
    if (((u32)(state - 2) < 3) &&
        (FUN_71000bce50(stack_obj, (s64)(*(s32 **)(this_ptr + 0x78) + 1)),
         stack_obj[0] != 0)) {
        return 1;
    }
    time_now = *(s64 *)(*(s64 *)(*(s64 *)(this_ptr + 0x70) + 0xa0) + 0x58);
    time_elapsed = *(s64 *)(this_ptr + 0x58);
    tick_rate_ptr = (s64 *)FUN_71000bb680();
    delta_ticks = 0;
    if (*tick_rate_ptr != 0) {
        delta_ticks = (time_now - time_elapsed) / *tick_rate_ptr;
    }
    if (0 < delta_ticks) {
        *(u64 *)(this_ptr + 0x58) = *(u64 *)(*(s64 *)(*(s64 *)(this_ptr + 0x70) + 0xa0) + 0x58);
    }
    *(u8 **)(this_ptr + 0x30) = PTR_FUN_71052a5728;
    *(u64 *)(this_ptr + 0x38) = 0;
    *(const char **)(this_ptr + 0x40) = "ProcessConnectionRequestJob::SendConnectionResponse";
    return 0;
}

// 0x71001d4640 — Returns cached time or computes adjusted time from base + offsets (128 bytes)
s64 FUN_71001d4640(s64 this_ptr)
{
    s64 current_time;

    if (*(s32 *)(this_ptr + 0x28) != 0) {
        return *(s64 *)(this_ptr + 0x20);
    }
    if (*PTR_DAT_71052a5868 == '\0') {
        FUN_71001b6a50(&current_time);
    } else {
        FUN_71001b68a0(&current_time, 0);
    }
    *(s64 *)PTR_DAT_71052a5870 = current_time;
    return ((current_time - *(s64 *)(this_ptr + 0x10)) - *(s64 *)(this_ptr + 0x18)) +
           *(s64 *)(this_ptr + 0x20);
}

// 0x71001d6930 — Grows or shrinks buffer range at +0x10/+0x18 to target size (128 bytes)
s64 FUN_71001d6930(s64 this_ptr, u64 target_size)
{
    s64  buf_start;
    u64  current_size;
    s64 *range_ptr;

    range_ptr = (s64 *)(this_ptr + 0x10);
    buf_start = *range_ptr;
    current_size = (u64)(*(s64 *)(this_ptr + 0x18) - buf_start);
    if (current_size < target_size) {
        FUN_71001dd4a0(range_ptr, target_size - current_size);
        return *range_ptr;
    }
    if (target_size < current_size) {
        *(u64 *)(this_ptr + 0x18) = (u64)buf_start + target_size;
    }
    return buf_start;
}

// 0x71001d76e0 — Destructor: swap to dtor vtable, cleanup if field[2] set, swap to base vtable (160 bytes)
void FUN_71001d76e0(s64 *this_ptr)
{
    *this_ptr = (s64)(PTR_DAT_71052a5d00 + 0x10);
    if (this_ptr[2] != 0) {
        FUN_71001b1870();
    }
    *this_ptr = (s64)(PTR_DAT_71052a5970 + 0x10);
}

// 0x71001e9f20 — Delegates to FUN_71001f2ba0 with DAT string and zero flags (176 bytes)
void FUN_71001e9f20(u64 param_1)
{
    FUN_71001f2ba0(param_1, (const char *)&DAT_710449be6f, 0);
}
