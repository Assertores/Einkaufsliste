#pragma once

#include <string_view>

#include "common/unit.h"
#include "interface/i_file.h"

namespace common {
class Recipe final : public interface::IFile
{
public:
	explicit Recipe(const std::filesystem::path& aPath)
		: IFile(aPath) {};
	explicit Recipe(std::shared_ptr<interface::IFileImpl> aFileImpl)
		: IFile(std::move(aFileImpl)) {};

	[[nodiscard]] std::string Print() const override;

	void SetDescription(std::string_view aText);
	[[nodiscard]] std::string GetDescription() const;

	void AddIngredient(const Unit& aIngredient);
	void RemoveIngredient(const Unit& aIngredient);
	[[nodiscard]] std::vector<std::string> GetIngredients() const;

	void SetName(std::string_view aName);
	[[nodiscard]] std::string GetName() const;
};
} // namespace common
