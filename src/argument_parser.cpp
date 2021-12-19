#include "biz/argument_parser.h"

#include "biz/application.h"
#include "biz/patcher.h"
#include "common/updater_template_method.h"
#include "interface/i_logger.h"

#include <sstream>
#include <string_view>

namespace biz {

void
InterpreteStartArguments(
	const std::vector<std::string_view>& aArgs,
	AppSettings& aApp,
	common::UpdaterSettings& aUpdater,
	PatcherSettings& aPatcher) {
	ReadArgumentsFromFile(aApp, aUpdater, aPatcher);

	auto errors = RunInterpretion(aArgs, CreateInterpreter(aApp, aUpdater, aPatcher));

	for (auto& [line, argument] : errors) {
		std::stringstream log;
		log << " argument '" << argument << "' (nr. " << line << ") was not interpreted";
		infas::ILogger::Log(infas::LogLevel::Verbose, infas::LogType::StartUp, log.str());
	}
}

void
ReadArgumentsFromFile(AppSettings& aApp, common::UpdaterSettings& aUpdater, PatcherSettings& aPatcher) {}

Interpreter
CreateInterpreter(AppSettings& aApp, common::UpdaterSettings& aUpdater, PatcherSettings& aPatcher) {
	Interpreter interpreter;
	interpreter["--no-patch"] = [&](auto& /*unused*/) { aPatcher.doPatching = false; };
	interpreter["--no-update"] = [&](auto& /*unused*/) { aUpdater.doUpdate = false; };
	interpreter["--set-update-url"] = [&](auto& aQueue) {
		aUpdater.url = aQueue.front();
		aQueue.pop();
	};
	interpreter["--shut-down"] = [&](auto& /*unused*/) { aApp.doRun = false; };
	interpreter["--log-level"] = [](auto& aQueue) {
		auto element = aQueue.front();
		aQueue.pop();
		if (element == "silent") {
			infas::ILogger::SetLogLevel(infas::LogLevel::Silent);
		} else if (element == "fatal") {
			infas::ILogger::SetLogLevel(infas::LogLevel::Fatal);
		} else if (element == "error") {
			infas::ILogger::SetLogLevel(infas::LogLevel::Error);
		} else if (element == "debug") {
			infas::ILogger::SetLogLevel(infas::LogLevel::Debug);
		} else if (element == "verbose") {
			infas::ILogger::SetLogLevel(infas::LogLevel::Verbose);
		}
	};
	interpreter["--help"] = [=](auto& /*unused*/) {
		for (const auto& it : interpreter) {
			aApp.output << it.first << '\n';
		}
	};
	return std::move(interpreter);
}

std::vector<std::pair<int, std::string_view>>
RunInterpretion(const std::vector<std::string_view>& aArgs, const Interpreter& aInterpreter) {
	ArgumentQueue args;
	for (int i = 1; i < aArgs.size(); i++) {
		args.emplace(aArgs[i]);
	}

	std::vector<std::pair<int, std::string_view>> invalideArguments;
	for (int i = 1; !args.empty(); i++) {
		auto arg = args.front();
		args.pop();
		auto it = aInterpreter.find(arg);
		if (it == aInterpreter.end()) {
			invalideArguments.emplace_back(std::make_pair(i, arg));
			continue;
		}
		it->second(args);
	}
	return invalideArguments;
}
}  // namespace biz

