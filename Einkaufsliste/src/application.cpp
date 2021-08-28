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
		auto changeRecipeName =
			std::make_shared<common::PrintCurrentFile>(); // TODO(andreas): impliment
		auto changeRecipeDescription =
			std::make_shared<common::PrintCurrentFile>(); // TODO(andreas): impliment
		auto addRecipeIngrediant =
			std::make_shared<common::PrintCurrentFile>(); // TODO(andreas): impliment
		auto removeRecipeIngrediant =
			std::make_shared<common::PrintCurrentFile>(); // TODO(andreas): impliment
		myFrontend = std::make_shared<CommandLineInterface>(
			aSettings.input,
			aSettings.output,
			openRecipe,
			printFile,
			changeRecipeName,
			changeRecipeDescription,
			addRecipeIngrediant,
			removeRecipeIngrediant);
		openRecipe->SetReferences(myFrontend, myCurrentRecipe);
		printFile->SetReferences(&aSettings.output, myCurrentRecipe);
		changeRecipeName->SetReferences(
			&aSettings.output,
			myCurrentRecipe); // TODO(andreas): impliment
		changeRecipeDescription->SetReferences(
			&aSettings.output,
			myCurrentRecipe); // TODO(andreas): impliment
		addRecipeIngrediant->SetReferences(
			&aSettings.output,
			myCurrentRecipe); // TODO(andreas): impliment
		removeRecipeIngrediant->SetReferences(
			&aSettings.output,
			myCurrentRecipe); // TODO(andreas): impliment
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
