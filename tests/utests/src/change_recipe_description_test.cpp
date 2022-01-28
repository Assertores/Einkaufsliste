#include "biz/change_recipe_description.h"

#include "interface/i_file_impl.h"

#include <gtest/gtest.h>

TEST(ChangeRecipeDescription, description_is_added_to_recipe)  // NOLINT
{
	auto mockRecipe = std::make_shared<infas::fake::FileImpl>();
	auto frontend = std::make_shared<infas::fake::Frontend>();
	auto recipe = std::make_shared<common::Observable<std::optional<common::Recipe>>>();
	recipe->Set(std::make_optional<common::Recipe>(mockRecipe));

	auto subject = biz::ChangeRecipeDescription::Create();
	subject->SetReferences(frontend, recipe);

	subject->Execute();

	// TODO(andreas): Silent Contract? find better way to test this.
	ASSERT_NE(mockRecipe->myContent.find("Description"), mockRecipe->myContent.end());
	ASSERT_GT(mockRecipe->myContent["Description"].size(), 0);
	EXPECT_EQ(mockRecipe->myContent["Description"][0], infas::fake::Frontend::defaultText);

	infas::IFileImpl::Clear();
}

TEST(ChangeRecipeDescription, description_is_reverted_to_previous_description_by_memento)  // NOLINT
{
	std::string_view firstDescription = "bnzdsfbasefksadf";
	auto mockRecipe = std::make_shared<infas::fake::FileImpl>();
	auto frontend = std::make_shared<infas::fake::Frontend>();
	auto recipe = std::make_shared<common::Observable<std::optional<common::Recipe>>>();
	recipe->Set(std::make_optional<common::Recipe>(mockRecipe));

	auto subject = biz::ChangeRecipeDescription::Create();
	subject->SetReferences(frontend, recipe);
	common::Recipe(mockRecipe).SetDescription(firstDescription);

	auto memento = subject->Execute();
	memento->Revert();

	ASSERT_NE(mockRecipe->myContent.find("Description"), mockRecipe->myContent.end());
	ASSERT_GT(mockRecipe->myContent["Description"].size(), 0);
	EXPECT_EQ(mockRecipe->myContent["Description"][0], firstDescription);

	infas::IFileImpl::Clear();
}

TEST(ChangeRecipeDescription, description_is_readded_to_recipe_by_memento)	// NOLINT
{
	auto mockRecipe = std::make_shared<infas::fake::FileImpl>();
	auto frontend = std::make_shared<infas::fake::Frontend>();
	auto recipe = std::make_shared<common::Observable<std::optional<common::Recipe>>>();
	recipe->Set(std::make_optional<common::Recipe>(mockRecipe));

	auto subject = biz::ChangeRecipeDescription::Create();
	subject->SetReferences(frontend, recipe);

	auto memento = subject->Execute();
	memento->Revert();
	memento->ReExecute();

	ASSERT_NE(mockRecipe->myContent.find("Description"), mockRecipe->myContent.end());
	ASSERT_GT(mockRecipe->myContent["Description"].size(), 0);
	EXPECT_EQ(mockRecipe->myContent["Description"][0], infas::fake::Frontend::defaultText);

	infas::IFileImpl::Clear();
}
