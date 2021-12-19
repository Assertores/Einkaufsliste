#pragma once

#include "common/updater_template_method.h"

#include <cpr/cpr.h>
#include <nlohmann/json.hpp>

#include <filesystem>
#include <string>

namespace biz {
class GithubUpdater : public common::UpdaterTemplateMethod {
public:
	bool RetrieveMetaData() override;
	bool IsPatchUpdate() override;
	bool RetrievePatchLocation() override;
	bool DownloadPatch() override;
	bool ExtractPatch() override;
	bool ApplyPatch() override;
	void CleanUp() override;

	virtual std::filesystem::path GetExePath();
	std::filesystem::path GetZipPath();
	std::filesystem::path GetPatchPath();
	std::filesystem::path GetVersionPath();
	static bool CompareVersion(
		const std::string& aOldVersion, const std::string& aNewVersion, bool& aOutIsNewer);

	std::filesystem::path myExePath {};
	nlohmann::json myJson {};
	cpr::Url myPatch {};
	std::string myNewVersion {};
};
}  // namespace biz

