#pragma once

#include "common/observable.h"
#include "common/recipe.h"
#include "interface/i_command.h"
#include "interface/i_frontend.h"
#include "interface/i_observer.h"

#include <optional>
#include <string>

namespace biz {
class RemoveRecipeUnit
	: public infas::ICommand
	, public std::enable_shared_from_this<RemoveRecipeUnit> {
public:
	static std::shared_ptr<RemoveRecipeUnit> Create() {
		return std::make_shared<RemoveRecipeUnit>();
	}

	std::unique_ptr<infas::ICommandMemento> Execute() override;

	void SetReferences(
		std::weak_ptr<infas::IFrontend> aFrontend,
		std::shared_ptr<common::Observable<std::optional<common::Recipe>>> aCurrentRecipe);

	// protected:
	RemoveRecipeUnit() = default;
	RemoveRecipeUnit(const RemoveRecipeUnit&) = delete;
	RemoveRecipeUnit(RemoveRecipeUnit&&) = default;
	RemoveRecipeUnit& operator=(const RemoveRecipeUnit&) = delete;
	RemoveRecipeUnit& operator=(RemoveRecipeUnit&&) = default;
	~RemoveRecipeUnit() override = default;

private:
	std::weak_ptr<infas::IFrontend> myFrontend;
	std::weak_ptr<common::Observable<std::optional<common::Recipe>>> myRecipe;
};
} // namespace biz
