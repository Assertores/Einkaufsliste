#include "interface/i_logger.h"

namespace interface {
std::queue<std::tuple<LogLevel, LogType, std::string>> ILogger::myReplayQueue {};
std::shared_ptr<ILogger> ILogger::myLoggerImplimentation = nullptr;
LogLevel ILogger::myLogLevel = LogLevel::Verbose;
LogMask ILogger::myLogMask = LogMasks::All;

void
ILogger::Log(LogLevel aLevel, LogType aType, std::string_view aLog)
{
	if (aLevel > myLogLevel)
	{
		return;
	}
	if ((myLogMask & static_cast<LogMask>(aType)) != 0)
	{
		if (!myLoggerImplimentation)
		{
			myReplayQueue.emplace(aLevel, aType, aLog);
			return;
		}
		myLoggerImplimentation->DoLog(aLevel, aType, aLog);
	}
}

void
ILogger::SetLogLevel(LogLevel aLevel)
{
	myLogLevel = aLevel;
}

void
ILogger::SetLogMask(LogMask aTypeMask)
{
	myLogMask = aTypeMask;
}
}; // namespace interface
