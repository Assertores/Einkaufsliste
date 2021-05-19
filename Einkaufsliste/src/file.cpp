#include "common/file.h"

namespace common {
std::map<std::filesystem::path, std::shared_ptr<IFile>> File::myFiles {};

std::shared_ptr<common::IFile>
common::IFile::Create(const std::filesystem::path& aPath)
{
	return File::Create(aPath);
}

std::shared_ptr<common::IFile>
common::File::Create(const std::filesystem::path& aPath)
{
	auto it = myFiles.find(aPath);
	if (it != myFiles.end())
	{
		return it->second;
	}
	auto file = std::make_shared<File>();
	file->Open(aPath);

	myFiles[aPath] = file;
	return file;
}

File::~File() {
	Save();
}

void
File::Open(const std::filesystem::path& aPath)
{
	// TODO: deside whitch parsser to use
	// TODO: open file
}

void
File::Save()
{
	// TODO: save data to file
}
} // namespace common
