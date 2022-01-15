
#include "biz/github_updater.h"

#include "biz/log_on_console.h"

#include <gtest/gtest.h>

#include <filesystem>

static const std::filesystem::path locAssetDir{ASSETS_DIR "_Live"};

class GithubUpdaterStub : public biz::GithubUpdater {
public:
	bool RetrieveMetaData(bool aPrerelease) override {
		// TODO(andreas): replace this with a json of my own repository once i made a release
		myJson = nlohmann::json::parse(
			R"json({
                "url": "https://api.github.com/repos/octocat/Hello-World/releases/1",
                "html_url": "https://github.com/octocat/Hello-World/releases/v1.0.0",
                "assets_url": "https://api.github.com/repos/octocat/Hello-World/releases/1/assets",
                "upload_url": "https://uploads.github.com/repos/octocat/Hello-World/releases/1/assets{?name,label}",
                "tarball_url": "https://api.github.com/repos/octocat/Hello-World/tarball/v1.0.0",
                "zipball_url": "https://api.github.com/repos/octocat/Hello-World/zipball/v1.0.0",
                "discussion_url": "https://github.com/octocat/Hello-World/discussions/90",
                "id": 1,
                "node_id": "MDc6UmVsZWFzZTE=",
                "tag_name": ")json"
			+ myTestVersion + R"json(",
                "target_commitish": "master",
                "name": "avndsfuse",
                "body": "Description of the release",
                "draft": false,
                "prerelease": false,
                "created_at": "2013-02-27T19:35:32Z",
                "published_at": "2013-02-27T19:35:32Z",
                "author": {
                    "login": "octocat",
                    "id": 1,
                    "node_id": "MDQ6VXNlcjE=",
                    "avatar_url": "https://github.com/images/error/octocat_happy.gif",
                    "gravatar_id": "",  "url": "https://api.github.com/users/octocat",
                    "html_url": "https://github.com/octocat",
                    "followers_url": "https://api.github.com/users/octocat/followers",
                    "following_url": "https://api.github.com/users/octocat/following{/other_user}",
                    "gists_url": "https://api.github.com/users/octocat/gists{/gist_id}",
                    "starred_url": "https://api.github.com/users/octocat/starred{/owner}{/repo}",
                    "subscriptions_url": "https://api.github.com/users/octocat/subscriptions",
                    "organizations_url": "https://api.github.com/users/octocat/orgs",
                    "repos_url": "https://api.github.com/users/octocat/repos",
                    "events_url": "https://api.github.com/users/octocat/events{/privacy}",
                    "received_events_url": "https://api.github.com/users/octocat/received_events",
                    "type": "User",
                    "site_admin": false
                },
                "assets": [ {
                    "url": "https://api.github.com/repos/octocat/Hello-World/releases/assets/1",
                    "browser_download_url": ")json"
			+ myDownloadUrlWin + R"json(",
                    "id": 1,
                    "node_id": "MDEyOlJlbGVhc2VBc3NldDE=",
                    "name": ")json"
			+ myAssetNameWin + R"json(",
                    "label": "short description",
                    "state": "uploaded",
                    "content_type": "application/zip",
                    "size": 1024,
                    "download_count": 42,
                    "created_at": "2013-02-27T19:35:32Z",
                    "updated_at": "2013-02-27T19:35:32Z",
                    "uploader": {
                        "login": "octocat",
                        "id": 1,
                        "node_id": "MDQ6VXNlcjE=",
                        "avatar_url": "https://github.com/images/error/octocat_happy.gif",
                        "gravatar_id": "",
                        "url": "https://api.github.com/users/octocat",
                        "html_url": "https://github.com/octocat",
                        "followers_url": "https://api.github.com/users/octocat/followers",
                        "following_url": "https://api.github.com/users/octocat/following{/other_user}",
                        "gists_url": "https://api.github.com/users/octocat/gists{/gist_id}",
                        "starred_url": "https://api.github.com/users/octocat/starred{/owner}{/repo}",
                        "subscriptions_url": "https://api.github.com/users/octocat/subscriptions",
                        "organizations_url": "https://api.github.com/users/octocat/orgs",
                        "repos_url": "https://api.github.com/users/octocat/repos",
                        "events_url": "https://api.github.com/users/octocat/events{/privacy}",
                        "received_events_url": "https://api.github.com/users/octocat/received_events",
                        "type": "User",
                        "site_admin": false
                    }
                }, {
                    "url": "https://api.github.com/repos/octocat/Hello-World/releases/assets/1",
                    "browser_download_url": ")json"
			+ myDownloadUrlLin + R"json(",
                    "id": 1,
                    "node_id": "MDEyOlJlbGVhc2VBc3NldDE=",
                    "name": ")json"
			+ myAssetNameLin + R"json(",
                    "label": "short description",
                    "state": "uploaded",
                    "content_type": "application/zip",
                    "size": 1024,
                    "download_count": 42,
                    "created_at": "2013-02-27T19:35:32Z",
                    "updated_at": "2013-02-27T19:35:32Z",
                    "uploader": {
                        "login": "octocat",
                        "id": 1,
                        "node_id": "MDQ6VXNlcjE=",
                        "avatar_url": "https://github.com/images/error/octocat_happy.gif",
                        "gravatar_id": "",
                        "url": "https://api.github.com/users/octocat",
                        "html_url": "https://github.com/octocat",
                        "followers_url": "https://api.github.com/users/octocat/followers",
                        "following_url": "https://api.github.com/users/octocat/following{/other_user}",
                        "gists_url": "https://api.github.com/users/octocat/gists{/gist_id}",
                        "starred_url": "https://api.github.com/users/octocat/starred{/owner}{/repo}",
                        "subscriptions_url": "https://api.github.com/users/octocat/subscriptions",
                        "organizations_url": "https://api.github.com/users/octocat/orgs",
                        "repos_url": "https://api.github.com/users/octocat/repos",
                        "events_url": "https://api.github.com/users/octocat/events{/privacy}",
                        "received_events_url": "https://api.github.com/users/octocat/received_events",
                        "type": "User",
                        "site_admin": false
                    }
                }]
            })json");
		return true;
	}

	bool DownloadPatch() override { return true; }

	std::filesystem::path GetExePath() override { return locAssetDir; }

	std::string myTestVersion = "v1.0.0";
	std::string myAssetNameWin = "Einkaufsliste_1.0.0_win10.zip";
	std::string myAssetNameLin = "Einkaufsliste_1.0.0_linux.zip";
	std::string myDownloadUrlWin = "www.something.com/to/download/win10.zip";
	std::string myDownloadUrlLin = "www.something.com/to/download/linux.zip";
};

