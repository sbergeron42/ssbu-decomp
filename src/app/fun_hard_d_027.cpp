// HARD-tier FUN_* functions � 0x7100 address range, batch hard-d-026
// Pool-d worker: WorkModule::RndFloat, ItemModule::GetHaveItemSize,
//   NexNatServerAddressResolveJob step, nn::pia session slot array ctor,
//   nn::vfx stripe reset, nn::vfx::EmitterResource::Setup,
//   nn::vfx stripe slot allocator, GroundModule::GetRightPos

#include "types.h"

#define HIDDEN __attribute__((visibility("hidden")))

// ---------------------------------------------------------------------------
// External data
// ---------------------------------------------------------------------------

// Xorshift128 PRNG state block pointer-to-pointer (WorkModule::RndFloat)
extern void **DAT_71052c15b0     HIDDEN;
// 1.0f used as range epsilon in RndFloat
extern float  DAT_7104470b4c     HIDDEN;
// RAND_STEP = 1/2^32
extern float  RAND_STEP          HIDDEN;  // DAT_7104471710

// NexNat singleton / jump-table pointers
extern void  *PTR_s_pInstance_71052a2d88 HIDDEN;
extern void  *PTR_s_pInstance_71052a2c70 HIDDEN;
extern void  *PTR_LAB_71052a2f50         HIDDEN;
extern void  *PTR_LAB_71052a2f68         HIDDEN;

// nn::pia vtable stubs for session slot objects
extern void  *PTR_DAT_71052a2f90 HIDDEN;
extern void  *PTR_DAT_71052a2f98 HIDDEN;

// ---------------------------------------------------------------------------
// External functions
// ---------------------------------------------------------------------------

extern "C" void *memset(void *dst, int c, u64 n);

extern u64  FUN_71000c36d0(void *instance);   // NexNat availability check

namespace nn { namespace pia { namespace common {
    void *HeapManager_GetHeap();
}}}
namespace pead {
    void *allocateFromSeadHeap(u64 size, void *heap);
}
extern void FUN_7100112710(s64 *obj);  // init nn::pia peer-session slot

extern s64  FUN_71000339f0(void *handle);  // nn::vfx pixel buffer lock
extern void FUN_7100033a10(void *handle);  // nn::vfx pixel buffer unlock
extern u64  FUN_710008a850(void *emitterRes, void *resData);  // EmitterResource bind

namespace Resource {
    void *GetG3dPrimitive(void *pResource, u64 index);
}
namespace detail {
    namespace ShaderManager {
        void *GetShader(void *shaderRes, s32 idx);
    }
    void OutputWarning(const char *msg);
}
namespace nn { namespace vfx { namespace detail {
    void Warning(void *ctx, u32 flags);
    void OutputWarning(const char *msg);
}}}

// ============================================================================
// 1. WorkModule::RndFloat
//    13.0.4 address: 0x71004e5400   13.0.1 entry: 0x71004e4480   size: 112 B
//    Xorshift128 PRNG step, scale result to [lo, hi), call this->SetFloat(result, id).
// ============================================================================
namespace app {

void WorkModule_RndFloat(void *self, float lo, float hi, s32 id)
{
    float eps = DAT_7104470b4c;  // 1.0f
    if (lo > hi) return;
    if (hi != lo) {
        void **ppState = (void **)DAT_71052c15b0;
        s64    state   = *(s64 *)*ppState;

        u32 w = *(u32 *)(state + 0x20);
        *(s32 *)(state + 0x24) += 1;

        u32 t = *(u32 *)(state + 0x14);
        t ^= t << 0xb;
        *(u32 *)(state + 0x14) = *(u32 *)(state + 0x18);
        t ^= (t >> 8) ^ w ^ (w >> 0x13);
        *(u32 *)(state + 0x18) = *(u32 *)(state + 0x1c);
        *(u32 *)(state + 0x1c) = w;
        *(u32 *)(state + 0x20) = t;

        // Map to [lo, hi+eps): ((hi - lo + 1.0) * rand * step) + lo
        hi = ((hi - lo) + eps) * (float)t * RAND_STEP + lo;
    }
    // vtable call: this->SetFloat(hi, id)
    void ***vtbl = (void ***)self;
    ((void (*)(void *, float, s32))(*vtbl)[0])(self, hi, id);
}

} // namespace app

