#pragma once

#include "common/observable.h"
#include "common/week.h"
#include "interface/i_command.h"
#include "interface/i_frontend.h"

#include <memory>
#include <optional>

namespace biz {
class OpenWeek : public infas::ICommand {
public:
	static std::shared_ptr<OpenWeek> Create() { return std::make_shared<OpenWeek>(); }

	void SetReferences(
		std::weak_ptr<infas::IFrontend> aFrontend,
		std::weak_ptr<common::Observable<std::optional<common::Week>>> aWeekObservable);

	std::unique_ptr<infas::ICommandMemento> Execute() override;

	// protected:
	// OpenRecipe() = default;

private:
	std::weak_ptr<infas::IFrontend> myFrontend;
	std::weak_ptr<common::Observable<std::optional<common::Week>>> myWeekObservable;
};
} // namespace biz
