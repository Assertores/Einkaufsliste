#include "biz/change_recipe_name.h"

#include "interface/i_file_impl.h"

#include <gtest/gtest.h>

TEST(ChangeRecipeName, description_is_added_to_recipe)  // NOLINT
{
	auto mockRecipe = std::static_pointer_cast<infas::fake::FileImpl>(infas::IFileImpl::Open<infas::fake::FileImpl>("aubhfuke"));
	auto frontend = std::make_shared<infas::fake::Frontend>();
	auto recipe = std::make_shared<common::Observable<std::optional<common::Recipe>>>();
	recipe->Set(std::make_optional<common::Recipe>(mockRecipe));

	auto subject = biz::ChangeRecipeName::Create();
	subject->SetReferences(frontend, recipe);

	subject->Execute();

	infas::IFileImpl::Clear();

	// TODO(andreas): Silent Contract? find better way to test this.
	ASSERT_NE(mockRecipe->myContent.find("Name"), mockRecipe->myContent.end());
	ASSERT_GT(mockRecipe->myContent["Name"].size(), 0);
	EXPECT_EQ(mockRecipe->myContent["Name"][0], infas::fake::Frontend::defaultText);
}

TEST(ChangeRecipeName, description_is_reverted_to_previous_description_by_memento)  // NOLINT
{
	std::string_view firstName = "bnzdsfbasefksadf";

	auto mockRecipe = std::static_pointer_cast<infas::fake::FileImpl>(infas::IFileImpl::Open<infas::fake::FileImpl>("aubhfuke"));
	auto frontend = std::make_shared<infas::fake::Frontend>();
	auto recipe = std::make_shared<common::Observable<std::optional<common::Recipe>>>();
	recipe->Set(std::make_optional<common::Recipe>(mockRecipe));

	auto subject = biz::ChangeRecipeName::Create();
	subject->SetReferences(frontend, recipe);
	common::Recipe(mockRecipe).SetName(firstName);

	auto memento = subject->Execute();
	memento->Revert();

	infas::IFileImpl::Clear();

	ASSERT_NE(mockRecipe->myContent.find("Name"), mockRecipe->myContent.end());
	ASSERT_GT(mockRecipe->myContent["Name"].size(), 0);
	EXPECT_EQ(mockRecipe->myContent["Name"][0], firstName);
}

TEST(ChangeRecipeName, description_is_readded_to_recipe_by_memento)	// NOLINT
{
	auto mockRecipe = std::static_pointer_cast<infas::fake::FileImpl>(infas::IFileImpl::Open<infas::fake::FileImpl>("aubhfuke"));
	auto frontend = std::make_shared<infas::fake::Frontend>();
	auto recipe = std::make_shared<common::Observable<std::optional<common::Recipe>>>();
	recipe->Set(std::make_optional<common::Recipe>(mockRecipe));

	auto subject = biz::ChangeRecipeName::Create();
	subject->SetReferences(frontend, recipe);

	auto memento = subject->Execute();
	memento->Revert();
	memento->ReExecute();

	infas::IFileImpl::Clear();

	ASSERT_NE(mockRecipe->myContent.find("Name"), mockRecipe->myContent.end());
	ASSERT_GT(mockRecipe->myContent["Name"].size(), 0);
	EXPECT_EQ(mockRecipe->myContent["Name"][0], infas::fake::Frontend::defaultText);
}
