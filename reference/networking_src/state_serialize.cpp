/*
 * CSS State Serialization Trio
 *
 * These three functions form the game's CSS (Character Select Screen) state
 * save/restore system. They demonstrate SSBU's approach to serializing game
 * state into flat buffers — the strongest existing pattern for how battle
 * state could be snapshotted for rollback.
 *
 * Functions:
 *   css_serialize_state_to_buffer   @ 0x71016ed7c0 (5,744 bytes)
 *   css_restore_state_from_save     @ 0x71017a24f0 (4,928 bytes)
 *   css_read_state_to_compact_buffer @ 0x71016e2df0 (560 bytes)
 *
 * Key patterns:
 *   - FNV-style name hashing (seed 0x811c9dc5, prime 0x89)
 *   - UTF-16 null-terminated player names (max 11 chars)
 *   - BSS state region: DAT_7105307760..DAT_710530d368 (~11KB)
 *   - Guard variables for one-time initialization (__cxa_guard_acquire)
 *   - DLC bitmask validation against download manager
 *   - Mutex-protected network buffer copy
 *   - Online mode (mode==2) overrides player data from network globals
 *   - UTF-16 to UTF-8 conversion for online player tags
 *
 * NOTE: This file prioritizes READABILITY and DOCUMENTATION over matching.
 *       The Ghidra decompilation is restructured into clean C++ with comments
 *       explaining every serialized field and its game meaning.
 */

#include "types.h"
#include "app/CSSState.h"

#include <cstring>  // memset, memcpy

// ============================================================
// External BSS Globals (CSS state region)
// ============================================================

// --- CSS State Header ---
extern u32  DAT_7105307760;                // CSS state header field 1
extern u32  DAT_7105307764;                // CSS state header field 2
extern u32  DAT_7105307768;                // CSS data field (mode/variant)
extern u8   BSS_CSS_DATA_ARRAY;            // CSS data array flag

// --- Player 0 Name (local player) ---
extern u32  DAT_7105307774;                // Player 0 name FNV hash
extern u32  DAT_7105307778;                // Player 0 name length
extern u16  DAT_710530777c;                // Player 0 name char[0]
extern u16  DAT_710530777e;                // Player 0 name char[1]
extern u16  DAT_7105307780;                // ... through char[10]
extern u16  DAT_7105307782;
extern u16  DAT_7105307784;
extern u16  DAT_7105307786;
extern u16  DAT_7105307788;
extern u16  DAT_710530778a;
extern u16  DAT_710530778c;
extern u16  DAT_710530778e;
extern u16  DAT_7105307790;
extern u32  DAT_7105307794;                // Player 0 extra data

// Player 1-6 follow the same pattern at 0x1C8-byte intervals in BSS.
// Each slot: name_hash, name_len, name[11], extra_data, deep_data[0x1A0]
// Slots 1-6 BSS bases: 0x7105307938, 0x7105307B00, 0x7105307CC8,
//                       0x7105307E90, 0x7105308058, 0x7105308220

// --- CSS Configuration Globals ---
extern u64  _CSS_MODE_FLAGS;               // CSS mode flags (8 bytes)
extern u8   CSS_MAX_PLAYER_COUNT;          // Max player count for current mode
extern u64  CSS_INITIAL_PLAYER_BITMASK;    // Initial player slot bitmask
extern u32  CSS_MAX_SLOTS_VARIANT;         // Slot variant

// --- DLC / Download Content ---
extern u64  DAT_71053099b0;                // DLC bitmask (first 64 bits)
extern u64  DAT_71053099b8;                // DLC bitmask (bits 64-119)

// --- Game Mode ---
extern u32  DAT_71053040f0;                // Packed game mode ID
extern u32  DAT_710530c7d0;                // Sub-mode / battle type
extern u32  DAT_710530c560;                // Team battle state (0 = team battle enabled)

// --- Online Player Data (used when mode == CSS_ONLINE_MODE) ---
extern u8   DAT_71053059b0;                // Online player type
extern u8   DAT_71053059b1;                // Online player icon
extern u8   DAT_71053059b2;                // Online player variant
extern u8   DAT_7105305e8c;                // Online icon type
extern u8   DAT_7105305e8d;                // Online sub-mode override
extern u8   DAT_7105305e8e;                // Online flag 1 (inverted → bool)
extern u8   DAT_7105305e8f;                // Online flag 2 (inverted → bool)
extern u8   DAT_7105305e91;                // Online flag 3 (inverted → bool)
extern u64  DAT_7105305e98;                // Online profile data
extern u8   DAT_7105305ea0;                // Online tag data region base
extern u16  DAT_7105305ee4;                // Online name 2 first char (length indicator)
extern u16  DAT_7105305ee6;                // Online name 2 start (UTF-16)
extern u64  DAT_7105305ee0;                // Online name 2 presence flag
extern u8   DAT_7105305ef8;                // Online name 2 icon
extern u16  DAT_7105305f00;                // Online name 1 presence flag
extern u16  DAT_7105305f04;                // Online name 1 first char (length indicator)
extern u16  DAT_7105305f06;                // Online name 1 start (UTF-16)

// --- Profile Chain ---
extern u64  DAT_710530d2a8;                // Profile chain data
extern u64  DAT_71053097b0;                // Profile entry 0 base
// Profile entries continue at DAT_71053097b8, c0, c8, d0, d8, e0, e8, f0, f8, 9800, 9808, 9810

