cmake_minimum_required (VERSION 3.15)

project ("Einkaufsliste" C CXX)

include("CodeAnalysis.cmake")
include(CTest)

include("root.cmake")
add_subdirectory("extern/googletest")
add_subdirectory("tests/utests")
