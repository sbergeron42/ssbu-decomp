// =============================================================================
// SSBU Net Frame Exchange — per-frame game data send/recv over UDP
//
// Address range: 0x710012xxxx
//
// After nn::ldn::Connect establishes the session and
// ldn_connect_setup_socket (0x710016c120) creates a UDP socket on port 12345,
// these functions handle the per-frame game state exchange:
//
//   ldn_send_game_state (0x710012b530) — serialize + send to one peer
//   ldn_recv_and_process (0x710012ac30) — receive + validate + dispatch
//   ldn_send_reply (0x710012ba00) — reply/sync with 3x redundancy
//
// See include/app/LDNSession.h for struct layouts.
// See src/docs/networking.md for protocol documentation.
// =============================================================================

#include "types.h"
#include "app/networking/LDNTransport.h"
#include "app/networking/FrameStateCondition.h"
#include "app/networking/FrameDataSubObject.h"

using app::FrameStateCondition;
using app::FrameDataSubObject;
using app::FRAME_CONDITION_NUM_SLOTS;
using app::FRAME_CONDITION_DEFAULT_TICK_COUNT;
using app::FRAME_RANGE_NO_FILTER;

// LDN transport constants — from include/app/LDNSession.h
// (not included directly due to nn/types.h u64 redefinition conflict)
static constexpr u32 LDN_ERR_INVALID_STATE = 0x10c07;
static constexpr u32 LDN_ERR_UNKNOWN       = 0x10c08;
static constexpr u32 LDN_ERR_RECV_DISCONNECT = 0x2c09;
static constexpr u32 LDN_ERR_SEND_FAIL     = 0x4c0d;
static constexpr u32 LDN_MAX_GAME_STATE_SIZE = 0x425;
static constexpr u32 LDN_MAX_RECV_SIZE     = 0x554;
static constexpr u32 LDN_MAX_REPLY_SIZE    = 0x515;
static constexpr u8  PACKET_TYPE_GAME_DATA     = 0;
static constexpr u8  PACKET_TYPE_ENCRYPTED     = 1;
static constexpr u8  PACKET_TYPE_SYNC_REQUEST  = 2;

extern "C" void* memcpy(void*, const void*, unsigned long);
extern "C" void* memset(void*, int, unsigned long);
extern "C" int   memcmp(const void*, const void*, unsigned long);

// ---- External globals -------------------------------------------------------

extern u8 PTR_DAT_71052a4080;    // Game state manager global
extern u8 PTR_DAT_71052a3df0;    // Spectator manager global
extern u8 PTR_DAT_71052a3c30;    // Log/debug transport global

// ---- Byte serialization (already compiled in fun_easy_final_003.cpp) --------

extern void FUN_71000bb9d0(u8 *, u8);               // write_byte
extern void FUN_71000bb980(u8 *, u32);               // write_u32_be
extern void FUN_71000bb930(u8 *, u64);               // write_u64_be
extern u32  FUN_71000bb9a0(u32 *);                   // read_u32_be
extern u8   FUN_71000bb9e0(u8 *);                    // read_byte

// ---- Socket / transport functions -------------------------------------------

extern void FUN_71000ba5c0(int *, long, long, u32, u8 *, u8 *);   // socket_send_to
extern void FUN_71000ba450(u64 *, long, long, u32, u8 *, u8 *, u32 *);  // socket_recv_from
extern void FUN_71000bcf30(int *, void *);            // error_result_copy
extern void FUN_71000bce50(void *, void *);           // error_result_copy_alt
extern u64  FUN_71000b2820(u8 *, long);               // compare_addresses
extern void FUN_71000b1c30(u8 *);                     // address_init
extern void FUN_71000b1cf0(u8 *);                     // address_cleanup
extern void FUN_71000b1c60(u8 *, long);               // address_copy_from
extern void FUN_71000b1fa0(u8 *, void *);             // address_from_log
extern u64  FUN_71000b1f50(long);                     // address_is_v6
extern void FUN_71000b1da0(void *, long, void *);     // address_get_v4
extern void FUN_71000b2110(void *, long, void *);     // address_get_v6

// ---- Crypto / security functions --------------------------------------------

extern void FUN_7100129550(u64, u64, u64);            // flush_crypto_state
extern void FUN_7100129590(void *, u64, void *, u32, void *, u32); // aes_encrypt
extern void FUN_71001296b0(void *, u64, void *, u32, void *, u32); // aes_decrypt
extern void FUN_71001297f0(void *, u64, long, u32, void *, u32);   // hmac_compute
extern void FUN_71000b4c70(int *, long, long, u32, long, u32, void *); // auth_tag_generate
extern void FUN_71000b4e70(u8 *, void *, long, u32, long, u32, void *); // auth_tag_verify
extern void FUN_71000b6400(long, u32);                // fill_random_bytes

// ---- Session / peer management functions ------------------------------------

extern u8   FUN_7100192590(u64);                      // is_spectator
extern long FUN_710011be80(u64, u8);                   // get_peer_by_index
extern long FUN_710011be50(u64);                       // get_local_peer
extern long FUN_710011be60(u64);                       // get_primary_peer
extern long FUN_710011be70(u64);                       // get_secondary_peer
extern u64  FUN_710011bfe0(u64);                       // check_peer_state

// ---- PRNG -------------------------------------------------------------------

extern void FUN_7100138520(void *);                    // prng_init
extern u8   FUN_7100138620(void *);                    // prng_next_byte

// ---- Frame data processing --------------------------------------------------

extern void FUN_710012e410(void *, long *, long, int); // deserialize_game_state
extern void FUN_710012de50(void *, u64, void *, u32 *, u32); // serialize_reply_data
extern void FUN_710012f640(void *, long, long, int);   // frame_state_input
extern void FUN_710012fba0(long, void *);              // frame_state_update (4-byte stub)
extern u64  FUN_710012ed20(long, u64);                 // frame_state_check

// ---- Error / disconnect handling --------------------------------------------

extern void FUN_7100121af0(u64);                       // trigger_disconnect
extern void FUN_71000b4180(long, void *);              // keepalive_dispatch
extern u64  FUN_71000b63d0(void);                      // get_crypto_param
extern void FUN_71000bb5d0(u64 *);                     // get_current_time
extern long*FUN_71000bb680(void);                      // get_keepalive_interval
extern void FUN_7100119a50(u64, u8 *, u32);           // peer_write_data

// ---- nn::err (error result variant) -----------------------------------------

namespace nn { namespace err {
    struct ErrorResultVariant;
    void ErrorResultVariant_ctor(ErrorResultVariant *);
    void ErrorResultVariant_assign(ErrorResultVariant *, u32 *);
}}

// ---- Forward declarations (defined later in this file) ----------------------

extern bool FUN_7100125e30(long param_1);
extern u8   FUN_7100129a90(long param_1);
extern void FUN_7100125f90(long param_1);

// Defined later in this file:
void FUN_710012ba00(int *err_out, long param_2, u8 *source_addr, void *crypto_data, u32 crypto_size,
                    u64 *iv_material, u32 iv_size, u32 encryption_ok, u32 short_packet, u8 use_alt_serializer);

// =============================================================================
// FUN_710012b530 — Send game state to a peer
// Address: 0x710012b530 | Size: 1,220 bytes
//
// Serializes the current frame's game state and sends it to a specific peer
// over the UDP transport. Handles both encrypted and unencrypted modes.
//
// param_1: output error result
// param_2: LDN transport session pointer
// param_3: peer index (must be < 2)
// =============================================================================

