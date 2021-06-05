#include "common/log_on_console.h"

#include <sstream>

#include <gmock/gmock.h>
#include <gtest/gtest.h>

using testing::HasSubstr;

TEST(LogOnConsole, log_message_is_containt_in_output) // NOLINT
{
	std::string stringToLog = "labsuzfuabef";

	std::stringstream output;
	common::LogOnConsole subject(output);

	subject.DoLog(interface::LogLevel::Debug, interface::LogType::Generic, stringToLog);

	EXPECT_THAT(output.str(), HasSubstr(stringToLog));
}