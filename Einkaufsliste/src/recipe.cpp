#include "common/recipe.h"

static constexpr const char* locDescriptionKey = "Description";
static constexpr const char* locIngredientsKey = "Ingredients";

namespace common {
void
Recipe::SetDescription(std::string_view aText)
{
	WriteField(myName + "/" + locDescriptionKey, aText);
}

std::string_view
Recipe::GetDescription()
{
	return ReadFromField(myName + "/" + locDescriptionKey);
}

void
Recipe::AddIngredient(std::string_view aIngredient)
{
	AddToField(myName + "/" + locIngredientsKey, { aIngredient });
}

void
Recipe::RemoveIngredient(std::string_view aIngredient)
{
	RemoveFromField(myName + "/" + locIngredientsKey, { aIngredient });
}

std::vector<std::string_view>
Recipe::GetIngredients()
{
	return ReadAllFromField(myName + "/" + locIngredientsKey);
}

void
Recipe::SetName(std::string_view aName)
{
	myName = std::string(aName);
}

std::string_view
Recipe::GetName()
{
	if (myName.empty())
	{
		myName = GetAllKeys()[0].begin()->string();
	}
	return myName;
}
} // namespace common