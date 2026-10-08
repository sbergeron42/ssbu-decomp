import os
import sys
import tempfile
import unittest
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parents[1] / "tools"))
from dependency_tracking import needs_rebuild, read_dependencies, ensure_build_signature


class DependencyTrackingTests(unittest.TestCase):
    def setUp(self):
        self.tempdir = tempfile.TemporaryDirectory()
        self.addCleanup(self.tempdir.cleanup)
        self.root = Path(self.tempdir.name)
        self.source = self.root / "fighter.cpp"
        self.header = self.root / "include" / "fighter state.h"
        self.header.parent.mkdir()
        self.obj = self.root / "fighter.o"
        self.dep = self.root / "fighter.d"
        self.source.write_text('#include "include/fighter state.h"\n')
        self.header.write_text('struct State {};\n')
        self.obj.write_bytes(b'object')
        self.dep.write_text('fighter.o: fighter.cpp include/fighter\\ state.h\n')
        self.set_times()

    def set_times(self):
        for path in (self.source, self.header):
            os.utime(path, ns=(1_000_000_000, 1_000_000_000))
        os.utime(self.obj, ns=(2_000_000_000, 2_000_000_000))

    def check(self):
        return needs_rebuild(self.source, self.obj, self.dep, self.root)

    def test_stable_headers_reuse_object(self):
        self.assertFalse(self.check())

    def test_newer_header_forces_rebuild(self):
        os.utime(self.header, ns=(3_000_000_000, 3_000_000_000))
        self.assertTrue(self.check())

    def test_newer_source_forces_rebuild(self):
        os.utime(self.source, ns=(3_000_000_000, 3_000_000_000))
        self.assertTrue(self.check())

    def test_missing_header_forces_rebuild(self):
        self.header.unlink()
        self.assertTrue(self.check())

    def test_missing_depfile_forces_rebuild(self):
        self.dep.unlink()
        self.assertTrue(self.check())

    def test_malformed_depfile_forces_rebuild(self):
        self.dep.write_text('malformed')
        self.assertTrue(self.check())

    def test_missing_object_forces_rebuild(self):
        self.obj.unlink()
        self.assertTrue(self.check())

    def test_compiler_flags_invalidate_cached_objects(self):
        compiler = self.root / "fake-clang.exe"
        compiler.write_bytes(b"clang-8")
        stamp = self.root / ".verify_local_compile.sha256"
        self.assertTrue(ensure_build_signature(stamp, compiler, "-O2"))
        os.utime(stamp, ns=(500_000_000, 500_000_000))
        self.assertFalse(needs_rebuild(self.source, self.obj, self.dep,
                                       self.root, extra_dependencies=(stamp,)))
        self.assertFalse(ensure_build_signature(stamp, compiler, "-O2"))
        self.assertTrue(ensure_build_signature(stamp, compiler, "-O3"))
        self.assertTrue(needs_rebuild(self.source, self.obj, self.dep,
                                      self.root, extra_dependencies=(stamp,)))

    def test_replacing_compiler_in_place_invalidates_cache(self):
        compiler = self.root / "fake-clang.exe"
        compiler.write_bytes(b"clang-8")
        stamp = self.root / ".verify_local_compile.sha256"
        self.assertTrue(ensure_build_signature(stamp, compiler, "-O2"))
        self.assertFalse(ensure_build_signature(stamp, compiler, "-O2"))
        compiler.write_bytes(b"clang-8-replaced")
        self.assertTrue(ensure_build_signature(stamp, compiler, "-O2"))

    def test_missing_signature_rebuilds(self):
        missing = self.root / "no-stamp"
        self.assertTrue(needs_rebuild(self.source, self.obj, self.dep,
                                      self.root, extra_dependencies=(missing,)))

    def test_escaped_spaces_and_continuations(self):
        self.dep.write_text('fighter.o: fighter.cpp \\\n include/fighter\\ state.h\n')
        self.assertEqual(read_dependencies(self.dep),
                         ['fighter.cpp', 'include/fighter state.h'])

    def test_windows_drive_colon_is_not_target_separator(self):
        self.dep.write_text('C:\\build\\fighter.o: C:\\src\\fighter.cpp C:\\include\\fighter.h\n')
        self.assertEqual(read_dependencies(self.dep),
                         ['C:\\src\\fighter.cpp', 'C:\\include\\fighter.h'])


if __name__ == '__main__':
    unittest.main()
