#include "biz/command_line_interface.h"

#include "interface/i_logger.h"

namespace biz {
std::filesystem::path
CommandLineInterface::AskForFile()
{
	std::filesystem::path path;
	myOutput << "please enter a a file path: ";
	myInput >> path;
	return path;
}

bool
CommandLineInterface::Poll()
{
	std::string command;
	myInput >> command;
	if (command == "exit" || command == "quit")
	{
		return true;
	}
	// TODO: add funktionality here

	interface::ILogger::Log(
		interface::LogLevel::Verbose,
		interface::LogType::Commands,
		"ignore me");

	return false;
}
} // namespace biz
