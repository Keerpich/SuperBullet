cmake_minimum_required (VERSION 3.1.2)

project (SuperBullet)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /EHc /std:c++latest")

message ("cxx Flags: " ${CMAKE_CXX_FLAGS})

include(${CMAKE_BINARY_DIR}/conanbuildinfo_multi.cmake)
conan_basic_setup()

# Sub-directories where more CMakeLists.txt exist
add_subdirectory(main)
add_subdirectory(ModuleWindow)
add_subdirectory(ModuleRendering)
add_subdirectory(Components)
add_subdirectory(Utilities)