void FUN_710012b530(u64 err_out, long param_2, u32 peer_index)
{
    app::LDNTransportSession *session = reinterpret_cast<app::LDNTransportSession *>(param_2);
    long send_buf_base;
    long loop_step;
    u8 *game_state_mgr;
    u32 payload_size;
    u8 rand_byte;
    u32 is_host;
    u64 check;
    long *peer_obj;
    int *result_ptr;
    u64 *addr_iter;
    int loop_idx;
    long loop_counter;
    u64 prng_state;
    u32 *addr_buf_ptr;
    u32 addr_buf_size;
    u32 uStack_6ec;
    u64 addr_data;
    u32 addr_pad[48];
    u32 peer_addr[6];
    u16 peer_port;
    u8 port_pad[4];
    int send_result[4];
    u32 crypto_addr;
    u8 crypto_addr_pad[12];
    int serialize_result[5];
    u32 serialized_size;
    int payload_buf[344];

    addr_iter = &prng_state;
    if ((peer_index & 0xff) < 2) {
        // Validate session handle and connection state
        if (((session->session_handle != 0) &&
            (check = FUN_7100129a90((u64)session->session_handle), (check & 1) != 0)) &&
           (check = FUN_7100125e30((u64)session->session_handle),
            game_state_mgr = (u8 *)*(long *)&PTR_DAT_71052a4080,
           (check & 1) != 0)) {
            // Get peer object and serialize game state via vtable[0x28]
            peer_obj = (long *)FUN_710011be80(*(u64 *)
                                             (*(long *)&PTR_DAT_71052a4080 +
                                              (u64)*(u8 *)(*(long *)&PTR_DAT_71052a4080 + 0x162) * 8 +
                                             0x168), peer_index);
            (**(void (**)(int *, long *, int *, u32 *, u32))(*peer_obj + 0x28))(
                serialize_result, peer_obj, payload_buf, &serialized_size, LDN_MAX_GAME_STATE_SIZE);

            if (serialize_result[0] == 0) {
                // Write packet header into send buffer (+0x5C4)
                send_buf_base = (long)session->send_buffer;
                FUN_71000bb9d0((u8 *)send_buf_base, PACKET_TYPE_GAME_DATA);
                FUN_71000bb980((u8 *)(param_2 + 0x5c5), serialized_size);
                memcpy((void *)(param_2 + 0x5c9), payload_buf, (u64)serialized_size);
                payload_size = serialized_size;

                // Increment sequence number
                *(long *)&session->sequence_number = *(long *)&session->sequence_number + 1;

                // Write trailer: end-of-frame marker, host flag, sequence, key
                FUN_71000bb9d0((u8 *)(send_buf_base + (u64)(serialized_size + 5)), PACKET_TYPE_SYNC_REQUEST);
                is_host = (u32)FUN_7100125e30((u64)session->session_handle);
                FUN_71000bb9d0((u8 *)(send_buf_base + (u64)(payload_size + 6)), is_host & 1);
                FUN_71000bb930((u8 *)(send_buf_base + (u64)(payload_size + 7)), session->sequence_number);
                memcpy((void *)(send_buf_base + (u64)(payload_size + 0xf)), (void *)session->encryption_key, 0x10);

                check = FUN_7100125e30((u64)session->session_handle);
                if ((check & 1) == 0) {
                    // Unencrypted path: fill 16 random header bytes + 256 random padding bytes
                    FUN_7100138520(&prng_state);
                    rand_byte = FUN_7100138620(&prng_state);
                    *(u8 *)(send_buf_base + (u64)(payload_size + 0x1f)) = rand_byte;
                    rand_byte = FUN_7100138620(&prng_state);
                    *(u8 *)(send_buf_base + (u64)(payload_size + 0x20)) = rand_byte;
                    rand_byte = FUN_7100138620(&prng_state);
                    *(u8 *)(send_buf_base + (u64)(payload_size + 0x21)) = rand_byte;
                    rand_byte = FUN_7100138620(&prng_state);
                    *(u8 *)(send_buf_base + (u64)(payload_size + 0x22)) = rand_byte;
                    rand_byte = FUN_7100138620(&prng_state);
                    *(u8 *)(send_buf_base + (u64)(payload_size + 0x23)) = rand_byte;
                    rand_byte = FUN_7100138620(&prng_state);
                    *(u8 *)(send_buf_base + (u64)(payload_size + 0x24)) = rand_byte;
                    rand_byte = FUN_7100138620(&prng_state);
                    *(u8 *)(send_buf_base + (u64)(payload_size + 0x25)) = rand_byte;
                    rand_byte = FUN_7100138620(&prng_state);
                    *(u8 *)(send_buf_base + (u64)(payload_size + 0x26)) = rand_byte;
                    rand_byte = FUN_7100138620(&prng_state);
                    *(u8 *)(send_buf_base + (u64)(payload_size + 0x27)) = rand_byte;
                    rand_byte = FUN_7100138620(&prng_state);
                    *(u8 *)(send_buf_base + (u64)(payload_size + 0x28)) = rand_byte;
                    rand_byte = FUN_7100138620(&prng_state);
                    *(u8 *)(send_buf_base + (u64)(payload_size + 0x29)) = rand_byte;
                    rand_byte = FUN_7100138620(&prng_state);
                    *(u8 *)(send_buf_base + (u64)(payload_size + 0x2a)) = rand_byte;
                    rand_byte = FUN_7100138620(&prng_state);
                    *(u8 *)(send_buf_base + (u64)(payload_size + 0x2b)) = rand_byte;
                    rand_byte = FUN_7100138620(&prng_state);
                    *(u8 *)(send_buf_base + (u64)(payload_size + 0x2c)) = rand_byte;
                    rand_byte = FUN_7100138620(&prng_state);
                    *(u8 *)(send_buf_base + (u64)(payload_size + 0x2d)) = rand_byte;
                    rand_byte = FUN_7100138620(&prng_state);
                    loop_counter = 0;
                    *(u8 *)(send_buf_base + (u64)(payload_size + 0x2e)) = rand_byte;
                    // Fill 256 bytes of random padding
                    do {
                        rand_byte = FUN_7100138620(&prng_state);
                        loop_idx = (int)loop_counter;
                        loop_counter = loop_counter + 1;
                        *(u8 *)(param_2 + (u64)(payload_size + 0x2f + loop_idx) + 0x5c4) = rand_byte;
                    } while (loop_counter != 0x100);
                }
                else {
                    // Encrypted path: build crypto address, encrypt, generate auth tag
                    check = FUN_71000b1f50((long)session->session_handle + 0x70);
                    if ((check & 1) == 0) {
                        peer_addr[0] = 0;
                        FUN_71000b1da0(&prng_state, (long)session->session_handle + 0x70, peer_addr);
                        FUN_71000bb980((u8 *)&crypto_addr, peer_addr[0]);
                    }
                    else {
                        prng_state = 0;
                        addr_buf_ptr = (u32 *)0;
                        FUN_71000b2110(peer_addr, (long)session->session_handle + 0x70, &prng_state);
                        memcpy(&crypto_addr, &prng_state, 4);
                    }
                    FUN_71000bb930(crypto_addr_pad, session->sequence_number);
                    FUN_7100129590(&prng_state, (u64)session->session_handle, (void *)session->encryption_key, 0x10,
                                   peer_addr, 0x10);
                    FUN_71000bcf30(serialize_result, &prng_state);
                    *(u32 *)&prng_state = 1;
                    addr_buf_size = 0xc;
                    addr_pad[0] = 0x10;
                    addr_buf_ptr = &crypto_addr;
                    addr_data = (u64)peer_addr;
                    FUN_71000b4c70(send_result, (long)session->send_buffer + (u64)(payload_size + 0x2f), (long)session->encryption_iv, 0x100,
                                   (long)session->send_buffer + (u64)(payload_size + 0x1f), 0x10, &prng_state);
                }

                // Build destination address for send
                FUN_71000b1c60((u8 *)peer_addr, (long)session->session_handle + 0x70);
                peer_port = 30000;
                prng_state = (u64)(*(long *)&PTR_DAT_71052a3c30 + 0x10);
                addr_buf_size = 0xc0;
                *(u8 *)((long)&addr_data + 4) = 0;
                loop_counter = 0;
                do {
                    *(u16 *)((long)addr_iter + 0x1d) = 0;
                    loop_step = loop_counter + 4;
                    *(u8 *)((long)addr_iter + 0x1f) = 0;
                    addr_iter = (u64 *)((long)&prng_state + loop_counter + 4);
                    *(u8 *)((long)addr_pad + loop_counter) = 0;
                    loop_counter = loop_step;
                } while (loop_step != 0xc0);
                uStack_6ec = 0;
                *(u32 *)&addr_data = 0;
                addr_buf_ptr = (u32 *)((long)&addr_data + 4);
                FUN_71000b1fa0((u8 *)peer_addr, &prng_state);

                // Send the packet
                FUN_71000ba5c0(send_result, (long)&session->socket, send_buf_base,
                               serialized_size + 0x12f, (u8 *)peer_addr, port_pad);
                FUN_71000bcf30(serialize_result, send_result);
                if (serialize_result[0] != 0) {
                    // Send failed
                    send_result[0] = LDN_ERR_SEND_FAIL;
                    nn::err::ErrorResultVariant_ctor((nn::err::ErrorResultVariant *)((u64)send_result | 4));
                    crypto_addr = 0;
                    nn::err::ErrorResultVariant_assign(
                        (nn::err::ErrorResultVariant *)((u64)send_result | 4), &crypto_addr);
                    if (serialize_result[0] != send_result[0]) {
                        FUN_7100121af0(*(u64 *)(*(long *)game_state_mgr + 8));
                    }
                }
                FUN_71000b1cf0((u8 *)peer_addr);
            }
            result_ptr = serialize_result;
            goto LAB_710012b6e0;
        }
        payload_buf[0] = LDN_ERR_UNKNOWN;
    }
    else {
        payload_buf[0] = LDN_ERR_INVALID_STATE;
    }
    nn::err::ErrorResultVariant_ctor((nn::err::ErrorResultVariant *)((u64)payload_buf | 4));
    *(u32 *)&prng_state = 0;
    nn::err::ErrorResultVariant_assign(
        (nn::err::ErrorResultVariant *)((u64)payload_buf | 4), (u32 *)&prng_state);
    result_ptr = payload_buf;
LAB_710012b6e0:
    FUN_71000bce50((void *)err_out, result_ptr);
    return;
}

// =============================================================================
// FUN_710012ac30 — Receive and process game data
// Address: 0x710012ac30 | Size: 2,060 bytes
//
// The main per-frame receive function. Called each game tick to:
//   1. Flush pending crypto state
//   2. RecvFrom on UDP socket
//   3. Validate source address
//   4. Parse packet header and dispatch by type
//   5. Decrypt/verify if encrypted
//   6. Deserialize game state
//   7. If send_pending: send to all peers and update keepalive
//
// Returns 0xa0004 (success/continue code) always.
// =============================================================================

