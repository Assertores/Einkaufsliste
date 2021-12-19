#include "common/platform.h"

namespace common {
std::string
PlatformIdentifyer() {
	return "linux";
}

void
StartProcess(
	const std::filesystem::path& aExe,
	const std::vector<std::string_view>& aCommands,
	const std::filesystem::path& aWorkingDirectory) {
	static_assert(false, "not implimented");
}

std::filesystem::path
CurrentExe() {
	return std::filesystem::canonical("/proc/self/exe");
}
}  // namespace common
