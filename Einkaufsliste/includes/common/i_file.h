#pragma once

#include <filesystem>
#include <memory>
#include <string_view>
#include <vector>

namespace common {
class IFileImpl;

class IFile
{
public:
	IFile(const std::filesystem::path& aPath);
	~IFile();

protected:
	bool FieldIsArray(const std::filesystem::path& aKey);

	void WriteField(const std::filesystem::path& aKey, std::string_view aValue);
	std::string_view ReadFromField(const std::filesystem::path& aKey);

	void AddToField(const std::filesystem::path& aKey, const std::vector<std::string_view>& aValue);
	void
	RemoveFromField(const std::filesystem::path& aKey, const std::vector<std::string_view>& aValue);
	std::vector<std::string_view> ReadAllFromField(const std::filesystem::path& aKey);

private:
	std::shared_ptr<IFileImpl> myFileImplimentation;
};
} // namespace common
