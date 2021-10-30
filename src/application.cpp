#include "biz/application.h"

#include "biz/add_recipe_unit.h"
#include "biz/change_recipe_description.h"
#include "biz/change_recipe_name.h"
#include "biz/command_line_interface.h"
#include "biz/open_convertion_files.h"
#include "biz/open_recipe.h"
#include "biz/print_current_file.h"
#include "biz/remove_recipe_unit.h"
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
		auto changeRecipeDescription = common::ChangeRecipeDescription::Create();
		auto addRecipeIngrediant = common::AddRecipeUnit::Create();
		auto removeRecipeIngrediant = common::RemoveRecipeUnit::Create();
		auto openConvertion = common::OpenConvertionFile::Create();
		auto openWeek = common::RemoveRecipeUnit::Create();
		auto compile = common::RemoveRecipeUnit::Create();
		auto addWeekRecipe = common::RemoveRecipeUnit::Create();
		auto removeWeekRecipe = common::RemoveRecipeUnit::Create();
		CliCommands commands { .myOpenRecipeCommand = openRecipe,
							   .myPrintCurrentFileCommand = printFile,
							   .myChangeNameOfRecipeCommand = changeRecipeName,
							   .myChangeDescriptionOfRecipeCommand = changeRecipeDescription,
							   .myAddIngredientToRecipeCommand = addRecipeIngrediant,
							   .myRemoveIngredientToRecipeCommand = removeRecipeIngrediant,
							   .myOpenConvertionCommand = openConvertion,
							   .myOpenWeekCommand = openWeek,
							   .myCompileListCommand = compile,
							   .myAddRecipeToWeekCommand = addWeekRecipe,
							   .myRemoveRecipeFromWeekCommand = removeWeekRecipe };

		myFrontend =
			std::make_shared<CommandLineInterface>(aSettings.input, aSettings.output, commands);

		openRecipe->SetReferences(myFrontend, myCurrentRecipe);
		printFile->SetReferences(&aSettings.output, myCurrentRecipe);
		changeRecipeName->SetReferences(myFrontend, myCurrentRecipe);
		changeRecipeDescription->SetReferences(myFrontend, myCurrentRecipe);
		addRecipeIngrediant->SetReferences(myFrontend, myCurrentRecipe);
		removeRecipeIngrediant->SetReferences(myFrontend, myCurrentRecipe);
		openConvertion->SetReferences(myFrontend);
		openWeek->SetReferences(myFrontend, myCurrentRecipe);
		compile->SetReferences(myFrontend, myCurrentRecipe);
		addWeekRecipe->SetReferences(myFrontend, myCurrentRecipe);
		removeWeekRecipe->SetReferences(myFrontend, myCurrentRecipe);
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
