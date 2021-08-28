#include "common/change_recipe_name.h"

namespace common {
std::unique_ptr<interface::ICommand>
ChangeRecipeName::Clone()
{
	// TODO(andreas): command cant be unique because some need to make shared from this
	auto result = std::make_unique<
}

bool
ChangeRecipeName::DoExecute()
{
	myPrevName = myCurrentRecipe->GetName();

	auto frontend = myFrontend.lock();
	if (!frontend)
	{
		return false;
	}
	myCurrentRecipe->SetName(frontend->AskForText());
	return true;
}

void
ChangeRecipeName::SetReferences(
	std::weak_ptr<interface::IFrontend> aFrontend,
	std::shared_ptr<Observable<Recipe>> aCurrentRecipe)
{
	aCurrentRecipe->Subscribe(weak_from_this());
	myFrontend = aFrontend;
}

void
ChangeRecipeName::OnChange(Recipe aElement)
{
	myCurrentRecipe = std::make_unique<Recipe>(std::move(aElement));
}
} // namespace common