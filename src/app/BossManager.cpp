#include "types.h"

// BossManager — operates on BossManager* directly
// Inner struct at [bm + 0x8]; entity list begin/end at [inner + 0x110/0x118]
// Each list entry is 16 bytes (stride 0x10), first 8 bytes = entity handle pointer
// Default entity singleton loaded via adrp 0x7104f73000 + 0xb70

struct BossManager;

extern "C" void FUN_71004e9e30(void*, s32);
extern "C" bool FUN_71004e5780(void*);
extern "C" void FUN_71039c20c0(void*);  // std::__1::__shared_weak_count::__release_weak

// Default entity singleton at 0x7104f73b70 (adrp 0x7104f73000 + #0xb70)
extern "C" u8 DAT_7104f73b70;

namespace app::lua_bind {

#define BVTCALL(obj, off, ...) \
    reinterpret_cast<void(*)(void*, ##__VA_ARGS__)>((*reinterpret_cast<void***>(obj))[(off)/8])(obj, ##__VA_ARGS__)

// 7102145890 — framed loop: notify boss defeat for entries with hash 0x18e
void BossManager__notify_on_boss_defeat_impl(BossManager* bm, s32 id) {
    if (id != 0x4d) return;
    auto* inner = *reinterpret_cast<u8**>(reinterpret_cast<u8*>(bm) + 0x8);
    u8** begin = *reinterpret_cast<u8***>(inner + 0x110);
    u8** end = *reinterpret_cast<u8***>(inner + 0x118);
    for (u8** it = begin; it != end; it = reinterpret_cast<u8**>(reinterpret_cast<u8*>(it) + 0x10)) {
        // Resolve entity: if null or expired, use default singleton
        void* entity;
        void* handle = *reinterpret_cast<void**>(it);
        if (handle && !reinterpret_cast<bool(*)(void*)>((*reinterpret_cast<void***>(handle))[0x10/8])(handle)) {
            entity = *reinterpret_cast<void**>(it);
        } else {
            entity = &DAT_7104f73b70;
        }
        // Check hash == 0x18e
        u32 hash = reinterpret_cast<u32(*)(void*)>((*reinterpret_cast<void***>(entity))[0x30/8])(entity);
        if (hash != 0x18e) continue;
        // Resolve again for action
        void* entity2;
        void* handle2 = *reinterpret_cast<void**>(it);
        if (handle2 && !reinterpret_cast<bool(*)(void*)>((*reinterpret_cast<void***>(handle2))[0x10/8])(handle2)) {
            entity2 = *reinterpret_cast<void**>(it);
        } else {
            entity2 = &DAT_7104f73b70;
        }
        reinterpret_cast<void(*)(void*)>((*reinterpret_cast<void***>(entity2))[0x50/8])(entity2);
    }
}

// 7102145950 — cmp w1,#0x4d; b.ne ret; ldr x0,[x0,#8]; mov w1,#0x18e; b external
void BossManager__notify_on_boss_keyoff_bgm_impl(BossManager* bm, s32 id) {
    if (id != 0x4d) return;
    FUN_71004e9e30(*reinterpret_cast<void**>(reinterpret_cast<u8*>(bm) + 0x8), 0x18e);
}

// 71021457a0 — framed loop: check if any boss SE is stoppable
#ifdef MATCHING_HACK_NX_CLANG
__attribute__((naked))
bool BossManager__is_stoppable_se_impl(BossManager* bm, s32 id) {
    asm("stp x22, x21, [sp, #-0x30]!\n"
        "stp x20, x19, [sp, #0x10]\n"
        "stp x29, x30, [sp, #0x20]\n"
        "add x29, sp, #0x20\n"
        "ldr x20, [x0, #0x8]\n"
        "ldr w8, [x20, #0x100]\n"
        "cmp w8, #4\n"
        "b.ne 90f\n"
        "ldp x19, x21, [x20, #0x110]\n"
        "cmp x19, x21\n"
        "b.eq 90f\n"
        "adrp x22, DAT_7104f73b70\n"
        "add x22, x22, :lo12:DAT_7104f73b70\n"
        // First loop
        "10:\n"
        "ldr x0, [x19]\n"
        "cbz x0, 11f\n"
        "ldr x8, [x0]\n"
        "ldr x8, [x8, #0x10]\n"
        "blr x8\n"
        "tbz w0, #0, 12f\n"
        "11:\n"
        "mov x0, x22\n"
        "b 13f\n"
        "12:\n"
        "ldr x0, [x19]\n"
        "13:\n"
        "ldr x8, [x0]\n"
        "ldr x8, [x8, #0x58]\n"
        "blr x8\n"
        "tbz w0, #0, 90f\n"
        // Check hash
        "ldr x0, [x19]\n"
        "cbz x0, 14f\n"
        "ldr x8, [x0]\n"
        "ldr x8, [x8, #0x10]\n"
        "blr x8\n"
        "tbz w0, #0, 15f\n"
        "14:\n"
        "mov x0, x22\n"
        "b 16f\n"
        "15:\n"
        "ldr x0, [x19]\n"
        "16:\n"
        "ldr x8, [x0]\n"
        "ldr x8, [x8, #0x30]\n"
        "blr x8\n"
        "cmp w0, #0x175\n"
        "b.eq 90f\n"
        "add x19, x19, #0x10\n"
        "cmp x21, x19\n"
        "b.ne 10b\n"
        // Second loop
        "ldp x19, x20, [x20, #0x110]\n"
        "cmp x19, x20\n"
        "b.eq 90f\n"
        "20:\n"
        "mov x0, x19\n"
        "bl FUN_71004e5780\n"
        "tbnz w0, #0, 92f\n"
        "add x19, x19, #0x10\n"
        "cmp x20, x19\n"
        "b.ne 20b\n"
        "90:\n"
        "mov w0, wzr\n"
        "91:\n"
        "ldp x29, x30, [sp, #0x20]\n"
        "ldp x20, x19, [sp, #0x10]\n"
        "ldp x22, x21, [sp], #0x30\n"
        "ret\n"
        "92:\n"
        "orr w0, wzr, #1\n"
        "b 91b\n");
}
#endif

// 7102145970 — iterate boss list by index; if hash==0x18e, clear entry and
// release shared_ptr weak refcount via ldaxr/stlxr loop
#ifdef MATCHING_HACK_NX_CLANG
__attribute__((naked))
void BossManager__notify_on_boss_dead_impl(BossManager* bm, s32 id) {
    asm(
        "str x23, [sp, #-0x40]!\n"
        "stp x22, x21, [sp, #0x10]\n"
        "stp x20, x19, [sp, #0x20]\n"
        "stp x29, x30, [sp, #0x30]\n"
        "add x29, sp, #0x30\n"
        "cmp w1, #0x4d\n"
        "b.ne 9f\n"
        "ldr x20, [x0, #0x8]\n"
        "ldp x8, x9, [x20, #0x110]\n"
        "cmp x9, x8\n"
        "b.eq 9f\n"
        "mov x21, xzr\n"
        "adrp x22, DAT_7104f73b70\n"
        "add x22, x22, :lo12:DAT_7104f73b70\n"
        // Loop: x8=begin, x21=index, x23=&item[x21]
        "0:\n"
        "add x23, x8, x21, lsl #4\n"
        "ldr x0, [x23]\n"
        "cbz x0, 1f\n"
        "ldr x8, [x0]\n"
        "ldr x8, [x8, #0x10]\n"
        "blr x8\n"
        "tbz w0, #0, 2f\n"
        "1:\n"
        "mov x0, x22\n"
        "b 3f\n"
        "2:\n"
        "ldr x0, [x23]\n"
        "3:\n"
        "ldr x8, [x0]\n"
        "ldr x8, [x8, #0x30]\n"
        "blr x8\n"
        "cmp w0, #0x18e\n"
        "b.ne 8f\n"
        // Clear entry, release weak ref
        "ldr x19, [x23, #0x8]\n"
        "stp xzr, xzr, [x23]\n"
        "cbz x19, 8f\n"
        "add x8, x19, #0x8\n"
        // Atomic decrement (ldaxr/stlxr retry loop)
        "4:\n"
        "ldaxr x9, [x8]\n"
        "sub x10, x9, #0x1\n"
        "stlxr w11, x10, [x8]\n"
        "cbnz w11, 4b\n"
        "cbnz x9, 8f\n"
        // Release: vtable[0x10] destructor + FUN_71039c20c0
        "ldr x8, [x19]\n"
        "ldr x8, [x8, #0x10]\n"
        "mov x0, x19\n"
        "blr x8\n"
        "mov x0, x19\n"
        "bl FUN_71039c20c0\n"
        // Loop tail: reload begin/end, advance index, check count
        "8:\n"
        "ldp x8, x9, [x20, #0x110]\n"
        "sub x9, x9, x8\n"
        "add x21, x21, #0x1\n"
        "asr x9, x9, #0x4\n"
        "cmp x9, x21\n"
        "b.hi 0b\n"
        "9:\n"
        "ldp x29, x30, [sp, #0x30]\n"
        "ldp x20, x19, [sp, #0x20]\n"
        "ldp x22, x21, [sp, #0x10]\n"
        "ldr x23, [sp], #0x40\n"
        "ret\n"
    );
}
#endif

} // namespace app::lua_bind
