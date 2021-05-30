#include "common\open_recipe.h"

#include "common/recipe.h"

std::unique_ptr<interface::ICommand>
common::OpenRecipe::Clone()
{
	return std::make_unique<OpenRecipe>(myFrontend, myHub);
}

bool
common::OpenRecipe::DoExecute()
{
	auto frontend = myFrontend.lock();
	if (!frontend)
	{
		return false;
	}
	auto hub = myHub.lock();
	if (!hub)
	{
		return false;
	}

	auto file = frontend->AskForFile();
	hub->currentRecipe.Notify(Recipe(file));

	return false;
}
