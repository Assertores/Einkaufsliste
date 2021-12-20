#include "biz/remove_week_recipe.h"

#include "common/unit.h"

namespace common {
class RemoveWeekRecipeMemento : public infas::ICommandMemento {
public:
	RemoveWeekRecipeMemento(Week aWeek, Recipe aNewRecipe, WeekDay aWeekDay, DayTime aDayTime)
		: myWeek(std::move(aWeek))
		, myNewRecipe(std::move(aNewRecipe))
		, myWeekDay(aWeekDay)
		, myDayTime(aDayTime){};

	void ReExecute() override { myWeek.RemoveRecipe(myWeekDay, myDayTime); }

	void Revert() override { myWeek.AddRecipe(myNewRecipe, myWeekDay, myDayTime); }

private:
	Week myWeek;
	Recipe myNewRecipe;
	WeekDay myWeekDay;
	DayTime myDayTime;
};

std::unique_ptr<infas::ICommandMemento>
RemoveWeekRecipe::Execute() {
	auto sub = myWeek.lock();
	if (!sub) {
		infas::ILogger::Log(
			infas::LogLevel::Fatal,
			infas::LogType::Commands,
			"lost connection to observable");
		return nullptr;
	}
	auto week = sub->Get();
	if (!week.has_value()) {
		infas::ILogger::Log(
			infas::LogLevel::Fatal,
			infas::LogType::Commands,
			"tryed to access current file but it is not set");
		return nullptr;
	}
	auto frontend = myFrontend.lock();
	if (!frontend) {
		return nullptr;
	}
	WeekDay day{};
	while (!frontend->AskForWeekDay(day)) {
		infas::ILogger::Log(infas::LogLevel::Error, infas::LogType::Commands, "invalid input");
		// TODO(andreas): handle error
	}
	DayTime time{};
	while (!frontend->AskForDayTime(time)) {
		infas::ILogger::Log(infas::LogLevel::Error, infas::LogType::Commands, "invalid input");
		// TODO(andreas): handle error
	}

	auto file = week->GetRecipe(day, time);
	week->RemoveRecipe(day, time);

	return std::make_unique<RemoveWeekRecipeMemento>(week.value(), file, day, time);
}

void
RemoveWeekRecipe::SetReferences(
	std::weak_ptr<infas::IFrontend> aFrontend,
	std::shared_ptr<Observable<std::optional<Week>>> aCurrentWeek)	// NOLINT
{
	myWeek = aCurrentWeek;
	myFrontend = std::move(aFrontend);
}
}  // namespace common
