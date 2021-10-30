#pragma once

#include <string>
#include <optional>

#include "common/observable.h"
#include "common/recipe.h"
#include "interface/i_command.h"
#include "interface/i_frontend.h"
#include "interface/i_observer.h"

namespace common {
class ChangeRecipeDescription
	: public interface::ICommand
	, public std::enable_shared_from_this<ChangeRecipeDescription>
{
public:
	static std::shared_ptr<ChangeRecipeDescription> Create()
	{
		return std::make_shared<ChangeRecipeDescription>();
	}

	std::unique_ptr<interface::ICommandMemento> Execute() override;

	void SetReferences(
		std::weak_ptr<interface::IFrontend> aFrontend,
		std::shared_ptr<Observable<std::optional<Recipe>>> aCurrentRecipe);

	// protected:
	ChangeRecipeDescription() = default;
	ChangeRecipeDescription(const ChangeRecipeDescription&) = delete;
	ChangeRecipeDescription(ChangeRecipeDescription&&) = default;
	ChangeRecipeDescription& operator=(const ChangeRecipeDescription&) = delete;
	ChangeRecipeDescription& operator=(ChangeRecipeDescription&&) = default;
	~ChangeRecipeDescription() override = default;

private:
	std::weak_ptr<interface::IFrontend> myFrontend;
	std::weak_ptr<Observable<std::optional<Recipe>>> myRecipe;
};
} // namespace common