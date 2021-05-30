#pragma once

#include <string>

namespace biz {
struct UpdaterSettings
{
	bool doUpdate;
	std::string url;
};

bool Update(const UpdaterSettings& aSettings);
} // namespace biz
