#define _SILENCE_ALL_CXX17_DEPRECATION_WARNINGS	 // NOLINT
												 // "bugprone-reserved-identifier,cert-dcl37-c,cert-dcl51-cpp"
#include "biz/updater.h"

#include "interface/i_logger.h"

#include <cpr/cpr.h>
#include <nlohmann/json.hpp>

namespace biz {

static constexpr auto locHttpOk = 200;

// TODO(andreas): impliment
std::filesystem::path
GetExePath() {
	infas::ILogger::Log(
		infas::LogLevel::Fatal,
		infas::LogType::StartUp,
		"GetExePath not implimented");
	return std::filesystem::current_path();
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
	// TODO(andreas): check if version is newer than current version

	if (!jsonDocument.contains("assets") || !jsonDocument["assets"].is_array()) {
		infas::ILogger::Log(
			infas::LogLevel::Error,
			infas::LogType::StartUp,
			"json document doesn't contain key 'assets' or it's not an array:\n"
				+ jsonDocument.dump());
		return false;
	}
	const auto assets = jsonDocument["assets"].array();

	// TODO(andreas): figure out which platform to download
	const std::string platform = "win10";
	// TODO(andreas): weard random magic string also now is win10 specific
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

	std::ofstream zip(GetExePath() / "patch.zip");
	cpr::Session().SetUrl(patchUrl);
	auto resp = cpr::Download(zip);
	if (resp.error) {
		infas::ILogger::Log(
			infas::LogLevel::Error,
			infas::LogType::StartUp,
			"unable to download patch from: " + patchUrl.str());
		return false;
	}
	// TODO(andreas): rename stuff to .old
	// TODO(andreas): unzip
	// TODO(andreas): save new version number or something
	infas::ILogger::Log(infas::LogLevel::Fatal, infas::LogType::StartUp, "updater not implimented");
	return false;
}
}  // namespace biz
