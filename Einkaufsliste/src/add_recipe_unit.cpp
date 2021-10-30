#include "biz/add_recipe_unit.h"

#include "common/unit.h"

namespace common {

class AddRecipeUnitMemento : public interface::ICommandMemento
{
public:
	AddRecipeUnitMemento(Recipe aRecipe, common::Unit aNewUnit)
		: myRecipe(std::move(aRecipe))
		, myNewUnit(std::move(aNewUnit)) {};

	void ReExecute() override { myRecipe.AddIngredient(myNewUnit); }

	void Revert() override { myRecipe.RemoveIngredient(myNewUnit); }

private:
	Recipe myRecipe;
	common::Unit myNewUnit;
};

std::unique_ptr<interface::ICommandMemento>
AddRecipeUnit::Execute()
{
	auto sub = myRecipe.lock();
	if (!sub)
	{
		// TODO(andreas): connection to observable lost
		return nullptr;
	}
	auto recipe = sub->Get();
	if (!recipe.has_value())
	{
		// TODO(andreas): not recipe
		return nullptr;
	}
	auto frontend = myFrontend.lock();
	if (!frontend)
	{
		return nullptr;
	}
	const auto unit = frontend->AskForUnit();
	recipe.value().AddIngredient(unit);
	return std::make_unique<AddRecipeUnitMemento>(recipe.value(), unit);
}

void
AddRecipeUnit::SetReferences(
	std::weak_ptr<interface::IFrontend> aFrontend,
	std::shared_ptr<Observable<std::optional<Recipe>>> aCurrentRecipe) // NOLINT
{
	myRecipe = aCurrentRecipe;
	myFrontend = std::move(aFrontend);
}
} // namespace common