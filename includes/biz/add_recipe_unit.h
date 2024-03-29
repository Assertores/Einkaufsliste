#pragma once

#include "common/observable.h"
#include "common/recipe.h"
#include "interface/i_command.h"
#include "interface/i_frontend.h"
#include "interface/i_observer.h"

#include <optional>
#include <string>

namespace biz {
class AddRecipeUnit
	: public infas::ICommand
	, public std::enable_shared_from_this<AddRecipeUnit> {
public:
	static std::shared_ptr<AddRecipeUnit> Create() { return std::make_shared<AddRecipeUnit>(); }

	std::unique_ptr<infas::ICommandMemento> Execute() override;

	void SetReferences(
		std::weak_ptr<infas::IFrontend> aFrontend,
		std::shared_ptr<common::Observable<std::optional<common::Recipe>>> aCurrentRecipe);

	// protected:
	AddRecipeUnit() = default;
	AddRecipeUnit(const AddRecipeUnit&) = delete;
	AddRecipeUnit(AddRecipeUnit&&) = default;
	AddRecipeUnit& operator=(const AddRecipeUnit&) = delete;
	AddRecipeUnit& operator=(AddRecipeUnit&&) = default;
	~AddRecipeUnit() override = default;

private:
	std::weak_ptr<infas::IFrontend> myFrontend;
	std::weak_ptr<common::Observable<std::optional<common::Recipe>>> myRecipe;
};
} // namespace biz
