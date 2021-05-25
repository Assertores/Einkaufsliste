#include "common/unit_convertion.h"

#include <charconv>
#include <map>

namespace common {
void
UnitConvertion::SetConvertionRate(std::string_view aUnit, float aConvertionRate)
{
	WriteField(aUnit, std::to_string(aConvertionRate));
}

bool
UnitConvertion::GetConvertionRate(std::string_view aCurrentUnit, float& aOutConvertionRate) const
{
	auto rate = ReadFromField(aCurrentUnit);
	if (rate.empty())
	{
		return false;
	}
	float value = NAN;
	const auto* end = &*rate.end();
	auto errors = std::from_chars(rate.data(), end, value);
	if (errors.ec != std::errc() || errors.ptr != end)
	{
		// TODO: log that file was faulty
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
	auto allUnits = GetAllKeys();

	std::string currentUnit;
	float currentConvertedAmount = std::numeric_limits<float>::max();
	for (const auto& it : allUnits)
	{
		float rate = NAN;
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