class GithubTestFixture : public ::testing::Test {
protected:
	void SetUp() override {
		std::filesystem::copy(
			ASSETS_DIR,
			locAssetDir,
			std::filesystem::copy_options::overwrite_existing
				| std::filesystem::copy_options::recursive);

		infas::ILogger::SetLogLevel(infas::LogLevel::Verbose);
		infas::ILogger::SetLogMask(infas::locLogMaskAll);
	}

	void TearDown() override {
		if (HasFailure()) {
			infas::ILogger::SetImplementation(biz::LogOnConsole(std::cout));
			std::cout << "===== ===== assetContent ===== =====\n";
			for (const auto& it : std::filesystem::recursive_directory_iterator(
					 std::filesystem::path(locAssetDir))) {
				std::cout << " > " << it.path().u8string() << '\n';
				if (it.is_regular_file()) {
					auto file = std::ifstream(it.path());
					std::cout << std::string(
						(std::istreambuf_iterator<char>(file)),
						(std::istreambuf_iterator<char>()))
							  << '\n';
					file.close();
				}
			}
		}
		infas::ILogger::Clear();

		std::filesystem::remove_all(locAssetDir);
	}
};

TEST_F(GithubTestFixture, higher_version_is_identifyed_as_patch)  // NOLINT
{
	GithubUpdaterStub subject;
	subject.myTestVersion = "v2.0.0";
	subject.RetrieveMetaData(false);
	EXPECT_TRUE(subject.IsPatchUpdate());
	subject.myTestVersion = "v1.3.0";
	subject.RetrieveMetaData(false);
	EXPECT_TRUE(subject.IsPatchUpdate());
	subject.myTestVersion = "v1.2.4";
	subject.RetrieveMetaData(false);
	EXPECT_TRUE(subject.IsPatchUpdate());
}

