cmake_minimum_required(VERSION 3.28)
project(TriHarder VERSION 1.0 DESCRIPTION "SDL2 OpenGL Project" LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED  ON)

include_directories(${PROJECT_SOURCE_DIR}/libs/triharder/src)

# ------------------------------------------------------------------------------
# Subprojects

add_subdirectory(libs/triharder)
add_subdirectory(research/spdlog)
add_subdirectory(tests/triharder)

# ------------------------------------------------------------------------------
# Project Build

add_executable(${PROJECT_NAME} src/main.cpp)
target_precompile_headers(${PROJECT_NAME} PUBLIC
        <vector>
        <string>
        <iostream>
)
target_link_libraries(${PROJECT_NAME} PUBLIC TriHarderLIB)

 # Copy SDL2 library to target directory
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        $<TARGET_FILE:SDL2::SDL2>
        $<TARGET_FILE_DIR:${PROJECT_NAME}>)
