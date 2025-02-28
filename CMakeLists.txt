cmake_minimum_required(VERSION 3.29)
project(LongNum)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3")

add_executable(LongNum
        longnum_realization.cpp
        test.cpp
        catch_amalgamated.cpp
        main.cpp
)