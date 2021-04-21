add_library(Filesystem STATIC "Paths.cpp" "Raw.cpp")
target_precompile_headers(Filesystem PRIVATE pch.h)

target_link_libraries(Filesystem Utils)

target_include_directories(Filesystem PUBLIC ../)