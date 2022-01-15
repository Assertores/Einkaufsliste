#include "biz/add_recipe_unit.h"

#include "common/unit.h"

namespace biz {

class AddRecipeUnitMemento : public infas::ICommandMemento {
public:
	AddRecipeUnitMemento(common::Recipe aRecipe, common::Unit aNewUnit)
		: myRecipe(std::move(aRecipe))
		, myNewUnit(std::move(aNewUnit)){};

	void ReExecute() override { myRecipe.AddIngredient(myNewUnit); }

	void Revert() override { myRecipe.RemoveIngredient(myNewUnit); }

private:
	common::Recipe myRecipe;
	common::Unit myNewUnit;
};

std::unique_ptr<infas::ICommandMemento>
AddRecipeUnit::Execute() {
	auto sub = myRecipe.lock();
	if (!sub) {
		infas::ILogger::Log(
			infas::LogLevel::Fatal,
			infas::LogType::Commands,
			"lost connection to observable");
		return nullptr;
	}
	auto recipe = sub->Get();
	if (!recipe.has_value()) {
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
	const auto unit = frontend->AskForUnit();
	recipe.value().AddIngredient(unit);
	return std::make_unique<AddRecipeUnitMemento>(recipe.value(), unit);
}

void
AddRecipeUnit::SetReferences(
	std::weak_ptr<infas::IFrontend> aFrontend,
	std::shared_ptr<common::Observable<std::optional<common::Recipe>>> aCurrentRecipe)	// NOLINT
{
	myRecipe = aCurrentRecipe;
	myFrontend = std::move(aFrontend);
}
}  // namespace biz
