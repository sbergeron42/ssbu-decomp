// game_init.cpp — Game initialization helpers (resource service area)
// Part of game_ldn_initialize (FUN_7103741990) decomp

#include <nn/oe.h>
#include <nn/settings.h>

using namespace nn::settings;

// FUN_7103741520 — Map system language to SSBU internal language index
// [derived: called from game_ldn_initialize at +0x568, uses nn::oe::GetDesiredLanguage]
// Returns: game language index 0-13
//   0=Japanese, 1=English, 2=CanadianFrench, 3=LatinAmericanSpanish,
//   4=BritishEnglish, 5=French, 6=Spanish, 7=German, 8=Dutch,
//   9=Italian, 10=Russian, 11=SimplifiedChinese, 12=TraditionalChinese, 13=Korean
s32 FUN_7103741520() {
    LanguageCode desired = nn::oe::GetDesiredLanguage();
    Language lang;

    lang = Language_Japanese;
    if (desired == lang) return 0;

    lang = Language_English;
    if (desired == lang) return 1;

    lang = Language_French;
    if (desired == lang) return 5;

    lang = Language_German;
    if (desired == lang) return 7;

    lang = Language_Italian;
    if (desired == lang) return 9;

    lang = Language_Spanish;
    if (desired == lang) return 6;

    lang = Language_Korean;
    if (desired == lang) return 13;

    lang = Language_Dutch;
    if (desired == lang) return 8;

    lang = Language_Russian;
    if (desired == lang) return 10;

    lang = Language_Russian;
    if (desired == lang) return 10;

    lang = Language_BritishEnglish;
    if (desired == lang) return 4;

    lang = Language_CanadianFrench;
    if (desired == lang) return 2;

    lang = Language_LatinAmericanSpanish;
    if (desired == lang) return 3;

    lang = Language_SimplifiedChinese;
    if (desired == lang) return 11;

    lang = Language_TraditionalChinese;
    if (desired == lang) return 12;

    return 1; // default: English
}
