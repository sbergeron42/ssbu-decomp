# SSBU Networking Architecture

Reverse-engineered networking stack for Super Smash Bros. Ultimate v13.0.4.
This documents the layers from SDK through game-level session management.

## Layer Diagram

```
+------------------------------------------------------------------+
|                    Game Session Manager                           |
|  game_network_session_create (0x7103705150)                      |
|  Modes: 1=LDN Local, 2=Online, 3=Arena                          |
+------------------+------------------+----------------------------+
                   |                  |
        +----------v------+   +------v-----------+
        | Game LDN Layer   |   | Online Service   |
        | (0x710016xxxx)   |   | Layer            |
        +----------+------+   +------+-----------+
                   |                  |
        +----------v------+   +------v-----------+
        | nn::ldn SDK      |   | libcurl HTTP     |
        | (0x71039c09xx)   |   | (0x710000xxxx)   |
        +----------+------+   +------+-----------+
                   |                  |
        +----------v------------------v-----------+
        |           nn::socket SDK                 |
        |           (0x71039bfbxx)                 |
        +------------------+-----------------------+
                           |
        +------------------v-----------------------+
        |           nn::ssl SDK                    |
        |           (0x71039bfexx)                 |
        +------------------------------------------+
```

## Layer 1: SDK Import Stubs

### nn::socket (BSD Sockets)
Raw socket API. Two copies exist (main NSO and SDK module).

| Function | Address (Main) | Address (SDK) |
|----------|---------------|---------------|
| nnsocketSocket | 0x71039bfbf0 | 0x710744abc8 |
| nnsocketBind | 0x71039bfc10 | 0x710744ab78 |
| nnsocketConnect | 0x71039bfc20 | 0x710744ab88 |
| nnsocketClose | 0x71039bfbb0 | 0x710744ab80 |
| nnsocketSend | 0x71039bfd70 | 0x710744abf0 |
| nnsocketRecv | 0x71039bfd80 | 0x710744abb0 |
| nnsocketPoll | 0x71039bfd60 | 0x710744abe8 |
| nnsocketFcntl | 0x71039bfd30 | 0x710744abd8 |
| nnsocketGetSockOpt | 0x71039bfbc0 | 0x710744aba0 |
| nnsocketSetSockOpt | 0x71039bfbe0 | 0x710744abc0 |
| nnsocketGetPeerName | 0x71039bfb60 | 0x710744ab90 |
| nnsocketGetSockName | 0x71039bfb80 | 0x710744ab98 |
| nnsocketInetHtons | 0x71039bfc00 | 0x710744ab30 |
| nnsocketInetNtohs | 0x71039bfb90 | 0x710744aba8 |
| nnsocketGetLastErrno | 0x71039bfb70 | 0x710744ab60 |
| nnsocketSetLastErrno | 0x71039bfbd0 | 0x710744abb8 |
| nnsocketGetHostByNameWithOptions | 0x71039bffe0 | 0x710744ace8 |
| nnsocketResolverGetOption | 0x71039bfc90 | 0x710744ab68 |
| nnsocketResolverSetOption | 0x71039bfc30 | 0x710744ab70 |

### nn::ssl (SSL/TLS)
Full SSL stack for HTTPS connections.

| Function | Address (Main) | Address (SDK) |
|----------|---------------|---------------|
| nnsslInitialize | 0x71039bfe00 | 0x710744aca8 |
| nnsslFinalize | 0x71039bfe40 | 0x710744aca0 |
| nnsslConnectionCreate | 0x71039bfe70 | 0x710744ac20 |
| nnsslConnectionDestroy | 0x71039bff00 | 0x710744ac28 |
| nnsslConnectionDoHandshakeWithCertBuffer | 0x71039bfe50 | 0x710744ac30 |
| nnsslConnectionSetSocketDescriptor | 0x71039bfe90 | 0x710744ac78 |
| nnsslConnectionSetHostName | 0x71039bfea0 | 0x710744ac58 |
| nnsslConnectionSetIoMode | 0x71039bff10 | 0x710744ac60 |
| nnsslConnectionSetOption | 0x71039bfe80 | 0x710744ac68 |
| nnsslConnectionSetVerifyOption | 0x71039bfeb0 | 0x710744ac80 |
| nnsslConnectionSetSessionCacheMode | 0x71039bfec0 | 0x710744ac70 |
| nnsslConnectionGetConnectionId | 0x71039bfef0 | 0x710744ac38 |
| nnsslConnectionGetVerifyCertError | 0x71039bfee0 | 0x710744ac40 |
| nnsslConnectionPending | 0x71039bff30 | 0x710744ac48 |
| nnsslConnectionRead | - | 0x710744ac50 |
| nnsslConnectionWrite | - | 0x710744ac88 |
| nnsslContextDestroy | 0x71039bfed0 | 0x710744ac90 |
| nnsslContextGetContextId | 0x71039bfe60 | 0x710744ac98 |

