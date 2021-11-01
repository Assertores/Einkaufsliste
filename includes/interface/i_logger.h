#pragma once

#include <functional>
#include <memory>
#include <queue>
#include <string_view>
#include <utility>

namespace interface {
enum class LogLevel {
	Silent,
	Fatal,
	Error,
	Debug,
	Verbose,
};
enum class LogType : uint8_t {
	Generic = 1U << 0U,
	StartUp = 1U << 1U,
	Network = 1U << 2U,
	File = 1U << 3U,
	Commands = 1U << 4U,
	Units = 1U << 5U,
	Observer = 1U << 6U,
	Frontend = 1U << 7U,
};

using LogMask = std::underlying_type_t<LogType>;

constexpr LogMask
operator|(const LogType& aLhs, const LogType& aRhs) {
	return static_cast<LogMask>(aLhs) | static_cast<LogMask>(aRhs);
}

constexpr LogMask
operator|(const LogMask& aLhs, const LogType& aRhs) {
	return aLhs | static_cast<LogMask>(aRhs);
}

static constexpr LogMask locLogMaskNone = 0;
static constexpr LogMask locLogMaskApplication =
	LogType::Generic | LogType::StartUp | LogType::Frontend;
static constexpr LogMask locLogMaskIO = LogType::Network | LogType::File;
static constexpr LogMask locLogMaskAll = LogType::Generic | LogType::StartUp | LogType::Network
										 | LogType::File | LogType::Commands | LogType::Units
										 | LogType::Observer | LogType::Frontend;

class ILogger {
	friend class ReplayableLogger;

public:
	// returns sharedpointer to logger given via parameter for continuation.
	template <typename LogT, typename = std::enable_if_t<std::is_base_of_v<ILogger, LogT>>>
	static void SetImplimentation(LogT aLogger);

	static void Log(LogLevel aLevel, LogType aType, std::string_view aLog);
	static void SetLogLevel(LogLevel aLevel);
	static void SetLogMask(LogMask aTypeMask);

	static void Clear() {
		myLoggerImplimentation = nullptr;
		myReplayQueue = {};
		myLogLevel = LogLevel::Verbose;
		myLogMask = locLogMaskNone;
	}

	virtual ~ILogger() = default;

protected:
	virtual void DoLog(LogLevel aLevel, LogType aType, std::string_view aLog) = 0;

private:
	static std::shared_ptr<ILogger> myLoggerImplimentation;
	static std::queue<std::tuple<LogLevel, LogType, std::string>> myReplayQueue;

	static LogLevel myLogLevel;
	static LogMask myLogMask;
};

namespace fake {
class Logger : public ILogger {
public:
	std::function<void(LogLevel, LogType, std::string_view)> doLog =
		[this](auto /*unused*/, auto /*unused*/, auto /*unused*/) { doLogCount++; };

	void DoLog(LogLevel aLevel, LogType aType, std::string_view aLog) override {
		doLog(aLevel, aType, aLog);
	}

	int doLogCount = 0;
};
}  // namespace fake

template <typename LogT, typename>
void
ILogger::SetImplimentation(LogT aLogger) {
	myLoggerImplimentation = std::make_shared<LogT>(std::move(aLogger));
	while (!myReplayQueue.empty()) {
		myLoggerImplimentation->DoLog(
			std::get<0>(myReplayQueue.front()),
			std::get<1>(myReplayQueue.front()),
			std::get<2>(myReplayQueue.front()));
		myReplayQueue.pop();
	}
}

constexpr std::string_view
ToString(const LogLevel& aLevel) {
	switch (aLevel) {
	case LogLevel::Silent:
		return "[Silent]";
	case LogLevel::Fatal:
		return "[Fatal]";
	case LogLevel::Error:
		return "[Error]";
	case LogLevel::Debug:
		return "[Debug]";
	case LogLevel::Verbose:
		return "[Verbose]";
	}
	ILogger::Log(LogLevel::Error, LogType::Generic, "invalide log level");
	return "";
}

constexpr std::string_view
ToString(const LogType& aLevel) {
	switch (aLevel) {
	case LogType::Generic:
		return "Generic";
	case LogType::StartUp:
		return "StartUp";
	case LogType::Network:
		return "Network";
	case LogType::File:
		return "File";
	case LogType::Commands:
		return "Commands";
	case LogType::Units:
		return "Units";
	case LogType::Observer:
		return "Observer";
	case LogType::Frontend:
		return "Frontend";
	}
	ILogger::Log(LogLevel::Error, LogType::Generic, "invalide log level");
	return "";
}
};	// namespace interface
