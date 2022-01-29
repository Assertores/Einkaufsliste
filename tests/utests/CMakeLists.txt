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

target_include_directories(UnitTests
	PUBLIC
		"../utility"
)

target_sources(UnitTests
	PRIVATE
		"src/add_list_recipe_test.cpp"
		"src/add_list_week_test.cpp"
		"src/add_recipe_unit_test.cpp"
		"src/add_week_recipe_test.cpp"
		"src/argument_parser_test.cpp"
		"src/change_recipe_description_test.cpp"
		"src/change_recipe_name_test.cpp"
		"src/command_chain_test.cpp"
		"src/compile_list_test.cpp"
		"src/file_implementation_test.cpp"
		"src/github_updater_test.cpp"
		"src/log_on_console_test.cpp"
		"src/logger_test.cpp"
		"src/md_parser_test.cpp"
		"src/observer_test.cpp"
		"src/open_list_test.cpp"
		"src/open_recipe_test.cpp"
		"src/open_week_test.cpp"
		"src/remove_recipe_unit_test.cpp"
		"src/remove_week_recipe_test.cpp"
		"src/unit_test.cpp"
)

add_custom_command(
	TARGET UnitTests POST_BUILD
	COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_LIST_DIR}/assets $<TARGET_FILE_DIR:UnitTests>/assets
)

target_compile_definitions(UnitTests PRIVATE ASSETS_DIR="$<TARGET_FILE_DIR:UnitTests>/assets")

add_test(NAME UnitTests COMMAND UnitTests)