u64 FUN_710012ac30(long param_1)
{
    app::LDNTransportSession *session = reinterpret_cast<app::LDNTransportSession *>(param_1);
    bool use_alt_serializer;
    u32 header_end;
    u32 min_pkt_size;
    u32 recv_peer_flags;
    char send_pending;
    bool crypto_verified;
    bool hmac_verified;
    u8 is_spectator;
    u8 resolved_type;
    u32 has_crypto;
    int payload_len;
    u32 host_flag;
    int clear_header;
    int peer_id_match;
    u64 crypto_param_a;
    u64 crypto_param_b;
    u64 check;
    long *peer_primary;
    u64 *iter_cur;
    u64 *iter_end;
    long *peer_match;
    long secondary_obj;
    long recv_buf;
    long *game_state_mgr;
    u8 packet_type;
    u8 keepalive_err[16];
    u8 hmac_result[16];
    u8 auth_verify[16];
    u64 scratch_a;
    u8 *scratch_b;
    u32 scratch_c;
    u32 *scratch_d;
    u32 scratch_e;
    u32 decrypt_buf[5];
    u8 crypto_addr[4];
    u8 seq_number_buf[8];
    u8 recv_key[16];
    u8 stored_key[16];
    u64 recv_result;
    u64 uStack_198;
    u32 recv_size;
    u8 recv_size_pad[4];
    u8 source_addr[24];
    s16 source_port;
    int err_result[6];

    // Initialize error result
    err_result[0] = 0;
    nn::err::ErrorResultVariant_ctor((nn::err::ErrorResultVariant *)((u64)err_result | 4));
    *(u32 *)&recv_result = 0;
    nn::err::ErrorResultVariant_assign(
        (nn::err::ErrorResultVariant *)((u64)err_result | 4), (u32 *)&recv_result);
    FUN_71000b1c30(source_addr);

    // Step 1: Flush pending crypto state if flagged
    if (*(char *)&session->crypto_flush_pending != '\0') {
        crypto_param_a = FUN_71000b63d0();
        crypto_param_b = FUN_71000b63d0();
        if ((long)session->session_handle != 0) {
            FUN_7100129550((u64)session->session_handle, crypto_param_a, crypto_param_b);
        }
        session->crypto_flush_pending = 0;
    }

    // Step 2: Get game state manager from global
    game_state_mgr = *(long **)(*(long *)&PTR_DAT_71052a4080 +
                         (u64)*(u8 *)(*(long *)&PTR_DAT_71052a4080 + 0x162) * 8 + 0x168);
    if (game_state_mgr == (long *)0) goto LAB_710012b004;

    // Step 3: Check if spectator, determine crypto capability
    is_spectator = FUN_7100192590(*(u64 *)&PTR_DAT_71052a3df0);
    check = FUN_7100125e30((u64)session->session_handle);
    if ((check & 1) == 0) {
        has_crypto = 0;
    }
    else {
        has_crypto = (u32)FUN_7100129a90((u64)session->session_handle);
    }

    // Step 4: Receive packet from UDP socket into recv buffer (+0x70)
    FUN_71000ba450(&recv_result, (long)&session->socket, (long)session->recv_buffer,
                   LDN_MAX_RECV_SIZE, source_addr, recv_size_pad, &recv_size);
    FUN_71000bcf30(err_result, &recv_result);
    if (err_result[0] != 0) {
        // Receive error — report disconnect
        *(u32 *)&recv_result = LDN_ERR_RECV_DISCONNECT;
        nn::err::ErrorResultVariant_ctor((nn::err::ErrorResultVariant *)((u64)&recv_result | 4));
        *(u32 *)&scratch_a = 0;
        nn::err::ErrorResultVariant_assign(
            (nn::err::ErrorResultVariant *)((u64)&recv_result | 4), (u32 *)&scratch_a);
        goto LAB_710012ad58;
    }

    // Step 5: Validate source address matches expected peer
    check = FUN_71000b2820(source_addr, (long)session->session_handle + 0x50);
    if (((check & 1) != 0) && (source_port == *(s16 *)((long)session->session_handle + 0x96)))
        goto LAB_710012b004;

    // Step 6: Parse packet header from recv buffer
    packet_type = *(u8 *)((long)session->recv_buffer);
    payload_len = (int)FUN_71000bb9a0((u32 *)(param_1 + 0x71));
    header_end = payload_len + 5;
    if (header_end < recv_size) {
        if ((1 < packet_type) || (min_pkt_size = payload_len + 0x2f, recv_size < min_pkt_size))
            goto LAB_710012ad58;

        // Read end-of-frame marker and host flag from trailer
        resolved_type = FUN_71000bb9e0((u8 *)((long)session->recv_buffer + (u64)header_end));
        host_flag = (u32)FUN_71000bb9e0((u8 *)((long)session->recv_buffer + (u64)(payload_len + 6)));
        use_alt_serializer = 1 < resolved_type;
        recv_peer_flags = has_crypto ^ (host_flag & 1);
        clear_header = 0;
        resolved_type = 2;
        if ((recv_peer_flags & 1) == 0) {
            resolved_type = packet_type;
        }
        if ((((recv_peer_flags & 1) != 0) || (((has_crypto ^ 1) & 1) != 0)) || ((host_flag & 1) == 0))
            goto joined_r0x00710012aed4;

        // Has crypto context and packet is from host — attempt decryption
        check = FUN_71000b1f50((long)session->session_handle + 0x70);
        if ((check & 1) == 0) {
            *(u32 *)&scratch_a = 0;
            FUN_71000b1da0(&recv_result, (long)session->session_handle + 0x70, &scratch_a);
            FUN_71000bb980(crypto_addr, (u32)(scratch_a & 0xffffffff));
        }
        else {
            recv_result = 0;
            uStack_198 = 0;
            FUN_71000b2110(&scratch_a, (long)session->session_handle + 0x70, &recv_result);
            memcpy(crypto_addr, &recv_result, 4);
        }
        memcpy(seq_number_buf, (void *)(param_1 + (u64)(payload_len + 7) + 0x70), 8);

        if (packet_type == PACKET_TYPE_ENCRYPTED) {
            // Encrypted packet — decrypt and verify auth tag
            if ((u32)(payload_len + 0x3f) <= recv_size) {
                recv_buf = (long)session->recv_buffer;
                memcpy(recv_key, (void *)(recv_buf + (u64)(payload_len + 0xf)), 0x10);
                memcpy(stored_key, (void *)((long)session->encryption_key), 0x10);
                FUN_71001296b0(&recv_result, (u64)session->session_handle, recv_key, 0x20, decrypt_buf, 0x10);
                FUN_71000bcf30(err_result, &recv_result);
                scratch_b = crypto_addr;
                scratch_c = 0xc;
                scratch_e = 0x10;
                *(u32 *)&scratch_a = 1;
                scratch_d = decrypt_buf;
                FUN_71000b4e70(auth_verify, &recv_result, recv_buf + (u64)min_pkt_size, 0x10,
                               recv_buf + (u64)(payload_len + 0x1f), 0x10, &scratch_a);
                FUN_71000bcf30(err_result, auth_verify);
                if (err_result[0] == 0) {
                    FUN_71001297f0(hmac_result, (u64)session->session_handle, (long)session->encryption_iv, 0x100,
                                   auth_verify, 0x10);
                    FUN_71000bcf30(err_result, hmac_result);
                    clear_header = memcmp(&recv_result, auth_verify, 0x10);
                    hmac_verified = clear_header == 0;
                }
                else {
                    hmac_verified = false;
                }
                clear_header = 0;
                goto LAB_710012b040;
            }
LAB_710012b2bc:
            crypto_verified = true;
            clear_header = 0;
            packet_type = PACKET_TYPE_SYNC_REQUEST;
        }
        else if (packet_type == PACKET_TYPE_GAME_DATA) {
            // Unencrypted packet — verify HMAC signature
            if (recv_size < (u32)(payload_len + 0x12f)) goto LAB_710012b2bc;
            recv_buf = (long)session->recv_buffer;
            memcpy(recv_key, (void *)(recv_buf + (u64)(payload_len + 0xf)), 0x10);
            FUN_7100129590(&recv_result, (u64)session->session_handle, recv_key, 0x10, decrypt_buf, 0x10);
            FUN_71000bcf30(err_result, &recv_result);
            scratch_b = crypto_addr;
            scratch_c = 0xc;
            scratch_e = 0x10;
            *(u32 *)&scratch_a = 1;
            scratch_d = decrypt_buf;
            FUN_71000b4e70(auth_verify, &recv_result, recv_buf + (u64)min_pkt_size, 0x100,
                           recv_buf + (u64)(payload_len + 0x1f), 0x10, &scratch_a);
            FUN_71000bcf30(err_result, auth_verify);
            crypto_verified = err_result[0] == 0;
            clear_header = 0;
            packet_type = PACKET_TYPE_GAME_DATA;
        }
        else {
            crypto_verified = true;
            hmac_verified = true;
            clear_header = 0;
            if (packet_type == PACKET_TYPE_ENCRYPTED) goto LAB_710012b040;
        }
LAB_710012aed8:
        // Non-encrypted game data dispatch path
        if (((packet_type != PACKET_TYPE_GAME_DATA) || ((is_spectator & 1) != 0)) ||
           (check = (**(u64 (**)(long *))(*game_state_mgr + 0xe0))(game_state_mgr), (check & 1) == 0))
            goto LAB_710012ad58;

        // Process as unencrypted game data
        recv_buf = param_1 + 0xb18;
        FUN_710012f640(&scratch_a, recv_buf, param_1 + 0x75, payload_len);
        *(u32 *)&scratch_b = 0;
        scratch_a = 0x40000000;
        FUN_710012fba0(recv_buf, &scratch_a);
        peer_primary = (long *)FUN_710011be50((u64)game_state_mgr);
        *(u32 *)&scratch_b = 0;
        scratch_a = 0x40000000;
        (**(void (**)(long *, u64 *))(*peer_primary + 0x58))(peer_primary, &scratch_a);
        crypto_param_a = FUN_710011be50((u64)game_state_mgr);
        check = FUN_710012ed20(recv_buf, crypto_param_a);
        if ((check & 1) == 0) goto LAB_710012ad58;

        // Send reply back
        FUN_710012ba00((int *)&scratch_a, param_1, source_addr, recv_key, 0x10, &recv_result, 0x100,
                       crypto_verified, clear_header, use_alt_serializer);
        FUN_71000bcf30(err_result, &scratch_a);
        send_pending = *(char *)&session->send_pending;
    }
    else {
        // Short packet or no crypto — simplified path
        use_alt_serializer = false;
        clear_header = 1;
        resolved_type = packet_type;
joined_r0x00710012aed4:
        packet_type = resolved_type;
        crypto_verified = true;
        hmac_verified = true;
        if (packet_type != PACKET_TYPE_ENCRYPTED) goto LAB_710012aed8;
LAB_710012b040:
        // Encrypted packet dispatch — deserialize game state
        if (((is_spectator | (hmac_verified ^ 0xff)) & 1) == 0) {
            if (clear_header != 0) {
                // Clear 32 bytes after header for padding alignment
                memset((void *)(param_1 + (u64)header_end + 0x5c4), 0, 0x20);
                payload_len = payload_len + 0x20;
            }
            // Deserialize via primary peer
            peer_primary = (long *)FUN_710011be60((u64)game_state_mgr);
            recv_buf = param_1 + 0x75;
            if (!use_alt_serializer) {
                FUN_710012e410(&scratch_a, peer_primary, recv_buf, payload_len);
                peer_primary = (long *)FUN_710011be70((u64)game_state_mgr);
                if (peer_primary != (long *)0) goto LAB_710012b0b8;
                goto LAB_710012ad58;
            }
            (**(void (**)(void *, long *, long, int))(*peer_primary + 0x78))(
                &scratch_a, peer_primary, recv_buf, payload_len);
            peer_primary = (long *)FUN_710011be70((u64)game_state_mgr);
            if (peer_primary == (long *)0) goto LAB_710012ad58;
LAB_710012b0b8:
            // Find matching peer by ID
            for (iter_cur = (u64 *)(**(u64 *(**)(void))(*peer_primary + 0x18))();
                iter_end = (u64 *)(**(u64 *(**)(long *))(*peer_primary + 0x28))(peer_primary),
                iter_cur != iter_end;
                iter_cur = iter_cur + 1) {
                clear_header = (**(int (**)(void))(*(long *)*iter_cur + 0x18))();
                peer_match = (long *)FUN_710011be60((u64)game_state_mgr);
                peer_id_match = (**(int (**)(void))(*peer_match + 0x18))();
                if (clear_header == peer_id_match) {
                    peer_primary = (long *)*iter_cur;
                    if (peer_primary != (long *)0) goto LAB_710012b16c;
                    break;
                }
            }
            // Fallback: use next slot from secondary peer list
            secondary_obj = FUN_710011be70((u64)game_state_mgr);
            if ((*(u16 *)(secondary_obj + 10) == 0) ||
                (*(u16 *)(secondary_obj + 10) <= *(u16 *)(secondary_obj + 8)))
                goto LAB_710012ad58;
            peer_primary = *(long **)(*(long *)(secondary_obj + 0x10) + (u64)*(u16 *)(secondary_obj + 8) * 8);
            (**(void (**)(long *))(*peer_primary + 0x50))(peer_primary);
            *(s16 *)(secondary_obj + 8) = *(s16 *)(secondary_obj + 8) + 1;
            if (peer_primary == (long *)0) goto LAB_710012ad58;
LAB_710012b16c:
            // Deserialize into the matched peer
            if (use_alt_serializer) {
                (**(void (**)(void *, long *, long, int))(*peer_primary + 0x78))(
                    &scratch_a, peer_primary, recv_buf, payload_len);
            }
            else {
                FUN_710012e410(&scratch_a, peer_primary, recv_buf, payload_len);
            }
            *(u32 *)&scratch_b = 0;
            scratch_a = 0x40000000;
            (**(void (**)(long *, u64 *))(*peer_primary + 0x58))(peer_primary, &scratch_a);
            send_pending = *(char *)&session->send_pending;
            goto joined_r0x00710012b31c;
        }
LAB_710012ad58:
        send_pending = *(char *)&session->send_pending;
    }
joined_r0x00710012b31c:
    // Post-receive: handle send_pending flag and keepalive timer
    if (send_pending == '\0') {
        // No send pending — check if keepalive timer expired
        if (*(int *)((u8 *)session + app::LDN_KEEPALIVE_STATE_OFFSET) == 1) {
            scratch_a = 0;
            FUN_71000bb5d0(&scratch_a);
            if (*(u64 *)((u8 *)session + app::LDN_KEEPALIVE_DEADLINE_OFFSET) < scratch_a) {
                // Timer expired — dispatch keepalive
                *(u32 *)&scratch_a = 0;
                nn::err::ErrorResultVariant_ctor((nn::err::ErrorResultVariant *)((u64)&scratch_a | 4));
                decrypt_buf[0] = 0;
                nn::err::ErrorResultVariant_assign(
                    (nn::err::ErrorResultVariant *)((u64)&scratch_a | 4), decrypt_buf);
                FUN_71000bce50(keepalive_err, &scratch_a);
                FUN_71000b4180((long)((u8 *)session + app::LDN_KEEPALIVE_STATE_OFFSET), keepalive_err);
            }
        }
    }
    else {
        // Send pending — regenerate crypto material and send to all connected peers
        if ((has_crypto & 1) != 0) {
            FUN_71000b6400((long)session->encryption_key, 0x10);
            FUN_71000b6400((long)session->encryption_iv, 0x100);
        }
        if (*(char *)&session->num_peers != '\0') {
            has_crypto = 0;
            do {
                FUN_710012b530((u64)&scratch_a, param_1, has_crypto);
                has_crypto = has_crypto + 1;
            } while ((has_crypto & 0xff) < (u32)session->num_peers);
        }
        // Clear send_pending flag and reset keepalive timer
        session->send_pending = 0;
        game_state_mgr = (long *)FUN_71000bb680();
        recv_buf = *game_state_mgr;
        scratch_a = 0;
        FUN_71000bb5d0(&scratch_a);
        *(u64 *)((u8 *)session + app::LDN_KEEPALIVE_DEADLINE_OFFSET) = scratch_a + recv_buf * 2000;
    }
LAB_710012b004:
    FUN_71000b1cf0(source_addr);
    return 0xa0004;
}

