#include <nn/time.h>
#include <nn/oe.h>
#include <nn/settings.h>

// Packed calendar time format used by the engine:
// bits 0-11:  year (12 bits)
// bits 12-15: month (4 bits)
// bits 16-20: day (5 bits)
// bits 21-25: hour (5 bits)
// bits 26-31: minute (6 bits)
// bits 32-37: second (6 bits)
// bits 48-50: day of week (3 bits)
// bit 62:     is_utc flag
// bit 63:     is_valid flag

// 0x7103741260 — Convert PosixTime to packed calendar time (local timezone)
// [derived: calls nn::time::ToCalendarTime, GetDayOfWeek, IsValidDate]
bool FUN_7103741260_3741260(nn::time::PosixTime posix_time, u64* packed) {
    nn::time::CalendarTime ct;
    nn::time::CalendarAdditionalInfo info;
    nn::Result result = nn::time::ToCalendarTime(&ct, &info, posix_time);
    if (result == 0) {
        *packed = (*packed & 0xFFFFFFC000000000ULL) |
                  ((u64)ct.year & 0xFFF) |
                  (((u64)(ct.month & 0xF)) << 12) |
                  (((u64)(ct.day & 0x1F)) << 16) |
                  (((u64)(ct.hour & 0x1F)) << 21) |
                  (((u64)(ct.minute & 0x3F)) << 26) |
                  (((u64)(ct.second & 0x3F)) << 32);

        int dow = nn::time::GetDayOfWeek(ct.year, ct.month, ct.day);
        *packed = (*packed & ~((7ULL << 48) | (1ULL << 62))) | ((u64)(dow & 7) << 48);

        int valid = nn::time::IsValidDate(ct.year, ct.month, ct.day);
        *packed = (*packed & ~(1ULL << 63)) | ((u64)(valid & 1) << 63);
    }
    return result == 0;
}

// 0x7103741330 — Convert PosixTime to packed calendar time (UTC)
// [derived: calls nn::time::ToCalendarTimeInUtc, IsValidDate, GetDayOfWeek]
u32 FUN_7103741330_3741330(nn::time::PosixTime posix_time, u64* packed) {
    nn::time::CalendarTime ct = nn::time::ToCalendarTimeInUtc(posix_time);
    int valid = nn::time::IsValidDate(ct.year, ct.month, ct.day);
    if (valid & 1) {
        *packed = (*packed & 0xFFFFFFC000000000ULL) |
                  ((u64)ct.year & 0xFFF) |
                  (((u64)(ct.month & 0xF)) << 12) |
                  (((u64)(ct.day & 0x1F)) << 16) |
                  (((u64)(ct.hour & 0x1F)) << 21) |
                  (((u64)(ct.minute & 0x3F)) << 26) |
                  (((u64)(ct.second & 0x3F)) << 32);
        int dow = nn::time::GetDayOfWeek(ct.year, ct.month, ct.day);
        *packed = (*packed & ~(7ULL << 48)) | ((u64)(dow & 7) << 48) | 0xC000000000000000ULL;
    }
    return valid & 1;
}

// 0x7103741410 — Convert packed calendar time to PosixTime
// [derived: calls nn::time::IsValidDate, ToPosixTime, ToPosixTimeFromUtc]
bool FUN_7103741410_3741410(const u32* packed_in, u64* posix_out) {
    u32 lo = packed_in[0];
    u32 hi = packed_in[1];

    nn::time::CalendarTime ct;
    ct.year = (s16)(lo & 0xFFF);
    ct.month = (s8)((lo >> 12) & 0xF);
    ct.day = (s8)((lo >> 16) & 0x1F);
    ct.hour = (s8)((lo >> 21) & 0x1F);
    ct.minute = (s8)(lo >> 26);
    ct.second = (s8)(hi & 0x3F);

    if (!nn::time::IsValidDate(lo & 0xFFF, (lo >> 12) & 0xF, (lo >> 16) & 0x1F)) {
        *posix_out = 0;
        return false;
    }

    // Check is_utc flag (bit 62 = bit 6 of byte 7)
    if (((const u8*)packed_in)[7] >> 6 & 1) {
        nn::time::PosixTime pt = nn::time::ToPosixTimeFromUtc(ct);
        *posix_out = pt.time;
        return true;
    }

    int count;
    nn::time::PosixTime results[2];
    nn::Result err = nn::time::ToPosixTime(&count, results, 2, ct);
    bool success = (err == 0);
    if (err == 0) {
        if (count == 2) {
            *posix_out = results[1].time;
        } else if (count == 1) {
            *posix_out = results[0].time;
        }
    }
    return success;
}

// FUN_7103741520 — get_language_region_index
// MOVED to game_init.cpp (canonical version, verified match)
