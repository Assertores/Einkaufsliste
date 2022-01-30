#include "biz/remove_week_recipe.h"

#include "interface/i_file_impl.h"

#include <gtest/gtest.h>

TEST(RemoveWeekRecipe, recipe_is_removed_from_week) // NOLINT
{
	auto mockWeek = std::static_pointer_cast<infas::fake::FileImpl>(
		infas::IFileImpl::Open<infas::fake::FileImpl>("aubhfuke"));
	auto frontend = std::make_shared<infas::fake::Frontend>();
	auto week = std::make_shared<common::Observable<std::optional<common::Week>>>();
	week->Set(std::make_optional<common::Week>(mockWeek));
	common::Week(mockWeek).AddRecipe(
		common::Recipe(infas::fake::Frontend::defaultFilePath),
		infas::fake::Frontend::defaultWeekDay,
		infas::fake::Frontend::defaultDayTime);

	auto subject = biz::RemoveWeekRecipe::Create();
	subject->SetReferences(frontend, week);

	subject->Execute();

	infas::IFileImpl::Clear();

	EXPECT_LE(mockWeek->myContent.size(), 1);
}

TEST(RemoveWeekRecipe, recipe_is_readded_to_week_by_memento) // NOLINT
{
	auto mockWeek = std::static_pointer_cast<infas::fake::FileImpl>(
		infas::IFileImpl::Open<infas::fake::FileImpl>("aubhfuke"));
	auto frontend = std::make_shared<infas::fake::Frontend>();
	auto week = std::make_shared<common::Observable<std::optional<common::Week>>>();
	week->Set(std::make_optional<common::Week>(mockWeek));
	common::Week(mockWeek).AddRecipe(
		common::Recipe(infas::fake::Frontend::defaultFilePath),
		infas::fake::Frontend::defaultWeekDay,
		infas::fake::Frontend::defaultDayTime);

	auto subject = biz::RemoveWeekRecipe::Create();
	subject->SetReferences(frontend, week);

	auto memento = subject->Execute();
	memento->Revert();

	EXPECT_GT(mockWeek->myContent.size(), 1);
	const auto result = common::Week(mockWeek).GetRecipe(
		infas::fake::Frontend::defaultWeekDay,
		infas::fake::Frontend::defaultDayTime);
	EXPECT_EQ(result, common::Recipe(infas::fake::Frontend::defaultFilePath));

	infas::IFileImpl::Clear();
}

TEST(RemoveWeekRecipe, recipe_is_removed_again_from_week_by_memento) // NOLINT
{
	auto mockWeek = std::static_pointer_cast<infas::fake::FileImpl>(
		infas::IFileImpl::Open<infas::fake::FileImpl>("aubhfuke"));
	auto frontend = std::make_shared<infas::fake::Frontend>();
	auto week = std::make_shared<common::Observable<std::optional<common::Week>>>();
	week->Set(std::make_optional<common::Week>(mockWeek));
	common::Week(mockWeek).AddRecipe(
		common::Recipe(infas::fake::Frontend::defaultFilePath),
		infas::fake::Frontend::defaultWeekDay,
		infas::fake::Frontend::defaultDayTime);

	auto subject = biz::RemoveWeekRecipe::Create();
	subject->SetReferences(frontend, week);

	auto memento = subject->Execute();
	memento->Revert();
	memento->ReExecute();

	infas::IFileImpl::Clear();

	EXPECT_LE(mockWeek->myContent.size(), 1);
}
