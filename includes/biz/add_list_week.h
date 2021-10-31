#pragma once

#include "common/list.h"
#include "common/observable.h"
#include "interface/i_command.h"
#include "interface/i_frontend.h"
#include "interface/i_observer.h"

#include <optional>
#include <string>

namespace common {
class AddListWeek
	: public interface::ICommand
	, public std::enable_shared_from_this<AddListWeek> {
public:
	static std::shared_ptr<AddListWeek> Create() { return std::make_shared<AddListWeek>(); }

	std::unique_ptr<interface::ICommandMemento> Execute() override;

	void SetReferences(
		std::weak_ptr<interface::IFrontend> aFrontend,
		std::shared_ptr<Observable<std::optional<List>>> aCurrentList);

	// protected:
	AddListWeek() = default;
	AddListWeek(const AddListWeek&) = delete;
	AddListWeek(AddListWeek&&) = default;
	AddListWeek& operator=(const AddListWeek&) = delete;
	AddListWeek& operator=(AddListWeek&&) = default;
	~AddListWeek() override = default;

private:
	std::weak_ptr<interface::IFrontend> myFrontend;
	std::weak_ptr<Observable<std::optional<List>>> myList;
};
}  // namespace common
