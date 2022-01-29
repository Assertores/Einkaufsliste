#pragma once

#include <gtest/gtest.h>

#include <filesystem>
#include <fstream>
#include <iostream>

static const std::filesystem::path locAssetDir{ASSETS_DIR "_Live"};

class AssetsFolderFixture : public ::testing::Test {
protected:
	void SetUp() override {
		std::filesystem::copy(
			ASSETS_DIR,
			locAssetDir,
			std::filesystem::copy_options::overwrite_existing
				| std::filesystem::copy_options::recursive);
	}

	void TearDown() override {
		if (HasFailure()) {
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
		std::filesystem::remove_all(locAssetDir);
	}
};