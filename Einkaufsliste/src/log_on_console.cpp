#include "common\log_on_console.h"

#include <chrono>
#include <ctime>
#include <array>

static constexpr auto locBufferSize = 32;

void
common::LogOnConsole::DoLog(
	interface::LogLevel aLevel,
	interface::LogType aType,
	std::string_view aLog)
{
	auto t = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
	tm tm {};
	localtime_s(&tm, &t);

	std::string time;
	time.reserve(locBufferSize);
	strftime(time.data(), locBufferSize, "%d %m %Y %H:%M:%S", &tm);

	myOut << time.c_str() << " | " << interface::ToString(aLevel)
		  << ' ' << interface::ToString(aType) << ": " << aLog
		  << '\n';
}
