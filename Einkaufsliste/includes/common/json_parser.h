#pragma once

#include "i_file_impl.h"

namespace common {
class JsonParser final : public IFileImpl
{
public:
	void Open(std::filesystem::path aPath) override;
	void Save() override;

	void AddToKey(std::filesystem::path aKey, std::string_view aValue) override;
	void RemoveFromKey(std::filesystem::path aKey, std::string_view aValue) override;
	void ClearField(std::filesystem::path aKey) override;

	std::vector<std::string_view> GetKey(std::filesystem::path aKey) override;
};
} // namespace common
