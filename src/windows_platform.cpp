#include "common/platform.h"

#include <windows.h>

#include <cuchar>
#include <string>

namespace common {
void
StartProcess(
	const std::filesystem::path& aExe,
	const std::vector<std::string_view>& aCommands,
	const std::filesystem::path& aWorkingDirectory) {
	std::string commandline;

	std::string seperator;
	for (const auto& it : aCommands) {
		commandline += seperator;
		commandline += it;
		seperator = " ";
	}

	std::wstring wCommandline;

	std::mbstate_t state{};
	char16_t c16{};
	const char* ptr = &commandline[0];
	const char* end = &commandline[0] + commandline.size();
	while (std::size_t rc = std::mbrtoc16(&c16, ptr, end - ptr + 1, &state)) {
		wCommandline += c16;
		if (rc == (std::size_t)-3) {
			continue;
		}
		if (rc == (std::size_t)-2) {
			break;
		}
		if (rc == (std::size_t)-1) {
			break;
		}
		ptr += rc;
	}

	STARTUPINFOW si{};
	PROCESS_INFORMATION pi{};
	si.cb = sizeof(si);
	if (CreateProcessW(
			aExe.native().c_str(),
			wCommandline.data(),
			nullptr,
			nullptr,
			FALSE,
			CREATE_UNICODE_ENVIRONMENT | CREATE_NEW_CONSOLE,
			nullptr,
			aWorkingDirectory.native().c_str(),
			&si,
			&pi)
		== FALSE) {
		return;
	}
	CloseHandle(pi.hProcess);
	CloseHandle(pi.hThread);
}

std::filesystem::path
CurrentExe() {
	wchar_t exePath[UNICODE_STRING_MAX_CHARS];						 // NOLINT
	GetModuleFileNameW(nullptr, exePath, UNICODE_STRING_MAX_CHARS);	 // NOLINT
	return exePath;
}
}  // namespace common
