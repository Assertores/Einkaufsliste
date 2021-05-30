#include <gtest/gtest.h>

#include "interface/i_logger.h"

TEST(Logger, logs_get_replayed) // NOLINT
{
	interface::fake::Logger subject;
	interface::ILogger::SetLogLevel(interface::LogLevel::Verbose);
	interface::ILogger::SetLogMask(interface::LogMasks::All);
	interface::ILogger::Log(interface::LogLevel::Error, interface::LogType::Generic, "lbukwe");

	ASSERT_EQ(subject.doLogCount, 0);

	interface::ILogger::SetImplimentation(subject);

	EXPECT_EQ(subject.doLogCount, 1);

	interface::ILogger::Clear();
}

TEST(Logger, replay_data_is_same) // NOLINT
{
	auto logLevel = interface::LogLevel::Error;
	auto logType = interface::LogType::Generic;
	const auto* log = "lbukwe";
	interface::fake::Logger subject;
	auto outLogLevel = interface::LogLevel::Silent;
	auto outLogType = interface::LogType::StartUp;
	std::string outLog;
	subject.doLog = [&](auto aLevel, auto aType, auto aLog) {
		outLogLevel = aLevel;
		outLogType = aType;
		outLog = std::string(aLog);
	};

	interface::ILogger::SetLogLevel(interface::LogLevel::Verbose);
	interface::ILogger::SetLogMask(interface::LogMasks::All);
	interface::ILogger::Log(logLevel, logType, log);

	interface::ILogger::SetImplimentation(std::move(subject));

	EXPECT_EQ(outLogLevel, logLevel);
	EXPECT_EQ(outLogType, logType);
	EXPECT_EQ(outLog, log);

	interface::ILogger::Clear();
}

TEST(Logger, only_higher_or_equal_log_level_is_loged) // NOLINT
{
	interface::fake::Logger subject;
	interface::ILogger::SetLogLevel(interface::LogLevel::Error);
	interface::ILogger::SetLogMask(interface::LogMasks::All);
	interface::ILogger::SetImplimentation(subject);

	interface::ILogger::Log(interface::LogLevel::Fatal, interface::LogType::Generic, "lbukwe");
	EXPECT_EQ(subject.doLogCount, 1);
	interface::ILogger::Log(interface::LogLevel::Error, interface::LogType::Generic, "lbukwe");
	EXPECT_EQ(subject.doLogCount, 2);
	interface::ILogger::Log(interface::LogLevel::Debug, interface::LogType::Generic, "lbukwe");
	EXPECT_EQ(subject.doLogCount, 2);

	interface::ILogger::Clear();
}

TEST(Logger, only_logs_Type_in_mask) // NOLINT
{
	interface::fake::Logger subject;
	interface::ILogger::SetLogLevel(interface::LogLevel::Verbose);
	interface::ILogger::SetLogMask(interface::LogMasks::None | interface::LogType::Network);
	interface::ILogger::SetImplimentation(subject);

	interface::ILogger::Log(interface::LogLevel::Error, interface::LogType::Network, "lbukwe");
	EXPECT_EQ(subject.doLogCount, 1);

	interface::ILogger::Log(interface::LogLevel::Error, interface::LogType::StartUp, "lbukwe");
	EXPECT_EQ(subject.doLogCount, 1);

	interface::ILogger::Clear();
}
