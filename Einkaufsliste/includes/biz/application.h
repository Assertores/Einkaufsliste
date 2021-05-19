#pragma once

namespace biz {
struct AppSettings
{
	bool doPatching;
};

void Run(const AppSettings& aSettings);
} // namespace biz
