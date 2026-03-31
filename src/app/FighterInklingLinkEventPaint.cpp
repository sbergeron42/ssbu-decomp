#include "types.h"
#define VT(m) (*reinterpret_cast<void***>(m))

struct FighterInklingLinkEventPaint;

namespace app::lua_bind {

void FighterInklingLinkEventPaint__store_l2c_table_impl(FighterInklingLinkEventPaint* ev) { reinterpret_cast<void(*)(FighterInklingLinkEventPaint*)>(VT(ev)[0x28/8])(ev); }
void FighterInklingLinkEventPaint__load_from_l2c_table_impl(FighterInklingLinkEventPaint* obj,u64 p1) { reinterpret_cast<void(*)(FighterInklingLinkEventPaint*,u64)>(VT(obj)[0x38/8])(obj,p1); }

} // namespace app::lua_bind
