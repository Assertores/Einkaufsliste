cmake_minimum_required (VERSION 3.15)

add_executable(UnitTests)

target_compile_features(UnitTests
	PUBLIC
		cxx_std_17
)

target_link_libraries(UnitTests
	PRIVATE
		biz
		GTest::gtest_main
)

target_sources(UnitTests
	PRIVATE
		"src/argument_parser_test.cpp"
		"src/command_test.cpp"
		"src/file_implimentation_test.cpp"
)
