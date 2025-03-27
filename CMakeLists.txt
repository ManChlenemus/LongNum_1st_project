cmake_minimum_required(VERSION 3.20)
project(LongNum)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3")

include_directories(headers)
add_library(LongNumLib STATIC realization/longnum_realization.cpp)
target_include_directories(LongNumLib PUBLIC headers)

# Tests from tutor
Include(FetchContent)

FetchContent_Declare(
        Catch2
        GIT_REPOSITORY https://github.com/catchorg/Catch2.git
        GIT_TAG        v3.8.0
)

FetchContent_MakeAvailable(Catch2)
# - general -
add_executable(test_ tests/test_.cpp)
target_link_libraries(test_ PRIVATE LongNumLib Catch2::Catch2WithMain)
# - additional -
add_executable(tests tests/test.cpp)
target_link_libraries(tests PRIVATE LongNumLib Catch2::Catch2WithMain)

# тесты
enable_testing()
add_test(NAME LongNumTests COMMAND tests)
add_test(NAME test_ COMMAND test_)
