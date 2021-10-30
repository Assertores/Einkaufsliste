#pragma once

namespace biz {
struct PatcherSettings
{
	bool doPatching;
};

void Patch(const PatcherSettings& aSettings);
} // namespace biz
