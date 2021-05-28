#include "common\log_on_console.h"

void
common::LogOnConsole::DoLog(
	interface::LogLevel aLevel,
	interface::LogType aType,
	std::string_view aLog)
{
	myOut << interface::ToString(aLevel) << ' ' << interface::ToString(aType) << ": " << aLog
		  << '\n';
}
