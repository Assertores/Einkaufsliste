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
	OpenRecipe(
		std::weak_ptr<interface::IFrontend> aFrontend,
		common::Observable<common::Recipe>& aRecipeObservable)
		: myFrontend(std::move(aFrontend))
		, myRecipeObservable(myRecipeObservable) {};

	virtual std::unique_ptr<ICommand> Clone() override;
	virtual bool DoExecute() override;

private:
	std::weak_ptr<interface::IFrontend> myFrontend;
	common::Observable<common::Recipe>& myRecipeObservable;
};
} // namespace common
