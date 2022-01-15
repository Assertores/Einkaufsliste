#pragma once

#include "common/observable.h"
#include "common/recipe.h"
#include "interface/i_command.h"
#include "interface/i_frontend.h"

#include <memory>
#include <optional>

namespace biz {
class OpenRecipe : public infas::ICommand {
public:
	static std::shared_ptr<OpenRecipe> Create() { return std::make_shared<OpenRecipe>(); }

	void SetReferences(
		std::weak_ptr<infas::IFrontend> aFrontend,
		std::weak_ptr<common::Observable<std::optional<common::Recipe>>> aRecipeObservable);

	std::unique_ptr<infas::ICommandMemento> Execute() override;

	// protected:
	// OpenRecipe() = default;

private:
	std::weak_ptr<infas::IFrontend> myFrontend;
	std::weak_ptr<common::Observable<std::optional<common::Recipe>>> myRecipeObservable;
};
}  // namespace biz
