set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${PROJECT_SOURCE_DIR}/cmake")

find_package(SDL2 REQUIRED)

add_library(Utils STATIC "String.cpp" "PerfMonitor.cpp" "MessageBox.cpp")
target_precompile_headers(Utils PRIVATE pch.h)

target_link_libraries(Utils ${SDL2_LIBRARY})

target_include_directories(Utils PUBLIC ${SDL2_INCLUDE_DIR})