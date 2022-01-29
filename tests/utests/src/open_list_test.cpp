#include "biz/open_list.h"

#include "interface/i_file_impl.h"

#include <gtest/gtest.h>

TEST(OpenList, list_is_opend)  // NOLINT
{
	auto frontend = std::make_shared<infas::fake::Frontend>();
	auto list = std::make_shared<common::Observable<std::optional<common::List>>>();

	auto subject = biz::OpenList::Create();
	subject->SetReferences(frontend, list);

	subject->Execute();

	ASSERT_TRUE(list->Get().has_value());
	EXPECT_EQ(list->Get(), common::List(infas::fake::Frontend::defaultFilePath));

	infas::IFileImpl::Clear();
}

TEST(OpenList, opening_a_list_can_not_be_undone)  // NOLINT
{
	auto frontend = std::make_shared<infas::fake::Frontend>();
	auto list = std::make_shared<common::Observable<std::optional<common::List>>>();

	auto subject = biz::OpenList::Create();
	subject->SetReferences(frontend, list);

	auto memento = subject->Execute();

	infas::IFileImpl::Clear();

	EXPECT_EQ(memento, nullptr);
}
