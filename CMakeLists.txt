cmake_minimum_required(VERSION 3.18)
project(week4 VERSION 0.1.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 20)

# you should change this path according to the location of or-tools folder on your computer
set(CMAKE_PREFIX_PATH "/Users/apple/Desktop/or-tools/include/ortools/algorithms/knapsack_solver.h")  
find_package(ortools CONFIG REQUIRED)

add_executable(titanic              src/main.cpp src/titanic.cpp src/titanic.h src/ortools.h)
target_link_libraries(titanic ortools::ortools)