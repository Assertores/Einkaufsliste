#pragma once

#include "interface/i_command.h"
#include "interface/i_frontend.h"

namespace common {
class OpenConversionFile : public infas::ICommand {
public:
	static std::shared_ptr<OpenConversionFile> Create() {
		return std::make_shared<OpenConversionFile>();
	}

	std::unique_ptr<infas::ICommandMemento> Execute() override;

	void SetReferences(std::weak_ptr<infas::IFrontend> aFrontend);

	// protected:
	// OpenConversionFile() = default;

private:
	std::weak_ptr<infas::IFrontend> myFrontend;
};
}  // namespace common
