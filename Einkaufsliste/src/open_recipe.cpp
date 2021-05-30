#include "common/open_recipe.h"

#include "common/recipe.h"

namespace common {
std::unique_ptr<interface::ICommand>
OpenRecipe::Clone()
{
	return std::make_unique<OpenRecipe>(myFrontend, myRecipeObservable);
}

bool
OpenRecipe::DoExecute()
{
	auto frontend = myFrontend.lock();
	if (!frontend)
	{
		return false;
	}

	auto file = frontend->AskForFile();
	myRecipeObservable.Notify(Recipe(file));

	return false;
}
} // namespace common