// ============================================================================
// 2. ItemModule::GetHaveItemSize
//    13.0.4 address: 0x7100472bc0   13.0.1 entry: 0x7100471ac0   size: 112 B
//    Returns the s32 size field for the have-item at the given slot index.
// ============================================================================
namespace app {

s32 ItemModule_GetHaveItemSize(void *self, s32 slot)
{
    // field_0x18 -> have-item array; stride 0x20; +0x14 = size
    s64 table = *(s64 *)((u8 *)self + 0x18);
    return *(s32 *)(table + (s64)slot * 0x20 + 0x14);
}

} // namespace app

// ============================================================================
// 3. NexNatServerAddressResolveJob step function
//    13.0.4 address: 0x71000d3110   13.0.1 entry: 0x71000d3050   size: 112 B
//    Note: 0x71000d3110 is an interior instruction in the 13.0.1 function.
//    Checks pia readiness and relay state; drives address resolve state machine.
//    Returns: 5 = StepComplete, 7 = StepResolveRelayServerSetting
// ============================================================================
namespace nn { namespace nex {

u64 NexNatServerAddressResolveJob_Step(s64 job)
{
    void *inst = PTR_s_pInstance_71052a2d88;

    u64 ready = FUN_71000c36d0(*(void **)PTR_s_pInstance_71052a2d88);
    if ((ready & 1) != 0) {
        u64 threshold = *(u64 *)(*(s64 *)PTR_s_pInstance_71052a2c70 + 0x30);
        u64 cur       = *(u64 *)(job + 0x60);
        if (threshold <= cur) {
            // vtable[+0x88][+0x40] � IsReady()
            s64 vobj = *(s64 *)*(s64 *)((s64)inst + 0x88);
            u64 ok   = (**(u64 (**)())(vobj + 0x40))();
            if ((ok & 1) == 0) {
                return 5;
            }
            // vtable[+0x88][+0x48] � GetResult(int[4])
            s32 result[4];
            (**(void (**)(s32 *))(*(s64 *)*(s64 *)((s64)inst + 0x88) + 0x48))(result);
            if (result[0] == 0) {
                s64 relayObj = *(s64 *)(job + 0x58);
                if (relayObj != 0 && *(s8 *)(relayObj + 0x28) == '\0') {
                    *(void **)(job + 0x30)       = PTR_LAB_71052a2f68;
                    *(s64 *)(job + 0x38)         = 0;
                    *(const char **)(job + 0x40) =
                        "NexNatServerAddressResolveJob::StepResolveRelayServerSetting";
                    return 7;
                }
            }
        }
    }

    *(void **)(job + 0x30)       = PTR_LAB_71052a2f50;
    *(s64 *)(job + 0x38)         = 0;
    *(const char **)(job + 0x40) = "NexNatServerAddressResolveJob::StepComplete";
    return 5;
}

}} // namespace nn::nex

// ============================================================================
// 4. 0x71000d31a0 � NOT FOUND in 13.0.1 binary; skipped.
// ============================================================================

// ============================================================================
// 5. nn::pia session slot array constructor
//    13.0.4 address: 0x71000d4bc0   13.0.1 entry: 0x71000d4b40   size: 112 B
//    Sets vtable, allocates count*8 bytes from pia heap, zero-inits,
//    then constructs each slot object (0x270 bytes each).
// ============================================================================
namespace nn { namespace pia {

void SessionSlotArray_Ctor(s64 *self, u64 count)
{
    *(u16 *)((u8 *)self + 8)  = 0;
    *(s16 *)((u8 *)self + 10) = (s16)count;
    *self = (s64)((u8 *)PTR_DAT_71052a2f90 + 0x10);

    void *heap = nn::pia::common::HeapManager_GetHeap();
    u64   n    = count & 0xffff;
    s64   arr  = (s64)pead::allocateFromSeadHeap(n << 3, heap);

    if (arr != 0 && (count & 0xffff) != 0) {
        u64 rem = n & 3;
        s64 i   = 0;
        if (n - 1 >= 3) {
            u64 *p = (u64 *)(arr + 0x10);
            do {
                i += 4;
                p[-2] = 0; p[-1] = 0; p[0] = 0; p[1] = 0;
                p += 4;
            } while (n - rem != (u64)i);
        }
        if (rem != 0) {
            s64  neg = -(s64)rem;
            u64 *p   = (u64 *)(arr + i * 8);
            do { neg++; *p++ = 0; } while (neg != 0);
        }
    }
    self[2] = arr;

    u16 cnt = *(u16 *)((u8 *)self + 10);
    if (cnt != 0) {
        u64  j       = 0;
        u8  *vtblPtr = (u8 *)PTR_DAT_71052a2f98 + 0x10;
        do {
            void  *heap2 = nn::pia::common::HeapManager_GetHeap();
            s64   *obj   = (s64 *)pead::allocateFromSeadHeap(0x270, heap2);
            if (obj != nullptr) {
                memset(obj, 0, 0x270);
                FUN_7100112710(obj);
                *obj = (s64)vtblPtr;
            }
            *(s64 **)(self[2] + (s64)j * 8) = obj;
            j++;
        } while (j < cnt);
    }
}

}} // namespace nn::pia

