cmake_minimum_required(VERSION 3.16)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

project("Athena")

# Libraries
add_subdirectory("ThirdParty")

# Engine code
add_subdirectory("Sources")