#include "biz/log_on_console.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <sstream>

using testing::HasSubstr;

TEST(LogOnConsole, log_message_is_containt_in_output)  // NOLINT
{
	std::string stringToLog = "labsuzfuabef";

	std::stringstream output;
	biz::LogOnConsole subject(output);

	subject.DoLog(infas::LogLevel::Debug, infas::LogType::Generic, stringToLog);

	infas::ILogger::Clear();

	EXPECT_THAT(output.str(), HasSubstr(stringToLog));
}