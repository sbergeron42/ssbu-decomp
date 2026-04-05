// jemalloc 5.1.0 — TSD accessors, extent accessors, size utilities
// Pool-b decomp: addresses in range 0x71039498e0 — 0x710395f6d0
// jemalloc compiled with optnone-equivalent optimization in NX build

typedef unsigned long size_t;
typedef unsigned char uint8_t;

#define OPTNONE __attribute__((optnone))

extern "C" {

// Forward declarations for jemalloc internal functions
bool FUN_7103950de0(long p);           // tsdn_null
void* FUN_7103950e00(void *p);         // tsdn_tsd (identity cast)

// ==========================================================================
// TSD accessor chain: tcache_enabled
// jemalloc 5.1.0: tsd.h MALLOC_TSD O() macro expansions
// ==========================================================================

// tsd_tcache_enabledp_get_unsafe: returns pointer to tcache_enabled field
// 0x7103951430 — called by FUN_7103951400
// (not writing this one, it's a simple field offset return)

// tsd_tcache_enabledp_get: wraps unsafe version with assert
// 0x7103951400 — called by FUN_7103951350
void* FUN_7103951400(void *tsd);

// 0x7103951350 (48 bytes) — tsd_tcache_enabled_get
// jemalloc 5.1.0: tsd.h:220 — O(tcache_enabled, bool, bool)
OPTNONE long FUN_7103951350(void *tsd) {
    void *ptr = FUN_7103951400(tsd);
    return *(long *)ptr;
}

// tsd_tcache_enabledp_get variant for tsdn
// 0x71039514f0 — called by FUN_7103951470
void* FUN_71039514f0(void *tsd);

// 0x7103951470 (96 bytes) — tsdn_tcache_enabledp_get
// jemalloc 5.1.0: tsd.h:207 — tsdn_##n##p_get pattern
OPTNONE void* FUN_7103951470(void *tsdn) {
    bool is_null = FUN_7103950de0((long)tsdn);
    if (!is_null) {
        void *tsd = FUN_7103950e00(tsdn);
        return FUN_71039514f0(tsd);
    } else {
        return 0;
    }
}

// ==========================================================================
// TSD accessor chain: tcache
// jemalloc 5.1.0: tsd.h MALLOC_TSD O() macro expansions
// ==========================================================================

// 0x7103951450 — tsd_tcachep_get(tsd)
void FUN_7103951450(long val);

// 0x7103951140 (48 bytes) — tsd_tcache_set (stores tcache at tsd+0x7d80)
// jemalloc 5.1.0: tsd.h:229 — O(tcache, tcache_t, tcache_t)
OPTNONE void FUN_7103951140(long tsd) {
    FUN_7103951450(*(long *)((char*)tsd + 0x7d80));
}

// ==========================================================================
// TSD accessor: arenas_tdata_bypass
// jemalloc 5.1.0: tsd.h MALLOC_TSD O() macro expansions
// ==========================================================================

// 0x7103951c50 — tsd_arenas_tdata_bypassp_get_unsafe
void* FUN_7103951c50(void *tsd);

// 0x7103951c20 — tsd_arenas_tdata_bypassp_get (reads byte, masks &1)
uint8_t FUN_7103951c20(void *tsd);

// 0x7103951920 (80 bytes) — tsd_arenas_tdata_bypass_get
// jemalloc 5.1.0: tsd.h:220 — O(arenas_tdata_bypass, bool, bool)
OPTNONE bool FUN_7103951920(void *tsd) {
    uint8_t val = FUN_7103951c20(tsd);
    return (val & 1) != 0;
}

// ==========================================================================
// TSD accessor: arenas_tdata (gated by bypass check)
// ==========================================================================

// 0x7103951bd0 — tsd_arenas_tdatap_get
void* FUN_7103951bd0(void *tsd);

// 0x7103951970 (80 bytes) — tsd_arenas_tdatap_get gated by bypass
// returns NULL if bypass is set, else returns arenas_tdata pointer
OPTNONE void* FUN_7103951970(void *tsd) {
    bool bypass = FUN_7103951920(tsd);
    if (!bypass) {
        return 0;
    } else {
        return FUN_7103951bd0(tsd);
    }
}

// ==========================================================================
// Extent accessor: slab bit
// jemalloc 5.1.0: extent_inlines.h
// ==========================================================================

// 0x710395d240 — extent field pointer accessor
void* FUN_710395d240(void *extent);

// 0x710395d210 — reads byte from extent, masks &1
uint8_t FUN_710395d210(void *extent);

// 0x710395cf30 (80 bytes) — extent_slab_get
// jemalloc 5.1.0: extent_inlines.h:96
OPTNONE bool FUN_710395cf30(void *extent) {
    uint8_t val = FUN_710395d210(extent);
    return (val & 1) != 0;
}

// ==========================================================================
// Extent accessor: slab_data (gated by slab bit)
// jemalloc 5.1.0: extent_inlines.h
// ==========================================================================

// 0x710395d1e0 — extent_slab_data_get_unsafe
void* FUN_710395d1e0(void *extent);

// 0x710395cf80 (80 bytes) — extent_slab_data_get (conditional)
// Returns slab_data only if extent is a slab
OPTNONE void* FUN_710395cf80(void *extent) {
    bool is_slab = FUN_710395cf30(extent);
    if (!is_slab) {
        return 0;
    } else {
        return FUN_710395d1e0(extent);
    }
}

// ==========================================================================
// sz_s2u — size to usable size
// jemalloc 5.1.0: sz.h:249
// ==========================================================================

// 0x710395d430 — sz_s2u_lookup
size_t FUN_710395d430(size_t size);

// 0x710395d470 — sz_s2u_compute
size_t FUN_710395d470(size_t diff, size_t size);

#define LOOKUP_MAXCLASS 0x1000

// 0x710395d3d0 (96 bytes) — sz_s2u
// jemalloc 5.1.0: sz.h:249
OPTNONE size_t FUN_710395d3d0(size_t size) {
    if (size <= LOOKUP_MAXCLASS) {
        return FUN_710395d430(size);
    }
    return FUN_710395d470(size - LOOKUP_MAXCLASS, size);
}

} // extern "C"
