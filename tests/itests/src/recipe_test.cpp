#include "common/recipe.h"

#include "common/unit.h"
#include "interface/i_file_impl.h"

#include <gtest/gtest.h>

TEST(Recipe, read_and_write)  // NOLINT
{
	auto mockingFileImpl = std::make_shared<interface::fake::FileImpl>();
	mockingFileImpl->getField = [](auto /*unused*/) { return std::vector<std::string>{"1"}; };
	mockingFileImpl->getKeys = [](auto /*unused*/) {
		return std::vector<std::filesystem::path>{"kg"};
	};
	common::UnitConvertion convertion(mockingFileImpl);

	common::Unit::SetConvertionFiles({convertion});
	const auto* name = "Example";
	const auto* description = "this is a example recipe.";
	std::vector<common::Unit> ingredians = {
		{1, "kg", "apfel"},
		{1, "kg", "kirschen"},
		{1, "kg", "wassermelone"}};

	const auto recipePath = std::filesystem::current_path() / "example.md";
	std::filesystem::remove(recipePath);
	std::cout << "example recepy was created at: " << recipePath.string() << '\n';
	{
		common::Recipe subject(recipePath);

		subject.SetName(name);
		subject.SetDescription(description);
		for (const auto& it : ingredians) {
			subject.AddIngredient(it);
		}
	}
	// NOTE(andreas): forces programm to read it in from the file
	interface::IFileImpl::Clear();

	common::Recipe subject(recipePath);

	EXPECT_EQ(subject.GetName(), name);
	EXPECT_EQ(subject.GetDescription(), description);
	auto resultIngredians = subject.GetIngredients();
	ASSERT_EQ(resultIngredians.size(), ingredians.size());
	for (int i = 0; i < ingredians.size(); i++) {
		EXPECT_EQ(resultIngredians[i], ingredians[i]);
	}
}
