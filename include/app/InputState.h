#pragma once

#include <stdint.h>

// =============================================================================
// SSBU Input System Structures
//
// These structures define the input pipeline from hardware polling through
// final mapped game input. The pipeline is:
//   nn::hid::GetNpadState -> input_poll_all_players -> final_input_mapping
//                         -> mapped input (8 bytes per player)
//
// For rollback/netplay, the override mechanism at offsets 0x540-0x578 allows
// network-received inputs to replace locally-computed ones after each frame.
// =============================================================================

// -- Mapped Input Button Flags ------------------------------------------------
// The output of final_input_mapping is a 32-bit bitfield. These flags represent
// game-level actions, NOT physical buttons. The mapping table determines which
// physical button maps to which game action.

#define BTN_ATTACK          (1 << 0)    // 0x00001 - Attack
#define BTN_SPECIAL         (1 << 1)    // 0x00002 - Special
// Bit 2 unused
#define BTN_JUMP_MACRO_A    (1 << 3)    // 0x00008 - Jump component of Jump+Attack macro
#define BTN_JUMP_MACRO_B    (1 << 4)    // 0x00010 - Jump component of Jump+Attack macro
#define BTN_GRAB            (1 << 5)    // 0x00020 - Grab (attack+special simultaneous)
#define BTN_JUMP_MINI       (1 << 6)    // 0x00040 - Short hop (two jump buttons pressed)
#define BTN_CSTICK_ON       (1 << 7)    // 0x00080 - C-stick is active
#define BTN_SHIELD_L        (1 << 8)    // 0x00100 - Shield (from shoulder button check)
#define BTN_ATTACK_MIRROR   (1 << 9)    // 0x00200 - Mirrors BTN_ATTACK
// Bit 10 unused
#define BTN_SPECIAL_MIRROR  (1 << 11)   // 0x00800 - Mirrors BTN_SPECIAL
// Bit 12 unused
#define BTN_TAUNT_UP        (1 << 13)   // 0x02000 - Taunt up (D-pad context)
#define BTN_TAUNT_DOWN      (1 << 14)   // 0x04000 - Taunt down (D-pad context)
#define BTN_APPEAL          (1 << 15)   // 0x08000 - Appeal / taunt button held
#define BTN_SHIELD_DOUBLE   (1 << 16)   // 0x10000 - Two shield buttons pressed
#define BTN_SMASH_ATTACK    (1 << 17)   // 0x20000 - Smash attack (from Jump+Attack macro)

// Combined masks for mirror bits
#define BTN_ATTACK_BOTH     (BTN_ATTACK | BTN_ATTACK_MIRROR)    // 0x00201
#define BTN_SPECIAL_BOTH    (BTN_SPECIAL | BTN_SPECIAL_MIRROR)  // 0x00802
#define BTN_JUMP_MACRO      (BTN_JUMP_MACRO_A | BTN_JUMP_MACRO_B) // 0x00018

// -- Button Mapping Byte Values -----------------------------------------------
// Each byte in the per-player mapping table maps a physical button to a game action.

#define MAP_ATTACK          0   // Maps to BTN_ATTACK (bit 0)
#define MAP_SPECIAL         1   // Maps to BTN_SPECIAL (bit 1)
#define MAP_JUMP            2   // Maps to jump (counted — 2+ triggers short hop)
#define MAP_SHIELD          3   // Maps to shield (counted — 2+ triggers double shield)
#define MAP_JUMP_ATTACK     4   // Maps to BTN_JUMP_MACRO_A | BTN_JUMP_MACRO_B (0x18)
#define MAP_UNBOUND         13  // 0x0D — button is not mapped, ignored

// -- Controller Style Types ---------------------------------------------------
// From NpadState+0x9C. Determines which section of the mapping table to use.

