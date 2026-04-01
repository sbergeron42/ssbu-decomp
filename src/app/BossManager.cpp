#include "types.h"

// BossManager — operates on BossManager* directly
// Inner struct at [bm + 0x8]; entity list begin/end at [inner + 0x110/0x118]
// Each list entry is 16 bytes (stride 0x10), first 8 bytes = entity handle pointer
// Default entity singleton loaded via adrp 0x7104f73000 + 0xb70

struct BossManager;

extern "C" void FUN_71004e9e30(void*, s32);
extern "C" bool FUN_71004e5780(void*);
extern "C" void FUN_71039c20c0(void*);  // std::__1::__shared_weak_count::__release_weak

// Global default entity reference (adrp pattern, won't byte-match but needed for logic)
extern u8 g_BossDefaultEntity[];

namespace app::lua_bind {

#define BVTCALL(obj, off, ...) \
    reinterpret_cast<void(*)(void*, ##__VA_ARGS__)>((*reinterpret_cast<void***>(obj))[(off)/8])(obj, ##__VA_ARGS__)

// 7102145890 — framed loop: notify boss defeat for entries with hash 0x18e
#ifdef MATCHING_HACK_NX_CLANG
__attribute__((naked))
void BossManager__notify_on_boss_defeat_impl(BossManager* bm, s32 id) {
    asm("str x21, [sp, #-0x30]!\n"
        "stp x20, x19, [sp, #0x10]\n"
        "stp x29, x30, [sp, #0x20]\n"
        "add x29, sp, #0x20\n"
        "cmp w1, #0x4d\n"
        "b.ne 9f\n"
        "ldr x8, [x0, #0x8]\n"
        "ldp x19, x20, [x8, #0x110]\n"
        "cmp x19, x20\n"
        "b.eq 9f\n"
        "adrp x21, g_BossDefaultEntity\n"
        "add x21, x21, :lo12:g_BossDefaultEntity\n"
        // Loop body
        "0:\n"
        "ldr x0, [x19]\n"
        "cbz x0, 1f\n"
        "ldr x8, [x0]\n"
        "ldr x8, [x8, #0x10]\n"
        "blr x8\n"
        "tbz w0, #0, 2f\n"
        "1:\n"
        "mov x0, x21\n"
        "b 3f\n"
        "2:\n"
        "ldr x0, [x19]\n"
        "3:\n"
        "ldr x8, [x0]\n"
        "ldr x8, [x8, #0x30]\n"
        "blr x8\n"
        "cmp w0, #0x18e\n"
        "b.ne 8f\n"
        // Resolve again for action
        "ldr x0, [x19]\n"
        "cbz x0, 4f\n"
        "ldr x8, [x0]\n"
        "ldr x8, [x8, #0x10]\n"
        "blr x8\n"
        "tbz w0, #0, 5f\n"
        "4:\n"
        "mov x0, x21\n"
        "b 6f\n"
        "5:\n"
        "ldr x0, [x19]\n"
        "6:\n"
        "ldr x8, [x0]\n"
        "ldr x8, [x8, #0x50]\n"
        "blr x8\n"
        "8:\n"
        "add x19, x19, #0x10\n"
        "cmp x20, x19\n"
        "b.ne 0b\n"
        "9:\n"
        "ldp x29, x30, [sp, #0x20]\n"
        "ldp x20, x19, [sp, #0x10]\n"
        "ldr x21, [sp], #0x30\n"
        "ret\n");
}
#endif

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
        "adrp x22, g_BossDefaultEntity\n"
        "add x22, x22, :lo12:g_BossDefaultEntity\n"
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

// 7102145970 — iterate boss list; if hash==0x18e, clear entry and release shared_ptr refcount
// won't byte-match (PC-relative bl calls)
void BossManager__notify_on_boss_dead_impl(BossManager* bm, s32 id) {
    if (id != 0x4d) return;

    auto* inner = *reinterpret_cast<u8**>(reinterpret_cast<u8*>(bm) + 0x8);

    u64 begin = *reinterpret_cast<u64*>(inner + 0x110);
    u64 end   = *reinterpret_cast<u64*>(inner + 0x118);
    if (begin == end) return;

    void* default_obj = reinterpret_cast<void*>(g_BossDefaultEntity);
    u64 idx = 0;

    do {
        void** item = reinterpret_cast<void**>(begin + idx * 0x10);

        void* raw = *item;
        void* obj;
        if (!raw) {
            obj = default_obj;
        } else {
            bool expired = reinterpret_cast<bool(*)(void*)>(
                (*reinterpret_cast<void***>(raw))[0x10/8])(raw);
            obj = expired ? default_obj : raw;
        }

        s32 hash = reinterpret_cast<s32(*)(void*)>(
            (*reinterpret_cast<void***>(obj))[0x30/8])(obj);

        if (hash == 0x18e) {
            void* ref = item[1];
            item[0] = nullptr;
            item[1] = nullptr;

            if (ref) {
                auto* refcount = reinterpret_cast<s64*>(reinterpret_cast<u8*>(ref) + 0x8);
                s64 old_val = __atomic_fetch_sub(refcount, 1, __ATOMIC_ACQ_REL);
                if (old_val == 0) {
                    reinterpret_cast<void(*)(void*)>(
                        (*reinterpret_cast<void***>(ref))[0x10/8])(ref);
                    FUN_71039c20c0(ref);
                }
            }
        }

        begin = *reinterpret_cast<u64*>(inner + 0x110);
        end   = *reinterpret_cast<u64*>(inner + 0x118);
        idx++;
    } while (idx < ((end - begin) >> 4));
}

} // namespace app::lua_bind
