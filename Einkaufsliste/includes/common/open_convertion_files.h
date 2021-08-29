#pragma once

#include "interface/i_command.h"
#include "interface/i_frontend.h"

namespace common {
class OpenConvertionFile : public interface::ICommand
{
public:
	static std::shared_ptr<OpenConvertionFile> Create()
	{
		return std::make_shared<OpenConvertionFile>();
	}

	std::unique_ptr<interface::ICommandMemento> Execute() override;

	// protected:
	// OpenConvertionFile() = default;

private:
	std::weak_ptr<interface::IFrontend> myFrontend;
};
} // namespace common
