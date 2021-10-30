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
	std::shared_ptr<interface::ICommand> myCompileListCommand;
	std::shared_ptr<interface::ICommand> myAddRecipeToWeekCommand;
	std::shared_ptr<interface::ICommand> myRemoveRecipeFromWeekCommand;
};

class CommandLineInterface : public interface::IFrontend
{
public:
	CommandLineInterface(std::istream& aInput, std::ostream& aOutput)
		: myInput(aInput)
		, myOutput(aOutput) {};

	void SetCommands(CliCommands aCommands) { myCommands = std::move(aCommands); }

	std::filesystem::path AskForFile() override;
	std::filesystem::path AskForFolder() override;
	common::Unit AskForUnit() override;
	std::string AskForText() override;

	bool Poll() override;

private:
	std::istream& myInput;
	std::ostream& myOutput;
	common::CommandChain myCommandChain;
	CliCommands myCommands;
};
} // namespace biz