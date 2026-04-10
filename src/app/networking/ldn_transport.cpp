// LDN Transport Layer — game-level data exchange over nn::ldn
// Address range: 0x710016xxxx (LDN wrappers), 0x71000bxxxx (socket ops),
//                0x710012xxxx (frame data send/recv)
//
// This layer sits between the game's frame sync logic and the nn::ldn SDK.
// After nn::ldn::Connect establishes the LDN session, these functions:
//   1. Get the IPv4 address assigned by the LDN network
//   2. Open a UDP socket on port 12345 (0x3039) for game data
//   3. Send/receive serialized game state each frame
//   4. Handle encryption for online (relay) mode
//
// The flow is:
//   ldn_connect_with_retry (0x710016f0c0)
//     -> ldn_post_connect_get_config (0x710016f400)
//     -> ldn_post_connect_setup_udp  (0x710016da00)
//     -> ldn_connect_setup_socket    (0x710016c120)
//     -> set job "LdnBackgroundProcessJob::WaitConnectNetworkEvent"
//
// Then per-frame:
//   ldn_recv_and_process (0x710012ac30)
//     -> RecvFrom on UDP socket
//     -> decrypt if encrypted mode
//     -> dispatch to game state deserializer
//     -> trigger ldn_send_game_state for each peer
//
//   ldn_send_game_state (0x710012b530)
//     -> serialize game state via vtable call
//     -> build packet header (type, length, sequence, key/padding)
//     -> SendTo on UDP socket
//
// See include/app/LDNSession.h for struct layouts and constants.
// See src/docs/networking.md for full protocol documentation.

#include "app/LDNSession.h"

// =========================================================================
// FUN_710016b2f0 — LDN error code translator
// Address: 0x710016b2f0
//
// Translates nn::ldn SDK Result codes into game-specific error codes.
// nn::ldn Results use module ID 0xcb (203). The function extracts the
// module (bits 0..8) and category (bits 9..21) to map:
//
//   Result == 0                             -> LDN_OK
//   Module != 0xcb                          -> LDN_ERR_UNKNOWN (0x10c08)
//   Module == 0xcb:
//     category 0x11..0x15                   -> LDN_ERR_GENERAL_NET (0xa46e) + SDK detail
//     category 0x16..0x1a:
//       detail_field == 0x3000              -> LDN_ERR_CRYPTO_B (0xc421)
//       detail_field == 0x2e00              -> LDN_ERR_CRYPTO_A (0xc420)
//       else                               -> LDN_ERR_GENERAL_NET + SDK detail
//     category 2                            -> LDN_ERR_NETWORK_GENERAL (0x6c1b)
//     category 4:
//       detail 0x8600                       -> LDN_ERR_CONNECT_TRANSIENT (0x6838)
//       detail 0x8400                       -> LDN_ERR_DISCONNECTED (0x6c0e)
//       detail 0x8200                       -> LDN_ERR_CONNECT_REJECTED (0x6c1c)
//       else                               -> LDN_ERR_GENERAL_NET + SDK detail
//     category 7 (via case 5)              -> LDN_ERR_GENERAL_NET + SDK detail
//     category 9 (via case 7)              -> LDN_ERR_SPECTATOR_JOIN (0x6422)
//     default                               -> LDN_ERR_UNKNOWN (0x10c08)
// =========================================================================

// =========================================================================
// FUN_710016af60 — Get LDN connection parameter
// Address: 0x710016af60
// Body: 0x710016af60 - 0x710016af77 (24 bytes, trivial accessor)
//
// Returns connection parameter from session's sub-object:
//   if (*(session + 0x48) != 0)
//     return *(*( session + 0x48) + 8);
//   return 0;
// =========================================================================

// =========================================================================
// FUN_710016f400 — Post-connect: get network config
// Address: 0x710016f400
//
// Called immediately after nn::ldn::Connect succeeds in ldn_connect_with_retry.
// Calls nn::ldn::GetNetworkConfig to retrieve the LDN network configuration
// into connect_ctx + 0x2f0, then translates any error through
// ldn_translate_error (FUN_710016b2f0).
//
// Pseudocode:
//   sdk_result = nn::ldn::GetNetworkConfig(connect_ctx + 0x2f0);
//   session_handle = *(connect_ctx + 0x70);
//   ldn_translate_error(translated, session_handle, sdk_result);
//   if (translated == 0) return OK;
//   else return translated;
// =========================================================================

