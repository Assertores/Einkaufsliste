#include "biz/open_list.h"

#include "common/unit_convertion.h"
#include "common/list.h"

namespace common {
std::unique_ptr<interface::ICommandMemento>
OpenList::Execute()
{
	auto frontend = myFrontend.lock();
	if (!frontend)
	{
		return nullptr;
	}
	auto listObservable = myListObservable.lock();
	if (!listObservable)
	{
		return nullptr;
	}
	
	auto file = frontend->AskForFile();
	listObservable->Set(List(std::filesystem::current_path() / file));

	return nullptr;
}

void
OpenList::SetReferences(std::weak_ptr<interface::IFrontend> aFrontend,
	std::weak_ptr<common::Observable<std::optional<List>>> aListObservable)
{
	myFrontend = std::move(aFrontend);
	myListObservable = std::move(aListObservable);
}
} // namespace common
