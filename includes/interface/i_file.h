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
	explicit IFile(const std::filesystem::path& aPath);
	explicit IFile(std::shared_ptr<IFileImpl> aFileImpl)
		: myFileImplimentation(std::move(aFileImpl)) {};

	IFile(const IFile&) = default;
	IFile(IFile&&) = default;
	IFile& operator=(const IFile&) = default;
	IFile& operator=(IFile&&) = default;

	virtual ~IFile();

	friend bool operator==(const IFile& aLhs, const IFile& aRhs)
	{
		return aLhs.myFileImplimentation == aRhs.myFileImplimentation;
	}
	friend bool operator!=(const IFile& aLhs, const IFile& aRhs)
	{
		return aLhs.myFileImplimentation != aRhs.myFileImplimentation;
	}

	[[nodiscard]] virtual std::string Print() const = 0;

protected:
	[[nodiscard]] bool FieldIsArray(const std::filesystem::path& aKey) const;

	void WriteField(const std::filesystem::path& aKey, std::string_view aValue);
	[[nodiscard]] std::string ReadFromField(const std::filesystem::path& aKey) const;

	void AddToField(const std::filesystem::path& aKey, const std::vector<std::string_view>& aValue);
	void
	RemoveFromField(const std::filesystem::path& aKey, const std::vector<std::string_view>& aValue);
	[[nodiscard]] std::vector<std::string>
	ReadAllFromField(const std::filesystem::path& aKey) const;
	[[nodiscard]] std::vector<std::filesystem::path>
	GetSubKeys(const std::filesystem::path& aRoot) const;

private:
	std::shared_ptr<IFileImpl> myFileImplimentation;
};
} // namespace interface
