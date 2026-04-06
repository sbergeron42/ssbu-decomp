// res_small_funcs.cpp — Small/medium functions in the resource service area
// Pool-a assignment: resource service area, sorted by size

#include <nn/prepo.h>

// Placement new (no <new> header in baremetal toolchain)
inline void* operator new(unsigned long, void* p) noexcept { return p; }

extern "C" void* je_aligned_alloc(unsigned long, unsigned long);
extern "C" void FUN_710392e590(void*);  // je_free
extern "C" void* memset(void*, int, unsigned long);
extern "C" char* strcpy(char*, const char*);

__attribute__((visibility("hidden"))) extern s64* DAT_7105331f00;  // OOM handler singleton (40+ refs in binary)

// ============================================================================
// start_prepo_report — 0x710375a4e0 (336 bytes)
// Allocates a play report buffer and initializes nn::prepo::PlayReport.
// Layout: event_name[0x20] + data_buffer[0x4000] + PlayReport[0x38] = 0x4058
// [derived: nn::prepo::PlayReport from NintendoSDK 8.2.1]
// [derived: allocation size 0x4058 confirmed by je_aligned_alloc call]
// [derived: PlayReport at +0x4020 from constructor call target]
// Status: 63% raw match — body logic correct, diffs are prologue scheduling
//   (NX Clang fork), BL relocations, and instruction scheduling only
// ============================================================================
void start_prepo_report_375a4e0(u64* param_1, const char* event_name) {
    u32 oom_flags;
    u64 oom_size;

    u64* holder = (u64*)je_aligned_alloc(0x10, 8);
    if (holder == nullptr) {
        if (DAT_7105331f00 != nullptr) {
            oom_flags = 0;
            oom_size = 8;
            u64 r = ((u64(*)(s64*, u32*, u64*))(*(s64*)(*DAT_7105331f00 + 0x30)))
                     (DAT_7105331f00, &oom_flags, &oom_size);
            if (((r & 1) != 0) &&
                (holder = (u64*)je_aligned_alloc(0x10, 8), holder != nullptr))
                goto LAB_710375a55c;
        }
        holder = nullptr;
    }
LAB_710375a55c:
    char* buf = (char*)je_aligned_alloc(0x10, 0x4058);
    if (buf == nullptr) {
        if (DAT_7105331f00 != nullptr) {
            oom_flags = 0;
            oom_size = 0x4058;
            u64 r = ((u64(*)(s64*, u32*, u64*))(*(s64*)(*DAT_7105331f00 + 0x30)))
                     (DAT_7105331f00, &oom_flags, &oom_size);
            if (((r & 1) != 0) &&
                (buf = (char*)je_aligned_alloc(0x10, 0x4058), buf != nullptr))
                goto LAB_710375a5b8;
        }
        buf = nullptr;
    }
LAB_710375a5b8:
    memset(buf + 0x20, 0, 0x4000);
    nn::prepo::PlayReport* report = new (buf + 0x4020) nn::prepo::PlayReport();
    strcpy(buf, event_name);
    report->SetEventId(event_name);
    report->SetBuffer(buf + 0x20, 0x4000);
    *holder = (u64)buf;
    *param_1 = (u64)holder;
}

// Forward declarations for FUN_7103754500
extern "C" long FUN_71002c48f0();  // nu::ModuleInitializer<GraphicsModule>::Instance()
extern "C" void FUN_71037e57f0(long, u8*);  // graphics module element process
extern "C" void FUN_71039c1400(void*);  // nu::VirtualFreeHook (PLT)
__attribute__((visibility("hidden"))) extern void* PTR_VirtualFreeHook_71052a7a70;

