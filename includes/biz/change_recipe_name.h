#pragma once

#include "common/observable.h"
#include "common/recipe.h"
#include "interface/i_command.h"
#include "interface/i_frontend.h"
#include "interface/i_observer.h"

#include <optional>
#include <string>

namespace biz {
class ChangeRecipeName
	: public infas::ICommand
	, public std::enable_shared_from_this<ChangeRecipeName> {
public:
	static std::shared_ptr<ChangeRecipeName> Create() {
		return std::make_shared<ChangeRecipeName>();
	}

	std::unique_ptr<infas::ICommandMemento> Execute() override;

	void SetReferences(
		std::weak_ptr<infas::IFrontend> aFrontend,
		std::shared_ptr<common::Observable<std::optional<common::Recipe>>> aCurrentRecipe);

	// protected:
	ChangeRecipeName() = default;
	ChangeRecipeName(const ChangeRecipeName&) = delete;
	ChangeRecipeName(ChangeRecipeName&&) = default;
	ChangeRecipeName& operator=(const ChangeRecipeName&) = delete;
	ChangeRecipeName& operator=(ChangeRecipeName&&) = default;
	~ChangeRecipeName() override = default;

private:
	std::weak_ptr<infas::IFrontend> myFrontend;
	std::weak_ptr<common::Observable<std::optional<common::Recipe>>> myRecipe;
};
} // namespace biz
