cmake_minimum_required(VERSION 3.20)
project(LongNum)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3")

add_executable(LongNum main.cpp
        realization/longnum_realization.cpp
)
target_include_directories(LongNum PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/headers
        ${CMAKE_CURRENT_SOURCE_DIR}/library
)

add_executable(tests
        tests/test.cpp
        realization/longnum_realization.cpp
        library/catch_amalgamated.cpp
)
target_include_directories(tests PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/headers
        ${CMAKE_CURRENT_SOURCE_DIR}/library
)
add_executable(tests2
        tests/test2.cpp
        realization/longnum_realization.cpp
        library/catch_amalgamated.cpp
)
target_include_directories(tests2 PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/headers
        ${CMAKE_CURRENT_SOURCE_DIR}/library
)
enable_testing()
add_test(NAME LongNumTests COMMAND tests)
add_test(NAME LongNumTests2 COMMAND tests2)