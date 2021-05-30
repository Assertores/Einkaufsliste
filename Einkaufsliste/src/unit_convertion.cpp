#include "common/unit_convertion.h"

#include <charconv>
#include <map>

#include "interface/i_logger.h"

namespace common {
void
UnitConvertion::SetConvertionRate(std::string_view aUnit, float aConvertionRate)
{
	WriteField(aUnit, std::to_string(aConvertionRate));
}

bool
UnitConvertion::CanConvertUnit(std::string_view aUnit) const
{
	return !ReadFromField(aUnit).empty();
}

bool
UnitConvertion::GetConvertionRate(std::string_view aCurrentUnit, float& aOutConvertionRate) const
{
	auto rate = ReadFromField(aCurrentUnit);
	if (rate.empty())
	{
		return false;
	}
	float value = std::numeric_limits<float>::quiet_NaN();
	const auto* end = rate.data() + rate.size(); // NOLINT
	auto errors = std::from_chars(rate.data(), end, value);
	if (errors.ec != std::errc() || errors.ptr != end)
	{
		interface::ILogger::Log(
			interface::LogLevel::Error,
			interface::LogType::Units,
			rate + " is not a floatingpoint number");
		return false;
	}
	aOutConvertionRate = value;
	return true;
}

std::string
UnitConvertion::GetBestUnit(
	float aBaseUnitAmount,
	float& aOutConvertedAmount) const
{
	auto allUnits = GetSubKeys("");

	std::string currentUnit;
	float currentConvertedAmount = std::numeric_limits<float>::max();
	for (const auto& it : allUnits)
	{
		float rate = std::numeric_limits<float>::quiet_NaN();
		GetConvertionRate(it.string(), rate);
		rate *= aBaseUnitAmount;

		if (rate >= 1 && rate < currentConvertedAmount)
		{
			currentUnit = it.string();
			currentConvertedAmount = rate;
		}
	}

	aOutConvertedAmount = currentConvertedAmount;
	return currentUnit;
}
} // namespace common
