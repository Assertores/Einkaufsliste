#include "biz/entry.h"
#include "common/md_parser.h"
#include "common/recipe.h"

#include <gtest/gtest.h>

#include <thread>

using namespace std::chrono_literals;

static constexpr auto locSleepTime = 5ms;

TEST(application, complains_if_command_is_unrecogniced)	 // NOLINT
{
	std::stringstream out;
	biz::Entry(
		std::vector<std::string_view>{
			"exe",
			"--no-patch",
			"--no-update",
			"--shut-down",
			"--log-level",
			"verbose",
			"-something"},
		out);

	EXPECT_FALSE(out.str().empty());
}

TEST(application, reacts_to_exit_commands)	// NOLINT
{
	std::stringstream out;
	std::stringstream in;
	in << "exit\n";

	std::vector<std::string_view> args =
		{"exe", "--no-patch", "--no-update", "--log-level", "verbose"};
	std::thread thread(biz::Entry, args, std::ref(out), std::ref(in));

	EXPECT_TRUE(thread.joinable());
	thread.join();
}

TEST(application, reacts_to_quit_commands)	// NOLINT
{
	std::stringstream out;
	std::stringstream in;
	in << "quit\n";

	std::vector<std::string_view> args =
		{"exe", "--no-patch", "--no-update", "--log-level", "verbose"};
	std::thread thread(biz::Entry, args, std::ref(out), std::ref(in));

	EXPECT_TRUE(thread.joinable());
	thread.join();
}

TEST(application, can_undo)	 // NOLINT
{
	const auto* const name = "dfzjzejdsaf";
	const auto* const fileName = "assets/exampleRecipeLive.md";
	std::filesystem::copy_file(
		"assets/exampleRecipe.md",
		fileName,
		std::filesystem::copy_options::overwrite_existing);

	std::stringstream out;
	std::stringstream in;
	in << "open recipe\n";
	in << fileName << '\n';
	in << "change recipe name\n";
	in << name << '\n';
	in << "undo\n";
	in << "exit\n";

	std::vector<std::string_view> args =
		{"exe", "--no-patch", "--no-update", "--log-level", "verbose"};
	std::thread thread(biz::Entry, args, std::ref(out), std::ref(in));

	thread.join();

	auto parser = std::make_shared<common::MdParser>();
	auto file = std::ifstream(fileName);
	parser->Parse(file);
	common::Recipe result(parser);
	const auto prevName = result.GetName();

	EXPECT_EQ(result.GetName(), prevName);
}

TEST(application, can_redo)	 // NOLINT
{
	const auto* const name = "ezzsjzsdaf";
	const auto* const fileName = "assets/exampleRecipeLive.md";
	std::filesystem::copy_file(
		"assets/exampleRecipe.md",
		fileName,
		std::filesystem::copy_options::overwrite_existing);

	std::stringstream out;
	std::stringstream in;
	in << "open recipe\n";
	in << fileName << '\n';
	in << "change recipe name\n";
	in << name << '\n';
	in << "undo\n";
	in << "redo\n";
	in << "exit\n";

	std::vector<std::string_view> args =
		{"exe", "--no-patch", "--no-update", "--log-level", "verbose"};
	std::thread thread(biz::Entry, args, std::ref(out), std::ref(in));

	thread.join();

	auto parser = std::make_shared<common::MdParser>();
	auto file = std::ifstream(fileName);
	parser->Parse(file);
	common::Recipe result(parser);
	EXPECT_EQ(result.GetName(), name);
}

TEST(application, can_open_recipe)	// NOLINT
{
	const auto* const fileName = "assets/exampleRecipeLive.md";
	std::filesystem::copy_file(
		"assets/exampleRecipe.md",
		fileName,
		std::filesystem::copy_options::overwrite_existing);

	std::stringstream out;
	std::stringstream in;
	in << "open recipe\n";
	in << fileName << '\n';
	in << "exit\n";

	std::vector<std::string_view> args =
		{"exe", "--no-patch", "--no-update", "--log-level", "verbose"};
	std::thread thread(biz::Entry, args, std::ref(out), std::ref(in));

	// TODO(andreas): how to test this?
	thread.join();
}

TEST(application, can_name_recipe)	// NOLINT
{
	const auto* const name = "hsaudfhak";
	const auto* const fileName = "assets/exampleRecipeLive.md";
	std::filesystem::copy_file(
		"assets/exampleRecipe.md",
		fileName,
		std::filesystem::copy_options::overwrite_existing);

	std::stringstream out;
	std::stringstream in;
	in << "open recipe\n";
	in << fileName << '\n';
	in << "change recipe name\n";
	in << name << '\n';
	in << "exit\n";

	std::vector<std::string_view> args =
		{"exe", "--no-patch", "--no-update", "--log-level", "verbose"};
	std::thread thread(biz::Entry, args, std::ref(out), std::ref(in));

	thread.join();

	auto parser = std::make_shared<common::MdParser>();
	auto file = std::ifstream(fileName);
	parser->Parse(file);
	common::Recipe result(parser);
	EXPECT_EQ(result.GetName(), name);
}

