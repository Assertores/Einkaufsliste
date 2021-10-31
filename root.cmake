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
		# cpr::cpr
		# rapidjson
)

target_include_directories(biz
	PUBLIC
		"includes"
		# "extern/cpr/include"
)

target_sources(biz
	PUBLIC
		"includes/biz/add_list_recipe.h"
		"includes/biz/add_list_week.h"
		"includes/biz/add_recipe_unit.h"
		"includes/biz/add_week_recipe.h"
		"includes/biz/application.h"
		"includes/biz/argument_parser.h"
		"includes/biz/change_recipe_description.h"
		"includes/biz/change_recipe_name.h"
		"includes/biz/command_line_interface.h"
		"includes/biz/compile_list.h"
		"includes/biz/entry.h"
		"includes/biz/log_on_console.h"
		"includes/biz/open_convertion_files.h"
		"includes/biz/open_list.h"
		"includes/biz/open_recipe.h"
		"includes/biz/open_week.h"
		"includes/biz/patcher.h"
		"includes/biz/print_current_file.h"
		"includes/biz/remove_recipe_unit.h"
		"includes/biz/remove_week_recipe.h"
		"includes/biz/updater.h"
		"includes/common/command_chain.h"
		"includes/common/json_parser.h"
		"includes/common/list.h"
		"includes/common/md_parser.h"
		"includes/common/observable.h"
		"includes/common/recipe.h"
		"includes/common/unit.h"
		"includes/common/unit_convertion.h"
		"includes/common/week.h"
		"includes/interface/i_command.h"
		"includes/interface/i_command_memento.h"
		"includes/interface/i_file.h"
		"includes/interface/i_file_impl.h"
		"includes/interface/i_frontend.h"
		"includes/interface/i_logger.h"
		"includes/interface/i_observer.h"
	PRIVATE
		"src/add_list_recipe.cpp"
		"src/add_list_week.cpp"
		"src/add_recipe_unit.cpp"
		"src/add_week_recipe.cpp"
		"src/application.cpp"
		"src/argument_parser.cpp"
		"src/change_recipe_description.cpp"
		"src/change_recipe_name.cpp"
		"src/command_chain.cpp"
		"src/command_line_interface.cpp"
		"src/compile_list.cpp"
		"src/entry.cpp"
		"src/i_file.cpp"
		"src/i_logger.cpp"
		"src/json_parser.cpp"
		"src/list.cpp"
		"src/log_on_console.cpp"
		"src/md_parser.cpp"
		"src/open_convertion_files.cpp"
		"src/open_list.cpp"
		"src/open_recipe.cpp"
		"src/open_week.cpp"
		"src/patcher.cpp"
		"src/print_current_file.cpp"
		"src/recipe.cpp"
		"src/remove_recipe_unit.cpp"
		"src/remove_week_recipe.cpp"
		"src/unit_convertion.cpp"
		"src/unit.cpp"
		"src/updater.cpp"
		"src/week.cpp"
)