### nn::ldn (Local Network / LAN Play)
Nintendo's local wireless networking SDK. Used for LDN mode AND as a
transport layer for online play through Nintendo's relay infrastructure.

| Function | Address (Main) | Address (SDK) |
|----------|---------------|---------------|
| Initialize | 0x71039c09e0 | 0x710744b208 |
| CreateNetwork | 0x71039c09d0 | 0x710744b090 |
| CreateNetworkPrivate | 0x71039c0a60 | 0x710744b0b0 |
| DestroyNetwork | 0x71039c0a10 | 0x710744b0a0 |
| Connect | 0x71039c0a30 | 0x710744b0c0 |
| ConnectPrivate | 0x71039c0a80 | 0x710744b098 |
| Disconnect | 0x71039c0a50 | 0x710744b080 |
| GetDisconnectReason | 0x71039c0a90 | 0x710744b0d8 |
| GetNetworkInfo | 0x71039c0920 | 0x7107449e38 |
| GetNetworkConfig | 0x71039c0a40 | 0x710744b0a8 |
| Scan | 0x71039c0a20 | 0x710744b0b8 |
| ScanPrivate | 0x71039c0a70 | 0x710744b088 |
| OpenStation | 0x71039c0950 | 0x710744b028 |
| CloseStation | 0x71039c0960 | 0x710744b030 |
| SetStationAcceptPolicy | 0x71039c0970 | 0x710744b070 |
| SetAdvertiseData | 0x71039c0990 | 0x710744b050 |

Also referenced in decompiled code: `nn::ldn::GetState()` (used to check if LDN is active/connected).

## Layer 2: libcurl HTTP Client (~0x710000xxxx)

An embedded build of libcurl handles all HTTP/HTTPS traffic (telemetry, DLC
checks, account services). Identified by SOCKS4/5 proxy strings,
"CURLOPT_SOCKS5_AUTH", and the characteristic connection state machine.

### Renamed Functions

| Name | Address | Purpose |
|------|---------|---------|
| curl_socket_send | 0x71000162c0 | Wraps nnsocketSend, handles EINTR/EAGAIN, logs "Send failure" |
| curl_socket_recv | 0x7100016980 | Wraps nnsocketRecv, handles EINTR/EAGAIN |
| curl_singleipconnect | 0x7100003840 | Creates socket, binds, sets SO_NOSIGPIPE/SO_KEEPALIVE, connects |
| curl_is_connected | 0x7100002f80 | Polls socket pairs for connect completion, retries on failure |
| curl_connecthost | 0x71000036e0 | Iterates address list calling curl_singleipconnect |
| curl_multi_runsingle | 0x7100009d00 | Main transfer state machine (19 states: resolve -> connect -> SSL -> transfer -> done) |
| curl_SOCKS4_connect | 0x7100022dc0 | SOCKS4/4a proxy handler |
| curl_SOCKS5_connect | 0x7100023290 | SOCKS5 proxy handler with auth negotiation |
| curl_socket_cleanup | 0x7100003660 | Closes socket file descriptor |
| curl_log_error | 0x7100016040 | Error-level logging (printf-style) |
| curl_log_info | 0x7100015de0 | Info-level logging (printf-style) |
| curl_strerror_from_errno | 0x71000175d0 | Converts errno to human-readable string |
| curl_socket_check | 0x7100015800 | select/poll wrapper for socket readiness |
| curl_set_socket_blocking | 0x7100013730 | Sets socket blocking/non-blocking mode |
| curl_timeleft | 0x7100002af0 | Calculates remaining timeout |
| curl_post_connect_setup | 0x710001edb0 | Post-connection initialization |

