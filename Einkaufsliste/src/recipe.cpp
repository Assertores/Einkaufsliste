#include "common/recipe.h"

static constexpr std::string_view locDescriptionKey = "Description";

namespace common {
void
Recipe::SetDescription(std::string_view aText)
{
	WriteField(locDescriptionKey, aText);
}

std::string_view
Recipe::GetDescription()
{
	return ReadFromField(locDescriptionKey);
}
} // namespace common