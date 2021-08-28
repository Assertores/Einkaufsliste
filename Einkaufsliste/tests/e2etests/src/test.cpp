#include <thread>

#include <gtest/gtest.h>

#include "biz/entry.h"
#include "common/md_parser.h"
#include "common/recipe.h"

using namespace std::chrono_literals;

static constexpr auto locSleepTime = 5ms;

TEST(application, complains_if_command_is_unrecogniced) // NOLINT
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
	in << "exit";

	std::vector<std::string_view> args = { "exe",
										   "--no-patch",
										   "--no-update",
										   "--log-level",
										   "verbose" };
	std::thread thread(biz::Entry, args, std::ref(out), std::ref(in));

	EXPECT_TRUE(thread.joinable());
	thread.join();
}

TEST(application, reacts_to_quit_commands) // NOLINT
{
	std::stringstream out;
	std::stringstream in;
	in << "quit";

	std::vector<std::string_view> args = { "exe",
										   "--no-patch",
										   "--no-update",
										   "--log-level",
										   "verbose" };
	std::thread thread(biz::Entry, args, std::ref(out), std::ref(in));

	EXPECT_TRUE(thread.joinable());
	thread.join();
}

TEST(application, can_open_recipe) // NOLINT
{
	std::stringstream out;
	std::stringstream in;
	in << "open-recipe\n";
	in << "assets/exampleRecipe.md\n";
	in << "exit";

	std::vector<std::string_view> args = {"exe",
		"--no-patch",
		"--no-update",
		"--log-level",
		"verbose"};
	std::thread thread(biz::Entry, args, std::ref(out), std::ref(in));

	thread.join();
}

TEST(application, can_name_recipe) // NOLINT
{
	const auto *const name = "hsaudfhak";
	const auto *const fileName = "assets/exampleRecipe.md";

	std::stringstream out;
	std::stringstream in;
	in << "open-recipe\n";
	in << fileName << "\n";
	in << "change-recipe-name\n";
	in << name << "\n";
	in << "exit";

	std::vector<std::string_view> args = { "exe",
										   "--no-patch",
										   "--no-update",
										   "--log-level",
										   "verbose" };
	std::thread thread(biz::Entry, args, std::ref(out), std::ref(in));

	thread.join();

	auto parser = std::make_shared<common::MdParser>();
	auto file = std::ifstream(fileName);
	parser->Parse(file);
	common::Recipe result(parser);
	EXPECT_EQ(result.GetName(), name);
}

