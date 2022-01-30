#pragma once

#include "common/observable.h"
#include "common/recipe.h"
#include "interface/i_command.h"
#include "interface/i_frontend.h"
#include "interface/i_observer.h"

#include <optional>
#include <string>

namespace biz {
class RemoveWeekRecipe
	: public infas::ICommand
	, public std::enable_shared_from_this<RemoveWeekRecipe> {
public:
	static std::shared_ptr<RemoveWeekRecipe> Create() {
		return std::make_shared<RemoveWeekRecipe>();
	}

	std::unique_ptr<infas::ICommandMemento> Execute() override;

	void SetReferences(
		std::weak_ptr<infas::IFrontend> aFrontend,
		std::shared_ptr<common::Observable<std::optional<common::Week>>> aCurrentWeek);

	// protected:
	RemoveWeekRecipe() = default;
	RemoveWeekRecipe(const RemoveWeekRecipe&) = delete;
	RemoveWeekRecipe(RemoveWeekRecipe&&) = default;
	RemoveWeekRecipe& operator=(const RemoveWeekRecipe&) = delete;
	RemoveWeekRecipe& operator=(RemoveWeekRecipe&&) = default;
	~RemoveWeekRecipe() override = default;

private:
	std::weak_ptr<infas::IFrontend> myFrontend;
	std::weak_ptr<common::Observable<std::optional<common::Week>>> myWeek;
};
} // namespace biz
