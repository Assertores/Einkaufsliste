#include "common/platform.h"

#include <spawn.h>

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
	std::vector<std::string> argCopy(aCommands.cbegin(), aCommands.cend());
	std::vector<char*> args{};
	for (auto& it : argCopy) {
		args.push_back(it.data());
	}
	args.push_back(nullptr);

	pid_t pid{};
	posix_spawn(&pid, aExe.native().c_str(), nullptr, nullptr, args.data(), nullptr);
}

std::filesystem::path
CurrentExe() {
	return std::filesystem::canonical("/proc/self/exe");
}
}  // namespace common
