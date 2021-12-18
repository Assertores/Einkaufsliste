#include "common/platform.h"

#include <filesystem>
#include <iostream>
#include <string>

int
main(int argc, char** argv) // NOLINT
{
	if (argc == 1) {
		std::cout << "no arguments. starting another instance.\n";
		common::StartProcess(common::CurrentExe(), {"1", "2", "❤", "💋"}, std::filesystem::current_path());
	} else {
		std::cout << argc << " arguments:\n";
		for (int i = 0; i < argc; i++) {
			std::cout << argv[i] << '\n';
		}
	}
	std::cout << "input anything: ";
	std::string tmp;
	std::cin >> tmp;
	return 0;
}
