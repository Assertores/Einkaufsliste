#include "biz/open_recipe.h"

#include "common/recipe.h"

namespace common {
void
OpenRecipe::SetReferences(
	std::weak_ptr<infas::IFrontend> aFrontend,
	std::weak_ptr<common::Observable<std::optional<common::Recipe>>> aRecipeObservable) {
	myFrontend = std::move(aFrontend);
	myRecipeObservable = std::move(aRecipeObservable);
}

std::unique_ptr<infas::ICommandMemento>
OpenRecipe::Execute() {
	auto frontend = myFrontend.lock();
	if (!frontend) {
		return nullptr;
	}
	auto recipeObservable = myRecipeObservable.lock();
	if (!recipeObservable) {
		return nullptr;
	}
	std::filesystem::path file = frontend->AskForFile();
	while (file.extension().empty()) {
		infas::ILogger::Log(infas::LogLevel::Error, infas::LogType::Commands, "invalid input");
		file = frontend->AskForFile();
	}
	recipeObservable->Set(Recipe(file));

	return nullptr;
}
}  // namespace common
