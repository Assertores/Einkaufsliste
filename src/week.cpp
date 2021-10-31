#include "common/week.h"

#include <algorithm>
#include <sstream>

static constexpr const char* locDescriptionKey = "Description";
static constexpr const char* locIngredientsKey = "Ingredients";
static constexpr const char* locNameKey = "Name";

namespace common {
std::string
ToString(WeekDay aWeekDay)
{
	switch (aWeekDay)
	{
	case WeekDay::Monday:
		return "Monday";
	case WeekDay::Tuesday:
		return "Tuesday";
	case WeekDay::Wednesday:
		return "Wednesday";
	case WeekDay::Thursday:
		return "Thursday";
	case WeekDay::Friday:
		return "Friday";
	case WeekDay::Saturday:
		return "Saturday";
	case WeekDay::Sunday:
		return "Sunday";
	}
}

std::string
ToString(DayTime aDayTime)
{
	return std::to_string(aDayTime.myHours) + ":" + std::to_string(aDayTime.myMinutes);
}

bool
FromString(std::string_view aString, WeekDay& aOutWeekDay)
{
	if (aString == "Monday" || aString == "Mo")
	{
		aOutWeekDay = WeekDay::Monday;
		return true;
	}
	if (aString == "Tuesday" || aString == "Tu")
	{
		aOutWeekDay = WeekDay::Tuesday;
		return true;
	}
	if (aString == "Wednesday" || aString == "We")
	{
		aOutWeekDay = WeekDay::Wednesday;
		return true;
	}
	if (aString == "Thursday" || aString == "Th")
	{
		aOutWeekDay = WeekDay::Thursday;
		return true;
	}
	if (aString == "Friday" || aString == "Fr")
	{
		aOutWeekDay = WeekDay::Friday;
		return true;
	}
	if (aString == "Saturday" || aString == "Sa")
	{
		aOutWeekDay = WeekDay::Saturday;
		return true;
	}
	if (aString == "Sunday" || aString == "Su")
	{
		aOutWeekDay = WeekDay::Sunday;
		return true;
	}
	return false;
}

bool
FromString(std::string_view aString, DayTime& aOutWeekDay)
{
	DayTime result {};
	 // NOLINTNEXTLINE
	if (sscanf(std::string(aString).c_str(), "%d:%d", &result.myHours, &result.myMinutes)
		== 2)
	{
		aOutWeekDay = result;
		return true;
	}
	return false;
}

std::string
Week::Print() const
{
	std::stringstream result;
	std::vector<std::string> days { ToString(WeekDay::Monday),	  ToString(WeekDay::Tuesday),
									ToString(WeekDay::Wednesday), ToString(WeekDay::Thursday),
									ToString(WeekDay::Friday),	  ToString(WeekDay::Saturday),
									ToString(WeekDay::Sunday) };

	for (const auto& day : days)
	{
		result << day << '\n';
		for (const auto& it : GetSubKeys(day))
		{
			result << it.filename().string() << " | " << ReadFromField(it) << '\n';
		}
	}

	return result.str();
}

void
Week::AddRecipe(const Recipe& aRecipe, WeekDay aWeekDay, DayTime aDayTime)
{
	std::filesystem::path key(ToString(aWeekDay));
	key /= ToString(aDayTime);
	WriteField(key, aRecipe.GetFile());
}

Recipe
Week::GetRecipe(WeekDay aWeekDay, DayTime aDayTime) const
{
	std::filesystem::path key(ToString(aWeekDay));
	key /= ToString(aDayTime);
	return Recipe(ReadFromField(key));
}

void
Week::RemoveRecipe(WeekDay aWeekDay, DayTime aDayTime)
{
	std::filesystem::path key(ToString(aWeekDay));
	key /= ToString(aDayTime);
	WriteField(key, "");
}

std::set<Recipe>
Week::GetAllRecipes() const
{
	std::set<Recipe> result;
	auto keys = GetSubKeys("");
	for (const auto& it : keys)
	{
		result.insert(Recipe(ReadFromField(it)));
	}
	return result;
}
} // namespace common
