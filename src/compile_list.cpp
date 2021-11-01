#include "biz/compile_list.h"

#include "common/list.h"
#include "common/unit_convertion.h"

namespace common {
std::unique_ptr<interface::ICommandMemento>
CompileList::Execute() {
	auto sub = myList.lock();
	if (!sub) {
		interface::ILogger::Log(
			interface::LogLevel::Fatal,
			interface::LogType::Commands,
			"lost connection to observable");
		return nullptr;
	}
	auto list = sub->Get();
	list->Compile();

	return nullptr;
}

void
CompileList::SetReferences(std::weak_ptr<common::Observable<std::optional<List>>> aList) {
	myList = std::move(aList);
}
}  // namespace common
