cmake_minimum_required(VERSION 3.29)
project(Anthill)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(GLOB_RECURSE PROJECT_SOURCES
        "${CMAKE_SOURCE_DIR}/src/*.cpp"
        "${CMAKE_SOURCE_DIR}/src/*.h"
)


include(local_config.cmake OPTIONAL)
find_package(SFML 2.5.1 COMPONENTS graphics audio REQUIRED)

add_executable(${PROJECT_NAME} main.cpp ${PROJECT_SOURCES} "src/models/Enemy.cpp" "src/models/Enemy.h" "src/views/Enemy_render.h" "src/views/Enemy_render.cpp")

target_link_libraries(Anthill sfml-graphics sfml-audio)
file(COPY resources DESTINATION ${CMAKE_CURRENT_BINARY_DIR})