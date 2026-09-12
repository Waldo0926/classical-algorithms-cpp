cmake_minimum_required(VERSION 3.16)
project(classical_algorithms_cpp VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_library(classical_algorithms
    src/lis.cpp
    src/inversion_count.cpp
    src/knapsack.cpp
    src/genetic_knapsack.cpp
    src/maximum_clique.cpp
)
target_include_directories(classical_algorithms PUBLIC include)

if(MSVC)
    target_compile_options(classical_algorithms PRIVATE /W4)
else()
    target_compile_options(classical_algorithms PRIVATE -Wall -Wextra -Wpedantic)
endif()

add_executable(algorithm_demo apps/demo.cpp)
target_link_libraries(algorithm_demo PRIVATE classical_algorithms)

add_executable(algorithm_tests tests/test_algorithms.cpp)
target_link_libraries(algorithm_tests PRIVATE classical_algorithms)

add_executable(algorithm_benchmark benchmarks/benchmark.cpp)
target_link_libraries(algorithm_benchmark PRIVATE classical_algorithms)

enable_testing()
add_test(NAME algorithm_tests COMMAND algorithm_tests)
