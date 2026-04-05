// jemalloc 5.1.0 — malloc_io.c helper functions
// Pool-b decomp: addresses in range 0x71039498e0 — 0x710395f6d0
// NOTE: jemalloc was compiled with optnone-equivalent optimization in NX build

// Freestanding type declarations
typedef unsigned long long uintmax_t;
typedef long long intmax_t;
typedef unsigned long size_t;

#define OPTNONE __attribute__((optnone))

extern "C" {

// External declarations
int* __errno_location(void);
void* memcpy(void* dst, const void* src, size_t n);
size_t strlen(const char* s);
void abort(void);

// ==========================================================================
// set_errno wrapper — NX out-of-lines the errno assignment
// jemalloc 5.1.0: malloc_io.h (set_errno macro)
// ==========================================================================

// 0x71039544d0 (48 bytes)
OPTNONE void FUN_71039544d0(int errnum) {
    *__errno_location() = errnum;
}

// ==========================================================================
// u2s — unsigned integer to string
// jemalloc 5.1.0: malloc_io.c:235
// ==========================================================================

#define U2S_BUFSIZE 65  // (1 << (LG_SIZEOF_INTMAX_T + 3)) + 1, LG=3 for 64-bit

// 0x7103956bb0 (464 bytes incl padding)
OPTNONE char* FUN_7103956bb0(uintmax_t x, unsigned base, bool uppercase, char *s,
    size_t *slen_p) {
    unsigned i;

    i = U2S_BUFSIZE - 1;
    s[i] = '\0';
    switch (base) {
    case 10:
        do {
            i--;
            s[i] = "0123456789"[x % (uintmax_t)10];
            x /= (uintmax_t)10;
        } while (x > 0);
        break;
    case 16: {
        const char *digits = (uppercase)
            ? "0123456789ABCDEF"
            : "0123456789abcdef";

        do {
            i--;
            s[i] = digits[x & 0xf];
            x >>= 4;
        } while (x > 0);
        break;
    } default: {
        const char *digits = (uppercase)
            ? "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ"
            : "0123456789abcdefghijklmnopqrstuvwxyz";

        do {
            i--;
            s[i] = digits[x % (uintmax_t)base];
            x /= (uintmax_t)base;
        } while (x > 0);
    }}

    *slen_p = U2S_BUFSIZE - 1 - i;
    return &s[i];
}

// ==========================================================================
// d2s — signed decimal integer to string
// jemalloc 5.1.0: malloc_io.c:277
// ==========================================================================

// 0x7103956a10 (256 bytes)
OPTNONE char* FUN_7103956a10(intmax_t x, char sign, char *s, size_t *slen_p) {
    bool neg;

    if ((neg = (x < 0))) {
        x = -x;
    }
    s = FUN_7103956bb0(x, 10, false, s, slen_p);
    if (neg) {
        sign = '-';
    }
    switch (sign) {
    case '-':
        if (!neg) {
            break;
        }
        /* Fall through. */
    case ' ':
    case '+':
        s--;
        (*slen_p)++;
        *s = sign;
        break;
    default:
        abort();
    }
    return s;
}

// ==========================================================================
// o2s — unsigned octal to string
// jemalloc 5.1.0: malloc_io.c:305
// ==========================================================================

// 0x7103956b10 (160 bytes)
OPTNONE char* FUN_7103956b10(uintmax_t x, bool alt_form, char *s, size_t *slen_p) {
    s = FUN_7103956bb0(x, 8, false, s, slen_p);
    if (alt_form && *s != '0') {
        s--;
        (*slen_p)++;
        *s = '0';
    }
    return s;
}

// ==========================================================================
// x2s — unsigned hex to string
// jemalloc 5.1.0: malloc_io.c:316
// ==========================================================================

// 0x7103956d80 (176 bytes)
OPTNONE char* FUN_7103956d80(uintmax_t x, bool alt_form, bool uppercase, char *s,
    size_t *slen_p) {
    s = FUN_7103956bb0(x, 16, uppercase, s, slen_p);
    if (alt_form) {
        s -= 2;
        (*slen_p) += 2;
        memcpy(s, uppercase ? "0X" : "0x", 2);
    }
    return s;
}

// ==========================================================================
// malloc_strtoumax — string to unsigned integer
// jemalloc 5.1.0: malloc_io.c:114
// ==========================================================================

// 0x71039540b0 (1056 bytes)
OPTNONE uintmax_t FUN_71039540b0(const char *nptr, char **endptr, int base) {
    uintmax_t ret, digit;
    unsigned b;
    bool neg;
    const char *p, *ns;

    p = nptr;
    if (base < 0 || base == 1 || base > 36) {
        ns = p;
        FUN_71039544d0(22); // EINVAL
        ret = ~(uintmax_t)0;
        goto label_return;
    }
    b = base;

    /* Swallow leading whitespace and get sign, if any. */
    neg = false;
    while (true) {
        switch (*p) {
        case '\t': case '\n': case '\v': case '\f': case '\r': case ' ':
            p++;
            break;
        case '-':
            neg = true;
            /* Fall through. */
        case '+':
            p++;
            /* Fall through. */
        default:
            goto label_prefix;
        }
    }

    /* Get prefix, if any. */
    label_prefix:
    ns = p;
    if (*p == '0') {
        switch (p[1]) {
        case '0': case '1': case '2': case '3': case '4': case '5':
        case '6': case '7':
            if (b == 0) {
                b = 8;
            }
            if (b == 8) {
                p++;
            }
            break;
        case 'X': case 'x':
            switch (p[2]) {
            case '0': case '1': case '2': case '3': case '4':
            case '5': case '6': case '7': case '8': case '9':
            case 'A': case 'B': case 'C': case 'D': case 'E':
            case 'F':
            case 'a': case 'b': case 'c': case 'd': case 'e':
            case 'f':
                if (b == 0) {
                    b = 16;
                }
                if (b == 16) {
                    p += 2;
                }
                break;
            default:
                break;
            }
            break;
        default:
            p++;
            ret = 0;
            goto label_return;
        }
    }
    if (b == 0) {
        b = 10;
    }

    /* Convert. */
    ret = 0;
    while ((*p >= '0' && *p <= '9' && (digit = *p - '0') < b)
        || (*p >= 'A' && *p <= 'Z' && (digit = 10 + *p - 'A') < b)
        || (*p >= 'a' && *p <= 'z' && (digit = 10 + *p - 'a') < b)) {
        uintmax_t pret = ret;
        ret *= b;
        ret += digit;
        if (ret < pret) {
            /* Overflow. */
            FUN_71039544d0(34); // ERANGE
            ret = ~(uintmax_t)0;
            goto label_return;
        }
        p++;
    }
    if (neg) {
        ret = (uintmax_t)(-((intmax_t)ret));
    }

    if (p == ns) {
        /* No conversion performed. */
        FUN_71039544d0(22); // EINVAL
        ret = ~(uintmax_t)0;
        goto label_return;
    }

label_return:
    if (endptr != 0) {
        if (p == ns) {
            *endptr = (char *)nptr;
        } else {
            *endptr = (char *)p;
        }
    }
    return ret;
}

} // extern "C"
