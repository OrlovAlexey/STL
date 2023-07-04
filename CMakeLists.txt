cmake_minimum_required(VERSION 3.17)
project(stl)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(
        "${CMAKE_CURRENT_SOURCE_DIR}/googletest"
        googletest
)

# Unordered Map
add_executable(unordered_map unordered_map/main.cpp unordered_map/src/Pool.hpp unordered_map/src/FixedAllocator.hpp unordered_map/src/FastAllocator.hpp unordered_map/src/List.hpp unordered_map/src/UnorderedMap.hpp)

add_executable(test_unordered_map unordered_map/src/Pool.hpp unordered_map/src/FixedAllocator.hpp unordered_map/src/FastAllocator.hpp unordered_map/src/List.hpp unordered_map/src/UnorderedMap.hpp unordered_map/tests/unordered_map_test.cpp)

target_include_directories(
        unordered_map PRIVATE
        "${CMAKE_CURRENT_SOURCE_DIR}/unordered_map/src"
)

target_include_directories(
        test_unordered_map PRIVATE
        "${CMAKE_CURRENT_SOURCE_DIR}/unordered_map/src"
)

target_link_libraries(
        test_unordered_map PRIVATE
        gtest gtest_main
)

target_compile_options(
        unordered_map PRIVATE
        -Wall -Wextra -pedantic -Werror
)

target_compile_options(
        test_unordered_map PRIVATE
        -Wall -Wextra -pedantic -Werror
)