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
		std::shared_ptr<interface::ICommand> aOpenRecipeCommand)
		: myInput(aInput)
		, myOutput(aOutput)
		, myOpenRecipeCommand(aOpenRecipeCommand) {};

	std::filesystem::path AskForFile() override;
	bool Poll() override;

private:
	std::istream& myInput;
	std::ostream& myOutput;
	std::shared_ptr<interface::ICommand> myOpenRecipeCommand;
};
} // namespace biz