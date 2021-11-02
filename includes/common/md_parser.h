#pragma once

#include "interface/i_file_impl.h"

#include <fstream>
#include <map>
#include <string>

namespace common {
class MdParser final : public infas::IFileImpl {
public:
	void Open(const std::filesystem::path& aPath) override;
	void Save() override;
	void Refresh() override;
	[[nodiscard]] std::filesystem::path GetPath() const override;

	void AddToKey(std::filesystem::path aKey, std::string_view aValue) override;
	void RemoveFromKey(std::filesystem::path aKey, std::string_view aValue) override;
	void ClearField(std::filesystem::path aKey) override;

	[[nodiscard]] std::vector<std::string> GetField(std::filesystem::path aKey) const override;
	[[nodiscard]] std::vector<std::filesystem::path> GetKeys(
		std::filesystem::path aKey) const override;

	void Parse(std::istream& aIn);
	void Serialize(std::ostream& aOut);

private:
	std::map<std::filesystem::path, std::vector<std::string>> myContent;
	std::filesystem::path myFile;
};
}  // namespace common
