#include "common/i_file.h"

#include "common/json_parser.h"

namespace common {
std::map<std::filesystem::path, std::shared_ptr<IFileImpl>> IFileImpl::myFiles {};

IFile::IFile(const std::filesystem::path& aPath)
{
	// TODO: deside what parser to use via the file ending
	myFileImplimentation = IFileImpl::Open<JsonParser>(aPath);
}

IFile::~IFile()
{
	myFileImplimentation->Save();
}

bool
IFile::FieldIsArray(const std::filesystem::path& aKey)
{
	return myFileImplimentation->GetKey(aKey).size() > 1;
}

void
IFile::WriteField(const std::filesystem::path& aKey, std::string_view aValue)
{
	myFileImplimentation->ClearField(aKey);
	myFileImplimentation->AddToKey(aKey, aValue);
}

std::string_view
IFile::ReadFromField(const std::filesystem::path& aKey)
{
	return myFileImplimentation->GetKey(aKey)[0];
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

std::vector<std::string_view>
IFile::ReadAllFromField(const std::filesystem::path& aKey)
{
	return myFileImplimentation->GetKey(aKey);
}
} // namespace common