### State Machine States (curl_multi_runsingle)
```
0  = INIT
1  = PENDING
2  = CONNECT (resolve host, find connection)
3  = RESOLVE (DNS lookup)
4  = CONNECTING (wait for TCP connect)
5  = CONNECTED (SSL check)
6  = TUNNEL_INIT (proxy tunnel setup)
7  = TUNNEL_COMPLETE
8  = PROTOCOL_CONNECT
9  = PROTOCOL_CONNECTING (vtable dispatch to protocol handler)
10 = SSL_CONNECT
11 = SSL_CONNECTING
12 = WAITDO (pre-request setup)
13 = SENDPROTOHEADER
14 = DO (send/receive data)
15 = SPEED_CHECK (rate limiting)
16 = DONE (cleanup)
17 = COMPLETED (final state)
18 = MSGSENT
```

## Layer 3: Game LDN Wrappers (~0x710016xxxx)

Thin wrappers around nn::ldn that add error handling, retry logic, and
integration with the game's error reporting system.

| Name | Address | Wraps | Notes |
|------|---------|-------|-------|
| ldn_open_station_wrapper | 0x710016c060 | nn::ldn::OpenStation | Error result propagation |
| ldn_close_station_wrapper | 0x710016c090 | nn::ldn::CloseStation | Error result propagation |
| ldn_initialize_wrapper | 0x710016e740 | nn::ldn::Initialize | Called during session setup |
| ldn_connect_with_retry | 0x710016f0c0 | nn::ldn::Connect | Retries on error 0x6838, sets up WaitConnectNetworkEvent |

### ldn_connect_with_retry (0x710016f0c0) Flow
1. Calls ldn_open_station_wrapper
2. Sets up security mode (1=open, 2=private based on session flag)
3. Builds UserConfig from session parameters
4. Calls nn::ldn::Connect(NetworkInfo, SecurityConfig, UserConfig)
5. On error 0x6838: retries once (transient connection failure)
6. On success: calls FUN_710016f400 (post-connect setup) and FUN_710016da00
7. Sets job name to "LdnBackgroundProcessJob::WaitConnectNetworkEvent"

## Layer 4: Game Network Session Manager (~0x71037xxxxx)

### game_network_session_create (0x7103705150)
The central session creation function. Takes a session descriptor and creates
the appropriate network connection.

**Mode 1 (LDN Local):**
- Calls `nn::ldn::GetState()` to check current LDN state
- If state is 6 (connected) or 0 (idle), calls `nn::ldn::GetNetworkInfo()`
- Otherwise, builds session parameters with channel list [0..15]
- Looks up player station in global player table at DAT_710593a580

**Mode 2 (Online):**
- Sets connect timeout to 300ms (`*(param_1 + 0x28) = 300`)
- Uses different session parameter structure (0x4d8 byte config)
- Takes additional param_2 flag for session type

**Mode 3 (Arena):**
- Similar to Mode 1 but with fixed channel assignment
- Uses 10000ms/1000ms timeout pair
- Includes 16-channel list [0..15]

**All modes:**
- Reference global player manager at DAT_710593a580
  - Player entries at stride 0x198 (408 bytes per entry)
  - Up to plVar11[0xe58] entries
- Call FUN_7100144f10 for final session initialization
- Call FUN_71000bcf30 for result validation

### Related Game Functions

| Name | Address | Purpose |
|------|---------|---------|
| game_ldn_initialize | 0x7103741990 | Top-level LDN initialization from game code |
| online_ldn_initialize | 0x7100191040 | LDN initialization for online mode |
| FUN_710016f400 | 0x710016f400 | Post-connect setup after LDN Connect |
| FUN_710016da00 | 0x710016da00 | Secondary post-connect initialization |
| FUN_710016c120 | 0x710016c120 | Called during LDN connect flow |
| FUN_710016b2f0 | 0x710016b2f0 | Error code translation for LDN |
| FUN_710016af60 | 0x710016af60 | Gets LDN connection parameter |
| FUN_710017ddf0 | 0x710017ddf0 | Sets LDN mode (param: 2) |

## Layer 5: Online Service Functions

Account authentication and Nintendo online service integration.

