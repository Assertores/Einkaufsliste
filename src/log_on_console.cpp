#include "biz/log_on_console.h"

#include <array>
#include <chrono>
#include <ctime>

static constexpr auto locBufferSize = 32;

namespace common {
void
LogOnConsole::DoLog(interface::LogLevel aLevel, interface::LogType aType, std::string_view aLog)
{
	auto t = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
	std::string time;
	time.reserve(locBufferSize);
	// NOTE(andreas): localtime_s is only available in visual studio localtime_r is not. to be able
	// to compile in visual studio and github ci i use the deprecated version
	strftime(
		time.data(),
		locBufferSize,
		"%d.%m.%Y %H:%M:%S",
		localtime(&t)); // NOLINT(clang-diagnostic-deprecated-declarations)

	myOut << time.c_str() << " | " << interface::ToString(aLevel) << ' '
		  << interface::ToString(aType) << ": " << aLog << '\n';
}
} // namespace common
