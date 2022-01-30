#pragma once

#include "common/observable.h"
#include "common/recipe.h"
#include "interface/i_command.h"
#include "interface/i_frontend.h"
#include "interface/i_observer.h"

#include <optional>
#include <string>

namespace biz {
class ChangeRecipeDescription
	: public infas::ICommand
	, public std::enable_shared_from_this<ChangeRecipeDescription> {
public:
	static std::shared_ptr<ChangeRecipeDescription> Create() {
		return std::make_shared<ChangeRecipeDescription>();
	}

	std::unique_ptr<infas::ICommandMemento> Execute() override;

	void SetReferences(
		std::weak_ptr<infas::IFrontend> aFrontend,
		std::shared_ptr<common::Observable<std::optional<common::Recipe>>> aCurrentRecipe);

	// protected:
	ChangeRecipeDescription() = default;
	ChangeRecipeDescription(const ChangeRecipeDescription&) = delete;
	ChangeRecipeDescription(ChangeRecipeDescription&&) = default;
	ChangeRecipeDescription& operator=(const ChangeRecipeDescription&) = delete;
	ChangeRecipeDescription& operator=(ChangeRecipeDescription&&) = default;
	~ChangeRecipeDescription() override = default;

private:
	std::weak_ptr<infas::IFrontend> myFrontend;
	std::weak_ptr<common::Observable<std::optional<common::Recipe>>> myRecipe;
};
} // namespace biz
