#include "biz/argument_parser.h"

#include <gtest/gtest.h>

TEST(ArgumentParser, ignores_first_argument) // NOLINT
{
	std::string argument = "asdfefc";
	bool wasCalled = false;
	std::vector<std::string_view> args;
	args.emplace_back(argument);

	biz::Interpreter subject;
	subject[argument] = [&](auto /*unused*/) {
		wasCalled = true;
	};

	biz::RunInterpretion(args, subject);

	EXPECT_FALSE(wasCalled);
}