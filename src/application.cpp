#include "biz/application.h"

#include "biz/add_list_recipe.h"
#include "biz/add_list_week.h"
#include "biz/add_recipe_unit.h"
#include "biz/add_week_recipe.h"
#include "biz/change_recipe_description.h"
#include "biz/change_recipe_name.h"
#include "biz/command_line_interface.h"
#include "biz/compile_list.h"
#include "biz/open_convertion_files.h"
#include "biz/open_list.h"
#include "biz/open_recipe.h"
#include "biz/open_week.h"
#include "biz/print_current_file.h"
#include "biz/remove_recipe_unit.h"
#include "biz/remove_week_recipe.h"
#include "interface/i_file_impl.h"
#include "interface/i_logger.h"

namespace biz {
Application::Application(const AppSettings& aSettings) {
	interface::ILogger::Log(
		interface::LogLevel::Verbose,
		interface::LogType::StartUp,
		"application creation started");
	switch (aSettings.frontendType) {
	case FrontendType::Cli: {
		auto openRecipe = common::OpenRecipe::Create();
		auto printFile = common::PrintCurrentFile::Create();
		auto changeRecipeName = common::ChangeRecipeName::Create();
		auto changeRecipeDescription = common::ChangeRecipeDescription::Create();
		auto addRecipeIngrediant = common::AddRecipeUnit::Create();
		auto removeRecipeIngrediant = common::RemoveRecipeUnit::Create();
		auto openConvertion = common::OpenConvertionFile::Create();
		auto openWeek = common::OpenWeek::Create();
		auto startNewList = common::OpenList::Create();
		auto addListWeek = common::AddListWeek::Create();
		auto addListRecipe = common::AddListRecipe::Create();
		auto compileList = common::CompileList::Create();
		auto addWeekRecipe = common::AddWeekRecipe::Create();
		auto removeWeekRecipe = common::RemoveWeekRecipe::Create();
		CliCommands commands{
			.myOpenRecipeCommand = openRecipe,
			.myPrintCurrentFileCommand = printFile,
			.myChangeNameOfRecipeCommand = changeRecipeName,
			.myChangeDescriptionOfRecipeCommand = changeRecipeDescription,
			.myAddIngredientToRecipeCommand = addRecipeIngrediant,
			.myRemoveIngredientToRecipeCommand = removeRecipeIngrediant,
			.myOpenConvertionCommand = openConvertion,
			.myOpenWeekCommand = openWeek,
			.myStartList = startNewList,
			.myAddWeekToListCommand = addListWeek,
			.myAddRecipeToListCommand = addListRecipe,
			.myCompileListCommand = compileList,
			.myAddRecipeToWeekCommand = addWeekRecipe,
			.myRemoveRecipeFromWeekCommand = removeWeekRecipe};

		interface::ILogger::Log(
			interface::LogLevel::Verbose,
			interface::LogType::StartUp,
			"commands created");

		myFrontend =
			std::make_shared<CommandLineInterface>(aSettings.input, aSettings.output, commands);

		interface::ILogger::Log(
			interface::LogLevel::Verbose,
			interface::LogType::StartUp,
			"frontend created");

		openRecipe->SetReferences(myFrontend, myCurrentRecipe);
		printFile->SetReferences(&aSettings.output, myCurrentRecipe, myCurrentWeek, myCurrentList);
		changeRecipeName->SetReferences(myFrontend, myCurrentRecipe);
		changeRecipeDescription->SetReferences(myFrontend, myCurrentRecipe);
		addRecipeIngrediant->SetReferences(myFrontend, myCurrentRecipe);
		removeRecipeIngrediant->SetReferences(myFrontend, myCurrentRecipe);
		openConvertion->SetReferences(myFrontend);
		openWeek->SetReferences(myFrontend, myCurrentWeek);
		startNewList->SetReferences(myFrontend, myCurrentList);
		addListWeek->SetReferences(myFrontend, myCurrentList);
		addListRecipe->SetReferences(myFrontend, myCurrentList);
		compileList->SetReferences(myCurrentList);
		addWeekRecipe->SetReferences(myFrontend, myCurrentWeek);
		removeWeekRecipe->SetReferences(myFrontend, myCurrentWeek);

		interface::ILogger::Log(
			interface::LogLevel::Verbose,
			interface::LogType::StartUp,
			"commands set up");
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
Application::Run(const AppSettings& aSettings) {
	if (!aSettings.doRun) {
		interface::ILogger::Log(
			interface::LogLevel::Debug,
			interface::LogType::Generic,
			"asked to imediatley shut down");
		return;
	}
	while (!myFrontend->Poll()) {
		interface::ILogger::Log(
			interface::LogLevel::Verbose,
			interface::LogType::Generic,
			"poll again");
	}

	interface::ILogger::Log(
		interface::LogLevel::Debug,
		interface::LogType::Generic,
		"shutting down");
	interface::IFileImpl::Clear();
	interface::ILogger::Clear();
}
}  // namespace biz
