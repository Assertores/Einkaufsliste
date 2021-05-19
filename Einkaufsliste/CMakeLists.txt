cmake_minimum_required (VERSION 3.15)

project ("Einkaufsliste" C CXX)

include("CodeAnalysis.cmake")

add_executable(Einkaufsliste "src/main.cpp")

target_link_libraries(Einkaufsliste
	PRIVATE
		biz
)

add_library(biz)

target_compile_features(biz
	PUBLIC
		cxx_std_17
)

target_include_directories(biz
	PUBLIC
		"includes"
)
