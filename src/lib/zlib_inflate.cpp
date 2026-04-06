// zlib 1.2.11.f-NINTENDO-SDK-v1 — inflateInit2_
// [derived: Ghidra FUN_71000281d0, 572 bytes]
// zlib: inflate.c — Nintendo SDK fork with inline resets and 0x3f34 state magic

#include "types.h"

typedef void* (*alloc_func)(void* opaque, u32 items, u32 size);
typedef void  (*free_func)(void* opaque, void* address);

struct z_stream {
    void*       next_in;     // +0x00
    u32         avail_in;    // +0x08
    u32         _pad0;       // +0x0C
    u64         total_in;    // +0x10
    void*       next_out;    // +0x18
    u32         avail_out;   // +0x20
    u32         _pad1;       // +0x24
    u64         total_out;   // +0x28
    char*       msg;         // +0x30
    void*       state;       // +0x38
    alloc_func  zalloc;      // +0x40
    free_func   zfree;       // +0x48
    void*       opaque;      // +0x50
    s32         data_type;   // +0x58
    u32         _pad2;       // +0x5C
    u64         adler;       // +0x60
    u64         reserved;    // +0x68
};

struct inflate_state {
    z_stream*   strm;           // +0x000
    u32         status;         // +0x008
    u32         _pad0;          // +0x00C
    s32         wrap;           // +0x010
    u32         flags;          // +0x014
    u32         _pad1a;         // +0x018
    u32         dmax;           // +0x01C
    u64         _pad2;          // +0x020
    u64         check;          // +0x028
    u64         total;          // +0x030
    u32         wbits;          // +0x038
    u32         last;           // +0x03C
    u32         havedict;       // +0x040
    u32         unk_44;         // +0x044
    u64         window;         // +0x048
    u64         hold;           // +0x050
    u32         bits;           // +0x058
    u32         _pad3;          // +0x05C
    u64         _gap60;         // +0x060
    u64         lencode;        // +0x068
    u64         distcode;       // +0x070
    u8          _gap78[0x18];   // +0x078
    u64         next;           // +0x090
    u8          _gap98[0x4C0];  // +0x098
    u8          codes[0x1690];  // +0x558
    u64         sane;           // +0x1BE8
    u8          _end[8];        // +0x1BF0
};

extern alloc_func zcalloc_default;
extern free_func  zcfree_default;

#define NX_INIT_STATE   0x3f34

// FUN_71000281d0 — inflateInit2_ (Nintendo SDK zlib fork)
// Address: 0x71000281d0 (572 bytes)
int FUN_71000281d0(z_stream* strm, int windowBits, const char* version, int stream_size) {
    if (version == (const char*)0)
        return -6;

    if (stream_size != (int)sizeof(z_stream))
        return -6;

    if (*version != '1')
        return -6;

    if (strm == (z_stream*)0)
        return -2;

    alloc_func alloc_fn = strm->zalloc;
    strm->msg = (char*)0;

    if (alloc_fn == (alloc_func)0) {
        strm->zalloc = zcalloc_default;
        strm->opaque = (void*)0;
        alloc_fn = zcalloc_default;
    }
    if (strm->zfree == (free_func)0) {
        strm->zfree = zcfree_default;
    }

    inflate_state* state = (inflate_state*)alloc_fn(strm->opaque, 1, (u32)sizeof(inflate_state));
    if (state == (inflate_state*)0)
        return -4;

    strm->state = state;
    state->strm = strm;
    state->window = 0;
    state->status = NX_INIT_STATE;

    // inflateReset2 — 1st validation (state kept across zfree call, needs callee-saved reg)
    if (strm->zalloc != (alloc_func)0 && strm->zfree != (free_func)0) {
        inflate_state* s = (inflate_state*)strm->state;
        if (s != (inflate_state*)0 && s->strm == strm && (s->status - (u32)NX_INIT_STATE) < 0x20u) {
            int wrap;
            if (windowBits < 0) {
                wrap = 0;
                windowBits = -windowBits;
            } else {
                wrap = (windowBits >> 4) + 5;
                if (windowBits < 48)
                    windowBits &= 15;
            }

            if (windowBits == 0 || (windowBits & ~7) == 8) {
                if (s->window != 0 && s->wbits != (u32)windowBits) {
                    strm->zfree(strm->opaque, (void*)s->window);
                    s->window = 0;
                }
                s->wrap = wrap;
                s->wbits = (u32)windowBits;

                // inflateResetKeep — 2nd validation (no calls, can use caller-saved)
                if (strm->zalloc != (alloc_func)0 && strm->zfree != (free_func)0) {
                    inflate_state* s2 = (inflate_state*)strm->state;
                    if (s2 != (inflate_state*)0 && s2->strm == strm &&
                        (s2->status - (u32)NX_INIT_STATE) < 0x20u) {
                        *(u64*)((char*)s2 + 0x3c) = 0;
                        s2->unk_44 = 0;

                        // inflateReset — 3rd validation (no calls, can use caller-saved)
                        if (strm->zalloc != (alloc_func)0 && strm->zfree != (free_func)0) {
                            inflate_state* s3 = (inflate_state*)strm->state;
                            if (s3 != (inflate_state*)0 && s3->strm == strm &&
                                (s3->status - (u32)NX_INIT_STATE) < 0x20u) {
                                s3->check = 0;
                                strm->total_in = 0;
                                strm->total_out = 0;
                                strm->msg = (char*)0;
                                if (s3->wrap != 0) {
                                    strm->adler = (u64)((u32)s3->wrap & 1);
                                }
                                s3->status = NX_INIT_STATE;
                                u8* codes_ptr = (u8*)s3 + 0x558;
                                s3->dmax = 0x8000;
                                s3->total = 0;
                                s3->next = (u64)codes_ptr;
                                s3->flags = 0;
                                s3->hold = 0;
                                s3->bits = 0;
                                s3->lencode = (u64)codes_ptr;
                                s3->distcode = (u64)codes_ptr;
                                s3->sane = 1;
                                return 0;
                            }
                        }
                    }
                }
            }
        }
    }

    // Cleanup on failure
    strm->zfree(strm->opaque, state);
    strm->state = (void*)0;
    return -2;
}
