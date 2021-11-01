#include "biz/add_week_recipe.h"

#include "common/unit.h"

namespace common {
class AddWeekRecipeMemento : public interface::ICommandMemento {
public:
	AddWeekRecipeMemento(Week aWeek, Recipe aNewRecipe, WeekDay aWeekDay, DayTime aDayTime)
		: myWeek(std::move(aWeek))
		, myNewRecipe(std::move(aNewRecipe))
		, myWeekDay(aWeekDay)
		, myDayTime(aDayTime){};

	void ReExecute() override { myWeek.AddRecipe(myNewRecipe, myWeekDay, myDayTime); }

	void Revert() override { myWeek.RemoveRecipe(myWeekDay, myDayTime); }

private:
	Week myWeek;
	Recipe myNewRecipe;
	WeekDay myWeekDay;
	DayTime myDayTime;
};

std::unique_ptr<interface::ICommandMemento>
AddWeekRecipe::Execute() {
	auto sub = myWeek.lock();
	if (!sub) {
		interface::ILogger::Log(
			interface::LogLevel::Fatal,
			interface::LogType::Commands,
			"lost connection to observable");
		return nullptr;
	}
	auto week = sub->Get();
	if (!week.has_value()) {
		interface::ILogger::Log(
			interface::LogLevel::Fatal,
			interface::LogType::Commands,
			"tryed to access current file but it is not set");
		return nullptr;
	}
	auto frontend = myFrontend.lock();
	if (!frontend) {
		return nullptr;
	}
	std::filesystem::path filePath = frontend->AskForFile();
	while (filePath.extension().empty()) {
		interface::ILogger::Log(
			interface::LogLevel::Error,
			interface::LogType::Commands,
			"invalide input");
		filePath = frontend->AskForFile();
	}
	auto file = Recipe(filePath);
	WeekDay day{};
	while (!frontend->AskForWeekDay(day)) {
		interface::ILogger::Log(
			interface::LogLevel::Error,
			interface::LogType::Commands,
			"invalide input");
		// TODO(andreas): invalide input
	}
	DayTime time{};
	while (!frontend->AskForDayTime(time)) {
		interface::ILogger::Log(
			interface::LogLevel::Error,
			interface::LogType::Commands,
			"invalide input");
		// TODO(andreas): invalide input
	}
	week->AddRecipe(file, day, time);

	return std::make_unique<AddWeekRecipeMemento>(week.value(), file, day, time);
}

void
AddWeekRecipe::SetReferences(
	std::weak_ptr<interface::IFrontend> aFrontend,
	std::shared_ptr<Observable<std::optional<Week>>> aCurrentWeek)	// NOLINT
{
	myWeek = aCurrentWeek;
	myFrontend = std::move(aFrontend);
}
}  // namespace common
