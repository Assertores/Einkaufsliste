#include "biz/open_convertion_files.h"

#include "common/unit_convertion.h"
#include "interface/i_logger.h"

namespace common {
std::unique_ptr<infas::ICommandMemento>
OpenConvertionFile::Execute() {
	auto frontend = myFrontend.lock();
	if (!frontend) {
		return nullptr;
	}
	std::filesystem::path folder = frontend->AskForFolder();
	while (!std::filesystem::is_directory(folder)) {
		infas::ILogger::Log(infas::LogLevel::Error, infas::LogType::Commands, "invalide input");
		folder = frontend->AskForFolder();
	}

	std::vector<UnitConvertion> files{};
	for (const auto& it : std::filesystem::directory_iterator(folder)) {
		files.emplace_back(it);
	}
	Unit::SetConvertionFiles(files);

	return nullptr;
}

void
OpenConvertionFile::SetReferences(std::weak_ptr<infas::IFrontend> aFrontend) {
	myFrontend = std::move(aFrontend);
}
}  // namespace common
