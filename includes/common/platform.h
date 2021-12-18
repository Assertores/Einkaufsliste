#pragma once

#include <filesystem>
#include <string_view>
#include <vector>

namespace common {
void StartProcess(const std::filesystem::path& aExe, const std::vector<std::string_view>& aCommands, const std::filesystem::path& aWorkingDirectory);

std::filesystem::path CurrentExe();
}  // namespace common
