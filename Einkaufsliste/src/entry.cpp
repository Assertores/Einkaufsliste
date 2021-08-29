#include "biz/entry.h"

#include "biz/application.h"
#include "biz/argument_parser.h"
#include "biz/patcher.h"
#include "biz/updater.h"
#include "common/log_on_console.h"
#include "interface/i_logger.h"

static constexpr std::string_view locDefaultUrl =
	"https://api.github.com/repos/Assertores/Einkaufsliste/releases/latest";

namespace biz {
int
Entry(const std::vector<std::string_view>& aArgs, std::ostream& aOutput, std::istream& aInput)
{
	{
		common::LogOnConsole logger(aOutput);
		interface::ILogger::SetLogLevel(interface::LogLevel::Error);
		interface::ILogger::SetLogMask(interface::locLogMaskAll);
		interface::ILogger::SetImplimentation(std::move(logger));
	}

	AppSettings appSettings { true, FrontendType::Cli, aOutput, aInput };
	UpdaterSettings updaterSettings { true, false, locDefaultUrl.data() };
	PatcherSettings patcherSettings { true };

	InterpreteStartArguments(aArgs, appSettings, updaterSettings, patcherSettings);
	aOutput << "checking for updates ...\n";
	if (Update(updaterSettings))
	{
		// TODO(andreas): restart application
		return 1;
	}
	Patch(patcherSettings);
	aOutput << "starting ...\n";
	Application app(appSettings);
	app.Run(appSettings);
	return 0;
}
} // namespace biz
