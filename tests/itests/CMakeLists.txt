cmake_minimum_required (VERSION 3.15)

add_executable(IntegrationTests)

target_compile_features(IntegrationTests
	PUBLIC
		cxx_std_17
)

target_link_libraries(IntegrationTests
	PRIVATE
		biz
		GTest::gtest_main
)

target_sources(IntegrationTests
	PRIVATE
		"src/recipe_test.cpp"
)

add_test(NAME IntegrationTests COMMAND IntegrationTests)
