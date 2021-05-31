#pragma once

#include <string_view>

#include "common/unit.h"
#include "interface/i_file.h"

namespace common {
class Recipe final : public interface::IFile
{
public:
	Recipe(const std::filesystem::path& aPath)
		: IFile(aPath) {};
	Recipe(std::shared_ptr<interface::IFileImpl> aFileImpl)
		: IFile(aFileImpl) {};

	std::string Print() const override;

	void SetDescription(std::string_view aText);
	std::string GetDescription() const;

	void AddIngredient(const Unit& aIngredient);
	void RemoveIngredient(const Unit& aIngredient);
	std::vector<std::string> GetIngredients() const;

	void SetName(std::string_view aName);
	std::string GetName() const;
};
} // namespace common
