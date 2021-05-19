#pragma once

#include <filesystem>
#include <memory>

namespace common {
class IFile
{
public:
	virtual ~IFile() = default;

	static std::shared_ptr<IFile> Create(const std::filesystem::path& aPath);

	virtual void Save() = 0;
};
} // namespace common
