#include "biz/add_list_recipe.h"

#include "common/unit.h"

namespace biz {
#if not_implemented
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

std::unique_ptr<infas::ICommandMemento>
AddListRecipe::Execute() {
	auto sub = myList.lock();
	if (!sub) {
		infas::ILogger::Log(
			infas::LogLevel::Fatal,
			infas::LogType::Commands,
			"lost connection to observable");
		return nullptr;
	}
	auto list = sub->Get();
	if (!list.has_value()) {
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
	std::filesystem::path file = frontend->AskForFile();
	while (file.extension().empty()) {
		infas::ILogger::Log(infas::LogLevel::Error, infas::LogType::Commands, "invalid input");
		file = frontend->AskForFile();
	}

	list->AddRecipe(common::Recipe(file));

	return nullptr;
}

void
AddListRecipe::SetReferences(
	std::weak_ptr<infas::IFrontend> aFrontend,
	std::shared_ptr<common::Observable<std::optional<common::List>>> aCurrentList) // NOLINT
{
	myList = aCurrentList;
	myFrontend = std::move(aFrontend);
}
} // namespace biz
