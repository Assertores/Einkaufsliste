#include "interface/i_logger.h"

#include <gtest/gtest.h>

TEST(Logger, logs_get_replayed)	 // NOLINT
{
	infas::fake::Logger subject;
	infas::ILogger::SetLogLevel(infas::LogLevel::Verbose);
	infas::ILogger::SetLogMask(infas::locLogMaskAll);
	infas::ILogger::Log(infas::LogLevel::Error, infas::LogType::Generic, "lbukwe");

	ASSERT_EQ(subject.doLogCount, 0);

	infas::ILogger::SetImplimentation(subject);

	EXPECT_EQ(subject.doLogCount, 1);

	infas::ILogger::Clear();
}

TEST(Logger, replay_data_is_same)  // NOLINT
{
	auto logLevel = infas::LogLevel::Error;
	auto logType = infas::LogType::Generic;
	const auto* log = "lbukwe";
	infas::fake::Logger subject;
	auto outLogLevel = infas::LogLevel::Silent;
	auto outLogType = infas::LogType::StartUp;
	std::string outLog;
	subject.doLog = [&](auto aLevel, auto aType, auto aLog) {
		outLogLevel = aLevel;
		outLogType = aType;
		outLog = std::string(aLog);
	};

	infas::ILogger::SetLogLevel(infas::LogLevel::Verbose);
	infas::ILogger::SetLogMask(infas::locLogMaskAll);
	infas::ILogger::Log(logLevel, logType, log);

	infas::ILogger::SetImplimentation(std::move(subject));

	EXPECT_EQ(outLogLevel, logLevel);
	EXPECT_EQ(outLogType, logType);
	EXPECT_EQ(outLog, log);

	infas::ILogger::Clear();
}

TEST(Logger, only_higher_or_equal_log_level_is_loged)  // NOLINT
{
	infas::fake::Logger subject;
	infas::ILogger::SetLogLevel(infas::LogLevel::Error);
	infas::ILogger::SetLogMask(infas::locLogMaskAll);
	infas::ILogger::SetImplimentation(subject);

	infas::ILogger::Log(infas::LogLevel::Fatal, infas::LogType::Generic, "lbukwe");
	EXPECT_EQ(subject.doLogCount, 1);
	infas::ILogger::Log(infas::LogLevel::Error, infas::LogType::Generic, "lbukwe");
	EXPECT_EQ(subject.doLogCount, 2);
	infas::ILogger::Log(infas::LogLevel::Debug, infas::LogType::Generic, "lbukwe");
	EXPECT_EQ(subject.doLogCount, 2);

	infas::ILogger::Clear();
}

TEST(Logger, only_logs_Type_in_mask)  // NOLINT
{
	infas::fake::Logger subject;
	infas::ILogger::SetLogLevel(infas::LogLevel::Verbose);
	infas::ILogger::SetLogMask(infas::locLogMaskNone | infas::LogType::Network);
	infas::ILogger::SetImplimentation(subject);

	infas::ILogger::Log(infas::LogLevel::Error, infas::LogType::Network, "lbukwe");
	EXPECT_EQ(subject.doLogCount, 1);

	infas::ILogger::Log(infas::LogLevel::Error, infas::LogType::StartUp, "lbukwe");
	EXPECT_EQ(subject.doLogCount, 1);

	infas::ILogger::Clear();
}
