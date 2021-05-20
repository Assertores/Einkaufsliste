#include "common/json_parser.h"

namespace common {
void
JsonParser::Open(const std::filesystem::path& aPath)
{
}

void
JsonParser::Save()
{
}

void
JsonParser::Refresh()
{
}

void
JsonParser::AddToKey(std::filesystem::path aKey, std::string_view aValue)
{
}

void
JsonParser::RemoveFromKey(std::filesystem::path aKey, std::string_view aValue)
{
}

void
JsonParser::ClearField(std::filesystem::path aKey)
{
}

std::vector<std::string_view>
JsonParser::GetKey(std::filesystem::path aKey)
{
	return std::vector<std::string_view>();
}
} // namespace common