TEST_F(GithubTestFixture, lower_version_is_identifyed_as_no_patch)	// NOLINT
{
	GithubUpdaterStub subject;
	subject.myTestVersion = "v0.0.0";
	subject.RetrieveMetaData(false);
	EXPECT_FALSE(subject.IsPatchUpdate());
	subject.myTestVersion = "v1.0.0";
	subject.RetrieveMetaData(false);
	EXPECT_FALSE(subject.IsPatchUpdate());
	subject.myTestVersion = "v1.2.0";
	subject.RetrieveMetaData(false);
	EXPECT_FALSE(subject.IsPatchUpdate());
}

TEST_F(GithubTestFixture, same_version_is_identifyed_as_no_patch)  // NOLINT
{
	GithubUpdaterStub subject;
	subject.myTestVersion = "v1.2.3";
	subject.RetrieveMetaData(false);
	EXPECT_FALSE(subject.IsPatchUpdate());
}

TEST_F(GithubTestFixture, can_handle_negative_numbers)	// NOLINT
{
	bool isNewer = false;
	ASSERT_TRUE(biz::GithubUpdater::CompareVersion("v0.0.-1", "v0.0.0", isNewer));
	EXPECT_TRUE(isNewer);
}

TEST_F(GithubTestFixture, download_url_is_read_out_from_json)  // NOLINT
{
	GithubUpdaterStub subject;
	subject.RetrieveMetaData(false);
	ASSERT_TRUE(subject.RetrievePatchLocation());
#if _WIN32
	EXPECT_EQ(subject.myPatch, subject.myDownloadUrlWin);
#elif __linux__
	EXPECT_EQ(subject.myPatch, subject.myDownloadUrlLin);
#else
#error "unsupporded platform"
#endif
}

TEST_F(GithubTestFixture, patch_zip_is_unpacked)  // NOLINT
{
	GithubUpdaterStub subject;
	ASSERT_TRUE(subject.ExtractPatch());

	EXPECT_TRUE(std::filesystem::exists(subject.GetPatchPath()));
	EXPECT_TRUE(std::filesystem::exists(subject.GetPatchPath() / "stuff.txt"));
	EXPECT_TRUE(std::filesystem::exists(subject.GetPatchPath() / "subfolder"));
	EXPECT_TRUE(std::filesystem::exists(subject.GetPatchPath() / "subfolder" / "moreStuff.txt"));

	auto stuffFile = std::ifstream(subject.GetPatchPath() / "stuff.txt");
	const std::string stuffContent(
		(std::istreambuf_iterator<char>(stuffFile)),
		(std::istreambuf_iterator<char>()));
	stuffFile.close();
	EXPECT_EQ(stuffContent, "content");

	auto moreStuffFile = std::ifstream(subject.GetPatchPath() / "subfolder" / "moreStuff.txt");
	const std::string moreStuffContent(
		(std::istreambuf_iterator<char>(moreStuffFile)),
		(std::istreambuf_iterator<char>()));
	moreStuffFile.close();
	EXPECT_EQ(moreStuffContent, "different content");
}

