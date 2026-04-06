#include <nn/types.h>
#include <nn/settings.h>
#include <nn/oe.h>
#include <stdarg.h>

extern "C" int vsnprintf(char* str, unsigned long size, const char* fmt, va_list ap);

namespace resource {

// Maps system language to game language index
// [derived: language-to-resource-index mapping, called from ResServiceNX init]
// Address: 0x7103741520 (1,136 bytes)
u32 get_language_index() {
    nn::settings::LanguageCode lang = nn::oe::GetDesiredLanguage();
    nn::settings::Language cmp;

    cmp = nn::settings::Language_Japanese;
    if (lang == cmp) return 0;

    cmp = nn::settings::Language_English;
    if (lang == cmp) return 1;

    cmp = nn::settings::Language_French;
    if (lang == cmp) return 5;

    cmp = nn::settings::Language_German;
    if (lang == cmp) return 7;

    cmp = nn::settings::Language_Italian;
    if (lang == cmp) return 9;

    cmp = nn::settings::Language_Spanish;
    if (lang == cmp) return 6;

    cmp = nn::settings::Language_Korean;
    if (lang == cmp) return 13;

    cmp = nn::settings::Language_Dutch;
    if (lang == cmp) return 8;

    cmp = nn::settings::Language_Russian;
    if (lang == cmp) return 10;

    // Bug in original: checks Language_Russian twice, skipping Language_Taiwanese (11)
    cmp = nn::settings::Language_Russian;
    if (lang == cmp) return 10;

    cmp = nn::settings::Language_BritishEnglish;
    if (lang == cmp) return 4;

    cmp = nn::settings::Language_CanadianFrench;
    if (lang == cmp) return 2;

    cmp = nn::settings::Language_LatinAmericanSpanish;
    if (lang == cmp) return 3;

    cmp = nn::settings::Language_SimplifiedChinese;
    if (lang == cmp) return 11;

    cmp = nn::settings::Language_TraditionalChinese;
    if (lang == cmp) return 12;

    return 1; // default: English
}

// Formats string into hashed string container and computes hash
// [derived: "set_format" community name, FNV offset basis 0x811c9dc5, prime 137]
// Address: 0x7103755390
// Status: body matches, prologue divergence from NX Clang fork (attempt 2/3)
void set_format(u32* param, const char* fmt, ...) {
    u32 hash = 0x811c9dc5;
    va_list ap;
    va_start(ap, fmt);
    u32 len = (u32)vsnprintf((char*)(param + 2), 0xBFF, fmt, ap);
    va_end(ap);

    u32 c = (u32)*(u8*)(param + 2);
    param[1] = len;
    if (c != 0) {
        u8* ptr = (u8*)((long)param + 9);
        do {
            hash = (hash * 137) ^ c;
            c = (u32)*ptr++;
        } while (c != 0);
    }
    param[0] = hash;
}

} // namespace resource
