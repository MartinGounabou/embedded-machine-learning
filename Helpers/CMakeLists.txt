cmake_minimum_required(VERSION 3.16)
project(EML)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}  -O3  -Wall -Wextra -std=c++20")

add_executable(output main.cpp)

