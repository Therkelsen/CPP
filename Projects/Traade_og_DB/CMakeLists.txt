cmake_minimum_required(VERSION 3.5)

project(Traade_og_DB LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt5 COMPONENTS Core REQUIRED)

set(CMAKE_CXX_FLAGS_COVERAGE "${CMAKE_CXX_FLAGS_RELEASE} -fprofile-arcs -ftest-coverage")

# set up a mapping so that the Release configuration for the Qt imported target is
# used in the COVERAGE CMake configuration.
set_target_properties(Qt5::Core PROPERTIES MAP_IMPORTED_CONFIG_COVERAGE "RELEASE")

# SQL
find_package(Qt5 COMPONENTS Sql REQUIRED)

add_executable(Traade_og_DB main.cpp database.h database.cpp cargenerator.h cargenerator.cpp)

# Link libraries
target_link_libraries(Traade_og_DB PRIVATE Qt5::Sql)

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")