TEST_F(GithubTestFixture, patch_is_applied_to_folder)  // NOLINT
{
	GithubUpdaterStub subject;
	ASSERT_TRUE(subject.ExtractPatch());
	ASSERT_TRUE(subject.ApplyPatch());

	EXPECT_TRUE(std::filesystem::exists(subject.GetExePath() / "stuff.txt"));
	EXPECT_TRUE(std::filesystem::exists(subject.GetExePath() / "subfolder"));
	EXPECT_TRUE(std::filesystem::exists(subject.GetExePath() / "subfolder" / "moreStuff.txt"));

	auto stuffFile = std::ifstream(subject.GetExePath() / "stuff.txt");
	const std::string stuffContent(
		(std::istreambuf_iterator<char>(stuffFile)),
		(std::istreambuf_iterator<char>()));
	stuffFile.close();
	EXPECT_EQ(stuffContent, "content");

	auto moreStuffFile = std::ifstream(subject.GetExePath() / "subfolder" / "moreStuff.txt");
	const std::string moreStuffContent(
		(std::istreambuf_iterator<char>(moreStuffFile)),
		(std::istreambuf_iterator<char>()));
	moreStuffFile.close();
	EXPECT_EQ(moreStuffContent, "different content");
}

TEST_F(GithubTestFixture, existing_files_are_renaimed_to_old)  // NOLINT
{
	GithubUpdaterStub subject;
	ASSERT_TRUE(subject.ExtractPatch());
	ASSERT_TRUE(subject.ApplyPatch());

	EXPECT_TRUE(std::filesystem::exists(subject.GetExePath() / "stuff.txt.old"));

	auto stuffFile = std::ifstream(subject.GetExePath() / "stuff.txt.old");
	const std::string stuffContent(
		(std::istreambuf_iterator<char>(stuffFile)),
		(std::istreambuf_iterator<char>()));
	stuffFile.close();
	EXPECT_EQ(stuffContent, "SHOULD BE OVERWRITTEN");
}

TEST_F(GithubTestFixture, version_file_is_not_overwritten)	// NOLINT
{
	GithubUpdaterStub subject;
	ASSERT_TRUE(subject.ExtractPatch());
	ASSERT_TRUE(subject.ApplyPatch());

	EXPECT_FALSE(std::filesystem::exists(subject.GetExePath() / "version.txt.old"));
	// TODO(andreas): this test is not sufficiont!!!
}

TEST_F(GithubTestFixture, new_version_is_written_to_version_file)  // NOLINT
{
	GithubUpdaterStub subject;
	subject.myNewVersion = "asbfnuaeklskd";
	ASSERT_TRUE(subject.ExtractPatch());
	ASSERT_TRUE(subject.ApplyPatch());

	auto versionFile = std::ifstream(subject.GetExePath() / "version.txt");
	const std::string versionContent(
		(std::istreambuf_iterator<char>(versionFile)),
		(std::istreambuf_iterator<char>()));
	versionFile.close();
	EXPECT_EQ(versionContent, subject.myNewVersion);
}

TEST_F(GithubTestFixture, temporary_files_are_cleaned_up)  // NOLINT
{
	GithubUpdaterStub subject;
	ASSERT_TRUE(subject.ExtractPatch());
	subject.CleanUp();

	EXPECT_FALSE(std::filesystem::exists(subject.GetPatchPath()));
	EXPECT_FALSE(std::filesystem::exists(subject.GetZipPath()));
}

TEST_F(GithubTestFixture, cleanup_wont_crash_on_partial_data)  // NOLINT
{
	GithubUpdaterStub subject;
	EXPECT_NO_THROW(subject.CleanUp());	 // NOLINT

	EXPECT_FALSE(std::filesystem::exists(subject.GetPatchPath()));
	EXPECT_FALSE(std::filesystem::exists(subject.GetZipPath()));
}

TEST_F(GithubTestFixture, extraction_fails_if_zip_file_is_missing)	// NOLINT
{
	GithubUpdaterStub subject;
	std::filesystem::remove(locAssetDir / "patch.zip");
	EXPECT_FALSE(subject.ExtractPatch());
}
