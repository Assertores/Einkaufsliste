#include "biz/change_recipe_name.h"

namespace common {

class ChangeRecipeNameMemento : public interface::ICommandMemento {
public:
	ChangeRecipeNameMemento(Recipe aRecipe, std::string aNewName, std::string aPrevName)
		: myRecipe(std::move(aRecipe))
		, myNewName(std::move(aNewName))
		, myPrevName(std::move(aPrevName)){};

	void ReExecute() override { myRecipe.SetName(myNewName); }

	void Revert() override { myRecipe.SetName(myPrevName); }

private:
	Recipe myRecipe;
	std::string myNewName;
	std::string myPrevName;
};

std::unique_ptr<interface::ICommandMemento>
ChangeRecipeName::Execute() {
	auto sub = myRecipe.lock();
	if (!sub) {
		// TODO(andreas): connection to observable lost
		return nullptr;
	}
	auto recipe = sub->Get();
	if (!recipe.has_value()) {
		// TODO(andreas): not recipe
		return nullptr;
	}
	const auto privName = recipe.value().GetName();

	auto frontend = myFrontend.lock();
	if (!frontend) {
		return nullptr;
	}
	const auto name = frontend->AskForText();
	recipe.value().SetName(name);
	return std::make_unique<ChangeRecipeNameMemento>(recipe.value(), name, privName);
}

void
ChangeRecipeName::SetReferences(
	std::weak_ptr<interface::IFrontend> aFrontend,
	std::shared_ptr<Observable<std::optional<Recipe>>> aCurrentRecipe)	// NOLINT
{
	myRecipe = aCurrentRecipe;
	myFrontend = std::move(aFrontend);
}
}  // namespace common
