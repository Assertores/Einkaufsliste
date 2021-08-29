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
		std::shared_ptr<interface::ICommand> aPrintCurrentFileCommand,
		std::shared_ptr<interface::ICommand> aChangeNameOfRecipeCommand,
		std::shared_ptr<interface::ICommand> aChangeDescriptionOfRecipeCommand,
		std::shared_ptr<interface::ICommand> aAddIngredientToRecipeCommand,
		std::shared_ptr<interface::ICommand> aRemoveIngredientToRecipeCommand)
		: myInput(aInput)
		, myOutput(aOutput)
		, myOpenRecipeCommand(std::move(aOpenRecipeCommand))
		, myPrintCurrentFileCommand(std::move(aPrintCurrentFileCommand))
		, myChangeNameOfRecipeCommand(std::move(aChangeNameOfRecipeCommand))
		, myChangeDescriptionOfRecipeCommand(std::move(aChangeDescriptionOfRecipeCommand))
		, myAddIngredientToRecipeCommand(std::move(aAddIngredientToRecipeCommand))
		, myRemoveIngredientToRecipeCommand(std::move(aRemoveIngredientToRecipeCommand)) {};

	std::filesystem::path AskForFile() override;
	std::filesystem::path AskForFolder() override;
	common::Unit AskForUnit() override;
	std::string AskForText() override;

	bool Poll() override;

private:
	std::istream& myInput;
	std::ostream& myOutput;
	std::shared_ptr<interface::ICommand> myOpenRecipeCommand;
	std::shared_ptr<interface::ICommand> myPrintCurrentFileCommand;
	std::shared_ptr<interface::ICommand> myChangeNameOfRecipeCommand;
	std::shared_ptr<interface::ICommand> myChangeDescriptionOfRecipeCommand;
	std::shared_ptr<interface::ICommand> myAddIngredientToRecipeCommand;
	std::shared_ptr<interface::ICommand> myRemoveIngredientToRecipeCommand;
};
} // namespace biz