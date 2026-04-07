#include "types.h"
#include "resource/LoadedArc.h"
#include "resource/ResServiceNX.h"

namespace resource {

// [derived: DAT_7105331f28 — global ResServiceNX* used by ARCropolis hooks]
extern ResServiceNX* g_res_service __attribute__((visibility("hidden")));

// FUN_7103541200 — lookup_stream_hash
// Looks up a stream file in the ARC archive by hash and returns its size, offset, and path.
// [derived: ARCropolis lookup_stream_hash hook — one of 9 hook targets]
// [derived: signature from ARCropolis: (out_path, arc, size_out, offset_out, hash)]
void FUN_7103541200(FixedString256* out_path, LoadedArc* arc, u64* size_out, u64* offset_out, u64 hash) {
    // Binary search for hash in stream_hash_to_entries (lower_bound pattern)
    // [derived: arc->stream_hash_to_entries at +0xC0, sorted by hash40 for binary lookup]
    HashToIndex* first = arc->stream_hash_to_entries;
    u32 n = arc->stream_header->stream_hash_count;
    HashToIndex* end = first + n;

    s64 count = (s64)(u64)n;
    while (count != 0) {
        s64 half = count / 2;
        HashToIndex* mid = first + half;
        if ((mid->raw & 0xFFFFFFFFFFULL) < hash) {
            first = mid + 1;
            count = count - half - 1;
        } else {
            count = half;
        }
    }

    // Check if entry was found: not at end, hash matches, and index is valid (not sentinel)
    // [derived: 0xFFFFFF sentinel = no valid stream entry]
    if (first == end || (first->raw & 0xFFFFFFFFFFULL) != hash || (first->raw >> 40) == 0xFFFFFF) {
        *size_out = 0;
        *offset_out = 0;
    } else {
        u32 entry_idx = (u32)(first->raw >> 40);
        StreamEntry* entry = &arc->stream_entries[entry_idx];

        // Determine locale offset based on stream entry type
        // [derived: locale_type 2=region (+0xD8), 1=language (+0xDC) from FUN_7103541200 switch]
        int locale_offset;
        switch (entry->locale_type) {
        case 2: {
            int idx = (int)g_res_service->region_idx;
            locale_offset = (idx != -1) ? idx : 0;
            break;
        }
        case 1: {
            int idx = (int)g_res_service->language_idx;
            locale_offset = (idx != -1) ? idx : 0;
            break;
        }
        default:
            locale_offset = 0;
            break;
        }

        // Look up stream data through file index table
        // [derived: stream_entries -> stream_file_indices -> stream_datas lookup chain]
        int file_group_idx = (int)entry->file_group_index();
        u32 file_idx = arc->stream_file_indices[locale_offset + file_group_idx];
        StreamData* data = &arc->stream_datas[file_idx];

        *offset_out = data->offset;
        *size_out = data->size;
    }

    // Copy ARC path string to output (always, regardless of lookup result)
    // [derived: g_res_service->arc_string copied to out_path for every lookup]
    ResServiceNX* svc = g_res_service;
    out_path->data[0] = '\0';
    u16 src_len = svc->arc_string.length;
    out_path->length = 0;
    if (src_len != 0) {
        const char* src = svc->arc_string.data;
        u64 remaining = (u64)src_len;
        do {
            out_path->data[out_path->length++] = *src++;
        } while (--remaining);
    }
    out_path->data[out_path->length] = '\0';
}

} // namespace resource
