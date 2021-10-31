#include "biz/add_week_recipe.h"

#include "common/unit.h"

namespace common {
class AddWeekRecipeMemento : public interface::ICommandMemento
{
public:
	AddWeekRecipeMemento(Week aWeek, Recipe aNewRecipe, WeekDay aWeekDay, DayTime aDayTime)
		: myWeek(std::move(aWeek))
		, myNewRecipe(std::move(aNewRecipe))
		, myWeekDay(aWeekDay)
		, myDayTime(aDayTime) {};

	void ReExecute() override { myWeek.AddRecipe(myNewRecipe, myWeekDay, myDayTime); }

	void Revert() override { myWeek.RemoveRecipe(myWeekDay, myDayTime); }

private:
	Week myWeek;
	Recipe myNewRecipe;
	WeekDay myWeekDay;
	DayTime myDayTime;
};

std::unique_ptr<interface::ICommandMemento>
AddWeekRecipe::Execute()
{
	auto sub = myWeek.lock();
	if (!sub)
	{
		// TODO(andreas): connection to observable lost
		return nullptr;
	}
	auto week = sub->Get();
	if (!week.has_value())
	{
		// TODO(andreas): not week
		return nullptr;
	}
	auto frontend = myFrontend.lock();
	if (!frontend)
	{
		return nullptr;
	}
	auto file = Recipe(frontend->AskForFile());
	auto day = frontend->AskForWeekDay();
	auto time = frontend->AskForDayTime();
	week->AddRecipe(file, day, time);

	return std::make_unique<AddWeekRecipeMemento>(week.value(), file, day, time);
}

void
AddWeekRecipe::SetReferences(
	std::weak_ptr<interface::IFrontend> aFrontend,
	std::shared_ptr<Observable<std::optional<Week>>> aCurrentWeek) // NOLINT
{
	myWeek = aCurrentWeek;
	myFrontend = std::move(aFrontend);
}
} // namespace common
