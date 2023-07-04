cmake_minimum_required(VERSION 3.17)
project(string)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(
        "${CMAKE_CURRENT_SOURCE_DIR}/googletest"
        googletest
)

# String
add_executable(string string/main.cpp string/String.cpp string/String.hpp)

add_executable(test_string string/String.cpp string/String.hpp string/tests/string_test.cpp)

target_include_directories(
        test_string PRIVATE
        "${CMAKE_CURRENT_SOURCE_DIR}/string"
)

target_link_libraries(
        test_string PRIVATE
        gtest gtest_main
)

target_compile_options(
        string PRIVATE
        -Wall -Wextra -pedantic -Werror
)

target_compile_options(
        test_string PRIVATE
        -Wall -Wextra -pedantic -Werror
)
