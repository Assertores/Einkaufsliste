#include "common/md_parser.h"

#include <algorithm>
#include <fstream>
#include <iostream>
#include <stack>

namespace common {
void
MdParser::Open(const std::filesystem::path& aPath)
{
	std::filesystem::create_directories(aPath.parent_path());
	myFile = aPath;
	auto file = std::ifstream(aPath);
	Parse(file);
}

void
MdParser::Save()
{
	auto file = std::ofstream(myFile);
	Serialize(file);
}

void
MdParser::Refresh()
{
	auto file = std::ifstream(myFile);
	Parse(file);
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

std::vector<std::string>
MdParser::GetField(std::filesystem::path aKey) const
{
	return myContent.find(aKey)->second;
}

std::vector<std::filesystem::path>
MdParser::GetKeys(std::filesystem::path aKey) const
{
	std::vector<std::filesystem::path> result;
	for (const auto& it : myContent)
	{
		auto relPath = it.first.lexically_relative(aKey);
		if (relPath != "."
			&& *relPath.begin() != "..") // NOLINT TODO(andreas): check if key is a parent path
		{
			result.push_back(it.first);
		}
	}
	return result;
}

void
MdParser::Parse(std::istream& aIn)
{
	myContent = {};

	std::string line;
	std::vector<std::string> keyBuilder;
	std::filesystem::path currentKey;
	while (std::getline(aIn, line))
	{
		if (line.empty())
		{
			continue;
		}
		if (line[0] == '#')
		{
			int headerDepth = 0;
			for (const auto& it : line)
			{
				if (it != '#')
				{
					break;
				}
				headerDepth++;
			}
			keyBuilder.resize(headerDepth - 1);
			keyBuilder.emplace_back(line.substr(headerDepth + 1));
			continue;
		}
		if (line[0] == '-')
		{
			myContent[currentKey].emplace_back(line.substr(2));
			continue;
		}
		currentKey = "";
		for (const auto& it : keyBuilder)
		{
			currentKey /= it;
		}
		currentKey /= line;
		myContent[currentKey] = {};
	}
}

void
MdParser::Serialize(std::ostream& aOut)
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
		currentPath = element.lexically_relative(currentPath.parent_path());
		for (const auto& it : currentPath.parent_path())
		{
			if (it == "..")
			{
				headerCounterDepth--;
				continue;
			}
			for (int i = 0; i < headerCounterDepth; i++)
			{
				aOut << '#';
			}
			aOut << ' ' << it.string() << '\n';

			headerCounterDepth++;
		}
		aOut << currentPath.filename().string() << '\n';
		for (auto& it : myContent[element])
		{
			aOut << "- " << it << '\n';
		}
		aOut << '\n';
	}
}
} // namespace common
