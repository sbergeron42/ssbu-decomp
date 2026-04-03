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

## Notes for Rollback Modding

1. **The actual game frame sync path is NOT through libcurl.** libcurl handles
   HTTP services only (telemetry, accounts, DLC).

2. **nn::ldn is the game transport** -- even for online play. Nintendo routes
   LDN traffic through their relay servers for online mode, so the game uses
   the same LDN API for both local and online.

3. **Key intercept point for rollback**: game_network_session_create
   (0x7103705150) is where the session mode is decided. The mode byte at
   param_1+0x14 controls LDN vs Online vs Arena.

4. **Data exchange functions are likely in the 0x710016xxxx-0x710019xxxx
   range** but use nn::ldn internally (no named symbols found for SendData/
   ReceiveData -- these may be inlined or use a different API path).

5. **The global player manager** at DAT_710593a580 is critical infrastructure
   -- it holds all connected player state with 408-byte entries.

6. **Two SDK stub ranges** (0x71039bxxxx and 0x710744xxxx) suggest the binary
   has multiple modules/NSOs linked together. The 0x71039b range is in the
   main executable, the 0x710744 range is in an SDK support module.