// ============================================================================
// FUN_7103754500 — 0x7103754500 (304 bytes)
// Clears graphics resource vector: iterates forward calling FUN_71037e57f0,
// then backward freeing libc++ SSO heap strings, resets end pointer,
// and zeroes 12 CppVector sub-objects at stride 0x20 from offset 0x20.
// [derived: nu::ModuleInitializer<GraphicsModule>::Instance() call at 0x71002c48f0]
// [derived: SSO string layout: byte[0] bit 0 = heap flag, qword[0x10] = heap ptr]
// [derived: VirtualFreeHook ptr at 0x71052a7a70 — PLT stub at 0x71039c1400]
// Status: 85% raw match — ALL diffs are prologue (NX fork) + BL/ADRP relocations.
//   Zero logic differences. Effectively a perfect match post-linking.
// ============================================================================
void FUN_7103754500_3754500(long* param_1) {
    FUN_71002c48f0();
    long graphics = FUN_71002c48f0();

    u8* start = (u8*)*param_1;
    u8* end = (u8*)param_1[1];

    if (start != end) {
        u8* p = start;
        do {
            FUN_71037e57f0(graphics + 0x60, p);
            p += 0x18;
        } while (end != p);

        start = (u8*)*param_1;
        end = (u8*)param_1[1];
        void* vfh = PTR_VirtualFreeHook_71052a7a70;

        while (end != start) {
            end -= 0x18;
            if (*end & 1) {
                void* heap = *(void**)(end + 0x10);
                if (vfh != nullptr) {
                    FUN_71039c1400(heap);
                }
                FUN_710392e590(heap);
            }
        }
    }

    param_1[1] = (long)start;

    // Zero 12 CppVector sub-objects (3 qwords each, stride 0x20, starting at offset 0x20)
    for (int i = 0; i < 12; i++) {
        long* slot = &param_1[4 + i * 4];
        slot[0] = 0;
        slot[1] = 0;
        slot[2] = 0;
    }
}

// ============================================================================
// SKIPPED — nn::mii / nn::friends (per WORKER.md rules)
// ============================================================================
//
// FUN_7103757140 (336 bytes) — nn::mii object destructor
//   Releases shared_ptrs at +0x24f0 and +0x2500, destroys vector at +0x24d0,
//   calls nn::mii::Database::~Database(this+0x20), std::mutex::~mutex(this),
//   then je_free(this). Full Mii database teardown.
//
// FUN_7103758e20 (304 bytes) — nn::mii get CharInfo by index
//   Locks mutex, calls nn::mii::Database::GetCount, reads 0x58-byte CharInfo
//   at this+0x60+index*0x58, validates with CharInfoAccessor::IsValid,
//   copies into vector of 0x68-byte elements at this+0x24d0. Returns 1/0.
//
// GlobalParameter / FUN_7103756640 (896 bytes) — nn::friends hash map builder
//   Calls nn::friends::GetFriendList(300 max), iterates results,
//   calls Friend::IsValid/GetAccountId, inserts into hash map at +0x25990.
//   Hash map uses open chaining with load factor rehash.
//
// ============================================================================
// NOT RESOURCE — documented for future assignment
// ============================================================================
//
// FUN_7103741010 (336 bytes) — binary protocol logger ("bnqp" format)
//   Writes structured messages to ring buffer. Magic bytes: 0x64716e62 ("bnqd"),
//   0x2070716e62 ("bnqp "). Uses ExclusiveMonitorPass (atomic increment) at +0x3c.
//   Requires globals: DAT_7106dd4588, DAT_7106dd40c8, DAT_7106dd40c9, DAT_7106dd4408.
//
// FUN_7103755270 (288 bytes) — nn::web show offline HTML page
//   Builds URL via set_format, creates ShowOfflineHtmlPageArg, adjusts volume
//   via nn::oe, calls nn::web::ShowOfflineHtmlPage. Needs nn::web headers.
//
// FUN_710375f480 (464 bytes) — engine vector dispatch
//   Clears u64 vector at param_2+0x178, iterates linked list from *param_1,
//   calls FUN_71000425f0 for each node, pushes results with vector growth.
//
// FUN_7103754ef0 (624 bytes) — std::any-like singleton swap
//   Complex vtable dispatch through global at DAT_710593a570. Manipulates
//   polymorphic objects via vtable offsets 0x10/0x18/0x20/0x28.
//
// FUN_7103755a50 (608 bytes) — nn::account user info loader
//   Searches 0xcc0-sized user entries by nn::account::Uid, checks
//   IsNetworkServiceAccountAvailable, calls LoadCachedNintendoAccountInfo.
//   Needs nn::account::CachedNintendoAccountInfo type (not in SDK headers).
