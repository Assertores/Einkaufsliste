#pragma once

#include "common/unit.h"
#include "interface/i_file.h"

#include <string_view>

namespace common {
class Recipe : public infas::IFile {
public:
	explicit Recipe(const std::filesystem::path& aPath)
		: IFile(aPath){};
	explicit Recipe(std::shared_ptr<infas::IFileImpl> aFileImpl)
		: IFile(std::move(aFileImpl)){};

	[[nodiscard]] std::string Print() const override;

	void SetDescription(std::string_view aText);
	[[nodiscard]] std::string GetDescription() const;

	void AddIngredient(const Unit& aIngredient);
	bool RemoveIngredient(const Unit& aIngredient);
	[[nodiscard]] std::vector<Unit> GetIngredients() const;

	void SetName(std::string_view aName);
	[[nodiscard]] std::string GetName() const;
};
}  // namespace common
