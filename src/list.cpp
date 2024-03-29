#include "common/list.h"

#include "interface/i_file_impl.h"

#include <algorithm>
#include <map>
#include <sstream>

static constexpr auto locRecipeListKey = "Recipes";
static constexpr auto locIngreadianceKey = "List";

namespace common {
std::string
List::Print() const {
	std::stringstream result;
	auto units = ReadAllFromField(locIngreadianceKey);
	result << "Current List\n";
	for (const auto& it : units) {
		result << it << '\n';
	}
	return result.str();
}

void
List::AddWeek(const Week& aWeek) {
	auto recipes = aWeek.GetAllRecipes();
	for (const auto& it : recipes) {
		AddToField(locRecipeListKey, {it.GetFile()});
	}
}

void
List::AddRecipe(const Recipe& aRecipe) {
	AddToField(locRecipeListKey, {aRecipe.GetFile()});
}

void
List::Compile() {
	auto recipePaths = ReadAllFromField(locRecipeListKey);
	std::map<std::string, std::vector<Unit>> list;
	for (const auto& recipePath : recipePaths) {
		for (const auto& it : Recipe(recipePath).GetIngredients()) {
			auto& units = list[it.GetType()];
			bool wasInjected = false;
			for (auto& unit : units) {
				if (unit.Add(it)) {
					wasInjected = true;
					break;
				}
			}
			if (!wasInjected) {
				units.emplace_back(it);
			}
		}
	}
	for (const auto& it : list) {
		AddToField(locIngreadianceKey, {Unit::ToString(it.second)});
	}
}
} // namespace common
