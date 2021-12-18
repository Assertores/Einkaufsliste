cmake_minimum_required (VERSION 3.15)

add_executable(MTStartProcess "src/start_process_test.cpp")

target_compile_features(MTStartProcess
	PUBLIC
		cxx_std_17
)

target_link_libraries(MTStartProcess
	PRIVATE
		biz
)
