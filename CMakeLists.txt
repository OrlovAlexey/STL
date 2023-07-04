cmake_minimum_required(VERSION 3.17)
project(stl)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(
        "${CMAKE_CURRENT_SOURCE_DIR}/googletest"
        googletest
)


# List
add_executable(list_fast_alloc list_fast_alloc/main.cpp list_fast_alloc/src/Pool.hpp list_fast_alloc/src/FixedAllocator.hpp list_fast_alloc/src/FastAllocator.hpp list_fast_alloc/src/List.hpp)

add_executable(test_list_fast_alloc list_fast_alloc/tests/list_test.cpp list_fast_alloc/src/Pool.hpp list_fast_alloc/src/FixedAllocator.hpp list_fast_alloc/src/FastAllocator.hpp list_fast_alloc/src/List.hpp)

target_include_directories(
        test_list_fast_alloc PRIVATE
        "${CMAKE_CURRENT_SOURCE_DIR}/list_fact_alloc/src"
)

target_link_libraries(
        test_list_fast_alloc PRIVATE
        gtest gtest_main
)

target_compile_options(
        list_fast_alloc PRIVATE
        -Wall -Wextra -pedantic -Werror
)

target_compile_options(
        test_list_fast_alloc PRIVATE
        -Wall -Wextra -pedantic -Werror
)

