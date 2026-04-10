# Undefined Types — Research Queue

Placeholder structs that need community research to identify proper names.
Each entry has: what we know from the binary, where it's used, and what's still unknown.

To contribute: identify the real class name, update the header, and remove the entry here.

## How to read this file

- **Placeholder name**: temporary name based on first-seen function address or usage
- **Header**: where the placeholder struct lives
- **Known fields**: offsets we've typed from binary evidence
- **Used by**: function addresses / source files that operate on this type
- **Research leads**: .dynsym symbols, vtable contents, cross-references that might identify it

---

## Active placeholders

## StageBase
- **Header**: `include/app/placeholders/StageBase.h`
- **Size**: 0x728 bytes (verified via static_assert)
- **Known fields**:
  - +0x000: `void** vtable` [derived: set in ctor/dtor, PTR_LAB_71050c44c8]
  - +0x0D0: `void* stage_ref` [derived: set to self in ctor, unregistered from StageManager in dtor]
  - +0x0D8: `u32 flags` [derived: bitmask, bit 4 checked / bit 2 set in FUN_71025d7970]
  - +0x180: `u64 buffer_begin` [derived: freed in dtor]
  - +0x1A0: `void* shared_ref` [derived: shared_ptr, atomic release in dtor]
  - +0x1A8: `void* vec_ptrs_begin` [derived: vector of ptrs, dtor iterates + frees]
  - +0x1C0: `void* vec_shared_begin` [derived: vector of shared_ptrs]
  - +0x300-0x358: 12 owned subsystem pointers [derived: dtor releases each via unique_ptr/free]
  - +0x350: `void* vec_container` [derived: iterated in FUN_71025d7970 and FUN_71025d8750]
  - +0x3D0: `void** event_listener_vt` [derived: embedded StageEventListener, PTR_FUN_71050c5ac0]
  - +0x4E0: `u32 stage_object_id` [derived: scene handle, checked/cleared in FUN_71025d7970]
  - +0x5E8: `u8 stage_active_flag` [derived: cleared in FUN_71025d7970]
  - +0x600: `u32 stage_params[0x2C]` [derived: u32 float param array, initialized in ctor]
  - +0x6B8: `void** sub_listener_vt` [derived: PTR_LAB_71050c5aa0, targets +0x3D0]
  - +0x6F4: `u32 init_color_param` [derived: init 0x876500]
  - +0x704: `u32 invalid_marker` [derived: init 0xFFFFFFFF, sentinel]
- **Used by**: `src/app/camera_functions.cpp` (4 stage destructors), `src/app/StageWufuIsland.cpp` (ctor), `src/app/StageManager.cpp` (stage queries)
- **Research leads**:
  - Constructor: FUN_71025d2dc0 (14,820 bytes, 2-param: this + init data)
  - Destructor: FUN_71025d7310 (1,560 bytes)
  - Vtable at PTR_LAB_71050c44c8 — scan entries for virtual function addresses
  - Intermediate class exists: vtable PTR_LAB_71050c4d70 adds +0x740/+0x750/+0x768 (dtor FUN_71025e55a0)
  - 13.0.1 Ghidra names this `StageBase` at 0x71025d2120 (ghidra_1301_named.csv)
- **Best guess**: `app::StageBase` or `app::stage::StageBase` (confidence: high — 13.0.1 ELF confirms name)

<!-- Template for new entries:

## UnkType_XXXXXXXX
- **Header**: `include/app/placeholders/UnkType_XXXXXXXX.h`
- **Size**: ~0xNNN bytes (estimated from largest offset + field size)
- **Known fields**:
  - +0x00: `void** vtable`
  - +0xNN: `type (description)` [derived/inferred: evidence]
- **Used by**: `src/app/file.cpp` (N functions)
- **Research leads**:
  - .dynsym: `symbol_name` references this type
  - Vtable at 0x71XXXXXXXX has N entries
  - Similar to `KnownType` (shares N fields)
- **Best guess**: `ClassName` (confidence: low/medium/high)

-->
