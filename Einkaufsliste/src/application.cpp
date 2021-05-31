#include "biz/application.h"

#include "biz/command_line_interface.h"
#include "common/open_recipe.h"
#include "common/print_current_file.h"
#include "interface/i_logger.h"

namespace biz {
Application::Application(const AppSettings& aSettings)
{
	switch (aSettings.frontendType)
	{
	case FrontendType::Cli: {
		auto openRecipe = std::make_shared<common::OpenRecipe>();
		auto printFile = std::make_shared<common::PrintCurrentFile>();
		myFrontend = std::make_shared<CommandLineInterface>(
			aSettings.input,
			aSettings.output,
			openRecipe,
			printFile);
		openRecipe->SetReferences(myFrontend, myCurrentRecipe);
		printFile->SetReferences(&aSettings.output, myCurrentRecipe);
		break;
	}
	default:
		interface::ILogger::Log(
			interface::LogLevel::Fatal,
			interface::LogType::StartUp,
			"unhandled frontend setting!");
		break;
	}
}

void
Application::Run(const AppSettings& aSettings)
{
	if (!aSettings.doRun)
	{
		return;
	}
	while (!myFrontend->Poll())
	{
	}
}
} // namespace biz
