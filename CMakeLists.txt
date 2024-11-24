cmake_minimum_required(VERSION 3.28)
project(IntroSort)

set(CMAKE_CXX_STANDARD 17)

add_executable(IntroSort
        ArrayGenerator.h
        ArrayGenerator.cpp
        SortTester.h
        SortTester.cpp
        QuickSort.cpp)
