cmake_minimum_required(VERSION 2.8)

project(test)

find_package(Catch2 REQUIRED)

add_executable(test tests.cpp)
target_link_libraries(test Catch2::Catch2WithMain airport flight graph minheap utils)