| Function | Address (Main) |
|----------|---------------|
| EnsureNetworkServiceAccountAvailable | 0x71039c7840 |
| IsNetworkServiceAccountAvailable | 0x71039c59a0 |
| GetNetworkServiceAccountId | 0x71039c0ed0 |
| EnsureNetworkServiceAccountIdTokenCacheAsync | 0x71039c0ea0 |
| LoadNetworkServiceAccountIdTokenCache | 0x71039c0ee0 |
| CheckFreeCommunicationPermission | 0x71039c59d0 |
| IsNetworkAvailable | 0x71039c2250 |
| SubmitNetworkRequest | 0x71039c2230 |
| SubmitNetworkRequestAndWait | 0x71039c71a0 |
| CancelNetworkRequest | 0x71039c71c0 |
| HandleNetworkRequestErrorResult | 0x71039c71d0 |
| IsNetworkRequestOnHold | 0x71039c2240 |
| RequestSyncDeliveryCache | 0x71039c7090 |

### Lobby / Matchmaking

| Function | Address (Main) |
|----------|---------------|
| ShowLobbyPage | 0x71039c0f40 |
| ShowLobbyPageArg | 0x71039c0ef0 |
| SetLobbyParameter | 0x71039c0f00 |
| LobbyPageReturnValue | 0x71039c0f30 |
| GetLobbyExitReason | 0x71039c0f50 |

### Online Mode Detection

| Function | Address |
|----------|---------|
| FighterManager__is_melee_mode_online_tournament_impl | 0x71021410b0 |

## Higher-Level Network Wrappers (C++ Classes)

These are likely virtual functions dispatched through vtables (no direct xrefs):

| Function | Address (Main) | Address (SDK) |
|----------|---------------|---------------|
| Socket (constructor) | 0x71039c0550 | 0x710744afb0 |
| Socket (constructor) | 0x71039c0c40 | 0x710744b1a8 |
| Send | 0x71039c0d00 | 0x710744b180 |
| SendTo | 0x71039c05b0, 0x71039c0cb0 | 0x710744afa8, 0x710744b1a0 |
| Recv | 0x71039c0cf0 | 0x710744b178 |
| RecvFrom | 0x71039c05a0, 0x71039c0c90 | 0x710744afb8, 0x710744b1d0 |

These appear to be part of a higher-level socket abstraction class (possibly
nn::socket::Socket or similar). The two address ranges may represent two
different socket types (TCP stream vs UDP datagram).

## Key Data Structures

### Global Player Manager
- **Address**: DAT_710593a580
- **Player entry stride**: 0x198 (408 bytes)
- **Max players**: stored at offset 0xe58 in the manager
- **Used by**: game_network_session_create to look up player station info

### Session Descriptor (param_1 in game_network_session_create)
- +0x14: Mode byte (1=LDN, 2=Online, 3=Arena)
- +0x1c: Session active flag
- +0x20: Player slot index
- +0x24: Network config byte
- +0x28: Session parameter pointer
- +0x30-0x40: Job/callback pointers

### LDN Connect Parameters (in ldn_connect_with_retry)
- +0x70: LDN session handle
- +0x2a0: NetworkInfo struct
- +0x2ac: Security passphrase
- +0x2ec: Passphrase length
- +0x58: Error result object

## Address Range Summary

| Range | Contents |
|-------|----------|
| 0x710000xxxx | libcurl HTTP client |
| 0x710016xxxx | Game LDN wrapper layer |
| 0x710019xxxx | Online LDN initialization |
| 0x71037xxxxx | Game session management |
| 0x71039bfbxx | nn::socket SDK stubs |
| 0x71039bfexx | nn::ssl SDK stubs |
| 0x71039c09xx | nn::ldn SDK stubs |
| 0x71039c0exx | Account/lobby service stubs |
| 0x71039c22xx | Network request service stubs |
| 0x71039c59xx | Network service account stubs |
| 0x71039c70xx | Delivery cache stubs |
| 0x71039c71xx | Network request management stubs |
| 0x71039c78xx | Account availability stubs |
| 0x710744xxxx | SDK module (duplicate stubs) |

## Layer 6: UDP Game Data Transport (~0x710012xxxx)

**CONFIRMED**: Game data exchange does NOT go through nn::ldn::SendData/
ReceiveData. Instead, after nn::ldn::Connect establishes the session, the
game opens a **raw UDP socket on port 12345 (0x3039)** and exchanges
serialized game state directly via nn::socket::SendTo / RecvFrom.

### Connection Establishment Flow

