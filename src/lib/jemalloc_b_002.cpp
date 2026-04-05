// jemalloc 5.1.0 — malloc_io.c high-level functions + misc wrappers
// Pool-b decomp: addresses in range 0x71039498e0 — 0x710395f6d0
// jemalloc compiled with optnone-equivalent optimization in NX build

typedef unsigned long long uintmax_t;
typedef long long intmax_t;
typedef unsigned long size_t;
typedef __builtin_va_list va_list;

#define OPTNONE __attribute__((optnone))

extern "C" {

// External declarations
size_t strlen(const char* s);
long write(int fd, const void *buf, size_t count);
void* memcpy(void* dst, const void* src, size_t n);

// Forward declarations for functions in jemalloc_b_001.cpp
size_t FUN_7103954500(char *str, size_t size, const char *format, va_list ap);

// ==========================================================================
// malloc_write_fd — write to stderr
// jemalloc 5.1.0: malloc_io.c (inlined as write(STDERR_FILENO, s, len))
// ==========================================================================

// 0x7103954070 (64 bytes)
OPTNONE void FUN_7103954070(const void *buf, size_t len) {
    int fd = 2;
    long ret = write(fd, buf, len);
    (void)ret;
}

// ==========================================================================
// wrtmessage — default malloc_message callback
// jemalloc 5.1.0: malloc_io.c:72
// ==========================================================================

// 0x7103954030 (64 bytes)
OPTNONE void FUN_7103954030(void *cbopaque, const char *s) {
    FUN_7103954070(s, strlen(s));
}

// ==========================================================================
// malloc_write — write message to stderr (simplified for NX)
// jemalloc 5.1.0: malloc_io.c:83
// ==========================================================================

// 0x7103954000 (48 bytes)
OPTNONE void FUN_7103954000(const char *s) {
    FUN_7103954030(0, s);
}

// ==========================================================================
// malloc_snprintf — formatted print to buffer (variadic wrapper)
// jemalloc 5.1.0: malloc_io.c (after malloc_vsnprintf)
// ==========================================================================

// 0x7103956e30 (208 bytes)
OPTNONE size_t FUN_7103956e30(char *str, size_t size, const char *format, ...) {
    size_t ret;
    va_list ap;

    __builtin_va_start(ap, format);
    ret = FUN_7103954500(str, size, format, ap);
    __builtin_va_end(ap);

    return ret;
}

// ==========================================================================
// malloc_vcprintf — formatted print via callback
// jemalloc 5.1.0: malloc_io.c
// Calls malloc_vsnprintf into 4096-byte buffer, then passes to callback
// ==========================================================================

typedef void (*write_cb_t)(void *, const char *);

// 0x7103956f00 (160 bytes)
OPTNONE void FUN_7103956f00(write_cb_t write_cb, void *cbopaque,
    const char *format, va_list ap) {
    char buf[4096];

    if (write_cb == 0) {
        write_cb = FUN_7103954030;
        cbopaque = 0;
    }
    FUN_7103954500(buf, sizeof(buf), format, ap);
    write_cb(cbopaque, buf);
}

// ==========================================================================
// tsdn_null — check if tsdn is NULL
// jemalloc 5.1.0: tsd.h (tsdn_null inline)
// ==========================================================================

// 0x7103950de0 (32 bytes)
OPTNONE bool FUN_7103950de0(long p) {
    return p == 0;
}

// ==========================================================================
// tsd_tsdn — cast tsd_t* to tsdn_t*
// jemalloc 5.1.0: tsd.h (tsd_tsdn inline)
// ==========================================================================

// 0x7103950e00 (32 bytes)
OPTNONE void* FUN_7103950e00(void *p) {
    return p;
}

} // extern "C"
