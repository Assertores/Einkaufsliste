#pragma once

#include <filesystem>
#include <functional>
#include <map>
#include <string_view>
#include <utility>
#include <vector>

static constexpr auto locVersionKey = "version";
static constexpr auto locVersion = "0.0.0";

namespace infas {
class IFileImpl {
public:
	template <typename Impl, typename = std::enable_if_t<std::is_base_of_v<IFileImpl, Impl>>>
	static std::shared_ptr<IFileImpl> Open(const std::filesystem::path& aPath);
	static void Clear() { myFiles.clear(); }

	virtual ~IFileImpl() = default;

	virtual void Open(const std::filesystem::path& aPath) = 0;
	virtual void Save() = 0;
	virtual void Refresh() = 0;
	[[nodiscard]] virtual std::filesystem::path GetPath() const = 0;

	virtual void AddToKey(std::filesystem::path aKey, std::string_view aValue) = 0;
	virtual void RemoveFromKey(std::filesystem::path aKey, std::string_view aValue) = 0;
	virtual void ClearField(std::filesystem::path aKey) = 0;

	[[nodiscard]] virtual std::vector<std::string> GetField(std::filesystem::path aKey) const = 0;
	[[nodiscard]] virtual std::vector<std::filesystem::path> GetKeys(
		std::filesystem::path aKey) const = 0;

private:
	static std::map<std::filesystem::path, std::shared_ptr<IFileImpl>> myFiles;
};

namespace fake {
class FileImpl : public IFileImpl {
public:
	std::function<void(const std::filesystem::path&)> open = [this](auto aPath) {
		openCount++;
		myPath = aPath;
	};
	std::function<void()> save = [this]() { saveCount++; };
	std::function<void()> refresh = [this]() { refreshCount++; };
	std::function<std::filesystem::path()> getPath = [this]() {
		getPathCount++;
		return myPath;
	};
	std::function<void(std::filesystem::path, std::string_view)> addToKey =
		[this](auto aKey, auto aValue) {
			addToKeyCount++;
			myContent[aKey].emplace_back(aValue);
		};
	std::function<void(std::filesystem::path, std::string_view)> removeFromKey = [this](
																					 auto aKey,
																					 auto aValue) {
		removeFromKeyCount++;
		myContent[aKey].erase(std::find(myContent[aKey].begin(), myContent[aKey].end(), aValue));
	};
	std::function<void(std::filesystem::path)> clearField = [this](auto aKey) {
		myContent.erase(aKey);
		clearFieldCount++;
	};
	std::function<std::vector<std::string>(std::filesystem::path)> getField = [this](auto aKey) {
		getFieldCount++;
		auto tmp = myContent.find(aKey);
		return tmp == myContent.end() ? std::vector<std::string>{} : tmp->second;
	};
	std::function<std::vector<std::filesystem::path>(std::filesystem::path)> getKeys =
		[this](auto aKey) {
			getKeysCount++;
			std::vector<std::filesystem::path> result;
			for (const auto& it : myContent) {
				auto relPath = it.first.lexically_relative(aKey);
				if (relPath != "."
					&& *relPath.begin()
						   != "..") // NOLINT TODO(andreas): check if key is a parent path
				{
					result.push_back(it.first);
				}
			}
			return result;
		};

	void Open(const std::filesystem::path& aPath) override { open(aPath); }
	void Save() override { save(); }
	void Refresh() override { refresh(); }
	[[nodiscard]] std::filesystem::path GetPath() const override { return getPath(); }
	void AddToKey(std::filesystem::path aKey, std::string_view aValue) override {
		addToKey(aKey, aValue);
	}
	void RemoveFromKey(std::filesystem::path aKey, std::string_view aValue) override {
		removeFromKey(aKey, aValue);
	}
	void ClearField(std::filesystem::path aKey) override { clearField(aKey); }
	[[nodiscard]] std::vector<std::string> GetField(std::filesystem::path aKey) const override {
		return getField(aKey);
	}
	[[nodiscard]] std::vector<std::filesystem::path> GetKeys(
		std::filesystem::path aKey) const override {
		return getKeys(aKey);
	};

	int openCount = 0;
	int saveCount = 0;
	int refreshCount = 0;
	int getPathCount = 0;
	int addToKeyCount = 0;
	int removeFromKeyCount = 0;
	int clearFieldCount = 0;
	int getFieldCount = 0;
	int getKeysCount = 0;

	std::map<std::filesystem::path, std::vector<std::string>> myContent;
	std::filesystem::path myPath;
};
} // namespace fake

template <typename Impl, typename>
std::shared_ptr<IFileImpl>
IFileImpl::Open(const std::filesystem::path& aPath) {
	auto it = myFiles.find(aPath);
	if (it != myFiles.end()) {
		return it->second;
	}
	auto file = std::make_shared<Impl>();
	myFiles[aPath] = file;
	file->Open(aPath);
	const auto keys = file->GetKeys("");
	if (std::find(keys.begin(), keys.end(), locVersionKey) == keys.end()) {
		file->AddToKey(locVersionKey, locVersion);
	}
	return file;
}
} // namespace infas
