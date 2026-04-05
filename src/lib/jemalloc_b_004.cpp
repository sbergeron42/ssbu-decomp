// jemalloc 5.1.0 — ctl.c handler functions (CTL_RO_NL_GEN expansions + arenas_create_ctl)
// Pool-b decomp: addresses in range 0x71039498e0 — 0x710395f6d0
// jemalloc compiled with optnone-equivalent optimization in NX build

typedef unsigned long size_t;
typedef long ssize_t;

#define OPTNONE __attribute__((optnone))

extern "C" {

// External declarations
void* memcpy(void* dst, const void* src, size_t n);

// jemalloc error codes (POSIX errno values)
#define EPERM   1
#define EAGAIN  11
#define EINVAL  22

// Forward declarations for jemalloc internal functions
void* FUN_7103946490(void *tsd);               // tsd_tsdn
void  FUN_7103946e10(void *tsdn, void *mutex);  // malloc_mutex_lock
void  FUN_7103946f70(void *tsdn, void *mutex);  // malloc_mutex_unlock

// Global variables (resolved by linker, addresses won't match but logic will)
extern unsigned opt_narenas;                     // DAT_7106dd3fe8
extern size_t opt_max_background_threads;        // DAT_7106dd40a8
extern void *ctl_mtx;                            // mutex for ctl operations
extern void *extent_hooks_default;               // PTR_FUN_71052935a0

// ==========================================================================
// CTL_RO_NL_GEN macro expansion template:
//   READONLY check → set oldval → READ into output buffer → return 0
// jemalloc 5.1.0: ctl.c:1441
// ==========================================================================

// 0x710394a490 (256 bytes) — arenas_page_ctl
// jemalloc 5.1.0: ctl.c:2426 — CTL_RO_NL_GEN(arenas_page, PAGE, size_t)
// PAGE = 0x10000 (64KB on NX)
OPTNONE int FUN_710394a490(void *tsd, const size_t *mib, size_t miblen,
    void *oldp, size_t *oldlenp, void *newp, size_t newlen) {
    int ret;
    size_t oldval;

    // READONLY()
    if (newp != 0 || newlen != 0) {
        ret = EPERM;
        goto label_return;
    }

    oldval = 0x10000; // PAGE

    // READ(oldval, size_t)
    if (oldp != 0 && oldlenp != 0) {
        if (*oldlenp != sizeof(size_t)) {
            size_t copylen = (sizeof(size_t) <= *oldlenp)
                ? sizeof(size_t) : *oldlenp;
            memcpy(oldp, (void *)&oldval, copylen);
            ret = EINVAL;
            goto label_return;
        }
        *(size_t *)oldp = oldval;
    }

    ret = 0;
label_return:
    return ret;
}

// 0x710394a7a0 (528 bytes) — opt_narenas_ctl
// jemalloc 5.1.0: ctl.c:1660 — CTL_RO_NL_GEN(opt_narenas, opt_narenas, unsigned)
OPTNONE int FUN_710394a7a0(void *tsd, const size_t *mib, size_t miblen,
    void *oldp, size_t *oldlenp, void *newp, size_t newlen) {
    int ret;
    unsigned oldval;

    // READONLY()
    if (newp != 0 || newlen != 0) {
        ret = EPERM;
        goto label_return;
    }

    oldval = opt_narenas;

    // READ(oldval, unsigned)
    if (oldp != 0 && oldlenp != 0) {
        if (*oldlenp != sizeof(unsigned)) {
            size_t copylen = (sizeof(unsigned) <= *oldlenp)
                ? sizeof(unsigned) : *oldlenp;
            memcpy(oldp, (void *)&oldval, copylen);
            ret = EINVAL;
            goto label_return;
        }
        *(unsigned *)oldp = oldval;
    }

    ret = 0;
label_return:
    return ret;
}

// 0x710394a590 (528 bytes) — opt_max_background_threads_ctl
// jemalloc 5.1.0: ctl.c:1664 — CTL_RO_NL_GEN(opt_max_background_threads, opt_max_background_threads, size_t)
OPTNONE int FUN_710394a590(void *tsd, const size_t *mib, size_t miblen,
    void *oldp, size_t *oldlenp, void *newp, size_t newlen) {
    int ret;
    size_t oldval;

    // READONLY()
    if (newp != 0 || newlen != 0) {
        ret = EPERM;
        goto label_return;
    }

    oldval = opt_max_background_threads;

    // READ(oldval, size_t)
    if (oldp != 0 && oldlenp != 0) {
        if (*oldlenp != sizeof(size_t)) {
            size_t copylen = (sizeof(size_t) <= *oldlenp)
                ? sizeof(size_t) : *oldlenp;
            memcpy(oldp, (void *)&oldval, copylen);
            ret = EINVAL;
            goto label_return;
        }
        *(size_t *)oldp = oldval;
    }

    ret = 0;
label_return:
    return ret;
}

// ==========================================================================
// arenas_create_ctl — creates a new arena
// jemalloc 5.1.0: ctl.c:2453
// ==========================================================================

// Forward declarations
int FUN_710394b510(void *tsd, void *extent_hooks);  // ctl_arena_init

// 0x710394a9b0 (896 bytes) — arenas_create_ctl
// jemalloc 5.1.0: ctl.c:2453-2474
OPTNONE int FUN_710394a9b0(void *tsd, const size_t *mib, size_t miblen,
    void *oldp, size_t *oldlenp, void *newp, size_t newlen) {
    int ret;
    void *extent_hooks;
    unsigned arena_ind;

    void *tsdn = FUN_7103946490(tsd);   // tsd_tsdn(tsd)
    FUN_7103946e10(tsdn, &ctl_mtx);     // malloc_mutex_lock(tsdn, &ctl_mtx)

    extent_hooks = &extent_hooks_default;

    // WRITE(extent_hooks, extent_hooks_t *)
    if (newp != 0) {
        if (newlen != sizeof(void*)) {
            ret = EINVAL;
            goto label_return;
        }
        extent_hooks = *(void **)newp;
    }

    arena_ind = (unsigned)FUN_710394b510(tsd, extent_hooks);
    if (arena_ind == 0xFFFFFFFF) {  // UINT_MAX
        ret = EAGAIN;
        goto label_return;
    }

    // READ(arena_ind, unsigned)
    if (oldp != 0 && oldlenp != 0) {
        if (*oldlenp != sizeof(unsigned)) {
            size_t copylen = (sizeof(unsigned) <= *oldlenp)
                ? sizeof(unsigned) : *oldlenp;
            memcpy(oldp, (void *)&arena_ind, copylen);
            ret = EINVAL;
            goto label_return;
        }
        *(unsigned *)oldp = arena_ind;
    }

    ret = 0;
label_return:
    tsdn = FUN_7103946490(tsd);         // tsd_tsdn(tsd)
    FUN_7103946f70(tsdn, &ctl_mtx);     // malloc_mutex_unlock(tsdn, &ctl_mtx)
    return ret;
}

// ==========================================================================
// ctl_arena_init — initialize a new arena, reusing destroyed slots
// jemalloc 5.1.0: ctl.c:885-912
// ==========================================================================

// Forward declarations
void* FUN_7103949550(void *tsd, int arena_ind, int p3, int p4);  // arenas_i_impl
void* FUN_71039298a0(void *tsdn, int arena_ind, void *extent_hooks);  // arena_init

// ctl_arenas struct: +0x8 = narenas, +0x10 = destroyed list head
extern void *ctl_arenas_ptr;  // DAT_7106dd3fb8

// 0x710394b510 (896 bytes) — ctl_arena_init
// jemalloc 5.1.0: ctl.c:885-912
OPTNONE int FUN_710394b510(void *tsd, void *extent_hooks) {
    int arena_ind;
    long *ctl_arenas = (long *)ctl_arenas_ptr;
    int *destroyed_head_ptr;

    // Check destroyed list (ql_last at ctl_arenas+0x10)
    if (*(long *)(ctl_arenas + 2) == 0) {   // ctl_arenas->destroyed == NULL
        destroyed_head_ptr = 0;
    } else {
        // ql_last: get last element via head->prev
        destroyed_head_ptr = *(int **)(*(long *)(ctl_arenas + 2) + 0x10);
    }

    if (destroyed_head_ptr == 0) {
        // No destroyed arenas — use narenas
        arena_ind = *(int *)(ctl_arenas + 1);  // ctl_arenas->narenas
    } else {
        // Reuse destroyed arena slot — ql_remove
        if (*(int **)((long)ctl_arenas + 0x10) == destroyed_head_ptr) {
            *(long *)((long)ctl_arenas + 0x10) = *(long *)(*(long *)((long)ctl_arenas + 0x10) + 8);
        }
        if (*(int **)((long)ctl_arenas + 0x10) == destroyed_head_ptr) {
            *(long *)((long)ctl_arenas + 0x10) = 0;
        } else {
            *(long *)(*(long *)(destroyed_head_ptr + 4) + 8) = *(long *)(destroyed_head_ptr + 2);
            *(long *)(*(long *)(destroyed_head_ptr + 2) + 0x10) = *(long *)(destroyed_head_ptr + 4);
            *(int **)(destroyed_head_ptr + 2) = destroyed_head_ptr;
            *(int **)(destroyed_head_ptr + 4) = destroyed_head_ptr;
        }
        arena_ind = *destroyed_head_ptr;
    }

    // Try to allocate arena stats
    long result = (long)FUN_7103949550(tsd, arena_ind, 0, 1);
    if (result == 0) {
        return -1;  // UINT_MAX
    }

    // Initialize the arena
    void *tsdn = FUN_7103946490(tsd);
    long arena = (long)FUN_71039298a0(tsdn, arena_ind, extent_hooks);
    if (arena == 0) {
        return -1;  // UINT_MAX
    }

    // If this is a new arena (not reused), bump narenas
    if (arena_ind == *(int *)(ctl_arenas + 1)) {
        *(int *)(ctl_arenas + 1) = *(int *)(ctl_arenas + 1) + 1;
    }

    return arena_ind;
}

} // extern "C"
