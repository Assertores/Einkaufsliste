#include "biz/remove_week_recipe.h"

#include "common/unit.h"

namespace biz {
class RemoveWeekRecipeMemento : public infas::ICommandMemento {
public:
	RemoveWeekRecipeMemento(
		common::Week aWeek,
		common::Recipe aNewRecipe,
		common::WeekDay aWeekDay,
		common::DayTime aDayTime)
		: myWeek(std::move(aWeek))
		, myNewRecipe(std::move(aNewRecipe))
		, myWeekDay(aWeekDay)
		, myDayTime(aDayTime){};

	void ReExecute() override { myWeek.RemoveRecipe(myWeekDay, myDayTime); }

	void Revert() override { myWeek.AddRecipe(myNewRecipe, myWeekDay, myDayTime); }

private:
	common::Week myWeek;
	common::Recipe myNewRecipe;
	common::WeekDay myWeekDay;
	common::DayTime myDayTime;
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
	common::WeekDay day{};
	while (!frontend->AskForWeekDay(day)) {
		infas::ILogger::Log(infas::LogLevel::Error, infas::LogType::Commands, "invalid input");
		// TODO(andreas): handle error
	}
	common::DayTime time{};
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
	std::shared_ptr<common::Observable<std::optional<common::Week>>> aCurrentWeek)	// NOLINT
{
	myWeek = aCurrentWeek;
	myFrontend = std::move(aFrontend);
}
}  // namespace biz
