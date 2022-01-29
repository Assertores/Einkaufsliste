cmake_minimum_required (VERSION 3.15)

add_executable(DependencyTests)

target_compile_features(DependencyTests
	PUBLIC
		cxx_std_17
)

target_link_libraries(DependencyTests
	PRIVATE
		cpr::cpr
		nlohmann_json::nlohmann_json
		elzip
		GTest::gtest_main
		GTest::gmock
)

target_include_directories(DependencyTests
	PUBLIC
		"../utility"
)

target_sources(DependencyTests
	PRIVATE
		"src/cpr_curl_test.cpp"
		"src/eleven_zip_test.cpp"
		"src/json_nlohmann_test.cpp"
)

add_custom_command(
	TARGET DependencyTests POST_BUILD
	COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_LIST_DIR}/assets $<TARGET_FILE_DIR:DependencyTests>/assets
)

target_compile_definitions(DependencyTests PRIVATE ASSETS_DIR="$<TARGET_FILE_DIR:DependencyTests>/assets")

add_test(NAME DependencyTests COMMAND DependencyTests)
