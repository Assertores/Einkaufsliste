#include "assets_folder_fixture.h"

#include <cpr/cpr.h>
#include <gtest/gtest.h>

#include <filesystem>
#include <fstream>
#include <iostream>

using CprFixture = AssetsFolderFixture;

TEST(Cpr, can_connect_to_internet) // NOLINT
{
	auto responce = cpr::Get(cpr::Url("httpbin.org/status/200"));

	EXPECT_EQ(responce.status_code, 200);
}

TEST(Cpr, can_reseave_text_data) // NOLINT
{
	// NOTE(andreas): base64 is the best i can get it to just return whatever i send it
	auto responce = cpr::Get(cpr::Url("httpbin.org/base64/SFRUUEJJTiBpcyBhd2Vzb21l"));

	ASSERT_EQ(responce.status_code, 200);
	EXPECT_EQ(responce.text, "HTTPBIN is awesome");
}

TEST_F(CprFixture, can_stream_binary_data_into_file) // NOLINT
{
	const auto binPath = locAssetDir / "a.bin";
	constexpr auto bytes = 10;
	const std::string bytesString = "10";

	std::ofstream bin(binPath, std::ios_base::out | std::ios_base::binary);
	cpr::Session session{};
	session.SetUrl(cpr::Url("httpbin.org/bytes/" + bytesString));
	auto responce = session.Download(bin);
	bin.close();

	ASSERT_EQ(responce.status_code, 200);
	ASSERT_TRUE(std::filesystem::exists(binPath));
	EXPECT_EQ(std::filesystem::file_size(binPath), bytes);
}