// =============================================================================
// FUN_710012ba00 — Send reply packet with triple-send for UDP reliability
// Address: 0x710012ba00 | Size: 2,624 bytes
//
// Sends a reply/sync packet to a peer with 3x redundancy.
// The same packet is sent three times to compensate for UDP packet loss.
//
// param_1: output error result
// param_2: LDN transport session pointer
// param_3: source address (for logging)
// param_4: crypto data
// param_5: crypto data size
// param_6: IV material
// param_7: IV material size
// param_8: encryption enabled flag
// param_9: short packet mode flag
// param_10: use alternate serializer flag
// =============================================================================

void FUN_710012ba00(int *err_out, long param_2, u8 *source_addr, void *crypto_data, u32 crypto_size,
                    u64 *iv_material, u32 iv_size, u32 encryption_ok, u32 short_packet, u8 use_alt_serializer)
{
    app::LDNTransportSession *session = reinterpret_cast<app::LDNTransportSession *>(param_2);
    long send_buf_base;
    long loop_step;
    u32 payload_size_copy;
    u8 rand_byte;
    u32 is_host;
    long *peer_obj;
    u64 check;
    u64 peer_state;
    long send_buf_ptr;
    u64 *addr_iter;
    int total_packet_size;
    u64 payload_size_u64;
    u64 game_state_mgr;
    u8 prng_state[8];
    u8 *addr_buf_ptr;
    u32 addr_buf_size;
    u32 uStack_6f4;
    u64 addr_data;
    u32 addr_pad[48];
    u8 auth_tag[16];
    u32 hmac_buf[4];
    int send_result[5];
    u8 crypto_addr[4];
    u8 seq_buf[8];
    u8 reply_key[16];
    u8 reply_key_ext[20];
    u32 serialized_size;
    u32 payload_buf[344];

    // Get game state manager
    game_state_mgr = *(u64 *)
              (*(long *)&PTR_DAT_71052a4080 + (u64)*(u8 *)(*(long *)&PTR_DAT_71052a4080 + 0x162) * 8
              + 0x168);

    // Initialize error output
    *err_out = 0;
    nn::err::ErrorResultVariant_ctor((nn::err::ErrorResultVariant *)(err_out + 1));
    payload_buf[0] = 0;
    nn::err::ErrorResultVariant_assign((nn::err::ErrorResultVariant *)(err_out + 1), payload_buf);

    // Serialize reply data via local peer's serialize method
    if ((use_alt_serializer & 1) == 0) {
        check = FUN_710011be50(game_state_mgr);
        FUN_710012de50(prng_state, check, payload_buf, &serialized_size, LDN_MAX_REPLY_SIZE);
    }
    else {
        peer_obj = (long *)FUN_710011be50(game_state_mgr);
        (**(void (**)(u8 *, long *, u32 *, u32 *, u32))(*peer_obj + 0x70))(
            prng_state, peer_obj, payload_buf, &serialized_size, LDN_MAX_REPLY_SIZE);
    }
    FUN_71000bcf30(err_out, prng_state);

    if (*err_out == 0) {
        // Write reply packet header: type=ENCRYPTED, length, payload
        send_buf_base = (long)session->send_buffer;
        FUN_71000bb9d0((u8 *)send_buf_base, PACKET_TYPE_ENCRYPTED);
        FUN_71000bb980((u8 *)(param_2 + 0x5c5), serialized_size);
        memcpy((void *)(param_2 + 0x5c9), payload_buf, (u64)serialized_size);
        payload_size_copy = serialized_size;

        if ((short_packet & 1) == 0) {
            // Full packet: write sequence number, host flag, crypto material
            *(long *)&session->sequence_number = *(long *)&session->sequence_number + 1;
            FUN_71000bb9d0((u8 *)(send_buf_base + (u64)(serialized_size + 5)), PACKET_TYPE_SYNC_REQUEST);
            is_host = (u32)FUN_7100125e30((u64)session->session_handle);
            FUN_71000bb9d0((u8 *)(send_buf_base + (u64)(payload_size_copy + 6)), is_host & 1);
            FUN_71000bb930((u8 *)(send_buf_base + (u64)(payload_size_copy + 7)), session->sequence_number);
            is_host = serialized_size;
            payload_size_u64 = (u64)serialized_size;

            check = FUN_7100125e30((u64)session->session_handle);
            if ((((check & 1) == 0) ||
                (check = FUN_7100129a90((u64)session->session_handle), (check & 1) == 0)) ||
               ((encryption_ok & 1) == 0)) {
                // Unencrypted reply: fill 64 random padding bytes
                // The compiler unrolled this from the original binary — 27 individual bytes
                // at negative offsets from payload end, then 5 bytes forward, then 48 more
                FUN_7100138520(prng_state);
                rand_byte = FUN_7100138620(prng_state);
                send_buf_ptr = (long)session->send_buffer;
                *(u8 *)(send_buf_ptr + (u64)(is_host - 0x1b)) = rand_byte;
                rand_byte = FUN_7100138620(prng_state);
                *(u8 *)(send_buf_ptr + (u64)(is_host - 0x1a)) = rand_byte;
                rand_byte = FUN_7100138620(prng_state);
                *(u8 *)(send_buf_ptr + (u64)(is_host - 0x19)) = rand_byte;
                rand_byte = FUN_7100138620(prng_state);
                *(u8 *)(send_buf_ptr + (u64)(is_host - 0x18)) = rand_byte;
                rand_byte = FUN_7100138620(prng_state);
                *(u8 *)(send_buf_ptr + (u64)(is_host - 0x17)) = rand_byte;
                rand_byte = FUN_7100138620(prng_state);
                *(u8 *)(send_buf_ptr + (u64)(is_host - 0x16)) = rand_byte;
                rand_byte = FUN_7100138620(prng_state);
                *(u8 *)(send_buf_ptr + (u64)(is_host - 0x15)) = rand_byte;
                rand_byte = FUN_7100138620(prng_state);
                *(u8 *)(send_buf_ptr + (u64)(is_host - 0x14)) = rand_byte;
                rand_byte = FUN_7100138620(prng_state);
                *(u8 *)(send_buf_ptr + (u64)(is_host - 0x13)) = rand_byte;
                rand_byte = FUN_7100138620(prng_state);
                *(u8 *)(send_buf_ptr + (u64)(is_host - 0x12)) = rand_byte;
                rand_byte = FUN_7100138620(prng_state);
                *(u8 *)(send_buf_ptr + (u64)(is_host - 0x11)) = rand_byte;
                rand_byte = FUN_7100138620(prng_state);
                *(u8 *)(send_buf_ptr + (u64)(is_host - 0x10)) = rand_byte;
                rand_byte = FUN_7100138620(prng_state);
                *(u8 *)(send_buf_ptr + (u64)(is_host - 0xf)) = rand_byte;
                rand_byte = FUN_7100138620(prng_state);
                *(u8 *)(send_buf_ptr + (u64)(is_host - 0xe)) = rand_byte;
                rand_byte = FUN_7100138620(prng_state);
                *(u8 *)(send_buf_ptr + (u64)(is_host - 0xd)) = rand_byte;
                rand_byte = FUN_7100138620(prng_state);
                *(u8 *)(send_buf_ptr + (u64)(is_host - 0xc)) = rand_byte;
                rand_byte = FUN_7100138620(prng_state);
                *(u8 *)(send_buf_ptr + (u64)(is_host - 0xb)) = rand_byte;
                rand_byte = FUN_7100138620(prng_state);
                *(u8 *)(send_buf_ptr + (u64)(is_host - 10)) = rand_byte;
                rand_byte = FUN_7100138620(prng_state);
                *(u8 *)(send_buf_ptr + (u64)(is_host - 9)) = rand_byte;
                rand_byte = FUN_7100138620(prng_state);
                *(u8 *)(send_buf_ptr + (u64)(is_host - 8)) = rand_byte;
                rand_byte = FUN_7100138620(prng_state);
                *(u8 *)(send_buf_ptr + (u64)(is_host - 7)) = rand_byte;
                rand_byte = FUN_7100138620(prng_state);
                *(u8 *)(send_buf_ptr + (u64)(is_host - 6)) = rand_byte;
                rand_byte = FUN_7100138620(prng_state);
                *(u8 *)(send_buf_ptr + (u64)(is_host - 5)) = rand_byte;
                rand_byte = FUN_7100138620(prng_state);
                *(u8 *)(send_buf_ptr + (u64)(is_host - 4)) = rand_byte;
                rand_byte = FUN_7100138620(prng_state);
                *(u8 *)(send_buf_ptr + (u64)(is_host - 3)) = rand_byte;
                rand_byte = FUN_7100138620(prng_state);
                *(u8 *)(send_buf_ptr + (u64)(is_host - 2)) = rand_byte;
                rand_byte = FUN_7100138620(prng_state);
                *(u8 *)(send_buf_ptr + (u64)(is_host - 1)) = rand_byte;
                rand_byte = FUN_7100138620(prng_state);
                *(u8 *)(send_buf_ptr + payload_size_u64) = rand_byte;
                rand_byte = FUN_7100138620(prng_state);
                *(u8 *)(send_buf_ptr + (u64)(is_host + 1)) = rand_byte;
                rand_byte = FUN_7100138620(prng_state);
                *(u8 *)(send_buf_ptr + (u64)(is_host + 2)) = rand_byte;
                rand_byte = FUN_7100138620(prng_state);
                *(u8 *)(send_buf_ptr + (u64)(is_host + 3)) = rand_byte;
                rand_byte = FUN_7100138620(prng_state);
                *(u8 *)(send_buf_ptr + (u64)(is_host + 4)) = rand_byte;
                rand_byte = FUN_7100138620(prng_state);
                *(u8 *)(send_buf_ptr + (u64)(payload_size_copy + 0xf)) = rand_byte;
                rand_byte = FUN_7100138620(prng_state);
                *(u8 *)(send_buf_ptr + (u64)(payload_size_copy + 0x10)) = rand_byte;
                rand_byte = FUN_7100138620(prng_state);
                *(u8 *)(send_buf_ptr + (u64)(payload_size_copy + 0x11)) = rand_byte;
                rand_byte = FUN_7100138620(prng_state);
                *(u8 *)(send_buf_ptr + (u64)(payload_size_copy + 0x12)) = rand_byte;
                rand_byte = FUN_7100138620(prng_state);
                *(u8 *)(send_buf_ptr + (u64)(payload_size_copy + 0x13)) = rand_byte;
                rand_byte = FUN_7100138620(prng_state);
                *(u8 *)(send_buf_ptr + (u64)(payload_size_copy + 0x14)) = rand_byte;
                rand_byte = FUN_7100138620(prng_state);
                *(u8 *)(send_buf_ptr + (u64)(payload_size_copy + 0x15)) = rand_byte;
                rand_byte = FUN_7100138620(prng_state);
                *(u8 *)(send_buf_ptr + (u64)(payload_size_copy + 0x16)) = rand_byte;
                rand_byte = FUN_7100138620(prng_state);
                *(u8 *)(send_buf_ptr + (u64)(payload_size_copy + 0x17)) = rand_byte;
                rand_byte = FUN_7100138620(prng_state);
                *(u8 *)(send_buf_ptr + (u64)(payload_size_copy + 0x18)) = rand_byte;
                rand_byte = FUN_7100138620(prng_state);
                *(u8 *)(send_buf_ptr + (u64)(payload_size_copy + 0x19)) = rand_byte;
                rand_byte = FUN_7100138620(prng_state);
                *(u8 *)(send_buf_ptr + (u64)(payload_size_copy + 0x1a)) = rand_byte;
                rand_byte = FUN_7100138620(prng_state);
                *(u8 *)(send_buf_ptr + (u64)(payload_size_copy + 0x1b)) = rand_byte;
                rand_byte = FUN_7100138620(prng_state);
                *(u8 *)(send_buf_ptr + (u64)(payload_size_copy + 0x1c)) = rand_byte;
                rand_byte = FUN_7100138620(prng_state);
                *(u8 *)(send_buf_ptr + (u64)(payload_size_copy + 0x1d)) = rand_byte;
                rand_byte = FUN_7100138620(prng_state);
                *(u8 *)(send_buf_ptr + (u64)(payload_size_copy + 0x1e)) = rand_byte;
                rand_byte = FUN_7100138620(prng_state);
                *(u8 *)(send_buf_ptr + (u64)(payload_size_copy + 0x1f)) = rand_byte;
                rand_byte = FUN_7100138620(prng_state);
                *(u8 *)(send_buf_ptr + (u64)(payload_size_copy + 0x20)) = rand_byte;
                rand_byte = FUN_7100138620(prng_state);
                *(u8 *)(send_buf_ptr + (u64)(payload_size_copy + 0x21)) = rand_byte;
                rand_byte = FUN_7100138620(prng_state);
                *(u8 *)(send_buf_ptr + (u64)(payload_size_copy + 0x22)) = rand_byte;
                rand_byte = FUN_7100138620(prng_state);
                *(u8 *)(send_buf_ptr + (u64)(payload_size_copy + 0x23)) = rand_byte;
                rand_byte = FUN_7100138620(prng_state);
                *(u8 *)(send_buf_ptr + (u64)(payload_size_copy + 0x24)) = rand_byte;
                rand_byte = FUN_7100138620(prng_state);
                *(u8 *)(send_buf_ptr + (u64)(payload_size_copy + 0x25)) = rand_byte;
                rand_byte = FUN_7100138620(prng_state);
                *(u8 *)(send_buf_ptr + (u64)(payload_size_copy + 0x26)) = rand_byte;
                rand_byte = FUN_7100138620(prng_state);
                *(u8 *)(send_buf_ptr + (u64)(payload_size_copy + 0x27)) = rand_byte;
                rand_byte = FUN_7100138620(prng_state);
                *(u8 *)(send_buf_ptr + (u64)(payload_size_copy + 0x28)) = rand_byte;
                rand_byte = FUN_7100138620(prng_state);
                *(u8 *)(send_buf_ptr + (u64)(payload_size_copy + 0x29)) = rand_byte;
                rand_byte = FUN_7100138620(prng_state);
                *(u8 *)(send_buf_ptr + (u64)(payload_size_copy + 0x2a)) = rand_byte;
                rand_byte = FUN_7100138620(prng_state);
                *(u8 *)(send_buf_ptr + (u64)(payload_size_copy + 0x2b)) = rand_byte;
                rand_byte = FUN_7100138620(prng_state);
                *(u8 *)(send_buf_ptr + (u64)(payload_size_copy + 0x2c)) = rand_byte;
                rand_byte = FUN_7100138620(prng_state);
                *(u8 *)(send_buf_ptr + (u64)(payload_size_copy + 0x2d)) = rand_byte;
                rand_byte = FUN_7100138620(prng_state);
                *(u8 *)(send_buf_ptr + (u64)(payload_size_copy + 0x2e)) = rand_byte;
                rand_byte = FUN_7100138620(prng_state);
                *(u8 *)(send_buf_ptr + (u64)(payload_size_copy + 0x2f)) = rand_byte;
                rand_byte = FUN_7100138620(prng_state);
                *(u8 *)(send_buf_ptr + (u64)(payload_size_copy + 0x30)) = rand_byte;
                rand_byte = FUN_7100138620(prng_state);
                *(u8 *)(send_buf_ptr + (u64)(payload_size_copy + 0x31)) = rand_byte;
                rand_byte = FUN_7100138620(prng_state);
                *(u8 *)(send_buf_ptr + (u64)(payload_size_copy + 0x32)) = rand_byte;
                rand_byte = FUN_7100138620(prng_state);
                *(u8 *)(send_buf_ptr + (u64)(payload_size_copy + 0x33)) = rand_byte;
                rand_byte = FUN_7100138620(prng_state);
                *(u8 *)(send_buf_ptr + (u64)(payload_size_copy + 0x34)) = rand_byte;
                rand_byte = FUN_7100138620(prng_state);
                *(u8 *)(send_buf_ptr + (u64)(payload_size_copy + 0x35)) = rand_byte;
                rand_byte = FUN_7100138620(prng_state);
                *(u8 *)(send_buf_ptr + (u64)(payload_size_copy + 0x36)) = rand_byte;
                rand_byte = FUN_7100138620(prng_state);
                *(u8 *)(send_buf_ptr + (u64)(payload_size_copy + 0x37)) = rand_byte;
                rand_byte = FUN_7100138620(prng_state);
                *(u8 *)(send_buf_ptr + (u64)(payload_size_copy + 0x38)) = rand_byte;
                rand_byte = FUN_7100138620(prng_state);
                *(u8 *)(send_buf_ptr + (u64)(payload_size_copy + 0x39)) = rand_byte;
                rand_byte = FUN_7100138620(prng_state);
                *(u8 *)(send_buf_ptr + (u64)(payload_size_copy + 0x3a)) = rand_byte;
                rand_byte = FUN_7100138620(prng_state);
                *(u8 *)(send_buf_ptr + (u64)(payload_size_copy + 0x3b)) = rand_byte;
                rand_byte = FUN_7100138620(prng_state);
                *(u8 *)(send_buf_ptr + (u64)(payload_size_copy + 0x3c)) = rand_byte;
                rand_byte = FUN_7100138620(prng_state);
                *(u8 *)(send_buf_ptr + (u64)(payload_size_copy + 0x3d)) = rand_byte;
                rand_byte = FUN_7100138620(prng_state);
                *(u8 *)(send_buf_ptr + (u64)(payload_size_copy + 0x3e)) = rand_byte;
            }
            else {
                // Encrypted reply: generate key, encrypt, compute HMAC and auth tag
                if (0xf < crypto_size) {
                    crypto_size = 0x10;
                }
                FUN_71000b6400((long)reply_key, 0x10);
                memcpy(reply_key_ext, crypto_data, (u64)crypto_size);
                peer_state = FUN_710011bfe0(game_state_mgr);
                if ((peer_state & 1) == 0) {
                    FUN_7100119a50(game_state_mgr, reply_key, 0x20);
                    FUN_7100125f90((u64)session->session_handle);
                    memcpy((void *)(param_2 + (u64)(is_host - 0x1b) + 0x5c4), reply_key, 0x20);
                }
                memcpy((void *)(param_2 + (u64)(payload_size_copy + 0xf) + 0x5c4), reply_key, 0x10);

                // Build crypto address for auth tag
                check = FUN_71000b1f50((long)session->session_handle + 0x70);
                if ((check & 1) == 0) {
                    send_result[0] = 0;
                    FUN_71000b1da0(prng_state, (long)session->session_handle + 0x70, send_result);
                    FUN_71000bb980(crypto_addr, (u32)send_result[0]);
                }
                else {
                    *(u64 *)prng_state = 0;
                    addr_buf_ptr = (u8 *)0;
                    FUN_71000b2110(send_result, (long)session->session_handle + 0x70, prng_state);
                    memcpy(crypto_addr, prng_state, 4);
                }
                FUN_71000bb930(seq_buf, session->sequence_number);

                // AES decrypt + HMAC + generate auth tag
                FUN_71001296b0(prng_state, (u64)session->session_handle, reply_key, 0x20, send_result, 0x10);
                FUN_71000bcf30(err_out, prng_state);
                FUN_71001297f0(prng_state, (u64)session->session_handle, (long)iv_material, iv_size, hmac_buf, 0x10);
                FUN_71000bcf30(err_out, prng_state);
                addr_buf_size = 0xc;
                *(u32 *)prng_state = 1;
                addr_pad[0] = 0x10;
                addr_buf_ptr = crypto_addr;
                addr_data = (u64)send_result;
                FUN_71000b4c70((int *)auth_tag, (long)session->send_buffer + (u64)(payload_size_copy + 0x2f),
                               (long)hmac_buf, 0x10,
                               (long)session->send_buffer + (u64)(payload_size_copy + 0x1f), 0x10, prng_state);
            }
            total_packet_size = serialized_size + 0x3f;
        }
        else {
            // Short packet mode — no sequence/key/padding overhead
            total_packet_size = serialized_size - 0x1b;
        }

        // Build destination address from source
        FUN_71000b1c60(reply_key, (long)source_addr);
        addr_buf_ptr = (u8 *)((long)&addr_data + 4);
        *(u64 *)prng_state = (u64)(*(long *)&PTR_DAT_71052a3c30 + 0x10);
        addr_buf_size = 0xc0;
        *(u8 *)((long)&addr_data + 4) = 0;
        send_buf_ptr = 0;
        addr_iter = (u64 *)prng_state;
        do {
            *(u16 *)((long)addr_iter + 0x1d) = 0;
            loop_step = send_buf_ptr + 4;
            *(u8 *)((long)addr_iter + 0x1f) = 0;
            addr_iter = (u64 *)((long)prng_state + loop_step);
            *(u8 *)((long)addr_pad + send_buf_ptr) = 0;
            send_buf_ptr = loop_step;
        } while (loop_step != 0xc0);
        uStack_6f4 = 0;
        *(u32 *)&addr_data = 0;
        FUN_71000b1fa0(reply_key, (void *)*(u64 *)prng_state);

        // Triple-send for UDP reliability — send same packet 3 times
        param_2 = (long)&session->socket;

        // Send #1
        FUN_71000ba5c0(send_result, param_2, send_buf_base, total_packet_size, reply_key, auth_tag);
        FUN_71000bcf30(err_out, send_result);
        if (*err_out != 0) {
            send_result[0] = LDN_ERR_SEND_FAIL;
            nn::err::ErrorResultVariant_ctor((nn::err::ErrorResultVariant *)((u64)send_result | 4));
            hmac_buf[0] = 0;
            nn::err::ErrorResultVariant_assign(
                (nn::err::ErrorResultVariant *)((u64)send_result | 4), hmac_buf);
            if (*err_out != send_result[0]) {
                FUN_7100121af0(*(u64 *)(*(long *)&PTR_DAT_71052a4080 + 8));
            }
        }

        // Send #2
        FUN_71000ba5c0(send_result, param_2, send_buf_base, total_packet_size, reply_key, auth_tag);
        FUN_71000bcf30(err_out, send_result);
        if (*err_out != 0) {
            send_result[0] = LDN_ERR_SEND_FAIL;
            nn::err::ErrorResultVariant_ctor((nn::err::ErrorResultVariant *)((u64)send_result | 4));
            hmac_buf[0] = 0;
            nn::err::ErrorResultVariant_assign(
                (nn::err::ErrorResultVariant *)((u64)send_result | 4), hmac_buf);
            if (*err_out != send_result[0]) {
                FUN_7100121af0(*(u64 *)(*(long *)&PTR_DAT_71052a4080 + 8));
            }
        }

        // Send #3
        FUN_71000ba5c0(send_result, param_2, send_buf_base, total_packet_size, reply_key, auth_tag);
        FUN_71000bcf30(err_out, send_result);
        if (*err_out != 0) {
            send_result[0] = LDN_ERR_SEND_FAIL;
            nn::err::ErrorResultVariant_ctor((nn::err::ErrorResultVariant *)((u64)send_result | 4));
            hmac_buf[0] = 0;
            nn::err::ErrorResultVariant_assign(
                (nn::err::ErrorResultVariant *)((u64)send_result | 4), hmac_buf);
            if (*err_out != send_result[0]) {
                FUN_7100121af0(*(u64 *)(*(long *)&PTR_DAT_71052a4080 + 8));
            }
        }

        FUN_71000b1cf0(reply_key);
    }
    return;
}

