#include "biz/open_convertion_files.h"

#include "common/unit_convertion.h"

namespace common {
std::unique_ptr<interface::ICommandMemento>
OpenConvertionFile::Execute()
{
	auto frontend = myFrontend.lock();
	if (!frontend)
	{
		return nullptr;
	}
	auto folder = frontend->AskForFolder();
	if(!std::filesystem::is_directory(folder)){
		// TODO(andreas): log error
		return nullptr;
	}
	std::vector<UnitConvertion> files {};
	for (const auto& it : std::filesystem::directory_iterator(folder))
	{
		files.emplace_back(it);
	}
	Unit::SetConvertionFiles(files);

	return nullptr;
}

void
OpenConvertionFile::SetReferences(std::weak_ptr<interface::IFrontend> aFrontend)
{
	myFrontend = std::move(aFrontend);
}
} // namespace common
