// SSBU 13.0.4 — MEDIUM-tier decompilation batch 006
// Address range: 0x71002280d0 – 0x7100254d50
// Worker: pool-b

#include "types.h"

namespace app {
namespace lua_bind {

// Forward declarations for callees
extern "C" {
    void *FUN_7100228110(u64 size);
    u64   FUN_71001b4e00(void *ctx, const char *name);
    void  FUN_71001b4200(void *out, void *in);
    void  FUN_71001b4300(void *dst, void *src);
    long  FUN_71001d6b80(long p);
    void  stdFunctionCleanup_71001b4910(void *p);
    void  FUN_71001d0c80(void *a, void *b, u32 c);
    void  FUN_710024c6d0(void *a, void *b);
    void  FUN_7100228e20(void *a, void *b);
    void  FUN_71001d1960(void *a, void *b, void *c, int d);
    void  FUN_71001cd870(void *p);
    void  FUN_71001d6410(void *p, int v);
    void  FUN_7100230a20(void *p);
    u64   FUN_71001df8c0();
    void  FUN_71001df8d0(void *a, void *b, int c);
    void  FUN_71001df950(void *a, void *b, void *c);
    u32   FUN_710024fb10(void *a, void *b, void *c);
    u32   FUN_710024ff60(void *a, void *b, void *c);
    u32   FUN_7100250180(void *a, void *b, void *c);
    u32   FUN_7100250a20(void *a, void *b, void *c);
    u32   FUN_7100251150(void *a, void *b, void *c, void *d, void *e);
    u32   FUN_71002513c0(void *a, void *b, void *c, void *d, void *e);
    u32   FUN_7100251f10(void *a, void *b, void *c);
    u32   FUN_7100252330(void *a, void *b, void *c);
    long  FUN_710170de70(void *a, void *b, void *c);
    long  FUN_71001b4d20(void *p);
}

// FUN_71002280d0 — bswap64: byte-swap both 32-bit halves and swap positions
u64 FUN_71002280d0(u64 param_1) {
    extern u32 FUN_7100227700(u32);
    u32 lo = FUN_7100227700((u32)param_1);
    u32 hi = FUN_7100227700((u32)(param_1 >> 32));
    return ((u64)lo << 32) | (u64)hi;
}

// FUN_7100228150 — store param_1 and param_2 to globals, set flag if param_1 != 0
static long  DAT_71052b4450;
static void *DAT_71052b4458;
static u32   DAT_71052b4448;

void FUN_7100228150(long param_1, void *param_2) {
    DAT_71052b4450 = param_1;
    DAT_71052b4458 = param_2;
    DAT_71052b4448 = (param_1 != 0) ? 1 : 0;
}

// FUN_7100228180 — allocate 16-byte node via FUN_7100228110, zero it
void FUN_7100228180() {
    u64 *node = (u64 *)FUN_7100228110(0x10);
    if (node) {
        node[0] = 0;
        node[1] = 0;
    }
}

// FUN_7100228250 — allocate 16-byte node, prepend to singly-linked list
// Returns 0 on success, 0xfffffe0c on alloc failure
u64 FUN_7100228250(long *param_1, u64 param_2) {
    u64 *node = (u64 *)FUN_7100228110(0x10);
    if (!node) return 0xfffffe0c;
    node[0] = param_2;
    node[1] = *param_1;
    *param_1 = (long)node;
    if (param_1[1] != 0) return 0;
    param_1[1] = (long)node;
    return 0;
}

// FUN_710022b090 — init node: clear byte at +8, set ptr to PTR+0x10
extern u8 *PTR_DAT_71052a6540;
void FUN_710022b090(long *param_1) {
    *(u8 *)(param_1 + 1) = 0;
    *param_1 = (long)(PTR_DAT_71052a6540 + 0x10);
}

// FUN_710022b140 — stream byte reader with EOF detection and 4-byte skip
void FUN_710022b140(long param_1, long param_2) {
    *(u8 *)(param_2 + 8) = 0;
    if (*(s8 *)(param_1 + 0x69) == 0) {
        long buf   = *(long *)(param_1 + 0x10);
        long *pos  = (long *)(param_1 + 0x18);
        if (*(long *)(buf + 0x18) == *pos) {
            *(u8 *)(param_1 + 8) = 1;
            *(u8 *)(param_2 + 8) = 0;
        } else {
            *(u8 *)(param_2 + 8) = *(u8 *)(*(long *)(buf + 0x10) + *(long *)(buf + 0x28) + *pos);
            *pos = *pos + 1;
        }
        if (*(s8 *)(param_1 + 8) == 0) {
            if ((u64)(*(long *)(*(long *)(param_1 + 0x10) + 0x18) - *(long *)(param_1 + 0x18)) > 3) {
                *(long *)(param_1 + 0x18) = *(long *)(param_1 + 0x18) + 4;
            } else {
                *(u8 *)(param_1 + 8) = 1;
            }
        }
    }
}

// FUN_710022b360 — call FUN_71001b4e00 with string at DAT_71043ab5ee
extern char DAT_71043ab5ee;
void FUN_710022b360(void *param_1, long param_2) {
    FUN_71001b4e00(*(void **)(param_2 + 0x18), &DAT_71043ab5ee);
}

// FUN_710022b510 — read 4 bytes from stream, advance pos; set EOF flag if short
u32 FUN_710022b510(long param_1) {
    long buf  = *(long *)(param_1 + 0x10);
    long pos  = *(long *)(param_1 + 0x18);
    if ((u64)(*(long *)(buf + 0x18) - pos) < 4) {
        *(u8 *)(param_1 + 8) = 1;
        return 0;
    }
    u32 val = *(u32 *)(*(long *)(buf + 0x10) + *(long *)(buf + 0x28) + pos);
    *(long *)(param_1 + 0x18) = pos + 4;
    return val;
}

// FUN_710022b560 — copy 3 u64 from param_2 and store via FUN_71001b4300
void FUN_710022b560(long param_1, u64 *param_2) {
    extern long FUN_71001d6b80(long);
    long lVar1 = FUN_71001d6b80(*(long *)(param_1 + 0x58) + 0x50);
    u64 tmp[3];
    tmp[0] = param_2[0];
    tmp[1] = param_2[1];
    tmp[2] = param_2[2];
    FUN_71001b4300((void *)(lVar1 + 0x40), tmp);
}

// FUN_710022bcf0 — vtable dispatch through double-indirected global at +0x28
extern void **PTR_PTR_DAT_71052a6570;
void FUN_710022bcf0(void *p1, void *p2, void *p3, void *p4) {
    long *base = *(long **)PTR_PTR_DAT_71052a6570;
    typedef void (*Fn)(long *, void *, void *, void *, void *);
    ((Fn)(*(void ***)*PTR_PTR_DAT_71052a6570)[5])((long *)base, p1, p2, p3, p4);
}

// FUN_710022e4b8 — vtable[5] dispatch via param_1+0x58 (returns 1)
u64 FUN_710022e4b8(long param_1) {
    long *mod = *(long **)(param_1 + 0x58);
    typedef void (*Fn)(long *, long);
    ((Fn)(*(void ***)mod)[5])(mod, param_1);
    return 1;
}

// FUN_710022e4e8 — vtable[6] dispatch via param_1+0x58 (returns 1)
u64 FUN_710022e4e8(long param_1) {
    long *mod = *(long **)(param_1 + 0x58);
    typedef void (*Fn)(long *, long);
    ((Fn)(*(void ***)mod)[6])(mod, param_1);
    return 1;
}

// FUN_710022e510 — read 4 bytes from stream (identical to FUN_710022b510)
u32 FUN_710022e510(long param_1) {
    long buf = *(long *)(param_1 + 0x10);
    long pos = *(long *)(param_1 + 0x18);
    if ((u64)(*(long *)(buf + 0x18) - pos) < 4) {
        *(u8 *)(param_1 + 8) = 1;
        return 0;
    }
    u32 val = *(u32 *)(*(long *)(buf + 0x10) + *(long *)(buf + 0x28) + pos);
    *(long *)(param_1 + 0x18) = pos + 4;
    return val;
}

// FUN_710022f060 — copy 3 fields: u8 at +8, u32 at +0xc, u32 at +0x10
void FUN_710022f060(long param_1, long param_2) {
    *(u8  *)(param_1 + 0x08) = *(u8  *)(param_2 + 0x08);
    *(u32 *)(param_1 + 0x0c) = *(u32 *)(param_2 + 0x0c);
    *(u32 *)(param_1 + 0x10) = *(u32 *)(param_2 + 0x10);
}

// FUN_7100230c10 — check flag via FUN_7100230c50; if clear, call FUN_7100230a20
extern u64 FUN_7100230c50();
u64 FUN_7100230c10(void *param_1) {
    u64 v = FUN_7100230c50();
    if (v & 1) return 1;
    FUN_7100230a20(param_1);
    return 0;
}

// FUN_7100231560 — if ptr at +0x30 == 0, return 1, else call FUN_71001df8c0
u64 FUN_7100231560(long param_1) {
    if (*(long *)(param_1 + 0x30) != 0) {
        return FUN_71001df8c0();
    }
    return 1;
}

// FUN_7100231580 — store param_2 at +0x20, then two async subscribe calls
void FUN_7100231580(long param_1, void *param_2, void *param_3) {
    *(void **)(param_1 + 0x20) = param_2;
    FUN_71001df8d0(*(void **)(param_1 + 0x30), param_2, 0);
    void *local = param_2;
    FUN_71001df950(*(void **)(param_1 + 0x30), param_3, &local);
}

// FUN_71002315f0 — replace callback at +0x28: call old vtable[1] if present, store new
void FUN_71002315f0(long param_1, void *param_2) {
    void **old = *(void ***)(param_1 + 0x28);
    if (old) {
        typedef void (*Fn)();
        ((Fn)(*(void ***)old)[1])();
    }
    *(void **)(param_1 + 0x28) = param_2;
}

// FUN_710023bd10 — report error 0x80010002
void FUN_710023bd10(void *param_1) {
    u32 code = 0x80010002;
    FUN_71001b4200(param_1, &code);
}

// FUN_710023bd40 — report error 0x80010002 (duplicate entry)
void FUN_710023bd40(void *param_1) {
    u32 code = 0x80010002;
    FUN_71001b4200(param_1, &code);
}

// FUN_7100240210 — copy 3 u64 from +0x2a0 and call FUN_710023d9c0
extern void FUN_710023d9c0(void *a, void *b);
void FUN_7100240210(long param_1) {
    u64 tmp[3];
    tmp[0] = *(u64 *)(param_1 + 0x2a0);
    tmp[1] = *(u64 *)(param_1 + 0x2a8);
    tmp[2] = *(u64 *)(param_1 + 0x2b0);
    FUN_710023d9c0((void *)param_1, tmp);
}

// FUN_7100243a70 — LDN session state machine (cases 0-4)
// Large function: manages network session connect/disconnect lifecycle
// Uses exclusive-monitor atomics for ref-counting shared connection objects
extern u32   FUN_71001e5e90(long);
extern void *FUN_71001f16c0(long);
extern void  FUN_71001f1bc0(void *, long);
extern long  FUN_71001b52a0(void *);
extern short FUN_71001e5d60(long);
extern char  FUN_71001f2d10(long);
extern void  FUN_71001f1c90(void *);
extern void  FUN_71001e0070(void *, void *);
extern void  FUN_71001eea00(void *, u32);
extern void  FUN_71001f2f60(void **, long);
extern void  FUN_71001f2eb0(void *, void **);
extern void  FUN_71001f1eb0(void *, void *);
extern void  FUN_71001f2d30(void *, u32);
extern void  FUN_71001f2080(void *);
extern long  FUN_71001b1820(u64 size);
extern void  FUN_71001b1870(void *p);
extern void  FUN_71001ced90(long p);
extern void  FUN_71001cef10(void *p);
extern void  FUN_71001ceef0(void *p);
extern long  FUN_71001af850(u64);
extern long  FUN_71001df960(void *a, void *b, void *c, void *d, void *e, void *f, u32 g, int h);
extern long  FUN_7100237b70(long a, void *b, void *c, void *d);
extern long  FUN_7100238090(void *a, void *b, void *c, void *d, void *e);
extern long  FUN_710022f9b0(void *a, void *b, const void *c, void *d, void *e, void *f);
extern void  FUN_71001cf680(long a, void *b);
extern long  FUN_71001cf560(void *a, int *b, int c, int d);
extern u32   FUN_71001b7590(void *);
extern u64   FUN_71001b4280(void *, void *);
extern void *FUN_71001df870_fwd();
extern void  FUN_71001ece20(void *, void *);

extern u8  *PTR_DAT_71052a3d80;
extern u8  *PTR_LAB_71052a6988;
extern u8  *PTR_LAB_71052a6990;
extern u8   DAT_71052b4941;

void FUN_7100243a70(long param_1) {
    switch (*(u32 *)(param_1 + 100)) {
    case 0: {
        long zone = param_1 + 0x350;
        u32 sv = FUN_71001e5e90(zone);
        *(u32 *)(param_1 + 1000) = sv;
        void *conn = FUN_71001f16c0(zone);
        *(void **)(param_1 + 0x3e0) = conn;
        void *name_obj[2] = {};
        FUN_71001f1bc0(name_obj, zone);
        long has_name = FUN_71001b52a0(name_obj);
        short lang    = FUN_71001e5d60(zone);
        if (!has_name || !lang) {
            name_obj[0] = PTR_DAT_71052a3d80 + 0x10;
            stdFunctionCleanup_71001b4910(name_obj);
        } else {
            char use_filter = FUN_71001f2d10(zone);
            name_obj[0] = PTR_DAT_71052a3d80 + 0x10;
            stdFunctionCleanup_71001b4910(name_obj);
            if (use_filter) {
                void *filter[2] = {};
                FUN_71001f1c90(filter);
                void *df = FUN_71001df870_fwd();
                FUN_71001e0070(filter, df);
                u32 fmode = (u32)(u64)FUN_71001f2d10(zone);
                FUN_71001eea00(filter, fmode);
                void *fname[2] = {};
                FUN_71001f2f60((void **)fname, zone);
                FUN_71001f2eb0(filter, fname);
                fname[0] = PTR_DAT_71052a3d80 + 0x10;
                stdFunctionCleanup_71001b4910(fname);
                // build list node
                extern u8 *PTR_DAT_71052a66b8;
                extern u8 *PTR_DAT_71052a66c0;
                u8 flag = 0;
                void *item[10] = {};
                FUN_71001f1c90(item);
                void *label[2] = { PTR_DAT_71052a66c0 + 0x10, 0 };
                FUN_71001ece20(item, filter);
                long *node = (long *)FUN_71001b1820(0x98);
                node[0] = 0;
                FUN_71001f1eb0(node + 4, item);
                node[2] = (long)(PTR_DAT_71052a66b8 + 0x10);
                *(u8 *)(node + 3) = flag;
                *(u32 *)(node + 0x12) = *(u32 *)(param_1 + 1000);
                node[1] = param_1 + 0x2b0;
                node[2] = (long)(PTR_DAT_71052a66c0 + 0x10);
                long prev = *(long *)(param_1 + 0x2b0);
                node[0] = prev;
                *(long **)(prev + 8) = node;
                *(long **)(param_1 + 0x2b0) = node;
                *(long *)(param_1 + 0x2c0) += 1;
                fname[0] = PTR_DAT_71052a66b8 + 0x10;
                FUN_71001f2080(item);
                FUN_71001f2080(filter);
            }
            conn = *(void **)(param_1 + 0x3e0);
        }
        if (!conn && *(s32 *)(param_1 + 1000) == 0) {
            u32 err = 0x80050003;
            void *res[2] = {};
            FUN_71001b4200(res, &err);
            FUN_71001b4300((void *)(param_1 + 0x338), res);
            *(u32 *)(param_1 + 100) = 5;
            FUN_71001cd870((void *)param_1);
        } else {
            *(u32 *)(param_1 + 100) = 2;
        }
        return;
    }
    case 1:
        break;
    case 2: {
        u32 next_state;
        if (!*(long *)(param_1 + 0x3e0) || !*(long *)(param_1 + 0x2c0)) {
            next_state = 1;
        } else {
            long net130 = *(long *)(param_1 + 0x130);
            bool has_peer = false;
            if (net130 && *(long *)(net130 + 0x10)) has_peer = true;
            next_state = has_peer ? 3 : 1;
        }
        *(u32 *)(param_1 + 100) = next_state;
        return;
    }
    case 3: {
        if (!*(long *)(param_1 + 0x2c0)) {
            u32 err = 0x80050003;
            void *res[2] = {};
            FUN_71001b4200(res, &err);
            FUN_71001b4300((void *)(param_1 + 0x338), res);
            *(u32 *)(param_1 + 100) = 5;
            FUN_71001cd870((void *)param_1);
            return;
        }
        long agent   = *(long *)(*(long *)(param_1 + 0x2a0) + 8);
        void *ticket = *(void **)(*(long *)(*(long *)(agent + 0x60) + 0x78) + 0x30);
        // Replace old connect task
        if (*(long **)(param_1 + 0x138)) {
            (*(void(**)())(*(void ***)(*(long *)(param_1 + 0x138)))[1])();
        }
        long task1 = FUN_71001af850(0x30);
        if (task1) FUN_71001ced90(task1);
        *(long *)(param_1 + 0x138) = task1;
        long peer48 = *(long *)(agent + 0x48);
        void *peer_info  = peer48 ? *(void **)(peer48 + 0x10) : 0;
        long net130 = *(long *)(param_1 + 0x130);
        void *user_info  = net130 ? *(void **)(net130 + 0x10) : 0;
        FUN_7100237b70(task1, peer_info, user_info, (void *)(param_1 + 0x148));
        if (*(long **)(param_1 + 0x140)) {
            (*(void(**)())(*(void ***)(*(long *)(param_1 + 0x140)))[1])();
        }
        long task2 = FUN_71001af850(0x30);
        if (task2) FUN_71001ced90(task2);
        *(long *)(param_1 + 0x140) = task2;
        // build pending-send list
        long pending_count = 0;
        void *list_stack[2] = { &list_stack, &list_stack };
        long node_iter = *(long *)(param_1 + 0x2b8);
        while (node_iter != param_1 + 0x2b0) {
            void *item_a[2] = {};
            FUN_71001f1eb0(item_a, (void *)(node_iter + 0x20));
            FUN_71001f2d30(item_a, *(u32 *)(node_iter + 0x90));
            long *pnode = (long *)FUN_71001b1820(0x80);
            pnode[0] = 0;
            FUN_71001f1eb0(pnode + 2, item_a);
            pnode[0] = (long)list_stack[0];
            pnode[1] = (long)&list_stack;
            ((long **)list_stack[1])[1] = (long *)pnode;
            pending_count++;
            node_iter = *(long *)(node_iter + 8);
            list_stack[0] = pnode;
            FUN_71001f2080(item_a);
        }
        // submit to network layer
        void *ctx_ref[1] = { (void *)param_1 };
        FUN_71001d1960((void *)(param_1 + 0x210), PTR_LAB_71052a6990, ctx_ref, 0);
        void *local48 = *(void **)(param_1 + 0x3d8);
        u32 bval = FUN_71001b7590(&local48);
        long ok = FUN_71001df960(ticket, (void *)(param_1 + 0x210),
                                  *(void **)(param_1 + 0x138 + 0x10),
                                  *(void **)(param_1 + 0x140 + 0x10),
                                  list_stack, (void *)(param_1 + 0x2a8), bval, 0);
        if (!(ok & 1)) {
            u32 fail = 0x8001000d;
            void *res[2] = {};
            FUN_71001b4200(res, &fail);
            FUN_71001b4300((void *)(param_1 + 0x338), res);
            *(u32 *)(param_1 + 100) = 4;
            FUN_71001d6410((void *)param_1, 4);
        } else {
            *(u32 *)(param_1 + 100) = 4;
            FUN_71001d6410((void *)param_1, 2);
        }
        return;
    }
    case 4: {
        long *async = *(long **)(param_1 + 0x3f0);
        if (async) {
            // atomic decrement refcount
            volatile int *rc = (volatile int *)(async + 1);
            int old;
            do { old = *rc; } while (!__sync_bool_compare_and_swap(rc, old, old - 1));
            if (old - 1 == 0 && !*((u8 *)async + 0xc)) {
                *((u8 *)async + 0xc) = 1;
                (*(void(**)())(*async + 8))();
            }
            *(long *)(param_1 + 0x3f0) = 0;
        }
        // check success path
        u8 flag = 1;
        u64  ok2 = FUN_71001b4280((void *)(param_1 + 0x338), &flag);
        if (ok2 & 1) {
            FUN_71001ceef0(*(void **)(param_1 + 0x140));
            long t2  = *(long *)(param_1 + 0x140);
            int seq  = *(int  *)(param_1 + 0x148);
            void *buf[1] = {};
            FUN_71001ced90((long)buf);
            FUN_71001cf680(t2, buf);
            int recv_seq;
            long eof_flag;
            if (!*(s8 *)(t2 + 8)) {
                FUN_71001cf560(buf, &recv_seq, 4, 1);
                if (!*(s8 *)&eof_flag && recv_seq == seq + 1) {
                    FUN_71001cef10(buf);
                } else {
                    goto fail_seq;
                }
            } else {
            fail_seq:
                FUN_71001cef10(buf);
                u32 ferr = 0x80050004; // -0x7ffafff6
                void *fres[2] = {};
                FUN_71001b4200(fres, &ferr);
                FUN_71001b4300((void *)(param_1 + 0x338), fres);
            }
            long *agent2 = *(long **)(param_1 + 0x2a0);
            if (agent2) {
                long net130_2 = *(long *)(param_1 + 0x130);
                typedef void (*CbFn)(long *, long);
                ((CbFn)(*(void ***)agent2)[0x23])(agent2,
                    net130_2 ? *(long *)(net130_2 + 0x10) + 0x58 : 0);
            }
        }
        *(u32 *)(param_1 + 100) = 5;
        FUN_71001cd870((void *)param_1);
        return;
    }
    default:
        return;
    }
}

// FUN_7100246338 — delegate to FUN_71001d0c80 with param_1's u32 at +0x90
u64 FUN_7100246338(long param_1, void *param_2, void *param_3) {
    FUN_71001d0c80(param_3, (void *)param_1, *(u32 *)(param_1 + 0x90));
    return 1;
}

// FUN_7100246560 — report error 0x80050001
void FUN_7100246560(void *param_1) {
    u32 code = 0x80050001;
    FUN_71001b4200(param_1, &code);
}

// FUN_7100246590 — report error 0x80050001 (duplicate entry)
void FUN_7100246590(void *param_1) {
    u32 code = 0x80050001;
    FUN_71001b4200(param_1, &code);
}

// FUN_7100248210 — call two helpers sequentially
extern void FUN_7100248160();
void FUN_7100248210() {
    FUN_7100248160();
    extern u64 FUN_71001b1270(u64);
    FUN_71001b1270(0);
}

// FUN_710024a610 — check "AuthenticationInfo" name; if matched, delegate to FUN_710022b360
extern void FUN_710022b360_v(void *, long);
u64 FUN_710024a610(void *param_1, long param_2) {
    u64 matched = FUN_71001b4e00(*(void **)(param_2 + 0x18), "AuthenticationInfo");
    if (matched & 1) return 1;
    FUN_710022b360_v(param_1, param_2);
    return 0;
}

// FUN_710024cc10 — call FUN_71001b4e00 with "Gathering"
void FUN_710024cc10(void *param_1, long param_2) {
    FUN_71001b4e00(*(void **)(param_2 + 0x18), "Gathering");
}

// FUN_710024cc70 — call FUN_710024c6d0(param_2, param_1) then FUN_7100228e20
void FUN_710024cc70(long param_1, long param_2) {
    FUN_710024c6d0((void *)param_2, (void *)param_1);
    if (*(s8 *)(param_2 + 8)) return;
    *(u8 *)(param_1 + 0x60) = 0;
    FUN_7100228e20((void *)param_2, (void *)(param_1 + 0x68));
}

// FUN_710024dfc0 — delegate to FUN_710024fb10 at param_1+0x140, return low bit
u32 FUN_710024dfc0(long param_1, void *param_2, u32 param_3) {
    u32 local = param_3;
    return FUN_710024fb10((void *)(param_1 + 0x140), param_2, &local) & 1;
}

// FUN_710024ff30 — delegate to FUN_710024ff60, return low bit
u32 FUN_710024ff30(long param_1, void *param_2, u32 param_3) {
    u32 local = param_3;
    return FUN_710024ff60((void *)(param_1 + 0x140), param_2, &local) & 1;
}

// FUN_7100250150 — delegate to FUN_7100250180, u64 param, return low bit
u32 FUN_7100250150(long param_1, void *param_2, u64 param_3) {
    u64 local = param_3;
    return FUN_7100250180((void *)(param_1 + 0x140), param_2, &local) & 1;
}

// FUN_71002509f0 — delegate to FUN_7100250a20, return low bit
u32 FUN_71002509f0(long param_1, void *param_2, u32 param_3) {
    u32 local = param_3;
    return FUN_7100250a20((void *)(param_1 + 0x140), param_2, &local) & 1;
}

// FUN_7100251110 — delegate to FUN_7100251150 with 5 params, return low bit
u32 FUN_7100251110(long param_1, void *param_2, u64 param_3, void *param_4, void *param_5) {
    u64 local = param_3;
    return FUN_7100251150((void *)(param_1 + 0x140), param_2, param_5, &local, param_4) & 1;
}

// FUN_7100251380 — delegate to FUN_71002513c0 with 5 params, return low bit
u32 FUN_7100251380(long param_1, void *param_2, u64 param_3, void *param_4, void *param_5) {
    u64 local = param_3;
    return FUN_71002513c0((void *)(param_1 + 0x140), param_2, param_5, &local, param_4) & 1;
}

// FUN_7100251ee0 — delegate to FUN_7100251f10, return low bit
u32 FUN_7100251ee0(long param_1, void *param_2, u32 param_3) {
    u32 local = param_3;
    return FUN_7100251f10((void *)(param_1 + 0x140), param_2, &local) & 1;
}

// FUN_7100252300 — delegate to FUN_7100252330, return low bit
u32 FUN_7100252300(long param_1, void *param_2, u32 param_3) {
    u32 local = param_3;
    return FUN_7100252330((void *)(param_1 + 0x140), param_2, &local) & 1;
}

// FUN_7100254160 — copy u8 at +8; if src != dst, call FUN_710170de70 for rest
long FUN_7100254160(long param_1, long param_2) {
    *(u8 *)(param_1 + 8) = *(u8 *)(param_2 + 8);
    if (param_1 != param_2) {
        FUN_710170de70((void *)(param_1 + 0x10),
                       *(void **)(param_2 + 0x10),
                       (void *)(param_2 + 0x18));
    }
    return param_1;
}

// FUN_71002549d0 — return whether FUN_71001b4d20 on +0x18 is non-null
bool FUN_71002549d0(long param_1) {
    long r = FUN_71001b4d20(*(void **)(param_1 + 0x18));
    return r != 0;
}

// FUN_7100254d50 — packet deserializer: reads fields from stream into output struct
extern void FUN_710024c6d0_v(long a, long b);
extern void FUN_7100255230(long stream, void *out);
extern void FUN_71001d0670(long stream, void *out);
extern void FUN_71001dd4a0(void *buf, int len);
extern u64  FUN_71001d0480(long stream, void *buf, int len);
extern void FUN_71001b0580(void *dst, void *src);
extern void FUN_7100228650(long stream, void *out);
extern void FUN_7100254310(long stream, void *out);

void FUN_7100254d50(long param_1, long param_2) {
    FUN_710024c6d0_v(param_1, param_2); // validate stream header
    if (*(s8 *)(param_1 + 8)) return;

    *(u8 *)(param_2 + 0x60) = 0;

    // Read optional version tag if not in fixed mode
    bool fixed = *(s8 *)(param_1 + 0x69) != 0;
    u32 tag = 0;
    long base_pos = 0;
    u64 remaining;
    if (!fixed) {
        long buf = *(long *)(param_1 + 0x10);
        long *pos = (long *)(param_1 + 0x18);
        long limit = *(long *)(buf + 0x18);
        if (limit == *pos) {
            *(u8 *)(param_1 + 8) = 1;
            *(u8 *)(param_2 + 0x60) = 0;
        } else {
            *(u8 *)(param_2 + 0x60) = *(u8 *)(*(long *)(buf + 0x10) + *(long *)(buf + 0x28) + *pos);
            *pos += 1;
        }
        if (*(s8 *)(param_1 + 8)) return;
        // read 4-byte tag
        buf = *(long *)(param_1 + 0x10);
        long pos2 = *(long *)(param_1 + 0x18);
        remaining = (u64)(*(long *)(buf + 0x18) - pos2);
        if (remaining < 4) goto eof;
        tag = *(u32 *)(*(long *)(buf + 0x10) + *(long *)(buf + 0x28) + pos2);
        base_pos = pos2 + 4;
        *(long *)(param_1 + 0x18) = base_pos;
    } else {
        long pos2 = *(long *)(param_1 + 0x18);
        long buf  = *(long *)(param_1 + 0x10);
        remaining = (u64)(*(long *)(buf + 0x18) - pos2);
    }

    // read u32 at +100
    if (remaining < 4) {
        *(u8 *)(param_1 + 8) = 1;
        *(u32 *)(param_2 + 100) = 0;
        return;
    }
    {
        long buf  = *(long *)(*(long *)(param_1 + 0x10) + 0x10);
        long off  = *(long *)(*(long *)(param_1 + 0x10) + 0x28);
        long pos3 = *(long *)(param_1 + 0x18);
        *(u32 *)(param_2 + 100) = *(u32 *)(buf + off + pos3);
        *(long *)(param_1 + 0x18) = pos3 + 4;
    }

    // read sub-fields
    FUN_7100255230(param_1, (void *)(param_2 + 0x68));
    if (*(s8 *)(param_1 + 8)) return;

    FUN_71001d0670(param_1, (void *)(param_2 + 0x80));
    if (*(s8 *)(param_1 + 8)) return;

    // u32 at +0x84
    {
        long buf  = *(long *)(param_1 + 0x10);
        long pos3 = *(long *)(param_1 + 0x18);
        if ((u64)(*(long *)(buf + 0x18) - pos3) < 4) {
            *(u8 *)(param_1 + 8) = 1;
            *(u32 *)(param_2 + 0x84) = 0;
            return;
        }
        *(u32 *)(param_2 + 0x84) = *(u32 *)(*(long *)(buf + 0x10) + *(long *)(buf + 0x28) + pos3);
        *(long *)(param_1 + 0x18) = pos3 + 4;
    }

    // optional blob at +0x88
    {
        *(void **)(param_2 + 0x90) = *(void **)(param_2 + 0x88);
        long buf  = *(long *)(param_1 + 0x10);
        long pos3 = *(long *)(param_1 + 0x18);
        if ((u64)(*(long *)(buf + 0x18) - pos3) > 3) {
            int blen = *(int *)(*(long *)(buf + 0x10) + *(long *)(buf + 0x28) + pos3);
            *(long *)(param_1 + 0x18) = pos3 + 4;
            if (blen != 0) {
                FUN_71001dd4a0(*(void **)(param_2 + 0x88), blen);
                u64 ok = FUN_71001d0480(param_1, *(void **)(param_2 + 0x88), blen);
                if (!(ok & 1)) {
                    *(void **)(param_2 + 0x90) = *(void **)(param_2 + 0x88);
                }
            }
        }
    }
    if (*(s8 *)(param_1 + 8)) return;

    // u32 at +0xa0
    {
        long buf  = *(long *)(param_1 + 0x10);
        long pos3 = *(long *)(param_1 + 0x18);
        if ((u64)(*(long *)(buf + 0x18) - pos3) < 4) {
            *(u8 *)(param_1 + 8) = 1;
            *(u32 *)(param_2 + 0xa0) = 0;
            return;
        }
        *(u32 *)(param_2 + 0xa0) = *(u32 *)(*(long *)(buf + 0x10) + *(long *)(buf + 0x28) + pos3);
        *(long *)(param_1 + 0x18) = pos3 + 4;
    }

    // byte at +0xa4
    {
        long buf  = *(long *)(param_1 + 0x10);
        long pos3 = *(long *)(param_1 + 0x18);
        if (*(long *)(buf + 0x18) == pos3) {
            *(u8 *)(param_1 + 8) = 1;
            *(u8 *)(param_2 + 0xa4) = 0;
        } else {
            *(u8 *)(param_2 + 0xa4) = *(u8 *)(*(long *)(buf + 0x10) + *(long *)(buf + 0x28) + pos3);
            *(long *)(param_1 + 0x18) = pos3 + 1;
        }
        if (*(s8 *)(param_1 + 8)) return;
    }

    // optional blob at +0xa8
    {
        *(void **)(param_2 + 0xb0) = *(void **)(param_2 + 0xa8);
        long buf  = *(long *)(param_1 + 0x10);
        long pos3 = *(long *)(param_1 + 0x18);
        if ((u64)(*(long *)(buf + 0x18) - pos3) > 3) {
            int blen2 = *(int *)(*(long *)(buf + 0x10) + *(long *)(buf + 0x28) + pos3);
            *(long *)(param_1 + 0x18) = pos3 + 4;
            if (blen2) {
                FUN_71001dd4a0(*(void **)(param_2 + 0xa8), blen2);
                u64 ok2 = FUN_71001d0480(param_1, *(void **)(param_2 + 0xa8), blen2);
                if (!(ok2 & 1)) {
                    *(void **)(param_2 + 0xb0) = *(void **)(param_2 + 0xa8);
                }
            }
        }
    }
    if (*(s8 *)(param_1 + 8)) return;

    // u32 at +0xc0
    {
        long buf  = *(long *)(param_1 + 0x10);
        long pos3 = *(long *)(param_1 + 0x18);
        if ((u64)(*(long *)(buf + 0x18) - pos3) < 4) {
            *(u8 *)(param_1 + 8) = 1;
            *(u32 *)(param_2 + 0xc0) = 0;
            return;
        }
        *(u32 *)(param_2 + 0xc0) = *(u32 *)(*(long *)(buf + 0x10) + *(long *)(buf + 0x28) + pos3);
        *(long *)(param_1 + 0x18) = pos3 + 4;
    }

    FUN_7100254310(param_1, (void *)(param_2 + 200));
    if (*(s8 *)(param_1 + 8)) return;

    // u64 at +0xf0
    {
        long buf  = *(long *)(param_1 + 0x10);
        long pos3 = *(long *)(param_1 + 0x18);
        u64 val8;
        if ((u64)(*(long *)(buf + 0x18) - pos3) < 8) {
            val8 = 0;
            *(u8 *)(param_1 + 8) = 1;
        } else {
            val8 = *(u64 *)(*(long *)(buf + 0x10) + *(long *)(buf + 0x28) + pos3);
            *(long *)(param_1 + 0x18) = pos3 + 8;
        }
        FUN_71001b0580((void *)(param_2 + 0xf0), &val8);
    }
    if (*(s8 *)(param_1 + 8)) return;

    FUN_7100228650(param_1, (void *)(param_2 + 0xf8));
    if (*(s8 *)(param_1 + 8)) return;

    // u32 at +0x120
    {
        long buf  = *(long *)(param_1 + 0x10);
        long pos3 = *(long *)(param_1 + 0x18);
        if ((u64)(*(long *)(buf + 0x18) - pos3) < 4) {
            *(u8 *)(param_1 + 8) = 1;
            *(u32 *)(param_2 + 0x120) = 0;
            return;
        }
        *(u32 *)(param_2 + 0x120) = *(u32 *)(*(long *)(buf + 0x10) + *(long *)(buf + 0x28) + pos3);
        *(long *)(param_1 + 0x18) = pos3 + 4;
    }

    FUN_71001d0670(param_1, (void *)(param_2 + 0x124));
    if (*(s8 *)(param_1 + 8)) return;
    FUN_71001d0670(param_1, (void *)(param_2 + 0x125));
    if (*(s8 *)(param_1 + 8)) return;
    FUN_7100228650(param_1, (void *)(param_2 + 0x128));
    if (*(s8 *)(param_1 + 8)) return;

    // If variable-length mode, align position to tag boundary
    if (!fixed) {
        u64 target = (u64)base_pos + tag;
        u64 cur    = (u64)*(long *)(param_1 + 0x18);
        u64 limit  = (u64)*(long *)(*(long *)(param_1 + 0x10) + 0x18);
        if (cur <= target && target <= limit) {
            *(long *)(param_1 + 0x18) = (long)target;
        }
    }
    return;

eof:
    *(u8 *)(param_1 + 8) = 1;
}

} // namespace lua_bind
} // namespace app
