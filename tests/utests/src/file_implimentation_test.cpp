#include "interface/i_file_impl.h"

#include <gtest/gtest.h>

TEST(FileImpl, opening_same_file_twice_returns_cashed_instance)	 // NOLINT
{
	auto subject1 = interface::IFileImpl::Open<interface::fake::FileImpl>("some/path");
	auto subject2 = interface::IFileImpl::Open<interface::fake::FileImpl>("some/path");

	EXPECT_EQ(subject1, subject2);

	interface::IFileImpl::Clear();
}

TEST(FileImpl, opening_different_file_returns_different_instance)  // NOLINT
{
	auto subject1 = interface::IFileImpl::Open<interface::fake::FileImpl>("some/path");
	auto subject2 = interface::IFileImpl::Open<interface::fake::FileImpl>("some/different/path");

	EXPECT_NE(subject1, subject2);

	interface::IFileImpl::Clear();
}

TEST(FileImpl, opening_calls_open_funktion_on_instance)	 // NOLINT
{
	auto subject = interface::IFileImpl::Open<interface::fake::FileImpl>("some/path");

	EXPECT_TRUE(dynamic_cast<interface::fake::FileImpl*>(subject.get())->openCount);

	interface::IFileImpl::Clear();
}
