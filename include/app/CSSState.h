#pragma once

#include "types.h"

/*
 * CSS (Character Select Screen) State Serialization Structures
 *
 * The game has a complete CSS state save/restore system used for:
 * - Persisting CSS state across screen transitions
 * - Sending CSS configuration over the network (compact buffer)
 * - Restoring CSS state on re-entry
 *
 * Three functions operate on these structures:
 *   css_serialize_state_to_buffer  @ 0x71016ed7c0 (5,744 bytes)
 *   css_restore_state_from_save    @ 0x71017a24f0 (4,928 bytes)
 *   css_read_state_to_compact_buffer @ 0x71016e2df0 (560 bytes)
 *
 * BSS state region: DAT_7105307760 through DAT_710530d368 (~11KB)
 *
 * Key globals referenced:
 *   g_team_param_init_guard  - Guards one-time team parameter initialization
 *   CSS_MODE_FLAGS           - Current CSS mode flags
 *   CSS_MAX_PLAYER_COUNT     - Max players for current mode
 *   CSS_INITIAL_PLAYER_BITMASK - Initial player slot bitmask
 *   CSS_MAX_SLOTS_VARIANT    - Slot variant for current mode
 *   DAT_71053040f0           - Encoded game mode ID (packed u32)
 *   DAT_710530c7d0           - Sub-mode / battle type
 */

// ============================================================
// Constants
// ============================================================

#define CSS_MAX_NAME_CHARS        11    // Max UTF-16 characters in a player name
#define CSS_MAX_PLAYER_SLOTS       8    // Total player slots
#define CSS_ADDITIONAL_SLOTS       7    // Additional player slots beyond local player
#define CSS_DLC_CHECK_COUNT      120    // Number of DLC content IDs to validate (0x78)
#define CSS_DOWNLOAD_SLOT_COUNT   17    // Download timer entries (stride 0x20)
#define CSS_PLAYER_DATA_SIZE    0x1A0   // Bytes per player deep-copy (FUN_71016b6bb0)
#define CSS_PROFILE_SUB_COUNT      8    // Sub-profile entries in restore

// FNV-style hash used for player name integrity
#define CSS_NAME_HASH_SEED    0x811c9dc5u
#define CSS_NAME_HASH_PRIME   0x89u   // Custom prime (not standard FNV-1a 0x01000193)

// Encoded game mode IDs (stored in DAT_71053040f0)
#define CSS_GAMEMODE_SMASH_2P     0x2020000u
#define CSS_GAMEMODE_SMASH_3P     0x2030100u
#define CSS_GAMEMODE_SMASH_4P     0x2030200u
#define CSS_GAMEMODE_TOURNEY      0x3010000u
#define CSS_GAMEMODE_TEAM_3P      0x4020100u
#define CSS_GAMEMODE_TEAM_4P      0x4020200u
#define CSS_GAMEMODE_TEAM_CUSTOM  0x4020300u

// Online mode constant (checked in serialize for online-specific player data)
#define CSS_ONLINE_MODE           2

// ============================================================
// Player Name
// ============================================================

/*
 * CSSPlayerName: UTF-16 null-terminated player name with integrity hash.
 *
 * The name is stored as up to CSS_MAX_NAME_CHARS UTF-16 code units,
 * followed by a null terminator. The hash is computed as:
 *   hash = CSS_NAME_HASH_SEED
 *   for each non-zero char c in name[]:
 *     hash = (hash * CSS_NAME_HASH_PRIME) ^ c
 *
 * This appears throughout the CSS state for both the local player
 * and additional player slots.
 */
struct CSSPlayerName {
    u32 hash;                              // +0x00: FNV-style hash of name
    u32 length;                            // +0x04: Number of UTF-16 chars (excluding null)
    u16 chars[CSS_MAX_NAME_CHARS + 1];     // +0x08: UTF-16 name + null terminator (24 bytes)
};
// sizeof = 0x20 (32 bytes)

// ============================================================
// Serialize Buffer (output of css_serialize_state_to_buffer)
// ============================================================

/*
 * CSSAdditionalPlayerSlot: Per-player data for players 2-8 in the
 * serialize buffer. Each slot is 0x48 bytes.
 *
 * In the serialize buffer, these start at offset +0x120.
 * Up to CSS_ADDITIONAL_SLOTS (7) entries, one per additional player.
 */
