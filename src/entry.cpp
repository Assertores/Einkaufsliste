#include "biz/entry.h"

#include "biz/application.h"
#include "biz/argument_parser.h"
#include "biz/github_updater.h"
#include "biz/log_on_console.h"
#include "biz/patcher.h"
#include "common/platform.h"
#include "interface/i_logger.h"

#include <sstream>

namespace biz {
int
Entry(const std::vector<std::string_view>& aArgs, std::ostream& aOutput, std::istream& aInput) {
	{
		biz::LogOnConsole logger(aOutput);
		infas::ILogger::SetLogLevel(infas::LogLevel::Error);
		infas::ILogger::SetLogMask(infas::locLogMaskAll);
		infas::ILogger::SetImplementation(std::move(logger));
	}

	AppSettings appSettings{true, FrontendType::Cli, aOutput, aInput};
	infas::UpdaterSettings updaterSettings{true, false, ""};
	PatcherSettings patcherSettings{true};

	InterpreteStartArguments(aArgs, appSettings, updaterSettings, patcherSettings);

	std::unique_ptr<infas::IUpdaterTemplateMethod> updater = nullptr;
	// NOTE(andreas): here we can deside whitch updater to use. currently there is only this one
	{
		if (!updaterSettings.url.empty()) {
			updater = std::make_unique<GithubUpdater>(updaterSettings.url);
		} else {
			updater = std::make_unique<GithubUpdater>();
		}
	}
	aOutput << "checking for updates ...\n";
	if (updater->Execute(updaterSettings)) {
		infas::ILogger::Log(
			infas::LogLevel::Debug,
			infas::LogType::StartUp,
			"update available, need to restart.");
		common::StartProcess(common::CurrentExe(), aArgs, std::filesystem::current_path());
		return 1;
	}
	Patch(patcherSettings);

	aOutput << "starting ...\n";
	Application app(appSettings);
	app.Run(appSettings);
	return 0;
}
}  // namespace biz
