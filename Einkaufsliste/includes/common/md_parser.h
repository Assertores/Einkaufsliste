#pragma once

#include <map>
#include <string>
#include <fstream>

#include "i_file_impl.h"

namespace common {
class MdParser final : public IFileImpl
{
public:
	void Open(const std::filesystem::path& aPath) override;
	void Save() override;
	void Refresh() override;

	void AddToKey(std::filesystem::path aKey, std::string_view aValue) override;
	void RemoveFromKey(std::filesystem::path aKey, std::string_view aValue) override;
	void ClearField(std::filesystem::path aKey) override;

	std::vector<std::string_view> GetKey(std::filesystem::path aKey) override;

private:
	std::map<std::filesystem::path, std::vector<std::string>> myContent;
	std::ofstream myFile;
};
} // namespace common
