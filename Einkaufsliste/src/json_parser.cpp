#include "common/json_parser.h"

#include "interface/i_logger.h"

namespace common {
void
JsonParser::Open(const std::filesystem::path& aPath)
{
	interface::ILogger::Log(
		interface::LogLevel::Fatal,
		interface::LogType::File,
		"not implimented");
}

void
JsonParser::Save()
{
	interface::ILogger::Log(
		interface::LogLevel::Fatal,
		interface::LogType::File,
		"not implimented");
}

void
JsonParser::Refresh()
{
	interface::ILogger::Log(
		interface::LogLevel::Fatal,
		interface::LogType::File,
		"not implimented");
}

void
JsonParser::AddToKey(std::filesystem::path aKey, std::string_view aValue)
{
	interface::ILogger::Log(
		interface::LogLevel::Fatal,
		interface::LogType::File,
		"not implimented");
}

void
JsonParser::RemoveFromKey(std::filesystem::path aKey, std::string_view aValue)
{
	interface::ILogger::Log(
		interface::LogLevel::Fatal,
		interface::LogType::File,
		"not implimented");
}

void
JsonParser::ClearField(std::filesystem::path aKey)
{
	interface::ILogger::Log(
		interface::LogLevel::Fatal,
		interface::LogType::File,
		"not implimented");
}

std::vector<std::string>
JsonParser::GetField(std::filesystem::path aKey) const
{
	interface::ILogger::Log(
		interface::LogLevel::Fatal,
		interface::LogType::File,
		"not implimented");
	return std::vector<std::string>();
}

std::vector<std::filesystem::path>
JsonParser::GetKeys(std::filesystem::path aKey) const
{
	interface::ILogger::Log(
		interface::LogLevel::Fatal,
		interface::LogType::File,
		"not implimented");
	return std::vector<std::filesystem::path>();
}
} // namespace common
