#pragma once

#include <memory>
#include <iostream>

#include "common/observable.h"
#include "common/recipe.h"
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
	Application(const AppSettings& aSettings);

	void Run(const AppSettings& aSettings);

private:
	std::shared_ptr<interface::IFrontend> myFrontend;

	common::Observable<common::Recipe> currentRecipe;
};
} // namespace biz
