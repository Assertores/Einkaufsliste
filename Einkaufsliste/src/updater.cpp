#include "biz/updater.h"

namespace biz {
bool
Update(const UpdaterSettings& aSettings)
{
	if (!aSettings.doUpdate)
	{
		return false;
	}
	// TODO(andreas): do REST API call to Github
	// (https://docs.github.com/en/rest/reference/repos#get-the-latest-release)
	return false;
}
} // namespace biz
