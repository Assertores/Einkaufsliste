#pragma once

#include <filesystem>
#include <functional>
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

namespace fake {
class FileImpl : public IFileImpl
{
public:
	std::function<void(const std::filesystem::path&)> open = [this](auto /*unused*/) {
		openCount++;
	};
	std::function<void()> save = [this]() {
		saveCount++;
	};
	std::function<void()> refresh = [this]() {
		refreshCount++;
	};
	std::function<void(std::filesystem::path, std::string_view)> addToKey =
		[this](auto /*unused*/, auto /*unused*/) {
			addToKeyCount++;
		};
	std::function<void(std::filesystem::path, std::string_view)> removeFromKey =
		[this](auto /*unused*/, auto /*unused*/) {
			removeFromKeyCount++;
		};
	std::function<void(std::filesystem::path)> clearField = [this](auto /*unused*/) {
		clearFieldCount++;
	};
	std::function<std::vector<std::string>(std::filesystem::path)> getField =
		[this](auto /*unused*/) {
			getFieldCount++;
			return std::vector<std::string>();
		};
	std::function<std::vector<std::filesystem::path>(std::filesystem::path)> getKeys =
		[this](auto /*unused*/) {
			getKeysCount++;
			return std::vector<std::filesystem::path>();
		};

	void Open(const std::filesystem::path& aPath) override { open(aPath); }
	void Save() override { save(); }
	void Refresh() override { refresh(); }
	void AddToKey(std::filesystem::path aKey, std::string_view aValue) override
	{
		addToKey(aKey, aValue);
	}
	void RemoveFromKey(std::filesystem::path aKey, std::string_view aValue) override
	{
		removeFromKey(aKey, aValue);
	}
	void ClearField(std::filesystem::path aKey) override { clearField(aKey); }
	std::vector<std::string> GetField(std::filesystem::path aKey) const override
	{
		return getField(aKey);
	}
	std::vector<std::filesystem::path> GetKeys(std::filesystem::path aKey) const override
	{
		return getKeys(aKey);
	};

	int openCount = 0;
	int saveCount = 0;
	int refreshCount = 0;
	int addToKeyCount = 0;
	int removeFromKeyCount = 0;
	int clearFieldCount = 0;
	int getFieldCount = 0;
	int getKeysCount = 0;
};
} // namespace fake

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
