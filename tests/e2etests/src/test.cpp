#include "biz/entry.h"
#include "common/md_parser.h"
#include "common/recipe.h"

#include <gtest/gtest.h>

#include <thread>

// TODO(andreas): ingetrate asset folder fixture

using namespace std::chrono_literals;

static constexpr auto locSleepTime = 5ms;
static const std::filesystem::path locAssetDir{ASSETS_DIR};

TEST(application, complains_if_command_is_unrecogniced) // NOLINT
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

TEST(application, reacts_to_exit_commands) // NOLINT
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

TEST(application, reacts_to_quit_commands) // NOLINT
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

TEST(application, can_undo) // NOLINT
{
	const auto* const name = "dfzjzejdsaf";
	const auto fileName = locAssetDir / "exampleRecipeLive.md";
	std::filesystem::copy_file(
		locAssetDir / "exampleRecipe.md",
		fileName,
		std::filesystem::copy_options::overwrite_existing);
	ASSERT_TRUE(std::filesystem::is_regular_file(fileName))
		<< "og path: " << (locAssetDir / "exampleRecipe.md").string()
		<< "\nnew path: " << fileName.string();

	std::stringstream out;
	std::stringstream in;
	in << "open recipe\n";
	in << fileName.string() << '\n';
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

TEST(application, can_redo) // NOLINT
{
	const auto* const name = "ezzsjzsdaf";
	const auto fileName = locAssetDir / "exampleRecipeLive.md";
	std::filesystem::copy_file(
		locAssetDir / "exampleRecipe.md",
		fileName,
		std::filesystem::copy_options::overwrite_existing);
	ASSERT_TRUE(std::filesystem::is_regular_file(fileName))
		<< "og path: " << (locAssetDir / "exampleRecipe.md").string()
		<< "\nnew path: " << fileName.string();

	std::stringstream out;
	std::stringstream in;
	in << "open recipe\n";
	in << fileName.string() << '\n';
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

TEST(application, can_open_recipe) // NOLINT
{
	const auto fileName = locAssetDir / "exampleRecipeLive.md";
	std::filesystem::copy_file(
		locAssetDir / "exampleRecipe.md",
		fileName,
		std::filesystem::copy_options::overwrite_existing);
	ASSERT_TRUE(std::filesystem::is_regular_file(fileName))
		<< "og path: " << (locAssetDir / "exampleRecipe.md").string()
		<< "\nnew path: " << fileName.string();

	std::stringstream out;
	std::stringstream in;
	in << "open recipe\n";
	in << fileName.string() << '\n';
	in << "exit\n";

	std::vector<std::string_view> args =
		{"exe", "--no-patch", "--no-update", "--log-level", "verbose"};
	std::thread thread(biz::Entry, args, std::ref(out), std::ref(in));

	// TODO(andreas): how to test this?
	thread.join();
}

TEST(application, can_name_recipe) // NOLINT
{
	const auto* const name = "hsaudfhak";
	const auto fileName = locAssetDir / "exampleRecipeLive.md";
	std::filesystem::copy_file(
		locAssetDir / "exampleRecipe.md",
		fileName,
		std::filesystem::copy_options::overwrite_existing);
	ASSERT_TRUE(std::filesystem::is_regular_file(fileName))
		<< "og path: " << (locAssetDir / "exampleRecipe.md").string()
		<< "\nnew path: " << fileName.string();

	std::stringstream out;
	std::stringstream in;
	in << "open recipe\n";
	in << fileName.string() << '\n';
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

TEST(application, can_add_description_to_recipe) // NOLINT
{
	const auto* const description = "bsdgse";
	const auto fileName = locAssetDir / "exampleRecipeLive.md";
	std::filesystem::copy_file(
		locAssetDir / "exampleRecipe.md",
		fileName,
		std::filesystem::copy_options::overwrite_existing);
	ASSERT_TRUE(std::filesystem::is_regular_file(fileName))
		<< "og path: " << (locAssetDir / "exampleRecipe.md").string()
		<< "\nnew path: " << fileName.string();

	std::stringstream out;
	std::stringstream in;
	in << "open recipe\n";
	in << fileName.string() << '\n';
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
TEST(application, can - open - conversion - file) // NOLINT
{
	const auto* const conversionFileName = "assets/exampleConversion.md";

	std::stringstream out;
	std::stringstream in;
	in << "open-conversion\n";
	in << conversionFileName << '\n';
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

TEST(application, can_add_ingrediance_to_recipe) // NOLINT
{
	const auto* const type = "bsdgse";
	const auto amount = 3;
	const auto* const unit = "kg";
	const auto fileName = locAssetDir / "exampleRecipeLive.md";
	std::filesystem::copy_file(
		locAssetDir / "exampleRecipe.md",
		fileName,
		std::filesystem::copy_options::overwrite_existing);
	const auto conversionFileName = locAssetDir / "conversionLive";
	ASSERT_TRUE(std::filesystem::is_directory(locAssetDir / "conversion"))
		<< "path: " << (locAssetDir / "conversion").string();
	std::filesystem::copy(
		locAssetDir / "conversion",
		conversionFileName,
		std::filesystem::copy_options::overwrite_existing
			| std::filesystem::copy_options::recursive);
	ASSERT_TRUE(std::filesystem::is_directory(conversionFileName))
		<< "og path: " << (locAssetDir / "conversion").string()
		<< "\nnew path: " << conversionFileName.string();
	ASSERT_TRUE(std::filesystem::is_regular_file(fileName))
		<< "og path: " << (locAssetDir / "exampleRecipe.md").string()
		<< "\nnew path: " << fileName.string();

	std::stringstream out;
	std::stringstream in;
	in << "open conversion\n";
	in << conversionFileName.string() << '\n';
	in << "open recipe\n";
	in << fileName.string() << '\n';
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

TEST(application, can_remove_ingrediance_from_recipe) // NOLINT
{
	const auto* const type = "bsdgse";
	const auto amount = 3;
	const auto* const unit = "kg";
	const auto fileName = locAssetDir / "exampleRecipeLive.md";
	std::filesystem::copy_file(
		locAssetDir / "exampleRecipe.md",
		fileName,
		std::filesystem::copy_options::overwrite_existing);
	const auto conversionFileName = locAssetDir / "conversionLive";
	std::filesystem::copy(
		locAssetDir / "conversion",
		conversionFileName,
		std::filesystem::copy_options::overwrite_existing
			| std::filesystem::copy_options::recursive);
	ASSERT_TRUE(std::filesystem::is_directory(conversionFileName))
		<< "og path: " << (locAssetDir / "conversion").string()
		<< "\nnew path: " << conversionFileName.string();
	ASSERT_TRUE(std::filesystem::is_regular_file(fileName))
		<< "og path: " << (locAssetDir / "exampleRecipe.md").string()
		<< "\nnew path: " << fileName.string();

	std::stringstream out;
	std::stringstream in;
	in << "open conversion\n";
	in << conversionFileName.string() << '\n';
	in << "open recipe\n";
	in << fileName.string() << '\n';
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
