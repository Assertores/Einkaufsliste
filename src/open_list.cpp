#include "biz/open_list.h"

#include "common/list.h"
#include "common/unit_conversion.h"

namespace biz {
std::unique_ptr<infas::ICommandMemento>
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
		infas::ILogger::Log(infas::LogLevel::Error, infas::LogType::Commands, "invalid input");
		file = frontend->AskForFile();
	}
	listObservable->Set(common::List(file));

	return nullptr;
}

void
OpenList::SetReferences(
	std::weak_ptr<infas::IFrontend> aFrontend,
	std::weak_ptr<common::Observable<std::optional<common::List>>> aListObservable) {
	myFrontend = std::move(aFrontend);
	myListObservable = std::move(aListObservable);
}
}  // namespace biz
