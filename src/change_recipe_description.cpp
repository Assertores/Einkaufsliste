#include "biz/change_recipe_description.h"

namespace common {

class ChangeRecipeDescriptionMemento : public interface::ICommandMemento {
public:
	ChangeRecipeDescriptionMemento(
		Recipe aRecipe, std::string aNewDescription, std::string aPrevDescription)
		: myRecipe(std::move(aRecipe))
		, myNewDescription(std::move(aNewDescription))
		, myPrevDescription(std::move(aPrevDescription)){};

	void ReExecute() override { myRecipe.SetDescription(myNewDescription); }

	void Revert() override { myRecipe.SetDescription(myPrevDescription); }

private:
	Recipe myRecipe;
	std::string myNewDescription;
	std::string myPrevDescription;
};

std::unique_ptr<interface::ICommandMemento>
ChangeRecipeDescription::Execute() {
	auto sub = myRecipe.lock();
	if (!sub) {
		interface::ILogger::Log(
			interface::LogLevel::Fatal,
			interface::LogType::Commands,
			"lost connection to observable");
		return nullptr;
	}
	auto recipe = sub->Get();
	if (!recipe.has_value()) {
		interface::ILogger::Log(
			interface::LogLevel::Fatal,
			interface::LogType::Commands,
			"tryed to access current file but it is not set");
		return nullptr;
	}
	const auto privDesc = recipe.value().GetDescription();

	auto frontend = myFrontend.lock();
	if (!frontend) {
		return nullptr;
	}
	const auto desc = frontend->AskForText();
	recipe.value().SetDescription(desc);
	return std::make_unique<ChangeRecipeDescriptionMemento>(recipe.value(), desc, privDesc);
}

void
ChangeRecipeDescription::SetReferences(
	std::weak_ptr<interface::IFrontend> aFrontend,
	std::shared_ptr<Observable<std::optional<Recipe>>> aCurrentRecipe)	// NOLINT
{
	myRecipe = aCurrentRecipe;
	myFrontend = std::move(aFrontend);
}
}  // namespace common