#define CTRL_STYLE_DPAD_ONLY      1  // NES controller / D-pad only
#define CTRL_STYLE_LEFT_JOYCON    2  // Left-side Joy-Con
#define CTRL_STYLE_RIGHT_JOYCON   3  // Right-side Joy-Con (axes inverted)
#define CTRL_STYLE_DUAL_JOYCON    4  // Dual Joy-Con
#define CTRL_STYLE_STANDARD_5     5  // Standard variant
#define CTRL_STYLE_STANDARD_6     6  // Standard variant
#define CTRL_STYLE_PRO            7  // Pro Controller / full controller

// -- Max Players --------------------------------------------------------------
#define INPUT_MAX_PLAYERS   8
#define INPUT_MAX_CONTROLLERS 10

// =============================================================================
// Structures
// =============================================================================

// 8 bytes — the atomic unit of input state per player per frame.
// This is what gets transmitted over the network and saved for rollback.
struct MappedInput {
    uint32_t buttons;       // +0x00: Button bitfield (see BTN_* flags)
    int8_t   stick_x;       // +0x04: Main stick X (-127..127)
    int8_t   stick_y;       // +0x05: Main stick Y (-127..127)
    int8_t   cstick_x;      // +0x06: C-stick X (set by fim_cstick_handler)
    int8_t   cstick_y;      // +0x07: C-stick Y (set by fim_cstick_handler)
};
static_assert(sizeof(MappedInput) == 8, "MappedInput must be exactly 8 bytes");

// Raw controller state from nn::hid. The full NpadState is larger, but these
// are the fields accessed by the input mapping code.
struct NpadStateMinimal {
    uint8_t  pad0[0x08];
    uint32_t raw_buttons;   // +0x08: Hardware button bitfield
    uint8_t  pad1[0x04];
    float    stick_data[4]; // +0x10: Two analog sticks (x0, y0, x1, y1)
    uint8_t  pad2[0x78];
    int32_t  style_type;    // +0x9C: Controller style (see CTRL_STYLE_*)
};

// Controller struct wrapper — the game wraps the NpadState behind a pointer.
struct ControllerStruct {
    uint8_t  pad0[0x10];
    NpadStateMinimal* npad_state;  // +0x10: Pointer to actual NpadState data
};

// Per-player mapping table (0x50 bytes per player).
// Contains button mappings for all controller style variants plus config data.
struct PerPlayerMapping {
    // Pro Controller / type 7 button mappings (offsets 0x00-0x0B)
    uint8_t pro_button[12];     // +0x00: 12 button mapping slots for Pro Controller
    uint8_t pro_ab_grab;        // +0x0C: Grab macro config (A+B simultaneous)
    uint8_t pro_appeal;         // +0x0D: Appeal button enable
    uint8_t pro_cstick_mode;    // +0x0E: C-stick control scheme for Pro Controller

    // Standard / types 1-6 button mappings (offsets 0x0F-0x1B)
    uint8_t std_button[12];     // +0x0F: 12 button mapping slots for standard types
    uint8_t std_reserved;       // +0x1B: (unused)
    uint8_t std_ab_grab;        // +0x1C: Grab macro config
    uint8_t std_appeal;         // +0x1D: Appeal button enable
    uint8_t std_cstick_mode;    // +0x1E: C-stick control scheme for standard

    // D-pad / types 3-4 button mappings (offsets 0x1F-0x2A)
    uint8_t dpad_button[8];     // +0x1F: D-pad direction button slots
    uint8_t dpad_ab_grab;       // +0x27: (unused / reserved)
    uint8_t dpad_appeal;        // +0x28: Grab macro config for D-pad
    uint8_t dpad_appeal2;       // +0x29: Appeal config for D-pad
    uint8_t dpad_reserved;      // +0x2A: (unused)

    // C-stick config (offsets 0x2B-0x32) — passed to fim_cstick_handler
    uint8_t cstick_config[8];   // +0x2B: C-stick state/config bytes
                                //   [0]: tracking byte 0 (history)
                                //   [1]: tracking byte 1 (history)
                                //   [3]: smash charge delay counter
                                //   [4-5]: cached smash direction (x, y)
                                //   [9]: frame delay countdown
                                //   [10]: tilt latch flag

