#pragma once

#include <set>
#include <string_view>

#include "common/recipe.h"
#include "interface/i_file.h"

namespace common {
enum class WeekDay
{
	Monday,
	Tuesday,
	Wednesday,
	Thursday,
	Friday,
	Saturday,
	Sunday,
};

struct DayTime
{
	int myHours;
	int myMinutes;
};

std::string ToString(WeekDay aWeekDay);
std::string ToString(DayTime aDayTime);
bool FromString(std::string_view aString, WeekDay& aOutWeekDay);
bool FromString(std::string_view aString, DayTime& aOutWeekDay);

class Week : public interface::IFile
{
public:
	explicit Week(const std::filesystem::path& aPath)
		: IFile(aPath) {};
	explicit Week(std::shared_ptr<interface::IFileImpl> aFileImpl)
		: IFile(std::move(aFileImpl)) {};

	[[nodiscard]] std::string Print() const override;

	void AddRecipe(const Recipe& aRecipe, WeekDay aWeekDay, DayTime aDayTime);
	void RemoveRecipe(WeekDay aWeekDay, DayTime aDayTime);

	[[nodiscard]] std::set<Recipe> GetAllRecipes() const;
};
} // namespace common
