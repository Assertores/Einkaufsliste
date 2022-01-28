#include "biz/add_recipe_unit.h"

#include "interface/i_file_impl.h"

#include <gtest/gtest.h>

void
SetupMockUnitConvertion() {
	auto mockingFileImpl = std::make_shared<infas::fake::FileImpl>();
	mockingFileImpl->getField = [](auto /*unused*/) { return std::vector<std::string>{"1"}; };
	mockingFileImpl->getKeys = [](auto /*unused*/) {
		return std::vector<std::filesystem::path>{"kg"};
	};
	common::UnitConversion conversion(mockingFileImpl);
	common::Unit::SetConversionFiles({conversion});
}

TEST(AddRecipeUnit, unit_is_added_to_recipe)  // NOLINT
{
	SetupMockUnitConvertion();
	auto mockRecipe = std::make_shared<infas::fake::FileImpl>();
	auto frontend = std::make_shared<infas::fake::Frontend>();
	auto recipe = std::make_shared<common::Observable<std::optional<common::Recipe>>>();
	recipe->Set(std::make_optional<common::Recipe>(mockRecipe));

	auto subject = biz::AddRecipeUnit::Create();
	subject->SetReferences(frontend, recipe);

	subject->Execute();

	// TODO(andreas): Silent Contract? find better way to test this.
	ASSERT_NE(mockRecipe->myContent.find("Ingredients"), mockRecipe->myContent.end());
	EXPECT_GT(mockRecipe->myContent["Ingredients"].size(), 0);

	infas::IFileImpl::Clear();
}

TEST(AddRecipeUnit, unit_is_removed_from_recipe_by_memento)	 // NOLINT
{
	SetupMockUnitConvertion();
	auto mockRecipe = std::make_shared<infas::fake::FileImpl>();
	auto frontend = std::make_shared<infas::fake::Frontend>();
	auto recipe = std::make_shared<common::Observable<std::optional<common::Recipe>>>();
	recipe->Set(std::make_optional<common::Recipe>(mockRecipe));

	auto subject = biz::AddRecipeUnit::Create();
	subject->SetReferences(frontend, recipe);

	auto memento = subject->Execute();
	memento->Revert();

	ASSERT_NE(mockRecipe->myContent.find("Ingredients"), mockRecipe->myContent.end());
	EXPECT_EQ(mockRecipe->myContent["Ingredients"].size(), 0);

	infas::IFileImpl::Clear();
}

TEST(AddRecipeUnit, unit_is_readded_to_recipe_by_memento)  // NOLINT
{
	SetupMockUnitConvertion();
	auto mockRecipe = std::make_shared<infas::fake::FileImpl>();
	auto frontend = std::make_shared<infas::fake::Frontend>();
	auto recipe = std::make_shared<common::Observable<std::optional<common::Recipe>>>();
	recipe->Set(std::make_optional<common::Recipe>(mockRecipe));

	auto subject = biz::AddRecipeUnit::Create();
	subject->SetReferences(frontend, recipe);

	auto memento = subject->Execute();
	memento->Revert();
	memento->ReExecute();

	ASSERT_NE(mockRecipe->myContent.find("Ingredients"), mockRecipe->myContent.end());
	EXPECT_GT(mockRecipe->myContent["Ingredients"].size(), 0);

	infas::IFileImpl::Clear();
}