    // Shared state
    uint8_t grab_macro_state;   // +0x33: Tracks attack+special simultaneous hold
    uint8_t pad[0x1C];          // +0x34: Padding to 0x50

    // Total: 0x50 bytes per player
};
static_assert(sizeof(PerPlayerMapping) == 0x50, "PerPlayerMapping must be 0x50 bytes");

// The main input polling structure. One instance exists at the scene level.
// FUN_71017547f0 operates on this struct each frame.
struct InputPollStruct {
    uint8_t           pad0[0x18];
    PerPlayerMapping  mappings[INPUT_MAX_PLAYERS];       // +0x018: Per-player button mapping tables
    uint8_t           pad1[0x18];                        // +0x298 - 0x280 = 0x18 pad? No...
    // Actually layout computed from offsets:
    // mappings at +0x18 = 0x50 * 8 = 0x280 bytes → ends at +0x298
    uint32_t          controller_ids[INPUT_MAX_PLAYERS]; // +0x298: Controller ID per player slot (0-9)
    MappedInput       mapped_inputs[INPUT_MAX_PLAYERS];  // +0x2B8: Output: mapped input per player
    uint8_t           pad2[0x240];                       // +0x2F8: gap to 0x538
    uint8_t           disconnect_counter[INPUT_MAX_PLAYERS]; // +0x538: Per-player disconnect frame counter
    MappedInput       override_inputs[INPUT_MAX_PLAYERS];    // +0x540: Network override input data
    uint8_t           override_enable[INPUT_MAX_PLAYERS];    // +0x580: Per-player override enable flags
    uint8_t           pad3[0x38];                            // +0x588: gap to 0x5C0
    uint8_t           player0_special_flag;                  // +0x5C0: Affects final_input_mapping arg5 for player 0
};

// Key offsets (from Ghidra, padding may need adjustment for matching):
// mappings at +0x18, controller_ids at +0x298, mapped_inputs at +0x2B8
// disconnect_counter at +0x538, override_inputs at +0x540
// override_enable at +0x580, player0_special_flag at +0x5C0

// =============================================================================
// External globals
// =============================================================================

// Global controller array — indexed by controller_id (0-9).
// Each entry is a pointer to a ControllerStruct.
// DAT_7105338860 in Ghidra.
extern ControllerStruct* g_controller_array[INPUT_MAX_CONTROLLERS]; // @ 0x7105338860

// Default controller struct — used when the controller subsystem reports
// no specific controller is connected for a slot.
// DAT_7105338830 in Ghidra.
extern ControllerStruct g_default_controller;   // @ 0x7105338830

// Controller subsystem active flag — at DAT_71053388b0+8.
// When this is '\0' (active), use g_default_controller.
// When non-zero (subsystem initialized), look up g_controller_array.
extern char g_controller_subsystem_flag;         // @ 0x71053388b8

// =============================================================================
// Function declarations
// =============================================================================

// Per-frame input polling loop. Iterates all 8 player slots, maps raw controller
// input to game input, then applies network override slots.
// Address: 0x71017547f0
bool input_poll_all_players(InputPollStruct* input);

// Core button mapping function. Reads raw hardware buttons from the controller
// and writes an 8-byte MappedInput using the per-player mapping table.
// Address: 0x7101750f70
void final_input_mapping(PerPlayerMapping* mappings, int player_idx,
                         MappedInput* out, ControllerStruct* controller, bool arg);

// C-stick post-processing. Handles tilt stick, smash stick, and special modes.
// Address: 0x7101752a10
void fim_cstick_handler(MappedInput* out, NpadStateMinimal* npad,
                        uint8_t cstick_mode, uint32_t param_unused,
                        uint8_t* cstick_config, int* shield_count, int* jump_count);

// Stick normalization. Applies deadzone and scaling from param data to convert
// raw float stick values to the -1.0..1.0 range.
// Address: 0x7101752390
void normalize_stick(float* out_xy, float* raw_stick_xy, int style_type);