TEST(application, can_add_description_to_recipe)  // NOLINT
{
	const auto* const description = "bsdgse";
	const auto* const fileName = "assets/exampleRecipeLive.md";
	std::filesystem::copy_file(
		"assets/exampleRecipe.md",
		fileName,
		std::filesystem::copy_options::overwrite_existing);

	std::stringstream out;
	std::stringstream in;
	in << "open recipe\n";
	in << fileName << '\n';
	in << "change recipe description\n";
	in << description << '\n';
	in << "exit\n";

	std::vector<std::string_view> args =
		{"exe", "--no-patch", "--no-update", "--log-level", "verbose"};
	std::thread thread(biz::Entry, args, std::ref(out), std::ref(in));

	thread.join();

	auto parser = std::make_shared<common::MdParser>();
	auto file = std::ifstream(fileName);
	parser->Parse(file);
	common::Recipe result(parser);
	EXPECT_EQ(result.GetDescription(), description);
}

#if not_tesable
TEST(application, can - open - convertion - file)  // NOLINT
{
	const auto* const convertionFileName = "assets/exampleConvertion.md";

	std::stringstream out;
	std::stringstream in;
	in << "open-convertion\n";
	in << convertionFileName << '\n';
	in << "print\n";
	in << "exit\n";

	std::vector<std::string_view> args =
		{"exe", "--no-patch", "--no-update", "--log-level", "verbose"};
	std::thread thread(biz::Entry, args, std::ref(out), std::ref(in));

	thread.join();

	"g: 1000\n"
	"kg: 1\n"
	"t: 0.001\n"
}
#endif

TEST(application, can_add_ingrediance_to_recipe)  // NOLINT
{
	const auto* const type = "bsdgse";
	const auto amount = 3;
	const auto* const unit = "kg";
	const auto* const fileName = "assets/exampleRecipeLive.md";
	std::filesystem::copy_file(
		"assets/exampleRecipe.md",
		fileName,
		std::filesystem::copy_options::overwrite_existing);
	const auto* const convertionFileName = "assets/convertionLive";
	std::filesystem::copy(
		"assets/convertion",
		convertionFileName,
		std::filesystem::copy_options::overwrite_existing);

	std::stringstream out;
	std::stringstream in;
	in << "open convertion\n";
	in << convertionFileName << '\n';
	in << "open recipe\n";
	in << fileName << '\n';
	in << "add recipe ingredient\n";
	in << type << '\n';
	in << amount << '\n';
	in << unit << '\n';
	in << "exit\n";

	std::vector<std::string_view> args =
		{"exe", "--no-patch", "--no-update", "--log-level", "verbose"};
	std::thread thread(biz::Entry, args, std::ref(out), std::ref(in));

	thread.join();

	auto parser = std::make_shared<common::MdParser>();
	auto file = std::ifstream(fileName);
	parser->Parse(file);
	common::Recipe result(parser);
	const auto ingrediance = result.GetIngredients();
	ASSERT_GT(ingrediance.size(), 0);
	EXPECT_EQ(ingrediance.size(), 1);
	EXPECT_EQ(ingrediance[0], common::Unit(amount, unit, type));
}

TEST(application, can_remove_ingrediance_from_recipe)  // NOLINT
{
	const auto* const type = "bsdgse";
	const auto amount = 3;
	const auto* const unit = "kg";
	const auto* const fileName = "assets/exampleRecipeLive.md";
	std::filesystem::copy_file(
		"assets/exampleRecipe.md",
		fileName,
		std::filesystem::copy_options::overwrite_existing);
	const auto* const convertionFileName = "assets/convertionLive";
	std::filesystem::copy(
		"assets/convertion",
		convertionFileName,
		std::filesystem::copy_options::overwrite_existing);

	std::stringstream out;
	std::stringstream in;
	in << "open convertion\n";
	in << convertionFileName << '\n';
	in << "open recipe\n";
	in << fileName << '\n';
	in << "add recipe ingredient\n";
	in << type << '\n';
	in << amount << '\n';
	in << unit << '\n';
	in << "remove recipe ingredient\n";
	in << type << '\n';
	in << amount << '\n';
	in << unit << '\n';
	in << "exit\n";

	std::vector<std::string_view> args =
		{"exe", "--no-patch", "--no-update", "--log-level", "verbose"};
	std::thread thread(biz::Entry, args, std::ref(out), std::ref(in));

	thread.join();

	auto parser = std::make_shared<common::MdParser>();
	auto file = std::ifstream(fileName);
	parser->Parse(file);
	common::Recipe result(parser);
	const auto ingrediance = result.GetIngredients();
	EXPECT_EQ(ingrediance.size(), 0);
}