struct CSSAdditionalPlayerSlot {
    u8  player_data[0x18];                 // +0x00: Player slot header data
    CSSPlayerName name;                    // +0x18: Player name with hash
    u8  extended_data[0x10];               // +0x38: Extended player data (profile/icon)
};
// sizeof = 0x48 (72 bytes)

/*
 * CSSSerializeBuffer: Full CSS state buffer written by
 * css_serialize_state_to_buffer.
 *
 * This is a flat buffer that captures the complete CSS state:
 * - Local player data (name, tag, icon, profile)
 * - Game mode and rule configuration
 * - DLC/download content bitmask
 * - Team configuration
 * - Additional player slots (up to 7)
 * - Online-specific overrides (when mode == CSS_ONLINE_MODE)
 * - Mutex-protected network copy at the end
 *
 * The buffer is written to param_2 in css_serialize_state_to_buffer
 * and read back by css_restore_state_from_save.
 */
struct CSSSerializeBuffer {
    // --- Header (0x00 - 0x0F) ---
    u8  header[5];                         // +0x00: Buffer header / version
    u8  mode_flags_low;                    // +0x05: Low 6 bits = CSS mode flags
    u8  _pad06;                            // +0x06
    u8  online_icon_index;                 // +0x07: Online player icon (set when mode==2)
    u8  _pad08[8];                         // +0x08

    // --- Rule Configuration (0x10 - 0x4F) ---
    u16 marker;                            // +0x10: Always set to 0x1E after init
    u8  rule_config[0x1A];                 // +0x12: Rule parameters (from DAT_7105309974..)
    //   +0x12..0x19: rule_config_1 (8 bytes from DAT_7105309974)
    //   +0x1A..0x21: rule_config_2 (8 bytes, continued)
    //   +0x22..0x29: rule_config_3 (8 bytes, continued)
    u8  mode_flags_full[0x0A];             // +0x2C: CSS_MODE_FLAGS (8 bytes) + extra
    //   +0x2C..0x33: CSS_MODE_FLAGS
    //   +0x34..0x3B: rule_config_4
    u8  rule_flag;                         // +0x3C: Flag byte
    u8  _pad3D[3];                         // +0x3D
    u8  max_player_count;                  // +0x40: CSS_MAX_PLAYER_COUNT
    u8  _pad41[3];                         // +0x41
    u64 initial_player_bitmask;            // +0x44: CSS_INITIAL_PLAYER_BITMASK
    u32 max_slots_variant;                 // +0x4C: CSS_MAX_SLOTS_VARIANT

    // --- DLC Content Bitmask (0x50 - 0x5F) ---
    u64 dlc_bitmask_1;                     // +0x50: First 64 DLC content bits
    u64 dlc_bitmask_2;                     // +0x58: Next 56 DLC content bits (120 total)

    // --- Local Player Slot (0x60 - 0x11F) ---
    u8  local_player_data[0x18];           // +0x60: Local player header (from param_1 or player lookup)
    CSSPlayerName local_player_name;       // +0x78: Local player name with hash
    u8  local_extended_data[0x20];         // +0x98: Extended player data
    u8  local_tag_data[0x38];              // +0xB8: Tag/icon data (via FUN_7101696040, 56 bytes)
                                           //        at +0xC0 in the raw buffer
    // ... overlapping field annotations:
    //   +0xA8: player_type (u8) - offline: from DAT_710530547c, online: from DAT_71053059b1
    //   +0xA9: game_mode_encoded (u8) - encoded from DAT_71053040f0
    //   +0xAA: additional_player_count (u8) - incremented per additional player found
    //   +0xAB: sub_mode (u8) - from DAT_710530c7d0 or online override
    //   +0xB0: profile_chain_data (u64)
    //   +0xB8: max_download_timer (f32) - max of CSS_DOWNLOAD_SLOT_COUNT entries
    //   +0xBC: is_team_battle (bool) - true if DAT_710530c560 == 0
    //   +0xBD: force_flag (u8) - bit 0 of param_4

    // Online-specific overrides (when mode == CSS_ONLINE_MODE):
    //   +0xC0: online tag data (copied from DAT_7105305ea8)
    //   +0xF8: online player tag (UTF-8, converted from UTF-16 at DAT_7105305f06)
    //   +0xFE: online_player_type (from DAT_71053059b0)
    //   +0xFF: online_player_variant (from DAT_71053059b2)
    //   +0x100: online_icon_type (from DAT_7105305e8c)
    //   +0x101..0x109: online_name_utf8 (from DAT_7105305ee6, UTF-16 to UTF-8)
    //   +0x110: online_profile (8 bytes from DAT_7105305e98)
    //   +0x118: online_flag_1 (bool, inverted from DAT_7105305e8e)
    //   +0x119: online_flag_2 (bool, inverted from DAT_7105305e8f)
    //   +0x11A: online_flag_3 (bool, inverted from DAT_7105305e91)

