#include "types.h"
#define VT(m) (*reinterpret_cast<void***>(m))

struct Weapon;

namespace app::lua_bind {

u32 Weapon__get_founder_id_impl(Weapon* obj) { return reinterpret_cast<u32(*)(Weapon*)>(VT(obj)[0x3e8/8])(obj); }

} // namespace app::lua_bind
