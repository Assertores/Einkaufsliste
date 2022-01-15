#pragma once

#include "common/list.h"
#include "common/observable.h"
#include "interface/i_command.h"
#include "interface/i_frontend.h"
#include "interface/i_observer.h"

#include <optional>
#include <string>

namespace biz {
class AddListRecipe
	: public infas::ICommand
	, public std::enable_shared_from_this<AddListRecipe> {
public:
	static std::shared_ptr<AddListRecipe> Create() { return std::make_shared<AddListRecipe>(); }

	std::unique_ptr<infas::ICommandMemento> Execute() override;

	void SetReferences(
		std::weak_ptr<infas::IFrontend> aFrontend,
		std::shared_ptr<common::Observable<std::optional<common::List>>> aCurrentList);

	// protected:
	AddListRecipe() = default;
	AddListRecipe(const AddListRecipe&) = delete;
	AddListRecipe(AddListRecipe&&) = default;
	AddListRecipe& operator=(const AddListRecipe&) = delete;
	AddListRecipe& operator=(AddListRecipe&&) = default;
	~AddListRecipe() override = default;

private:
	std::weak_ptr<infas::IFrontend> myFrontend;
	std::weak_ptr<common::Observable<std::optional<common::List>>> myList;
};
}  // namespace biz
