#pragma once

#include <functional>
#include <memory>
#include <queue>
#include <string_view>
#include <utility>

namespace interface {
enum class LogLevel
{
	Silent,
	Fatal,
	Error,
	Debug,
	Verbose,
};
enum LogType : uint8_t
{
	None = 0,
	Generic = 1 << 0,
	StartUp = 1 << 1,
	Network = 1 << 2,
	File = 1 << 3,
	Commands = 1 << 4,
	Units = 1 << 5,

	Application = Generic | StartUp | Units,
	IO = Network | File,
	All = Generic | StartUp | Network | File | Commands | Units,
};

using LogMask = std::underlying_type_t<LogType>;

class ILogger
{
	friend class ReplayableLogger;
public:
	static std::shared_ptr<ILogger> Instance() { return myInstance; }
	// returns sharedpointer to logger given via parameter for continuation.
	template <
		typename LogT,
		typename = std::enable_if_t<std::is_base_of_v<ILogger, LogT>>>
	static std::shared_ptr<ILogger> SetInstance(LogT aLogger);

	void Log(LogLevel aLevel, LogType aType, std::string_view aLog);
	void SetLog(LogLevel aLevel, LogMask aTypeMask);

protected:

	virtual void DoLog(std::string_view aLog) = 0;
private:
	static std::shared_ptr<ILogger> myInstance;
	static std::queue<std::string> myReplayQueue;

	LogLevel myLogLevel;
	LogMask myLogMask;
};

namespace fake {
class Logger : public ILogger
{
public:
	std::function<void(std::string_view)> doLog = [this](auto /*unused*/) {
		doLogCount++;
	};

	void
	DoLog(std::string_view aLog) override
	{
		DoLog(aLog);
	}

	int doLogCount = 0;
};
} // namespace fake

template <typename LogT, typename>
std::shared_ptr<ILogger>
ILogger::SetInstance(LogT aLogger)
{
	myInstance = std::make_shared<LogT>(aLogger);
	while (!myReplayQueue.empty())
	{
		myInstance->DoLog(myReplayQueue.front());
		myReplayQueue.pop();
	}
	return myInstance;
}
}; // namespace interface
