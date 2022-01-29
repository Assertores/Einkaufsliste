#include "biz/remove_recipe_unit.h"

#include "interface/i_file_impl.h"

#include <gtest/gtest.h>

// TODO(andreas): remove this after Convertion rework
namespace {
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
}  // namespace

TEST(RemoveRecipeUnit, unit_is_removed_from_recipe)  // NOLINT
{
	SetupMockUnitConvertion();

	auto mockRecipe = std::static_pointer_cast<infas::fake::FileImpl>(infas::IFileImpl::Open<infas::fake::FileImpl>("aubhfuke"));
	auto frontend = std::make_shared<infas::fake::Frontend>();
	auto recipe = std::make_shared<common::Observable<std::optional<common::Recipe>>>();
	recipe->Set(std::make_optional<common::Recipe>(mockRecipe));
	common::Recipe(mockRecipe).AddIngredient(infas::fake::Frontend::DefaultUnion());

	auto subject = biz::RemoveRecipeUnit::Create();
	subject->SetReferences(frontend, recipe);

	subject->Execute();

	infas::IFileImpl::Clear();

	// TODO(andreas): Silent Contract? find better way to test this.
	ASSERT_NE(mockRecipe->myContent.find("Ingredients"), mockRecipe->myContent.end());
	EXPECT_EQ(mockRecipe->myContent["Ingredients"].size(), 0);
}

TEST(RemoveRecipeUnit, unit_is_readded_to_recipe_by_memento)	 // NOLINT
{
	SetupMockUnitConvertion();

	auto mockRecipe = std::static_pointer_cast<infas::fake::FileImpl>(infas::IFileImpl::Open<infas::fake::FileImpl>("aubhfuke"));
	auto frontend = std::make_shared<infas::fake::Frontend>();
	auto recipe = std::make_shared<common::Observable<std::optional<common::Recipe>>>();
	recipe->Set(std::make_optional<common::Recipe>(mockRecipe));
	common::Recipe(mockRecipe).AddIngredient(infas::fake::Frontend::DefaultUnion());

	auto subject = biz::RemoveRecipeUnit::Create();
	subject->SetReferences(frontend, recipe);

	auto memento = subject->Execute();
	memento->Revert();

	infas::IFileImpl::Clear();

	ASSERT_NE(mockRecipe->myContent.find("Ingredients"), mockRecipe->myContent.end());
	EXPECT_GT(mockRecipe->myContent["Ingredients"].size(), 0);
}

TEST(RemoveRecipeUnit, unit_is_removed_again_from_recipe_by_memento)  // NOLINT
{
	SetupMockUnitConvertion();

	auto mockRecipe = std::static_pointer_cast<infas::fake::FileImpl>(infas::IFileImpl::Open<infas::fake::FileImpl>("aubhfuke"));
	auto frontend = std::make_shared<infas::fake::Frontend>();
	auto recipe = std::make_shared<common::Observable<std::optional<common::Recipe>>>();
	recipe->Set(std::make_optional<common::Recipe>(mockRecipe));
	common::Recipe(mockRecipe).AddIngredient(infas::fake::Frontend::DefaultUnion());

	auto subject = biz::RemoveRecipeUnit::Create();
	subject->SetReferences(frontend, recipe);

	auto memento = subject->Execute();
	memento->Revert();
	memento->ReExecute();

	infas::IFileImpl::Clear();

	ASSERT_NE(mockRecipe->myContent.find("Ingredients"), mockRecipe->myContent.end());
	EXPECT_EQ(mockRecipe->myContent["Ingredients"].size(), 0);
}
