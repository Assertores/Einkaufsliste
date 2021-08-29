#include "biz/application.h"

#include "biz/command_line_interface.h"
#include "common/change_recipe_name.h"
#include "common/open_recipe.h"
#include "common/print_current_file.h"
#include "interface/i_logger.h"

namespace biz {
Application::Application(const AppSettings& aSettings)
{
	switch (aSettings.frontendType)
	{
	case FrontendType::Cli: {
		auto openRecipe = common::OpenRecipe::Create();
		auto printFile = common::PrintCurrentFile::Create();
		auto changeRecipeName = common::ChangeRecipeName::Create();
		auto changeRecipeDescription =
			common::PrintCurrentFile::Create(); // TODO(andreas): impliment
		auto addRecipeIngrediant = common::PrintCurrentFile::Create(); // TODO(andreas): impliment
		auto removeRecipeIngrediant =
			common::PrintCurrentFile::Create(); // TODO(andreas): impliment

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
		changeRecipeName->SetReferences(myFrontend, myCurrentRecipe);
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
