set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${PROJECT_SOURCE_DIR}/cmake")

if(${CMAKE_SYSTEM_NAME} MATCHES "Emscripten")
    set(USE_FLAGS "-s USE_SDL=2")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${USE_FLAGS}")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${USE_FLAGS}")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${USE_FLAGS}")
    set(CMAKE_EXECUTABLE_SUFFIX .html)
else()
	find_package(SDL2 REQUIRED)
endif()

add_library(Utils STATIC "String.cpp" "PerfMonitor.cpp" "MessageBox.cpp")
target_precompile_headers(Utils PRIVATE pch.h)

target_link_libraries(Utils ${SDL2_LIBRARY})

target_include_directories(Utils PUBLIC ${SDL2_INCLUDE_DIR})