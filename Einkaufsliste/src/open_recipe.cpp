#include "common/open_recipe.h"

#include "common/recipe.h"

namespace common {
void
OpenRecipe::SetReferences(
	std::weak_ptr<interface::IFrontend> aFrontend,
	std::weak_ptr<common::Observable<common::Recipe>> aRecipeObservable)
{
	myFrontend = std::move(aFrontend);
	myRecipeObservable = std::move(aRecipeObservable);
}

std::unique_ptr<interface::ICommand>
OpenRecipe::Clone()
{
	auto result = std::make_unique<OpenRecipe>();
	result->myFrontend = myFrontend;
	result->myRecipeObservable = myRecipeObservable;
	return result;
}

bool
OpenRecipe::DoExecute()
{
	auto frontend = myFrontend.lock();
	if (!frontend)
	{
		return false;
	}
	auto recipeObservable = myRecipeObservable.lock();
	if (!recipeObservable)
	{
		return false;
	}

	auto file = frontend->AskForFile();
	recipeObservable->Notify(Recipe(std::filesystem::current_path() / file));

	return false;
}
} // namespace common
