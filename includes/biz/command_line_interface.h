#pragma once

#include <iostream>
#include <memory>

#include "common/command_chain.h"
#include "interface/i_command.h"
#include "interface/i_frontend.h"

namespace biz {
struct CliCommands
{
	std::shared_ptr<interface::ICommand> myOpenRecipeCommand;
	std::shared_ptr<interface::ICommand> myPrintCurrentFileCommand;
	std::shared_ptr<interface::ICommand> myChangeNameOfRecipeCommand;
	std::shared_ptr<interface::ICommand> myChangeDescriptionOfRecipeCommand;
	std::shared_ptr<interface::ICommand> myAddIngredientToRecipeCommand;
	std::shared_ptr<interface::ICommand> myRemoveIngredientToRecipeCommand;
	std::shared_ptr<interface::ICommand> myOpenConvertionCommand;
	std::shared_ptr<interface::ICommand> myOpenWeekCommand;
	std::shared_ptr<interface::ICommand> myStartList;
	std::shared_ptr<interface::ICommand> myAddWeekToListCommand;
	std::shared_ptr<interface::ICommand> myAddRecipeToListCommand;
	std::shared_ptr<interface::ICommand> myCompileListCommand;
	std::shared_ptr<interface::ICommand> myAddRecipeToWeekCommand;
	std::shared_ptr<interface::ICommand> myRemoveRecipeFromWeekCommand;
};

class CommandLineInterface : public interface::IFrontend
{
public:
	CommandLineInterface(std::istream& aInput, std::ostream& aOutput, CliCommands aCommands)
		: myInput(aInput)
		, myOutput(aOutput)
		, myCommands(std::move(aCommands)) {};

	[[nodiscard]] std::filesystem::path AskForFile() override;
	[[nodiscard]] std::filesystem::path AskForFolder() override;
	[[nodiscard]] common::Unit AskForUnit() override;
	[[nodiscard]] std::string AskForText() override;
	[[nodiscard]] common::WeekDay AskForWeekDay() override;
	[[nodiscard]] common::DayTime AskForDayTime() override;

	bool Poll() override;

private:
	std::istream& myInput;
	std::ostream& myOutput;
	common::CommandChain myCommandChain;
	CliCommands myCommands;
};
} // namespace biz