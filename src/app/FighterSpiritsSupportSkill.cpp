#include "types.h"
#define VT(m) (*reinterpret_cast<void***>(m))

struct FighterSpiritsSupportSkill;

namespace app::lua_bind {

bool FighterSpiritsSupportSkill__is_unsync_vis_whole_effect_impl(FighterSpiritsSupportSkill* obj) { return reinterpret_cast<bool(*)(FighterSpiritsSupportSkill*)>(VT(obj)[0x148/8])(obj); }
bool FighterSpiritsSupportSkill__is_visible_effect_impl(FighterSpiritsSupportSkill* obj) { return reinterpret_cast<bool(*)(FighterSpiritsSupportSkill*)>(VT(obj)[0x158/8])(obj); }

} // namespace app::lua_bind
