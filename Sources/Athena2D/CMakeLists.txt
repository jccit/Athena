set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${PROJECT_SOURCE_DIR}/cmake")

if(${CMAKE_SYSTEM_NAME} MATCHES "Emscripten")
    set(USE_FLAGS "-s USE_SDL=2 -s USE_SDL_IMAGE=2 -s SDL2_IMAGE_FORMATS='[\"png\"]' -s NO_DISABLE_EXCEPTION_CATCHING --preload-file sprites/ --preload-file scripts/ --use-preload-plugins")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${USE_FLAGS}")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${USE_FLAGS}")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${USE_FLAGS}")
    set(CMAKE_EXECUTABLE_SUFFIX .html)
else()
	find_package(SDL2 REQUIRED)
	find_package(SDL2_image REQUIRED)
endif()

# Enable additional defines for the Debug build configuration
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -D_DEBUG")
set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -D_DEBUG")

file(GLOB SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp ${CMAKE_CURRENT_SOURCE_DIR}/**/*.cpp)
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
# target_link_libraries(Athena squirrel sqstdlib)
if(WIN32)
	target_link_libraries(Athena simplesquirrel_static)
else()
	target_link_libraries(Athena simplesquirrel)
endif()

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