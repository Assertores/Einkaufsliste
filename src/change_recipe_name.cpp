#include "biz/change_recipe_name.h"

namespace biz {

class ChangeRecipeNameMemento : public infas::ICommandMemento {
public:
	ChangeRecipeNameMemento(common::Recipe aRecipe, std::string aNewName, std::string aPrevName)
		: myRecipe(std::move(aRecipe))
		, myNewName(std::move(aNewName))
		, myPrevName(std::move(aPrevName)){};

	void ReExecute() override { myRecipe.SetName(myNewName); }

	void Revert() override { myRecipe.SetName(myPrevName); }

private:
	common::Recipe myRecipe;
	std::string myNewName;
	std::string myPrevName;
};

std::unique_ptr<infas::ICommandMemento>
ChangeRecipeName::Execute() {
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
	const auto privName = recipe.value().GetName();

	auto frontend = myFrontend.lock();
	if (!frontend) {
		return nullptr;
	}
	const auto name = frontend->AskForText();
	recipe.value().SetName(name);
	return std::make_unique<ChangeRecipeNameMemento>(recipe.value(), name, privName);
}

void
ChangeRecipeName::SetReferences(
	std::weak_ptr<infas::IFrontend> aFrontend,
	std::shared_ptr<common::Observable<std::optional<common::Recipe>>> aCurrentRecipe) // NOLINT
{
	myRecipe = aCurrentRecipe;
	myFrontend = std::move(aFrontend);
}
} // namespace biz
