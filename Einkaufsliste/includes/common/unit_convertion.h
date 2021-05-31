#pragma once

#include <string>
#include <string_view>

#include "interface/i_file.h"

namespace common {
class UnitConvertion final : public interface::IFile
{
public:
	UnitConvertion(const std::filesystem::path& aPath)
		: IFile(aPath) {};
	UnitConvertion(std::shared_ptr<interface::IFileImpl> aFileImpl)
		: IFile(aFileImpl) {};

	std::string Print() const override;

	bool CanConvertUnit(std::string_view aUnit) const;
	// returns wether or not it was able to convert. out parameter is only set if successfull.
	bool GetConvertionRate(std::string_view aCurrentUnit, float& aOutConvertionRate) const;
	void SetConvertionRate(std::string_view aUnit, float aConvertionRate);
	std::string GetBestUnit(float aBaseUnitAmount, float& aOutConvertedAmount) const;
};
} // namespace common
