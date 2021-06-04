#pragma once

#include <filesystem>

#include "common/unit.h"

namespace interface {
class IFrontend
{
public:
	virtual ~IFrontend() = default;

	// blocking, returns true if the application should be terminated
	virtual bool Poll() = 0;

	virtual std::filesystem::path AskForFile() = 0;
	virtual std::filesystem::path AskForFolder() = 0;
	virtual common::Unit AskForUnit() = 0;
};
}; // namespace interface