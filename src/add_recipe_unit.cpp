#include "biz/add_recipe_unit.h"

#include "common/unit.h"

namespace common {

class AddRecipeUnitMemento : public interface::ICommandMemento {
public:
	AddRecipeUnitMemento(Recipe aRecipe, Unit aNewUnit)
		: myRecipe(std::move(aRecipe))
		, myNewUnit(std::move(aNewUnit)){};

	void ReExecute() override { myRecipe.AddIngredient(myNewUnit); }

	void Revert() override { myRecipe.RemoveIngredient(myNewUnit); }

private:
	Recipe myRecipe;
	Unit myNewUnit;
};

std::unique_ptr<interface::ICommandMemento>
AddRecipeUnit::Execute() {
	auto sub = myRecipe.lock();
	if (!sub) {
		interface::ILogger::Log(
			interface::LogLevel::Fatal,
			interface::LogType::Commands,
			"lost connection to observable");
		return nullptr;
	}
	auto recipe = sub->Get();
	if (!recipe.has_value()) {
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
	const auto unit = frontend->AskForUnit();
	recipe.value().AddIngredient(unit);
	return std::make_unique<AddRecipeUnitMemento>(recipe.value(), unit);
}

void
AddRecipeUnit::SetReferences(
	std::weak_ptr<interface::IFrontend> aFrontend,
	std::shared_ptr<Observable<std::optional<Recipe>>> aCurrentRecipe)	// NOLINT
{
	myRecipe = aCurrentRecipe;
	myFrontend = std::move(aFrontend);
}
}  // namespace common
