#pragma once

#include <iostream>
#include <memory>

#include "interface/i_command.h"
#include "interface/i_frontend.h"

namespace biz {
class CommandLineInterface : public interface::IFrontend
{
public:
	CommandLineInterface(
		std::istream& aInput,
		std::ostream& aOutput,
		std::shared_ptr<interface::ICommand> aOpenRecipeCommand,
		std::shared_ptr<interface::ICommand> aPrintCurrentFileCommand)
		: myInput(aInput)
		, myOutput(aOutput)
		, myOpenRecipeCommand(aOpenRecipeCommand)
		, myPrintCurrentFileCommand(aPrintCurrentFileCommand) {};

	std::filesystem::path AskForFile() override;
	std::filesystem::path AskForFolder() override;
	common::Unit AskForUnit() override;
	bool Poll() override;

private:
	std::istream& myInput;
	std::ostream& myOutput;
	std::shared_ptr<interface::ICommand> myOpenRecipeCommand;
	std::shared_ptr<interface::ICommand> myPrintCurrentFileCommand;
};
} // namespace biz