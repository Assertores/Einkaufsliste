#pragma once

#include <iostream>

#include "interface/i_frontend.h"

namespace biz {
class CommandLineInterface : public interface::IFrontend
{
public:
	CommandLineInterface(std::istream& aInput, std::ostream& aOutput)
		: myInput(aInput)
		, myOutput(aOutput) {};

	std::filesystem::path AskForFile() override;
	bool Poll() override;

private:
	std::istream& myInput;
	std::ostream& myOutput;
};
} // namespace biz