// ============================================================================
// 6. nn::vfx stripe/particle system reset
//    13.0.4 address: 0x71000823d0  (interior)   13.0.1 entry: 0x71000807c0   size: 128 B
//    Clears pixel buffer, drains three intrusive doubly-linked lists,
//    walks per-slot list array, then rebuilds the free-list chain.
// ============================================================================
namespace nn { namespace vfx {

void StripeSystem_Reset(s64 self)
{
    // Clear pixel buffer: lock -> memset -> unlock
    s64 base = FUN_71000339f0(*(void **)(self + 0x1e90));
    memset((void *)(base + *(s64 *)(self + 0x1e98)),
           0,
           (u64)(u32)(*(s32 *)(self + 0x2c) * *(s32 *)(self + 0x28)));
    FUN_7100033a10(*(void **)(self + 0x1e90));

    // Drain intrusive doubly-linked list: repeatedly unlinks front node from tail
    auto drainList = [](s64 base, s64 tailOff, s64 sentOff) {
        s64 *tail = *(s64 **)(base + tailOff);
        s64 *sent = (s64 *)(base + sentOff);
        while (tail != sent) {
            s64 *next = (s64 *)tail[1];
            s64  prev = *next;
            *(s64 **)(*tail + 8) = next;
            *next = *tail;
            *(s64 **)(prev + 8) = tail;
            *tail = prev;
            tail = *(s64 **)(base + tailOff);
        }
    };

    drainList(self, 0x58, 0x50);
    drainList(self, 0x68, 0x60);
    drainList(self, 0x78, 0x70);

    // Per-slot lists: stride 0x18, count at +0x1880, list head/tail at +0x88/+0x80
    u32 cnt = *(u32 *)(self + 0x1880);
    if (cnt != 0) {
        u64 idx = 0;
        do {
            s64  slotBase = self + (s64)idx * 0x18;
            u64 *pHead    = (u64 *)(slotBase + 0x88);
            s64 *head     = (s64 *)*pHead;
            s64 *sent     = (s64 *)(slotBase + 0x80);
            if (head != sent) {
                do {
                    s64 *next = (s64 *)head[1];
                    s64  prev = *next;
                    *(s64 **)(*head + 8) = next;
                    *next = *head;
                    *(s64 **)(prev + 8) = head;
                    *head = prev;
                    head  = (s64 *)*pHead;
                } while (head != sent);
                cnt = *(u32 *)(self + 0x1880);
            }
            idx++;
        } while (idx < cnt);
    }
    *(u32 *)(self + 0x1880) = 0;

    // Rebuild free-list chain (entries have stride 0x58 = 11 * 8 words)
    s64 arr  = *(s64 *)(self + 0x40);
    u32 last = (u32)(*(s32 *)(self + 0x48) - 1);
    *(u64 *)(self + 0x30) = 0;
    *(s64 *)(self + 0x38) = arr;

    if (*(s32 *)(self + 0x48) > 1) {
        s64 i = 0;
        if (last != 1) {
            s64 *p = (s64 *)(arr + 0x58);
            do {
                i += 2;
                p[-0xb] = (s64)p;
                *p      = (s64)(p + 0xb);
                p += 0x16;
            } while ((u64)last - ((u64)last & 1) != (u64)i);
        }
        if ((last & 1) != 0) {
            s64 *p = (s64 *)(arr + i * 0x58);
            *p = (s64)(p + 0xb);
        }
    }
    *(u64 *)(arr + (s64)(s32)(last * 0xb) * 8) = 0;
    *(s64 *)(self + 0x40) = arr;
}

}} // namespace nn::vfx

