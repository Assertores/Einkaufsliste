#pragma once

#include "common/observable.h"
#include "common/week.h"
#include "interface/i_command.h"
#include "interface/i_frontend.h"

#include <memory>
#include <optional>

namespace common {
class OpenWeek : public interface::ICommand {
public:
	static std::shared_ptr<OpenWeek> Create() { return std::make_shared<OpenWeek>(); }

	void SetReferences(
		std::weak_ptr<interface::IFrontend> aFrontend,
		std::weak_ptr<common::Observable<std::optional<Week>>> aWeekObservable);

	std::unique_ptr<interface::ICommandMemento> Execute() override;

	// protected:
	// OpenRecipe() = default;

private:
	std::weak_ptr<interface::IFrontend> myFrontend;
	std::weak_ptr<common::Observable<std::optional<Week>>> myWeekObservable;
};
}  // namespace common
