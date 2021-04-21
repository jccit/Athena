set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${PROJECT_SOURCE_DIR}/cmake")

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)

file(GLOB SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)
file(GLOB IMGUI_SOURCES ../../ThirdParty/imgui/*.cpp)

add_executable(Athena WIN32 ${SOURCES} ${IMGUI_SOURCES} ../../ThirdParty/imgui/backends/imgui_impl_sdl.cpp ../../ThirdParty/imgui_sdl/imgui_sdl.cpp)

if(WIN32)
	set_target_properties(Athena PROPERTIES WIN32_EXECUTABLE TRUE)
endif()

target_precompile_headers(Athena PRIVATE pch.h)

target_link_libraries(Athena Utils)
target_link_libraries(Athena Console)
target_link_libraries(Athena Filesystem)
target_link_libraries(Athena ${SDL2_LIBRARY} ${SDL2_IMAGE_LIBRARIES} ${SDL2MAIN_LIBRARY})
target_link_libraries(Athena squirrel sqstdlib)
target_link_libraries(Athena simplesquirrel_static)

target_include_directories(Athena PUBLIC .)
target_include_directories(Athena PUBLIC ..)
target_include_directories(Athena PUBLIC ${SDL2_INCLUDE_DIRS} ${SDL2_IMAGE_INCLUDE_DIRS} ${SDL2_TTF_INCLUDE_DIRS})
target_include_directories(Athena PUBLIC ${simplesquirrel_SOURCE_DIR}/include ${simplesquirrel_SOURCE_DIR}/libs/squirrel/include)
target_include_directories(Athena PUBLIC ${SQUIRREL_INCLUDE_DIR})
target_include_directories(Athena PUBLIC ../../ThirdParty)
target_include_directories(Athena PUBLIC ../../ThirdParty/cereal/include)
target_include_directories(Athena PUBLIC ../../ThirdParty/argh)
target_include_directories(Athena PUBLIC ../../ThirdParty/imgui)
target_include_directories(Athena PUBLIC ../../ThirdParty/imgui_sdl)