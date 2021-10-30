#include "common/recipe.h"

#include <algorithm>
#include <sstream>

static constexpr const char* locDescriptionKey = "Description";
static constexpr const char* locIngredientsKey = "Ingredients";
static constexpr const char* locNameKey = "Name";

namespace common {
std::string
Recipe::Print() const
{
	std::stringstream result;
	result << "Name: " << GetName() << '\n';
	result << "Ingrediance:\n";

	auto ingredients = GetIngredients();

	auto first = ingredients.begin();
	const auto last = ingredients.end();
	while (first != last)
	{
		auto middle = std::partition(first, last, [type = first->GetType()](const auto& aOther) {
			return aOther.GetType() == type;
		});
		result << "- " << Unit::ToString({ first, middle }) << '\n';
		first = middle;
	}
	result << "Description:\n" << GetDescription() << '\n';
	return result.str();
}
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
	auto ingrediants = ReadAllFromField(locIngredientsKey);
	auto element = std::find_if(
		ingrediants.begin(),
		ingrediants.end(),
		[type = aIngredient.GetType()](const auto& aElement) {
			return Unit::ResultsInUnitsOfType(aElement) == type;
		});

	if (element == ingrediants.end())
	{
		AddToField(locIngredientsKey, { Unit::ToString({ aIngredient }) });
		return;
	}

	auto units = Unit::FromString(*element);
	for (auto& it : units)
	{
		if (it.Add(aIngredient))
		{
			RemoveFromField(locIngredientsKey, { *element });
			AddToField(locIngredientsKey, { Unit::ToString(units) });
			return;
		}
	}

	units.emplace_back(aIngredient);
	AddToField(locIngredientsKey, { Unit::ToString(units) });
}

bool
Recipe::RemoveIngredient(const Unit& aIngredient)
{
	auto ingrediants = ReadAllFromField(locIngredientsKey);
	auto element = std::find_if(
		ingrediants.begin(),
		ingrediants.end(),
		[type = aIngredient.GetType()](const auto& aElement) {
			return Unit::ResultsInUnitsOfType(aElement) == type;
		});

	if (element == ingrediants.end())
	{
		return false;
	}

	auto units = Unit::FromString(*element);
	for (auto& it : units)
	{
		if (it.Subtract(aIngredient))
		{
			RemoveFromField(locIngredientsKey, { *element });
			AddToField(locIngredientsKey, { Unit::ToString(units) });
			return true;
		}
	}
	return false;
}

std::vector<Unit>
Recipe::GetIngredients() const
{
	const auto ingrediansAsString = ReadAllFromField(locIngredientsKey);
	if (ingrediansAsString.empty())
	{
		return {};
	}
	std::vector<Unit> result;
	for (const auto& it : ingrediansAsString)
	{
		auto units = Unit::FromString(it);
		result.insert(result.end(), units.begin(), units.end());
	}
	return result;
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
