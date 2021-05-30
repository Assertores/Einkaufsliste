#pragma once

#include <functional>
#include <map>
#include <queue>
#include <string>
#include <string_view>

namespace biz {
struct AppSettings;
struct PatcherSettings;
struct UpdaterSettings;

using ArgumentQueue = std::queue<std::string_view>;
using Interpreter = std::map<std::string_view, std::function<void(ArgumentQueue&)>>;

void InterpreteStartArguments(
	const std::vector<std::string_view>& aArgs,
	AppSettings& aApp,
	UpdaterSettings& aUpdater,
	PatcherSettings& aPatcher);

void SetDefaultArguments(AppSettings& aApp, UpdaterSettings& aUpdater, PatcherSettings& aPatcher);

void ReadArgumentsFromFile(AppSettings& aApp, UpdaterSettings& aUpdater, PatcherSettings& aPatcher);

Interpreter
CreateInterpreter(AppSettings& aApp, UpdaterSettings& aUpdater, PatcherSettings& aPatcher);

std::vector<std::pair<int, std::string_view>>
RunInterpretion(const std::vector<std::string_view>& aArgs, const Interpreter& aInterpreter);
} // namespace biz
