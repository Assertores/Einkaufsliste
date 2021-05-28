#pragma once

#include <filesystem>
#include <memory>
#include <string_view>
#include <vector>

namespace interface {
class IFileImpl;

class IFile
{
public:
	IFile(const std::filesystem::path& aPath);
	IFile(std::shared_ptr<IFileImpl> aFileImpl)
		: myFileImplimentation(aFileImpl) {};
	virtual ~IFile();

protected:
	bool FieldIsArray(const std::filesystem::path& aKey) const;

	void WriteField(const std::filesystem::path& aKey, std::string_view aValue);
	std::string ReadFromField(const std::filesystem::path& aKey) const;

	void AddToField(const std::filesystem::path& aKey, const std::vector<std::string_view>& aValue);
	void
	RemoveFromField(const std::filesystem::path& aKey, const std::vector<std::string_view>& aValue);
	std::vector<std::string> ReadAllFromField(const std::filesystem::path& aKey) const;
	std::vector<std::filesystem::path> GetSubKeys(const std::filesystem::path& aRoot) const;

private:
	std::shared_ptr<IFileImpl> myFileImplimentation;
};
} // namespace interface
