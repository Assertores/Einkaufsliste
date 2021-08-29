#include "common/change_recipe_name.h"

namespace common {

std::unique_ptr<interface::ICommandMemento>
ChangeRecipeName::Execute()
{
	myPrevName = myCurrentRecipe->GetName();

	auto frontend = myFrontend.lock();
	if (!frontend)
	{
		return nullptr;
	}
	myCurrentRecipe->SetName(frontend->AskForText());
	return nullptr; // TODO(andreas): change to memento
}

void
ChangeRecipeName::SetReferences(
	std::weak_ptr<interface::IFrontend> aFrontend,
	std::shared_ptr<Observable<Recipe>> aCurrentRecipe) // NOLINT "performance-unnecessary-value-param"
{
	aCurrentRecipe->Subscribe(weak_from_this()); // TODO(andreas): unsubscripe on destructor?
	myFrontend = std::move(aFrontend);
}

void
ChangeRecipeName::OnChange(Recipe aElement)
{
	myCurrentRecipe = std::make_unique<Recipe>(std::move(aElement));
}
} // namespace common