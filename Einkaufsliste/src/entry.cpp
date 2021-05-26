#include "biz/entry.h"

#include "biz/application.h"
#include "biz/argument_parser.h"
#include "biz/patcher.h"
#include "biz/updater.h"
#include "interface/i_logger.h"

namespace biz {
int
Entry(const std::vector<std::string_view>& aArgs, std::istream& aInput, std::ostream& aOutput)
{
	{
		interface::fake::Logger logger;
		logger.SetLog(interface::LogLevel::Error, interface::LogType_All);
		interface::ILogger::SetInstance(std::move(logger));
	}

	AppSettings appSettings {};
	UpdaterSettings updaterSettings {};
	PatcherSettings patcherSettings {};

	InterpreteStartArguments(aArgs, appSettings, updaterSettings, patcherSettings);
	Update(updaterSettings);
	Patch(patcherSettings);
	Run(appSettings);
	return 0;
}
} // namespace biz
