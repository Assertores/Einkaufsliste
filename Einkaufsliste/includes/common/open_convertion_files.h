#pragma once

#include "interface/i_command.h"
#include "interface/i_frontend.h"

namespace common {
class OpenConvertionFile : public interface::ICommand
{
public:
	std::unique_ptr<interface::ICommandMemento> Execute() override;

private:
	std::weak_ptr<interface::IFrontend> myFrontend;
};
} // namespace common
