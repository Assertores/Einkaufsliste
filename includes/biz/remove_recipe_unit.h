#pragma once

#include <string>
#include <optional>

#include "common/observable.h"
#include "common/recipe.h"
#include "interface/i_command.h"
#include "interface/i_frontend.h"
#include "interface/i_observer.h"

namespace common {
class RemoveRecipeUnit
	: public interface::ICommand
	, public std::enable_shared_from_this<RemoveRecipeUnit>
{
public:
	static std::shared_ptr<RemoveRecipeUnit> Create()
	{
		return std::make_shared<RemoveRecipeUnit>();
	}

	std::unique_ptr<interface::ICommandMemento> Execute() override;

	void SetReferences(
		std::weak_ptr<interface::IFrontend> aFrontend,
		std::shared_ptr<Observable<std::optional<Recipe>>> aCurrentRecipe);

	// protected:
	RemoveRecipeUnit() = default;
	RemoveRecipeUnit(const RemoveRecipeUnit&) = delete;
	RemoveRecipeUnit(RemoveRecipeUnit&&) = default;
	RemoveRecipeUnit& operator=(const RemoveRecipeUnit&) = delete;
	RemoveRecipeUnit& operator=(RemoveRecipeUnit&&) = default;
	~RemoveRecipeUnit() override = default;

private:
	std::weak_ptr<interface::IFrontend> myFrontend;
	std::weak_ptr<Observable<std::optional<Recipe>>> myRecipe;
};
} // namespace common