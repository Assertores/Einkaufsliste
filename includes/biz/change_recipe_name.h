#pragma once

#include "common/observable.h"
#include "common/recipe.h"
#include "interface/i_command.h"
#include "interface/i_frontend.h"
#include "interface/i_observer.h"

#include <optional>
#include <string>

namespace common {
class ChangeRecipeName
	: public interface::ICommand
	, public std::enable_shared_from_this<ChangeRecipeName> {
public:
	static std::shared_ptr<ChangeRecipeName> Create() {
		return std::make_shared<ChangeRecipeName>();
	}

	std::unique_ptr<interface::ICommandMemento> Execute() override;

	void SetReferences(
		std::weak_ptr<interface::IFrontend> aFrontend,
		std::shared_ptr<Observable<std::optional<Recipe>>> aCurrentRecipe);

	// protected:
	ChangeRecipeName() = default;
	ChangeRecipeName(const ChangeRecipeName&) = delete;
	ChangeRecipeName(ChangeRecipeName&&) = default;
	ChangeRecipeName& operator=(const ChangeRecipeName&) = delete;
	ChangeRecipeName& operator=(ChangeRecipeName&&) = default;
	~ChangeRecipeName() override = default;

private:
	std::weak_ptr<interface::IFrontend> myFrontend;
	std::weak_ptr<Observable<std::optional<Recipe>>> myRecipe;
};
}  // namespace common
