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
void FUN_710012ba00(int *param_1, long param_2, u8 *param_3, void *param_4, u32 param_5,
                    u64 *param_6, u32 param_7, u32 param_8, u32 param_9, u8 param_10);

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

void FUN_710012b530(u64 param_1, long param_2, u32 param_3)
{
    long lVar1;
    long lVar2;
    u8 *puVar3;
    u32 uVar4;
    u8 uVar5;
    u32 uVar6;
    u64 uVar7;
    long *plVar8;
    int *piVar9;
    u64 *puVar10;
    int iVar11;
    long lVar12;
    u64 local_700;
    u32 *local_6f8;
    u32 local_6f0;
    u32 uStack_6ec;
    u64 local_6e8;
    u32 local_6e0[48];
    u32 local_620[6];
    u16 local_608;
    u8 auStack_5fc[4];
    int local_5f8[4];
    u32 local_5e8;
    u8 auStack_5e4[12];
    int local_5d8[5];
    u32 local_5c4;
    int local_5c0[344];

    puVar10 = &local_700;
    if ((param_3 & 0xff) < 2) {
        if (((*(long *)(param_2 + 0x58) != 0) && (uVar7 = FUN_7100129a90(*(u64 *)(param_2 + 0x58)), (uVar7 & 1) != 0)) &&
           (uVar7 = FUN_7100125e30(*(u64 *)(param_2 + 0x58)), puVar3 = (u8 *)*(long *)&PTR_DAT_71052a4080,
           (uVar7 & 1) != 0)) {
            plVar8 = (long *)FUN_710011be80(*(u64 *)
                                             (*(long *)&PTR_DAT_71052a4080 +
                                              (u64)*(u8 *)(*(long *)&PTR_DAT_71052a4080 + 0x162) * 8 +
                                             0x168), param_3);
            (**(void (**)(int *, long *, int *, u32 *, u32))(*plVar8 + 0x28))(local_5d8, plVar8, local_5c0, &local_5c4, 0x425);
            if (local_5d8[0] == 0) {
                lVar1 = param_2 + 0x5c4;
                FUN_71000bb9d0((u8 *)lVar1, 0);
                FUN_71000bb980((u8 *)(param_2 + 0x5c5), local_5c4);
                memcpy((void *)(param_2 + 0x5c9), local_5c0, (u64)local_5c4);
                uVar4 = local_5c4;
                *(long *)(param_2 + 0xdc8) = *(long *)(param_2 + 0xdc8) + 1;
                FUN_71000bb9d0((u8 *)(lVar1 + (u64)(local_5c4 + 5)), 2);
                uVar6 = (u32)FUN_7100125e30(*(u64 *)(param_2 + 0x58));
                FUN_71000bb9d0((u8 *)(lVar1 + (u64)(uVar4 + 6)), uVar6 & 1);
                FUN_71000bb930((u8 *)(lVar1 + (u64)(uVar4 + 7)), *(u64 *)(param_2 + 0xdc8));
                memcpy((void *)(lVar1 + (u64)(uVar4 + 0xf)), (void *)(param_2 + 0xdd0), 0x10);
                uVar7 = FUN_7100125e30(*(u64 *)(param_2 + 0x58));
                if ((uVar7 & 1) == 0) {
                    // Unencrypted path: fill random padding
                    FUN_7100138520(&local_700);
                    uVar5 = FUN_7100138620(&local_700);
                    *(u8 *)(lVar1 + (u64)(uVar4 + 0x1f)) = uVar5;
                    uVar5 = FUN_7100138620(&local_700);
                    *(u8 *)(lVar1 + (u64)(uVar4 + 0x20)) = uVar5;
                    uVar5 = FUN_7100138620(&local_700);
                    *(u8 *)(lVar1 + (u64)(uVar4 + 0x21)) = uVar5;
                    uVar5 = FUN_7100138620(&local_700);
                    *(u8 *)(lVar1 + (u64)(uVar4 + 0x22)) = uVar5;
                    uVar5 = FUN_7100138620(&local_700);
                    *(u8 *)(lVar1 + (u64)(uVar4 + 0x23)) = uVar5;
                    uVar5 = FUN_7100138620(&local_700);
                    *(u8 *)(lVar1 + (u64)(uVar4 + 0x24)) = uVar5;
                    uVar5 = FUN_7100138620(&local_700);
                    *(u8 *)(lVar1 + (u64)(uVar4 + 0x25)) = uVar5;
                    uVar5 = FUN_7100138620(&local_700);
                    *(u8 *)(lVar1 + (u64)(uVar4 + 0x26)) = uVar5;
                    uVar5 = FUN_7100138620(&local_700);
                    *(u8 *)(lVar1 + (u64)(uVar4 + 0x27)) = uVar5;
                    uVar5 = FUN_7100138620(&local_700);
                    *(u8 *)(lVar1 + (u64)(uVar4 + 0x28)) = uVar5;
                    uVar5 = FUN_7100138620(&local_700);
                    *(u8 *)(lVar1 + (u64)(uVar4 + 0x29)) = uVar5;
                    uVar5 = FUN_7100138620(&local_700);
                    *(u8 *)(lVar1 + (u64)(uVar4 + 0x2a)) = uVar5;
                    uVar5 = FUN_7100138620(&local_700);
                    *(u8 *)(lVar1 + (u64)(uVar4 + 0x2b)) = uVar5;
                    uVar5 = FUN_7100138620(&local_700);
                    *(u8 *)(lVar1 + (u64)(uVar4 + 0x2c)) = uVar5;
                    uVar5 = FUN_7100138620(&local_700);
                    *(u8 *)(lVar1 + (u64)(uVar4 + 0x2d)) = uVar5;
                    uVar5 = FUN_7100138620(&local_700);
                    lVar12 = 0;
                    *(u8 *)(lVar1 + (u64)(uVar4 + 0x2e)) = uVar5;
                    do {
                        uVar5 = FUN_7100138620(&local_700);
                        iVar11 = (int)lVar12;
                        lVar12 = lVar12 + 1;
                        *(u8 *)(param_2 + (u64)(uVar4 + 0x2f + iVar11) + 0x5c4) = uVar5;
                    } while (lVar12 != 0x100);
                }
                else {
                    // Encrypted path: AES encrypt + auth tag
                    uVar7 = FUN_71000b1f50(*(long *)(param_2 + 0x58) + 0x70);
                    if ((uVar7 & 1) == 0) {
                        local_620[0] = 0;
                        FUN_71000b1da0(&local_700, *(long *)(param_2 + 0x58) + 0x70, local_620);
                        FUN_71000bb980((u8 *)&local_5e8, local_620[0]);
                    }
                    else {
                        local_700 = 0;
                        local_6f8 = (u32 *)0;
                        FUN_71000b2110(local_620, *(long *)(param_2 + 0x58) + 0x70, &local_700);
                        memcpy(&local_5e8, &local_700, 4);
                    }
                    FUN_71000bb930(auStack_5e4, *(u64 *)(param_2 + 0xdc8));
                    FUN_7100129590(&local_700, *(u64 *)(param_2 + 0x58), (void *)(param_2 + 0xdd0), 0x10,
                                   local_620, 0x10);
                    FUN_71000bcf30(local_5d8, &local_700);
                    *(u32 *)&local_700 = 1;
                    local_6f0 = 0xc;
                    local_6e0[0] = 0x10;
                    local_6f8 = &local_5e8;
                    local_6e8 = (u64)local_620;
                    FUN_71000b4c70(local_5f8, param_2 + 0x5c4 + (u64)(uVar4 + 0x2f), param_2 + 0xde0, 0x100,
                                   param_2 + 0x5c4 + (u64)(uVar4 + 0x1f), 0x10, &local_700);
                }
                // Get peer address for logging
                FUN_71000b1c60((u8 *)local_620, *(long *)(param_2 + 0x58) + 0x70);
                local_608 = 30000;
                local_700 = (u64)(*(long *)&PTR_DAT_71052a3c30 + 0x10);
                local_6f0 = 0xc0;
                *(u8 *)((long)&local_6e8 + 4) = 0;
                lVar12 = 0;
                do {
                    *(u16 *)((long)puVar10 + 0x1d) = 0;
                    lVar2 = lVar12 + 4;
                    *(u8 *)((long)puVar10 + 0x1f) = 0;
                    puVar10 = (u64 *)((long)&local_700 + lVar12 + 4);
                    *(u8 *)((long)local_6e0 + lVar12) = 0;
                    lVar12 = lVar2;
                } while (lVar2 != 0xc0);
                uStack_6ec = 0;
                *(u32 *)&local_6e8 = 0;
                local_6f8 = (u32 *)((long)&local_6e8 + 4);
                FUN_71000b1fa0((u8 *)local_620, &local_700);
                // Send the packet
                FUN_71000ba5c0(local_5f8, param_2 + 0x60, lVar1, local_5c4 + 0x12f, (u8 *)local_620, auStack_5fc);
                FUN_71000bcf30(local_5d8, local_5f8);
                if (local_5d8[0] != 0) {
                    // Send failed — set error 0x4c0d
                    local_5f8[0] = 0x4c0d;
                    nn::err::ErrorResultVariant_ctor((nn::err::ErrorResultVariant *)((u64)local_5f8 | 4));
                    local_5e8 = 0;
                    nn::err::ErrorResultVariant_assign(
                        (nn::err::ErrorResultVariant *)((u64)local_5f8 | 4), &local_5e8);
                    if (local_5d8[0] != local_5f8[0]) {
                        FUN_7100121af0(*(u64 *)(*(long *)puVar3 + 8));
                    }
                }
                FUN_71000b1cf0((u8 *)local_620);
            }
            piVar9 = local_5d8;
            goto LAB_710012b6e0;
        }
        local_5c0[0] = 0x10c08;
    }
    else {
        local_5c0[0] = 0x10c07;
    }
    nn::err::ErrorResultVariant_ctor((nn::err::ErrorResultVariant *)((u64)local_5c0 | 4));
    *(u32 *)&local_700 = 0;
    nn::err::ErrorResultVariant_assign(
        (nn::err::ErrorResultVariant *)((u64)local_5c0 | 4), (u32 *)&local_700);
    piVar9 = local_5c0;
LAB_710012b6e0:
    FUN_71000bce50((void *)param_1, piVar9);
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
    bool bVar1;
    u32 uVar2;
    u32 uVar3;
    u32 uVar4;
    char cVar5;
    bool bVar6;
    bool bVar7;
    u8 bVar8;
    u8 bVar9;
    u32 uVar10;
    int iVar11;
    u32 uVar12;
    int iVar13;
    int iVar14;
    u64 uVar15;
    u64 uVar16;
    u64 uVar17;
    long *plVar18;
    u64 *puVar19;
    u64 *puVar20;
    long *plVar21;
    long lVar22;
    long lVar23;
    long *plVar24;
    u8 bVar25;
    u8 auStack_238[16];
    u8 auStack_228[16];
    u8 auStack_218[16];
    u64 local_208;
    u8 *local_200;
    u32 local_1f8;
    u32 *local_1f0;
    u32 local_1e8;
    u32 local_1e0[5];
    u8 auStack_1cc[4];
    u8 auStack_1c8[8];
    u8 auStack_1c0[16];
    u8 auStack_1b0[16];
    u64 local_1a0;
    u64 uStack_198;
    u32 local_a0;
    u8 auStack_9c[4];
    u8 auStack_98[24];
    s16 local_80;
    int local_78[6];

    local_78[0] = 0;
    nn::err::ErrorResultVariant_ctor((nn::err::ErrorResultVariant *)((u64)local_78 | 4));
    *(u32 *)&local_1a0 = 0;
    nn::err::ErrorResultVariant_assign(
        (nn::err::ErrorResultVariant *)((u64)local_78 | 4), (u32 *)&local_1a0);
    FUN_71000b1c30(auStack_98);

    // Step 1: Flush pending crypto state
    if (*(char *)(param_1 + 0xdc0) != '\0') {
        uVar15 = FUN_71000b63d0();
        uVar16 = FUN_71000b63d0();
        if (*(long *)(param_1 + 0x58) != 0) {
            FUN_7100129550(*(u64 *)(param_1 + 0x58), uVar15, uVar16);
        }
        *(u8 *)(param_1 + 0xdc0) = 0;
    }

    // Step 2: Get game state manager
    plVar24 = *(long **)(*(long *)&PTR_DAT_71052a4080 +
                         (u64)*(u8 *)(*(long *)&PTR_DAT_71052a4080 + 0x162) * 8 + 0x168);
    if (plVar24 == (long *)0) goto LAB_710012b004;

    // Step 3: Check connection mode
    bVar8 = FUN_7100192590(*(u64 *)&PTR_DAT_71052a3df0);
    uVar17 = FUN_7100125e30(*(u64 *)(param_1 + 0x58));
    if ((uVar17 & 1) == 0) {
        uVar10 = 0;
    }
    else {
        uVar10 = (u32)FUN_7100129a90(*(u64 *)(param_1 + 0x58));
    }

    // Step 4: RecvFrom on UDP socket
    FUN_71000ba450(&local_1a0, param_1 + 0x60, param_1 + 0x70, 0x554, auStack_98, auStack_9c, &local_a0);
    FUN_71000bcf30(local_78, &local_1a0);
    if (local_78[0] != 0) {
        // Recv error — set disconnect
        *(u32 *)&local_1a0 = 0x2c09;
        nn::err::ErrorResultVariant_ctor((nn::err::ErrorResultVariant *)((u64)&local_1a0 | 4));
        *(u32 *)&local_208 = 0;
        nn::err::ErrorResultVariant_assign(
            (nn::err::ErrorResultVariant *)((u64)&local_1a0 | 4), (u32 *)&local_208);
        goto LAB_710012ad58;
    }

    // Step 5: Validate source address
    uVar17 = FUN_71000b2820(auStack_98, *(long *)(param_1 + 0x58) + 0x50);
    if (((uVar17 & 1) != 0) && (local_80 == *(s16 *)(*(long *)(param_1 + 0x58) + 0x96)))
        goto LAB_710012b004;

    // Step 6: Parse packet header
    bVar25 = *(u8 *)(param_1 + 0x70);
    iVar11 = (int)FUN_71000bb9a0((u32 *)(param_1 + 0x71));
    uVar2 = iVar11 + 5;
    if (uVar2 < local_a0) {
        if ((1 < bVar25) || (uVar3 = iVar11 + 0x2f, local_a0 < uVar3)) goto LAB_710012ad58;
        bVar9 = FUN_71000bb9e0((u8 *)(param_1 + 0x70 + (u64)uVar2));
        uVar12 = (u32)FUN_71000bb9e0((u8 *)(param_1 + 0x70 + (u64)(iVar11 + 6)));
        bVar1 = 1 < bVar9;
        uVar4 = uVar10 ^ (uVar12 & 1);
        iVar13 = 0;
        bVar9 = 2;
        if ((uVar4 & 1) == 0) {
            bVar9 = bVar25;
        }
        if ((((uVar4 & 1) != 0) || (((uVar10 ^ 1) & 1) != 0)) || ((uVar12 & 1) == 0))
            goto joined_r0x00710012aed4;

        // Has crypto context and is from host — decrypt path
        uVar17 = FUN_71000b1f50(*(long *)(param_1 + 0x58) + 0x70);
        if ((uVar17 & 1) == 0) {
            *(u32 *)&local_208 = 0;
            FUN_71000b1da0(&local_1a0, *(long *)(param_1 + 0x58) + 0x70, &local_208);
            FUN_71000bb980(auStack_1cc, (u32)(local_208 & 0xffffffff));
        }
        else {
            local_1a0 = 0;
            uStack_198 = 0;
            FUN_71000b2110(&local_208, *(long *)(param_1 + 0x58) + 0x70, &local_1a0);
            memcpy(auStack_1cc, &local_1a0, 4);
        }
        memcpy(auStack_1c8, (void *)(param_1 + (u64)(iVar11 + 7) + 0x70), 8);

        if (bVar25 == 1) {
            // Encrypted packet (type 1)
            if ((u32)(iVar11 + 0x3f) <= local_a0) {
                lVar23 = param_1 + 0x70;
                memcpy(auStack_1c0, (void *)(lVar23 + (u64)(iVar11 + 0xf)), 0x10);
                memcpy(auStack_1b0, (void *)(param_1 + 0xdd0), 0x10);
                FUN_71001296b0(&local_1a0, *(u64 *)(param_1 + 0x58), auStack_1c0, 0x20, local_1e0, 0x10);
                FUN_71000bcf30(local_78, &local_1a0);
                local_200 = auStack_1cc;
                local_1f8 = 0xc;
                local_1e8 = 0x10;
                *(u32 *)&local_208 = 1;
                local_1f0 = local_1e0;
                FUN_71000b4e70(auStack_218, &local_1a0, lVar23 + (u64)uVar3, 0x10,
                               lVar23 + (u64)(iVar11 + 0x1f), 0x10, &local_208);
                FUN_71000bcf30(local_78, auStack_218);
                if (local_78[0] == 0) {
                    FUN_71001297f0(auStack_228, *(u64 *)(param_1 + 0x58), param_1 + 0xde0, 0x100,
                                   auStack_218, 0x10);
                    FUN_71000bcf30(local_78, auStack_228);
                    iVar13 = memcmp(&local_1a0, auStack_218, 0x10);
                    bVar7 = iVar13 == 0;
                }
                else {
                    bVar7 = false;
                }
                iVar13 = 0;
                goto LAB_710012b040;
            }
LAB_710012b2bc:
            bVar6 = true;
            iVar13 = 0;
            bVar25 = 2;
        }
        else if (bVar25 == 0) {
            // Unencrypted packet (type 0) — verify HMAC
            if (local_a0 < (u32)(iVar11 + 0x12f)) goto LAB_710012b2bc;
            lVar23 = param_1 + 0x70;
            memcpy(auStack_1c0, (void *)(lVar23 + (u64)(iVar11 + 0xf)), 0x10);
            FUN_7100129590(&local_1a0, *(u64 *)(param_1 + 0x58), auStack_1c0, 0x10, local_1e0, 0x10);
            FUN_71000bcf30(local_78, &local_1a0);
            local_200 = auStack_1cc;
            local_1f8 = 0xc;
            local_1e8 = 0x10;
            *(u32 *)&local_208 = 1;
            local_1f0 = local_1e0;
            FUN_71000b4e70(auStack_218, &local_1a0, lVar23 + (u64)uVar3, 0x100,
                           lVar23 + (u64)(iVar11 + 0x1f), 0x10, &local_208);
            FUN_71000bcf30(local_78, auStack_218);
            bVar6 = local_78[0] == 0;
            iVar13 = 0;
            bVar25 = 0;
        }
        else {
            bVar6 = true;
            bVar7 = true;
            iVar13 = 0;
            if (bVar25 == 1) goto LAB_710012b040;
        }
LAB_710012aed8:
        if (((bVar25 != 0) || ((bVar8 & 1) != 0)) ||
           (uVar17 = (**(u64 (**)(long *))(*plVar24 + 0xe0))(plVar24), (uVar17 & 1) == 0)) goto LAB_710012ad58;
        lVar23 = param_1 + 0xb18;
        FUN_710012f640(&local_208, lVar23, param_1 + 0x75, iVar11);
        *(u32 *)&local_200 = 0;
        local_208 = 0x40000000;
        FUN_710012fba0(lVar23, &local_208);
        plVar18 = (long *)FUN_710011be50((u64)plVar24);
        *(u32 *)&local_200 = 0;
        local_208 = 0x40000000;
        (**(void (**)(long *, u64 *))(*plVar18 + 0x58))(plVar18, &local_208);
        uVar15 = FUN_710011be50((u64)plVar24);
        uVar17 = FUN_710012ed20(lVar23, uVar15);
        if ((uVar17 & 1) == 0) goto LAB_710012ad58;
        FUN_710012ba00((int *)&local_208, param_1, auStack_98, auStack_1c0, 0x10, &local_1a0, 0x100, bVar6, iVar13,
                       bVar1);
        FUN_71000bcf30(local_78, &local_208);
        cVar5 = *(char *)(param_1 + 0xd81);
    }
    else {
        bVar1 = false;
        iVar13 = 1;
        bVar9 = bVar25;
joined_r0x00710012aed4:
        bVar25 = bVar9;
        bVar6 = true;
        bVar7 = true;
        if (bVar25 != 1) goto LAB_710012aed8;
LAB_710012b040:
        if (((bVar8 | (bVar7 ^ 0xff)) & 1) == 0) {
            if (iVar13 != 0) {
                memset((void *)(param_1 + (u64)uVar2 + 0x5c4), 0, 0x20);
                iVar11 = iVar11 + 0x20;
            }
            plVar18 = (long *)FUN_710011be60((u64)plVar24);
            lVar23 = param_1 + 0x75;
            if (!bVar1) {
                FUN_710012e410(&local_208, plVar18, lVar23, iVar11);
                plVar18 = (long *)FUN_710011be70((u64)plVar24);
                if (plVar18 != (long *)0) goto LAB_710012b0b8;
                goto LAB_710012ad58;
            }
            (**(void (**)(void *, long *, long, int))(*plVar18 + 0x78))(&local_208, plVar18, lVar23, iVar11);
            plVar18 = (long *)FUN_710011be70((u64)plVar24);
            if (plVar18 == (long *)0) goto LAB_710012ad58;
LAB_710012b0b8:
            for (puVar19 = (u64 *)(**(u64 *(**)(void))(*plVar18 + 0x18))();
                puVar20 = (u64 *)(**(u64 *(**)(long *))(*plVar18 + 0x28))(plVar18), puVar19 != puVar20;
                puVar19 = puVar19 + 1) {
                iVar13 = (**(int (**)(void))(*(long *)*puVar19 + 0x18))();
                plVar21 = (long *)FUN_710011be60((u64)plVar24);
                iVar14 = (**(int (**)(void))(*plVar21 + 0x18))();
                if (iVar13 == iVar14) {
                    plVar18 = (long *)*puVar19;
                    if (plVar18 != (long *)0) goto LAB_710012b16c;
                    break;
                }
            }
            lVar22 = FUN_710011be70((u64)plVar24);
            if ((*(u16 *)(lVar22 + 10) == 0) || (*(u16 *)(lVar22 + 10) <= *(u16 *)(lVar22 + 8)))
                goto LAB_710012ad58;
            plVar18 = *(long **)(*(long *)(lVar22 + 0x10) + (u64)*(u16 *)(lVar22 + 8) * 8);
            (**(void (**)(long *))(*plVar18 + 0x50))(plVar18);
            *(s16 *)(lVar22 + 8) = *(s16 *)(lVar22 + 8) + 1;
            if (plVar18 == (long *)0) goto LAB_710012ad58;
LAB_710012b16c:
            if (bVar1) {
                (**(void (**)(void *, long *, long, int))(*plVar18 + 0x78))(&local_208, plVar18, lVar23, iVar11);
            }
            else {
                FUN_710012e410(&local_208, plVar18, lVar23, iVar11);
            }
            *(u32 *)&local_200 = 0;
            local_208 = 0x40000000;
            (**(void (**)(long *, u64 *))(*plVar18 + 0x58))(plVar18, &local_208);
            cVar5 = *(char *)(param_1 + 0xd81);
            goto joined_r0x00710012b31c;
        }
LAB_710012ad58:
        cVar5 = *(char *)(param_1 + 0xd81);
    }
joined_r0x00710012b31c:
    // Post-receive: handle send_pending and keepalive
    if (cVar5 == '\0') {
        // No send pending — check keepalive timer
        if (*(int *)(param_1 + 0xd88) == 1) {
            local_208 = 0;
            FUN_71000bb5d0(&local_208);
            if (*(u64 *)(param_1 + 0xdb8) < local_208) {
                *(u32 *)&local_208 = 0;
                nn::err::ErrorResultVariant_ctor((nn::err::ErrorResultVariant *)((u64)&local_208 | 4));
                local_1e0[0] = 0;
                nn::err::ErrorResultVariant_assign(
                    (nn::err::ErrorResultVariant *)((u64)&local_208 | 4), local_1e0);
                FUN_71000bce50(auStack_238, &local_208);
                FUN_71000b4180(param_1 + 0xd88, auStack_238);
            }
        }
    }
    else {
        // Send pending — regenerate crypto and send to all peers
        if ((uVar10 & 1) != 0) {
            FUN_71000b6400(param_1 + 0xdd0, 0x10);
            FUN_71000b6400(param_1 + 0xde0, 0x100);
        }
        if (*(char *)(param_1 + 0xd80) != '\0') {
            uVar10 = 0;
            do {
                FUN_710012b530((u64)&local_208, param_1, uVar10);
                uVar10 = uVar10 + 1;
            } while ((uVar10 & 0xff) < (u32)*(u8 *)(param_1 + 0xd80));
        }
        *(u8 *)(param_1 + 0xd81) = 0;
        plVar24 = (long *)FUN_71000bb680();
        lVar23 = *plVar24;
        local_208 = 0;
        FUN_71000bb5d0(&local_208);
        *(u64 *)(param_1 + 0xdb8) = local_208 + lVar23 * 2000;
    }
LAB_710012b004:
    FUN_71000b1cf0(auStack_98);
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

void FUN_710012ba00(int *param_1, long param_2, u8 *param_3, void *param_4, u32 param_5,
                    u64 *param_6, u32 param_7, u32 param_8, u32 param_9, u8 param_10)
{
    long lVar1;
    long lVar2;
    u32 uVar3;
    u8 uVar4;
    u32 uVar5;
    long *plVar6;
    u64 uVar7;
    u64 uVar8;
    long lVar9;
    u64 *puVar10;
    int iVar11;
    u64 uVar12;
    u64 uVar13;
    u8 local_708[8];
    u8 *local_700;
    u32 local_6f8;
    u32 uStack_6f4;
    u64 local_6f0;
    u32 local_6e8[48];
    u8 auStack_628[16];
    u32 local_618[4];
    int local_608[5];
    u8 auStack_5f4[4];
    u8 auStack_5f0[8];
    u8 auStack_5e8[16];
    u8 auStack_5d8[20];
    u32 local_5c4;
    u32 local_5c0[344];

    uVar13 = *(u64 *)
              (*(long *)&PTR_DAT_71052a4080 + (u64)*(u8 *)(*(long *)&PTR_DAT_71052a4080 + 0x162) * 8
              + 0x168);
    *param_1 = 0;
    nn::err::ErrorResultVariant_ctor((nn::err::ErrorResultVariant *)(param_1 + 1));
    local_5c0[0] = 0;
    nn::err::ErrorResultVariant_assign((nn::err::ErrorResultVariant *)(param_1 + 1), local_5c0);

    // Serialize reply data
    if ((param_10 & 1) == 0) {
        uVar7 = FUN_710011be50(uVar13);
        FUN_710012de50(local_708, uVar7, local_5c0, &local_5c4, 0x515);
    }
    else {
        plVar6 = (long *)FUN_710011be50(uVar13);
        (**(void (**)(u8 *, long *, u32 *, u32 *, u32))(*plVar6 + 0x70))(local_708, plVar6, local_5c0, &local_5c4, 0x515);
    }
    FUN_71000bcf30(param_1, local_708);
    if (*param_1 == 0) {
        lVar1 = param_2 + 0x5c4;
        FUN_71000bb9d0((u8 *)lVar1, 1);
        FUN_71000bb980((u8 *)(param_2 + 0x5c5), local_5c4);
        memcpy((void *)(param_2 + 0x5c9), local_5c0, (u64)local_5c4);
        uVar3 = local_5c4;

        if ((param_9 & 1) == 0) {
            // Full packet with sequence number and crypto
            *(long *)(param_2 + 0xdc8) = *(long *)(param_2 + 0xdc8) + 1;
            FUN_71000bb9d0((u8 *)(lVar1 + (u64)(local_5c4 + 5)), 2);
            uVar5 = (u32)FUN_7100125e30(*(u64 *)(param_2 + 0x58));
            FUN_71000bb9d0((u8 *)(lVar1 + (u64)(uVar3 + 6)), uVar5 & 1);
            FUN_71000bb930((u8 *)(lVar1 + (u64)(uVar3 + 7)), *(u64 *)(param_2 + 0xdc8));
            uVar5 = local_5c4;
            uVar12 = (u64)local_5c4;
            uVar8 = FUN_7100125e30(*(u64 *)(param_2 + 0x58));
            if ((((uVar8 & 1) == 0) ||
                (uVar8 = FUN_7100129a90(*(u64 *)(param_2 + 0x58)), (uVar8 & 1) == 0)) ||
               ((param_8 & 1) == 0)) {
                // Unencrypted reply: fill random padding bytes
                FUN_7100138520(local_708);
                uVar4 = FUN_7100138620(local_708);
                lVar9 = param_2 + 0x5c4;
                *(u8 *)(lVar9 + (u64)(uVar5 - 0x1b)) = uVar4;
                uVar4 = FUN_7100138620(local_708);
                *(u8 *)(lVar9 + (u64)(uVar5 - 0x1a)) = uVar4;
                uVar4 = FUN_7100138620(local_708);
                *(u8 *)(lVar9 + (u64)(uVar5 - 0x19)) = uVar4;
                uVar4 = FUN_7100138620(local_708);
                *(u8 *)(lVar9 + (u64)(uVar5 - 0x18)) = uVar4;
                uVar4 = FUN_7100138620(local_708);
                *(u8 *)(lVar9 + (u64)(uVar5 - 0x17)) = uVar4;
                uVar4 = FUN_7100138620(local_708);
                *(u8 *)(lVar9 + (u64)(uVar5 - 0x16)) = uVar4;
                uVar4 = FUN_7100138620(local_708);
                *(u8 *)(lVar9 + (u64)(uVar5 - 0x15)) = uVar4;
                uVar4 = FUN_7100138620(local_708);
                *(u8 *)(lVar9 + (u64)(uVar5 - 0x14)) = uVar4;
                uVar4 = FUN_7100138620(local_708);
                *(u8 *)(lVar9 + (u64)(uVar5 - 0x13)) = uVar4;
                uVar4 = FUN_7100138620(local_708);
                *(u8 *)(lVar9 + (u64)(uVar5 - 0x12)) = uVar4;
                uVar4 = FUN_7100138620(local_708);
                *(u8 *)(lVar9 + (u64)(uVar5 - 0x11)) = uVar4;
                uVar4 = FUN_7100138620(local_708);
                *(u8 *)(lVar9 + (u64)(uVar5 - 0x10)) = uVar4;
                uVar4 = FUN_7100138620(local_708);
                *(u8 *)(lVar9 + (u64)(uVar5 - 0xf)) = uVar4;
                uVar4 = FUN_7100138620(local_708);
                *(u8 *)(lVar9 + (u64)(uVar5 - 0xe)) = uVar4;
                uVar4 = FUN_7100138620(local_708);
                *(u8 *)(lVar9 + (u64)(uVar5 - 0xd)) = uVar4;
                uVar4 = FUN_7100138620(local_708);
                *(u8 *)(lVar9 + (u64)(uVar5 - 0xc)) = uVar4;
                uVar4 = FUN_7100138620(local_708);
                *(u8 *)(lVar9 + (u64)(uVar5 - 0xb)) = uVar4;
                uVar4 = FUN_7100138620(local_708);
                *(u8 *)(lVar9 + (u64)(uVar5 - 10)) = uVar4;
                uVar4 = FUN_7100138620(local_708);
                *(u8 *)(lVar9 + (u64)(uVar5 - 9)) = uVar4;
                uVar4 = FUN_7100138620(local_708);
                *(u8 *)(lVar9 + (u64)(uVar5 - 8)) = uVar4;
                uVar4 = FUN_7100138620(local_708);
                *(u8 *)(lVar9 + (u64)(uVar5 - 7)) = uVar4;
                uVar4 = FUN_7100138620(local_708);
                *(u8 *)(lVar9 + (u64)(uVar5 - 6)) = uVar4;
                uVar4 = FUN_7100138620(local_708);
                *(u8 *)(lVar9 + (u64)(uVar5 - 5)) = uVar4;
                uVar4 = FUN_7100138620(local_708);
                *(u8 *)(lVar9 + (u64)(uVar5 - 4)) = uVar4;
                uVar4 = FUN_7100138620(local_708);
                *(u8 *)(lVar9 + (u64)(uVar5 - 3)) = uVar4;
                uVar4 = FUN_7100138620(local_708);
                *(u8 *)(lVar9 + (u64)(uVar5 - 2)) = uVar4;
                uVar4 = FUN_7100138620(local_708);
                *(u8 *)(lVar9 + (u64)(uVar5 - 1)) = uVar4;
                uVar4 = FUN_7100138620(local_708);
                *(u8 *)(lVar9 + uVar12) = uVar4;
                uVar4 = FUN_7100138620(local_708);
                *(u8 *)(lVar9 + (u64)(uVar5 + 1)) = uVar4;
                uVar4 = FUN_7100138620(local_708);
                *(u8 *)(lVar9 + (u64)(uVar5 + 2)) = uVar4;
                uVar4 = FUN_7100138620(local_708);
                *(u8 *)(lVar9 + (u64)(uVar5 + 3)) = uVar4;
                uVar4 = FUN_7100138620(local_708);
                *(u8 *)(lVar9 + (u64)(uVar5 + 4)) = uVar4;
                uVar4 = FUN_7100138620(local_708);
                *(u8 *)(lVar9 + (u64)(uVar3 + 0xf)) = uVar4;
                uVar4 = FUN_7100138620(local_708);
                *(u8 *)(lVar9 + (u64)(uVar3 + 0x10)) = uVar4;
                uVar4 = FUN_7100138620(local_708);
                *(u8 *)(lVar9 + (u64)(uVar3 + 0x11)) = uVar4;
                uVar4 = FUN_7100138620(local_708);
                *(u8 *)(lVar9 + (u64)(uVar3 + 0x12)) = uVar4;
                uVar4 = FUN_7100138620(local_708);
                *(u8 *)(lVar9 + (u64)(uVar3 + 0x13)) = uVar4;
                uVar4 = FUN_7100138620(local_708);
                *(u8 *)(lVar9 + (u64)(uVar3 + 0x14)) = uVar4;
                uVar4 = FUN_7100138620(local_708);
                *(u8 *)(lVar9 + (u64)(uVar3 + 0x15)) = uVar4;
                uVar4 = FUN_7100138620(local_708);
                *(u8 *)(lVar9 + (u64)(uVar3 + 0x16)) = uVar4;
                uVar4 = FUN_7100138620(local_708);
                *(u8 *)(lVar9 + (u64)(uVar3 + 0x17)) = uVar4;
                uVar4 = FUN_7100138620(local_708);
                *(u8 *)(lVar9 + (u64)(uVar3 + 0x18)) = uVar4;
                uVar4 = FUN_7100138620(local_708);
                *(u8 *)(lVar9 + (u64)(uVar3 + 0x19)) = uVar4;
                uVar4 = FUN_7100138620(local_708);
                *(u8 *)(lVar9 + (u64)(uVar3 + 0x1a)) = uVar4;
                uVar4 = FUN_7100138620(local_708);
                *(u8 *)(lVar9 + (u64)(uVar3 + 0x1b)) = uVar4;
                uVar4 = FUN_7100138620(local_708);
                *(u8 *)(lVar9 + (u64)(uVar3 + 0x1c)) = uVar4;
                uVar4 = FUN_7100138620(local_708);
                *(u8 *)(lVar9 + (u64)(uVar3 + 0x1d)) = uVar4;
                uVar4 = FUN_7100138620(local_708);
                *(u8 *)(lVar9 + (u64)(uVar3 + 0x1e)) = uVar4;
                uVar4 = FUN_7100138620(local_708);
                *(u8 *)(lVar9 + (u64)(uVar3 + 0x1f)) = uVar4;
                uVar4 = FUN_7100138620(local_708);
                *(u8 *)(lVar9 + (u64)(uVar3 + 0x20)) = uVar4;
                uVar4 = FUN_7100138620(local_708);
                *(u8 *)(lVar9 + (u64)(uVar3 + 0x21)) = uVar4;
                uVar4 = FUN_7100138620(local_708);
                *(u8 *)(lVar9 + (u64)(uVar3 + 0x22)) = uVar4;
                uVar4 = FUN_7100138620(local_708);
                *(u8 *)(lVar9 + (u64)(uVar3 + 0x23)) = uVar4;
                uVar4 = FUN_7100138620(local_708);
                *(u8 *)(lVar9 + (u64)(uVar3 + 0x24)) = uVar4;
                uVar4 = FUN_7100138620(local_708);
                *(u8 *)(lVar9 + (u64)(uVar3 + 0x25)) = uVar4;
                uVar4 = FUN_7100138620(local_708);
                *(u8 *)(lVar9 + (u64)(uVar3 + 0x26)) = uVar4;
                uVar4 = FUN_7100138620(local_708);
                *(u8 *)(lVar9 + (u64)(uVar3 + 0x27)) = uVar4;
                uVar4 = FUN_7100138620(local_708);
                *(u8 *)(lVar9 + (u64)(uVar3 + 0x28)) = uVar4;
                uVar4 = FUN_7100138620(local_708);
                *(u8 *)(lVar9 + (u64)(uVar3 + 0x29)) = uVar4;
                uVar4 = FUN_7100138620(local_708);
                *(u8 *)(lVar9 + (u64)(uVar3 + 0x2a)) = uVar4;
                uVar4 = FUN_7100138620(local_708);
                *(u8 *)(lVar9 + (u64)(uVar3 + 0x2b)) = uVar4;
                uVar4 = FUN_7100138620(local_708);
                *(u8 *)(lVar9 + (u64)(uVar3 + 0x2c)) = uVar4;
                uVar4 = FUN_7100138620(local_708);
                *(u8 *)(lVar9 + (u64)(uVar3 + 0x2d)) = uVar4;
                uVar4 = FUN_7100138620(local_708);
                *(u8 *)(lVar9 + (u64)(uVar3 + 0x2e)) = uVar4;
                uVar4 = FUN_7100138620(local_708);
                *(u8 *)(lVar9 + (u64)(uVar3 + 0x2f)) = uVar4;
                uVar4 = FUN_7100138620(local_708);
                *(u8 *)(lVar9 + (u64)(uVar3 + 0x30)) = uVar4;
                uVar4 = FUN_7100138620(local_708);
                *(u8 *)(lVar9 + (u64)(uVar3 + 0x31)) = uVar4;
                uVar4 = FUN_7100138620(local_708);
                *(u8 *)(lVar9 + (u64)(uVar3 + 0x32)) = uVar4;
                uVar4 = FUN_7100138620(local_708);
                *(u8 *)(lVar9 + (u64)(uVar3 + 0x33)) = uVar4;
                uVar4 = FUN_7100138620(local_708);
                *(u8 *)(lVar9 + (u64)(uVar3 + 0x34)) = uVar4;
                uVar4 = FUN_7100138620(local_708);
                *(u8 *)(lVar9 + (u64)(uVar3 + 0x35)) = uVar4;
                uVar4 = FUN_7100138620(local_708);
                *(u8 *)(lVar9 + (u64)(uVar3 + 0x36)) = uVar4;
                uVar4 = FUN_7100138620(local_708);
                *(u8 *)(lVar9 + (u64)(uVar3 + 0x37)) = uVar4;
                uVar4 = FUN_7100138620(local_708);
                *(u8 *)(lVar9 + (u64)(uVar3 + 0x38)) = uVar4;
                uVar4 = FUN_7100138620(local_708);
                *(u8 *)(lVar9 + (u64)(uVar3 + 0x39)) = uVar4;
                uVar4 = FUN_7100138620(local_708);
                *(u8 *)(lVar9 + (u64)(uVar3 + 0x3a)) = uVar4;
                uVar4 = FUN_7100138620(local_708);
                *(u8 *)(lVar9 + (u64)(uVar3 + 0x3b)) = uVar4;
                uVar4 = FUN_7100138620(local_708);
                *(u8 *)(lVar9 + (u64)(uVar3 + 0x3c)) = uVar4;
                uVar4 = FUN_7100138620(local_708);
                *(u8 *)(lVar9 + (u64)(uVar3 + 0x3d)) = uVar4;
                uVar4 = FUN_7100138620(local_708);
                *(u8 *)(lVar9 + (u64)(uVar3 + 0x3e)) = uVar4;
            }
            else {
                // Encrypted reply: decrypt + HMAC + auth tag
                if (0xf < param_5) {
                    param_5 = 0x10;
                }
                FUN_71000b6400((long)auStack_5e8, 0x10);
                memcpy(auStack_5d8, param_4, (u64)param_5);
                uVar8 = FUN_710011bfe0(uVar13);
                if ((uVar8 & 1) == 0) {
                    FUN_7100119a50(uVar13, auStack_5e8, 0x20);
                    FUN_7100125f90(*(u64 *)(param_2 + 0x58));
                    memcpy((void *)(param_2 + (u64)(uVar5 - 0x1b) + 0x5c4), auStack_5e8, 0x20);
                }
                memcpy((void *)(param_2 + (u64)(uVar3 + 0xf) + 0x5c4), auStack_5e8, 0x10);
                uVar8 = FUN_71000b1f50(*(long *)(param_2 + 0x58) + 0x70);
                if ((uVar8 & 1) == 0) {
                    local_608[0] = 0;
                    FUN_71000b1da0(local_708, *(long *)(param_2 + 0x58) + 0x70, local_608);
                    FUN_71000bb980(auStack_5f4, (u32)local_608[0]);
                }
                else {
                    *(u64 *)local_708 = 0;
                    local_700 = (u8 *)0;
                    FUN_71000b2110(local_608, *(long *)(param_2 + 0x58) + 0x70, local_708);
                    memcpy(auStack_5f4, local_708, 4);
                }
                FUN_71000bb930(auStack_5f0, *(u64 *)(param_2 + 0xdc8));
                FUN_71001296b0(local_708, *(u64 *)(param_2 + 0x58), auStack_5e8, 0x20, local_608, 0x10);
                FUN_71000bcf30(param_1, local_708);
                FUN_71001297f0(local_708, *(u64 *)(param_2 + 0x58), (long)param_6, param_7, local_618, 0x10);
                FUN_71000bcf30(param_1, local_708);
                local_6f8 = 0xc;
                *(u32 *)local_708 = 1;
                local_6e8[0] = 0x10;
                local_700 = auStack_5f4;
                local_6f0 = (u64)local_608;
                FUN_71000b4c70((int *)auStack_628, param_2 + 0x5c4 + (u64)(uVar3 + 0x2f), (long)local_618, 0x10,
                               param_2 + 0x5c4 + (u64)(uVar3 + 0x1f), 0x10, local_708);
            }
            iVar11 = local_5c4 + 0x3f;
        }
        else {
            // Short packet mode — no sequence/key/padding overhead
            iVar11 = local_5c4 - 0x1b;
        }

        // Build destination address for logging
        FUN_71000b1c60(auStack_5e8, (long)param_3);
        local_700 = (u8 *)((long)&local_6f0 + 4);
        *(u64 *)local_708 = (u64)(*(long *)&PTR_DAT_71052a3c30 + 0x10);
        local_6f8 = 0xc0;
        *(u8 *)((long)&local_6f0 + 4) = 0;
        lVar9 = 0;
        puVar10 = (u64 *)local_708;
        do {
            *(u16 *)((long)puVar10 + 0x1d) = 0;
            lVar2 = lVar9 + 4;
            *(u8 *)((long)puVar10 + 0x1f) = 0;
            puVar10 = (u64 *)((long)local_708 + lVar2);
            *(u8 *)((long)local_6e8 + lVar9) = 0;
            lVar9 = lVar2;
        } while (lVar2 != 0xc0);
        uStack_6f4 = 0;
        *(u32 *)&local_6f0 = 0;
        FUN_71000b1fa0(auStack_5e8, (void *)*(u64 *)local_708);

        // Triple-send for UDP reliability
        param_2 = param_2 + 0x60;

        // Send #1
        FUN_71000ba5c0(local_608, param_2, lVar1, iVar11, auStack_5e8, auStack_628);
        FUN_71000bcf30(param_1, local_608);
        if (*param_1 != 0) {
            local_608[0] = 0x4c0d;
            nn::err::ErrorResultVariant_ctor((nn::err::ErrorResultVariant *)((u64)local_608 | 4));
            local_618[0] = 0;
            nn::err::ErrorResultVariant_assign(
                (nn::err::ErrorResultVariant *)((u64)local_608 | 4), local_618);
            if (*param_1 != local_608[0]) {
                FUN_7100121af0(*(u64 *)(*(long *)&PTR_DAT_71052a4080 + 8));
            }
        }

        // Send #2
        FUN_71000ba5c0(local_608, param_2, lVar1, iVar11, auStack_5e8, auStack_628);
        FUN_71000bcf30(param_1, local_608);
        if (*param_1 != 0) {
            local_608[0] = 0x4c0d;
            nn::err::ErrorResultVariant_ctor((nn::err::ErrorResultVariant *)((u64)local_608 | 4));
            local_618[0] = 0;
            nn::err::ErrorResultVariant_assign(
                (nn::err::ErrorResultVariant *)((u64)local_608 | 4), local_618);
            if (*param_1 != local_608[0]) {
                FUN_7100121af0(*(u64 *)(*(long *)&PTR_DAT_71052a4080 + 8));
            }
        }

        // Send #3
        FUN_71000ba5c0(local_608, param_2, lVar1, iVar11, auStack_5e8, auStack_628);
        FUN_71000bcf30(param_1, local_608);
        if (*param_1 != 0) {
            local_608[0] = 0x4c0d;
            nn::err::ErrorResultVariant_ctor((nn::err::ErrorResultVariant *)((u64)local_608 | 4));
            local_618[0] = 0;
            nn::err::ErrorResultVariant_assign(
                (nn::err::ErrorResultVariant *)((u64)local_608 | 4), local_618);
            if (*param_1 != local_608[0]) {
                FUN_7100121af0(*(u64 *)(*(long *)&PTR_DAT_71052a4080 + 8));
            }
        }

        FUN_71000b1cf0(auStack_5e8);
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

void FUN_710012cf80(u64 param_1, long param_2, u8 param_3, u32 *param_4)
{
    u32 local_38[4];
    u32 local_28[2];

    if ((param_4 == (u32 *)0) || (5 < param_3)) {
        local_38[0] = 0x10c07;
    }
    else {
        *param_4 = *(u32 *)(param_2 + (u64)param_3 * 4 + 0x20);
        local_38[0] = 0;
    }
    nn::err::ErrorResultVariant_ctor((nn::err::ErrorResultVariant *)((u64)local_38 | 4));
    local_28[0] = 0;
    nn::err::ErrorResultVariant_assign(
        (nn::err::ErrorResultVariant *)((u64)local_38 | 4), local_28);
    FUN_71000bce50((void *)param_1, local_38);
}

u64 FUN_710012ed20(long param_1, long *param_2)
{
    u16 uVar1;
    bool bVar2;
    u16 uVar3;
    s16 sVar4;
    s16 sVar5;
    int iVar6;
    int iVar7;
    u64 uVar8;
    u32 uVar9;
    long lVar10;
    long lVar11;
    u32 *puVar12;
    u64 uVar13;
    u32 *puVar14;
    long lVar15;
    int local_60[4];
    u32 local_44;

    iVar6 = (**(int (**)(long *))(*param_2 + 0x10))(param_2);
    uVar9 = *(u32 *)(param_1 + 0x260);
    if (((uVar9 >> 4 & 1) == 0) || (*(int *)(param_1 + 0x20) == iVar6)) {
        if (((uVar9 & 1) != 0) &&
           ((uVar1 = *(u16 *)(param_1 + 600), uVar1 != 0xffff && (*(s16 *)(param_1 + 0x256) != -1))
           )) {
            uVar3 = (**(u16 (**)(long *))(*param_2 + 0x28))(param_2);
            if (uVar3 < uVar1) {
                return 0;
            }
            uVar1 = *(u16 *)(param_1 + 0x256);
            uVar3 = (**(u16 (**)(long *))(*param_2 + 0x28))(param_2);
            if (uVar1 < uVar3) {
                return 0;
            }
            uVar9 = *(u32 *)(param_1 + 0x260);
        }
        if ((((uVar9 >> 1 & 1) != 0) && (uVar1 = *(u16 *)(param_1 + 0x25c), uVar1 != 0xffff)) &&
           (*(s16 *)(param_1 + 0x25a) != -1)) {
            uVar3 = (**(u16 (**)(long *))(*param_2 + 0x30))(param_2);
            if (uVar3 < uVar1) {
                return 0;
            }
            uVar1 = *(u16 *)(param_1 + 0x25a);
            uVar3 = (**(u16 (**)(long *))(*param_2 + 0x30))(param_2);
            if (uVar1 < uVar3) {
                return 0;
            }
            uVar9 = *(u32 *)(param_1 + 0x260);
        }
        if ((((uVar9 >> 5 & 1) == 0) ||
            (iVar6 = *(int *)(param_1 + 0x24), iVar7 = (int)FUN_710012cea0((long)param_2), iVar6 == iVar7)) &&
           ((*(char *)(param_1 + 0x25e) == '\0' ||
            (uVar8 = (**(u64 (**)(long *))(*param_2 + 0x38))(param_2), (uVar8 & 1) != 0)))) {
            if (*(char *)(param_1 + 0x25f) != '\0') {
                sVar4 = (**(s16 (**)(long *))(*param_2 + 0x20))(param_2);
                sVar5 = (**(s16 (**)(long *))(*param_2 + 0x30))(param_2);
                if (sVar4 == sVar5) {
                    return 0;
                }
            }
            uVar8 = 0;
            puVar14 = (u32 *)(param_1 + 0x34);
            lVar15 = param_1 + 0x28;
            do {
                if ((*(u32 *)(param_1 + 0x260) & (0x40 << (u64)((u32)uVar8 & 0x1f))) != 0) {
                    if (*(char *)(param_1 + uVar8 + 0x250) == '\0') {
                        lVar11 = param_1 + uVar8 * 4;
                        if (*(int *)(lVar11 + 0x208) != 0) {
                            local_44 = 0;
                            FUN_710012cf80((u64)local_60, (long)param_2, (u8)(uVar8 & 0xff), &local_44);
                            if (local_60[0] != 0) {
                                return 0;
                            }
                            uVar9 = *(u32 *)(lVar11 + 0x208);
                            uVar13 = (u64)uVar9;
                            if (uVar9 == 0) {
                                return 0;
                            }
                            if (uVar13 - 1 < 3) {
                                lVar11 = 0;
                                bVar2 = false;
                            }
                            else {
                                lVar11 = 0;
                                bVar2 = false;
                                puVar12 = puVar14;
                                do {
                                    lVar11 = lVar11 + 4;
                                    bVar2 = (bool)(bVar2 | local_44 == puVar12[-3] | local_44 == puVar12[-2] |
                                                   local_44 == puVar12[-1] | local_44 == *puVar12);
                                    puVar12 = puVar12 + 4;
                                } while (uVar13 - (uVar13 & 3) != (u64)lVar11);
                            }
                            if ((uVar9 & 3) != 0) {
                                lVar10 = -(u64)(uVar13 & 3);
                                puVar12 = (u32 *)(lVar15 + lVar11 * 4);
                                do {
                                    lVar10 = lVar10 + 1;
                                    bVar2 = (bool)(bVar2 | local_44 == *puVar12);
                                    puVar12 = puVar12 + 1;
                                } while (lVar10 != 0);
                            }
                            if (!bVar2) {
                                return 0;
                            }
                        }
                    }
                    else {
                        local_44 = 0;
                        FUN_710012cf80((u64)local_60, (long)param_2, (u8)(uVar8 & 0xff), &local_44);
                        if (local_60[0] != 0) {
                            return 0;
                        }
                        lVar11 = param_1 + uVar8 * 4;
                        if (local_44 < *(u32 *)(lVar11 + 0x220)) {
                            return 0;
                        }
                        if (*(u32 *)(lVar11 + 0x238) < local_44) {
                            return 0;
                        }
                    }
                }
                uVar8 = uVar8 + 1;
                puVar14 = puVar14 + 0x14;
                lVar15 = lVar15 + 0x50;
                if (5 < uVar8) {
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

void FUN_710012ebe0(u64 param_1, long param_2, u32 param_3, u32 param_4)
{
    u32 local_38[4];
    u32 local_28[2];

    if (param_3 < 6) {
        *(u32 *)(param_2 + (u64)param_3 * 0x50 + 0x28) = param_4;
        *(u32 *)(param_2 + (u64)param_3 * 4 + 0x208) = 1;
        *(u8 *)(param_2 + (u64)param_3 + 0x250) = 0;
        *(u32 *)(param_2 + 0x260) = *(u32 *)(param_2 + 0x260) | (1 << (u64)(param_3 + 6 & 0x1f));
        local_38[0] = 0;
    }
    else {
        local_38[0] = 0x10c07;
    }
    nn::err::ErrorResultVariant_ctor((nn::err::ErrorResultVariant *)((u64)local_38 | 4));
    local_28[0] = 0;
    nn::err::ErrorResultVariant_assign(
        (nn::err::ErrorResultVariant *)((u64)local_38 | 4), local_28);
    FUN_71000bce50((void *)param_1, local_38);
}

// FUN_710012ec80 — Set slot to match value range [min, max]
// Address: 0x710012ec80 | Size: 160 bytes

void FUN_710012ec80(u64 param_1, long param_2, u32 param_3, u32 param_4, u32 param_5)
{
    long lVar1;
    u32 local_38[4];
    u32 local_28[2];

    if ((param_3 < 6) && (param_4 <= param_5)) {
        lVar1 = param_2 + (u64)param_3 * 4;
        *(u32 *)(lVar1 + 0x220) = param_4;
        *(u32 *)(lVar1 + 0x238) = param_5;
        *(u8 *)(param_2 + (u64)param_3 + 0x250) = 1;
        *(u32 *)(param_2 + 0x260) = *(u32 *)(param_2 + 0x260) | (1 << (u64)(param_3 + 6 & 0x1f));
        local_38[0] = 0;
    }
    else {
        local_38[0] = 0x10c07;
    }
    nn::err::ErrorResultVariant_ctor((nn::err::ErrorResultVariant *)((u64)local_38 | 4));
    local_28[0] = 0;
    nn::err::ErrorResultVariant_assign(
        (nn::err::ErrorResultVariant *)((u64)local_38 | 4), local_28);
    FUN_71000bce50((void *)param_1, local_38);
}

// FUN_710012ea10 — Reset all 6 frame state slots to defaults
// Address: 0x710012ea10 | Size: 272 bytes
//
// Clears all slot data, sets frame ranges to 0xFFFF (no filter),
// sets both bool flags to true, and resets the dirty bitmask.
// Final field at +0xc is set to 100 (default tick count).

void FUN_710012ea10(long param_1)
{
    FUN_710014f0b0();
    *(u64 *)(param_1 + 0x20) = 0;
    *(u64 *)(param_1 + 0x256) = 0xffffffffffffffffULL;
    *(u16 *)(param_1 + 0x25e) = 0x101;
    *(u32 *)(param_1 + 0x260) = 0;
    // Slot 0
    memset((void *)(param_1 + 0x28), 0, 0x50);
    *(u32 *)(param_1 + 0x208) = 0;
    *(u32 *)(param_1 + 0x220) = 0;
    *(u32 *)(param_1 + 0x238) = 0;
    *(u8 *)(param_1 + 0x250) = 0;
    // Slot 1
    memset((void *)(param_1 + 0x78), 0, 0x50);
    *(u32 *)(param_1 + 0x20c) = 0;
    *(u32 *)(param_1 + 0x224) = 0;
    *(u32 *)(param_1 + 0x23c) = 0;
    *(u8 *)(param_1 + 0x251) = 0;
    // Slot 2
    memset((void *)(param_1 + 200), 0, 0x50);
    *(u32 *)(param_1 + 0x210) = 0;
    *(u32 *)(param_1 + 0x228) = 0;
    *(u32 *)(param_1 + 0x240) = 0;
    *(u8 *)(param_1 + 0x252) = 0;
    // Slot 3
    memset((void *)(param_1 + 0x118), 0, 0x50);
    *(u32 *)(param_1 + 0x214) = 0;
    *(u32 *)(param_1 + 0x22c) = 0;
    *(u32 *)(param_1 + 0x244) = 0;
    *(u8 *)(param_1 + 0x253) = 0;
    // Slot 4
    memset((void *)(param_1 + 0x168), 0, 0x50);
    *(u32 *)(param_1 + 0x218) = 0;
    *(u32 *)(param_1 + 0x230) = 0;
    *(u32 *)(param_1 + 0x248) = 0;
    *(u8 *)(param_1 + 0x254) = 0;
    // Slot 5
    memset((void *)(param_1 + 0x1b8), 0, 0x50);
    *(u32 *)(param_1 + 0x21c) = 0;
    *(u32 *)(param_1 + 0x234) = 0;
    *(u32 *)(param_1 + 0x24c) = 0;
    *(u8 *)(param_1 + 0x255) = 0;
    // Default tick count
    *(u32 *)(param_1 + 0xc) = 100;
}

// FUN_710012fbb0 — Frame data sub-object constructor
// Address: 0x710012fbb0 | Size: 128 bytes
// Initializes a small frame data object with multiple vtable pointers.

void FUN_710012fbb0(long *param_1)
{
    u8 *puVar1;
    u8 *puVar2;

    FUN_710014f150();
    puVar1 = &PTR_DAT_71052a4ba0 + 0x10;
    puVar2 = &PTR_DAT_71052a4870 + 0x10;
    param_1[2] = (long)(&PTR_DAT_71052a4ba0 + 0x50);
    param_1[3] = (long)puVar2;
    *param_1 = (long)puVar1;
    *(u64 *)((long)param_1 + 0x34) = 0;
    param_1[0xc] = 0;
    *(u32 *)((long)param_1 + 0x3c) = 0;
    param_1[8] = 0;
    param_1[4] = (long)param_1 + 0x34;
    param_1[5] = 0x28;
    *(u16 *)(param_1 + 9) = 0;
    *(u64 *)((long)param_1 + 0x4a) = 0;
    *(u64 *)((long)param_1 + 0x52) = 0;
    *(u16 *)((long)param_1 + 0x5a) = 0;
    *(u8 *)((long)param_1 + 0x5c) = 0;
    *(u32 *)(param_1 + 6) = 0;
}
