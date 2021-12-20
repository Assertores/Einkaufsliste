#pragma once

#include "common/unit_conversion.h"

#include <optional>
#include <string>
#include <string_view>
#include <vector>

namespace common {
class Unit {
public:
	Unit(float aAmount, std::string_view aUnit, std::string aType);

	// returns the name of the type given string will result in
	static std::string ResultsInUnitsOfType(std::string_view aString);
	static std::vector<Unit> FromString(std::string_view aString);
	static std::string ToString(const std::vector<Unit>& aUnits);
	static void SetConversionFiles(std::vector<UnitConversion> aConversionFiles) {
		myConversionFiles = std::move(aConversionFiles);
	}

	// returns wether or not it was able to add aOther to this object
	bool Add(const Unit& aOther);
	bool Subtract(const Unit& aOther);

	[[nodiscard]] std::string GetType() const { return myType; }
	[[nodiscard]] bool Equals(const Unit& aOther) const {
		return myType == aOther.myType && myAmount == aOther.myAmount;
	}

	friend bool operator==(const Unit& aLhs, const Unit& aRhs) { return aLhs.Equals(aRhs); }

private:
	float myAmount = 0;
	std::string myType;
	std::optional<UnitConversion> myConversionFile;
	static std::vector<UnitConversion> myConversionFiles;
};
}  // namespace common
