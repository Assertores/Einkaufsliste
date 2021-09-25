#pragma once

#include <iostream>
#include <memory>
#include <optional>

#include "common/observable.h"
#include "common/recipe.h"
#include "interface/i_command.h"
#include "interface/i_frontend.h"

namespace biz {
enum class FrontendType
{
	Cli,
};
struct AppSettings
{
	bool doRun;
	FrontendType frontendType;
	std::ostream& output;
	std::istream& input;
};

class Application
{
public:
	explicit Application(const AppSettings& aSettings);

	void Run(const AppSettings& aSettings);

private:
	std::shared_ptr<interface::IFrontend> myFrontend;

	std::shared_ptr<common::Observable<std::optional<common::Recipe>>> myCurrentRecipe =
		std::make_shared<common::Observable<std::optional<common::Recipe>>>();
};
} // namespace biz
