#pragma once

#include <string>
#include <string_view>
#include <vector>

#include "common/unit_convertion.h"

namespace common {
class Unit
{
public:
	Unit(
		float aAmount,
		std::string_view aUnit,
		std::string aType,
		const UnitConvertion& aConvertionFile);

	// returns the name of the type given string will result in
	static std::string ResultsInUnitsOfType(std::string_view aString);
	static std::vector<Unit> FromString(std::string_view aString);
	static std::string ToString(const std::vector<Unit>& aUnits);
	static void SetConvertionFiles(std::vector<UnitConvertion> aConvertionFiles)
	{
		myConvertionFiles = std::move(aConvertionFiles);
	}

	// returns wether or not it was able to add aOther to this object
	bool Add(const Unit& aOther);
	bool Subtract(const Unit& aOther);

	[[nodiscard]] std::string GetType() const { return myType; }
	[[nodiscard]] bool Equals(const Unit& aOther) const
	{
		return myType == aOther.myType && myAmount == aOther.myAmount;
	}

	friend bool operator==(const Unit& aLhs, const Unit& aRhs) { return aLhs.Equals(aRhs); }

private:
	float myAmount = 0;
	std::string myType;
	UnitConvertion myConvertionFile;
	static std::vector<UnitConvertion> myConvertionFiles;
};
} // namespace common
