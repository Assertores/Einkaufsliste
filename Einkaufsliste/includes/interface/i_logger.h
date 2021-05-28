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
enum class LogType : uint8_t
{
	Generic = 1 << 0,
	StartUp = 1 << 1,
	Network = 1 << 2,
	File = 1 << 3,
	Commands = 1 << 4,
	Units = 1 << 5,
};

using LogMask = std::underlying_type_t<LogType>;

constexpr LogMask
operator|(const LogType& aLhs, const LogType& aRhs)
{
	return static_cast<LogMask>(aLhs) | static_cast<LogMask>(aRhs);
}

constexpr LogMask
operator|(const LogMask& aLhs, const LogType& aRhs)
{
	return aLhs | static_cast<LogMask>(aRhs);
}

namespace LogMasks {
static constexpr LogMask None = 0;
static constexpr LogMask Application = LogType::Generic | LogType::StartUp | LogType::Units;
static constexpr LogMask IO = LogType::Network | LogType::File;
static constexpr LogMask All = LogType::Generic | LogType::StartUp | LogType::Network
	| LogType::File | LogType::Commands | LogType::Units;
}


class ILogger
{
	friend class ReplayableLogger;

public:
	// returns sharedpointer to logger given via parameter for continuation.
	template <typename LogT, typename = std::enable_if_t<std::is_base_of_v<ILogger, LogT>>>
	static void SetImplimentation(LogT aLogger);

	static void Log(LogLevel aLevel, LogType aType, std::string_view aLog);
	static void SetLog(LogLevel aLevel, LogMask aTypeMask);

	static void Clear()
	{
		myLoggerImplimentation = nullptr;
		myReplayQueue = {};
		myLogLevel = LogLevel::Verbose;
		myLogMask = LogMasks::None;
	}

protected:
	virtual void DoLog(LogLevel aLevel, LogType aType, std::string_view aLog) = 0;

private:
	static std::shared_ptr<ILogger> myLoggerImplimentation;
	static std::queue<std::tuple<LogLevel, LogType, std::string>> myReplayQueue;

	static LogLevel myLogLevel;
	static LogMask myLogMask;
};

namespace fake {
class Logger : public ILogger
{
public:
	std::function<void(LogLevel, LogType, std::string_view)> doLog =
		[this](auto /*unused*/, auto /*unused*/, auto /*unused*/) {
			doLogCount++;
		};

	void DoLog(LogLevel aLevel, LogType aType, std::string_view aLog) override
	{
		doLog(aLevel, aType, aLog);
	}

	int doLogCount = 0;
};
} // namespace fake

template <typename LogT, typename>
void
ILogger::SetImplimentation(LogT aLogger)
{
	myLoggerImplimentation = std::make_shared<LogT>(std::move(aLogger));
	while (!myReplayQueue.empty())
	{
		myLoggerImplimentation->DoLog(
			std::get<0>(myReplayQueue.front()),
			std::get<1>(myReplayQueue.front()),
			std::get<2>(myReplayQueue.front()));
		myReplayQueue.pop();
	}
	return;
}
}; // namespace interface
