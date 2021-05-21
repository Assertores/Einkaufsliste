#pragma once

#include "interface/i_file_impl.h"

namespace common {
class JsonParser final : public interface::IFileImpl
{
public:
	void Open(const std::filesystem::path& aPath) override;
	void Save() override;
	void Refresh() override;

	void AddToKey(std::filesystem::path aKey, std::string_view aValue) override;
	void RemoveFromKey(std::filesystem::path aKey, std::string_view aValue) override;
	void ClearField(std::filesystem::path aKey) override;

	std::vector<std::string_view> GetKey(std::filesystem::path aKey) override;
	std::vector<std::filesystem::path> GetKeys(std::filesystem::path aKey) override;
};
} // namespace common
