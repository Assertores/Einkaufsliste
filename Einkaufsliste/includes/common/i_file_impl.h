#pragma once

#include <filesystem>
#include <map>
#include <string_view>
#include <utility>
#include <vector>

namespace common {
class IFileImpl
{
public:
	template <typename Impl, typename = std::enable_if_t<std::is_base_of_v<IFileImpl, Impl>>>
	static std::shared_ptr<IFileImpl> Open(std::filesystem::path aPath);
	virtual void Open(std::filesystem::path aPath);
	virtual void Save() = 0;
	virtual void Refresh() = 0;

	virtual void AddToKey(std::filesystem::path aKey, std::string_view aValue) = 0;
	virtual void RemoveFromKey(std::filesystem::path aKey, std::string_view aValue) = 0;
	virtual void ClearField(std::filesystem::path aKey) = 0;

	virtual std::vector<std::string_view> GetKey(std::filesystem::path aKey) = 0;

private:
	std::map<std::filesystem::path, std::shared_ptr<IFileImpl>> myFiles;
};

template <typename Impl, typename>
std::shared_ptr<IFileImpl>
IFileImpl::Open(std::filesystem::path aPath)
{
	auto it = myFiles.find(aPath);
	if (it != myFiles.end())
	{
		return it->second;
	}
	auto file = std::make_shared<Impl>();
	myFiles[aPath] = file;
	file->Open(aPath);
	return std::move(file);
}
} // namespace common
