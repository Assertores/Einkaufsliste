#include "biz/github_updater.h"

#include "common/platform.h"
#include "interface/i_logger.h"

#include <elzip/elzip.hpp>

#include <fstream>
#include <iostream>

static constexpr auto locDefaultUrl =
	"https://api.github.com/repos/Assertores/Einkaufsliste/releases/latest";
static constexpr auto locHttpOk = 200;
static constexpr auto locVersionKey = "tag_name";
static constexpr auto locAssetKey = "assets";
static constexpr auto locAssetNameKey = "name";
static constexpr auto locAssetUrlKey = "browser_download_url";

namespace biz {
bool
GithubUpdater::RetrieveMetaData() {
	auto responce = cpr::Get(cpr::Url(locDefaultUrl));
	if (responce.status_code != locHttpOk) {
		infas::ILogger::Log(
			infas::LogLevel::Error,
			infas::LogType::StartUp,
			"endpoint answerd with Http error code: " + std::to_string(responce.status_code));
		return false;
	}

	myJson = nlohmann::json::parse(responce.text);
	return true;
}

bool
GithubUpdater::IsPatchUpdate() {
	auto versionFile = std::ifstream(GetVersionPath());
	const std::string currentVersion(
		(std::istreambuf_iterator<char>(versionFile)),
		(std::istreambuf_iterator<char>()));
	versionFile.close();

	if (!myJson.contains(locVersionKey) || !myJson[locVersionKey].is_string()) {
		infas::ILogger::Log(
			infas::LogLevel::Error,
			infas::LogType::StartUp,
			"json document doesn't contain key 'tag_name' or it's not a string:\n" + myJson.dump());
		return false;
	}
	myNewVersion = myJson[locVersionKey].get<std::string>();
	bool isNewer = false;
	if (!CompareVersion(currentVersion, myNewVersion, isNewer)) {
		infas::ILogger::Log(
			infas::LogLevel::Error,
			infas::LogType::StartUp,
			"unable to parse version numbers.\ncurrent: " + currentVersion
				+ "\nnew: " + myNewVersion);
		return false;
	}
	if (!isNewer) {
		infas::ILogger::Log(infas::LogLevel::Debug, infas::LogType::StartUp, "no update available");
	}

	return isNewer;
}

bool
GithubUpdater::RetrievePatchLocation() {
	if (!myJson.contains(locAssetKey) || !myJson[locAssetKey].is_array()) {
		infas::ILogger::Log(
			infas::LogLevel::Error,
			infas::LogType::StartUp,
			"json document doesn't contain key 'assets' or it's not an array:\n" + myJson.dump());
		return false;
	}
	const auto assets = myJson[locAssetKey];
	const auto platformId = common::PlatformIdentifyer();

	const auto build =
		std::find_if(assets.begin(), assets.end(), [&platformId](const auto& aElement) {
			return aElement.contains(locAssetNameKey) && aElement[locAssetNameKey].is_string()
				   && aElement[locAssetNameKey].template get<std::string>().find(platformId)
						  != std::string::npos;
		});
	if (build == assets.end()) {
		infas::ILogger::Log(
			infas::LogLevel::Error,
			infas::LogType::StartUp,
			"no valide build found for platform: " + platformId);
		return false;
	}
	if (!build->contains(locAssetUrlKey) || !(*build)[locAssetUrlKey].is_string()) {
		infas::ILogger::Log(
			infas::LogLevel::Error,
			infas::LogType::StartUp,
			"asset dosen't contain key 'browser_download_url' or it's not a string: "
				+ build->dump());
		return false;
	}

	myPatch = cpr::Url((*build)[locAssetUrlKey].get<std::string>());
	return true;
}

bool
GithubUpdater::DownloadPatch() {
	std::ofstream zip(GetZipPath());
	cpr::Session session{};
	session.SetUrl(myPatch);
	auto resp = session.Download(zip);
	zip.close();
	if (resp.error) {
		infas::ILogger::Log(
			infas::LogLevel::Error,
			infas::LogType::StartUp,
			"unable to download patch from: " + myPatch.str());
	}

	return !resp.error;
}

bool
GithubUpdater::ExtractPatch() {
	if (!std::filesystem::exists(GetZipPath())) {
		infas::ILogger::Log(
			infas::LogLevel::Error,
			infas::LogType::StartUp,
			GetZipPath().u8string() + " is missing");
		return false;
	}
	try {
		elz::extractZip(GetZipPath(), GetPatchPath());
	} catch (...) {
		return false;
	}
	return true;
}

bool
GithubUpdater::ApplyPatch() {
	const auto patchPath = GetPatchPath();
	std::filesystem::recursive_directory_iterator newFiles(patchPath);
	for (const auto& it : newFiles) {
		if (it.is_directory()) {
			continue;
		}
		if (it.path().filename() == "version.txt") {
			continue;
		}
		const auto file = GetExePath() / std::filesystem::relative(it.path(), patchPath);
		if (std::filesystem::exists(file)) {
			// NOTE(andreas): there is no easy way to concatinate a string with a path without
			// adding a '/'
			std::filesystem::rename(file, file.u8string() + ".old");
			// TODO(andreas): what if the .old file also already exists?
		}
		std::filesystem::create_directories(file.parent_path());
		std::filesystem::rename(it, file);
	}

	std::ofstream versionFile(GetVersionPath());
	versionFile.clear();
	versionFile << myNewVersion;
	versionFile.close();
	return true;
}

void
GithubUpdater::CleanUp() {
	std::filesystem::remove_all(GetZipPath());
	std::filesystem::remove_all(GetPatchPath());
}

std::filesystem::path
GithubUpdater::GetExePath() {
	if (myExePath.empty()) {
		myExePath = common::CurrentExe().parent_path();
	}

	return myExePath;
}

std::filesystem::path
GithubUpdater::GetZipPath() {
	return GetExePath() / "patch.zip";
}
std::filesystem::path
GithubUpdater::GetPatchPath() {
	return GetExePath() / "patch";
}

std::filesystem::path
GithubUpdater::GetVersionPath() {
	return GetExePath() / "version.txt";  // TODO(andreas): do i want to compile the version number
										  // into the executable
}

bool
GithubUpdater::CompareVersion(
	const std::string& aOldVersion, const std::string& aNewVersion, bool& aOutIsNewer) {
	int oldMayor = 0;
	int oldMinor = 0;
	int oldRevision = 0;
	// NOLINTNEXTLINE
	if (sscanf(aOldVersion.c_str(), "v%d.%d.%d", &oldMayor, &oldMinor, &oldRevision) != 3) {
		return false;
	}
	int newMayor = 0;
	int newMinor = 0;
	int newRevision = 0;
	// NOLINTNEXTLINE
	if (sscanf(aNewVersion.c_str(), "v%d.%d.%d", &newMayor, &newMinor, &newRevision) != 3) {
		return false;
	}
	if (newMayor != oldMayor) {
		aOutIsNewer = newMayor > oldMayor;
		return true;
	}
	if (newMinor != oldMinor) {
		aOutIsNewer = newMinor > oldMinor;
		return true;
	}
	if (newRevision != oldRevision) {
		aOutIsNewer = newRevision > oldRevision;
		return true;
	}
	aOutIsNewer = false;
	return true;
}
}  // namespace biz
