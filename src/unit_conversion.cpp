#include "common/unit_conversion.h"

#include "interface/i_logger.h"

#include <charconv>
#include <map>
#include <sstream>

namespace common {
std::string
UnitConversion::Print() const {
	std::stringstream reslut;
	for (const auto& it : GetSubKeys("")) {
		reslut << it << ": " << ReadFromField(it) << '\n';
	}
	return reslut.str();
}
void
UnitConversion::SetConversionRate(std::string_view aUnit, float aConversionRate) {
	WriteField(aUnit, std::to_string(aConversionRate));
}

bool
UnitConversion::CanConvertUnit(std::string_view aUnit) const {
	return !ReadFromField(aUnit).empty();
}

bool
UnitConversion::GetConversionRate(std::string_view aCurrentUnit, float& aOutConversionRate) const {
	auto rate = ReadFromField(aCurrentUnit);
	if (rate.empty()) {
		return false;
	}
	float value = std::numeric_limits<float>::quiet_NaN();
#if gcc_is_unable_to_compile_from_chars
	const auto* end = rate.data() + rate.size(); // NOLINT
	auto errors = std::from_chars(rate.data(), end, value);
	if (errors.ec != std::errc() || errors.ptr != end) {
		infas::ILogger::Log(
			infas::LogLevel::Error,
			infas::LogType::Units,
			rate + " is not a floatingpoint number");
		return false;
	}
#else
	// don't ask!!
	char* ptr = nullptr; // NOLINT(cppcoreguidelines-pro-type-vararg, hicpp-vararg)
	value = std::strtof(rate.data(), &ptr);
	if (ptr != rate.data() + rate.size()) // NOLINT
	{
		infas::ILogger::Log(
			infas::LogLevel::Error,
			infas::LogType::Units,
			rate + " is not a floatingpoint number");
		return false;
	}
#endif
	aOutConversionRate = 1 / value;
	return true;
}

std::string
UnitConversion::GetBestUnit(float aBaseUnitAmount, float& aOutConvertedAmount) const {
	if (aBaseUnitAmount == 0) {
		aOutConvertedAmount = 0;
		return "NAN";
	}

	auto allUnits = GetSubKeys("");

	std::string currentUnit;
	float currentConvertedAmount = std::numeric_limits<float>::max();
	for (const auto& it : allUnits) {
		float rate = std::numeric_limits<float>::quiet_NaN();
		GetConversionRate(it.string(), rate);
		rate = aBaseUnitAmount / rate;

		if (rate >= 1 && rate < currentConvertedAmount) {
			currentUnit = it.string();
			currentConvertedAmount = rate;
		}
	}

	aOutConvertedAmount = currentConvertedAmount;
	return currentUnit;
}
} // namespace common