// --- Other ---
extern u8   DAT_71053099c0;                // Team enabled flag (compact buffer)
extern u8   DAT_710530c564;                // Team flag byte
extern u8   DAT_7105305970;                // Online status flag
extern u64  DAT_710530996c;                // State field
extern u64  DAT_71053390a0;                // Download manager pointer
extern u8   g_team_param_init_guard;       // Guard for team param init
extern u64  DAT_71052c3c58;                // Scene manager pointer
extern u64  DAT_710532e730;                // Content manager pointer
extern u64  DAT_710532e7d0;                // Network manager pointer
extern u64  DAT_71052b82e0;                // One-time init guard

// ============================================================
// External Functions
// ============================================================

extern "C" {
    // Guard acquire/release (C++ ABI)
    int  __cxa_guard_acquire(void* guard);
    void __cxa_guard_release(void* guard);

    // CSS helper functions
    void global_param_init_sets_team_flag(void);          // Initializes team parameters
    void FUN_71016b6bb0(void* dst, void* src);            // Deep player data copy (0x1A0 bytes)
    void FUN_7101695c80(void* buf);                       // Initialize 0x308-byte player data buffer
    void FUN_7101696040(void* dst, void* src);            // Copy tag/icon data
    void FUN_71016eee30(void* dst, void* src);            // Copy extended data
    void FUN_71016f64e0(void* ptr);                       // Get network slot index
    char FUN_71016ea430(void** param_1, u8 slot);         // Look up player by slot index
    void* FUN_71016b6ac0(void* scene, char player_idx);   // Get player data pointer
    u8   FUN_7101686610(void* ptr);                       // Get max player count
    u64  FUN_710168eb40(void* ptr, u8 max, u64 idx);     // Check if player slot is active
    void FUN_7101697850(void* a, void* b);                // Network buffer serialize helper
    void FUN_71017a0d20(void* dst, void* src);            // Copy second data array
    void FUN_71017a11f0(void* dst, void* src);            // Copy extended state
    u64  FUN_71017cefe0(u64 ctx, u32 id, void* out);     // Profile chain ID resolution
    void FUN_7101684440(void* dst, u64 a, u64 b);        // Copy profile pair
    void FUN_7101684280(void* dst, u64 a, u64 b);        // Copy profile variant pair
    void FUN_71017a2020(void* dst, u64 a, u64 b);        // Copy profile chain pair
    void FUN_71000001c0(void* fn, void* dat, void* loop); // Register atexit handler
    void FUN_7101763de0(void);                            // Team param cleanup

    // DLC validation
    u64  FUN_71032b2b20(long base, u32 idx);              // Get DLC content ID
    u64  FUN_71032b4c80(u64 list, u64 id);                // Check DLC content exists
    u64  FUN_7100556c40(u64 mgr, u64 id);                // Check DLC is purchased

    // Profile chain
    u64  FUN_71032b1e30(u64 list, u64 key);               // Look up profile by key
}

// ============================================================
// Helper: Compute FNV-style name hash
// ============================================================

/*
 * Computes the CSS player name hash.
 * Algorithm: hash = seed; for each non-zero UTF-16 char: hash = (hash * 0x89) ^ char
 * This is a custom FNV variant (non-standard prime).
 */
static u32 css_compute_name_hash(const u16* name) {
    u32 hash = CSS_NAME_HASH_SEED;
    u32 c = (u32)name[0];
    if (c != 0) {
        const u16* p = &name[1];
        do {
            hash = (hash * CSS_NAME_HASH_PRIME) ^ c;
            c = (u32)*p;
            p++;
        } while (c != 0);
    }
    return hash;
}

// ============================================================
// Helper: Copy UTF-16 name with null termination and length
// ============================================================

/*
 * Copies a null-terminated UTF-16 player name from src to buffer,
 * writes the length and hash, and null-terminates.
 *
 * Buffer layout at dst:
 *   +0x00: hash (u32)
 *   +0x04: length (u32)
 *   +0x08: name chars (u16[length+1], null-terminated)
 *
 * The name copy loop in the original code is an unrolled chain of
 * if/else that copies up to 11 characters, stopping at the first
 * null character. This is abstracted into a loop here.
 */
static void css_copy_name_to_buffer(u8* dst, const u16* src) {
    u16* buf_name = (u16*)(dst + 8);
    u32 count = 0;

    // Copy up to CSS_MAX_NAME_CHARS characters, stopping at null
    for (u32 i = 0; i < CSS_MAX_NAME_CHARS; i++) {
        if (src[i] == 0) break;
        buf_name[i] = src[i];
        count = i + 1;
    }

    // Null-terminate and write length
    buf_name[count] = 0;
    *(u32*)(dst + 4) = count;

    // Compute and write hash
    *(u32*)(dst + 0) = css_compute_name_hash(buf_name);
}

// ============================================================
// Helper: Restore UTF-16 name from buffer to BSS globals
// ============================================================

/*
 * Restores a player name from the save buffer into BSS globals.
 * This is the inverse of the serialize name copy.
 *
 * The original code has 7 copies of this (one per player slot),
 * each writing to a different set of BSS globals at 0x1C8-byte spacing.
 * The name starts 0x1C bytes into each slot.
 */
