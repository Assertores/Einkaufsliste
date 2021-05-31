#include <thread>

#include <gtest/gtest.h>

#include "biz/entry.h"

TEST(test, test) // NOLINT
{
	std::stringstream out;
	biz::Entry(
		std::vector<std::string_view> { "exe",
										"--no-patch",
										"--no-update",
										"--shut-down",
										"--log-level",
										"verbose",
										"-something" },
		out);

	EXPECT_FALSE(out.str().empty());
}

TEST(application, reacts_to_exit_commands) // NOLINT
{
	std::stringstream out;
	std::stringstream in;
	std::vector<std::string_view> args = { "exe",
										   "--no-patch",
										   "--no-update",
										   "--log-level",
										   "verbose" };
	std::thread thread(biz::Entry, args, std::ref(out), std::ref(in));

	in << "exit";

	EXPECT_TRUE(thread.joinable());
	thread.join();
}
#if false
TEST(application, can_open_recipe) // NOLINT
{
	std::stringstream out;
	std::stringstream in;
	std::vector<std::string_view> args = { "exe",
										   "--no-patch",
										   "--no-update",
										   "--log-level",
										   "verbose" };
	std::thread thread(biz::Entry, args, std::ref(out), std::ref(in));

	in << "open-recipe";
	in << "assets/exampleRecipe.md";

	thread.join();
}
#endif
