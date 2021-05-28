#pragma once

#include <string>
#include <string_view>
#include <vector>

#include "common/unit_convertion.h"

namespace common {
class Unit final
{
public:
	Unit(
		float aAmount,
		std::string aType,
		std::string_view aUnit,
		const UnitConvertion& aConvertionFile);

	// returns wether or not it was able to add aOther to this object
	bool Add(const Unit& aOther);
	// returns the name of the type given string will result in
	static std::string ResultsInUnitsOfType(std::string_view aString);
	static std::vector<Unit>
	FromString(std::string_view aString, const std::vector<UnitConvertion>& aConverters);
	static std::string ToString(const std::vector<Unit>& aUnits);

	bool Equals(const Unit& aOther);

private:
	float myAmount = 0;
	std::string myType;
	UnitConvertion myConvertionFile;
};
} // namespace common
