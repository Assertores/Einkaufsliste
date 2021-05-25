#include "interface/i_file.h"

#include <queue>

#include "common/json_parser.h"
#include "common/md_parser.h"

namespace interface {
std::map<std::filesystem::path, std::shared_ptr<IFileImpl>> IFileImpl::myFiles {};

IFile::IFile(const std::filesystem::path& aPath)
{
	// TODO: deside what parser to use via the file ending
	auto extention = aPath.extension().string();
	if (extention == ".json")
	{
		myFileImplimentation = IFileImpl::Open<common::JsonParser>(aPath);
		return;
	}
	if (extention == ".md")
	{
		myFileImplimentation = IFileImpl::Open<common::MdParser>(aPath);
		return;
	}
	myFileImplimentation = IFileImpl::Open<interface::fake::FileImpl>(aPath);
}

IFile::~IFile()
{
	myFileImplimentation->Save();
}

bool
IFile::FieldIsArray(const std::filesystem::path& aKey) const
{
	return myFileImplimentation->GetField(aKey).size() > 1;
}

void
IFile::WriteField(const std::filesystem::path& aKey, std::string_view aValue)
{
	myFileImplimentation->ClearField(aKey);
	myFileImplimentation->AddToKey(aKey, aValue);
}

std::string
IFile::ReadFromField(const std::filesystem::path& aKey) const
{
	return myFileImplimentation->GetField(aKey)[0];
}

void
IFile::AddToField(const std::filesystem::path& aKey, const std::vector<std::string_view>& aValue)
{
	for (const auto& it : aValue)
	{
		myFileImplimentation->AddToKey(aKey, it);
	}
}

void
IFile::RemoveFromField(
	const std::filesystem::path& aKey,
	const std::vector<std::string_view>& aValue)
{
	for (const auto& it : aValue)
	{
		myFileImplimentation->RemoveFromKey(aKey, it);
	}
}

std::vector<std::string>
IFile::ReadAllFromField(const std::filesystem::path& aKey) const
{
	return myFileImplimentation->GetField(aKey);
}

std::vector<std::filesystem::path>
IFile::GetAllKeys() const
{
	std::queue<std::filesystem::path> openKeys;
	for (const auto& it : myFileImplimentation->GetKeys(""))
	{
		openKeys.emplace(it);
	}

	std::vector<std::filesystem::path> keys;
	for (; !openKeys.empty(); openKeys.pop())
	{
		auto newKeys = myFileImplimentation->GetKeys(openKeys.front());
		if (newKeys.empty())
		{
			keys.emplace_back(openKeys.front());
		}
		for (const auto& it : newKeys)
		{
			openKeys.emplace(it);
		}
	}
	return keys;
}
} // namespace interface
