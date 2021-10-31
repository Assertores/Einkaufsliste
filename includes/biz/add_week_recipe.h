#pragma once

#include <string>
#include <optional>

#include "common/observable.h"
#include "common/recipe.h"
#include "interface/i_command.h"
#include "interface/i_frontend.h"
#include "interface/i_observer.h"

namespace common {
class AddWeekRecipe
	: public interface::ICommand
	, public std::enable_shared_from_this<AddWeekRecipe>
{
public:
	static std::shared_ptr<AddWeekRecipe> Create()
	{
		return std::make_shared<AddWeekRecipe>();
	}

	std::unique_ptr<interface::ICommandMemento> Execute() override;

	void SetReferences(
		std::weak_ptr<interface::IFrontend> aFrontend,
		std::shared_ptr<Observable<std::optional<Week>>> aCurrentWeek);

	// protected:
	AddWeekRecipe() = default;
	AddWeekRecipe(const AddWeekRecipe&) = delete;
	AddWeekRecipe(AddWeekRecipe&&) = default;
	AddWeekRecipe& operator=(const AddWeekRecipe&) = delete;
	AddWeekRecipe& operator=(AddWeekRecipe&&) = default;
	~AddWeekRecipe() override = default;

private:
	std::weak_ptr<interface::IFrontend> myFrontend;
	std::weak_ptr<Observable<std::optional<Week>>> myWeek;
};
} // namespace common