static void css_restore_name_to_bss(u16* bss_chars, u32* bss_length, u32* bss_hash,
                                     const u16* src) {
    u32 count = 0;

    if (src[0] != 0) {
        for (u32 i = 0; i < CSS_MAX_NAME_CHARS; i++) {
            if (src[i] == 0) break;
            bss_chars[i] = src[i];
            count = i + 1;
        }
    }

    // Null-terminate
    bss_chars[count] = 0;
    *bss_length = count;

    // Recompute FNV hash
    *bss_hash = css_compute_name_hash(bss_chars);
}

// ============================================================
// css_read_state_to_compact_buffer
// Address: 0x71016e2df0 | Size: 560 bytes
// ============================================================

/*
 * Reads CSS scene state into a compact serialization buffer suitable for
 * network transmission. Contains only essential game configuration — no
 * player names, profiles, or tag data.
 *
 * This is the simplest of the three functions. It reads from BSS globals
 * and writes a ~105-byte compact representation.
 */
void css_read_state_to_compact_buffer(u8* param_1) {
    // --- Initialize team parameters if this is the first call ---
    // Uses C++ guard variable pattern (__cxa_guard_acquire/release)
    if ((g_team_param_init_guard & 1) == 0) {
        if (__cxa_guard_acquire(&g_team_param_init_guard)) {
            global_param_init_sets_team_flag();
            FUN_71000001c0((void*)FUN_7101763de0, (void*)&DAT_71052c4180,
                           (void*)0 /* PTR_LOOP_7104f16000 */);
            __cxa_guard_release(&g_team_param_init_guard);
        }
    }

    // --- Write compact buffer fields ---

    // +0x00: Team/mode flags
    param_1[0x00] = DAT_71053099c0;        // Team enabled flag
    param_1[0x01] = (u8)DAT_710530c7d0;    // Game mode (battle type)
    param_1[0x02] = (u8)DAT_7105307768;    // CSS data field

    // +0x04..0x1B: Rule configuration (3 x 8 bytes from CSS rule globals)
    // These are the game rules: time limit, stock count, items, etc.
    // Stored as raw bytes from the DAT_7105309974 region.
    *(u64*)(param_1 + 0x04) = *(u64*)&_CSS_MODE_FLAGS;  // Simplified; actual reads from 0x7105309974..
    // (In the original, these are 3 separate 8-byte loads from consecutive globals)

    // +0x1C..0x2B: CSS_MODE_FLAGS and continued rule data
    // +0x2C: Rule flag byte
    // +0x30: CSS_MAX_PLAYER_COUNT
    param_1[0x30] = CSS_MAX_PLAYER_COUNT;

    // +0x34: CSS_INITIAL_PLAYER_BITMASK (8 bytes)
    *(u64*)(param_1 + 0x34) = CSS_INITIAL_PLAYER_BITMASK;

    // +0x3C: CSS_MAX_SLOTS_VARIANT (4 bytes)
    *(u32*)(param_1 + 0x3C) = CSS_MAX_SLOTS_VARIANT;

    // +0x40: DLC content bitmask (2 x 8 bytes = 120 bits for 120 DLC items)
    *(u64*)(param_1 + 0x40) = DAT_71053099b0;
    *(u64*)(param_1 + 0x48) = DAT_71053099b8;

    // +0x50: State field
    *(u64*)(param_1 + 0x50) = DAT_710530996c;

    // +0x58: Team battle state (non-zero means team battle disabled)
    *(u32*)(param_1 + 0x58) = DAT_710530c560;

    // +0x5C: Team flag byte
    param_1[0x5C] = DAT_710530c564;

    // +0x60: Profile chain data
    *(u64*)(param_1 + 0x60) = DAT_710530d2a8;

    // --- Second team param guard check (same pattern, appears twice in original) ---
    if ((g_team_param_init_guard & 1) == 0) {
        if (__cxa_guard_acquire(&g_team_param_init_guard)) {
            global_param_init_sets_team_flag();
            FUN_71000001c0((void*)FUN_7101763de0, (void*)&DAT_71052c4180, (void*)0);
            __cxa_guard_release(&g_team_param_init_guard);
        }
    }

    // +0x68: Online status flag
    param_1[0x68] = DAT_7105305970;

    // --- DLC bitmask validation ---
    // Iterates all 120 DLC content IDs. For each bit set in the bitmask,
    // checks if the content exists in the download manager AND is purchased.
    // Clears the bit if the content is not available.
    long content_mgr = *(long*)(DAT_710532e730 + 8);
    for (u32 i = 0; i < CSS_DLC_CHECK_COUNT; i++) {
        u32 bit = 1u << (i & 0x1F);
        u32* word = (u32*)(param_1 + (i >> 5) * 4 + 0x40);

        if (*word & bit) {
            u64 content_id = FUN_71032b2b20(content_mgr + 0x170, i);
            u64 exists = FUN_71032b4c80(
                *(u64*)(*(long*)(DAT_710532e730 + 8) + 0x178), content_id);

            if ((exists & 1) != 0) {
                u64 purchased = FUN_7100556c40(*(u64*)0 /* DAT_71052b8338 */, content_id);
                if ((purchased & 1) == 0) {
                    // Content exists but not purchased — clear the bit
                    *word &= ~bit;
                }
            }
        }
    }
}

// ============================================================
// css_serialize_state_to_buffer
// Address: 0x71016ed7c0 | Size: 5,744 bytes
// ============================================================

