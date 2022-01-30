#include "biz/open_recipe.h"

#include "interface/i_file_impl.h"

#include <gtest/gtest.h>

TEST(OpenRecipe, recipe_is_opend) // NOLINT
{
	auto frontend = std::make_shared<infas::fake::Frontend>();
	auto recipe = std::make_shared<common::Observable<std::optional<common::Recipe>>>();

	auto subject = biz::OpenRecipe::Create();
	subject->SetReferences(frontend, recipe);

	subject->Execute();

	ASSERT_TRUE(recipe->Get().has_value());
	EXPECT_EQ(recipe->Get(), common::Recipe(infas::fake::Frontend::defaultFilePath));

	infas::IFileImpl::Clear();
}

TEST(OpenRecipe, opening_a_recipe_can_not_be_undone) // NOLINT
{
	auto frontend = std::make_shared<infas::fake::Frontend>();
	auto recipe = std::make_shared<common::Observable<std::optional<common::Recipe>>>();

	auto subject = biz::OpenRecipe::Create();
	subject->SetReferences(frontend, recipe);

	auto memento = subject->Execute();

	infas::IFileImpl::Clear();

	EXPECT_EQ(memento, nullptr);
}
