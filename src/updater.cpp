#define _SILENCE_ALL_CXX17_DEPRECATION_WARNINGS	 // NOLINT
												 // "bugprone-reserved-identifier,cert-dcl37-c,cert-dcl51-cpp"
#include "biz/updater.h"

#include "interface/i_logger.h"

#include <cpr/cpr.h>
#include <elzip/elzip.hpp>
#include <nlohmann/json.hpp>

#include <charconv>
#include <fstream>
#include <string>
#include <string_view>

#if _WIN32
#include <Windows.h>
#endif

namespace biz {

static constexpr auto locHttpOk = 200;

std::filesystem::path
GetExePath() {
#if _WIN32
	wchar_t exePath[UNICODE_STRING_MAX_CHARS]; // NOLINT
	GetModuleFileNameW(nullptr, exePath, UNICODE_STRING_MAX_CHARS); // NOLINT
	return exePath;
#else
	return std::filesystem::canonical("/proc/self/exe");
#endif
}

bool
CompareVersion(const std::string& aOldVersion, const std::string& aNewVersion, bool& aIsNewer) {
	// TODO(andreas): find a better way of doing this in general
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
	if (newMayor > oldMayor) {
		aIsNewer = true;
		return true;
	}
	if (newMinor > oldMinor) {
		aIsNewer = true;
		return true;
	}
	if (newRevision > oldRevision) {
		aIsNewer = true;
		return true;
	}
	aIsNewer = false;
	return true;
}

bool
Update(const UpdaterSettings& aSettings) {
	if (!aSettings.doUpdate) {
		infas::ILogger::Log(
			infas::LogLevel::Debug,
			infas::LogType::StartUp,
			"asked to not updater");
		return false;
	}
	const auto exeDir = GetExePath();
	auto versionFile = std::fstream(exeDir / "version.txt");
	// TODO(andreas): figure out which platform to download
	const std::string platform = "win10";
	// NOTE(andreas):
	// https://stackoverflow.com/questions/2912520/read-file-contents-into-a-string-in-c
	const std::string currentVersion(
		(std::istreambuf_iterator<char>(versionFile)),
		(std::istreambuf_iterator<char>()));

	// TODO(andreas): figure out how to work with prereleases
	// NOTE(andreas): (https://docs.github.com/en/rest/reference/repos#get-the-latest-release)
	cpr::Url url = !aSettings.url.empty()
					   ? aSettings.url
					   : "https://api.github.com/repos/Assertores/Einkaufsliste/releases/latest";
#if figure_out_how_to_do_this
	if (url) {
		infas::ILogger::Log(
			infas::LogLevel::Error,
			infas::LogType::StartUp,
			"invalide url: " + url.str());
		return false;
	}
#endif
	auto responce = cpr::Get(url);
	if (responce.status_code != locHttpOk) {
		infas::ILogger::Log(
			infas::LogLevel::Error,
			infas::LogType::StartUp,
			"endpoint answerd with Http error code: " + std::to_string(responce.status_code));
		return false;
	}

	const auto jsonDocument = nlohmann::json::parse(responce.text);
	if (!jsonDocument.contains("tag_name") || !jsonDocument["tag_name"].is_string()) {
		infas::ILogger::Log(
			infas::LogLevel::Error,
			infas::LogType::StartUp,
			"json document doesn't contain key 'tag_name' or it's not a string:\n"
				+ jsonDocument.dump());
		return false;
	}
	const auto patchVersion = jsonDocument["tag_name"].get<std::string>();
	bool isNewer = false;
	if (!CompareVersion(currentVersion, patchVersion, isNewer)) {
		infas::ILogger::Log(
			infas::LogLevel::Error,
			infas::LogType::StartUp,
			"unable to parse version numbers.\ncurrent: " + currentVersion
				+ "\nnew: " + patchVersion);
		return false;
	}
	if (isNewer) {
		infas::ILogger::Log(infas::LogLevel::Debug, infas::LogType::StartUp, "no update available");
		return false;
	}

	if (!jsonDocument.contains("assets") || !jsonDocument["assets"].is_array()) {
		infas::ILogger::Log(
			infas::LogLevel::Error,
			infas::LogType::StartUp,
			"json document doesn't contain key 'assets' or it's not an array:\n"
				+ jsonDocument.dump());
		return false;
	}
	const auto assets = jsonDocument["assets"].array();

	const auto build = std::find_if(assets.begin(), assets.end(), [&](const auto& aElement) {
		return aElement.contains("name") && aElement["name"].is_string()
			   && std::string(aElement["name"]).find(platform) != std::string::npos;
	});
	if (build == assets.end()) {
		infas::ILogger::Log(
			infas::LogLevel::Error,
			infas::LogType::StartUp,
			"no valide build found for platform: " + platform);
		return false;
	}
	if (!build->contains("browser_download_url") || !(*build)["browser_download_url"].is_string()) {
		infas::ILogger::Log(
			infas::LogLevel::Error,
			infas::LogType::StartUp,
			"asset dosen't contain key 'browser_download_url' or it's not a string: "
				+ build->dump());
		return false;
	}
	const auto patchUrl = cpr::Url((*build)["browser_download_url"].get<std::string>());

	const auto zipPath = exeDir / "patch.zip";
	std::ofstream zip(zipPath);
	cpr::Session session{};
	session.SetUrl(patchUrl);
	auto resp = session.Download(zip);
	if (resp.error) {
		infas::ILogger::Log(
			infas::LogLevel::Error,
			infas::LogType::StartUp,
			"unable to download patch from: " + patchUrl.str());
		return false;
	}
	zip.close();

	const auto patchPath = exeDir / "patch";
	elz::extractZip(zipPath, patchPath);
	std::filesystem::remove_all(zipPath);

	std::filesystem::recursive_directory_iterator newFiles(patchPath);
	for (const auto& it : newFiles) {
		const auto file = exeDir / std::filesystem::relative(it.path(), patchPath);
		if (std::filesystem::exists(file)) {
			// NOTE(andreas): there is no easy way to concatinate a string with a path without
			// adding a '/'
			std::filesystem::rename(file, file.string() + ".old");
		}
		std::filesystem::copy_file(it, file);
	}
	versionFile.clear();
	versionFile << patchVersion;
	// TODO(andreas): remove extracted files as well
	return true;
}
}  // namespace biz
