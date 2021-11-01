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
	std::filesystem::path file = frontend->AskForFile();
	while (file.extension().empty()) {
		interface::ILogger::Log(
			interface::LogLevel::Error,
			interface::LogType::Commands,
			"invalide input");
		file = frontend->AskForFile();
	}
	weekObservable->Set(Week(file));

	return nullptr;
}
}  // namespace common
