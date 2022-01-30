#pragma once

#include <filesystem>
#include <string>
#include <string_view>
#include <vector>

namespace common {
std::string PlatformIdentifyer();

void StartProcess(
	const std::filesystem::path& aExe,
	const std::vector<std::string_view>& aCommands,
	const std::filesystem::path& aWorkingDirectory);

std::filesystem::path CurrentExe();
} // namespace common
