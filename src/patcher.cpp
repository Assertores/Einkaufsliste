#include "biz/patcher.h"

namespace biz {
void
Patch(const PatcherSettings& aSettings)
{
	if (!aSettings.doPatching)
	{
		return;
	}
	// TODO(andreas): remove stuff from update
	// TODO(andreas): Translate data to new version
}
} // namespace biz
