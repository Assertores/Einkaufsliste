#pragma once

#include "common/recipe.h"
#include "interface/i_file.h"

#include <set>
#include <string_view>

namespace common {
enum class WeekDay {
	Monday,
	Tuesday,
	Wednesday,
	Thursday,
	Friday,
	Saturday,
	Sunday,
};

struct DayTime {
	int myHours;
	int myMinutes;
};

std::string ToString(WeekDay aWeekDay);
std::string ToString(DayTime aDayTime);
bool FromString(const std::string& aString, WeekDay& aOutWeekDay);
bool FromString(const std::string& aString, DayTime& aOutWeekDay);

class Week : public infas::IFile {
public:
	explicit Week(const std::filesystem::path& aPath)
		: IFile(aPath){};
	explicit Week(std::shared_ptr<infas::IFileImpl> aFileImpl)
		: IFile(std::move(aFileImpl)){};

	[[nodiscard]] std::string Print() const override;

	void AddRecipe(const Recipe& aRecipe, WeekDay aWeekDay, DayTime aDayTime);
	void RemoveRecipe(WeekDay aWeekDay, DayTime aDayTime);

	[[nodiscard]] Recipe GetRecipe(WeekDay aWeekDay, DayTime aDayTime) const;
	[[nodiscard]] std::vector<Recipe> GetAllRecipes() const;
};
} // namespace common
