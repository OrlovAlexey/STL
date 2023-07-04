cmake_minimum_required(VERSION 3.17)
project(deque)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(
        "${CMAKE_CURRENT_SOURCE_DIR}/googletest"
        googletest
)

# Deque
add_executable(deque deque/main.cpp deque/Deque.hpp)

add_executable(test_deque deque/Deque.hpp deque/tests/deque_test.cpp)

target_include_directories(
        test_deque PRIVATE
        "${CMAKE_CURRENT_SOURCE_DIR}/deque"
)

target_link_libraries(
        test_deque PRIVATE
        gtest gtest_main
)

target_compile_options(
        deque PRIVATE
        -Wall -Wextra -pedantic -Werror
)

target_compile_options(
        test_deque PRIVATE
        -Wall -Wextra -pedantic -Werror
)
