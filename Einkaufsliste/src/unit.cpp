#include "common/unit.h"

#include <charconv>
#include <sstream>

#include "interface/i_logger.h"

namespace common {

Unit::Unit(
	float aAmount,
	std::string aType,
	std::string_view aUnit,
	const UnitConvertion& aConvertionFile)
	: myType(std::move(aType))
	, myConvertionFile(aConvertionFile)
{
	float rate = NAN;
	if (!aConvertionFile.GetConvertionRate(aUnit, rate))
	{
		interface::ILogger::Instance()->Log(
			interface::LogLevel::Error,
			interface::LogType_Units,
			std::string("tryed to create unit ot type ") + aType
				+ " but the convertion file was not able to convert it ");
		myAmount = aAmount;
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
	return std::string(aString.substr(0, aString.find_first_of(' '))); // TODO(andreas): impliment
}

std::vector<Unit>
Unit::FromString(std::string_view aString, const std::vector<UnitConvertion>& aConverters)
{
	auto type = std::string(ResultsInUnitsOfType(aString));
	aString = aString.substr(aString.find_first_of(' ') + 1);

	std::vector<Unit> result {};

	while (!aString.empty())
	{
		std::string_view element;
		{
			auto split = aString.find_first_of(" & ");
			if (split == std::string_view::npos)
			{
				element = aString;
				aString = "";
			}
			else
			{
				element = aString.substr(0, aString.find_first_of(" & "));
				aString = aString.substr(aString.find_first_of(" & ") + 3);
			}
		}
		float value = NAN;
		auto errors =
			std::from_chars(element.data(), element.data() + element.size(), value); // NOLINT
		auto unit = element.substr(errors.ptr - element.data());
		for (const auto& it : aConverters)
		{
			if (it.CanConvertUnit(unit))
			{
				result.emplace_back(value, type, unit, it);
				break;
			}
		}
	}

	return result; // TODO(andreas): where do i get the ConvertionFile
}

std::string
Unit::ToString(std::vector<Unit> aUnits)
{
	if (aUnits.empty())
	{
		return "";
	}
	std::stringstream strBuilder;
	strBuilder << aUnits[0].myType << ' ';
	for (const auto& it : aUnits)
	{
		if (it.myType != aUnits[0].myType)
		{
			interface::ILogger::Instance()->Log(
				interface::LogLevel::Debug,
				interface::LogType_Units,
				std::string("units ") + aUnits[0].myType + " array contained unit of type "
					+ it.myType);
			return "";
		}
		float amount = NAN;
		auto unit = it.myConvertionFile.GetBestUnit(it.myAmount, amount);
		strBuilder << amount << unit << " & ";
	}
	auto result = strBuilder.str();
	return result.substr(0, result.size() - 3);
}

bool
Unit::Equals(const Unit& aOther)
{
	return myType == aOther.myType && myAmount == aOther.myAmount;
}
} // namespace common
