#pragma once

#include <string>
#include <optional>

#include "common/observable.h"
#include "common/list.h"
#include "interface/i_command.h"
#include "interface/i_frontend.h"
#include "interface/i_observer.h"

namespace common {
class AddListRecipe
	: public interface::ICommand
	, public std::enable_shared_from_this<AddListRecipe>
{
public:
	static std::shared_ptr<AddListRecipe> Create()
	{
		return std::make_shared<AddListRecipe>();
	}

	std::unique_ptr<interface::ICommandMemento> Execute() override;

	void SetReferences(
		std::weak_ptr<interface::IFrontend> aFrontend,
		std::shared_ptr<Observable<std::optional<List>>> aCurrentList);

	// protected:
	AddListRecipe() = default;
	AddListRecipe(const AddListRecipe&) = delete;
	AddListRecipe(AddListRecipe&&) = default;
	AddListRecipe& operator=(const AddListRecipe&) = delete;
	AddListRecipe& operator=(AddListRecipe&&) = default;
	~AddListRecipe() override = default;

private:
	std::weak_ptr<interface::IFrontend> myFrontend;
	std::weak_ptr<Observable<std::optional<List>>> myList;
};
} // namespace common
