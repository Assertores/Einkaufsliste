#include "biz/application.h"

#include "biz/add_list_recipe.h"
#include "biz/add_list_week.h"
#include "biz/add_recipe_unit.h"
#include "biz/add_week_recipe.h"
#include "biz/change_recipe_description.h"
#include "biz/change_recipe_name.h"
#include "biz/command_line_interface.h"
#include "biz/compile_list.h"
#include "biz/open_conversion_files.h"
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
	infas::ILogger::Log(
		infas::LogLevel::Verbose,
		infas::LogType::StartUp,
		"application creation started");
	switch (aSettings.frontendType) {
	case FrontendType::Cli: {
		auto openRecipe = biz::OpenRecipe::Create();
		auto printFile = biz::PrintCurrentFile::Create();
		auto changeRecipeName = biz::ChangeRecipeName::Create();
		auto changeRecipeDescription = biz::ChangeRecipeDescription::Create();
		auto addRecipeIngrediant = biz::AddRecipeUnit::Create();
		auto removeRecipeIngrediant = biz::RemoveRecipeUnit::Create();
		auto openConversion = biz::OpenConversionFile::Create();
		auto openWeek = biz::OpenWeek::Create();
		auto startNewList = biz::OpenList::Create();
		auto addListWeek = biz::AddListWeek::Create();
		auto addListRecipe = biz::AddListRecipe::Create();
		auto compileList = biz::CompileList::Create();
		auto addWeekRecipe = biz::AddWeekRecipe::Create();
		auto removeWeekRecipe = biz::RemoveWeekRecipe::Create();
		CliCommands commands{
			openRecipe,
			printFile,
			changeRecipeName,
			changeRecipeDescription,
			addRecipeIngrediant,
			removeRecipeIngrediant,
			openConversion,
			openWeek,
			startNewList,
			addListWeek,
			addListRecipe,
			compileList,
			addWeekRecipe,
			removeWeekRecipe};

		infas::ILogger::Log(infas::LogLevel::Verbose, infas::LogType::StartUp, "commands created");

		myFrontend =
			std::make_shared<CommandLineInterface>(aSettings.input, aSettings.output, commands);

		infas::ILogger::Log(infas::LogLevel::Verbose, infas::LogType::StartUp, "frontend created");

		openRecipe->SetReferences(myFrontend, myCurrentRecipe);
		printFile->SetReferences(&aSettings.output, myCurrentRecipe, myCurrentWeek, myCurrentList);
		changeRecipeName->SetReferences(myFrontend, myCurrentRecipe);
		changeRecipeDescription->SetReferences(myFrontend, myCurrentRecipe);
		addRecipeIngrediant->SetReferences(myFrontend, myCurrentRecipe);
		removeRecipeIngrediant->SetReferences(myFrontend, myCurrentRecipe);
		openConversion->SetReferences(myFrontend);
		openWeek->SetReferences(myFrontend, myCurrentWeek);
		startNewList->SetReferences(myFrontend, myCurrentList);
		addListWeek->SetReferences(myFrontend, myCurrentList);
		addListRecipe->SetReferences(myFrontend, myCurrentList);
		compileList->SetReferences(myCurrentList);
		addWeekRecipe->SetReferences(myFrontend, myCurrentWeek);
		removeWeekRecipe->SetReferences(myFrontend, myCurrentWeek);

		infas::ILogger::Log(infas::LogLevel::Verbose, infas::LogType::StartUp, "commands set up");
		break;
	}
	default:
		infas::ILogger::Log(
			infas::LogLevel::Fatal,
			infas::LogType::StartUp,
			"unhandled frontend setting!");
		break;
	}
}

void
Application::Run(const AppSettings& aSettings) {
	if (!aSettings.doRun) {
		infas::ILogger::Log(
			infas::LogLevel::Debug,
			infas::LogType::Generic,
			"asked to imediatley shut down");
		return;
	}
	while (!myFrontend->Poll()) {
		infas::ILogger::Log(infas::LogLevel::Verbose, infas::LogType::Generic, "poll again");
	}

	infas::ILogger::Log(infas::LogLevel::Debug, infas::LogType::Generic, "shutting down");
	infas::IFileImpl::Clear();
	infas::ILogger::Clear();
}
} // namespace biz