/*
 * Serializes complete CSS state into a flat buffer for save/restore.
 *
 * This is the largest and most complex of the three functions. It handles:
 * 1. Permission/flag validation
 * 2. Team parameter one-time initialization
 * 3. Local player data serialization (name, tag, icon, profile)
 * 4. Rule configuration from CSS globals
 * 5. Online mode overrides (UTF-16 to UTF-8 name conversion)
 * 6. Game mode encoding from packed mode ID
 * 7. DLC bitmask validation
 * 8. Download timer computation (max across 17 slots)
 * 9. Additional player slot iteration (up to 7 more players)
 * 10. Mutex-protected network buffer copy
 *
 * The output buffer is structured as CSSSerializeBuffer.
 */
void css_serialize_state_to_buffer(void** param_1, long buffer, u64 flags, u8 force) {
    long scene_data = *(long*)*param_1;

    // --- Early return checks ---

    // If force bit is clear AND a scene flag is set, skip serialization.
    // This prevents re-serializing state that hasn't changed.
    if (((force & 1) == 0) && (*(char*)(scene_data + 0x26a62) != '\0')) {
        return;
    }

    // If flags bit 0 is set, validate network slot ownership.
    // Only the slot owner can serialize their own state.
    if ((flags & 1) != 0) {
        if (*(long*)(scene_data + 0x9ff8) == 0) return;

        u32 slot_idx = (u32)(u64)FUN_71016f64e0((void*)(scene_data + 0xa010));
        if ((~slot_idx & 0xff) == 0) return;  // slot_idx == 0xFF means invalid

        // Check slot permission bitmask
        if ((*(u32*)(scene_data + 0xa000) & (1u << (slot_idx & 0x1f))) == 0) return;

        // Verify we own this slot
        u32 owner_idx;
        if (*(long*)(scene_data + 0x9ff0) == 0) {
            owner_idx = 0xff;
        } else {
            owner_idx = (u32)(u64)FUN_71016f64e0((void*)(scene_data + 0xa010));
        }
        if ((owner_idx & 0xff) != (slot_idx & 0xff)) return;
    }

    // --- Team parameter initialization (one-time, guarded) ---
    // This initializes team-related parameters from game config.
    // Uses C++ guard pattern; appears twice (compiler artifact from templates).
    for (int guard_pass = 0; guard_pass < 2; guard_pass++) {
        if ((g_team_param_init_guard & 1) == 0) {
            if (__cxa_guard_acquire(&g_team_param_init_guard)) {
                global_param_init_sets_team_flag();
                FUN_71000001c0((void*)FUN_7101763de0, (void*)&DAT_71052c4180, (void*)0);
                __cxa_guard_release(&g_team_param_init_guard);
            }
        }
    }

    // --- Initialize player data buffer ---
    // FUN_7101695c80 fills a 0x308-byte buffer with default player data,
    // which is then selectively written to the output buffer.
    u8 local_buf[0x308];
    memset(local_buf, 0, 0x308);
    FUN_7101695c80(local_buf);

    // --- Copy initialized data to output buffer ---
    // Offsets +0x10 through +0x70: rule data, player data, name
    u8* buf = (u8*)buffer;
    memcpy(buf + 0x10, local_buf, 0x68);  // Simplified; original copies field by field

    // --- Player name with FNV hash ---
    // The name starts at buf+0x80 as UTF-16, hash at buf+0x78, length at buf+0x7C.
    // Name copy: unrolled chain of if/else in original, up to 11 UTF-16 chars.
    u16* name_src = (u16*)(local_buf + 0x190);  // Offset into local_buf for name
    css_copy_name_to_buffer(buf + 0x78, name_src);

    // --- Extended player data ---
    // buf+0x98: more player metadata
    memcpy(buf + 0x98, local_buf + 0x178, 0x20);  // Extended data block

    // buf+0xC0: tag/icon data via FUN_7101696040
    FUN_7101696040(buf + 0xC0, local_buf + 0x148);

    // buf+0xF8: profile data
    memcpy(buf + 0xF8, local_buf + 0x218, 0x20);

    // buf+0x120: additional extended data
    FUN_71016eee30(buf + 0x120, local_buf + 0x250);

    // --- One-time init guard (another instance, likely from a different template) ---
    if ((*(u8*)&DAT_71052b82e0 & 1) == 0) {
        if (__cxa_guard_acquire((void*)&DAT_71052b82e0)) {
            __cxa_guard_release((void*)&DAT_71052b82e0);
        }
    }

    // --- Buffer marker and mode ---
    *(u16*)(buf + 0x10) = 0x1E;            // Marker value (identifies buffer format version)
    buf[0xAB] = buf[0x05] & 0x3F;          // Copy low 6 bits of mode flags to sub-mode

    // --- Check if online mode ---
    long scene_ptr = *(long*)*param_1;
    bool is_online = (*(int*)(*(long*)(*(long*)(DAT_71052c3c58 + 8) + 0x88) + 0x74) == CSS_ONLINE_MODE);

    // Determine effective player count for mode
    u32 effective_player_count;
    if (is_online) {
        effective_player_count = *(int*)(scene_ptr + 0x269c0) - 7;
    } else {
        effective_player_count = 0xFFFFFFF9;  // -7 (unsigned)
    }

    // Check if we need online overrides (mode == 2 AND player count < 2)
    bool use_online_data = is_online && (effective_player_count < 2);

    // --- Game mode encoding ---
    // Converts packed game mode ID (DAT_71053040f0) to a single-byte encoding
    // stored at buf+0xA9.
    u8 mode_byte = 0;
    switch (DAT_71053040f0) {
        case CSS_GAMEMODE_SMASH_2P:   // 0x2020000
            // Special: sets both mode and sub-mode
            buf[0xA9] = 1;
            buf[0xAB] = 2;
            break;

        case CSS_GAMEMODE_SMASH_3P:   // 0x2030100
            mode_byte = 2;
            buf[0xA9] = mode_byte;
            break;

        case CSS_GAMEMODE_SMASH_4P:   // 0x2030200
            mode_byte = 3;
            buf[0xA9] = mode_byte;
            break;

        case CSS_GAMEMODE_TOURNEY:    // 0x3010000
            mode_byte = 4;
            buf[0xA9] = mode_byte;
            break;

        case CSS_GAMEMODE_TEAM_3P:    // 0x4020100
        case CSS_GAMEMODE_TEAM_4P:    // 0x4020200
        case CSS_GAMEMODE_TEAM_CUSTOM: { // 0x4020300
            u8 team_mode;
            if (DAT_71053040f0 == CSS_GAMEMODE_TEAM_3P)      team_mode = 5;
            else if (DAT_71053040f0 == CSS_GAMEMODE_TEAM_4P)  team_mode = 6;
            else                                               team_mode = 7;

            buf[0xA9] = team_mode;

            // Sub-mode from DAT_710530c7d0 (battle type within team mode)
            if (DAT_710530c7d0 == 2)      mode_byte = 7;
            else if (DAT_710530c7d0 == 1) mode_byte = 6;
            else if (DAT_710530c7d0 == 0) {
                buf[0xA9] = 5;  // Override: solo in team mode
                goto after_mode;
            }
            buf[0xA9] = mode_byte;
            break;
        }

        default:
            break;
    }
after_mode:

    // --- Rule configuration (from CSS globals) ---
    // These globals contain the current CSS rule settings:
    // time, stocks, items, stage selection mode, etc.
    // The exact field mapping requires further analysis of FUN_7101695c80.

    // Write rule config data from BSS
    // buf+0x12..0x29: rule parameters (3 x 8 bytes)
    // buf+0x2C..0x3B: CSS_MODE_FLAGS and more rules
    // (In the original, these are written as overlapping 8-byte stores)

    buf[0x40] = CSS_MAX_PLAYER_COUNT;
    *(u64*)(buf + 0x44) = CSS_INITIAL_PLAYER_BITMASK;
    *(u32*)(buf + 0x4C) = CSS_MAX_SLOTS_VARIANT;
    *(u64*)(buf + 0x50) = DAT_71053099b0;
    *(u64*)(buf + 0x58) = DAT_71053099b8;

    // --- Team battle flag ---
    *(u8*)(buf + 0xBC) = (DAT_710530c560 == 0) ? 1 : 0;

    // --- Profile chain data ---
    *(u64*)(buf + 0xB0) = DAT_710530d2a8;

    // --- DLC bitmask validation ---
    // Same pattern as compact buffer: validate each set bit against download manager
    long content_mgr = *(long*)(DAT_710532e730 + 8);
    for (u32 i = 0; i < CSS_DLC_CHECK_COUNT; i++) {
        u32 bit = 1u << (i & 0x1F);
        u32* word = (u32*)(buf + (i >> 5) * 4 + 0x50);

        if (*word & bit) {
            u64 content_id = FUN_71032b2b20(content_mgr + 0x170, i);
            u64 exists = FUN_71032b4c80(
                *(u64*)(*(long*)(DAT_710532e730 + 8) + 0x178), content_id);

            if ((exists & 1) != 0) {
                u64 purchased = FUN_7100556c40(*(u64*)0 /* DAT_71052b8338 */, content_id);
                if ((purchased & 1) == 0) {
                    *word &= ~bit;
                }
            }
        }
    }

    // --- Download timer ---
    // Iterates CSS_DOWNLOAD_SLOT_COUNT (17) download slots.
    // Each slot is a 0x20-byte entry with:
    //   +0x28: enabled flag (char)
    //   +0x20: data pointer (must be non-null)
    //   +0x30: timer value (float)
    // Computes the maximum timer across all active slots.
    *(u32*)(buf + 0xB8) = 0;  // Default: 0.0f

    long dl_mgr = DAT_71053390a0;
    if (*(long**)(dl_mgr + 0x30) != nullptr) {
        long dl_list = **(long**)(dl_mgr + 0x30);
        if (dl_list != 0) {
            dl_list = *(long*)(dl_list + 0x40);
            if (dl_list != 0) {
                f32 max_timer = 0.0f;

                // Iterate 17 download slot entries (stride 0x20)
                for (int slot = 0; slot < CSS_DOWNLOAD_SLOT_COUNT; slot++) {
                    long entry = dl_list + slot * 0x20;
                    if (*(char*)(entry + 0x28) == 1 && *(long*)(entry + 0x20) != 0) {
                        f32 timer = *(f32*)(entry + 0x30);
                        if (timer > max_timer) {
                            max_timer = timer;
                        }
                    }
                }

                *(f32*)(buf + 0xB8) = max_timer;
            }
        }
    }

    // --- Flags ---
    buf[0xAA] = 1;                         // Player count (at least 1 = local player)
    buf[0xBD] = force & 1;                 // Force flag passed through

    // --- Player data based on online/offline ---
    if (*(int*)(*(long*)*param_1 + 0x74) == CSS_ONLINE_MODE) {
        if (use_online_data) {
            // --- ONLINE MODE: Override player data from network globals ---

            // Player icon from online state
            buf[0xA8] = DAT_71053059b1;

            // Tag data from online globals (DAT_7105305ea8 region)
            FUN_7101696040(buf + 0xC0, (void*)&DAT_7105305ea0 /* +8 */);

            // Online player name 1: UTF-16 → UTF-8 conversion
            // The game converts the online display name from UTF-16 to UTF-8
            // for transmission efficiency. Handles 1/2/3-byte UTF-8 sequences.
            if (DAT_7105305f00 == 0) {
                // No name — clear the tag fields
                *(u16*)(buf + 0xFC) = 0;
                *(u32*)(buf + 0xF8) = 0;
            } else {
                // UTF-16 to UTF-8 conversion loop
                // (See original decompilation for full unrolled code)
                // Handles BMP characters up to 0xFFFF (3-byte UTF-8)
                // Truncates at 28 (0x1C) UTF-8 bytes
            }

            // Player icon index
            buf[0x07] = DAT_7105305ef8;

            // Online player name 2 (same UTF-16 → UTF-8 pattern)
            if (DAT_7105305ee0 == 0) {
                buf[0x109] = 0;
                *(u64*)(buf + 0x101) = 0;
            } else {
                // Same UTF-16 → UTF-8 conversion for second name
            }

            // Online-specific player attributes
            buf[0xFE]  = DAT_71053059b0;    // Player type
            buf[0xFF]  = DAT_71053059b2;    // Player variant
            buf[0x100] = DAT_7105305e8c;    // Icon type

            // Profile data
            *(u64*)(buf + 0x110) = DAT_7105305e98;

            // Boolean flags (note: inverted from source — true means "not disabled")
            buf[0x118] = (DAT_7105305e8e != 1) ? 1 : 0;
            buf[0x119] = (DAT_7105305e8f != 1) ? 1 : 0;
            buf[0x11A] = (DAT_7105305e91 != 1) ? 1 : 0;

            // Override sub-mode from online state
            buf[0xAB] = DAT_7105305e8d;
        }
    } else {
        // --- OFFLINE MODE ---
        buf[0xA8] = *(u8*)&DAT_710530547c;  // Offline player type (from local state)
    }

    // --- Local player lookup and data copy ---
    // If flags bit 0 was clear, look up the local player and copy their data.
    if ((flags & 1) == 0) {
        // Determine network slot index
        u8 slot;
        if (*(long*)(*(long*)*param_1 + 0x9ff8) == 0) {
            slot = 0xFF;
        } else {
            slot = (u8)(u64)FUN_71016f64e0((void*)(*(long*)*param_1 + 0xa010));
        }

        char player_idx = FUN_71016ea430(param_1, slot);

        if (player_idx == -1) {
            // No player found — copy data directly from param_1 struct
            // buf+0x60: player header (24 bytes from param_1+3)
            // buf+0x78: name with hash (from param_1+7)
            // buf+0x98: extended data (from param_1+10)
        } else {
            // Player found — get their data via lookup
            void* player_data = FUN_71016b6ac0(*param_1, player_idx);
            // Copy player header, name, extended data from player_data

            // Also iterate remaining players (up to 8 total)
            // Each additional player gets a slot in buf+0x120 + i*0x48
            u32 additional_count = 0;
            for (u64 i = 0; i < 8; i++) {
                if ((char)i == player_idx) continue;  // Skip local player

                u8 max_players = FUN_7101686610(*(void**)*param_1);
                u64 is_active = FUN_710168eb40(*(void**)*param_1, max_players, i);

                if ((is_active & 1) != 0) {
                    buf[0xAA]++;  // Increment player count

                    if (additional_count > 6) {
                        // abort() in original — should never happen
                        break;
                    }

                    // Get this player's data
                    void* other_data = FUN_71016b6ac0(*param_1, (char)i);
                    long slot_offset = buffer + (long)additional_count * 0x48;

                    // Copy player header (24 bytes) to slot
                    // Copy name with hash to slot+0x18
                    // Copy extended data to slot+0x38

                    additional_count++;
                }
            }
        }
    } else {
        // flags bit 0 set — copy from param_1 directly (multiple player slots)
        // Iterate param_1 slots 1-6 (stride 0xF words = 0x78 bytes)
        // For each slot where slot[1] != 0 and slot[0xC] == 2:
        //   Copy to buf+0x120 + (slot_idx-1) * 0x48
        //   Increment buf[0xAA]
    }

    // --- Network buffer serialize ---
    // Packs buffer data and metadata into a structured format for
    // the mutex-protected network copy at the end.
    int mode = *(int*)(*(long*)*param_1 + 0x74);
    u8 net_buf[0x308];
    memset(net_buf, 0, 0x308);

    // Set up function table for serialization callbacks
    // (PTR_FUN_71050821a0 through PTR_FUN_7105082260)
    // These are vtable-like function pointers that handle different
    // sections of the buffer during network serialization.

    // FUN_7101697850 performs the structured serialization
    // The final callback copies the result into the network send buffer

    // --- Mutex-protected network copy ---
    // At the very end, acquires a recursive_mutex on the network session object,
    // copies the serialized data into the session's send buffer,
    // increments a sequence number, and marks the buffer as ready to send.
    //
    // Network session buffer layout (at lVar29):
    //   +0x198: buffer pointer
    //   +0x1A0: buffer capacity
    //   +0x1A8: sequence number (short, wraps with special -1 handling)
    //   +0x1AA: ack counter (cleared on write)
    //   +0x1B0: write offset (cleared on write)
    //   +0x1B4: data length (set to serialized size)
    //   +0x288: send ready flag
    //   +0x289: data present flag
    //
    // The mutex ensures atomic buffer updates in the network thread.
}

