#pragma once

#include <string>
#include <optional>

#include "common/observable.h"
#include "common/recipe.h"
#include "interface/i_command.h"
#include "interface/i_frontend.h"
#include "interface/i_observer.h"

namespace common {
class RemoveWeekRecipe
	: public interface::ICommand
	, public std::enable_shared_from_this<RemoveWeekRecipe>
{
public:
	static std::shared_ptr<RemoveWeekRecipe> Create()
	{
		return std::make_shared<RemoveWeekRecipe>();
	}

	std::unique_ptr<interface::ICommandMemento> Execute() override;

	void SetReferences(
		std::weak_ptr<interface::IFrontend> aFrontend,
		std::shared_ptr<Observable<std::optional<Week>>> aCurrentWeek);

	// protected:
	RemoveWeekRecipe() = default;
	RemoveWeekRecipe(const RemoveWeekRecipe&) = delete;
	RemoveWeekRecipe(RemoveWeekRecipe&&) = default;
	RemoveWeekRecipe& operator=(const RemoveWeekRecipe&) = delete;
	RemoveWeekRecipe& operator=(RemoveWeekRecipe&&) = default;
	~RemoveWeekRecipe() override = default;

private:
	std::weak_ptr<interface::IFrontend> myFrontend;
	std::weak_ptr<Observable<std::optional<Week>>> myWeek;
};
} // namespace common
