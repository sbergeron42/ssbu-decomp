#include "app/BattleObjectModuleAccessor.h"
#include "app/modules/CancelModule.h"
#define CN(a) static_cast<CancelModule*>((a)->cancel_module)

namespace app::lua_bind {

bool CancelModule__is_enable_cancel_impl(BattleObjectModuleAccessor* a) { return CN(a)->is_enable_cancel(); }
void CancelModule__enable_cancel_impl(BattleObjectModuleAccessor* a) { CN(a)->enable_cancel(); }

} // namespace app::lua_bind
