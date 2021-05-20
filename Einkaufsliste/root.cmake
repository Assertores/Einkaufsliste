add_executable(Einkaufsliste "src/main.cpp")

target_link_libraries(Einkaufsliste
	PRIVATE
		biz
)

add_library(biz)
SET_TARGET_PROPERTIES(biz PROPERTIES LINKER_LANGUAGE CXX)

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
		"includes/common/i_file_impl.h"
	PRIVATE
		"src/application.cpp"
		"src/argument_parser.cpp"
		"src/entry.cpp"
		"src/i_file.cpp"
		"src/patcher.cpp"
		"src/updater.cpp"
)
