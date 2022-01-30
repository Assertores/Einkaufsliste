#include "biz/add_week_recipe.h"

#include "interface/i_file_impl.h"

#include <gtest/gtest.h>

TEST(AddWeekRecipe, file_is_added_to_week) // NOLINT
{
	auto mockWeek = std::static_pointer_cast<infas::fake::FileImpl>(
		infas::IFileImpl::Open<infas::fake::FileImpl>("aubhfuke"));
	auto frontend = std::make_shared<infas::fake::Frontend>();
	auto week = std::make_shared<common::Observable<std::optional<common::Week>>>();
	week->Set(std::make_optional<common::Week>(mockWeek));

	auto subject = biz::AddWeekRecipe::Create();
	subject->SetReferences(frontend, week);

	subject->Execute();

	infas::IFileImpl::Clear();

	bool containsFile = false;
	for (const auto& it : mockWeek->myContent) {
		if (std::find(it.second.begin(), it.second.end(), infas::fake::Frontend::defaultFilePath)
			!= it.second.end()) {
			containsFile = true;
			break;
		}
	}
	EXPECT_TRUE(containsFile);
}

TEST(AddWeekRecipe, file_is_removed_from_week_by_memento) // NOLINT
{
	auto mockWeek = std::static_pointer_cast<infas::fake::FileImpl>(
		infas::IFileImpl::Open<infas::fake::FileImpl>("aubhfuke"));
	auto frontend = std::make_shared<infas::fake::Frontend>();
	auto week = std::make_shared<common::Observable<std::optional<common::Week>>>();
	week->Set(std::make_optional<common::Week>(mockWeek));

	auto subject = biz::AddWeekRecipe::Create();
	subject->SetReferences(frontend, week);

	auto memento = subject->Execute();
	memento->Revert();

	infas::IFileImpl::Clear();

	bool containsFile = false;
	for (const auto& it : mockWeek->myContent) {
		if (std::find(it.second.begin(), it.second.end(), infas::fake::Frontend::defaultFilePath)
			!= it.second.end()) {
			containsFile = true;
			break;
		}
	}
	EXPECT_FALSE(containsFile);
}

TEST(AddWeekRecipe, file_is_readded_to_week_by_memento) // NOLINT
{
	auto mockWeek = std::static_pointer_cast<infas::fake::FileImpl>(
		infas::IFileImpl::Open<infas::fake::FileImpl>("aubhfuke"));
	auto frontend = std::make_shared<infas::fake::Frontend>();
	auto week = std::make_shared<common::Observable<std::optional<common::Week>>>();
	week->Set(std::make_optional<common::Week>(mockWeek));

	auto subject = biz::AddWeekRecipe::Create();
	subject->SetReferences(frontend, week);

	auto memento = subject->Execute();
	memento->Revert();
	memento->ReExecute();

	infas::IFileImpl::Clear();

	bool containsFile = false;
	for (const auto& it : mockWeek->myContent) {
		if (std::find(it.second.begin(), it.second.end(), infas::fake::Frontend::defaultFilePath)
			!= it.second.end()) {
			containsFile = true;
			break;
		}
	}
	EXPECT_TRUE(containsFile);
}