    u8  local_profile_data[0x28];          // +0xF0 (approx): Profile/icon data block

    // --- Additional Player Slots (0x120+) ---
    CSSAdditionalPlayerSlot additional_players[CSS_ADDITIONAL_SLOTS];
                                           // +0x120: Up to 7 additional player slots
};

// ============================================================
// Save Buffer (input to css_restore_state_from_save)
// ============================================================

/*
 * CSSPlayerSaveSlot: Per-player data in the save buffer.
 * 7 consecutive slots, each 0x1C8 bytes, starting at the base of the save.
 *
 * The restore function reads from these slots and writes to BSS globals:
 *   Slot 0 → DAT_7105307760..DAT_7105307794 (+ deep copy to DAT_7105307798)
 *   Slot 1 → DAT_7105307938..DAT_710530795C (+ deep copy to DAT_7105307960)
 *   Slot 2 → DAT_7105307B00..DAT_7105307B24 (+ deep copy to DAT_7105307B28)
 *   Slot 3 → DAT_7105307CC8..DAT_7105307CEC (+ deep copy to DAT_7105307CF0)
 *   Slot 4 → DAT_7105307E90..DAT_7105307EB4 (+ deep copy to DAT_7105307EB8)
 *   Slot 5 → DAT_7105308058..DAT_710530807C (+ deep copy to DAT_7105308080)
 *   Slot 6 → DAT_7105308220..DAT_7105308244 (+ deep copy to DAT_7105308248)
 *
 * Each slot contains:
 *   - 12 bytes of header (4+4+4)
 *   - 1 byte of flag data
 *   - Player name (UTF-16, up to 11 chars) with FNV hash
 *   - 4 bytes of extra data
 *   - 0x1A0 bytes of deep player data (copied via FUN_71016b6bb0)
 *   - 1 byte flag
 *   - Next slot's name data
 */
struct CSSPlayerSaveSlot {
    u8  data[0x1C8];                       // Full slot (456 bytes)
};

/*
 * CSSSaveBuffer: The full save buffer read by css_restore_state_from_save.
 *
 * Layout:
 *   +0x0000..0x0003: header_1 (u32) → DAT_7105307760
 *   +0x0004..0x0007: header_2 (u32) → DAT_7105307764
 *   +0x0008..0x000B: header_3 (u32) → DAT_7105307768
 *   +0x0010:         data_array_flag (u8) → BSS_CSS_DATA_ARRAY
 *   +0x001C:         Player 0 name start
 *   +0x0038:         Player 0 deep data (FUN_71016b6bb0)
 *   +0x01C8:         Player 1 start (stride 0x1C8 per slot)
 *   ...
 *   +0x0CB0:         Player 6 deep data end
 *   +0x0E50+:        Second data array (FUN_71017a0d20 → BSS_CSS_SECOND_ARRAY)
 *   +0x2050..0x20B8: Profile chain data (8 entries, each with ID + flags)
 *   +0x20B8..0x2148: Profile extra data (0x90 bytes memcpy)
 *   +0x2148:         State field (u32)
 *   +0x214C..0x2198: CSS config globals (mode flags, player count, bitmask, etc.)
 *   +0x2190..0x219F: DLC bitmask pair
 *   +0x21A0..0x21A1: State flags
 *   +0x21A8+:        Extended state (FUN_71017a11f0 → DAT_71053099c8)
 *   +0x4D48..0x4FAF: Team config block (0x267 bytes memcpy)
 *   +0x4FB0..0x4FC8: Game mode data (DAT_710530c7d0..DAT_710530c7e8)
 *   +0x4FCC..0x5060: Sub-profile array (8 entries, stride 0x98)
 *   +0x548C..0x5A7F: Extended profile data (0x5F4 bytes memcpy)
 *   +0x5A80..0x5A9F: Profile chain pointers
 *   +0x5AA0..0x5B50: Profile chain deep copy data
 *   +0x5B60:         Valid flag (must be non-zero for restore to proceed)
 */
struct CSSSaveBuffer {
    u8  data[0x5B68];                      // ~23KB total save buffer
};

