#pragma once

#include <memory>

#include "interface/i_command.h"
#include "interface/i_frontend.h"
#include "interface/i_hub.h"

namespace common {
class OpenRecipe : public interface::ICommand
{
public:
	OpenRecipe(std::weak_ptr<interface::IFrontend> aFrontend, std::weak_ptr<interface::IHub> aHub)
		: myFrontend(std::move(aFrontend))
		, myHub(std::move(aHub)) {};

	virtual std::unique_ptr<ICommand> Clone() override;
	virtual bool DoExecute() override;

private:
	std::weak_ptr<interface::IFrontend> myFrontend;
	std::weak_ptr<interface::IHub> myHub;
};
} // namespace common
