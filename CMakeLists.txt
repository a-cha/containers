cmake_minimum_required(VERSION 3.17)
project(containers)

set(CMAKE_CXX_STANDARD 98)
set(GCC_COVERAGE_COMPILE_FLAGS "-Wall -Wextra -Werror -std=c++98 -pedantic")

add_definitions(${GCC_COVERAGE_COMPILE_FLAGS})

include_directories(_List _Map _Queue _Stack _Vector)

add_executable(containers
        tests/queue_test.hpp
        tests/map_test_std.hpp
        tests/list_test.hpp
        tests/test.hpp
        tests/vector_test.hpp
        tests/map_test_ft.hpp
        tests/stack_test.hpp
        tests/main.cpp
        _Vector/VectorIterator.hpp
        _Vector/Vector.hpp
        _Map/Map.hpp
        _List/ListIterator.ipp
        utils/RevIterator.ipp
        _Map/MapNode.ipp
        utils/Algorithm.hpp
        _Queue/Queue.hpp
        _List/List.hpp
        _List/ListNode.ipp
        _Stack/Stack.ipp
        _Map/MapIterator.hpp
        _Vector/VectorIterator.ipp
        _Vector/Vector.ipp
        utils/RevIterator.hpp
        _List/ListIterator.hpp
        _Map/Map.ipp
        _Map/MapNode.hpp
        _List/List.ipp
        _Queue/Queue.ipp
        _Map/MapIterator.ipp
        _Stack/Stack.hpp
        _List/ListNode.hpp
        )
