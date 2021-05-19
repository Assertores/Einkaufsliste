#pragma once

#include <filesystem>
#include <map>
#include <memory>

#include "common/i_file.h"

namespace common {

class File final : public IFile
{
public:
	~File();

	static std::shared_ptr<IFile> Create(const std::filesystem::path& aPath);

	void Open(const std::filesystem::path& aPath);
	void Save() override;

private:
	static std::map<std::filesystem::path, std::shared_ptr<IFile>> myFiles;
};
} // namespace common
