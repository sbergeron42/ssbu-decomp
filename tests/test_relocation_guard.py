import sys
import unittest
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parents[1] / "tools"))
from relocation_guard import is_verified_match, unresolved_offsets


class RelocationSafetyTests(unittest.TestCase):
    def test_fully_matched_resolved_is_verified(self):
        self.assertTrue(is_verified_match(3, 3, set()))

    def test_equal_bytes_with_unknown_relocation_are_not_verified(self):
        relocs = [(4, 275, "unresolved_symbol", 0)]
        pending = unresolved_offsets(relocs, set())
        self.assertEqual(pending, {4})
        self.assertFalse(is_verified_match(3, 3, pending))

    def test_partial_patch_keeps_remaining_relocation_unverified(self):
        relocs = [(0, 283, "FUN_7100001000", 0), (4, 275, ".rodata", 0)]
        self.assertEqual(unresolved_offsets(relocs, {0}), {4})

    def test_mismatching_bytes_remain_nonmatching(self):
        self.assertFalse(is_verified_match(2, 3, set()))

    def test_empty_functions_not_reported_verified(self):
        self.assertFalse(is_verified_match(0, 0, set()))
