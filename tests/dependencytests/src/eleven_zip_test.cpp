#include "assets_folder_fixture.h"

#include <elzip/elzip.hpp>
#include <gtest/gtest.h>

#include <filesystem>
#include <fstream>
#include <iostream>

using ElevenZipFixture = AssetsFolderFixture;

bool
CompareStreams(std::ifstream&& aLhs, std::ifstream&& aRhs) {
	while (aLhs.good() && aRhs.good()) {
		if (aLhs.get() != aRhs.get()) {
			return false;
		}
	}
	return aLhs.eof() == aRhs.eof();
}

TEST_F(ElevenZipFixture, wont_throw_while_unzipping) // NOLINT
{
	const auto zipPath = locAssetDir / "archive.zip";
	const auto extractPath = locAssetDir / "extracted";
	const auto originalPath = locAssetDir / "archive";

	// NOLINTNEXTLINE (cppcoreguidelines-avoid-goto,hicpp-avoid-goto)
	EXPECT_NO_THROW(elz::extractZip(zipPath, extractPath));
}

TEST_F(ElevenZipFixture, files_are_created_when_unziped) // NOLINT
{
	const auto zipPath = locAssetDir / "archive.zip";
	const auto extractPath = locAssetDir / "extracted";
	const auto originalPath = locAssetDir / "archive";

	elz::extractZip(zipPath, extractPath);

	EXPECT_TRUE(std::filesystem::exists(extractPath));
	EXPECT_TRUE(std::filesystem::exists(extractPath / "binary.png"));
	EXPECT_TRUE(std::filesystem::exists(extractPath / "stuff.txt"));
	EXPECT_TRUE(std::filesystem::exists(extractPath / "subfolder"));
	EXPECT_TRUE(std::filesystem::exists(extractPath / "subfolder" / "moreStuff.txt"));
}

TEST_F(ElevenZipFixture, files_are_equivalent_to_original_when_unziped) // NOLINT
{
	const auto zipPath = locAssetDir / "archive.zip";
	const auto extractPath = locAssetDir / "extracted";
	const auto originalPath = locAssetDir / "archive";

	elz::extractZip(zipPath, extractPath);

	EXPECT_TRUE(CompareStreams(
		std::ifstream(extractPath / "stuff.txt"),
		std::ifstream(originalPath / "stuff.txt")));
	EXPECT_TRUE(CompareStreams(
		std::ifstream(extractPath / "subfolder" / "moreStuff.txt"),
		std::ifstream(originalPath / "subfolder" / "moreStuff.txt")));
	EXPECT_TRUE(CompareStreams(
		std::ifstream(extractPath / "binary.png"),
		std::ifstream(originalPath / "binary.png")));
}