// NOTE: Small helper functions (FUN_7100125e30, FUN_7100125f90, FUN_7100129a90,
// FUN_7100125cc0, FUN_7100125d00, FUN_7100128210, FUN_710012cf70,
// FUN_710012eb20-ebc0) are already compiled in fun_easy_*.cpp and
// fun_batch_*.cpp files. All confirmed matching 100%.
// See src/docs/networking.md for their documented roles in the frame exchange.

// FUN_710012cea0 — already compiled in fun_easy_004.cpp (100% match)

extern u16 FUN_710012cea0(long);

// =============================================================================
// FUN_710012ed20 — Frame state condition check
// Address: 0x710012ed20 | Size: 744 bytes
//
// Validates whether the received frame data meets all configured conditions
// before applying it to the game state. Checks include:
//   - Frame range validation (vtable[0x28], vtable[0x30])
//   - Player ID matching (vtable[0x10])
//   - Match type comparison (FUN_710012cea0)
//   - Online connection check (vtable[0x38])
//   - Duplicate frame detection (vtable[0x20] == vtable[0x30])
//   - Per-channel value matching against allowed value lists
//
// Returns true (1) if all conditions pass, false (0) if any check fails.
// =============================================================================

// =============================================================================
// FUN_710012cf80 — Get channel value by index
// Address: 0x710012cf80 | Size: 128 bytes
//
// Reads a u32 value from the per-channel data array in the frame state struct.
// Channel index (param_3) must be 0..5. Output written to *param_4.
// =============================================================================

