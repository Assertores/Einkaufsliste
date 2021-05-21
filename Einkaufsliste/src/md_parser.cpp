#include "common/md_parser.h"

#include <algorithm>
#include <fstream>
#include <stack>

#include <iostream>

namespace common {
void
MdParser::Open(const std::filesystem::path& aPath)
{
	std::filesystem::create_directories(aPath.parent_path());
	std::ifstream file(aPath); // NOLINT
	// TODO: read in file
	myFile = std::ofstream(aPath);
}

void
MdParser::Save()
{
	std::vector<std::filesystem::path> keys {};
	for (const auto& it : myContent)
	{
		keys.emplace_back(it.first);
	}
	std::sort(keys.begin(), keys.end());

	int headerCounterDepth = 1;
	auto currentPath = std::filesystem::path();
	for (const auto& element : keys)
	{
		currentPath = element.lexically_relative(currentPath);
		for (const auto& it : currentPath.parent_path())
		{
			if (it == "..")
			{
				headerCounterDepth--;
				continue;
			}
			for (int i = 0; i < headerCounterDepth; i++)
			{
				myFile << '#';
			}
			myFile << ' ' << it.string() << '\n';

			headerCounterDepth++;
		}
		myFile << currentPath.filename().string() << '\n';
		for (auto& it : myContent[element])
		{
			myFile << "- " << it << '\n';
		}
		myFile << '\n';
	}
}

void
MdParser::Refresh()
{
}

void
MdParser::AddToKey(std::filesystem::path aKey, std::string_view aValue)
{
	myContent[aKey].emplace_back(aValue);
}

void
MdParser::RemoveFromKey(std::filesystem::path aKey, std::string_view aValue)
{
	myContent[aKey].erase(std::find(myContent[aKey].begin(), myContent[aKey].end(), aValue));
}

void
MdParser::ClearField(std::filesystem::path aKey)
{
	myContent[aKey] = std::vector<std::string>();
}

std::vector<std::string_view>
MdParser::GetKey(std::filesystem::path aKey)
{
	std::vector<std::string_view> result(myContent[aKey].size());
	for (int i = 0; i < myContent[aKey].size(); i++)
	{
		result[i] = myContent[aKey][i];
	}
	return result;
}
} // namespace common
