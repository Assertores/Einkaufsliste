#include "biz/compile_list.h"

#include "common/list.h"
#include "common/unit_conversion.h"

namespace common {
std::unique_ptr<infas::ICommandMemento>
CompileList::Execute() {
	auto sub = myList.lock();
	if (!sub) {
		infas::ILogger::Log(
			infas::LogLevel::Fatal,
			infas::LogType::Commands,
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

