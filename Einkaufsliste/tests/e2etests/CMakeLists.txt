cmake_minimum_required (VERSION 3.15)

add_executable(EndToEndTests)

target_compile_features(EndToEndTests
	PUBLIC
		cxx_std_17
)

target_link_libraries(EndToEndTests
	PRIVATE
		biz
		GTest::gtest_main
)

target_sources(EndToEndTests
	PRIVATE
		"src/test.cpp"
)