void FUN_710012cf80(u64 err_out, long param_2, u8 slot_index, u32 *value_out)
{
    u32 result[4];
    u32 zero[2];

    if ((value_out == (u32 *)0) || (FRAME_CONDITION_NUM_SLOTS - 1 < slot_index)) {
        result[0] = LDN_ERR_INVALID_STATE;
    }
    else {
        // Read the first match value from the requested slot
        // [derived: slot_values at +0x28 is accessed as flat u32 array at param_2 + slot*4 + 0x20]
        // NOTE: +0x20 with u32 stride means this reads the slot_values[slot_index][0] via
        // the FrameStateCondition layout (+0x28 - 0x8 offset due to param_2 pointing at +0x8)
        *value_out = *(u32 *)(param_2 + (u64)slot_index * 4 + 0x20);
        result[0] = 0;
    }
    nn::err::ErrorResultVariant_ctor((nn::err::ErrorResultVariant *)((u64)result | 4));
    zero[0] = 0;
    nn::err::ErrorResultVariant_assign(
        (nn::err::ErrorResultVariant *)((u64)result | 4), zero);
    FUN_71000bce50((void *)err_out, result);
}

u64 FUN_710012ed20(long param_1, long *param_2)
{
    FrameStateCondition *cond = reinterpret_cast<FrameStateCondition *>(param_1);
    u16 range_bound;
    bool found;
    u16 frame_val;
    s16 frame_a;
    s16 frame_b;
    int peer_id;
    int type_val;
    u64 check_result;
    u32 bits;
    long offset;
    long scan_offset;
    u32 *scan_ptr;
    u64 entry_count_u64;
    u32 *slot_ptr;
    long slot_base;
    int err_buf[4];
    u32 channel_value;

    // Get the peer's player ID via vtable[0x10]
    peer_id = (**(int (**)(long *))(*param_2 + 0x10))(param_2);
    bits = cond->dirty_bits;

    // Check bit 4: player ID filter
    if (((bits >> 4 & 1) == 0) || (cond->player_id == peer_id)) {
        // Check bit 0: primary frame range filter
        if (((bits & 1) != 0) &&
           ((range_bound = cond->frame_range_max, range_bound != FRAME_RANGE_NO_FILTER &&
            (cond->frame_range_min != -1)))) {
            frame_val = (**(u16 (**)(long *))(*param_2 + 0x28))(param_2);
            if (frame_val < range_bound) {
                return 0;
            }
            range_bound = (u16)cond->frame_range_min;
            frame_val = (**(u16 (**)(long *))(*param_2 + 0x28))(param_2);
            if (range_bound < frame_val) {
                return 0;
            }
            bits = cond->dirty_bits;
        }
        // Check bit 1: secondary frame range filter
        if ((((bits >> 1 & 1) != 0) &&
            (range_bound = cond->secondary_range_max, range_bound != FRAME_RANGE_NO_FILTER)) &&
           (cond->secondary_range_min != -1)) {
            frame_val = (**(u16 (**)(long *))(*param_2 + 0x30))(param_2);
            if (frame_val < range_bound) {
                return 0;
            }
            range_bound = (u16)cond->secondary_range_min;
            frame_val = (**(u16 (**)(long *))(*param_2 + 0x30))(param_2);
            if (range_bound < frame_val) {
                return 0;
            }
            bits = cond->dirty_bits;
        }
        // Check bit 5: match type filter
        if ((((bits >> 5 & 1) == 0) ||
            (peer_id = cond->match_type, type_val = (int)FUN_710012cea0((long)param_2), peer_id == type_val)) &&
           // Check require_online flag
           ((cond->require_online == 0 ||
            (check_result = (**(u64 (**)(long *))(*param_2 + 0x38))(param_2), (check_result & 1) != 0)))) {
            // Check reject_duplicate_frame flag
            if (cond->reject_duplicate_frame != 0) {
                frame_a = (**(s16 (**)(long *))(*param_2 + 0x20))(param_2);
                frame_b = (**(s16 (**)(long *))(*param_2 + 0x30))(param_2);
                if (frame_a == frame_b) {
                    return 0;
                }
            }
            // Check per-slot filters (bits 6..11)
            check_result = 0;
            slot_ptr = &cond->slot_values[0][3]; // puVar14 = param_1 + 0x34
            slot_base = param_1 + 0x28;
            do {
                if ((cond->dirty_bits & (0x40 << (u64)((u32)check_result & 0x1f))) != 0) {
                    if (cond->slot_mode[check_result] == 0) {
                        // Match-value mode
                        if (cond->slot_entry_count[check_result] != 0) {
                            channel_value = 0;
                            FUN_710012cf80((u64)err_buf, (long)param_2, (u8)(check_result & 0xff), &channel_value);
                            if (err_buf[0] != 0) {
                                return 0;
                            }
                            bits = cond->slot_entry_count[check_result];
                            entry_count_u64 = (u64)bits;
                            if (bits == 0) {
                                return 0;
                            }
                            // Vectorized 4-at-a-time comparison
                            if (entry_count_u64 - 1 < 3) {
                                scan_offset = 0;
                                found = false;
                            }
                            else {
                                scan_offset = 0;
                                found = false;
                                scan_ptr = slot_ptr;
                                do {
                                    scan_offset = scan_offset + 4;
                                    found = (bool)(found | channel_value == scan_ptr[-3] | channel_value == scan_ptr[-2] |
                                                   channel_value == scan_ptr[-1] | channel_value == *scan_ptr);
                                    scan_ptr = scan_ptr + 4;
                                } while (entry_count_u64 - (entry_count_u64 & 3) != (u64)scan_offset);
                            }
                            // Remainder comparison
                            if ((bits & 3) != 0) {
                                offset = -(u64)(entry_count_u64 & 3);
                                scan_ptr = (u32 *)(slot_base + scan_offset * 4);
                                do {
                                    offset = offset + 1;
                                    found = (bool)(found | channel_value == *scan_ptr);
                                    scan_ptr = scan_ptr + 1;
                                } while (offset != 0);
                            }
                            if (!found) {
                                return 0;
                            }
                        }
                    }
                    else {
                        // Range mode
                        channel_value = 0;
                        FUN_710012cf80((u64)err_buf, (long)param_2, (u8)(check_result & 0xff), &channel_value);
                        if (err_buf[0] != 0) {
                            return 0;
                        }
                        if (channel_value < cond->slot_range_min[check_result]) {
                            return 0;
                        }
                        if (cond->slot_range_max[check_result] < channel_value) {
                            return 0;
                        }
                    }
                }
                check_result = check_result + 1;
                slot_ptr = slot_ptr + 0x14;
                slot_base = slot_base + 0x50;
                if (5 < check_result) {
                    return 1;
                }
            } while (true);
        }
    }
    return 0;
}

