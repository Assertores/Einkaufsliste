#pragma once

#include "common/unit.h"
#include "common/week.h"

#include <filesystem>

namespace infas {
class IFrontend {
public:
	virtual ~IFrontend() = default;

	// blocking, returns true if the application should be terminated
	virtual bool Poll() = 0;

	[[nodiscard]] virtual std::filesystem::path AskForFile() = 0;
	[[nodiscard]] virtual std::filesystem::path AskForFolder() = 0;
	[[nodiscard]] virtual common::Unit AskForUnit() = 0;
	[[nodiscard]] virtual std::string AskForText() = 0;
	[[nodiscard]] virtual bool AskForWeekDay(common::WeekDay& aOutWeekDay) = 0;
	[[nodiscard]] virtual bool AskForDayTime(common::DayTime& aOutDayTime) = 0;
};

namespace fake {
class Frontend : public IFrontend {
public:
	static constexpr auto defaultFilePath = "./default/file/path.fake";
	static constexpr auto defaultFolderPath = "./default/folder";
	static common::Unit DefaultUnion() { return common::Unit{3, "kg", "Apple"}; };
	static constexpr auto defaultText = "default text";
	static constexpr auto defaultWeekDay = common::WeekDay::Friday;
	static constexpr auto defaultDayTime = common::DayTime{4, 23};

	std::function<bool()> poll = [this]() {
		pollCount++;
		return true;
	};
	std::function<std::filesystem::path()> askForFile = [this]() {
		askForFileCount++;
		return std::filesystem::path{defaultFilePath};
	};
	std::function<std::filesystem::path()> askForFolder = [this]() {
		askForFolderCount++;
		return std::filesystem::path{defaultFolderPath};
	};
	std::function<common::Unit()> askForUnit = [this]() {
		askForUnitCount++;
		return DefaultUnion();	// NOLINT
	};
	std::function<std::string()> askForText = [this]() {
		askForTextCount++;
		return defaultText;
	};
	std::function<bool(common::WeekDay&)> askForWeekDay = [this](auto& aOutWeekDay) {
		askForWeekDayCount++;
		aOutWeekDay = defaultWeekDay;
		return true;
	};
	std::function<bool(common::DayTime&)> askForDayTime = [this](auto& aOutDayTime) {
		askForDayTimeCount++;
		aOutDayTime = defaultDayTime;
		return true;
	};

	bool Poll() override { return poll(); }
	std::filesystem::path AskForFile() override { return askForFile(); }
	std::filesystem::path AskForFolder() override { return askForFolder(); }
	common::Unit AskForUnit() override { return askForUnit(); }
	std::string AskForText() override { return askForText(); }
	bool AskForWeekDay(common::WeekDay& aOutWeekDay) override { return askForWeekDay(aOutWeekDay); }
	bool AskForDayTime(common::DayTime& aOutDayTime) override { return askForDayTime(aOutDayTime); }

	int pollCount = 0;
	int askForFileCount = 0;
	int askForFolderCount = 0;
	int askForUnitCount = 0;
	int askForTextCount = 0;
	int askForWeekDayCount = 0;
	int askForDayTimeCount = 0;
};
}  // namespace fake
};	// namespace infas
