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
	IFile(std::filesystem::path aPath);
	~IFile();

protected:
	bool FieldIsArray(std::filesystem::path aKey);

	void WriteField(std::filesystem::path aKey, std::string_view aValue);
	std::string_view ReadFromField(std::filesystem::path aKey);

	void AddToField(std::filesystem::path aKey, std::vector<std::string_view> aValue);
	void RemoveFromField(std::filesystem::path aKey, std::vector<std::string_view> aValue);
	std::vector<std::string_view> ReadAllFromField(std::filesystem::path aKey);

private:
	std::shared_ptr<IFileImpl> myFileImplimentation;
};
} // namespace common