// =============================================================================
// Frame state slot management functions
//
// The frame state struct has 6 "slots" (channels) at stride 0x50, starting
// at offset +0x28. Each slot can have:
//   - A single match value (+0x28 + slot*0x50)
//   - A min/max range (+0x220/+0x238 + slot*4)
//   - A mode flag (+0x250 + slot): 0=match-value, 1=range
//   - An entry count (+0x208 + slot*4)
//
// Dirty bits at +0x260 track which slots changed (bits 6..11 for slots 0..5).
// =============================================================================

extern void FUN_710014f0b0(void);
extern void FUN_710014f150(void);
extern u8 PTR_DAT_71052a4ba0;
extern u8 PTR_DAT_71052a4870;

// FUN_710012ebe0 — Set slot to match single value
// Address: 0x710012ebe0 | Size: 160 bytes

void FUN_710012ebe0(u64 err_out, long param_2, u32 slot_index, u32 match_value)
{
    FrameStateCondition *cond = reinterpret_cast<FrameStateCondition *>(param_2);
    u32 result[4];
    u32 zero[2];

    if (slot_index < FRAME_CONDITION_NUM_SLOTS) {
        cond->slot_values[slot_index][0] = match_value;
        cond->slot_entry_count[slot_index] = 1;
        cond->slot_mode[slot_index] = 0;   // match-value mode
        cond->dirty_bits = cond->dirty_bits | (1 << (u64)(slot_index + 6 & 0x1f));
        result[0] = 0;
    }
    else {
        result[0] = LDN_ERR_INVALID_STATE;
    }
    nn::err::ErrorResultVariant_ctor((nn::err::ErrorResultVariant *)((u64)result | 4));
    zero[0] = 0;
    nn::err::ErrorResultVariant_assign(
        (nn::err::ErrorResultVariant *)((u64)result | 4), zero);
    FUN_71000bce50((void *)err_out, result);
}

