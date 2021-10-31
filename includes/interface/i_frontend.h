#pragma once

#include "common/unit.h"
#include "common/week.h"

#include <filesystem>

namespace interface {
class IFrontend {
public:
	virtual ~IFrontend() = default;

	// blocking, returns true if the application should be terminated
	virtual bool Poll() = 0;

	[[nodiscard]] virtual std::filesystem::path AskForFile() = 0;
	[[nodiscard]] virtual std::filesystem::path AskForFolder() = 0;
	[[nodiscard]] virtual common::Unit AskForUnit() = 0;
	[[nodiscard]] virtual std::string AskForText() = 0;
	[[nodiscard]] virtual common::WeekDay AskForWeekDay() = 0;
	[[nodiscard]] virtual common::DayTime AskForDayTime() = 0;
};
};	// namespace interface
