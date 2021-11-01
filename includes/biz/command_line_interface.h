#pragma once

#include "common/command_chain.h"
#include "interface/i_command.h"
#include "interface/i_frontend.h"

#include <functional>
#include <iostream>
#include <map>
#include <memory>
#include <string_view>

namespace biz {
struct CliCommands {
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

class CommandLineInterface : public interface::IFrontend {
public:
	CommandLineInterface(std::istream& aInput, std::ostream& aOutput, CliCommands aCommands);

	[[nodiscard]] std::filesystem::path AskForFile() override;
	[[nodiscard]] std::filesystem::path AskForFolder() override;
	[[nodiscard]] common::Unit AskForUnit() override;
	[[nodiscard]] std::string AskForText() override;
	[[nodiscard]] bool AskForWeekDay(common::WeekDay& aOutWeekDay) override;
	[[nodiscard]] bool AskForDayTime(common::DayTime& aOutDayTime) override;

	bool Poll() override;

private:
	std::istream& myInput;
	std::ostream& myOutput;
	common::CommandChain myCommandChain;
	CliCommands myCommands;
	std::map<std::string_view, std::function<void()>> myInterpreter;
};
}  // namespace biz
