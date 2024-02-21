cmake_minimum_required(VERSION 3.18)
project(week4 VERSION 0.1.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_PREFIX_PATH "/Users/nadezhdafomicheva/Documents/or-tools/lib/cmake")
find_package(ortools CONFIG REQUIRED)

add_executable(titanic              src/main.cpp src/titanic.cpp src/titanic.h)
target_link_libraries(titanic ortools::ortools)