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
#if false // TODO(andreas): reimpliment
	if (command == "exit" || command == "quit")
	{
		return true;
	}
	if (command == "undo")
	{
		interface::ICommand::Revert();
		return true;
	}
	if (command == "redo")
	{
		interface::ICommand::ReExecute();
		return true;
	}
	if (command == "open-recipe")
	{
		interface::ICommand::Execute(myOpenRecipeCommand->Clone());
		return false;
	}
	if (command == "change-recipe-name")
	{
		interface::ICommand::Execute(myChangeNameOfRecipeCommand->Clone());
		return false;
	}
	if (command == "change-recipe-description")
	{
		interface::ICommand::Execute(myChangeDescriptionOfRecipeCommand->Clone());
		return false;
	}
	if (command == "add-recipe-ingredient")
	{
		interface::ICommand::Execute(myAddIngredientToRecipeCommand->Clone());
		return false;
	}
	if (command == "remove-recipe-ingredient")
	{
		interface::ICommand::Execute(myRemoveIngredientToRecipeCommand->Clone());
		return false;
	}
	if (command == "print")
	{
		interface::ICommand::Execute(myPrintCurrentFileCommand->Clone());
		return false;
	}
	// TODO: add funktionality here
#endif

	interface::ILogger::Log(
		interface::LogLevel::Error,
		interface::LogType::Commands,
		"command '" + command + "' is unknowen.");

	return false;
}
} // namespace biz
