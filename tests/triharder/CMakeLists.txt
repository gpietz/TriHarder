cmake_minimum_required(VERSION 3.28)
project(TriHarderTests LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# -----------------------------------------------------------------------------
# Dependencies

# Catch2
include(FetchContent)
FetchContent_Declare(
    Catch2
    GIT_REPOSITORY https://github.com/catchorg/Catch2.git
    GIT_TAG v3.6.0
)
FetchContent_MakeAvailable(Catch2)

# -----------------------------------------------------------------------------
# Project build

add_executable(${PROJECT_NAME}
        test_main.cpp
        core/result_tests.cpp
)
target_link_libraries(${PROJECT_NAME} PRIVATE TriHarderLIB Catch2::Catch2WithMain)
