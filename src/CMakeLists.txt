cmake_minimum_required(VERSION 2.8)
project(airport)



add_library(utils utils.cpp)



add_library(flight flights.cpp)

add_library(airport airport.cpp)

target_link_libraries(airport utils)


add_library(minheap minheap.cpp)
target_link_libraries(minheap airport)



add_library(graph graph.cpp)
target_link_libraries(graph utils)


target_link_libraries(graph airport)
target_link_libraries(flight airport)
target_link_libraries(graph minheap)

add_executable(main main.cpp)
target_link_libraries(main graph airport)






