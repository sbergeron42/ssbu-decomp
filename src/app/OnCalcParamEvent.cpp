#include "types.h"
struct LargeRet { unsigned long long a, b, c; };
#define VT(m) (*reinterpret_cast<void***>(m))

struct OnCalcParamEvent;

namespace app::lua_bind {

LargeRet OnCalcParamEvent__store_l2c_table_impl(OnCalcParamEvent* ev) { return reinterpret_cast<LargeRet(*)(OnCalcParamEvent*)>(VT(ev)[0x28/8])(ev); }
void OnCalcParamEvent__load_from_l2c_table_impl(OnCalcParamEvent* obj,u64 p1) { reinterpret_cast<void(*)(OnCalcParamEvent*,u64)>(VT(obj)[0x38/8])(obj,p1); }

LargeRet OnCalcParamEvent__store_l2c_table_impl_71020bbef0(OnCalcParamEvent* ev, u64 p1) { return reinterpret_cast<LargeRet(*)(OnCalcParamEvent*, u64)>(VT(ev)[0x30/8])(ev, p1); }
} // namespace app::lua_bind
