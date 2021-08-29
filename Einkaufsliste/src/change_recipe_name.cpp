#include "common/change_recipe_name.h"

namespace common {

class ChangeRecipeNameMemento : public interface::ICommandMemento
{
public:
	ChangeRecipeNameMemento(Recipe aRecipe, std::string aNewName, std::string aPrevName)
		: myRecipe(std::move(aRecipe))
		, myNewName(std::move(aNewName))
		, myPrevName(std::move(aPrevName)) {};

	void ReExecute() override { myRecipe.SetName(myNewName); }

	void Revert() override { myRecipe.SetName(myPrevName); }

private:
	Recipe myRecipe;
	std::string myNewName;
	std::string myPrevName;
};

ChangeRecipeName::~ChangeRecipeName()
{
	auto recipe = mySubscription.lock();
	if (recipe)
	{
		recipe->Remove(weak_from_this());
	}
}

std::unique_ptr<interface::ICommandMemento>
ChangeRecipeName::Execute()
{
	const auto privName = myCurrentRecipe->GetName();

	auto frontend = myFrontend.lock();
	if (!frontend)
	{
		return nullptr;
	}
	const auto name = frontend->AskForText();
	myCurrentRecipe->SetName(name);
	return std::make_unique<ChangeRecipeNameMemento>(*myCurrentRecipe, name, privName);
}

void
ChangeRecipeName::SetReferences(
	std::weak_ptr<interface::IFrontend> aFrontend,
	std::shared_ptr<Observable<Recipe>> aCurrentRecipe) // NOLINT
{
	aCurrentRecipe->Subscribe(weak_from_this()); // TODO(andreas): unsubscripe on destructor?
	mySubscription = aCurrentRecipe;
	myFrontend = std::move(aFrontend);
}

void
ChangeRecipeName::OnChange(Recipe aElement)
{
	myCurrentRecipe = std::make_unique<Recipe>(std::move(aElement));
}
} // namespace common