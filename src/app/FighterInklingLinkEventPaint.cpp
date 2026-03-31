#include "types.h"
struct LargeRet { unsigned long long a, b, c; };
#define VT(m) (*reinterpret_cast<void***>(m))

struct FighterInklingLinkEventPaint;

namespace app::lua_bind {

LargeRet FighterInklingLinkEventPaint__store_l2c_table_impl(FighterInklingLinkEventPaint* ev) { return reinterpret_cast<LargeRet(*)(FighterInklingLinkEventPaint*)>(VT(ev)[0x28/8])(ev); }
void FighterInklingLinkEventPaint__load_from_l2c_table_impl(FighterInklingLinkEventPaint* obj,u64 p1) { reinterpret_cast<void(*)(FighterInklingLinkEventPaint*,u64)>(VT(obj)[0x38/8])(obj,p1); }

LargeRet FighterInklingLinkEventPaint__store_l2c_table_impl_710219f230(FighterInklingLinkEventPaint* ev, u64 p1) { return reinterpret_cast<LargeRet(*)(FighterInklingLinkEventPaint*, u64)>(VT(ev)[0x30/8])(ev, p1); }
} // namespace app::lua_bind
