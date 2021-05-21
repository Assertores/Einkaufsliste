#include "common/recipe.h"

#include <gtest/gtest.h>

#include "interface/i_file_impl.h"

TEST(Recipe, read_and_write) // NOLINT
{
	const auto* name = "Example";
	const auto* description = "this is a example recipe.";
	std::vector<std::string_view> ingredians = { "apfel", "kirschen", "wassermelone" };

	const auto recipePath = std::filesystem::current_path() / "example.md";
	std::filesystem::remove(recipePath);
	std::cout << "example recepy was created at: " << recipePath.string() << '\n';
	{
		common::Recipe subject(recipePath);

		subject.SetName(name);
		subject.SetDescription(description);
		for (const auto& it : ingredians)
		{
			subject.AddIngredient(it);
		}
	}
	interface::IFileImpl::Clear();

	common::Recipe subject(recipePath);

	EXPECT_EQ(subject.GetName(), name);
	EXPECT_EQ(subject.GetDescription(), description);
	auto resultIngredians = subject.GetIngredients();
	ASSERT_EQ(resultIngredians.size(), ingredians.size());
	for (int i = 0; i < ingredians.size(); i++)
	{
		EXPECT_EQ(resultIngredians[i], ingredians[i]);
	}
}
