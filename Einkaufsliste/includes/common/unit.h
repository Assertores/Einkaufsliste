#pragma once

#include <string>
#include <string_view>
#include <vector>

#include "common/unit_convertion.h"

namespace common {
class Unit
{
public:
	// TODO: convert amount to base unit
	Unit(float aAmount, std::string aType, std::string aUnit, UnitConvertion aConvertionFile);
	// returns wether or not it was able to add aOther to this object
	bool Add(const Unit& aOther);
	// returns the name of the type given string will result in
	static std::string ResultsInUnitsOfType(std::string_view aString);
	static std::vector<Unit> FromString(std::string_view aString);
	static std::string ToString(std::vector<Unit> aUnits, UnitConvertion aConvertionFile);

private:
	float myAmount = 0;
	std::string myType;
};
} // namespace common
