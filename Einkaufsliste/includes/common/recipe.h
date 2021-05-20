#pragma once

#include <string_view>

#include "common/i_file.h"

namespace common {
class Recipe final : public IFile
{
public:
	Recipe(const std::filesystem::path& aPath)
		: IFile(aPath) {};
	void SetDescription(std::string_view aText);
	std::string_view GetDescription();
};
} // namespace common