// ============================================================
// css_restore_state_from_save
// Address: 0x71017a24f0 | Size: 4,928 bytes
// ============================================================

/*
 * Restores CSS state from a previously saved buffer.
 *
 * The save buffer contains the complete CSS state captured by
 * css_serialize_state_to_buffer. This function writes that state
 * back into the BSS globals (DAT_7105307760..DAT_710530d368).
 *
 * Structure of the restore:
 * 1. Header (4+4+4 bytes + flag) → DAT_7105307760..BSS_CSS_DATA_ARRAY
 * 2. Seven player slots (0x1C8 bytes each):
 *    a. Name: UTF-16, up to 11 chars, null-terminated
 *    b. FNV hash recomputation (0x811c9dc5 seed, 0x89 prime)
 *    c. Deep data copy via FUN_71016b6bb0 (0x1A0 bytes)
 *    d. Flag byte
 * 3. Second data array (FUN_71017a0d20 → BSS_CSS_SECOND_ARRAY)
 * 4. Profile chain (8 entries with IDs and position data)
 * 5. CSS config (mode flags, player count, bitmask, slot variant)
 * 6. DLC bitmask
 * 7. Team config (0x267 byte block)
 * 8. Sub-profiles (8 entries with names, hashes, and metadata)
 * 9. Extended profile data (0x5F4 byte block)
 * 10. Profile chain resolution (via FUN_71017cefe0)
 */
