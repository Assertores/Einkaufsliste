#include <gtest/gtest.h>

#include "interface/i_file_impl.h"

class FileImplMock : public interface::IFileImpl
{
public:
	void Open(const std::filesystem::path& aPath) override { openWasCalled = true; }
	void Save() override {}
	void Refresh() override {}
	void AddToKey(std::filesystem::path aKey, std::string_view aValue) override {}
	void RemoveFromKey(std::filesystem::path aKey, std::string_view aValue) override {}
	void ClearField(std::filesystem::path aKey) override {}
	std::vector<std::string_view> GetKey(std::filesystem::path aKey) override
	{
		return std::vector<std::string_view>();
	}

	bool openWasCalled = false;
};

TEST(FileImpl, opening_same_file_twice_returns_cashed_instance) // NOLINT
{
	auto subject1 = interface::IFileImpl::Open<FileImplMock>("some/path");
	auto subject2 = interface::IFileImpl::Open<FileImplMock>("some/path");

	EXPECT_EQ(subject1, subject2);

	interface::IFileImpl::Clear();
}

TEST(FileImpl, opening_different_file_returns_different_instance) // NOLINT
{
	auto subject1 = interface::IFileImpl::Open<FileImplMock>("some/path");
	auto subject2 = interface::IFileImpl::Open<FileImplMock>("some/different/path");

	EXPECT_NE(subject1, subject2);

	interface::IFileImpl::Clear();
}

TEST(FileImpl, opening_calls_open_funktion_on_instance) // NOLINT
{
	auto subject = interface::IFileImpl::Open<FileImplMock>("some/path");

	EXPECT_TRUE(dynamic_cast<FileImplMock*>(subject.get())->openWasCalled);

	interface::IFileImpl::Clear();
}
