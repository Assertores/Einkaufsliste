#include "common/unit.h"

#include <gtest/gtest.h>

#include "common/unit_convertion.h"
#include "interface/i_file_impl.h"

TEST(Unit, parses_it_correctly) // NOLINT
{
	auto mockingFileImpl = std::make_shared<interface::fake::FileImpl>();
	mockingFileImpl->getField = [](auto /*unused*/) {
		return std::vector<std::string> { "1" };
	};
	mockingFileImpl->getKeys = [](auto /*unused*/) {
		return std::vector<std::filesystem::path> { "kg" };
	};
	common::UnitConvertion convertion(mockingFileImpl);
	common::Unit subject1(1, "apple", "kg", convertion);
	common::Unit subject2(3, "apple", "kg", convertion);

	auto result = common::Unit::ToString(std::vector<common::Unit> { subject1, subject2 });

	EXPECT_EQ(result, "apple 1kg & 3kg");
}

TEST(Unit, different_types_are_not_parsed) // NOLINT
{
	auto mockingFileImpl = std::make_shared<interface::fake::FileImpl>();
	mockingFileImpl->getField = [](auto /*unused*/) {
		return std::vector<std::string> { "1" };
	};
	mockingFileImpl->getKeys = [](auto /*unused*/) {
		return std::vector<std::filesystem::path> { "kg" };
	};
	common::UnitConvertion convertion(mockingFileImpl);
	common::Unit subject1(1, "apple", "kg", convertion);
	common::Unit subject2(3, "banana", "kg", convertion);

	auto result = common::Unit::ToString(std::vector<common::Unit> { subject1, subject2 });

	EXPECT_EQ(result, "");
}

TEST(Unit, same_types_can_be_added_together) // NOLINT
{
	auto mockingFileImpl = std::make_shared<interface::fake::FileImpl>();
	mockingFileImpl->getField = [](auto /*unused*/) {
		return std::vector<std::string> { "1" };
	};
	mockingFileImpl->getKeys = [](auto /*unused*/) {
		return std::vector<std::filesystem::path> { "kg" };
	};
	common::UnitConvertion convertion(mockingFileImpl);
	common::Unit subject1(1, "apple", "kg", convertion);
	common::Unit subject2(3, "apple", "kg", convertion);

	ASSERT_TRUE(subject1.Add(subject2));
	auto result = common::Unit::ToString(std::vector<common::Unit> { subject1 });

	EXPECT_EQ(result, "apple 4kg");
}

TEST(Unit, different_types_can_not_be_added_together) // NOLINT
{
	auto mockingFileImpl = std::make_shared<interface::fake::FileImpl>();
	mockingFileImpl->getField = [](auto /*unused*/) {
		return std::vector<std::string> { "1" };
	};
	mockingFileImpl->getKeys = [](auto /*unused*/) {
		return std::vector<std::filesystem::path> { "kg" };
	};
	common::UnitConvertion convertion(mockingFileImpl);
	common::Unit subject1(1, "apple", "kg", convertion);
	common::Unit subject2(3, "banana", "kg", convertion);

	ASSERT_FALSE(subject1.Add(subject2));
	auto result = common::Unit::ToString(std::vector<common::Unit> { subject1 });

	EXPECT_EQ(result, "apple 1kg");
}

TEST(Unit, type_can_be_deduced_from_string) // NOLINT
{
	auto subject = common::Unit::ResultsInUnitsOfType("apple 1kg & 3kg");
	EXPECT_EQ(subject, "apple");
}

TEST(Unit, parses_string_into_units) // NOLINT
{
	auto mockingFileImpl = std::make_shared<interface::fake::FileImpl>();
	mockingFileImpl->getField = [](auto /*unused*/) {
		return std::vector<std::string> { "1" };
	};
	mockingFileImpl->getKeys = [](auto /*unused*/) {
		return std::vector<std::filesystem::path> { "kg" };
	};
	common::UnitConvertion convertion(mockingFileImpl);
	common::Unit::SetConvertionFiles({ convertion });
	auto subject = common::Unit::FromString("apple 1kg & 3kg");

	ASSERT_EQ(subject.size(), 2);
	EXPECT_TRUE(subject[0].Equals(common::Unit(1, "apple", "kg", convertion)));
	EXPECT_TRUE(subject[1].Equals(common::Unit(3, "apple", "kg", convertion)));
}
