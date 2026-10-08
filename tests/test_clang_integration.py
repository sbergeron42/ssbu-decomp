"""Live compiler smoke test for MMD dependencies and build-stamp invalidation."""

import os
import shutil
import subprocess
import sys
import tempfile
import unittest
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parents[1] / "tools"))
from dependency_tracking import ensure_build_signature, needs_rebuild, read_dependencies


class ClangIntegrationTests(unittest.TestCase):
    @unittest.skipUnless(shutil.which("clang++"), "clang++ not installed")
    def test_real_clang_depfile_and_incremental_invalidations(self):
        clang = shutil.which("clang++")
        with tempfile.TemporaryDirectory() as folder:
            root = Path(folder)
            header = root / "stats.h"
            source = root / "stats.cpp"
            obj = root / "stats.o"
            dep = root / "stats.d"
            stamp = root / ".verify_local_compile.sha256"
            header.write_text("#define MULTIPLIER 2\n")
            source.write_text('#include "stats.h"\nint score() { return 21 * MULTIPLIER; }\n')

            def compile_source():
                cmd = [clang, "-std=c++17", "-O2", "-MMD", "-MF", str(dep),
                       "-MT", str(obj), "-c", str(source), "-o", str(obj)]
                subprocess.run(cmd, cwd=root, check=True, capture_output=True, text=True)

            self.assertTrue(ensure_build_signature(stamp, clang, "-O2"))
            compile_source()
            self.assertIn(str(header), read_dependencies(dep))
            self.assertFalse(needs_rebuild(source, obj, dep, root, extra_dependencies=(stamp,)))

            # Use a timestamp strictly after the object to avoid FS clock granularity.
            next_time = obj.stat().st_mtime_ns + 2_000_000_000
            os.utime(header, ns=(next_time, next_time))
            self.assertTrue(needs_rebuild(source, obj, dep, root, extra_dependencies=(stamp,)))
            compile_source()
            # The new object can inherit a time <= the deliberately future-touched header.
            os.utime(header, ns=(obj.stat().st_mtime_ns - 2_000_000_000,) * 2)
            self.assertFalse(needs_rebuild(source, obj, dep, root, extra_dependencies=(stamp,)))

            self.assertTrue(ensure_build_signature(stamp, clang, "-O3"))
            self.assertTrue(needs_rebuild(source, obj, dep, root, extra_dependencies=(stamp,)))


if __name__ == "__main__":
    unittest.main()
