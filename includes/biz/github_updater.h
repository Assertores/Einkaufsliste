#pragma once

#include "common/updater_template_methode.h"

#include <cpr/cpr.h>
#include <nlohmann/json.hpp>

#include <filesystem>
#include <string>


namespace biz {
class GithubUpdater : public common::UpdaterTemplateMethode {
public:
	bool RetraveMetaData() override;
	bool IsPatchUpdate() override;
	bool RetreavePatchLocation() override;
	bool DownloadPatch() override;
	bool ExtractPatch() override;
	bool ApplyPatch() override;
	void CleanUp() override;

	std::filesystem::path GetExePath();
	std::filesystem::path GetZipPath();
	std::filesystem::path GetPatchPath();
	std::filesystem::path GetVersionPath();
	static bool CompareVersion(
		const std::string& aOldVersion, const std::string& aNewVersion, bool& aIsNewer);

    std::filesystem::path myExePath;
	nlohmann::json myJson;
	cpr::Url myPatch;
    std::string myNewVersion;
};
}  // namespace biz