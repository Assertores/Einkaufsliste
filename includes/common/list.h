#pragma once

#include "common/recipe.h"
#include "common/week.h"
#include "interface/i_file.h"

#include <set>
#include <string_view>

namespace common {
class List : public infas::IFile {
public:
	explicit List(const std::filesystem::path& aPath)
		: IFile(aPath){};
	explicit List(std::shared_ptr<infas::IFileImpl> aFileImpl)
		: IFile(std::move(aFileImpl)){};

	[[nodiscard]] std::string Print() const override;

	void AddWeek(const Week& aWeek);
	void AddRecipe(const Recipe& aRecipe);

	void Compile();
};
}  // namespace common
