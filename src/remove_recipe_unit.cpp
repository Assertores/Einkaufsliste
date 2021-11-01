#include "biz/remove_recipe_unit.h"

#include "common/unit.h"

namespace common {

class RemoveRecipeUnitMemento : public interface::ICommandMemento {
public:
	RemoveRecipeUnitMemento(Recipe aRecipe, Unit aNewUnit)
		: myRecipe(std::move(aRecipe))
		, myNewUnit(std::move(aNewUnit)){};

	void ReExecute() override { myRecipe.RemoveIngredient(myNewUnit); }

	void Revert() override { myRecipe.AddIngredient(myNewUnit); }

private:
	Recipe myRecipe;
	Unit myNewUnit;
};

std::unique_ptr<interface::ICommandMemento>
RemoveRecipeUnit::Execute() {
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
	const auto wasRemoved = recipe.value().RemoveIngredient(unit);
	return wasRemoved ? std::make_unique<RemoveRecipeUnitMemento>(recipe.value(), unit) : nullptr;
}

void
RemoveRecipeUnit::SetReferences(
	std::weak_ptr<interface::IFrontend> aFrontend,
	std::shared_ptr<Observable<std::optional<Recipe>>> aCurrentRecipe)	// NOLINT
{
	myRecipe = aCurrentRecipe;
	myFrontend = std::move(aFrontend);
}
}  // namespace common