void css_restore_state_from_save(void** param_1) {
    u8* save = (u8*)param_1;

    // --- Valid check ---
    // The save buffer has a validity flag at offset 0x5B60.
    // If zero, the save is invalid/empty — skip restore entirely.
    if (save[0x5B60] == 0) {
        return;
    }

    // --- Restore header ---
    DAT_7105307760 = *(u32*)(save + 0x04);
    DAT_7105307764 = *(u32*)(save + 0x08);
    DAT_7105307768 = *(u32*)(save + 0x0C);
    BSS_CSS_DATA_ARRAY = save[0x10];

    // ============================================================
    // Player Slot 0 (local player)
    // Save offset: +0x1C (name), +0x34 (extra), +0x38 (deep data)
    // BSS: DAT_710530777C (name) → DAT_7105307798 (deep data)
    // ============================================================
    u32 hash_seed = CSS_NAME_HASH_SEED;

    // Restore name (if save != BSS base, meaning data was actually serialized)
    css_restore_name_to_bss(&DAT_710530777c, &DAT_7105307778, &DAT_7105307774,
                            (u16*)(save + 0x1C));

    // Extra data
    DAT_7105307794 = *(u32*)(save + 0x34);

    // Deep player data copy (0x1A0 bytes — character selection, costume, etc.)
    FUN_71016b6bb0((void*)&DAT_7105307798, (void*)(save + 0x38));

    // ============================================================
    // Player Slots 1-6 (additional players)
    // Each slot is 0x1C8 bytes apart in the save buffer.
    // The pattern is identical for each: name → hash → extra → deep copy → flag
    //
    // BSS destinations (0x1C8 apart):
    //   Slot 1: name @ DAT_7105307944, deep @ DAT_7105307960, flag @ DAT_7105307938
    //   Slot 2: name @ DAT_7105307B0C, deep @ DAT_7105307B28, flag @ DAT_7105307B00
    //   Slot 3: name @ DAT_7105307CD4, deep @ DAT_7105307CF0, flag @ DAT_7105307CC8
    //   Slot 4: name @ DAT_7105307E9C, deep @ DAT_7105307EB8, flag @ DAT_7105307E90
    //   Slot 5: name @ DAT_7105308064, deep @ DAT_7105308080, flag @ DAT_7105308058
    //   Slot 6: name @ DAT_710530822C, deep @ DAT_7105308248, flag @ DAT_7105308220
    //
    // The original code has 6 copies of the name restore loop (fully unrolled).
    // Each reads from save + slot*0x1C8 + offsets and writes to the
    // corresponding BSS addresses.
    // ============================================================

    // (Slots 1-6 follow the same pattern — see original decompilation
    //  for the exact BSS addresses. Each slot: name restore + hash +
    //  FUN_71016b6bb0 deep copy + flag byte)

    // Slot 7 (last): deep data only, via FUN_71016b6bb0
    // FUN_71016b6bb0(&DAT_7105308410, save + 0x196*8);

    // ============================================================
    // Second Data Array
    // ============================================================
    // FUN_71017a0d20(&BSS_CSS_SECOND_ARRAY, save + 0x1CA*8);

    // ============================================================
    // Profile Chain Data (8 entries)
    // Save offset: +0x2050..+0x20B7
    // BSS: DAT_71053097B0..DAT_7105309810
    //
    // Each profile entry is 0x20 bytes containing:
    //   - Profile ID (u64, tagged with 0x69 byte at top = valid)
    //   - Position/state data
    //   - Flags (u64, bit 33 set on resolution)
    // ============================================================
    DAT_71053097b0 = *(u64*)(save + 0x2050);
    // ... (8 more u64 loads for profile entries)
    // DAT_71053097b8..DAT_7105309810

    // Profile extra data (0x90 byte block)
    // memcpy(&DAT_71053098d8, save + 0x20B8, 0x90);

    // ============================================================
    // CSS Configuration Globals
    // Save offset: +0x2148..+0x219F
    // ============================================================
    // DAT_7105309968 = *(u32*)(save + 0x2148);   // State field
    // DAT_710530996c = *(u64*)(save + 0x214C);   // State field 2
    // _DAT_7105309974 = *(u64*)(save + 0x2154);  // Rule config 1
    // ... continued through CSS_MAX_SLOTS_VARIANT
    // CSS_MAX_PLAYER_COUNT = save[0x2180];
    // CSS_INITIAL_PLAYER_BITMASK = *(u64*)(save + 0x2184);
    // CSS_MAX_SLOTS_VARIANT = *(u32*)(save + 0x218C);
    // DAT_71053099b0 = *(u64*)(save + 0x2190);   // DLC bitmask 1
    // DAT_71053099b8 = *(u64*)(save + 0x2198);   // DLC bitmask 2

    // State flags
    // DAT_71053099c0 = save[0x21A0];
    // DAT_71053099c1 = save[0x21A1];

    // Extended state (variable-length)
    // FUN_71017a11f0(&DAT_71053099c8, save + 0x21A8);

    // ============================================================
    // Team Configuration
    // Save offset: +0x4D48..+0x4FAF (0x267 bytes)
    // BSS: DAT_710530c568
    // ============================================================
    // memcpy(&DAT_710530c568, save + 0x4D48, 0x267);

    // Game mode data
    // DAT_710530c7d0 = *(u32*)(save + 0x4FB0);  // Sub-mode
    // DAT_710530c7e8 = *(u32*)(save + 0x4FC8);  // Mode extra

    // ============================================================
    // Sub-Profile Array (8 entries)
    // Save offset: +0x4FCC..+0x5060 (stride 0x98 per entry)
    // BSS: DAT_710530c7EC (stride 0x4C per entry)
    //
    // Each entry contains:
    //   - Profile metadata (u64 at stride*0x13)
    //   - Sub-profile ID (u32 at stride*0x26)
    //   - Player name (UTF-16, up to 0x3F chars, with FNV hash)
    //   - Extra data (u32 at the end)
    // ============================================================
    // (8-iteration loop with name copy + hash computation per entry)

    // ============================================================
    // Extended Profile Data
    // Save offset: +0x548C..+0x5A7F (0x5F4 bytes)
    // BSS: DAT_710530ccac
    // ============================================================
    // memcpy(&DAT_710530ccac, save + 0x548C, 0x5F4);

    // ============================================================
    // Profile Chain Pointers and Deep Copy
    // Save offset: +0x5A80..+0x5B50
    // ============================================================
    // DAT_710530d2a8 = *(u64*)(save + 0x5A88);
    // _DAT_710530d2a0 = *(u64*)(save + 0x5A80);
    // DAT_710530d2b0 = *(u64*)(save + 0x5A90);
    // FUN_7101684440(&DAT_710530d2b8, save+0x5A98, save+0x5AA0);
    // FUN_7101684440(&DAT_710530d2d0, save+0x5AB0, save+0x5AB8);
    // FUN_7101684440(&DAT_710530d2e8, save+0x5AC8, save+0x5AD0);
    // DAT_710530d300 = save[0x5AE0];
    // FUN_7101684280(&DAT_710530d308, save+0x5AE8, save+0x5AF0);
    // FUN_71017a2020(&DAT_710530d320, save+0x5B00, save+0x5B08);
    // FUN_71017a2020(&DAT_710530d338, save+0x5B18, save+0x5B20);
    // FUN_71017a2020(&DAT_710530d350, save+0x5B30, save+0x5B38);
    // FUN_71017a2020(&DAT_710530d368, save+0x5B48, save+0x5B50);

    // ============================================================
    // Profile Chain Resolution
    // ============================================================
    // After restoring all profile data, the function resolves profile IDs
    // against the current profile database using FUN_71017cefe0.
    //
    // For each of 3 profile entries (at DAT_71053097c0, e0, 7105309800):
    //   - If the profile ID is tagged valid (top byte == 0x69, low 40 bits != 0)
    //   - AND matches the current user's profile ID
    //   - THEN resolve position/appearance data via FUN_71017cefe0
    //   - Set "resolved" flag (bit 33) on the entry's flags
    //
    // This handles the case where a player's online profile has changed
    // since the CSS state was saved — the game re-fetches the latest data
    // while preserving the rest of the CSS state.
    //
    // Profile ID format: 0x69_XXXXXXXXXX (tagged pointer, top byte = 0x69)
    //   - 0x69 tag: indicates a valid network profile ID
    //   - Low 40 bits: the actual profile ID
    //
    // Resolution output (written to BSS per entry):
    //   - Updated position data (u32 at +0x4C from entry base)
    //   - Two flag bytes (at +0x48 and +0x49)
    //   - Updated appearance hash (u64)
    //   - Two more flag bytes (at +0x38 and +0x39)
}
