#pragma once

#include <string_view>

#include "interface/i_file.h"

namespace common {
class Recipe final : public interface::IFile
{
public:
	Recipe(const std::filesystem::path& aPath)
		: IFile(aPath) {};
	void SetDescription(std::string_view aText);
	std::string_view GetDescription();

	void AddIngredient(std::string_view aIngredient);
	void RemoveIngredient(std::string_view aIngredient);
	std::vector<std::string_view> GetIngredients();

	void SetName(std::string_view aName);
	std::string_view GetName();

private:
	std::string myName;
};
} // namespace common
