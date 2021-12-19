#pragma once

#include "interface/i_file.h"

#include <string>
#include <string_view>

namespace common {
class UnitConversion : public infas::IFile {
public:
	explicit UnitConversion(const std::filesystem::path& aPath)
		: IFile(aPath){};
	explicit UnitConversion(std::shared_ptr<infas::IFileImpl> aFileImpl)
		: IFile(std::move(aFileImpl)){};

	[[nodiscard]] std::string Print() const override;

	[[nodiscard]] bool CanConvertUnit(std::string_view aUnit) const;
	// returns wether or not it was able to convert. out parameter is only set if successfull.
	bool GetConversionRate(std::string_view aCurrentUnit, float& aOutConversionRate) const;
	void SetConversionRate(std::string_view aUnit, float aConversionRate);
	std::string GetBestUnit(float aBaseUnitAmount, float& aOutConvertedAmount) const;
};
}  // namespace common

