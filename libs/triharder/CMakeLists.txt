cmake_minimum_required(VERSION 3.28)
project(TriHarderLIB VERSION 1.0 DESCRIPTION "SDL2 OpenGL Library" LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# -----------------------------------------------------------------------------
# Dependencies

# SDL2
include(FetchContent)
FetchContent_Declare(
        sdl2
        GIT_REPOSITORY https://github.com/libsdl-org/SDL
        GIT_TAG release-2.30.3
)
FetchContent_MakeAvailable(sdl2)

# spdlog
include(FetchContent)
FetchContent_Declare(
        spdlog
        GIT_REPOSITORY https://github.com/gabime/spdlog.git
        GIT_TAG v1.14.1
)
FetchContent_MakeAvailable(spdlog)

# -----------------------------------------------------------------------------
# Project build

# Include directories for TriHarder lib
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/../../external/glad ${CMAKE_CURRENT_BINARY_DIR}/glad)

add_library(${PROJECT_NAME} STATIC
        src/core/application.cpp
        src/core/window.cpp
        src/core/logging.cpp
        src/core/sdl_context.h
        src/core/sdl_context.cpp
)

target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/external/glad/include)
target_link_libraries(${PROJECT_NAME} PUBLIC SDL2 glad spdlog)