// =========================================================================
// FUN_710016da00 — Post-connect: set up UDP broadcast socket
// Address: 0x710016da00
//
// Called after ldn_post_connect_get_config succeeds.
// Sets up the UDP socket used for game data broadcast.
//
// Steps:
//   1. nn::ldn::GetIpv4Address(&addr, &mask) — get LDN-assigned IP
//   2. nn::ldn::MakeBroadcastAddress(addr, mask) — compute broadcast addr
//   3. Create address object for broadcast:12345 (port 0x3039)
//   4. Lock session mutex at +0x80
//   5. Register address with session socket list at +0x58
//   6. Set entry size to 0x10
//   7. Unlock mutex and destroy address object
//
// The broadcast address allows sending game data to all peers on the
// LDN network simultaneously. Port 12345 is hardcoded.
// =========================================================================

// =========================================================================
// FUN_710016c120 — Connect flow: set up data exchange socket
// Address: 0x710016c120
//
// Called after UDP broadcast setup. Creates and registers the data socket.
// Protected by mutex at session + 0x1770.
//
// If session+0x1768 != 0 (has socket descriptor):
//   1. Create UDP socket: AF_INET(2), SOCK_DGRAM(2), IPPROTO_UDP(0x11)
//      via FUN_71000b9f60
//   2. Bind to INADDR_ANY:12345 via FUN_71000ba0c0
//   3. Fall through to transport registration
//
// Transport registration (both paths):
//   Gets two transport managers via PTR_DAT_71052a3dc8:
//     transport_a = FUN_71001623f0(global) — primary transport
//     transport_b = FUN_7100162410(global) — secondary transport
//   For each: register socket via FUN_71000bedd0, then FUN_71000bed60
//   All four registrations must succeed.
// =========================================================================

// =========================================================================
// FUN_710017ddf0 — Set LDN mode
// Address: 0x710017ddf0
// Trivial: *(session + 0x474) = mode;
// Called with mode=2 during connect to mark session as LDN mode.
// =========================================================================

// =========================================================================
// FUN_71000b9f60 — Create socket
// Address: 0x71000b9f60
//
// Creates an AF_INET socket. Only family=2 is supported.
//   socket_desc[2] = 2 (family marker)
//   fd = nn::socket::Socket(2, type, protocol)
//   socket_desc[0] = fd
//   socket_desc[1]++ (generation counter — tracks socket recycling)
// Returns 0x10c07 if family != 2.
// =========================================================================

// =========================================================================
// FUN_71000ba5c0 — SendTo wrapper
// Address: 0x71000ba5c0
//
// Sends data via nn::socket::SendTo.
//   1. Check fd >= 0 (return 0x10c07 if invalid)
//   2. Build SockAddr from address object via FUN_71000baa00
//   3. nn::socket::SendTo(fd, data, len, 0, sockaddr, 0x10)
//   4. On failure: log error via FUN_71000b1fa0, return socket error
//   5. On success: optionally write bytes_sent, return OK
//
// Address object layout:
//   FUN_71000ba920 initializes it
//   FUN_71000ba930 sets address/port from params
//   FUN_71000baa00 returns the raw sockaddr pointer
// =========================================================================

// =========================================================================
// FUN_71000ba450 — RecvFrom wrapper
// Address: 0x71000ba450
//
// Receives data via nn::socket::RecvFrom with MSG_DONTWAIT (0x80).
//   1. Check fd >= 0 (return 0x10c07 if invalid)
//   2. nn::socket::RecvFrom(fd, buffer, max_len, 0x80, sockaddr, &addrlen)
//   3. On error:
//      - errno != 9 (EBADF): return would-block via FUN_71000b9de0
//      - errno == 9 && fd changed: return 0x2c09 (disconnect)
//      - errno == 9 && fd same: return 0x10c07 (invalid state)
//   4. On 0 bytes: return 0x2c09 (disconnect)
//   5. On success: copy source address via FUN_71000ba9b0, write bytes_recv
// =========================================================================

