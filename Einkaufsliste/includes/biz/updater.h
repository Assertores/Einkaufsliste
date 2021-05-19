#pragma once

#include <string>

namespace biz {
struct UpdaterSettings
{
	std::string url;
};

void Update(const UpdaterSettings& aSettings);
}
