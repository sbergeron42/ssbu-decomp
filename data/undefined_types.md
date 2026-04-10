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

(none yet — pools will populate this as Phase 3 proceeds)

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
