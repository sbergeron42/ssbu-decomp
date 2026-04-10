#pragma once

#include "types.h"

// LDN Transport Session layout for frame exchange functions
// Derived from FUN_710012b530, FUN_710012ac30, FUN_710012ba00
//
// This is a standalone copy of the layout from include/app/LDNSession.h
// to avoid the nn/types.h <-> types.h u64 redefinition conflict.
// If LDNSession.h's LDNTransportSession is updated, keep this in sync.

namespace app {

struct LDNTransportSession {
    u8 pad_00[0x58];
    void* session_handle;              // +0x58 [derived: checked non-null in FUN_710012b530/ac30]

    // +0x60: socket descriptor (passed to socket_send_to / socket_recv_from)
    // [derived: FUN_710012ac30 passes param_1+0x60 to FUN_71000ba450]
    struct {
        int fd;                        // +0x60
        int generation;                // +0x64
        u8 family;                     // +0x68
        u8 pad[7];                     // +0x69
    } socket;                          // +0x60

    u8 recv_buffer[0x554];             // +0x70 [derived: recv target in FUN_710012ac30, max 0x554]
    u8 send_buffer[0x554];             // +0x5C4 [derived: packet built here in FUN_710012b530/ba00]

    u8 pad_b18[0x268];                 // +0xB18..+0xD7F: frame data state region

    u8 num_peers;                      // +0xD80 [derived: loop bound in FUN_710012ac30 send loop]
    u8 send_pending;                   // +0xD81 [derived: flag checked/cleared in FUN_710012ac30]
    u8 pad_d82[0x3E];                  // +0xD82..+0xDBF

    u8 crypto_flush_pending;           // +0xDC0 [derived: checked/cleared at top of FUN_710012ac30]
    u8 pad_dc1[7];                     // +0xDC1..+0xDC7

    u64 sequence_number;               // +0xDC8 [derived: incremented in FUN_710012b530/ba00]
    u8 encryption_key[0x10];           // +0xDD0 [derived: memcpy'd into packet trailer, 16 bytes]
    u8 encryption_iv[0x100];           // +0xDE0 [derived: passed as IV material, 256 bytes]
};

// Keepalive timer deadline is at +0xDB8 within the pad_d82 region
// [derived: compared against current time in FUN_710012ac30]
static constexpr int LDN_KEEPALIVE_DEADLINE_OFFSET = 0xDB8;
static constexpr int LDN_KEEPALIVE_STATE_OFFSET    = 0xD88;

} // namespace app
