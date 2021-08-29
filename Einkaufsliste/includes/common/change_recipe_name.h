#pragma once

#include <string>

#include "common/observable.h"
#include "common/recipe.h"
#include "interface/i_command.h"
#include "interface/i_frontend.h"
#include "interface/i_observer.h"

namespace common {
class ChangeRecipeName
	: public interface::ICommand
	, public interface::IObserver<Recipe>
	, public std::enable_shared_from_this<ChangeRecipeName>
{
public:
	~ChangeRecipeName() override;

	static std::shared_ptr<ChangeRecipeName> Create()
	{
		return std::make_shared<ChangeRecipeName>();
	}

	std::unique_ptr<interface::ICommandMemento> Execute() override;

	void SetReferences(
		std::weak_ptr<interface::IFrontend> aFrontend,
		std::shared_ptr<Observable<Recipe>> aCurrentRecipe);

	void OnChange(Recipe aElement) override;

	// protected:
	ChangeRecipeName() = default;
	ChangeRecipeName(const ChangeRecipeName&) = delete;
	ChangeRecipeName(ChangeRecipeName&&) = default;
	ChangeRecipeName& operator=(const ChangeRecipeName&) = delete;
	ChangeRecipeName& operator=(ChangeRecipeName&&) = default;

private:
	std::weak_ptr<interface::IFrontend> myFrontend;
	std::weak_ptr<Observable<Recipe>> mySubscription;

	std::unique_ptr<Recipe> myCurrentRecipe;
};
} // namespace common