```
ldn_connect_with_retry (0x710016f0c0)
  |
  +-- ldn_open_station_wrapper (0x710016c060)
  +-- ldn_set_mode(session, 2) (0x710017ddf0)
  +-- Build SecurityConfig (mode 1=open, 2=private)
  +-- ldn_initialize_wrapper (0x710016e740) — get user nickname
  +-- nn::ldn::Connect(NetworkInfo, SecurityConfig, UserConfig)
  |     retry once on error 0x6838 (transient failure)
  +-- ldn_post_connect_get_config (0x710016f400)
  |     calls nn::ldn::GetNetworkConfig
  +-- ldn_post_connect_setup_udp (0x710016da00)
  |     calls nn::ldn::GetIpv4Address -> MakeBroadcastAddress
  |     creates UDP address object for broadcast:12345
  |     registers with session socket list under mutex
  +-- ldn_connect_setup_socket (0x710016c120)
  |     creates UDP socket (AF_INET, SOCK_DGRAM, IPPROTO_UDP)
  |     binds to INADDR_ANY:12345
  |     registers with two transport endpoints
  +-- set job "LdnBackgroundProcessJob::WaitConnectNetworkEvent"
```

### Per-Frame Data Exchange

```
ldn_recv_and_process (0x710012ac30)     [called each game tick]
  |
  +-- RecvFrom(socket, buffer, 0x554, MSG_DONTWAIT)
  +-- Validate source address
  +-- Parse packet header:
  |     [0]       packet_type (0=gamedata, 1=encrypted, 2=sync)
  |     [1..4]    payload_length
  |     [N+5]     end_marker (2)
  |     [N+6]     is_host (0 or 1)
  |     [N+7..14] sequence_number
  +-- If encrypted: decrypt via AES, verify auth tag
  +-- Deserialize game state via vtable dispatch
  +-- If send_pending:
        for each peer (0..num_peers):
          ldn_send_game_state(session, peer_index)
```

```
ldn_send_game_state (0x710012b530)      [per peer]
  |
  +-- Serialize game state via vtable[0x28] (max 0x425 bytes)
  +-- Build packet in send_buffer:
  |     type=0 (unencrypted) or type=1 (encrypted)
  |     payload_length, payload, marker, is_host, sequence_number
  |     + encryption key/random padding
  +-- SendTo(socket, send_buffer, total_len, dest_addr)
```

```
ldn_send_reply (0x710012ba00)           [reply/sync packets]
  |
  +-- Serialize reply via vtable[0x70] or [0x78] (max 0x515 bytes)
  +-- Build packet with type=1 or type=2
  +-- SendTo x3 (triple-send for UDP reliability)
  +-- On failure != 0x4c0d: trigger disconnect
```

### Game Data Packet Format

```
Offset  Size   Field
------  ----   -----
0x00    1      packet_type: 0=gamedata, 1=encrypted, 2=sync
0x01    4      payload_length (LE)
0x05    N      serialized game state payload
N+5     1      end_marker (always 2 = end-of-frame-data)
N+6     1      is_host (0=client, 1=host)
N+7     8      sequence_number (monotonic, incremented each send)
N+15    16     encryption_key material

--- Unencrypted mode (type 0): ---
N+0x1F  256    random padding bytes (from FUN_7100138620 PRNG)
               Total extra: 0x12F bytes after payload

--- Encrypted mode (type 1): ---
N+0x1F  16     AES auth tag
               Total extra: 0x3F bytes after payload
```

### Key Data Exchange Functions

| Name | Address | Purpose |
|------|---------|---------|
| ldn_send_game_state | 0x710012b530 | Serialize + send game state to one peer |
| ldn_recv_and_process | 0x710012ac30 | Receive + parse + dispatch game data |
| ldn_send_reply | 0x710012ba00 | Send reply packet (3x redundant) |
| socket_send_to | 0x71000ba5c0 | nn::socket::SendTo wrapper with error handling |
| socket_recv_from | 0x71000ba450 | nn::socket::RecvFrom wrapper (MSG_DONTWAIT) |
| socket_send_to_alt | 0x71000ba740 | Alternative SendTo (different address format) |
| socket_create | 0x71000b9f60 | Create AF_INET socket |

### Encryption

Two modes based on `is_host` flag and connection type:

1. **Unencrypted** (LDN local, or host in certain modes):
   - Packet type 0
   - 16-byte key + 256 bytes random padding appended (obfuscation only)

