#include "interface/i_file.h"

#include "common/json_parser.h"
#include "common/md_parser.h"
#include "interface/i_logger.h"

#include <queue>

namespace infas {
std::map<std::filesystem::path, std::shared_ptr<IFileImpl>> IFileImpl::myFiles{};

IFile::IFile(const std::filesystem::path& aPath) {
	auto extention = aPath.extension().string();
	if (extention == ".json") {
		myFileImplementation = IFileImpl::Open<common::JsonParser>(aPath);
		return;
	}
	if (extention == ".md") {
		myFileImplementation = IFileImpl::Open<common::MdParser>(aPath);
		return;
	}
	// NOTE(andreas): add all parsers here

	ILogger::Log(LogLevel::Debug, LogType::File, "no parser for this extention: " + extention);
	myFileImplementation = IFileImpl::Open<fake::FileImpl>(aPath);
}

IFile::~IFile() {
	if (myFileImplementation) {
		myFileImplementation->Save();
	}
}

std::string
IFile::GetFile() const {
	return myFileImplementation->GetPath().string();
}

bool
IFile::FieldIsArray(const std::filesystem::path& aKey) const {
	return myFileImplementation->GetField(aKey).size() > 1;
}

void
IFile::WriteField(const std::filesystem::path& aKey, std::string_view aValue) {
	myFileImplementation->ClearField(aKey);
	myFileImplementation->AddToKey(aKey, aValue);
}

std::string
IFile::ReadFromField(const std::filesystem::path& aKey) const {
	auto field = myFileImplementation->GetField(aKey);
	if (field.empty()) {
		return "";
	}
	return field[0];
}

void
IFile::AddToField(const std::filesystem::path& aKey, const std::vector<std::string_view>& aValue) {
	for (const auto& it : aValue) {
		myFileImplementation->AddToKey(aKey, it);
	}
}

void
IFile::RemoveFromField(
	const std::filesystem::path& aKey, const std::vector<std::string_view>& aValue) {
	for (const auto& it : aValue) {
		myFileImplementation->RemoveFromKey(aKey, it);
	}
}

std::vector<std::string>
IFile::ReadAllFromField(const std::filesystem::path& aKey) const {
	return myFileImplementation->GetField(aKey);
}

// TODO(andreas): change this!!!!
std::vector<std::filesystem::path>
IFile::GetSubKeys(const std::filesystem::path& aRoot) const {
	return myFileImplementation->GetKeys(aRoot);
}
}  // namespace infas
