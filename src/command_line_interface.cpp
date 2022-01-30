#include "biz/command_line_interface.h"

#include "interface/i_file_impl.h"
#include "interface/i_logger.h"

namespace biz {
CommandLineInterface::CommandLineInterface(
	std::istream& aInput, std::ostream& aOutput, CliCommands aCommands)
	: myInput(aInput)
	, myOutput(aOutput)
	, myCommands(std::move(aCommands)) {
	myInterpreter["undo"] = [this]() { myCommandChain.Undo(); };
	myInterpreter["redo"] = [this]() { myCommandChain.Redo(); };
	myInterpreter["open recipe"] = [this]() {
		myCommandChain.AddCommand(myCommands.myOpenRecipeCommand->Execute());
	};
	myInterpreter["change recipe name"] = [this]() {
		myCommandChain.AddCommand(myCommands.myChangeNameOfRecipeCommand->Execute());
	};
	myInterpreter["change recipe description"] = [this]() {
		myCommandChain.AddCommand(myCommands.myChangeDescriptionOfRecipeCommand->Execute());
	};
	myInterpreter["add recipe ingredient"] = [this]() {
		myCommandChain.AddCommand(myCommands.myAddIngredientToRecipeCommand->Execute());
	};
	myInterpreter["remove recipe ingredient"] = [this]() {
		myCommandChain.AddCommand(myCommands.myRemoveIngredientToRecipeCommand->Execute());
	};
	myInterpreter["print"] = [this]() {
		myCommandChain.AddCommand(myCommands.myPrintCurrentFileCommand->Execute());
	};
	myInterpreter["open conversion"] = [this]() {
		myCommandChain.AddCommand(myCommands.myOpenConversionCommand->Execute());
	};
	myInterpreter["open week"] = [this]() {
		myCommandChain.AddCommand(myCommands.myOpenWeekCommand->Execute());
	};
	myInterpreter["start list"] = [this]() {
		myCommandChain.AddCommand(myCommands.myStartList->Execute());
	};
	myInterpreter["add week to list"] = [this]() {
		myCommandChain.AddCommand(myCommands.myAddWeekToListCommand->Execute());
	};
	myInterpreter["add recipe to list"] = [this]() {
		myCommandChain.AddCommand(myCommands.myAddRecipeToListCommand->Execute());
	};
	myInterpreter["compile"] = [this]() {
		myCommandChain.AddCommand(myCommands.myCompileListCommand->Execute());
	};
	myInterpreter["add recipe to week"] = [this]() {
		myCommandChain.AddCommand(myCommands.myAddRecipeToWeekCommand->Execute());
	};
	myInterpreter["remove recipe from week"] = [this]() {
		myCommandChain.AddCommand(myCommands.myRemoveRecipeFromWeekCommand->Execute());
	};
	myInterpreter["help"] = [this]() {
		for (const auto& it : myInterpreter) {
			myOutput << it.first << '\n';
		}
	};
	// TODO: add functionality here
};

std::filesystem::path
CommandLineInterface::AskForFile() {
	myOutput << "please enter a file path: ";
	std::string pathBuffer;
	std::getline(myInput, pathBuffer);

	infas::ILogger::Log(
		infas::LogLevel::Verbose,
		infas::LogType::Frontend,
		"asked for file and returned: " + pathBuffer);
	return {pathBuffer};
}

std::filesystem::path
CommandLineInterface::AskForFolder() {
	myOutput << "please enter a folder path: ";
	std::string pathBuffer;
	std::getline(myInput, pathBuffer);

	infas::ILogger::Log(
		infas::LogLevel::Verbose,
		infas::LogType::Frontend,
		"asked for folder and returned: " + pathBuffer);
	return {pathBuffer};
}

common::Unit
CommandLineInterface::AskForUnit() {
	std::string type;
	std::string amount;
	std::string unit;
	myOutput << "please enter the type of ingredient: ";
	std::getline(myInput, type);
	myOutput << "please enter the amount (without unit): ";
	std::getline(myInput, amount);
	myOutput << "please enter the unit: ";
	std::getline(myInput, unit);

	infas::ILogger::Log(
		infas::LogLevel::Verbose,
		infas::LogType::Frontend,
		"asked for unit and returned: " + type + ", " + amount + ", " + unit);
	return {std::stof(amount), unit, type};
}

std::string
CommandLineInterface::AskForText() {
	std::string result;
	myOutput << "please enter your text: ";
	std::getline(myInput, result);

	infas::ILogger::Log(
		infas::LogLevel::Verbose,
		infas::LogType::Frontend,
		"asked for text and returned: " + result);
	return result;
}

bool
CommandLineInterface::AskForWeekDay(common::WeekDay& aOutWeekDay) {
	std::string day;
	myOutput << "please enter a weekday: ";
	std::getline(myInput, day);

	infas::ILogger::Log(
		infas::LogLevel::Verbose,
		infas::LogType::Frontend,
		"asked for weekday and returned: " + day);
	return FromString(day, aOutWeekDay);
}

bool
CommandLineInterface::AskForDayTime(common::DayTime& aOutDayTime) {
	std::string time;
	myOutput << "please enter a time: ";
	std::getline(myInput, time);

	infas::ILogger::Log(
		infas::LogLevel::Verbose,
		infas::LogType::Frontend,
		"asked for daytime and returned: " + time);
	return FromString(time, aOutDayTime);
}

bool
CommandLineInterface::Poll() {
	myOutput << "write command: ";
	std::string command;
	std::getline(myInput, command);

	infas::ILogger::Log(
		infas::LogLevel::Verbose,
		infas::LogType::Frontend,
		"read in next command: " + command);
	if (command == "exit" || command == "quit") {
		return true;
	}

	auto it = myInterpreter.find(command);
	if (it == myInterpreter.end()) {
		infas::ILogger::Log(
			infas::LogLevel::Error,
			infas::LogType::Commands,
			"command '" + command + "' is unknown.");

		return false;
	}
	it->second();
	return false;
}
} // namespace biz
