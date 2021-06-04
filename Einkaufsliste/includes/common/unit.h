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

	// returns the name of the type given string will result in
	static std::string ResultsInUnitsOfType(std::string_view aString);
	static std::vector<Unit>
	FromString(std::string_view aString);
	static std::string ToString(const std::vector<Unit>& aUnits);
	static void SetConvertionFiles(std::vector<UnitConvertion> aConvertionFiles)
	{
		myConvertionFiles = aConvertionFiles;
	}

	// returns wether or not it was able to add aOther to this object
	bool Add(const Unit& aOther);
	bool Subtract(const Unit& aOther);

	std::string GetType() const { return myType; }
	bool Equals(const Unit& aOther) const
	{
		return myType == aOther.myType && myAmount == aOther.myAmount;
	}

private:
	float myAmount = 0;
	std::string myType;
	UnitConvertion myConvertionFile;
	static std::vector<UnitConvertion> myConvertionFiles;
};
} // namespace common
