#include "biz/add_list_recipe.h"

#include "interface/i_file_impl.h"

#include <gtest/gtest.h>

TEST(AddListRecipe, file_is_added_to_list)	// NOLINT
{
	auto mockList = std::static_pointer_cast<infas::fake::FileImpl>(
		infas::IFileImpl::Open<infas::fake::FileImpl>("aubhfuke"));
	auto frontend = std::make_shared<infas::fake::Frontend>();
	auto list = std::make_shared<common::Observable<std::optional<common::List>>>();
	list->Set(std::make_optional<common::List>(mockList));

	auto subject = biz::AddListRecipe::Create();
	subject->SetReferences(frontend, list);

	subject->Execute();

	infas::IFileImpl::Clear();

	bool containsFile = false;
	for (const auto& it : mockList->myContent) {
		if (std::find(it.second.begin(), it.second.end(), infas::fake::Frontend::defaultFilePath)
			!= it.second.end()) {
			containsFile = true;
			break;
		}
	}
	EXPECT_TRUE(containsFile);
}

TEST(AddListRecipe, adding_file_to_list_can_not_be_undone)	// NOLINT
{
	auto mockList = std::static_pointer_cast<infas::fake::FileImpl>(
		infas::IFileImpl::Open<infas::fake::FileImpl>("aubhfuke"));
	auto frontend = std::make_shared<infas::fake::Frontend>();
	auto list = std::make_shared<common::Observable<std::optional<common::List>>>();
	list->Set(std::make_optional<common::List>(mockList));

	auto subject = biz::AddListRecipe::Create();
	subject->SetReferences(frontend, list);

	auto memento = subject->Execute();

	infas::IFileImpl::Clear();

	EXPECT_EQ(memento, nullptr);
}

TEST(AddListRecipe, file_is_removed_from_list_by_memento)  // NOLINT
{
	GTEST_SKIP();
	auto mockList = std::static_pointer_cast<infas::fake::FileImpl>(
		infas::IFileImpl::Open<infas::fake::FileImpl>("aubhfuke"));
	auto frontend = std::make_shared<infas::fake::Frontend>();
	auto list = std::make_shared<common::Observable<std::optional<common::List>>>();
	list->Set(std::make_optional<common::List>(mockList));

	auto subject = biz::AddListRecipe::Create();
	subject->SetReferences(frontend, list);

	auto memento = subject->Execute();
	memento->Revert();

	infas::IFileImpl::Clear();

	bool containsFile = false;
	for (const auto& it : mockList->myContent) {
		if (std::find(it.second.begin(), it.second.end(), infas::fake::Frontend::defaultFilePath)
			!= it.second.end()) {
			containsFile = true;
			break;
		}
	}
	EXPECT_FALSE(containsFile);
}

TEST(AddListRecipe, file_is_readded_to_list_by_memento)	 // NOLINT
{
	GTEST_SKIP();
	auto mockList = std::static_pointer_cast<infas::fake::FileImpl>(
		infas::IFileImpl::Open<infas::fake::FileImpl>("aubhfuke"));
	auto frontend = std::make_shared<infas::fake::Frontend>();
	auto list = std::make_shared<common::Observable<std::optional<common::List>>>();
	list->Set(std::make_optional<common::List>(mockList));

	auto subject = biz::AddListRecipe::Create();
	subject->SetReferences(frontend, list);

	auto memento = subject->Execute();
	memento->Revert();
	memento->ReExecute();

	infas::IFileImpl::Clear();

	bool containsFile = false;
	for (const auto& it : mockList->myContent) {
		if (std::find(it.second.begin(), it.second.end(), infas::fake::Frontend::defaultFilePath)
			!= it.second.end()) {
			containsFile = true;
			break;
		}
	}
	EXPECT_TRUE(containsFile);
}
