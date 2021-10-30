cmake_minimum_required (VERSION 3.15)

project ("Einkaufsliste" C CXX)

set(CPR_USE_SYSTEM_GTEST ON)
set(CPR_BUILD_TESTS OFF)
set(CPR_BUILD_TESTS_SSL OFF)
set(BUILD_SHARED_LIBS OFF)

add_subdirectory("extern/googletest")
# add_subdirectory("extern/rapidjson")
# add_subdirectory("extern/cpr")

include("CodeAnalysis.cmake")
include(CTest)

include("root.cmake")

add_subdirectory("tests/e2etests")
add_subdirectory("tests/utests")
add_subdirectory("tests/itests")