2. **Encrypted** (online relay mode):
   - Packet type 1
   - AES encryption via FUN_7100129590 (encrypt) / FUN_71001296b0 (decrypt)
   - 16-byte auth tag for integrity verification
   - Key stored at session+0xDD0, IV material at session+0xDE0

### LDN Transport Session Layout

```
Offset   Size    Field
------   ----    -----
+0x58    8       session_handle (connection/crypto context)
+0x60    16      socket_descriptor {fd:4, generation:4, family:1, pad:7}
+0x70    0x554   recv_buffer
+0x5C4   0x554   send_buffer
+0xB18   ...     frame data state machine
+0xD80   1       num_peers
+0xD81   1       send_pending flag
+0xD88   4       keepalive_state (1=active)
+0xDB8   8       next_keepalive_deadline
+0xDC0   1       crypto_pending flag
+0xDC8   8       sequence_number (u64, monotonic)
+0xDD0   16      encryption_key
+0xDE0   256     encryption_iv_material
```

### Error Code Map (FUN_710016b2f0)

The game translates nn::ldn SDK Result codes into its own error system:

| Game Error | Value | Meaning |
|-----------|-------|---------|
| LDN_OK | 0x0000 | Success |
| LDN_ERR_SPECTATOR_JOIN | 0x6422 | Spectator join issue |
| LDN_ERR_CONNECT_TRANSIENT | 0x6838 | Transient failure (retried once) |
| LDN_ERR_DISCONNECTED | 0x6c0e | Peer disconnected |
| LDN_ERR_NETWORK_GENERAL | 0x6c1b | General LDN network error |
| LDN_ERR_CONNECT_REJECTED | 0x6c1c | Connection rejected |
| LDN_ERR_RECV_DISCONNECT | 0x2c09 | Disconnect during receive |
| LDN_ERR_SEND_FAIL | 0x4c0d | UDP send failure |
| LDN_ERR_GENERAL_NET | 0xa46e | General net error (with SDK detail) |
| LDN_ERR_CRYPTO_A | 0xc420 | Crypto/auth error |
| LDN_ERR_CRYPTO_B | 0xc421 | Crypto/auth error |
| LDN_ERR_INVALID_STATE | 0x10c07 | Bad state / invalid socket |
| LDN_ERR_UNKNOWN | 0x10c08 | Unrecognized SDK error |

## Notes for Rollback Modding

1. **The actual game frame sync path is NOT through libcurl.** libcurl handles
   HTTP services only (telemetry, accounts, DLC).

2. **nn::ldn is the game transport** -- even for online play. Nintendo routes
   LDN traffic through their relay servers for online mode, so the game uses
   the same LDN API for both local and online.

3. **Key intercept point for rollback**: game_network_session_create
   (0x7103705150) is where the session mode is decided. The mode byte at
   param_1+0x14 controls LDN vs Online vs Arena.

4. **Game data goes over raw UDP, NOT nn::ldn::SendData/ReceiveData.**
   After nn::ldn::Connect, the game opens its own UDP socket on port 12345
   and exchanges serialized game state directly via nn::socket::SendTo/RecvFrom.
   The nn::ldn SDK is only used for session establishment.

5. **The global player manager** at DAT_710593a580 is critical infrastructure
   -- it holds all connected player state with 408-byte entries.

6. **Two SDK stub ranges** (0x71039bxxxx and 0x710744xxxx) suggest the binary
   has multiple modules/NSOs linked together. The 0x71039b range is in the
   main executable, the 0x710744 range is in an SDK support module.

7. **Triple-send for reliability**: Reply/sync packets (0x710012ba00) are
   sent 3 times to compensate for UDP packet loss. Game data packets are
   sent once per peer per frame.

8. **Encryption is AES-based**: Online mode encrypts game data with a
   session key at +0xDD0. Local LDN mode uses unencrypted packets with
   random padding. The encrypt/decrypt functions at 0x7100129590/0x71001296b0
   are the key intercept points for packet analysis.

9. **For rollback implementation**: The critical intercept points are:
   - **ldn_send_game_state (0x710012b530)**: Hook to inject rollback frame data
   - **ldn_recv_and_process (0x710012ac30)**: Hook to intercept received state
   - **The vtable serialize/deserialize calls**: These encode/decode the actual
     game state that needs to be saved/restored for rollback
   - **sequence_number at session+0xDC8**: Can be used to detect packet ordering
