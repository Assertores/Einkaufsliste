#pragma once

#include "common/list.h"
#include "common/observable.h"
#include "interface/i_command.h"
#include "interface/i_frontend.h"

namespace biz {
class OpenList : public infas::ICommand {
public:
	static std::shared_ptr<OpenList> Create() { return std::make_shared<OpenList>(); }

	std::unique_ptr<infas::ICommandMemento> Execute() override;

	void SetReferences(
		std::weak_ptr<infas::IFrontend> aFrontend,
		std::weak_ptr<common::Observable<std::optional<common::List>>> aListObservable);

	// protected:
	// OpenList() = default;

private:
	std::weak_ptr<infas::IFrontend> myFrontend;
	std::weak_ptr<common::Observable<std::optional<common::List>>> myListObservable;
};
}  // namespace biz
