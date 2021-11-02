#pragma once

#include "interface/i_file.h"

#include <string>
#include <string_view>

namespace common {
class UnitConvertion : public infas::IFile {
public:
	explicit UnitConvertion(const std::filesystem::path& aPath)
		: IFile(aPath){};
	explicit UnitConvertion(std::shared_ptr<infas::IFileImpl> aFileImpl)
		: IFile(std::move(aFileImpl)){};

	[[nodiscard]] std::string Print() const override;

	[[nodiscard]] bool CanConvertUnit(std::string_view aUnit) const;
	// returns wether or not it was able to convert. out parameter is only set if successfull.
	bool GetConvertionRate(std::string_view aCurrentUnit, float& aOutConvertionRate) const;
	void SetConvertionRate(std::string_view aUnit, float aConvertionRate);
	std::string GetBestUnit(float aBaseUnitAmount, float& aOutConvertedAmount) const;
};
}  // namespace common
