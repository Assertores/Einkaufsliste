#include "biz/open_week.h"

#include "interface/i_file_impl.h"

#include <gtest/gtest.h>

TEST(OpenWeek, week_is_opend)  // NOLINT
{
	auto frontend = std::make_shared<infas::fake::Frontend>();
	auto week = std::make_shared<common::Observable<std::optional<common::Week>>>();

	auto subject = biz::OpenWeek::Create();
	subject->SetReferences(frontend, week);

	subject->Execute();

	ASSERT_TRUE(week->Get().has_value());
	EXPECT_EQ(week->Get(), common::Week(infas::fake::Frontend::defaultFilePath));

	infas::IFileImpl::Clear();
}

TEST(OpenWeek, opening_a_week_can_not_be_undone)  // NOLINT
{
	auto frontend = std::make_shared<infas::fake::Frontend>();
	auto week = std::make_shared<common::Observable<std::optional<common::Week>>>();

	auto subject = biz::OpenWeek::Create();
	subject->SetReferences(frontend, week);

	auto memento = subject->Execute();

	infas::IFileImpl::Clear();

	EXPECT_EQ(memento, nullptr);
}
