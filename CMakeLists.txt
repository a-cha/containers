cmake_minimum_required(VERSION 3.17)
project(containers)

set(CMAKE_CXX_STANDARD 98)

add_executable(containers
        test/main.cpp
        test/list_test.hpp
        test/test.hpp
        test/stack_test.hpp
        test/queue_test.hpp
        test/vector_test.hpp
        test/map_test_std.hpp
        test/map_test_ft.hpp

        List.ipp
        List.hpp
        ListNode.hpp
        ListNode.ipp
        ListIterator.hpp
        ListIterator.ipp
        RevIterator.hpp
        RevIterator.ipp
        Algorithm.hpp
        Stack.hpp
        Stack.ipp
        Queue.ipp
        Queue.hpp
        Vector.ipp
        Vector.hpp
        VectorIterator.hpp
        VectorIterator.ipp
        Map.hpp
        MapNode.hpp
        MapIterator.hpp

        Map.ipp MapNode.ipp)
