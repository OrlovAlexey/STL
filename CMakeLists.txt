cmake_minimum_required(VERSION 3.17)


project(stl)


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

# List
add_executable(list_fast_alloc list_fast_alloc/main.cpp list_fast_alloc/src/Pool.hpp list_fast_alloc/src/FixedAllocator.hpp list_fast_alloc/src/FastAllocator.hpp list_fast_alloc/src/List.hpp)

add_executable(test_list_fast_alloc list_fast_alloc/tests/list_test.cpp list_fast_alloc/src/Pool.hpp list_fast_alloc/src/FixedAllocator.hpp list_fast_alloc/src/FastAllocator.hpp list_fast_alloc/src/List.hpp)

target_include_directories(
        list_fast_alloc PRIVATE
        "${CMAKE_CURRENT_SOURCE_DIR}/list_fast_alloc/src"
)

target_include_directories(
        test_list_fast_alloc PRIVATE
        "${CMAKE_CURRENT_SOURCE_DIR}/list_fast_alloc/src"
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