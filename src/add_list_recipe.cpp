#include "biz/add_list_recipe.h"

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
AddListRecipe::Execute() {
	auto sub = myList.lock();
	if (!sub) {
		// TODO(andreas): connection to observable lost
		return nullptr;
	}
	auto list = sub->Get();
	if (!list.has_value()) {
		// TODO(andreas): not list
		return nullptr;
	}
	auto frontend = myFrontend.lock();
	if (!frontend) {
		return nullptr;
	}
	list->AddRecipe(Recipe(frontend->AskForFile()));

	return nullptr;
}

void
AddListRecipe::SetReferences(
	std::weak_ptr<interface::IFrontend> aFrontend,
	std::shared_ptr<Observable<std::optional<List>>> aCurrentList)	// NOLINT
{
	myList = aCurrentList;
	myFrontend = std::move(aFrontend);
}
}  // namespace common
