cmake_minimum_required (VERSION 3.15)

project ("Einkaufsliste" C CXX)

set(CPR_USE_SYSTEM_GTEST ON)
set(CPR_BUILD_TESTS OFF)
set(CPR_BUILD_TESTS_SSL OFF)
set(BUILD_SHARED_LIBS OFF)
set(CURL_ZLIB OFF CACHE STRING "" FORCE)

add_subdirectory("extern/11Zip" EXCLUDE_FROM_ALL)
set(CURRENT_BUILD_TESTING ${BUILD_TESTING}) # NOTE(andreas): cpr sets BUILD_TESTING to OFF in there cmake file.
add_subdirectory("extern/cpr" EXCLUDE_FROM_ALL)
set(BUILD_TESTING ${CURRENT_BUILD_TESTING})
add_subdirectory("extern/googletest" EXCLUDE_FROM_ALL)
add_subdirectory("extern/json" EXCLUDE_FROM_ALL)

# NOTE(andreas): this file contains a non ASCII copyright simbole whitch prevents clang of compiling it.
# https://github.com/curl/curl/issues/7765
file(WRITE "${CMAKE_BINARY_DIR}/_deps/curl-src/lib/libcurl.rc" "")

include("CodeAnalysis.cmake")
include(CTest)

include("root.cmake")

add_subdirectory("tests/e2etests")
add_subdirectory("tests/utests")
add_subdirectory("tests/itests")
