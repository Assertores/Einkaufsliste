#include "common/recipe.h"

static constexpr const char* locDescriptionKey = "Description";
static constexpr const char* locIngredientsKey = "Ingredients";

namespace common {
void
Recipe::SetDescription(std::string_view aText)
{
	WriteField(GetName() + "/" + locDescriptionKey, aText);
}

std::string
Recipe::GetDescription() const
{
	return ReadFromField(GetName() + "/" + locDescriptionKey);
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
	return ReadAllFromField(GetName() + "/" + locIngredientsKey);
}

void
Recipe::SetName(std::string_view aName)
{
	// TODO(andreas): set name
}

std::string
Recipe::GetName() const
{
	return GetAllKeys()[0].begin()->string();
}
} // namespace common
