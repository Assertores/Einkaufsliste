#include "interface/i_file.h"

#include "common/json_parser.h"
#include "common/md_parser.h"
#include "interface/i_logger.h"

#include <queue>

namespace interface {
std::map<std::filesystem::path, std::shared_ptr<IFileImpl>> IFileImpl::myFiles{};

IFile::IFile(const std::filesystem::path& aPath) {
	auto extention = aPath.extension().string();
	if (extention == ".json") {
		myFileImplimentation = IFileImpl::Open<common::JsonParser>(aPath);
		return;
	}
	if (extention == ".md") {
		myFileImplimentation = IFileImpl::Open<common::MdParser>(aPath);
		return;
	}
	// TODO(andreas): add all parsers here

	interface::ILogger::Log(
		interface::LogLevel::Debug,
		interface::LogType::File,
		"no parser for this extention: " + extention);
	myFileImplimentation = IFileImpl::Open<interface::fake::FileImpl>(aPath);
}

IFile::~IFile() {
	if (myFileImplimentation) {
		myFileImplimentation->Save();
	}
}

std::string
IFile::GetFile() const {
	return myFileImplimentation->GetPath().string();
}

bool
IFile::FieldIsArray(const std::filesystem::path& aKey) const {
	return myFileImplimentation->GetField(aKey).size() > 1;
}

void
IFile::WriteField(const std::filesystem::path& aKey, std::string_view aValue) {
	myFileImplimentation->ClearField(aKey);
	myFileImplimentation->AddToKey(aKey, aValue);
}

std::string
IFile::ReadFromField(const std::filesystem::path& aKey) const {
	auto field = myFileImplimentation->GetField(aKey);
	if (field.empty()) {
		return "";
	}
	return field[0];
}

void
IFile::AddToField(const std::filesystem::path& aKey, const std::vector<std::string_view>& aValue) {
	for (const auto& it : aValue) {
		myFileImplimentation->AddToKey(aKey, it);
	}
}

void
IFile::RemoveFromField(
	const std::filesystem::path& aKey, const std::vector<std::string_view>& aValue) {
	for (const auto& it : aValue) {
		myFileImplimentation->RemoveFromKey(aKey, it);
	}
}

std::vector<std::string>
IFile::ReadAllFromField(const std::filesystem::path& aKey) const {
	return myFileImplimentation->GetField(aKey);
}

// TODO(andreas): change this!!!!
std::vector<std::filesystem::path>
IFile::GetSubKeys(const std::filesystem::path& aRoot) const {
	return myFileImplimentation->GetKeys(aRoot);
}
}  // namespace interface