// ============================================================================
// 7. nn::vfx::EmitterResource::Setup
//    13.0.4 address: 0x710008b460  (interior)   13.0.1 entry: 0x710008b350   size: 128 B
//    Binds color/depth/distortion shader permutations and optional G3D primitive.
//    Returns true on success, false on missing shader or bind failure.
// ============================================================================
namespace nn { namespace vfx {

bool EmitterResource_Setup(u8 *self, u8 *pResource)
{
    if (*self != '\0') return true;
    if (pResource[0x4c0] == '\0') return false;
    if (pResource[0x508] == '\0') return false;

    s64  res10      = *(s64 *)(self + 0x10);
    void *resData   = *(void **)(pResource + 0x10);
    u8   *shaderBase = pResource + 0x4c0;

    // Optionally bind G3D primitive (only for standard emitter types 0 or >3)
    u64 g3dIdx = *(u64 *)(res10 + 0x8c8);
    if (g3dIdx != 0xffffffffffffffffULL) {
        s32 emitType = *(s32 *)(self + 0x330);
        if (emitType == 0 || emitType > 3) {
            void *prim = Resource::GetG3dPrimitive(pResource, g3dIdx);
            res10 = *(s64 *)(self + 0x10);
            *(void **)(self + 0x78) = prim;
        }
    }

    *(u64 *)(self + 0x350) = 0;
    *(u64 *)(self + 0x348) = 0;

    // Bind primary (color) shader
    void *sh = ::detail::ShaderManager::GetShader(shaderBase, *(s32 *)(res10 + 0x914));
    res10 = *(s64 *)(self + 0x10);
    *(void **)(self + 0x340) = sh;

    if (*(s32 *)(res10 + 0x91c) != -1) {
        // Bind depth/refraction shader
        sh = ::detail::ShaderManager::GetShader(shaderBase, *(s32 *)(res10 + 0x91c));
        *(void **)(self + 0x348) = sh;
        if (sh == nullptr) {
            ::detail::OutputWarning("ShaderBinary Bind Error.\n");
            return false;
        }
        res10 = *(s64 *)(self + 0x10);
    }

    // Bind distortion shader
    if (*(s32 *)(res10 + 0x920) != -1) {
        sh = ::detail::ShaderManager::GetShader(shaderBase, *(s32 *)(res10 + 0x920));
        *(void **)(self + 0x350) = sh;
        if (sh == nullptr) {
            ::detail::OutputWarning("ShaderBinary Bind Error.\n");
            return false;
        }
        res10 = *(s64 *)(self + 0x10);
    }

    // Set animation uniform block pointer
    if (*(s32 *)(res10 + 0x918) != -1) {
        *(s64 *)(self + 0x358) = *(s64 *)(pResource + 0x520) +
                                  (s64)*(s32 *)(res10 + 0x918) * 0x40;
    }

    u64 ok = FUN_710008a850(self, resData);
    if ((ok & 1) != 0) {
        *self = 1;
        return true;
    }
    return false;
}

}} // namespace nn::vfx

