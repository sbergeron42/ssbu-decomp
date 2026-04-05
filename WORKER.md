# Worker: pool-a

## Model: Opus

## Task: Add derivation chains to all struct field names in existing headers

The 18+ recovered module headers have field names but no derivation comments showing HOW each name was determined. Add them.

### What to add
For each named field in a struct header, add a derivation comment:

Instead of:
    s32 situation_kind;  // +0xD8

Write:
    s32 situation_kind;  // +0xD8 [derived: situation_kind_impl (.dynsym) reads this as s32]

Or for inferred names:
    u32 status_flags;    // +0xE0 [inferred: bitmask pattern in 12 functions, no proven name]

### Files to update
All headers in include/app/:
- include/app/modules/StatusModule.h
- include/app/modules/WorkModule.h
- include/app/modules/GroundModule.h
- include/app/modules/PostureModule.h
- include/app/modules/MotionModule.h
- include/app/modules/AttackModule.h
- include/app/modules/DamageModule.h
- include/app/modules/KineticModule.h
- include/app/modules/EffectModule.h
- include/app/modules/ControlModule.h
- include/app/modules/SoundModule.h
- include/app/modules/CameraModule.h
- include/app/modules/LinkModule.h
- include/app/modules/PhysicsModule.h
- include/app/modules/ComboModule.h
- include/app/modules/HitModule.h
- include/app/modules/ShieldModule.h
- include/app/FighterManager.h
- include/app/FighterInformation.h
- include/app/FighterEntry.h
- All other headers with named fields

### How to derive
- Vtable methods: [derived: METHOD_NAME_impl (.dynsym) dispatches through this slot]
- Data fields: use Ghidra MCP to find which .dynsym-proven function reads/writes the offset
- If no proven function references the field: [inferred: REASON]
- If truly unknown: leave as unk_0xXX

### Rules
- ONLY edit include/app/ headers (comments only, no code changes)
- Do NOT change any field types, offsets, or names
- Do NOT edit .cpp files
- This is comment-only work — zero compilation impact
