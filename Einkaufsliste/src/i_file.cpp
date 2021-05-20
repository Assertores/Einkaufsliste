#include "common/i_file.h"

#include "common/json_parser.h"

namespace common {
IFile::IFile(std::filesystem::path aPath)
{
	// TODO: deside what parser to use via the file ending
	myFileImplimentation = IFileImpl::Open<JsonParser>(aPath);
}

bool
IFile::FieldIsArray(std::filesystem::path aKey)
{
	return myFileImplimentation->GetKey(aKey).size() > 1;
}

void
IFile::WriteField(std::filesystem::path aKey, std::string_view aValue)
{
	myFileImplimentation->ClearField(aKey);
	myFileImplimentation->AddToKey(aKey, aValue);
}

std::string_view
IFile::ReadFromField(std::filesystem::path aKey)
{
	return myFileImplimentation->GetKey(aKey)[0];
}

void
IFile::AddToField(std::filesystem::path aKey, std::vector<std::string_view> aValue)
{
	for (auto& it : aValue)
	{
		myFileImplimentation->AddToKey(aKey, it);
	}
}

void
IFile::RemoveFromField(std::filesystem::path aKey, std::vector<std::string_view> aValue)
{
	for (auto& it : aValue)
	{
		myFileImplimentation->RemoveFromKey(aKey, it);
	}
}

std::vector<std::string_view>
IFile::ReadAllFromField(std::filesystem::path aKey)
{
	return myFileImplimentation->GetKey(aKey);
}
} // namespace common
