add_executable(Einkaufsliste "src/main.cpp")

target_link_libraries(Einkaufsliste
	PRIVATE
		biz
)

add_library(biz STATIC)
SET_TARGET_PROPERTIES(biz PROPERTIES LINKER_LANGUAGE CXX)

target_compile_features(biz
	PUBLIC
		cxx_std_17
)

target_link_libraries(biz
	PRIVATE
		cpr::cpr
		rapidjson
)

target_include_directories(biz
	PUBLIC
		"includes"
		"extern/cpr/include"
)

target_sources(biz
	PUBLIC
		"includes/biz/application.h"
		"includes/biz/entry.h"
		"includes/biz/patcher.h"
		"includes/biz/argument_parser.h"
		"includes/biz/command_line_interface.h"
		"includes/biz/updater.h"
		"includes/common/change_recipe_name.h"
		"includes/common/command_chain.h"
		"includes/common/json_parser.h"
		"includes/common/log_on_console.h"
		"includes/common/md_parser.h"
		"includes/common/observable.h"
		"includes/common/open_convertion_files.h"
		"includes/common/open_recipe.h"
		"includes/common/print_current_file.h"
		"includes/common/recipe.h"
		"includes/common/unit.h"
		"includes/common/unit_convertion.h"
		"includes/interface/i_command.h"
		"includes/interface/i_command_memento.h"
		"includes/interface/i_file.h"
		"includes/interface/i_file_impl.h"
		"includes/interface/i_frontend.h"
		"includes/interface/i_logger.h"
		"includes/interface/i_observer.h"
	PRIVATE
		"src/application.cpp"
		"src/argument_parser.cpp"
		"src/change_recipe_name.cpp"
		"src/command_line_interface.cpp"
		"src/entry.cpp"
		"src/command_chain.cpp"
		"src/i_file.cpp"
		"src/i_logger.cpp"
		"src/json_parser.cpp"
		"src/log_on_console.cpp"
		"src/md_parser.cpp"
		"src/open_convertion_files.cpp"
		"src/open_recipe.cpp"
		"src/patcher.cpp"
		"src/print_current_file.cpp"
		"src/recipe.cpp"
		"src/unit.cpp"
		"src/unit_convertion.cpp"
		"src/updater.cpp"
)
