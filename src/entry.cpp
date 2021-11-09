#include "biz/entry.h"

#include "biz/application.h"
#include "biz/argument_parser.h"
#include "biz/github_updater.h"
#include "biz/log_on_console.h"
#include "biz/patcher.h"
#include "interface/i_logger.h"

#include <sstream>

static constexpr std::string_view locDefaultUrl =
	"https://api.github.com/repos/Assertores/Einkaufsliste/releases/latest";

namespace biz {
int
Entry(const std::vector<std::string_view>& aArgs, std::ostream& aOutput, std::istream& aInput) {
	{
		common::LogOnConsole logger(aOutput);
		infas::ILogger::SetLogLevel(infas::LogLevel::Error);
		infas::ILogger::SetLogMask(infas::locLogMaskAll);
		infas::ILogger::SetImplimentation(std::move(logger));
	}

	AppSettings appSettings{true, FrontendType::Cli, aOutput, aInput};
	common::UpdaterSettings updaterSettings{true, false, locDefaultUrl.data()};
	PatcherSettings patcherSettings{true};

	InterpreteStartArguments(aArgs, appSettings, updaterSettings, patcherSettings);
	aOutput << "checking for updates ...\n";
	std::unique_ptr<common::UpdaterTemplateMethode> updater = nullptr;
	// NOTE(andreas): here we can deside whitch updater to use. currently there is only this one
	updater = std::make_unique<GithubUpdater>();
	if (updater->Execute(updaterSettings)) {
		infas::ILogger::Log(
			infas::LogLevel::Debug,
			infas::LogType::StartUp,
			"update available, need to restart.");
		std::stringstream stringBuilder{};
		for (const auto& it : aArgs) {
			stringBuilder << it << ' ';
		}
		// TODO(andreas): make this run in a non sub process
		std::system(stringBuilder.str().c_str());  // NOLINT
		return 1;
	}
	Patch(patcherSettings);
	aOutput << "starting ...\n";
	Application app(appSettings);
	app.Run(appSettings);
	return 0;
}
}  // namespace biz