// FUN_710012ec80 — Set slot to match value range [min, max]
// Address: 0x710012ec80 | Size: 160 bytes

void FUN_710012ec80(u64 err_out, long param_2, u32 slot_index, u32 range_min, u32 range_max)
{
    FrameStateCondition *cond = reinterpret_cast<FrameStateCondition *>(param_2);
    u32 result[4];
    u32 zero[2];

    if ((slot_index < FRAME_CONDITION_NUM_SLOTS) && (range_min <= range_max)) {
        cond->slot_range_min[slot_index] = range_min;
        cond->slot_range_max[slot_index] = range_max;
        cond->slot_mode[slot_index] = 1;   // range mode
        cond->dirty_bits = cond->dirty_bits | (1 << (u64)(slot_index + 6 & 0x1f));
        result[0] = 0;
    }
    else {
        result[0] = LDN_ERR_INVALID_STATE;
    }
    nn::err::ErrorResultVariant_ctor((nn::err::ErrorResultVariant *)((u64)result | 4));
    zero[0] = 0;
    nn::err::ErrorResultVariant_assign(
        (nn::err::ErrorResultVariant *)((u64)result | 4), zero);
    FUN_71000bce50((void *)err_out, result);
}

// FUN_710012ea10 — Reset all 6 frame state slots to defaults
// Address: 0x710012ea10 | Size: 272 bytes
//
// Clears all slot data, sets frame ranges to 0xFFFF (no filter),
// sets both bool flags to true, and resets the dirty bitmask.
// Final field at +0xc is set to 100 (default tick count).

void FUN_710012ea10(long param_1)
{
    FrameStateCondition *cond = reinterpret_cast<FrameStateCondition *>(param_1);

    FUN_710014f0b0();

    // Clear filter parameters
    cond->player_id = 0;
    cond->match_type = 0;

    // Set all frame ranges to "no filter" (0xFFFF)
    *(u64 *)&cond->frame_range_min = 0xffffffffffffffffULL;

    // Enable both boolean flags
    cond->require_online = 1;
    cond->reject_duplicate_frame = 1;

    // Clear dirty bits
    cond->dirty_bits = 0;

    // Reset all 6 slots
    // Slot 0
    memset(cond->slot_values[0], 0, 0x50);
    cond->slot_entry_count[0] = 0;
    cond->slot_range_min[0] = 0;
    cond->slot_range_max[0] = 0;
    cond->slot_mode[0] = 0;
    // Slot 1
    memset(cond->slot_values[1], 0, 0x50);
    cond->slot_entry_count[1] = 0;
    cond->slot_range_min[1] = 0;
    cond->slot_range_max[1] = 0;
    cond->slot_mode[1] = 0;
    // Slot 2
    memset(cond->slot_values[2], 0, 0x50);
    cond->slot_entry_count[2] = 0;
    cond->slot_range_min[2] = 0;
    cond->slot_range_max[2] = 0;
    cond->slot_mode[2] = 0;
    // Slot 3
    memset(cond->slot_values[3], 0, 0x50);
    cond->slot_entry_count[3] = 0;
    cond->slot_range_min[3] = 0;
    cond->slot_range_max[3] = 0;
    cond->slot_mode[3] = 0;
    // Slot 4
    memset(cond->slot_values[4], 0, 0x50);
    cond->slot_entry_count[4] = 0;
    cond->slot_range_min[4] = 0;
    cond->slot_range_max[4] = 0;
    cond->slot_mode[4] = 0;
    // Slot 5
    memset(cond->slot_values[5], 0, 0x50);
    cond->slot_entry_count[5] = 0;
    cond->slot_range_min[5] = 0;
    cond->slot_range_max[5] = 0;
    cond->slot_mode[5] = 0;

    // Default tick count
    cond->tick_count = FRAME_CONDITION_DEFAULT_TICK_COUNT;
}

// FUN_710012fbb0 — Frame data sub-object constructor
// Address: 0x710012fbb0 | Size: 128 bytes
// Initializes a small frame data object with multiple vtable pointers.

void FUN_710012fbb0(long *param_1)
{
    FrameDataSubObject *obj = reinterpret_cast<FrameDataSubObject *>(param_1);
    u8 *vtable_a;
    u8 *vtable_b;

    FUN_710014f150();

    vtable_a = &PTR_DAT_71052a4ba0 + 0x10;
    vtable_b = &PTR_DAT_71052a4870 + 0x10;

    // Set vtable pointers
    // [derived: FUN_710012fbb0 sets 3 vtable slots from PTR_DAT_71052a4ba0 and PTR_DAT_71052a4870]
    obj->vtable_secondary = &PTR_DAT_71052a4ba0 + 0x50;
    obj->vtable_tertiary = vtable_b;
    obj->vtable_primary = vtable_a;

    // Initialize inline data region
    obj->inline_data = 0;
    obj->field_60 = 0;
    obj->field_3c = 0;
    obj->field_40 = 0;

    // Self-pointer to inline data at +0x34
    obj->inline_data_ptr = reinterpret_cast<u8 *>(param_1) + 0x34;
    obj->data_offset = 0x28;

    // Clear remaining fields
    obj->field_48 = 0;
    *(u64 *)(reinterpret_cast<u8 *>(param_1) + 0x4a) = 0;
    *(u64 *)(reinterpret_cast<u8 *>(param_1) + 0x52) = 0;
    obj->field_5a = 0;
    obj->field_5c = 0;
    *(u32 *)(param_1 + 6) = 0;
}
