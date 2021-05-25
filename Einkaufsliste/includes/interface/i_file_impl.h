#pragma once

#include <filesystem>
#include <map>
#include <string_view>
#include <utility>
#include <vector>

namespace interface {
class IFileImpl
{
public:
	template <typename Impl, typename = std::enable_if_t<std::is_base_of_v<IFileImpl, Impl>>>
	static std::shared_ptr<IFileImpl> Open(const std::filesystem::path& aPath);
	static void Clear() { myFiles.clear(); }

	virtual ~IFileImpl() = default;

	virtual void Open(const std::filesystem::path& aPath) = 0;
	virtual void Save() = 0;
	virtual void Refresh() = 0;

	virtual void AddToKey(std::filesystem::path aKey, std::string_view aValue) = 0;
	virtual void RemoveFromKey(std::filesystem::path aKey, std::string_view aValue) = 0;
	virtual void ClearField(std::filesystem::path aKey) = 0;

	virtual std::vector<std::string> GetField(std::filesystem::path aKey) const = 0;
	virtual std::vector<std::filesystem::path> GetKeys(std::filesystem::path aKey) const = 0;

private:
	static std::map<std::filesystem::path, std::shared_ptr<IFileImpl>> myFiles;
};

template <typename Impl, typename>
std::shared_ptr<IFileImpl>
IFileImpl::Open(const std::filesystem::path& aPath)
{
	auto it = myFiles.find(aPath);
	if (it != myFiles.end())
	{
		return it->second;
	}
	auto file = std::make_shared<Impl>();
	myFiles[aPath] = file;
	file->Open(aPath);
	return file;
}
} // namespace interface
