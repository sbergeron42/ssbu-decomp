#include "types.h"

// pool-d: libcurl + nn networking stub functions (<=64B, EASY tier)
// Most 16B nn-dispatch stubs call through PTR_ function pointer tables and cannot
// be byte-matched without full SDK headers; the auto-generable ones are below.

// ---------------------------------------------------------------------------
// libcurl internal helpers
// ---------------------------------------------------------------------------

// 0x71000047a0  16B  Curl_resolver_cleanup -- noop stub
void Curl_resolver_cleanup_47a0(void*) { }

// 0x7100006530  16B  Curl_ipvalid -- test addr_family field != 2 (AF_INET6 exclusion)
bool Curl_ipvalid_6530(void* p) {
    return *reinterpret_cast<long*>(reinterpret_cast<u8*>(p) + 0x868) != 2;
}

// Curl_llist_count_69a0 — deduped to fun_region_000.cpp

// 0x710000 5b80  32B  Curl_num_addresses -- walk linked list via +0x28, count nodes
int Curl_num_addresses_5b80(long p) {
    int count = 0;
    if (p != 0) {
        do {
            p = *reinterpret_cast<long*>(p + 0x28);
            count++;
        } while (p != 0);
    }
    return count;
}

// 0x7100014f90  48B  Curl_pgrsResetTimesSizes -- zero progress tracking fields
void Curl_pgrsResetTimesSizes_14f90(long p) {
    *reinterpret_cast<u64*>(p + 0x9d8) = 0;
    *reinterpret_cast<u64*>(p + 0xa30) = 0;
    *reinterpret_cast<u64*>(p + 0xa28) = 0;
    *reinterpret_cast<u64*>(p + 0xa48) = 0;
    *reinterpret_cast<u64*>(p + 0xa40) = 0;
    *reinterpret_cast<u64*>(p + 0x9e0) = 0;
    *reinterpret_cast<u32*>(p + 0xa08) &= 0xffffff9fu;
}

// 0x7100016c80  64B  curl_slist_free_all -- free a curl_slist linked list
extern "C" void Curl_SigloFree(void*);

void curl_slist_free_all_16c80(u64** p) {
    if (p) {
        do {
            u64** next = reinterpret_cast<u64**>(p[1]);
            Curl_SigloFree(reinterpret_cast<void*>(*p));
            *p = 0;
            Curl_SigloFree(reinterpret_cast<void*>(p));
            p = next;
        } while (p);
    }
}

// 0x7100013700  48B  Curl_digest_cleanup -- clean two sasl digest structs at fixed offsets
extern "C" void Curl_sasl_digest_cleanup(void*);

void Curl_digest_cleanup_13700(long p) {
    Curl_sasl_digest_cleanup(reinterpret_cast<void*>(p + 0x4c40));
    Curl_sasl_digest_cleanup(reinterpret_cast<void*>(p + 0x4c80));
}

// ---------------------------------------------------------------------------
// Socket / network object stubs
// ---------------------------------------------------------------------------

// 0x71000b9f50  16B  ~Socket -- noop dtor
void dtor_Socket_b9f50(void*) { }

// 0x7100162480  16B  GetNetworkFactory -- return factory pointer field at +8
u64 GetNetworkFactory_162480(void* obj) {
    return *reinterpret_cast<u64*>(reinterpret_cast<u8*>(obj) + 0x8);
}
