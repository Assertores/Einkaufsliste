#include "biz/open_list.h"

#include "common/list.h"
#include "common/unit_convertion.h"

namespace common {
std::unique_ptr<interface::ICommandMemento>
OpenList::Execute() {
	auto frontend = myFrontend.lock();
	if (!frontend) {
		return nullptr;
	}
	auto listObservable = myListObservable.lock();
	if (!listObservable) {
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
	listObservable->Set(List(file));

	return nullptr;
}

void
OpenList::SetReferences(
	std::weak_ptr<interface::IFrontend> aFrontend,
	std::weak_ptr<common::Observable<std::optional<List>>> aListObservable) {
	myFrontend = std::move(aFrontend);
	myListObservable = std::move(aListObservable);
}
}  // namespace common
