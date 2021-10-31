#pragma once

#include "common/list.h"
#include "common/observable.h"
#include "interface/i_command.h"
#include "interface/i_frontend.h"

namespace common {
class OpenList : public interface::ICommand {
public:
	static std::shared_ptr<OpenList> Create() { return std::make_shared<OpenList>(); }

	std::unique_ptr<interface::ICommandMemento> Execute() override;

	void SetReferences(
		std::weak_ptr<interface::IFrontend> aFrontend,
		std::weak_ptr<common::Observable<std::optional<List>>> aListObservable);

	// protected:
	// OpenList() = default;

private:
	std::weak_ptr<interface::IFrontend> myFrontend;
	std::weak_ptr<common::Observable<std::optional<List>>> myListObservable;
};
}  // namespace common
