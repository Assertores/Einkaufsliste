#include "biz/change_recipe_description.h"

namespace biz {

class ChangeRecipeDescriptionMemento : public infas::ICommandMemento {
public:
	ChangeRecipeDescriptionMemento(
		common::Recipe aRecipe, std::string aNewDescription, std::string aPrevDescription)
		: myRecipe(std::move(aRecipe))
		, myNewDescription(std::move(aNewDescription))
		, myPrevDescription(std::move(aPrevDescription)){};

	void ReExecute() override { myRecipe.SetDescription(myNewDescription); }

	void Revert() override { myRecipe.SetDescription(myPrevDescription); }

private:
	common::Recipe myRecipe;
	std::string myNewDescription;
	std::string myPrevDescription;
};

std::unique_ptr<infas::ICommandMemento>
ChangeRecipeDescription::Execute() {
	auto sub = myRecipe.lock();
	if (!sub) {
		infas::ILogger::Log(
			infas::LogLevel::Fatal,
			infas::LogType::Commands,
			"lost connection to observable");
		return nullptr;
	}
	auto recipe = sub->Get();
	if (!recipe.has_value()) {
		infas::ILogger::Log(
			infas::LogLevel::Fatal,
			infas::LogType::Commands,
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
	std::weak_ptr<infas::IFrontend> aFrontend,
	std::shared_ptr<common::Observable<std::optional<common::Recipe>>> aCurrentRecipe)	// NOLINT
{
	myRecipe = aCurrentRecipe;
	myFrontend = std::move(aFrontend);
}
}  // namespace biz