// ============================================================
// Compact Buffer (output of css_read_state_to_compact_buffer)
// ============================================================

/*
 * CSSCompactBuffer: Minimal CSS state for network transmission.
 * Written by css_read_state_to_compact_buffer.
 *
 * Contains only the essential configuration (no player names or profiles),
 * making it suitable for quick network sync of CSS state.
 */
struct CSSCompactBuffer {
    u8  team_enabled;                      // +0x00: DAT_71053099c0 (team mode flag)
    u8  game_mode;                         // +0x01: DAT_710530c7d0 (battle type)
    u8  css_data_field;                    // +0x02: DAT_7105307768
    u8  _pad03;                            // +0x03
    u64 rule_config_1;                     // +0x04: From DAT_7105309974 region
    u64 rule_config_2;                     // +0x0C: Continued rule data
    u64 rule_config_3;                     // +0x14: Continued rule data
    u64 mode_flags;                        // +0x1C: CSS_MODE_FLAGS
    u64 rule_config_4;                     // +0x24: More rule data
    u8  rule_flag;                         // +0x2C: Flag from DAT_710530999b+1
    u8  _pad2D[3];                         // +0x2D
    u8  max_player_count;                  // +0x30: CSS_MAX_PLAYER_COUNT
    u8  _pad31[3];                         // +0x31
    u64 initial_player_bitmask;            // +0x34: CSS_INITIAL_PLAYER_BITMASK
    u32 max_slots_variant;                 // +0x3C: CSS_MAX_SLOTS_VARIANT
    u64 dlc_bitmask_1;                     // +0x40: DLC content bits (first 64)
    u64 dlc_bitmask_2;                     // +0x48: DLC content bits (next 56)
    u64 state_field;                       // +0x50: DAT_710530996c
    u32 team_state;                        // +0x58: DAT_710530c560
    u8  team_flag;                         // +0x5C: DAT_710530c564
    u8  _pad5D[3];                         // +0x5D
    u64 profile_data;                      // +0x60: DAT_710530d2a8
    u8  online_flag;                       // +0x68: DAT_7105305970
};
// sizeof ~ 0x69 (105 bytes)

// ============================================================
// Function Declarations
// ============================================================

/*
 * Serializes complete CSS state into a flat buffer.
 *
 * param_1: Pointer to CSS scene object (contains vtable, player data)
 * buffer:  Output buffer (CSSSerializeBuffer or raw pointer)
 * flags:   Bit 0: if set, checks network permission before serializing
 * force:   Bit 0: if clear, skips if a scene flag is set
 *
 * The function:
 * 1. Validates permissions (flag checks, network slot ownership)
 * 2. Initializes team parameters if needed (g_team_param_init_guard)
 * 3. Copies local player data (name with FNV hash, profile, tag/icon)
 * 4. Writes rule configuration from CSS globals
 * 5. If online (mode == 2): overrides player data from network globals
 * 6. Encodes game mode from DAT_71053040f0
 * 7. Validates DLC bitmask against download manager
 * 8. Computes max download timer across all download slots
 * 9. Iterates additional players (up to 7) and serializes each
 * 10. Performs mutex-protected copy into network send buffer
 */
void css_serialize_state_to_buffer(void** param_1, long buffer, u64 flags, u8 force);

/*
 * Restores CSS state from a previously saved buffer.
 *
 * param_1: Pointer to save buffer (CSSSaveBuffer)
 *
 * Writes to BSS globals DAT_7105307760 through DAT_710530d368.
 * For each of 7 player slots:
 *   - Restores player name (UTF-16) and recomputes FNV hash
 *   - Deep-copies player data via FUN_71016b6bb0 (0x1A0 bytes each)
 * Then restores:
 *   - Profile chain data (8 profile entries with ID resolution)
 *   - CSS config (mode flags, player count, bitmask, slot variant)
 *   - DLC bitmask
 *   - Team configuration (0x267 byte block)
 *   - Sub-profile array (8 entries)
 *   - Extended profile data (0x5F4 byte block)
 *   - Profile chain resolution via FUN_71017cefe0
 */
void css_restore_state_from_save(void** param_1);

/*
 * Reads CSS state into a compact buffer for network transmission.
 *
 * param_1: Output buffer (CSSCompactBuffer)
 *
 * Copies only essential CSS configuration (no player names or profiles).
 * Validates DLC bitmask against download manager (120 entries).
 * Used for quick network sync of CSS mode/rules.
 */
void css_read_state_to_compact_buffer(u8* param_1);
