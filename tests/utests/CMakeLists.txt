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
		GTest::gmock
)

target_sources(UnitTests
	PRIVATE
		"src/argument_parser_test.cpp"
		"src/command_chain_test.cpp"
		"src/file_implimentation_test.cpp"
		"src/log_on_console_test.cpp"
		"src/logger_test.cpp"
		"src/md_parser_test.cpp"
		"src/observer_test.cpp"
		"src/unit_test.cpp"
)

add_test(NAME UnitTests COMMAND UnitTests)
