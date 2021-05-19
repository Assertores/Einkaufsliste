#include "biz/argument_parser.h"

#include <iostream>
#include <string_view>

#include "biz/patcher.h"
#include "biz/updater.h"

namespace biz {
static constexpr std::string_view locDefaultUrl =
	"https://api.github.com/repos/Assertores/Einkaufsliste/releases/latest";

void
InterpreteStartArguments(
	const std::vector<std::string_view>& aArgs,
	AppSettings& aApp,
	UpdaterSettings& aUpdater,
	PatcherSettings& aPatcher,
	std::ostream& aOutput)
{
	Interpreter interpreter;
	interpreter["--no-patch"] = [&](auto& /*unused*/) {
		aPatcher.doPatching = true;
	};
	interpreter["--set-update-url"] = [&](auto& aQueue) {
		aUpdater.url = aQueue.front();
		aQueue.pop();
	};
	// TODO: add all arguments here

	aPatcher.doPatching = true;
	aUpdater.url = locDefaultUrl;

	auto errors = RunInterpretion(aArgs, interpreter);

	for (auto& [line, argument] : errors)
	{
		aOutput << "[LOG] argument: '" << argument << "' (nr. " << line
				  << ") was not interpreted \n";
	}
}

std::vector<std::pair<int, std::string_view>>
RunInterpretion(const std::vector<std::string_view>& aArgs, const Interpreter& aInterpreter)
{
	ArgumentQueue args;
	for (int i = 1; i < aArgs.size(); i++)
	{
		args.emplace(aArgs[i]);
	}

	std::vector<std::pair<int, std::string_view>> invalideArguments;
	for (int i = 1; !args.empty(); i++)
	{
		auto arg = args.front();
		args.pop();
		auto it = aInterpreter.find(arg);
		if (it == aInterpreter.end())
		{
			invalideArguments.emplace_back(std::make_pair(i, arg));
			continue;
		}
		it->second(args);
	}
	return invalideArguments;
}
} // namespace biz
