add_library(Console STATIC "Console.cpp" "CVar.cpp")
target_precompile_headers(Console PRIVATE pch.h)
