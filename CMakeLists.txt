cmake_minimum_required(VERSION 3.29)
project(Anthills)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(GLOB_RECURSE PROJECT_SOURCES
        "${CMAKE_SOURCE_DIR}/src/*.cpp"
        "${CMAKE_SOURCE_DIR}/src/*.h"
)

add_executable(${PROJECT_NAME} ${PROJECT_SOURCES})