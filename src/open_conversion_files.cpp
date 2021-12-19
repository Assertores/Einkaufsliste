#include "biz/open_conversion_files.h"

#include "common/unit_conversion.h"
#include "interface/i_logger.h"

namespace common {
std::unique_ptr<infas::ICommandMemento>
OpenConversionFile::Execute() {
	auto frontend = myFrontend.lock();
	if (!frontend) {
		return nullptr;
	}
	std::filesystem::path folder = frontend->AskForFolder();
	while (!std::filesystem::is_directory(folder)) {
		infas::ILogger::Log(infas::LogLevel::Error, infas::LogType::Commands, "invalide input");
		folder = frontend->AskForFolder();
	}

	std::vector<UnitConversion> files{};
	for (const auto& it : std::filesystem::directory_iterator(folder)) {
		files.emplace_back(it);
	}
	Unit::SetConversionFiles(files);

	return nullptr;
}

void
OpenConversionFile::SetReferences(std::weak_ptr<infas::IFrontend> aFrontend) {
	myFrontend = std::move(aFrontend);
}
}  // namespace common

