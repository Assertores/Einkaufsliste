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

target_sources(biz
	PUBLIC
		"includes/biz/application.h"
		"includes/biz/entry.h"
		"includes/biz/patcher.h"
		"includes/biz/start_argument_parser.h"
		"includes/biz/updater.h"
	PRIVATE
		"src/application.cpp"
		"src/entry.cpp"
		"src/patcher.cpp"
		"src/start_argument_parser.cpp"
		"src/updater.cpp"
)
