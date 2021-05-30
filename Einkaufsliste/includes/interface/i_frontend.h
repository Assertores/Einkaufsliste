#pragma once

#include <filesystem>

namespace interface {
class IFrontend
{
public:
	virtual std::filesystem::path AskForFile() = 0;
};
}; // namespace interface