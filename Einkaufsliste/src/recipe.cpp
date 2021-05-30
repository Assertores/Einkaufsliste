#include "common/recipe.h"

static constexpr const char* locDescriptionKey = "Description";
static constexpr const char* locIngredientsKey = "Ingredients";
static constexpr const char* locNameKey = "Name";

namespace common {
void
Recipe::SetDescription(std::string_view aText)
{
	WriteField(locDescriptionKey, aText);
}

std::string
Recipe::GetDescription() const
{
	return ReadFromField(locDescriptionKey);
}

void
Recipe::AddIngredient(const Unit& aIngredient)
{
	// TODO(andreas): correctly impliment this function
	// AddToField(myName + "/" + locIngredientsKey, { aIngredient });
}

void
Recipe::RemoveIngredient(const Unit& aIngredient)
{
	// TODO(andreas): correctly impliment this function
	// RemoveFromField(myName + "/" + locIngredientsKey, { aIngredient });
}

std::vector<std::string>
Recipe::GetIngredients() const
{
	return ReadAllFromField(locIngredientsKey);
}

void
Recipe::SetName(std::string_view aName)
{
	WriteField(locNameKey, aName);
}

std::string
Recipe::GetName() const
{
	return ReadFromField(locNameKey);
}
} // namespace common
