cmake_minimum_required(VERSION 3.10)
project(MyProject)

set(CMAKE_CXX_STANDARD 17)
add_subdirectory(googletest)

add_executable(OrientedList main.cpp
        OrientedGraph.cpp
        OrientedGraph.h
        VertexIterator.cpp
        VertexIterator.h
        EdgeIterator.cpp
        EdgeIterator.h
        EdgeIncidentIterator.cpp
        EdgeIncidentIterator.h
        AdjacentVertexIterator.cpp
        AdjacentVertexIterator.h)

add_executable(OrientedListTest
        test/testOrientedGraph.cpp
        OrientedGraph.h
        OrientedGraph.cpp
        test/testAdjacentVertexIterator.cpp
        AdjacentVertexIterator.h
        test/testEdgeIncidentIterator.cpp
        EdgeIncidentIterator.h
        test/testEdgeIterator.cpp
        EdgeIterator.h
        test/testVertexIterator.cpp
        VertexIterator.h)

target_link_libraries(OrientedList gtest gtest_main)

enable_testing()

add_test(NAME OrientedListTest COMMAND OrientedListTest)
add_executable(my_executable main.cpp)