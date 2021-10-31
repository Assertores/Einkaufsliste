#pragma once

#include <string>

namespace biz {
struct UpdaterSettings {
	bool doUpdate;
	bool getPrerelease;
	std::string url;
};

bool Update(const UpdaterSettings& aSettings);
}  // namespace biz
