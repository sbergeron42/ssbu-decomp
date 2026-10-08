"""Smoke tests that verify the actual upstream tools use the safety helpers."""
import unittest
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]


class ToolIntegrationTests(unittest.TestCase):
    def test_unknown_relocations_do_not_copy_expected_bytes(self):
        source = (ROOT / 'tools/verify_all.py').read_text(encoding='utf-8')
        self.assertNotIn('code_bytes[r_offset:r_offset + 4] = orig_bytes', source)
        self.assertIn('is_verified_match(match_count, num_insns, unresolved)', source)
        self.assertIn('unresolved_offsets(relocs, patched_offsets)', source)

    def test_incremental_build_tracks_headers_and_compiler_flags(self):
        source = (ROOT / 'tools/verify_local.py').read_text(encoding='utf-8')
        self.assertIn('ensure_build_signature(stamp, CLANG, CFLAGS)', source)
        self.assertIn('extra_dependencies=(stamp,)', source)
        self.assertIn('-MMD -MF', source)
