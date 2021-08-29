#include "biz/command_line_interface.h"

#include "common/open_recipe.h"
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
	return common::Unit(
		3,
		"fake",
		"kg",
		common::UnitConvertion(std::make_shared<interface::fake::FileImpl>()));
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
		myCommandChain.AddCommand(myOpenRecipeCommand->Execute());
		return false;
	}
	if (command == "change-recipe-name")
	{
		myCommandChain.AddCommand(myChangeNameOfRecipeCommand->Execute());
		return false;
	}
	if (command == "change-recipe-description")
	{
		myCommandChain.AddCommand(myChangeDescriptionOfRecipeCommand->Execute());
		return false;
	}
	if (command == "add-recipe-ingredient")
	{
		myCommandChain.AddCommand(myAddIngredientToRecipeCommand->Execute());
		return false;
	}
	if (command == "remove-recipe-ingredient")
	{
		myCommandChain.AddCommand(myRemoveIngredientToRecipeCommand->Execute());
		return false;
	}
	if (command == "print")
	{
		myCommandChain.AddCommand(myPrintCurrentFileCommand->Execute());
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
