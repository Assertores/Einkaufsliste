#include "biz/command_line_interface.h"

#include "interface/i_file_impl.h"
#include "interface/i_logger.h"

namespace biz {
std::filesystem::path
CommandLineInterface::AskForFile()
{
	std::filesystem::path path;
	do
	{
		myOutput << "please enter a file path: ";
		std::string pathBuffer;
		std::getline(myInput, pathBuffer);
		path = std::filesystem::path(pathBuffer);
	} while (!std::filesystem::is_regular_file(path));
	return path;
}

std::filesystem::path
CommandLineInterface::AskForFolder()
{
	std::filesystem::path path;
	do
	{
		myOutput << "please enter a folder path: ";
		std::string pathBuffer;
		std::getline(myInput, pathBuffer);
		path = std::filesystem::path(pathBuffer);
	} while (!std::filesystem::is_directory(path));
	return path;
}

common::Unit
CommandLineInterface::AskForUnit()
{
	std::string type;
	float amount = std::numeric_limits<float>::quiet_NaN();
	std::string unit;
	myOutput << "please enter the type of ingredient: ";
	myInput >> type;
	myOutput << "please enter the amount (without unit): ";
	myInput >> amount;
	myOutput << "please enter the unit: ";
	myInput >> unit;
	return { amount, unit, type };
}

std::string
CommandLineInterface::AskForText()
{
	std::string result;
	myOutput << "please enter your text: ";
	std::getline(myInput, result);
	return result;
}

common::WeekDay
CommandLineInterface::AskForWeekDay()
{
	common::WeekDay result {};
	std::string day;
	do
	{
		myOutput << "please enter a weekday: ";
		myInput >> day;
	} while (!FromString(day, result));
	return result;
}

common::DayTime
CommandLineInterface::AskForDayTime()
{
	common::DayTime result {};
	std::string time;
	do
	{
		myOutput << "please enter a time: ";
		std::getline(myInput, time);
	} while (!FromString(time, result));
	return result;
}

bool
CommandLineInterface::Poll()
{
	myOutput << "write command: ";
	std::string command;
	std::getline(myInput, command);
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
	if (command == "open recipe")
	{
		myCommandChain.AddCommand(myCommands.myOpenRecipeCommand->Execute());
		return false;
	}
	if (command == "change recipe name")
	{
		myCommandChain.AddCommand(myCommands.myChangeNameOfRecipeCommand->Execute());
		return false;
	}
	if (command == "change recipe description")
	{
		myCommandChain.AddCommand(myCommands.myChangeDescriptionOfRecipeCommand->Execute());
		return false;
	}
	if (command == "add recipe ingredient")
	{
		myCommandChain.AddCommand(myCommands.myAddIngredientToRecipeCommand->Execute());
		return false;
	}
	if (command == "remove recipe ingredient")
	{
		myCommandChain.AddCommand(myCommands.myRemoveIngredientToRecipeCommand->Execute());
		return false;
	}
	if (command == "print")
	{
		myCommandChain.AddCommand(myCommands.myPrintCurrentFileCommand->Execute());
		return false;
	}
	if (command == "open convertion")
	{
		myCommandChain.AddCommand(myCommands.myOpenConvertionCommand->Execute());
		return false;
	}
	if (command == "open week")
	{
		myCommandChain.AddCommand(myCommands.myOpenWeekCommand->Execute());
		return false;
	}
	if (command == "start list")
	{
		myCommandChain.AddCommand(myCommands.myStartList->Execute());
		return false;
	}
	if (command == "add week to list")
	{
		myCommandChain.AddCommand(myCommands.myAddWeekToListCommand->Execute());
		return false;
	}
	if (command == "add recipe to list")
	{
		myCommandChain.AddCommand(myCommands.myAddRecipeToListCommand->Execute());
		return false;
	}
	if (command == "compile")
	{
		myCommandChain.AddCommand(myCommands.myCompileListCommand->Execute());
		return false;
	}
	if (command == "add recipe to week")
	{
		myCommandChain.AddCommand(myCommands.myAddRecipeToWeekCommand->Execute());
		return false;
	}
	if (command == "remove recipe from week")
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
