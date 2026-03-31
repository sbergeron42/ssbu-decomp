#include "types.h"
#define VT(m) (*reinterpret_cast<void***>(m))

struct OnCalcParamEvent;

namespace app::lua_bind {

void OnCalcParamEvent__store_l2c_table_impl(OnCalcParamEvent* ev) { reinterpret_cast<void(*)(OnCalcParamEvent*)>(VT(ev)[0x28/8])(ev); }
void OnCalcParamEvent__load_from_l2c_table_impl(OnCalcParamEvent* obj,u64 p1) { reinterpret_cast<void(*)(OnCalcParamEvent*,u64)>(VT(obj)[0x38/8])(obj,p1); }

} // namespace app::lua_bind
