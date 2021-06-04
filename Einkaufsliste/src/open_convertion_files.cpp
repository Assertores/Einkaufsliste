#include "common/open_convertion_files.h"

#include "common/unit_convertion.h"

namespace common {
std::unique_ptr<interface::ICommand>
OpenConvertionFile::Clone()
{
	auto result = std::make_unique<OpenConvertionFile>();
	result->myFrontend = myFrontend;
	return result;
}

bool
OpenConvertionFile::DoExecute()
{
	auto frontend = myFrontend.lock();
	if (!frontend)
	{
		return false;
	}
	auto folder = frontend->AskForFolder();
	std::vector<UnitConvertion> files {};
	for (const auto& it : std::filesystem::directory_iterator(folder))
	{
		files.emplace_back(it);
	}
	Unit::SetConvertionFiles(files);

	return false;
}
} // namespace common
