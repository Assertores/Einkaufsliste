#include "interface/i_logger.h"

namespace interface {
class ReplayableLogger : public ILogger
{
	void DoLog(std::string_view aLog) override { myReplayQueue.emplace(aLog); }
};

std::queue<std::string> ILogger::myReplayQueue {};
std::shared_ptr<ILogger> ILogger::myInstance = std::make_shared<ReplayableLogger>();

void
ILogger::Log(LogLevel aLevel, LogType aType, std::string_view aLog)
{
	if (aLevel < myLogLevel)
	{
		return;
	}
	if (myLogMask & aType)
	{
		DoLog(aLog);
	}
}

void
ILogger::SetLog(LogLevel aLevel, LogMask aTypeMask)
{
	myLogLevel = aLevel;
	myLogMask = aTypeMask;
}
}; // namespace interface
