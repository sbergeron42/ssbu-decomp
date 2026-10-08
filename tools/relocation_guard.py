"""Guard verified-match reporting when relocations cannot be resolved.

This is deliberately separate from binary patching: unknown relocation targets
are not evidence that the compiled bytes match the original instructions.
"""


def unresolved_offsets(relocations, patched_offsets):
    """Return relocation offsets without a successful independently computed patch."""
    return {offset for offset, *_ in relocations if offset not in patched_offsets}


def is_verified_match(matched_instructions, total_instructions, unresolved):
    """Byte-identical only if every instruction matches and every reloc resolves."""
    return total_instructions > 0 and matched_instructions == total_instructions and not unresolved
