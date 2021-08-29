#pragma once

#include <memory>

#include "common/observable.h"
#include "common/recipe.h"
#include "interface/i_command.h"
#include "interface/i_frontend.h"

namespace common {
class OpenRecipe : public interface::ICommand
{
public:
	void SetReferences(
		std::weak_ptr<interface::IFrontend> aFrontend,
		std::weak_ptr<common::Observable<common::Recipe>> aRecipeObservable);

	std::unique_ptr<interface::ICommandMemento> Execute() override;

private:
	std::weak_ptr<interface::IFrontend> myFrontend;
	std::weak_ptr<common::Observable<common::Recipe>> myRecipeObservable;
};
} // namespace common
