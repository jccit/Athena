add_library(Console STATIC "Console.cpp" "CVar.cpp")
target_precompile_headers(Console PRIVATE pch.h)

# Enable additional defines for the Debug build configuration
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -D_DEBUG")
set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -D_DEBUG")