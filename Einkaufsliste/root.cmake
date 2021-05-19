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
		"includes/biz/argument_parser.h"
		"includes/biz/updater.h"
		"includes/common/i_file.h"
	PRIVATE
		"includes/common/file.h"
		"src/application.cpp"
		"src/entry.cpp"
		"src/file.cpp"
		"src/patcher.cpp"
		"src/argument_parser.cpp"
		"src/updater.cpp"
)
