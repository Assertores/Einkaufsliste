#include "biz/open_recipe.h"

#include "common/recipe.h"

namespace common {
void
OpenRecipe::SetReferences(
	std::weak_ptr<interface::IFrontend> aFrontend,
	std::weak_ptr<common::Observable<std::optional<common::Recipe>>> aRecipeObservable)
{
	myFrontend = std::move(aFrontend);
	myRecipeObservable = std::move(aRecipeObservable);
}

std::unique_ptr<interface::ICommandMemento>
OpenRecipe::Execute()
{
	auto frontend = myFrontend.lock();
	if (!frontend)
	{
		return nullptr;
	}
	auto recipeObservable = myRecipeObservable.lock();
	if (!recipeObservable)
	{
		return nullptr;
	}

	auto file = frontend->AskForFile();
	recipeObservable->Set(Recipe(std::filesystem::current_path() / file));

	return nullptr;
}
} // namespace common
