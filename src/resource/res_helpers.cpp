#include "types.h"

// Forward declarations for nn SDK types used by resource service helpers
namespace nn::settings {

enum Language {
    Language_Japanese,
    Language_English,
    Language_French,
    Language_German,
    Language_Italian,
    Language_Spanish,
    Language_Chinese,
    Language_Korean,
    Language_Dutch,
    Language_Portuguese,
    Language_Russian,
    Language_Taiwanese,
    Language_BritishEnglish,
    Language_CanadianFrench,
    Language_LatinAmericanSpanish,
    Language_SimplifiedChinese,
    Language_TraditionalChinese,
};

struct LanguageCode {
    char code[0x8];
};

bool operator==(LanguageCode const&, Language const&);

} // namespace nn::settings

namespace nn::oe {
nn::settings::LanguageCode GetDesiredLanguage();
} // namespace nn::oe

// FUN_7103754c70 — get_desired_language
// Converts system LanguageCode to nn::settings::Language by linear scan of all 17 languages.
// Returns Language_English (1) as default if no match found.
// [derived: calls nn::oe::GetDesiredLanguage, compares via nn::settings::operator==]
// [derived: table in .rodata has 17 Language entries (0-16)]
nn::settings::Language FUN_7103754c70_3754c70() {
    nn::settings::Language table[17] = {
        nn::settings::Language_Japanese,
        nn::settings::Language_English,
        nn::settings::Language_French,
        nn::settings::Language_German,
        nn::settings::Language_Italian,
        nn::settings::Language_Spanish,
        nn::settings::Language_Chinese,
        nn::settings::Language_Korean,
        nn::settings::Language_Dutch,
        nn::settings::Language_Portuguese,
        nn::settings::Language_Russian,
        nn::settings::Language_Taiwanese,
        nn::settings::Language_BritishEnglish,
        nn::settings::Language_CanadianFrench,
        nn::settings::Language_LatinAmericanSpanish,
        nn::settings::Language_SimplifiedChinese,
        nn::settings::Language_TraditionalChinese,
    };

    nn::settings::LanguageCode code = nn::oe::GetDesiredLanguage();

    for (int i = 0; i < 17; i++) {
        if (code == table[i]) {
            return table[i];
        }
    }
    return nn::settings::Language_English;
}

// FUN_7103741520 — get_language_region_index
// MOVED to game_init.cpp (canonical version, verified match)



