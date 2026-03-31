cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(dsac)

include_directories(${CMAKE_SOURCE_DIR}/include)

add_executable(dsac src/main.cpp)

add_executable(
    my_test 
    #tests/test_vector_1.cpp 
    #tests/test_vector_2.cpp
    #tests/test_matrix.cpp
    tests/test_linked_list.cpp
)

enable_testing()
add_test(NAME my_test COMMAND my_test)