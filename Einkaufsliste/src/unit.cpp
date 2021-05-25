#include "common/unit.h"

#include <sstream>

namespace common {

Unit::Unit(float aAmount, std::string aType, std::string aUnit, UnitConvertion aConvertionFile)
	: myType(aType)
{
	float rate = NAN;
	if (!aConvertionFile.GetConvertionRate(aUnit, rate))
	{
		return;
	}
	myAmount = aAmount * rate;
};

bool
Unit::Add(const Unit& aOther)
{
	if (aOther.myType != myType)
	{
		return false;
	}
	myAmount += aOther.myAmount;
	return true;
}

std::string
Unit::ResultsInUnitsOfType(std::string_view aString)
{
	return ""; // TODO: impliment
}

std::vector<Unit>
Unit::FromString(std::string_view aString)
{
	return std::vector<Unit>(); // TODO: where do i get the ConvertionFile
}

std::string
Unit::ToString(std::vector<Unit> aUnits, UnitConvertion aConvertionFile)
{
	if (aUnits.empty())
	{
		return "";
	}
	std::stringstream result;
	result << aUnits[0].myType << ' ';
	for (const auto& it : aUnits)
	{
		if (it.myType != aUnits[0].myType)
		{
			// TODO: print warning
			return "";
		}
		float amount = NAN;
		auto unit = aConvertionFile.GetBestUnit(it.myAmount, amount);
		result << amount << unit << " & ";
	}
	return result.str();
}
} // namespace common
