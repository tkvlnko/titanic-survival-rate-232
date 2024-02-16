cmake_minimum_required(VERSION 3.18)
project(week4 VERSION 0.1.0 LANGUAGES C CXX)


set(CMAKE_CXX_STANDARD 20)

add_executable(titanic              src/main.cpp src/titanic.cpp src/titanic.h)
