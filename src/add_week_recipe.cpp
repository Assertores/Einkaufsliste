#include "biz/add_week_recipe.h"

#include "common/unit.h"

namespace biz {
class AddWeekRecipeMemento : public infas::ICommandMemento {
public:
	AddWeekRecipeMemento(
		common::Week aWeek,
		common::Recipe aNewRecipe,
		common::WeekDay aWeekDay,
		common::DayTime aDayTime)
		: myWeek(std::move(aWeek))
		, myNewRecipe(std::move(aNewRecipe))
		, myWeekDay(aWeekDay)
		, myDayTime(aDayTime){};

	void ReExecute() override { myWeek.AddRecipe(myNewRecipe, myWeekDay, myDayTime); }

	void Revert() override { myWeek.RemoveRecipe(myWeekDay, myDayTime); }

private:
	common::Week myWeek;
	common::Recipe myNewRecipe;
	common::WeekDay myWeekDay;
	common::DayTime myDayTime;
};

std::unique_ptr<infas::ICommandMemento>
AddWeekRecipe::Execute() {
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
	std::filesystem::path filePath = frontend->AskForFile();
	while (filePath.extension().empty()) {
		infas::ILogger::Log(infas::LogLevel::Error, infas::LogType::Commands, "invalid input");
		filePath = frontend->AskForFile();
	}
	auto file = common::Recipe(filePath);
	common::WeekDay day{};
	while (!frontend->AskForWeekDay(day)) {
		infas::ILogger::Log(infas::LogLevel::Error, infas::LogType::Commands, "invalid input");
		// TODO(andreas): invalid input
	}
	common::DayTime time{};
	while (!frontend->AskForDayTime(time)) {
		infas::ILogger::Log(infas::LogLevel::Error, infas::LogType::Commands, "invalid input");
		// TODO(andreas): invalid input
	}
	week->AddRecipe(file, day, time);

	return std::make_unique<AddWeekRecipeMemento>(week.value(), file, day, time);
}

void
AddWeekRecipe::SetReferences(
	std::weak_ptr<infas::IFrontend> aFrontend,
	std::shared_ptr<common::Observable<std::optional<common::Week>>> aCurrentWeek)	// NOLINT
{
	myWeek = aCurrentWeek;
	myFrontend = std::move(aFrontend);
}
}  // namespace biz
