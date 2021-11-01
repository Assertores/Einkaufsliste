#include "biz/add_list_week.h"

#include "common/unit.h"

namespace common {
#if not_implimented
class AddListRecipeMemento : public interface::ICommandMemento {
public:
	AddListRecipeMemento(Week aWeek, Recipe aNewRecipe, WeekDay aWeekDay, DayTime aDayTime)
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
#endif

std::unique_ptr<interface::ICommandMemento>
AddListWeek::Execute() {
	auto sub = myList.lock();
	if (!sub) {
		interface::ILogger::Log(
			interface::LogLevel::Fatal,
			interface::LogType::Commands,
			"lost connection to observable");
		return nullptr;
	}
	auto list = sub->Get();
	if (!list.has_value()) {
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
	std::filesystem::path file = frontend->AskForFile();
	while (file.extension().empty()) {
		interface::ILogger::Log(
			interface::LogLevel::Error,
			interface::LogType::Commands,
			"invalide input");
		file = frontend->AskForFile();
	}

	list->AddWeek(Week(file));

	return nullptr;
}

void
AddListWeek::SetReferences(
	std::weak_ptr<interface::IFrontend> aFrontend,
	std::shared_ptr<Observable<std::optional<List>>> aCurrentList)	// NOLINT
{
	myList = aCurrentList;
	myFrontend = std::move(aFrontend);
}
}  // namespace common
