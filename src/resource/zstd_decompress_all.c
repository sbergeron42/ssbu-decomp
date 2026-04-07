/* Amalgamation build of zstd decompressor
 * Compiles all zstd decompress sources as a single TU for matching
 * [derived: zstd v1.3.7, ZSTD_LEGACY_SUPPORT=4]
 */

/* Common sources */
#include "../../lib/zstd/common/entropy_common.c"
#include "../../lib/zstd/common/error_private.c"
#include "../../lib/zstd/common/fse_decompress.c"
#include "../../lib/zstd/common/xxhash.c"
#include "../../lib/zstd/common/zstd_common.c"

/* Decompressor */
#include "../../lib/zstd/decompress/huf_decompress.c"
#include "../../lib/zstd/decompress/zstd_decompress.c"