// =========================================================================
// FUN_710012b530 — Send game state to a peer
// Address: 0x710012b530
//
// Called for each connected peer to send the current frame's game state.
// param_3 is the peer index (must be < 2).
//
// Packet construction in send_buffer (session + 0x5C4):
//   1. Serialize game state via vtable[0x28] into send_buffer+5
//      (max 0x425 bytes, actual length returned in local_5c4)
//   2. send_buffer[0] = packet_type (0 = gamedata)
//   3. send_buffer[1..4] = payload_length (4 bytes, little-endian)
//   4. send_buffer[N+5] = 2 (end-of-frame-data marker)
//   5. send_buffer[N+6] = is_host (from FUN_7100125e30)
//   6. send_buffer[N+7..14] = sequence_number++ (from session+0xDC8)
//   7. send_buffer[N+15..24] = encryption_key[16] (from session+0xDD0)
//
//   If UNENCRYPTED (is_host=0 or not relay mode):
//     Fill 256 bytes of random padding via xorshift128_7100138620 (PRNG)
//     Total packet: payload_len + 0x12F bytes
//
//   If ENCRYPTED (online relay mode):
//     Get peer address from socket handle
//     Encrypt via FUN_7100129590 (AES encrypt)
//     Generate auth tag via FUN_71000b4c70
//     Total packet: payload_len + 0x3F bytes
//
//   8. SendTo via FUN_71000ba5c0 to session+0x60 (socket descriptor)
//   9. On send error: set game error 0x4c0d, trigger disconnect if different
// =========================================================================

// =========================================================================
// FUN_710012ac30 — Receive and process game data
// Address: 0x710012ac30
// Returns: 0xa0004 (always — success/continue code)
//
// The main per-frame receive function called from the network tick.
//
// Flow:
//   1. If crypto_pending (session+0xDC0): flush pending crypto state
//      via FUN_7100129550
//
//   2. Get game state manager via PTR_DAT_71052a4080 global
//
//   3. Check connection mode:
//      - bVar8 = FUN_7100192590() — is spectator?
//      - uVar10 = FUN_7100129a90() — has crypto context? (only if is_host)
//
//   4. RecvFrom(socket+0x60, recv_buffer+0x70, 0x554, MSG_DONTWAIT)
//      On error: return 0x2c09 (peer disconnected)
//
//   5. Validate source address matches expected peer:
//      FUN_71000b2820(src_addr, session+0x58+0x50)
//      Also check port matches session+0x58+0x96
//
//   6. Parse received packet:
//      - bVar25 = recv_buffer[0] (packet type: 0, 1, or 2)
//      - iVar11 = recv_buffer[1..4] (payload length, 4 bytes)
//      - End marker at payload+5, is_host at payload+6
//
//   7. Packet type dispatch:
//      Type 0 (gamedata, unencrypted):
//        Requires payload+0x12F <= total received
//        Decrypt auth tag via FUN_71001296b0
//        Verify tag via FUN_71000b4e70
//        Verify HMAC via FUN_71001297f0
//        Compare MAC values
//
//      Type 1 (encrypted):
//        Requires payload+0x3F <= total received
//        Decrypt via FUN_7100129590
//        Verify tag via FUN_71000b4e70
//
//      Type 2 (sync/keepalive):
//        Minimal validation, used for connection heartbeat
//
//   8. Deserialize game state via vtable dispatch:
//      - FUN_710012e410 for normal deserialization
//      - vtable[0x78] for encrypted path
//
//   9. Post-receive: if send_pending (session+0xD81) is set:
//      - Regenerate crypto state (if host with crypto)
//      - For each peer (0..num_peers at session+0xD80):
//        Call ldn_send_game_state(session, peer_index)
//      - Clear send_pending flag
//      - Update keepalive deadline: now + 2 * keepalive_interval
// =========================================================================

// =========================================================================
// FUN_710012ba00 — Send reply packet (multi-send with retry)
// Address: 0x710012ba00
//
// Sends a reply/sync packet to a specific peer with 3x redundancy.
// Used when responding to a received packet that requires acknowledgment.
//
// Key differences from ldn_send_game_state:
//   - Uses vtable[0x70] or [0x78] for serialization (reply-specific data)
//   - Max payload: 0x515 bytes
//   - If param_9 == 0 (normal reply):
//       Increments sequence number
//       Writes end marker, is_host, sequence
//       Handles encryption same as send_game_state
//   - If param_9 != 0:
//       Uses shorter packet format (payload - 0x1b bytes)
//       No sequence/key/padding overhead
//
//   - Sends the SAME packet 3 times via SendTo (UDP reliability)
//   - After each failed send:
//       If error == 0x4c0d (send fail): continue to next attempt
//       If error != 0x4c0d: trigger disconnect via FUN_7100121af0
//
// The triple-send pattern compensates for UDP packet loss without
// implementing a full reliability protocol.
// =========================================================================

// =============================================================================
// Compiled LDN transport functions
// =============================================================================

extern u64 FUN_71000b2850(long);

// FUN_710017f1d0 — Get LDN session flag byte
// Address: 0x710017f1d0 | Size: 16 bytes
// Returns byte at session+0x1735.

u8 FUN_710017f1d0(long param_1)
{
    return *(u8 *)(param_1 + 0x1735);
}

