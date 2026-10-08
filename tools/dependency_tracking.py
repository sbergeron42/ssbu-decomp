"""Read Clang/GCC -MMD dependency files for safe incremental recompilation.

If a depfile is absent, malformed, or refers to a missing header, rebuild the
object instead of trusting an old timestamp.
"""

import hashlib
import os
import re
from pathlib import Path


# Escaped newlines join Makefile continuations; a colon followed by whitespace
# separates the target from prerequisites without splitting Windows drive paths.
_LINE_CONTINUATION = re.compile(r"\\\r?\n")
_TARGET_END = re.compile(r"(?<!\\):(?=\s)")
_TOKEN = re.compile(r"(?:\\.|[^\s])+")
_ESCAPED_CHAR = re.compile(r"\\([ \\#:$])")


def read_dependencies(depfile):
    """Parse prerequisites from a Clang -MMD -MF generated .d file.

    Supports escaped spaces, Makefile line continuations, and Windows drive
    letters. A parse failure raises ValueError and forces a safe rebuild.
    """
    contents = _LINE_CONTINUATION.sub(" ", Path(depfile).read_text(encoding="utf-8"))
    separator = _TARGET_END.search(contents)
    if separator is None:
        raise ValueError("dependency file is missing its target separator")
    prerequisites = contents[separator.end():]
    tokens = _TOKEN.findall(prerequisites)
    if not tokens:
        raise ValueError("dependency file has no prerequisites")
    return [_ESCAPED_CHAR.sub(lambda match: match.group(1), token)
            for token in tokens]


def ensure_build_signature(stamp_file, compiler, compiler_flags):
    """Write a cache-invalidation stamp only when compiler identity/flags change.

    The compiler's size and nanosecond mtime detect in-place replacement of
    a toolchain at the same path. The stamp belongs beside the build output.
    Returns True when the signature changes.
    """
    compiler_path = Path(compiler)
    try:
        metadata = compiler_path.stat()
        compiler_identity = f"{metadata.st_size}:{metadata.st_mtime_ns}"
    except OSError:
        compiler_identity = "missing"

    spec = "\n".join((str(compiler_path), compiler_identity, compiler_flags))
    digest = hashlib.sha256(spec.encode("utf-8")).hexdigest()
    stamp_file = Path(stamp_file)
    try:
        if stamp_file.read_text(encoding="ascii").strip() == digest:
            return False
    except (OSError, UnicodeError):
        pass

    stamp_file.parent.mkdir(parents=True, exist_ok=True)
    temporary = stamp_file.with_name(stamp_file.name + ".tmp")
    temporary.write_text(digest + "\n", encoding="ascii")
    os.replace(temporary, stamp_file)
    return True


def needs_rebuild(source, obj, depfile, project_root, extra_dependencies=()):
    """True if the source or any transitive header changed since the object."""
    source, obj, depfile, project_root = map(
        Path, (source, obj, depfile, project_root))
    try:
        obj_mtime = obj.stat().st_mtime_ns
        prerequisites = read_dependencies(depfile)
        for dependency in (source, *(Path(name) for name in prerequisites),
                           *(Path(name) for name in extra_dependencies)):
            absolute_path = (project_root / dependency) if not dependency.is_absolute() else dependency
            if absolute_path.stat().st_mtime_ns >= obj_mtime:
                return True
    except (OSError, ValueError, UnicodeError):
        return True
    return False
