#include "common/unit.h"

#include "interface/i_logger.h"

#include <charconv>
#include <sstream>

namespace common {
std::vector<UnitConvertion> Unit::myConvertionFiles{};

Unit::Unit(float aAmount, std::string_view aUnit, std::string aType)
	: myType(std::move(aType)) {
	for (const auto& it : myConvertionFiles) {
		if (it.CanConvertUnit(aUnit)) {
			myConvertionFile = it;
			break;
		}
	}
	if (!myConvertionFile) {
		interface::ILogger::Log(
			interface::LogLevel::Error,
			interface::LogType::Units,
			std::string("tryed to create unit ot type ") + aType
				+ " but the convertion file was not able to convert it ");
		myAmount = aAmount;
		return;
	}

	float rate = std::numeric_limits<float>::quiet_NaN();
	if (!myConvertionFile->GetConvertionRate(aUnit, rate)) {
		interface::ILogger::Log(
			interface::LogLevel::Error,
			interface::LogType::Units,
			std::string("tryed to create unit ot type ") + aType
				+ " but the convertion file was not able to convert it ");
		myAmount = aAmount;
		return;
	}
	myAmount = aAmount * rate;
};

bool
Unit::Add(const Unit& aOther) {
	if (aOther.myType != myType) {
		return false;
	}
	if (aOther.myConvertionFile != myConvertionFile) {
		return false;
	}
	myAmount += aOther.myAmount;
	return true;
}

bool
Unit::Subtract(const Unit& aOther) {
	if (aOther.myType != myType) {
		return false;
	}
	if (aOther.myConvertionFile != myConvertionFile) {
		return false;
	}
	myAmount -= aOther.myAmount;
	return true;
}

std::string
Unit::ResultsInUnitsOfType(std::string_view aString) {
	return std::string(aString.substr(0, aString.find_first_of(' ')));	// TODO(andreas): impliment
}

std::vector<Unit>
Unit::FromString(std::string_view aString) {
	auto type = std::string(ResultsInUnitsOfType(aString));
	aString = aString.substr(aString.find_first_of(' ') + 1);

	std::vector<Unit> result{};

	while (!aString.empty()) {
		std::string_view element;
		{
			auto split = aString.find_first_of(" & ");
			if (split == std::string_view::npos) {
				element = aString;
				aString = "";
			} else {
				element = aString.substr(0, aString.find_first_of(" & "));
				aString = aString.substr(aString.find_first_of(" & ") + 3);
			}
		}
		float value = std::numeric_limits<float>::quiet_NaN();
#if gcc_is_unable_to_compile_from_chars
		auto errors =
			std::from_chars(element.data(), element.data() + element.size(), value);  // NOLINT
		auto unit = element.substr(errors.ptr - element.data());
#else
		// don't ask!!
		char* ptr = nullptr;  // NOLINT(cppcoreguidelines-pro-type-vararg, hicpp-vararg)
		value = std::strtof(element.data(), &ptr);
		auto unit = element.substr(ptr - element.data());
#endif
		result.emplace_back(value, unit, type);
	}

	return result;	// TODO(andreas): where do i get the ConvertionFile
}

std::string
Unit::ToString(const std::vector<Unit>& aUnits) {
	if (aUnits.empty()) {
		return "";
	}
	bool valid = false;
	std::stringstream strBuilder;
	strBuilder << aUnits[0].myType << ' ';
	for (const auto& it : aUnits) {
		if (it.myType != aUnits[0].myType) {
			interface::ILogger::Log(
				interface::LogLevel::Debug,
				interface::LogType::Units,
				std::string("units ") + aUnits[0].myType + " array contained unit of type "
					+ it.myType);
			return "";
		}
		float amount = std::numeric_limits<float>::quiet_NaN();
		auto unit = it.myConvertionFile->GetBestUnit(it.myAmount, amount);
		if (amount > 0) {
			valid = true;
			strBuilder << amount << unit << " & ";
		}
	}
	auto result = strBuilder.str();
	return valid ? result.substr(0, result.size() - 3) : "";
}
}  // namespace common
