#pragma once
// LDN Transport Layer structures for SSBU networking
// Derived from decompilation of functions in 0x710016xxxx-0x710019xxxx range

#include <nn/types.h>

namespace nn {
namespace ldn {

struct NetworkConfig {
    u8 data[0x20]; // exact layout TBD
};

struct NetworkInfo {
    u8 data[0x480]; // large struct, passed to Connect
};

struct SecurityConfig {
    u16 security_mode;   // 1=open, 2=private (passphrase)
    u8 passphrase_len;
    u8 passphrase[0x40];
};

struct UserConfig {
    char nickname[0x20];
    u8 reserved[0x10];
};

struct Ipv4Address {
    u32 addr;
};

struct SubnetMask {
    u32 mask;
};

// SDK function declarations
nn::Result Initialize();
nn::Result CreateNetwork(void* params);
nn::Result CreateNetworkPrivate(void* params);
nn::Result DestroyNetwork();
nn::Result Connect(NetworkInfo* info, SecurityConfig* sec, UserConfig* user, int param, int flags);
nn::Result ConnectPrivate(void* params);
nn::Result Disconnect();
nn::Result GetDisconnectReason(u32* reason);
nn::Result GetNetworkInfo(NetworkInfo* out);
nn::Result GetNetworkConfig(NetworkConfig* out);
nn::Result Scan(void* out, int* count, int max);
nn::Result ScanPrivate(void* params);
nn::Result OpenStation();
nn::Result CloseStation();
nn::Result SetStationAcceptPolicy(int policy);
nn::Result SetAdvertiseData(void* data, u32 size);
nn::Result GetState(u32* state);
nn::Result GetIpv4Address(Ipv4Address* addr, SubnetMask* mask);
u32 MakeBroadcastAddress(u32 addr, u32 mask);

} // namespace ldn
} // namespace nn

namespace app {

// Game error codes used by the LDN error translator (FUN_710016b2f0)
enum LDNErrorCode : u32 {
    LDN_OK                    = 0,
    LDN_ERR_NETWORK_GENERAL   = 0x6c1b,  // nn::ldn module=0xcb, category 2
    LDN_ERR_CONNECT_TRANSIENT = 0x6838,  // Transient connection failure (retried)
    LDN_ERR_DISCONNECTED      = 0x6c0e,  // Peer disconnected
    LDN_ERR_CONNECT_REJECTED  = 0x6c1c,  // Connection rejected
    LDN_ERR_SPECTATOR_JOIN    = 0x6422,  // Spectator join issue
    LDN_ERR_GENERAL_NET       = 0xa46e,  // General network error (with detail)
    LDN_ERR_CRYPTO_A          = 0xc420,  // Crypto/auth error A
    LDN_ERR_CRYPTO_B          = 0xc421,  // Crypto/auth error B
    LDN_ERR_UNKNOWN           = 0x10c08, // Unrecognized nn::ldn error
    LDN_ERR_INVALID_STATE     = 0x10c07, // Invalid state / bad socket fd
    LDN_ERR_RECV_DISCONNECT   = 0x2c09,  // Disconnected during receive
    LDN_ERR_SEND_FAIL         = 0x4c0d,  // UDP send failure
};

// nn::ldn Result code module ID and categories
// Result format: [module:9][category:13][detail:10]
// Module 0xcb = nn::ldn
// Category 2 (0x4000) = general network
// Category 4 (0x8000) = connection errors
static constexpr u32 LDN_MODULE_ID = 0xcb;

// Packet type byte — first byte of every UDP packet in the LDN transport
enum LDNPacketType : u8 {
    PACKET_TYPE_GAME_DATA     = 0,  // Full game state data (unencrypted path)
    PACKET_TYPE_ENCRYPTED     = 1,  // Encrypted game state data
    PACKET_TYPE_SYNC_REQUEST  = 2,  // Sync/keepalive marker
};

// LDN transport session — the game-level struct managing the UDP data exchange.
// Base is at param_2 in the transport functions.
// Offsets derived from FUN_710012ac30 (recv loop) and FUN_710012b530 (send).
struct LDNTransportSession {
    u8 pad_00[0x58];
    void* session_handle;          // +0x58: session/connection handle
    u8 pad_60[8];
    // +0x60: socket descriptor struct (int fd at +0, generation at +4, family at +8)
    struct {
        int fd;
        int generation;
        u8 family;
        u8 pad[7];
    } socket;                      // +0x60
    u8 recv_buffer[0x554];         // +0x70: receive buffer (max 0x554 bytes)
    u8 send_buffer[0x554];         // +0x5C4: send buffer
    u8 pad_b18[0x268];
    // +0xB18: frame data state machine
    u8 pad_d80[0x68];
    u8 num_peers;                  // +0xD80: number of connected peers to send to
    u8 send_pending;               // +0xD81: flag — send data on next tick
    u8 pad_d82[6];
    u32 keepalive_state;           // +0xD88: keepalive timer state (1=active)
    u8 pad_d8c[0x3C];
    u64 sequence_number;           // +0xDC8: monotonic packet sequence counter
    u8 encryption_key[0x10];       // +0xDD0: AES key for packet encryption
    u8 encryption_iv[0x100];       // +0xDE0: IV/nonce material
};

// UDP port used by the LDN game transport (decimal 12345)
static constexpr u16 LDN_GAME_PORT = 0x3039;

// Maximum receive buffer size (per RecvFrom call)
static constexpr u32 LDN_MAX_RECV_SIZE = 0x554;

// Maximum game state payload size (per vtable serialize call)
static constexpr u32 LDN_MAX_GAME_STATE_SIZE = 0x425;

// Maximum reply payload size
static constexpr u32 LDN_MAX_REPLY_SIZE = 0x515;

// Packet header layout within send_buffer (+0x5C4):
//   [0]       u8  packet_type (0=gamedata, 1=encrypted, 2=sync)
//   [1..4]    u32 payload_length (little-endian)
//   [5..N]    u8  payload (serialized game state)
//   [N+5]     u8  marker (2 = end-of-frame-data)
//   [N+6]     u8  is_host (0 or 1)
//   [N+7..14] u64 sequence_number
//   [N+15..24] u8 encryption_key[16] (or random padding in unencrypted mode)
//   -- if unencrypted (type 0): [N+0x1F..N+0x11E] random padding (256 bytes)
//   -- if encrypted (type 1):   [N+0x1F..N+0x2E] encrypted auth tag (16 bytes)

} // namespace app
