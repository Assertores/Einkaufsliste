#pragma once

#include "interface/i_command.h"
#include "interface/i_frontend.h"

namespace common {
class OpenConvertionFile : public infas::ICommand {
public:
	static std::shared_ptr<OpenConvertionFile> Create() {
		return std::make_shared<OpenConvertionFile>();
	}

	std::unique_ptr<infas::ICommandMemento> Execute() override;

	void SetReferences(std::weak_ptr<infas::IFrontend> aFrontend);

	// protected:
	// OpenConvertionFile() = default;

private:
	std::weak_ptr<infas::IFrontend> myFrontend;
};
}  // namespace common
