add_library(Filesystem STATIC "Paths.cpp" "Raw.cpp")
target_precompile_headers(Filesystem PRIVATE pch.h)

# Enable additional defines for the Debug build configuration
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -D_DEBUG")
set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -D_DEBUG")

target_link_libraries(Filesystem Utils)

target_include_directories(Filesystem PUBLIC ../)