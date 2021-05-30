#pragma once

#include <filesystem>

namespace interface {
class IFrontend
{
public:
	virtual ~IFrontend() = default;

	// blocking, returns true if the application should be terminated
	virtual bool Poll() = 0;

	virtual std::filesystem::path AskForFile() = 0;
};
}; // namespace interface