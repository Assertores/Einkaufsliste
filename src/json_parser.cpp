#include "common/json_parser.h"

#include "interface/i_logger.h"

namespace common {
void
JsonParser::Open(const std::filesystem::path& aPath) {
	infas::ILogger::Log(infas::LogLevel::Fatal, infas::LogType::File, "not implemented");
}

void
JsonParser::Save() {
	infas::ILogger::Log(infas::LogLevel::Fatal, infas::LogType::File, "not implemented");
}

void
JsonParser::Refresh() {
	infas::ILogger::Log(infas::LogLevel::Fatal, infas::LogType::File, "not implemented");
}

std::filesystem::path
JsonParser::GetPath() const {
	infas::ILogger::Log(infas::LogLevel::Fatal, infas::LogType::File, "not implemented");
	return {};
}

void
JsonParser::AddToKey(std::filesystem::path aKey, std::string_view aValue) {
	infas::ILogger::Log(infas::LogLevel::Fatal, infas::LogType::File, "not implemented");
}

void
JsonParser::RemoveFromKey(std::filesystem::path aKey, std::string_view aValue) {
	infas::ILogger::Log(infas::LogLevel::Fatal, infas::LogType::File, "not implemented");
}

void
JsonParser::ClearField(std::filesystem::path aKey) {
	infas::ILogger::Log(infas::LogLevel::Fatal, infas::LogType::File, "not implemented");
}

std::vector<std::string>
JsonParser::GetField(std::filesystem::path aKey) const {
	infas::ILogger::Log(infas::LogLevel::Fatal, infas::LogType::File, "not implemented");
	return {};
}

std::vector<std::filesystem::path>
JsonParser::GetKeys(std::filesystem::path aKey) const {
	infas::ILogger::Log(infas::LogLevel::Fatal, infas::LogType::File, "not implemented");
	return {};
}
}  // namespace common

