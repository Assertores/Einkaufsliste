#include "biz/command_line_interface.h"

#include "interface/i_file_impl.h"
#include "interface/i_logger.h"

namespace biz {
std::filesystem::path
CommandLineInterface::AskForFile()
{
	std::filesystem::path path;
	myOutput << "please enter a file path: ";
	myInput >> path;
	return path;
}

std::filesystem::path
CommandLineInterface::AskForFolder()
{
	std::filesystem::path path;
	myOutput << "please enter a folder path: ";
	myInput >> path;
	return path;
}

common::Unit
CommandLineInterface::AskForUnit()
{
	interface::ILogger::Log(
		interface::LogLevel::Fatal,
		interface::LogType::Commands,
		"not implimented");
	return { 3,
			 "kg",
			 "fake",
			 common::UnitConvertion(std::make_shared<interface::fake::FileImpl>()) };
}

std::string
CommandLineInterface::AskForText()
{
	std::string result;
	myOutput << "please enter your text (without white space characters): ";
	myInput >> result;
	return result;
}

bool
CommandLineInterface::Poll()
{
	myOutput << "write command: ";
	std::string command;
	myInput >> command;
	if (command == "exit" || command == "quit")
	{
		return true;
	}
	// TODO(andreas): help
	if (command == "undo")
	{
		myCommandChain.Undo();
		return false;
	}
	if (command == "redo")
	{
		myCommandChain.Redo();
		return false;
	}
	if (command == "open-recipe")
	{
		myCommandChain.AddCommand(myCommands.myOpenRecipeCommand->Execute());
		return false;
	}
	if (command == "change-recipe-name")
	{
		myCommandChain.AddCommand(myCommands.myChangeNameOfRecipeCommand->Execute());
		return false;
	}
	if (command == "change-recipe-description")
	{
		myCommandChain.AddCommand(myCommands.myChangeDescriptionOfRecipeCommand->Execute());
		return false;
	}
	if (command == "add-recipe-ingredient")
	{
		myCommandChain.AddCommand(myCommands.myAddIngredientToRecipeCommand->Execute());
		return false;
	}
	if (command == "remove-recipe-ingredient")
	{
		myCommandChain.AddCommand(myCommands.myRemoveIngredientToRecipeCommand->Execute());
		return false;
	}
	if (command == "print")
	{
		myCommandChain.AddCommand(myCommands.myPrintCurrentFileCommand->Execute());
		return false;
	}
	if (command == "open-convertion")
	{
		myCommandChain.AddCommand(myCommands.myOpenConvertionCommand->Execute());
		return false;
	}
	if (command == "open-week")
	{
		myCommandChain.AddCommand(myCommands.myOpenWeekCommand->Execute());
		return false;
	}
	if (command == "compile")
	{
		myCommandChain.AddCommand(myCommands.myCompileListCommand->Execute());
		return false;
	}
	if (command == "add-recipe-to-week")
	{
		myCommandChain.AddCommand(myCommands.myAddRecipeToWeekCommand->Execute());
		return false;
	}
	if (command == "remove-recipe-from-week")
	{
		myCommandChain.AddCommand(myCommands.myRemoveRecipeFromWeekCommand->Execute());
		return false;
	}
	// TODO: add funktionality here

	interface::ILogger::Log(
		interface::LogLevel::Error,
		interface::LogType::Commands,
		"command '" + command + "' is unknowen.");

	return false;
}
} // namespace biz
