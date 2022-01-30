#include "biz/argument_parser.h"

#include <gtest/gtest.h>

TEST(ArgumentParser, ignores_first_argument) // NOLINT
{
	std::string argument = "asdfefc";
	std::vector<std::string_view> args{argument};

	bool wasCalled = false;
	biz::Interpreter subject;
	subject[argument] = [&](auto /*unused*/) { wasCalled = true; };

	biz::RunInterpretion(args, subject);

	EXPECT_FALSE(wasCalled);
}

TEST(ArgumentParser, lambda_is_called_if_argument_is_encountered) // NOLINT
{
	std::string argument = "asdfefc";
	std::vector<std::string_view> args{"", argument};

	bool wasCalled = false;
	biz::Interpreter subject;
	subject[argument] = [&](auto& /*unused*/) { wasCalled = true; };

	biz::RunInterpretion(args, subject);

	EXPECT_TRUE(wasCalled);
}

TEST(ArgumentParser, argument_is_removed_from_queue_on_lambda_call) // NOLINT
{
	std::string argument1 = "asdfefc";
	std::string argument2 = "basdzte";
	std::vector<std::string_view> args{"", argument1, argument2};

	std::string firstElement;
	biz::Interpreter subject;
	subject[argument1] = [&](auto& aQueue) { firstElement = aQueue.front(); };

	biz::RunInterpretion(args, subject);

	EXPECT_EQ(firstElement, argument2);
}

TEST(ArgumentParser, unparsed_arguments_are_returned) // NOLINT
{
	std::string argument1 = "asdfefc";
	std::string argument2 = "basdzte";
	std::vector<std::string_view> args{"", argument1, argument2};

	std::string firstElement;
	biz::Interpreter subject;
	subject[argument1] = [&](auto& aQueue) { firstElement = aQueue.front(); };

	auto errors = biz::RunInterpretion(args, subject);

	ASSERT_GT(errors.size(), 0);
	EXPECT_EQ(errors[0].first, 2);
	EXPECT_EQ(errors[0].second, argument2);
}
