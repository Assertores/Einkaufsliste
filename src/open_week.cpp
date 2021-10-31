#include "biz/open_week.h"

#include "common/week.h"

namespace common {
void
OpenWeek::SetReferences(
	std::weak_ptr<interface::IFrontend> aFrontend,
	std::weak_ptr<common::Observable<std::optional<Week>>> aWeekObservable) {
	myFrontend = std::move(aFrontend);
	myWeekObservable = std::move(aWeekObservable);
}

std::unique_ptr<interface::ICommandMemento>
OpenWeek::Execute() {
	auto frontend = myFrontend.lock();
	if (!frontend) {
		return nullptr;
	}
	auto weekObservable = myWeekObservable.lock();
	if (!weekObservable) {
		return nullptr;
	}

	auto file = frontend->AskForFile();
	weekObservable->Set(Week(std::filesystem::current_path() / file));

	return nullptr;
}
}  // namespace common
