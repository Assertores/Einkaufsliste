#pragma once

#include "common/list.h"
#include "common/observable.h"
#include "interface/i_command.h"
#include "interface/i_frontend.h"

namespace biz {
class CompileList : public infas::ICommand {
public:
	static std::shared_ptr<CompileList> Create() { return std::make_shared<CompileList>(); }

	std::unique_ptr<infas::ICommandMemento> Execute() override;

	void SetReferences(std::weak_ptr<common::Observable<std::optional<common::List>>> aList);

	// protected:
	// CompileList() = default;

private:
	std::weak_ptr<common::Observable<std::optional<common::List>>> myList;
};
} // namespace biz