// ============================================================================
// 8. nn::vfx stripe slot allocator
//    13.0.4 address: 0x710009da10   13.0.1 entry: 0x710009d9c0   size: 128 B
//    Finds a free stripe slot, allocates and links a ring-buffer of history
//    entries, marks it active. Returns slot pointer or 0 on failure.
// ============================================================================
namespace nn { namespace vfx {

s64 StripeManager_AllocSlot(s64 mgr, void *sys)
{
    s32 total = *(s32 *)(mgr + 0x1c);
    if (total <= 0) goto warn_no_slots;

    {
        s64 slotArr = *(s64 *)(mgr + 0x30);
        s32 idx     = *(s32 *)(mgr + 0x28);
        s32 scanned = 0;

        do {
            char *active = (char *)(slotArr + (s64)idx * 0x90 + 0x84);
            if (*active == '\0') {
                s64 slot = slotArr + (s64)idx * 0x90;

                // Determine ring capacity from particle system state
                u32 cap = (u32)*(float *)(
                    *(s64 *)(*(s64 *)((s64)sys + 0x238) + 0x338) + 0x14);

                // Allocate ring-buffer (cap entries * 0x40 bytes, 0x80-aligned)
                typedef s64 (*AllocFn)(s64, u64, u32);
                s64 buf = ((AllocFn)*(s64 *)((s64)sys + 0x828 + 0x10))(
                    (s64)sys + 0x828, (u64)cap << 6, 0x80);

                s64 *pBuf = (s64 *)(slot + 0x50);
                *pBuf = buf;
                if (buf == 0) {
                    nn::vfx::detail::Warning(sys, 0x4000);
                    nn::vfx::detail::OutputWarning(
                        "Buffer for stripe history is not enough\n");
                    return 0;
                }

                // Build forward-link ring: entry[i].next = entry[i+1] (last wraps)
                u32 last = cap - 1;
                if (last != 0) {
                    s64 off = 0, i = 0;
                    if (last > 1) {
                        do {
                            *(s64 *)(buf + off + 0x30) = buf + off + 0x40;
                            buf  = *pBuf + off;
                            off += 0x80;
                            *(s64 *)(buf + 0x70) = buf + 0x80;
                            buf  = *pBuf;
                            i   += 2;
                        } while ((u64)last - ((u64)last & 1) != (u64)i);
                    }
                    if ((last & 1) != 0) {
                        buf = buf + i * 0x40;
                        *(s64 *)(buf + 0x30) = buf + 0x40;
                        buf = *pBuf;
                    }

                    // Build backward-link ring: entry[i].prev = entry[i-1] (wraps)
                    if (cap > 1) {
                        u64 j    = 1;
                        s64 boff = 0;
                        if (cap > 2) {
                            do {
                                *(s64 *)(buf + boff + 0x78) = buf + boff;
                                buf  = *pBuf + boff;
                                boff += 0x80;
                                *(s64 *)(buf + 0xb8) = buf + 0x40;
                                buf  = *pBuf;
                                j   += 2;
                            } while ((u64)cap - (u64)(~cap & 1) != j);
                        }
                        if ((~cap & 1) != 0) {
                            buf = buf + j * 0x40;
                            *(s64 *)(buf + 0x38) = buf - 0x40;
                            buf = *pBuf;
                        }
                    }
                }

                // Close the ring
                *(s64 *)(buf + (u64)last * 0x40 + 0x30) = buf;
                *(u64 *)(*pBuf + 0x38) = *pBuf + (u64)last * 0x40;

                // Initialize slot state
                s64 sp   = slotArr + (s64)idx * 0x90;
                s64 head = *pBuf;
                *(s64 *)(sp + 0x58) = head;
                *(s64 *)(sp + 0x60) = head;
                *active             = '\x01';
                *(u32 *)(sp + 0x70) = 0;
                *(u64 *)(sp + 0x78) = 0;
                *(u64 *)(sp + 0x68) = 0;
                *(s32 *)(mgr + 0x2c) += 1;
                return slot;
            }

            scanned++;
            s32 next = (idx + 1 < total) ? idx + 1 : 0;
            *(s32 *)(mgr + 0x28) = next;
            idx = next;
        } while (scanned < total);
    }

warn_no_slots:
    nn::vfx::detail::Warning(sys, 0x2000);
    nn::vfx::detail::OutputWarning("There is no available Stripe instance.\n");
    return 0;
}

}} // namespace nn::vfx

// ============================================================================
// 9. GroundModule::GetRightPos
//    13.0.4 address: 0x7100464560   13.0.1 entry: 0x7100464540   size: 128 B
//    Returns the right-edge ground contact position as a 16-byte float tuple.
//    When field_0x44 == 0 (has live ground normal), adds posture module offset.
// ============================================================================
namespace app {

// AArch64 returns 16-byte structs in v0/v1; Ghidra represents as CONCAT44 pairs.
struct Vec4f { float x, y, z, w; };

Vec4f GroundModule_GetRightPos(void *self)
{
    Vec4f r;

    // Get ground info ptr via virtual dispatch (FUN_710045eec0 slot)
    typedef void *(*VtFn)(void *);
    void *gInfo = ((VtFn)(*(void ***)self)[0])(self);

    if (*(s32 *)((u8 *)self + 0x44) == 0) {
        // Fetch posture offset from BattleObjectModuleAccessor
        // Pattern: (**(*(accessor+0x38)))()  ->  u64* containing two f32 components
        s64   acc    = *(s64 *)((u8 *)self + 0x20);
        void **entry = *(void ***)(acc + 0x38);
        u64  *posOff = (u64 *)(**(u64 (**)())entry)();

        // Ghidra CONCAT44: lo = (float)(u32)*posOff, hi = (float)(*posOff >> 32)
        u32 raw_lo = (u32)(u64)*posOff;
        u32 raw_hi = (u32)((u64)*posOff >> 32);
        float off_x = *(float *)&raw_lo;
        float off_y = *(float *)&raw_hi;

        r.x = *(float *)((u8 *)gInfo + 0x30) + off_x;
        r.y = *(float *)((u8 *)gInfo + 0x34) + off_y;
        r.z = *(float *)((u8 *)gInfo + 0x38) + 0.0f;
        r.w = *(float *)((u8 *)gInfo + 0x3c) + 0.0f;
    } else {
        r.x = *(float *)((u8 *)gInfo + 0x30);
        r.y = *(float *)((u8 *)gInfo + 0x34);
        r.z = *(float *)((u8 *)gInfo + 0x38);
        r.w = *(float *)((u8 *)gInfo + 0x3c);
    }
    return r;
}

} // namespace app
