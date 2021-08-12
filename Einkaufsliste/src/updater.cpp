#include "biz/updater.h"
#if false
#include <filesystem>

#include <cpr/cpr.h>
#undef max
#undef min
#define _SILENCE_ALL_CXX17_DEPRECATION_WARNINGS // NOLINT
#define _SILENCE_CXX17_ITERATOR_BASE_CLASS_DEPRECATION_WARNING // NOLINT
#include <rapidjson/document.h> // NOLINT clang-diagnostic-deprecated-declarations
#endif
namespace biz {

static constexpr auto locHttpOk = 200;

bool
Update(const UpdaterSettings& aSettings)
{
	#if false
	if (!aSettings.doUpdate)
	{
		return false;
	}
	// NOTE(andreas): (https://docs.github.com/en/rest/reference/repos#get-the-latest-release)
	auto responce =
		cpr::Get(cpr::Url("https://api.github.com/repos/Assertores/Einkaufsliste/releases/latest"));
	if (responce.status_code != locHttpOk)
	{
		// TODO(andreas): log error
		return false;
	}
	rapidjson::Document jsonDocument {};
	jsonDocument.Parse(responce.text.c_str());
	if (jsonDocument.HasMember("prerelease") && jsonDocument["prerelease"].IsBool())
	{
		if (jsonDocument["prerelease"].GetBool() && !aSettings.getPrerelease)
		{
			// TODO(andreas): get next one?
			return false;
		}
	}
	if (!jsonDocument.HasMember("published_at") || !jsonDocument["published_at"].IsString())
	{
		// TODO(andreas): handle error.
		return false;
	}
	// TODO(andreas): check if version is newer than current version
	if (!jsonDocument.HasMember("assets") || !jsonDocument["assets"].IsArray())
	{
		// TODO(andreas): handle error.
		return false;
	}
	auto assets = jsonDocument["assets"].GetArray();
	assets[0].HasMember("name");
	assets[0]["name"].IsString();
	assets[0]["name"].GetString();
	// TODO(andreas): weard random magic string also now is win10 specific
	auto* build = std::find_if(assets.begin(), assets.end(), [&](const auto& aElement) {
		return aElement.HasMember("name") && aElement["name"].IsString()
			&& std::string(assets[0]["name"].GetString()).find("win10") != std::string::npos;
	});
	if (build == assets.end())
	{
		// TODO(andreas): handle error.
		return false;
	}
	if (!build->HasMember("browser_download_url") || !(*build)["browser_download_url"].IsString())
	{
		// TODO(andreas): handle error.
		return false;
	}
	std::ofstream zip(std::filesystem::current_path() / "patch.zip");
	cpr::Session().SetUrl(cpr::Url((*build)["browser_download_url"].GetString()));
	auto resp = cpr::Download(zip);
	if (resp.error)
	{
		// TODO(andreas): handle error.
		return false; // NOLINT // TODO(andreas): remove this noce i know how to handle errors
	}
	// TODO(andreas): rename stuff to .old
	// TODO(andreas): unzip
	// TODO(andreas): save new version number or something
	return true;
	#else
	return false;
	#endif
}
} // namespace biz
