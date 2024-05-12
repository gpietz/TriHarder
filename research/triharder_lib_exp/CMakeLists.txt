cmake_minimum_required(VERSION 3.28)
project(TriHarderLIBExp VERSION 1.0 DESCRIPTION "TriHarder Libary Experiments" LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED  ON)

add_executable(${PROJECT_NAME} src/main.cpp)
target_link_libraries(${PROJECT_NAME} PRIVATE TriHarderLIB)