// FUN_7100172880 — Check if LDN transport has pending data
// Address: 0x7100172880 | Size: 32 bytes
// Returns 1 if short at +0x28 is non-zero, otherwise forwards to
// FUN_71000b2850 for a deeper transport-level check.

u64 FUN_7100172880(long param_1)
{
    u64 uVar1;

    if (*(s16 *)(param_1 + 0x28) != 0) {
        return 1;
    }
    uVar1 = FUN_71000b2850(param_1 + 8);
    return uVar1;
}

// FUN_710017dcc0 — Cleanup three optional sub-objects via vtable dispatch
// Address: 0x710017dcc0 | Size: 96 bytes
// Calls vtable[0x10] (destructor) on up to 3 sub-objects at +0x300/+0x308/+0x310
// if they are non-null.

void FUN_710017dcc0(long param_1)
{
    if (*(long **)(param_1 + 0x310) != (long *)0) {
        (**(void (**)())(* *(long **)(param_1 + 0x310) + 0x10))();
    }
    if (*(long **)(param_1 + 0x308) != (long *)0) {
        (**(void (**)())(* *(long **)(param_1 + 0x308) + 0x10))();
    }
    if (*(long **)(param_1 + 0x300) != (long *)0) {
        (**(void (**)())(* *(long **)(param_1 + 0x300) + 0x10))();
    }
}

// FUN_7100177d40 — Initialize LDN message handler
// Address: 0x7100177d40 | Size: 80 bytes
// Sets vtable from PTR_DAT_71052a5280, stores parent ref at +3,
// zeros out fields, and initializes sub-object at +9 via FUN_71000b4050.

extern void FUN_710013cff0(void);
extern void FUN_71000b4050(long *);
extern u8 PTR_DAT_71052a5280;

void FUN_7100177d40(long *param_1, long param_2)
{
    u8 *puVar1;

    FUN_710013cff0();
    puVar1 = &PTR_DAT_71052a5280;
    param_1[5] = 0;
    param_1[3] = param_2;
    param_1[4] = 0;
    *(u32 *)(param_1 + 6) = 0;
    param_1[7] = 0;
    *(u8 *)(param_1 + 8) = 0;
    *param_1 = (long)(puVar1 + 0x10);
    FUN_71000b4050(param_1 + 9);
}

// =============================================================================
// Small transport helper functions — trivial getters/setters/cleanup
// =============================================================================

// FUN_71001561f0 — Init keepalive sender (timeout=1000ms, enabled)
// Address: 0x71001561f0 | Size: 32 bytes

void FUN_71001561f0(u32 *param_1)
{
    *param_1 = 1000;
    *(u8 *)(param_1 + 1) = 1;
}

// FUN_7100185d40 — Clear two u64 fields (zero 16 bytes at +0x58/+0x60)
// Address: 0x7100185d40 | Size: 16 bytes

void FUN_7100185d40(long param_1)
{
    *(u64 *)(param_1 + 0x58) = 0;
    *(u64 *)(param_1 + 0x60) = 0;
}

// FUN_71001545b0 — Clear transport flag at +0x368
// Address: 0x71001545b0 | Size: 16 bytes

void FUN_71001545b0(long param_1)
{
    if (*(char *)(param_1 + 0x368) != '\0') {
        *(u8 *)(param_1 + 0x368) = 0;
    }
}

// FUN_710015e370 — Reset transport profile counters
// Address: 0x710015e370 | Size: 32 bytes

void FUN_710015e370(long param_1)
{
    *(u32 *)(param_1 + 0xc) = 0;
    *(u16 *)(param_1 + 0x10) = 0;
    *(u8 *)(param_1 + 0x12) = 1;
}

// FUN_71001acd10 — Set max RTT value in session and global config
// Address: 0x71001acd10 | Size: 32 bytes

extern u8 PTR_DAT_71052a3bd0;

void FUN_71001acd10(long param_1, u16 param_2)
{
    *(u16 *)(param_1 + 0x30) = param_2;
    *(u16 *)(*(long *)&PTR_DAT_71052a3bd0 + 0x104) = param_2;
}

// FUN_71001acd30 — Set max relay count (forced even) in session and global config
// Address: 0x71001acd30 | Size: 32 bytes

void FUN_71001acd30(long param_1, u16 param_2)
{
    u16 val = param_2 & 0xfffe;
    *(u16 *)(param_1 + 0x32) = val;
    *(u16 *)(*(long *)&PTR_DAT_71052a3bd0 + 0x106) = val;
}
