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
	std::shared_ptr<infas::ICommand> myOpenRecipeCommand;
	std::shared_ptr<infas::ICommand> myPrintCurrentFileCommand;
	std::shared_ptr<infas::ICommand> myChangeNameOfRecipeCommand;
	std::shared_ptr<infas::ICommand> myChangeDescriptionOfRecipeCommand;
	std::shared_ptr<infas::ICommand> myAddIngredientToRecipeCommand;
	std::shared_ptr<infas::ICommand> myRemoveIngredientToRecipeCommand;
	std::shared_ptr<infas::ICommand> myOpenConversionCommand;
	std::shared_ptr<infas::ICommand> myOpenWeekCommand;
	std::shared_ptr<infas::ICommand> myStartList;
	std::shared_ptr<infas::ICommand> myAddWeekToListCommand;
	std::shared_ptr<infas::ICommand> myAddRecipeToListCommand;
	std::shared_ptr<infas::ICommand> myCompileListCommand;
	std::shared_ptr<infas::ICommand> myAddRecipeToWeekCommand;
	std::shared_ptr<infas::ICommand> myRemoveRecipeFromWeekCommand;
};

class CommandLineInterface : public infas::IFrontend {
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

